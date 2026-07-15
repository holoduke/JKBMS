// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
static void drawTabs(bool autoActive, float prog) {
    const int y = 6, h = 28;
    const int tabX[2] = {TAB1_X, TAB2_X};
    for (int t = 0; t < numBms; t++) {
        int x = tabX[t]; bool on = (view == t);
        bool offline = !demoMode && !bmsLive[t];   // real mode + this BMS isn't answering
        uint32_t bg = on ? (offline ? C_BAD : C_ACCENT) : C_CARD;
        fRect(x, y, TAB_W, h, 8, bg);
        if (!on) dRect(x, y, TAB_W, h, 8, offline ? C_BAD : C_BORDER);
        char lbl[20]; snprintf(lbl, sizeof(lbl), "%s %d", T(K_BAT), t + 1);
        cText(lbl, x + TAB_W / 2, y + h / 2, F16, on ? C_BG : (offline ? C_BAD : C_MUTED));
        if (on && autoActive && numBms >= 2) fRect(x + 6, y + h - 3, (int)((TAB_W - 12) * prog), 2, 0, C_BG);
    }
    // wifi status icon, just right of the battery buttons (green = connected, grey = not)
    // centred on y+h/2 — same vertical centre as the weather glyph, temperature and clock
    int wifiX = 210;   // status cluster starts at the right column (where the gauges/tiles begin, rx=200), independent of tab width
    int midY = y + h / 2;   // shared vertical centre for the whole top-bar row
    drawWifiSmall(wifiX, midY, WiFi.status() == WL_CONNECTED ? C_ACCENT : C_MUTED);
    if (wxOk) {   // today's weather: glyph + temp, right of the wifi icon
        bool stale = wxStale();                                     // offline / not refreshed → grey it out
        uint32_t wcol = stale ? C_MUTED : C_TEXT;
        int wx = wifiX + 36; drawWxIcon(wx, midY + 1, wxCurCode, 1.15f, stale);   // +1 centres the sun glyph (its art sits slightly high)
        char wt[6]; snprintf(wt, sizeof(wt), "%d", wxCurTemp);
        int tw = textW(wt, F16), tx = wx + 18;
        cText(wt, tx + tw / 2, midY, F16, wcol);                    // centred on midY, same as the clock
        fCircle(tx + tw + 3, midY - 5, 1, wcol);                    // degree mark, upper-right of the digits
        wxBoxL = wx - 16; wxBoxR = tx + tw + 8;                     // tap zone → opens the forecast popup
    } else { wxBoxL = wxBoxR = 0; }
    struct tm ti;
    if (getLocalTime(&ti, 0)) {   // TZ already set once for this task in setup()
        char ts[6]; snprintf(ts, sizeof(ts), "%02d:%02d", ti.tm_hour, ti.tm_min);
        cText(ts, BED_X - 36, midY, F16, C_TEXT);
    }
    fRect(BED_X, y, BED_W, h, 8, C_CARD);
    dRect(BED_X, y, BED_W, h, 8, C_BORDER);
    drawLock(BED_X + BED_W / 2, y + h / 2, C_MUTED);
    fRect(GEAR_X, GEAR_Y, GEAR_W, h, 8, C_CARD);
    dRect(GEAR_X, GEAR_Y, GEAR_W, h, 8, C_BORDER);
    drawGear(GEAR_X + GEAR_W / 2, GEAR_Y + h / 2, 7, C_MUTED, C_CARD);
    if (updAvail) {   // firmware update available → bare green arrow, now with room between weather and clock
        int ux = BED_X - 84;
        icoUpdate(ux, midY, C_ACCENT);
        updBoxL = ux - 12; updBoxR = ux + 12;
    } else { updBoxL = updBoxR = 0; }
}
static void drawRing(int cx, int cy, int ro, int ri, float pct, uint32_t base, bool stale = false) {
    ring(cx, cy, ro, ri, 0, 360, C_BORDER);          // full track
    if (!stale) {
        // `base` is the pack's charge-level hue (red→amber→green→violet — see socRingColor).
        // The whole arc shares that hue; within it the fill ramps from a dim tail at the bottom
        // to the vivid base at the leading edge, so it reads as a glowing sweep AND its colour
        // shifts with the actual %: a full pack glows violet, a healthy one green, a low one red.
        float ff = pct >= 99.5f ? 1.0f : (pct > 0.5f ? pct / 100.0f : 0.0f);
        const int N = 40;                             // segments around the full circle (9° each)
        int filled = (int)(ff * N + 0.5f); if (filled < 1 && ff > 0) filled = 1;
        for (int s = 0; s < N; s++) {
            if ((float)s / N >= ff) break;
            int a0 = (270 + (int)((float)s / N * 360)) % 360;
            int a1 = (270 + (int)((float)(s + 1) / N * 360)) % 360; if (a1 == 0) a1 = 360;
            float g = filled > 1 ? (float)s / (filled - 1) : 1.0f;   // 0 = tail (bottom) → 1 = leading edge
            ring(cx, cy, ro, ri, a0, a1, dimColor(base, 0.6f + 0.4f * g));   // dim tail → vivid head (floor keeps the deep full-hue legible)
        }
    }
    if (stale) { cText("--", cx, cy - 6, F48, C_MUTED); return; }
    char buf[8]; snprintf(buf, sizeof(buf), "%d", (int)(pct + 0.5f));
    cText(buf, cx, cy - 6, F48, base);   // big % in the pack's charge-level colour
    cText("%", cx, cy + 30, F16, C_MUTED);
}
// Charging spinner: a thin track + a comet-tail arc orbiting just outside the SOC ring.
// Built from N short segments whose opacity fades from the bright leading head down the
// tail, so it reads as a glowing trail when it turns. Angle is time-based (millis) → the
// rotation speed is constant regardless of frame rate.
static void drawSpinner(int cx, int cy, uint32_t nowMs, uint32_t col = C_ACCENT) {
    const int ro = 82, ri = 80;                       // 2px thin, ~6px outside the 74px SOC ring
    ring(cx, cy, ro, ri, 0, 360, C_BORDER);           // faint full track
    const int N = 9, seg = 9;                         // 9 segments × 9° ≈ 80° comet tail
    float head = fmodf(nowMs * 0.45f, 360.0f);        // ~1.25 rev/sec leading edge
    for (int k = 0; k < N; k++) {
        int a0 = (((int)(head - (k + 1) * seg)) % 360 + 360) % 360;
        int a1 = (a0 + seg) % 360; if (a1 == 0) a1 = 360;
        lv_opa_t opa = (lv_opa_t)(40 + (215 * (N - 1 - k)) / (N - 1));   // head ~255 → tail ~40
        ringA(cx, cy, ro, ri, a0, a1, col, opa);      // matches the SOC ring's charge-level hue
    }
}
static void drawTile(int x, int y, int w, int h, const char *label, const char *val, const char *unit, uint32_t valCol) {
    cardBg(x, y, w, h);
    lText(label, x + 8, y + 6, F10, C_MUTED);   // title size matches CAPACITY/POWER DRAW (F10)
    if (unit) {
        lText(val, x + 8, y + 24, F20, valCol);
        lText(unit, x + 8, y + h - 16, F12, C_MUTED);
    } else {
        // value vertically centred in the area below the label
        lv_point_t sz; lv_text_get_size(&sz, val, F20, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
        int top = y + 24, bot = y + h - 4;
        lText(val, x + 8, top + (bot - top - sz.y) / 2, F20, valCol);
    }
}
// Voltage tile: no title — the big "%.2fV" sits at the top, with the three MOSFET/balancer
// statuses below, each a short translated label + a state dot (green = on, red = off; the
// balancer's off state is muted since idle is normal).
static void drawVoltTile(int x, int y, int w, int h, const Bms &b, bool stale = false) {
    cardBg(x, y, w, h);
    char vbuf[10]; if (stale) snprintf(vbuf, sizeof(vbuf), "--"); else snprintf(vbuf, sizeof(vbuf), "%.2fV", b.v);
    lText(vbuf, x + 8, y + 4, F20, stale ? C_MUTED : C_TEXT);
    const int key[3] = {K_M_CHG, K_M_DIS, K_M_BAL};
    const bool on[3] = {b.chgMos, b.disMos, b.balWork};
    const uint32_t offCol[3] = {C_BAD, C_BAD, C_MUTED};   // chg/dis off is notable (red); balancer off is normal (grey)
    for (int r = 0; r < 3; r++) {
        int ry = y + 29 + r * 13;
        lText(T(key[r]), x + 8, ry, F10, C_MUTED);
        uint32_t dc = stale ? C_MUTED : (on[r] ? C_ACCENT : offCol[r]);
        fCircle(x + w - 10, ry + 7, 3, dc);   // +7 sits on the F10 label's optical centre
    }
}
static void drawTempsTile(int x, int y, int w, int h, float mos, float t1, float t2, bool stale = false) {
    cardBg(x, y, w, h);
    const char *lbl[3] = {T(K_MOS), T(K_T1), T(K_T2)}; float v[3] = {mos, t1, t2};
    for (int r = 0; r < 3; r++) {
        int ry = y + 12 + r * 19;
        lText(lbl[r], x + 8, ry + 2, F10, C_MUTED);
        // an unwired probe reads a saturated sentinel (~±200C) → show n/c, not a fake temp
        bool noProbe = (v[r] < -50 || v[r] > 120);   // saturated sentinel → n/c (applies to MOS + both probes)
        if (stale || noProbe) { lText("--", x + 34, ry, F12, C_MUTED); continue; }
        char buf[8]; snprintf(buf, sizeof(buf), "%.0fC", v[r]);
        lText(buf, x + 34, ry, F12, tempColor(v[r]));
    }
}
static void drawStatsTile(int x, int y, int w, int h, float pkChg, float pkDis, uint32_t upSec, const char *rt, uint32_t rtCol, bool stale = false) {
    cardBg(x, y, w, h);
    const char *lbl[4] = {T(K_PK_CHG), T(K_PK_DIS), T(K_UPTIME), T(K_REMAIN)};
    char val[4][10];
    snprintf(val[0], sizeof(val[0]), "%.0fW", pkChg);
    snprintf(val[1], sizeof(val[1]), "%.0fW", pkDis);
    uint32_t m = upSec / 60;
    if (m >= 6000) snprintf(val[2], sizeof(val[2]), "%lud%luh", (unsigned long)(m / 1440), (unsigned long)((m % 1440) / 60));   // ≥100h → days
    else snprintf(val[2], sizeof(val[2]), "%luh%02lu", (unsigned long)(m / 60), (unsigned long)(m % 60));
    snprintf(val[3], sizeof(val[3]), "%s", rt);
    uint32_t vc[4] = {C_ACCENT, C_WARN, C_TEXT, rtCol};
    if (stale) { for (int r = 0; r < 4; r++) { if (r != 2) { snprintf(val[r], sizeof(val[r]), "--"); vc[r] = C_MUTED; } } }  // uptime still real
    for (int r = 0; r < 4; r++) {
        int ry = y + 8 + r * 15;
        lText(lbl[r], x + 8, ry, F10, C_MUTED);
        lText(val[r], x + w - textW(val[r], F10) - 8, ry, F10, vc[r]);
    }
}
static void drawCells(int x, int y, int w, int h, const Bms &b, bool stale = false) {
    cardBg(x, y, w, h);
    int n = b.nCells; if (n < 1) n = 1; if (n > MAXCELLS) n = MAXCELLS;
    float lo = 9, hi = 0, sum = 0;
    for (int i = 0; i < n; i++) { float c = b.cell[i]; if (c < lo) lo = c; if (c > hi) hi = c; sum += c; }
    float mean = sum / n;   // heatmap: colour each cell by its deviation from the pack mean
    char hdr[28];
    if (stale) snprintf(hdr, sizeof(hdr), "%s  --", T(K_CELLS));
    else snprintf(hdr, sizeof(hdr), "%s  %dmV", T(K_CELLS), (int)((hi - lo) * 1000));
    icoCells(x + 8, y + 7, C_MUTED); lText(hdr, x + 22, y + 6, F10, C_MUTED);   // title size matches CAPACITY (F10)
    if (!stale && b.balWork) {                 // balancer active → show its current, right-aligned in the header
        char bt[12]; snprintf(bt, sizeof(bt), "%.1fA", b.balCur);
        int tw = textW(bt, F10);
        fCircle(x + w - 14 - tw - 5, y + 10, 3, C_CYAN);
        lText(bt, x + w - 8 - tw, y + 6, F10, C_CYAN);
    }
    // adaptive grid: 1 column with bars for small packs, 2-3 columns for bigger ones
    int cols = n <= 6 ? 1 : n <= 16 ? 2 : 3;
    int rows = (n + cols - 1) / cols;
    const int top = y + 22, cw = (w - 8) / cols; int rh = (h - 26) / rows; if (rh > 18) rh = 18;
    for (int i = 0; i < n; i++) {
        int col = i / rows, row = i % rows;
        int cxo = x + 6 + col * cw, ry = top + row * rh, midY = ry + (rh - 9) / 2;
        char cl[5]; snprintf(cl, sizeof(cl), "C%d", i + 1);
        lText(cl, cxo, midY, F10, C_MUTED);
        float devMv = fabsf(b.cell[i] - mean) * 1000.0f;        // distance from the mean → balance colour
        uint32_t c = stale ? C_MUTED : cellDevColor(devMv);     // green balanced · amber drifting · red outlier
        char cv[8]; if (stale) snprintf(cv, sizeof(cv), "--"); else snprintf(cv, sizeof(cv), "%.2f", b.cell[i]);
        lText(cv, cxo + cw - 8 - textW(cv, F10), midY, F10, c);
        if (cols == 1 && !stale) {   // room for a fill bar only in single-column mode
            int bx = cxo + 22, bw = cw - 22 - 36, by = ry + 3, bh = rh - 6;
            float frac = (b.cell[i] - 3.0f) / 0.6f; frac = frac < 0.05f ? 0.05f : frac > 1 ? 1 : frac;
            fRect(bx, by, bw, bh, 2, C_BORDER); fRect(bx, by, (int)(bw * frac), bh, 2, c);
        }
    }
}
static void fmtWh(char *buf, size_t n, float wh) {
    if (wh >= 1000.0f) snprintf(buf, n, "%.2fkWh", wh / 1000.0f);
    else snprintf(buf, n, "%.0fWh", wh);
}
// Energy drawn from a pack ("spent") over the last `nSamples` history points.
// History is logged every HIST_INTERVAL_MS only while the pack is live, so this
// assumes roughly continuous logging (gaps from downtime shorten the real window).
static float whSpent(int v, int nSamples) {
    int cnt = histCount[v]; if (cnt <= 0) return 0;
    int start = cnt - nSamples; if (start < 0) start = 0;
    const float perH = HIST_INTERVAL_MS / 3600000.0f;          // 5 min = 1/12 h
    float wh = 0;
    for (int i = start; i < cnt; i++) {                         // histPwr is charge-positive → discharge is negative
        int w = histPwr[v][i];
        if (w < 0) wh += -w * perH;
    }
    return wh;
}
// Energy charged INTO the pack over the last nSamples (the positive-power counterpart of whSpent).
static float whGained(int v, int nSamples) {
    int cnt = histCount[v]; if (cnt <= 0) return 0;
    int start = cnt - nSamples; if (start < 0) start = 0;
    const float perH = HIST_INTERVAL_MS / 3600000.0f;
    float wh = 0;
    for (int i = start; i < cnt; i++) { int w = histPwr[v][i]; if (w > 0) wh += w * perH; }
    return wh;
}
// Average discharge power (W) over the last nSamples, divided by the *actual*
// elapsed window (so a short history doesn't deflate the rate). Counts idle time
// in the denominator → a realistic "typical net draw" for runtime estimates.
static float avgDrawW(int v, int nSamples) {
    int cnt = histCount[v]; if (cnt <= 0) return 0;
    int span = cnt < nSamples ? cnt : nSamples;
    float hours = span * (HIST_INTERVAL_MS / 3600000.0f);
    return hours > 0.01f ? whSpent(v, nSamples) / hours : 0;
}
// Total pack energy (Wh) = full Ah × nominal 3.2V/cell, cell count inferred from voltage.
static float packTotalWh(int t) {
    float fullAh = (!demoMode && bmsLive[t]) ? packFullAh[t] : PACK_AH;
    float v = bms[t].v;
    int cells = bms[t].nCells > 0 ? bms[t].nCells           // prefer the detected series count
              : (v > 1.5f) ? (int)(v / 3.3f + 0.5f) : NCELLS;
    if (cells < 1) cells = NCELLS;
    return fullAh * cells * 3.2f;
}
static void drawEnergyTile(int x, int y, int w, int h, float totalWh, float remAh, float wh24, float wh6, int hcount, bool stale) {
    cardBg(x, y, w, h);
    icoBattery(x + 8, y + 6, C_MUTED); lText(T(K_CAPACITY), x + 24, y + 6, F10, C_MUTED);
    char buf[12];
    if (stale) snprintf(buf, sizeof(buf), "--"); else fmtWh(buf, sizeof(buf), totalWh);
    lText(buf, x + 8, y + 22, F16, C_ACCENT);                  // headline: total pack capacity
    if (!stale) { char ah[10]; snprintf(ah, sizeof(ah), "%.0fAh", remAh); lText(ah, x + w - 8 - textW(ah, F12), y + 25, F12, C_MUTED); }   // remaining Ah, right
    line(x + 8, y + 48, x + w - 8, y + 48, C_BORDER, 170);
    float val[2] = {wh24, wh6};   // energy drawn (used) over each window (24h, 6h)
    for (int r = 0; r < 2; r++) {
        int ry = y + 56 + r * 20;
        int win = r ? 72 : 288, have = hcount < win ? hcount : win; float hrs = have * 5.0f / 60.0f;   // real span until the ring fills
        char lb[8];
        if (have >= win) snprintf(lb, sizeof(lb), "%dh", r ? 6 : 24);
        else if (hrs >= 1.0f) snprintf(lb, sizeof(lb), "%.0fh", hrs);
        else snprintf(lb, sizeof(lb), "%.0fm", hrs * 60.0f);
        lText(lb, x + 8, ry, F10, C_MUTED);
        if (stale) { lText("--", x + w - textW("--", F12) - 8, ry, F12, C_MUTED); continue; }
        fmtWh(buf, sizeof(buf), val[r]);
        char pc[8]; snprintf(pc, sizeof(pc), "%d%%", totalWh > 1 ? (int)(val[r] / totalWh * 100.0f + 0.5f) : 0);
        int pcw = textW(pc, F10);                                  // % of total capacity, small + dim, far right
        lText(pc, x + w - 8 - pcw, ry + 1, F10, C_MUTED);
        lText(buf, x + w - 8 - pcw - 5 - textW(buf, F12), ry, F12, C_WARN);   // Wh just left of it
    }
}
static void drawPowerGraph(int x, int y, int w, int h, const Bms &b) {
    cardBg(x, y, w, h);
    // Window is stored draw-positive (discharge up, charge down). Show it single-sided and
    // always positive: while charging it's the "Charge" power, while discharging it's the
    // "Power draw" — title + line colour track the live current direction.
    bool charging = b.i > 0.5f;
    uint32_t gcol = charging ? C_ACCENT : C_CYAN;
    char ph[24]; snprintf(ph, sizeof(ph), "%s  W", charging ? T(K_M_CHG) : T(K_POWER_DRAW));
    icoBolt(x + 8, y + 6, gcol); lText(ph, x + 21, y + 6, F10, C_MUTED);
    if (b.pwrCount < 2) { cText(T(K_COLLECTING), x + w / 2, y + h / 2, F12, C_MUTED); return; }
    const int lblW = 24, gx = x + 8 + lblW, gy = y + 22, gw = w - 14 - lblW, gh = h - 38, base = gy + gh;
    int cnt = b.pwrCount > NCAP ? NCAP : b.pwrCount;
    auto pv = [&](int i) { float v = charging ? -b.pwr[i] : b.pwr[i]; return v < 0 ? 0.0f : v; };   // current-mode magnitude
    float hi = 0;
    for (int i = 0; i < cnt; i++) { float v = pv(i); if (v > hi) hi = v; }
    if (hi < 50) hi = 50;   // min span → no sawtooth on idle noise
    for (int k = 0; k < 5; k++) line(gx + (int)((float)k / 4 * gw), gy, gx + (int)((float)k / 4 * gw), gy + gh, C_BORDER, 170);
    line(gx, base, gx + gw, base, C_BORDER, 170);   // zero baseline at the bottom
    char lb[8];
    snprintf(lb, sizeof(lb), "%d", (int)hi); lText(lb, x + 4, gy - 3, F10, C_MUTED);
    lText("0", x + 4, base - 9, F10, C_MUTED);
    int px = -1, py = -1;
    for (int i = 0; i < cnt; i++) {
        int sx = gx + (int)((float)i / (cnt - 1) * gw);
        int sy = base - (int)(pv(i) / hi * gh);
        fillCol(sx, sy, base, gcol);                            // gradient fill from line → baseline
        if (px >= 0) line(px, py, sx, sy, gcol, LV_OPA_COVER, 2);
        px = sx; py = sy;
    }
    for (int k = 0; k < 5; k++) {
        int fx = gx + (int)((float)k / 4 * gw);
        float minsAgo = b.pwrSpanMin * (1.0f - k / 4.0f);
        char lbl[8];
        if (minsAgo < 0.05f) snprintf(lbl, sizeof(lbl), "now");
        else if (b.pwrSpanMin < 2.0f) snprintf(lbl, sizeof(lbl), "%.0fs", minsAgo * 60.0f);   // <2 min → seconds
        else snprintf(lbl, sizeof(lbl), "%.0fm", minsAgo);
        if (k == 0) lText(lbl, fx, base + 6, F10, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F10), base + 6, F10, C_MUTED);
        else cText(lbl, fx, base + 11, F10, C_MUTED);
    }
}
static void drawCapacityGraph(int x, int y, int w, int h, const Bms &b) {
    cardBg(x, y, w, h);
    char hdr[40];
    if (b.capSpanDays >= 2.0f) snprintf(hdr, sizeof(hdr), "%s   %.0f %s", T(K_CAPACITY), b.capSpanDays, T(K_DAYS));
    else if (b.capCount >= 2) snprintf(hdr, sizeof(hdr), "%s   %.0f %s", T(K_CAPACITY), b.capSpanDays * 24.0f, T(K_HOURS));
    else snprintf(hdr, sizeof(hdr), "%s", T(K_CAPACITY));
    lText(hdr, x + 8, y + 6, F10, C_MUTED);
    if (b.capCount < 2) { cText(T(K_COLLECTING), x + w / 2, y + h / 2, F12, C_MUTED); return; }
    const int lblW = 22, gx = x + 10 + lblW, gy = y + 26, gw = w - 20 - lblW, gh = h - 44, base = gy + gh;
    for (int p = 0; p <= 100; p += 50) {
        int yy = base - (int)(p / 100.0f * gh);
        line(gx, yy, gx + gw, yy, C_BORDER, 170);
        char lb[5]; snprintf(lb, sizeof(lb), "%d", p); lText(lb, x + 6, yy - 5, F10, C_MUTED);
    }
    for (int k = 0; k < 5; k++) line(gx + (int)((float)k / 4 * gw), gy, gx + (int)((float)k / 4 * gw), gy + gh, C_BORDER, 170);
    int cnt = (b.capCount < 2) ? 2 : (b.capCount > NCAP ? NCAP : b.capCount);
    int px = -1, py = -1;
    for (int i = 0; i < cnt; i++) {
        int sx = gx + (int)((float)i / (cnt - 1) * gw);
        int sy = base - (int)(b.cap[i] / 100.0f * gh);
        fillCol(sx, sy, base, C_ACCENT);   // gradient fill under the SOC trace
        if (px >= 0) line(px, py, sx, sy, C_ACCENT, LV_OPA_COVER, 2);
        px = sx; py = sy;
    }
    for (int k = 0; k < 5; k++) {
        int fx = gx + (int)((float)k / 4 * gw);
        char lbl[8]; timeLabel(lbl, sizeof(lbl), b.capSpanDays * (1.0f - k / 4.0f), b.capSpanDays);
        if (k == 0) lText(lbl, fx, base + 6, F10, C_MUTED);
        else if (k == 4) lText(lbl, fx - textW(lbl, F10), base + 6, F10, C_MUTED);
        else cText(lbl, fx, base + 11, F10, C_MUTED);
    }
}

