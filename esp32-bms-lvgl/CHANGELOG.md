# Changelog

## 1.0.215
- **Self-update from GitHub Releases** — the device checks for new releases and can
  download + flash `firmware.bin` itself (manual "Update now" button, or an optional
  auto-update toggle). An accent dot on the gear and a web banner show when an update
  is available.
- **Dashboard polish** — gradient SOC gauge (red→amber→green), gradient graph fills,
  card depth, tile icons, and a cell-balance heatmap.
- **Charging comet spinner** around the SOC ring while charging.
- **In-browser history charts** (SOC / power / temperature) in the web portal.
- **Per-cell voltages** published to Home Assistant via MQTT.
- **Remaining Ah**, time-accurate 24h/6h energy windows, persisted peaks, and a
  7-day temperature history.

## 1.0.x (earlier)
- 12-language UI, weather + 5-day forecast, NTP clock, PIN lock, screensaver.
- Lifetime energy counters, threshold push alerts, CSV history export.
- Dual-core split (UI on core 1, network + BMS poll on core 0) for smooth rendering.
- MQTT / Home Assistant auto-discovery, web portal, OTA, auto-versioning.
