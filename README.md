# ⚡ JK BMS Controller

A standalone **ESP32 touchscreen** that monitors and controls your **JK-BMS** battery system
(LiFePO₄ / Li-ion). Wire it to the BMS, mount it on the wall, and you get a live dashboard, a
built-in web app, over-the-air updates, a Home Assistant integration, and a **12-language UI** —
all running locally, with nothing leaving your network. One or two battery packs are supported.

<p align="center"><img src="docs/device-screen.png" width="70%" alt="The dashboard running on the device"></p>
<p align="center"><em>The live dashboard, captured straight from the device.</em></p>

### Highlights

- 🔋 **Live dashboard** — SOC ring, power/current with charge·discharge direction, per-cell bars, real BMS status
- 🎛️ **Full control** — toggle charge/discharge MOSFETs & balancer, edit every protection setting (written back & verified)
- 📈 **7-day history** — persisted SOC & power graphs that survive reboots, plus 24 h / 6 h energy used
- 🌍 **12 languages** — EN · FR · DE · NL · PL · PT · ES · VI · RU · ZH · AR (RTL) · HI, on the device *and* the web app
- 🌤️ **Weather & clock** — today + 3-day forecast (geo-located by IP) and an NTP-synced clock in the top bar
- 🏠 **Home Assistant** — MQTT auto-discovery, no YAML
- 🌐 **Built-in web app** — responsive, multilingual, with a live screenshot of the LCD
- 🔒 **PIN lock & screensaver** — optional auto-lock with a 6-digit unlock pad, selectable idle screensavers
- 🔄 **Wireless OTA** — update from the browser or PlatformIO after the first USB flash

---

## What it does

**On the screen** you get the essentials at a glance: a big SOC ring, the current power draw
with a charge/discharge arrow, and a status pill that reflects the BMS's real state (charging,
discharging, full, balancing, idle, alarm). Below that are voltage, peaks and temperatures,
per-cell bars, a 10-minute power graph, and an energy panel showing total capacity and what
you've used over the last 24 h and 6 h. The top bar also shows the time and today's weather.

**You can change BMS settings right from the touchscreen** — capacity, cell count, current
limits, cell OVP/UVP, SOC calibration, balancing, charge profile and temperature protections.
Every value is entered on an on-screen keypad and read back from the BMS to confirm it stuck.

**A built-in web app** lives at `http://<device-ip>/`. It mirrors the screen in your browser
with the same controls and settings, shows a live snapshot of the LCD, and lets you flash new
firmware — all behind a password, in a clean responsive UI with its own 12-language selector.
After the first USB flash, every update is wireless (from the browser or PlatformIO).

**Home Assistant** is one checkbox away. Turn on MQTT in the web app and each pack appears
automatically (auto-discovery) as a device with sensors for SOC, voltage, current, power,
temperatures, health, cycles and status, plus switches for the charge/discharge MOSFETs and the
balancer. No YAML to write.

**Make it yours.** Pick from **12 interface languages** (English, French, German, Dutch, Polish,
Portuguese, Spanish, Vietnamese, Russian, Chinese, Arabic — right-to-left — and Hindi) in
**Settings → System → Language**; the web app has its own language selector too. The top bar shows
the time (NTP-synced) and **today's weather with a 3-day forecast**, located automatically by IP.
You can set an optional **PIN lock** (auto-lock after a chosen idle time, unlocked with a 6-digit
pad) and a **screensaver** (several animated idle screens, with their own timeout). Plus power-save
auto-dim / auto-sleep / eco modes. All fonts are open-source (Montserrat + Noto).

> For the full technical write-up — rendering pipeline, JK protocol map, web portal and OTA —
> see **[esp32-bms-lvgl/README.md](esp32-bms-lvgl/README.md)**.

---

## What you'll need

| | Part | Why | Buy |
|---|------|-----|-----|
| 📟 | **Guition JC3248W535** | The display board — ESP32-S3-N16R8 with a 3.5″ 320×480 touchscreen | **[AliExpress](https://nl.aliexpress.com/item/1005008495512979.html)** |
| 🔋 | **JK-BMS** | Any JK-BMS with an **RS485** port (e.g. JK-B2A8S20P) | **[AliExpress](https://nl.aliexpress.com/item/1005008215378422.html)** |
| 🔌 | **Buck converter** | Steps the pack voltage down to a clean 5 V for the board | **[AliExpress](https://nl.aliexpress.com/item/1005006537133858.html)** |
| 🧵 | **4-pin + 8-pin cables** | To tap the JK-BMS RS485 port without splicing | **[AliExpress](https://nl.aliexpress.com/item/1005007277110532.html)** |

**Wiring.** Connect the BMS RS485/UART to the ESP32 with a shared ground. The defaults are
`IO18`/`IO17` (RX/TX) for the first pack and `IO15`/`IO16` for the second — both changeable in
**Settings → BMS**. Set the JK's protocol to **"JK BMS RS485 Modbus" at 115200 baud**, or the
device won't read it.

**Power.** Feed the board 5 V from the buck converter. Note that powering through the buck often
disables the USB *data* port, so do the first flash over USB from a PC, then switch to the buck.
For switched installs, prefer high-side switching — and never connect VBAT to a logic pin.

---

## Getting started

1. Install **[PlatformIO](https://platformio.org/)** (CLI or the VS Code extension) and clone this repo.
2. Flash once over USB:
   ```sh
   cd esp32-bms-lvgl
   pio run -t upload
   ```
3. On the device, open **Settings → WiFi** and join your network, then **Settings → BMS** to set
   the number of packs and the UART pins.
4. Open the web app at **`http://<device-ip>/`**. The IP and login are shown under
   **Settings → System** — it's `admin` with a unique per-device password, both editable.
5. From here, updates are wireless: use the web app's *Firmware update*, or `pio run` + `espota`
   to the device (hostname `jkbms`).

Running two packs? Set **Settings → BMS → Batteries → 2** and wire the second pack to BMS2's
pins. The whole UI — tabs, web app and API — adapts automatically.

---

## Also in this repo

If you don't have the hardware yet, or want a quick check from a phone, two smaller front-ends
speak the same JK protocol:

- **🌐 Web Bluetooth dashboard** (`index.html`) — a single-file browser app that talks to the
  BMS over Bluetooth, no install. Open it in Chrome/Edge; add `?demo=1` to try it with no hardware.
- **📟 Arduino_GFX firmware** (`esp32-bms/`) — the original, lighter build for the same board.

---

© 2025–2026 Gillis Haasnoot
