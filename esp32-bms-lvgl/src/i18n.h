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

// First 8 (LANG_EN..LANG_VI) share the Montserrat extended-Latin+Cyrillic font and live in the
// STR[][LANG_LATIN8] table. Languages added after share that font too (Russian) or bring their
// own (Chinese, via curFont) and live in flat STR_<lang>[] arrays — so adding a language doesn't
// require editing all 161 rows of STR.
enum { LANG_EN, LANG_FR, LANG_DE, LANG_NL, LANG_PL, LANG_PT, LANG_ES, LANG_VI, LANG_RU, LANG_ZH, LANG_AR, LANG_HI, LANG_COUNT };
#define LANG_LATIN8 (LANG_VI + 1)   // languages held in the STR[][] table
static uint8_t g_lang = 0;   // index into the columns below; persisted in NVS ("lang")

// Native names for the picker (never translated).
static const char *const LANG_NAME[LANG_COUNT] = {
    "English", "Français", "Deutsch", "Nederlands", "Polski", "Português", "Español", "Tiếng Việt",
    "Русский", "中文", "العربية", "हिन्दी"};

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
    // ---- BMS config rows ----
    K_BATTERIES, K_CONFIGURE, K_UART_TX, K_UART_RX, K_PARAMETERS, K_OFFLINE_LC, K_DEMO_LC,
    K_READING, K_CHARGE_MOSFET, K_DISCHARGE_MOSFET, K_BALANCER,
    // ---- WiFi screen ----
    K_SCAN, K_RESCAN, K_WIFI_TAP_SCAN, K_WIFI_SCANNING, K_WIFI_NETS, K_WIFI_NO_NETS,
    K_WIFI_SCAN_FAIL, K_WIFI_CONNECTING, K_WIFI_CONNECTED, K_WIFI_CONN_FAIL, K_WIFI_NOT_FOUND,
    K_WIFI_CONN_LOST, K_NOT_CONNECTED,
    // ---- keyboard ----
    K_ENTER_PASSWORD, K_ENTER_USERNAME, K_ENTER_NEW_PASSWORD, K_HDR_WEB_USER, K_HDR_WEB_PASS,
    K_KB_SPACE, K_CANCEL, K_SAVE,
    // ---- info popup ----
    K_HDR_SYSINFO, K_BOARD, K_FLASH, K_PSRAM_FREE, K_HEAP_FREE, K_WEB_LOGIN, K_UPTIME_INFO,
    K_TAP_CLOSE, K_BMS_SOON,
    // ---- BMS protection-parameter labels (battery abbreviations OVP/UVP/OCP/OTP/UTP kept) ----
    K_S_NOMINAL_CAP, K_S_CELL_COUNT, K_S_MAX_CHG_A, K_S_MAX_DIS_A, K_S_CELL_OVP, K_S_CELL_OVP_REC,
    K_S_CELL_UVP, K_S_CELL_UVP_REC, K_S_SOC100_V, K_S_SOC0_V, K_S_BAL_START_V, K_S_BAL_TRIG_DV,
    K_S_MAX_BAL_A, K_S_REQ_CHG_V, K_S_REQ_FLOAT_V, K_S_POWER_OFF_V, K_S_CHG_OCP_DELAY,
    K_S_CHG_OCP_REC, K_S_DIS_OCP_DELAY, K_S_DIS_OCP_REC, K_S_SCP_DELAY, K_S_SCP_REC,
    K_S_CHG_OTP, K_S_CHG_OTP_REC, K_S_DIS_OTP, K_S_DIS_OTP_REC, K_S_CHG_UTP, K_S_CHG_UTP_REC,
    K_S_MOS_OTP, K_S_MOS_OTP_REC, K_S_SMART_SLEEP_V, K_S_HEAT_START_T, K_S_SMART_SLEEP_H,
    // ---- BMS bit-flag labels ----
    K_B_HEATING, K_B_DIS_TEMP_SENS, K_B_DISP_ALWAYS, K_B_SMART_SLEEP, K_B_DISABLE_PCL,
    K_B_TIMED_DATA, K_B_CHG_FLOAT, K_B_EMERGENCY, K_B_DRY_CONTACT, K_B_DIS_OCP2,
    // ---- alarm / error names ----
    K_E_WIRE_RES, K_E_MOS_OT, K_E_CELL_MISMATCH, K_E_FULLY_CHARGED, K_E_PACK_OV, K_E_CHG_OC,
    K_E_CHG_SC, K_E_CHG_OT, K_E_CHG_UT, K_E_COPROC, K_E_CELL_UV, K_E_PACK_UV, K_E_DIS_OC,
    K_E_DIS_SC, K_E_DIS_OT, K_E_CHG_MOS_FAULT, K_E_DIS_MOS_FAULT, K_E_GPS_DISC, K_E_CHG_PWD,
    K_E_DIS_ON_FAIL, K_E_BAT_OT, K_E_TEMP_ANOM, K_E_PL_ANOM, K_E_SCP_REL_FAIL, K_E_DIS_OCP2,
    K_E_DIS_OCP3, K_E_DIS_UT, K_E_GPS_LOCK,
    // ---- battery tab label (formatted "BAT %d") ----
    K_BAT,
    // ---- temperature tile labels (MOSFET temp + two probes) ----
    K_MOS, K_T1, K_T2,
    // ---- PIN lock ----
    K_AUTO_LOCK, K_LOCK_PIN, K_ENTER_PIN, K_SET_PIN, K_WRONG_PIN, K_PIN_SET, K_PIN_NONE,
    // ---- MOSFET status (voltage tile) — kept short to fit the narrow tile ----
    K_M_CHG, K_M_DIS, K_M_BAL,
    // ---- weather forecast popup (day header + condition descriptions) ----
    K_TODAY, K_WX_CLEAR, K_WX_PARTLY, K_WX_CLOUDY, K_WX_RAIN, K_WX_SNOW, K_WX_STORM,
    // ---- appended keys (keep at the end: STR_RU/STR_ZH are positional flat arrays) ----
    K_TIMEZONE, K_SCREENSAVER_FOR, K_UNTIL_TAP,
    K_COUNT
};

