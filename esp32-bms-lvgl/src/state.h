// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
#ifndef FW_VERSION
#define FW_VERSION "1.0-dev"   // fallback; the real version is injected from git by version.py at build time
#endif
#ifndef FW_GIT_SHA
#define FW_GIT_SHA "0000000"   // short HEAD SHA (build-time); used for the update-available check
#endif
static volatile bool updAvail = false;   // a newer GitHub release than this build exists
static bool autoUpdate = false;          // when set, self-OTA from a new release automatically
static char updTag[24] = "";             // latest release tag on GitHub
static char instTag[24] = "";            // tag we last installed (NVS); empty → compare to FW_VERSION
static char updUrl[160] = "";            // firmware.bin download URL of the latest release
static volatile bool updGo = false;      // request: download + flash the latest release now
static volatile int updProgress = -1;    // -1 idle · 0..100 flashing % · -2 failed
static bool updPopup = false;            // top-bar update icon tapped → details modal
static int updBoxL = 0, updBoxR = 0;     // top-bar update-icon hit region
#define BL_CH_FREQ 5000
#define BL_CH_RES 8
#define BMS_TX_PIN 17               // BMS1: ESP TX -> BMS RX
#define BMS_RX_PIN 18               // BMS1: ESP RX <- BMS TX
#define BMS2_TX_PIN 16              // BMS2: ESP TX -> BMS RX (IO16, on the 8P)
#define BMS2_RX_PIN 15             // BMS2: ESP RX <- BMS TX (IO15, on the 8P)

// ---- palette (identical to the original) ----
#define C_BG 0x04060c
#define C_CARD 0x121824
#define C_CARD_HI 0x1b2436   // slightly lighter card top → subtle depth sheen
#define C_BORDER 0x2a3342
#define C_TEXT 0xeaf2fb
#define C_MUTED 0x7e8ba0
#define C_ACCENT 0x3df0a8
#define C_CYAN 0x22d3ee
#define C_WARN 0xfbbf24
#define C_BAD 0xfb7185
#define C_DISCHG 0x968aff            // discharging accent — purple/blue, slightly lightened (green = charging)

#define NCELLS 4                    // demo/fallback cell count
#define MAXCELLS 24                 // JK realtime frame carries up to 24 cells; actual count detected at runtime
#define NCAP 168
#define Wd 480
#define Ht 320

// top-bar geometry (matches original)
#define TAB_W 88              // narrower so BAT1+BAT2 fit the left (SOC) column (ends ~192, left of rx=200)
#define TAB1_X 8
#define TAB2_X 104
#define GEAR_X (Wd - 38)
#define GEAR_Y 6
#define GEAR_W 30
#define BED_W 40
#define BED_X (GEAR_X - 8 - BED_W)

// This AXS15231B QSPI panel only displays correctly with a FULL-frame write
// (raw per-shape and partial-region pushes show black / tear). So LVGL renders
// into a persistent Arduino_Canvas framebuffer and the whole canvas is flushed
// once per frame (~40ms → ~25fps ceiling). We keep each frame cheap by only
// redrawing the regions that changed (the canvas keeps the rest).
// Canvas with a cache-friendly rotated blit. The framebuffer lives in PSRAM
// (320x480x2 = 300KB, too big for internal RAM). The stock Arduino_GFX rotate
// writes the framebuffer with a 640-byte stride → every pixel is a PSRAM/cache
// miss (~150ms for a full screen). blit() instead writes each framebuffer column
// CONTIGUOUSLY (burst-friendly) and reads the small internal LVGL buffer strided
// → the same 90° rotation, ~5-8x faster.
class FastCanvas : public Arduino_Canvas {
public:
    FastCanvas(int16_t w, int16_t h, Arduino_G *o, int16_t ox, int16_t oy, uint8_t r)
        : Arduino_Canvas(w, h, o, ox, oy, r) {}
    void blit(int x, int y, int w, int h, const uint16_t *src) {
        uint16_t *fb = getFramebuffer();
        const int FBH = _height;          // physical height in this rotation = 320
        const int top = _max_y;           // 319
        for (int i = 0; i < w; i++) {
            uint16_t *d = fb + (int32_t)(x + i) * FBH + (top - y);   // landscape (x+i, y) in fb
            const uint16_t *s = src + i;
            for (int j = 0; j < h; j++) { *d-- = *s; s += w; }       // ly++ → fb addr-- (contiguous)
        }
    }
};

Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *g = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_res_W, TFT_res_H);
FastCanvas *gfx = new FastCanvas(TFT_res_W, TFT_res_H, g, 0, 0, TFT_rot);
AXS15231B_Touch touch(Touch_SCL, Touch_SDA, Touch_INT, Touch_ADDR, TFT_rot);
static bool gfxDirty = false;
static volatile uint32_t g_flushUs = 0;     // last full-canvas flush duration (µs)
static volatile uint32_t g_fps = 0;         // flushes/sec measured over the last second

