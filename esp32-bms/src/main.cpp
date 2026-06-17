// JK BMS → Guition JC3248W535 (480x320 landscape) — DEMO DASHBOARD + SETTINGS.
// Tabs [BMS 1][BMS 2][gear]. Auto-switch cycles only between BMS 1<->2; a tap
// pauses it for 30s then it resumes; Settings is never auto-cycled. Touch via the
// AXS15231B (I2C). Data is simulated until the real BMS UART parser lands.
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
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

#define TOUCH_SDA 4
#define TOUCH_SCL 8
#define TOUCH_INT 3
#define TOUCH_ADDR 0x3B

#define BL_CH_FREQ 5000
#define BL_CH_RES 8

static constexpr int BMS_TX_PIN = 17;
static constexpr int BMS_RX_PIN = 18;
HardwareSerial BmsSerial(1);

Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *panel = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_W, TFT_H);
Arduino_Canvas *gfx = new Arduino_Canvas(TFT_W, TFT_H, panel, 0, 0);
AXS15231B_Touch touch(TOUCH_SCL, TOUCH_SDA, TOUCH_INT, TOUCH_ADDR, TFT_ROT);

static uint16_t C_BG, C_CARD, C_BORDER, C_TEXT, C_MUTED, C_ACCENT, C_CYAN, C_WARN, C_BAD;
static int16_t Wd, Ht;

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
    float cap[NCAP];
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