static const char *const STR[K_COUNT][LANG_LATIN8] = {
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

    // ---- BMS config rows ----
    /*K_BATTERIES*/      {"Batteries",      "Batteries",       "Batterien",     "Accu's",       "Baterie",       "Baterias",      "Baterías",        "Số pin"},
    /*K_CONFIGURE*/      {"Configure",      "Configurer",      "Konfig.",       "Configureren", "Konfiguruj",    "Configurar",    "Configurar",      "Cấu hình"},
    /*K_UART_TX*/        {"UART TX pin",    "UART TX",         "UART TX",       "UART TX",      "UART TX",       "UART TX",       "UART TX",         "UART TX"},
    /*K_UART_RX*/        {"UART RX pin",    "UART RX",         "UART RX",       "UART RX",      "UART RX",       "UART RX",       "UART RX",         "UART RX"},
    /*K_PARAMETERS*/     {"Parameters",     "Paramètres",      "Parameter",     "Parameters",   "Parametry",     "Parâmetros",    "Parámetros",      "Tham số"},
    /*K_OFFLINE_LC*/     {"offline",        "hors ligne",      "offline",       "offline",      "offline",       "offline",       "sin conexión",    "ngoại tuyến"},
    /*K_DEMO_LC*/        {"demo mode",      "mode démo",       "Demo-Modus",    "demo-modus",   "tryb demo",     "modo demo",     "modo demo",       "chế độ demo"},
    /*K_READING*/        {"reading...",     "lecture...",      "lese...",       "lezen...",     "odczyt...",     "lendo...",      "leyendo...",      "đang đọc..."},
    /*K_CHARGE_MOSFET*/  {"Charge MOSFET",  "MOSFET charge",   "Lade-MOSFET",   "Laad-MOSFET",  "MOSFET ład.",   "MOSFET carga",  "MOSFET carga",    "MOSFET sạc"},
    /*K_DISCHARGE_MOSFET*/{"Discharge MOSFET","MOSFET décharge","Entlade-MOSFET","Ontl.-MOSFET","MOSFET rozł.",  "MOSFET desc.",  "MOSFET desc.",    "MOSFET xả"},
    /*K_BALANCER*/       {"Balancer",       "Équilibreur",     "Balancer",      "Balancer",     "Balanser",      "Equalizador",   "Balanceador",     "Bộ cân bằng"},

    // ---- WiFi screen ----
    /*K_SCAN*/           {"Scan",           "Scanner",         "Scannen",       "Scannen",      "Skanuj",        "Buscar",        "Buscar",          "Quét"},
    /*K_RESCAN*/         {"Rescan",         "Rescanner",       "Neu scannen",   "Opnieuw",      "Skanuj zn.",    "Rebuscar",      "Rebuscar",        "Quét lại"},
    /*K_WIFI_TAP_SCAN*/  {"tap Scan to find networks","Scanner pour chercher","Scannen zum Suchen","tik Scannen","dotknij Skanuj","toque Buscar","toca Buscar","chạm Quét để tìm"},
    /*K_WIFI_SCANNING*/  {"scanning...",    "analyse...",      "scanne...",     "scannen...",   "skanowanie...", "buscando...",   "buscando...",     "đang quét..."},
    /*K_WIFI_NETS*/      {"networks found", "réseaux trouvés", "Netze gefunden","netwerken",    "sieci",         "redes",         "redes",           "mạng tìm thấy"},
    /*K_WIFI_NO_NETS*/   {"no networks found","aucun réseau",  "keine Netze",   "geen netwerken","brak sieci",   "sem redes",     "sin redes",       "không có mạng"},
    /*K_WIFI_SCAN_FAIL*/ {"scan failed",    "échec scan",      "Scan-Fehler",   "scan mislukt", "błąd skan.",    "falha busca",   "fallo búsqueda",  "quét lỗi"},
    /*K_WIFI_CONNECTING*/{"connecting to",  "connexion à",     "verbinde mit",  "verbinden met","łączenie z",    "conectando a",  "conectando a",    "đang nối tới"},
    /*K_WIFI_CONNECTED*/ {"Connected:",     "Connecté :",      "Verbunden:",    "Verbonden:",   "Połączono:",    "Conectado:",    "Conectado:",      "Đã nối:"},
    /*K_WIFI_CONN_FAIL*/ {"connect failed (password?)","échec (mot de passe ?)","Verbindung fehlgeschl.","verbinden mislukt","błąd (hasło?)","falha (senha?)","fallo (¿clave?)","nối lỗi (mật khẩu?)"},
    /*K_WIFI_NOT_FOUND*/ {"network not found","réseau introuvable","Netz nicht gefunden","netwerk niet gevonden","nie znaleziono","rede não encontrada","red no hallada","không thấy mạng"},
    /*K_WIFI_CONN_LOST*/ {"connection lost","connexion perdue","Verbindung verloren","verbinding weg","utracono poł.","conexão perdida","conexión perdida","mất kết nối"},
    /*K_NOT_CONNECTED*/  {"not connected",  "non connecté",    "nicht verbunden","niet verbonden","nie połączono","não conectado","no conectado",   "chưa nối"},

    // ---- keyboard ----
    /*K_ENTER_PASSWORD*/ {"enter password", "saisir mot de passe","Passwort eingeben","wachtwoord","wpisz hasło",  "digite a senha","escribe la clave","nhập mật khẩu"},
    /*K_ENTER_USERNAME*/ {"enter username", "saisir utilisateur","Benutzer eingeben","gebruiker",  "wpisz użytk.",  "digite usuário","escribe usuario","nhập tên"},
    /*K_ENTER_NEW_PASSWORD*/{"enter new password","nouveau mot de passe","neues Passwort","nieuw wachtwoord","nowe hasło","nova senha","nueva clave","mật khẩu mới"},
    /*K_HDR_WEB_USER*/   {"Web interface username","Utilisateur interface web","Web-Benutzername","Webgebruikersnaam","Nazwa użytkownika web","Usuário da interface web","Usuario interfaz web","Tên đăng nhập web"},
    /*K_HDR_WEB_PASS*/   {"Web interface password","Mot de passe interface web","Web-Passwort","Webwachtwoord","Hasło interfejsu web","Senha da interface web","Clave interfaz web","Mật khẩu web"},
    /*K_KB_SPACE*/       {"space",          "espace",          "Leer",          "spatie",       "spacja",        "espaço",        "espacio",         "cách"},
    /*K_CANCEL*/         {"Cancel",         "Annuler",         "Abbr.",         "Annul.",       "Anuluj",        "Cancelar",      "Cancelar",        "Hủy"},
    /*K_SAVE*/           {"Save",           "Enreg.",          "Speich.",       "Opslaan",      "Zapisz",        "Salvar",        "Guardar",         "Lưu"},

    // ---- info popup ----
    /*K_HDR_SYSINFO*/    {"SYSTEM INFO",    "INFOS SYSTÈME",   "SYSTEM-INFO",   "SYSTEEMINFO",  "INFO SYSTEMU",  "INFO SISTEMA",  "INFO SISTEMA",    "THÔNG TIN HỆ THỐNG"},
    /*K_BOARD*/          {"Board",          "Carte",           "Platine",       "Bord",         "Płytka",        "Placa",         "Placa",           "Bo mạch"},
    /*K_FLASH*/          {"Flash",          "Flash",           "Flash",         "Flash",        "Flash",         "Flash",         "Flash",           "Flash"},
    /*K_PSRAM_FREE*/     {"PSRAM free",     "PSRAM libre",     "PSRAM frei",    "PSRAM vrij",   "PSRAM wolne",   "PSRAM livre",   "PSRAM libre",     "PSRAM trống"},
    /*K_HEAP_FREE*/      {"Heap free",      "Tas libre",       "Heap frei",     "Heap vrij",    "Sterta wolna",  "Heap livre",    "Heap libre",      "Heap trống"},
    /*K_WEB_LOGIN*/      {"Web login",      "Login web",       "Web-Login",     "Weblogin",     "Login web",     "Login web",     "Acceso web",      "Đăng nhập web"},
    /*K_UPTIME_INFO*/    {"Uptime",         "Durée",           "Laufzeit",      "Actief",       "Czas pracy",    "Ativo",         "Activo",          "Thời gian chạy"},
    /*K_TAP_CLOSE*/      {"tap to close",   "toucher fermer",  "tippen schließt","tik sluiten", "dotknij zamknij","toque fechar", "toca cerrar",     "chạm để đóng"},
    /*K_BMS_SOON*/       {"BMS info: coming soon","BMS : bientôt","BMS-Info: bald","BMS: binnenkort","BMS: wkrótce","BMS: em breve","BMS: pronto",   "BMS: sắp có"},

    // ---- BMS protection-parameter labels (OVP/UVP/OCP/OTP/UTP/SOC/MOS/SCP kept) ----
    /*K_S_NOMINAL_CAP*/  {"Nominal cap",    "Cap. nominale",   "Nennkapaz.",    "Nom. cap.",    "Poj. znam.",    "Cap. nominal",  "Cap. nominal",    "Dung lượng dm"},
    /*K_S_CELL_COUNT*/   {"Cell count",     "Nb cellules",     "Zellenzahl",    "Aantal cellen","Liczba ogniw",  "Nº células",    "Nº celdas",       "Số ô pin"},
    /*K_S_MAX_CHG_A*/    {"Max charge A",   "Charge max A",    "Max Lad. A",    "Max laad A",   "Maks ład A",    "Carga máx A",   "Carga máx A",     "Sạc tối đa A"},
    /*K_S_MAX_DIS_A*/    {"Max discharge A","Décharge max A",  "Max Entl. A",   "Max ontl A",   "Maks rozł A",   "Desc. máx A",   "Desc. máx A",     "Xả tối đa A"},
    /*K_S_CELL_OVP*/     {"Cell OVP",       "Cellule OVP",     "Zelle OVP",     "Cel OVP",      "Ogniwo OVP",    "Célula OVP",    "Celda OVP",       "Ô OVP"},
    /*K_S_CELL_OVP_REC*/ {"Cell OVP recover","OVP récup.",     "OVP-Reset",     "OVP herstel",  "OVP powrót",    "OVP recup.",    "OVP recup.",      "OVP phục hồi"},
    /*K_S_CELL_UVP*/     {"Cell UVP",       "Cellule UVP",     "Zelle UVP",     "Cel UVP",      "Ogniwo UVP",    "Célula UVP",    "Celda UVP",       "Ô UVP"},
    /*K_S_CELL_UVP_REC*/ {"Cell UVP recover","UVP récup.",     "UVP-Reset",     "UVP herstel",  "UVP powrót",    "UVP recup.",    "UVP recup.",      "UVP phục hồi"},
    /*K_S_SOC100_V*/     {"SOC 100% volt",  "SOC 100% V",      "SOC 100% V",    "SOC 100% V",   "SOC 100% V",    "SOC 100% V",    "SOC 100% V",      "SOC 100% V"},
    /*K_S_SOC0_V*/       {"SOC 0% volt",    "SOC 0% V",        "SOC 0% V",      "SOC 0% V",     "SOC 0% V",      "SOC 0% V",      "SOC 0% V",        "SOC 0% V"},
    /*K_S_BAL_START_V*/  {"Balance start V","Début équil. V",  "Bal.-Start V",  "Bal. start V", "Start bal. V",  "Início bal. V", "Inicio bal. V",   "Bắt đầu CB V"},
    /*K_S_BAL_TRIG_DV*/  {"Balance trig dV","Seuil équil. dV", "Bal.-Diff dV",  "Bal. drmpl dV","Próg bal. dV",  "Limiar bal. dV","Umbral bal. dV",  "Ngưỡng CB dV"},
    /*K_S_MAX_BAL_A*/    {"Max balance A",  "Équil. max A",    "Max Bal. A",    "Max bal. A",   "Maks bal. A",   "Bal. máx A",    "Bal. máx A",      "CB tối đa A"},
    /*K_S_REQ_CHG_V*/    {"Req charge volt","Tens. charge",    "Soll-Ladesp.",  "Gevr. laad V", "Żąd. nap. ład", "Tensão carga",  "Tensión carga",   "Đ.áp sạc"},
    /*K_S_REQ_FLOAT_V*/  {"Req float volt", "Tens. float",     "Soll-Float V",  "Gevr. float V","Żąd. podtrzym", "Tensão flut.",  "Tensión flot.",   "Đ.áp duy trì"},
    /*K_S_POWER_OFF_V*/  {"Power off volt", "Tens. coupure",   "Abschalt-Sp.",  "Uitschakel V", "Nap. wył.",     "Tensão deslig.","Tensión apag.",   "Đ.áp tắt"},
    /*K_S_CHG_OCP_DELAY*/{"Charge OCP delay","OCP charge délai","Lade-OCP Verz.","Laad-OCP vert","OCP ład zwłoka","OCP carga atr.","OCP carga ret.",  "Trễ OCP sạc"},
    /*K_S_CHG_OCP_REC*/  {"Charge OCP recov","OCP charge réc.","Lade-OCP Reset","Laad-OCP hers","OCP ład powr.", "OCP carga rec.","OCP carga rec.",  "OCP sạc ph.hồi"},
    /*K_S_DIS_OCP_DELAY*/{"Dischg OCP delay","OCP déch. délai","Entl-OCP Verz.","Ontl-OCP vert","OCP rozł zwł.", "OCP desc atr.", "OCP desc ret.",   "Trễ OCP xả"},
    /*K_S_DIS_OCP_REC*/  {"Dischg OCP recov","OCP déch. réc.","Entl-OCP Reset","Ontl-OCP hers","OCP rozł powr.","OCP desc rec.", "OCP desc rec.",   "OCP xả ph.hồi"},
    /*K_S_SCP_DELAY*/    {"Short-circ delay","SCP délai",      "SCP Verz.",     "SCP vertr.",   "SCP zwłoka",    "SCP atraso",    "SCP retardo",     "Trễ SCP"},
    /*K_S_SCP_REC*/      {"Short-circ recov","SCP récup.",     "SCP Reset",     "SCP herstel",  "SCP powrót",    "SCP recup.",    "SCP recup.",      "SCP ph.hồi"},
    /*K_S_CHG_OTP*/      {"Charge OTP",     "OTP charge",      "Lade-OTP",      "Laad-OTP",     "OTP ład.",      "OTP carga",     "OTP carga",       "OTP sạc"},
    /*K_S_CHG_OTP_REC*/  {"Charge OTP recov","OTP charge réc.","Lade-OTP Reset","Laad-OTP hers","OTP ład powr.", "OTP carga rec.","OTP carga rec.",  "OTP sạc ph.hồi"},
    /*K_S_DIS_OTP*/      {"Dischg OTP",     "OTP décharge",    "Entl-OTP",      "Ontl-OTP",     "OTP rozł.",     "OTP desc.",     "OTP desc.",       "OTP xả"},
    /*K_S_DIS_OTP_REC*/  {"Dischg OTP recov","OTP déch. réc.","Entl-OTP Reset","Ontl-OTP hers","OTP rozł powr.","OTP desc rec.", "OTP desc rec.",   "OTP xả ph.hồi"},
    /*K_S_CHG_UTP*/      {"Charge UTP",     "UTP charge",      "Lade-UTP",      "Laad-UTP",     "UTP ład.",      "UTP carga",     "UTP carga",       "UTP sạc"},
    /*K_S_CHG_UTP_REC*/  {"Charge UTP recov","UTP charge réc.","Lade-UTP Reset","Laad-UTP hers","UTP ład powr.", "UTP carga rec.","UTP carga rec.",  "UTP sạc ph.hồi"},
    /*K_S_MOS_OTP*/      {"MOS OTP",        "MOS OTP",         "MOS OTP",       "MOS OTP",      "MOS OTP",       "MOS OTP",       "MOS OTP",         "MOS OTP"},
    /*K_S_MOS_OTP_REC*/  {"MOS OTP recover","MOS OTP récup.",  "MOS OTP Reset", "MOS OTP herst","MOS OTP powr.", "MOS OTP recup.","MOS OTP recup.",  "MOS OTP ph.hồi"},
    /*K_S_SMART_SLEEP_V*/{"Smart sleep V",  "Veille auto V",   "Smart-Schlaf V","Slim slapen V","Sen V",         "Sono auto V",   "Reposo V",        "Ngủ t.minh V"},
    /*K_S_HEAT_START_T*/ {"Heating start T","Chauffe début T", "Heizstart T",   "Verwarm start","Grzanie start T","Aquec. início T","Calor inicio T", "Sưởi bắt đầu T"},
    /*K_S_SMART_SLEEP_H*/{"Smart sleep hrs","Veille auto h",   "Smart-Schlaf h","Slim slapen u","Sen godz.",     "Sono auto h",   "Reposo h",        "Ngủ t.minh giờ"},

    // ---- BMS bit-flag labels ----
    /*K_B_HEATING*/      {"Heating",        "Chauffage",       "Heizung",       "Verwarming",   "Grzanie",       "Aquecimento",   "Calefacción",     "Sưởi"},
    /*K_B_DIS_TEMP_SENS*/{"Disable temp sens","Désact. capteur T","Temp-Sensor aus","Temp-sensor uit","Wyłącz czuj T","Desat. sensor T","Desact. sensor T","Tắt cảm biến T"},
    /*K_B_DISP_ALWAYS*/  {"Display always on","Écran toujours on","Display immer an","Scherm altijd aan","Ekran zawsze wł","Tela sempre on","Pantalla siempre","Màn hình luôn bật"},
    /*K_B_SMART_SLEEP*/  {"Smart sleep",    "Veille auto",     "Smart-Schlaf",  "Slim slapen",  "Sen inteligentny","Sono autom.", "Reposo intel.",   "Ngủ thông minh"},
    /*K_B_DISABLE_PCL*/  {"Disable PCL",    "Désact. PCL",     "PCL aus",       "PCL uit",      "Wyłącz PCL",    "Desat. PCL",    "Desact. PCL",     "Tắt PCL"},
    /*K_B_TIMED_DATA*/   {"Timed stored data","Données horodatées","Daten zeitges.","Tijddata",  "Dane czasowe",  "Dados cronom.", "Datos cronom.",   "Dữ liệu hẹn giờ"},
    /*K_B_CHG_FLOAT*/    {"Charging float", "Charge float",    "Float-Ladung",  "Float laden",  "Ład. podtrzym", "Carga flut.",   "Carga flot.",     "Sạc duy trì"},
    /*K_B_EMERGENCY*/    {"Emergency button","Bouton urgence",  "Notschalter",   "Noodknop",     "Przycisk awar.","Botão emerg.",  "Botón emerg.",    "Nút khẩn cấp"},
    /*K_B_DRY_CONTACT*/  {"Dry-contact intmt","Contact sec interm.","Trockenkontakt","Potentiaalvrij","Styk bezpot.","Contato seco","Contacto seco",  "Tiếp điểm khô"},
    /*K_B_DIS_OCP2*/     {"Discharge OCP2", "OCP2 décharge",   "Entlade-OCP2",  "Ontlaad-OCP2", "OCP2 rozł.",    "OCP2 desc.",    "OCP2 desc.",      "OCP2 xả"},

    // ---- alarm / error names ----
    /*K_E_WIRE_RES*/     {"Wire resistance","Résistance fil",  "Leitungswid.",  "Draadweerst.", "Rezyst. przew.","Resist. fio",   "Resist. cable",   "Điện trở dây"},
    /*K_E_MOS_OT*/       {"MOSFET over-temp","MOSFET surchauf.","MOSFET Übertemp","MOSFET overtemp","MOSFET przegrz","MOSFET sobreaq.","MOSFET sobretemp","MOSFET quá nhiệt"},
    /*K_E_CELL_MISMATCH*/{"Cell count mismatch","Nb cellules incoh.","Zellenzahl-Fehler","Celaantal fout","Błąd liczby ogniw","Nº células errado","Nº celdas erróneo","Sai số ô pin"},
    /*K_E_FULLY_CHARGED*/{"Fully charged",  "Pleine charge",   "Voll geladen",  "Volledig vol", "Naładowany",    "Carga total",   "Carga completa",  "Đã sạc đầy"},
    /*K_E_PACK_OV*/      {"Pack over-voltage","Surtension pack", "Pack Überspann.","Pack overspann.","Przepięcie","Sobretensão",   "Sobretensión",    "Quá áp gói"},
    /*K_E_CHG_OC*/       {"Charge over-current","Surcourant charge","Lade-Überstrom","Laad-overstroom","Przetęż. ład.","Sobrecorr. carga","Sobrecorr. carga","Quá dòng sạc"},
    /*K_E_CHG_SC*/       {"Charge short-circuit","Court-circ. charge","Lade-Kurzschl.","Laad-kortsluit","Zwarcie ład.","Curto carga",  "Cortocirc. carga","Ngắn mạch sạc"},
    /*K_E_CHG_OT*/       {"Charge over-temp","Surchauffe charge","Lade-Übertemp.","Laad-overtemp", "Przegrz. ład.", "Sobreaq. carga","Sobretemp carga", "Quá nhiệt sạc"},
    /*K_E_CHG_UT*/       {"Charge under-temp","Sous-temp. charge","Lade-Untertemp.","Laad-ondertemp","NiedoT ład.","Subtemp carga", "Subtemp carga",   "Thiếu nhiệt sạc"},
    /*K_E_COPROC*/       {"Coprocessor comm err","Err. coprocesseur","Koproz.-Fehler","Coproc.-fout","Błąd koproc.","Erro coproc.",  "Error coproc.",   "Lỗi đồng x.lý"},
    /*K_E_CELL_UV*/      {"Cell under-voltage","Sous-tension cellule","Zelle Unterspann.","Cel onderspann.","Podnap. ogniwa","Subtensão célula","Subtensión celda","Thiếu áp ô"},
    /*K_E_PACK_UV*/      {"Pack under-voltage","Sous-tension pack","Pack Unterspann.","Pack onderspann.","Podnap. pakietu","Subtensão pack","Subtensión pack","Thiếu áp gói"},
    /*K_E_DIS_OC*/       {"Discharge over-current","Surcourant décharge","Entl.-Überstrom","Ontl-overstroom","Przetęż. rozł.","Sobrecorr. desc.","Sobrecorr. desc.","Quá dòng xả"},
    /*K_E_DIS_SC*/       {"Discharge short-circuit","Court-circ. décharge","Entl.-Kurzschl.","Ontl-kortsluit","Zwarcie rozł.","Curto desc.","Cortocirc. desc.","Ngắn mạch xả"},
    /*K_E_DIS_OT*/       {"Discharge over-temp","Surchauffe décharge","Entl.-Übertemp.","Ontl-overtemp","Przegrz. rozł.","Sobreaq. desc.","Sobretemp desc.","Quá nhiệt xả"},
    /*K_E_CHG_MOS_FAULT*/{"Charge MOSFET fault","Défaut MOSFET charge","Lade-MOSFET Fehler","Laad-MOSFET fout","Awaria MOSFET ład","Falha MOSFET carga","Fallo MOSFET carga","Lỗi MOSFET sạc"},
    /*K_E_DIS_MOS_FAULT*/{"Discharge MOSFET fault","Défaut MOSFET déch.","Entl-MOSFET Fehler","Ontl-MOSFET fout","Awaria MOSFET rozł","Falha MOSFET desc","Fallo MOSFET desc","Lỗi MOSFET xả"},
    /*K_E_GPS_DISC*/     {"GPS disconnected","GPS déconnecté",  "GPS getrennt",  "GPS losgekop.", "GPS odłączony", "GPS desconect.","GPS desconect.",  "Mất GPS"},
    /*K_E_CHG_PWD*/      {"Change password","Changer mot de passe","Passwort ändern","Wachtwoord wijz","Zmień hasło","Mudar senha","Cambiar clave",   "Đổi mật khẩu"},
    /*K_E_DIS_ON_FAIL*/  {"Discharge-on failed","Activ. décharge échec","Entl.-Ein Fehler","Ontl-aan mislukt","Wł. rozł. błąd","Falha lig. desc.","Fallo act. desc.","Bật xả lỗi"},
    /*K_E_BAT_OT*/       {"Battery over-temp","Batterie surchauf.","Akku Übertemp.","Accu overtemp", "Przegrz. baterii","Bateria sobreaq.","Batería sobretemp","Pin quá nhiệt"},
    /*K_E_TEMP_ANOM*/    {"Temp sensor anomaly","Anomalie capteur T","Temp-Sensor Anom.","Temp-sensor anom.","Anomalia czuj T","Anom. sensor T","Anom. sensor T","Bất thường c.biến T"},
    /*K_E_PL_ANOM*/      {"PL module anomaly","Anomalie module PL","PL-Modul Anom.","PL-module anom.","Anomalia PL",  "Anom. módulo PL","Anom. módulo PL","Bất thường PL"},
    /*K_E_SCP_REL_FAIL*/ {"SCP release failed","Reset SCP échec","SCP-Reset Fehler","SCP vrijg. mislukt","SCP zwoln. błąd","Falha lib. SCP","Fallo lib. SCP","SCP nhả lỗi"},
    /*K_E_DIS_OCP2*/     {"Discharge OCP2",  "OCP2 décharge",   "Entlade-OCP2",  "Ontlaad-OCP2", "OCP2 rozł.",    "OCP2 desc.",    "OCP2 desc.",      "OCP2 xả"},
    /*K_E_DIS_OCP3*/     {"Discharge OCP3",  "OCP3 décharge",   "Entlade-OCP3",  "Ontlaad-OCP3", "OCP3 rozł.",    "OCP3 desc.",    "OCP3 desc.",      "OCP3 xả"},
    /*K_E_DIS_UT*/       {"Discharge under-temp","Sous-temp. décharge","Entl.-Untertemp.","Ontl-ondertemp","NiedoT rozł.","Subtemp desc.","Subtemp desc.","Thiếu nhiệt xả"},
    /*K_E_GPS_LOCK*/     {"GPS remote lock", "Verrou GPS dist.", "GPS-Fernsperre","GPS afst.-slot","Blok. GPS zdal.","Bloq. GPS rem.","Bloqueo GPS rem.","Khóa GPS từ xa"},
    /*K_BAT*/            {"BAT",            "BAT",             "AKKU",          "ACCU",         "AKU",           "BAT",           "BAT",             "PIN"},
    /*K_MOS*/            {"MOS",            "MOS",             "MOS",           "MOS",          "MOS",           "MOS",           "MOS",             "MOS"},
    /*K_T1*/             {"T1",             "T1",              "T1",            "T1",           "T1",            "T1",            "T1",              "T1"},
    /*K_T2*/             {"T2",             "T2",              "T2",            "T2",           "T2",            "T2",            "T2",              "T2"},
    /*K_AUTO_LOCK*/      {"Auto-lock",      "Verrou auto",     "Auto-Sperre",   "Auto-vergr.",  "Auto-blokada",  "Bloq. autom.",  "Bloqueo auto",    "Tự khóa"},
    /*K_LOCK_PIN*/       {"Lock PIN",       "Code PIN",        "Sperr-PIN",     "Vergr.-pincode","PIN blokady",  "PIN bloqueio",  "PIN bloqueo",     "Mã PIN khóa"},
    /*K_ENTER_PIN*/      {"Enter PIN",      "Saisir le PIN",   "PIN eingeben",  "Pincode invoeren","Wpisz PIN",  "Digite o PIN",  "Introduce PIN",   "Nhập mã PIN"},
    /*K_SET_PIN*/        {"Set a 6-digit PIN","Définir un PIN à 6 chiffres","6-stellige PIN festlegen","Stel 6-cijferige pincode in","Ustaw 6-cyfrowy PIN","Defina um PIN de 6 dígitos","Define un PIN de 6 dígitos","Đặt mã PIN 6 số"},
    /*K_WRONG_PIN*/      {"Wrong PIN",      "PIN incorrect",   "Falsche PIN",   "Onjuiste pincode","Błędny PIN", "PIN errado",    "PIN incorrecto",  "Sai mã PIN"},
    /*K_PIN_SET*/        {"set",            "défini",          "gesetzt",       "ingesteld",    "ustawiony",     "definido",      "definido",        "đã đặt"},
    /*K_PIN_NONE*/       {"none",           "aucun",           "keine",         "geen",         "brak",          "nenhum",        "ninguno",         "chưa đặt"},
    /*K_M_CHG*/          {"Charge",         "Charge",          "Laden",         "Laden",        "Ład.",          "Carga",         "Carga",           "Sạc"},
    /*K_M_DIS*/          {"Discharge",      "Décharge",        "Entladen",      "Ontladen",     "Rozład.",       "Descarga",      "Descarga",        "Xả"},
    /*K_M_BAL*/          {"Balance",        "Équil.",          "Balance",       "Balans",       "Balans",        "Equilíb.",      "Balance",         "Cân bằng"},
    /*K_TODAY*/          {"Today",          "Aujourd'hui",     "Heute",         "Vandaag",      "Dziś",          "Hoje",          "Hoy",             "Hôm nay"},
    /*K_WX_CLEAR*/       {"Clear",          "Clair",           "Klar",          "Helder",       "Bezchm.",       "Limpo",         "Despejado",       "Quang"},
    /*K_WX_PARTLY*/      {"Partly",         "Éclaircies",      "Heiter",        "Half bewolkt", "Częśc.",        "Parcial",       "Parcial",         "Ít mây"},
    /*K_WX_CLOUDY*/      {"Cloudy",         "Nuageux",         "Bewölkt",       "Bewolkt",      "Pochm.",        "Nublado",       "Nublado",         "Nhiều mây"},
    /*K_WX_RAIN*/        {"Rain",           "Pluie",           "Regen",         "Regen",        "Deszcz",        "Chuva",         "Lluvia",          "Mưa"},
    /*K_WX_SNOW*/        {"Snow",           "Neige",           "Schnee",        "Sneeuw",       "Śnieg",         "Neve",          "Nieve",           "Tuyết"},
    /*K_WX_STORM*/       {"Storm",          "Orage",           "Sturm",         "Storm",        "Burza",         "Tempest.",      "Tormenta",        "Bão"},
    /*K_TIMEZONE*/       {"Timezone",       "Fuseau horaire",  "Zeitzone",      "Tijdzone",     "Strefa czasowa","Fuso horário",  "Zona horaria",    "Múi giờ"},
    /*K_SCREENSAVER_FOR*/{"Screensaver for","Veille pendant",  "Schoner für",   "Schermbev. duur","Wygaszacz przez","Tela por",     "Salvap. durante", "Bảo vệ trong"},
    /*K_UNTIL_TAP*/      {"until tap",      "jusqu'au toucher","bis Tippen",    "tot tik",      "do dotknięcia", "até tocar",     "hasta tocar",     "đến khi chạm"},
};

