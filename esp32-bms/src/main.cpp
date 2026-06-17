// JK BMS → Guition JC3248W535 (320x480 QSPI AXS15231B) — FANCY DEMO DASHBOARD.
// Tab bar [BMS 1][BMS 2] auto-switching (active highlighted), SOC ring gauge,
// V/A/temp tiles with charge/discharge arrow, per-cell bars, power sparkline.
// Data is SIMULATED for now (smooth, time-based) until the real BMS UART is wired.
//
// Rendering: full-screen Arduino_Canvas redrawn each frame + flush (~15-18fps,
// smooth now that USB-CDC no longer blocks the loop — see setTxTimeoutMs/if(Serial)).
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <math.h>

#define TFT_BL 1
#define TFT_CS 45
#define TFT_SCK 47
#define TFT_SDA0 21
#define TFT_SDA1 48
#define TFT_SDA2 40
#define TFT_SDA3 39
#define TFT_ROT 1        // landscape 480x320
#define TFT_W 320        // native canvas size (panel is 320x480); rotation swaps W/H
#define TFT_H 480
#define NCELLS 4
#define HISTN 180

static constexpr int BMS_TX_PIN = 17;
static constexpr int BMS_RX_PIN = 18;
HardwareSerial BmsSerial(1);

Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *panel = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_W, TFT_H);
Arduino_Canvas *gfx = new Arduino_Canvas(TFT_W, TFT_H, panel, 0, 0);

static uint16_t C_BG, C_CARD, C_BORDER, C_TEXT, C_MUTED, C_ACCENT, C_CYAN, C_WARN, C_BAD;
static int16_t Wd, Ht;   // landscape draw size (480x320), set after setRotation

struct Bms {
    float soc, v, i, temp;
    float cell[NCELLS];
    float hist[HISTN];
    int histHead;
};
static Bms bms[2];

// ---- helpers ----
static void centerText(const char* s, int16_t cx, int16_t cy, uint8_t size, uint16_t color) {
    int16_t x1, y1; uint16_t w, h;
    gfx->setTextSize(size);
    gfx->getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
    gfx->setTextColor(color);
    gfx->setCursor(cx - w / 2 - x1, cy - h / 2 - y1);
    gfx->print(s);
}
static void leftText(const char* s, int16_t x, int16_t y, uint8_t size, uint16_t color) {
    gfx->setTextSize(size); gfx->setTextColor(color); gfx->setCursor(x, y); gfx->print(s);
}
static uint16_t socColor(float soc) {
    if (soc >= 60) return C_ACCENT;
    if (soc >= 30) return C_WARN;
    return C_BAD;
}

static void drawTabs(int active, float prog) {
    const int16_t y = 6, h = 28, gap = 8, w = 120;
    for (int t = 0; t < 2; t++) {
        int16_t x = 8 + t * (w + gap);
        bool on = (t == active);
        gfx->fillRoundRect(x, y, w, h, 8, on ? C_ACCENT : C_CARD);
        if (!on) gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
        char lbl[8]; snprintf(lbl, sizeof(lbl), "BMS %d", t + 1);
        centerText(lbl, x + w / 2, y + h / 2, 2, on ? C_BG : C_MUTED);
        // auto-switch progress underline on the active tab
        if (on) gfx->fillRect(x + 6, y + h - 3, (int16_t)((w - 12) * prog), 2, C_BG);
    }
}

static void drawRing(int16_t cx, int16_t cy, int16_t ro, int16_t ri, float pct, uint16_t col) {
    gfx->fillArc(cx, cy, ro, ri, 0, 360, C_BORDER);                 // track
    if (pct > 0.5f) gfx->fillArc(cx, cy, ro, ri, 0, pct * 3.6f, col); // fill
    char buf[8]; snprintf(buf, sizeof(buf), "%d", (int)(pct + 0.5f));
    centerText(buf, cx, cy - 6, 5, C_TEXT);
    centerText("%", cx, cy + 26, 2, C_MUTED);
}

