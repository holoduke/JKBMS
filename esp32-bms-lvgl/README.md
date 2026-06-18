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
- ⏳ Phase 2: rebuild the full dashboard (tabs, SOC gauge, tiles, cell bars,
  power/capacity charts, settings + WiFi, sleep) in LVGL.
