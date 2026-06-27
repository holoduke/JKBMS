// Lightweight i18n for the JK BMS firmware. Included into main.cpp (same TU).
// One string table keyed by StrKey, with a column per language. T(k) returns the
// string for the current language g_lang. Only the FUNCTIONAL UI (dashboard +
// settings + status + errors) is translated; the decorative screensaver/HUD prop
// text stays English on purpose.
//
// Source is UTF-8; literals below are written with real accented characters so
// LVGL (which renders UTF-8) shows them directly. Phase 1 languages share one
// extended-Latin font (regenerated from Montserrat). Russian/Chinese/Arabic
// (+ RTL) come later and will need their own fonts.
#pragma once
#include <stdint.h>

enum { LANG_EN, LANG_FR, LANG_DE, LANG_NL, LANG_PL, LANG_PT, LANG_ES, LANG_VI, LANG_COUNT };
static uint8_t g_lang = 0;   // index into the columns below; persisted in NVS ("lang")

// Native names for the picker (never translated).
static const char *const LANG_NAME[LANG_COUNT] = {
    "English", "Français", "Deutsch", "Nederlands", "Polski", "Português", "Español", "Tiếng Việt"};

enum {
    // ---- status pill (bmsStatusStr) ----
    K_OFFLINE, K_ALARM, K_FET_OFF, K_BALANCING, K_CHARGING, K_DISCHARGING, K_FULL, K_IDLE,
    // ---- dashboard tiles / chrome ----
    K_VOLTAGE, K_PK_CHG, K_PK_DIS, K_UPTIME, K_REMAIN, K_CELLS, K_POWER_DRAW, K_CAPACITY,
    K_COLLECTING, K_DAYS, K_HOURS,
    // ---- settings: System tab ----
    K_SETTINGS, K_AUTO_SWITCH, K_SWITCH_INTERVAL, K_BRIGHTNESS, K_AUTO_SLEEP, K_ECO_MODE,
    K_DIM_AFTER, K_TEMP_UNIT, K_TIME_FORMAT, K_WIFI_AUTO, K_DEMO_SPEED, K_SYSTEM_INFO,
    K_FIRMWARE, K_DEMO_MODE, K_SCREENSAVER, K_SCREENSAVER_AFTER, K_WEB_ADDRESS,
    K_WEB_USERNAME, K_WEB_PASSWORD, K_LANGUAGE,
    // ---- settings: System values ----
    K_ON, K_OFF, K_NEVER, K_CELSIUS, K_FAHRENHEIT, K_12_HOUR, K_24_HOUR, K_VIEW,
    // ---- sub-tab names ----
    K_TAB_WIFI, K_TAB_SYSTEM,
    K_COUNT
};

