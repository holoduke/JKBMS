// JK BMS → Guition JC3248W535 (480x320 landscape) — DEMO DASHBOARD + SETTINGS.
// Tabs [BMS 1][BMS 2][gear]. Auto-switch cycles only between BMS 1<->2; a tap
// pauses it for 30s then it resumes; Settings is never auto-cycled. Touch via the
// AXS15231B (I2C). Data is simulated until the real BMS UART parser lands.
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <WiFi.h>
#include <Preferences.h>
#include <math.h>
#include "AXS15231B_touch.h"

#define TFT_BL 1
#define TFT_CS 45
#define TFT_SCK 47
#define TFT_SDA0 21
#define TFT_SDA1 48
#define TFT_SDA2 40
#define TFT_SDA3 39
#define TFT_ROT 1
#define TFT_W 320
#define TFT_H 480
#define NCELLS 4
#define NCAP 168
#define FW_VERSION "0.3.0"

#define TOUCH_SDA 4
#define TOUCH_SCL 8
#define TOUCH_INT 3
#define TOUCH_ADDR 0x3B

#define BL_CH_FREQ 5000
#define BL_CH_RES 8

// top-bar tab geometry (BMS tabs left; bed + gear on the right)
#define TAB_W 104
#define TAB1_X 8
#define TAB2_X 120

static constexpr int BMS_TX_PIN = 17;
static constexpr int BMS_RX_PIN = 18;
HardwareSerial BmsSerial(1);

Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *panel = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_W, TFT_H);
Arduino_Canvas *gfx = new Arduino_Canvas(TFT_W, TFT_H, panel, 0, 0);
AXS15231B_Touch touch(TOUCH_SCL, TOUCH_SDA, TOUCH_INT, TOUCH_ADDR, TFT_ROT);

static uint16_t C_BG, C_CARD, C_BORDER, C_TEXT, C_MUTED, C_ACCENT, C_CYAN, C_WARN, C_BAD, C_INDIGO;
static int16_t Wd, Ht;
static bool standby = false, pendingSleep = false;
static uint32_t standbySince = 0;

// ---- settings sub-navigation + features ----
enum SubTab { ST_BMS = 0, ST_WIFI = 1, ST_SYSTEM = 2 };
static int subTab = ST_SYSTEM;
static int autoSleepMin = 0;                 // 0 = never; else 2/5/30/120
static uint32_t lastActivity = 0;
static bool bmsCharge = true, bmsDischarge = true, bmsBalancer = false;
// wifi
#define MAXNET 10
#define WIFI_MAXVIS 5
static char netSsid[MAXNET][33];
static int  netRssi[MAXNET];
static bool netEnc[MAXNET];
static int  netCount = 0;
static int  wifiSel = -1;
static bool kbActive = false;
static char wifiPass[33] = "";
static int  wifiPassLen = 0;
static int  kbMode = 0;                      // 0 lower, 1 UPPER, 2 symbols
static int  wifiScroll = 0;                  // first visible network index
static char wifiMsg[48] = "tap Scan to find networks";
static bool wifiScanning = false;
static bool infoPopup = false;
static Preferences prefs;
static char connSsid[33] = "", connPass[33] = "";   // last/attempted credentials
static bool wifiSaved = false;                       // creds persisted for this connection

// ---- UI state ----
enum View { V_BMS1 = 0, V_BMS2 = 1, V_SETTINGS = 2 };
static int view = V_BMS1;
static bool autoSwitch = true;
static uint32_t intervalMs = 5000;
static int brightness = 90;          // percent
static uint32_t lastSwitch = 0;
static uint32_t manualUntil = 0;     // auto-switch paused until this time
static const uint32_t PAUSE_MS = 30000;
static bool DEBUG_TOUCH = false;     // set true to show a marker at each touch point
static int16_t dbgX = -1, dbgY = -1;
static uint32_t dbgUntil = 0;

struct Bms {
    float soc, v, i;
    float tMos, tp1, tp2;
    float cell[NCELLS];
    float cap[NCAP];        // SOC % history
    float pwr[NCAP];        // power (W) history, same time base
    int capCount;
    float capSpanDays;
};
static Bms bms[2];

// ---- helpers ----
static void centerText(const char* s, int16_t cx, int16_t cy, uint8_t size, uint16_t color) {
    int16_t x1, y1; uint16_t w, h;
    gfx->setTextSize(size); gfx->getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
    gfx->setTextColor(color); gfx->setCursor(cx - w / 2 - x1, cy - h / 2 - y1); gfx->print(s);
}
static void leftText(const char* s, int16_t x, int16_t y, uint8_t size, uint16_t color) {
    gfx->setTextSize(size); gfx->setTextColor(color); gfx->setCursor(x, y); gfx->print(s);
}
static uint16_t dim(uint8_t r, uint8_t g, uint8_t b, uint8_t br) {
    return gfx->color565((r * br) / 255, (g * br) / 255, (b * br) / 255);
}
static uint16_t socColor(float soc) { return soc >= 60 ? C_ACCENT : soc >= 30 ? C_WARN : C_BAD; }
static void timeLabel(char* out, size_t n, float daysAgo, float span);   // fwd decl
static uint16_t tempColor(float t)  { return t >= 55 ? C_BAD : t >= 45 ? C_WARN : C_ACCENT; }
static void setBrightness(int pct)  { ledcWrite(TFT_BL, map(constrain(pct, 5, 100), 0, 100, 0, 255)); }

// Debug: marker at the last touch point so we can see where/how often touch fires.
static void drawTouchBlob() {
    if (!DEBUG_TOUCH || dbgX < 0 || millis() > dbgUntil) return;
    uint16_t mag = gfx->color565(255, 0, 200), wht = gfx->color565(255, 255, 255);
    gfx->fillCircle(dbgX, dbgY, 9, mag);
    gfx->drawCircle(dbgX, dbgY, 15, wht);
    gfx->drawFastHLine(dbgX - 22, dbgY, 44, wht);
    gfx->drawFastVLine(dbgX, dbgY - 22, 44, wht);
    char b[16]; snprintf(b, sizeof(b), "%d,%d", dbgX, dbgY);
    int16_t lx = (dbgX > Wd - 70) ? dbgX - 74 : dbgX + 18;
    leftText(b, lx, dbgY - 4, 2, wht);
}

// gear icon
static void drawGear(int16_t cx, int16_t cy, int16_t r, uint16_t col, uint16_t hole) {
    for (int k = 0; k < 8; k++) {
        float a = k * (PI / 4);
        gfx->fillCircle(cx + (int16_t)((r + 2) * cosf(a)), cy + (int16_t)((r + 2) * sinf(a)), 2, col);
    }
    gfx->fillCircle(cx, cy, r, col);
    gfx->fillCircle(cx, cy, r * 0.42f, hole);
}

// simple bed icon (side view) for the sleep button
static void drawBed(int16_t cx, int16_t cy, uint16_t col) {
    int16_t x = cx - 13, y = cy + 5;
    gfx->fillRect(x + 1, y, 2, 4, col);              // left leg
    gfx->fillRect(x + 22, y, 2, 4, col);             // right leg
    gfx->fillRoundRect(x, y - 6, 26, 6, 2, col);     // mattress
    gfx->fillRect(x, y - 13, 3, 9, col);             // headboard
    gfx->fillRoundRect(x + 4, y - 9, 8, 4, 2, col);  // pillow
    leftText("z", x + 20, y - 15, 1, col);           // little sleep z
}

