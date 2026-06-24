// JK BMS LVGL dashboard — Guition JC3248W535 (480x320 landscape).
// Faithful pixel-for-pixel reproduction of the esp32-bms/ Arduino_GFX dashboard,
// drawn through LVGL's vector draw API (so the text is anti-aliased). Every shape,
// coordinate and colour matches the original; only the fonts are nicer. Data is
// simulated; tabs auto-switch (BMS1<->BMS2), a tap pauses it for 30s.
#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <WiFi.h>
#include <esp_mac.h>
#include <Preferences.h>
#include <time.h>
#include <math.h>
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"

#define FW_VERSION "0.4.0"
#define BL_CH_FREQ 5000
#define BL_CH_RES 8
#define BMS_TX_PIN 17               // BMS1: ESP TX -> BMS RX
#define BMS_RX_PIN 18               // BMS1: ESP RX <- BMS TX
#define BMS2_TX_PIN 16              // BMS2: ESP TX -> BMS RX (IO16, on the 8P)
#define BMS2_RX_PIN 15             // BMS2: ESP RX <- BMS TX (IO15, on the 8P)

// ---- palette (identical to the original) ----
#define C_BG 0x04060c
#define C_CARD 0x121824
#define C_BORDER 0x2a3342
#define C_TEXT 0xeaf2fb
#define C_MUTED 0x7e8ba0
#define C_ACCENT 0x3df0a8
#define C_CYAN 0x22d3ee
#define C_WARN 0xfbbf24
#define C_BAD 0xfb7185

#define NCELLS 4
#define NCAP 168
#define Wd 480
#define Ht 320

// top-bar geometry (matches original)
#define TAB_W 104
#define TAB1_X 8
#define TAB2_X 120
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

