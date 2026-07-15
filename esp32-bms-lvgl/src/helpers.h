// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
static uint32_t socColor(float soc) { return soc >= 60 ? C_ACCENT : soc >= 30 ? C_WARN : C_BAD; }
// Single source of truth for the status pill — uses REAL BMS state (fault bitmask,
// actual MOSFET + balancer flags) not just a current threshold. Shared by the
// device dashboard and the web /api so they never diverge.
// Canonical English status (used by MQTT/HA + web portal — kept stable for automations).
// keyOut (optional) returns the i18n StrKey so the device UI can show it localized.
static const char *bmsStatusStr(int t, bool live, uint32_t *col, int *keyOut = nullptr) {
    const Bms &b = bms[t];
    int k; const char *s;
    if (!live)                  { *col = C_BAD;    k = K_OFFLINE;     s = "Offline"; }
    else if (b.errFlags)        { *col = C_BAD;    k = K_ALARM;       s = "Alarm"; }   // BMS reports a protection/warning
    else if (!b.disMos || !b.chgMos) { *col = C_WARN; k = K_FET_OFF;  s = "FET off"; }
    else if (b.balWork)         { *col = C_CYAN;   k = K_BALANCING;   s = "Balancing"; }
    else if (b.i > 0.5f)        { *col = C_ACCENT; k = K_CHARGING;    s = "Charging"; }
    else if (b.i < -0.5f)       { *col = C_DISCHG; k = K_DISCHARGING; s = "Discharging"; }
    else if (b.soc >= 99)       { *col = C_ACCENT; k = K_FULL;        s = "Full"; }
    else                        { *col = C_MUTED;  k = K_IDLE;        s = "Idle"; }
    if (keyOut) *keyOut = k;
    return s;
}
static uint32_t lerpColor(uint32_t a, uint32_t b, float t) {
    if (t < 0) t = 0; if (t > 1) t = 1;
    int ar = (a >> 16) & 0xff, ag = (a >> 8) & 0xff, ab = a & 0xff;
    int br = (b >> 16) & 0xff, bg = (b >> 8) & 0xff, bb = b & 0xff;
    return ((uint32_t)(ar + (br - ar) * t) << 16) | ((uint32_t)(ag + (bg - ag) * t) << 8) | (uint32_t)(ab + (bb - ab) * t);
}
// SOC ring colour driven by the ACTUAL charge level, so the ring's hue alone tells you the
// pack's state at a glance: red (empty) → amber → green (healthy) → violet (near full). The
// violet only engages above 90% — a full pack reads unmistakably different from a healthy one.
#define C_FULL 0x5a4be0             // deep cool blue-violet — the "full battery" hue (>90%); reads distinct from the green plateau
static uint32_t socRingColor(float soc) {
    if (soc >= 90) return lerpColor(C_ACCENT, C_FULL,  (soc - 90) / 10.0f);   // 90→100 : green → violet
    if (soc >= 55) return C_ACCENT;                                           // healthy plateau : green
    if (soc >= 30) return lerpColor(C_WARN,  C_ACCENT, (soc - 30) / 25.0f);   // 30→55  : amber → green
    return               lerpColor(C_BAD,    C_WARN,   soc / 30.0f);          // 0→30   : red   → amber
}
// Scale a colour's luminance toward black (k=0 → black, k=1 → unchanged). Used to fade the
// ring fill from a dim tail to a vivid leading edge so the arc reads as a glowing sweep.
static uint32_t dimColor(uint32_t c, float k) { return lerpColor(0x000000, c, k); }
// Cell balance heatmap: a cell's deviation from the pack mean (mV) → colour.
static uint32_t cellDevColor(float devMv) { return devMv < 10.0f ? C_ACCENT : devMv < 30.0f ? C_WARN : C_BAD; }
static uint32_t tempColor(float t) { return t >= 55 ? C_BAD : t >= 45 ? C_WARN : C_ACCENT; }
#define PACK_AH 100.0f
static float avgDrawW(int v, int nSamples);            // typical recent discharge power — defined after the history helpers
static void fmtMins(char *o, size_t n, int m, const char *pfx) {   // minutes → "8h30" / "2d4h", with an optional prefix
    if (m < 60) snprintf(o, n, "%s%dm", pfx, m);
    else if (m < 1440) snprintf(o, n, "%s%dh%02d", pfx, m / 60, m % 60);
    else snprintf(o, n, "%s%dd%dh", pfx, m / 1440, (m % 1440) / 60);
}
// estimated runtime (discharging) / time-to-full (charging), shorthand e.g. 8h30.
// When the pack is idle (no meaningful current), fall back to an estimate from
// recent average consumption (6h window, then 24h) — shown with a "~" prefix.
static void runtimeStr(int v, float soc, float i, float fullAh, char *o, size_t n, uint32_t *col) {
    if (i < -0.5f) {                                   // discharging → time left at the current rate
        fmtMins(o, n, (int)((soc / 100.0f * fullAh) / (-i) * 60.0f + 0.5f), "");
        *col = C_TEXT; return;
    }
    if (i > 0.5f) {                                    // charging → time to full
        fmtMins(o, n, (int)(((100.0f - soc) / 100.0f * fullAh) / i * 60.0f + 0.5f), "+");
        *col = C_ACCENT; return;
    }
    // idle → estimate from typical recent draw (prefer the 6h window, fall back to 24h)
    float aw = avgDrawW(v, 72); if (aw < 1.0f) aw = avgDrawW(v, 288);
    float packV = bms[v].v > 1.5f ? bms[v].v : 3.2f * NCELLS;
    float remWh = soc / 100.0f * fullAh * packV;
    if (aw >= 1.0f && remWh > 0) { fmtMins(o, n, (int)(remWh / aw * 60.0f + 0.5f), "~"); *col = C_TEXT; }
    else { snprintf(o, n, "--"); *col = C_MUTED; }     // no recent usage history yet → unknown
}
static void timeLabel(char *out, size_t n, float daysAgo, float span) {
    float minsAgo = daysAgo * 1440.0f;
    if (minsAgo < 1.0f) { snprintf(out, n, "now"); return; }
    if (span >= 2.0f) snprintf(out, n, "%.0fd", daysAgo);                   // ≥2 days → days
    else if (span >= 0.083f) snprintf(out, n, "%.0fh", daysAgo * 24.0f);    // ≥~2h → hours
    else snprintf(out, n, "%.0fm", minsAgo);                                // short history → minutes
}