static void drawTile(int16_t x, int16_t y, int16_t w, int16_t h,
                     const char* label, const char* val, const char* unit,
                     uint16_t valCol, int arrow /*0 none,1 up,-1 down*/) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    leftText(label, x + 8, y + 8, 1, C_MUTED);
    leftText(val, x + 8, y + 26, 2, valCol);
    leftText(unit, x + 8, y + h - 14, 1, C_MUTED);
    if (arrow) {  // small charge/discharge triangle, top-right
        int16_t ax = x + w - 16, ay = y + 10;
        if (arrow > 0) gfx->fillTriangle(ax, ay + 8, ax + 10, ay + 8, ax + 5, ay, C_ACCENT);
        else           gfx->fillTriangle(ax, ay, ax + 10, ay, ax + 5, ay + 8, C_WARN);
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
        float frac = (b.cell[i] - 3.0f) / 0.6f; if (frac < 0.05f) frac = 0.05f; if (frac > 1) frac = 1;
        int16_t barH = (int16_t)(bh * frac);
        int16_t cxp = bx + i * bw;
        uint16_t c = (i == loI) ? C_CYAN : (i == hiI) ? C_WARN : C_ACCENT;
        gfx->fillRoundRect(cxp + 2, by + (bh - barH), bw - 8, barH, 3, c);
        char cv[8]; snprintf(cv, sizeof(cv), "%.2f", b.cell[i]);
        centerText(cv, cxp + (bw - 4) / 2, y + h - 10, 1, C_MUTED);
    }
}

static void drawSparkline(int16_t x, int16_t y, int16_t w, int16_t h, const Bms& b, uint16_t col) {
    gfx->fillRoundRect(x, y, w, h, 8, C_CARD);
    gfx->drawRoundRect(x, y, w, h, 8, C_BORDER);
    leftText("PACK POWER (W)", x + 8, y + 8, 1, C_MUTED);
    const int16_t gx = x + 8, gy = y + 22, gw = w - 16, gh = h - 30;
    float lo = 1e9, hi = -1e9;
    for (int i = 0; i < HISTN; i++) { float v = b.hist[i]; if (v < lo) lo = v; if (v > hi) hi = v; }
    if (hi - lo < 1) { hi += 1; lo -= 1; }
    gfx->drawFastHLine(gx, gy + gh / 2, gw, C_BORDER);   // zero-ish baseline
    int16_t px = -1, py = -1;
    for (int i = 0; i < HISTN; i++) {
        int idx = (b.histHead + i) % HISTN;
        int16_t sx = gx + (int16_t)((float)i / (HISTN - 1) * gw);
        int16_t sy = gy + gh - (int16_t)((b.hist[idx] - lo) / (hi - lo) * gh);
        if (px >= 0) gfx->drawLine(px, py, sx, sy, col);
        px = sx; py = sy;
    }
}

static void render(int active, float switchProg) {
    const Bms& b = bms[active];
    gfx->fillScreen(C_BG);
    gfx->fillRect(0, 0, Wd, 3, C_ACCENT);

    drawTabs(active, switchProg);

    // ---- LEFT: SOC ring gauge ----
    const int16_t cx = 100, cy = 178;
    centerText("STATE OF CHARGE", cx, 52, 1, C_MUTED);
    drawRing(cx, cy, 74, 58, b.soc, socColor(b.soc));
    char pw[12]; snprintf(pw, sizeof(pw), "%.0f W", b.v * b.i);
    centerText(pw, cx, cy + 96, 2, (b.i >= 0) ? C_ACCENT : C_WARN);
    centerText((b.i >= 0) ? "CHARGING" : "DISCHARGING", cx, cy + 120, 1, C_MUTED);

    // ---- RIGHT column ----
    const int16_t rx = 200, rw = Wd - rx - 8;   // 200..472
    // Tiles row
    char vbuf[8], ibuf[8], tbuf[8];
    snprintf(vbuf, sizeof(vbuf), "%.1f", b.v);
    snprintf(ibuf, sizeof(ibuf), "%+.1f", b.i);
    snprintf(tbuf, sizeof(tbuf), "%.0f", b.temp);
    const int16_t ty = 40, th = 70, gap = 8, tw = (rw - 2 * gap) / 3;
    drawTile(rx,                  ty, tw, th, "VOLTAGE", vbuf, "VOLT", C_TEXT, 0);
    drawTile(rx + tw + gap,       ty, tw, th, "CURRENT", ibuf, "AMP",  (b.i >= 0) ? C_ACCENT : C_WARN, b.i >= 0 ? 1 : -1);
    drawTile(rx + 2 * (tw + gap), ty, tw, th, "TEMP",    tbuf, "DEG", C_CYAN, 0);

    drawCells(rx, 120, rw, 86, b);
    drawSparkline(rx, 216, rw, 96, b, C_CYAN);

    gfx->flush();
}