// ---- simulated BMS data ----
struct Bms {
    float soc, v, i, tMos, tp1, tp2;
    float cell[NCELLS];
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
// Real graph history: one sample / 5 min per BMS, ring-buffered to HIST_N (=2016 = 7 days),
// persisted to NVS so the trends survive a reboot. Demo mode uses genCap() instead.
// Compact storage: SOC fits a byte, pack power an int16 (W) → ~6 KB/BMS in NVS.
#define HIST_INTERVAL_MS 300000UL    // 5 min between samples → HIST_N samples span 7 days
#define HIST_N 2016                  // 5 min × 7 days
static uint8_t  histCap[2][HIST_N];  // SOC %, oldest→newest
static int16_t  histPwr[2][HIST_N];  // pack power (W), oldest→newest
static uint16_t histCount[2] = {0, 0};
static uint32_t histLastMs[2] = {0, 0};
static bool histDirty = false; static uint32_t histDirtyAt = 0;
// Power graph: fast rolling 10-minute window, one sample per refresh (~1 s), per BMS.
#define PWR_DT 1000UL                // sample interval (ms) ≈ one per data refresh
#define PWR_WIN 600                  // 600 samples × 1 s = 10 minutes
static int16_t pwrWin[2][PWR_WIN];   // pack power (W), oldest→newest
static uint16_t pwrWinN[2] = {0, 0};
static uint32_t pwrWinLast[2] = {0, 0};
static bool bmsLive[2] = {false, false};   // per-BMS: real device responded over Modbus this poll
static bool demoMode = false;              // ON = both BMSes simulated; OFF = poll real BMS 1 (addr 1) & 2 (addr 2)
static float packFullAh[2] = {100.0f, 100.0f};   // full-charge capacity from each BMS (Ah)
HardwareSerial bmsSerial(1);           // BMS1 UART: RX=IO18, TX=IO17, 115200
HardwareSerial bmsSerial2(2);          // BMS2 UART: RX=IO15, TX=IO16, 115200
static HardwareSerial &bmsPort(int idx) { return idx == 0 ? bmsSerial : bmsSerial2; }   // each pack on its own bus
// configurable UART pins (defaults match the connectors): B1TX, B1RX, B2TX, B2RX
static int bmsPin[4] = {BMS_TX_PIN, BMS_RX_PIN, BMS2_TX_PIN, BMS2_RX_PIN};
// GPIOs broken out on the 4P + 8P connectors (safe to assign; avoids display/touch/USB pins)
static const uint8_t VALIDPINS[] = {5, 6, 7, 9, 14, 15, 16, 17, 18, 46};
#define NVALID ((int)(sizeof(VALIDPINS) / sizeof(VALIDPINS[0])))
static int nextPin(int cur) { for (int i = 0; i < NVALID; i++) if (VALIDPINS[i] == cur) return VALIDPINS[(i + 1) % NVALID]; return VALIDPINS[0]; }
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
static bool tempF = false, fmt12 = false, wifiAuto = true;
static int simSpeed = 1;            // demo data speed (1/2/5x)
#define WEB_USER "admin"            // web portal + OTA login (password is changeable, stored in NVS)
static char webPass[24] = "jkbms";  // default; change it from the web page's Security section
static void webBegin();             // defined in web_portal.h (started on first WiFi connect)
static void webLoop();
static int sysScroll = 0;           // System-tab scroll offset (px)
static int bmsScroll = 0;           // BMS-tab scroll offset (px)
static bool infoPopup = false;
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
static int idleScreen = 0;           // no-data screen: 0=Dashboard 1=HUD 2=Init 3=Radar
#define IDLE_DELAY 8000UL            // offline + no touch this long → show the idle screen
static lv_timer_t *barTimer = nullptr, *dataTimer = nullptr;
static bool cfgDirty = false; static uint32_t cfgDirtyAt = 0;   // debounced settings save
// wifi
#define MAXNET 10
static char netSsid[MAXNET][33];
static int netRssi[MAXNET];
static bool netEnc[MAXNET];
static int netCount = 0, wifiSel = -1, wifiScroll = 0, kbMode = 0;
static bool kbActive = false, wifiScanning = false, ntpStarted = false, wifiSaved = false;
static char wifiPass[33] = ""; static int wifiPassLen = 0;
static char wifiMsg[56] = "tap Scan to find networks";
static char connSsid[33] = "", connPass[33] = "";
static Preferences prefs;
static void setBrightness(int pct) { ledcWrite(TFT_BL, map(constrain(pct, 5, 100), 0, 100, 0, 255)); }

static void genCap(Bms &b, float span, int count) {
    if (count > NCAP) count = NCAP; if (count < 2) count = 2;
    b.capSpanDays = span; b.capCount = count;
    for (int i = 0; i < count; i++) {
        float d = (float)i / (count - 1) * span;
        float v = 64 + 26 * sinf((d - 0.3f) * 2 * PI) + 6 * sinf(d * 0.9f) + 3 * sinf(i * 1.3f);
        b.cap[i] = v < 12 ? 12 : (v > 99 ? 99 : v);
        b.pwr[i] = 220 * cosf((d - 0.3f) * 2 * PI) + 30 * sinf(i * 1.7f);
    }
}
static void simInit() { genCap(bms[0], 7, 168); genCap(bms[1], 1, 48); }
// Append one real sample to BMS idx's history (ring-buffer, drops the oldest when full).
static void histAppend(int idx, float soc, float watt) {
    if (histCount[idx] >= HIST_N) {
        memmove(histCap[idx], histCap[idx] + 1, (HIST_N - 1) * sizeof(histCap[0][0]));
        memmove(histPwr[idx], histPwr[idx] + 1, (HIST_N - 1) * sizeof(histPwr[0][0]));
        histCount[idx] = HIST_N - 1;
    }
    int s = (int)(soc + 0.5f); s = s < 0 ? 0 : s > 100 ? 100 : s;
    float w = watt < -32000 ? -32000 : watt > 32000 ? 32000 : watt;
    histCap[idx][histCount[idx]] = (uint8_t)s;
    histPwr[idx][histCount[idx]] = (int16_t)w;
    histCount[idx]++;
    histDirty = true; histDirtyAt = millis();
}
// Sample any live BMS once per HIST_INTERVAL (first reading seeds it immediately).
static void histSample() {
    uint32_t now = millis();
    for (int t = 0; t < 2; t++) {
        if (!bmsLive[t]) continue;
        if (bms[t].soc < 1) continue;                  // skip implausible 0% (BMS not settled / bad read)
        if (histCount[t] == 0 || (now - histLastMs[t]) >= HIST_INTERVAL_MS) {
            histAppend(t, bms[t].soc, bms[t].v * bms[t].i);
            histLastMs[t] = now;
        }
    }
}
// Append the current power to each pack's 10-min window (once per PWR_DT). Samples
// whenever there's data to plot (live, or demo sim). Returns true if a sample landed.
static bool pwrSample() {
    uint32_t now = millis(); bool added = false;
    for (int t = 0; t < 2; t++) {
        if (!demoMode && !bmsLive[t]) continue;             // nothing to sample
        if (pwrWinN[t] != 0 && (now - pwrWinLast[t]) < PWR_DT) continue;
        float w = -(bms[t].v * bms[t].i);                  // draw-positive: discharging (using power) reads up, charging down
        if (w < -32000) w = -32000; if (w > 32000) w = 32000;
        if (pwrWinN[t] >= PWR_WIN) {                        // ring: drop oldest
            memmove(pwrWin[t], pwrWin[t] + 1, (PWR_WIN - 1) * sizeof(pwrWin[0][0]));
            pwrWinN[t] = PWR_WIN - 1;
        }
        pwrWin[t][pwrWinN[t]++] = (int16_t)w;
        pwrWinLast[t] = now; added = true;
    }
    return added;
}
static void simStep(uint32_t nowMs) {
    float s = nowMs / 1000.0f * simSpeed;
    for (int t = 0; t < 2; t++) {
        if (!demoMode) continue;                 // live mode shows only real data (or a stale/offline state)
        float ph = t * 2.1f;
        bms[t].soc = 62 + 30 * sinf(s * 0.05f + ph);
        bms[t].i = 28 * sinf(s * 0.18f + ph) + (t ? -4 : 3);
        bms[t].v = 13.2f + 0.35f * sinf(s * 0.12f + ph) + bms[t].i * 0.004f;
        bms[t].tMos = 33 + fabsf(bms[t].i) * 0.45f + 3 * sinf(s * 0.07f + ph);
        bms[t].tp1 = 24 + 3 * sinf(s * 0.03f + ph) + t;
        bms[t].tp2 = 25 + 3 * sinf(s * 0.04f + ph + 1) + t;
        for (int i = 0; i < NCELLS; i++) bms[t].cell[i] = bms[t].v / NCELLS + 0.015f * sinf(s * 0.5f + i * 1.7f + ph);
        bms[t].bmsOk = true; bms[t].errFlags = 0;
        bms[t].chgMos = bms[t].disMos = true; bms[t].soh = 100;   // healthy simulated pack (else status pill shows "FET off")
        float p = bms[t].v * bms[t].i;
        if (p > bms[t].peakChg) bms[t].peakChg = p;
        if (-p > bms[t].peakDis) bms[t].peakDis = -p;
    }
}
// ---- real BMS over Modbus RTU (JK "RS485 Modbus", TTL on the GPS/UART port) ----
static uint16_t mbCrc(const uint8_t *d, int n) {
    uint16_t c = 0xFFFF;
    for (int i = 0; i < n; i++) { c ^= d[i]; for (int b = 0; b < 8; b++) c = (c & 1) ? (c >> 1) ^ 0xA001 : c >> 1; }
    return c;
}
// Read the 0x1200 status block from one BMS (Modbus addr) into bms[idx]. Sets bmsLive[idx].
static void bmsReadAddr(uint8_t addr, int idx) {
    HardwareSerial &S = bmsPort(idx);
    uint8_t req[8] = {addr, 3, 0x12, 0x00, 0x00, 0x71, 0, 0};
    uint16_t crc = mbCrc(req, 6); req[6] = crc & 0xFF; req[7] = crc >> 8;
    while (S.available()) S.read();
    S.write(req, 8); S.flush();
    // Reply (5 + 0x71*2 ≈ 231 bytes) takes ~25 ms at 115200; the loop exits the
    // instant a full frame lands, so this timeout only bites when a pack is silent.
    static uint8_t r[260]; int n = 0; uint32_t t0 = millis();
    while (millis() - t0 < 70) { while (S.available() && n < 260) r[n++] = S.read(); if (n >= 5 && n >= 3 + r[2] + 2) break; }
    if (n < 5 || r[0] != addr || r[1] != 3) { bmsLive[idx] = false; return; }
    int bc = r[2]; if (n < 3 + bc + 2 || (r[3 + bc] | (r[4 + bc] << 8)) != mbCrc(r, 3 + bc)) { bmsLive[idx] = false; return; }
    uint8_t *p = r + 3;
    auto U16 = [&](int o) { return (uint16_t)(p[o] << 8 | p[o + 1]); };
    auto U32 = [&](int o) { return (uint32_t)((uint32_t)p[o] << 24 | p[o + 1] << 16 | p[o + 2] << 8 | p[o + 3]); };
    Bms &b = bms[idx];
    for (int i = 0; i < NCELLS; i++) b.cell[i] = U16(i * 2) / 1000.0f;
    b.v = U32(0x90) / 1000.0f;
    b.i = (int32_t)U32(0x98) / 1000.0f;
    b.tMos = (int16_t)U16(0x8A) / 10.0f;
    b.tp1 = (int16_t)U16(0x9C) / 10.0f;
    b.tp2 = (int16_t)U16(0x9E) / 10.0f;
    b.soc = p[0xA7];
    uint32_t full = U32(0xAC); if (full > 1000) packFullAh[idx] = full / 1000.0f;
    uint32_t up = U32(0xBC);                          // total runtime (s) — web frame offset 194 − 6
    if (up > 0 && up < 4000000000UL) { b.uptime = up; b.uptimeOk = true; }
    float w = b.v * b.i; if (w > b.peakChg) b.peakChg = w; if (-w > b.peakDis) b.peakDis = -w;
    b.errFlags = U32(0xA0);            // protection/warning bitmask (web offset 166)
    b.chgMos = p[0xC0];                // actual charge MOSFET state (web 198)
    b.disMos = p[0xC1];                // actual discharge MOSFET state (web 199)
    b.balWork = p[0xC3];               // balancer actively working (web 201)
    b.cycles = U32(0xB0);              // cycle count (web 182)
    b.soh = p[0xB8];                   // state of health % (web 190)
    b.bmsOk = (b.errFlags == 0);       // operational unless the BMS reports a fault
    bmsLive[idx] = true;
}
// Poll both real BMSes (addr 1 → BMS 1, addr 2 → BMS 2). Skipped in demo mode.
// A pack that's offline is retried only every BMS_RETRY polls, not every poll, so
// a missing pack doesn't stall the UI with a timeout every second.
// Read the settings/parameter block (Modbus reg 0x1000, 125 regs = 250 bytes) into
// Read `count` holding registers from `reg` into dst[dstOff..], big-endian like realtime.
// Returns true on a valid, CRC-checked reply. Keeps each reply small enough not to
// overrun the UART RX buffer (the reason a single 250-byte settings read failed).
static bool mbReadInto(HardwareSerial &S, uint8_t addr, uint16_t reg, uint8_t count,
                       uint8_t *dst, int dstOff, int dstCap, uint32_t toMs) {
    uint8_t req[8] = {addr, 3, (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF), 0, count, 0, 0};
    uint16_t crc = mbCrc(req, 6); req[6] = crc & 0xFF; req[7] = crc >> 8;
    while (S.available()) S.read();
    S.write(req, 8); S.flush();
    static uint8_t r[280]; int n = 0; uint32_t t0 = millis();
    while (millis() - t0 < toMs) { while (S.available() && n < (int)sizeof(r)) r[n++] = S.read(); if (n >= 5 && n >= 3 + r[2] + 2) break; }
    if (n < 5 || r[0] != addr || r[1] != 3) return false;
    int bc = r[2]; if (n < 3 + bc + 2 || (r[3 + bc] | (r[4 + bc] << 8)) != mbCrc(r, 3 + bc)) return false;
    int cp = bc; if (dstOff + cp > dstCap) cp = dstCap - dstOff; if (cp < 0) cp = 0;
    memcpy(dst + dstOff, r + 3, cp);
    return true;
}
// setRaw[idx]. byte k == web settings-frame offset k+6, big-endian like realtime.
// The 125-register (250-byte) block is read in two parts so neither reply overruns
// the UART buffer; offsets are identical to the old single read.
static void bmsReadSettings(uint8_t addr, int idx) {
    HardwareSerial &S = bmsPort(idx);
    auto rd = [&](uint16_t reg, uint8_t cnt, int off, int cap) -> bool {     // retry a couple times for transient misses
        for (int t = 0; t < 3; t++) if (mbReadInto(S, addr, reg, cnt, setRaw[idx], off, cap, 70)) return true;
        return false;
    };
    // This BMS reliably answers at most ~64 registers per read, so the 125-register
    // (250-byte) block is split into two ≤64-register reads. Offsets match the old single read.
    bool a = rd(0x1000, 0x40, 0,   250);    // regs 0x1000.. (64) → bytes 0..127
    bool b = rd(0x1040, 0x3D, 128, 250);    // regs 0x1040.. (61) → bytes 128..249
    setOk[idx] = a && b;
    if (!setOk[idx]) { setOk2[idx] = false; return; }
    // tail read: reg 0x10FA (frame offset 256) → bitmask/heating/sleep fields, stored at index 250
    setOk2[idx] = rd(0x10FA, 0x14, 250, 300);
}
#define BMS_RETRY 4
static void bmsRead() {
    if (demoMode) { bmsLive[0] = bmsLive[1] = false; return; }
    static uint8_t skip[2] = {0, 0};
    static bool wasLive[2] = {false, false};
    static uint8_t setTick = 0; setTick++;
    for (int t = 0; t < 2; t++) {
        if (!bmsLive[t] && skip[t] > 0) { skip[t]--; continue; }   // back off from a silent pack
        bmsReadAddr(1, t);                                         // each pack is addr 1 on its own UART
        skip[t] = bmsLive[t] ? 0 : BMS_RETRY;                      // online → poll every cycle
        // settings: read on first contact, then refresh every ~10 polls — but stagger the two
        // packs (BMS0 at tick 0,10,…; BMS1 at 5,15,…) so a failed read (~400ms) never blocks
        // both in the same poll, which would freeze the UI for ~0.8-1.3s.
        bool firstContact = bmsLive[t] && !wasLive[t];
        bool wantSet = (setTick % 10) == (uint8_t)(t * 5);
        if (bmsLive[t] && (firstContact || wantSet)) bmsReadSettings(1, t);
        wasLive[t] = bmsLive[t];
        if (!bmsLive[t]) { setOk[t] = false; setOk2[t] = false; }
    }
}
// Write a UINT32 control register (function 0x10, 2 registers) to BMS idx (addr 1, own bus).
static void bmsWrite(int idx, uint16_t reg, uint32_t val) {
    HardwareSerial &S = bmsPort(idx);
    uint8_t f[13] = {1, 0x10, (uint8_t)(reg >> 8), (uint8_t)reg, 0, 2, 4,
                     (uint8_t)(val >> 24), (uint8_t)(val >> 16), (uint8_t)(val >> 8), (uint8_t)val, 0, 0};
    uint16_t crc = mbCrc(f, 11); f[11] = crc & 0xFF; f[12] = crc >> 8;
    while (S.available()) S.read();
    S.write(f, 13); S.flush();
    uint32_t t0 = millis(); while (millis() - t0 < 40) { while (S.available()) S.read(); }   // drain the 8-byte echo
}
// Read one UINT32 control register back (function 0x03, 2 registers). false on no/bad reply.
static bool bmsReadReg(int idx, uint16_t reg, uint32_t *out) {
    HardwareSerial &S = bmsPort(idx);
    uint8_t req[8] = {1, 3, (uint8_t)(reg >> 8), (uint8_t)reg, 0, 2, 0, 0};
    uint16_t crc = mbCrc(req, 6); req[6] = crc & 0xFF; req[7] = crc >> 8;
    while (S.available()) S.read();
    S.write(req, 8); S.flush();
    uint8_t r[16]; int n = 0; uint32_t t0 = millis();
    while (millis() - t0 < 70) { while (S.available() && n < 16) r[n++] = S.read(); if (n >= 9) break; }
    if (n < 9 || r[0] != 1 || r[1] != 3 || r[2] != 4) return false;
    if ((r[7] | (r[8] << 8)) != mbCrc(r, 7)) return false;
    *out = (uint32_t)r[3] << 24 | r[4] << 16 | r[5] << 8 | r[6];
    return true;
}
// Write a control register, then read it back to confirm the BMS accepted the value.
// The read-back can be transiently slow/missed right after the write (BMS busy),
// so retry a few times before declaring failure — otherwise a good write reports
// as "didn't change" and the UI keeps the old value.
static bool bmsSet(int idx, uint16_t reg, uint32_t val) {
    bmsWrite(idx, reg, val);
    uint32_t rb = 0;
    for (int t = 0; t < 4; t++) {
        if (bmsReadReg(idx, reg, &rb) && rb == val) return true;
        delay(25);
    }
    Serial.printf("[bms] verify failed: reg %04X wrote %lu, read %lu\n", reg, (unsigned long)val, (unsigned long)rb);
    return false;
}
static uint32_t socColor(float soc) { return soc >= 60 ? C_ACCENT : soc >= 30 ? C_WARN : C_BAD; }
// Single source of truth for the status pill — uses REAL BMS state (fault bitmask,
// actual MOSFET + balancer flags) not just a current threshold. Shared by the
// device dashboard and the web /api so they never diverge.
static const char *bmsStatusStr(int t, bool live, uint32_t *col) {
    const Bms &b = bms[t];
    if (!live)             { *col = C_BAD;   return "Offline"; }
    if (b.errFlags)        { *col = C_BAD;   return "Alarm"; }      // BMS reports a protection/warning
    if (!b.disMos || !b.chgMos) { *col = C_WARN; return "FET off"; }
    if (b.balWork)         { *col = C_CYAN;  return "Balancing"; }
    if (b.i > 0.5f)        { *col = C_ACCENT; return "Charging"; }
    if (b.i < -0.5f)       { *col = C_WARN;  return "Discharging"; }
    if (b.soc >= 99)       { *col = C_ACCENT; return "Full"; }
    return *col = C_MUTED, "Idle";
}
static uint32_t lerpColor(uint32_t a, uint32_t b, float t) {
    if (t < 0) t = 0; if (t > 1) t = 1;
    int ar = (a >> 16) & 0xff, ag = (a >> 8) & 0xff, ab = a & 0xff;
    int br = (b >> 16) & 0xff, bg = (b >> 8) & 0xff, bb = b & 0xff;
    return ((uint32_t)(ar + (br - ar) * t) << 16) | ((uint32_t)(ag + (bg - ag) * t) << 8) | (uint32_t)(ab + (bb - ab) * t);
}
// SOC ring colour: normal palette up to 90%, then fades green → deep purple-blue at 100%.
#define C_FULL 0x4012a0
static uint32_t socRingColor(float soc) {
    if (soc >= 90) return lerpColor(C_ACCENT, C_FULL, (soc - 90) / 10.0f);
    return socColor(soc);
}
static uint32_t tempColor(float t) { return t >= 55 ? C_BAD : t >= 45 ? C_WARN : C_ACCENT; }
#define PACK_AH 100.0f
// estimated runtime (discharging) / time-to-full (charging), shorthand e.g. 8h30
static void runtimeStr(float soc, float i, float fullAh, char *o, size_t n, uint32_t *col) {
    if (i < -0.5f) {                                   // discharging → time left
        int m = (int)((soc / 100.0f * fullAh) / (-i) * 60.0f + 0.5f);
        if (m < 60) snprintf(o, n, "%dm", m);
        else if (m < 1440) snprintf(o, n, "%dh%02d", m / 60, m % 60);
        else snprintf(o, n, "%dd%dh", m / 1440, (m % 1440) / 60);
        *col = C_TEXT;
    } else if (i > 0.5f) {                             // charging → time to full
        int m = (int)(((100.0f - soc) / 100.0f * fullAh) / i * 60.0f + 0.5f);
        if (m < 60) snprintf(o, n, "+%dm", m);
        else snprintf(o, n, "+%dh%02d", m / 60, m % 60);
        *col = C_ACCENT;
    } else { snprintf(o, n, "--"); *col = C_MUTED; }   // idle
}
static void timeLabel(char *out, size_t n, float daysAgo, float span) {
    float minsAgo = daysAgo * 1440.0f;
    if (minsAgo < 1.0f) { snprintf(out, n, "now"); return; }
    if (span >= 2.0f) snprintf(out, n, "%.0fd", daysAgo);                   // ≥2 days → days
    else if (span >= 0.083f) snprintf(out, n, "%.0fh", daysAgo * 24.0f);    // ≥~2h → hours
    else snprintf(out, n, "%.0fm", minsAgo);                                // short history → minutes
}

// ============================================================================
//  LVGL draw wrappers — a thin Arduino_GFX-like layer over the LVGL draw API,
//  so the original drawing code ports almost verbatim. Text is anti-aliased.
// ============================================================================
static lv_layer_t *L = nullptr;
// Custom 1-bpp Montserrat (no anti-aliasing) — same letterforms/metrics as the
// built-in 4-bpp fonts but far cheaper to render (no per-pixel alpha blending).
LV_FONT_DECLARE(mont1_10) LV_FONT_DECLARE(mont1_12) LV_FONT_DECLARE(mont1_14)
LV_FONT_DECLARE(mont1_16) LV_FONT_DECLARE(mont1_20) LV_FONT_DECLARE(mont1_28)
LV_FONT_DECLARE(mont1_48)
#define F10 &mont1_10
#define F12 &mont1_12
#define F14 &mont1_14
#define F16 &mont1_16
#define F20 &mont1_20
#define F28 &mont1_28
#define F48 &mont1_48

// pooled label text so the string outlives LVGL's deferred draw dispatch
static char tpool[80][24];
static int tpi = 0;
static const char *pool(const char *s) { char *d = tpool[tpi]; tpi = (tpi + 1) % 80; snprintf(d, 24, "%s", s); return d; }

static void fRect(int x, int y, int w, int h, int r, uint32_t col, lv_opa_t opa = LV_OPA_COVER) {
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_color = lv_color_hex(col); d.bg_opa = opa; d.radius = r;
    lv_area_t a = {x, y, x + w - 1, y + h - 1}; lv_draw_rect(L, &d, &a);
}
static void dRect(int x, int y, int w, int h, int r, uint32_t col) {  // border only
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_opa = LV_OPA_TRANSP; d.radius = r;
    d.border_color = lv_color_hex(col); d.border_width = 1; d.border_opa = LV_OPA_COVER;
    lv_area_t a = {x, y, x + w - 1, y + h - 1}; lv_draw_rect(L, &d, &a);
}
static void fCircle(int cx, int cy, int r, uint32_t col) { fRect(cx - r, cy - r, 2 * r, 2 * r, LV_RADIUS_CIRCLE, col); }
static void line(int x1, int y1, int x2, int y2, uint32_t col, lv_opa_t opa = LV_OPA_COVER, int wdt = 1) {
    lv_draw_line_dsc_t d; lv_draw_line_dsc_init(&d);
    d.color = lv_color_hex(col); d.opa = opa; d.width = wdt;
    d.p1.x = x1; d.p1.y = y1; d.p2.x = x2; d.p2.y = y2;
    lv_draw_line(L, &d);
}
static void tri(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t col) {
    lv_draw_triangle_dsc_t d; lv_draw_triangle_dsc_init(&d);
    d.color = lv_color_hex(col); d.opa = LV_OPA_COVER;
    d.p[0].x = x1; d.p[0].y = y1; d.p[1].x = x2; d.p[1].y = y2; d.p[2].x = x3; d.p[2].y = y3;
    lv_draw_triangle(L, &d);
}
static void ring(int cx, int cy, int ro, int ri, int a0, int a1, uint32_t col) {
    lv_draw_arc_dsc_t d; lv_draw_arc_dsc_init(&d);
    d.color = lv_color_hex(col); d.width = ro - ri; d.opa = LV_OPA_COVER;
    d.center.x = cx; d.center.y = cy; d.radius = ro;
    d.start_angle = a0; d.end_angle = a1;
    lv_draw_arc(L, &d);
}
static int textW(const char *s, const lv_font_t *f) {
    lv_point_t p; lv_text_get_size(&p, s, f, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE); return p.x;
}
static void lText(const char *s, int x, int y, const lv_font_t *f, uint32_t col) {  // top-left
    lv_draw_label_dsc_t d; lv_draw_label_dsc_init(&d);
    d.text = pool(s); d.color = lv_color_hex(col); d.font = f;
    lv_area_t a = {x, y, x + 460, y + 60}; lv_draw_label(L, &d, &a);
}
static void cText(const char *s, int cx, int cy, const lv_font_t *f, uint32_t col) {  // centred on point
    lv_point_t sz; lv_text_get_size(&sz, s, f, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
    lv_draw_label_dsc_t d; lv_draw_label_dsc_init(&d);
    d.text = pool(s); d.color = lv_color_hex(col); d.font = f;
    lv_area_t a = {cx - sz.x / 2, cy - sz.y / 2, cx - sz.x / 2 + sz.x, cy - sz.y / 2 + sz.y};
    lv_draw_label(L, &d, &a);
}

// ============================================================================
//  Widgets — ported 1:1 from esp32-bms/src/main.cpp
// ============================================================================
static void drawGear(int cx, int cy, int r, uint32_t col, uint32_t hole) {
    for (int k = 0; k < 8; k++) {
        float a = k * (PI / 4);
        fCircle(cx + (int)((r + 2) * cosf(a)), cy + (int)((r + 2) * sinf(a)), 2, col);
    }
    fCircle(cx, cy, r, col);
    fCircle(cx, cy, (int)(r * 0.42f), hole);
}
static void drawBed(int cx, int cy, uint32_t col) {
    int x = cx - 13, y = cy + 5;
    fRect(x + 1, y, 2, 4, 0, col);
    fRect(x + 22, y, 2, 4, 0, col);
    fRect(x, y - 6, 26, 6, 2, col);
    fRect(x, y - 13, 3, 9, 0, col);
    fRect(x + 4, y - 9, 8, 4, 2, col);
    lText("z", x + 20, y - 18, F12, col);
}
static void drawWifi(int cx, int cy, uint32_t color) {
    fCircle(cx, cy, 2, color);
    const float a0 = 50.0f * (PI / 180.0f), a1 = 130.0f * (PI / 180.0f), yScale = 0.72f;
    int radii[3] = {7, 12, 17};
    for (int k = 0; k < 3; k++) {
        int r = radii[k], px = -1, py = -1;
        for (int s = 0; s <= 10; s++) {
            float a = a0 + (a1 - a0) * s / 10.0f;
            int x = cx + (int)(r * cosf(a)), y = cy - (int)(r * sinf(a) * yScale);
            if (px >= 0) { line(px, py, x, y, color); line(px, py + 1, x, y + 1, color); }
            px = x; py = y;
        }
    }
}
// compact wifi glyph for the top bar (dot at bottom, arcs fanning up)
static void drawWifiSmall(int cx, int cy, uint32_t color) {
    fCircle(cx, cy, 1, color);
    const float a0 = 50.0f * (PI / 180.0f), a1 = 130.0f * (PI / 180.0f), yScale = 0.72f;
    int radii[3] = {4, 8, 12};
    for (int k = 0; k < 3; k++) {
        int r = radii[k], px = -1, py = -1;
        for (int s = 0; s <= 8; s++) {
            float a = a0 + (a1 - a0) * s / 8.0f;
            int x = cx + (int)(r * cosf(a)), y = cy - (int)(r * sinf(a) * yScale);
            if (px >= 0) line(px, py, x, y, color);
            px = x; py = y;
        }
    }
}
static void drawTabs(bool autoActive, float prog) {
    const int y = 6, h = 28;
    const int tabX[2] = {TAB1_X, TAB2_X};
    for (int t = 0; t < 2; t++) {
        int x = tabX[t]; bool on = (view == t);
        bool offline = !demoMode && !bmsLive[t];   // real mode + this BMS isn't answering
        uint32_t bg = on ? (offline ? C_BAD : C_ACCENT) : C_CARD;
        fRect(x, y, TAB_W, h, 8, bg);
        if (!on) dRect(x, y, TAB_W, h, 8, offline ? C_BAD : C_BORDER);
        char lbl[8]; snprintf(lbl, sizeof(lbl), "BAT %d", t + 1);
        cText(lbl, x + TAB_W / 2, y + h / 2, F16, on ? C_BG : (offline ? C_BAD : C_MUTED));
        if (on && autoActive) fRect(x + 6, y + h - 3, (int)((TAB_W - 12) * prog), 2, 0, C_BG);
    }
    // wifi status icon, just right of the battery buttons (green = connected, grey = not)
    // dot sits at the baseline, arcs fan ~9px up → place the dot below centre so the glyph centres
    drawWifiSmall(TAB2_X + TAB_W + 22, y + h / 2 + 5, WiFi.status() == WL_CONNECTED ? C_ACCENT : C_MUTED);
    struct tm ti;
    if (getLocalTime(&ti, 0)) {
        char ts[6]; snprintf(ts, sizeof(ts), "%02d:%02d", ti.tm_hour, ti.tm_min);
        cText(ts, BED_X - 36, 20, F16, C_TEXT);
    }
    fRect(BED_X, y, BED_W, h, 8, C_CARD);
    dRect(BED_X, y, BED_W, h, 8, C_BORDER);
    drawBed(BED_X + BED_W / 2, y + h / 2, C_MUTED);
    fRect(GEAR_X, GEAR_Y, GEAR_W, h, 8, C_CARD);
    dRect(GEAR_X, GEAR_Y, GEAR_W, h, 8, C_BORDER);
    drawGear(GEAR_X + GEAR_W / 2, GEAR_Y + h / 2, 7, C_MUTED, C_CARD);
}
static void drawRing(int cx, int cy, int ro, int ri, float pct, uint32_t col, bool stale = false) {
    ring(cx, cy, ro, ri, 0, 360, C_BORDER);          // empty track only when stale
    if (!stale) {
        if (pct >= 99.5f) ring(cx, cy, ro, ri, 0, 360, col);
        else if (pct > 0.5f) {
            int ea = 270 + (int)(pct * 3.6f); while (ea >= 360) ea -= 360;
            ring(cx, cy, ro, ri, 270, ea, col);
        }
    }
    if (stale) { cText("--", cx, cy - 6, F48, C_MUTED); return; }
    char buf[8]; snprintf(buf, sizeof(buf), "%d", (int)(pct + 0.5f));
    cText(buf, cx, cy - 6, F48, C_TEXT);
    cText("%", cx, cy + 30, F16, C_MUTED);
}
static void drawTile(int x, int y, int w, int h, const char *label, const char *val, const char *unit, uint32_t valCol) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    lText(label, x + 8, y + 8, F12, C_MUTED);
    if (unit) {
        lText(val, x + 8, y + 24, F20, valCol);
        lText(unit, x + 8, y + h - 16, F12, C_MUTED);
    } else {
        // value vertically centred in the area below the label
        lv_point_t sz; lv_text_get_size(&sz, val, F20, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
        int top = y + 24, bot = y + h - 4;
        lText(val, x + 8, top + (bot - top - sz.y) / 2, F20, valCol);
    }
}
static void drawTempsTile(int x, int y, int w, int h, float mos, float t1, float t2, bool stale = false) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    const char *lbl[3] = {"MOS", "T1", "T2"}; float v[3] = {mos, t1, t2};
    for (int r = 0; r < 3; r++) {
        int ry = y + 12 + r * 19;
        lText(lbl[r], x + 8, ry + 2, F10, C_MUTED);
        // an unwired probe reads a saturated sentinel (~±200C) → show n/c, not a fake temp
        bool noProbe = (r > 0) && (v[r] < -50 || v[r] > 120);
        if (stale || noProbe) { lText("--", x + 34, ry, F12, C_MUTED); continue; }
        char buf[8]; snprintf(buf, sizeof(buf), "%.0fC", v[r]);
        lText(buf, x + 34, ry, F12, tempColor(v[r]));
    }
}
static void drawStatsTile(int x, int y, int w, int h, float pkChg, float pkDis, uint32_t upSec, const char *rt, uint32_t rtCol, bool stale = false) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    const char *lbl[4] = {"PK CHG", "PK DIS", "UPTIME", "REMAIN"};
    char val[4][10];
    snprintf(val[0], sizeof(val[0]), "%.0fW", pkChg);
    snprintf(val[1], sizeof(val[1]), "%.0fW", pkDis);
    uint32_t m = upSec / 60;
    if (m >= 6000) snprintf(val[2], sizeof(val[2]), "%lud%luh", (unsigned long)(m / 1440), (unsigned long)((m % 1440) / 60));   // ≥100h → days
    else snprintf(val[2], sizeof(val[2]), "%luh%02lu", (unsigned long)(m / 60), (unsigned long)(m % 60));
    snprintf(val[3], sizeof(val[3]), "%s", rt);
    uint32_t vc[4] = {C_ACCENT, C_WARN, C_TEXT, rtCol};
    if (stale) { for (int r = 0; r < 4; r++) { if (r != 2) { snprintf(val[r], sizeof(val[r]), "--"); vc[r] = C_MUTED; } } }  // uptime still real
    for (int r = 0; r < 4; r++) {
        int ry = y + 8 + r * 15;
        lText(lbl[r], x + 8, ry, F10, C_MUTED);
        lText(val[r], x + w - textW(val[r], F10) - 8, ry, F10, vc[r]);
    }
}
static void drawCells(int x, int y, int w, int h, const Bms &b, bool stale = false) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    float lo = 9, hi = 0; int loI = 0, hiI = 0;
    for (int i = 0; i < NCELLS; i++) { if (b.cell[i] < lo) { lo = b.cell[i]; loI = i; } if (b.cell[i] > hi) { hi = b.cell[i]; hiI = i; } }
    char hdr[20];
    if (stale) snprintf(hdr, sizeof(hdr), "CELLS  --");
    else snprintf(hdr, sizeof(hdr), "CELLS  %dmV", (int)((hi - lo) * 1000));
    lText(hdr, x + 8, y + 7, F12, C_MUTED);
    const int top = y + 22, rh = (h - 28) / NCELLS;
    for (int i = 0; i < NCELLS; i++) {
        int ry = top + i * rh, midY = ry + (rh - 8) / 2 - 2;
        char cl[4]; snprintf(cl, sizeof(cl), "C%d", i + 1);
        lText(cl, x + 8, midY, F12, C_MUTED);
        int bx = x + 28, bw = w - 28 - 42, by = ry + 2, bh = rh - 4;
        fRect(bx, by, bw, bh, 2, C_BORDER);
        if (stale) { lText("--", x + w - 40, midY, F12, C_MUTED); continue; }
        float frac = (b.cell[i] - 3.0f) / 0.6f; frac = frac < 0.05f ? 0.05f : frac > 1 ? 1 : frac;
        uint32_t c = (i == loI) ? C_CYAN : (i == hiI) ? C_WARN : C_ACCENT;
        fRect(bx, by, (int)(bw * frac), bh, 2, c);
        char cv[8]; snprintf(cv, sizeof(cv), "%.2f", b.cell[i]);
        lText(cv, x + w - 40, midY, F12, C_TEXT);
    }
}
static void fmtWh(char *buf, size_t n, float wh) {
    if (wh >= 1000.0f) snprintf(buf, n, "%.2fkWh", wh / 1000.0f);
    else snprintf(buf, n, "%.0fWh", wh);
}
// Energy drawn from a pack ("spent") over the last `nSamples` history points.
// History is logged every HIST_INTERVAL_MS only while the pack is live, so this
// assumes roughly continuous logging (gaps from downtime shorten the real window).
static float whSpent(int v, int nSamples) {
    int cnt = histCount[v]; if (cnt <= 0) return 0;
    int start = cnt - nSamples; if (start < 0) start = 0;
    const float perH = HIST_INTERVAL_MS / 3600000.0f;          // 5 min = 1/12 h
    float wh = 0;
    for (int i = start; i < cnt; i++) {                         // histPwr is charge-positive → discharge is negative
        int w = histPwr[v][i];
        if (w < 0) wh += -w * perH;
    }
    return wh;
}
// Total pack energy (Wh) = full Ah × nominal 3.2V/cell, cell count inferred from voltage.
static float packTotalWh(int t) {
    float fullAh = (!demoMode && bmsLive[t]) ? packFullAh[t] : PACK_AH;
    float v = bms[t].v;
    int cells = (v > 1.5f) ? (int)(v / 3.3f + 0.5f) : NCELLS; if (cells < 1) cells = NCELLS;
    return fullAh * cells * 3.2f;
}
static void drawEnergyTile(int x, int y, int w, int h, float totalWh, float wh24, float wh6, bool stale) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    lText("CAPACITY", x + 8, y + 6, F10, C_MUTED);
    char buf[12];
    if (stale) snprintf(buf, sizeof(buf), "--"); else fmtWh(buf, sizeof(buf), totalWh);
    lText(buf, x + 8, y + 22, F16, C_ACCENT);                  // headline: total pack capacity
    line(x + 8, y + 48, x + w - 8, y + 48, C_BORDER, 170);
    const char *lbl[2] = {"24h", "6h"}; float val[2] = {wh24, wh6};   // energy drawn (used) over each window
    for (int r = 0; r < 2; r++) {
        int ry = y + 56 + r * 20;
        lText(lbl[r], x + 8, ry, F10, C_MUTED);
        if (stale) { lText("--", x + w - textW("--", F12) - 8, ry, F12, C_MUTED); continue; }
        fmtWh(buf, sizeof(buf), val[r]);
        char pc[8]; snprintf(pc, sizeof(pc), "%d%%", totalWh > 1 ? (int)(val[r] / totalWh * 100.0f + 0.5f) : 0);
        int pcw = textW(pc, F10);                                  // % of total capacity, small + dim, far right
        lText(pc, x + w - 8 - pcw, ry + 1, F10, C_MUTED);
        lText(buf, x + w - 8 - pcw - 5 - textW(buf, F12), ry, F12, C_WARN);   // Wh just left of it
    }
}
static void drawPowerGraph(int x, int y, int w, int h, const Bms &b) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    lText("POWER DRAW  W", x + 8, y + 6, F10, C_MUTED);
    if (b.pwrCount < 2) { cText("collecting data", x + w / 2, y + h / 2, F12, C_MUTED); return; }
    const int lblW = 24, gx = x + 8 + lblW, gy = y + 22, gw = w - 14 - lblW, gh = h - 38, base = gy + gh;
    int cnt = b.pwrCount > NCAP ? NCAP : b.pwrCount;
    float lo = 1e9f, hi = -1e9f;
    for (int i = 0; i < cnt; i++) { float v = b.pwr[i]; if (v < lo) lo = v; if (v > hi) hi = v; }
    if (lo > 0) lo = 0; if (hi < 0) hi = 0;
    if (hi - lo < 50) { float g = (50 - (hi - lo)) * 0.5f; hi += g; lo -= g; }   // min 50W span → no sawtooth on idle noise
    int zeroY = base - (int)((0 - lo) / (hi - lo) * gh);
    for (int k = 0; k < 5; k++) line(gx + (int)((float)k / 4 * gw), gy, gx + (int)((float)k / 4 * gw), gy + gh, C_BORDER, 170);
    line(gx, zeroY, gx + gw, zeroY, C_BORDER, 170);
    char lb[8];
    snprintf(lb, sizeof(lb), "%d", (int)hi); lText(lb, x + 4, gy - 3, F10, C_MUTED);
    lText("0", x + 4, zeroY - 7, F10, C_MUTED);
    snprintf(lb, sizeof(lb), "%d", (int)lo); lText(lb, x + 4, base - 9, F10, C_MUTED);
    int px = -1, py = -1;
    for (int i = 0; i < cnt; i++) {
        int sx = gx + (int)((float)i / (cnt - 1) * gw);
        int sy = base - (int)((b.pwr[i] - lo) / (hi - lo) * gh);
        int t = sy < zeroY ? sy : zeroY;
        line(sx, t, sx, t + abs(sy - zeroY), C_CYAN, 45);
        if (px >= 0) line(px, py, sx, sy, C_CYAN, LV_OPA_COVER, 2);
        px = sx; py = sy;
    }
    for (int k = 0; k < 5; k++) {
        int fx = gx + (int)((float)k / 4 * gw);
        float minsAgo = b.pwrSpanMin * (1.0f - k / 4.0f);
        char lbl[8];
        if (minsAgo < 0.05f) snprintf(lbl, sizeof(lbl), "now");
        else if (b.pwrSpanMin < 2.0f) snprintf(lbl, sizeof(lbl), "%.0fs", minsAgo * 60.0f);   // <2 min → seconds
        else snprintf(lbl, sizeof(lbl), "%.0fm", minsAgo);
        if (k == 0) lText(lbl, fx, base + 6, F10, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F10), base + 6, F10, C_MUTED);
        else cText(lbl, fx, base + 11, F10, C_MUTED);
    }
}
static void drawCapacityGraph(int x, int y, int w, int h, const Bms &b) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    char hdr[28];
    if (b.capSpanDays >= 2.0f) snprintf(hdr, sizeof(hdr), "CAPACITY   %.0f days", b.capSpanDays);
    else if (b.capCount >= 2) snprintf(hdr, sizeof(hdr), "CAPACITY   %.0f hours", b.capSpanDays * 24.0f);
    else snprintf(hdr, sizeof(hdr), "CAPACITY");
    lText(hdr, x + 8, y + 6, F10, C_MUTED);
    if (b.capCount < 2) { cText("collecting data", x + w / 2, y + h / 2, F12, C_MUTED); return; }
    const int lblW = 22, gx = x + 10 + lblW, gy = y + 26, gw = w - 20 - lblW, gh = h - 44, base = gy + gh;
    for (int p = 0; p <= 100; p += 50) {
        int yy = base - (int)(p / 100.0f * gh);
        line(gx, yy, gx + gw, yy, C_BORDER, 170);
        char lb[5]; snprintf(lb, sizeof(lb), "%d", p); lText(lb, x + 6, yy - 5, F10, C_MUTED);
    }
    for (int k = 0; k < 5; k++) line(gx + (int)((float)k / 4 * gw), gy, gx + (int)((float)k / 4 * gw), gy + gh, C_BORDER, 170);
    int cnt = (b.capCount < 2) ? 2 : (b.capCount > NCAP ? NCAP : b.capCount);
    int px = -1, py = -1;
    for (int i = 0; i < cnt; i++) {
        int sx = gx + (int)((float)i / (cnt - 1) * gw);
        int sy = base - (int)(b.cap[i] / 100.0f * gh);
        line(sx, sy, sx, base, C_ACCENT, 45);
        if (px >= 0) line(px, py, sx, sy, C_ACCENT, LV_OPA_COVER, 2);
        px = sx; py = sy;
    }
    for (int k = 0; k < 5; k++) {
        int fx = gx + (int)((float)k / 4 * gw);
        char lbl[8]; timeLabel(lbl, sizeof(lbl), b.capSpanDays * (1.0f - k / 4.0f), b.capSpanDays);
        if (k == 0) lText(lbl, fx, base + 6, F10, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F10), base + 6, F10, C_MUTED);
        else cText(lbl, fx, base + 11, F10, C_MUTED);
    }
}

