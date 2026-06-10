# ⚡ JK BMS Controller — live dashboard

![JK BMS Controller dashboard](screenshot-dashboard.png)

A single-file (no build step) **Web Bluetooth** dashboard for **JK-BMS** battery management systems, targeting the **JK-B2A8S20P** (hardware v11+, which uses the `JK02_32S` protocol).

Everything runs in your browser — no app, no cloud, no account. Nothing leaves your device.

**Try it without hardware:** open the page with `?demo=1` for a fully interactive simulated LiFePO₄ pack — add `&cells=8` (or 16/24/32) to preview any pack size.

## Features

- **Live dashboard**: SOC / voltage / power-load ring gauges, per-cell voltages & internal resistances with min/max highlighting, temperatures, cycle count, SOH.
- **Trends**: rolling sparkline charts (pack V, current, power, SOC, MOSFET temp), session energy stats (Wh in/out, peaks), and a per-cell balance deviation chart.
- **Control**: nearly every protection setting and switch is writable (MOSFETs, balancer, OVP/UVP, OCP/OTP/UTP, heating, capacity, …) — booleans are inline toggle switches and numbers are click-to-edit; every write goes through an explicit confirmation dialog with bounds checking.
- Decodes the full **settings** frame (UVP/OVP, OCP, OTP/UTP, balancing, switches, controls bitfield, …), **device info**, and the full 32-bit **alarm/error** bitmask.
- **Multi-pack**: connect several BMSes at once — every pack keeps streaming, the picker switches the view instantly and shows live V/SOC per pack.
- **Auto-reconnect** for every known pack with exponential backoff, stale-data banner, connection-state indicator.
- **Demo mode** (`?demo=1`, optional `&cells=4…32`, `&packs=2`): realistic simulated pack — try the whole UI, including setting editors, in any browser.
- **Dev tool** (collapsible panel): paste a captured frame hex dump to decode it offline, verify the CRC, and run a byte-coverage gap analysis that highlights bytes no field decodes yet.

## Quick start

```sh
python3 -m http.server 8765 --bind 127.0.0.1
# then open http://127.0.0.1:8765/ in Chrome or Edge
```

`http://127.0.0.1` is a secure context, so Web Bluetooth works without HTTPS. Click **Connect a battery** and pair with the BMS over BLE. (Web Bluetooth is not supported in Firefox/Safari.)

## Protocol

Implements the JK02_32S BLE frame format (header `55 AA EB 90`, type byte at offset 4: `01`=settings, `02`=realtime, `03`=device info). Write frames are `AA 55 90 EB | register | len | value LE | CRC`. Registers and offsets validated against the reference reverse-engineered implementation [`syssi/esphome-jk-bms`](https://github.com/syssi/esphome-jk-bms).

## Tech notes

- Single `index.html`, zero runtime dependencies. Tailwind is compiled statically into the page (rebuild with `npx tailwindcss@3.4 --content index.html` if you add new utility classes).
- All BLE writes are serialized through a queue and bounds-checked; the UI updates values in place instead of rebuilding the DOM per frame.

## License

© 2025–2026 Gillis Haasnoot
