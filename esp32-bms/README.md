# esp32-bms — JK BMS dashboard on a Guition JC3248W535

ESP32-S3 firmware that reads JK BMS data over the wired UART ("GPS" port) and
shows it on the board's built-in 3.5" touch display — a hardware companion to the
web dashboard in the parent repo.

## Hardware
- **Board:** Guition **JC3248W535** (ESP32-S3-WROOM-1U-N16R8, 16 MB flash, 8 MB octal PSRAM)
- **Display:** 3.5" 320×480 IPS, **QSPI**, controller **AXS15231B** (capacitive touch via the same chip)
- **BMS:** JK BMS, 12 V (4S) packs, **two in parallel**

## Toolchain
- **PlatformIO** + Arduino framework via the **pioarduino** platform (arduino-esp32 3.3.x / IDF 5.5)
- Display: **Arduino_GFX** (`Arduino_ESP32QSPI` + `Arduino_AXS15231B`)

```bash
pio run -t upload          # build + flash (native USB)
pio device monitor         # serial console @115200
```

> First-time only: a full `esptool erase-flash` may be needed to clear the factory bootloader.

## Wiring — JK BMS "GPS"/UART port → board
3.3 V TTL UART, **3 wires, TX/RX crossed**:

| JK port | Board (JST1.25 4P IO connector) |
|---|---|
| GND (0 V) | GND |
| TX (3 V) | IO18 (ESP RX) |
| RX (3 V) | IO17 (ESP TX) |
| VBAT (12 V) | ⛔ **leave open** |

Power the board from USB-C or a buck off the pack's main P+/P− output (not the GPS VBAT pin).

## Status
- ✅ Display + animated **demo dashboard** (landscape 480×320): auto-switching
  `[BMS 1] [BMS 2]` tabs, SOC ring gauge, V/A tiles, compact MOS/T1/T2 temps,
  cell bars, and a **capacity-over-time** area graph (per-BMS window, 5 time ticks).
- ✅ **Touch** (AXS15231B) + **Settings** screen (gear tab): auto-switch on/off,
  interval, brightness (PWM). Smart auto-switch pauses 30 s on interaction.
- ✅ Efficient **render-on-change** loop (redraws only when data/view changes).
- ⏳ Data is currently **simulated**; next step is the JK UART protocol parser to
  show live values, then the second BMS and charge/discharge control.

## Display notes (hard-won)
- The AXS15231B renders **only** via the `Arduino_Canvas` blit (`flush()`); drawing
  directly to the panel object shows black.
- On ESP32-S3, never `Serial.print()` unconditionally in the loop — USB-CDC blocks
  the loop when no host reads it. Use `Serial.setTxTimeoutMs(0)` + `if (Serial)`.