// Russian (Cyrillic) — flat array in StrKey order; uses the same font (Cyrillic added to mont1).
static const char *const STR_RU[K_COUNT] = {
    /*status*/ "Не в сети", "Тревога", "FET выкл", "Баланс.", "Зарядка", "Разрядка", "Полный", "Простой",
    /*tiles*/ "НАПРЯЖ.", "ПИК ЗАР", "ПИК РАЗ", "ВРЕМЯ", "ОСТАЛОСЬ", "ЯЧЕЙКИ", "МОЩНОСТЬ", "ЁМКОСТЬ",
    "сбор данных...", "дн", "ч",
    /*system*/ "НАСТРОЙКИ", "Авто-переключ.", "Интервал", "Яркость", "Авто-сон", "Эко-режим",
    "Затемн. через", "Ед. темп.", "Формат врем.", "WiFi авто", "Скор. демо", "О системе",
    "Прошивка", "Демо-режим", "Заставка", "Заставка через", "Веб-адрес", "Веб-логин", "Веб-пароль", "Язык",
    /*values*/ "ВКЛ", "ВЫКЛ", "Никогда", "Цельсий", "Фаренг.", "12-час", "24-час", "смотр.",
    /*subtabs*/ "WiFi", "Система",
    /*bms config*/ "Батареи", "Настроить", "UART TX", "UART RX", "Параметры", "не в сети", "демо-режим",
    "чтение...", "MOSFET заряда", "MOSFET разряда", "Балансир",
    /*wifi*/ "Скан.", "Скан. снова", "нажмите Скан.", "сканирование...", "сетей найдено", "сети не найдены",
    "ошибка скан.", "подключение к", "Подключено:", "сбой (пароль?)", "сеть не найдена", "связь потеряна",
    "не подключено",
    /*keyboard*/ "введите пароль", "введите логин", "новый пароль", "Логин веб-интерфейса",
    "Пароль веб-интерфейса", "пробел", "Отмена", "Сохр.",
    /*info*/ "О СИСТЕМЕ", "Плата", "Flash", "PSRAM своб.", "Heap своб.", "Веб-вход", "Время работы",
    "нажмите чтобы закрыть", "BMS: скоро",
    /*params*/ "Ном. ёмкость", "Кол-во яч.", "Макс заряд A", "Макс разряд A", "Яч. OVP", "OVP возврат",
    "Яч. UVP", "UVP возврат", "SOC 100% В", "SOC 0% В", "Старт бал. В", "Порог бал. dV", "Макс бал. A",
    "Напр. заряда", "Напр. подд.", "Напр. откл.", "OCP зар. задерж", "OCP зар. возвр", "OCP раз. задерж",
    "OCP раз. возвр", "SCP задержка", "SCP возврат", "OTP заряда", "OTP зар. возвр", "OTP разряда",
    "OTP раз. возвр", "UTP заряда", "UTP зар. возвр", "MOS OTP", "MOS OTP возвр", "Умный сон В",
    "Старт нагр. T", "Умный сон ч",
    /*bit flags*/ "Нагрев", "Откл. датчик T", "Экран всегда вкл", "Умный сон", "Откл. PCL",
    "Данные по врем.", "Заряд подд.", "Кнопка авар.", "Сухой контакт", "OCP2 разряда",
    /*errors*/ "Сопрот. провода", "MOSFET перегрев", "Несоответ. яч.", "Полный заряд", "Перенапр. пакета",
    "Перегруз заряда", "КЗ заряда", "Перегрев заряда", "Недогрев заряда", "Ошибка сопроц.",
    "Недонапр. яч.", "Недонапр. пакета", "Перегруз разряда", "КЗ разряда", "Перегрев разряда",
    "Сбой MOSFET зар.", "Сбой MOSFET раз.", "GPS отключён", "Смена пароля", "Сбой вкл. разряда",
    "Перегрев батареи", "Аномалия датч. T", "Аномалия мод. PL", "Сбой сброса SCP", "OCP2 разряда",
    "OCP3 разряда", "Недогрев разряда", "Удал. блок. GPS",
    /*K_BAT*/ "БАТ", /*K_MOS*/ "MOS", /*K_T1*/ "T1", /*K_T2*/ "T2",
    /*K_AUTO_LOCK*/ "Автоблок.", /*K_LOCK_PIN*/ "PIN-код", /*K_ENTER_PIN*/ "Введите PIN",
    /*K_SET_PIN*/ "Задайте PIN из 6 цифр", /*K_WRONG_PIN*/ "Неверный PIN",
    /*K_PIN_SET*/ "задан", /*K_PIN_NONE*/ "нет",
    /*K_M_CHG*/ "Заряд", /*K_M_DIS*/ "Разряд", /*K_M_BAL*/ "Баланс",
    /*K_TODAY*/ "Сегодня", /*K_WX_CLEAR*/ "Ясно", /*K_WX_PARTLY*/ "Перем.", /*K_WX_CLOUDY*/ "Облачно",
    /*K_WX_RAIN*/ "Дождь", /*K_WX_SNOW*/ "Снег", /*K_WX_STORM*/ "Гроза",
    /*K_TIMEZONE*/ "Часовой пояс", /*K_SCREENSAVER_FOR*/ "Заставка на", /*K_UNTIL_TAP*/ "до касания",
};