// ---- simulation ----
static void simInit() {
    for (int t = 0; t < 2; t++) {
        bms[t].histHead = 0;
        for (int i = 0; i < HISTN; i++) bms[t].hist[i] = 0;
    }
}
static void simStep(uint32_t nowMs) {
    float s = nowMs / 1000.0f;
    for (int t = 0; t < 2; t++) {
        float ph = t * 2.1f;
        bms[t].soc  = 62 + 30 * sinf(s * 0.05f + ph);
        bms[t].i    = 28 * sinf(s * 0.18f + ph) + (t ? -4 : 3);
        bms[t].v    = 13.2f + 0.35f * sinf(s * 0.12f + ph) + bms[t].i * 0.004f;
        bms[t].temp = 24 + 4 * sinf(s * 0.03f + ph) + (t * 2);
        for (int i = 0; i < NCELLS; i++)
            bms[t].cell[i] = bms[t].v / NCELLS + 0.015f * sinf(s * 0.5f + i * 1.7f + ph);
        // push power history at ~20Hz
        bms[t].hist[bms[t].histHead] = bms[t].v * bms[t].i;
        bms[t].histHead = (bms[t].histHead + 1) % HISTN;
    }
}

void setup() {
    Serial.begin(115200);
    Serial.setTxTimeoutMs(0);
    delay(300);
    Serial.println("\n[bms] boot — fancy demo dashboard");

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, LOW);
    if (!gfx->begin()) Serial.println("[bms] ERROR: gfx->begin() failed");
    gfx->setRotation(TFT_ROT);
    Wd = gfx->width(); Ht = gfx->height();   // 480 x 320 landscape

    C_BG     = gfx->color565(0x04, 0x06, 0x0c);
    C_CARD   = gfx->color565(0x12, 0x18, 0x24);
    C_BORDER = gfx->color565(0x2a, 0x33, 0x42);
    C_TEXT   = gfx->color565(0xea, 0xf2, 0xfb);
    C_MUTED  = gfx->color565(0x7e, 0x8b, 0xa0);
    C_ACCENT = gfx->color565(0x3d, 0xf0, 0xa8);
    C_CYAN   = gfx->color565(0x22, 0xd3, 0xee);
    C_WARN   = gfx->color565(0xfb, 0xbf, 0x24);
    C_BAD    = gfx->color565(0xfb, 0x71, 0x85);

    simInit();
    simStep(millis());
    render(0, 0);
    digitalWrite(TFT_BL, HIGH);
    Serial.println("[bms] dashboard ready");

    BmsSerial.begin(115200, SERIAL_8N1, BMS_RX_PIN, BMS_TX_PIN);
    pinMode(BMS_RX_PIN, INPUT_PULLUP);
}

void loop() {
    static uint32_t fpsT = 0, frames = 0;
    uint32_t now = millis();
    simStep(now);

    int active = (now / 5000) % 2;            // auto-switch every 5s
    float prog = (now % 5000) / 5000.0f;
    render(active, prog);
    frames++;

    int nb = 0;
    while (BmsSerial.available() && nb++ < 64) { uint8_t x = BmsSerial.read(); if (Serial) Serial.printf("%02X ", x); }

    if (now - fpsT >= 1000) {
        if (Serial) Serial.printf("[bms] fps=%lu cpu=%uMHz heap=%u\n",
                                  (unsigned long)frames, (unsigned)getCpuFrequencyMhz(), (unsigned)ESP.getFreeHeap());
        frames = 0; fpsT = now;
    }
}
