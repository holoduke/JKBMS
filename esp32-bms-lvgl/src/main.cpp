// JK BMS LVGL dashboard — Guition JC3248W535 (480x320 landscape).
// Faithful pixel-for-pixel reproduction of the esp32-bms/ Arduino_GFX dashboard,
// drawn through LVGL's vector draw API (so the text is anti-aliased). Every shape,
// coordinate and colour matches the original; only the fonts are nicer. Data is
// simulated; tabs auto-switch (BMS1<->BMS2), a tap pauses it for 30s.
#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <WiFi.h>
#include <Preferences.h>
#include <time.h>
#include <math.h>
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"

#define FW_VERSION "0.4.0"
#define BL_CH_FREQ 5000
#define BL_CH_RES 8

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
Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *g = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_res_W, TFT_res_H);
Arduino_Canvas *gfx = new Arduino_Canvas(TFT_res_W, TFT_res_H, g, 0, 0, TFT_rot);
AXS15231B_Touch touch(Touch_SCL, Touch_SDA, Touch_INT, Touch_ADDR, TFT_rot);
static bool gfxDirty = false;

// ---- simulated BMS data ----
struct Bms {
    float soc, v, i, tMos, tp1, tp2;
    float cell[NCELLS];
    float cap[NCAP], pwr[NCAP];
    int capCount; float capSpanDays;
    float peakChg, peakDis;
};
static Bms bms[2];
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
static bool bmsCharge = true, bmsDischarge = true, bmsBalancer = false;
static bool tempF = false, fmt12 = false, wifiAuto = true;
static int simSpeed = 1;            // demo data speed (1/2/5x)
static int sysScroll = 0;           // System-tab scroll offset (px)
static bool infoPopup = false;
static bool pendingSleep = false, standby = false;
static uint32_t lastActivity = 0;
// wifi
#define MAXNET 10
#define WIFI_MAXVIS 5
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
static void simStep(uint32_t nowMs) {
    float s = nowMs / 1000.0f * simSpeed;
    for (int t = 0; t < 2; t++) {
        float ph = t * 2.1f;
        bms[t].soc = 62 + 30 * sinf(s * 0.05f + ph);
        bms[t].i = 28 * sinf(s * 0.18f + ph) + (t ? -4 : 3);
        bms[t].v = 13.2f + 0.35f * sinf(s * 0.12f + ph) + bms[t].i * 0.004f;
        bms[t].tMos = 33 + fabsf(bms[t].i) * 0.45f + 3 * sinf(s * 0.07f + ph);
        bms[t].tp1 = 24 + 3 * sinf(s * 0.03f + ph) + t;
        bms[t].tp2 = 25 + 3 * sinf(s * 0.04f + ph + 1) + t;
        for (int i = 0; i < NCELLS; i++) bms[t].cell[i] = bms[t].v / NCELLS + 0.015f * sinf(s * 0.5f + i * 1.7f + ph);
        float p = bms[t].v * bms[t].i;
        if (p > bms[t].peakChg) bms[t].peakChg = p;
        if (-p > bms[t].peakDis) bms[t].peakDis = -p;
    }
}
static uint32_t socColor(float soc) { return soc >= 60 ? C_ACCENT : soc >= 30 ? C_WARN : C_BAD; }
static uint32_t tempColor(float t) { return t >= 55 ? C_BAD : t >= 45 ? C_WARN : C_ACCENT; }
static void timeLabel(char *out, size_t n, float daysAgo, float span) {
    if (daysAgo < 0.04f) { snprintf(out, n, "now"); return; }
    if (span >= 2.0f) snprintf(out, n, "%.0fd", daysAgo);
    else snprintf(out, n, "%.0fh", daysAgo * 24.0f);
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
static void drawTabs(bool autoActive, float prog) {
    const int y = 6, h = 28;
    const int tabX[2] = {TAB1_X, TAB2_X};
    for (int t = 0; t < 2; t++) {
        int x = tabX[t]; bool on = (view == t);
        fRect(x, y, TAB_W, h, 8, on ? C_ACCENT : C_CARD);
        if (!on) dRect(x, y, TAB_W, h, 8, C_BORDER);
        char lbl[8]; snprintf(lbl, sizeof(lbl), "BMS %d", t + 1);
        cText(lbl, x + TAB_W / 2, y + h / 2, F16, on ? C_BG : C_MUTED);
        if (on && autoActive) fRect(x + 6, y + h - 3, (int)((TAB_W - 12) * prog), 2, 0, C_BG);
    }
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
static void drawRing(int cx, int cy, int ro, int ri, float pct, uint32_t col) {
    ring(cx, cy, ro, ri, 0, 360, C_BORDER);
    if (pct >= 99.5f) ring(cx, cy, ro, ri, 0, 360, col);
    else if (pct > 0.5f) {
        int ea = 270 + (int)(pct * 3.6f); while (ea >= 360) ea -= 360;
        ring(cx, cy, ro, ri, 270, ea, col);
    }
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
static void drawTempsTile(int x, int y, int w, int h, float mos, float t1, float t2) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    const char *lbl[3] = {"MOS", "T1", "T2"}; float v[3] = {mos, t1, t2};
    for (int r = 0; r < 3; r++) {
        int ry = y + 12 + r * 19;
        lText(lbl[r], x + 8, ry + 2, F10, C_MUTED);
        char buf[8]; snprintf(buf, sizeof(buf), "%.0fC", v[r]);
        lText(buf, x + 34, ry, F12, tempColor(v[r]));
    }
}
static void drawStatsTile(int x, int y, int w, int h, float pkChg, float pkDis, uint32_t upSec) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    const char *lbl[3] = {"PK CHG", "PK DIS", "UPTIME"};
    char val[3][10];
    snprintf(val[0], sizeof(val[0]), "%.0fW", pkChg);
    snprintf(val[1], sizeof(val[1]), "%.0fW", pkDis);
    uint32_t m = upSec / 60; snprintf(val[2], sizeof(val[2]), "%luh%02lu", (unsigned long)(m / 60), (unsigned long)(m % 60));
    uint32_t vc[3] = {C_ACCENT, C_WARN, C_TEXT};
    for (int r = 0; r < 3; r++) {
        int ry = y + 12 + r * 20;
        lText(lbl[r], x + 8, ry, F10, C_MUTED);
        lText(val[r], x + w - textW(val[r], F10) - 8, ry, F10, vc[r]);
    }
}
static void drawCells(int x, int y, int w, int h, const Bms &b) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    float lo = 9, hi = 0; int loI = 0, hiI = 0;
    for (int i = 0; i < NCELLS; i++) { if (b.cell[i] < lo) { lo = b.cell[i]; loI = i; } if (b.cell[i] > hi) { hi = b.cell[i]; hiI = i; } }
    char hdr[20]; snprintf(hdr, sizeof(hdr), "CELLS  %dmV", (int)((hi - lo) * 1000));
    lText(hdr, x + 8, y + 7, F12, C_MUTED);
    const int top = y + 22, rh = (h - 28) / NCELLS;
    for (int i = 0; i < NCELLS; i++) {
        int ry = top + i * rh, midY = ry + (rh - 8) / 2 - 2;
        char cl[4]; snprintf(cl, sizeof(cl), "C%d", i + 1);
        lText(cl, x + 8, midY, F12, C_MUTED);
        int bx = x + 28, bw = w - 28 - 42, by = ry + 2, bh = rh - 4;
        fRect(bx, by, bw, bh, 2, C_BORDER);
        float frac = (b.cell[i] - 3.0f) / 0.6f; frac = frac < 0.05f ? 0.05f : frac > 1 ? 1 : frac;
        uint32_t c = (i == loI) ? C_CYAN : (i == hiI) ? C_WARN : C_ACCENT;
        fRect(bx, by, (int)(bw * frac), bh, 2, c);
        char cv[8]; snprintf(cv, sizeof(cv), "%.2f", b.cell[i]);
        lText(cv, x + w - 40, midY, F12, C_TEXT);
    }
}
static void drawPowerGraph(int x, int y, int w, int h, const Bms &b) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    lText("POWER  W", x + 8, y + 6, F10, C_MUTED);
    const int lblW = 24, gx = x + 8 + lblW, gy = y + 22, gw = w - 14 - lblW, gh = h - 38, base = gy + gh;
    int cnt = (b.capCount < 2) ? 2 : (b.capCount > NCAP ? NCAP : b.capCount);
    float lo = 1e9f, hi = -1e9f;
    for (int i = 0; i < cnt; i++) { float v = b.pwr[i]; if (v < lo) lo = v; if (v > hi) hi = v; }
    if (lo > 0) lo = 0; if (hi < 0) hi = 0; if (hi - lo < 1) hi = lo + 1;
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
        char lbl[8]; timeLabel(lbl, sizeof(lbl), b.capSpanDays * (1.0f - k / 4.0f), b.capSpanDays);
        if (k == 0) lText(lbl, fx, base + 6, F10, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F10), base + 6, F10, C_MUTED);
        else cText(lbl, fx, base + 11, F10, C_MUTED);
    }
}
static void drawCapacityGraph(int x, int y, int w, int h, const Bms &b) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    char hdr[28];
    if (b.capSpanDays >= 2.0f) snprintf(hdr, sizeof(hdr), "CAPACITY   %.0f days", b.capSpanDays);
    else snprintf(hdr, sizeof(hdr), "CAPACITY   24 hours");
    lText(hdr, x + 8, y + 6, F10, C_MUTED);
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
#define POW_W 132
#define POW_H 86
#define CAP_W 272
#define CAP_H 96
static lv_obj_t *powCv = nullptr, *capCv = nullptr;
static void renderGraphs() {
    if (!powCv || !capCv) return;
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
static void switchView(int v) { view = v; renderGraphs(); }

static void renderBms() {
    const Bms &b = bms[view];
    uint32_t now = millis();
    bool autoActive = (now >= manualUntil);
    float prog = autoActive ? (float)(now - lastSwitch) / intervalMs : 0;
    if (prog > 1) prog = 1; if (prog < 0) prog = 0;
    drawTabs(autoActive, prog);

    const int cx = 100, cy = 178;
    cText("STATE OF CHARGE", cx, 52, F12, C_MUTED);
    drawRing(cx, cy, 74, 58, b.soc, socColor(b.soc));
    bool chg = (b.i >= 0); uint32_t pcol = chg ? C_ACCENT : C_WARN;
    char pw[12]; snprintf(pw, sizeof(pw), "%.0f W", fabsf(b.v * b.i));
    int bw = textW(pw, F20);
    cText(pw, cx + 8, cy + 96, F20, pcol);
    int ax = cx + 8 - bw / 2 - 16, ay = cy + 96 - 6;
    if (chg) tri(ax, ay + 10, ax + 10, ay + 10, ax + 5, ay, C_ACCENT);
    else tri(ax, ay, ax + 10, ay, ax + 5, ay + 10, C_WARN);
    char sub[26]; snprintf(sub, sizeof(sub), "%s  %.1f A", chg ? "CHARGING" : "DISCHARGING", fabsf(b.i));
    cText(sub, cx, cy + 122, F12, C_MUTED);

    const int rx = 200, rw = Wd - rx - 8;
    char vbuf[10]; snprintf(vbuf, sizeof(vbuf), "%.2fV", b.v);
    const int ty = 40, th = 70, gap = 8, tw = (rw - 2 * gap) / 3;
    drawTile(rx, ty, tw, th, "VOLTAGE", vbuf, nullptr, C_TEXT);
    drawStatsTile(rx + tw + gap, ty, tw, th, b.peakChg, b.peakDis, now / 1000);
    drawTempsTile(rx + 2 * (tw + gap), ty, tw, th, b.tMos, b.tp1, b.tp2);

    const int halfW = (rw - 8) / 2;
    drawCells(rx, 120, halfW, 86, b);
    blitCanvas(powCv, rx + halfW + 8, 120, POW_W, POW_H);
    blitCanvas(capCv, rx, 216, CAP_W, CAP_H);
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

// ---- scrollable System list ----
static const char *SYS_LABEL[] = {
    "Auto-switch", "Switch interval", "Brightness   - / +", "Auto-sleep", "Temp unit",
    "Time format", "WiFi auto-connect", "Demo speed", "System info", "Firmware"};
#define SYS_ROWS ((int)(sizeof(SYS_LABEL) / sizeof(SYS_LABEL[0])))
static void sysVal(int i, char *o, size_t n, uint32_t *vc) {
    switch (i) {
        case 0: snprintf(o, n, "%s", autoSwitch ? "ON" : "OFF"); *vc = autoSwitch ? C_ACCENT : C_MUTED; break;
        case 1: snprintf(o, n, "%lus", (unsigned long)(intervalMs / 1000)); *vc = C_CYAN; break;
        case 2: snprintf(o, n, "%d%%", brightness); *vc = C_TEXT; break;
        case 3: if (autoSleepMin == 0) snprintf(o, n, "Never"); else snprintf(o, n, "%d min", autoSleepMin); *vc = autoSleepMin ? C_CYAN : C_MUTED; break;
        case 4: snprintf(o, n, "%s", tempF ? "Fahr." : "Celsius"); *vc = C_CYAN; break;
        case 5: snprintf(o, n, "%s", fmt12 ? "12-hour" : "24-hour"); *vc = C_CYAN; break;
        case 6: snprintf(o, n, "%s", wifiAuto ? "ON" : "OFF"); *vc = wifiAuto ? C_ACCENT : C_MUTED; break;
        case 7: snprintf(o, n, "%dx", simSpeed); *vc = C_CYAN; break;
        case 8: snprintf(o, n, "view"); *vc = C_CYAN; break;
        default: snprintf(o, n, "v" FW_VERSION); *vc = C_MUTED; break;
    }
}
static int sysViewH() { return Ht - LIST_TOP - 2; }
static int sysContentH() { return SYS_ROWS * SROW_STEP; }
static int sysMaxScroll() { int m = sysContentH() - sysViewH(); return m > 0 ? m : 0; }
static void subTabGeom(int i, int *x, int *w) { int gap = 6; *w = (Wd - 16 - 2 * gap) / 3; *x = 8 + i * (*w + gap); }
static void drawCloseBtn() {
    int x = CLOSE_X, y = 8, w = 32, h = 26, cx = x + w / 2, cy = y + h / 2;
    fRect(x, y, w, h, 6, C_CARD); dRect(x, y, w, h, 6, C_BORDER);
    for (int o = -1; o <= 1; o++) { line(cx - 6, cy - 6 + o, cx + 6, cy + 6 + o, C_BAD); line(cx - 6, cy + 6 + o, cx + 6, cy - 6 + o, C_BAD); }
}
static void drawSubTabs() {
    const char *nm[3] = {"BMS", "WiFi", "System"};
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
        char val[16]; uint32_t vc; sysVal(i, val, sizeof(val), &vc);
        srowAt(y, SYS_LABEL[i], val, vc);
    }
    if (sysMaxScroll() > 0) {                               // scrollbar
        int tX = Wd - 6, tY = LIST_TOP, tH = sysViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)sysViewH() / sysContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)sysScroll / sysMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
}
static void renderBmsTab() {
    srow(0, "Charge MOSFET", bmsCharge ? "ON" : "OFF", bmsCharge ? C_ACCENT : C_BAD);
    srow(1, "Discharge MOSFET", bmsDischarge ? "ON" : "OFF", bmsDischarge ? C_ACCENT : C_BAD);
    srow(2, "Balancer", bmsBalancer ? "ON" : "OFF", bmsBalancer ? C_ACCENT : C_MUTED);
    srow(3, "Cell count", "4S", C_MUTED);
    srow(4, "Pack capacity", "100 Ah", C_MUTED);
}
static int netRowY(int i) { return 104 + i * 34; }
static int rescanY() { return 104 + WIFI_MAXVIS * 34 + 2; }
static int wifiMaxScroll() { return netCount > WIFI_MAXVIS ? netCount - WIFI_MAXVIS : 0; }
static void renderWifiTab() {
    bool conn = (WiFi.status() == WL_CONNECTED);
    if (wifiScroll > wifiMaxScroll()) wifiScroll = wifiMaxScroll();
    char msg[72];
    if (netCount > WIFI_MAXVIS) snprintf(msg, sizeof(msg), "%s   (%d-%d/%d)", wifiMsg, wifiScroll + 1,
                                         wifiScroll + WIFI_MAXVIS < netCount ? wifiScroll + WIFI_MAXVIS : netCount, netCount);
    else snprintf(msg, sizeof(msg), "%s", wifiMsg);
    lText(msg, 12, 82, F12, conn ? C_ACCENT : C_MUTED);
    int vis = netCount - wifiScroll; if (vis > WIFI_MAXVIS) vis = WIFI_MAXVIS;
    for (int i = 0; i < vis; i++) {
        int idx = wifiScroll + i, y = netRowY(i), x = 8, w = Wd - 16, h = 30;
        fRect(x, y, w, h, 6, C_CARD); dRect(x, y, w, h, 6, C_BORDER);
        lText(netSsid[idx], x + 12, y + 8, F12, C_TEXT);
        int bars = netRssi[idx] > -55 ? 4 : netRssi[idx] > -65 ? 3 : netRssi[idx] > -75 ? 2 : 1;
        for (int b = 0; b < 4; b++) fRect(x + w - 64 + b * 7, y + h - 6 - b * 4, 5, 4 + b * 4, 0, b < bars ? C_ACCENT : C_BORDER);
        if (netEnc[idx]) lText("L", x + w - 18, y + 8, F12, C_WARN);
    }
    if (wifiMaxScroll() > 0) {
        int tX = Wd - 6, tY = netRowY(0), tH = netRowY(WIFI_MAXVIS - 1) + 30 - netRowY(0);
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)WIFI_MAXVIS / netCount); if (thH < 14) thH = 14;
        int thY = tY + (int)((tH - thH) * (float)wifiScroll / wifiMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
    int ry = rescanY();
    if (wifiMaxScroll() > 0) {
        fRect(8, ry, 48, 28, 6, C_CARD); dRect(8, ry, 48, 28, 6, C_BORDER);
        tri(32, ry + 8, 26, ry + 18, 38, ry + 18, wifiScroll > 0 ? C_CYAN : C_BORDER);
        fRect(60, ry, 48, 28, 6, C_CARD); dRect(60, ry, 48, 28, 6, C_BORDER);
        tri(84, ry + 20, 78, ry + 10, 90, ry + 10, wifiScroll < wifiMaxScroll() ? C_CYAN : C_BORDER);
        int rx = 116, rw = Wd - 8 - rx;
        fRect(rx, ry, rw, 28, 6, C_CARD); dRect(rx, ry, rw, 28, 6, C_BORDER);
        cText("Rescan", rx + rw / 2, ry + 14, F16, C_CYAN);
    } else {
        fRect(8, ry, Wd - 16, 28, 6, C_CARD); dRect(8, ry, Wd - 16, 28, 6, C_BORDER);
        cText(netCount ? "Rescan" : "Scan", Wd / 2, ry + 14, F16, C_CYAN);
    }
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
    if (WiFi.status() == WL_CONNECTED) kvLine(lx, &ly, "IP", WiFi.localIP().toString().c_str());
    else kvLine(lx, &ly, "WiFi", "not connected");
    snprintf(b, sizeof(b), "%lu s", (unsigned long)(millis() / 1000)); kvLine(lx, &ly, "Uptime", b);
    lText("BMS info: coming soon", lx, ly + 3, F12, C_MUTED);
    lText("tap to close", x + w - 92, y + h - 18, F12, C_MUTED);
}
static void renderSettings() {
    if (kbActive) { renderKeyboard(); return; }
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

// ---- touch handling (logic) ----
static void handleTap(int x, int y) {
    dirtyFull = true;   // most taps change the whole screen unless noted below
    if (view == V_SETTINGS) {
        if (infoPopup) { infoPopup = false; return; }
        if (kbActive) {
            if (x >= CLOSE_X - 4 && y <= 40) { kbActive = false; return; }
            int code = kbProcess(false, x, y);
            if (code > 0) { if (wifiPassLen < 32) { wifiPass[wifiPassLen++] = (char)code; wifiPass[wifiPassLen] = 0; } }
            else if (code == -1) { if (wifiPassLen > 0) wifiPass[--wifiPassLen] = 0; }
            else if (code == -2) kbMode = (kbMode + 1) % 3;
            else if (code == -4) { kbActive = false; wifiTryConnect(); }
            return;
        }
        if (x >= CLOSE_X - 4 && y <= 40) { view = V_BMS1; renderGraphs(); manualUntil = millis() + PAUSE_MS; lastSwitch = millis(); return; }
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
                case 2: brightness += (x < Wd / 2) ? -10 : 10; brightness = constrain(brightness, 10, 100); setBrightness(brightness); break;
                case 3: autoSleepMin = autoSleepMin == 0 ? 2 : autoSleepMin == 2 ? 5 : autoSleepMin == 5 ? 30 : autoSleepMin == 30 ? 120 : 0; break;
                case 4: tempF = !tempF; break;
                case 5: fmt12 = !fmt12; break;
                case 6: wifiAuto = !wifiAuto; WiFi.setAutoReconnect(wifiAuto); break;
                case 7: simSpeed = simSpeed == 1 ? 2 : simSpeed == 2 ? 5 : 1; break;
                case 8: infoPopup = true; return;   // full redraw for the popup
                default: return;                     // firmware row: no-op
            }
            markRowAt(ry);
        } else if (subTab == ST_BMS) {
            if (y >= srowY(0) && y < srowY(0) + 40) { bmsCharge = !bmsCharge; markRow(0); }
            else if (y >= srowY(1) && y < srowY(1) + 40) { bmsDischarge = !bmsDischarge; markRow(1); }
            else if (y >= srowY(2) && y < srowY(2) + 40) { bmsBalancer = !bmsBalancer; markRow(2); }
        } else {
            int vis = netCount - wifiScroll; if (vis > WIFI_MAXVIS) vis = WIFI_MAXVIS;
            for (int i = 0; i < vis; i++) if (y >= netRowY(i) && y < netRowY(i) + 30) {
                wifiSel = wifiScroll + i;
                if (netEnc[wifiSel]) { wifiPass[0] = 0; wifiPassLen = 0; kbMode = 0; kbActive = true; }
                else wifiTryConnect();
                return;
            }
            int ry = rescanY();
            if (y >= ry && y < ry + 28) {
                if (wifiMaxScroll() > 0) {
                    if (x < 56) { if (wifiScroll > 0) wifiScroll--; }
                    else if (x < 108) { if (wifiScroll < wifiMaxScroll()) wifiScroll++; }
                    else wifiStartScan();
                } else wifiStartScan();
            }
        }
        return;
    }
    // dashboard top bar
    manualUntil = millis() + PAUSE_MS;
    if (y >= 6 && y <= 34) {
        if (x >= TAB1_X && x < TAB1_X + TAB_W) { view = V_BMS1; renderGraphs(); lastSwitch = millis(); }
        else if (x >= TAB2_X && x < TAB2_X + TAB_W) { view = V_BMS2; renderGraphs(); lastSwitch = millis(); }
        else if (x >= BED_X && x < BED_X + BED_W) pendingSleep = true;
        else if (x >= GEAR_X - 4) { view = V_SETTINGS; subTab = ST_SYSTEM; kbActive = false; infoPopup = false; }
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
static void playSleepAnimation() {
    const int cx = Wd / 2, cy = Ht / 2; const int NS = 56;
    float ang[NS], spd[NS], ph[NS];
    for (int i = 0; i < NS; i++) { ang[i] = fmodf(i * 2.39996f, 6.2832f); spd[i] = 0.7f + 0.6f * fabsf(sinf(i * 1.7f)); ph[i] = fmodf(i * 0.137f, 1.0f); }
    float maxR = sqrtf((float)cx * cx + (float)cy * cy);
    uint32_t t0 = millis(); const float DUR = 2600.0f;
    uint16_t bg = c565(C_BG);
    for (;;) {
        float t = (millis() - t0) / DUR; if (t >= 1.0f) break;
        float endT = t > 0.66f ? (t - 0.66f) / 0.34f : 0.0f;
        gfx->fillScreen(bg);
        float warp = t * t * 2.4f + endT * endT * 7.0f;
        for (int i = 0; i < NS; i++) {
            float r = fmodf(ph[i] + warp * spd[i], 1.0f), rr = r * r * maxR;
            float streak = 6.0f + r * 44.0f + endT * 140.0f;
            float rl = rr - streak; if (rl < 0) rl = 0;
            float c = cosf(ang[i]), s = sinf(ang[i]); uint8_t br = (uint8_t)(60 + 180 * r);
            gfx->drawLine(cx + (int)(c * rl), cy + (int)(s * rl), cx + (int)(c * rr), cy + (int)(s * rr), dimC(0x6b, 0x86, 0xff, br));
        }
        float pulse = 0.5f + 0.5f * sinf(t * PI * 4.0f), glowF = 1.0f - endT;
        for (int gg = 4; gg >= 1; gg--) { int rad = (int)((24 + gg * 18 * (0.8f + 0.4f * pulse)) * glowF); if (rad > 1) gfx->fillCircle(cx, cy, rad, dimC(0x3d, 0xf0, 0xa8, (uint8_t)(8 + (4 - gg) * 7))); }
        float scale = 40.0f * (0.78f + 0.42f * sinf(t * PI));
        if (endT > 0) scale *= (1.0f - endT) * (1.0f - endT);
        drawIco(cx, cy, scale, t * 7.8f, t * 5.9f, t * 4.0f, t * 2.4f);
        gfx->flush();
    }
    gfx->fillScreen(gfx->color565(255, 255, 255)); gfx->flush();
    gfx->fillScreen(bg); gfx->flush();
    standby = true;
}

// ============================================================================
//  LVGL glue
// ============================================================================
static uint32_t millis_cb(void) { return millis(); }
static void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, lv_area_get_width(area), lv_area_get_height(area));
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
static bool pressHandled = false, gMoved = false;
static int gStartY = 0, gBaseScroll = 0;
// Keyboard keys act on PRESS (immediate). The System list drag-scrolls on PRESSING.
// Everything else acts on RELEASE — and only if the finger didn't drag — so
// scrolling never accidentally toggles a setting.
static void press_cb(lv_event_t *e) {
    lastActivity = millis();
    if (standby) return;
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    gStartY = p.y; gBaseScroll = sysScroll; gMoved = false;
    if (view == V_SETTINGS && kbActive) { handleTap(p.x, p.y); pressHandled = true; lv_obj_invalidate(scr); }
}
static void pressing_cb(lv_event_t *e) {
    if (standby || pressHandled) return;
    if (!(view == V_SETTINGS && subTab == ST_SYSTEM && !kbActive)) return;
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    int dy = p.y - gStartY;
    if (abs(dy) > 4) gMoved = true;
    if (!gMoved) return;
    int ns = gBaseScroll - dy;
    if (ns < 0) ns = 0; if (ns > sysMaxScroll()) ns = sysMaxScroll();
    if (ns != sysScroll) { sysScroll = ns; lastActivity = millis(); invArea(0, LIST_TOP, Wd - 1, Ht - 1); }
}
static void release_cb(lv_event_t *e) {
    lastActivity = millis();
    if (standby) { standby = false; setBrightness(brightness); lv_obj_invalidate(scr); return; }  // wake
    if (pressHandled) { pressHandled = false; return; }   // keyboard handled on press
    if (gMoved) { gMoved = false; return; }               // was a scroll → don't toggle
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    handleTap(p.x, p.y);
    if (dirtyFull) lv_obj_invalidate(scr);
    else lv_obj_invalidate_area(scr, &dirtyRect);
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
static void barTick_cb(lv_timer_t *t) {
    if (standby || view == V_SETTINGS) return;
    invArea(6, 4, TAB2_X + TAB_W, 36);
}
static void dataTick_cb(lv_timer_t *t) {
    uint32_t now = millis();
    simStep(now);
    if (autoSleepMin > 0 && !standby && now - lastActivity > (uint32_t)autoSleepMin * 60000UL) { pendingSleep = true; return; }
    if (standby || view == V_SETTINGS) return;
    if (autoSwitch && now >= manualUntil && now - lastSwitch >= intervalMs) {
        switchView(view ^ 1); lastSwitch = now;
        invArea(0, 36, Wd - 1, Ht - 1);            // full body: new BMS + new graphs
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

void setup() {
    Serial.begin(115200);
    Serial.setTxTimeoutMs(0);   // never block the loop when no USB host is reading
    delay(300);
    Serial.printf("\n[lvgl] boot — LVGL %d.%d.%d\n", lv_version_major(), lv_version_minor(), lv_version_patch());

    if (!gfx->begin(40000000UL)) Serial.println("[lvgl] display init FAILED");
    gfx->fillScreen(0x0000);
    ledcAttach(TFT_BL, BL_CH_FREQ, BL_CH_RES);
    setBrightness(brightness);

    touch.begin(); touch.setRotation(TFT_rot);
    touch.enOffsetCorrection(true);
    touch.setOffsets(Touch_X_min, Touch_X_max, TFT_res_W - 1, Touch_Y_min, Touch_Y_max, TFT_res_H - 1);

    lv_init();
    lv_tick_set_cb(millis_cb);
    // Larger draw buffer => fewer render chunks => draw_cb runs far fewer times
    // per full repaint (was /10 = 10 chunks; /4 = ~4) => snappier taps/switches.
    uint32_t w = gfx->width(), h = gfx->height(), bufSize = w * h / 4;
    lv_color_t *buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
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
    void *pb = heap_caps_malloc(LV_CANVAS_BUF_SIZE(POW_W, POW_H, 16, LV_DRAW_BUF_STRIDE_ALIGN), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    void *cb = heap_caps_malloc(LV_CANVAS_BUF_SIZE(CAP_W, CAP_H, 16, LV_DRAW_BUF_STRIDE_ALIGN), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    lv_canvas_set_buffer(powCv, pb, POW_W, POW_H, LV_COLOR_FORMAT_RGB565);
    lv_canvas_set_buffer(capCv, cb, CAP_W, CAP_H, LV_COLOR_FORMAT_RGB565);

    // auto-reconnect to the last saved WiFi
    WiFi.mode(WIFI_STA); WiFi.setAutoReconnect(true);
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
    renderGraphs();
    lastActivity = millis();
    lv_obj_invalidate(scr);                     // first full paint
    // Refresh rates kept modest so the panel isn't flushed at max rate (each full
    // flush ~40ms blocks touch polling). Between ticks lv_task_handler runs every
    // ~1ms and polls touch → responsive input.
    lv_timer_create(barTick_cb, 120, NULL);    // auto-switch progress bar
    lv_timer_create(dataTick_cb, 300, NULL);   // live values
    lv_timer_create(wifiTick_cb, 500, NULL);
    Serial.println("[lvgl] dashboard ready");
}

void loop() {
    lv_task_handler();
    if (pendingSleep) {
        pendingSleep = false;
        playSleepAnimation();   // blocking, draws + flushes itself; sets standby
        gfxDirty = false;
        return;
    }
    if (gfxDirty) { gfx->flush(); gfxDirty = false; }
    delay(1);
}