// Chinese (Simplified) — flat array in StrKey order; rendered via the CJK font (see curFont).
static const char *const STR_ZH[K_COUNT] = {
    /*status*/ "离线", "报警", "FET关", "均衡中", "充电中", "放电中", "满电", "空闲",
    /*tiles*/ "电压", "峰值充", "峰值放", "运行", "剩余", "电芯", "功率", "容量",
    "采集中...", "天", "时",
    /*system*/ "设置", "自动切换", "切换间隔", "亮度", "自动休眠", "节能模式",
    "变暗延时", "温度单位", "时间格式", "WiFi自动", "演示速度", "系统信息",
    "固件", "演示模式", "屏保", "屏保延时", "网页地址", "网页用户", "网页密码", "语言",
    /*values*/ "开", "关", "从不", "摄氏", "华氏", "12小时", "24小时", "查看",
    /*subtabs*/ "WiFi", "系统",
    /*bms config*/ "电池数", "配置", "UART TX", "UART RX", "参数", "离线", "演示模式",
    "读取中...", "充电MOSFET", "放电MOSFET", "均衡器",
    /*wifi*/ "扫描", "重新扫描", "点击扫描查找网络", "扫描中...", "个网络", "无网络",
    "扫描失败", "连接到", "已连接:", "失败(密码?)", "未找到网络", "连接丢失",
    "未连接",
    /*keyboard*/ "输入密码", "输入用户名", "输入新密码", "网页界面用户名",
    "网页界面密码", "空格", "取消", "保存",
    /*info*/ "系统信息", "主板", "闪存", "PSRAM可用", "Heap可用", "网页登录", "运行时间",
    "点击关闭", "BMS信息: 即将推出",
    /*params*/ "标称容量", "电芯数", "最大充电A", "最大放电A", "电芯OVP", "OVP恢复",
    "电芯UVP", "UVP恢复", "SOC100%电压", "SOC0%电压", "均衡起始V", "均衡压差dV", "最大均衡A",
    "充电电压", "浮充电压", "关机电压", "OCP充延时", "OCP充恢复", "OCP放延时",
    "OCP放恢复", "SCP延时", "SCP恢复", "OTP充电", "OTP充恢复", "OTP放电",
    "OTP放恢复", "UTP充电", "UTP充恢复", "MOS OTP", "MOS OTP恢复", "智能休眠V",
    "加热起始T", "智能休眠时",
    /*bit flags*/ "加热", "禁用温度传感", "屏幕常亮", "智能休眠", "禁用PCL",
    "定时存储数据", "浮充", "紧急按钮", "干接点间歇", "放电OCP2",
    /*errors*/ "线缆电阻", "MOSFET过温", "电芯数不符", "充满", "组过压",
    "充电过流", "充电短路", "充电过温", "充电低温", "协处理器错误",
    "电芯欠压", "组欠压", "放电过流", "放电短路", "放电过温",
    "充电MOSFET故障", "放电MOSFET故障", "GPS断开", "更改密码", "放电开启失败",
    "电池过温", "温度传感异常", "PL模块异常", "SCP释放失败", "放电OCP2",
    "放电OCP3", "放电低温", "GPS远程锁定",
    /*K_BAT*/ "电池", /*K_MOS*/ "管温", /*K_T1*/ "温1", /*K_T2*/ "温2",
    /*K_AUTO_LOCK*/ "自动锁定", /*K_LOCK_PIN*/ "锁定密码", /*K_ENTER_PIN*/ "输入密码",
    /*K_SET_PIN*/ "设置6位密码", /*K_WRONG_PIN*/ "密码错误",
    /*K_PIN_SET*/ "已设置", /*K_PIN_NONE*/ "无",
    /*K_M_CHG*/ "充电", /*K_M_DIS*/ "放电", /*K_M_BAL*/ "均衡",
    /*K_TODAY*/ "今天", /*K_WX_CLEAR*/ "晴", /*K_WX_PARTLY*/ "多云间晴", /*K_WX_CLOUDY*/ "多云",
    /*K_WX_RAIN*/ "雨", /*K_WX_SNOW*/ "雪", /*K_WX_STORM*/ "雷暴",
    /*K_TIMEZONE*/ "Timezone", /*K_SCREENSAVER_FOR*/ "Screensaver for", /*K_UNTIL_TAP*/ "until tap",   // new keys: English until the CJK subset font is regenerated with their glyphs
};

