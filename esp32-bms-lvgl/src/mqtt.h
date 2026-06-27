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

static void mqPubSensor(int t, const char *key, const char *name, const char *unit, const char *dc) {
    char uid[48], topic[80], dev[120], pl[480];
    snprintf(uid, sizeof(uid), "%s_p%d_%s", mqId.c_str(), t, key);
    snprintf(topic, sizeof(topic), "homeassistant/sensor/%s/config", uid);
    snprintf(dev, sizeof(dev), "{\"ids\":[\"jkbms_%s_p%d\"],\"name\":\"JK BMS %d\",\"mf\":\"holoduke\",\"mdl\":\"JKBMS-ESP32\"}", mqId.c_str(), t, t + 1);
    int n = snprintf(pl, sizeof(pl),
        "{\"name\":\"%s\",\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/state\",\"val_tpl\":\"{{value_json.%s}}\",\"avty_t\":\"%s/status\",\"dev\":%s",
        name, uid, mqBase.c_str(), t, key, mqBase.c_str(), dev);
    if (unit[0]) n += snprintf(pl + n, sizeof(pl) - n, ",\"unit_of_meas\":\"%s\"", unit);
    if (dc[0])   n += snprintf(pl + n, sizeof(pl) - n, ",\"dev_cla\":\"%s\"", dc);
    snprintf(pl + n, sizeof(pl) - n, "}");
    mqtt.publish(topic, pl, true);
}

// Cumulative energy sensor — device_class energy + state_class total_increasing so it
// feeds the Home Assistant Energy dashboard (kWh). Separate from mqPubSensor (no state_class).
static void mqPubEnergy(int t, const char *key, const char *name) {
    char uid[48], topic[80], dev[120], pl[480];
    snprintf(uid, sizeof(uid), "%s_p%d_%s", mqId.c_str(), t, key);
    snprintf(topic, sizeof(topic), "homeassistant/sensor/%s/config", uid);
    snprintf(dev, sizeof(dev), "{\"ids\":[\"jkbms_%s_p%d\"],\"name\":\"JK BMS %d\",\"mf\":\"holoduke\",\"mdl\":\"JKBMS-ESP32\"}", mqId.c_str(), t, t + 1);
    snprintf(pl, sizeof(pl),
        "{\"name\":\"%s\",\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/state\",\"val_tpl\":\"{{value_json.%s}}\",\"avty_t\":\"%s/status\","
        "\"unit_of_meas\":\"kWh\",\"dev_cla\":\"energy\",\"stat_cla\":\"total_increasing\",\"dev\":%s}",
        name, uid, mqBase.c_str(), t, key, mqBase.c_str(), dev);
    mqtt.publish(topic, pl, true);
}

static void mqPubSwitch(int t, const char *key, const char *name) {
    char uid[48], topic[80], dev[120], pl[500];
    snprintf(uid, sizeof(uid), "%s_p%d_%s", mqId.c_str(), t, key);
    snprintf(topic, sizeof(topic), "homeassistant/switch/%s/config", uid);
    snprintf(dev, sizeof(dev), "{\"ids\":[\"jkbms_%s_p%d\"],\"name\":\"JK BMS %d\",\"mf\":\"holoduke\",\"mdl\":\"JKBMS-ESP32\"}", mqId.c_str(), t, t + 1);
    snprintf(pl, sizeof(pl),
        "{\"name\":\"%s\",\"uniq_id\":\"%s\",\"stat_t\":\"%s/p%d/state\",\"val_tpl\":\"{{value_json.%s}}\",\"cmd_t\":\"%s/p%d/%s/set\","
        "\"pl_on\":\"1\",\"pl_off\":\"0\",\"stat_on\":\"1\",\"stat_off\":\"0\",\"avty_t\":\"%s/status\",\"dev\":%s}",
        name, uid, mqBase.c_str(), t, key, mqBase.c_str(), t, key, mqBase.c_str(), dev);
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
        mqPubSensor(t, "cyc", "Cycles", "", "");
        mqPubSensor(t, "delta", "Cell delta", "mV", "voltage");
        mqPubSensor(t, "bcur", "Balance current", "A", "current");
        mqPubEnergy(t, "ein", "Energy charged");
        mqPubEnergy(t, "eout", "Energy discharged");
        mqPubSensor(t, "status", "Status", "", "");
        mqPubSensor(t, "alarms", "Alarms", "", "");
        mqPubSwitch(t, "chg", "Charge MOSFET");
        mqPubSwitch(t, "dis", "Discharge MOSFET");
        mqPubSwitch(t, "bal", "Balancer");
        delay(3);
    }
}