// The two graphs only change when the active BMS changes, so they are rendered
// once into offscreen canvases and blitted as images each frame (saves ~336
// per-frame line draws). Sizes match their slots in renderBms().
#define POW_W 164
#define POW_H 86
#define CAP_W 164                   // match the power graph; energy panel fills the rest
#define CAP_H 96
static lv_obj_t *powCv = nullptr, *capCv = nullptr;
// Capacity graph: persisted 7-day SOC history (live) or genCap() curve (demo).
// Power graph: the fast 10-minute rolling window (always), decimated to fit.
#define POW_PTS 160                  // display columns for the power window
static void prepGraphData(int v) {
    Bms &b = bms[v];
    if (!demoMode) {                                         // capacity from history
        int n = histCount[v];
        b.capSpanDays = n > 1 ? (float)(n - 1) / 288.0f : 0.0f;   // 288 samples/day (5 min)
        if (n <= NCAP) { for (int i = 0; i < n; i++) b.cap[i] = histCap[v][i]; b.capCount = n; }
        else {
            for (int j = 0; j < NCAP; j++) {
                int lo = (int)((int64_t)j * n / NCAP), hi = (int)((int64_t)(j + 1) * n / NCAP);
                if (hi <= lo) hi = lo + 1;
                float sc = 0; for (int i = lo; i < hi; i++) sc += histCap[v][i];
                b.cap[j] = sc / (hi - lo);
            }
            b.capCount = NCAP;
        }
    }   // demo: b.cap stays the genCap() curve
    // power = 10-minute window, newest-on-right
    int pn = pwrWinN[v];
    b.pwrSpanMin = pn * (PWR_DT / 1000.0f) / 60.0f;
    if (pn <= POW_PTS) { for (int i = 0; i < pn; i++) b.pwr[i] = pwrWin[v][i]; b.pwrCount = pn; }
    else {
        for (int j = 0; j < POW_PTS; j++) {
            int lo = (int)((int64_t)j * pn / POW_PTS), hi = (int)((int64_t)(j + 1) * pn / POW_PTS);
            if (hi <= lo) hi = lo + 1;
            float sp = 0; for (int i = lo; i < hi; i++) sp += pwrWin[v][i];
            b.pwr[j] = sp / (hi - lo);
        }
        b.pwrCount = POW_PTS;
    }
}
static void renderGraphs() {
    if (!powCv || !capCv) return;
    prepGraphData(view);
    lv_layer_t lyr;
    lv_canvas_init_layer(powCv, &lyr); L = &lyr;
    fRect(0, 0, POW_W, POW_H, 0, C_BG);
    drawPowerGraph(0, 0, POW_W, POW_H, bms[view]);
    lv_canvas_finish_layer(powCv, &lyr);
    lv_canvas_init_layer(capCv, &lyr); L = &lyr;
    fRect(0, 0, CAP_W, CAP_H, 0, C_BG);
    drawCapacityGraph(0, 0, CAP_W, CAP_H, bms[view]);
    lv_canvas_finish_layer(capCv, &lyr);
}
static void blitCanvas(lv_obj_t *cv, int x, int y, int w, int h) {
    lv_draw_image_dsc_t id; lv_draw_image_dsc_init(&id);
    id.src = lv_canvas_get_image(cv);
    lv_area_t a = {x, y, x + w - 1, y + h - 1};
    lv_draw_image(L, &id, &a);
}
static void switchView(int v) { view = v; renderGraphs(); }   // gauges read from the continuously-polled cache → instant

static void renderBms() {
    const Bms &b = bms[view];
    uint32_t now = millis();
    bool autoActive = (now >= manualUntil);
    float prog = autoActive ? (float)(now - lastSwitch) / intervalMs : 0;
    if (prog > 1) prog = 1; if (prog < 0) prog = 0;
    drawTabs(autoActive, prog);

    const int cx = 100, cy = 178;
    // operational status — real BMS state (fault bitmask + actual MOSFET/balancer flags)
    uint32_t sc; const char *st = bmsStatusStr(view, demoMode || bmsLive[view], &sc);
    int pw2 = textW(st, F12) + 28, px2 = cx - pw2 / 2, py2 = 52;
    fRect(px2, py2, pw2, 20, 10, C_CARD); dRect(px2, py2, pw2, 20, 10, C_BORDER);
    fCircle(px2 + 13, py2 + 10, 4, sc);
    lText(st, px2 + 22, py2 + 5, F12, sc);
    bool stale = (!demoMode && !bmsLive[view]);   // live mode, this pack isn't answering → no data
    drawRing(cx, cy, 74, 58, b.soc, socRingColor(b.soc), stale);
    int py = cy + 100;                            // power + current readout, big & centered, just below the ring
    if (stale) {
        cText("--", cx, py + 2, F28, C_MUTED);
    } else {
        bool chg = (b.i >= 0); uint32_t pcol = chg ? C_ACCENT : C_WARN;   // green = charging, amber = discharging
        char pw[10], cu[10];
        snprintf(pw, sizeof(pw), "%.0fW", fabsf(b.v * b.i));
        if (fabsf(b.i) < 100) snprintf(cu, sizeof(cu), "%.1fA", fabsf(b.i));
        else snprintf(cu, sizeof(cu), "%.0fA", fabsf(b.i));
        lText(pw, cx - 16 - textW(pw, F28), py, F28, pcol);   // power: right-aligned, left of centre
        lText(cu, cx + 16, py, F28, pcol);                     // current: left-aligned, right of centre
        int aw = 7, ay = py + 3, ah = 15;                      // direction arrow, centred between them
        if (chg) tri(cx - aw, ay + ah, cx + aw, ay + ah, cx, ay, pcol);   // up = charging
        else     tri(cx - aw, ay, cx + aw, ay, cx, ay + ah, pcol);        // down = discharging
    }

    const int rx = 200, rw = Wd - rx - 8;
    char vbuf[10]; if (stale) snprintf(vbuf, sizeof(vbuf), "--"); else snprintf(vbuf, sizeof(vbuf), "%.2fV", b.v);
    const int ty = 40, th = 70, gap = 8;
    const int vW = 78, sW = 102, tpW = rw - vW - sW - 2 * gap;  // stats wider, temps + voltage narrower
    drawTile(rx, ty, vW, th, "VOLTAGE", vbuf, nullptr, stale ? C_MUTED : C_TEXT);
    char rt[10]; uint32_t rtCol;
    float fullAh = (!demoMode && bmsLive[view]) ? packFullAh[view] : PACK_AH;
    runtimeStr(b.soc, b.i, fullAh, rt, sizeof(rt), &rtCol);
    uint32_t upSec = (!demoMode && bmsLive[view] && b.uptimeOk) ? b.uptime : now / 1000;   // BMS runtime if live, else device uptime
    drawStatsTile(rx + vW + gap, ty, sW, th, b.peakChg, b.peakDis, upSec, rt, rtCol, stale);
    drawTempsTile(rx + vW + gap + sW + gap, ty, tpW, th, b.tMos, b.tp1, b.tp2, stale);

    const int cellsW = rw - 8 - POW_W;          // ~1/3 cells, ~2/3 power graph
    drawCells(rx, 120, cellsW, 86, b, stale);
    blitCanvas(powCv, rx + cellsW + 8, 120, POW_W, POW_H);
    // bottom row, columns aligned with the row above: energy summary (left) + capacity graph (right)
    drawEnergyTile(rx, 216, cellsW, CAP_H, packTotalWh(view), whSpent(view, 288), whSpent(view, 72), stale);
    blitCanvas(capCv, rx + cellsW + 8, 216, CAP_W, CAP_H);
}

// ============================================================================
//  Settings screen — ported 1:1 from esp32-bms (size1->F12, size2->F16)
// ============================================================================
#define CLOSE_X (Wd - 40)
static const char *KB[3][4] = {
    {"1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm"},
    {"1234567890", "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"},
    {"1234567890", "@#$%&*-+()", "!?:;'/_=.", ",~[]{}<>"},
};
#define SROW_H 40
#define SROW_STEP 46
#define LIST_TOP 80
static int srowY(int i) { return 86 + i * SROW_STEP; }   // fixed rows (BMS tab)
static void srowAt(int y, const char *label, const char *val, uint32_t vc) {
    int x = 8, w = Wd - 16, h = SROW_H;
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    lText(label, x + 14, y + h / 2 - 9, F16, C_TEXT);
    lText(val, x + w - textW(val, F16) - 16, y + h / 2 - 9, F16, vc);
}
static void srow(int i, const char *label, const char *val, uint32_t vc) { srowAt(srowY(i), label, val, vc); }
// iOS-style pill toggle, right-aligned in a settings row
static void srowToggle(int y, const char *label, bool on) {
    int x = 8, w = Wd - 16, h = SROW_H;
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    lText(label, x + 14, y + h / 2 - 9, F16, C_TEXT);
    int tw = 44, th = 22, tx = x + w - 16 - tw, ty = y + h / 2 - th / 2;
    fRect(tx, ty, tw, th, th / 2, on ? C_ACCENT : C_BORDER);
    int kr = 8, kx = on ? tx + tw - kr - 3 : tx + kr + 3;
    fCircle(kx, ty + th / 2, kr, on ? C_BG : C_MUTED);
}

// ---- scrollable System list ----
static const char *SYS_LABEL[] = {
    "Auto-switch", "Switch interval", "Brightness   - / +", "Auto-sleep", "Eco mode", "Dim after",
    "Temp unit", "Time format", "WiFi auto-connect", "Demo speed", "System info", "Firmware", "Demo mode", "No-data screen"};