// Arabic (RTL; LVGL bidi + Arabic shaping). Designated initializers — any key left out
// falls back to English. Latin tech abbreviations (OVP/UVP/OCP/OTP/UTP/SOC/MOS/SCP/FET) kept.
struct KV { uint16_t k; const char *s; };
static const KV AR_KV[] = {
    {K_OFFLINE,"غير متصل"},{K_ALARM,"إنذار"},{K_FET_OFF,"FET مغلق"},{K_BALANCING,"موازنة"},{K_CHARGING,"شحن"},{K_DISCHARGING,"تفريغ"},{K_FULL,"ممتلئ"},{K_IDLE,"خامل"},
    {K_VOLTAGE,"الجهد"},{K_PK_CHG,"ذروة شحن"},{K_PK_DIS,"ذروة تفريغ"},{K_UPTIME,"التشغيل"},{K_REMAIN,"المتبقي"},{K_CELLS,"الخلايا"},{K_POWER_DRAW,"الطاقة"},{K_CAPACITY,"السعة"},
    {K_COLLECTING,"جمع البيانات..."},{K_DAYS,"أيام"},{K_HOURS,"ساعات"},
    {K_SETTINGS,"الإعدادات"},{K_AUTO_SWITCH,"تبديل تلقائي"},{K_SWITCH_INTERVAL,"فترة التبديل"},{K_BRIGHTNESS,"السطوع"},{K_AUTO_SLEEP,"نوم تلقائي"},{K_ECO_MODE,"وضع اقتصادي"},
    {K_DIM_AFTER,"تعتيم بعد"},{K_TEMP_UNIT,"وحدة الحرارة"},{K_TIME_FORMAT,"تنسيق الوقت"},{K_WIFI_AUTO,"WiFi تلقائي"},{K_DEMO_SPEED,"سرعة العرض"},{K_SYSTEM_INFO,"معلومات النظام"},
    {K_FIRMWARE,"البرنامج الثابت"},{K_DEMO_MODE,"وضع العرض"},{K_SCREENSAVER,"شاشة التوقف"},{K_SCREENSAVER_AFTER,"التوقف بعد"},{K_WEB_ADDRESS,"عنوان الويب"},{K_WEB_USERNAME,"مستخدم الويب"},{K_WEB_PASSWORD,"كلمة مرور الويب"},{K_LANGUAGE,"اللغة"},
    {K_ON,"تشغيل"},{K_OFF,"إيقاف"},{K_NEVER,"أبداً"},{K_CELSIUS,"مئوية"},{K_FAHRENHEIT,"فهرنهايت"},{K_12_HOUR,"12 ساعة"},{K_24_HOUR,"24 ساعة"},{K_VIEW,"عرض"},
    {K_TAB_SYSTEM,"النظام"},
    {K_BATTERIES,"البطاريات"},{K_CONFIGURE,"تهيئة"},{K_PARAMETERS,"المعاملات"},{K_OFFLINE_LC,"غير متصل"},{K_DEMO_LC,"وضع العرض"},{K_READING,"قراءة..."},{K_CHARGE_MOSFET,"MOSFET الشحن"},{K_DISCHARGE_MOSFET,"MOSFET التفريغ"},{K_BALANCER,"الموازن"},
    {K_SCAN,"مسح"},{K_RESCAN,"إعادة المسح"},{K_WIFI_TAP_SCAN,"اضغط مسح للبحث"},{K_WIFI_SCANNING,"جارٍ المسح..."},{K_WIFI_NETS,"شبكات"},{K_WIFI_NO_NETS,"لا توجد شبكات"},{K_WIFI_SCAN_FAIL,"فشل المسح"},{K_WIFI_CONNECTING,"الاتصال بـ"},{K_WIFI_CONNECTED,"متصل:"},{K_WIFI_CONN_FAIL,"فشل (كلمة المرور؟)"},{K_WIFI_NOT_FOUND,"الشبكة غير موجودة"},{K_WIFI_CONN_LOST,"انقطع الاتصال"},{K_NOT_CONNECTED,"غير متصل"},
    {K_ENTER_PASSWORD,"أدخل كلمة المرور"},{K_ENTER_USERNAME,"أدخل اسم المستخدم"},{K_ENTER_NEW_PASSWORD,"كلمة مرور جديدة"},{K_HDR_WEB_USER,"اسم مستخدم واجهة الويب"},{K_HDR_WEB_PASS,"كلمة مرور واجهة الويب"},{K_KB_SPACE,"مسافة"},{K_CANCEL,"إلغاء"},{K_SAVE,"حفظ"},
    {K_HDR_SYSINFO,"معلومات النظام"},{K_BOARD,"اللوحة"},{K_PSRAM_FREE,"PSRAM متاح"},{K_HEAP_FREE,"Heap متاح"},{K_WEB_LOGIN,"دخول الويب"},{K_UPTIME_INFO,"مدة التشغيل"},{K_TAP_CLOSE,"اضغط للإغلاق"},{K_BMS_SOON,"BMS: قريباً"},
    {K_S_NOMINAL_CAP,"السعة الاسمية"},{K_S_CELL_COUNT,"عدد الخلايا"},{K_S_MAX_CHG_A,"أقصى شحن A"},{K_S_MAX_DIS_A,"أقصى تفريغ A"},{K_S_CELL_OVP,"خلية OVP"},{K_S_CELL_OVP_REC,"OVP استرجاع"},{K_S_CELL_UVP,"خلية UVP"},{K_S_CELL_UVP_REC,"UVP استرجاع"},{K_S_SOC100_V,"SOC 100% فولت"},{K_S_SOC0_V,"SOC 0% فولت"},{K_S_BAL_START_V,"بدء الموازنة V"},{K_S_BAL_TRIG_DV,"عتبة موازنة dV"},{K_S_MAX_BAL_A,"أقصى موازنة A"},{K_S_REQ_CHG_V,"جهد الشحن"},{K_S_REQ_FLOAT_V,"جهد التعويم"},{K_S_POWER_OFF_V,"جهد الإيقاف"},
    {K_B_HEATING,"التسخين"},{K_B_DIS_TEMP_SENS,"تعطيل مستشعر الحرارة"},{K_B_DISP_ALWAYS,"الشاشة دائماً"},{K_B_SMART_SLEEP,"نوم ذكي"},{K_B_DISABLE_PCL,"تعطيل PCL"},{K_B_TIMED_DATA,"بيانات مؤقتة"},{K_B_CHG_FLOAT,"شحن تعويمي"},{K_B_EMERGENCY,"زر الطوارئ"},{K_B_DRY_CONTACT,"تلامس جاف"},{K_B_DIS_OCP2,"OCP2 تفريغ"},
    {K_E_WIRE_RES,"مقاومة السلك"},{K_E_MOS_OT,"MOSFET ساخن"},{K_E_CELL_MISMATCH,"عدد خلايا خاطئ"},{K_E_FULLY_CHARGED,"مشحون بالكامل"},{K_E_PACK_OV,"جهد زائد"},{K_E_CHG_OC,"تيار شحن زائد"},{K_E_CHG_SC,"قصر شحن"},{K_E_CHG_OT,"حرارة شحن زائدة"},{K_E_CHG_UT,"حرارة شحن منخفضة"},{K_E_COPROC,"خطأ المعالج المساعد"},{K_E_CELL_UV,"جهد خلية منخفض"},{K_E_PACK_UV,"جهد حزمة منخفض"},{K_E_DIS_OC,"تيار تفريغ زائد"},{K_E_DIS_SC,"قصر تفريغ"},{K_E_DIS_OT,"حرارة تفريغ زائدة"},{K_E_CHG_MOS_FAULT,"عطل MOSFET الشحن"},{K_E_DIS_MOS_FAULT,"عطل MOSFET التفريغ"},{K_E_GPS_DISC,"GPS مفصول"},{K_E_CHG_PWD,"تغيير كلمة المرور"},{K_E_DIS_ON_FAIL,"فشل تشغيل التفريغ"},{K_E_BAT_OT,"بطارية ساخنة"},{K_E_TEMP_ANOM,"خلل مستشعر الحرارة"},{K_E_PL_ANOM,"خلل وحدة PL"},{K_E_SCP_REL_FAIL,"فشل تحرير SCP"},{K_E_DIS_OCP2,"OCP2 تفريغ"},{K_E_DIS_OCP3,"OCP3 تفريغ"},{K_E_DIS_UT,"حرارة تفريغ منخفضة"},{K_E_GPS_LOCK,"قفل GPS عن بُعد"},
    {K_BAT,"بطارية"},
    {K_AUTO_LOCK,"قفل تلقائي"},{K_LOCK_PIN,"رمز القفل"},{K_ENTER_PIN,"أدخل الرمز"},{K_SET_PIN,"حدد رمزاً من 6 أرقام"},{K_WRONG_PIN,"رمز خاطئ"},{K_PIN_SET,"محدد"},{K_PIN_NONE,"لا يوجد"},
    {K_M_CHG,"شحن"},{K_M_DIS,"تفريغ"},{K_M_BAL,"موازنة"},
    {K_TODAY,"اليوم"},{K_WX_CLEAR,"صافٍ"},{K_WX_PARTLY,"غائم جزئي"},{K_WX_CLOUDY,"غائم"},{K_WX_RAIN,"مطر"},{K_WX_SNOW,"ثلج"},{K_WX_STORM,"عاصفة"},
};