static void mqPublishState() {
    char buf[400], topic[48];
    for (int t = 0; t < numBms; t++) {
        const Bms &b = bms[t];
        float mn = 9, mx = 0;
        for (int i = 0; i < b.nCells; i++) { if (b.cell[i] < mn) mn = b.cell[i]; if (b.cell[i] > mx) mx = b.cell[i]; }
        uint32_t sc; const char *st = bmsStatusStr(t, demoMode || bmsLive[t], &sc);
        char al[90] = ""; int na = 0;
        for (int bit = 0; bit < 29 && na < 3; bit++)
            if (((b.errFlags >> bit) & 1u) && ERR_NAMES[bit][0]) { if (na++) strncat(al, ", ", sizeof(al) - strlen(al) - 1); strncat(al, ERR_NAMES[bit], sizeof(al) - strlen(al) - 1); }
        if (!na) strcpy(al, "none");
        snprintf(buf, sizeof(buf),
            "{\"soc\":%.0f,\"v\":%.2f,\"i\":%.1f,\"w\":%.0f,\"tmos\":%.0f,\"soh\":%d,\"cyc\":%lu,\"delta\":%d,\"bcur\":%.2f,"
            "\"ein\":%.3f,\"eout\":%.3f,\"status\":\"%s\",\"alarms\":\"%s\",\"chg\":\"%d\",\"dis\":\"%d\",\"bal\":\"%d\"}",
            b.soc, b.v, b.i, b.v * b.i, b.tMos, b.soh, (unsigned long)b.cycles, (int)((mx - mn) * 1000), b.balCur,
            lifeWhIn[t] / 1000.0, lifeWhOut[t] / 1000.0,
            st, al, bmsCharge[t] ? 1 : 0, bmsDischarge[t] ? 1 : 0, bmsBalancer[t] ? 1 : 0);
        snprintf(topic, sizeof(topic), "%s/p%d/state", mqBase.c_str(), t);
        mqtt.publish(topic, buf);
    }
}

// HA → device: jkbms/<id>/pN/<chg|dis|bal>/set  payload "1"/"0"
static void mqCallback(char *topic, byte *pl, unsigned int len) {
    String tp(topic); int pp = tp.indexOf("/p");
    if (pp < 0 || pp + 2 >= (int)tp.length()) return;
    int t = topic[pp + 2] - '0'; if (t < 0 || t >= numBms) return;
    bool on = len && pl[0] == '1';
    uint16_t reg = tp.indexOf("/chg/") > 0 ? 0x1070 : tp.indexOf("/dis/") > 0 ? 0x1074 : tp.indexOf("/bal/") > 0 ? 0x1078 : 0;
    if (!reg) return;
    if (bmsSet(t, reg, on ? 1 : 0)) {
        if (reg == 0x1070) bmsCharge[t] = on; else if (reg == 0x1074) bmsDischarge[t] = on; else bmsBalancer[t] = on;
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
        if (!mqBufSet) { mqtt.setBufferSize(768); mqtt.setSocketTimeout(3); mqBufSet = true; }   // 3s (not the 15s default) so an unreachable broker can't hog the core-0 task (it also runs the BMS poll)
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