// WiFi symbol (dot + 3 upward arcs); cy = baseline/dot position.
static void drawWifi(int16_t cx, int16_t cy, uint16_t color) {
    gfx->fillCircle(cx, cy, 2, color);
    const float a0 = 50.0f * (PI / 180.0f), a1 = 130.0f * (PI / 180.0f), yScale = 0.55f;  // flatter
    int16_t radii[3] = {7, 12, 17};
    for (int k = 0; k < 3; k++) {
        int16_t r = radii[k], px = -1, py = -1;
        for (int s = 0; s <= 10; s++) {
            float a = a0 + (a1 - a0) * s / 10.0f;
            int16_t x = cx + (int16_t)(r * cosf(a)), y = cy - (int16_t)(r * sinf(a) * yScale);
            if (px >= 0) { gfx->drawLine(px, py, x, y, color); gfx->drawLine(px, py + 1, x, y + 1, color); }
            px = x; py = y;
        }
    }
}

// ---- tab bar (shared) ----
#define GEAR_X (Wd - 38)
#define GEAR_Y 6
#define GEAR_W 30
#define BED_W 40
#define BED_X (GEAR_X - 8 - BED_W)   // sits just left of the gear
static void drawTabs(bool autoActive, float prog) {
    const int16_t y = 6, h = 28;
    const int16_t tabX[2] = {TAB1_X, TAB2_X};
    for (int t = 0; t < 2; t++) {
        int16_t x = tabX[t]; bool on = (view == t);
        gfx->fillRoundRect(x, y, TAB_W, h, 8, on ? C_ACCENT : C_CARD);
        if (!on) gfx->drawRoundRect(x, y, TAB_W, h, 8, C_BORDER);
        char lbl[8]; snprintf(lbl, sizeof(lbl), "BMS %d", t + 1);
        centerText(lbl, x + TAB_W / 2, y + h / 2, 2, on ? C_BG : C_MUTED);
        if (on && autoActive) gfx->fillRect(x + 6, y + h - 3, (int16_t)((TAB_W - 12) * prog), 2, C_BG);
    }
    // WiFi indicator (only when connected) — next to the BMS tabs
    if (WiFi.status() == WL_CONNECTED) drawWifi(252, 30, C_ACCENT);

    // sleep button (bed icon) — just left of the gear
    gfx->fillRoundRect(BED_X, y, BED_W, h, 8, C_CARD);
    gfx->drawRoundRect(BED_X, y, BED_W, h, 8, C_BORDER);
    drawBed(BED_X + BED_W / 2, y + h / 2, C_INDIGO);
    // gear tab
    bool gon = (view == V_SETTINGS);
    gfx->fillRoundRect(GEAR_X, GEAR_Y, GEAR_W, h, 8, gon ? C_ACCENT : C_CARD);
    if (!gon) gfx->drawRoundRect(GEAR_X, GEAR_Y, GEAR_W, h, 8, C_BORDER);
    drawGear(GEAR_X + GEAR_W / 2, GEAR_Y + h / 2, 7, gon ? C_BG : C_MUTED, gon ? C_ACCENT : C_CARD);
}

// ---- BMS widgets ----
static void drawRing(int16_t cx, int16_t cy, int16_t ro, int16_t ri, float pct, uint16_t col) {
    gfx->fillArc(cx, cy, ro, ri, 0, 360, C_BORDER);
    if (pct > 0.5f) gfx->fillArc(cx, cy, ro, ri, 0, pct * 3.6f, col);
    char buf[8]; snprintf(buf, sizeof(buf), "%d", (int)(pct + 0.5f));
    centerText(buf, cx, cy - 6, 5, C_TEXT);
    centerText("%", cx, cy + 26, 2, C_MUTED);
}
static void drawTile(int16_t x, int16_t y, int16_t w, int16_t h, const char* label,
                     const char* val, const char* unit, uint16_t valCol, int arrow) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    leftText(label, x + 8, y + 8, 1, C_MUTED);
    leftText(val, x + 8, y + 26, 2, valCol);
    leftText(unit, x + 8, y + h - 14, 1, C_MUTED);
    if (arrow) {
        int16_t ax = x + w - 16, ay = y + 10;
        if (arrow > 0) gfx->fillTriangle(ax, ay + 8, ax + 10, ay + 8, ax + 5, ay, C_ACCENT);
        else           gfx->fillTriangle(ax, ay, ax + 10, ay, ax + 5, ay + 8, C_WARN);
    }
}
static void drawTempsTile(int16_t x, int16_t y, int16_t w, int16_t h, float mos, float t1, float t2) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    const char* lbl[3] = {"MOS", "T1", "T2"};
    float v[3] = {mos, t1, t2};
    for (int r = 0; r < 3; r++) {
        int16_t ry = y + 9 + r * 22;
        leftText(lbl[r], x + 8, ry + 4, 1, C_MUTED);
        char buf[6]; snprintf(buf, sizeof(buf), "%.0f", v[r]);
        leftText(buf, x + 34, ry, 2, tempColor(v[r]));
        int16_t bx, by; uint16_t bw, bh; gfx->setTextSize(2);
        gfx->getTextBounds(buf, 0, 0, &bx, &by, &bw, &bh);
        leftText("C", x + 36 + bw, ry + 5, 1, C_MUTED);
    }
}
// Compact CELLS panel: 4 horizontal bars stacked vertically (fits half width).
static void drawCells(int16_t x, int16_t y, int16_t w, int16_t h, const Bms& b) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    float lo = 9, hi = 0; int loI = 0, hiI = 0;
    for (int i = 0; i < NCELLS; i++) { if (b.cell[i] < lo) { lo = b.cell[i]; loI = i; } if (b.cell[i] > hi) { hi = b.cell[i]; hiI = i; } }
    char hdr[20]; snprintf(hdr, sizeof(hdr), "CELLS  %dmV", (int)((hi - lo) * 1000));
    leftText(hdr, x + 8, y + 7, 1, C_MUTED);
    const int16_t top = y + 20, rh = (h - 26) / NCELLS;
    for (int i = 0; i < NCELLS; i++) {
        int16_t ry = top + i * rh, midY = ry + (rh - 8) / 2;
        char cl[4]; snprintf(cl, sizeof(cl), "C%d", i + 1);
        leftText(cl, x + 8, midY, 1, C_MUTED);
        int16_t bx = x + 28, bw = w - 28 - 42, by = ry + 2, bh = rh - 4;
        gfx->fillRoundRect(bx, by, bw, bh, 2, C_BORDER);
        float frac = (b.cell[i] - 3.0f) / 0.6f; frac = frac < 0.05f ? 0.05f : frac > 1 ? 1 : frac;
        uint16_t c = (i == loI) ? C_CYAN : (i == hiI) ? C_WARN : C_ACCENT;
        gfx->fillRoundRect(bx, by, (int16_t)(bw * frac), bh, 2, c);
        char cv[8]; snprintf(cv, sizeof(cv), "%.2f", b.cell[i]);
        leftText(cv, x + w - 40, midY, 1, C_TEXT);
    }
}

