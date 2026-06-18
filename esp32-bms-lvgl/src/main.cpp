// JK BMS LVGL dashboard — Guition JC3248W535.
// Phase 1: bring up LVGL 9 (display + touch) with a test screen to verify
// rendering, anti-aliased fonts, and touch. Phase 2 replaces this with the
// full dashboard.
#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"

Arduino_DataBus *bus = new Arduino_ESP32QSPI(TFT_CS, TFT_SCK, TFT_SDA0, TFT_SDA1, TFT_SDA2, TFT_SDA3);
Arduino_GFX *g = new Arduino_AXS15231B(bus, GFX_NOT_DEFINED, 0, false, TFT_res_W, TFT_res_H);
Arduino_Canvas *gfx = new Arduino_Canvas(TFT_res_W, TFT_res_H, g, 0, 0, TFT_rot);
AXS15231B_Touch touch(Touch_SCL, Touch_SDA, Touch_INT, Touch_ADDR, TFT_rot);

static bool gfxDirty = false;

static uint32_t millis_cb(void) { return millis(); }

static void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = lv_area_get_width(area), h = lv_area_get_height(area);
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
    gfxDirty = true;                       // canvas changed -> push to panel in loop()
    lv_disp_flush_ready(disp);
}

static void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    uint16_t x, y;
    if (touch.touched()) {
        touch.readData(&x, &y);
        data->point.x = x; data->point.y = y;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

// ---- test screen ----
static lv_obj_t *tapLabel;
static int tapCount = 0;
static void btn_cb(lv_event_t *e) {
    char b[24]; snprintf(b, sizeof(b), "Tapped: %d", ++tapCount);
    lv_label_set_text(tapLabel, b);
}

static void build_test_ui() {
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x04060c), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "JK BMS  -  LVGL");
    lv_obj_set_style_text_color(title, lv_color_hex(0xeaf2fb), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 12);

    // SOC-style arc gauge
    lv_obj_t *arc = lv_arc_create(scr);
    lv_obj_set_size(arc, 160, 160);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_range(arc, 0, 100);
    lv_arc_set_value(arc, 72);
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0x2a3342), LV_PART_MAIN);
    lv_obj_set_style_arc_color(arc, lv_color_hex(0x3df0a8), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, 14, LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 14, LV_PART_INDICATOR);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_obj_align(arc, LV_ALIGN_LEFT_MID, 20, 10);

    lv_obj_t *pct = lv_label_create(scr);
    lv_label_set_text(pct, "72%");
    lv_obj_set_style_text_color(pct, lv_color_hex(0xeaf2fb), 0);
    lv_obj_set_style_text_font(pct, &lv_font_montserrat_28, 0);
    lv_obj_align_to(pct, arc, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *btn = lv_button_create(scr);
    lv_obj_set_size(btn, 150, 60);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x3df0a8), 0);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_RIGHT, -24, -30);
    lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_CLICKED, NULL);
    tapLabel = lv_label_create(btn);
    lv_label_set_text(tapLabel, "Tap me");
    lv_obj_set_style_text_color(tapLabel, lv_color_hex(0x04060c), 0);
    lv_obj_set_style_text_font(tapLabel, &lv_font_montserrat_16, 0);
    lv_obj_center(tapLabel);
}

void setup() {
    Serial.begin(115200);
    delay(300);
    Serial.printf("\n[lvgl] boot — LVGL %d.%d.%d\n", lv_version_major(), lv_version_minor(), lv_version_patch());

    if (!gfx->begin(40000000UL)) { Serial.println("[lvgl] display init FAILED"); }
    gfx->fillScreen(0x0000);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    touch.begin();
    touch.setRotation(TFT_rot);
    touch.enOffsetCorrection(true);
    touch.setOffsets(Touch_X_min, Touch_X_max, TFT_res_W - 1, Touch_Y_min, Touch_Y_max, TFT_res_H - 1);

    lv_init();
    lv_tick_set_cb(millis_cb);

    uint32_t w = gfx->width(), h = gfx->height();
    uint32_t bufSize = w * h / 10;
    lv_color_t *buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!buf) { Serial.println("[lvgl] draw buffer alloc FAILED"); return; }

    lv_display_t *disp = lv_display_create(w, h);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, buf, NULL, bufSize * 2, LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touchpad_read);

    build_test_ui();
    Serial.println("[lvgl] ready");
}

void loop() {
    lv_task_handler();
    if (gfxDirty) { gfx->flush(); gfxDirty = false; }   // push canvas to panel only when LVGL redrew
    delay(5);
}