// ---- simulated BMS data ----
struct Bms {
    float soc, v, i, tMos, tp1, tp2;
    float cell[MAXCELLS]; float cellRes[MAXCELLS]; int nCells; float balCur;   // per-cell V + resistance, detected count, balance current
    float cap[NCAP], pwr[NCAP];
    int capCount; float capSpanDays;
    int pwrCount; float pwrSpanMin;   // power graph: short rolling window (minutes)
    float peakChg, peakDis;
    bool bmsOk;                 // BMS-reported operational state (errors bitmask == 0)
    uint32_t errFlags;          // BMS protection/warning bitmask (realtime offset 166)
    bool chgMos, disMos, balWork;  // actual charge/discharge MOSFET + balancer state from the BMS
    uint32_t cycles; uint8_t soh;  // cycle count + state-of-health % (realtime 182 / 190)
    uint32_t uptime;            // BMS-reported total runtime (seconds); 0 = unknown
    bool uptimeOk;              // device-info read succeeded
};
static Bms bms[2];
// JK protection/warning bitmask bit → name (realtime errors field, offset 166). Bits 3,29-31 unused.
#define NERR 29   // number of defined protection/warning bits (loop bound for ERR_NAMES/ERR_KEY)
static const char *ERR_NAMES[NERR] = {
    "Wire resistance", "MOSFET over-temp", "Cell count mismatch", "", "Fully charged",
    "Pack over-voltage", "Charge over-current", "Charge short-circuit", "Charge over-temp",
    "Charge under-temp", "Coprocessor comm err", "Cell under-voltage", "Pack under-voltage",
    "Discharge over-current", "Discharge short-circuit", "Discharge over-temp", "Charge MOSFET fault",
    "Discharge MOSFET fault", "GPS disconnected", "Change password", "Discharge-on failed",
    "Battery over-temp", "Temp sensor anomaly", "PL module anomaly", "SCP release failed",
    "Discharge OCP2", "Discharge OCP3", "Discharge under-temp", "GPS remote lock"};
// i18n keys parallel to ERR_NAMES (English kept for MQTT/web). 0xFF = no name (skip).
static const uint8_t ERR_KEY[NERR] = {
    K_E_WIRE_RES, K_E_MOS_OT, K_E_CELL_MISMATCH, 0xFF, K_E_FULLY_CHARGED, K_E_PACK_OV, K_E_CHG_OC,
    K_E_CHG_SC, K_E_CHG_OT, K_E_CHG_UT, K_E_COPROC, K_E_CELL_UV, K_E_PACK_UV, K_E_DIS_OC,
    K_E_DIS_SC, K_E_DIS_OT, K_E_CHG_MOS_FAULT, K_E_DIS_MOS_FAULT, K_E_GPS_DISC, K_E_CHG_PWD,
    K_E_DIS_ON_FAIL, K_E_BAT_OT, K_E_TEMP_ANOM, K_E_PL_ANOM, K_E_SCP_REL_FAIL, K_E_DIS_OCP2,
    K_E_DIS_OCP3, K_E_DIS_UT, K_E_GPS_LOCK};