// Power (W) over time — autoscaled signed series with a zero baseline.
static void drawPowerGraph(int16_t x, int16_t y, int16_t w, int16_t h, const Bms& b) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    leftText("POWER  W", x + 8, y + 7, 1, C_MUTED);
    const int16_t gx = x + 8, gy = y + 22, gw = w - 14, gh = h - 38, base = gy + gh;
    int cnt = (b.capCount < 2) ? 2 : (b.capCount > NCAP ? NCAP : b.capCount);
    float lo = 1e9f, hi = -1e9f;
    for (int i = 0; i < cnt; i++) { float v = b.pwr[i]; if (v < lo) lo = v; if (v > hi) hi = v; }
    if (lo > 0) lo = 0; if (hi < 0) hi = 0; if (hi - lo < 1) hi = lo + 1;
    uint16_t area = dim(0x22, 0xd3, 0xee, 45), grid = dim(0x2a, 0x33, 0x42, 170);
    int16_t zeroY = base - (int16_t)((0 - lo) / (hi - lo) * gh);
    for (int k = 0; k < 5; k++) gfx->drawFastVLine(gx + (int16_t)((float)k / 4 * gw), gy, gh, grid);
    gfx->drawFastHLine(gx, zeroY, gw, grid);
    int16_t px = -1, py = -1;
    for (int i = 0; i < cnt; i++) {
        int16_t sx = gx + (int16_t)((float)i / (cnt - 1) * gw);
        int16_t sy = base - (int16_t)((b.pwr[i] - lo) / (hi - lo) * gh);
        int16_t t = sy < zeroY ? sy : zeroY;
        gfx->drawFastVLine(sx, t, abs(sy - zeroY), area);
        if (px >= 0) gfx->drawLine(px, py, sx, sy, C_CYAN);
        px = sx; py = sy;
    }
    for (int k = 0; k < 5; k++) {
        int16_t fx = gx + (int16_t)((float)k / 4 * gw);
        char lbl[8]; timeLabel(lbl, sizeof(lbl), b.capSpanDays * (1.0f - k / 4.0f), b.capSpanDays);
        if (k == 0) leftText(lbl, fx, base + 8, 1, C_MUTED);
        else if (k == 4) { int16_t x1, y1; uint16_t tw, th; gfx->setTextSize(1); gfx->getTextBounds(lbl, 0, 0, &x1, &y1, &tw, &th); leftText(lbl, fx - tw, base + 8, 1, C_MUTED); }
        else centerText(lbl, fx, base + 11, 1, C_MUTED);
    }
}
static void timeLabel(char* out, size_t n, float daysAgo, float span) {
    if (daysAgo < 0.04f) { snprintf(out, n, "now"); return; }
    if (span >= 2.0f) snprintf(out, n, "%.0fd", daysAgo);
    else              snprintf(out, n, "%.0fh", daysAgo * 24.0f);
}
static void drawCapacityGraph(int16_t x, int16_t y, int16_t w, int16_t h, const Bms& b) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    char hdr[28];
    if (b.capSpanDays >= 2.0f) snprintf(hdr, sizeof(hdr), "CAPACITY   %.0f days", b.capSpanDays);
    else                       snprintf(hdr, sizeof(hdr), "CAPACITY   24 hours");
    leftText(hdr, x + 8, y + 8, 1, C_MUTED);
    const int16_t gx = x + 10, gy = y + 24, gw = w - 20, gh = h - 42, base = gy + gh;
    uint16_t area = dim(0x3d, 0xf0, 0xa8, 45), grid = dim(0x2a, 0x33, 0x42, 170);
    for (int p = 0; p <= 100; p += 50) gfx->drawFastHLine(gx, base - (int16_t)(p / 100.0f * gh), gw, grid);
    for (int k = 0; k < 5; k++) gfx->drawFastVLine(gx + (int16_t)((float)k / 4 * gw), gy, gh, grid);
    int cnt = (b.capCount < 2) ? 2 : (b.capCount > NCAP ? NCAP : b.capCount);
    int16_t px = -1, py = -1;
    for (int i = 0; i < cnt; i++) {
        int16_t sx = gx + (int16_t)((float)i / (cnt - 1) * gw);
        int16_t sy = base - (int16_t)(b.cap[i] / 100.0f * gh);
        gfx->drawFastVLine(sx, sy, base - sy, area);
        if (px >= 0) gfx->drawLine(px, py, sx, sy, C_ACCENT);
        px = sx; py = sy;
    }
    for (int k = 0; k < 5; k++) {
        int16_t fx = gx + (int16_t)((float)k / 4 * gw);
        char lbl[8]; timeLabel(lbl, sizeof(lbl), b.capSpanDays * (1.0f - k / 4.0f), b.capSpanDays);
        if (k == 0) leftText(lbl, fx, base + 8, 1, C_MUTED);
        else if (k == 4) { int16_t x1, y1; uint16_t tw, th; gfx->setTextSize(1); gfx->getTextBounds(lbl, 0, 0, &x1, &y1, &tw, &th); leftText(lbl, fx - tw, base + 8, 1, C_MUTED); }
        else centerText(lbl, fx, base + 11, 1, C_MUTED);
    }
}

static void renderBms(int active, float prog, bool autoActive) {
    const Bms& b = bms[active];
    gfx->fillScreen(C_BG);
    drawTabs(autoActive, prog);

    const int16_t cx = 100, cy = 178;
    centerText("STATE OF CHARGE", cx, 52, 1, C_MUTED);
    drawRing(cx, cy, 74, 58, b.soc, socColor(b.soc));
    char pw[12]; snprintf(pw, sizeof(pw), "%.0f W", b.v * b.i);
    centerText(pw, cx, cy + 96, 2, (b.i >= 0) ? C_ACCENT : C_WARN);
    centerText((b.i >= 0) ? "CHARGING" : "DISCHARGING", cx, cy + 120, 1, C_MUTED);

    const int16_t rx = 200, rw = Wd - rx - 8;
    char vbuf[8], ibuf[8];
    snprintf(vbuf, sizeof(vbuf), "%.1f", b.v);
    snprintf(ibuf, sizeof(ibuf), "%+.1f", b.i);
    const int16_t ty = 40, th = 70, gap = 8, tw = (rw - 2 * gap) / 3;
    drawTile(rx,                  ty, tw, th, "VOLTAGE", vbuf, "VOLT", C_TEXT, 0);
    drawTile(rx + tw + gap,       ty, tw, th, "CURRENT", ibuf, "AMP",  (b.i >= 0) ? C_ACCENT : C_WARN, b.i >= 0 ? 1 : -1);
    drawTempsTile(rx + 2 * (tw + gap), ty, tw, th, b.tMos, b.tp1, b.tp2);

    const int16_t halfW = (rw - 8) / 2;
    drawCells(rx, 120, halfW, 86, b);
    drawPowerGraph(rx + halfW + 8, 120, rw - halfW - 8, 86, b);
    drawCapacityGraph(rx, 216, rw, 96, b);
    drawTouchBlob();
    gfx->flush();
}

