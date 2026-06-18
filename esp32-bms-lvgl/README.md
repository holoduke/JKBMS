# esp32-bms-lvgl — LVGL version of the JK BMS dashboard

A rebuild of the `esp32-bms/` dashboard using **LVGL 9** for anti-aliased fonts,
smooth scrolling, gestures, and real widgets. Same hardware, nicer UI.

- **Board:** Guition JC3248W535 (ESP32-S3-N16R8, 320×480 QSPI AXS15231B)
- **Stack:** PlatformIO + pioarduino (arduino-esp32 3.3.x) + Arduino_GFX (display
  driver) + **LVGL 9.5** + AXS15231B touch
- LVGL renders into a partial buffer; `my_disp_flush` blits dirty areas to an
  `Arduino_Canvas`, which is pushed to the panel in `loop()` only when something
  changed.

```bash
pio run -t upload
pio device monitor
```

LVGL config: `include/lv_conf.h` (Montserrat 12/14/16/20/28 enabled, 16-bit colour).

## Status
- ✅ Phase 1: LVGL up — display + touch + AA fonts (test screen).
- ✅ Phase 2a: main dashboard in LVGL — header tabs + WiFi/clock/sleep/settings
  icons (LVGL symbols), SOC arc gauge, voltage/stats/temps cards, 4 cell bars,
  power + capacity graphs (drawn via LVGL vector API) — pixel-faithful to the
  original, anti-aliased text. Simulated data + auto-switch (tap pauses 30s).
- ✅ Phase 2b: settings (close + BMS/WiFi/System sub-tabs), scrollable System list
  (10 settings + right scrollbar, drag-scroll, tap-on-release), WiFi scan/connect
  + on-screen keyboard (keys on press) + NVS persist/auto-reconnect, System info
  popup, brightness PWM, 3D sleep animation + auto-sleep, WiFi icon/clock.

## Performance notes (this panel is full-flush only — see code comment)
- Partial-window writes don't work on this AXS15231B; the whole canvas is flushed
  per frame (~40ms, ~24fps ceiling). Custom **1-bpp Montserrat** fonts (no AA) +
  region-based / per-row invalidation + a w*h/4 draw buffer keep it usable.
- The original Arduino_GFX `esp32-bms/` is faster (bitmap fonts, no LVGL pipeline);
  this LVGL build trades some speed for nicer rendering.