#define SYS_ROWS ((int)(sizeof(SYS_LABEL) / sizeof(SYS_LABEL[0])))
static void dimStr(char *o, size_t n) {
    if (dimAfterSec == 0) snprintf(o, n, "Off");
    else if (dimAfterSec < 60) snprintf(o, n, "%ds", dimAfterSec);
    else snprintf(o, n, "%d min", dimAfterSec / 60);
}
static void sysVal(int i, char *o, size_t n, uint32_t *vc) {
    switch (i) {
        case 0: snprintf(o, n, "%s", autoSwitch ? "ON" : "OFF"); *vc = autoSwitch ? C_ACCENT : C_MUTED; break;
        case 1: snprintf(o, n, "%lus", (unsigned long)(intervalMs / 1000)); *vc = C_CYAN; break;
        case 2: snprintf(o, n, "%d%%", brightness); *vc = C_TEXT; break;
        case 3: if (autoSleepMin == 0) snprintf(o, n, "Never"); else snprintf(o, n, "%d min", autoSleepMin); *vc = autoSleepMin ? C_CYAN : C_MUTED; break;
        case 4: snprintf(o, n, "%s", ecoMode ? "ON" : "OFF"); *vc = ecoMode ? C_ACCENT : C_MUTED; break;
        case 5: dimStr(o, n); *vc = dimAfterSec ? C_CYAN : C_MUTED; break;
        case 6: snprintf(o, n, "%s", tempF ? "Fahr." : "Celsius"); *vc = C_CYAN; break;
        case 7: snprintf(o, n, "%s", fmt12 ? "12-hour" : "24-hour"); *vc = C_CYAN; break;
        case 8: snprintf(o, n, "%s", wifiAuto ? "ON" : "OFF"); *vc = wifiAuto ? C_ACCENT : C_MUTED; break;
        case 9: snprintf(o, n, "%dx", simSpeed); *vc = C_CYAN; break;
        case 10: snprintf(o, n, "view"); *vc = C_CYAN; break;
        case 13: { static const char *IN[6] = {"Dashboard", "HUD", "Init", "Radar", "Arcade", "Security"}; snprintf(o, n, "%s", IN[idleScreen % 6]); *vc = C_CYAN; break; }
        default: snprintf(o, n, "v" FW_VERSION); *vc = C_MUTED; break;
    }
}
static int sysViewH() { return Ht - LIST_TOP - 2; }
// + one row of bottom padding so the last entry can scroll clear of the panel's
// bottom edge (touch is unreliable in the last few px there).
static int sysContentH() { return SYS_ROWS * SROW_STEP + SROW_STEP; }
static int sysMaxScroll() { int m = sysContentH() - sysViewH(); return m > 0 ? m : 0; }
static void subTabGeom(int i, int *x, int *w) { int gap = 6; *w = (Wd - 16 - 2 * gap) / 3; *x = 8 + i * (*w + gap); }
static void drawCloseBtn() {
    int x = CLOSE_X, y = 8, w = 32, h = 26, cx = x + w / 2, cy = y + h / 2;
    fRect(x, y, w, h, 6, C_CARD); dRect(x, y, w, h, 6, C_BORDER);
    for (int o = -1; o <= 1; o++) { line(cx - 6, cy - 6 + o, cx + 6, cy + 6 + o, C_BAD); line(cx - 6, cy + 6 + o, cx + 6, cy - 6 + o, C_BAD); }
}
static void drawSubTabs() {
    const char *nm[3] = {cfgBms ? "BAT 2" : "BAT 1", "WiFi", "System"};
    for (int i = 0; i < 3; i++) {
        int x, w; subTabGeom(i, &x, &w); bool on = (subTab == i);
        fRect(x, 44, w, 30, 8, on ? C_ACCENT : C_CARD); if (!on) dRect(x, 44, w, 30, 8, C_BORDER);
        cText(nm[i], x + w / 2, 44 + 15, F16, on ? C_BG : C_MUTED);
    }
}
static void renderSysTab() {
    if (sysScroll > sysMaxScroll()) sysScroll = sysMaxScroll();
    for (int i = 0; i < SYS_ROWS; i++) {
        int y = LIST_TOP + i * SROW_STEP - sysScroll;
        if (y + SROW_H < LIST_TOP || y > Ht) continue;     // off-screen
        if (i == 0) srowToggle(y, SYS_LABEL[i], autoSwitch);
        else if (i == 4) srowToggle(y, SYS_LABEL[i], ecoMode);
        else if (i == 8) srowToggle(y, SYS_LABEL[i], wifiAuto);
        else if (i == 12) srowToggle(y, SYS_LABEL[i], demoMode);
        else { char val[16]; uint32_t vc; sysVal(i, val, sizeof(val), &vc); srowAt(y, SYS_LABEL[i], val, vc); }
    }
    if (sysMaxScroll() > 0) {                               // scrollbar
        int tX = Wd - 6, tY = LIST_TOP, tH = sysViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)sysViewH() / sysContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)sysScroll / sysMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
}
// ---- editable BMS settings (derived from the web 0x01 settings frame) ----
// Modbus register = 0x1000 + (frame offset - 6). Values decode big-endian like the
// realtime block. All offsets here are < 250 so one 125-register read covers them.
enum FType { FT_U32, FT_U16, FT_I32, FT_I16, FT_U8, FT_I8 };
struct SetDef { const char *label; uint16_t off; uint8_t type; float scale; const char *unit; float vmin, vmax, vstep; };
// Ordered most-important-first (display order only; each entry's register `off`
// is independent, so reordering is safe). Grouped: pack basics → current limits →
// cell-voltage protection → SOC cal → balancing → charge profile → then the
// rarely-touched timing / temperature / sleep protections.
static const SetDef SETDEFS[] = {
    // pack basics
    {"Nominal cap",      130, FT_U32, 0.001f, "Ah", 1, 2000, 1},
    {"Cell count",       114, FT_U32, 1.0f,   "",   3, 32, 1},
    // current limits
    {"Max charge A",      50, FT_U32, 0.001f, "A",  1, 200, 1},
    {"Max discharge A",   62, FT_U32, 0.001f, "A",  1, 200, 1},
    // cell voltage protection
    {"Cell OVP",          18, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"Cell OVP recover",  22, FT_U32, 0.001f, "V",  2.4f, 4.20f, 0.01f},
    {"Cell UVP",          10, FT_U32, 0.001f, "V",  1.5f, 3.50f, 0.01f},
    {"Cell UVP recover",  14, FT_U32, 0.001f, "V",  1.6f, 3.60f, 0.01f},
    // SOC calibration
    {"SOC 100% volt",     30, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"SOC 0% volt",       34, FT_U32, 0.001f, "V",  1.5f, 3.50f, 0.01f},
    // balancing
    {"Balance start V",  138, FT_U32, 0.001f, "V",  2.5f, 4.20f, 0.01f},
    {"Balance trig dV",   26, FT_U32, 0.001f, "V",  0.005f, 0.50f, 0.005f},
    {"Max balance A",     78, FT_U32, 0.001f, "A",  0.1f, 2.0f, 0.1f},
    // charge profile (inverter/charger handshake)
    {"Req charge volt",   38, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"Req float volt",    42, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"Power off volt",    46, FT_U32, 0.001f, "V",  1.5f, 3.20f, 0.01f},
    // current-protection timing
    {"Charge OCP delay",  54, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Charge OCP recov",  58, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Dischg OCP delay",  66, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Dischg OCP recov",  70, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Short-circ delay", 134, FT_U32, 1.0f,   "us", 0, 1000, 1},
    {"Short-circ recov",  74, FT_U32, 1.0f,   "s",  1, 256, 1},
    // temperature protection (Modbus stores these as 32-bit, not the BLE frame's u16)
    {"Charge OTP",        82, FT_U32, 0.1f,   "C",  20, 100, 1},
    {"Charge OTP recov",  86, FT_U32, 0.1f,   "C",  15, 95, 1},
    {"Dischg OTP",        90, FT_U32, 0.1f,   "C",  20, 100, 1},
    {"Dischg OTP recov",  94, FT_U32, 0.1f,   "C",  15, 95, 1},
    {"Charge UTP",        98, FT_I32, 0.1f,   "C",  -30, 20, 1},
    {"Charge UTP recov", 102, FT_I32, 0.1f,   "C",  -25, 25, 1},
    {"MOS OTP",          106, FT_I32, 0.1f,   "C",  50, 120, 1},
    {"MOS OTP recover",  110, FT_I32, 0.1f,   "C",  40, 110, 1},
    // sleep
    {"Smart sleep V",      6, FT_U32, 0.001f, "V",  2.0f, 3.60f, 0.01f},
};
#define NSET ((int)(sizeof(SETDEFS) / sizeof(SETDEFS[0])))
// settings that live in the tail region (need the 2nd read; setOk2)
static const SetDef TAILDEFS[] = {
    {"Heating start T",  284, FT_I8, 1.0f, "C", -30, 20, 1},
    {"Smart sleep hrs",  286, FT_U8, 1.0f, "h", 0, 240, 1},
};
#define NTAIL ((int)(sizeof(TAILDEFS) / sizeof(TAILDEFS[0])))
// on/off flags packed in the u16 control word at frame offset 282 (reg 0x1114)
struct BitDef { const char *label; uint16_t mask; };
static const BitDef BITDEFS[] = {
    {"Heating",            0x0001}, {"Disable temp sens", 0x0002},
    {"Display always on",  0x0010}, {"Smart sleep",       0x0040},
    {"Disable PCL",        0x0080}, {"Timed stored data", 0x0100},
    {"Charging float",     0x0200}, {"Emergency button",  0x0400},
    {"Dry-contact intmt",  0x0800}, {"Discharge OCP2",    0x1000},
};
#define NBIT ((int)(sizeof(BITDEFS) / sizeof(BITDEFS[0])))
static int setWidth(uint8_t t) { return (t == FT_U8 || t == FT_I8) ? 1 : (t == FT_U16 || t == FT_I16) ? 2 : 4; }
static float setGet(int b, const SetDef &d) {
    const uint8_t *p = setRaw[b]; int o = d.off - 6; uint32_t raw = 0;
    switch (setWidth(d.type)) {
        case 1: raw = p[o]; break;
        case 2: raw = (uint16_t)(p[o] << 8 | p[o + 1]); break;
        default: raw = (uint32_t)p[o] << 24 | p[o + 1] << 16 | p[o + 2] << 8 | p[o + 3]; break;
    }
    if (d.type == FT_I32) return (int32_t)raw * d.scale;
    if (d.type == FT_I16) return (int16_t)raw * d.scale;
    if (d.type == FT_I8) return (int8_t)raw * d.scale;
    return raw * d.scale;
}
// numeric rows = main settings, plus tail settings when the tail read succeeded
static int numCount(int b) { return NSET + (setOk2[b] ? NTAIL : 0); }
static const SetDef &numDef(int i) { return i < NSET ? SETDEFS[i] : TAILDEFS[i - NSET]; }
static uint16_t bitWord(int b) { return (uint16_t)(setRaw[b][276] << 8 | setRaw[b][277]); }   // offset 282
static int setDec(const SetDef &d) { return d.vstep < 0.1f ? (d.vstep < 0.01f ? 3 : 2) : (d.vstep < 1.0f ? 1 : 0); }
static void fmtSetting(char *o, size_t n, const SetDef &d, float v) { snprintf(o, n, "%.*f%s", setDec(d), v, d.unit); }
// Write a setting (register from the frame offset) and verify by read-back.
static bool setPut(int b, const SetDef &d, float v) {
    if (v < d.vmin) v = d.vmin; if (v > d.vmax) v = d.vmax;
    long raw = lroundf(v / d.scale);
    uint16_t reg = 0x1000 + (d.off - 6);
    if (!bmsSet(b, reg, (uint32_t)(int32_t)raw)) return false;
    int o = d.off - 6;                                       // mirror into local buffer so the row updates
    switch (setWidth(d.type)) {
        case 1: setRaw[b][o] = raw & 0xFF; break;
        case 2: setRaw[b][o] = (raw >> 8) & 0xFF; setRaw[b][o + 1] = raw & 0xFF; break;
        default: setRaw[b][o] = (raw >> 24) & 0xFF; setRaw[b][o + 1] = (raw >> 16) & 0xFF; setRaw[b][o + 2] = (raw >> 8) & 0xFF; setRaw[b][o + 3] = raw & 0xFF; break;
    }
    return true;
}
// Full-screen numeric keypad editor (4x4): 7 8 9 DEL / 4 5 6 CLR / 1 2 3 +/- / . 0 Cancel Save
static const char *KEYLBL[16] = {"7", "8", "9", "DEL", "4", "5", "6", "CLR", "1", "2", "3", "+/-", ".", "0", "Cancel", "Save"};
static void keyRect(int k, int *kx, int *ky, int *kw, int *kh) {
    int x0 = 12, y0 = 96, gap = 8, gw = Wd - 24, gh = Ht - 96 - 10;
    int cw = (gw - 3 * gap) / 4, ch = (gh - 3 * gap) / 4;
    *kx = x0 + (k % 4) * (cw + gap); *ky = y0 + (k / 4) * (ch + gap); *kw = cw; *kh = ch;
}
static void renderEditor() {
    const SetDef &d = numDef(editIdx);
    fRect(0, 0, Wd, Ht, 0, C_BG);
    lText(d.label, 14, 10, F16, C_TEXT);
    int dec = setDec(d);
    char rng[44]; snprintf(rng, sizeof(rng), "range %.*f to %.*f %s", dec, d.vmin, dec, d.vmax, d.unit);
    lText(rng, 14, 70, F12, C_MUTED);
    fRect(14, 32, Wd - 28, 34, 8, C_CARD); dRect(14, 32, Wd - 28, 34, 8, C_ACCENT);
    char shown[24]; snprintf(shown, sizeof(shown), "%s %s", editStr[0] ? editStr : "0", d.unit);
    lText(shown, Wd - 22 - textW(shown, F20), 38, F20, C_TEXT);
    for (int k = 0; k < 16; k++) {
        int kx, ky, kw, kh; keyRect(k, &kx, &ky, &kw, &kh);
        bool save = (k == 15), cancel = (k == 14);
        fRect(kx, ky, kw, kh, 8, save ? C_ACCENT : C_CARD);
        if (!save) dRect(kx, ky, kw, kh, 8, cancel ? C_BAD : C_BORDER);
        cText(KEYLBL[k], kx + kw / 2, ky + kh / 2 - 9, F20, save ? C_BG : (cancel ? C_BAD : C_TEXT));
    }
}
// always-shown rows: 0 battery, 1 TX pin, 2 RX pin. Then (when live) 3 switches,
// then (when the settings block is read) the numeric params + bitmask flags.
#define BMS_FIXED 3
static int bmsRowCount() {
    int b = cfgBms;
    bool live = !demoMode && bmsLive[b];
    bool avail = live && setOk[b];
    if (!live) return BMS_FIXED + 1;                         // + "offline/demo" notice
    if (!avail) return BMS_FIXED + 3 + 1;                    // 3 switches + "reading..." notice
    return BMS_FIXED + 3 + numCount(b) + (setOk2[b] ? NBIT : 0);
}
static int bmsViewH() { return Ht - LIST_TOP - 2; }
static int bmsContentH() { return bmsRowCount() * SROW_STEP + SROW_STEP; }
static int bmsMaxScroll() { int m = bmsContentH() - bmsViewH(); return m > 0 ? m : 0; }
static void renderBmsTab() {
    int b = cfgBms;
    bool live = !demoMode && bmsLive[b];
    bool avail = live && setOk[b];
    int rows = bmsRowCount();
    if (bmsScroll > bmsMaxScroll()) bmsScroll = bmsMaxScroll();
    for (int i = 0; i < rows; i++) {
        int y = LIST_TOP + i * SROW_STEP - bmsScroll;
        if (y + SROW_H < LIST_TOP || y > Ht) continue;
        if (i == 0) srowAt(y, "Battery", cfgBms ? "BAT 2  >" : "BAT 1  >", C_CYAN);
        else if (i == 1) { char v[8]; snprintf(v, sizeof(v), "IO%d", bmsPin[b * 2]);     srowAt(y, "UART TX pin", v, C_CYAN); }
        else if (i == 2) { char v[8]; snprintf(v, sizeof(v), "IO%d", bmsPin[b * 2 + 1]); srowAt(y, "UART RX pin", v, C_CYAN); }
        else if (!live) srowAt(y, "Parameters", demoMode ? "demo mode" : "offline", C_MUTED);
        else {
            int si = i - BMS_FIXED;                          // live section
            if (si == 0) srowToggle(y, "Charge MOSFET", bmsCharge[b]);
            else if (si == 1) srowToggle(y, "Discharge MOSFET", bmsDischarge[b]);
            else if (si == 2) srowToggle(y, "Balancer", bmsBalancer[b]);
            else if (!avail) srowAt(y, "Parameters", "reading...", C_MUTED);
            else {
                int pi = si - 3;
                if (pi < numCount(b)) { const SetDef &d = numDef(pi); char v[16]; fmtSetting(v, sizeof(v), d, setGet(b, d)); srowAt(y, d.label, v, C_TEXT); }
                else { const BitDef &f = BITDEFS[pi - numCount(b)]; srowToggle(y, f.label, bitWord(b) & f.mask); }
            }
        }
    }
    if (bmsMaxScroll() > 0) {                                // scrollbar
        int tX = Wd - 6, tY = LIST_TOP, tH = bmsViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)bmsViewH() / bmsContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)bmsScroll / bmsMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
}
// pixel-scrolled WiFi list (drag to scroll, fixed message + Rescan button)
#define WROW_STEP 34
#define WROW_H 30
static int wListTop() { return 100; }
static int wRescanY() { return Ht - 34; }
static int wViewH() { return wRescanY() - 4 - wListTop(); }
static int wContentH() { return netCount * WROW_STEP; }
static int wMaxScroll() { int m = wContentH() - wViewH(); return m > 0 ? m : 0; }
static void renderWifiTab() {
    bool conn = (WiFi.status() == WL_CONNECTED);
    if (wifiScroll > wMaxScroll()) wifiScroll = wMaxScroll();
    int top = wListTop(), vbot = wRescanY() - 4;
    for (int i = 0; i < netCount; i++) {
        int y = top + i * WROW_STEP - wifiScroll;
        if (y + WROW_H < top || y > vbot) continue;
        int x = 8, w = Wd - 16, h = WROW_H;
        fRect(x, y, w, h, 6, C_CARD); dRect(x, y, w, h, 6, C_BORDER);
        lText(netSsid[i], x + 12, y + 8, F12, C_TEXT);
        int bars = netRssi[i] > -55 ? 4 : netRssi[i] > -65 ? 3 : netRssi[i] > -75 ? 2 : 1;
        for (int b = 0; b < 4; b++) fRect(x + w - 64 + b * 7, y + h - 6 - b * 4, 5, 4 + b * 4, 0, b < bars ? C_ACCENT : C_BORDER);
        if (netEnc[i]) lText("L", x + w - 18, y + 8, F12, C_WARN);
    }
    if (wMaxScroll() > 0) {                                 // scrollbar
        int tX = Wd - 6, tY = top, tH = wViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)wViewH() / wContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)wifiScroll / wMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
    // mask the strip above the list + draw the status message on top
    fRect(0, 78, Wd, top - 78, 0, C_BG);
    lText(wifiMsg, 12, 82, F12, conn ? C_ACCENT : C_MUTED);
    // mask the strip below the list + draw the Rescan button on top
    int ry = wRescanY();
    fRect(0, ry - 2, Wd, Ht - (ry - 2), 0, C_BG);
    fRect(8, ry, Wd - 16, 28, 6, C_CARD); dRect(8, ry, Wd - 16, 28, 6, C_BORDER);
    cText(netCount ? "Rescan" : "Scan", Wd / 2, ry + 14, F16, C_CYAN);
}
// keyboard: draw (draw=true) or hit-test (draw=false -> returns key code)
static int kbProcess(bool draw, int tx, int ty) {
    const int KB_TOP = 96, KH = 34, GAP = 4, KW = 42, CTLH = 44;
    int hit = 0;
    for (int r = 0; r < 4; r++) {
        const char *s = KB[kbMode][r]; int Ln = strlen(s);
        int totalW = Ln * KW + (Ln - 1) * GAP, sx = (Wd - totalW) / 2, y = KB_TOP + r * (KH + GAP);
        for (int i = 0; i < Ln; i++) {
            int x = sx + i * (KW + GAP);
            if (draw) {
                fRect(x, y, KW, KH, 5, C_CARD); dRect(x, y, KW, KH, 5, C_BORDER);
                char c[2] = {s[i], 0}; cText(c, x + KW / 2, y + KH / 2, F16, C_TEXT);
            } else if (tx >= x && tx < x + KW && ty >= y && ty < y + KH) hit = s[i];
        }
    }
    int y = KB_TOP + 4 * (KH + GAP);
    struct { int x, w; const char *lb; int code; } ctl[4] = {
        {8, 62, kbMode == 0 ? "ABC" : kbMode == 1 ? "#+=" : "abc", -2},
        {74, 176, "space", 32}, {254, 92, "del", -1}, {350, 122, "OK", -4}};
    for (int k = 0; k < 4; k++) {
        if (draw) {
            uint32_t bg = ctl[k].code == -4 ? C_ACCENT : C_CARD;
            fRect(ctl[k].x, y, ctl[k].w, CTLH, 6, bg); dRect(ctl[k].x, y, ctl[k].w, CTLH, 6, C_BORDER);
            cText(ctl[k].lb, ctl[k].x + ctl[k].w / 2, y + CTLH / 2, F16, ctl[k].code == -4 ? C_BG : C_TEXT);
        } else if (tx >= ctl[k].x && tx < ctl[k].x + ctl[k].w && ty >= y && ty < y + CTLH) hit = ctl[k].code;
    }
    return hit;
}
static void renderKeyboard() {
    char hdr[48]; snprintf(hdr, sizeof(hdr), "Wi-Fi: %s", wifiSel >= 0 ? netSsid[wifiSel] : "");
    lText(hdr, 12, 8, F12, C_MUTED);
    drawCloseBtn();
    fRect(12, 30, Wd - 24, 30, 6, C_CARD); dRect(12, 30, Wd - 24, 30, 6, C_BORDER);
    lText(wifiPassLen ? wifiPass : "enter password", 22, 38, F16, wifiPassLen ? C_TEXT : C_MUTED);
    kbProcess(true, 0, 0);
}
static void kvLine(int x, int *y, const char *k, const char *v) {
    lText(k, x, *y, F12, C_MUTED); lText(v, x + 96, *y, F12, C_TEXT); *y += 21;
}
static void renderInfoPopup() {
    int w = Wd - 56, h = Ht - 44, x = (Wd - w) / 2, y = (Ht - h) / 2;
    fRect(x, y, w, h, 10, C_CARD); dRect(x, y, w, h, 10, C_ACCENT);
    lText("SYSTEM INFO", x + 16, y + 12, F16, C_TEXT);
    lText("v" FW_VERSION, x + w - 62, y + 14, F12, C_ACCENT);
    int lx = x + 16, ly = y + 44; char b[40];
    kvLine(lx, &ly, "Board", "JC3248W535");
    snprintf(b, sizeof(b), "ESP32-S3 2-core %uMHz", (unsigned)getCpuFrequencyMhz()); kvLine(lx, &ly, "MCU", b);
    snprintf(b, sizeof(b), "%lu MB", (unsigned long)(ESP.getFlashChipSize() / 1048576UL)); kvLine(lx, &ly, "Flash", b);
    snprintf(b, sizeof(b), "%lu / %lu KB", (unsigned long)(ESP.getFreePsram() / 1024), (unsigned long)(ESP.getPsramSize() / 1024)); kvLine(lx, &ly, "PSRAM free", b);
    snprintf(b, sizeof(b), "%lu KB", (unsigned long)(ESP.getFreeHeap() / 1024)); kvLine(lx, &ly, "Heap free", b);
    kvLine(lx, &ly, "MAC", WiFi.macAddress().c_str());
    if (WiFi.status() == WL_CONNECTED) {
        kvLine(lx, &ly, "IP", WiFi.localIP().toString().c_str());
        snprintf(b, sizeof(b), "%s / %s", WEB_USER, webPass); kvLine(lx, &ly, "Web login", b);   // portal + OTA credentials
    } else kvLine(lx, &ly, "WiFi", "not connected");
    snprintf(b, sizeof(b), "%lu s", (unsigned long)(millis() / 1000)); kvLine(lx, &ly, "Uptime", b);
    lText("BMS info: coming soon", lx, ly + 3, F12, C_MUTED);
    lText("tap to close", x + w - 92, y + h - 18, F12, C_MUTED);
}
static void renderSettings() {
    if (kbActive) { renderKeyboard(); return; }
    if (editIdx >= 0) { renderEditor(); return; }   // full-screen modal stepper
    // content first, then mask the header strip so overscrolled rows don't bleed
    // over the title/sub-tabs, then draw the chrome on top.
    if (subTab == ST_BMS) renderBmsTab();
    else if (subTab == ST_WIFI) renderWifiTab();
    else renderSysTab();
    fRect(0, 0, Wd, LIST_TOP - 4, 0, C_BG);
    lText("SETTINGS", 12, 12, F16, C_TEXT);
    drawCloseBtn();
    drawSubTabs();
    if (infoPopup) renderInfoPopup();
}

