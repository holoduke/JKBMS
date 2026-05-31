# JK BMS Bluetooth Dashboard

A single-file (no build step) **Web Bluetooth** dashboard for **JK-BMS** battery management systems, targeting the **JK-B2A8S20P** (hardware v11+, which uses the `JK02_32S` protocol).

Open `index.html` in **Chrome or Edge** (Web Bluetooth is not supported in Firefox/Safari), click **Connect**, and pair with the BMS over BLE.

## Features

- Live dashboard: SOC, pack voltage, current/power, per-cell voltages & resistances, temperatures, cycle count, SOH.
- Decodes the full **settings** frame (UVP/OVP, OCP, OTP/UTP, balancing, switches, controls bitfield, etc.).
- Decodes **device info** (vendor, hardware/software version, serial, passcodes, protocol numbers).
- Full 32-bit **alarm/error** bitmask decode (incl. charge/discharge MOSFET-abnormal flags).
- Toggle charge / discharge / balancer MOSFETs and set max charge/discharge current & capacity.
- **Dev tool** (panel at bottom): paste a captured frame hex dump to decode it offline, verify the CRC, and run a **byte-coverage gap analysis** that highlights bytes no field decodes yet.

## Protocol

Implements the JK02_32S BLE frame format (header `55 AA EB 90`, type byte at offset 4: `01`=settings, `02`=realtime, `03`=device info). Offsets validated against the reference reverse-engineered implementation [`syssi/esphome-jk-bms`](https://github.com/syssi/esphome-jk-bms).

## Running locally

```sh
python3 -m http.server 8765 --bind 127.0.0.1
# then open http://127.0.0.1:8765/ in Chrome
```

`http://127.0.0.1` is treated as a secure context by Chrome, so Web Bluetooth works without HTTPS.

## License

© 2025 Gillis Haasnoot
