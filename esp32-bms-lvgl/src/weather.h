// Weather: locate by public IP (ip-api.com, HTTP) then fetch the forecast from
// Open-Meteo (HTTPS, no API key). Writes the wx* globals declared in main.cpp;
// the top bar draws today's glyph + temp, the web portal shows the 3-day forecast.
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

static uint32_t wxLastFetch = 0;
static float wxLat = 0, wxLon = 0;
static bool wxGeo = false;

static bool wxGeoIP() {
    WiFiClient net; HTTPClient http; http.setConnectTimeout(5000); http.setTimeout(5000);
    if (!http.begin(net, "http://ip-api.com/json/?fields=status,lat,lon,city")) return false;
    bool ok = false;
    if (http.GET() == 200) {
        JsonDocument d;
        if (!deserializeJson(d, http.getStream()) && d["status"] == "success") {
            wxLat = d["lat"] | 0.0f; wxLon = d["lon"] | 0.0f;
            strncpy(wxCity, d["city"] | "", sizeof(wxCity) - 1); wxCity[sizeof(wxCity) - 1] = 0;
            wxGeo = (wxLat != 0 || wxLon != 0); ok = wxGeo;
        }
    }
    http.end(); return ok;
}

static bool wxFetch() {
    if (!wxGeo) return false;
    WiFiClientSecure net; net.setInsecure();   // Open-Meteo is HTTPS; skip cert validation (no clock-of-trust on device)
    HTTPClient http; http.setConnectTimeout(6000); http.setTimeout(6000);
    char url[280];
    snprintf(url, sizeof(url),
        "https://api.open-meteo.com/v1/forecast?latitude=%.3f&longitude=%.3f"
        "&current=temperature_2m,weather_code&daily=weather_code,temperature_2m_max,temperature_2m_min"
        "&forecast_days=4&timezone=auto", wxLat, wxLon);
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
            int n = 0;
            for (int i = 0; i < 4 && i < (int)code.size(); i++) {
                wxDay[i].code = code[i] | 0;
                wxDay[i].tmax = (int)lroundf((float)(mx[i] | 0.0));
                wxDay[i].tmin = (int)lroundf((float)(mn[i] | 0.0));
                n++;
            }
            wxDays = n; wxOk = n > 0; ok = wxOk;
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