// ---- wifi (logic) ----
static void wifiStartScan() {
    if (wifiScanning) return;
    wifiScanning = true; wifiSel = -1; wifiScroll = 0;
    snprintf(wifiMsg, sizeof(wifiMsg), "scanning...");
    WiFi.mode(WIFI_STA); WiFi.scanNetworks(true);
}
static void wifiTryConnect() {
    if (wifiSel < 0) return;
    strncpy(connSsid, netSsid[wifiSel], 32); connSsid[32] = 0;
    strncpy(connPass, wifiPass, 32); connPass[32] = 0;
    wifiSaved = false; WiFi.begin(connSsid, connPass);
    snprintf(wifiMsg, sizeof(wifiMsg), "connecting to %s...", connSsid);
}
static bool wifiPoll() {
    bool changed = false;
    if (wifiScanning) {
        int r = WiFi.scanComplete();
        if (r >= 0) {
            int n = r > MAXNET ? MAXNET : r; netCount = n;
            for (int i = 0; i < n; i++) {
                strncpy(netSsid[i], WiFi.SSID(i).c_str(), 32); netSsid[i][32] = 0;
                netRssi[i] = WiFi.RSSI(i); netEnc[i] = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
            }
            WiFi.scanDelete(); wifiScanning = false; changed = true;
            snprintf(wifiMsg, sizeof(wifiMsg), n ? "%d networks found" : "no networks found", n);
        } else if (r == WIFI_SCAN_FAILED) { wifiScanning = false; changed = true; snprintf(wifiMsg, sizeof(wifiMsg), "scan failed"); }
        return changed;
    }
    static uint32_t lastRetry = 0;
    if (connSsid[0] && WiFi.status() != WL_CONNECTED && millis() - lastRetry > 15000) { lastRetry = millis(); WiFi.begin(connSsid, connPass); }
    static wl_status_t last = WL_IDLE_STATUS;
    wl_status_t st = WiFi.status();
    if (st != last) {
        last = st; changed = true;
        if (st == WL_CONNECTED) {
            snprintf(wifiMsg, sizeof(wifiMsg), "Connected: %s", WiFi.SSID().c_str());
            webBegin();   // start the web portal + OTA once we have an IP
            if (!ntpStarted) { configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org", "time.nist.gov"); ntpStarted = true; }
            if (!wifiSaved && connSsid[0]) { prefs.begin("wifi", false); prefs.putString("ssid", connSsid); prefs.putString("pass", connPass); prefs.end(); wifiSaved = true; }
        } else if (st == WL_CONNECT_FAILED) snprintf(wifiMsg, sizeof(wifiMsg), "connect failed (password?)");
        else if (st == WL_NO_SSID_AVAIL) snprintf(wifiMsg, sizeof(wifiMsg), "network not found");
        else if (st == WL_CONNECTION_LOST) snprintf(wifiMsg, sizeof(wifiMsg), "connection lost");
    }
    return changed;
}

// After a tap, only this rect needs repainting (defaults to full screen). Setting
// it to a single settings row makes toggles repaint just that row → snappy.
static bool dirtyFull = true;
static lv_area_t dirtyRect;
static void markRowAt(int y) { dirtyFull = false; dirtyRect = (lv_area_t){8, y, Wd - 9, y + SROW_H - 1}; }
static void markRow(int i) { markRowAt(srowY(i)); }

// ---- settings persistence (NVS) ----
static void markCfg() { cfgDirty = true; cfgDirtyAt = millis(); }
static void saveSettings() {
    prefs.begin("set", false);
    prefs.putBool("autosw", autoSwitch); prefs.putUInt("ival", intervalMs);
    prefs.putInt("bright", brightness); prefs.putInt("sleep", autoSleepMin);
    prefs.putBool("eco", ecoMode); prefs.putInt("dim", dimAfterSec);
    prefs.putBool("tF", tempF); prefs.putBool("f12", fmt12);
    prefs.putBool("wauto", wifiAuto); prefs.putInt("sim", simSpeed);
    prefs.putBool("bc0", bmsCharge[0]); prefs.putBool("bc1", bmsCharge[1]);
    prefs.putBool("bd0", bmsDischarge[0]); prefs.putBool("bd1", bmsDischarge[1]);
    prefs.putBool("bb0", bmsBalancer[0]); prefs.putBool("bb1", bmsBalancer[1]);
    prefs.putBool("demo", demoMode);
    prefs.putInt("idle", idleScreen);
    prefs.putBytes("pins", bmsPin, sizeof(bmsPin));
    prefs.putString("wpass", webPass);
    prefs.end();
}
static void loadSettings() {
    prefs.begin("set", true);
    autoSwitch = prefs.getBool("autosw", autoSwitch); intervalMs = prefs.getUInt("ival", intervalMs);
    brightness = prefs.getInt("bright", brightness); autoSleepMin = prefs.getInt("sleep", autoSleepMin);
    ecoMode = prefs.getBool("eco", ecoMode); dimAfterSec = prefs.getInt("dim", dimAfterSec);
    tempF = prefs.getBool("tF", tempF); fmt12 = prefs.getBool("f12", fmt12);
    wifiAuto = prefs.getBool("wauto", wifiAuto); simSpeed = prefs.getInt("sim", simSpeed);
    bmsCharge[0] = prefs.getBool("bc0", true); bmsCharge[1] = prefs.getBool("bc1", true);
    bmsDischarge[0] = prefs.getBool("bd0", true); bmsDischarge[1] = prefs.getBool("bd1", true);
    bmsBalancer[0] = prefs.getBool("bb0", false); bmsBalancer[1] = prefs.getBool("bb1", false);
    demoMode = prefs.getBool("demo", demoMode);
    idleScreen = prefs.getInt("idle", idleScreen);
    if (prefs.isKey("pins")) prefs.getBytes("pins", bmsPin, sizeof(bmsPin));
    if (prefs.isKey("wpass")) { String wp = prefs.getString("wpass", webPass); strncpy(webPass, wp.c_str(), sizeof(webPass) - 1); webPass[sizeof(webPass) - 1] = 0; }
    else { uint8_t mac[6] = {0}; esp_read_mac(mac, ESP_MAC_WIFI_STA); snprintf(webPass, sizeof(webPass), "jk-%02x%02x", mac[4], mac[5]); }   // fresh install → unique default (from eFuse MAC), not the public 'jkbms'
    prefs.end();
    appliedB = brightness;
}
// Persist the real graph history (only the valid `count` samples per BMS).
static void saveHistory() {
    prefs.begin("hist", false);
    for (int t = 0; t < 2; t++) {
        char k[8];
        size_t capN = histCount[t] * sizeof(histCap[0][0]), pwrN = histCount[t] * sizeof(histPwr[0][0]);
        snprintf(k, sizeof(k), "c%d", t); prefs.putUShort(k, histCount[t]);
        snprintf(k, sizeof(k), "cap%d", t); size_t wc = prefs.putBytes(k, histCap[t], capN);
        snprintf(k, sizeof(k), "pwr%d", t); size_t wp = prefs.putBytes(k, histPwr[t], pwrN);
        if (wc != capN || wp != pwrN) Serial.printf("[nvs] history save BMS%d failed (cap %u/%u, pwr %u/%u) — NVS full?\n",
                                                     t + 1, (unsigned)wc, (unsigned)capN, (unsigned)wp, (unsigned)pwrN);
    }
    prefs.end();
}
static void loadHistory() {
    prefs.begin("hist", false);
    if (prefs.getUChar("ver", 0) != 1) {               // one-time wipe of pre-fix history (had bogus 0% points)
        prefs.clear(); prefs.putUChar("ver", 1);
        histCount[0] = histCount[1] = 0;
        prefs.end(); return;
    }
    for (int t = 0; t < 2; t++) {
        char k[8];
        snprintf(k, sizeof(k), "c%d", t); int c = prefs.getUShort(k, 0); if (c > HIST_N) c = HIST_N;
        snprintf(k, sizeof(k), "cap%d", t); prefs.getBytes(k, histCap[t], c * sizeof(histCap[0][0]));
        snprintf(k, sizeof(k), "pwr%d", t); prefs.getBytes(k, histPwr[t], c * sizeof(histPwr[0][0]));
        histCount[t] = c;
    }
    prefs.end();
}

// ---- touch handling (logic) ----
static void handleTap(int x, int y) {
    dirtyFull = true;   // most taps change the whole screen unless noted below
    if (view == V_SETTINGS) {
        if (infoPopup) { infoPopup = false; return; }
        if (editIdx >= 0) {                                  // numeric keypad modal
            const SetDef &d = numDef(editIdx);
            for (int k = 0; k < 16; k++) {
                int kx, ky, kw, kh; keyRect(k, &kx, &ky, &kw, &kh);
                if (x < kx || x >= kx + kw || y < ky || y >= ky + kh) continue;
                int len = strlen(editStr);
                if (k == 14) { editIdx = -1; }                                   // Cancel
                else if (k == 15) {                                             // Save → clamp, write, verify
                    bool hasNum = editStr[0] && !(editStr[0] == '-' && editStr[1] == 0);   // ignore empty / lone "-"
                    if (hasNum && setPut(editBms, d, atof(editStr))) markCfg();
                    editIdx = -1;
                } else if (k == 3) { if (len) editStr[len - 1] = 0; }           // DEL
                else if (k == 7) { editStr[0] = 0; }                            // CLR
                else if (k == 11) {                                            // +/-
                    if (editStr[0] == '-') memmove(editStr, editStr + 1, len);
                    else if (len < 10) { memmove(editStr + 1, editStr, len + 1); editStr[0] = '-'; }
                } else if (k == 12) { if (!strchr(editStr, '.') && len < 10) { editStr[len] = '.'; editStr[len + 1] = 0; } }  // '.'
                else if (len < 10) { editStr[len] = KEYLBL[k][0]; editStr[len + 1] = 0; }   // digit
                return;
            }
            return;
        }
        if (kbActive) {
            if (x >= CLOSE_X - 12 && y <= 44) { kbActive = false; return; }
            int code = kbProcess(false, x, y);
            if (code > 0) { if (wifiPassLen < 32) { wifiPass[wifiPassLen++] = (char)code; wifiPass[wifiPassLen] = 0; } }
            else if (code == -1) { if (wifiPassLen > 0) wifiPass[--wifiPassLen] = 0; }
            else if (code == -2) kbMode = (kbMode + 1) % 3;
            else if (code == -4) { kbActive = false; wifiTryConnect(); }
            return;
        }
        if (x >= CLOSE_X - 12 && y <= 44) { switchView(V_BMS1); manualUntil = millis() + PAUSE_MS; lastSwitch = millis(); return; }
        if (y >= 44 && y < 74) {
            for (int i = 0; i < 3; i++) { int tx, tw; subTabGeom(i, &tx, &tw);
                if (x >= tx && x < tx + tw) { subTab = i; if (i == ST_WIFI && netCount == 0) wifiStartScan(); return; } }
            return;
        }
        if (subTab == ST_SYSTEM) {
            if (y < LIST_TOP) return;
            int idx = (y + sysScroll - LIST_TOP) / SROW_STEP;
            int ry = LIST_TOP + idx * SROW_STEP - sysScroll;
            if (idx < 0 || idx >= SYS_ROWS || y < ry || y >= ry + SROW_H) return;
            switch (idx) {
                case 0: autoSwitch = !autoSwitch; break;
                case 1: intervalMs = intervalMs == 3000 ? 5000 : intervalMs == 5000 ? 10000 : 3000; break;
                case 2: brightness += (x < Wd / 2) ? -10 : 10; brightness = constrain(brightness, 10, 100); setBrightness(brightness); appliedB = brightness; break;
                case 3: autoSleepMin = autoSleepMin == 0 ? 2 : autoSleepMin == 2 ? 5 : autoSleepMin == 5 ? 30 : autoSleepMin == 30 ? 120 : 0; break;
                case 4: ecoMode = !ecoMode; break;
                case 5: dimAfterSec = dimAfterSec == 0 ? 30 : dimAfterSec == 30 ? 60 : dimAfterSec == 60 ? 300 : 0; break;
                case 6: tempF = !tempF; break;
                case 7: fmt12 = !fmt12; break;
                case 8: wifiAuto = !wifiAuto; WiFi.setAutoReconnect(wifiAuto); break;
                case 9: simSpeed = simSpeed == 1 ? 2 : simSpeed == 2 ? 5 : 1; break;
                case 10: infoPopup = true; return;   // full redraw for the popup
                case 12: demoMode = !demoMode; if (demoMode) simInit(); bmsRead(); break;   // toggle sim vs live BMS, re-poll
                case 13: idleScreen = (idleScreen + 1) % 6; break;   // cycle no-data screen
                default: return;                      // firmware row: no-op
            }
            markCfg(); markRowAt(ry);
        } else if (subTab == ST_BMS) {
            if (y < LIST_TOP) return;
            int idx = (y + bmsScroll - LIST_TOP) / SROW_STEP;
            int ry = LIST_TOP + idx * SROW_STEP - bmsScroll;
            if (idx < 0 || idx >= bmsRowCount() || y < ry || y >= ry + SROW_H) return;
            int b = cfgBms;
            bool live = !demoMode && bmsLive[b];
            if (idx == 0) { cfgBms ^= 1; bmsScroll = 0; return; }                                     // switch pack (full redraw)
            if (idx == 1) { bmsPin[b * 2] = nextPin(bmsPin[b * 2]); bmsBegin(); markCfg(); markRowAt(ry); return; }        // UART TX pin
            if (idx == 2) { bmsPin[b * 2 + 1] = nextPin(bmsPin[b * 2 + 1]); bmsBegin(); markCfg(); markRowAt(ry); return; } // UART RX pin
            if (!live) return;                                                                        // offline/demo: nothing below
            int si = idx - BMS_FIXED;                                                                 // live section
            if (si == 0) { bmsCharge[b] = !bmsCharge[b]; if (!bmsSet(b, 0x1070, bmsCharge[b] ? 1 : 0)) bmsCharge[b] = !bmsCharge[b]; markCfg(); markRowAt(ry); return; }
            if (si == 1) { bmsDischarge[b] = !bmsDischarge[b]; if (!bmsSet(b, 0x1074, bmsDischarge[b] ? 1 : 0)) bmsDischarge[b] = !bmsDischarge[b]; markCfg(); markRowAt(ry); return; }
            if (si == 2) { bmsBalancer[b] = !bmsBalancer[b]; if (!bmsSet(b, 0x1078, bmsBalancer[b] ? 1 : 0)) bmsBalancer[b] = !bmsBalancer[b]; markCfg(); markRowAt(ry); return; }
            if (setOk[b]) {
                int pi = si - 3;
                // Only the main 4-byte (UINT32) settings are writable; the packed tail
                // fields (bitmask flags, heating, sleep-hours) are display-only.
                if (pi >= 0 && pi < NSET) { editIdx = pi; editBms = b; editStr[0] = 0; }   // open keypad (full redraw)
            }
        } else {   // ST_WIFI
            int top = wListTop(), vbot = wRescanY() - 4;
            if (y >= top && y <= vbot) {
                int idx = (y + wifiScroll - top) / WROW_STEP;
                int ry2 = top + idx * WROW_STEP - wifiScroll;
                if (idx >= 0 && idx < netCount && y >= ry2 && y < ry2 + WROW_H) {
                    wifiSel = idx;
                    if (netEnc[wifiSel]) { wifiPass[0] = 0; wifiPassLen = 0; kbMode = 0; kbActive = true; }
                    else wifiTryConnect();
                }
                return;
            }
            int ry = wRescanY();
            if (y >= ry && y < ry + 28) wifiStartScan();
        }
        return;
    }
    // dashboard top bar — generous hit zones (corners are hard to hit precisely)
    manualUntil = millis() + PAUSE_MS;
    if (y <= 44) {
        if (x >= TAB1_X && x < TAB1_X + TAB_W) { switchView(V_BMS1); lastSwitch = millis(); }
        else if (x >= TAB2_X && x < TAB2_X + TAB_W) { switchView(V_BMS2); lastSwitch = millis(); }
        else if (x >= GEAR_X - 10) { cfgBms = (view == V_BMS2) ? 1 : 0; view = V_SETTINGS; kbActive = false; infoPopup = false; }  // keep last sub-tab
        else if (x >= BED_X - 8) pendingSleep = true;                                                              // sleep, left of the gear
    }
}

// ============================================================================
//  Sleep animation — drawn straight to the canvas (full flush), like the original
// ============================================================================
static uint16_t c565(uint32_t hex) { return gfx->color565((hex >> 16) & 0xff, (hex >> 8) & 0xff, hex & 0xff); }
static uint16_t dimC(uint8_t r, uint8_t gg, uint8_t b, uint8_t br) { return gfx->color565((r * br) / 255, (gg * br) / 255, (b * br) / 255); }
static uint16_t wheel(float h) {
    h = fmodf(h, 1.0f); if (h < 0) h += 1.0f;
    float r = fabsf(h * 6 - 3) - 1, g = 2 - fabsf(h * 6 - 2), b = 2 - fabsf(h * 6 - 4);
    auto cl = [](float v) { return v < 0 ? 0.0f : v > 1 ? 1.0f : v; };
    return gfx->color565((uint8_t)(cl(r) * 255), (uint8_t)(cl(g) * 255), (uint8_t)(cl(b) * 255));
}
static void drawIco(int cx, int cy, float scale, float ax, float ay, float az, float hue) {
    static const float t = 1.61803f;
    static const float BV[12][3] = {{-1,t,0},{1,t,0},{-1,-t,0},{1,-t,0},{0,-1,t},{0,1,t},{0,-1,-t},{0,1,-t},{t,0,-1},{t,0,1},{-t,0,-1},{-t,0,1}};
    static const uint8_t F[20][3] = {{0,11,5},{0,5,1},{0,1,7},{0,7,10},{0,10,11},{1,5,9},{5,11,4},{11,10,2},{10,7,6},{7,1,8},{3,9,4},{3,4,2},{3,2,6},{3,6,8},{3,8,9},{4,9,5},{2,4,11},{6,2,10},{8,6,7},{9,8,1}};
    float rx[12], ry[12], rz[12]; int px[12], py[12];
    float ca = cosf(ax), sa = sinf(ax), cb = cosf(ay), sb = sinf(ay), cc = cosf(az), sc = sinf(az);
    const float d = 4.0f;
    for (int i = 0; i < 12; i++) {
        float x = BV[i][0], y = BV[i][1], z = BV[i][2];
        float y1 = y * ca - z * sa, z1 = y * sa + z * ca;
        float x2 = x * cb + z1 * sb, z2 = -x * sb + z1 * cb;
        float x3 = x2 * cc - y1 * sc, y3 = x2 * sc + y1 * cc;
        rx[i] = x3; ry[i] = y3; rz[i] = z2;
        float p = d / (d - z2);
        px[i] = cx + (int)(x3 * scale * p); py[i] = cy + (int)(y3 * scale * p);
    }
    const float lx = 0.40f, ly = 0.50f, lz = 0.77f;
    int order[20]; float fz[20]; int n = 0;
    for (int f = 0; f < 20; f++) {
        int a = F[f][0], b = F[f][1], c = F[f][2];
        long area = (long)(px[b] - px[a]) * (py[c] - py[a]) - (long)(py[b] - py[a]) * (px[c] - px[a]);
        if (area <= 0) continue;
        order[n] = f; fz[n] = rz[a] + rz[b] + rz[c]; n++;
    }
    for (int i = 1; i < n; i++) { int oo = order[i]; float ff = fz[i]; int k = i - 1; while (k >= 0 && fz[k] > ff) { fz[k+1] = fz[k]; order[k+1] = order[k]; k--; } order[k+1] = oo; fz[k+1] = ff; }
    for (int i = 0; i < n; i++) {
        int f = order[i], a = F[f][0], b = F[f][1], c = F[f][2];
        float ux = rx[b]-rx[a], uy = ry[b]-ry[a], uz = rz[b]-rz[a];
        float vx = rx[c]-rx[a], vy = ry[c]-ry[a], vz = rz[c]-rz[a];
        float nx = uy*vz-uz*vy, ny = uz*vx-ux*vz, nz = ux*vy-uy*vx;
        float nl = sqrtf(nx*nx+ny*ny+nz*nz); if (nl < 1e-3f) nl = 1;
        float diff = (nx*lx + ny*ly + nz*lz) / nl; if (diff < 0) diff = -diff;
        float br = 0.22f + 0.78f * diff; if (br > 1) br = 1;
        uint16_t base = wheel(hue + f * 0.013f);
        uint8_t rr = ((base >> 11) & 0x1f) << 3, gg = ((base >> 5) & 0x3f) << 2, bb = (base & 0x1f) << 3;
        gfx->fillTriangle(px[a], py[a], px[b], py[b], px[c], py[c], gfx->color565((uint8_t)(rr*br), (uint8_t)(gg*br), (uint8_t)(bb*br)));
    }
    uint16_t ec = dimC(0xff, 0xff, 0xff, 70);
    for (int i = 0; i < n; i++) { int f = order[i], a = F[f][0], b = F[f][1], c = F[f][2]; gfx->drawTriangle(px[a], py[a], px[b], py[b], px[c], py[c], ec); }
}
// Robot-vision power-OFF: the image collapses vertically into a bright scan line,
// flickers, retracts horizontally to a dot, then blinks out — the reverse of
// playVisionOn(). Ends with the backlight at its lowest (restored on wake).
static void playSleepAnimation() {
    const uint16_t BG = gfx->color565(0x09, 0x03, 0x02);
    const uint16_t AMBER = gfx->color565(0xff, 0xb0, 0x28), GLOW = gfx->color565(0x70, 0x40, 0x12);
    const uint16_t WHITE = gfx->color565(0xff, 0xf0, 0xd0);
    int cx = Wd / 2, cy = Ht / 2;
    uint32_t t0 = millis();                                   // vertical collapse → horizontal line
    for (;;) {
        uint32_t el = millis() - t0; float p = el / 300.0f; if (p > 1) p = 1;
        int hh = (int)((1 - p) * cy);                         // half-height shrinks to 0
        uint8_t v = (uint8_t)(60 + 195 * p);                  // brightens as it concentrates
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - hh, Wd, hh * 2 + 2, gfx->color565(v, (uint8_t)(v * 0.85f), (uint8_t)(v * 0.5f)));
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    for (int f = 0; f < 3; f++) {                             // flicker
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - 2, Wd, 4, (f & 1) ? AMBER : WHITE);
        gfx->flush(); uint32_t b = millis(); while (millis() - b < 45) delay(1);
    }
    uint32_t t1 = millis();                                   // line retracts to a dot
    for (;;) {
        uint32_t el = millis() - t1; float p = el / 360.0f; if (p > 1) p = 1;
        int hw = (int)((1 - p) * (1 - p) * (Wd / 2));         // ease-out retract
        int gh = 3 + (int)(5 * p), core = hw < 6 ? hw : 6;
        gfx->fillScreen(BG);
        gfx->fillRect(cx - hw - 2, cy - gh, (hw + 2) * 2, gh * 2, GLOW);
        gfx->fillRect(cx - hw, cy - 2, hw * 2 + 1, 4, AMBER);
        gfx->fillRect(cx - core, cy - 1, core * 2 + 1, 2, WHITE);
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    for (int f = 0; f < 2; f++) {                             // dot blinks out
        gfx->fillScreen(BG); int r = 4 - f * 2; if (r > 0) gfx->fillCircle(cx, cy, r, WHITE);
        gfx->flush(); uint32_t b = millis(); while (millis() - b < 55) delay(1);
    }
    gfx->fillScreen(BG); gfx->flush();
    ledcWrite(TFT_BL, 0); appliedB = 0;                       // backlight off (lowest) until a touch wakes us
    standby = true;
}

// centred bitmap text straight on the canvas (used by the boot animation)
static void ctc(const char *s, int cx, int cy, uint8_t size, uint16_t col) {
    int16_t x1, y1; uint16_t w, h; gfx->setTextSize(size); gfx->getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
    gfx->setTextColor(col); gfx->setCursor(cx - w / 2 - x1, cy - h / 2 - y1); gfx->print(s);
}
// jagged lightning bolt from (x1,y1) to (x2,y2)
static void tl(int x1, int y1, int x2, int y2, uint16_t c) {   // 2px line
    gfx->drawLine(x1, y1, x2, y2, c); gfx->drawLine(x1, y1 + 1, x2, y2 + 1, c);
}
// Round-capped thick line — gives the ninja solid, tapered limbs (not 2px sticks).
static void thickLine(int x1, int y1, int x2, int y2, int th, uint16_t c) {
    int n = abs(x2 - x1) > abs(y2 - y1) ? abs(x2 - x1) : abs(y2 - y1); if (n < 1) n = 1;
    int r = th / 2; if (r < 1) r = 1;
    for (int i = 0; i <= n; i++) gfx->fillCircle(x1 + (x2 - x1) * i / n, y1 + (y2 - y1) * i / n, r, c);
}
// Red ninja in a leaning run: hooded head + eye-slit + headband tails, solid
// tapered torso tilted forward, thick bent-knee legs (back leg kicks up behind),
// swinging bent arms. air = mid-leap (knees tucked).
static void drawNinja(int cx, int footY, float run, bool air, float sc) {
    uint16_t body = gfx->color565(0xcc, 0x22, 0x22), limb = gfx->color565(0x8c, 0x16, 0x16);
    uint16_t scarf = gfx->color565(0xff, 0x55, 0x55), blade = gfx->color565(0xcf, 0xd8, 0xe6);
    uint16_t skin = gfx->color565(0xe6, 0xc2, 0xa0);
    int hipY = footY - (int)(24 * sc), shY = footY - (int)(44 * sc);
    int lean = (int)(11 * sc), shCx = cx + lean;          // shoulders/head lean forward over the hips
    int headX = shCx + (int)(2 * sc), headY = shY - (int)(9 * sc), hr = (int)(9 * sc);
    int legTh = (int)(7 * sc), armTh = (int)(6 * sc), thigh = (int)(13 * sc), shin = (int)(13 * sc);
    float sw = sinf(run * 6.2832f);                       // stride phase (-1..1)
    // bent-knee leg. s>0 = leg reaching forward-down, s<0 = leg kicking up behind.
    auto drawLeg = [&](float s, uint16_t col) {
        float ta = s * 0.85f, bend = 0.55f + 0.85f * (0.5f - 0.5f * s);
        int kx = cx + (int)(sinf(ta) * thigh), ky = hipY + (int)(cosf(ta) * thigh);
        float sa = ta - bend;
        int fx = kx + (int)(sinf(sa) * shin), fy = ky + (int)(cosf(sa) * shin);
        thickLine(cx, hipY, kx, ky, legTh, col);
        thickLine(kx, ky, fx, fy, legTh, col);
        gfx->fillRect(fx - (int)(2 * sc), fy - (int)(2 * sc), (int)(9 * sc), (int)(4 * sc), col);
    };
    auto drawLegTuck = [&](float s, uint16_t col) {      // knees pulled up while airborne
        int kx = cx + (int)(s * 11 * sc), ky = hipY + (int)(1 * sc);
        int fx = kx + (int)(s * 3 * sc), fy = ky - (int)(11 * sc);
        thickLine(cx, hipY, kx, ky, legTh, col);
        thickLine(kx, ky, fx, fy, legTh, col);
    };
    // bent arm swinging from the (leaning) shoulder.
    auto drawArm = [&](float s, uint16_t col) {
        float ua = s * 0.95f;
        int ex = shCx + (int)(sinf(ua) * 9 * sc), ey = shY + (int)(7 * sc) + (int)(cosf(ua) * 4 * sc);
        float fa = ua + 1.15f;
        int hx = ex + (int)(sinf(fa) * 9 * sc), hy = ey + (int)(cosf(fa) * 7 * sc);
        thickLine(shCx, shY + (int)(3 * sc), ex, ey, armTh, col);
        thickLine(ex, ey, hx, hy, armTh, col);
    };
    // back limbs first (darker, behind torso); legs & arms swing opposite
    if (air) { drawLegTuck(-0.8f, limb); drawArm(-1.3f, limb); }
    else { drawLeg(-sw, limb); drawArm(sw, limb); }
    // katana across the (leaning) back
    thickLine(shCx - (int)(4 * sc), shY + (int)(1 * sc), shCx - (int)(13 * sc), shY + (int)(20 * sc), (int)(3 * sc), blade);
    // solid tapered torso, tilted forward (hips at cx, shoulders at shCx)
    gfx->fillTriangle(cx - (int)(7 * sc), hipY, cx + (int)(7 * sc), hipY, shCx + (int)(5 * sc), shY, body);
    gfx->fillTriangle(cx - (int)(7 * sc), hipY, shCx + (int)(5 * sc), shY, shCx - (int)(5 * sc), shY, body);
    gfx->fillRect(cx - (int)(7 * sc), hipY - (int)(2 * sc), (int)(14 * sc), (int)(3 * sc), gfx->color565(0x40, 0x0a, 0x0a)); // belt
    // head (hood + eye-slit + headband + flowing tails)
    gfx->fillCircle(headX, headY, hr, body);
    gfx->fillRect(headX + (int)(1 * sc), headY - (int)(1 * sc), (int)(7 * sc), (int)(3 * sc), skin);   // eye slit
    gfx->fillRect(headX - hr, headY - (int)(4 * sc), 2 * hr, (int)(3 * sc), scarf);                     // band
    for (int k = 0; k < 3; k++) { int x1 = headX - hr - (int)((4 + k * 7) * sc), y1 = headY - (int)(2 * sc) + (int)(7 * sc * sinf(run * 6.2832f * 1.5f + k)); tl(headX - hr, headY - (int)(2 * sc), x1, y1, scarf); }
    // front limbs (brighter, in front of torso)
    if (air) { drawArm(1.3f, body); drawLegTuck(0.8f, body); }
    else { drawArm(-sw, body); drawLeg(sw, body); }
}
// Draw the parallax city scene + ninja for boot time t (0..0.82 on-screen).
static int bootSx[44], bootSy[44]; static bool bootInit = false;
static void drawBootScene(float t) {
    const int W = Wd, H = Ht, groundY = 250;
    if (!bootInit) { for (int i = 0; i < 44; i++) { bootSx[i] = (i * 97) % W; bootSy[i] = (i * 53) % 70 + 4; } bootInit = true; }
    // sky gradient (dark blue → near black at top)
    for (int b = 0; b < 6; b++) gfx->fillRect(0, b * 12, W, 12, gfx->color565(3 + b, 4 + b, 10 + b * 2));
    gfx->fillRect(0, 72, W, groundY - 72, gfx->color565(7, 8, 20));
    gfx->fillCircle(W - 70, 56, 26, gfx->color565(0x40, 0x44, 0x60));      // moon
    gfx->fillCircle(W - 62, 50, 26, gfx->color565(7, 8, 20));              // crescent cut
    float scF = t * W * 0.5f;                                              // stars (far parallax)
    for (int i = 0; i < 44; i++) { int x = ((int)(bootSx[i] - scF * (0.3f + (i % 3) * 0.15f))) % W; if (x < 0) x += W; gfx->drawPixel(x, bootSy[i], dimC(0x9d, 0xb4, 0xff, 110 + (i % 4) * 35)); }
    float bc = fmodf(t * W * 1.6f, 1120);                                  // buildings (mid) + windows
    for (int i = -1; i < 16; i++) {
        int bx = (int)(i * 70 - bc), bh = 44 + (((i + 16) * 53) % 86), bw = 36 + (((i + 16) * 37) % 26);
        gfx->fillRect(bx, groundY - bh, bw, bh, gfx->color565(14, 15, 28));
        for (int wy = groundY - bh + 6; wy < groundY - 6; wy += 12)
            for (int wx = bx + 5; wx < bx + bw - 4; wx += 10)
                if (((wx * 7 + wy * 13 + i) % 5) < 2) gfx->fillRect(wx, wy, 4, 5, gfx->color565(0x6a, 0x5a, 0x20));
    }
    for (int i = 0; i < 18; i++) {                                         // speed lines (fast)
        float r = fmodf(t * 3.4f * (0.6f + (i % 5) * 0.12f) + i * 0.137f, 1.0f);
        int x = (int)((1 - r) * (W + 90)) - 90, y = (i * 113) % H, len = 26 + (int)(80 * r);
        gfx->drawFastHLine(x, y, len, dimC(0xff, 0x44, 0x44, (uint8_t)(45 + 140 * r)));
    }
    gfx->fillRect(0, groundY, W, H - groundY, gfx->color565(9, 10, 18));
    gfx->drawFastHLine(0, groundY, W, gfx->color565(0x80, 0x14, 0x14));
    float gc = fmodf(t * W * 2.8f, 40);                                    // ground dashes (fastest)
    for (int i = -1; i < W / 40 + 1; i++) gfx->drawFastHLine((int)(i * 40 - gc), groundY + 8, 20, dimC(0xff, 0x30, 0x30, 90));
    // ninja: runs in place (world scrolls), then leaps OFF the top-right
    int nx, ny; bool air;
    if (t < 0.60f) { nx = 150; ny = groundY; air = false; }
    else { float a = (t - 0.60f) / 0.22f; if (a > 1) a = 1; nx = 150 + (int)(a * (W - 60)); ny = groundY - (int)(a * (groundY + 120)); air = true; }
    drawNinja(nx, ny, t * 8.0f, air, 1.7f);
}
// Power-on: fast parallax city, a running ninja leaps off-screen, then flashes.
static void playBootAnimation() {
    uint32_t t0 = millis(); const float DUR = 3000.0f;
    for (;;) {
        float t = (millis() - t0) / DUR; if (t >= 1.0f) break;
        setBrightness((int)(20 + 80 * (t < 0.7f ? t / 0.7f : 1.0f)));
        if (t < 0.82f) drawBootScene(t);                                   // scene + leap-out
        else { float f = (t - 0.82f) / 0.18f; if (f > 1) f = 1; uint8_t w = (uint8_t)(255 * (1.0f - f) + 4); gfx->fillScreen(gfx->color565(w, w, w)); }  // one flash, fades to bg
        gfx->flush();
    }
    gfx->fillScreen(c565(C_BG)); gfx->flush();                             // hand off to the app
    setBrightness(brightness);
}
// Robot-vision power-on: a single dot swells into a full-width scan line, flickers,
// then blooms vertically into a fading flash — like an optical sensor coming online.
static void playVisionOn() {
    const uint16_t BG = gfx->color565(0x09, 0x03, 0x02);
    const uint16_t AMBER = gfx->color565(0xff, 0xb0, 0x28), GLOW = gfx->color565(0x70, 0x40, 0x12);
    const uint16_t WHITE = gfx->color565(0xff, 0xf0, 0xd0);
    int cx = Wd / 2, cy = Ht / 2;
    setBrightness(brightness);
    uint32_t t0 = millis();                                   // dot → horizontal line
    for (;;) {
        uint32_t el = millis() - t0; float p = el / 420.0f; if (p > 1) p = 1;
        int hw = (int)(p * p * (Wd / 2 - 2));                 // ease-in half-width
        int gh = 3 + (int)(5 * (1 - p));                      // glow thicker early (the dot)
        int core = hw < 6 ? hw : 6;
        gfx->fillScreen(BG);
        gfx->fillRect(cx - hw - 2, cy - gh, (hw + 2) * 2, gh * 2, GLOW);
        gfx->fillRect(cx - hw, cy - 2, hw * 2 + 1, 4, AMBER);
        gfx->fillRect(cx - core, cy - 1, core * 2 + 1, 2, WHITE);
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    for (int f = 0; f < 3; f++) {                             // quick flicker
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - 2, Wd, 4, (f & 1) ? WHITE : AMBER);
        gfx->flush(); uint32_t b = millis(); while (millis() - b < 45) delay(1);
    }
    uint32_t t1 = millis();                                   // vertical bloom + fade to black
    for (;;) {
        uint32_t el = millis() - t1; float p = el / 260.0f; if (p > 1) p = 1;
        int hh = (int)(p * cy);
        uint8_t v = (uint8_t)(255 * (1 - p) + 8);
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - hh, Wd, hh * 2, gfx->color565(v, (uint8_t)(v * 0.85f), (uint8_t)(v * 0.5f)));
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    gfx->fillScreen(BG); gfx->flush();
}
// Second act: a retro tactical-HUD boot log (Terminator-style) — amber pixel text
// on black with scanlines, status lines flipping to [ OK ], a progress bar and a
// blinking cursor, ending on READY. Built-in GFX font = chunky monospace look.
static void playHudBoot() {
    static const char *HUD[] = {
        "POWER CORE",
        "DISPLAY DRIVER",
        "TOUCH INTERFACE",
        "ESTABLISHING DATA LINK",
        "SECURING DATA LINK",
        "CONNECTING BATTERIES",
        "RECEIVING INPUT DATA",
        "WAITING FOR DATA",
        "SYSTEMS ONLINE",
    };
    const int N = sizeof(HUD) / sizeof(HUD[0]);
    const uint32_t STEP = 230, TAIL = 650, END = N * STEP + TAIL;
    const uint16_t AMBER = gfx->color565(0xff, 0xb0, 0x28), RED = gfx->color565(0xff, 0x38, 0x20);
    const uint16_t DIM = gfx->color565(0x4a, 0x16, 0x0e), BG = gfx->color565(0x09, 0x03, 0x02);
    setBrightness(brightness);
    uint32_t t0 = millis();
    for (;;) {
        uint32_t el = millis() - t0;
        gfx->fillScreen(BG);
        for (int y = (el / 70) % 3; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);   // scrolling scanlines
        // header + rule
        gfx->setTextSize(2); gfx->setTextColor(RED); gfx->setCursor(14, 12); gfx->print("JK-BMS TACTICAL MONITOR");
        gfx->drawFastHLine(14, 36, Wd - 28, RED); gfx->drawFastHLine(14, 38, Wd - 28, DIM);
        // targeting reticle, tucked in the top-right corner (clear of the status tags)
        int rx = Wd - 26, ry = 18;
        gfx->drawCircle(rx, ry, 12, AMBER); gfx->drawCircle(rx, ry, 4, RED);
        gfx->drawFastHLine(rx - 12, ry, 24, AMBER); gfx->drawFastVLine(rx, ry - 12, 24, AMBER);
        // log lines
        int shown = el / STEP; if (shown > N) shown = N;
        gfx->setTextSize(2);
        for (int i = 0; i < shown; i++) {
            int ly = 54 + i * 24;
            bool ok = el > (i + 1) * STEP + 60;                  // [ .. ] then flips to [ OK ]
            gfx->setTextColor(AMBER); gfx->setCursor(16, ly); gfx->print(HUD[i]);
            gfx->setTextColor(ok ? AMBER : RED); gfx->setCursor(Wd - 16 - 72, ly); gfx->print(ok ? "[ OK ]" : "[ .. ]");
        }
        if (shown < N && ((el / 320) & 1)) { gfx->fillRect(16, 54 + shown * 24, 13, 17, AMBER); }   // cursor
        // progress bar
        int bx = 16, by = Ht - 24, bw = Wd - 32;
        float p = (float)el / END; if (p > 1) p = 1;
        gfx->drawRect(bx, by, bw, 14, RED);
        gfx->fillRect(bx + 2, by + 2, (int)((bw - 4) * p), 10, AMBER);
        gfx->setTextSize(1); gfx->setTextColor(AMBER); gfx->setCursor(bx, by - 12);
        char pc[8]; snprintf(pc, sizeof(pc), "%d%%", (int)(p * 100)); gfx->print(pc);
        gfx->flush();
        if (el > END) break;
        delay(1);
    }
    // "READY" with dots building up one by one
    uint32_t r0 = millis();
    for (;;) {
        uint32_t el = millis() - r0; if (el > 950) break;
        gfx->fillScreen(BG);
        for (int y = (el / 70) % 3; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);
        int dots = el / 150; if (dots > 5) dots = 5;
        char buf[12] = "READY"; for (int i = 0; i < dots; i++) buf[5 + i] = '.'; buf[5 + dots] = 0;
        gfx->setTextSize(4); gfx->setTextColor(RED);
        gfx->setCursor((Wd - 5 * 24) / 2, (Ht - 32) / 2); gfx->print(buf);   // size4 → 24px/char
        gfx->flush(); delay(1);
    }
    gfx->fillScreen(c565(C_BG)); gfx->flush();   // hand off to the app
}

// ============================================================================
//  Idle / "no battery detected" screens (gfx-direct, animated; chosen in Settings)
// ============================================================================
static bool idleActiveNow() {
    if (idleScreen == 0 || standby || demoMode || kbActive) return false;
    if (view != V_BMS1 && view != V_BMS2) return false;          // only over a dashboard view
    if (bmsLive[0] || bmsLive[1]) return false;                  // any pack answering → keep the real UI
    return (millis() - lastActivity) > IDLE_DELAY;               // settle after the last touch
}
static void idleText(int x, int y, const char *s, uint8_t sz, uint16_t c) {
    gfx->setTextSize(sz); gfx->setTextColor(c); gfx->setCursor(x, y); gfx->print(s);
}
// 1) Looping tactical HUD — scanlines, cycling status lines, link bar, reticle.
static void renderHudIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x09, 0x03, 0x02), AMBER = gfx->color565(0xff, 0xb0, 0x28);
    const uint16_t RED = gfx->color565(0xff, 0x38, 0x20), DIM = gfx->color565(0x4a, 0x16, 0x0e);
    gfx->fillScreen(BG);
    for (int y = (ms / 70) % 3; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);
    idleText(14, 12, "SECURITY INTERFACE MONITOR", 2, RED);
    gfx->drawFastHLine(14, 36, Wd - 28, RED); gfx->drawFastHLine(14, 38, Wd - 28, DIM);
    int rx = Wd - 26, ry = 18; float a = ms * 0.004f;            // sweeping reticle, tucked in the top-right corner
    gfx->drawCircle(rx, ry, 12, AMBER); gfx->drawCircle(rx, ry, 4, RED);
    gfx->drawLine(rx, ry, rx + (int)(12 * cosf(a)), ry + (int)(12 * sinf(a)), AMBER);
    static const char *L[] = {"SCANNING BATTERY BUS", "PROBING BMS NODES", "NO BATTERY DETECTED"};
    int shown = ((ms / 700) % 5) + 1; if (shown > 3) shown = 3;
    for (int i = 0; i < shown; i++) {
        int ly = 56 + i * 24; bool last = (i == shown - 1);
        idleText(16, ly, L[i], 2, AMBER);
        char dots[4] = "   "; int nd = (ms / 300) % 4; for (int d = 0; d < nd && d < 3; d++) dots[d] = '.';
        idleText(Wd - 16 - 72, ly, last ? dots : "[ -- ]", 2, last ? RED : AMBER);
    }
    // prominent waiting banner (pulsing)
    if (((ms / 450) & 1)) {
        char wd[24] = "WAITING FOR DATA"; int nd = (ms / 300) % 4; int l = strlen(wd);
        for (int d = 0; d < nd && d < 3; d++) wd[l + d] = '.';
        idleText(Wd / 2 - (strlen(wd) * 18) / 2, 160, wd, 3, RED);
    }
    int bx = 16, by = Ht - 24, bw = Wd - 32;                     // looping link bar
    gfx->drawRect(bx, by, bw, 14, RED);
    float p = (ms % 1800) / 1800.0f;
    gfx->fillRect(bx + 2, by + 2, (int)((bw - 4) * p), 10, AMBER);
    idleText(bx, by - 14, "BATTERY DATA LINK", 1, AMBER);
    if (((ms / 500) & 1)) idleText(Wd - 80, by - 14, "tap for menu", 1, DIM);
}
// 2) System-initialisation screen — grid, ring %, four loaders, hex stream.
static void renderInitIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x03, 0x05, 0x0c), CY = gfx->color565(0x3d, 0xf0, 0xa8);
    const uint16_t BL = gfx->color565(0x12, 0x2a, 0x40), TX = gfx->color565(0xcf, 0xe6, 0xff);
    const uint16_t OK = gfx->color565(0x46, 0xff, 0x6a), RD = gfx->color565(0xff, 0x3a, 0x2a);
    gfx->fillScreen(BG);
    for (int x = 0; x < Wd; x += 30) gfx->drawFastVLine(x, 0, Ht, BL);      // grid
    for (int y = 0; y < Ht; y += 30) gfx->drawFastHLine(0, y, Wd, BL);
    idleText(14, 8, "BATTERY LINK INITIALISATION", 2, CY);
    // 7 fake init steps complete, then the battery connect stalls and fails at 95%
    static const char *NM[8] = {"BOOT VECTOR", "KERNEL MODULES", "SECURE ENCLAVE", "AES-256 KEYRING",
                                "PACKET INSPECTOR", "TELEMETRY DECODER", "BUS ARBITRATION", "CONNECTING TO BATTERY"};
    const int N = 8;
    uint32_t CYCLE = 13000, t = ms % CYCLE, LOAD = 9000;
    bool failed = (t >= LOAD);
    float prog = failed ? 95.0f : 95.0f * t / LOAD;            // climbs 0→95, then halts
    for (int i = 0; i < N; i++) {
        float lo = (i < 7) ? i * 85.0f / 7.0f : 85.0f;         // first 7 share 0..85%, battery is 85..100%
        float hi = (i < 7) ? (i + 1) * 85.0f / 7.0f : 100.0f;
        if (prog < lo) break;                                  // reveal one row at a time
        float fill = (prog - lo) / (hi - lo); if (fill > 1) fill = 1; if (fill < 0) fill = 0;
        // centered block: label | bar | status
        int y = 34 + i * 20, lblX = 66, bx = 216, bw = 150, bh = 8;
        bool isBat = (i == 7);
        idleText(lblX, y, NM[i], 1, TX);
        gfx->drawRect(bx, y - 1, bw, bh, BL);
        gfx->fillRect(bx + 1, y, (int)((bw - 2) * fill), bh - 2, (isBat && failed) ? RD : CY);
        int stx = bx + bw + 10;
        if (isBat && failed) idleText(stx, y, "FAIL", 1, RD);
        else if (fill >= 1.0f) idleText(stx, y, "OK", 1, OK);
        else { char d[4] = "   "; int nd = (ms / 200) % 4; for (int k = 0; k < nd && k < 3; k++) d[k] = '.'; idleText(stx, y, d, 1, CY); }
    }
    char pc[6]; snprintf(pc, sizeof(pc), "%d%%", (int)(prog + 0.5f));   // big % centered below loaders
    idleText((Wd - (int)strlen(pc) * 18) / 2, 208, pc, 3, failed ? RD : TX);
    if (failed && ((ms / 400) & 1)) {                          // fail banner, centered below the %
        const char *f = "FAILED TO INITIALIZE";
        idleText((Wd - (int)strlen(f) * 12) / 2, 250, f, 2, RD);
    }
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, BL);
}
// 3) Sensor radar / scope standby — rotating sweep, blips, scrolling waveform.
static void renderRadarIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x02, 0x08, 0x05), GR = gfx->color565(0x12, 0x3a, 0x22);
    const uint16_t GRN = gfx->color565(0x3d, 0xf0, 0x90), TX = gfx->color565(0xbf, 0xe6, 0xcf);
    const uint16_t OK = gfx->color565(0x46, 0xff, 0x6a);
    gfx->fillScreen(BG);
    idleText(14, 12, "BATTERY SENSOR ARRAY", 2, GRN);
    // --- radar, confined to the left half so it never overlaps the log ---
    int cx = 98, cy = 192, R = 90; float a = ms * 0.003f;
    for (int r = R / 3; r <= R; r += R / 3) gfx->drawCircle(cx, cy, r, GR);  // rings
    gfx->drawLine(cx - R, cy, cx + R, cy, GR); gfx->drawLine(cx, cy - R, cx, cy + R, GR);
    for (int k = 0; k < R; k += 3) gfx->drawLine(cx, cy, cx + (int)(k * cosf(a)), cy + (int)(k * sinf(a)), GRN);  // sweep
    for (int i = 0; i < 4; i++) {                               // fading blips
        float ba = i * 1.9f, br = 26 + (i * 21) % (R - 18);
        float age = fmodf(a - ba, 6.2832f); if (age < 0) age += 6.2832f;
        if (age < 1.2f) gfx->fillCircle(cx + (int)(br * cosf(ba)), cy + (int)(br * sinf(ba)), 3, GRN);
    }
    // --- right column: mini scope + secure-link log ---
    int lx = 200, gx = lx, gw = Wd - lx - 10, gy = 40, gh = 44;
    gfx->drawRect(gx, gy, gw, gh, GR);
    int px = -1, py = -1;
    for (int i = 0; i < gw - 4; i++) {
        float v = sinf((i + ms * 0.08f) * 0.16f) * 0.5f + sinf((i + ms * 0.05f) * 0.4f) * 0.2f;
        int wx = gx + 2 + i, wy = gy + gh / 2 - (int)(v * (gh / 2 - 4));
        if (px >= 0) gfx->drawLine(px, py, wx, wy, GRN); px = wx; py = wy;
    }
    static const char *L[] = {"SERIAL LINK 115200", "AES-256 ENCRYPTION", "BMS HANDSHAKE 0x90EB",
                              "DECRYPTING TELEMETRY", "CRC16 VALIDATION", "CONNECTING TO BATTERY"};
    const int N = 6;
    const uint16_t RD = gfx->color565(0xff, 0x3a, 0x2a);
    uint32_t CYCLE = 9000, t = ms % CYCLE, LOAD = 6000;          // load ~6s, then fail held ~3s, loop
    bool failed = (t >= LOAD);
    int shown = failed ? N : (int)(t / (LOAD / N)) + 1; if (shown > N) shown = N;
    int rxs = Wd - 10;
    for (int i = 0; i < shown; i++) {
        int ly = 96 + i * 20; bool isLast = (i == N - 1);
        idleText(lx, ly, L[i], 1, TX);
        char dots[4] = "   "; int nd = (ms / 200) % 4; for (int d = 0; d < nd && d < 3; d++) dots[d] = '.';
        if (isLast && failed) idleText(rxs - 24, ly, "FAIL", 1, RD);
        else if (i < shown - 1) idleText(rxs - 12, ly, "OK", 1, OK);  // done → green
        else idleText(rxs - 18, ly, dots, 1, GRN);                    // in progress
    }
    if (failed && ((ms / 400) & 1)) {                           // red FAILED below the list (~3s window)
        const char *f = "FAILED";
        idleText(lx + ((Wd - lx) - (int)strlen(f) * 12) / 2, 96 + N * 20 + 10, f, 2, RD);
    }
    idleText(14, Ht - 14, "no battery signal", 1, GR);
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, GR);
}
// 4) Retro arcade GAME OVER — dead-battery sprite, blinking INSERT COIN, jokes.
static void renderArcadeIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0, 0, 0), RED = gfx->color565(0xff, 0x30, 0x28);
    const uint16_t WHT = gfx->color565(0xf0, 0xf0, 0xf0), YEL = gfx->color565(0xff, 0xd0, 0x30);
    const uint16_t GRY = gfx->color565(0x66, 0x6c, 0x78), DIM = gfx->color565(0x1c, 0x1c, 0x1c);
    gfx->fillScreen(BG);
    for (int y = 0; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);     // scanlines
    idleText(10, 8, "1UP", 1, RED); idleText(40, 8, "00000000", 1, WHT);
    idleText(Wd - 96, 8, "HI 00009999", 1, WHT);
    const char *go = "GAME OVER"; int sh = (ms / 120) % 2;                 // tiny shake
    uint16_t goCol = wheel((ms % 60000) / 60000.0f);                       // slow full-hue cycle (~60s)
    idleText((Wd - (int)strlen(go) * 30) / 2, 64 + sh, go, 5, goCol);
    // dead battery sprite (X eyes + flat mouth)
    int cx = Wd / 2, bw = 80, bh = 42, bx = cx - bw / 2, by = 132;
    gfx->drawRect(bx, by, bw, bh, GRY); gfx->drawRect(bx + 1, by + 1, bw - 2, bh - 2, GRY);
    gfx->fillRect(bx + bw, by + bh / 2 - 7, 6, 14, GRY);
    int e1 = bx + 24, e2 = bx + bw - 24, ey = by + 16;
    for (int o = 0; o < 2; o++) {
        gfx->drawLine(e1 - 6, ey - 6 + o, e1 + 6, ey + 6 + o, WHT); gfx->drawLine(e1 - 6, ey + 6 + o, e1 + 6, ey - 6 + o, WHT);
        gfx->drawLine(e2 - 6, ey - 6 + o, e2 + 6, ey + 6 + o, WHT); gfx->drawLine(e2 - 6, ey + 6 + o, e2 + 6, ey - 6 + o, WHT);
    }
    gfx->drawLine(cx - 9, by + bh - 9, cx + 9, by + bh - 9, WHT);          // flat mouth
    if (((ms / 450) & 1)) { const char *ic = "INSERT COIN TO CONTINUE"; idleText((Wd - (int)strlen(ic) * 12) / 2, 210, ic, 2, YEL); }
    static const char *J[] = {"NO BATTERY DETECTED", "PLAYER 1 (BMS) HAS LEFT", "HAVE YOU TRIED PLUGGING IT IN?",
                              "DATA: NONE   VIBES: OK", "GIT GUD - CONNECT A BATTERY"};
    const char *j = J[(ms / 2200) % 5];
    idleText((Wd - (int)strlen(j) * 6) / 2, 244, j, 1, GRY);
    idleText(10, Ht - 14, "CREDIT 00", 1, YEL);
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, DIM);
}
// 5) Maximum-security control room — dial gauges, bar meters, threat graph, status.
static void renderSecurityIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x02, 0x06, 0x0c), GRID = gfx->color565(0x0b, 0x18, 0x26);
    const uint16_t CY = gfx->color565(0x32, 0xd8, 0xff), GN = gfx->color565(0x3d, 0xf0, 0x8a);
    const uint16_t AM = gfx->color565(0xff, 0xc0, 0x30), RD = gfx->color565(0xff, 0x44, 0x3a);
    const uint16_t TX = gfx->color565(0xbf, 0xd8, 0xe6), DIM = gfx->color565(0x16, 0x2a, 0x3a);
    gfx->fillScreen(BG);
    for (int x = 0; x < Wd; x += 24) gfx->drawFastVLine(x, 0, Ht, GRID);
    for (int y = 0; y < Ht; y += 24) gfx->drawFastHLine(0, y, Wd, GRID);
    idleText(14, 6, "MAXIMUM SECURITY MONITOR", 2, CY);
    idleText(Wd - 92, 8, "ARMED", 1, RD);
    if (((ms / 500) & 1)) gfx->fillCircle(Wd - 16, 13, 5, RD);
    // --- three dial gauges ---
    const char *GL[3] = {"CPU", "ENCRYPT", "UPLINK"}; uint16_t GC[3] = {CY, GN, AM}; float GP[3] = {0, 1.3f, 2.6f};
    for (int i = 0; i < 3; i++) {
        int cx = 80 + i * 160, cy = 92, r = 38;
        float v = 0.5f + 0.45f * sinf(ms * 0.001f + GP[i]);
        int fillTo = 180 + (int)(v * 180);
        for (int d = 180; d <= 360; d += 6) { float a = d * 0.01745f; gfx->fillCircle(cx + (int)(r * cosf(a)), cy + (int)(r * sinf(a)), 2, (d <= fillTo) ? GC[i] : DIM); }
        float na = (180 + v * 180) * 0.01745f;
        gfx->drawLine(cx, cy, cx + (int)((r - 6) * cosf(na)), cy + (int)((r - 6) * sinf(na)), GC[i]);
        gfx->fillCircle(cx, cy, 3, GC[i]);
        char val[6]; snprintf(val, sizeof(val), "%d%%", (int)(v * 100));
        idleText(cx - (int)strlen(val) * 3, cy + 8, val, 1, GC[i]);
        idleText(cx - (int)strlen(GL[i]) * 3, cy + 20, GL[i], 1, TX);
    }
    // --- threat-analysis scrolling graph ---
    int gx = 14, gy = 138, gw = 212, gh = 88;
    gfx->drawRect(gx, gy, gw, gh, DIM); idleText(gx + 6, gy + 4, "THREAT ANALYSIS", 1, TX);
    int px = -1, py = -1;
    for (int i = 0; i < gw - 4; i++) {
        float v = sinf((i + ms * 0.09f) * 0.13f) * 0.4f + sinf((i + ms * 0.05f) * 0.5f) * 0.18f;
        int sx = gx + 2 + i, sy = gy + gh / 2 + 6 - (int)(v * (gh / 2 - 10));
        if (px >= 0) gfx->drawLine(px, py, sx, sy, GN); px = sx; py = sy;
    }
    // --- vertical bar meters ---
    for (int i = 0; i < 6; i++) {
        int bx = 240 + i * 38, base = 226, h = 18 + (int)(58 * (0.5f + 0.5f * sinf(ms * 0.0022f + i * 0.9f)));
        uint16_t c = h > 64 ? RD : h > 42 ? AM : GN;
        gfx->drawRect(bx, base - 78, 22, 78, DIM);
        gfx->fillRect(bx + 2, base - h, 18, h, c);
    }
    idleText(240, 138, "SECTOR INTEGRITY", 1, TX);
    // --- status strip ---
    idleText(14, 240, "FIREWALL: ACTIVE", 1, GN);
    idleText(168, 240, "INTRUSION: NONE", 1, GN);
    idleText(320, 240, "CIPHER: AES-256", 1, CY);
    if (((ms / 400) & 1)) idleText(14, 258, "LOCKDOWN ENGAGED", 1, RD);
    idleText(180, 258, "BIOMETRIC LOCK OK", 1, GN);
    idleText(14, Ht - 14, "MAXIMUM SECURITY // ALL SYSTEMS NOMINAL", 1, DIM);
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, DIM);
}
static void renderIdleFrame() {
    uint32_t ms = millis();
    if (idleScreen == 1) renderHudIdle(ms);
    else if (idleScreen == 2) renderInitIdle(ms);
    else if (idleScreen == 3) renderRadarIdle(ms);
    else if (idleScreen == 4) renderArcadeIdle(ms);
    else renderSecurityIdle(ms);
}

