// MQTT + Home Assistant auto-discovery. Included into main.cpp (same TU) after the
// globals/helpers it uses (bms[], numBms, bmsStatusStr, ERR_NAMES, bmsSet, the mqtt*
// config globals). The device publishes HA discovery configs once on connect, then
// pushes per-pack state JSON; HA creates all sensors + the FET/balancer switches.
#include <PubSubClient.h>

static WiFiClient mqttNet;
static PubSubClient mqtt(mqttNet);
static String mqId, mqBase;          // device id (MAC tail) + base topic "jkbms/<id>"
static uint32_t mqLastState = 0, mqLastTry = 0;
static bool mqBufSet = false;

static void mqInitIds() {
    if (mqId.length()) return;
    uint8_t m[6] = {0}; esp_read_mac(m, ESP_MAC_WIFI_STA);
    char b[10]; snprintf(b, sizeof(b), "%02x%02x%02x", m[3], m[4], m[5]);
    mqId = b; mqBase = "jkbms/" + mqId;
}

// Shared HA "device" block — one physical BMS pack. All entities for pack t carry the same
// `ids`, so HA groups them under a single device card named "JK BMS 1"/"JK BMS 2", with the
// firmware version shown and a clickable link (cu) straight to the device's web portal.
static void mqDev(char *o, size_t n, int t) {
    snprintf(o, n, "{\"ids\":[\"jkbms_%s_p%d\"],\"name\":\"JK BMS %d\",\"mf\":\"holoduke\",\"mdl\":\"JKBMS-ESP32\","
                   "\"sw\":\"" FW_VERSION "\",\"cu\":\"http://%s\"}",
             mqId.c_str(), t, t + 1, WiFi.localIP().toString().c_str());
}
// sc = state_class ("measurement" for a live reading → HA keeps long-term statistics/graphs;
// "" for text sensors like status/alarms; "total_increasing" for monotonic counters). Every
// entity sets has_entity_name so HA composes the friendly name as "JK BMS 1 <name>".
static void mqPubSensor(int t, const char *key, const char *name, const char *unit, const char *dc, const char *sc = "measurement") {
    char uid[48], topic[80], dev[176], pl[576];
    snprintf(uid, sizeof(uid), "%s_p%d_%s", mqId.c_str(), t, key);
    snprintf(topic, sizeof(topic), "homeassistant/sensor/%s/config", uid);
    mqDev(dev, sizeof(dev), t);
    int n = snprintf(pl, sizeof(pl),
        "{\"name\":\"%s\",\"has_entity_name\":true,\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/state\",\"val_tpl\":\"{{value_json.%s}}\",\"avty_t\":\"%s/status\",\"dev\":%s",
        name, uid, mqBase.c_str(), t, key, mqBase.c_str(), dev);
    if (unit[0]) n += snprintf(pl + n, sizeof(pl) - n, ",\"unit_of_meas\":\"%s\"", unit);
    if (dc[0])   n += snprintf(pl + n, sizeof(pl) - n, ",\"dev_cla\":\"%s\"", dc);
    if (sc[0])   n += snprintf(pl + n, sizeof(pl) - n, ",\"stat_cla\":\"%s\"", sc);
    snprintf(pl + n, sizeof(pl) - n, "}");
    mqtt.publish(topic, pl, true);
}

// Cumulative energy sensor — device_class energy + state_class total_increasing so it
// feeds the Home Assistant Energy dashboard (kWh).
static void mqPubEnergy(int t, const char *key, const char *name) {
    char uid[48], topic[80], dev[176], pl[576];
    snprintf(uid, sizeof(uid), "%s_p%d_%s", mqId.c_str(), t, key);
    snprintf(topic, sizeof(topic), "homeassistant/sensor/%s/config", uid);
    mqDev(dev, sizeof(dev), t);
    snprintf(pl, sizeof(pl),
        "{\"name\":\"%s\",\"has_entity_name\":true,\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/state\",\"val_tpl\":\"{{value_json.%s}}\",\"avty_t\":\"%s/status\","
        "\"unit_of_meas\":\"kWh\",\"dev_cla\":\"energy\",\"stat_cla\":\"total_increasing\",\"dev\":%s}",
        name, uid, mqBase.c_str(), t, key, mqBase.c_str(), dev);
    mqtt.publish(topic, pl, true);
}

