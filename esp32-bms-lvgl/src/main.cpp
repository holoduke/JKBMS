// JK BMS LVGL dashboard — Guition JC3248W535.
// Phase 2a: main dashboard in LVGL (tabs + icons, SOC arc, V/temps/stats cards,
// cell bars, power + capacity charts) with simulated data + auto-switch.
#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <math.h>
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"

// ---- palette ----
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
static int active = 0;
static bool autoSwitch = true;
static uint32_t lastSwitch = 0;

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

// ---- LVGL glue ----
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

// ---- widgets (updated each tick) ----
static lv_obj_t *tabBtn[2], *wifiIcon, *clockLbl;
static lv_obj_t *socArc, *socPct, *powLbl, *stateLbl;
static lv_obj_t *voltVal, *tempVal[3], *statVal[3];
static lv_obj_t *cellBar[NCELLS], *cellVal[NCELLS];
static lv_obj_t *powChart, *capChart;
static lv_chart_series_t *powSer, *capSer;

static lv_obj_t *mkLabel(lv_obj_t *par, const char *txt, const lv_font_t *font, uint32_t color) {
    lv_obj_t *l = lv_label_create(par);
    lv_label_set_text(l, txt);
    lv_obj_set_style_text_font(l, font, 0);
    lv_obj_set_style_text_color(l, lv_color_hex(color), 0);
    return l;
}
static lv_obj_t *mkCard(lv_obj_t *par, int x, int y, int w, int h) {
    lv_obj_t *o = lv_obj_create(par);
    lv_obj_set_pos(o, x, y); lv_obj_set_size(o, w, h);
    lv_obj_set_style_bg_color(o, lv_color_hex(C_CARD), 0);
    lv_obj_set_style_border_color(o, lv_color_hex(C_BORDER), 0);
    lv_obj_set_style_border_width(o, 1, 0);
    lv_obj_set_style_radius(o, 8, 0);
    lv_obj_set_style_pad_all(o, 6, 0);
    lv_obj_remove_flag(o, LV_OBJ_FLAG_SCROLLABLE);
    return o;
}

static void setActiveTab(int t) {
    active = t;
    for (int i = 0; i < 2; i++) {
        bool on = (i == t);
        lv_obj_set_style_bg_color(tabBtn[i], lv_color_hex(on ? C_ACCENT : C_CARD), 0);
        lv_obj_set_style_text_color(lv_obj_get_child(tabBtn[i], 0), lv_color_hex(on ? C_BG : C_MUTED), 0);
    }
}
static void tab_cb(lv_event_t *e) { setActiveTab((int)(intptr_t)lv_event_get_user_data(e)); autoSwitch = false; lastSwitch = millis(); }

static void reloadCharts() {
    const Bms &b = bms[active];
    int n = b.capCount;
    lv_chart_set_point_count(capChart, n);
    lv_chart_set_point_count(powChart, n);
    int32_t *cy = lv_chart_get_y_array(capChart, capSer);
    int32_t *py = lv_chart_get_y_array(powChart, powSer);
    for (int i = 0; i < n; i++) { cy[i] = (int32_t)b.cap[i]; py[i] = (int32_t)b.pwr[i]; }
    lv_chart_refresh(capChart);
    lv_chart_refresh(powChart);
}

static void updateLive() {
    const Bms &b = bms[active];
    char buf[24];
    lv_arc_set_value(socArc, (int)(b.soc + 0.5f));
    snprintf(buf, sizeof(buf), "%d%%", (int)(b.soc + 0.5f)); lv_label_set_text(socPct, buf);
    bool chg = b.i >= 0;
    snprintf(buf, sizeof(buf), "%s %.0f W", chg ? LV_SYMBOL_UP : LV_SYMBOL_DOWN, fabsf(b.v * b.i));
    lv_label_set_text(powLbl, buf);
    lv_obj_set_style_text_color(powLbl, lv_color_hex(chg ? C_ACCENT : C_WARN), 0);
    snprintf(buf, sizeof(buf), "%s  %.1f A", chg ? "CHARGING" : "DISCHARGING", fabsf(b.i));
    lv_label_set_text(stateLbl, buf);

    snprintf(buf, sizeof(buf), "%.1f", b.v); lv_label_set_text(voltVal, buf);
    float tv[3] = {b.tMos, b.tp1, b.tp2};
    for (int i = 0; i < 3; i++) { snprintf(buf, sizeof(buf), "%.0f" "\xC2\xB0", tv[i]); lv_label_set_text(tempVal[i], buf); }
    snprintf(buf, sizeof(buf), "%.0fW", b.peakChg); lv_label_set_text(statVal[0], buf);
    snprintf(buf, sizeof(buf), "%.0fW", b.peakDis); lv_label_set_text(statVal[1], buf);
    uint32_t m = millis() / 60000; snprintf(buf, sizeof(buf), "%luh%02lu", (unsigned long)(m / 60), (unsigned long)(m % 60));
    lv_label_set_text(statVal[2], buf);

    float lo = 9, hi = 0;
    for (int i = 0; i < NCELLS; i++) { if (b.cell[i] < lo) lo = b.cell[i]; if (b.cell[i] > hi) hi = b.cell[i]; }
    for (int i = 0; i < NCELLS; i++) {
        lv_bar_set_value(cellBar[i], (int)((b.cell[i] - 3.0f) / 0.6f * 100), LV_ANIM_OFF);
        uint32_t c = (b.cell[i] <= lo) ? C_CYAN : (b.cell[i] >= hi) ? C_WARN : C_ACCENT;
        lv_obj_set_style_bg_color(cellBar[i], lv_color_hex(c), LV_PART_INDICATOR);
        snprintf(buf, sizeof(buf), "%.2f", b.cell[i]); lv_label_set_text(cellVal[i], buf);
    }
}