// ============================================================================
//  LVGL glue
// ============================================================================
static uint32_t millis_cb(void) { return millis(); }
static void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    gfx->blit(area->x1, area->y1, lv_area_get_width(area), lv_area_get_height(area), (uint16_t *)px_map);
    gfxDirty = true;
    lv_disp_flush_ready(disp);
}
static void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    uint16_t x, y;
    if (touch.touched()) { touch.readData(&x, &y); data->point.x = x; data->point.y = y; data->state = LV_INDEV_STATE_PRESSED; }
    else data->state = LV_INDEV_STATE_RELEASED;
}

static lv_obj_t *scr;
static void invArea(int x1, int y1, int x2, int y2);
static void draw_cb(lv_event_t *e) {
    L = lv_event_get_layer(e);
    tpi = 0;
    if (view == V_SETTINGS) renderSettings();
    else renderBms();
}
static bool pressHandled = false, gMoved = false, gAnchored = false;
static int gStartY = 0, gBaseScroll = 0, gLastY = 0;
static uint32_t gLastT = 0;
static float gVel = 0;              // finger velocity px/ms during a drag
// kinetic (momentum) scroll
static float flingVel = 0;          // scroll velocity px/ms
static int *flingVar = nullptr, flingMax = 0, flingTop = 0, flingBot = 0;
// scroll context for the current tab (nullptr = nothing scrolls here)
static int *scrollCtx(int *maxS, int *top, int *bot) {
    if (view == V_SETTINGS && subTab == ST_SYSTEM) { *maxS = sysMaxScroll(); *top = LIST_TOP; *bot = Ht; return &sysScroll; }
    if (view == V_SETTINGS && subTab == ST_BMS && editIdx < 0) { *maxS = bmsMaxScroll(); *top = LIST_TOP; *bot = Ht; return &bmsScroll; }
    if (view == V_SETTINGS && subTab == ST_WIFI) { *maxS = wMaxScroll(); *top = wListTop(); *bot = wRescanY() - 4; return &wifiScroll; }
    return nullptr;
}
// Keyboard keys act on PRESS (immediate). The System list drag-scrolls on PRESSING.
// Everything else acts on RELEASE — and only if the finger didn't drag — so
// scrolling never accidentally toggles a setting.
static void unsave() {   // instantly undo dim / eco on interaction
    if (appliedB != brightness) { setBrightness(brightness); appliedB = brightness; }
    if (ecoActive) { ecoActive = false; if (dataTimer) lv_timer_set_period(dataTimer, 220); if (barTimer) lv_timer_set_period(barTimer, 130); }
}
static void press_cb(lv_event_t *e) {
    lastActivity = millis();
    if (standby) return;
    unsave();
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    gMoved = false; gAnchored = false; gVel = 0; flingVel = 0;   // grab cancels any momentum
    // keyboards handle on press (not release): a tap with touch jitter would set
    // gMoved and get dropped as a "scroll" — but a keypad has nothing to scroll.
    if (view == V_SETTINGS && (kbActive || editIdx >= 0)) { handleTap(p.x, p.y); pressHandled = true; lv_obj_invalidate(scr); }
}
static void pressing_cb(lv_event_t *e) {
    if (standby || pressHandled || kbActive) return;
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    int maxS = 0, top = 0, bot = 0; int *scrollVar = scrollCtx(&maxS, &top, &bot);
    if (!gAnchored) {                    // first stable sample → anchor (PRESSED coord can be stale)
        gStartY = p.y; gBaseScroll = scrollVar ? *scrollVar : 0; gAnchored = true;
        gLastY = p.y; gLastT = millis(); gVel = 0; return;
    }
    int dy = p.y - gStartY;
    if (abs(dy) > 6) gMoved = true;      // ANY drag suppresses the tap on release (also on non-scrolling tabs)
    uint32_t tn = millis();              // track finger velocity for momentum
    if (tn > gLastT) gVel = 0.6f * gVel + 0.4f * ((float)(p.y - gLastY) / (tn - gLastT));
    gLastY = p.y; gLastT = tn;
    if (gMoved && scrollVar) {           // scroll only where there's a list
        int ns = gBaseScroll - dy;
        if (ns < 0) ns = 0; if (ns > maxS) ns = maxS;
        if (ns != *scrollVar) { *scrollVar = ns; lastActivity = millis(); invArea(0, top, Wd - 1, bot); }
    }
}
static void release_cb(lv_event_t *e) {
    lastActivity = millis();
    if (standby) { standby = false; appliedB = brightness; setBrightness(brightness); unsave(); lv_obj_invalidate(scr); return; }  // wake
    if (pressHandled) { pressHandled = false; return; }   // keyboard handled on press
    if (gMoved) {                                         // was a scroll → fling, don't toggle
        gMoved = false;
        int maxS = 0, top = 0, bot = 0; int *sv = scrollCtx(&maxS, &top, &bot);
        if (sv && millis() - gLastT < 80 && fabsf(gVel) > 0.05f) {   // released while moving → momentum
            flingVel = -gVel; if (flingVel > 2.5f) flingVel = 2.5f; if (flingVel < -2.5f) flingVel = -2.5f;
            flingVar = sv; flingMax = maxS; flingTop = top; flingBot = bot;
        }
        return;
    }
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    handleTap(p.x, p.y);
    if (dirtyFull) lv_obj_invalidate(scr);
    else lv_obj_invalidate_area(scr, &dirtyRect);
}
// momentum scroll: decays the released velocity until it stops or hits an edge
static void fling_cb(lv_timer_t *t) {
    if (!flingVar || fabsf(flingVel) < 0.04f) { flingVel = 0; return; }
    int ns = *flingVar + (int)(flingVel * 30.0f);        // 30ms step
    if (ns < 0) { ns = 0; flingVel = 0; }
    if (ns > flingMax) { ns = flingMax; flingVel = 0; }
    if (ns != *flingVar) { *flingVar = ns; invArea(0, flingTop, Wd - 1, flingBot); }
    flingVel *= 0.86f;                                    // friction
}
// The Arduino_Canvas is a persistent full framebuffer: regions we don't
// invalidate keep their previous pixels. So we redraw selectively —
//   • tab strip at high rate  → smooth auto-switch bar
//   • live values slower       → tiles/ring/cells/power graph
//   • capacity graph (static)  → only on a BMS switch
// A full AA repaint of the whole screen is ~220ms; this keeps each repaint small.
static void invArea(int x1, int y1, int x2, int y2) {
    lv_area_t a = {x1, y1, x2, y2}; lv_obj_invalidate_area(scr, &a);
}
// Poll the live BMSes; when a pack's online/offline state flips, repaint the tab
// row (red ↔ accent) and the body (stale ↔ live) so the UI tracks reconnects.
static void bmsPoll_cb(lv_timer_t *t) {
    bool was0 = bmsLive[0], was1 = bmsLive[1];
    int hc = histCount[view];
    bmsRead();
    histSample();                              // append a real point when one is due
    if (standby || view == V_SETTINGS) return;
    if (bmsLive[0] != was0 || bmsLive[1] != was1) {
        invArea(6, 4, TAB2_X + TAB_W, 36);     // tab colours
        invArea(0, 36, Wd - 1, Ht - 1);        // body: stale ↔ live values
    }
    if (histCount[view] != hc) {               // a new sample landed → refresh the graphs
        renderGraphs();
        invArea(196, 118, Wd - 1, 313);        // power + capacity graph slots
    }
}
static void barTick_cb(lv_timer_t *t) {
    if (standby || view == V_SETTINGS || idleActiveNow()) return;
    if (!autoSwitch || millis() < manualUntil) return;   // paused/off → bar not moving, skip flush
    invArea(6, 4, TAB2_X + TAB_W, 36);
}
static void dataTick_cb(lv_timer_t *t) {
    uint32_t now = millis();
    simStep(now);
    if (pwrSample() && !standby && view != V_SETTINGS && !idleActiveNow()) {   // new power point → refresh graphs
        renderGraphs(); invArea(196, 118, Wd - 1, 313);
    }
    if (cfgDirty && now - cfgDirtyAt > 1500) { cfgDirty = false; saveSettings(); }   // persist settings
    if (histDirty && now - histDirtyAt > 2000) { histDirty = false; saveHistory(); } // persist graph history
    // ---- power saving (escalates with idle time; any touch resets it) ----
    uint32_t idle = now - lastActivity;
    if (!standby) {                                                 // (sleep keeps the backlight off)
        int tB = (dimAfterSec && idle > (uint32_t)dimAfterSec * 1000UL) ? DIM_LEVEL : brightness;
        if (tB != appliedB) { setBrightness(tB); appliedB = tB; }   // auto-dim
    }
    // eco throttles the UI to 1fps when idle — but NOT while auto-switch is rotating,
    // or the cycling display lags (each switch/value only repaints once a second).
    bool eco = ecoMode && !standby && !autoSwitch && idle > ECO_IDLE_MS;
    if (eco != ecoActive) {                                          // low-fps when idle
        ecoActive = eco;
        if (dataTimer) lv_timer_set_period(dataTimer, eco ? 1000 : 220);
        if (barTimer) lv_timer_set_period(barTimer, eco ? 1000 : 130);
    }
    if (autoSleepMin > 0 && !standby && idle > (uint32_t)autoSleepMin * 60000UL) { pendingSleep = true; return; }
    if (standby || view == V_SETTINGS || idleActiveNow()) return;   // idle screen owns the canvas
    if (autoSwitch && now >= manualUntil && now - lastSwitch >= intervalMs) {
        int other = view ^ 1;
        // only flip to the other pack if it's available (demo mode shows both;
        // in live mode skip a BMS that isn't answering — if both are down, stay put)
        bool otherOk = demoMode || bmsLive[other];
        lastSwitch = now;
        if (otherOk) {
            switchView(other);
            invArea(0, 36, Wd - 1, Ht - 1);        // full body: new BMS + new graphs
        }
        return;
    }
    // Spread the heavy AA repaint over several ticks — one section per tick keeps
    // each frame small so the auto-switch bar stays smooth between updates.
    static int sec = 0;
    switch (sec) {
        case 0: invArea(0, 40, 195, 305); break;   // left: SOC ring + power readout
        case 1: invArea(196, 36, 479, 112); break; // tiles row (V / stats / temps)
        case 2: invArea(196, 114, 338, 207); break;// cells card
    }
    sec = (sec + 1) % 3;
}
static void wifiTick_cb(lv_timer_t *t) {
    if (wifiPoll() && view == V_SETTINGS && !standby) lv_obj_invalidate(scr);
}

