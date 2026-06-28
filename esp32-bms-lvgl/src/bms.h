// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
static void genCap(Bms &b, float span, int count) {
    if (count > NCAP) count = NCAP; if (count < 2) count = 2;
    b.capSpanDays = span; b.capCount = count;
    for (int i = 0; i < count; i++) {
        float d = (float)i / (count - 1) * span;
        float v = 64 + 26 * sinf((d - 0.3f) * 2 * PI) + 6 * sinf(d * 0.9f) + 3 * sinf(i * 1.3f);
        b.cap[i] = v < 12 ? 12 : (v > 99 ? 99 : v);
        b.pwr[i] = 220 * cosf((d - 0.3f) * 2 * PI) + 30 * sinf(i * 1.7f);
    }
}
static void simInit() { genCap(bms[0], 7, 168); genCap(bms[1], 1, 48); }
// Append one real sample to BMS idx's history (ring-buffer, drops the oldest when full).
static void histAppend(int idx, float soc, float watt, float tmp) {
    if (histCount[idx] >= HIST_N) {
        memmove(histCap[idx], histCap[idx] + 1, (HIST_N - 1) * sizeof(histCap[0][0]));
        memmove(histPwr[idx], histPwr[idx] + 1, (HIST_N - 1) * sizeof(histPwr[0][0]));
        memmove(histTmp[idx], histTmp[idx] + 1, (HIST_N - 1) * sizeof(histTmp[0][0]));
        histCount[idx] = HIST_N - 1;
    }
    int s = (int)(soc + 0.5f); s = s < 0 ? 0 : s > 100 ? 100 : s;
    float w = watt < -32000 ? -32000 : watt > 32000 ? 32000 : watt;
    int tc = (int)lroundf(tmp); tc = tc < -128 ? -128 : tc > 127 ? 127 : tc;
    histCap[idx][histCount[idx]] = (uint8_t)s;
    histPwr[idx][histCount[idx]] = (int16_t)w;
    histTmp[idx][histCount[idx]] = (int8_t)tc;
    histCount[idx]++;
    histDirty = true; histDirtyAt = millis();
}
// Sample any live BMS once per HIST_INTERVAL (first reading seeds it immediately).
static void histSample() {
    uint32_t now = millis();
    for (int t = 0; t < numBms; t++) {
        if (!bmsLive[t]) continue;
        if (bms[t].soc < 1) continue;                  // skip implausible 0% (BMS not settled / bad read)
        if (histCount[t] == 0 || (now - histLastMs[t]) >= HIST_INTERVAL_MS) {
            histAppend(t, bms[t].soc, bms[t].v * bms[t].i, bms[t].tMos);
            histLastMs[t] = now;
        }
    }
}
// Integrate pack power into the lifetime Wh counters. Called every BMS poll (~1 s) for
// live packs; the dt anchor resets when a pack goes offline so downtime never back-fills.
static void energyIntegrate() {
    uint32_t now = millis();
    for (int t = 0; t < numBms; t++) {
        if (!bmsLive[t]) { lifeLastMs[t] = 0; continue; }
        if (lifeLastMs[t] == 0) { lifeLastMs[t] = now; continue; }   // first live sample seeds the anchor
        uint32_t dt = now - lifeLastMs[t]; lifeLastMs[t] = now;
        if (dt == 0 || dt > 15000) continue;                         // implausible gap (downtime / wrap) → skip
        double wh = (double)(bms[t].v * bms[t].i) * dt / 3600000.0;  // charge-positive
        if (wh > 0) lifeWhIn[t] += wh; else lifeWhOut[t] += -wh;     // saved on the existing 5-min history cadence
    }
}
// Append the current power to each pack's 10-min window (once per PWR_DT). Samples
// whenever there's data to plot (live, or demo sim). Returns true if a sample landed.
static bool pwrSample() {
    uint32_t now = millis(); bool added = false;
    for (int t = 0; t < numBms; t++) {
        if (!demoMode && !bmsLive[t]) continue;             // nothing to sample
        if (pwrWinN[t] != 0 && (now - pwrWinLast[t]) < PWR_DT) continue;
        float w = -(bms[t].v * bms[t].i);                  // draw-positive: discharging (using power) reads up, charging down
        if (w < -32000) w = -32000; if (w > 32000) w = 32000;
        if (pwrWinN[t] >= PWR_WIN) {                        // ring: drop oldest
            memmove(pwrWin[t], pwrWin[t] + 1, (PWR_WIN - 1) * sizeof(pwrWin[0][0]));
            pwrWinN[t] = PWR_WIN - 1;
        }
        pwrWin[t][pwrWinN[t]++] = (int16_t)w;
        pwrWinLast[t] = now; added = true;
    }
    return added;
}
static void simStep(uint32_t nowMs) {
    float s = nowMs / 1000.0f * simSpeed;
    for (int t = 0; t < numBms; t++) {
        if (!demoMode) continue;                 // live mode shows only real data (or a stale/offline state)
        float ph = t * 2.1f;
        bms[t].soc = 62 + 30 * sinf(s * 0.05f + ph);
        bms[t].i = 28 * sinf(s * 0.18f + ph) + (t ? -4 : 3);
        bms[t].v = 13.2f + 0.35f * sinf(s * 0.12f + ph) + bms[t].i * 0.004f;
        bms[t].tMos = 33 + fabsf(bms[t].i) * 0.45f + 3 * sinf(s * 0.07f + ph);
        bms[t].tp1 = 24 + 3 * sinf(s * 0.03f + ph) + t;
        bms[t].tp2 = 25 + 3 * sinf(s * 0.04f + ph + 1) + t;
        bms[t].nCells = NCELLS;
        for (int i = 0; i < NCELLS; i++) { bms[t].cell[i] = bms[t].v / NCELLS + 0.015f * sinf(s * 0.5f + i * 1.7f + ph); bms[t].cellRes[i] = 0.30f + 0.05f * i; }
        bms[t].bmsOk = true; bms[t].errFlags = 0;
        bms[t].chgMos = bms[t].disMos = true; bms[t].soh = 100;   // healthy simulated pack (else status pill shows "FET off")
        float p = bms[t].v * bms[t].i;
        if (p > bms[t].peakChg) bms[t].peakChg = p;
        if (-p > bms[t].peakDis) bms[t].peakDis = -p;
    }
}
// ---- real BMS over Modbus RTU (JK "RS485 Modbus", TTL on the GPS/UART port) ----
static uint16_t mbCrc(const uint8_t *d, int n) {
    uint16_t c = 0xFFFF;
    for (int i = 0; i < n; i++) { c ^= d[i]; for (int b = 0; b < 8; b++) c = (c & 1) ? (c >> 1) ^ 0xA001 : c >> 1; }
    return c;
}
// Read the 0x1200 status block from one BMS (Modbus addr) into bms[idx]. Sets bmsLive[idx].
// One realtime-block read attempt. Returns true (and sets bmsLive) on a fully valid
// frame; false on no/short/corrupt reply (leaves bmsLive untouched — the caller retries).
static bool bmsTryReadAddr(uint8_t addr, int idx) {
    HardwareSerial &S = bmsPort(idx);
    uint8_t req[8] = {addr, 3, 0x12, 0x00, 0x00, 0x71, 0, 0};
    uint16_t crc = mbCrc(req, 6); req[6] = crc & 0xFF; req[7] = crc >> 8;
    while (S.available()) S.read();
    S.write(req, 8); S.flush();
    // Reply (5 + 0x71*2 ≈ 231 bytes) takes ~25 ms at 115200; the loop exits the
    // instant a full frame lands, so this timeout only bites when a pack is silent.
    static uint8_t r[260]; int n = 0; uint32_t t0 = millis();
    while (millis() - t0 < 70) { while (S.available() && n < 260) r[n++] = S.read(); if (n >= 5 && n >= 3 + r[2] + 2) break; }
    if (n < 5 || r[0] != addr || r[1] != 3) return false;
    int bc = r[2];
    if (bc < 196) return false;   // a short but CRC-valid frame would decode stale buffer bytes → reject (we read up to offset 0xC3)
    if (n < 3 + bc + 2 || (r[3 + bc] | (r[4 + bc] << 8)) != mbCrc(r, 3 + bc)) return false;
    uint8_t *p = r + 3;
    auto U16 = [&](int o) { return (uint16_t)(p[o] << 8 | p[o + 1]); };
    auto U32 = [&](int o) { return (uint32_t)((uint32_t)p[o] << 24 | p[o + 1] << 16 | p[o + 2] << 8 | p[o + 3]); };
    Bms &b = bms[idx];
    int nc = 0;                                       // cells: voltage @0x00.., resistance @0x4A.. (web 6/80), up to 24
    for (int i = 0; i < MAXCELLS; i++) {
        b.cell[i] = U16(i * 2) / 1000.0f;
        b.cellRes[i] = U16(0x4A + i * 2) / 1000.0f;   // mΩ
        if (b.cell[i] > 0.5f) nc = i + 1;             // highest populated cell → actual series count
    }
    b.nCells = nc > 0 ? nc : NCELLS;
    b.balCur = (int16_t)U16(0xA4) / 1000.0f;          // balance current (web offset 170)
    b.v = (int32_t)U32(0x90) / 1000.0f;   // signed like current, matches the JK i32 encoding
    b.i = (int32_t)U32(0x98) / 1000.0f;
    b.tMos = (int16_t)U16(0x8A) / 10.0f;
    b.tp1 = (int16_t)U16(0x9C) / 10.0f;
    b.tp2 = (int16_t)U16(0x9E) / 10.0f;
    b.soc = p[0xA7];
    uint32_t full = U32(0xAC); if (full > 1000) packFullAh[idx] = full / 1000.0f;
    uint32_t up = U32(0xBC);                          // total runtime (s) — web frame offset 194 − 6
    if (up > 0 && up < 4000000000UL) { b.uptime = up; b.uptimeOk = true; }
    float w = b.v * b.i; if (w > b.peakChg) b.peakChg = w; if (-w > b.peakDis) b.peakDis = -w;
    b.errFlags = U32(0xA0);            // protection/warning bitmask (web offset 166)
    b.chgMos = p[0xC0];                // actual charge MOSFET state (web 198)
    b.disMos = p[0xC1];                // actual discharge MOSFET state (web 199)
    b.balWork = p[0xC3];               // balancer actively working (web 201)
    b.cycles = U32(0xB0);              // cycle count (web 182)
    b.soh = p[0xB8];                   // state of health % (web 190)
    b.bmsOk = (b.errFlags == 0);       // operational unless the BMS reports a fault
    bmsLive[idx] = true;
    return true;
}
// Realtime read with one retry — a single dropped/corrupt frame shouldn't flap a pack to
// "offline" (which clears its data row + settings and loses a history sample).
static void bmsReadAddr(uint8_t addr, int idx) {
    bool wasLive = bmsLive[idx];
    if (bmsTryReadAddr(addr, idx)) return;
    if (wasLive) { delay(6); if (bmsTryReadAddr(addr, idx)) return; }   // a live pack glitched → one retry (avoids flap); a silent pack isn't retried
    bmsLive[idx] = false;
}
// Poll both real BMSes (addr 1 → BMS 1, addr 2 → BMS 2). Skipped in demo mode.
// A pack that's offline is retried only every BMS_RETRY polls, not every poll, so
// a missing pack doesn't stall the UI with a timeout every second.
// Read the settings/parameter block (Modbus reg 0x1000, 125 regs = 250 bytes) into
// Read `count` holding registers from `reg` into dst[dstOff..], big-endian like realtime.
// Returns true on a valid, CRC-checked reply. Keeps each reply small enough not to
// overrun the UART RX buffer (the reason a single 250-byte settings read failed).
static bool mbReadInto(HardwareSerial &S, uint8_t addr, uint16_t reg, uint8_t count,
                       uint8_t *dst, int dstOff, int dstCap, uint32_t toMs) {
    uint8_t req[8] = {addr, 3, (uint8_t)(reg >> 8), (uint8_t)(reg & 0xFF), 0, count, 0, 0};
    uint16_t crc = mbCrc(req, 6); req[6] = crc & 0xFF; req[7] = crc >> 8;
    while (S.available()) S.read();
    S.write(req, 8); S.flush();
    static uint8_t r[280]; int n = 0; uint32_t t0 = millis();
    while (millis() - t0 < toMs) { while (S.available() && n < (int)sizeof(r)) r[n++] = S.read(); if (n >= 5 && n >= 3 + r[2] + 2) break; }
    if (n < 5 || r[0] != addr || r[1] != 3) return false;
    int bc = r[2]; if (n < 3 + bc + 2 || (r[3 + bc] | (r[4 + bc] << 8)) != mbCrc(r, 3 + bc)) return false;
    int cp = bc; if (dstOff + cp > dstCap) cp = dstCap - dstOff; if (cp < 0) cp = 0;
    memcpy(dst + dstOff, r + 3, cp);
    return true;
}
// setRaw[idx]. byte k == web settings-frame offset k+6, big-endian like realtime.
// The 125-register (250-byte) block is read in two parts so neither reply overruns
// the UART buffer; offsets are identical to the old single read.
static void bmsReadSettings(uint8_t addr, int idx) {
    HardwareSerial &S = bmsPort(idx);
    auto rd = [&](uint16_t reg, uint8_t cnt, int off, int cap) -> bool {     // retry a couple times for transient misses
        for (int t = 0; t < 3; t++) if (mbReadInto(S, addr, reg, cnt, setRaw[idx], off, cap, 70)) return true;
        return false;
    };
    // This BMS reliably answers at most ~64 registers per read, so the 125-register
    // (250-byte) block is split into two ≤64-register reads. Offsets match the old single read.
    bool a = rd(0x1000, 0x40, 0,   250);    // regs 0x1000.. (64) → bytes 0..127
    bool b = rd(0x1040, 0x3D, 128, 250);    // regs 0x1040.. (61) → bytes 128..249
    setOk[idx] = a && b;
    if (!setOk[idx]) { setOk2[idx] = false; return; }
    // tail read: reg 0x10FA (frame offset 256) → bitmask/heating/sleep fields, stored at index 250
    setOk2[idx] = rd(0x10FA, 0x14, 250, 300);
}
#define BMS_RETRY 4
static void bmsRead() {
    if (demoMode) { bmsLive[0] = bmsLive[1] = false; return; }
    if (busMux && xSemaphoreTake(busMux, 0) != pdTRUE) return;   // a write is mid-flight on the other core → skip this poll
    static uint8_t skip[2] = {0, 0};
    static bool wasLive[2] = {false, false};
    static uint8_t setTick = 0; setTick++;
    if (numBms < 2) bmsLive[1] = false;            // pack 2 disabled → never "live"
    for (int t = 0; t < numBms; t++) {
        if (!bmsLive[t] && skip[t] > 0) { skip[t]--; continue; }   // back off from a silent pack
        bmsReadAddr(1, t);                                         // each pack is addr 1 on its own UART
        skip[t] = bmsLive[t] ? 0 : BMS_RETRY;                      // online → poll every cycle
        // settings: read on first contact, then refresh every ~10 polls — but stagger the two
        // packs (BMS0 at tick 0,10,…; BMS1 at 5,15,…) so a failed read (~400ms) never blocks
        // both in the same poll, which would freeze the UI for ~0.8-1.3s.
        bool firstContact = bmsLive[t] && !wasLive[t];
        bool wantSet = (setTick % 10) == (uint8_t)(t * 5);
        if (bmsLive[t] && (firstContact || wantSet)) bmsReadSettings(1, t);
        wasLive[t] = bmsLive[t];
        if (!bmsLive[t]) { setOk[t] = false; setOk2[t] = false; }
    }
    if (busMux) xSemaphoreGive(busMux);
}
// Write a UINT32 control register (function 0x10, 2 registers) to BMS idx (addr 1, own bus).
static void bmsWrite(int idx, uint16_t reg, uint32_t val) {
    HardwareSerial &S = bmsPort(idx);
    uint8_t f[13] = {1, 0x10, (uint8_t)(reg >> 8), (uint8_t)reg, 0, 2, 4,
                     (uint8_t)(val >> 24), (uint8_t)(val >> 16), (uint8_t)(val >> 8), (uint8_t)val, 0, 0};
    uint16_t crc = mbCrc(f, 11); f[11] = crc & 0xFF; f[12] = crc >> 8;
    while (S.available()) S.read();
    S.write(f, 13); S.flush();
    uint32_t t0 = millis(); while (millis() - t0 < 40) { while (S.available()) S.read(); }   // drain the 8-byte echo
}
// Read one UINT32 control register back (function 0x03, 2 registers). false on no/bad reply.
static bool bmsReadReg(int idx, uint16_t reg, uint32_t *out) {
    HardwareSerial &S = bmsPort(idx);
    uint8_t req[8] = {1, 3, (uint8_t)(reg >> 8), (uint8_t)reg, 0, 2, 0, 0};
    uint16_t crc = mbCrc(req, 6); req[6] = crc & 0xFF; req[7] = crc >> 8;
    while (S.available()) S.read();
    S.write(req, 8); S.flush();
    uint8_t r[16]; int n = 0; uint32_t t0 = millis();
    while (millis() - t0 < 70) { while (S.available() && n < 16) r[n++] = S.read(); if (n >= 9) break; }
    if (n < 9 || r[0] != 1 || r[1] != 3 || r[2] != 4) return false;
    if ((r[7] | (r[8] << 8)) != mbCrc(r, 7)) return false;
    *out = (uint32_t)r[3] << 24 | r[4] << 16 | r[5] << 8 | r[6];
    return true;
}
// Write a control register, then read it back to confirm the BMS accepted the value.
// The read-back can be transiently slow/missed right after the write (BMS busy),
// so retry a few times before declaring failure — otherwise a good write reports
// as "didn't change" and the UI keeps the old value.
static bool bmsSet(int idx, uint16_t reg, uint32_t val) {
    if (busMux) xSemaphoreTake(busMux, portMAX_DELAY);   // exclusive bus access (poll runs on the other core)
    bmsWrite(idx, reg, val);
    uint32_t rb = 0; bool ok = false;
    for (int t = 0; t < 4; t++) {
        if (bmsReadReg(idx, reg, &rb) && rb == val) { ok = true; break; }
        delay(25);
    }
    if (busMux) xSemaphoreGive(busMux);
    if (!ok) Serial.printf("[bms] verify failed: reg %04X wrote %lu, read %lu\n", reg, (unsigned long)val, (unsigned long)rb);
    return ok;
}