static void tick_cb(lv_timer_t *t) {
    uint32_t now = millis();
    simStep(now);
    if (autoSwitch && now - lastSwitch >= 5000) { setActiveTab(active ^ 1); lastSwitch = now; reloadCharts(); }
    updateLive();
    // clock
    struct tm ti;
    if (getLocalTime(&ti, 0)) { char ts[6]; snprintf(ts, sizeof(ts), "%02d:%02d", ti.tm_hour, ti.tm_min); lv_label_set_text(clockLbl, ts); }
}

static lv_obj_t *mkIconBtn(lv_obj_t *par, const char *sym, int x) {
    lv_obj_t *b = lv_button_create(par);
    lv_obj_set_size(b, 34, 30); lv_obj_set_pos(b, x, 3);
    lv_obj_set_style_bg_color(b, lv_color_hex(C_CARD), 0);
    lv_obj_set_style_border_color(b, lv_color_hex(C_BORDER), 0);
    lv_obj_set_style_border_width(b, 1, 0);
    lv_obj_t *l = mkLabel(b, sym, &lv_font_montserrat_16, C_MUTED); lv_obj_center(l);
    return b;
}

static void build_dashboard() {
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(C_BG), 0);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(scr, 0, 0);

    // header: BMS tabs
    for (int i = 0; i < 2; i++) {
        tabBtn[i] = lv_button_create(scr);
        lv_obj_set_size(tabBtn[i], 104, 30); lv_obj_set_pos(tabBtn[i], 8 + i * 112, 4);
        lv_obj_set_style_radius(tabBtn[i], 8, 0);
        char nm[8]; snprintf(nm, sizeof(nm), "BMS %d", i + 1);
        lv_obj_t *l = mkLabel(tabBtn[i], nm, &lv_font_montserrat_16, C_MUTED); lv_obj_center(l);
        lv_obj_add_event_cb(tabBtn[i], tab_cb, LV_EVENT_CLICKED, (void *)(intptr_t)i);
    }
    wifiIcon = mkLabel(scr, LV_SYMBOL_WIFI, &lv_font_montserrat_16, C_ACCENT); lv_obj_set_pos(wifiIcon, 244, 10);
    lv_obj_add_flag(wifiIcon, LV_OBJ_FLAG_HIDDEN);
    clockLbl = mkLabel(scr, "", &lv_font_montserrat_16, C_TEXT); lv_obj_set_pos(clockLbl, 300, 10);
    mkIconBtn(scr, LV_SYMBOL_POWER, 398);     // sleep (wired in phase 2b)
    mkIconBtn(scr, LV_SYMBOL_SETTINGS, 438);  // settings (wired in phase 2b)

    // SOC arc (left)
    socArc = lv_arc_create(scr);
    lv_obj_set_size(socArc, 168, 168); lv_obj_set_pos(socArc, 12, 70);
    lv_arc_set_rotation(socArc, 135); lv_arc_set_bg_angles(socArc, 0, 270);
    lv_arc_set_range(socArc, 0, 100);
    lv_obj_remove_flag(socArc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(socArc, lv_color_hex(C_BORDER), LV_PART_MAIN);
    lv_obj_set_style_arc_color(socArc, lv_color_hex(C_ACCENT), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(socArc, 12, LV_PART_MAIN);
    lv_obj_set_style_arc_width(socArc, 12, LV_PART_INDICATOR);
    lv_obj_remove_style(socArc, NULL, LV_PART_KNOB);
    socPct = mkLabel(scr, "--%", &lv_font_montserrat_28, C_TEXT);
    lv_obj_align_to(socPct, socArc, LV_ALIGN_CENTER, 0, -6);
    powLbl = mkLabel(scr, "-- W", &lv_font_montserrat_20, C_ACCENT);
    lv_obj_set_pos(powLbl, 40, 246);
    stateLbl = mkLabel(scr, "", &lv_font_montserrat_12, C_MUTED);
    lv_obj_set_pos(stateLbl, 24, 274);

    // right column: voltage / temps / stats cards
    const int rx = 200, rw = 272;
    lv_obj_t *cv = mkCard(scr, rx, 40, 84, 70);
    mkLabel(cv, "VOLTAGE", &lv_font_montserrat_12, C_MUTED);
    voltVal = mkLabel(cv, "--.-", &lv_font_montserrat_20, C_TEXT); lv_obj_set_pos(voltVal, 0, 24);
    lv_obj_set_pos(mkLabel(cv, "V", &lv_font_montserrat_12, C_MUTED), 0, 48);

    lv_obj_t *cs = mkCard(scr, rx + 94, 40, 84, 70);
    const char *sl[3] = {"PK+", "PK-", "UP"};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *a = mkLabel(cs, sl[i], &lv_font_montserrat_12, C_MUTED); lv_obj_set_pos(a, 0, i * 18);
        statVal[i] = mkLabel(cs, "--", &lv_font_montserrat_12, (i == 0) ? C_ACCENT : (i == 1) ? C_WARN : C_TEXT);
        lv_obj_set_pos(statVal[i], 34, i * 18);
    }
    lv_obj_t *ct = mkCard(scr, rx + 188, 40, 84, 70);
    const char *tl[3] = {"MOS", "T1", "T2"};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *a = mkLabel(ct, tl[i], &lv_font_montserrat_12, C_MUTED); lv_obj_set_pos(a, 0, i * 18);
        tempVal[i] = mkLabel(ct, "--", &lv_font_montserrat_16, C_ACCENT); lv_obj_set_pos(tempVal[i], 34, i * 18 - 2);
    }

    // cells card (4 horizontal bars)
    lv_obj_t *cc = mkCard(scr, rx, 118, 84 + 94, 86);   // spans two columns
    mkLabel(cc, "CELLS", &lv_font_montserrat_12, C_MUTED);
    for (int i = 0; i < NCELLS; i++) {
        int16_t yy = 16 + i * 15;
        const char *cn[NCELLS] = {"C1", "C2", "C3", "C4"};
        lv_obj_set_pos(mkLabel(cc, cn[i], &lv_font_montserrat_12, C_MUTED), 0, yy);
        cellBar[i] = lv_bar_create(cc);
        lv_obj_set_size(cellBar[i], 78, 8); lv_obj_set_pos(cellBar[i], 24, yy + 1);
        lv_bar_set_range(cellBar[i], 0, 100);
        lv_obj_set_style_bg_color(cellBar[i], lv_color_hex(C_BORDER), LV_PART_MAIN);
        lv_obj_set_style_bg_color(cellBar[i], lv_color_hex(C_ACCENT), LV_PART_INDICATOR);
        cellVal[i] = mkLabel(cc, "-.--", &lv_font_montserrat_12, C_TEXT); lv_obj_set_pos(cellVal[i], 108, yy);
    }

    // power + capacity charts (right) — use full right width
    lv_obj_t *pc = mkCard(scr, rx, 212, 132, 96);
    mkLabel(pc, "POWER W", &lv_font_montserrat_12, C_MUTED);
    powChart = lv_chart_create(pc);
    lv_obj_set_size(powChart, 116, 56); lv_obj_set_pos(powChart, 0, 18);
    lv_chart_set_type(powChart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(powChart, 3, 0);
    lv_chart_set_range(powChart, LV_CHART_AXIS_PRIMARY_Y, -260, 260);
    lv_obj_set_style_size(powChart, 0, 0, LV_PART_INDICATOR);   // hide points
    powSer = lv_chart_add_series(powChart, lv_color_hex(C_CYAN), LV_CHART_AXIS_PRIMARY_Y);

    lv_obj_t *capc = mkCard(scr, rx + 140, 212, 132, 96);
    mkLabel(capc, "CAPACITY %", &lv_font_montserrat_12, C_MUTED);
    capChart = lv_chart_create(capc);
    lv_obj_set_size(capChart, 116, 56); lv_obj_set_pos(capChart, 0, 18);
    lv_chart_set_type(capChart, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(capChart, 3, 0);
    lv_chart_set_range(capChart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_obj_set_style_size(capChart, 0, 0, LV_PART_INDICATOR);
    capSer = lv_chart_add_series(capChart, lv_color_hex(C_ACCENT), LV_CHART_AXIS_PRIMARY_Y);

    setActiveTab(0);
    reloadCharts();
    updateLive();
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

    simInit();
    build_dashboard();
    lv_timer_create(tick_cb, 400, NULL);
    Serial.println("[lvgl] dashboard ready");
}

void loop() {
    lv_task_handler();
    if (gfxDirty) { gfx->flush(); gfxDirty = false; }
    delay(5);
}
