// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
// ============================================================================
//  Settings screen — keyboard, settings tabs, info/weather/update popups
// ============================================================================
#define CLOSE_X (Wd - 40)
static const char *KB[3][4] = {
    {"1234567890", "qwertyuiop", "asdfghjkl", "zxcvbnm"},
    {"1234567890", "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"},
    {"1234567890", "@#$%&*-+()", "!?:;'/_=.", ",~[]{}<>"},
};
#define SROW_H 40
#define SROW_STEP 46
#define LIST_TOP 80
static int srowY(int i) { return 86 + i * SROW_STEP; }   // fixed rows (BMS tab)
static void srowAt(int y, const char *label, const char *val, uint32_t vc) {
    int x = 8, w = Wd - 16, h = SROW_H;
    cardBg(x, y, w, h);
    lText(label, x + 14, y + h / 2 - 9, F16, C_TEXT);
    lText(val, x + w - textW(val, F16) - 16, y + h / 2 - 9, F16, vc);
}
static void srow(int i, const char *label, const char *val, uint32_t vc) { srowAt(srowY(i), label, val, vc); }
// iOS-style pill toggle, right-aligned in a settings row
static void srowToggle(int y, const char *label, bool on) {
    int x = 8, w = Wd - 16, h = SROW_H;
    cardBg(x, y, w, h);
    lText(label, x + 14, y + h / 2 - 9, F16, C_TEXT);
    int tw = 44, th = 22, tx = x + w - 16 - tw, ty = y + h / 2 - th / 2;
    fRect(tx, ty, tw, th, th / 2, on ? C_ACCENT : C_BORDER);
    int kr = 8, kx = on ? tx + tw - kr - 3 : tx + kr + 3;
    fCircle(kx, ty + th / 2, kr, on ? C_BG : C_MUTED);
}

// ---- scrollable System list ----
static const uint8_t SYS_KEY[] = {
    K_AUTO_SWITCH, K_SWITCH_INTERVAL, K_BRIGHTNESS, K_AUTO_SLEEP, K_ECO_MODE, K_DIM_AFTER,
    K_TEMP_UNIT, K_TIME_FORMAT, K_WIFI_AUTO, K_DEMO_SPEED, K_SYSTEM_INFO, K_FIRMWARE, K_DEMO_MODE,
    K_SCREENSAVER, K_SCREENSAVER_AFTER, K_SCREENSAVER_FOR, K_AUTO_LOCK, K_LOCK_PIN,
    K_WEB_ADDRESS, K_WEB_USERNAME, K_WEB_PASSWORD, K_LANGUAGE, K_TIMEZONE};