static const char *errNameL(int bit) { return (bit < NERR && ERR_KEY[bit] != 0xFF) ? T(ERR_KEY[bit]) : ""; }
// Real graph history: one sample / 5 min per BMS, ring-buffered to HIST_N (=2016 = 7 days),
// persisted to NVS so the trends survive a reboot. Demo mode uses genCap() instead.
// Compact storage: SOC fits a byte, pack power an int16 (W) → ~6 KB/BMS in NVS.
#define HIST_INTERVAL_MS 300000UL    // 5 min between samples → HIST_N samples span 7 days
#define HIST_N 2016                  // 5 min × 7 days
static uint8_t  histCap[2][HIST_N];  // SOC %, oldest→newest
static int16_t  histPwr[2][HIST_N];  // pack power (W), oldest→newest
static int8_t   histTmp[2][HIST_N];  // MOSFET temp (°C), oldest→newest
static uint16_t histCount[2] = {0, 0};
static uint32_t histLastMs[2] = {0, 0};
static bool histDirty = false; static uint32_t histDirtyAt = 0;
// Long-term capacity / state-of-health trend: one BMS-reported sample per calendar month per
// pack (capacity fade is a months-to-years signal). Baseline = first recorded full capacity
// ("as new"). Persisted to NVS; all access on core 1 (sampled in bmsPoll_cb). SOH_N ≈ 3 years.
#define SOH_N 36
struct SohPt { uint16_t mon; uint16_t capX10; uint8_t soh; uint16_t cyc; };   // mon=year*12+month; capX10 = 0.1 Ah units
static SohPt    sohHist[2][SOH_N];
static uint16_t sohCount[2] = {0, 0};
static float    sohBaseAh[2] = {0, 0};   // first recorded full-charge capacity (Ah) = "as new" reference
static bool sohDirty = false;
// Lifetime cumulative energy per pack (Wh), integrated from v*i every poll while live.
// Persisted alongside the graph history (NVS "hist") on its ~30-min save cadence.
static double lifeWhIn[2] = {0, 0}, lifeWhOut[2] = {0, 0};
static uint32_t lifeLastMs[2] = {0, 0};
// Power graph: fast rolling 10-minute window, one sample per refresh (~1 s), per BMS.
#define PWR_DT 1000UL                // sample interval (ms) ≈ one per data refresh
#define PWR_WIN 600                  // 600 samples × 1 s = 10 minutes
static int16_t pwrWin[2][PWR_WIN];   // pack power (W), oldest→newest
static uint16_t pwrWinN[2] = {0, 0};
static uint32_t pwrWinLast[2] = {0, 0};
static bool bmsLive[2] = {false, false};   // per-BMS: real device responded over Modbus this poll
// Modbus comms health (per pack) — updated on the poll (core 0), read by the info popup / /api / /metrics
// (core 1). Same accepted cross-core treatment as bms[]: a torn read is cosmetic, self-corrects next poll.
static uint32_t commAttempts[2] = {0, 0}, commOk[2] = {0, 0};       // poll attempts vs valid replies → success rate
static uint16_t commConsecFail[2] = {0, 0}, commReconnects[2] = {0, 0};   // current fail streak; offline→online transitions
static uint8_t  commLastErr[2] = {0, 0};   // last failure: 0=ok, 1=no/short reply (timeout), 2=bad frame/CRC
static bool demoMode = false;              // ON = both BMSes simulated; OFF = poll real BMS 1 (addr 1) & 2 (addr 2)
static float packFullAh[2] = {100.0f, 100.0f};   // full-charge capacity from each BMS (Ah)
// Both packs are Modbus slave address 1, each on its OWN UART (no shared bus).
HardwareSerial bmsSerial(1);           // BMS1 UART: RX=IO18, TX=IO17, 115200
HardwareSerial bmsSerial2(2);          // BMS2 UART: RX=IO15, TX=IO16, 115200
static HardwareSerial &bmsPort(int idx) { return idx == 0 ? bmsSerial : bmsSerial2; }   // each pack on its own bus
// configurable UART pins (defaults match the connectors): B1TX, B1RX, B2TX, B2RX
static int bmsPin[4] = {BMS_TX_PIN, BMS_RX_PIN, BMS2_TX_PIN, BMS2_RX_PIN};
// GPIOs broken out on the 4P + 8P connectors (safe to assign; avoids display/touch/USB pins)
static const uint8_t VALIDPINS[] = {5, 6, 7, 9, 14, 15, 16, 17, 18, 46};
#define NVALID ((int)(sizeof(VALIDPINS) / sizeof(VALIDPINS[0])))
// Cycle a UART pin to the next valid GPIO, skipping pins already assigned to any other
// slot — TX==RX or a pin shared between the two packs would silently break both reads.
static bool pinTaken(int p, int slot) { for (int i = 0; i < 4; i++) if (i != slot && bmsPin[i] == p) return true; return false; }
static int nextPin(int cur, int slot) {
    int start = 0; for (int i = 0; i < NVALID; i++) if (VALIDPINS[i] == cur) { start = i; break; }
    for (int k = 1; k <= NVALID; k++) { int p = VALIDPINS[(start + k) % NVALID]; if (!pinTaken(p, slot)) return p; }
    return cur;   // all other pins taken (can't happen with 10 valid pins / 4 slots)
}
static void bmsBegin() {                // (re)open both UARTs with the current pin assignment
    bmsSerial.setRxBufferSize(512);  bmsSerial2.setRxBufferSize(512);   // settings reply ~255B — don't overflow the default 256B FIFO
    bmsSerial.end();  bmsSerial.begin(115200, SERIAL_8N1, bmsPin[1], bmsPin[0]);   // (rx, tx)
    bmsSerial2.end(); bmsSerial2.begin(115200, SERIAL_8N1, bmsPin[3], bmsPin[2]);
}
enum View { V_BMS1 = 0, V_BMS2 = 1, V_SETTINGS = 2 };
static int view = V_BMS1;
static uint32_t lastSwitch = 0, manualUntil = 0;
static uint32_t intervalMs = 5000;
static const uint32_t PAUSE_MS = 30000;