// Hindi (Devanagari). NOTE: LVGL can't shape Devanagari → glyphs render unjoined (best-effort, as agreed).
static const KV HI_KV[] = {
    {K_OFFLINE,"ऑफ़लाइन"},{K_ALARM,"अलार्म"},{K_FET_OFF,"FET बंद"},{K_BALANCING,"संतुलन"},{K_CHARGING,"चार्जिंग"},{K_DISCHARGING,"डिस्चार्ज"},{K_FULL,"पूर्ण"},{K_IDLE,"निष्क्रिय"},
    {K_VOLTAGE,"वोल्टेज"},{K_PK_CHG,"शिखर चार्ज"},{K_PK_DIS,"शिखर डिस्च"},{K_UPTIME,"अपटाइम"},{K_REMAIN,"शेष"},{K_CELLS,"सेल"},{K_POWER_DRAW,"पावर"},{K_CAPACITY,"क्षमता"},
    {K_COLLECTING,"डेटा एकत्र..."},{K_DAYS,"दिन"},{K_HOURS,"घंटे"},
    {K_SETTINGS,"सेटिंग्स"},{K_AUTO_SWITCH,"ऑटो-स्विच"},{K_SWITCH_INTERVAL,"स्विच अंतराल"},{K_BRIGHTNESS,"चमक"},{K_AUTO_SLEEP,"ऑटो-स्लीप"},{K_ECO_MODE,"इको मोड"},
    {K_DIM_AFTER,"मंद करें"},{K_TEMP_UNIT,"तापमान इकाई"},{K_TIME_FORMAT,"समय प्रारूप"},{K_WIFI_AUTO,"WiFi ऑटो"},{K_DEMO_SPEED,"डेमो गति"},{K_SYSTEM_INFO,"सिस्टम जानकारी"},
    {K_FIRMWARE,"फर्मवेयर"},{K_DEMO_MODE,"डेमो मोड"},{K_SCREENSAVER,"स्क्रीनसेवर"},{K_SCREENSAVER_AFTER,"स्क्रीनसेवर बाद"},{K_WEB_ADDRESS,"वेब पता"},{K_WEB_USERNAME,"वेब उपयोगकर्ता"},{K_WEB_PASSWORD,"वेब पासवर्ड"},{K_LANGUAGE,"भाषा"},
    {K_ON,"चालू"},{K_OFF,"बंद"},{K_NEVER,"कभी नहीं"},{K_CELSIUS,"सेल्सियस"},{K_FAHRENHEIT,"फ़ारेन."},{K_12_HOUR,"12-घंटा"},{K_24_HOUR,"24-घंटा"},{K_VIEW,"देखें"},
    {K_TAB_SYSTEM,"सिस्टम"},
    {K_BATTERIES,"बैटरियां"},{K_CONFIGURE,"कॉन्फ़िगर"},{K_PARAMETERS,"पैरामीटर"},{K_OFFLINE_LC,"ऑफ़लाइन"},{K_DEMO_LC,"डेमो मोड"},{K_READING,"पढ़ रहा..."},{K_CHARGE_MOSFET,"चार्ज MOSFET"},{K_DISCHARGE_MOSFET,"डिस्च MOSFET"},{K_BALANCER,"बैलेंसर"},
    {K_SCAN,"स्कैन"},{K_RESCAN,"पुनः स्कैन"},{K_WIFI_TAP_SCAN,"नेटवर्क हेतु स्कैन"},{K_WIFI_SCANNING,"स्कैन हो रहा..."},{K_WIFI_NETS,"नेटवर्क मिले"},{K_WIFI_NO_NETS,"कोई नेटवर्क नहीं"},{K_WIFI_SCAN_FAIL,"स्कैन विफल"},{K_WIFI_CONNECTING,"कनेक्ट हो रहा"},{K_WIFI_CONNECTED,"कनेक्टेड:"},{K_WIFI_CONN_FAIL,"विफल (पासवर्ड?)"},{K_WIFI_NOT_FOUND,"नेटवर्क नहीं मिला"},{K_WIFI_CONN_LOST,"कनेक्शन टूटा"},{K_NOT_CONNECTED,"कनेक्ट नहीं"},
    {K_ENTER_PASSWORD,"पासवर्ड दर्ज करें"},{K_ENTER_USERNAME,"उपयोगकर्ता दर्ज करें"},{K_ENTER_NEW_PASSWORD,"नया पासवर्ड"},{K_HDR_WEB_USER,"वेब उपयोगकर्ता नाम"},{K_HDR_WEB_PASS,"वेब पासवर्ड"},{K_KB_SPACE,"स्पेस"},{K_CANCEL,"रद्द"},{K_SAVE,"सहेजें"},
    {K_HDR_SYSINFO,"सिस्टम जानकारी"},{K_BOARD,"बोर्ड"},{K_PSRAM_FREE,"PSRAM खाली"},{K_HEAP_FREE,"Heap खाली"},{K_WEB_LOGIN,"वेब लॉगिन"},{K_UPTIME_INFO,"अपटाइम"},{K_TAP_CLOSE,"बंद करने हेतु"},{K_BMS_SOON,"BMS: जल्द"},
    {K_S_NOMINAL_CAP,"नाममात्र क्षमता"},{K_S_CELL_COUNT,"सेल संख्या"},{K_S_MAX_CHG_A,"अधि चार्ज A"},{K_S_MAX_DIS_A,"अधि डिस्च A"},{K_S_CELL_OVP,"सेल OVP"},{K_S_CELL_UVP,"सेल UVP"},{K_S_SOC100_V,"SOC 100% V"},{K_S_SOC0_V,"SOC 0% V"},{K_S_MAX_BAL_A,"अधि बैलेंस A"},{K_S_REQ_CHG_V,"चार्ज वोल्टेज"},{K_S_REQ_FLOAT_V,"फ्लोट वोल्टेज"},
    {K_B_HEATING,"हीटिंग"},{K_B_SMART_SLEEP,"स्मार्ट स्लीप"},{K_B_DISABLE_PCL,"PCL बंद"},{K_B_CHG_FLOAT,"फ्लोट चार्ज"},{K_B_EMERGENCY,"आपातकालीन बटन"},
    {K_E_FULLY_CHARGED,"पूर्ण चार्ज"},{K_E_PACK_OV,"अधिक वोल्टेज"},{K_E_CHG_OC,"चार्ज अधिक धारा"},{K_E_DIS_OC,"डिस्च अधिक धारा"},{K_E_CELL_UV,"सेल कम वोल्टेज"},{K_E_BAT_OT,"बैटरी अधिक ताप"},{K_E_CHG_MOS_FAULT,"चार्ज MOSFET दोष"},{K_E_DIS_MOS_FAULT,"डिस्च MOSFET दोष"},
    {K_BAT,"बैटरी"},
    {K_AUTO_LOCK,"ऑटो-लॉक"},{K_LOCK_PIN,"लॉक पिन"},{K_ENTER_PIN,"पिन दर्ज करें"},{K_SET_PIN,"6 अंकों का पिन सेट करें"},{K_WRONG_PIN,"गलत पिन"},{K_PIN_SET,"सेट"},{K_PIN_NONE,"कोई नहीं"},
    {K_M_CHG,"चार्ज"},{K_M_DIS,"डिस्चार्ज"},{K_M_BAL,"बैलेंस"},
    {K_TODAY,"आज"},{K_WX_CLEAR,"साफ़"},{K_WX_PARTLY,"आंशिक बादल"},{K_WX_CLOUDY,"बादल"},{K_WX_RAIN,"बारिश"},{K_WX_SNOW,"बर्फ़"},{K_WX_STORM,"तूफ़ान"},
};