static void mqPubSwitch(int t, const char *key, const char *name) {
    char uid[48], topic[80], dev[176], pl[600];
    snprintf(uid, sizeof(uid), "%s_p%d_%s", mqId.c_str(), t, key);
    snprintf(topic, sizeof(topic), "homeassistant/switch/%s/config", uid);
    mqDev(dev, sizeof(dev), t);
    snprintf(pl, sizeof(pl),
        "{\"name\":\"%s\",\"has_entity_name\":true,\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/state\",\"val_tpl\":\"{{value_json.%s}}\",\"cmd_t\":\"%s/p%d/%s/set\","
        "\"pl_on\":\"1\",\"pl_off\":\"0\",\"stat_on\":\"1\",\"stat_off\":\"0\",\"avty_t\":\"%s/status\",\"dev\":%s}",
        name, uid, mqBase.c_str(), t, key, mqBase.c_str(), t, key, mqBase.c_str(), dev);
    mqtt.publish(topic, pl, true);
}

// Per-cell voltage sensor. All cells share one state topic (.../cells = JSON array);
// each sensor pulls its index. Marked diagnostic so they don't clutter the main HA card.
static void mqPubCell(int t, int i) {
    char uid[52], topic[84], dev[176], pl[576];
    snprintf(uid, sizeof(uid), "%s_p%d_c%d", mqId.c_str(), t, i);
    snprintf(topic, sizeof(topic), "homeassistant/sensor/%s/config", uid);
    mqDev(dev, sizeof(dev), t);
    snprintf(pl, sizeof(pl),
        "{\"name\":\"Cell %d\",\"has_entity_name\":true,\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/cells\",\"val_tpl\":\"{{value_json[%d]}}\","
        "\"unit_of_meas\":\"V\",\"dev_cla\":\"voltage\",\"stat_cla\":\"measurement\",\"ent_cat\":\"diagnostic\",\"avty_t\":\"%s/status\",\"dev\":%s}",
        i + 1, uid, mqBase.c_str(), t, i, mqBase.c_str(), dev);
    mqtt.publish(topic, pl, true);
}
static void mqDiscovery() {
    for (int t = 0; t < numBms; t++) {
        mqPubSensor(t, "soc", "SOC", "%", "battery");
        mqPubSensor(t, "v", "Voltage", "V", "voltage");
        mqPubSensor(t, "i", "Current", "A", "current");
        mqPubSensor(t, "w", "Power", "W", "power");
        mqPubSensor(t, "tmos", "MOSFET temp", "°C", "temperature");
        mqPubSensor(t, "soh", "Health", "%", "");
        mqPubSensor(t, "cyc", "Cycles", "", "", "total_increasing");   // monotonic counter, not a measurement
        mqPubSensor(t, "delta", "Cell delta", "mV", "voltage");
        mqPubSensor(t, "bcur", "Balance current", "A", "current");
        mqPubEnergy(t, "ein", "Energy charged");
        mqPubEnergy(t, "eout", "Energy discharged");
        mqPubSensor(t, "status", "Status", "", "", "");     // text → no state_class
        mqPubSensor(t, "alarms", "Alarms", "", "", "");     // text → no state_class
        mqPubSwitch(t, "chg", "Charge MOSFET");
        mqPubSwitch(t, "dis", "Discharge MOSFET");
        mqPubSwitch(t, "bal", "Balancer");
        for (int i = 0; i < bms[t].nCells && i < MAXCELLS; i++) { mqPubCell(t, i); delay(2); }   // per-cell voltage sensors
        delay(3);
    }
}

