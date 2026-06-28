// Weather: locate by public IP (ip-api.com, HTTP) then fetch the forecast from
// Open-Meteo (HTTPS, no API key). Writes the wx* globals declared in main.cpp;
// the top bar draws today's glyph + temp, the web portal shows the 3-day forecast.
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

static uint32_t wxLastFetch = 0;
static float wxLat = 0, wxLon = 0;
static bool wxGeo = false;

// Persist the last good forecast so a reboot-while-offline shows weather immediately
// (greyed as stale until a live fetch refreshes it). Coords ride along so we skip
// re-geolocating on a fixed install. Magic-gated so a layout change ignores old blobs.
#define WX_NVS_MAGIC 0x57583101u   // 'WX' + v01
static void saveWeather() {
    prefs.begin("wx", false);
    prefs.putUChar("ok", wxOk ? 1 : 0);
    prefs.putInt("t", wxCurTemp);
    prefs.putInt("c", wxCurCode);
    prefs.putInt("days", wxDays);
    prefs.putBytes("day", wxDay, sizeof(wxDay));
    prefs.putBytes("at", &wxFetchedAt, sizeof(wxFetchedAt));
    prefs.putFloat("lat", wxLat);
    prefs.putFloat("lon", wxLon);
    prefs.putString("city", wxCity);
    prefs.putUInt("magic", WX_NVS_MAGIC);   // magic LAST → a torn first write leaves no magic → ignored on load
    prefs.end();
}
static void loadWeather() {
    prefs.begin("wx", true);
    if (prefs.getUInt("magic", 0) == WX_NVS_MAGIC) {
        wxOk = prefs.getUChar("ok", 0) != 0;
        wxCurTemp = prefs.getInt("t", 0);
        wxCurCode = prefs.getInt("c", -1);
        wxDays = prefs.getInt("days", 0);
        prefs.getBytes("day", wxDay, sizeof(wxDay));
        prefs.getBytes("at", &wxFetchedAt, sizeof(wxFetchedAt));
        wxLat = prefs.getFloat("lat", 0); wxLon = prefs.getFloat("lon", 0);
        wxGeo = (wxLat != 0 || wxLon != 0);    // have coords → skip re-geolocation, go straight to the forecast
        String c = prefs.getString("city", ""); strncpy(wxCity, c.c_str(), sizeof(wxCity) - 1); wxCity[sizeof(wxCity) - 1] = 0;
    }
    prefs.end();
    // wxFreshThisBoot stays false → restored data shows greyed until the first live fetch this boot.
}

// Primary geo source: boogiewoogiedoo /visitors/location (HTTPS, precise lat/lon as strings).
static bool wxGeoPrimary() {
    WiFiClientSecure net; net.setInsecure();
    HTTPClient http; http.setConnectTimeout(6000); http.setTimeout(6000);
    if (!http.begin(net, "https://www.boogiewoogiedoo.com/visitors/location")) return false;
    bool ok = false;
    if (http.GET() == 200) {
        String body = http.getString();
        JsonDocument d;
        if (!deserializeJson(d, body)) {
            wxLat = atof(d["lat"] | "0"); wxLon = atof(d["lon"] | "0");   // values arrive as strings
            strncpy(wxCity, d["city"] | "", sizeof(wxCity) - 1); wxCity[sizeof(wxCity) - 1] = 0;
            wxGeo = (wxLat != 0 || wxLon != 0); ok = wxGeo;
        }
    }
    http.end(); return ok;
}
// Fallback geo: ip-api.com (plain HTTP, city-centroid).
static bool wxGeoFallback() {
    WiFiClient net; HTTPClient http; http.setConnectTimeout(5000); http.setTimeout(5000);
    if (!http.begin(net, "http://ip-api.com/json/?fields=status,lat,lon,city")) return false;
    bool ok = false;
    if (http.GET() == 200) {
        String body = http.getString();
        JsonDocument d;
        if (!deserializeJson(d, body) && d["status"] == "success") {
            wxLat = d["lat"] | 0.0f; wxLon = d["lon"] | 0.0f;
            strncpy(wxCity, d["city"] | "", sizeof(wxCity) - 1); wxCity[sizeof(wxCity) - 1] = 0;
            wxGeo = (wxLat != 0 || wxLon != 0); ok = wxGeo;
        }
    }
    http.end(); return ok;
}
static bool wxGeoIP() { return wxGeoPrimary() || wxGeoFallback(); }

static bool wxFetch() {
    if (!wxGeo) return false;
    WiFiClientSecure net; net.setInsecure();   // Open-Meteo is HTTPS; skip cert validation (no clock-of-trust on device)
    HTTPClient http; http.setConnectTimeout(6000); http.setTimeout(6000);
    char url[280];
    snprintf(url, sizeof(url),
        "https://api.open-meteo.com/v1/forecast?latitude=%.3f&longitude=%.3f"
        "&current=temperature_2m,weather_code&daily=weather_code,temperature_2m_max,temperature_2m_min,precipitation_probability_max"
        "&forecast_days=5&timezone=auto", wxLat, wxLon);
    if (!http.begin(net, url)) { wxHttp = -1000; return false; }
    bool ok = false;
    int code = http.GET();
    wxHttp = code;
    if (code == 200) {
        String body = http.getString();          // buffer whole body — chunked TLS streams parse unreliably
        JsonDocument d;
        DeserializationError err = deserializeJson(d, body);
        if (err) wxHttp = -2000 - (int)err.code();
        if (!err) {
            wxCurTemp = (int)lroundf((float)(d["current"]["temperature_2m"] | 0.0));
            wxCurCode = d["current"]["weather_code"] | -1;
            JsonArray code = d["daily"]["weather_code"], mx = d["daily"]["temperature_2m_max"], mn = d["daily"]["temperature_2m_min"];
            JsonArray pp = d["daily"]["precipitation_probability_max"];
            int n = 0;
            for (int i = 0; i < 5 && i < (int)code.size(); i++) {
                wxDay[i].code = code[i] | 0;
                wxDay[i].tmax = (int)lroundf((float)(mx[i] | 0.0));
                wxDay[i].tmin = (int)lroundf((float)(mn[i] | 0.0));
                wxDay[i].pop = pp[i] | 0;
                n++;
            }
            wxDays = n; wxOk = n > 0; ok = wxOk;
            if (wxOk) { wxFetchedAt = time(nullptr); wxFreshThisBoot = true; wxDirty = true; }   // cache for reboot + clear stale; core 1 does the NVS write (prefs is core-1-only)
        }
    }
    http.end(); return ok;
}

static void weatherLoop() {
    if (otaActive || !timeSynced || WiFi.status() != WL_CONNECTED) return;   // wait until the net is proven (NTP synced)
    uint32_t now = millis();
    uint32_t interval = wxOk ? 1800000UL : 60000UL;   // 30 min once we have data; retry every minute until first success
    if (wxLastFetch && now - wxLastFetch < interval) return;
    wxLastFetch = now;
    if (!wxGeo) wxGeoIP();
    wxFetch();
}
