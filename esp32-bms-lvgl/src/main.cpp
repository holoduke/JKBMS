// JK BMS LVGL dashboard — Guition JC3248W535 (480x320 landscape).
// Reads one or two JK-BMS packs over Modbus-RTU (each on its own UART) and renders
// the dashboard through LVGL's vector draw API (anti-aliased text). Tabs auto-switch
// between connected packs; a tap pauses the rotation for 30s. A demo mode (Settings)
// substitutes simulated data when no real pack is wired up.
//
// Single translation unit: feature code lives in the .h files #included below, in
// dependency order (shared globals, no separate compilation — include order matters).
#include <Arduino.h>
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <WiFi.h>
#include <esp_mac.h>
#include <Preferences.h>
#include <time.h>
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <esp_random.h>
#include <esp_task_wdt.h>   // hardware task watchdog → auto-reboot if the UI task wedges
#include "pincfg.h"
#include "dispcfg.h"
#include "AXS15231B_touch.h"
#include "i18n.h"          // language tables + T(key); g_lang persisted in NVS

#include "state.h"
#include "bms.h"
#include "helpers.h"
#include "draw.h"
#include "widgets.h"
#include "settings_ui.h"
#include "wifi_nvs.h"
#include "touch.h"
#include "fx.h"
#include "events.h"
#include "web_portal.h"   // monitor + controls + OTA
#include "mqtt.h"         // MQTT + Home Assistant
#include "weather.h"      // geo-IP + Open-Meteo
#include "alerts.h"       // threshold push alerts
#include "ota.h"          // GitHub release self-update
void setup() {
    Serial.begin(115200);
    Serial.setTxTimeoutMs(0);   // never block the loop when no USB host is reading
    delay(300);
    Serial.printf("\n[lvgl] boot — LVGL %d.%d.%d\n", lv_version_major(), lv_version_minor(), lv_version_patch());
    loadSettings();             // restore saved settings before they're used (brightness, wifi, …)
    applyTz();                  // apply the saved timezone to this (render/loop) task — newlib TZ is per-task
    if (freshWebPass) saveSettings();   // first boot → lock in the randomly-generated default password
    if (lockAfterSec > 0 && lockPin[0]) locked = true;
    loadHistory();              // restore the persisted graph history (survives reboot)
    loadWeather();              // restore the last forecast → shows immediately (greyed as stale until a live fetch)
    loadSoh();                  // restore the long-term capacity/SoH trend + baseline

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
    initScriptFonts();   // build Arabic/Hindi fonts with a Montserrat fallback for Latin/digits
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
    // graph canvases live in PSRAM (re-rendered only every few seconds, not per frame) →
    // keeps ~59KB of internal heap free so the Open-Meteo TLS handshake (two ~16KB mbedTLS
    // record buffers) can allocate without fragmenting against the 75KB internal draw buffer.
    void *pb = heap_caps_malloc(LV_CANVAS_BUF_SIZE(POW_W, POW_H, 16, LV_DRAW_BUF_STRIDE_ALIGN), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    void *cb = heap_caps_malloc(LV_CANVAS_BUF_SIZE(CAP_W, CAP_H, 16, LV_DRAW_BUF_STRIDE_ALIGN), MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
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
        strncpy(connPass, pw.c_str(), sizeof(connPass) - 1); connPass[sizeof(connPass) - 1] = 0;
        wifiSaved = true; WiFi.begin(connSsid, connPass);
        snprintf(wifiMsg, sizeof(wifiMsg), "%s %s...", T(K_WIFI_CONNECTING), connSsid);
    }

    simInit();
    // Live BMSes over Modbus-RTU, each on its own UART at address 1:
    //   BMS1 = UART1 (RX=IO18, TX=IO17), BMS2 = UART2 (RX=IO15, TX=IO16).
    // bmsRead() flips bmsLive[] per a valid reply; a silent pack shows a red tab +
    // "Offline". Skipped entirely in demo mode.
    busMux = xSemaphoreCreateMutex();   // serialise Modbus access (UI-core poll vs. net-core MQTT writes)
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
    barTimer = lv_timer_create(barTick_cb, 250, NULL);    // auto-switch progress bar (250ms is smooth enough at the 24fps ceiling)
    dataTimer = lv_timer_create(dataTick_cb, 220, NULL);  // live values (+ power-save supervisor)
    lv_timer_create(fling_cb, 30, NULL);                  // momentum scroll
    lv_timer_create(spin_cb, 50, NULL);                   // charging spinner (~20fps — leaves more flush-free windows for touch polling)
    lv_timer_create(wifiTick_cb, 500, NULL);
    lv_timer_create(bmsPoll_cb, 500, NULL);               // react to core-0 poll results (reconnect repaint, graph refresh)
    // Blocking network I/O on core 0, away from the render/touch core (1). 10 KB stack
    // covers the mbedTLS handshake; low priority so it never preempts the UI.
    xTaskCreatePinnedToCore(netTask, "net", 10240, NULL, 1, NULL, 0);

    // Hardware task watchdog on the UI task (this loopTask, core 1). If rendering/touch ever
    // wedges for >20s, the chip panics and reboots — the device self-recovers unattended.
    // Only the UI task is watched: the core-0 netTask intentionally makes long blocking calls
    // (TLS handshakes, OTA flash) and selfUpdate() runs there while loopTask keeps drawing the
    // progress bar, so watching netTask would false-trip. 20s clears every legit UI stall
    // (full-canvas flush ~40ms, sleep animation ~1.5s, NVS writes ~tens of ms).
    esp_task_wdt_config_t wdtCfg = { .timeout_ms = 20000, .idle_core_mask = 0, .trigger_panic = true };
    if (esp_task_wdt_init(&wdtCfg) == ESP_ERR_INVALID_STATE) esp_task_wdt_reconfigure(&wdtCfg);   // Arduino may have inited it already
    esp_task_wdt_add(NULL);   // subscribe loopTask
    Serial.println("[lvgl] dashboard ready");
}

void loop() {
    static bool wdtOn = true;
    if (otaActive) {   // an OTA flash blocks here for tens of seconds → unsubscribe so the WDT can't bite mid-flash
        if (wdtOn) { esp_task_wdt_delete(NULL); wdtOn = false; }
        ArduinoOTA.handle(); return;   // OTA in progress → give it the whole CPU
    }
    if (!wdtOn) { esp_task_wdt_add(NULL); wdtOn = true; }   // OTA ended or failed → re-arm the watchdog
    esp_task_wdt_reset();   // feed: UI task is alive
    lv_task_handler();
    webLoop();   // serve the web portal + handle OTA (no-op until WiFi connects)
    // MQTT / weather / alerts now run on the core-0 netTask so their blocking socket
    // I/O can't stall rendering or touch — see netTask().
    if (pendingSleep) {
        pendingSleep = false;
        playSleepAnimation();   // blocking, draws + flushes itself; sets standby
        gfxDirty = false;
        return;
    }
    // animated "no battery" idle screen (chosen in Settings) — owns the canvas directly
    static bool wasIdle = false;
    bool idle = idleActiveNow();
    saverShowing = idle;                             // so a wake-tap can be swallowed (see press/release_cb)
    if (!idle && wasIdle) lv_obj_invalidate(scr);   // leaving idle → repaint the real UI
    wasIdle = idle;
    if (idle) {
        static uint32_t lastFrame = 0; uint32_t now = millis();
        uint32_t period = (appliedB <= DIM_LEVEL) ? 250 : 80;   // ~4 fps once dimmed (motion invisible), else ~12 fps
        if (now - lastFrame >= period) { lastFrame = now; renderIdleFrame(); gfx->flush(); gfxDirty = false; }
        delay(1); return;
    }
    if (gfxDirty) {
        uint32_t t = micros(); gfx->flush(); g_flushUs = micros() - t; gfxDirty = false;
        static uint32_t fc = 0, fsec = 0; fc++;
        uint32_t ms = millis(); if (ms - fsec >= 1000) { g_fps = fc; fc = 0; fsec = ms; }
    }
    delay(1);
}