// The two graphs only change when the active BMS changes, so they are rendered
// once into offscreen canvases and blitted as images each frame (saves ~336
// per-frame line draws). Sizes match their slots in renderBms().
#define POW_W 164
#define POW_H 86
#define CAP_W 164                   // match the power graph; energy panel fills the rest
#define CAP_H 96
static lv_obj_t *powCv = nullptr, *capCv = nullptr;
// Capacity graph: persisted 7-day SOC history (live) or genCap() curve (demo).
// Power graph: the fast 10-minute rolling window (always), decimated to fit.
#define POW_PTS 160                  // display columns for the power window
// Capacity downsample (2016 history → ≤NCAP). Only changes on a new 5-min sample or view
// switch, so it's NOT redone on the per-second power tick (see renderPwrCanvas).
static void prepCapData(int v) {
    Bms &b = bms[v];
    if (demoMode) return;                                   // demo: b.cap stays the genCap() curve
    int n = histCount[v];
    b.capSpanDays = n > 1 ? (float)(n - 1) / 288.0f : 0.0f;   // 288 samples/day (5 min)
    if (n <= NCAP) { for (int i = 0; i < n; i++) b.cap[i] = histCap[v][i]; b.capCount = n; }
    else {
        for (int j = 0; j < NCAP; j++) {
            int lo = (int)((int64_t)j * n / NCAP), hi = (int)((int64_t)(j + 1) * n / NCAP);
            if (hi <= lo) hi = lo + 1;
            float sc = 0; for (int i = lo; i < hi; i++) sc += histCap[v][i];
            b.cap[j] = sc / (hi - lo);
        }
        b.capCount = NCAP;
    }
}
// Power 10-minute window → ≤POW_PTS, newest-on-right. Cheap; refreshed every ~1s.
static void prepPwrData(int v) {
    Bms &b = bms[v];
    int pn = pwrWinN[v];
    b.pwrSpanMin = (pn > 1 ? (pn - 1) : 0) * (PWR_DT / 1000.0f) / 60.0f;   // (n-1) intervals between first & last
    if (pn <= POW_PTS) { for (int i = 0; i < pn; i++) b.pwr[i] = pwrWin[v][i]; b.pwrCount = pn; }
    else {
        for (int j = 0; j < POW_PTS; j++) {
            int lo = (int)((int64_t)j * pn / POW_PTS), hi = (int)((int64_t)(j + 1) * pn / POW_PTS);
            if (hi <= lo) hi = lo + 1;
            float sp = 0; for (int i = lo; i < hi; i++) sp += pwrWin[v][i];
            b.pwr[j] = sp / (hi - lo);
        }
        b.pwrCount = POW_PTS;
    }
}
static void renderPwrCanvas() {
    if (!powCv) return;
    prepPwrData(view);
    lv_layer_t lyr;
    lv_canvas_init_layer(powCv, &lyr); L = &lyr;
    fRect(0, 0, POW_W, POW_H, 0, C_BG);
    drawPowerGraph(0, 0, POW_W, POW_H, bms[view]);
    lv_canvas_finish_layer(powCv, &lyr);
}
static void renderCapCanvas() {
    if (!capCv) return;
    prepCapData(view);
    lv_layer_t lyr;
    lv_canvas_init_layer(capCv, &lyr); L = &lyr;
    fRect(0, 0, CAP_W, CAP_H, 0, C_BG);
    drawCapacityGraph(0, 0, CAP_W, CAP_H, bms[view]);
    lv_canvas_finish_layer(capCv, &lyr);
}
static void renderGraphs() { renderPwrCanvas(); renderCapCanvas(); }   // both (view switch / startup)
static void blitCanvas(lv_obj_t *cv, int x, int y, int w, int h) {
    lv_draw_image_dsc_t id; lv_draw_image_dsc_init(&id);
    id.src = lv_canvas_get_image(cv);
    lv_area_t a = {x, y, x + w - 1, y + h - 1};
    lv_draw_image(L, &id, &a);
}
static void switchView(int v) { if (v == V_BMS2 && numBms < 2) v = V_BMS1; view = v; renderGraphs(); }   // gauges read from the continuously-polled cache → instant

