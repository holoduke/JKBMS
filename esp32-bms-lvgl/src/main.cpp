// JK BMS LVGL dashboard — Guition JC3248W535 (480x320 landscape).
// Faithful pixel-for-pixel reproduction of the esp32-bms/ Arduino_GFX dashboard,
// drawn through LVGL's vector draw API (so the text is anti-aliased). Every shape,
// coordinate and colour matches the original; only the fonts are nicer. Data is
// simulated; tabs auto-switch (BMS1<->BMS2), a tap pauses it for 30s.
#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <time.h>
#include <math.h>
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"

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
static int view = 0;                 // 0=BMS1, 1=BMS2
static uint32_t lastSwitch = 0, manualUntil = 0;
static const uint32_t intervalMs = 5000, PAUSE_MS = 30000;

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
    float s = nowMs / 1000.0f;
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
#define F12 &lv_font_montserrat_12
#define F14 &lv_font_montserrat_14
#define F16 &lv_font_montserrat_16
#define F20 &lv_font_montserrat_20
#define F28 &lv_font_montserrat_28
#define F48 &lv_font_montserrat_48

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
    lText(val, x + 8, y + 24, F20, valCol);
    lText(unit, x + 8, y + h - 16, F12, C_MUTED);
}
static void drawTempsTile(int x, int y, int w, int h, float mos, float t1, float t2) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    const char *lbl[3] = {"MOS", "T1", "T2"}; float v[3] = {mos, t1, t2};
    for (int r = 0; r < 3; r++) {
        int ry = y + 9 + r * 22;
        lText(lbl[r], x + 8, ry + 3, F12, C_MUTED);
        char buf[6]; snprintf(buf, sizeof(buf), "%.0f", v[r]);
        lText(buf, x + 34, ry, F16, tempColor(v[r]));
        lText("C", x + 38 + textW(buf, F16), ry + 4, F12, C_MUTED);
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
        int ry = y + 10 + r * 20;
        lText(lbl[r], x + 8, ry, F12, C_MUTED);
        lText(val[r], x + w - textW(val[r], F12) - 8, ry, F12, vc[r]);
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
    lText("POWER  W", x + 8, y + 6, F12, C_MUTED);
    const int lblW = 26, gx = x + 8 + lblW, gy = y + 22, gw = w - 14 - lblW, gh = h - 38, base = gy + gh;
    int cnt = (b.capCount < 2) ? 2 : (b.capCount > NCAP ? NCAP : b.capCount);
    float lo = 1e9f, hi = -1e9f;
    for (int i = 0; i < cnt; i++) { float v = b.pwr[i]; if (v < lo) lo = v; if (v > hi) hi = v; }
    if (lo > 0) lo = 0; if (hi < 0) hi = 0; if (hi - lo < 1) hi = lo + 1;
    int zeroY = base - (int)((0 - lo) / (hi - lo) * gh);
    for (int k = 0; k < 5; k++) line(gx + (int)((float)k / 4 * gw), gy, gx + (int)((float)k / 4 * gw), gy + gh, C_BORDER, 170);
    line(gx, zeroY, gx + gw, zeroY, C_BORDER, 170);
    char lb[8];
    snprintf(lb, sizeof(lb), "%d", (int)hi); lText(lb, x + 4, gy - 4, F12, C_MUTED);
    lText("0", x + 4, zeroY - 8, F12, C_MUTED);
    snprintf(lb, sizeof(lb), "%d", (int)lo); lText(lb, x + 4, base - 10, F12, C_MUTED);
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
        if (k == 0) lText(lbl, fx, base + 6, F12, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F12), base + 6, F12, C_MUTED);
        else cText(lbl, fx, base + 12, F12, C_MUTED);
    }
}
static void drawCapacityGraph(int x, int y, int w, int h, const Bms &b) {
    fRect(x, y, w, h, 8, C_CARD); dRect(x, y, w, h, 8, C_BORDER);
    char hdr[28];
    if (b.capSpanDays >= 2.0f) snprintf(hdr, sizeof(hdr), "CAPACITY   %.0f days", b.capSpanDays);
    else snprintf(hdr, sizeof(hdr), "CAPACITY   24 hours");
    lText(hdr, x + 8, y + 7, F12, C_MUTED);
    const int lblW = 22, gx = x + 10 + lblW, gy = y + 24, gw = w - 20 - lblW, gh = h - 42, base = gy + gh;
    for (int p = 0; p <= 100; p += 50) {
        int yy = base - (int)(p / 100.0f * gh);
        line(gx, yy, gx + gw, yy, C_BORDER, 170);
        char lb[5]; snprintf(lb, sizeof(lb), "%d", p); lText(lb, x + 6, yy - 8, F12, C_MUTED);
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
        if (k == 0) lText(lbl, fx, base + 6, F12, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F12), base + 6, F12, C_MUTED);
        else cText(lbl, fx, base + 12, F12, C_MUTED);
    }
}

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
    char vbuf[8]; snprintf(vbuf, sizeof(vbuf), "%.1f", b.v);
    const int ty = 40, th = 70, gap = 8, tw = (rw - 2 * gap) / 3;
    drawTile(rx, ty, tw, th, "VOLTAGE", vbuf, "VOLT", C_TEXT);
    drawStatsTile(rx + tw + gap, ty, tw, th, b.peakChg, b.peakDis, now / 1000);
    drawTempsTile(rx + 2 * (tw + gap), ty, tw, th, b.tMos, b.tp1, b.tp2);

    const int halfW = (rw - 8) / 2;
    drawCells(rx, 120, halfW, 86, b);
    drawPowerGraph(rx + halfW + 8, 120, rw - halfW - 8, 86, b);
    drawCapacityGraph(rx, 216, rw, 96, b);
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
static void draw_cb(lv_event_t *e) {
    L = lv_event_get_layer(e);
    tpi = 0;
    renderBms();
}
static void click_cb(lv_event_t *e) {
    lv_indev_t *indev = lv_indev_active();
    if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    uint32_t now = millis();
    if (p.y >= 6 && p.y <= 34) {
        if (p.x >= TAB1_X && p.x <= TAB1_X + TAB_W) { view = 0; manualUntil = now + PAUSE_MS; lastSwitch = now; }
        else if (p.x >= TAB2_X && p.x <= TAB2_X + TAB_W) { view = 1; manualUntil = now + PAUSE_MS; lastSwitch = now; }
        // gear/bed (settings + sleep) wired in phase 2b
    }
    lv_obj_invalidate(scr);
}
static void tick_cb(lv_timer_t *t) {
    uint32_t now = millis();
    simStep(now);
    if (now >= manualUntil && now - lastSwitch >= intervalMs) { view ^= 1; lastSwitch = now; }
    lv_obj_invalidate(scr);
}

void setup() {
    Serial.begin(115200);
    delay(300);
    Serial.printf("\n[lvgl] boot — LVGL %d.%d.%d\n", lv_version_major(), lv_version_minor(), lv_version_patch());

    if (!gfx->begin(40000000UL)) Serial.println("[lvgl] display init FAILED");
    gfx->fillScreen(0x0000);
    pinMode(TFT_BL, OUTPUT); digitalWrite(TFT_BL, HIGH);

    touch.begin(); touch.setRotation(TFT_rot);
    touch.enOffsetCorrection(true);
    touch.setOffsets(Touch_X_min, Touch_X_max, TFT_res_W - 1, Touch_Y_min, Touch_Y_max, TFT_res_H - 1);

    lv_init();
    lv_tick_set_cb(millis_cb);
    uint32_t w = gfx->width(), h = gfx->height(), bufSize = w * h / 10;
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
    lv_obj_add_event_cb(scr, click_cb, LV_EVENT_CLICKED, NULL);

    simInit();
    lv_timer_create(tick_cb, 250, NULL);
    Serial.println("[lvgl] dashboard ready");
}

void loop() {
    lv_task_handler();
    if (gfxDirty) { gfx->flush(); gfxDirty = false; }
    delay(5);
}
