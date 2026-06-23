// On-device web portal: live monitor + controls + OTA firmware update.
// Included into main.cpp AFTER the globals/helpers it uses (bms[], bmsLive[],
// bmsSet, setPut, SETDEFS, etc.). HTTP Basic auth (WEB_USER / webPass) on every
// route. Served by the sync WebServer + ArduinoOTA, both pumped from loop().
#include <WebServer.h>
#include <ArduinoOTA.h>
#include <Update.h>

static WebServer webServer(80);
static bool webStarted = false;
volatile bool otaActive = false;   // true during an OTA → loop() drops everything but OTA

// require auth on every request; returns false (and sends the 401) if not authed
static bool webAuth() {
    if (webServer.authenticate(WEB_USER, webPass)) return true;
    webServer.requestAuthentication();
    return false;
}

static const char WEB_PAGE[] PROGMEM = R"HTML(<!doctype html><html><head><meta charset=utf-8>
<meta name=viewport content="width=device-width,initial-scale=1">
<title>JK BMS</title><style>
*{box-sizing:border-box}body{margin:0;background:#0b0f14;color:#e6edf3;font:14px system-ui,sans-serif}
h1{font-size:18px;margin:14px}.wrap{max-width:760px;margin:0 auto;padding:8px}
.card{background:#11161d;border:1px solid #1f2731;border-radius:12px;padding:14px;margin:10px}
.row{display:flex;justify-content:space-between;align-items:center;padding:4px 0}
.big{font-size:30px;font-weight:700}.mut{color:#7d8590}.grn{color:#3fb950}.amb{color:#d29922}.red{color:#f85149}
.pill{display:inline-block;padding:2px 10px;border-radius:10px;background:#1f2731;font-size:12px}
.cells{display:grid;grid-template-columns:repeat(auto-fill,minmax(78px,1fr));gap:6px;margin-top:8px}
.cell{background:#0b0f14;border:1px solid #1f2731;border-radius:6px;padding:4px 6px;font-size:12px;text-align:center}
button{background:#1f6feb;color:#fff;border:0;border-radius:8px;padding:8px 12px;font-size:14px;cursor:pointer}
button.off{background:#30363d}button.sm{padding:4px 8px;font-size:12px}
table{width:100%;border-collapse:collapse}td{padding:5px 4px;border-bottom:1px solid #1f2731}
input{background:#0b0f14;color:#e6edf3;border:1px solid #30363d;border-radius:6px;padding:6px;width:90px}
.tab{display:inline-block;padding:6px 14px;border-radius:8px;background:#1f2731;margin-right:6px;cursor:pointer}
.tab.on{background:#1f6feb}#prog{height:8px;background:#30363d;border-radius:4px;overflow:hidden;display:none}
#bar{height:100%;width:0;background:#3fb950}</style></head><body><div class=wrap>
<h1>JK BMS Controller <span class=mut id=fw></span></h1>
<div><span class=tab id=t0 onclick=sel(0)>BAT 1</span><span class=tab id=t1 onclick=sel(1)>BAT 2</span>
<span class=pill id=net style=float:right></span></div>
<div class=card id=mon></div>
<div class=card><b>Controls</b><div id=ctl></div></div>
<div class=card><b>Settings</b> <span class=mut>(tap value to edit)</span><table id=params></table></div>
<div class=card><b>Firmware update</b>
<p class=mut id=fwv></p><input type=file id=fwf accept=.bin>
<button onclick=upl()>Upload &amp; flash</button><div id=prog><div id=bar></div></div><p id=ust></p></div>
<div class=card><b>Security</b><div class=row><span>Change password</span>
<span><input type=password id=np placeholder="new password"><button class=sm onclick=chpw()>Save</button></span></div></div>
</div><script>
let cur=0,D={};
function sel(b){cur=b;t0.className='tab'+(b==0?' on':'');t1.className='tab'+(b==1?' on':'');render()}
async function load(){try{D=await(await fetch('/api')).json();fw.textContent='v'+D.fw;
net.textContent=D.ip+' · up '+Math.floor(D.up/60)+'m';fwv.textContent='current: v'+D.fw;render()}catch(e){}}
function tc(t){return (t<-50||t>120)?'--':t.toFixed(0)+'C'}
function render(){if(!D.packs)return;let p=D.packs[cur];
let col=p.i>2?'grn':p.i<-2?'amb':'mut';
mon.innerHTML=`<div class=row><span class=pill>${p.st}</span><span class=mut>${p.live?'live':'offline'}</span></div>
<div class=row><span class=big>${p.soc.toFixed(0)}%</span><span class="big ${col}">${p.w.toFixed(0)}W</span></div>
<div class=row><span class=mut>Voltage</span><b>${p.v.toFixed(2)}V</b></div>
<div class=row><span class=mut>Current</span><b>${p.i.toFixed(1)}A</b></div>
<div class=row><span class=mut>Capacity</span><b>${p.cap.toFixed(0)}Ah</b></div>
<div class=row><span class=mut>Temps</span><b>MOS ${tc(p.tmos)} · T1 ${tc(p.t1)} · T2 ${tc(p.t2)}</b></div>
<div class=cells>${p.cells.map((c,i)=>`<div class=cell>C${i+1}<br><b>${c.toFixed(2)}</b></div>`).join('')}</div>`;
ctl.innerHTML=[['chg','Charge MOSFET',p.chg],['dis','Discharge MOSFET',p.dis],['bal','Balancer',p.bal]]
.map(([k,n,v])=>`<div class=row><span>${n}</span><button class="sm ${v?'':'off'}" onclick="tog('${k}')">${v?'ON':'OFF'}</button></div>`).join('');
let ps=D.params&&D.params[cur]||[];
params.innerHTML=ps.map(s=>`<tr><td>${s.l}</td><td style=text-align:right onclick="ed(${s.i},'${s.l}')"><b>${s.v}</b></td></tr>`).join('')
||'<tr><td class=mut>not loaded yet</td></tr>';}
async function tog(k){await fetch('/toggle?bms='+cur+'&which='+k,{method:'POST'});setTimeout(load,400)}
async function ed(i,l){let v=prompt('New value for '+l);if(v===null||v==='')return;
await fetch('/setparam?bms='+cur+'&idx='+i+'&val='+encodeURIComponent(v),{method:'POST'});setTimeout(load,500)}
async function chpw(){if(!np.value)return;await fetch('/setpass?p='+encodeURIComponent(np.value),{method:'POST'});
np.value='';ust.textContent='password changed — re-login on next action'}
function upl(){let f=fwf.files[0];if(!f){ust.textContent='pick a .bin first';return}
let x=new XMLHttpRequest();x.open('POST','/update');prog.style.display='block';
x.upload.onprogress=e=>{bar.style.width=(e.loaded/e.total*100)+'%'};
x.onload=()=>{ust.textContent=x.status==200?'OK — device rebooting…':'failed: '+x.responseText};
let fd=new FormData();fd.append('f',f);x.send(fd)}
load();setInterval(load,2000);
</script></body></html>)HTML";

// ---- JSON state ----
static String webJson() {
    String j = "{\"fw\":\"" FW_VERSION "\",\"ip\":\"" + WiFi.localIP().toString() +
               "\",\"up\":" + String(millis() / 1000) + ",\"packs\":[";
    for (int t = 0; t < 2; t++) {
        const Bms &b = bms[t];
        bool live = demoMode || bmsLive[t];
        float clo = 9, chi = 0;
        for (int i = 0; i < NCELLS; i++) { if (b.cell[i] < clo) clo = b.cell[i]; if (b.cell[i] > chi) chi = b.cell[i]; }
        const char *st = !live ? "Offline" : !b.bmsOk ? "Protected"
                       : (!bmsDischarge[t] || !bmsCharge[t]) ? "FET off"
                       : (bmsBalancer[t] && (chi - clo) > 0.015f) ? "Balancing"
                       : b.i > 2 ? "Charging" : b.i < -2 ? "Discharging" : b.soc >= 99 ? "Full" : "Idle";
        float fullAh = (!demoMode && bmsLive[t]) ? packFullAh[t] : PACK_AH;
        if (t) j += ",";
        j += "{\"live\":" + String(live ? 1 : 0) + ",\"soc\":" + String(b.soc, 0) +
             ",\"v\":" + String(b.v, 2) + ",\"i\":" + String(b.i, 1) +
             ",\"w\":" + String(b.v * b.i, 0) + ",\"tmos\":" + String(b.tMos, 0) +
             ",\"t1\":" + String(b.tp1, 0) + ",\"t2\":" + String(b.tp2, 0) +
             ",\"cap\":" + String(fullAh, 0) + ",\"chg\":" + String(bmsCharge[t] ? 1 : 0) +
             ",\"dis\":" + String(bmsDischarge[t] ? 1 : 0) + ",\"bal\":" + String(bmsBalancer[t] ? 1 : 0) +
             ",\"ok\":" + String(b.bmsOk ? 1 : 0) + ",\"st\":\"" + st + "\",\"cells\":[";
        for (int i = 0; i < NCELLS; i++) { if (i) j += ","; j += String(b.cell[i], 2); }
        j += "]}";
    }
    j += "],\"params\":[";
    for (int t = 0; t < 2; t++) {
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

static void webBegin() {
    if (webStarted) return;
    webServer.on("/", []() { if (!webAuth()) return; webServer.send_P(200, "text/html", WEB_PAGE); });
    webServer.on("/api", []() { if (!webAuth()) return; webServer.send(200, "application/json", webJson()); });
    webServer.on("/toggle", HTTP_POST, []() {
        if (!webAuth()) return;
        int b = webServer.arg("bms").toInt() & 1; String w = webServer.arg("which");
        bool ok = false;
        if (w == "chg")      { bool n = !bmsCharge[b];    if (bmsSet(b, 0x1070, n)) { bmsCharge[b] = n; ok = true; } }
        else if (w == "dis") { bool n = !bmsDischarge[b]; if (bmsSet(b, 0x1074, n)) { bmsDischarge[b] = n; ok = true; } }
        else if (w == "bal") { bool n = !bmsBalancer[b];  if (bmsSet(b, 0x1078, n)) { bmsBalancer[b] = n; ok = true; } }
        if (ok) { cfgDirty = true; cfgDirtyAt = millis(); }
        webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : "write failed");
    });
    webServer.on("/setparam", HTTP_POST, []() {
        if (!webAuth()) return;
        int b = webServer.arg("bms").toInt() & 1, idx = webServer.arg("idx").toInt();
        if (idx < 0 || idx >= NSET) { webServer.send(400, "text/plain", "bad idx"); return; }
        bool ok = setPut(b, SETDEFS[idx], webServer.arg("val").toFloat());
        webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : "write failed");
    });
    webServer.on("/setpass", HTTP_POST, []() {
        if (!webAuth()) return;
        String p = webServer.arg("p");
        if (p.length() < 1 || p.length() >= sizeof(webPass)) { webServer.send(400, "text/plain", "bad"); return; }
        strncpy(webPass, p.c_str(), sizeof(webPass) - 1); webPass[sizeof(webPass) - 1] = 0;
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
            if (!webServer.authenticate(WEB_USER, webPass)) return;   // guard the upload stream too
            HTTPUpload &up = webServer.upload();
            if (up.status == UPLOAD_FILE_START) { WiFi.setSleep(false); Update.begin(UPDATE_SIZE_UNKNOWN); }
            else if (up.status == UPLOAD_FILE_WRITE) { Update.write(up.buf, up.currentSize); }
            else if (up.status == UPLOAD_FILE_END) { Update.end(true); }
        });
    webServer.begin();
    // ArduinoOTA: push builds from PlatformIO over WiFi (espota), same password.
    // OTA needs handle() called tightly, so onStart suspends the UI/polling and
    // disables WiFi modem-sleep — otherwise the stream starves and drops (broken pipe).
    ArduinoOTA.setHostname("jkbms");
    ArduinoOTA.setPassword(webPass);
    ArduinoOTA.onStart([]() { otaActive = true; WiFi.setSleep(false); });
    ArduinoOTA.onError([](ota_error_t e) { otaActive = false; });
    ArduinoOTA.begin();
    webStarted = true;
}

static void webLoop() {
    if (!webStarted) return;
    webServer.handleClient();
    ArduinoOTA.handle();
}