static void renderWeatherPopup();   // defined below (with the other modals)
static void renderUpdatePopup();
static void renderUpdating();
static void updBtnRect(int *bx, int *by, int *bw, int *bh) {   // "Update now" button rect in the update modal
    int mw = Wd - 80, mh = 150, my = (Ht - mh) / 2;
    *bw = 150; *bh = 34; *bx = (Wd - *bw) / 2; *by = my + 96; (void)mw;
}
static void renderBms() {
    const Bms &b = bms[view];
    uint32_t now = millis();
    bool autoActive = (now >= manualUntil);
    float prog = autoActive ? (float)(now - lastSwitch) / intervalMs : 0;
    if (prog > 1) prog = 1; if (prog < 0) prog = 0;
    drawTabs(autoActive, prog);

    const int cx = 100, cy = 178;
    // operational status — real BMS state (fault bitmask + actual MOSFET/balancer flags)
    uint32_t sc; int stk; bmsStatusStr(view, demoMode || bmsLive[view], &sc, &stk);
    const char *st = T(stk);
    int pw2 = textW(st, F12) + 28, px2 = cx - pw2 / 2, py2 = 52;
    fRect(px2, py2, pw2, 20, 10, C_CARD); dRect(px2, py2, pw2, 20, 10, C_BORDER);
    fCircle(px2 + 13, py2 + 11, 4, sc);
    lText(st, px2 + 22, py2 + 3, F12, sc);   // dot at +11 sits on the text's optical centre (lowercase x-height)
    if (b.errFlags && (demoMode || bmsLive[view])) {   // name the active protection(s) under the pill
        char al[44] = ""; int shown = 0;
        for (int bit = 0; bit < 29 && shown < 2; bit++)
            if (((b.errFlags >> bit) & 1) && errNameL(bit)[0]) {
                if (shown) strncat(al, " · ", sizeof(al) - strlen(al) - 1);
                strncat(al, errNameL(bit), sizeof(al) - strlen(al) - 1); shown++;
            }
        if (shown) cText(al, cx, py2 + 24, F10, C_BAD);
    }
    bool stale = (!demoMode && !bmsLive[view]);   // live mode, this pack isn't answering → no data
    uint32_t socCol = socRingColor(b.soc);
    drawRing(cx, cy, 74, 58, b.soc, socCol, stale);
    if (!stale && b.i > 0.5f) drawSpinner(cx, cy, now, socCol);   // comet spinner only while charging, tinted to match the ring
    int py = cy + 100;                            // power + current readout, big & centered, just below the ring
    if (stale) {
        cText("--", cx, py + 2, F28, C_MUTED);
    } else {
        bool idle = fabsf(b.i) < 0.5f;          // same ±0.5A dead-band as the status pill / runtime
        bool chg = (b.i >= 0);
        uint32_t pcol = idle ? C_MUTED : chg ? C_ACCENT : C_DISCHG;   // grey idle / green charge / purple discharge
        char pw[10], cu[10];
        snprintf(pw, sizeof(pw), "%.0fW", fabsf(b.v * b.i));
        if (fabsf(b.i) < 100) snprintf(cu, sizeof(cu), "%.1fA", fabsf(b.i));
        else snprintf(cu, sizeof(cu), "%.0fA", fabsf(b.i));
        lText(pw, cx - 16 - textW(pw, F28), py, F28, pcol);   // power: right-aligned, left of centre
        lText(cu, cx + 16, py, F28, pcol);                     // current: left-aligned, right of centre
        int aw = 7, ay = py + 8, ah = 15;                      // direction arrow, vertically centred with the W/A numbers
        if (idle) {}                                           // idle → no arrow
        else if (chg) tri(cx - aw, ay + ah, cx + aw, ay + ah, cx, ay, pcol);   // up = charging
        else          tri(cx - aw, ay, cx + aw, ay, cx, ay + ah, pcol);        // down = discharging
    }

    const int rx = 200, rw = Wd - rx - 8;
    const int ty = 40, th = 70, gap = 8;
    const int vW = 78, sW = 102, tpW = rw - vW - sW - 2 * gap;  // stats wider, temps + voltage narrower
    drawVoltTile(rx, ty, vW, th, b, stale);
    char rt[10]; uint32_t rtCol;
    float fullAh = (!demoMode && bmsLive[view]) ? packFullAh[view] : PACK_AH;
    runtimeStr(view, b.soc, b.i, fullAh, rt, sizeof(rt), &rtCol);
    uint32_t upSec = (!demoMode && bmsLive[view] && b.uptimeOk) ? b.uptime : now / 1000;   // BMS runtime if live, else device uptime
    drawStatsTile(rx + vW + gap, ty, sW, th, b.peakChg, b.peakDis, upSec, rt, rtCol, stale);
    drawTempsTile(rx + vW + gap + sW + gap, ty, tpW, th, b.tMos, b.tp1, b.tp2, stale);

    const int cellsW = rw - 8 - POW_W;          // ~1/3 cells, ~2/3 power graph
    drawCells(rx, 120, cellsW, 86, b, stale);
    blitCanvas(powCv, rx + cellsW + 8, 120, POW_W, POW_H);
    // bottom row, columns aligned with the row above: energy summary (left) + capacity graph (right)
    float remAh = b.soc / 100.0f * ((!demoMode && bmsLive[view]) ? packFullAh[view] : PACK_AH);   // remaining capacity
    drawEnergyTile(rx, 216, cellsW, CAP_H, packTotalWh(view), remAh, whSpent(view, 288), whSpent(view, 72), histCount[view], stale);
    blitCanvas(capCv, rx + cellsW + 8, 216, CAP_W, CAP_H);
    if (wxPopup) renderWeatherPopup();   // forecast modal overlays the dashboard
    if (updPopup) renderUpdatePopup();   // firmware-update modal
}

