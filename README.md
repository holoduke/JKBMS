# ⚡ JK BMS Controller — ESP32 touchscreen firmware

Monitor and control your **JK-BMS** battery system (LiFePO₄ / Li-ion) from a standalone
**ESP32 touchscreen** wired to the BMS over RS485/UART. A permanent panel with a built-in
**web app**, **over-the-air updates** and **Home Assistant (MQTT)** — everything runs locally,
nothing leaves your network. **One or two packs** supported.

<p align="center"><img src="docs/device-screen.png" width="70%" alt="LVGL dashboard captured from the device"></p>
<p align="center"><em>The live dashboard, captured from the device framebuffer.</em></p>

---

## ✨ Features

- **Live dashboard**: SOC ring gauge, big W·A readout with charge/discharge arrow, status pill
  (Charging / Discharging / Full / Idle / Balancing / FET-off / Alarm — from the BMS's real
  state), voltage / peaks / temps tiles, per-cell bars, a **power-draw graph** (10-min window)
  and a **capacity panel** (total kWh + energy used in the last 24 h / 6 h, with %).
- **Today's weather** in the top bar (geo-located by IP, no key) with a 3-day forecast in the
  web app, plus an NTP-synced clock.
- **Two packs**: auto-switching tabs; both polled every second.
- **Editable settings** written back to the BMS: capacity, cell count, current limits, cell
  OVP/UVP, SOC calibration, balancing, charge profile, temperature protections — via an
  on-screen numeric keypad, each write read-back-verified.
- **Settings**: BMS / WiFi / System tabs, on-screen keyboard, the web address + login shown
  and editable on-device, power-save (auto-dim / -sleep / eco), selectable "idle" screens.
- **📶 Built-in web portal** at `http://<device-ip>/` — a responsive dashboard mirroring the
  screen, with **controls**, the full **editable settings**, a **live screenshot** of the LCD,
  and **firmware update**. Password-protected (HTTP Digest).
- **🏠 Home Assistant**: optional **MQTT** with **auto-discovery** — each pack shows up
  automatically as a device with SOC / voltage / current / power / temps / health / cycles /
  status sensors plus Charge / Discharge / Balancer switches. Configure the broker in the web
  portal's *Home Assistant (MQTT)* card; no YAML needed.
- **🔄 OTA**: update over WiFi from the browser *or* PlatformIO — **no cable** after the first flash.

See **[esp32-bms-lvgl/README.md](esp32-bms-lvgl/README.md)** for the deep dive (rendering
pipeline, protocol map, web portal, OTA).

---

## 🛒 Hardware you need

| | Part | What to get | Buy |
|---|------|-------------|-----|
| 📟 | **Display board** | Guition **JC3248W535** — ESP32-S3-N16R8, 3.5″ 320×480 QSPI touch | **[AliExpress](https://nl.aliexpress.com/item/1005008495512979.html)** |
| 🔋 | **BMS** | A **JK-BMS** with an **RS485** port (LiFePO₄ / Li-ion) | **[AliExpress](https://nl.aliexpress.com/item/1005008215378422.html)** |
| 🔌 | **Buck converter** | Step the pack voltage down to a clean **5 V** for the board | **[AliExpress](https://nl.aliexpress.com/item/1005006537133858.html)** |
| 🧵 | **Connector cables** | **4-pin** (RS485) and **8-pin** cables to tap the JK-BMS port | **[AliExpress](https://nl.aliexpress.com/item/1005007277110532.html)** |

Full wiring + setup notes in [Recommended hardware](#-recommended-hardware) below.

---

## 🔌 Recommended hardware

| Part | Notes |
|------|-------|
| **Display board** | **Guition JC3248W535** — ESP32-S3-N16R8, 3.5″ 320×480 QSPI (AXS15231B) capacitive touch. 👉 **[Get it on AliExpress](https://nl.aliexpress.com/item/1005008495512979.html)** |
| **BMS** | Any JK-BMS with an **RS485 port** (e.g. JK-B2A8S20P). Set its protocol to **"JK BMS RS485 Modbus", 115200 baud**. 👉 **[Get it on AliExpress](https://nl.aliexpress.com/item/1005008215378422.html)** |
| **Wiring** | BMS RS485/UART → ESP32. Defaults: **BMS1** RX `IO18` / TX `IO17`, **BMS2** RX `IO15` / TX `IO16`, shared GND. Pins are configurable in Settings → BMS. A **[4-pin (RS485) + 8-pin cable set](https://nl.aliexpress.com/item/1005007277110532.html)** makes tapping the JK port easy. |
| **Power** | 5 V to the board, e.g. via a **[buck converter](https://nl.aliexpress.com/item/1005006537133858.html)** stepping down the pack voltage. ⚠️ Powering from a buck converter often disables the USB **data** port — flash over USB from a PC, then run from the buck. For switched installs, prefer **high-side** switching. |

> ⚠️ Always verify your own wiring and never connect VBAT to a logic pin. Set the JK's RS485
> protocol correctly or the device won't read it.

---

## 🚀 Getting started

1. Install **[PlatformIO](https://platformio.org/)** (CLI or the VS Code extension).
2. Clone this repo.
3. First flash over USB:
   ```sh
   cd esp32-bms-lvgl
   pio run -t upload
   ```
4. On the device: **Settings → WiFi** → connect your network. **Settings → BMS** → set
   **Batteries** (1 or 2) and the **UART pins**; make sure the JK's protocol is **RS485 Modbus**.
5. Open the web portal at **`http://<device-ip>/`** (the IP + login are shown on the device's
   **Settings → System** screen; login defaults to `admin` with a unique per-device password,
   all editable on-device or in the portal).
6. **Updates from now on are wireless** — no cable:
   - **Browser:** portal → *Firmware update* → pick `firmware.bin` (`.pio/build/jc3248w535/firmware.bin`).
   - **PlatformIO:** `pio run` then upload via `espota` to the device IP (hostname `jkbms`).

### Single vs. dual pack
Default is **one** pack. For two, set **Settings → BMS → Batteries → 2** (on the device) and
wire the second pack to BMS2's pins. The dashboard, tabs, web portal and API all adapt to the
count automatically.

---

## Also in this repo

Two other front-ends speak the same JK protocol, if you want them:

- **🌐 Web Bluetooth dashboard** (`index.html`) — a single-file, zero-install browser dashboard
  over BLE; handy for a quick check from a phone/laptop with no hardware. Serve it locally and
  open in Chrome/Edge (`…/?demo=1` to try with simulated data).
- **📟 Arduino_GFX firmware** (`esp32-bms/`) — the original, lighter build for the same board
  (bitmap fonts, no LVGL), fewer features.

---

## License
© 2025–2026 Gillis Haasnoot