// ---- settings screen (close button + BMS/WiFi/System sub-tabs) ----
#define CLOSE_X (Wd - 40)
static const char* KB[3][4] = {
    {"1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm"},
    {"1234567890", "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"},
    {"1234567890", "@#$%&*-+()", "!?:;'/_=.", ",~[]{}<>"},
};
static int16_t srowY(int i) { return 86 + i * 46; }
static void srow(int i, const char* label, const char* val, uint16_t vc) {
    int16_t y = srowY(i), x = 8, w = Wd - 16, h = 40;
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    leftText(label, x + 14, y + h / 2 - 7, 2, C_TEXT);
    int16_t bx, by; uint16_t bw, bh; gfx->setTextSize(2); gfx->getTextBounds(val, 0, 0, &bx, &by, &bw, &bh);
    leftText(val, x + w - bw - 16, y + h / 2 - 7, 2, vc);
}
static void subTabGeom(int i, int16_t* x, int16_t* w) { int16_t gap = 6; *w = (Wd - 16 - 2 * gap) / 3; *x = 8 + i * (*w + gap); }
static void drawCloseBtn() {
    int16_t x = CLOSE_X, y = 8, w = 32, h = 26, cx = x + w / 2, cy = y + h / 2;
    gfx->fillRoundRect(x, y, w, h, 6, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 6, C_BORDER);
    for (int o = -1; o <= 1; o++) {
        gfx->drawLine(cx - 6, cy - 6 + o, cx + 6, cy + 6 + o, C_BAD);
        gfx->drawLine(cx - 6, cy + 6 + o, cx + 6, cy - 6 + o, C_BAD);
    }
}
static void drawSubTabs() {
    const char* nm[3] = {"BMS", "WiFi", "System"};
    for (int i = 0; i < 3; i++) {
        int16_t x, w; subTabGeom(i, &x, &w); bool on = (subTab == i);
        gfx->fillRoundRect(x, 44, w, 30, 8, on ? C_ACCENT : C_CARD);
        if (!on) gfx->drawRoundRect(x, 44, w, 30, 8, C_BORDER);
        centerText(nm[i], x + w / 2, 44 + 15, 2, on ? C_BG : C_MUTED);
    }
}
static void renderSysTab() {
    char ib[10], bb[8], sl[10];
    snprintf(ib, sizeof(ib), "%lus", (unsigned long)(intervalMs / 1000));
    snprintf(bb, sizeof(bb), "%d%%", brightness);
    if (autoSleepMin == 0) snprintf(sl, sizeof(sl), "Never"); else snprintf(sl, sizeof(sl), "%d min", autoSleepMin);
    srow(0, "Auto-switch",        autoSwitch ? "ON" : "OFF", autoSwitch ? C_ACCENT : C_MUTED);
    srow(1, "Switch interval",    ib, C_CYAN);
    srow(2, "Brightness   - / +", bb, C_TEXT);
    srow(3, "Auto-sleep",         sl, autoSleepMin ? C_CYAN : C_MUTED);
    srow(4, "System info",        "view", C_CYAN);
}
static void renderBmsTab() {
    srow(0, "Charge MOSFET",    bmsCharge ? "ON" : "OFF",    bmsCharge ? C_ACCENT : C_BAD);
    srow(1, "Discharge MOSFET", bmsDischarge ? "ON" : "OFF", bmsDischarge ? C_ACCENT : C_BAD);
    srow(2, "Balancer",         bmsBalancer ? "ON" : "OFF",  bmsBalancer ? C_ACCENT : C_MUTED);
    srow(3, "Cell count",       "4S", C_MUTED);
    srow(4, "Pack capacity",    "100 Ah", C_MUTED);
}
static int16_t netRowY(int i) { return 104 + i * 34; }
static int16_t rescanY() { return 104 + WIFI_MAXVIS * 34 + 2; }
static int wifiMaxScroll() { return netCount > WIFI_MAXVIS ? netCount - WIFI_MAXVIS : 0; }
static void renderWifiTab() {
    bool conn = (WiFi.status() == WL_CONNECTED);
    if (wifiScroll > wifiMaxScroll()) wifiScroll = wifiMaxScroll();
    char msg[56];
    if (netCount > WIFI_MAXVIS) snprintf(msg, sizeof(msg), "%s   (%d-%d/%d)", wifiMsg,
                                         wifiScroll + 1, wifiScroll + WIFI_MAXVIS < netCount ? wifiScroll + WIFI_MAXVIS : netCount, netCount);
    else snprintf(msg, sizeof(msg), "%s", wifiMsg);
    leftText(msg, 12, 84, 1, conn ? C_ACCENT : C_MUTED);

    int vis = netCount - wifiScroll; if (vis > WIFI_MAXVIS) vis = WIFI_MAXVIS;
    for (int i = 0; i < vis; i++) {
        int idx = wifiScroll + i;
        int16_t y = netRowY(i), x = 8, w = Wd - 16, h = 30;
        gfx->fillRoundRect(x, y, w, h, 6, C_CARD);
        gfx->drawRoundRect(x, y, w, h, 6, C_BORDER);
        leftText(netSsid[idx], x + 12, y + 9, 1, C_TEXT);
        int bars = netRssi[idx] > -55 ? 4 : netRssi[idx] > -65 ? 3 : netRssi[idx] > -75 ? 2 : 1;
        for (int b = 0; b < 4; b++)
            gfx->fillRect(x + w - 64 + b * 7, y + h - 6 - b * 4, 5, 4 + b * 4, b < bars ? C_ACCENT : C_BORDER);
        if (netEnc[idx]) leftText("L", x + w - 18, y + 9, 1, C_WARN);
    }
    if (wifiMaxScroll() > 0) {                              // scrollbar indicator
        int16_t tX = Wd - 6, tY = netRowY(0), tH = netRowY(WIFI_MAXVIS - 1) + 30 - netRowY(0);
        gfx->fillRoundRect(tX, tY, 4, tH, 2, C_BORDER);
        int16_t thH = (int16_t)(tH * (float)WIFI_MAXVIS / netCount); if (thH < 14) thH = 14;
        int16_t thY = tY + (int16_t)((tH - thH) * (float)wifiScroll / wifiMaxScroll());
        gfx->fillRoundRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
    int16_t ry = rescanY();
    if (wifiMaxScroll() > 0) {                              // scroll arrows + Rescan
        gfx->fillRoundRect(8, ry, 48, 28, 6, C_CARD);  gfx->drawRoundRect(8, ry, 48, 28, 6, C_BORDER);
        gfx->fillTriangle(32, ry + 8, 26, ry + 18, 38, ry + 18, wifiScroll > 0 ? C_CYAN : C_BORDER);
        gfx->fillRoundRect(60, ry, 48, 28, 6, C_CARD); gfx->drawRoundRect(60, ry, 48, 28, 6, C_BORDER);
        gfx->fillTriangle(84, ry + 20, 78, ry + 10, 90, ry + 10, wifiScroll < wifiMaxScroll() ? C_CYAN : C_BORDER);
        int16_t rx = 116, rw = Wd - 8 - rx;
        gfx->fillRoundRect(rx, ry, rw, 28, 6, C_CARD); gfx->drawRoundRect(rx, ry, rw, 28, 6, C_BORDER);
        centerText("Rescan", rx + rw / 2, ry + 14, 2, C_CYAN);
    } else {
        gfx->fillRoundRect(8, ry, Wd - 16, 28, 6, C_CARD);
        gfx->drawRoundRect(8, ry, Wd - 16, 28, 6, C_BORDER);
        centerText(netCount ? "Rescan" : "Scan", Wd / 2, ry + 14, 2, C_CYAN);
    }
}
// keyboard: draw (draw=true) or hit-test (draw=false -> returns key code)
static int kbProcess(bool draw, int16_t tx, int16_t ty) {
    const int KB_TOP = 96, KH = 34, GAP = 4, KW = 42, CTLH = 44;
    int hit = 0;
    for (int r = 0; r < 4; r++) {
        const char* s = KB[kbMode][r]; int L = strlen(s);
        int totalW = L * KW + (L - 1) * GAP; int16_t sx = (Wd - totalW) / 2, y = KB_TOP + r * (KH + GAP);
        for (int i = 0; i < L; i++) {
            int16_t x = sx + i * (KW + GAP);
            if (draw) {
                gfx->fillRoundRect(x, y, KW, KH, 5, C_CARD); gfx->drawRoundRect(x, y, KW, KH, 5, C_BORDER);
                char c[2] = {s[i], 0}; centerText(c, x + KW / 2, y + KH / 2, 2, C_TEXT);
            } else if (tx >= x && tx < x + KW && ty >= y && ty < y + KH) hit = s[i];
        }
    }
    int16_t y = KB_TOP + 4 * (KH + GAP);   // control row, larger + roomier
    struct { int16_t x, w; const char* lb; int code; } ctl[4] = {
        {8, 62, kbMode == 0 ? "ABC" : kbMode == 1 ? "#+=" : "abc", -2},
        {74, 176, "space", 32}, {254, 92, "del", -1}, {350, 122, "OK", -4} };
    for (int k = 0; k < 4; k++) {
        if (draw) {
            uint16_t bg = ctl[k].code == -4 ? C_ACCENT : C_CARD;
            gfx->fillRoundRect(ctl[k].x, y, ctl[k].w, CTLH, 6, bg); gfx->drawRoundRect(ctl[k].x, y, ctl[k].w, CTLH, 6, C_BORDER);
            centerText(ctl[k].lb, ctl[k].x + ctl[k].w / 2, y + CTLH / 2, 2, ctl[k].code == -4 ? C_BG : C_TEXT);
        } else if (tx >= ctl[k].x && tx < ctl[k].x + ctl[k].w && ty >= y && ty < y + CTLH) hit = ctl[k].code;
    }
    return hit;
}
static void renderKeyboard() {
    char hdr[48]; snprintf(hdr, sizeof(hdr), "Wi-Fi: %s", wifiSel >= 0 ? netSsid[wifiSel] : "");
    leftText(hdr, 12, 10, 1, C_MUTED);
    drawCloseBtn();
    gfx->fillRoundRect(12, 30, Wd - 24, 30, 6, C_CARD);
    gfx->drawRoundRect(12, 30, Wd - 24, 30, 6, C_BORDER);
    leftText(wifiPassLen ? wifiPass : "enter password", 22, 40, 2, wifiPassLen ? C_TEXT : C_MUTED);
    kbProcess(true, 0, 0);
}
static void wifiStartScan() {                 // async — results harvested in wifiPoll()
    if (wifiScanning) return;
    wifiScanning = true; wifiSel = -1; wifiScroll = 0;
    snprintf(wifiMsg, sizeof(wifiMsg), "scanning...");
    WiFi.mode(WIFI_STA);
    WiFi.scanNetworks(true);
}
static void wifiTryConnect() {
    if (wifiSel < 0) return;
    strncpy(connSsid, netSsid[wifiSel], 32); connSsid[32] = 0;
    strncpy(connPass, wifiPass, 32); connPass[32] = 0;
    wifiSaved = false;
    WiFi.begin(connSsid, connPass);
    snprintf(wifiMsg, sizeof(wifiMsg), "connecting to %s...", connSsid);
}
// Non-blocking: harvest scan results + reflect connection status. Returns true if state changed.
static bool wifiPoll() {
    bool changed = false;
    if (wifiScanning) {
        int r = WiFi.scanComplete();
        if (r >= 0) {
            int n = r > MAXNET ? MAXNET : r; netCount = n;
            for (int i = 0; i < n; i++) {
                strncpy(netSsid[i], WiFi.SSID(i).c_str(), 32); netSsid[i][32] = 0;
                netRssi[i] = WiFi.RSSI(i);
                netEnc[i] = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
            }
            WiFi.scanDelete();
            wifiScanning = false; changed = true;
            snprintf(wifiMsg, sizeof(wifiMsg), n ? "%d networks found" : "no networks found", n);
        } else if (r == WIFI_SCAN_FAILED) {
            wifiScanning = false; changed = true;
            snprintf(wifiMsg, sizeof(wifiMsg), "scan failed");
        }
        return changed;
    }
    // reflect connection status (only meaningful after a connect attempt)
    static wl_status_t last = WL_IDLE_STATUS;
    wl_status_t st = WiFi.status();
    if (st != last) {
        last = st; changed = true;
        if (st == WL_CONNECTED) {
            snprintf(wifiMsg, sizeof(wifiMsg), "Connected: %s", WiFi.SSID().c_str());
            if (!wifiSaved && connSsid[0]) {        // remember creds for next power-on
                prefs.begin("wifi", false);
                prefs.putString("ssid", connSsid); prefs.putString("pass", connPass);
                prefs.end(); wifiSaved = true;
            }
        }
        else if (st == WL_CONNECT_FAILED)     snprintf(wifiMsg, sizeof(wifiMsg), "connect failed (password?)");
        else if (st == WL_NO_SSID_AVAIL)      snprintf(wifiMsg, sizeof(wifiMsg), "network not found");
        else if (st == WL_CONNECTION_LOST)    snprintf(wifiMsg, sizeof(wifiMsg), "connection lost");
    }
    return changed;
}
static void kvLine(int16_t x, int16_t* y, const char* k, const char* v) {
    leftText(k, x, *y, 1, C_MUTED);
    leftText(v, x + 96, *y, 1, C_TEXT);
    *y += 21;
}
static void renderInfoPopup() {
    int16_t w = Wd - 56, h = Ht - 44, x = (Wd - w) / 2, y = (Ht - h) / 2;
    gfx->fillRoundRect(x, y, w, h, 10, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 10, C_ACCENT);
    leftText("SYSTEM INFO", x + 16, y + 12, 2, C_TEXT);
    leftText("v" FW_VERSION, x + w - 62, y + 15, 1, C_ACCENT);
    int16_t lx = x + 16, ly = y + 44; char b[40];
    kvLine(lx, &ly, "Board", "JC3248W535");
    snprintf(b, sizeof(b), "ESP32-S3 2-core %uMHz", (unsigned)getCpuFrequencyMhz()); kvLine(lx, &ly, "MCU", b);
    snprintf(b, sizeof(b), "%lu MB", (unsigned long)(ESP.getFlashChipSize() / 1048576UL)); kvLine(lx, &ly, "Flash", b);
    snprintf(b, sizeof(b), "%lu / %lu KB", (unsigned long)(ESP.getFreePsram() / 1024), (unsigned long)(ESP.getPsramSize() / 1024)); kvLine(lx, &ly, "PSRAM free", b);
    snprintf(b, sizeof(b), "%lu KB", (unsigned long)(ESP.getFreeHeap() / 1024)); kvLine(lx, &ly, "Heap free", b);
    kvLine(lx, &ly, "MAC", WiFi.macAddress().c_str());
    if (WiFi.status() == WL_CONNECTED) kvLine(lx, &ly, "IP", WiFi.localIP().toString().c_str());
    else                               kvLine(lx, &ly, "WiFi", "not connected");
    snprintf(b, sizeof(b), "%lu s", (unsigned long)(millis() / 1000)); kvLine(lx, &ly, "Uptime", b);
    leftText("BMS info: coming soon", lx, ly + 3, 1, C_MUTED);
    leftText("tap to close", x + w - 92, y + h - 18, 1, C_MUTED);
}
static void renderSettings() {
    gfx->fillScreen(C_BG);
    if (kbActive) { renderKeyboard(); gfx->flush(); return; }
    leftText("SETTINGS", 12, 12, 2, C_TEXT);
    drawCloseBtn();
    drawSubTabs();
    if (subTab == ST_BMS)       renderBmsTab();
    else if (subTab == ST_WIFI) renderWifiTab();
    else                        renderSysTab();
    if (infoPopup) renderInfoPopup();
    gfx->flush();
}

// ---- touch handling ----
static void handleTap(int16_t x, int16_t y) {
    // (lastActivity is reset on every touch in loop(), before this is called)

    // ---- SETTINGS has its own UI ----
    if (view == V_SETTINGS) {
        if (infoPopup) { infoPopup = false; return; }     // tap (release) closes the popup
        if (kbActive) {                                   // on-screen keyboard
            if (x >= CLOSE_X - 4 && y <= 40) { kbActive = false; return; }
            int code = kbProcess(false, x, y);
            if (code > 0) { if (wifiPassLen < 32) { wifiPass[wifiPassLen++] = (char)code; wifiPass[wifiPassLen] = 0; } }
            else if (code == -1) { if (wifiPassLen > 0) wifiPass[--wifiPassLen] = 0; }
            else if (code == -2) { kbMode = (kbMode + 1) % 3; }
            else if (code == -4) { kbActive = false; wifiTryConnect(); }
            return;
        }
        if (x >= CLOSE_X - 4 && y <= 40) { view = V_BMS1; manualUntil = millis() + PAUSE_MS; return; }
        if (y >= 44 && y < 74) {                          // sub-tabs
            for (int i = 0; i < 3; i++) { int16_t tx, tw; subTabGeom(i, &tx, &tw);
                if (x >= tx && x < tx + tw) { subTab = i; if (i == ST_WIFI && netCount == 0) wifiStartScan(); return; } }
            return;
        }
        if (subTab == ST_SYSTEM) {
            if (y >= srowY(0) && y < srowY(0) + 40) autoSwitch = !autoSwitch;
            else if (y >= srowY(1) && y < srowY(1) + 40) intervalMs = intervalMs == 3000 ? 5000 : intervalMs == 5000 ? 10000 : 3000;
            else if (y >= srowY(2) && y < srowY(2) + 40) { brightness += (x < Wd / 2) ? -10 : 10; brightness = constrain(brightness, 10, 100); setBrightness(brightness); }
            else if (y >= srowY(3) && y < srowY(3) + 40) autoSleepMin = autoSleepMin == 0 ? 2 : autoSleepMin == 2 ? 5 : autoSleepMin == 5 ? 30 : autoSleepMin == 30 ? 120 : 0;
            else if (y >= srowY(4) && y < srowY(4) + 40) infoPopup = true;
        } else if (subTab == ST_BMS) {
            if (y >= srowY(0) && y < srowY(0) + 40) bmsCharge = !bmsCharge;
            else if (y >= srowY(1) && y < srowY(1) + 40) bmsDischarge = !bmsDischarge;
            else if (y >= srowY(2) && y < srowY(2) + 40) bmsBalancer = !bmsBalancer;
        } else { // ST_WIFI
            int vis = netCount - wifiScroll; if (vis > WIFI_MAXVIS) vis = WIFI_MAXVIS;
            for (int i = 0; i < vis; i++) if (y >= netRowY(i) && y < netRowY(i) + 30) {
                wifiSel = wifiScroll + i;
                if (netEnc[wifiSel]) { wifiPass[0] = 0; wifiPassLen = 0; kbMode = 0; kbActive = true; }
                else wifiTryConnect();
                return;
            }
            int16_t ry = rescanY();
            if (y >= ry && y < ry + 28) {
                if (wifiMaxScroll() > 0) {
                    if (x < 56)       { if (wifiScroll > 0) wifiScroll--; }                 // up
                    else if (x < 108) { if (wifiScroll < wifiMaxScroll()) wifiScroll++; }   // down
                    else              wifiStartScan();
                } else wifiStartScan();
            }
        }
        return;
    }

    // ---- dashboard top bar ----
    manualUntil = millis() + PAUSE_MS;
    if (y >= 6 && y <= 34) {
        if (x >= TAB1_X && x < TAB1_X + TAB_W) { view = V_BMS1; return; }
        if (x >= TAB2_X && x < TAB2_X + TAB_W) { view = V_BMS2; return; }
        if (x >= BED_X && x < BED_X + BED_W)   { pendingSleep = true; return; }
        if (x >= GEAR_X - 4)                   { view = V_SETTINGS; subTab = ST_SYSTEM; kbActive = false; return; }
    }
}

// ---- simulation ----
static void genCap(Bms& b, float spanDays, int count) {
    if (count > NCAP) count = NCAP;
    if (count < 2) count = 2;
    b.capSpanDays = spanDays; b.capCount = count;
    for (int i = 0; i < count; i++) {
        float dpos = (float)i / (count - 1) * spanDays;
        float v = 64.0f + 26.0f * sinf((dpos - 0.30f) * 2.0f * PI) + 6.0f * sinf(dpos * 0.9f) + 3.0f * sinf(i * 1.3f);
        b.cap[i] = v < 12 ? 12 : (v > 99 ? 99 : v);
        b.pwr[i] = 220.0f * cosf((dpos - 0.30f) * 2.0f * PI) + 30.0f * sinf(i * 1.7f);  // +charge / -discharge
    }
}
static void simInit() { genCap(bms[0], 7.0f, 168); genCap(bms[1], 1.0f, 48); }
static void simStep(uint32_t nowMs) {
    float s = nowMs / 1000.0f;
    for (int t = 0; t < 2; t++) {
        float ph = t * 2.1f;
        bms[t].soc  = 62 + 30 * sinf(s * 0.05f + ph);
        bms[t].i    = 28 * sinf(s * 0.18f + ph) + (t ? -4 : 3);
        bms[t].v    = 13.2f + 0.35f * sinf(s * 0.12f + ph) + bms[t].i * 0.004f;
        bms[t].tMos = 33 + fabsf(bms[t].i) * 0.45f + 3 * sinf(s * 0.07f + ph);
        bms[t].tp1  = 24 + 3 * sinf(s * 0.03f + ph) + t;
        bms[t].tp2  = 25 + 3 * sinf(s * 0.04f + ph + 1.0f) + t;
        for (int i = 0; i < NCELLS; i++) bms[t].cell[i] = bms[t].v / NCELLS + 0.015f * sinf(s * 0.5f + i * 1.7f + ph);
    }
}

// ---- flashy 3D standby animation ----
static uint16_t wheel(float h) {                       // hue 0..1 -> rgb565
    h = fmodf(h, 1.0f) * 6.0f; int i = (int)h; float f = h - i;
    uint8_t v = 255, p = 0, q = (uint8_t)(255 * (1 - f)), t = (uint8_t)(255 * f);
    switch (i) {
        case 0: return gfx->color565(v, t, p); case 1: return gfx->color565(q, v, p);
        case 2: return gfx->color565(p, v, t); case 3: return gfx->color565(p, q, v);
        case 4: return gfx->color565(t, p, v); default: return gfx->color565(v, p, q);
    }
}
// Flat-shaded rotating icosahedron (20 faces): rotate verts, perspective-project,
// back-face cull, depth-sort, Lambert-shade each face, glossy edges on top.
static void drawIco(int16_t cx, int16_t cy, float scale, float ax, float ay, float az, float hue) {
    static const float t = 1.61803f;
    static const float BV[12][3] = {{-1,t,0},{1,t,0},{-1,-t,0},{1,-t,0},{0,-1,t},{0,1,t},
        {0,-1,-t},{0,1,-t},{t,0,-1},{t,0,1},{-t,0,-1},{-t,0,1}};
    static const uint8_t F[20][3] = {{0,11,5},{0,5,1},{0,1,7},{0,7,10},{0,10,11},{1,5,9},{5,11,4},
        {11,10,2},{10,7,6},{7,1,8},{3,9,4},{3,4,2},{3,2,6},{3,6,8},{3,8,9},{4,9,5},{2,4,11},{6,2,10},{8,6,7},{9,8,1}};
    float rx[12], ry[12], rz[12]; int16_t px[12], py[12];
    float ca = cosf(ax), sa = sinf(ax), cb = cosf(ay), sb = sinf(ay), cc = cosf(az), sc = sinf(az);
    const float d = 4.0f;                                  // smaller = closer / punchier perspective
    for (int i = 0; i < 12; i++) {
        float x = BV[i][0], y = BV[i][1], z = BV[i][2];
        float y1 = y * ca - z * sa, z1 = y * sa + z * ca;
        float x2 = x * cb + z1 * sb, z2 = -x * sb + z1 * cb;
        float x3 = x2 * cc - y1 * sc, y3 = x2 * sc + y1 * cc;
        rx[i] = x3; ry[i] = y3; rz[i] = z2;
        float p = d / (d - z2);
        px[i] = cx + (int16_t)(x3 * scale * p);
        py[i] = cy + (int16_t)(y3 * scale * p);
    }
    const float lx = 0.40f, ly = 0.50f, lz = 0.77f;       // light direction
    int order[20]; float fz[20]; int n = 0;
    for (int f = 0; f < 20; f++) {
        int a = F[f][0], b = F[f][1], c = F[f][2];
        long area = (long)(px[b] - px[a]) * (py[c] - py[a]) - (long)(py[b] - py[a]) * (px[c] - px[a]);
        if (area <= 0) continue;                          // back-face cull
        order[n] = f; fz[n] = rz[a] + rz[b] + rz[c]; n++;
    }
    for (int i = 1; i < n; i++) {                          // depth sort (far first)
        int oo = order[i]; float ff = fz[i]; int k = i - 1;
        while (k >= 0 && fz[k] > ff) { fz[k+1] = fz[k]; order[k+1] = order[k]; k--; }
        order[k+1] = oo; fz[k+1] = ff;
    }
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
        gfx->fillTriangle(px[a], py[a], px[b], py[b], px[c], py[c],
                          gfx->color565((uint8_t)(rr*br), (uint8_t)(gg*br), (uint8_t)(bb*br)));
    }
    uint16_t ec = dim(0xff, 0xff, 0xff, 70);               // glossy edge highlight
    for (int i = 0; i < n; i++) { int f = order[i], a = F[f][0], b = F[f][1], c = F[f][2];
        gfx->drawTriangle(px[a], py[a], px[b], py[b], px[c], py[c], ec); }
}
static void playSleepAnimation() {
    const int16_t cx = Wd / 2, cy = Ht / 2; const int NS = 56;
    float ang[NS], spd[NS], ph[NS];
    for (int i = 0; i < NS; i++) { ang[i] = fmodf(i * 2.39996f, 6.2832f); spd[i] = 0.7f + 0.6f * fabsf(sinf(i * 1.7f)); ph[i] = fmodf(i * 0.137f, 1.0f); }
    float maxR = sqrtf((float)cx * cx + (float)cy * cy);
    uint32_t t0 = millis(); const float DUR = 2600.0f;
    for (;;) {
        float t = (millis() - t0) / DUR; if (t >= 1.0f) break;
        float endT = t > 0.66f ? (t - 0.66f) / 0.34f : 0.0f;        // recede / warp-away phase 0..1
        gfx->fillScreen(C_BG);
        float warp = t * t * 2.4f + endT * endT * 7.0f;             // accelerate hard at the end
        for (int i = 0; i < NS; i++) {                              // warp starfield streaks
            float r = fmodf(ph[i] + warp * spd[i], 1.0f), rr = r * r * maxR;
            float streak = 6.0f + r * 44.0f + endT * 140.0f;        // long light-streaks on the jump
            float rl = rr - streak; if (rl < 0) rl = 0;
            float c = cosf(ang[i]), s = sinf(ang[i]); uint8_t br = (uint8_t)(60 + 180 * r);
            gfx->drawLine(cx + (int16_t)(c * rl), cy + (int16_t)(s * rl),
                          cx + (int16_t)(c * rr), cy + (int16_t)(s * rr), dim(0x6b, 0x86, 0xff, br));
        }
        float pulse = 0.5f + 0.5f * sinf(t * PI * 4.0f), glowF = 1.0f - endT;
        for (int g = 4; g >= 1; g--) {
            int16_t rad = (int16_t)((24 + g * 18 * (0.8f + 0.4f * pulse)) * glowF);
            if (rad > 1) gfx->fillCircle(cx, cy, rad, dim(0x3d, 0xf0, 0xa8, (uint8_t)(8 + (4 - g) * 7)));
        }
        float scale = 40.0f * (0.78f + 0.42f * sinf(t * PI));       // bigger = closer
        if (endT > 0) scale *= (1.0f - endT) * (1.0f - endT);       // recede to the vanishing point
        drawIco(cx, cy, scale, t * 7.8f, t * 5.9f, t * 4.0f, t * 2.4f);  // faster spin
        gfx->flush();
    }
    gfx->fillScreen(gfx->color565(255, 255, 255)); gfx->flush();    // flash
    gfx->fillScreen(C_BG); gfx->flush();
}