// ---- tab bar (shared) ----
#define GEAR_X (Wd - 38)
#define GEAR_Y 6
#define GEAR_W 30
static void drawTabs(bool autoActive, float prog) {
    const int16_t y = 6, h = 28, gap = 8, w = 120;
    for (int t = 0; t < 2; t++) {
        int16_t x = 8 + t * (w + gap);
        bool on = (view == t);
        gfx->fillRoundRect(x, y, w, h, 8, on ? C_ACCENT : C_CARD);
        if (!on) gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
        char lbl[8]; snprintf(lbl, sizeof(lbl), "BMS %d", t + 1);
        centerText(lbl, x + w / 2, y + h / 2, 2, on ? C_BG : C_MUTED);
        if (on && autoActive) gfx->fillRect(x + 6, y + h - 3, (int16_t)((w - 12) * prog), 2, C_BG);
    }
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
static void drawCells(int16_t x, int16_t y, int16_t w, int16_t h, const Bms& b) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    float lo = 9, hi = 0; int loI = 0, hiI = 0;
    for (int i = 0; i < NCELLS; i++) { if (b.cell[i] < lo) { lo = b.cell[i]; loI = i; } if (b.cell[i] > hi) { hi = b.cell[i]; hiI = i; } }
    char hdr[24]; snprintf(hdr, sizeof(hdr), "CELLS   d %dmV", (int)((hi - lo) * 1000));
    leftText(hdr, x + 8, y + 8, 1, C_MUTED);
    const int16_t bx = x + 10, by = y + 24, bh = h - 44, bw = (w - 20) / NCELLS;
    for (int i = 0; i < NCELLS; i++) {
        float frac = (b.cell[i] - 3.0f) / 0.6f; frac = frac < 0.05f ? 0.05f : frac > 1 ? 1 : frac;
        int16_t barH = (int16_t)(bh * frac), cxp = bx + i * bw;
        uint16_t c = (i == loI) ? C_CYAN : (i == hiI) ? C_WARN : C_ACCENT;
        gfx->fillRoundRect(cxp + 2, by + (bh - barH), bw - 8, barH, 3, c);
        char cv[8]; snprintf(cv, sizeof(cv), "%.2f", b.cell[i]);
        centerText(cv, cxp + (bw - 4) / 2, y + h - 10, 1, C_MUTED);
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
    int cnt = (b.capCount < 2) ? 2 : b.capCount;
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
    gfx->fillRect(0, 0, Wd, 3, C_ACCENT);
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

    drawCells(rx, 120, rw, 86, b);
    drawCapacityGraph(rx, 216, rw, 96, b);
    drawTouchBlob();
    gfx->flush();
}

// ---- settings screen ----
#define ROW0_Y 48
#define ROW_H 52
static int16_t rowY(int i) { return ROW0_Y + i * (ROW_H + 8); }

static void settingRow(int i, const char* label, const char* val, uint16_t valCol, bool chip) {
    int16_t y = rowY(i), x = 8, w = Wd - 16;
    gfx->fillRoundRect(x, y, w, ROW_H, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, ROW_H, 8, C_BORDER);
    leftText(label, x + 14, y + ROW_H / 2 - 7, 2, C_TEXT);
    // value chip on the right
    int16_t vx, vy; uint16_t vw, vh; gfx->setTextSize(2); gfx->getTextBounds(val, 0, 0, &vx, &vy, &vw, &vh);
    int16_t chipW = vw + 28, chipX = x + w - chipW - 12, chipY = y + ROW_H / 2 - 15;
    if (chip) { gfx->fillRoundRect(chipX, chipY, chipW, 30, 15, dim((valCol >> 11) << 3, ((valCol >> 5) & 0x3f) << 2, (valCol & 0x1f) << 3, 60)); }
    centerText(val, chipX + chipW / 2, y + ROW_H / 2, 2, valCol);
}

static void renderSettings() {
    gfx->fillScreen(C_BG);
    gfx->fillRect(0, 0, Wd, 3, C_ACCENT);
    drawTabs(false, 0);

    char ibuf[8]; snprintf(ibuf, sizeof(ibuf), "%lus", (unsigned long)(intervalMs / 1000));
    char bbuf[8]; snprintf(bbuf, sizeof(bbuf), "%d%%", brightness);
    settingRow(0, "Auto-switch",     autoSwitch ? "ON" : "OFF", autoSwitch ? C_ACCENT : C_MUTED, true);
    settingRow(1, "Switch interval", ibuf, C_CYAN, true);
    settingRow(2, "Brightness  - / +", bbuf, C_TEXT, true);

    // info row
    int16_t y = rowY(3);
    gfx->fillRoundRect(8, y, Wd - 16, ROW_H, 8, C_CARD);
    gfx->drawRoundRect(8, y, Wd - 16, ROW_H, 8, C_BORDER);
    leftText("JC3248W535  -  2 BMS  -  demo v0.1", 14, y + 10, 1, C_MUTED);
    leftText("tap a BMS tab to exit settings", 14, y + 28, 1, C_MUTED);
    drawTouchBlob();
    gfx->flush();
}

// ---- touch handling ----
static void handleTap(int16_t x, int16_t y) {
    manualUntil = millis() + PAUSE_MS;          // any tap pauses auto-switch
    // tab bar
    if (y >= 6 && y <= 34) {
        if (x >= 8 && x < 128)        { view = V_BMS1; return; }
        if (x >= 136 && x < 256)      { view = V_BMS2; return; }
        if (x >= GEAR_X - 4)          { view = V_SETTINGS; return; }
    }
    if (view != V_SETTINGS) return;
    // settings rows
    if (y >= rowY(0) && y < rowY(0) + ROW_H) { autoSwitch = !autoSwitch; }
    else if (y >= rowY(1) && y < rowY(1) + ROW_H) {
        intervalMs = (intervalMs == 3000) ? 5000 : (intervalMs == 5000) ? 10000 : 3000;
    } else if (y >= rowY(2) && y < rowY(2) + ROW_H) {
        brightness += (x < Wd / 2) ? -10 : 10;
        brightness = constrain(brightness, 10, 100);
        setBrightness(brightness);
    }
}

// ---- simulation ----
static void genCap(Bms& b, float spanDays, int count) {
    if (count > NCAP) count = NCAP;
    b.capSpanDays = spanDays; b.capCount = count;
    for (int i = 0; i < count; i++) {
        float dpos = (float)i / (count - 1) * spanDays;
        float v = 64.0f + 26.0f * sinf((dpos - 0.30f) * 2.0f * PI) + 6.0f * sinf(dpos * 0.9f) + 3.0f * sinf(i * 1.3f);
        b.cap[i] = v < 12 ? 12 : (v > 99 ? 99 : v);
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
    C_BAD = gfx->color565(0xfb, 0x71, 0x85);

    touch.begin();
    touch.setRotation(TFT_ROT);
    touch.enOffsetCorrection(true);
    touch.setOffsets(12, 310, 319, 14, 461, 479);

    simInit();
    simStep(millis());
    renderBms(V_BMS1, 0, true);
    setBrightness(brightness);
    Serial.println("[bms] dashboard ready (touch + settings)");

    BmsSerial.begin(115200, SERIAL_8N1, BMS_RX_PIN, BMS_TX_PIN);
    pinMode(BMS_RX_PIN, INPUT_PULLUP);
}

void loop() {
    static uint32_t lastTap = 0, lastData = 0;
    static const uint32_t DATA_MS = 400;   // value/animation refresh rate
    uint32_t now = millis();
    bool dirty = false;

    // Touch is polled every loop (fast) -> responsive even between redraws.
    if (touch.touched()) {
        uint16_t tx, ty; touch.readData(&tx, &ty);
        if (DEBUG_TOUCH) { dbgX = (int16_t)tx; dbgY = (int16_t)ty; dbgUntil = now + 900;
                           if (Serial) Serial.printf("[touch] x=%u y=%u\n", tx, ty); }
        if (now - lastTap > 120) { handleTap((int16_t)tx, (int16_t)ty); lastTap = now; dirty = true; }
    }

    // Smart auto-switch: only between data screens, only when not recently touched.
    bool autoActive = autoSwitch && (view == V_BMS1 || view == V_BMS2) && (now >= manualUntil);
    if (autoActive) {
        if (now - lastSwitch >= intervalMs) { view = (view == V_BMS1) ? V_BMS2 : V_BMS1; lastSwitch = now; dirty = true; }
    } else {
        lastSwitch = now;
    }

    // Data tick: refresh values (and keep the progress underline moving) periodically.
    if (now - lastData >= DATA_MS) {
        simStep(now);
        lastData = now;
        if (view != V_SETTINGS) dirty = true;   // BMS views show live values
    }

    // Only redraw when something actually changed.
    if (dirty) {
        float prog = autoActive ? (float)(now - lastSwitch) / intervalMs : 0;
        if (view == V_SETTINGS) renderSettings();
        else                    renderBms(view, prog, autoActive);
    }

    int nb = 0;
    while (BmsSerial.available() && nb++ < 64) { uint8_t x = BmsSerial.read(); if (Serial) Serial.printf("%02X ", x); }
    delay(4);
}