#define SYS_ROWS ((int)(sizeof(SYS_KEY) / sizeof(SYS_KEY[0])))
static const char *sysLabel(int i) {            // localized row label; brightness keeps its "- / +" hint
    if (i == 2) { static char b[28]; snprintf(b, sizeof(b), "%s   - / +", T(K_BRIGHTNESS)); return b; }
    return T(SYS_KEY[i]);
}
static void dimStr(char *o, size_t n) {
    if (dimAfterSec == 0) snprintf(o, n, "%s", T(K_OFF));
    else if (dimAfterSec < 60) snprintf(o, n, "%ds", dimAfterSec);
    else snprintf(o, n, "%d min", dimAfterSec / 60);
}
static void saverStr(char *o, size_t n) {
    if (saverAfterSec == 0) snprintf(o, n, "%s", T(K_OFF));
    else if (saverAfterSec < 60) snprintf(o, n, "%ds", saverAfterSec);
    else if (saverAfterSec < 3600) snprintf(o, n, "%d min", saverAfterSec / 60);
    else snprintf(o, n, "%d hr", saverAfterSec / 3600);
}
static void saverShowStr(char *o, size_t n) {   // how long the timed saver stays before auto-returning (0 = until tapped)
    if (saverShowSec == 0) snprintf(o, n, "%s", T(K_UNTIL_TAP));
    else if (saverShowSec < 60) snprintf(o, n, "%ds", saverShowSec);
    else snprintf(o, n, "%d min", saverShowSec / 60);
}
static void sysVal(int i, char *o, size_t n, uint32_t *vc) {
    switch (i) {
        case 0: snprintf(o, n, "%s", autoSwitch ? T(K_ON) : T(K_OFF)); *vc = autoSwitch ? C_ACCENT : C_MUTED; break;
        case 1: snprintf(o, n, "%lus", (unsigned long)(intervalMs / 1000)); *vc = C_CYAN; break;
        case 2: snprintf(o, n, "%d%%", brightness); *vc = C_TEXT; break;
        case 3: if (autoSleepMin == 0) snprintf(o, n, "%s", T(K_NEVER)); else snprintf(o, n, "%d min", autoSleepMin); *vc = autoSleepMin ? C_CYAN : C_MUTED; break;
        case 4: snprintf(o, n, "%s", ecoMode ? T(K_ON) : T(K_OFF)); *vc = ecoMode ? C_ACCENT : C_MUTED; break;
        case 5: dimStr(o, n); *vc = dimAfterSec ? C_CYAN : C_MUTED; break;
        case 6: snprintf(o, n, "%s", tempF ? T(K_FAHRENHEIT) : T(K_CELSIUS)); *vc = C_CYAN; break;
        case 7: snprintf(o, n, "%s", fmt12 ? T(K_12_HOUR) : T(K_24_HOUR)); *vc = C_CYAN; break;
        case 8: snprintf(o, n, "%s", wifiAuto ? T(K_ON) : T(K_OFF)); *vc = wifiAuto ? C_ACCENT : C_MUTED; break;
        case 9: snprintf(o, n, "%dx", simSpeed); *vc = C_CYAN; break;
        case 10: snprintf(o, n, "%s", T(K_VIEW)); *vc = C_CYAN; break;
        case 12: snprintf(o, n, "%s", demoMode ? T(K_ON) : T(K_OFF)); *vc = demoMode ? C_ACCENT : C_MUTED; break;
        case 13: { const char *IN[7] = {T(K_OFF), "HUD", "Init", "Radar", "Arcade", "Security", "Nexus"}; snprintf(o, n, "%s", IN[idleScreen % 7]); *vc = idleScreen ? C_CYAN : C_MUTED; break; }
        case 14: saverStr(o, n); *vc = saverAfterSec ? C_CYAN : C_MUTED; break;
        case 15: saverShowStr(o, n); *vc = saverShowSec ? C_CYAN : C_MUTED; break;   // grouped with the other screensaver rows
        case 16: if (lockAfterSec == 0) snprintf(o, n, "%s", T(K_NEVER)); else if (lockAfterSec < 60) snprintf(o, n, "%ds", lockAfterSec); else if (lockAfterSec < 3600) snprintf(o, n, "%d min", lockAfterSec / 60); else snprintf(o, n, "%d hr", lockAfterSec / 3600); *vc = lockAfterSec ? C_CYAN : C_MUTED; break;
        case 17: snprintf(o, n, "%s", lockPin[0] ? T(K_PIN_SET) : T(K_PIN_NONE)); *vc = lockPin[0] ? C_CYAN : C_MUTED; break;
        case 18: if (WiFi.status() == WL_CONNECTED) { snprintf(o, n, "%s", WiFi.localIP().toString().c_str()); *vc = C_ACCENT; } else { snprintf(o, n, "no WiFi"); *vc = C_MUTED; } break;
        case 19: snprintf(o, n, "%s", webUser); *vc = C_CYAN; break;
        case 20: snprintf(o, n, "%s", webPass); *vc = C_CYAN; break;
        case 21: snprintf(o, n, "%s", LANG_NAME[g_lang]); *vc = C_CYAN; break;
        case 22: snprintf(o, n, "%s", TZDEFS[tzSel].name); *vc = C_CYAN; break;
        default: snprintf(o, n, "v" FW_VERSION); *vc = C_MUTED; break;
    }
}
static int sysViewH() { return Ht - LIST_TOP - 2; }
// + one row of bottom padding so the last entry can scroll clear of the panel's
// bottom edge (touch is unreliable in the last few px there).
static int sysContentH() { return SYS_ROWS * SROW_STEP + SROW_STEP; }
static int sysMaxScroll() { int m = sysContentH() - sysViewH(); return m > 0 ? m : 0; }
static void subTabGeom(int i, int *x, int *w) { int gap = 6; *w = (Wd - 16 - 2 * gap) / 3; *x = 8 + i * (*w + gap); }
static void drawCloseBtn() {
    int x = CLOSE_X, y = 8, w = 32, h = 26, cx = x + w / 2, cy = y + h / 2;
    fRect(x, y, w, h, 6, C_CARD); dRect(x, y, w, h, 6, C_BORDER);
    for (int o = -1; o <= 1; o++) { line(cx - 6, cy - 6 + o, cx + 6, cy + 6 + o, C_BAD); line(cx - 6, cy + 6 + o, cx + 6, cy - 6 + o, C_BAD); }
}
static void drawSubTabs() {
    static char bn[20]; snprintf(bn, sizeof(bn), "%s %d", T(K_BAT), cfgBms ? 2 : 1);
    const char *nm[3] = {bn, T(K_TAB_WIFI), T(K_TAB_SYSTEM)};
    for (int i = 0; i < 3; i++) {
        int x, w; subTabGeom(i, &x, &w); bool on = (subTab == i);
        fRect(x, 44, w, 30, 8, on ? C_ACCENT : C_CARD); if (!on) dRect(x, 44, w, 30, 8, C_BORDER);
        cText(nm[i], x + w / 2, 44 + 15, F16, on ? C_BG : C_MUTED);
    }
}
static void renderSysTab() {
    if (sysScroll > sysMaxScroll()) sysScroll = sysMaxScroll();
    for (int i = 0; i < SYS_ROWS; i++) {
        int y = LIST_TOP + i * SROW_STEP - sysScroll;
        if (y + SROW_H < LIST_TOP || y > Ht) continue;     // off-screen
        if (i == 0) srowToggle(y, sysLabel(i), autoSwitch);
        else if (i == 4) srowToggle(y, sysLabel(i), ecoMode);
        else if (i == 8) srowToggle(y, sysLabel(i), wifiAuto);
        else if (i == 12) srowToggle(y, sysLabel(i), demoMode);
        else { char val[28]; uint32_t vc; sysVal(i, val, sizeof(val), &vc); srowAt(y, sysLabel(i), val, vc); }
    }
    if (sysMaxScroll() > 0) {                               // scrollbar
        int tX = Wd - 6, tY = LIST_TOP, tH = sysViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)sysViewH() / sysContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)sysScroll / sysMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
}
// ---- editable BMS settings (derived from the web 0x01 settings frame) ----
// Modbus register = 0x1000 + (frame offset - 6). Values decode big-endian like the
// realtime block. All offsets here are < 250 so one 125-register read covers them.
enum FType { FT_U32, FT_U16, FT_I32, FT_I16, FT_U8, FT_I8 };
struct SetDef { const char *label; uint16_t off; uint8_t type; float scale; const char *unit; float vmin, vmax, vstep; };
// Ordered most-important-first (display order only; each entry's register `off`
// is independent, so reordering is safe). Grouped: pack basics → current limits →
// cell-voltage protection → SOC cal → balancing → charge profile → then the
// rarely-touched timing / temperature / sleep protections.
static const SetDef SETDEFS[] = {
    // pack basics
    {"Nominal cap",      130, FT_U32, 0.001f, "Ah", 1, 2000, 1},
    {"Cell count",       114, FT_U32, 1.0f,   "",   3, 32, 1},
    // current limits
    {"Max charge A",      50, FT_U32, 0.001f, "A",  1, 200, 1},
    {"Max discharge A",   62, FT_U32, 0.001f, "A",  1, 200, 1},
    // cell voltage protection
    {"Cell OVP",          18, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"Cell OVP recover",  22, FT_U32, 0.001f, "V",  2.4f, 4.20f, 0.01f},
    {"Cell UVP",          10, FT_U32, 0.001f, "V",  1.5f, 3.50f, 0.01f},
    {"Cell UVP recover",  14, FT_U32, 0.001f, "V",  1.6f, 3.60f, 0.01f},
    // SOC calibration
    {"SOC 100% volt",     30, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"SOC 0% volt",       34, FT_U32, 0.001f, "V",  1.5f, 3.50f, 0.01f},
    // balancing
    {"Balance start V",  138, FT_U32, 0.001f, "V",  2.5f, 4.20f, 0.01f},
    {"Balance trig dV",   26, FT_U32, 0.001f, "V",  0.005f, 0.50f, 0.005f},
    {"Max balance A",     78, FT_U32, 0.001f, "A",  0.1f, 2.0f, 0.1f},
    // charge profile (inverter/charger handshake)
    {"Req charge volt",   38, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"Req float volt",    42, FT_U32, 0.001f, "V",  2.5f, 4.25f, 0.01f},
    {"Power off volt",    46, FT_U32, 0.001f, "V",  1.5f, 3.20f, 0.01f},
    // current-protection timing
    {"Charge OCP delay",  54, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Charge OCP recov",  58, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Dischg OCP delay",  66, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Dischg OCP recov",  70, FT_U32, 1.0f,   "s",  1, 320, 1},
    {"Short-circ delay", 134, FT_U32, 1.0f,   "us", 0, 1000, 1},
    {"Short-circ recov",  74, FT_U32, 1.0f,   "s",  1, 256, 1},
    // temperature protection (Modbus stores these as 32-bit, not the BLE frame's u16)
    {"Charge OTP",        82, FT_U32, 0.1f,   "C",  20, 100, 1},
    {"Charge OTP recov",  86, FT_U32, 0.1f,   "C",  15, 95, 1},
    {"Dischg OTP",        90, FT_U32, 0.1f,   "C",  20, 100, 1},
    {"Dischg OTP recov",  94, FT_U32, 0.1f,   "C",  15, 95, 1},
    {"Charge UTP",        98, FT_I32, 0.1f,   "C",  -30, 20, 1},
    {"Charge UTP recov", 102, FT_I32, 0.1f,   "C",  -25, 25, 1},
    {"MOS OTP",          106, FT_I32, 0.1f,   "C",  50, 120, 1},
    {"MOS OTP recover",  110, FT_I32, 0.1f,   "C",  40, 110, 1},
    // sleep
    {"Smart sleep V",      6, FT_U32, 0.001f, "V",  2.0f, 3.60f, 0.01f},
};
#define NSET ((int)(sizeof(SETDEFS) / sizeof(SETDEFS[0])))
// settings that live in the tail region (need the 2nd read; setOk2)
static const SetDef TAILDEFS[] = {
    {"Heating start T",  284, FT_I8, 1.0f, "C", -30, 20, 1},
    {"Smart sleep hrs",  286, FT_U8, 1.0f, "h", 0, 240, 1},
};
#define NTAIL ((int)(sizeof(TAILDEFS) / sizeof(TAILDEFS[0])))
// on/off flags packed in the u16 control word at frame offset 282 (reg 0x1114)
struct BitDef { const char *label; uint16_t mask; };
static const BitDef BITDEFS[] = {
    {"Heating",            0x0001}, {"Disable temp sens", 0x0002},
    {"Display always on",  0x0010}, {"Smart sleep",       0x0040},
    {"Disable PCL",        0x0080}, {"Timed stored data", 0x0100},
    {"Charging float",     0x0200}, {"Emergency button",  0x0400},
    {"Dry-contact intmt",  0x0800}, {"Discharge OCP2",    0x1000},
};
#define NBIT ((int)(sizeof(BITDEFS) / sizeof(BITDEFS[0])))
// i18n keys parallel to the data tables above (English label kept for MQTT/web).
static const uint8_t SET_KEY[NSET] = {
    K_S_NOMINAL_CAP, K_S_CELL_COUNT, K_S_MAX_CHG_A, K_S_MAX_DIS_A, K_S_CELL_OVP, K_S_CELL_OVP_REC,
    K_S_CELL_UVP, K_S_CELL_UVP_REC, K_S_SOC100_V, K_S_SOC0_V, K_S_BAL_START_V, K_S_BAL_TRIG_DV,
    K_S_MAX_BAL_A, K_S_REQ_CHG_V, K_S_REQ_FLOAT_V, K_S_POWER_OFF_V, K_S_CHG_OCP_DELAY,
    K_S_CHG_OCP_REC, K_S_DIS_OCP_DELAY, K_S_DIS_OCP_REC, K_S_SCP_DELAY, K_S_SCP_REC,
    K_S_CHG_OTP, K_S_CHG_OTP_REC, K_S_DIS_OTP, K_S_DIS_OTP_REC, K_S_CHG_UTP, K_S_CHG_UTP_REC,
    K_S_MOS_OTP, K_S_MOS_OTP_REC, K_S_SMART_SLEEP_V};
static const uint8_t TAIL_KEY[NTAIL] = {K_S_HEAT_START_T, K_S_SMART_SLEEP_H};
static const uint8_t BIT_KEY[NBIT] = {
    K_B_HEATING, K_B_DIS_TEMP_SENS, K_B_DISP_ALWAYS, K_B_SMART_SLEEP, K_B_DISABLE_PCL,
    K_B_TIMED_DATA, K_B_CHG_FLOAT, K_B_EMERGENCY, K_B_DRY_CONTACT, K_B_DIS_OCP2};
static int numKey(int i) { return i < NSET ? SET_KEY[i] : TAIL_KEY[i - NSET]; }     // localized param label
static int setWidth(uint8_t t) { return (t == FT_U8 || t == FT_I8) ? 1 : (t == FT_U16 || t == FT_I16) ? 2 : 4; }
static float setGet(int b, const SetDef &d) {
    const uint8_t *p = setRaw[b]; int o = d.off - 6; uint32_t raw = 0;
    switch (setWidth(d.type)) {
        case 1: raw = p[o]; break;
        case 2: raw = (uint16_t)(p[o] << 8 | p[o + 1]); break;
        default: raw = (uint32_t)p[o] << 24 | p[o + 1] << 16 | p[o + 2] << 8 | p[o + 3]; break;
    }
    if (d.type == FT_I32) return (int32_t)raw * d.scale;
    if (d.type == FT_I16) return (int16_t)raw * d.scale;
    if (d.type == FT_I8) return (int8_t)raw * d.scale;
    return raw * d.scale;
}
// numeric rows = main settings, plus tail settings when the tail read succeeded
static int numCount(int b) { return NSET + (setOk2[b] ? NTAIL : 0); }
static const SetDef &numDef(int i) { return i < NSET ? SETDEFS[i] : TAILDEFS[i - NSET]; }
static uint16_t bitWord(int b) { return (uint16_t)(setRaw[b][276] << 8 | setRaw[b][277]); }   // offset 282
static int setDec(const SetDef &d) { return d.vstep < 0.1f ? (d.vstep < 0.01f ? 3 : 2) : (d.vstep < 1.0f ? 1 : 0); }
static void fmtSetting(char *o, size_t n, const SetDef &d, float v) { snprintf(o, n, "%.*f%s", setDec(d), v, d.unit); }
// Write a setting (register from the frame offset) and verify by read-back.
static bool setPut(int b, const SetDef &d, float v) {
    if (setWidth(d.type) != 4) return false;   // bmsWrite only writes a 4-byte register pair; a narrower field would clobber its neighbours
    if (v < d.vmin) v = d.vmin; if (v > d.vmax) v = d.vmax;
    long raw = lroundf(v / d.scale);
    uint16_t reg = 0x1000 + (d.off - 6);
    if (!bmsSet(b, reg, (uint32_t)(int32_t)raw)) return false;
    int o = d.off - 6;                                       // mirror into local buffer so the row updates
    switch (setWidth(d.type)) {
        case 1: setRaw[b][o] = raw & 0xFF; break;
        case 2: setRaw[b][o] = (raw >> 8) & 0xFF; setRaw[b][o + 1] = raw & 0xFF; break;
        default: setRaw[b][o] = (raw >> 24) & 0xFF; setRaw[b][o + 1] = (raw >> 16) & 0xFF; setRaw[b][o + 2] = (raw >> 8) & 0xFF; setRaw[b][o + 3] = raw & 0xFF; break;
    }
    return true;
}
// Full-screen numeric keypad editor (4x4): 7 8 9 DEL / 4 5 6 CLR / 1 2 3 +/- / . 0 Cancel Save
static const char *KEYLBL[16] = {"7", "8", "9", "DEL", "4", "5", "6", "CLR", "1", "2", "3", "+/-", ".", "0", "Cancel", "Save"};
static void keyRect(int k, int *kx, int *ky, int *kw, int *kh) {
    int x0 = 12, y0 = 96, gap = 8, gw = Wd - 24, gh = Ht - 96 - 10;
    int cw = (gw - 3 * gap) / 4, ch = (gh - 3 * gap) / 4;
    *kx = x0 + (k % 4) * (cw + gap); *ky = y0 + (k / 4) * (ch + gap); *kw = cw; *kh = ch;
}
static void renderEditor() {
    const SetDef &d = numDef(editIdx);
    fRect(0, 0, Wd, Ht, 0, C_BG);
    lText(T(numKey(editIdx)), 14, 10, F16, C_TEXT);
    int dec = setDec(d);
    char rng[44]; snprintf(rng, sizeof(rng), "range %.*f to %.*f %s", dec, d.vmin, dec, d.vmax, d.unit);
    lText(rng, 14, 70, F12, C_MUTED);
    fRect(14, 32, Wd - 28, 34, 8, C_CARD); dRect(14, 32, Wd - 28, 34, 8, C_ACCENT);
    char shown[24]; snprintf(shown, sizeof(shown), "%s %s", editStr[0] ? editStr : "0", d.unit);
    lText(shown, Wd - 22 - textW(shown, F20), 38, F20, C_TEXT);
    for (int k = 0; k < 16; k++) {
        int kx, ky, kw, kh; keyRect(k, &kx, &ky, &kw, &kh);
        bool save = (k == 15), cancel = (k == 14);
        fRect(kx, ky, kw, kh, 8, save ? C_ACCENT : C_CARD);
        if (!save) dRect(kx, ky, kw, kh, 8, cancel ? C_BAD : C_BORDER);
        const char *klbl = save ? T(K_SAVE) : cancel ? T(K_CANCEL) : KEYLBL[k];
        cText(klbl, kx + kw / 2, ky + kh / 2 - 9, F20, save ? C_BG : (cancel ? C_BAD : C_TEXT));
    }
}
// always-shown rows: 0 battery, 1 TX pin, 2 RX pin. Then (when live) 3 switches,
// then (when the settings block is read) the numeric params + bitmask flags.
#define BMS_FIXED 4
static int bmsRowCount() {
    int b = cfgBms;
    bool live = !demoMode && bmsLive[b];
    bool avail = live && setOk[b];
    if (!live) return BMS_FIXED + 1;                         // + "offline/demo" notice
    if (!avail) return BMS_FIXED + 3 + 1;                    // 3 switches + "reading..." notice
    return BMS_FIXED + 3 + numCount(b) + (setOk2[b] ? NBIT : 0);
}
static int bmsViewH() { return Ht - LIST_TOP - 2; }
static int bmsContentH() { return bmsRowCount() * SROW_STEP + SROW_STEP; }
static int bmsMaxScroll() { int m = bmsContentH() - bmsViewH(); return m > 0 ? m : 0; }
static void renderBmsTab() {
    int b = cfgBms;
    bool live = !demoMode && bmsLive[b];
    bool avail = live && setOk[b];
    int rows = bmsRowCount();
    if (bmsScroll > bmsMaxScroll()) bmsScroll = bmsMaxScroll();
    for (int i = 0; i < rows; i++) {
        int y = LIST_TOP + i * SROW_STEP - bmsScroll;
        if (y + SROW_H < LIST_TOP || y > Ht) continue;
        if (i == 0) srowAt(y, T(K_BATTERIES), numBms == 2 ? "2  >" : "1  >", C_CYAN);
        else if (i == 1) { char cv[20]; snprintf(cv, sizeof(cv), "%s %d  >", T(K_BAT), cfgBms ? 2 : 1); srowAt(y, T(K_CONFIGURE), cv, numBms == 2 ? C_CYAN : C_MUTED); }
        else if (i == 2) { char v[8]; snprintf(v, sizeof(v), "IO%d", bmsPin[b * 2]);     srowAt(y, T(K_UART_TX), v, C_CYAN); }
        else if (i == 3) { char v[8]; snprintf(v, sizeof(v), "IO%d", bmsPin[b * 2 + 1]); srowAt(y, T(K_UART_RX), v, C_CYAN); }
        else if (!live) srowAt(y, T(K_PARAMETERS), demoMode ? T(K_DEMO_LC) : T(K_OFFLINE_LC), C_MUTED);
        else {
            int si = i - BMS_FIXED;                          // live section
            if (si == 0) srowToggle(y, T(K_CHARGE_MOSFET), bmsCharge[b]);
            else if (si == 1) srowToggle(y, T(K_DISCHARGE_MOSFET), bmsDischarge[b]);
            else if (si == 2) srowToggle(y, T(K_BALANCER), bmsBalancer[b]);
            else if (!avail) srowAt(y, T(K_PARAMETERS), T(K_READING), C_MUTED);
            else {
                int pi = si - 3;
                if (pi < numCount(b)) { const SetDef &d = numDef(pi); char v[16]; fmtSetting(v, sizeof(v), d, setGet(b, d)); srowAt(y, T(numKey(pi)), v, C_TEXT); }
                else { int bi = pi - numCount(b); srowToggle(y, T(BIT_KEY[bi]), bitWord(b) & BITDEFS[bi].mask); }
            }
        }
    }
    if (bmsMaxScroll() > 0) {                                // scrollbar
        int tX = Wd - 6, tY = LIST_TOP, tH = bmsViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)bmsViewH() / bmsContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)bmsScroll / bmsMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
}
// pixel-scrolled WiFi list (drag to scroll, fixed message + Rescan button)
#define WROW_STEP 34
#define WROW_H 30
static int wListTop() { return 100; }
static int wRescanY() { return Ht - 34; }
static int wViewH() { return wRescanY() - 4 - wListTop(); }
static int wContentH() { return netCount * WROW_STEP; }
static int wMaxScroll() { int m = wContentH() - wViewH(); return m > 0 ? m : 0; }
static void renderWifiTab() {
    bool conn = (WiFi.status() == WL_CONNECTED);
    if (wifiScroll > wMaxScroll()) wifiScroll = wMaxScroll();
    int top = wListTop(), vbot = wRescanY() - 4;
    for (int i = 0; i < netCount; i++) {
        int y = top + i * WROW_STEP - wifiScroll;
        if (y + WROW_H < top || y > vbot) continue;
        int x = 8, w = Wd - 16, h = WROW_H;
        fRect(x, y, w, h, 6, C_CARD); dRect(x, y, w, h, 6, C_BORDER);
        lText(netSsid[i], x + 12, y + 8, F12, C_TEXT);
        int bars = netRssi[i] > -55 ? 4 : netRssi[i] > -65 ? 3 : netRssi[i] > -75 ? 2 : 1;
        for (int b = 0; b < 4; b++) fRect(x + w - 64 + b * 7, y + h - 6 - b * 4, 5, 4 + b * 4, 0, b < bars ? C_ACCENT : C_BORDER);
        if (netEnc[i]) lText("L", x + w - 18, y + 8, F12, C_WARN);
    }
    if (wMaxScroll() > 0) {                                 // scrollbar
        int tX = Wd - 6, tY = top, tH = wViewH();
        fRect(tX, tY, 4, tH, 2, C_BORDER);
        int thH = (int)(tH * (float)wViewH() / wContentH()); if (thH < 16) thH = 16;
        int thY = tY + (int)((tH - thH) * (float)wifiScroll / wMaxScroll());
        fRect(tX, thY, 4, thH, 2, C_ACCENT);
    }
    // mask the strip above the list + draw the status message on top
    fRect(0, 78, Wd, top - 78, 0, C_BG);
    lText(wifiMsg[0] ? wifiMsg : T(K_WIFI_TAP_SCAN), 12, 82, F12, conn ? C_ACCENT : C_MUTED);
    // mask the strip below the list + draw the Rescan button on top
    int ry = wRescanY();
    fRect(0, ry - 2, Wd, Ht - (ry - 2), 0, C_BG);
    fRect(8, ry, Wd - 16, 28, 6, C_CARD); dRect(8, ry, Wd - 16, 28, 6, C_BORDER);
    cText(netCount ? T(K_RESCAN) : T(K_SCAN), Wd / 2, ry + 14, F16, C_CYAN);
}
// keyboard: draw (draw=true) or hit-test (draw=false -> returns key code)
static int kbProcess(bool draw, int tx, int ty) {
    const int KB_TOP = 96, KH = 34, GAP = 4, KW = 42, CTLH = 44;
    int hit = 0;
    for (int r = 0; r < 4; r++) {
        const char *s = KB[kbMode][r]; int Ln = strlen(s);
        int totalW = Ln * KW + (Ln - 1) * GAP, sx = (Wd - totalW) / 2, y = KB_TOP + r * (KH + GAP);
        for (int i = 0; i < Ln; i++) {
            int x = sx + i * (KW + GAP);
            if (draw) {
                fRect(x, y, KW, KH, 5, C_CARD); dRect(x, y, KW, KH, 5, C_BORDER);
                char c[2] = {s[i], 0}; cText(c, x + KW / 2, y + KH / 2, F16, C_TEXT);
            } else if (tx >= x && tx < x + KW && ty >= y && ty < y + KH) hit = s[i];
        }
    }
    int y = KB_TOP + 4 * (KH + GAP);
    struct { int x, w; const char *lb; int code; } ctl[4] = {
        {8, 62, kbMode == 0 ? "ABC" : kbMode == 1 ? "#+=" : "abc", -2},
        {74, 176, T(K_KB_SPACE), 32}, {254, 92, "del", -1}, {350, 122, "OK", -4}};
    for (int k = 0; k < 4; k++) {
        if (draw) {
            uint32_t bg = ctl[k].code == -4 ? C_ACCENT : C_CARD;
            fRect(ctl[k].x, y, ctl[k].w, CTLH, 6, bg); dRect(ctl[k].x, y, ctl[k].w, CTLH, 6, C_BORDER);
            cText(ctl[k].lb, ctl[k].x + ctl[k].w / 2, y + CTLH / 2, F16, ctl[k].code == -4 ? C_BG : C_TEXT);
        } else if (tx >= ctl[k].x && tx < ctl[k].x + ctl[k].w && ty >= y && ty < y + CTLH) hit = ctl[k].code;
    }
    return hit;
}
static void renderKeyboard() {
    char hdr[48];
    const char *hint;
    if (kbTarget == KBT_WUSER) { snprintf(hdr, sizeof(hdr), "%s", T(K_HDR_WEB_USER)); hint = T(K_ENTER_USERNAME); }
    else if (kbTarget == KBT_WPASS) { snprintf(hdr, sizeof(hdr), "%s", T(K_HDR_WEB_PASS)); hint = T(K_ENTER_NEW_PASSWORD); }
    else { snprintf(hdr, sizeof(hdr), "Wi-Fi: %s", wifiSel >= 0 ? netSsid[wifiSel] : ""); hint = T(K_ENTER_PASSWORD); }
    lText(hdr, 12, 8, F12, C_MUTED);
    drawCloseBtn();
    fRect(12, 30, Wd - 24, 30, 6, C_CARD); dRect(12, 30, Wd - 24, 30, 6, C_BORDER);
    const char *shown = wifiPassLen ? wifiPass : hint;
    while (wifiPassLen && shown[1] && textW(shown, F16) > Wd - 48) shown++;   // long input (63-char WPA keys): keep the tail (typing end) visible
    lText(shown, 22, 38, F16, wifiPassLen ? C_TEXT : C_MUTED);
    kbProcess(true, 0, 0);
}
static void kvLine(int x, int *y, const char *k, const char *v) {
    lText(k, x, *y, F12, C_MUTED); lText(v, x + 96, *y, F12, C_TEXT); *y += 21;
}
static void renderInfoPopup() {
    int w = Wd - 56, h = Ht - 44, x = (Wd - w) / 2, y = (Ht - h) / 2;
    fRect(x, y, w, h, 10, C_CARD); dRect(x, y, w, h, 10, C_ACCENT);
    lText(T(K_HDR_SYSINFO), x + 16, y + 12, F16, C_TEXT);
    lText("v" FW_VERSION, x + w - 62, y + 14, F12, C_ACCENT);
    int lx = x + 16, ly = y + 44; char b[40];
    kvLine(lx, &ly, T(K_BOARD), "JC3248W535");
    snprintf(b, sizeof(b), "ESP32-S3 2-core %uMHz", (unsigned)getCpuFrequencyMhz()); kvLine(lx, &ly, "MCU", b);
    snprintf(b, sizeof(b), "%lu MB", (unsigned long)(ESP.getFlashChipSize() / 1048576UL)); kvLine(lx, &ly, T(K_FLASH), b);
    snprintf(b, sizeof(b), "%lu / %lu KB", (unsigned long)(ESP.getFreePsram() / 1024), (unsigned long)(ESP.getPsramSize() / 1024)); kvLine(lx, &ly, T(K_PSRAM_FREE), b);
    snprintf(b, sizeof(b), "%lu KB", (unsigned long)(ESP.getFreeHeap() / 1024)); kvLine(lx, &ly, T(K_HEAP_FREE), b);
    kvLine(lx, &ly, "MAC", WiFi.macAddress().c_str());
    if (WiFi.status() == WL_CONNECTED) {
        kvLine(lx, &ly, "IP", WiFi.localIP().toString().c_str());
        snprintf(b, sizeof(b), "%s / %s", webUser, webPass); kvLine(lx, &ly, T(K_WEB_LOGIN), b);   // portal + OTA credentials
    } else kvLine(lx, &ly, T(K_TAB_WIFI), T(K_NOT_CONNECTED));
    snprintf(b, sizeof(b), "%lu s", (unsigned long)(millis() / 1000)); kvLine(lx, &ly, T(K_UPTIME_INFO), b);
    // Per-pack diagnostics: Modbus read success rate + capacity retention (vs "as new") + cycles
    for (int t = 0; t < numBms; t++) {
        if (!commAttempts[t]) continue;
        int pct = (int)(100.0f * commOk[t] / commAttempts[t] + 0.5f);
        int ret = sohBaseAh[t] > 1 ? (int)(100.0f * packFullAh[t] / sohBaseAh[t] + 0.5f) : 100;
        snprintf(b, sizeof(b), "%d%% ok  cap %d%%  %lucyc", pct, ret, (unsigned long)bms[t].cycles);
        char key[8]; snprintf(key, sizeof(key), "BMS%d", t + 1);
        kvLine(lx, &ly, key, b);
    }
    lText(T(K_TAP_CLOSE), x + w - 92, y + h - 18, F12, C_MUTED);
}
static int wxCondKey(int code) {            // weather code → localized condition label
    switch (wxCat(code)) {
        case 0:  return K_WX_CLEAR;
        case 1:  return K_WX_PARTLY;
        case 2:  return K_WX_CLOUDY;
        case 3:  return K_WX_RAIN;
        case 4:  return K_WX_SNOW;
        default: return K_WX_STORM;
    }
}
static void drawDrop(int cx, int cy, uint32_t col) {   // tiny raindrop glyph
    fCircle(cx, cy + 1, 3, col);
    tri(cx - 3, cy + 1, cx + 3, cy + 1, cx, cy - 4, col);
}
// 5-day forecast modal — opened by tapping the top-bar weather glyph. Each day is a
// column: header (Today / D-M), a big icon, max/min temp, condition text and rain chance.
static void renderWeatherPopup() {
    const uint32_t RN = 0x4aa3ff;
    int w = Wd - 16, h = Ht - 44, x = 8, y = (Ht - h) / 2;
    fRect(x, y, w, h, 12, C_CARD); dRect(x, y, w, h, 12, C_ACCENT);
    lText(wxCity[0] ? wxCity : "Weather", x + 16, y + 10, F16, C_TEXT);
    lText(T(K_TAP_CLOSE), x + w - 92, y + h - 18, F12, C_MUTED);
    int n = wxDays < 1 ? 1 : wxDays;
    int colW = (w - 16) / n;
    // base date for the per-day header (Today + D/M for the rest); TZ set once in setup()
    struct tm ti; time_t base = 0; bool haveDate = false;
    if (getLocalTime(&ti, 0)) { base = mktime(&ti); haveDate = base > 0; }
    const int wdY = y + 38, dateY = y + 54, icoY = y + 98, mxY = y + 138, mnY = y + 160, condY = y + 184, popY = y + 208;
    for (int i = 0; i < wxDays; i++) {
        int cxo = x + 8 + i * colW, cx = cxo + colW / 2;
        if (i) dRect(cxo, y + 36, 1, h - 56, 0, C_BORDER);            // column separator
        // header: weekday (or "Today") on top, the date below
        struct tm dt; bool gotDt = false;
        if (haveDate) { time_t e = base + (time_t)i * 86400; localtime_r(&e, &dt); gotDt = true; }
        const char *top = (i == 0) ? T(K_TODAY) : (gotDt ? wday(dt.tm_wday) : "");
        cText(top, cx, wdY, F12, i == 0 ? C_ACCENT : C_TEXT);
        if (gotDt) { char ds[8]; snprintf(ds, sizeof(ds), "%d/%d", dt.tm_mday, dt.tm_mon + 1); cText(ds, cx, dateY, F10, C_MUTED); }
        drawWxIcon(cx, icoY, wxDay[i].code, 2.5f);
        char tb[10];
        snprintf(tb, sizeof(tb), "%d°", wxDay[i].tmax); cText(tb, cx, mxY, F16, C_TEXT);
        snprintf(tb, sizeof(tb), "%d°", wxDay[i].tmin); cText(tb, cx, mnY, F12, C_MUTED);
        cText(T(wxCondKey(wxDay[i].code)), cx, condY, F10, C_MUTED);
        if (wxDay[i].pop > 0) {
            char pp[6]; snprintf(pp, sizeof(pp), "%d%%", wxDay[i].pop);
            int pw = textW(pp, F10), tot = 9 + pw, sx = cx - tot / 2;
            drawDrop(sx + 3, popY + 4, RN);
            lText(pp, sx + 11, popY, F10, RN);
        }
    }
}
// Firmware-update details modal (opened by the top-bar update icon).
static void renderUpdatePopup() {
    int w = Wd - 80, h = 150, x = (Wd - w) / 2, y = (Ht - h) / 2;
    fRect(x, y, w, h, 12, C_CARD); dRect(x, y, w, h, 12, C_ACCENT);
    cText("Firmware update", x + w / 2, y + 16, F16, C_TEXT);
    char l1[40]; snprintf(l1, sizeof(l1), "New  %s", updTag); cText(l1, x + w / 2, y + 48, F16, C_ACCENT);
    char l0[40]; snprintf(l0, sizeof(l0), "Installed  v%s", FW_VERSION); cText(l0, x + w / 2, y + 72, F12, C_MUTED);
    int bx, by, bw, bh; updBtnRect(&bx, &by, &bw, &bh);
    fRect(bx, by, bw, bh, 8, C_ACCENT); cText("Update now", bx + bw / 2, by + bh / 2 - 8, F16, C_BG);
    cText(T(K_TAP_CLOSE), x + w / 2, y + h - 15, F10, C_MUTED);
}
// Full-screen progress while flashing (renderable because selfUpdate doesn't suspend core 1).
static void renderUpdating() {
    fRect(0, 0, Wd, Ht, 0, C_BG);
    int cx = Wd / 2;
    if (updProgress == -2) { cText("Update failed", cx, Ht / 2 - 18, F20, C_BAD); cText("tap to dismiss", cx, Ht / 2 + 16, F12, C_MUTED); return; }
    cText("Updating firmware", cx, Ht / 2 - 48, F20, C_TEXT);
    cText(updTag, cx, Ht / 2 - 22, F16, C_ACCENT);
    int bw = Wd - 120, bx = (Wd - bw) / 2, by = Ht / 2 + 6, bh = 18;
    fRect(bx, by, bw, bh, 9, C_CARD); dRect(bx, by, bw, bh, 9, C_BORDER);
    int p = updProgress < 0 ? 0 : updProgress > 100 ? 100 : updProgress;
    if (p > 0) fRect(bx + 2, by + 2, (bw - 4) * p / 100, bh - 4, 7, C_ACCENT);
    char pc[8]; snprintf(pc, sizeof(pc), "%d%%", p); cText(pc, cx, by + bh + 16, F12, C_TEXT);
    cText("do not power off", cx, Ht - 22, F10, C_MUTED);
}
static void renderLockPad(bool setMode);   // defined below (near the lock screen)
static void renderSettings() {
    if (lockSetMode) { renderLockPad(true); return; }   // setting a new PIN (modal numpad)
    if (kbActive) { renderKeyboard(); return; }
    if (editIdx >= 0) { renderEditor(); return; }   // full-screen modal stepper
    // content first, then mask the header strip so overscrolled rows don't bleed
    // over the title/sub-tabs, then draw the chrome on top.
    if (subTab == ST_BMS) renderBmsTab();
    else if (subTab == ST_WIFI) renderWifiTab();
    else renderSysTab();
    fRect(0, 0, Wd, LIST_TOP - 4, 0, C_BG);
    lText(T(K_SETTINGS), 12, 12, F16, C_TEXT);
    drawCloseBtn();
    drawSubTabs();
    if (infoPopup) renderInfoPopup();
}