static const char *const STR[K_COUNT][LANG_COUNT] = {
    //                        EN                FR                 DE               NL              PL               PT               ES                 VI
    /*K_OFFLINE*/        {"Offline",        "Hors ligne",      "Offline",       "Offline",      "Offline",       "Offline",       "Sin conexión",    "Ngoại tuyến"},
    /*K_ALARM*/          {"Alarm",          "Alarme",          "Alarm",         "Alarm",        "Alarm",         "Alarme",        "Alarma",          "Báo động"},
    /*K_FET_OFF*/        {"FET off",        "FET arrêt",       "FET aus",       "FET uit",      "FET wył.",      "FET deslig.",   "FET apag.",       "FET tắt"},
    /*K_BALANCING*/      {"Balancing",      "Équilibrage",     "Balancieren",   "Balanceren",   "Równoważ.",     "Equilibrando",  "Equilibrando",    "Cân bằng"},
    /*K_CHARGING*/       {"Charging",       "En charge",       "Lädt",          "Opladen",      "Ładowanie",     "Carregando",    "Cargando",        "Đang sạc"},
    /*K_DISCHARGING*/    {"Discharging",    "Décharge",        "Entlädt",       "Ontladen",     "Rozład.",       "Descarreg.",    "Descargando",     "Đang xả"},
    /*K_FULL*/           {"Full",           "Plein",           "Voll",          "Vol",          "Pełny",         "Cheio",         "Lleno",           "Đầy"},
    /*K_IDLE*/           {"Idle",           "Inactif",         "Leerlauf",      "Inactief",     "Bezczynny",     "Inativo",       "Inactivo",        "Nghỉ"},

    /*K_VOLTAGE*/        {"VOLTAGE",        "TENSION",         "SPANNUNG",      "SPANNING",     "NAPIĘCIE",      "TENSÃO",        "VOLTAJE",         "ĐIỆN ÁP"},
    /*K_PK_CHG*/         {"PK CHG",         "PIC CH",          "MAX LAD",       "PIEK LAD",     "SZCZ ŁAD",      "PICO CG",       "PICO CG",         "ĐỈNH SẠC"},
    /*K_PK_DIS*/         {"PK DIS",         "PIC DÉCH",        "MAX ENTL",      "PIEK ONTL",    "SZCZ ROZ",      "PICO DESC",     "PICO DESC",       "ĐỈNH XẢ"},
    /*K_UPTIME*/         {"UPTIME",         "DURÉE",           "LAUFZEIT",      "ACTIEF",       "CZAS PRACY",    "ATIVO",         "ACTIVO",          "HOẠT ĐỘNG"},
    /*K_REMAIN*/         {"REMAIN",         "RESTANT",         "VERBL.",        "RESTEREND",    "POZOST.",       "RESTANTE",      "RESTANTE",        "CÒN LẠI"},
    /*K_CELLS*/          {"CELLS",          "CELLULES",        "ZELLEN",        "CELLEN",       "OGNIWA",        "CÉLULAS",       "CELDAS",          "Ô PIN"},
    /*K_POWER_DRAW*/     {"POWER DRAW",     "PUISSANCE",       "LEISTUNG",      "VERMOGEN",     "MOC",           "POTÊNCIA",      "POTENCIA",        "CÔNG SUẤT"},
    /*K_CAPACITY*/       {"CAPACITY",       "CAPACITÉ",        "KAPAZITÄT",     "CAPACITEIT",   "POJEMNOŚĆ",     "CAPACID.",      "CAPACIDAD",       "DUNG LƯỢNG"},
    /*K_COLLECTING*/     {"collecting data","collecte...",     "sammle Daten",  "verzamelen...","zbieranie...",  "coletando...",  "recopilando...",  "đang thu..."},
    /*K_DAYS*/           {"days",           "jours",           "Tage",          "dagen",        "dni",           "dias",          "días",            "ngày"},
    /*K_HOURS*/          {"hours",          "heures",          "Std.",          "uren",         "godz.",         "horas",         "horas",           "giờ"},

    /*K_SETTINGS*/       {"SETTINGS",       "RÉGLAGES",        "EINSTELL.",     "INSTELL.",     "USTAWIENIA",    "AJUSTES",       "AJUSTES",         "CÀI ĐẶT"},
    /*K_AUTO_SWITCH*/    {"Auto-switch",    "Bascule auto",    "Auto-Wechsel",  "Auto-wissel",  "Auto-przeł.",   "Troca autom.",  "Cambio auto",     "Tự chuyển"},
    /*K_SWITCH_INTERVAL*/{"Switch interval","Intervalle",      "Wechselzeit",   "Wisselinterval","Interwał",     "Intervalo",     "Intervalo",       "Khoảng chuyển"},
    /*K_BRIGHTNESS*/     {"Brightness",     "Luminosité",      "Helligkeit",    "Helderheid",   "Jasność",       "Brilho",        "Brillo",          "Độ sáng"},
    /*K_AUTO_SLEEP*/     {"Auto-sleep",     "Veille auto",     "Auto-Schlaf",   "Auto-slaap",   "Auto-uśpienie", "Susp. auto",    "Suspens. auto",   "Tự ngủ"},
    /*K_ECO_MODE*/       {"Eco mode",       "Mode éco",        "Öko-Modus",     "Eco-modus",    "Tryb eco",      "Modo eco",      "Modo eco",        "Chế độ eco"},
    /*K_DIM_AFTER*/      {"Dim after",      "Atténuer après",  "Dimmen nach",   "Dimmen na",    "Przyciem. po",  "Escurecer após","Atenuar tras",    "Mờ sau"},
    /*K_TEMP_UNIT*/      {"Temp unit",      "Unité temp.",     "Temp.-Einh.",   "Temp.-eenheid","Jedn. temp.",   "Unid. temp.",   "Unidad temp.",    "Đơn vị nhiệt"},
    /*K_TIME_FORMAT*/    {"Time format",    "Format heure",    "Zeitformat",    "Tijdformaat",  "Format czasu",  "Formato hora",  "Formato hora",    "Định dạng giờ"},
    /*K_WIFI_AUTO*/      {"WiFi auto-connect","WiFi auto",     "WiFi Auto",     "WiFi auto",    "WiFi auto",     "WiFi auto",     "WiFi auto",       "WiFi tự nối"},
    /*K_DEMO_SPEED*/     {"Demo speed",     "Vitesse démo",    "Demo-Tempo",    "Demo-snelheid","Prędk. demo",   "Veloc. demo",   "Veloc. demo",     "Tốc độ demo"},
    /*K_SYSTEM_INFO*/    {"System info",    "Infos système",   "System-Info",   "Systeeminfo",  "Info systemu",  "Info sistema",  "Info sistema",    "Thông tin"},
    /*K_FIRMWARE*/       {"Firmware",       "Firmware",        "Firmware",      "Firmware",     "Firmware",      "Firmware",      "Firmware",        "Firmware"},
    /*K_DEMO_MODE*/      {"Demo mode",      "Mode démo",       "Demo-Modus",    "Demo-modus",   "Tryb demo",     "Modo demo",     "Modo demo",       "Chế độ demo"},
    /*K_SCREENSAVER*/    {"Screensaver",    "Écran de veille", "Bildschirmsch.","Schermbev.",   "Wygaszacz",     "Prot. de tela", "Salvapantallas",  "Bảo vệ m.hình"},
    /*K_SCREENSAVER_AFTER*/{"Screensaver after","Veille après","Schoner nach",  "Schermbev. na","Wygaszacz po",  "Tela após",     "Salvap. tras",    "Bảo vệ sau"},
    /*K_WEB_ADDRESS*/    {"Web address",    "Adresse web",     "Web-Adresse",   "Webadres",     "Adres web",     "Endereço web",  "Dirección web",   "Địa chỉ web"},
    /*K_WEB_USERNAME*/   {"Web username",   "Utilisateur web", "Web-Benutzer",  "Webgebruiker", "Użytkownik",    "Usuário web",   "Usuario web",     "Tên đăng nhập"},
    /*K_WEB_PASSWORD*/   {"Web password",   "Mot de passe web","Web-Passwort",  "Webwachtwoord","Hasło web",     "Senha web",     "Contraseña web",  "Mật khẩu web"},
    /*K_LANGUAGE*/       {"Language",       "Langue",          "Sprache",       "Taal",         "Język",         "Idioma",        "Idioma",          "Ngôn ngữ"},

    /*K_ON*/             {"ON",             "OUI",             "EIN",           "AAN",          "WŁ.",           "LIG",           "SÍ",              "BẬT"},
    /*K_OFF*/            {"OFF",            "NON",             "AUS",           "UIT",          "WYŁ.",          "DESL",          "NO",              "TẮT"},
    /*K_NEVER*/          {"Never",          "Jamais",          "Nie",           "Nooit",        "Nigdy",         "Nunca",         "Nunca",           "Không"},
    /*K_CELSIUS*/        {"Celsius",        "Celsius",         "Celsius",       "Celsius",      "Celsjusz",      "Celsius",       "Celsius",         "Celsius"},
    /*K_FAHRENHEIT*/     {"Fahr.",          "Fahr.",           "Fahr.",         "Fahr.",        "Fahr.",         "Fahr.",         "Fahr.",           "Fahr."},
    /*K_12_HOUR*/        {"12-hour",        "12 h",            "12-Std.",       "12-uur",       "12-godz.",      "12 h",          "12 h",            "12 giờ"},
    /*K_24_HOUR*/        {"24-hour",        "24 h",            "24-Std.",       "24-uur",       "24-godz.",      "24 h",          "24 h",            "24 giờ"},
    /*K_VIEW*/           {"view",           "voir",            "ansehen",       "tonen",        "pokaż",         "ver",           "ver",             "xem"},

    /*K_TAB_WIFI*/       {"WiFi",           "WiFi",            "WiFi",          "WiFi",         "WiFi",          "WiFi",          "WiFi",            "WiFi"},
    /*K_TAB_SYSTEM*/     {"System",         "Système",         "System",        "Systeem",      "System",        "Sistema",       "Sistema",         "Hệ thống"},
};

static inline const char *T(int k) { return STR[k][g_lang]; }
