// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.

// Background I/O worker, pinned to core 0 (the UI/render + LVGL run on core 1). All the
// blocking network work lives here so a slow/unreachable endpoint can never freeze the
// display or touch: MQTT (connect can block ~seconds), the weather/geo HTTPS fetches,
// and the alert webhook POSTs. The MQTT command path (mqCallback → bmsSet) is the only
// one that touches the Modbus bus, and that's serialised against the core-1 poll by busMux.
// Good home for any future blocking/background job (extra sensors, cloud sync, etc.).
// Panel push task (core 0): transmits the snapshot core 1 hands it. This is the ~40ms
// blocking pixel-swizzle+DMA — doing it here keeps core 1 free for touch + next-frame render.
// TLS trust for the self-update path (GitHub API + release CDN). Weather/alerts stay
// setInsecure (read-only data / user-chosen webhook), but here a MITM could feed us
// arbitrary FIRMWARE — so validate against the Mozilla root bundle that ships inside
// the prebuilt arduino-esp32 mbedtls (esp_crt_bundle; ~68KB flash, verified on demand
// from flash so it costs no extra heap). Validation needs a sane clock → callers gate
// on timeSynced. If GitHub ever rotates to a root outside the bundle the update check
// fails closed (no update offered) — the device otherwise keeps working.
extern const uint8_t CA_BUNDLE_START[] asm("_binary_x509_crt_bundle_start");
extern const uint8_t CA_BUNDLE_END[]   asm("_binary_x509_crt_bundle_end");
static void otaTrust(WiFiClientSecure &net) { net.setCACertBundle(CA_BUNDLE_START, (size_t)(CA_BUNDLE_END - CA_BUNDLE_START)); }
// Compare dotted numeric versions ("1.0.224") component-wise → true if `rel` > `cur`.
// Non-numeric tags parse as 0, so a stray tag won't trigger a (false) update.
static bool verNewer(const char *rel, const char *cur) {
    if (*rel == 'v' || *rel == 'V') rel++;   // tolerate "v1.0.225"-style tags
    if (*cur == 'v' || *cur == 'V') cur++;
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
    if (WiFi.status() != WL_CONNECTED || !timeSynced || otaActive) return;   // cert validation needs a real clock
    WiFiClientSecure net; otaTrust(net);
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
// One download+flash attempt of updUrl. Returns true only on a fully written, finalised image.
// Streams the GitHub asset (→ signed CDN redirect) straight into the inactive app slot.
static bool otaDownloadOnce() {
    WiFiClientSecure net; otaTrust(net);
    HTTPClient http; http.setConnectTimeout(8000); http.setTimeout(20000);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);  // GitHub asset → signed CDN redirect
    bool ok = false;
    if (http.begin(net, updUrl)) {
        http.addHeader("User-Agent", "jkbms-device");
        int code = http.GET();
        if (code == 200) {
            int len = http.getSize();
            WiFiClient *st = http.getStreamPtr();
            if (len > 0 && st && Update.begin(len)) {
                uint8_t buf[1460]; int written = 0; uint32_t t0 = millis();   // 1460 = one TCP segment
                while (written < len && http.connected()) {
                    size_t avail = st->available();
                    if (avail) {
                        int n = st->readBytes(buf, avail > sizeof(buf) ? sizeof(buf) : avail);
                        if (n <= 0 || Update.write(buf, n) != (size_t)n) break;
                        written += n; updProgress = (int)((int64_t)written * 100 / len); t0 = millis();
                    } else { if (millis() - t0 > 25000) break; delay(2); }   // 25s stall window (core 0 is unwatched by the WDT)
                }
                if (written == len) ok = Update.end(true);
                else { Serial.printf("[ota] stalled at %d/%d\n", written, len); Update.abort(); }
            } else Serial.printf("[ota] begin failed (len=%d)\n", len);
        } else Serial.printf("[ota] GET %d\n", code);
        http.end();
    }
    return ok;
}
// Download the latest release's firmware.bin and flash it, updating updProgress (0..100) for
// the on-screen + web progress bar. Runs on the core-0 net task; the render core stays live.
// Hardened after remote-OTA failures: the download used to abort mid-stream because (1) WiFi
// modem-sleep was left ON, letting the radio micro-sleep and stall the TLS read into the abort
// window, and (2) a single transient drop killed the whole update. Now: keep the radio awake
// for the whole transfer, free heap/socket by dropping MQTT first, and retry a few times.
static void selfUpdate() {
    if (!updUrl[0] || WiFi.status() != WL_CONNECTED) return;
    Serial.printf("[ota] self-update from %s\n", updUrl);
    updProgress = 0;
    WiFi.setSleep(false);                     // radio stays awake for the whole download (was the stall cause)
    if (mqtt.connected()) mqtt.disconnect();  // free the socket + buffer heap for the TLS download
    bool ok = false;
    for (int attempt = 0; attempt < 3 && !ok; attempt++) {
        if (attempt) { Serial.printf("[ota] retry %d/2\n", attempt); updProgress = 0; delay(1500); }
        ok = otaDownloadOnce();
    }
    if (!otaActive) WiFi.setSleep(true);      // restore modem power-save (unless an OTA push is now in flight)
    if (ok) {   // remember which tag we installed so we don't re-flash it in a loop
        updProgress = 100;
        // NVS's C API is thread-safe, but the shared global `prefs` OBJECT is not (core 1 may be
        // mid begin()/end() in a settings/history save) → use a private instance on this core-0 task.
        Preferences lp; lp.begin("set", false); lp.putString("instTag", updTag); lp.end();
        Serial.println("[ota] ok — rebooting"); delay(700); ESP.restart();
    } else { updProgress = -2; Serial.println("[ota] self-update failed after retries"); }
}
static void netTask(void *) {
    uint32_t lastPoll = 0, lastUpd = 0;
    for (;;) {
        mqttLoop();     // HA / MQTT — connect, keepalive, publish, handle commands
        weatherLoop();  // geo-IP + Open-Meteo forecast (self-throttled)
        alertLoop();    // threshold push alerts (self-throttled)
        if (alTestGo) { alTestGo = false; alTestRes = alertSend("JK BMS test alert \xE2\x9C\x93") ? 1 : 0; }   // web Test button (blocking POST → this core)
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