static void mqPublishState() {
    char buf[400], topic[48];
    for (int t = 0; t < numBms; t++) {
        const Bms &b = bms[t];
        float mn = 9, mx = 0;
        for (int i = 0; i < b.nCells; i++) { if (b.cell[i] < mn) mn = b.cell[i]; if (b.cell[i] > mx) mx = b.cell[i]; }
        int deltaMv = b.nCells > 0 ? (int)((mx - mn) * 1000) : 0;   // no cells read yet → 0, not -9000
        uint32_t sc; const char *st = bmsStatusStr(t, demoMode || bmsLive[t], &sc);
        char al[90] = ""; int na = 0;
        for (int bit = 0; bit < NERR && na < 3; bit++)
            if (((b.errFlags >> bit) & 1u) && ERR_NAMES[bit][0]) { if (na++) strncat(al, ", ", sizeof(al) - strlen(al) - 1); strncat(al, ERR_NAMES[bit], sizeof(al) - strlen(al) - 1); }
        if (!na) strcpy(al, "none");
        int jn = snprintf(buf, sizeof(buf),
            "{\"soc\":%.0f,\"v\":%.2f,\"i\":%.1f,\"w\":%.0f,\"tmos\":%.0f,\"soh\":%d,\"cyc\":%lu,\"delta\":%d,\"bcur\":%.2f,"
            "\"ein\":%.3f,\"eout\":%.3f,\"status\":\"%s\",\"alarms\":\"%s\",\"chg\":\"%d\",\"dis\":\"%d\",\"bal\":\"%d\"}",
            b.soc, b.v, b.i, b.v * b.i, b.tMos, b.soh, (unsigned long)b.cycles, deltaMv, b.balCur,
            lifeWhIn[t] / 1000.0, lifeWhOut[t] / 1000.0,
            st, al, bmsCharge[t] ? 1 : 0, bmsDischarge[t] ? 1 : 0, bmsBalancer[t] ? 1 : 0);
        if (jn < 0 || jn >= (int)sizeof(buf)) continue;   // truncated → invalid JSON; skip this cycle rather than feed HA garbage
        snprintf(topic, sizeof(topic), "%s/p%d/state", mqBase.c_str(), t);
        mqtt.publish(topic, buf);
        if (b.nCells > 0) {   // per-cell voltages as a JSON array on a side topic (each Cell N sensor pulls its index)
            char cb[220]; int cn = snprintf(cb, sizeof(cb), "[");
            for (int i = 0; i < b.nCells && i < MAXCELLS; i++) cn += snprintf(cb + cn, sizeof(cb) - cn, "%s%.3f", i ? "," : "", b.cell[i]);
            snprintf(cb + cn, sizeof(cb) - cn, "]");
            snprintf(topic, sizeof(topic), "%s/p%d/cells", mqBase.c_str(), t);
            mqtt.publish(topic, cb);
        }
    }
}

// HA → device: jkbms/<id>/pN/<chg|dis|bal>/set  payload "1"/"0"
static void mqCallback(char *topic, byte *pl, unsigned int len) {
    String tp(topic); int pp = tp.indexOf("/p");
    if (pp < 0 || pp + 2 >= (int)tp.length()) return;
    int t = topic[pp + 2] - '0'; if (t < 0 || t >= numBms) return;
    bool on = len && pl[0] == '1';
    uint16_t reg = tp.indexOf("/chg/") > 0 ? REG_CHG_SW : tp.indexOf("/dis/") > 0 ? REG_DIS_SW : tp.indexOf("/bal/") > 0 ? REG_BAL_SW : 0;
    if (!reg) return;
    if (bmsSet(t, reg, on ? 1 : 0)) {
        if (reg == REG_CHG_SW) bmsCharge[t] = on; else if (reg == REG_DIS_SW) bmsDischarge[t] = on; else bmsBalancer[t] = on;
        cfgDirty = true; cfgDirtyAt = millis();
    }
    mqPublishState();
}

static void mqttLoop() {
    if (otaActive) return;
    mqttUp = mqtt.connected();
    if (!mqttEnabled || mqttHost[0] == 0 || WiFi.status() != WL_CONNECTED) { if (mqttUp) mqtt.disconnect(); return; }
    if (mqttReconnect) { mqttReconnect = false; mqtt.disconnect(); mqLastTry = 0; }
    if (!mqtt.connected()) {
        if (mqLastTry && millis() - mqLastTry < 5000) return;
        mqLastTry = millis();
        mqInitIds();
        if (!mqBufSet) { mqtt.setBufferSize(1024); mqtt.setSocketTimeout(3); mqBufSet = true; }   // 1KB fits the enriched discovery config; 3s (not 15s default) timeout so an unreachable broker can't hog the core-0 task (it also runs the BMS poll)
        mqtt.setServer(mqttHost, mqttPort); mqtt.setCallback(mqCallback);
        char willT[48]; snprintf(willT, sizeof(willT), "%s/status", mqBase.c_str());
        char cid[40]; snprintf(cid, sizeof(cid), "jkbms-%s", mqId.c_str());
        bool ok = mqttUser[0] ? mqtt.connect(cid, mqttUser, mqttPass, willT, 0, true, "offline")
                              : mqtt.connect(cid, willT, 0, true, "offline");
        if (ok) {
            mqtt.publish(willT, "online", true);
            char sub[48]; snprintf(sub, sizeof(sub), "%s/+/+/set", mqBase.c_str()); mqtt.subscribe(sub);
            mqDiscovery(); mqPublishState(); mqLastState = millis();
        }
        mqttUp = mqtt.connected();
        return;
    }
    mqtt.loop();
    if (millis() - mqLastState > 4000) { mqLastState = millis(); mqPublishState(); }
}