#include "web_portal.h"   // monitor + controls + OTA (uses the globals/helpers above)

void setup() {
    Serial.begin(115200);
    Serial.setTxTimeoutMs(0);   // never block the loop when no USB host is reading
    delay(300);
    Serial.printf("\n[lvgl] boot — LVGL %d.%d.%d\n", lv_version_major(), lv_version_minor(), lv_version_patch());
    loadSettings();             // restore saved settings before they're used (brightness, wifi, …)
    loadHistory();              // restore the persisted graph history (survives reboot)

    // 40 MHz QSPI — 80 MHz caused pixel-offset artifacts on this AXS15231B panel.
    if (!gfx->begin(40000000UL)) Serial.println("[lvgl] display init FAILED");
    gfx->fillScreen(0x0000);
    ledcAttach(TFT_BL, BL_CH_FREQ, BL_CH_RES);
    // playBootAnimation();     // (ninja intro disabled for now)
    playVisionOn();             // robot-vision power-on: dot → line → flash
    playHudBoot();              // tactical-HUD boot log → READY.....

    touch.begin(); touch.setRotation(TFT_rot);
    touch.enOffsetCorrection(true);
    touch.setOffsets(Touch_X_min, Touch_X_max, TFT_res_W - 1, Touch_Y_min, Touch_Y_max, TFT_res_H - 1);

    lv_init();
    lv_tick_set_cb(millis_cb);
    // Larger draw buffer => fewer render chunks => draw_cb runs far fewer times
    // per full repaint (was /10 = 10 chunks; /4 = ~4) => snappier taps/switches.
    uint32_t w = gfx->width(), h = gfx->height(), bufSize = w * h / 4;
    lv_color_t *buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!buf) { Serial.println("[lvgl] FATAL: draw buffer alloc failed"); while (1) delay(1000); }
    lv_display_t *disp = lv_display_create(w, h);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, buf, NULL, bufSize * 2, LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touchpad_read);

    scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(C_BG), 0);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(scr, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(scr, draw_cb, LV_EVENT_DRAW_MAIN_END, NULL);
    lv_obj_add_event_cb(scr, press_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(scr, pressing_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(scr, release_cb, LV_EVENT_RELEASED, NULL);

    // offscreen canvases for the cached graphs
    powCv = lv_canvas_create(NULL);
    capCv = lv_canvas_create(NULL);
    void *pb = heap_caps_malloc(LV_CANVAS_BUF_SIZE(POW_W, POW_H, 16, LV_DRAW_BUF_STRIDE_ALIGN), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    void *cb = heap_caps_malloc(LV_CANVAS_BUF_SIZE(CAP_W, CAP_H, 16, LV_DRAW_BUF_STRIDE_ALIGN), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!pb || !cb) { Serial.println("[lvgl] FATAL: graph canvas alloc failed"); while (1) delay(1000); }
    lv_canvas_set_buffer(powCv, pb, POW_W, POW_H, LV_COLOR_FORMAT_RGB565);
    lv_canvas_set_buffer(capCv, cb, CAP_W, CAP_H, LV_COLOR_FORMAT_RGB565);

    // auto-reconnect to the last saved WiFi
    WiFi.mode(WIFI_STA); WiFi.setAutoReconnect(wifiAuto); WiFi.setSleep(true);   // modem power-save
    prefs.begin("wifi", true);
    String ss = prefs.getString("ssid", ""), pw = prefs.getString("pass", "");
    prefs.end();
    if (ss.length()) {
        strncpy(connSsid, ss.c_str(), 32); connSsid[32] = 0;
        strncpy(connPass, pw.c_str(), 32); connPass[32] = 0;
        wifiSaved = true; WiFi.begin(connSsid, connPass);
        snprintf(wifiMsg, sizeof(wifiMsg), "connecting to %s...", connSsid);
    }

    simInit();
    // Live BMSes over Modbus-RTU, each on its own UART at address 1:
    //   BMS1 = UART1 (RX=IO18, TX=IO17), BMS2 = UART2 (RX=IO15, TX=IO16).
    // bmsRead() flips bmsLive[] per a valid reply; a silent pack shows a red tab +
    // "Offline". Skipped entirely in demo mode.
    bmsBegin();                 // open both BMS UARTs with the saved pin assignment
    bmsRead();
    histSample();               // continue the persisted history with a fresh point
    pwrSample();                // seed the 10-min power window
    renderGraphs();
    lastActivity = millis();
    lv_obj_invalidate(scr);                     // first full paint
    // Refresh rates kept modest so the panel isn't flushed at max rate (each full
    // flush ~40ms blocks touch polling). Between ticks lv_task_handler runs every
    // ~1ms and polls touch → responsive input.
    barTimer = lv_timer_create(barTick_cb, 130, NULL);    // auto-switch progress bar
    dataTimer = lv_timer_create(dataTick_cb, 220, NULL);  // live values (+ power-save supervisor)
    lv_timer_create(fling_cb, 30, NULL);                  // momentum scroll
    lv_timer_create(wifiTick_cb, 500, NULL);
    lv_timer_create(bmsPoll_cb, 1000, NULL);              // poll live BMSes (+ repaint on reconnect)
    Serial.println("[lvgl] dashboard ready");
}

void loop() {
    if (otaActive) { ArduinoOTA.handle(); return; }   // OTA in progress → give it the whole CPU
    lv_task_handler();
    webLoop();   // serve the web portal + handle OTA (no-op until WiFi connects)
    if (pendingSleep) {
        pendingSleep = false;
        playSleepAnimation();   // blocking, draws + flushes itself; sets standby
        gfxDirty = false;
        return;
    }
    // animated "no battery" idle screen (chosen in Settings) — owns the canvas directly
    static bool wasIdle = false;
    bool idle = idleActiveNow();
    if (!idle && wasIdle) lv_obj_invalidate(scr);   // leaving idle → repaint the real UI
    wasIdle = idle;
    if (idle) {
        static uint32_t lastFrame = 0; uint32_t now = millis();
        uint32_t period = (appliedB <= DIM_LEVEL) ? 250 : 80;   // ~4 fps once dimmed (motion invisible), else ~12 fps
        if (now - lastFrame >= period) { lastFrame = now; renderIdleFrame(); gfx->flush(); gfxDirty = false; }
        delay(1); return;
    }
    if (gfxDirty) { gfx->flush(); gfxDirty = false; }
    delay(1);
}
