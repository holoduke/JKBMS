// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.

// Background I/O worker, pinned to core 0 (the UI/render + LVGL run on core 1). All the
// blocking network work lives here so a slow/unreachable endpoint can never freeze the
// display or touch: MQTT (connect can block ~seconds), the weather/geo HTTPS fetches,
// and the alert webhook POSTs. The MQTT command path (mqCallback → bmsSet) is the only
// one that touches the Modbus bus, and that's serialised against the core-1 poll by busMux.
// Good home for any future blocking/background job (extra sensors, cloud sync, etc.).
// Panel push task (core 0): transmits the snapshot core 1 hands it. This is the ~40ms
// blocking pixel-swizzle+DMA — doing it here keeps core 1 free for touch + next-frame render.
// Compare dotted numeric versions ("1.0.224") component-wise → true if `rel` > `cur`.
// Non-numeric tags parse as 0, so a stray tag won't trigger a (false) update.
static bool verNewer(const char *rel, const char *cur) {
    while (*rel || *cur) {
        int r = atoi(rel), c = atoi(cur);
        if (r != c) return r > c;
        const char *dr = strchr(rel, '.'), *dc = strchr(cur, '.');
        rel = dr ? dr + 1 : ""; cur = dc ? dc + 1 : "";
    }
    return false;
}
// Ask GitHub for the latest RELEASE: its tag (= firmware version) and the firmware.bin
// asset URL. updAvail = the released version differs from this build. Runs on core-0.
static void updateCheck() {
    if (WiFi.status() != WL_CONNECTED || otaActive) return;
    WiFiClientSecure net; net.setInsecure();
    HTTPClient http; http.setConnectTimeout(5000); http.setTimeout(6000);
    if (!http.begin(net, "https://api.github.com/repos/holoduke/JKBMS/releases/latest")) return;
    http.addHeader("User-Agent", "jkbms-device");
    if (http.GET() == 200) {
        JsonDocument filter;                                  // keep only the fields we need (the release JSON is big)
        filter["tag_name"] = true;
        filter["assets"][0]["name"] = true;
        filter["assets"][0]["browser_download_url"] = true;
        JsonDocument d;
        if (!deserializeJson(d, http.getStream(), DeserializationOption::Filter(filter))) {
            const char *tag = d["tag_name"] | "";
            const char *url = "";
            for (JsonObject a : d["assets"].as<JsonArray>())
                if (strcmp(a["name"] | "", "firmware.bin") == 0) { url = a["browser_download_url"] | ""; break; }
            if (tag[0] && url[0]) {
                strncpy(updTag, tag, sizeof(updTag) - 1); updTag[sizeof(updTag) - 1] = 0;
                strncpy(updUrl, url, sizeof(updUrl) - 1); updUrl[sizeof(updUrl) - 1] = 0;
                const char *cur = instTag[0] ? instTag : FW_VERSION;
                updAvail = verNewer(updTag, cur);   // only flag a genuinely NEWER release (not a downgrade)
            }
        }
    }
    http.end();
}
// Download the latest release's firmware.bin and flash it, updating updProgress (0..100)
// so the device + web can show a progress bar. Runs on the core-0 net task; the render core
// stays live to draw the bar (it only stalls briefly during each flash write — safe).
static void selfUpdate() {
    if (!updUrl[0] || WiFi.status() != WL_CONNECTED) return;
    Serial.printf("[ota] self-update from %s\n", updUrl);
    updProgress = 0;
    WiFiClientSecure net; net.setInsecure();
    HTTPClient http; http.setConnectTimeout(8000); http.setTimeout(15000);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);  // GitHub asset → signed CDN redirect
    bool ok = false;
    if (http.begin(net, updUrl)) {
        http.addHeader("User-Agent", "jkbms-device");
        if (http.GET() == 200) {
            int len = http.getSize();
            WiFiClient *st = http.getStreamPtr();
            if (len > 0 && st && Update.begin(len)) {
                uint8_t buf[1024]; int written = 0; uint32_t t0 = millis();
                while (written < len && http.connected()) {
                    size_t avail = st->available();
                    if (avail) {
                        int n = st->readBytes(buf, avail > sizeof(buf) ? sizeof(buf) : avail);
                        if (n <= 0 || Update.write(buf, n) != (size_t)n) break;
                        written += n; updProgress = (int)((int64_t)written * 100 / len); t0 = millis();
                    } else { if (millis() - t0 > 10000) break; delay(2); }
                }
                ok = (written == len) && Update.end(true);
            }
        }
        http.end();
    }
    if (ok) {   // remember which tag we installed so we don't re-flash it in a loop
        updProgress = 100;
        prefs.begin("set", false); prefs.putString("instTag", updTag); prefs.end();
        Serial.println("[ota] ok — rebooting"); delay(700); ESP.restart();
    } else { Update.abort(); updProgress = -2; Serial.println("[ota] self-update failed"); }
}
static void netTask(void *) {
    uint32_t lastPoll = 0, lastUpd = 0;
    for (;;) {
        mqttLoop();     // HA / MQTT — connect, keepalive, publish, handle commands
        weatherLoop();  // geo-IP + Open-Meteo forecast (self-throttled)
        alertLoop();    // threshold push alerts (self-throttled)
        // BMS Modbus poll lives here too — its blocking UART reads (≤~150ms for an
        // offline pack) used to stall the render core every second; now core 1 only
        // reacts to the cached results (see bmsPoll_cb). busMux keeps the bus exclusive.
        uint32_t now = millis();
        if (now - lastPoll >= 1000) {
            lastPoll = now;
            bmsRead();   // history sampling + energy integration run on core 1 (see bmsPoll_cb) to avoid a cross-core race on those buffers
        }
        if ((!lastUpd && now > 30000) || (lastUpd && now - lastUpd > 21600000UL)) {   // GitHub release check ~30s after boot, then every 6h
            lastUpd = now; updateCheck();
            if (updAvail && autoUpdate) updGo = true;          // auto-update enabled → flash it
        }
        if (updGo) { updGo = false; selfUpdate(); }            // manual "Update now" (web) or auto trigger
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