// ---- settings state ----
enum SubTab { ST_BMS = 0, ST_WIFI = 1, ST_SYSTEM = 2 };
static int subTab = ST_SYSTEM;
static bool autoSwitch = true;
static int brightness = 90;
static int autoSleepMin = 0;                 // 0 = never; else 2/5/30/120
static bool bmsCharge[2] = {true, true}, bmsDischarge[2] = {true, true}, bmsBalancer[2] = {false, false};
static int cfgBms = 0;              // which BMS the BMS-settings tab configures
static int numBms = 1;             // number of BMS packs in use (1 or 2); default 1
static bool tempF = false, fmt12 = false, wifiAuto = true;
static int simSpeed = 1;            // demo data speed (1/2/5x)
static char webUser[24] = "admin";  // web portal + OTA login name (editable from device Settings, stored in NVS)
static char webPass[24] = "jkbms";  // default; change it from device Settings or the web page's Security section
static bool freshWebPass = false;   // set when loadSettings generated a random default → persist it once
static void webBegin();             // defined in web_portal.h (started on first WiFi connect)
static void webLoop();
static void webOtaApplyPass();      // defined in web_portal.h; re-arms the espota password after a change
// MQTT / Home Assistant config (set from the web portal, persisted in NVS)
static bool mqttEnabled = false; static int mqttPort = 1883;
static char mqttHost[64] = "", mqttUser[40] = "", mqttPass[40] = "";
static volatile bool mqttReconnect = false;  // web (UI core) sets this on config change → mqttLoop (net core) re-applies
static volatile bool mqttUp = false;         // broker connection state; written by the net task, read by web/UI
static void mqttLoop();             // defined in mqtt.h
// Threshold push alerts — POST the message body to a webhook (ntfy.sh topic URL, or any
// endpoint that accepts a text body). Edge-triggered with a re-arm cooldown (no spam).
static bool alertEnabled = false;
static char alertUrl[120] = "";              // e.g. https://ntfy.sh/my-jkbms-topic
static int alSocLo = 15, alTempHi = 55, alDeltaHi = 300;   // SOC %, temp °C, cell delta mV thresholds
static bool alOnFault = true;                // also alert on any BMS protection fault
static uint8_t alState[2] = {0, 0};          // per-pack bitmask of currently-active conditions (edge detect)
static void alertLoop();                     // defined in alerts.h
static bool alertSend(const char *msg);      // defined in alerts.h (also used by the web Test button)
// Web "Test" button: queued to the core-0 net task (a dead webhook blocks up to ~8s of
// TLS+timeouts — never on the UI core). Result surfaces in /api as alTest.
static volatile bool alTestGo = false;       // web (UI core) requests a test send; netTask performs it
static volatile int8_t alTestRes = -1;       // -1 idle · -2 sending · 0 failed · 1 delivered
// Weather (geo-IP + Open-Meteo); fetched in weather.h, drawn in the top bar
struct WxDay { int code; int tmax, tmin; int pop; };   // pop = max precipitation probability %
static bool wxOk = false; static int wxCurTemp = 0, wxCurCode = -1; static WxDay wxDay[5]; static int wxDays = 0;
static char wxCity[28] = "";
static int wxHttp = 0;              // diagnostic: last Open-Meteo HTTP code (negative = HTTPClient error)
static time_t wxFetchedAt = 0;      // epoch of the last successful fetch (persisted → survives reboot)
static bool wxFreshThisBoot = false;// a live fetch has succeeded since power-on (else the data is restored-from-NVS)
static volatile bool wxDirty = false;   // wxFetch (core 0) flags a new forecast; core 1 flushes it to NVS (prefs is core-1-only)
#define WX_STALE_SECS 3600          // weather older than this (or never refreshed this boot) → dim the glyph
// "stale" = we're showing weather but it isn't current: restored from NVS with no live fetch yet,
// or the last good fetch is over an hour old (WiFi dropped / Open-Meteo failing). The top bar greys
// the glyph + temp so a frozen reading isn't mistaken for live.
static bool wxStale() {
    if (!wxOk) return false;
    if (!wxFreshThisBoot) return true;                 // restored from NVS, not yet refreshed this boot
    time_t now = time(nullptr);
    return wxFetchedAt && now > wxFetchedAt && (now - wxFetchedAt) > WX_STALE_SECS;
}
static void weatherLoop();          // defined in weather.h
static void saveWeather();          // defined in weather.h; only ever called on core 1 (NVS write)
static bool timeSynced = false;     // NTP has produced a valid wall-clock
// Timezone (Settings → System → Timezone). POSIX TZ strings with DST rules. newlib caches
// TZ per task — only core 1 (render/loop) formats local time, and applyTz runs there.
struct TzDef { const char *name; const char *tz; };
static const TzDef TZDEFS[] = {
    {"UTC",          "UTC0"},
    {"London",       "GMT0BST,M3.5.0/1,M10.5.0"},
    {"Berlin/Paris", "CET-1CEST,M3.5.0,M10.5.0/3"},
    {"Athens",       "EET-2EEST,M3.5.0/3,M10.5.0/4"},
    {"Moscow",       "MSK-3"},
    {"India",        "IST-5:30"},
    {"China",        "CST-8"},
    {"Japan",        "JST-9"},
    {"Sydney",       "AEST-10AEDT,M10.1.0,M4.1.0/3"},
    {"Brazil",       "<-03>3"},
    {"US East",      "EST5EDT,M3.2.0,M11.1.0"},
    {"US Central",   "CST6CDT,M3.2.0,M11.1.0"},
    {"US Mountain",  "MST7MDT,M3.2.0,M11.1.0"},
    {"US Pacific",   "PST8PDT,M3.2.0,M11.1.0"},
};
#define NTZ ((int)(sizeof(TZDEFS) / sizeof(TZDEFS[0])))
#define TZ_DEFAULT 2                // Berlin/Paris (CET) — matches the previously hardcoded zone
static int tzSel = TZ_DEFAULT;      // index into TZDEFS; persisted in NVS ("tz")
static const char *tzStr() { return TZDEFS[tzSel].tz; }
static void applyTz() { setenv("TZ", tzStr(), 1); tzset(); }   // call on core 1 only
static int sysScroll = 0;           // System-tab scroll offset (px)
static int bmsScroll = 0;           // BMS-tab scroll offset (px)
static bool infoPopup = false;
static bool wxPopup = false;            // weather forecast modal (tap the top-bar weather glyph)
static int wxBoxL = 0, wxBoxR = 0;      // hit region of the top-bar weather glyph+temp (set in drawTabs)
// raw settings block (Modbus reg 0x1000) per BMS — byte k == web frame offset k+6.
// Filled by two reads: 0x1000 (bytes 0..249) + a tail read for the bitmask region.
static uint8_t setRaw[2][300];
static bool setOk[2] = {false, false};      // main block read ok
static bool setOk2[2] = {false, false};     // tail (bitmask/heating/sleep) read ok
static int editIdx = -1;            // index into SETDEFS being edited (-1 = none)
static int editBms = 0; static char editStr[12] = "";   // keypad entry buffer
static bool pendingSleep = false, standby = false;
static uint32_t lastActivity = 0;
// power saving
static bool ecoMode = true;         // throttle refresh when idle
static int dimAfterSec = 60;        // auto-dim timeout (0 = off)
static int appliedB = 90;           // currently applied backlight %
static bool ecoActive = false;      // eco (low-fps) state active
#define DIM_LEVEL 12                 // backlight % when dimmed
#define ECO_IDLE_MS 20000UL          // idle before low-fps kicks in
static int idleScreen = 0;           // screensaver: 0=Off 1=HUD 2=Init 3=Radar 4=Arcade 5=Security
static int saverAfterSec = 0;        // inactivity before the screensaver kicks in (0 = off; only the no-data fallback applies)
#define IDLE_DELAY 8000UL            // offline + no touch this long → show the screensaver (no-data fallback)
// ---- PIN lock (separate from the screensaver) ----
static int lockAfterSec = 0;         // inactivity before auto-lock (0 = Never); else 30/60/300/1800/3600
static char lockPin[7] = "";         // 6-digit PIN; empty = lock disabled even if the timer is set
static bool locked = false;          // PIN required to use the device
static bool lockSetMode = false;     // settings is capturing a NEW PIN (modal numpad)
static char lockEntry[8] = ""; static int lockEntryLen = 0;
static uint32_t lockWrongUntil = 0;  // brief "wrong PIN" feedback window
static lv_timer_t *barTimer = nullptr, *dataTimer = nullptr;
static volatile bool cfgDirty = false; static volatile uint32_t cfgDirtyAt = 0;   // debounced settings save (set from UI + net cores)
// wifi
#define MAXNET 10
static char netSsid[MAXNET][33];
static int netRssi[MAXNET];
static bool netEnc[MAXNET];
static int netCount = 0, wifiSel = -1, wifiScroll = 0, kbMode = 0;
static bool kbActive = false, wifiScanning = false, wifiSaved = false;
enum KbTarget { KBT_WIFI = 0, KBT_WUSER, KBT_WPASS };   // what the text keyboard is editing
static int kbTarget = KBT_WIFI;
static char wifiPass[65] = ""; static int wifiPassLen = 0;   // WPA2 passphrases run to 63 chars; also the scratch buffer for web user/pass entry
static char wifiMsg[56] = "";   // empty → renderWifiTab shows the localized "tap Scan" hint
static char connSsid[33] = "", connPass[65] = "";
static Preferences prefs;
// Guards all Modbus bus access (bmsRead on the UI core vs. bmsSet from the core-0 net
// task's MQTT command handler). The poll try-takes (skips if a write is mid-flight);
// writes wait. Created in setup() before the net task starts.
static SemaphoreHandle_t busMux = nullptr;
static void setBrightness(int pct) { ledcWrite(TFT_BL, map(constrain(pct, 5, 100), 0, 100, 0, 255)); }

