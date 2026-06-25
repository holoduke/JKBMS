# esp32-bms-lvgl — LVGL version of the JK BMS dashboard

<p align="center"><img src="docs/dashboard.gif" width="480" alt="LVGL dashboard captured from the device framebuffer"></p>

A rebuild of the `esp32-bms/` dashboard using **LVGL 9** for anti-aliased fonts,
smooth scrolling, gestures, and real widgets. Same hardware, nicer UI.
*(The clip above is captured straight from the device's framebuffer over serial.)*

- **Board:** Guition JC3248W535 (ESP32-S3-N16R8, 320×480 QSPI AXS15231B) — [get it on AliExpress](https://nl.aliexpress.com/item/1005008495512979.html)
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

## Features

**Live BMS (real data — not simulated):**
- Reads the JK BMS over **RS485 Modbus RTU** (115200, addr 1, func 0x03/0x10).
  Realtime block `0x1200`; settings block `0x1000` read in ≤64-register chunks
  (this BMS only reliably answers ≤64 registers per request).
- **Two packs** on two hardware UARTs (BMS1 RX18/TX17, BMS2 RX15/TX16, pins
  configurable in Settings); both polled every second, instant tab switch.
- **Editable settings written back to the BMS** — capacity, cell count, current
  limits, cell OVP/UVP, SOC calibration, balancing, charge profile, temp
  protections — each write read-back-verified (with retry). FET/balancer toggles.
- Offline/stale rendering, `--` for unwired temp probes, demo mode for previews.

**Dashboard:** auto-switching BMS tabs (tap pauses), SOC ring gauge, big W/A
readout with charge/discharge arrow, status pill (Charging/Discharging/Full/
Idle/Balancing/FET off/Offline), voltage/stats/temps cards, per-cell bars,
**power-draw graph** (10-min window) and **capacity panel** (total Wh + energy
used last 24h/6h) beside a 7-day SOC graph. WiFi status icon + clock.

**Settings:** BMS / WiFi / System sub-tabs; scrollable lists with drag-scroll;
full-screen numeric keypad editor (handled on press, jitter-proof); WiFi
scan/connect with on-screen keyboard + NVS persist/auto-reconnect; System Info
popup (shows the web-portal login); brightness PWM, power-save (eco/auto-dim/
auto-sleep), selectable no-data idle screens; 3D sleep animation.

## Web portal & OTA (over WiFi)

Once connected to WiFi the device serves a **password-protected web portal** at
`http://<device-ip>/` (login `admin` / password shown on the System Info screen;
default is derived from the eFuse MAC, e.g. `jk-xxxx`):

- **Live dashboard** for both packs (SOC/V/A/W/temps/cells/status), responsive
  (two columns on desktop, stacked on mobile).
- **Controls:** toggle charge/discharge/balancer, tap any setting to edit it.
- **Device screen** — a live screenshot of the LCD framebuffer, JPEG-encoded on the device (`/screen.jpg`, ~30 KB).
- **Firmware update** — drag a `.bin` and flash it; the device reboots into it.
- **Security** — change the portal/OTA password (stored in NVS).
- **Home Assistant (MQTT)** — enable in the portal's *Home Assistant (MQTT)* card; each pack
  is published with MQTT **auto-discovery** (SOC/V/A/W/temps/health/cycles/status sensors +
  Charge/Discharge/Balancer switches) and an availability (LWT) topic — no YAML needed.

Two ways to update without a cable (HTTP Basic auth on everything):

```bash
# 1) browser: open the portal → Firmware update → pick firmware.bin
# 2) PlatformIO over WiFi (ArduinoOTA, host 'jkbms', same password):
pio run && python3 ~/.platformio/packages/framework-arduinoespressif32/tools/espota.py \
  -i <device-ip> -p 3232 -a <password> -f .pio/build/jc3248w535/firmware.bin
```

The partition table ships with dual OTA slots (`app0`/`app1`), so OTA works out
of the box. The web/OTA stack is in `src/web_portal.h`; it suspends the UI and
disables WiFi modem-sleep during a transfer so large streams don't stall.

## Performance notes (this panel is full-flush only — see code comment)
- Partial-window writes don't work on this AXS15231B; the whole canvas is flushed
  per frame (~40ms, ~24fps ceiling). Custom **1-bpp Montserrat** fonts (no AA) +
  region-based / per-row invalidation + a w*h/4 draw buffer keep it usable.
- The original Arduino_GFX `esp32-bms/` is faster (bitmap fonts, no LVGL pipeline);
  this LVGL build trades some speed for nicer rendering.