// ============================================================================
//  LVGL draw wrappers — a thin Arduino_GFX-like layer over the LVGL draw API,
//  so the original drawing code ports almost verbatim. Text is anti-aliased.
// ============================================================================
static lv_layer_t *L = nullptr;
// Custom 1-bpp Montserrat (no anti-aliasing) — same letterforms/metrics as the
// built-in 4-bpp fonts but far cheaper to render (no per-pixel alpha blending).
LV_FONT_DECLARE(mont1_10) LV_FONT_DECLARE(mont1_12) LV_FONT_DECLARE(mont1_14)
LV_FONT_DECLARE(mont1_16) LV_FONT_DECLARE(mont1_20) LV_FONT_DECLARE(mont1_28)
LV_FONT_DECLARE(mont1_48)
// Chinese needs CJK glyphs (Montserrat has none): a subset Hiragino font at the label sizes
// (10-20). The big sizes (28/48) only ever render digits, so they stay Montserrat.
LV_FONT_DECLARE(cjk_10) LV_FONT_DECLARE(cjk_12) LV_FONT_DECLARE(cjk_14)
LV_FONT_DECLARE(cjk_16) LV_FONT_DECLARE(cjk_20)
// Arabic (LVGL bidi+shaping) and Hindi/Devanagari each bring their own subset font, label sizes only.
// Those fonts have no Latin glyphs, so digits/units would render as boxes — give them a Montserrat
// fallback at runtime (generated structs are const → copy into RAM and set .fallback in initScriptFonts).
LV_FONT_DECLARE(ar_10) LV_FONT_DECLARE(ar_12) LV_FONT_DECLARE(ar_14) LV_FONT_DECLARE(ar_16) LV_FONT_DECLARE(ar_20)
LV_FONT_DECLARE(hi_10) LV_FONT_DECLARE(hi_12) LV_FONT_DECLARE(hi_14) LV_FONT_DECLARE(hi_16) LV_FONT_DECLARE(hi_20)
static lv_font_t arFont[5], hiFont[5];   // RAM copies of ar_*/hi_* with a Latin fallback
static void initScriptFonts() {
    const lv_font_t *ar[5] = {&ar_10, &ar_12, &ar_14, &ar_16, &ar_20};
    const lv_font_t *hi[5] = {&hi_10, &hi_12, &hi_14, &hi_16, &hi_20};
    const lv_font_t *mo[5] = {&mont1_10, &mont1_12, &mont1_14, &mont1_16, &mont1_20};
    for (int i = 0; i < 5; i++) { arFont[i] = *ar[i]; arFont[i].fallback = mo[i]; hiFont[i] = *hi[i]; hiFont[i].fallback = mo[i]; }
}
static inline int fontIdx(int sz) { return sz <= 10 ? 0 : sz <= 12 ? 1 : sz <= 14 ? 2 : sz <= 16 ? 3 : 4; }
// Pick the font for a size given the active language. F10..F48 resolve through this so every
// existing call site automatically uses the right script font (no per-call changes).
static inline const lv_font_t *curFont(int sz) {
    if (g_lang == LANG_ZH) switch (sz) {
        case 10: return &cjk_10; case 12: return &cjk_12; case 14: return &cjk_14;
        case 16: return &cjk_16; case 20: return &cjk_20;   // 28/48 fall through → Montserrat (digits only)
    }
    if (g_lang == LANG_AR && sz <= 20) return &arFont[fontIdx(sz)];   // 28/48 → Montserrat (digits)
    if (g_lang == LANG_HI && sz <= 20) return &hiFont[fontIdx(sz)];
    switch (sz) {
        case 10: return &mont1_10; case 12: return &mont1_12; case 14: return &mont1_14;
        case 16: return &mont1_16; case 20: return &mont1_20; case 28: return &mont1_28;
        default: return &mont1_48;
    }
}
#define F10 curFont(10)
#define F12 curFont(12)
#define F16 curFont(16)
#define F20 curFont(20)
#define F28 curFont(28)
#define F48 curFont(48)

// Pooled label text so the string outlives LVGL's deferred draw dispatch. Slots must hold the
// longest drawn string (incl. multibyte UTF-8): Russian labels reach ~40 bytes and WiFi status
// with an SSID can hit ~57 → 64-byte slots. Slot count covers the busiest frame (dashboard ~60).
#define TPOOL_N 96
#define TPOOL_W 64
static char tpool[TPOOL_N][TPOOL_W];
static int tpi = 0;
static const char *pool(const char *s) { char *d = tpool[tpi]; tpi = (tpi + 1) % TPOOL_N; snprintf(d, TPOOL_W, "%s", s); return d; }