void setup() {
    Serial.begin(115200);
    Serial.setTxTimeoutMs(0);
    delay(300);
    Serial.println("\n[bms] boot — demo dashboard + settings");

    ledcAttach(TFT_BL, BL_CH_FREQ, BL_CH_RES);
    setBrightness(0);
    if (!gfx->begin()) Serial.println("[bms] ERROR: gfx->begin() failed");
    gfx->setRotation(TFT_ROT);
    Wd = gfx->width(); Ht = gfx->height();

    C_BG = gfx->color565(0x04, 0x06, 0x0c); C_CARD = gfx->color565(0x12, 0x18, 0x24);
    C_BORDER = gfx->color565(0x2a, 0x33, 0x42); C_TEXT = gfx->color565(0xea, 0xf2, 0xfb);
    C_MUTED = gfx->color565(0x7e, 0x8b, 0xa0); C_ACCENT = gfx->color565(0x3d, 0xf0, 0xa8);
    C_CYAN = gfx->color565(0x22, 0xd3, 0xee); C_WARN = gfx->color565(0xfb, 0xbf, 0x24);
    C_BAD = gfx->color565(0xfb, 0x71, 0x85); C_INDIGO = gfx->color565(0x9d, 0xb4, 0xff);

    touch.begin();
    touch.setRotation(TFT_ROT);
    touch.enOffsetCorrection(true);
    touch.setOffsets(12, 310, 319, 14, 461, 479);

    WiFi.mode(WIFI_STA);                      // ready for scan/connect
    {   // auto-reconnect to the last remembered network
        prefs.begin("wifi", true);
        String ss = prefs.getString("ssid", ""), pw = prefs.getString("pass", "");
        prefs.end();
        if (ss.length()) {
            strncpy(connSsid, ss.c_str(), 32); connSsid[32] = 0;
            strncpy(connPass, pw.c_str(), 32); connPass[32] = 0;
            wifiSaved = true;                 // already stored
            WiFi.begin(connSsid, connPass);
            snprintf(wifiMsg, sizeof(wifiMsg), "reconnecting to %s...", connSsid);
        }
    }
    lastActivity = millis();

    simInit();
    simStep(millis());
    renderBms(V_BMS1, 0, true);
    setBrightness(brightness);
    Serial.println("[bms] dashboard ready (touch + settings)");

    BmsSerial.begin(115200, SERIAL_8N1, BMS_RX_PIN, BMS_TX_PIN);
    pinMode(BMS_RX_PIN, INPUT_PULLUP);
}

