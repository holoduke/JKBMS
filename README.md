# ⚡ JK BMS — dashboards & firmware

Tools for monitoring and controlling **JK-BMS** battery management systems — a
zero-install **Web Bluetooth** dashboard, and standalone **ESP32 touchscreen**
firmware. Everything runs locally; nothing leaves your device.

| | |
|---|---|
| 🌐 **[Web dashboard](#-web-dashboard)** | Browser app over Bluetooth — no install, no cloud |
| 📟 **[ESP32 firmware](#-esp32-touchscreen-firmware)** | Standalone 3.5" touchscreen monitor over the BMS UART |

---

## 🌐 Web dashboard

![JK BMS dashboard](screenshot-dashboard.png)

A single-file **Web Bluetooth** dashboard for JK-BMS (targeting the **JK-B2A8S20P**,
hardware v11+ / `JK02_32S` protocol). No app, no build step, no account.

> **Try it without hardware:** open the page with `?demo=1` for a fully interactive
> simulated LiFePO₄ pack — add `&cells=8` (or 16/24/32) and `&packs=2` to preview any setup.

**Highlights**
- **Live**: SOC / voltage / power ring gauges, per-cell voltages & resistances (min/max highlighted), temperatures, cycles, SOH.
- **Trends**: rolling sparklines (V, A, W, SOC, MOS temp), session energy (Wh in/out, peaks), per-cell balance chart.
- **Control**: nearly every protection setting and switch is writable (MOSFETs, balancer, OVP/UVP, OCP/OTP/UTP, …) — toggles & click-to-edit, each write confirmed with bounds checking.
- **Multi-pack**: connect several BMSes at once and switch instantly; auto-reconnect with backoff.
- **Dev tool**: paste a captured frame hex dump to decode it offline, verify CRC, and gap-analyse undecoded bytes.

**Run it**
```sh
python3 -m http.server 8765 --bind 127.0.0.1
# open http://127.0.0.1:8765/ in Chrome or Edge (a secure context, so BLE works without HTTPS)
```
Web Bluetooth is not supported in Firefox/Safari.

<details>
<summary>Protocol &amp; tech notes</summary>

Implements the JK02_32S BLE frame format (header `55 AA EB 90`; type byte at offset 4:
`01`=settings, `02`=realtime, `03`=device info). Writes are
`AA 55 90 EB | register | len | value LE | CRC`, validated against
[`syssi/esphome-jk-bms`](https://github.com/syssi/esphome-jk-bms).

Single `index.html`, zero runtime deps. Tailwind is compiled statically
(`npx tailwindcss@3.4 --content index.html`). BLE writes are queued &amp; bounds-checked;
the UI updates in place rather than rebuilding the DOM per frame.
</details>

---

## 📟 ESP32 touchscreen firmware

<p align="center"><img src="esp32-bms-lvgl/docs/dashboard.gif" width="480" alt="ESP32 LVGL dashboard, captured from the device"></p>

Standalone firmware for a **Guition JC3248W535** (ESP32-S3, 3.5" 320×480 QSPI touch
display) that reads **two JK-BMS packs live over their wired RS485/UART** and shows
everything on the built-in screen — no phone, no cloud. *(The clip above is captured
straight from the device framebuffer.)*

Two builds live side by side:

- **[`esp32-bms-lvgl/`](esp32-bms-lvgl/)** — the polished build using **LVGL 9**: anti-aliased
  fonts, auto-switching BMS tabs, SOC ring gauge, power-draw + capacity/energy charts,
  per-cell bars, scrollable **editable** settings (written back to the BMS), WiFi +
  on-screen keyboard, power-save, and power-on / sleep animations.
- **[`esp32-bms/`](esp32-bms/)** — the original, drawn directly with Arduino_GFX (no AA fonts,
  but lighter and faster).

**Live & writable:** reads the realtime block and the full settings block over Modbus,
and writes settings back (capacity, current limits, protections) and toggles the
charge/discharge/balancer MOSFETs — each write read-back-verified.

**Web portal + OTA:** on WiFi it serves a password-protected web app (live monitor,
controls, a live screenshot of the LCD, and a firmware-update page) and supports
**over-the-air updates** (browser upload or PlatformIO/espota) — no cable needed.

```sh
cd esp32-bms-lvgl && pio run -t upload   # first flash over USB; thereafter OTA over WiFi
```

See **[esp32-bms-lvgl/README.md](esp32-bms-lvgl/README.md)** for hardware, wiring, the web
portal, OTA, and build details.

---

## License

© 2025–2026 Gillis Haasnoot
