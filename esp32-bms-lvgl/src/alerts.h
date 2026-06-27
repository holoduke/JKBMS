// Threshold push alerts. Included into main.cpp AFTER the globals/helpers it uses
// (bms[], bmsLive[], numBms, alert* config, bmsStatusStr, ERR_NAMES). Conditions are
// edge-triggered per pack (a bitmask of what's currently active), so each problem fires
// exactly once when it appears and re-arms only after it clears — no notification spam.
//
// Delivery is a plain HTTP(S) POST with the message as the body, which is exactly the
// ntfy.sh contract (https://ntfy.sh/<topic>). Any webhook that accepts a text body works.
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// condition bits
#define AL_FAULT  0x01
#define AL_SOCLO  0x02
#define AL_TEMPHI 0x04
#define AL_DELTA  0x08

// POST `msg` to the configured webhook. Returns true on a 2xx. Brief timeout so a dead
// endpoint can't stall the main loop for long (alerts are infrequent + edge-triggered).
static bool alertSend(const char *msg) {
    if (!alertUrl[0] || WiFi.status() != WL_CONNECTED) return false;
    bool https = strncmp(alertUrl, "https://", 8) == 0;
    HTTPClient http; bool begun;
    WiFiClientSecure secure; WiFiClient plain;
    if (https) { secure.setInsecure(); begun = http.begin(secure, alertUrl); }
    else       { begun = http.begin(plain, alertUrl); }
    if (!begun) return false;
    http.setConnectTimeout(4000); http.setTimeout(4000);
    http.addHeader("Content-Type", "text/plain");
    http.addHeader("Title", "JK BMS");          // ntfy notification title (ignored by generic webhooks)
    int code = http.POST((uint8_t *)msg, strlen(msg));
    http.end();
    return code >= 200 && code < 300;
}

// Evaluate every live pack, send one message per newly-appeared condition. Called from loop().
static void alertLoop() {
    static uint32_t lastCheck = 0;
    if (!alertEnabled || !alertUrl[0] || otaActive) return;
    uint32_t now = millis();
    if (now - lastCheck < 3000) return;         // throttle the evaluation; sending only happens on edges
    lastCheck = now;
    if (WiFi.status() != WL_CONNECTED) return;

    for (int t = 0; t < numBms; t++) {
        if (!bmsLive[t]) { alState[t] = 0; continue; }   // offline → clear so a returning fault re-alerts
        const Bms &b = bms[t];
        uint8_t cur = 0;
        if (alOnFault && b.errFlags) cur |= AL_FAULT;
        if (b.soc > 0 && b.soc < alSocLo) cur |= AL_SOCLO;
        float tMax = b.tMos; if (b.tp1 > tMax) tMax = b.tp1; if (b.tp2 > tMax) tMax = b.tp2;
        if (tMax > alTempHi) cur |= AL_TEMPHI;
        float mn = 9, mx = 0;
        for (int i = 0; i < b.nCells; i++) { if (b.cell[i] < mn) mn = b.cell[i]; if (b.cell[i] > mx) mx = b.cell[i]; }
        int deltaMv = (b.nCells > 0) ? (int)((mx - mn) * 1000.0f) : 0;
        if (deltaMv > alDeltaHi) cur |= AL_DELTA;

        uint8_t fresh = cur & ~alState[t];      // conditions that just became active
        alState[t] = cur;
        if (!fresh) continue;

        char msg[200]; int n = snprintf(msg, sizeof(msg), "BMS %d: ", t + 1); bool first = true;
        if (fresh & AL_FAULT) {
            n += snprintf(msg + n, sizeof(msg) - n, "%sfault", first ? "" : ", "); first = false;
            for (int bit = 0, shown = 0; bit < 29 && shown < 2; bit++)
                if (((b.errFlags >> bit) & 1u) && ERR_NAMES[bit][0]) { n += snprintf(msg + n, sizeof(msg) - n, "%s%s", shown++ ? ", " : " (", ERR_NAMES[bit]); }
            if (msg[n - 1] != ' ' && strchr(msg, '(')) n += snprintf(msg + n, sizeof(msg) - n, ")");
        }
        if (fresh & AL_SOCLO)  { n += snprintf(msg + n, sizeof(msg) - n, "%slow SOC %.0f%%", first ? "" : ", ", b.soc); first = false; }
        if (fresh & AL_TEMPHI) { n += snprintf(msg + n, sizeof(msg) - n, "%shigh temp %.0f\xC2\xB0""C", first ? "" : ", ", tMax); first = false; }
        if (fresh & AL_DELTA)  { n += snprintf(msg + n, sizeof(msg) - n, "%scell delta %dmV", first ? "" : ", ", deltaMv); first = false; }
        alertSend(msg);
    }
}
