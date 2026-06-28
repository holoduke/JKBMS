// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
// ---- wifi (logic) ----
static void wifiStartScan() {
    if (wifiScanning) return;
    wifiScanning = true; wifiSel = -1; wifiScroll = 0;
    snprintf(wifiMsg, sizeof(wifiMsg), "%s", T(K_WIFI_SCANNING));
    WiFi.mode(WIFI_STA); WiFi.scanNetworks(true);
}
static void wifiTryConnect() {
    if (wifiSel < 0) return;
    strncpy(connSsid, netSsid[wifiSel], 32); connSsid[32] = 0;
    strncpy(connPass, wifiPass, 32); connPass[32] = 0;
    wifiSaved = false; WiFi.begin(connSsid, connPass);
    snprintf(wifiMsg, sizeof(wifiMsg), "%s %s...", T(K_WIFI_CONNECTING), connSsid);
}
static bool wifiPoll() {
    bool changed = false;
    if (wifiScanning) {
        int r = WiFi.scanComplete();
        if (r >= 0) {
            int n = r > MAXNET ? MAXNET : r; netCount = n;
            for (int i = 0; i < n; i++) {
                strncpy(netSsid[i], WiFi.SSID(i).c_str(), 32); netSsid[i][32] = 0;
                netRssi[i] = WiFi.RSSI(i); netEnc[i] = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
            }
            WiFi.scanDelete(); wifiScanning = false; changed = true;
            if (n) snprintf(wifiMsg, sizeof(wifiMsg), "%d %s", n, T(K_WIFI_NETS)); else snprintf(wifiMsg, sizeof(wifiMsg), "%s", T(K_WIFI_NO_NETS));
        } else if (r == WIFI_SCAN_FAILED) { wifiScanning = false; changed = true; snprintf(wifiMsg, sizeof(wifiMsg), "%s", T(K_WIFI_SCAN_FAIL)); }
        return changed;
    }
    static uint32_t lastRetry = 0;
    if (connSsid[0] && WiFi.status() != WL_CONNECTED && millis() - lastRetry > 15000) { lastRetry = millis(); WiFi.begin(connSsid, connPass); }
    static wl_status_t last = WL_IDLE_STATUS;
    wl_status_t st = WiFi.status();
    if (st != last) {
        last = st; changed = true;
        if (st == WL_CONNECTED) {
            snprintf(wifiMsg, sizeof(wifiMsg), "%s %s", T(K_WIFI_CONNECTED), WiFi.SSID().c_str());
            webBegin();   // start the web portal + OTA once we have an IP
            configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org", "time.nist.gov", "time.google.com");   // (re)start NTP on every (re)connect
            ntpStarted = true;
            if (!wifiSaved && connSsid[0]) { prefs.begin("wifi", false); prefs.putString("ssid", connSsid); prefs.putString("pass", connPass); prefs.end(); wifiSaved = true; }
        } else if (st == WL_CONNECT_FAILED) snprintf(wifiMsg, sizeof(wifiMsg), "%s", T(K_WIFI_CONN_FAIL));
        else if (st == WL_NO_SSID_AVAIL) snprintf(wifiMsg, sizeof(wifiMsg), "%s", T(K_WIFI_NOT_FOUND));
        else if (st == WL_CONNECTION_LOST) snprintf(wifiMsg, sizeof(wifiMsg), "%s", T(K_WIFI_CONN_LOST));
    }
    if (!timeSynced && WiFi.status() == WL_CONNECTED) {   // keep retrying NTP until the clock is real
        struct tm ti;
        if (getLocalTime(&ti, 0) && ti.tm_year >= 125) timeSynced = true;   // year >= 2025
        else { static uint32_t lastNtp = 0; if (!lastNtp || millis() - lastNtp > 20000) {
            lastNtp = millis(); configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", "pool.ntp.org", "time.google.com"); } }
    }
    return changed;
}

// After a tap, only this rect needs repainting (defaults to full screen). Setting
// it to a single settings row makes toggles repaint just that row → snappy.
static bool dirtyFull = true;
static lv_area_t dirtyRect;
static void markRowAt(int y) { dirtyFull = false; dirtyRect = (lv_area_t){8, y, Wd - 9, y + SROW_H - 1}; }
static void markRow(int i) { markRowAt(srowY(i)); }

// ---- settings persistence (NVS) ----
static void markCfg() { cfgDirty = true; cfgDirtyAt = millis(); }
static void saveSettings() {
    prefs.begin("set", false);
    prefs.putBool("autosw", autoSwitch); prefs.putUInt("ival", intervalMs);
    prefs.putInt("bright", brightness); prefs.putInt("sleep", autoSleepMin);
    prefs.putBool("eco", ecoMode); prefs.putInt("dim", dimAfterSec);
    prefs.putBool("tF", tempF); prefs.putBool("f12", fmt12);
    prefs.putBool("wauto", wifiAuto); prefs.putInt("sim", simSpeed);
    prefs.putBool("bc0", bmsCharge[0]); prefs.putBool("bc1", bmsCharge[1]);
    prefs.putBool("bd0", bmsDischarge[0]); prefs.putBool("bd1", bmsDischarge[1]);
    prefs.putBool("bb0", bmsBalancer[0]); prefs.putBool("bb1", bmsBalancer[1]);
    prefs.putBool("demo", demoMode);
    prefs.putInt("idle", idleScreen);
    prefs.putInt("saver", saverAfterSec);
    prefs.putInt("lockAft", lockAfterSec);
    prefs.putString("lockPin", lockPin);
    prefs.putUChar("lang", g_lang);
    prefs.putInt("nbms", numBms);
    prefs.putBytes("pins", bmsPin, sizeof(bmsPin));
    prefs.putString("wuser", webUser);
    prefs.putString("wpass", webPass);
    prefs.putBool("mqEn", mqttEnabled); prefs.putString("mqHost", mqttHost); prefs.putInt("mqPort", mqttPort);
    prefs.putString("mqUser", mqttUser); prefs.putString("mqPass", mqttPass);
    prefs.putBool("alEn", alertEnabled); prefs.putString("alUrl", alertUrl);
    prefs.putInt("alSoc", alSocLo); prefs.putInt("alTmp", alTempHi); prefs.putInt("alDlt", alDeltaHi);
    prefs.putBool("alFlt", alOnFault);
    prefs.putBool("autoUpd", autoUpdate);
    prefs.end();
}
static void loadSettings() {
    prefs.begin("set", true);
    autoSwitch = prefs.getBool("autosw", autoSwitch); intervalMs = prefs.getUInt("ival", intervalMs);
    brightness = prefs.getInt("bright", brightness); autoSleepMin = prefs.getInt("sleep", autoSleepMin);
    ecoMode = prefs.getBool("eco", ecoMode); dimAfterSec = prefs.getInt("dim", dimAfterSec);
    tempF = prefs.getBool("tF", tempF); fmt12 = prefs.getBool("f12", fmt12);
    wifiAuto = prefs.getBool("wauto", wifiAuto); simSpeed = prefs.getInt("sim", simSpeed);
    bmsCharge[0] = prefs.getBool("bc0", true); bmsCharge[1] = prefs.getBool("bc1", true);
    bmsDischarge[0] = prefs.getBool("bd0", true); bmsDischarge[1] = prefs.getBool("bd1", true);
    bmsBalancer[0] = prefs.getBool("bb0", false); bmsBalancer[1] = prefs.getBool("bb1", false);
    demoMode = prefs.getBool("demo", demoMode);
    idleScreen = prefs.getInt("idle", idleScreen);
    saverAfterSec = prefs.getInt("saver", saverAfterSec);
    lockAfterSec = prefs.getInt("lockAft", lockAfterSec);
    { String p = prefs.getString("lockPin", ""); strncpy(lockPin, p.c_str(), sizeof(lockPin) - 1); lockPin[sizeof(lockPin) - 1] = 0; }
    g_lang = prefs.getUChar("lang", g_lang); if (g_lang >= LANG_COUNT) g_lang = 0;
    if (prefs.isKey("nbms")) numBms = prefs.getInt("nbms", 2);
    else numBms = prefs.isKey("autosw") ? 2 : 1;   // existing install (ran the old hardcoded-dual build) → keep 2; fresh flash → default 1
    if (numBms < 1) numBms = 1; if (numBms > 2) numBms = 2;
    if (numBms < 2) { bmsLive[1] = false; cfgBms = 0; }
    if (prefs.isKey("pins")) prefs.getBytes("pins", bmsPin, sizeof(bmsPin));
    if (prefs.isKey("wuser")) { String wu = prefs.getString("wuser", webUser); strncpy(webUser, wu.c_str(), sizeof(webUser) - 1); webUser[sizeof(webUser) - 1] = 0; }
    if (prefs.isKey("wpass")) { String wp = prefs.getString("wpass", webPass); strncpy(webPass, wp.c_str(), sizeof(webPass) - 1); webPass[sizeof(webPass) - 1] = 0; }
    else {   // fresh install → a RANDOM default (not derivable from the MAC, which any LAN peer can read);
        const char *cs = "abcdefghijkmnpqrstuvwxyz23456789";   // 32 unambiguous chars (no 0/o/1/l)
        char p[10] = "jk-"; for (int i = 3; i < 9; i++) p[i] = cs[esp_random() & 31]; p[9] = 0;
        strncpy(webPass, p, sizeof(webPass) - 1); webPass[sizeof(webPass) - 1] = 0;
        freshWebPass = true;   // persist it once in setup() so it's stable across reboots
    }
    mqttEnabled = prefs.getBool("mqEn", false); mqttPort = prefs.getInt("mqPort", 1883);
    { String s = prefs.getString("mqHost", ""); strncpy(mqttHost, s.c_str(), sizeof(mqttHost) - 1); mqttHost[sizeof(mqttHost) - 1] = 0;
      s = prefs.getString("mqUser", ""); strncpy(mqttUser, s.c_str(), sizeof(mqttUser) - 1); mqttUser[sizeof(mqttUser) - 1] = 0;
      s = prefs.getString("mqPass", ""); strncpy(mqttPass, s.c_str(), sizeof(mqttPass) - 1); mqttPass[sizeof(mqttPass) - 1] = 0; }
    alertEnabled = prefs.getBool("alEn", false);
    { String s = prefs.getString("alUrl", ""); strncpy(alertUrl, s.c_str(), sizeof(alertUrl) - 1); alertUrl[sizeof(alertUrl) - 1] = 0; }
    alSocLo = prefs.getInt("alSoc", 15); alTempHi = prefs.getInt("alTmp", 55); alDeltaHi = prefs.getInt("alDlt", 300);
    alOnFault = prefs.getBool("alFlt", true);
    autoUpdate = prefs.getBool("autoUpd", false);
    { String s = prefs.getString("instTag", ""); strncpy(instTag, s.c_str(), sizeof(instTag) - 1); instTag[sizeof(instTag) - 1] = 0; }
    prefs.end();
    appliedB = brightness;
}
// Persist the real graph history (only the valid `count` samples per BMS).
static void saveHistory() {
    prefs.begin("hist", false);
    for (int t = 0; t < 2; t++) {
        char k[8];
        size_t capN = histCount[t] * sizeof(histCap[0][0]), pwrN = histCount[t] * sizeof(histPwr[0][0]);
        snprintf(k, sizeof(k), "cap%d", t); size_t wc = prefs.putBytes(k, histCap[t], capN);
        snprintf(k, sizeof(k), "pwr%d", t); size_t wp = prefs.putBytes(k, histPwr[t], pwrN);
        snprintf(k, sizeof(k), "tmp%d", t); prefs.putBytes(k, histTmp[t], histCount[t] * sizeof(histTmp[0][0]));
        // write the count LAST and only as large as BOTH blobs actually persisted, so a short/failed
        // data write can never leave a count out-running the cap OR pwr data (→ zero-tail graph).
        uint16_t capOk = (wc < capN) ? (uint16_t)wc : histCount[t];
        uint16_t pwrOk = (wp < pwrN) ? (uint16_t)(wp / sizeof(histPwr[0][0])) : histCount[t];
        uint16_t okCount = capOk < pwrOk ? capOk : pwrOk;
        snprintf(k, sizeof(k), "c%d", t); prefs.putUShort(k, okCount);
        if (wc != capN || wp != pwrN) Serial.printf("[nvs] history save BMS%d short (cap %u/%u, pwr %u/%u) — NVS full?\n",
                                                     t + 1, (unsigned)wc, (unsigned)capN, (unsigned)wp, (unsigned)pwrN);
    }
    prefs.putBytes("ein", lifeWhIn, sizeof(lifeWhIn));     // lifetime energy counters ride this ~30-min history save
    prefs.putBytes("eout", lifeWhOut, sizeof(lifeWhOut));
    float pk[4] = {bms[0].peakChg, bms[0].peakDis, bms[1].peakChg, bms[1].peakDis};   // persist peaks (else lost on reboot)
    prefs.putBytes("pk", pk, sizeof(pk));
    prefs.end();
}
static void loadHistory() {
    // Never wipe — always load and sanitize. Corruption (zero-tail from a partial save) is
    // healed by the clamp + trailing-zero trim below, so real history is preserved. (An earlier
    // version-bump wipe here destroyed good multi-day data; that path is gone for good.)
    prefs.begin("hist", true);
    for (int t = 0; t < 2; t++) {
        char k[8];
        snprintf(k, sizeof(k), "c%d", t); int c = prefs.getUShort(k, 0); if (c > HIST_N) c = HIST_N;
        snprintf(k, sizeof(k), "cap%d", t); size_t gotC = prefs.getBytes(k, histCap[t], c * sizeof(histCap[0][0]));
        snprintf(k, sizeof(k), "pwr%d", t); size_t gotP = prefs.getBytes(k, histPwr[t], c * sizeof(histPwr[0][0]));
        snprintf(k, sizeof(k), "tmp%d", t); prefs.getBytes(k, histTmp[t], c * sizeof(histTmp[0][0]));   // temp (may be absent on old data → zeros)
        if (gotC < (size_t)c) c = gotC;                          // cap blob shorter than the saved count → trust the bytes
        if (gotP / sizeof(histPwr[0][0]) < (size_t)c) c = gotP / sizeof(histPwr[0][0]);   // keep pwr aligned with cap
        while (c > 0 && histCap[t][c - 1] == 0) c--;    // SOC is never 0 → trailing zeros are corruption; drop them
        histCount[t] = c;
    }
    if (prefs.isKey("ein")) prefs.getBytes("ein", lifeWhIn, sizeof(lifeWhIn));      // restore lifetime energy
    if (prefs.isKey("eout")) prefs.getBytes("eout", lifeWhOut, sizeof(lifeWhOut));
    if (prefs.isKey("pk")) { float pk[4]; prefs.getBytes("pk", pk, sizeof(pk));      // restore peaks
        bms[0].peakChg = pk[0]; bms[0].peakDis = pk[1]; bms[1].peakChg = pk[2]; bms[1].peakDis = pk[3]; }
    prefs.end();
}