void loop() {
    static uint32_t lastData = 0, lastProgMs = 0, seqLastEvt = 0;
    static bool seqActive = false, seqMoved = false, seqPressHandled = false;
    static int16_t seqStartX = 0, seqStartY = 0;
    static int seqStartScroll = 0;
    static const uint32_t DATA_MS = 400;   // value/animation refresh rate
    uint32_t now = millis();
    bool dirty = false;

    // STANDBY: screen off, just wait for a (fresh) touch to wake -> main screen.
    if (standby) {
        bool t = touch.touched();                       // consume every touch event
        if (t && now - standbySince > 500) {            // ignore residual/held touch
            standby = false; view = V_BMS1;
            manualUntil = now + PAUSE_MS; lastSwitch = now; lastData = now; lastActivity = now;
            seqActive = true; seqPressHandled = true; seqLastEvt = now;   // consume the wake touch
            simStep(now);
            renderBms(V_BMS1, 0, false);
            setBrightness(brightness);     // reveal a clean frame
        }
        delay(8);
        return;
    }

    // Touch is polled every loop (fast) -> responsive even between redraws.
    // Gesture layer: reconstruct press / move / release from the controller's INT
    // pulse stream. Keyboard keys act on PRESS (instant). Everything else acts on
    // RELEASE if the finger didn't move (a tap). Moving the finger on the WiFi list
    // scrolls it (drag) and suppresses selection.
    if (touch.touched()) {
        uint16_t tx, ty; touch.readData(&tx, &ty);
        lastActivity = now; seqLastEvt = now;
        if (DEBUG_TOUCH) { dbgX = (int16_t)tx; dbgY = (int16_t)ty; dbgUntil = now + 900;
                           if (Serial) Serial.printf("[touch] x=%u y=%u\n", tx, ty); }
        if (!seqActive) {                                  // PRESS edge
            seqActive = true; seqMoved = false; seqPressHandled = false;
            seqStartX = (int16_t)tx; seqStartY = (int16_t)ty; seqStartScroll = wifiScroll;
            if (view == V_SETTINGS && kbActive) { handleTap((int16_t)tx, (int16_t)ty); seqPressHandled = true; dirty = true; }
        } else {                                           // MOVE
            if (abs((int)tx - seqStartX) > 12 || abs((int)ty - seqStartY) > 12) seqMoved = true;
            if (seqMoved && view == V_SETTINGS && subTab == ST_WIFI && !kbActive) {
                int ns = seqStartScroll + (seqStartY - (int)ty) / 34;   // drag-scroll the list
                if (ns < 0) ns = 0; if (ns > wifiMaxScroll()) ns = wifiMaxScroll();
                if (ns != wifiScroll) { wifiScroll = ns; dirty = true; }
            }
        }
    }
    if (seqActive && now - seqLastEvt > 90) {              // RELEASE
        seqActive = false;
        if (!seqMoved && !seqPressHandled) { handleTap(seqStartX, seqStartY); dirty = true; }
    }

    // Auto-sleep after the configured idle time.
    if (autoSleepMin > 0 && now >= lastActivity && now - lastActivity > (uint32_t)autoSleepMin * 60000UL)
        pendingSleep = true;

    // ZZZ pressed -> play the 3D animation, then go to standby (screen off).
    if (pendingSleep) {
        pendingSleep = false;
        playSleepAnimation();
        setBrightness(0);
        standby = true; standbySince = millis();
        touch.touched();               // drop any touch that fired during the animation
        return;
    }

    // Smart auto-switch: only between data screens, only when not recently touched.
    bool autoActive = autoSwitch && (view == V_BMS1 || view == V_BMS2) && (now >= manualUntil);
    if (autoActive) {
        if (now - lastSwitch >= intervalMs) { view = (view == V_BMS1) ? V_BMS2 : V_BMS1; lastSwitch = now; dirty = true; }
        if (now - lastProgMs >= 90) { lastProgMs = now; dirty = true; }   // smooth progress underline
    } else {
        lastSwitch = now;
    }

    // Non-blocking WiFi scan harvest + connection-status updates.
    if (wifiPoll() && view == V_SETTINGS && subTab == ST_WIFI) dirty = true;

    // Data tick: refresh values (and keep the progress underline moving) periodically.
    if (now - lastData >= DATA_MS) {
        simStep(now);
        lastData = now;
        if (view != V_SETTINGS) dirty = true;                 // BMS views show live values
        // Settings/WiFi/keyboard are NOT redrawn on a timer — only on input or a
        // real change (wifiPoll sets dirty on scan/connection changes). Idle full
        // flushes were blocking + delaying the touch read, hurting responsiveness.
    }

    // Only redraw when something actually changed.
    if (dirty) {
        float prog = autoActive ? (float)(now - lastSwitch) / intervalMs : 0;
        if (prog > 1.0f) prog = 1.0f;
        if (view == V_SETTINGS) renderSettings();
        else                    renderBms(view, prog, autoActive);
    }

    int nb = 0;
    while (BmsSerial.available() && nb++ < 64) { uint8_t x = BmsSerial.read(); if (Serial) Serial.printf("%02X ", x); }
    delay(4);
}