static inline const char *kvFind(const KV *a, int n, int k) { for (int i = 0; i < n; i++) if (a[i].k == k) return a[i].s; return 0; }
static inline const char *T(int k) {
    if (g_lang == LANG_RU) return STR_RU[k];
    if (g_lang == LANG_ZH) return STR_ZH[k];
    if (g_lang == LANG_AR) { const char *s = kvFind(AR_KV, (int)(sizeof(AR_KV)/sizeof(AR_KV[0])), k); return s ? s : STR[k][LANG_EN]; }
    if (g_lang == LANG_HI) { const char *s = kvFind(HI_KV, (int)(sizeof(HI_KV)/sizeof(HI_KV[0])), k); return s ? s : STR[k][LANG_EN]; }
    return STR[k][g_lang];   // LANG_EN..LANG_VI
}

// Short weekday names for the weather popup. Index = tm_wday (0=Sun .. 6=Sat); rows
// follow the LANG_* order. Kept separate from the K-table (it's a 7-wide grid, not a key).
static const char *const WDAY[LANG_COUNT][7] = {
    /*EN*/ {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"},
    /*FR*/ {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"},
    /*DE*/ {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"},
    /*NL*/ {"Zo", "Ma", "Di", "Wo", "Do", "Vr", "Za"},
    /*PL*/ {"Nd", "Pn", "Wt", "Śr", "Cz", "Pt", "So"},
    /*PT*/ {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sáb"},
    /*ES*/ {"Dom", "Lun", "Mar", "Mié", "Jue", "Vie", "Sáb"},
    /*VI*/ {"CN", "T2", "T3", "T4", "T5", "T6", "T7"},
    /*RU*/ {"Вс", "Пн", "Вт", "Ср", "Чт", "Пт", "Сб"},
    /*ZH*/ {"日", "一", "二", "三", "四", "五", "六"},
    /*AR*/ {"أحد", "إثن", "ثلا", "أرب", "خمي", "جمع", "سبت"},
    /*HI*/ {"रवि", "सोम", "मंगल", "बुध", "गुरु", "शुक्र", "शनि"},
};
static inline const char *wday(int wd) { return WDAY[g_lang][((wd % 7) + 7) % 7]; }
