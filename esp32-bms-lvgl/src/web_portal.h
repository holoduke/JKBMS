// On-device web portal: live monitor + controls + OTA firmware update.
// Included into main.cpp AFTER the globals/helpers it uses (bms[], bmsLive[],
// bmsSet, setPut, SETDEFS, etc.). HTTP Basic auth (WEB_USER / webPass) on every
// route. Served by the sync WebServer + ArduinoOTA, both pumped from loop().
#include <WebServer.h>
#include <ArduinoOTA.h>
#include <Update.h>
#include <JPEGENC.h>

static WebServer webServer(80);
static bool webStarted = false;
volatile bool otaActive = false;   // true during an OTA → loop() drops everything but OTA

// require auth on every request; returns false (and sends the 401) if not authed.
// Digest auth → the password is never sent in cleartext over the LAN (unlike Basic),
// without the self-signed-cert warnings/overhead that ESP32 TLS would bring.
static bool webAuth() {
    if (webServer.authenticate(webUser, webPass)) return true;
    webServer.requestAuthentication(DIGEST_AUTH, "JK BMS");
    return false;
}

static const char WEB_PAGE[] PROGMEM = R"HTML(<!doctype html><html lang=en><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1">
<title>JK BMS</title><style>
:root{--bg:#0a0e13;--bg2:#0e141c;--card:#121922;--card2:#0d131b;--bd:#212c38;--bd2:#2c3a49;
 --txt:#e8eef6;--mut:#8593a4;--acc:#3b82f6;--acc2:#2563eb;--good:#34d399;--warn:#fbbf24;--bad:#f87171;--cy:#22d3ee;--vio:#a78bfa}
*{box-sizing:border-box}
body{margin:0;color:var(--txt);font:14px/1.45 system-ui,-apple-system,Segoe UI,Roboto,sans-serif;
 background:radial-gradient(1200px 600px at 20% -10%,#16202c 0,var(--bg) 55%) fixed,var(--bg)}
.wrap{max-width:1120px;margin:0 auto;padding:14px 14px 40px}
.hd{position:sticky;top:0;z-index:5;display:flex;align-items:center;gap:12px;flex-wrap:wrap;
 padding:10px 12px;margin:-14px -14px 14px;background:rgba(10,14,19,.78);backdrop-filter:blur(10px);border-bottom:1px solid var(--bd)}
.brand{display:flex;align-items:center;gap:9px;font-weight:700;font-size:16px;letter-spacing:.2px}
.logo{width:24px;height:24px;border-radius:7px;background:linear-gradient(135deg,var(--acc),var(--vio));
 display:grid;place-items:center;font-size:13px;box-shadow:0 2px 10px rgba(59,130,246,.5)}
.grow{flex:1}
.sel{appearance:none;background:var(--card) url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='10' height='6'%3E%3Cpath d='M0 0l5 6 5-6z' fill='%238593a4'/%3E%3C/svg%3E") no-repeat right 10px center;
 color:var(--txt);border:1px solid var(--bd2);border-radius:9px;padding:7px 30px 7px 11px;font-size:13px;cursor:pointer}
.bar{display:flex;align-items:center;gap:10px;flex-wrap:wrap;margin:0 2px 14px}
.seg{display:inline-flex;gap:3px;padding:4px;background:var(--card2);border:1px solid var(--bd);border-radius:11px}
.tab{padding:7px 20px;border-radius:8px;color:var(--mut);cursor:pointer;font-weight:600;transition:.15s}
.tab:hover{color:var(--txt)}.tab.on{background:linear-gradient(135deg,var(--acc),var(--acc2));color:#fff;box-shadow:0 2px 10px rgba(37,99,235,.5)}
.bsingle{display:inline-flex;align-items:center;gap:8px;padding:7px 15px;border-radius:9px;background:var(--card);border:1px solid var(--bd);font-weight:600}
.bsingle::before{content:"";width:8px;height:8px;border-radius:50%;background:var(--good);box-shadow:0 0 8px var(--good)}
.pill{padding:3px 11px;border-radius:999px;background:var(--card);border:1px solid var(--bd);font-size:12px;color:var(--mut)}
.grid{display:flex;flex-direction:column;gap:14px}
@media(min-width:780px){.grid{flex-direction:row;align-items:flex-start}}
.col{display:flex;flex-direction:column;gap:14px;flex:1;min-width:0}
.card{background:linear-gradient(180deg,var(--card),var(--card2));border:1px solid var(--bd);border-radius:14px;
 padding:15px;box-shadow:0 1px 2px rgba(0,0,0,.3),0 8px 24px -16px rgba(0,0,0,.6);transition:border-color .15s,transform .15s}
.card:hover{border-color:var(--bd2)}
.ct{font-size:11px;color:var(--mut);text-transform:uppercase;letter-spacing:.07em;font-weight:600;margin-bottom:10px;display:flex;gap:6px;align-items:baseline}
.row{display:flex;justify-content:space-between;align-items:center;gap:10px;padding:5px 0;border-bottom:1px solid rgba(255,255,255,.04)}
.row:last-child{border-bottom:0}
.mut{color:var(--mut)}.grn{color:var(--good)}.amb{color:var(--warn)}.red{color:var(--bad)}.cy{color:var(--cy)}.vio{color:var(--vio)}
.big{font-size:30px;font-weight:800;line-height:1.05;letter-spacing:-.5px}
.met{display:grid;grid-template-columns:1fr 1fr;gap:10px}
.met>div{background:var(--card2);border:1px solid var(--bd);border-radius:10px;padding:10px;text-align:center}
.met .v{font-size:21px;font-weight:700}
.cells{display:grid;grid-template-columns:repeat(auto-fill,minmax(76px,1fr));gap:7px}
.cell{background:var(--card2);border:1px solid var(--bd);border-radius:9px;padding:7px 4px;text-align:center;font-size:12px}
.cell.hi{border-color:var(--warn);box-shadow:inset 0 0 0 1px rgba(251,191,36,.3)}.cell.lo{border-color:var(--cy);box-shadow:inset 0 0 0 1px rgba(34,211,238,.3)}
.btn,button{background:linear-gradient(135deg,var(--acc),var(--acc2));color:#fff;border:0;border-radius:9px;padding:8px 13px;font-size:14px;font-weight:600;cursor:pointer;transition:.15s}
button:hover{filter:brightness(1.08)}button:active{transform:translateY(1px)}
button.off{background:var(--card2);border:1px solid var(--bd2);color:var(--mut)}
button.sm{padding:5px 11px;font-size:12px}
table{width:100%;border-collapse:collapse}td{padding:7px 4px;border-bottom:1px solid rgba(255,255,255,.05)}tr:last-child td{border-bottom:0}
input{background:var(--card2);color:var(--txt);border:1px solid var(--bd2);border-radius:8px;padding:7px 9px;width:120px;font-size:13px}
input:focus{outline:0;border-color:var(--acc);box-shadow:0 0 0 3px rgba(59,130,246,.2)}
input[type=checkbox]{width:auto;accent-color:var(--acc)}
img{width:100%;max-width:480px;border:1px solid var(--bd);border-radius:10px;image-rendering:pixelated}
#prog{height:8px;background:var(--card2);border-radius:5px;overflow:hidden;display:none;margin-top:10px}#pb{height:100%;width:0;background:linear-gradient(90deg,var(--acc),var(--good));transition:width .2s}
.scrwrap{margin-top:10px;min-height:54px;display:flex;align-items:center;justify-content:center}
.spin{width:30px;height:30px;border:3px solid var(--bd2);border-top-color:var(--acc);border-radius:50%;animation:sp .8s linear infinite}
@keyframes sp{to{transform:rotate(360deg)}}
.stack{display:flex;gap:8px;align-items:center}
</style></head><body><div class=wrap>
<header class=hd>
 <div class=brand><span class=logo>⚡</span>JK BMS <span class=mut style=font-weight:500 id=fw></span></div>
 <div class=grow></div>
 <select class=sel id=lang title=Language></select>
 <span class=pill id=net></span>
</header>
<div class=bar><span class=seg id=seg><span class="tab on" id=t0 onclick=sel(0)>BAT 1</span><span class=tab id=t1 onclick=sel(1)>BAT 2</span></span>
<span class=bsingle id=single style=display:none data-i18n=bat1>Battery 1</span></div>
<div class=grid>
 <div class=col>
  <div class=card><div class=ct data-i18n=status>Status</div><div id=stat></div></div>
  <div class=card><div class=ct data-i18n=live>Live</div><div class=met id=met></div></div>
  <div class=card><div class=ct><span data-i18n=weather>Weather</span> <span id=wxc class=mut></span></div><div id=wx></div></div>
  <div class=card><div class=ct><span data-i18n=cells>Cells</span> <span id=cd class=mut></span></div><div class=cells id=cells></div></div>
  <div class=card><div class=ct data-i18n=temps>Temperatures</div><div id=temps></div></div>
  <div class=card><div class=ct data-i18n=session>Session</div><div id=sess></div></div>
  <div class=card><div class=ct data-i18n=history>History</div>
   <div class=mut style=font-size:11px>SOC %</div><canvas id=hsoc style=width:100%;height:78px;display:block></canvas>
   <div class=mut style="font-size:11px;margin-top:8px">Power W</div><canvas id=hpw style=width:100%;height:78px;display:block></canvas>
   <div class=mut style="font-size:11px;margin-top:8px">Temp °C</div><canvas id=htmp style=width:100%;height:78px;display:block></canvas>
   <div class=row style=margin-top:8px><span class=mut id=hspan></span>
    <a class="btn sm" href=/history.csv download style=text-decoration:none data-i18n=csvexport>Download CSV</a></div></div>
  <div class=card><div class=ct data-i18n=controls>Controls</div><div id=ctl></div></div>
 </div>
 <div class=col>
  <div class=card><div class=ct data-i18n=devscreen>Device screen</div><button class=sm onclick=shot() data-i18n=refresh>Refresh</button>
   <div class=scrwrap><img id=scr style=display:none><div id=scrld class=spin style=display:none></div><span id=scrh class=mut data-i18n=loading>loading…</span></div></div>
  <div class=card><div class=ct><span data-i18n=settings>Settings</span> <span class=mut data-i18n=tapedit>(tap value to edit)</span></div><table id=params></table></div>
  <div class=card><div class=ct data-i18n=fwupdate>Firmware update</div><p class=mut id=fwv></p>
   <div class=row id=updrow style=display:none><span id=updmsg class=grn></span><button class=sm onclick=doupd()>Update now</button></div>
   <div class=row><span><label class=stack><input type=checkbox id=aupd> <span>Auto-update from GitHub releases</span></label></span></div>
   <div class=stack style=margin-top:8px><input type=file id=fwf accept=.bin> <button onclick=upl() data-i18n=flash>Upload &amp; flash</button></div>
   <div id=prog><div id=pb></div></div><p id=ust></p></div>
  <div class=card><div class=ct data-i18n=security>Security</div><div class=row><span data-i18n=chgpw>Change password</span>
   <span class=stack><input type=password id=np data-ph=newpw><button class=sm onclick=chpw() data-i18n=save>Save</button></span></div></div>
  <div class=card><div class=ct>Home Assistant (MQTT)</div>
   <div class=row><span class=mut data-i18n=status>Status</span><span id=mqst>—</span></div>
   <div class=row><span data-i18n=broker>Broker host</span><input id=mqh placeholder=192.168.x.x></div>
   <div class=row><span data-i18n=port>Port</span><input id=mqp type=number placeholder=1883></div>
   <div class=row><span data-i18n=user>Username</span><input id=mqu data-ph=optional></div>
   <div class=row><span data-i18n=pass>Password</span><input id=mqpw type=password data-ph=unchanged></div>
   <div class=row><span><label class=stack><input type=checkbox id=mqe> <span data-i18n=enabled>Enabled</span></label></span><button class=sm onclick=savemq() data-i18n=save>Save</button></div></div>
  <div class=card><div class=ct data-i18n=alerts>Alerts</div>
   <p class=mut style=margin:0 0 8px data-i18n=alertshint>Push to an ntfy.sh topic or any webhook when a problem appears</p>
   <div class=row><span data-i18n=webhook>Webhook URL</span><input id=alu placeholder=https://ntfy.sh/...></div>
   <div class=row><span data-i18n=soclow>Low SOC %</span><input id=als type=number></div>
   <div class=row><span data-i18n=temphi>High temp °C</span><input id=alt type=number></div>
   <div class=row><span data-i18n=deltahi>Cell delta mV</span><input id=ald type=number></div>
   <div class=row><span><label class=stack><input type=checkbox id=alf> <span data-i18n=onfault>Alert on faults</span></label></span></div>
   <div class=row><span><label class=stack><input type=checkbox id=ale> <span data-i18n=enabled>Enabled</span></label></span>
    <span class=stack><button class="sm off" onclick=testal() data-i18n=test>Test</button><button class=sm onclick=saveal() data-i18n=save>Save</button></span></div>
   <p id=alst class=mut></p></div>
 </div>
</div></div><script>
const I18N={
en:{bat:"Battery",bat1:"Battery 1",status:"Status",live:"Live",weather:"Weather",cells:"Cells",temps:"Temperatures",session:"Session",controls:"Controls",devscreen:"Device screen",settings:"Settings",fwupdate:"Firmware update",security:"Security",tapedit:"(tap value to edit)",refresh:"Refresh",flash:"Upload & flash",save:"Save",chgpw:"Change password",newpw:"new password",broker:"Broker host",port:"Port",user:"Username",pass:"Password",enabled:"Enabled",optional:"optional",unchanged:"(unchanged)",loading:"loading…",retrying:"retrying…",loadfail:"load failed — tap Refresh",current:"current",pickbin:"pick a .bin first",rebooting:"OK — device rebooting…",failed:"failed",pwmin:"password min 4 chars",pwok:"password changed — re-login next action",pwfail:"change failed",mqsaved:"saved — connecting…",mqfail:"save failed",connected:"connected",notconn:"enabled, not connected",disabled:"disabled",up:"up",disconnected:"disconnected — retrying…",alarm:"Alarm",operational:"Operational",state:"State",link:"Link",livev:"live",offline:"offline",soc:"SOC",charging:"charging",discharging:"discharging",idle:"idle",voltage:"voltage",curr:"current",mosfet:"MOSFET",sensor:"Sensor",capacity:"Capacity",totalenergy:"Total energy",cycles:"Cycles",health:"Health",uptime:"Uptime",balcur:"Balance current",peakchg:"Peak charge",peakdis:"Peak discharge",chg24:"Charged 24h",used24:"Used 24h",chg6:"Charged 6h",used6:"Used 6h",chgmos:"Charge MOSFET",dismos:"Discharge MOSFET",balancer:"Balancer",on:"ON",off:"OFF",noset:"settings not loaded (BMS offline?)",today:"Today",tomorrow:"Tomorrow",indays:"In {n} days",wxnone:"no data — needs internet",newval:"New value for",writefail:"write failed",echg:"Charged total",edis:"Discharged total",history:"History",csvexport:"Download CSV",alerts:"Alerts",alertshint:"Push to an ntfy.sh topic or any webhook when a problem appears",webhook:"Webhook URL",soclow:"Low SOC %",temphi:"High temp °C",deltahi:"Cell delta mV",onfault:"Alert on faults",test:"Test",balancing:"balancing",alsaved:"saved",altestok:"test sent ✓",altestfail:"send failed"},
fr:{bat:"Batterie",bat1:"Batterie 1",status:"État",live:"En direct",weather:"Météo",cells:"Cellules",temps:"Températures",session:"Session",controls:"Commandes",devscreen:"Écran appareil",settings:"Réglages",fwupdate:"Mise à jour",security:"Sécurité",tapedit:"(touchez pour éditer)",refresh:"Rafraîchir",flash:"Téléverser & flasher",save:"Enreg.",chgpw:"Changer le mot de passe",newpw:"nouveau mot de passe",broker:"Hôte broker",port:"Port",user:"Utilisateur",pass:"Mot de passe",enabled:"Activé",optional:"optionnel",unchanged:"(inchangé)",loading:"chargement…",retrying:"nouvel essai…",loadfail:"échec — touchez Rafraîchir",current:"actuel",pickbin:"choisir un .bin",rebooting:"OK — redémarrage…",failed:"échec",pwmin:"mot de passe min 4 car.",pwok:"changé — reconnectez-vous",pwfail:"échec",mqsaved:"enregistré — connexion…",mqfail:"échec",connected:"connecté",notconn:"activé, non connecté",disabled:"désactivé",up:"actif",disconnected:"déconnecté — nouvel essai…",alarm:"Alarme",operational:"Opérationnel",state:"État",link:"Lien",livev:"en ligne",offline:"hors ligne",soc:"SOC",charging:"en charge",discharging:"décharge",idle:"inactif",voltage:"tension",curr:"courant",mosfet:"MOSFET",sensor:"Capteur",capacity:"Capacité",totalenergy:"Énergie totale",cycles:"Cycles",health:"Santé",uptime:"Durée",balcur:"Courant d'équil.",peakchg:"Pic charge",peakdis:"Pic décharge",chg24:"Chargé 24h",used24:"Utilisé 24h",chg6:"Chargé 6h",used6:"Utilisé 6h",chgmos:"MOSFET charge",dismos:"MOSFET décharge",balancer:"Équilibreur",on:"ON",off:"OFF",noset:"réglages non chargés (BMS hors ligne ?)",today:"Aujourd'hui",tomorrow:"Demain",indays:"Dans {n} jours",wxnone:"pas de données — internet requis",newval:"Nouvelle valeur pour",writefail:"échec d'écriture"},
de:{bat:"Akku",bat1:"Akku 1",status:"Status",live:"Live",weather:"Wetter",cells:"Zellen",temps:"Temperaturen",session:"Sitzung",controls:"Steuerung",devscreen:"Gerätebildschirm",settings:"Einstellungen",fwupdate:"Firmware-Update",security:"Sicherheit",tapedit:"(zum Bearbeiten tippen)",refresh:"Aktualisieren",flash:"Hochladen & flashen",save:"Speichern",chgpw:"Passwort ändern",newpw:"neues Passwort",broker:"Broker-Host",port:"Port",user:"Benutzer",pass:"Passwort",enabled:"Aktiviert",optional:"optional",unchanged:"(unverändert)",loading:"lädt…",retrying:"erneut…",loadfail:"Fehler — Aktualisieren tippen",current:"aktuell",pickbin:".bin wählen",rebooting:"OK — Neustart…",failed:"Fehler",pwmin:"Passwort min. 4 Zeichen",pwok:"geändert — neu anmelden",pwfail:"Fehler",mqsaved:"gespeichert — verbinde…",mqfail:"Fehler",connected:"verbunden",notconn:"aktiv, nicht verbunden",disabled:"deaktiviert",up:"aktiv",disconnected:"getrennt — erneut…",alarm:"Alarm",operational:"Betriebsbereit",state:"Zustand",link:"Verbindung",livev:"live",offline:"offline",soc:"SOC",charging:"lädt",discharging:"entlädt",idle:"Leerlauf",voltage:"Spannung",curr:"Strom",mosfet:"MOSFET",sensor:"Sensor",capacity:"Kapazität",totalenergy:"Gesamtenergie",cycles:"Zyklen",health:"Zustand",uptime:"Laufzeit",balcur:"Balance-Strom",peakchg:"Spitze Laden",peakdis:"Spitze Entladen",chg24:"Geladen 24h",used24:"Verbraucht 24h",chg6:"Geladen 6h",used6:"Verbraucht 6h",chgmos:"Lade-MOSFET",dismos:"Entlade-MOSFET",balancer:"Balancer",on:"AN",off:"AUS",noset:"Einstellungen nicht geladen (BMS offline?)",today:"Heute",tomorrow:"Morgen",indays:"In {n} Tagen",wxnone:"keine Daten — Internet nötig",newval:"Neuer Wert für",writefail:"Schreibfehler"},
nl:{bat:"Accu",bat1:"Accu 1",status:"Status",live:"Live",weather:"Weer",cells:"Cellen",temps:"Temperaturen",session:"Sessie",controls:"Bediening",devscreen:"Apparaatscherm",settings:"Instellingen",fwupdate:"Firmware-update",security:"Beveiliging",tapedit:"(tik om te bewerken)",refresh:"Vernieuwen",flash:"Uploaden & flashen",save:"Opslaan",chgpw:"Wachtwoord wijzigen",newpw:"nieuw wachtwoord",broker:"Broker-host",port:"Poort",user:"Gebruiker",pass:"Wachtwoord",enabled:"Ingeschakeld",optional:"optioneel",unchanged:"(ongewijzigd)",loading:"laden…",retrying:"opnieuw…",loadfail:"mislukt — tik Vernieuwen",current:"huidig",pickbin:"kies een .bin",rebooting:"OK — herstart…",failed:"mislukt",pwmin:"wachtwoord min 4 tekens",pwok:"gewijzigd — opnieuw inloggen",pwfail:"mislukt",mqsaved:"opgeslagen — verbinden…",mqfail:"mislukt",connected:"verbonden",notconn:"aan, niet verbonden",disabled:"uit",up:"actief",disconnected:"verbroken — opnieuw…",alarm:"Alarm",operational:"Operationeel",state:"Toestand",link:"Verbinding",livev:"live",offline:"offline",soc:"SOC",charging:"opladen",discharging:"ontladen",idle:"inactief",voltage:"spanning",curr:"stroom",mosfet:"MOSFET",sensor:"Sensor",capacity:"Capaciteit",totalenergy:"Totale energie",cycles:"Cycli",health:"Conditie",uptime:"Looptijd",balcur:"Balanceerstroom",peakchg:"Piek laden",peakdis:"Piek ontladen",chg24:"Geladen 24h",used24:"Gebruikt 24h",chg6:"Geladen 6h",used6:"Gebruikt 6h",chgmos:"Laad-MOSFET",dismos:"Ontlaad-MOSFET",balancer:"Balancer",on:"AAN",off:"UIT",noset:"instellingen niet geladen (BMS offline?)",today:"Vandaag",tomorrow:"Morgen",indays:"Over {n} dagen",wxnone:"geen data — internet nodig",newval:"Nieuwe waarde voor",writefail:"schrijven mislukt"},
pl:{bat:"Bateria",bat1:"Bateria 1",status:"Status",live:"Na żywo",weather:"Pogoda",cells:"Ogniwa",temps:"Temperatury",session:"Sesja",controls:"Sterowanie",devscreen:"Ekran urządzenia",settings:"Ustawienia",fwupdate:"Aktualizacja",security:"Bezpieczeństwo",tapedit:"(dotknij aby edytować)",refresh:"Odśwież",flash:"Wyślij i wgraj",save:"Zapisz",chgpw:"Zmień hasło",newpw:"nowe hasło",broker:"Host brokera",port:"Port",user:"Użytkownik",pass:"Hasło",enabled:"Włączone",optional:"opcjonalne",unchanged:"(bez zmian)",loading:"ładowanie…",retrying:"ponawianie…",loadfail:"błąd — dotknij Odśwież",current:"obecna",pickbin:"wybierz .bin",rebooting:"OK — restart…",failed:"błąd",pwmin:"hasło min 4 znaki",pwok:"zmienione — zaloguj ponownie",pwfail:"błąd",mqsaved:"zapisano — łączenie…",mqfail:"błąd",connected:"połączono",notconn:"włączone, brak połączenia",disabled:"wyłączone",up:"działa",disconnected:"rozłączono — ponawianie…",alarm:"Alarm",operational:"Sprawny",state:"Stan",link:"Łącze",livev:"online",offline:"offline",soc:"SOC",charging:"ładowanie",discharging:"rozładow.",idle:"bezczynny",voltage:"napięcie",curr:"prąd",mosfet:"MOSFET",sensor:"Czujnik",capacity:"Pojemność",totalenergy:"Energia całk.",cycles:"Cykle",health:"Kondycja",uptime:"Czas pracy",balcur:"Prąd balansu",peakchg:"Szczyt ład.",peakdis:"Szczyt rozł.",chg24:"Naład. 24h",used24:"Zużyte 24h",chg6:"Naład. 6h",used6:"Zużyte 6h",chgmos:"MOSFET ład.",dismos:"MOSFET rozł.",balancer:"Balanser",on:"WŁ",off:"WYŁ",noset:"ustawienia niezaładowane (BMS offline?)",today:"Dziś",tomorrow:"Jutro",indays:"Za {n} dni",wxnone:"brak danych — wymaga internetu",newval:"Nowa wartość dla",writefail:"błąd zapisu"},
pt:{bat:"Bateria",bat1:"Bateria 1",status:"Estado",live:"Ao vivo",weather:"Tempo",cells:"Células",temps:"Temperaturas",session:"Sessão",controls:"Controlos",devscreen:"Ecrã do dispositivo",settings:"Definições",fwupdate:"Atualização",security:"Segurança",tapedit:"(toque para editar)",refresh:"Atualizar",flash:"Enviar & gravar",save:"Guardar",chgpw:"Alterar palavra-passe",newpw:"nova palavra-passe",broker:"Host do broker",port:"Porta",user:"Utilizador",pass:"Palavra-passe",enabled:"Ativado",optional:"opcional",unchanged:"(inalterado)",loading:"a carregar…",retrying:"a repetir…",loadfail:"falhou — toque Atualizar",current:"atual",pickbin:"escolher um .bin",rebooting:"OK — a reiniciar…",failed:"falhou",pwmin:"senha mín 4 caracteres",pwok:"alterada — entre de novo",pwfail:"falhou",mqsaved:"guardado — a ligar…",mqfail:"falhou",connected:"ligado",notconn:"ativo, sem ligação",disabled:"desativado",up:"ativo",disconnected:"desligado — a repetir…",alarm:"Alarme",operational:"Operacional",state:"Estado",link:"Ligação",livev:"online",offline:"offline",soc:"SOC",charging:"a carregar",discharging:"a descarregar",idle:"inativo",voltage:"tensão",curr:"corrente",mosfet:"MOSFET",sensor:"Sensor",capacity:"Capacidade",totalenergy:"Energia total",cycles:"Ciclos",health:"Saúde",uptime:"Tempo ativo",balcur:"Corrente equil.",peakchg:"Pico carga",peakdis:"Pico descarga",chg24:"Carregado 24h",used24:"Usado 24h",chg6:"Carregado 6h",used6:"Usado 6h",chgmos:"MOSFET carga",dismos:"MOSFET descarga",balancer:"Equalizador",on:"LIG",off:"DESL",noset:"definições não carregadas (BMS offline?)",today:"Hoje",tomorrow:"Amanhã",indays:"Em {n} dias",wxnone:"sem dados — precisa de internet",newval:"Novo valor para",writefail:"falha de escrita"},
es:{bat:"Batería",bat1:"Batería 1",status:"Estado",live:"En vivo",weather:"Clima",cells:"Celdas",temps:"Temperaturas",session:"Sesión",controls:"Controles",devscreen:"Pantalla del dispositivo",settings:"Ajustes",fwupdate:"Actualización",security:"Seguridad",tapedit:"(toca para editar)",refresh:"Actualizar",flash:"Subir y flashear",save:"Guardar",chgpw:"Cambiar contraseña",newpw:"nueva contraseña",broker:"Host del broker",port:"Puerto",user:"Usuario",pass:"Contraseña",enabled:"Activado",optional:"opcional",unchanged:"(sin cambios)",loading:"cargando…",retrying:"reintentando…",loadfail:"falló — toca Actualizar",current:"actual",pickbin:"elige un .bin",rebooting:"OK — reiniciando…",failed:"falló",pwmin:"contraseña mín 4 caracteres",pwok:"cambiada — inicia sesión otra vez",pwfail:"falló",mqsaved:"guardado — conectando…",mqfail:"falló",connected:"conectado",notconn:"activo, sin conexión",disabled:"desactivado",up:"activo",disconnected:"desconectado — reintentando…",alarm:"Alarma",operational:"Operativo",state:"Estado",link:"Enlace",livev:"en línea",offline:"sin conexión",soc:"SOC",charging:"cargando",discharging:"descargando",idle:"inactivo",voltage:"tensión",curr:"corriente",mosfet:"MOSFET",sensor:"Sensor",capacity:"Capacidad",totalenergy:"Energía total",cycles:"Ciclos",health:"Salud",uptime:"Tiempo activo",balcur:"Corriente balance",peakchg:"Pico carga",peakdis:"Pico descarga",chg24:"Cargado 24h",used24:"Usado 24h",chg6:"Cargado 6h",used6:"Usado 6h",chgmos:"MOSFET carga",dismos:"MOSFET descarga",balancer:"Balanceador",on:"SÍ",off:"NO",noset:"ajustes no cargados (¿BMS sin conexión?)",today:"Hoy",tomorrow:"Mañana",indays:"En {n} días",wxnone:"sin datos — requiere internet",newval:"Nuevo valor para",writefail:"error de escritura"},
vi:{bat:"Pin",bat1:"Pin 1",status:"Trạng thái",live:"Trực tiếp",weather:"Thời tiết",cells:"Ô pin",temps:"Nhiệt độ",session:"Phiên",controls:"Điều khiển",devscreen:"Màn hình thiết bị",settings:"Cài đặt",fwupdate:"Cập nhật firmware",security:"Bảo mật",tapedit:"(chạm để sửa)",refresh:"Làm mới",flash:"Tải lên & nạp",save:"Lưu",chgpw:"Đổi mật khẩu",newpw:"mật khẩu mới",broker:"Máy chủ broker",port:"Cổng",user:"Tên đăng nhập",pass:"Mật khẩu",enabled:"Bật",optional:"tùy chọn",unchanged:"(không đổi)",loading:"đang tải…",retrying:"thử lại…",loadfail:"lỗi — chạm Làm mới",current:"hiện tại",pickbin:"chọn tệp .bin",rebooting:"OK — đang khởi động lại…",failed:"lỗi",pwmin:"mật khẩu tối thiểu 4 ký tự",pwok:"đã đổi — đăng nhập lại",pwfail:"lỗi",mqsaved:"đã lưu — đang kết nối…",mqfail:"lỗi",connected:"đã kết nối",notconn:"bật, chưa kết nối",disabled:"tắt",up:"hoạt động",disconnected:"mất kết nối — thử lại…",alarm:"Báo động",operational:"Hoạt động tốt",state:"Trạng thái",link:"Kết nối",livev:"trực tuyến",offline:"ngoại tuyến",soc:"SOC",charging:"đang sạc",discharging:"đang xả",idle:"nghỉ",voltage:"điện áp",curr:"dòng điện",mosfet:"MOSFET",sensor:"Cảm biến",capacity:"Dung lượng",totalenergy:"Tổng năng lượng",cycles:"Chu kỳ",health:"Sức khỏe",uptime:"Thời gian chạy",balcur:"Dòng cân bằng",peakchg:"Đỉnh sạc",peakdis:"Đỉnh xả",chg24:"Sạc 24h",used24:"Dùng 24h",chg6:"Sạc 6h",used6:"Dùng 6h",chgmos:"MOSFET sạc",dismos:"MOSFET xả",balancer:"Bộ cân bằng",on:"BẬT",off:"TẮT",noset:"chưa tải cài đặt (BMS ngoại tuyến?)",today:"Hôm nay",tomorrow:"Ngày mai",indays:"Sau {n} ngày",wxnone:"không có dữ liệu — cần internet",newval:"Giá trị mới cho",writefail:"ghi thất bại"},
ru:{bat:"Батарея",bat1:"Батарея 1",status:"Статус",live:"Вживую",weather:"Погода",cells:"Ячейки",temps:"Температуры",session:"Сессия",controls:"Управление",devscreen:"Экран устройства",settings:"Настройки",fwupdate:"Обновление ПО",security:"Безопасность",tapedit:"(нажмите для изменения)",refresh:"Обновить",flash:"Загрузить и прошить",save:"Сохранить",chgpw:"Сменить пароль",newpw:"новый пароль",broker:"Хост брокера",port:"Порт",user:"Пользователь",pass:"Пароль",enabled:"Включено",optional:"необязательно",unchanged:"(без изменений)",loading:"загрузка…",retrying:"повтор…",loadfail:"ошибка — нажмите Обновить",current:"текущая",pickbin:"выберите .bin",rebooting:"OK — перезагрузка…",failed:"ошибка",pwmin:"пароль мин 4 символа",pwok:"изменён — войдите снова",pwfail:"ошибка",mqsaved:"сохранено — подключение…",mqfail:"ошибка",connected:"подключено",notconn:"включено, нет связи",disabled:"выключено",up:"работает",disconnected:"отключено — повтор…",alarm:"Тревога",operational:"Исправно",state:"Состояние",link:"Связь",livev:"онлайн",offline:"не в сети",soc:"SOC",charging:"зарядка",discharging:"разрядка",idle:"простой",voltage:"напряжение",curr:"ток",mosfet:"MOSFET",sensor:"Датчик",capacity:"Ёмкость",totalenergy:"Всего энергии",cycles:"Циклы",health:"Здоровье",uptime:"Время работы",balcur:"Ток баланса",peakchg:"Пик заряда",peakdis:"Пик разряда",chg24:"Заряд 24ч",used24:"Расход 24ч",chg6:"Заряд 6ч",used6:"Расход 6ч",chgmos:"MOSFET заряда",dismos:"MOSFET разряда",balancer:"Балансир",on:"ВКЛ",off:"ВЫКЛ",noset:"настройки не загружены (BMS не в сети?)",today:"Сегодня",tomorrow:"Завтра",indays:"Через {n} дн.",wxnone:"нет данных — нужен интернет",newval:"Новое значение для",writefail:"ошибка записи"},
zh:{bat:"电池",bat1:"电池 1",status:"状态",live:"实时",weather:"天气",cells:"电芯",temps:"温度",session:"会话",controls:"控制",devscreen:"设备屏幕",settings:"设置",fwupdate:"固件更新",security:"安全",tapedit:"(点击数值编辑)",refresh:"刷新",flash:"上传并刷写",save:"保存",chgpw:"修改密码",newpw:"新密码",broker:"Broker 主机",port:"端口",user:"用户名",pass:"密码",enabled:"启用",optional:"可选",unchanged:"(不变)",loading:"加载中…",retrying:"重试中…",loadfail:"失败 — 点击刷新",current:"当前",pickbin:"选择 .bin 文件",rebooting:"OK — 设备重启中…",failed:"失败",pwmin:"密码至少 4 位",pwok:"已修改 — 请重新登录",pwfail:"失败",mqsaved:"已保存 — 连接中…",mqfail:"失败",connected:"已连接",notconn:"已启用，未连接",disabled:"已禁用",up:"运行",disconnected:"已断开 — 重试中…",alarm:"报警",operational:"正常",state:"状态",link:"连接",livev:"在线",offline:"离线",soc:"SOC",charging:"充电中",discharging:"放电中",idle:"空闲",voltage:"电压",curr:"电流",mosfet:"MOSFET",sensor:"传感器",capacity:"容量",totalenergy:"总能量",cycles:"循环",health:"健康度",uptime:"运行时间",balcur:"均衡电流",peakchg:"峰值充电",peakdis:"峰值放电",chg24:"24小时充电",used24:"24小时用电",chg6:"6小时充电",used6:"6小时用电",chgmos:"充电MOSFET",dismos:"放电MOSFET",balancer:"均衡器",on:"开",off:"关",noset:"设置未加载（BMS离线？）",today:"今天",tomorrow:"明天",indays:"{n}天后",wxnone:"无数据 — 需要联网",newval:"新值：",writefail:"写入失败"}};
const LNAMES={en:"English",fr:"Français",de:"Deutsch",nl:"Nederlands",pl:"Polski",pt:"Português",es:"Español",vi:"Tiếng Việt",ru:"Русский",zh:"中文"};
let L=localStorage.getItem('lang')||(navigator.language||'en').slice(0,2).toLowerCase();if(!I18N[L])L='en';
function t(k){return (I18N[L]&&I18N[L][k])||I18N.en[k]||k}
function applyI18n(){document.documentElement.lang=L;
 document.querySelectorAll('[data-i18n]').forEach(e=>e.textContent=t(e.dataset.i18n));
 document.querySelectorAll('[data-ph]').forEach(e=>e.placeholder=t(e.dataset.ph));}
let cur=0,D={},shotBusy=false,mqInit=false,scrInit=false,alInit=false,auInit=false,HIST=null;
function esc(s){return String(s).replace(/[<>&"']/g,c=>({'<':'&lt;','>':'&gt;','&':'&amp;','"':'&quot;',"'":'&#39;'}[c]))}
function sel(b){cur=b;t0.className='tab'+(b==0?' on':'');t1.className='tab'+(b==1?' on':'');render();drawHist()}
function chart(cv,arr,o){let dpr=window.devicePixelRatio||1,w=cv.clientWidth,h=cv.clientHeight;cv.width=w*dpr;cv.height=h*dpr;
 let x=cv.getContext('2d');x.setTransform(dpr,0,0,dpr,0,0);x.clearRect(0,0,w,h);
 if(!arr||arr.length<2){x.fillStyle='#8593a4';x.font='11px system-ui';x.textBaseline='middle';x.fillText(t('loading'),24,h/2);return}
 let mn=o.min,mx=o.max;
 if(mn==null){mn=Math.min(...arr);mx=Math.max(...arr);if(o.zero){mn=Math.min(mn,0);mx=Math.max(mx,0)}let p=(mx-mn)*0.12||1;mn-=p;mx+=p}
 if(mx-mn<1)mx=mn+1;
 let gx=26,gy=4,gw=w-gx-4,gh=h-12,yOf=v=>gy+gh-(v-mn)/(mx-mn)*gh;
 x.fillStyle='#8593a4';x.font='9px system-ui';x.textBaseline='middle';
 x.fillText(Math.round(mx),2,yOf(mx));x.fillText(Math.round(mn),2,yOf(mn));
 if(o.zero&&mn<0&&mx>0){let zy=yOf(0);x.strokeStyle='rgba(255,255,255,.12)';x.lineWidth=1;x.beginPath();x.moveTo(gx,zy);x.lineTo(gx+gw,zy);x.stroke()}
 x.beginPath();arr.forEach((v,i)=>{let px=gx+i/(arr.length-1)*gw,py=yOf(v);i?x.lineTo(px,py):x.moveTo(px,py)});
 x.strokeStyle=o.color;x.lineWidth=1.6;x.stroke();
 let bl=yOf(o.zero?0:mn);x.lineTo(gx+gw,bl);x.lineTo(gx,bl);x.closePath();x.fillStyle=o.fill;x.fill()}
function drawHist(){if(!HIST||!HIST.packs)return;let p=HIST.packs[cur];if(!p)return;
 hspan.textContent=(p.span||0).toFixed(1)+'d';
 chart(hsoc,p.soc,{min:0,max:100,color:'#34d399',fill:'rgba(52,211,153,.15)'});
 chart(hpw,p.w,{zero:1,color:'#22d3ee',fill:'rgba(34,211,238,.15)'});
 chart(htmp,p.tmp,{color:'#fbbf24',fill:'rgba(251,191,36,.15)'})}
async function loadHist(){try{HIST=await(await fetch('/history.json')).json();drawHist()}catch(e){}}
async function doupd(){if(!confirm('Download & flash '+(D.updTag||'the latest release')+'? The device will reboot.'))return;ust.textContent='downloading & flashing… device will reboot';await fetch('/selfupdate',{method:'POST'})}
function setaupd(){fetch('/setupd',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'en='+(aupd.checked?1:0)})}
function tc(t){return(t<-50||t>120)?'--':t.toFixed(0)+'°C'}
function wh(w){return Math.abs(w)>=1000?(w/1000).toFixed(2)+'kWh':w.toFixed(0)+'Wh'}
function pc(w,tt){return tt>1?' ('+Math.round(w/tt*100)+'%)':''}
(function initLang(){let s=document.getElementById('lang');
 s.innerHTML=Object.keys(LNAMES).map(k=>`<option value=${k}${k==L?' selected':''}>${LNAMES[k]}</option>`).join('');
 s.onchange=()=>{L=s.value;localStorage.setItem('lang',L);t0.textContent=t('bat')+' 1';t1.textContent=t('bat')+' 2';applyI18n();render()};
 t0.textContent=t('bat')+' 1';t1.textContent=t('bat')+' 2';applyI18n();})();
async function load(){if(shotBusy)return;try{D=await(await fetch('/api')).json();fw.textContent='v'+D.fw+(D.upd?' · ⬆ update available':'');
 net.style.color='';net.textContent=D.ip+' · '+t('up')+' '+Math.floor(D.up/60)+'m';fwv.textContent=t('current')+': v'+D.fw;
 let multi=D.n>1;seg.style.display=multi?'':'none';single.style.display=multi?'none':'';if(!multi)cur=0;if(cur>=D.n)sel(0);
 mqe.checked=!!D.mqEn;mqst.textContent=D.mqEn?(D.mqUp?t('connected')+' ✓':t('notconn')):t('disabled');mqst.className=D.mqUp?'grn':D.mqEn?'amb':'mut';
 if(!mqInit){mqh.value=D.mqHost||'';mqp.value=D.mqPort||1883;mqu.value=D.mqUser||'';mqInit=true}
 if(!alInit){alu.value=D.alUrl||'';als.value=D.alSoc;alt.value=D.alTmp;ald.value=D.alDlt;alInit=true}
 ale.checked=!!D.alEn;alf.checked=!!D.alFlt;
 if(!auInit){aupd.checked=!!D.autoUpd;auInit=true}
 if(D.upd){updrow.style.display='';updmsg.textContent='⬆ '+(D.updTag||'new')+' available'}else updrow.style.display='none';
 render();if(!scrInit){scrInit=true;shot()}}catch(e){net.style.color='var(--bad)';net.textContent=t('disconnected')}}
function wxcat(c){if(c<=0)return 0;if(c<=2)return 1;if(c==3||c==45||c==48)return 2;if((c>=71&&c<=77)||c==85||c==86)return 4;if(c>=95)return 5;return 3}
function wxsvg(c,s){var cat=wxcat(c);
 var cl='<g fill="#aeb8c4"><circle cx="9" cy="13" r="4.2"/><circle cx="14" cy="11" r="5.2"/><circle cx="18" cy="14" r="3.6"/><rect x="8" y="13" width="11" height="5.2" rx="2.6"/></g>';
 var ray='<g stroke="#ffd43b" stroke-width="1.6" stroke-linecap="round"><line x1="12" y1="2.5" x2="12" y2="4.6"/><line x1="12" y1="17.4" x2="12" y2="19.5"/><line x1="2.5" y1="11" x2="4.6" y2="11"/><line x1="19.4" y1="11" x2="21.5" y2="11"/><line x1="5" y1="4" x2="6.5" y2="5.5"/><line x1="17.5" y1="16.5" x2="19" y2="18"/><line x1="19" y1="4" x2="17.5" y2="5.5"/><line x1="6.5" y1="16.5" x2="5" y2="18"/></g>';
 var body;
 if(cat==0)body=ray+'<circle cx="12" cy="11" r="4.6" fill="#ffd43b"/>';
 else if(cat==1)body='<circle cx="8" cy="8" r="3.2" fill="#ffd43b"/><g stroke="#ffd43b" stroke-width="1.4" stroke-linecap="round"><line x1="8" y1="1.6" x2="8" y2="3"/><line x1="1.6" y1="8" x2="3" y2="8"/><line x1="3.4" y1="3.4" x2="4.5" y2="4.5"/><line x1="12.6" y1="3.4" x2="11.5" y2="4.5"/></g>'+cl;
 else if(cat==2)body=cl;
 else if(cat==3)body=cl+'<g stroke="#4aa3ff" stroke-width="1.8" stroke-linecap="round"><line x1="9" y1="19" x2="8" y2="22.5"/><line x1="13" y1="19" x2="12" y2="22.5"/><line x1="17" y1="19" x2="16" y2="22.5"/></g>';
 else if(cat==4)body=cl+'<g fill="#cfe6ff"><circle cx="9" cy="21.5" r="1.2"/><circle cx="13" cy="21.5" r="1.2"/><circle cx="17" cy="21.5" r="1.2"/></g>';
 else body=cl+'<polygon points="13,18 9.5,22.5 12,22.5 10.5,25.5 16,20 13,20" fill="#ffd43b"/>';
 return '<svg width="'+s+'" height="'+s+'" viewBox="0 0 24 26" style="vertical-align:middle">'+body+'</svg>'}
function renderWx(){if(!D.wxOk){wx.innerHTML='<div class=mut>'+t('wxnone')+'</div>';wxc.textContent='';return}
 wxc.textContent=(D.wxCity||'')+(D.wxStale?' · stale':'');
 let rows=(D.wxD||[]).map((d,i)=>`<div class=row><span>${wxsvg(d.c,24)} ${i==0?t('today'):i==1?t('tomorrow'):t('indays').replace('{n}',i)}</span><b>${d.mx}° / ${d.mn}°</b></div>`).join('');
 wx.innerHTML=`<div class=row><span class=big>${D.wxT}°</span>${wxsvg(D.wxC,46)}</div>${rows}`}
function render(){renderWx();if(!D.packs)return;let p=D.packs[cur];
 let op=p.err>0?['⚠ '+t('alarm'),'red']:['✓ '+t('operational'),'grn'];
 let alarms=(p.al&&p.al.length)?`<div style=margin-top:6px>${p.al.map(a=>`<div class=red>• ${esc(a)}</div>`).join('')}</div>`:'';
 stat.innerHTML=`<div class="big ${op[1]}">${op[0]}</div>${alarms}
  <div class=row style=margin-top:6px><span class=mut>${t('state')}</span><span class=pill>${p.st}</span></div>
  <div class=row><span class=mut>${t('link')}</span><span class=${p.live?'grn':'mut'}>${p.live?t('livev'):t('offline')}</span></div>`;
 let cc=p.i>0.5?'grn':p.i<-0.5?'vio':'mut';
 met.innerHTML=`<div><div class=big>${p.soc.toFixed(0)}%</div><div class=mut>${t('soc')}</div></div>
  <div><div class="v ${cc}">${p.w.toFixed(0)} W</div><div class=mut>${p.i>0.5?t('charging'):p.i<-0.5?t('discharging'):t('idle')}</div></div>
  <div><div class=v>${p.v.toFixed(2)} V</div><div class=mut>${t('voltage')}</div></div>
  <div><div class="v ${cc}">${Math.abs(p.i).toFixed(1)} A</div><div class=mut>${t('curr')}</div></div>`;
 let hc=p.cells&&p.cells.length>0;
 let mn=hc?Math.min(...p.cells):0,mx=hc?Math.max(...p.cells):0,mnI=hc?p.cells.indexOf(mn)+1:0,mxI=hc?p.cells.indexOf(mx)+1:0;
 cd.innerHTML=hc?('Δ '+((mx-mn)*1000).toFixed(0)+' mV · <span class=cy>↓C'+mnI+'</span> <span class=amb>↑C'+mxI+'</span>'+(p.balw?' · <span class=cy>⚖ '+t('balancing')+'</span>':'')):'—';
 cells.innerHTML=p.cells.map((c,i)=>`<div class="cell${c==mx?' hi':c==mn?' lo':''}">C${i+1}<br><b>${c.toFixed(3)}</b>${(p.res&&p.res[i]!=null)?`<br><span class=mut>${p.res[i].toFixed(2)} mΩ</span>`:''}</div>`).join('');
 temps.innerHTML=[[t('mosfet'),p.tmos],[t('sensor')+' 1',p.t1],[t('sensor')+' 2',p.t2]]
  .map(([n,v])=>`<div class=row><span class=mut>${n}</span><b>${tc(v)}</b></div>`).join('');
 let srows=[[t('capacity'),p.cap.toFixed(0)+' Ah'],[t('totalenergy'),wh(p.twh)],
  [t('echg'),(p.ein||0).toFixed(1)+' kWh'],[t('edis'),(p.eout||0).toFixed(1)+' kWh'],
  [t('cycles'),p.cyc],[t('health'),p.soh+'%'+(p.ret!=null?' · '+p.ret+'% cap':'')],
  [t('uptime'),(p.up_s/3600).toFixed(0)+' h'],[t('balcur'),(p.bcur||0).toFixed(2)+' A'],
  [t('peakchg'),p.pkc.toFixed(0)+' W'],[t('peakdis'),p.pkd.toFixed(0)+' W'],
  [t('chg24'),wh(p.c24||0)],[t('used24'),wh(p.u24)+pc(p.u24,p.twh)],
  [t('chg6'),wh(p.c6||0)],[t('used6'),wh(p.u6)+pc(p.u6,p.twh)]]
  .map(([n,v])=>`<div class=row><span class=mut>${n}</span><b>${v}</b></div>`).join('');
 // capacity-fade sparkline (monthly points). Flat line if the BMS reports a static rated capacity.
 let sh=p.sohH||[],spk='';
 if(sh.length>=2){let cs=sh.map(x=>x.c),lo=Math.min(...cs),hi=Math.max(...cs),rg=(hi-lo)||1;
  let pts=cs.map((c,i)=>`${(i/(cs.length-1)*100).toFixed(1)},${(28-(c-lo)/rg*26).toFixed(1)}`).join(' ');
  spk=`<div class=row style=margin-top:8px><span class=mut>${t('health')} ↗</span><span class=mut>${cs[0].toFixed(0)}→${cs[cs.length-1].toFixed(0)} Ah</span></div>`+
   `<svg width=100% height=34 viewBox="0 0 100 30" preserveAspectRatio=none style=display:block><polyline points="${pts}" fill=none stroke=#4aa3ff stroke-width=1.2 vector-effect=non-scaling-stroke/></svg>`;}
 sess.innerHTML=srows+spk;
 ctl.innerHTML=[['chg',t('chgmos'),p.chg],['dis',t('dismos'),p.dis],['bal',t('balancer'),p.bal]]
  .map(([k,n,v])=>`<div class=row><span>${n}</span><button class="sm ${v?'':'off'}" onclick="tog('${k}')">${v?t('on'):t('off')}</button></div>`).join('');
 let ps=D.params&&D.params[cur]||[];
 params.innerHTML=ps.map(s=>`<tr><td>${esc(s.l)}</td><td style=text-align:right;cursor:pointer onclick="ed(${s.i})"><b>${esc(s.v)}</b></td></tr>`).join('')
  ||'<tr><td class=mut>'+t('noset')+'</td></tr>';}
async function tog(k){await fetch('/toggle?bms='+cur+'&which='+k,{method:'POST'});setTimeout(load,500)}
async function ed(i){let s=(D.params[cur]||[]).find(x=>x.i==i);if(!s)return;
 let v=prompt(t('newval')+' '+s.l,s.v);if(v===null||v==='')return;
 let r=await fetch('/setparam?bms='+cur+'&idx='+i+'&val='+encodeURIComponent(v),{method:'POST'});
 if(!r.ok)alert(t('writefail'));setTimeout(load,600)}
async function chpw(){if(np.value.length<4){ust.textContent=t('pwmin');return}
 let r=await fetch('/setpass',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'p='+encodeURIComponent(np.value)});
 np.value='';ust.textContent=r.ok?t('pwok'):t('pwfail')}
async function savemq(){let b='en='+(mqe.checked?1:0)+'&host='+encodeURIComponent(mqh.value)+'&port='+(mqp.value||1883)+'&user='+encodeURIComponent(mqu.value)+'&pass='+encodeURIComponent(mqpw.value);
 let r=await fetch('/setmqtt',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:b});mqpw.value='';mqst.textContent=r.ok?t('mqsaved'):t('mqfail')}
async function saveal(){let b='en='+(ale.checked?1:0)+'&flt='+(alf.checked?1:0)+'&url='+encodeURIComponent(alu.value)+'&soc='+(als.value||15)+'&tmp='+(alt.value||55)+'&dlt='+(ald.value||300);
 let r=await fetch('/setalert',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:b});alst.textContent=r.ok?t('alsaved'):t('mqfail');return r.ok}
async function testal(){if(!await saveal())return;let r=await fetch('/testalert',{method:'POST'});alst.textContent=r.ok?t('altestok'):t('altestfail')}
function shot(retry){if(shotBusy&&!retry)return;shotBusy=true;scrld.style.display='block';scrh.style.display='none';
 scr.onload=()=>{shotBusy=false;scrld.style.display='none';scr.style.display='block'};
 scr.onerror=()=>{shotBusy=false;
   if(!retry){scrh.textContent=t('retrying');scrh.style.display='inline';setTimeout(()=>shot(1),800);return}  // JPEG can truncate under load → one auto-retry
   scrld.style.display='none';scrh.textContent=t('loadfail');scrh.style.display='inline'};
 scr.src='/screen.jpg?t='+Date.now()}
function upl(){let f=fwf.files[0];if(!f){ust.textContent=t('pickbin');return}
 let x=new XMLHttpRequest();x.open('POST','/update');prog.style.display='block';
 x.upload.onprogress=e=>{pb.style.width=(e.loaded/e.total*100)+'%'};
 x.onload=()=>{ust.textContent=x.status==200?t('rebooting'):t('failed')+': '+x.responseText};
 let fd=new FormData();fd.append('f',f);x.send(fd)}
load();setInterval(load,2000);   // /api every 2s; the JPEG snapshot auto-loads once then on Refresh
aupd.onchange=setaupd;
loadHist();setInterval(loadHist,60000);   // 7-day history charts (changes every 5min; refetch each minute)
window.addEventListener('resize',drawHist);
</script></body></html>)HTML";

// Minimal JSON string escaper for free-text values (host/user/URL/city) that could
// contain a quote/backslash/control char and otherwise break JSON.parse on the client.
static String jesc(const char *s) {
    String o; for (; *s; s++) {
        char c = *s;
        if (c == '"' || c == '\\') { o += '\\'; o += c; }
        else if ((uint8_t)c < 0x20) { char b[8]; snprintf(b, sizeof(b), "\\u%04x", c); o += b; }
        else o += c;
    }
    return o;
}
// ---- JSON state ----
static String webJson() {
    String j; j.reserve(6500);   // one allocation; avoids a realloc cascade from the +='s below
    char clk[12] = "--:--:--"; { struct tm ti; if (getLocalTime(&ti, 0)) snprintf(clk, sizeof(clk), "%02d:%02d:%02d", ti.tm_hour, ti.tm_min, ti.tm_sec); }
    j = "{\"fw\":\"" FW_VERSION "\",\"ip\":\"" + WiFi.localIP().toString() +
        "\",\"up\":" + String(millis() / 1000) + ",\"clk\":\"" + clk + "\",\"tsync\":" + String(timeSynced ? 1 : 0) +
        ",\"heap\":" + String((unsigned long)ESP.getFreeHeap()) + ",\"heapBig\":" + String((unsigned long)heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL)) + ",\"n\":" + String(numBms) +
        ",\"flushUs\":" + String((unsigned long)g_flushUs) + ",\"fps\":" + String((unsigned long)g_fps) +
        ",\"upd\":" + String(updAvail ? 1 : 0) + ",\"updTag\":\"" + jesc(updTag) + "\",\"autoUpd\":" + String(autoUpdate ? 1 : 0) + ",\"updProg\":" + String(updProgress) +
        ",\"mqEn\":" + String(mqttEnabled ? 1 : 0) + ",\"mqUp\":" + String(mqttUp ? 1 : 0) +
        ",\"mqHost\":\"" + jesc(mqttHost) + "\",\"mqPort\":" + String(mqttPort) + ",\"mqUser\":\"" + jesc(mqttUser) + "\"" +
        ",\"alEn\":" + String(alertEnabled ? 1 : 0) + ",\"alUrl\":\"" + jesc(alertUrl) + "\"" +
        ",\"alSoc\":" + String(alSocLo) + ",\"alTmp\":" + String(alTempHi) + ",\"alDlt\":" + String(alDeltaHi) + ",\"alFlt\":" + String(alOnFault ? 1 : 0) +
        ",\"wxOk\":" + String(wxOk ? 1 : 0) + ",\"wxStale\":" + String(wxStale() ? 1 : 0) + ",\"wxHttp\":" + String(wxHttp) + ",\"wxCity\":\"" + jesc(wxCity) + "\",\"wxT\":" + String(wxCurTemp) + ",\"wxC\":" + String(wxCurCode) + ",\"wxD\":[";
    for (int i = 0; i < wxDays; i++) { if (i) j += ","; j += "{\"c\":" + String(wxDay[i].code) + ",\"mx\":" + String(wxDay[i].tmax) + ",\"mn\":" + String(wxDay[i].tmin) + "}"; }
    j += "],\"packs\":[";
    for (int t = 0; t < numBms; t++) {
        const Bms &b = bms[t];
        bool live = demoMode || bmsLive[t];
        uint32_t sc; const char *st = bmsStatusStr(t, live, &sc);   // same real-BMS-state helper as the device UI
        float fullAh = (!demoMode && bmsLive[t]) ? packFullAh[t] : PACK_AH;
        if (t) j += ",";
        j += "{\"live\":" + String(live ? 1 : 0) + ",\"soc\":" + String(b.soc, 0) +
             ",\"v\":" + String(b.v, 2) + ",\"i\":" + String(b.i, 1) +
             ",\"w\":" + String(b.v * b.i, 0) + ",\"tmos\":" + String(b.tMos, 0) +
             ",\"t1\":" + String(b.tp1, 0) + ",\"t2\":" + String(b.tp2, 0) +
             ",\"cap\":" + String(fullAh, 0) + ",\"chg\":" + String(bmsCharge[t] ? 1 : 0) +
             ",\"dis\":" + String(bmsDischarge[t] ? 1 : 0) + ",\"bal\":" + String(bmsBalancer[t] ? 1 : 0) +
             ",\"ok\":" + String(b.bmsOk ? 1 : 0) + ",\"st\":\"" + st + "\"" +
             ",\"cyc\":" + String(b.cycles) + ",\"soh\":" + String(b.soh) +
             ",\"up_s\":" + String(b.uptimeOk ? b.uptime : 0) + ",\"err\":" + String(b.errFlags) +
             ",\"cAtt\":" + String(commAttempts[t]) + ",\"cOk\":" + String(commOk[t]) +
             ",\"cFail\":" + String(commConsecFail[t]) + ",\"cRcn\":" + String(commReconnects[t]) + ",\"cErr\":" + String(commLastErr[t]) +
             ",\"pkc\":" + String(b.peakChg, 0) + ",\"pkd\":" + String(b.peakDis, 0) +
             ",\"twh\":" + String(packTotalWh(t), 0) + ",\"bcur\":" + String(b.balCur, 2) +
             ",\"balw\":" + String(b.balWork ? 1 : 0) +
             ",\"ein\":" + String((double)(lifeWhIn[t] / 1000.0), 3) + ",\"eout\":" + String((double)(lifeWhOut[t] / 1000.0), 3) +
             ",\"u24\":" + String(whSpent(t, 288), 0) + ",\"u6\":" + String(whSpent(t, 72), 0) +
             ",\"c24\":" + String(whGained(t, 288), 0) + ",\"c6\":" + String(whGained(t, 72), 0) +
             ",\"cells\":[";
        for (int i = 0; i < b.nCells; i++) { if (i) j += ","; j += String(b.cell[i], 3); }
        j += "],\"res\":[";
        for (int i = 0; i < b.nCells; i++) { if (i) j += ","; j += String(b.cellRes[i], 2); }
        j += "],\"al\":[";
        int na = 0;
        for (int bit = 0; bit < NERR; bit++)
            if (((b.errFlags >> bit) & 1u) && ERR_NAMES[bit][0]) { if (na++) j += ","; j += "\""; j += ERR_NAMES[bit]; j += "\""; }
        // capacity-fade trend: baseline ("as new"), retention %, and the monthly history points
        int ret = sohBaseAh[t] > 1 ? (int)(100.0f * fullAh / sohBaseAh[t] + 0.5f) : 100;
        j += "],\"capBase\":" + String(sohBaseAh[t], 0) + ",\"ret\":" + String(ret) + ",\"sohH\":[";
        for (int s = 0; s < sohCount[t]; s++) { if (s) j += ",";
            j += "{\"m\":" + String(sohHist[t][s].mon) + ",\"c\":" + String(sohHist[t][s].capX10 / 10.0f, 1) +
                 ",\"s\":" + String(sohHist[t][s].soh) + ",\"y\":" + String(sohHist[t][s].cyc) + "}"; }
        j += "]}";
    }
    j += "],\"params\":[";
    for (int t = 0; t < numBms; t++) {
        if (t) j += ",";
        j += "[";
        bool avail = (!demoMode && bmsLive[t] && setOk[t]);
        if (avail) for (int i = 0; i < NSET; i++) {
            char v[16]; fmtSetting(v, sizeof(v), SETDEFS[i], setGet(t, SETDEFS[i]));
            if (i) j += ",";
            j += "{\"i\":" + String(i) + ",\"l\":\"" + SETDEFS[i].label + "\",\"v\":\"" + v + "\"}";
        }
        j += "]";
    }
    j += "]}";
    return j;
}

// WiFiClient.write() can do partial sends when the TCP buffer is full; loop until all sent
static void clientWriteAll(WiFiClient &c, const uint8_t *p, size_t n) {
    size_t sent = 0; uint32_t t0 = millis();
    while (sent < n && c.connected()) {
        size_t w = c.write(p + sent, n - sent);
        if (w) { sent += w; t0 = millis(); }
        else { if (millis() - t0 > 3000) break; delay(1); }
    }
}
// Stream the live LVGL framebuffer as a JPEG (~20-30KB vs the old 460KB BMP → far
// faster, no truncation). The canvas is rotated/column-major: landscape pixel (lx,ly)
// lives at fb[lx*Ht + (Ht-1-ly)], so de-rotate into a row-major RGB565 buffer first.
// Both scratch buffers live in PSRAM; JPEGENC is static (its state struct is large).
static JPEGENC jpgEnc;
static void handleScreen() {
    if (!webAuth()) return;
    const uint16_t *fb = gfx->getFramebuffer();
    if (!fb) { webServer.send(500, "text/plain", "no framebuffer"); return; }
    const int W = Wd, H = Ht;
    uint16_t *land = (uint16_t *)ps_malloc((size_t)W * H * 2);   // de-rotated row-major landscape
    const int outCap = 96 * 1024;
    uint8_t *out = (uint8_t *)ps_malloc(outCap);
    if (!land || !out) { free(land); free(out); webServer.send(500, "text/plain", "oom"); return; }
    for (int ly = 0; ly < H; ly++) {
        uint16_t *d = land + (size_t)ly * W;
        for (int lx = 0; lx < W; lx++) d[lx] = fb[(int32_t)lx * H + (H - 1 - ly)];
    }
    JPEGENCODE jpe; int sz = 0;
    if (jpgEnc.open(out, outCap) == JPEGE_SUCCESS) {
        if (jpgEnc.encodeBegin(&jpe, W, H, JPEGE_PIXEL_RGB565, JPEGE_SUBSAMPLE_420, JPEGE_Q_HIGH) == JPEGE_SUCCESS)
            jpgEnc.addFrame(&jpe, (uint8_t *)land, W * 2);
        sz = jpgEnc.close();
    }
    free(land);
    if (sz <= 0) { free(out); webServer.send(500, "text/plain", "encode failed"); return; }
    webServer.setContentLength(sz);
    webServer.send(200, "image/jpeg", "");
    WiFiClient client = webServer.client();
    WiFi.setSleep(false);                  // modem-sleep latency can stall the stream; disable while sending
    clientWriteAll(client, out, (size_t)sz);
    if (!otaActive) WiFi.setSleep(true);   // don't re-enable sleep if an OTA just started mid-send
    free(out);
}

// Prometheus / OpenMetrics text exposition for Grafana/InfluxDB scraping. TELEMETRY ONLY —
// no credentials, SSID or MQTT user — so it is served UNAUTHENTICATED on the trusted LAN.
// (This portal authenticates with HTTP Digest, which Prometheus can't scrape; exposing a
// read-only numeric metrics endpoint unauthenticated is the node_exporter convention.)
static String webMetrics() {
    String m; m.reserve(3072);
    auto g = [&](const char *name, const char *help, double v) {   // one global gauge (HELP+TYPE+sample)
        m += "# HELP "; m += name; m += ' '; m += help; m += "\n# TYPE "; m += name; m += " gauge\n";
        m += name; m += ' '; m += String(v, 3); m += '\n';
    };
    g("jkbms_uptime_seconds", "Device uptime in seconds", millis() / 1000.0);
    g("jkbms_heap_free_bytes", "Free internal heap", (double)ESP.getFreeHeap());
    g("jkbms_fps", "UI render frames per second", (double)g_fps);
    if (WiFi.status() == WL_CONNECTED) g("jkbms_wifi_rssi_dbm", "WiFi RSSI", (double)WiFi.RSSI());
    if (wxOk) g("jkbms_weather_temp_celsius", "Outdoor temperature", (double)wxCurTemp);
    m += "# HELP jkbms_info Build info (constant 1)\n# TYPE jkbms_info gauge\n";
    m += "jkbms_info{version=\""; m += FW_VERSION; m += "\",board=\"JC3248W535\"} 1\n";

    // Per-pack families: HELP/TYPE once, then one sample per pack (label pack="1"/"2").
    auto fam = [&](const char *name, const char *help, const char *type) {
        m += "# HELP "; m += name; m += ' '; m += help; m += "\n# TYPE "; m += name; m += ' '; m += type; m += '\n';
    };
    auto smp = [&](const char *name, int t, double v) {
        m += name; m += "{pack=\""; m += String(t + 1); m += "\"} "; m += String(v, 3); m += '\n';
    };
    fam("jkbms_pack_live", "BMS answered Modbus this poll (1/0)", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_pack_live", t, (demoMode || bmsLive[t]) ? 1 : 0);
    fam("jkbms_soc_percent", "State of charge %", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_soc_percent", t, bms[t].soc);
    fam("jkbms_voltage_volts", "Pack voltage", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_voltage_volts", t, bms[t].v);
    fam("jkbms_current_amps", "Pack current (+charge/-discharge)", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_current_amps", t, bms[t].i);
    fam("jkbms_power_watts", "Pack power (+charge/-discharge)", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_power_watts", t, bms[t].v * bms[t].i);
    fam("jkbms_soh_percent", "State of health %", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_soh_percent", t, bms[t].soh);
    fam("jkbms_capacity_ah", "Full-charge capacity (Ah)", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_capacity_ah", t, (!demoMode && bmsLive[t]) ? packFullAh[t] : PACK_AH);
    fam("jkbms_capacity_baseline_ah", "First recorded ('as new') capacity (Ah)", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_capacity_baseline_ah", t, sohBaseAh[t]);
    fam("jkbms_capacity_retention_percent", "Current capacity vs 'as new'", "gauge");
    for (int t = 0; t < numBms; t++) {
        double now = (!demoMode && bmsLive[t]) ? packFullAh[t] : PACK_AH;
        smp("jkbms_capacity_retention_percent", t, sohBaseAh[t] > 1 ? 100.0 * now / sohBaseAh[t] : 100.0);
    }
    fam("jkbms_cell_delta_volts", "Max-min cell voltage spread", "gauge");
    for (int t = 0; t < numBms; t++) {
        float mn = 9, mx = 0; for (int i = 0; i < bms[t].nCells; i++) { float c = bms[t].cell[i]; if (c < mn) mn = c; if (c > mx) mx = c; }
        smp("jkbms_cell_delta_volts", t, bms[t].nCells > 0 ? (mx - mn) : 0);
    }
    fam("jkbms_errflags", "BMS protection/warning bitmask", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_errflags", t, (double)bms[t].errFlags);
    fam("jkbms_cycles_total", "Charge cycle count", "counter");
    for (int t = 0; t < numBms; t++) smp("jkbms_cycles_total", t, (double)bms[t].cycles);
    fam("jkbms_energy_in_kwh_total", "Lifetime energy charged", "counter");
    for (int t = 0; t < numBms; t++) smp("jkbms_energy_in_kwh_total", t, lifeWhIn[t] / 1000.0);
    fam("jkbms_energy_out_kwh_total", "Lifetime energy discharged", "counter");
    for (int t = 0; t < numBms; t++) smp("jkbms_energy_out_kwh_total", t, lifeWhOut[t] / 1000.0);
    // Comms health
    fam("jkbms_comm_attempts_total", "Modbus poll attempts", "counter");
    for (int t = 0; t < numBms; t++) smp("jkbms_comm_attempts_total", t, (double)commAttempts[t]);
    fam("jkbms_comm_ok_total", "Modbus polls with a valid reply", "counter");
    for (int t = 0; t < numBms; t++) smp("jkbms_comm_ok_total", t, (double)commOk[t]);
    fam("jkbms_comm_consec_fail", "Current consecutive read-failure streak", "gauge");
    for (int t = 0; t < numBms; t++) smp("jkbms_comm_consec_fail", t, (double)commConsecFail[t]);
    fam("jkbms_comm_reconnects_total", "Offline->online transitions", "counter");
    for (int t = 0; t < numBms; t++) smp("jkbms_comm_reconnects_total", t, (double)commReconnects[t]);
    // Temperatures (sensor label) + per-cell voltages (cell label)
    fam("jkbms_temp_celsius", "Temperatures by sensor", "gauge");
    for (int t = 0; t < numBms; t++) {
        m += "jkbms_temp_celsius{pack=\"" + String(t + 1) + "\",sensor=\"mos\"} " + String(bms[t].tMos, 1) + '\n';
        m += "jkbms_temp_celsius{pack=\"" + String(t + 1) + "\",sensor=\"t1\"} " + String(bms[t].tp1, 1) + '\n';
        m += "jkbms_temp_celsius{pack=\"" + String(t + 1) + "\",sensor=\"t2\"} " + String(bms[t].tp2, 1) + '\n';
    }
    fam("jkbms_cell_volts", "Per-cell voltage", "gauge");
    for (int t = 0; t < numBms; t++)
        for (int i = 0; i < bms[t].nCells; i++)
            m += "jkbms_cell_volts{pack=\"" + String(t + 1) + "\",cell=\"" + String(i + 1) + "\"} " + String(bms[t].cell[i], 3) + '\n';
    return m;
}

static void webBegin() {
    if (webStarted) return;
    webServer.on("/", []() { if (!webAuth()) return; webServer.send_P(200, "text/html", WEB_PAGE); });
    webServer.on("/screen.jpg", handleScreen);
    webServer.on("/api", []() { if (!webAuth()) return; webServer.send(200, "application/json", webJson()); });
    webServer.on("/metrics", []() { webServer.send(200, "text/plain; version=0.0.4", webMetrics()); });   // Prometheus scrape — telemetry only, no auth (see webMetrics)
    webServer.on("/toggle", HTTP_POST, []() {
        if (!webAuth()) return;
        int b = webServer.arg("bms").toInt(); String w = webServer.arg("which");
        if (b < 0 || b >= numBms) { webServer.send(400, "text/plain", "pack not enabled"); return; }
        bool ok = false;
        if (w == "chg")      { bool n = !bmsCharge[b];    if (bmsSet(b, REG_CHG_SW, n)) { bmsCharge[b] = n; ok = true; } }
        else if (w == "dis") { bool n = !bmsDischarge[b]; if (bmsSet(b, REG_DIS_SW, n)) { bmsDischarge[b] = n; ok = true; } }
        else if (w == "bal") { bool n = !bmsBalancer[b];  if (bmsSet(b, REG_BAL_SW, n)) { bmsBalancer[b] = n; ok = true; } }
        if (ok) { cfgDirty = true; cfgDirtyAt = millis(); }
        webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : "write failed");
    });
    webServer.on("/setparam", HTTP_POST, []() {
        if (!webAuth()) return;
        if (!webServer.hasArg("idx") || !webServer.hasArg("val")) { webServer.send(400, "text/plain", "missing arg"); return; }
        int b = webServer.arg("bms").toInt(), idx = webServer.arg("idx").toInt();
        if (b < 0 || b >= numBms) { webServer.send(400, "text/plain", "pack not enabled"); return; }
        if (idx < 0 || idx >= NSET) { webServer.send(400, "text/plain", "bad idx"); return; }
        bool ok = setPut(b, SETDEFS[idx], webServer.arg("val").toFloat());   // setPut clamps to the setting's vmin/vmax
        webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : "write failed");
    });
    webServer.on("/setmqtt", HTTP_POST, []() {                               // configure MQTT / Home Assistant
        if (!webAuth()) return;
        mqttEnabled = webServer.arg("en") == "1";
        strncpy(mqttHost, webServer.arg("host").c_str(), sizeof(mqttHost) - 1); mqttHost[sizeof(mqttHost) - 1] = 0;
        strncpy(mqttUser, webServer.arg("user").c_str(), sizeof(mqttUser) - 1); mqttUser[sizeof(mqttUser) - 1] = 0;
        if (webServer.hasArg("pass") && webServer.arg("pass").length())       // keep existing pass if field left blank
            { strncpy(mqttPass, webServer.arg("pass").c_str(), sizeof(mqttPass) - 1); mqttPass[sizeof(mqttPass) - 1] = 0; }
        if (webServer.hasArg("port")) mqttPort = webServer.arg("port").toInt();
        if (mqttPort < 1 || mqttPort > 65535) mqttPort = 1883;
        saveSettings(); mqttReconnect = true;
        webServer.send(200, "text/plain", "ok");
    });
    webServer.on("/setalert", HTTP_POST, []() {                              // configure threshold push alerts
        if (!webAuth()) return;
        alertEnabled = webServer.arg("en") == "1";
        alOnFault = webServer.arg("flt") == "1";
        strncpy(alertUrl, webServer.arg("url").c_str(), sizeof(alertUrl) - 1); alertUrl[sizeof(alertUrl) - 1] = 0;
        if (webServer.hasArg("soc")) alSocLo = constrain(webServer.arg("soc").toInt(), 0, 100);
        if (webServer.hasArg("tmp")) alTempHi = constrain(webServer.arg("tmp").toInt(), 0, 120);
        if (webServer.hasArg("dlt")) alDeltaHi = constrain(webServer.arg("dlt").toInt(), 0, 5000);
        memset(alState, 0, sizeof(alState));   // re-arm so changed thresholds can fire again
        saveSettings();
        webServer.send(200, "text/plain", "ok");
    });
    webServer.on("/testalert", HTTP_POST, []() {                             // fire a test notification to the webhook
        if (!webAuth()) return;
        bool ok = alertSend("JK BMS test alert \xE2\x9C\x93");
        webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : "send failed");
    });
    webServer.on("/history.csv", []() {                                      // download the 7-day SOC/power log
        if (!webAuth()) return;
        webServer.sendHeader("Content-Disposition", "attachment; filename=jkbms-history.csv");
        webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
        webServer.send(200, "text/csv", "");
        int maxCount = 0; for (int t = 0; t < numBms; t++) if (histCount[t] > maxCount) maxCount = histCount[t];
        time_t nowEp = timeSynced ? time(nullptr) : 0;
        String hdr = "timestamp,minutes_ago";
        for (int t = 0; t < numBms; t++) hdr += ",bat" + String(t + 1) + "_soc," + "bat" + String(t + 1) + "_w";
        hdr += "\n"; webServer.sendContent(hdr);
        String chunk; chunk.reserve(2048);
        for (int j = maxCount - 1; j >= 0; j--) {                            // oldest → newest (5 min apart)
            char ts[20] = "";
            if (nowEp) { time_t e = nowEp - (time_t)j * 300; struct tm tv; localtime_r(&e, &tv); strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M", &tv); }
            chunk += ts; chunk += ","; chunk += String(j * 5);
            for (int t = 0; t < numBms; t++) {
                int idx = (int)histCount[t] - 1 - j;
                if (idx >= 0) { chunk += ","; chunk += String(histCap[t][idx]); chunk += ","; chunk += String(histPwr[t][idx]); }
                else chunk += ",,";
            }
            chunk += "\n";
            if (chunk.length() > 1600) { webServer.sendContent(chunk); chunk = ""; }
        }
        if (chunk.length()) webServer.sendContent(chunk);
        webServer.sendContent("");                                          // end the chunked response
    });
    webServer.on("/history.json", []() {                                    // downsampled history for the in-browser charts
        if (!webAuth()) return;
        const int N = 120;                                                  // chart resolution
        String j = "{\"packs\":[";
        for (int t = 0; t < numBms; t++) {
            if (t) j += ",";
            int cnt = histCount[t];
            float span = cnt > 1 ? (float)(cnt - 1) / 288.0f : 0.0f;        // days
            int pts = cnt < N ? cnt : N;
            j += "{\"span\":" + String(span, 2) + ",\"soc\":[";
            for (int k = 0; k < pts; k++) {                                 // bucket-average SOC
                int lo = (int)((int64_t)k * cnt / pts), hi = (int)((int64_t)(k + 1) * cnt / pts); if (hi <= lo) hi = lo + 1;
                int s = 0; for (int i = lo; i < hi; i++) s += histCap[t][i];
                if (k) j += ","; j += String(s / (hi - lo));
            }
            j += "],\"w\":[";
            for (int k = 0; k < pts; k++) {                                 // bucket-average power (charge-positive)
                int lo = (int)((int64_t)k * cnt / pts), hi = (int)((int64_t)(k + 1) * cnt / pts); if (hi <= lo) hi = lo + 1;
                long s = 0; for (int i = lo; i < hi; i++) s += histPwr[t][i];
                if (k) j += ","; j += String((int)(s / (hi - lo)));
            }
            j += "],\"tmp\":[";
            for (int k = 0; k < pts; k++) {                                 // bucket-average MOSFET temp (°C)
                int lo = (int)((int64_t)k * cnt / pts), hi = (int)((int64_t)(k + 1) * cnt / pts); if (hi <= lo) hi = lo + 1;
                int s = 0; for (int i = lo; i < hi; i++) s += histTmp[t][i];
                if (k) j += ","; j += String(s / (hi - lo));
            }
            j += "]}";
        }
        j += "]}";
        webServer.send(200, "application/json", j);
    });
    webServer.on("/setupd", HTTP_POST, []() {                               // toggle auto-update from new GitHub releases
        if (!webAuth()) return;
        autoUpdate = webServer.arg("en") == "1"; saveSettings();
        webServer.send(200, "text/plain", "ok");
    });
    webServer.on("/selfupdate", HTTP_POST, []() {                           // download + flash the latest release now
        if (!webAuth()) return;
        if (!updAvail || !updUrl[0]) { webServer.send(409, "text/plain", "no update"); return; }
        updGo = true;                                                       // the core-0 net task performs the OTA
        webServer.send(200, "text/plain", "updating");
    });
    webServer.on("/setpass", HTTP_POST, []() {
        if (!webAuth()) return;
        String p = webServer.arg("p");
        if (p.length() < 4 || p.length() >= sizeof(webPass)) { webServer.send(400, "text/plain", "min 4 chars"); return; }
        strncpy(webPass, p.c_str(), sizeof(webPass) - 1); webPass[sizeof(webPass) - 1] = 0;
        ArduinoOTA.setPassword(webPass);   // re-arm OTA too, else espota keeps the old password until reboot
        saveSettings();
        webServer.send(200, "text/plain", "ok");
    });
    // OTA via browser upload: stream the .bin straight into the inactive app slot
    webServer.on("/update", HTTP_POST,
        []() {
            if (!webAuth()) return;
            bool ok = !Update.hasError();
            webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : Update.errorString());
            if (ok) { delay(400); ESP.restart(); }
        },
        []() {
            if (!webServer.authenticate(webUser, webPass)) { Update.abort(); webServer.requestAuthentication(DIGEST_AUTH, "JK BMS"); return; }
            HTTPUpload &up = webServer.upload();
            if (up.status == UPLOAD_FILE_START) { WiFi.setSleep(false); Update.begin(UPDATE_SIZE_UNKNOWN); }
            else if (up.status == UPLOAD_FILE_WRITE) { if (Update.write(up.buf, up.currentSize) != up.currentSize) Update.abort(); }
            else if (up.status == UPLOAD_FILE_END) { Update.end(true); }
        });
    webServer.begin();
    // ArduinoOTA: push builds from PlatformIO over WiFi (espota), same password.
    // OTA needs handle() called tightly, so onStart suspends the UI/polling and
    // disables WiFi modem-sleep — otherwise the stream starves and drops (broken pipe).
    ArduinoOTA.setHostname("jkbms");
    ArduinoOTA.setPassword(webPass);
    ArduinoOTA.onStart([]() { otaActive = true; WiFi.setSleep(false); });
    ArduinoOTA.onEnd([]() { otaActive = false; });
    ArduinoOTA.onError([](ota_error_t e) { otaActive = false; Serial.printf("[OTA] error %u\n", (unsigned)e); });
    ArduinoOTA.begin();
    webStarted = true;
}

static void webLoop() {
    if (!webStarted) return;
    webServer.handleClient();
    ArduinoOTA.handle();
}
