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
h1{font-size:18px;margin:14px}.wrap{max-width:1000px;margin:0 auto;padding:8px}
.grid{display:grid;grid-template-columns:1fr;gap:0}.col{min-width:0}
@media(min-width:780px){.grid{grid-template-columns:1fr 1fr;align-items:start}}
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
<div class=grid>
<div class=col>
<div class=card id=mon></div>
<div class=card><b>Settings</b> <span class=mut>(tap value to edit)</span><table id=params></table></div>
<div class=card><b>Firmware update</b>
<p class=mut id=fwv></p><input type=file id=fwf accept=.bin>
<button onclick=upl()>Upload &amp; flash</button><div id=prog><div id=bar></div></div><p id=ust></p></div>
<div class=card><b>Security</b><div class=row><span>Change password</span>
<span><input type=password id=np placeholder="new password"><button class=sm onclick=chpw()>Save</button></span></div></div>
</div>
<div class=col>
<div class=card><b>Device screen</b> <button class=sm onclick=shot()>Refresh</button>
<div style=margin-top:8px><img id=scr style="width:100%;max-width:480px;border:1px solid #1f2731;border-radius:8px;image-rendering:pixelated" alt="tap Refresh"></div></div>
<div class=card><b>Controls</b><div id=ctl></div></div>
</div>
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
async function chpw(){if(np.value.length<4){ust.textContent='password min 4 chars';return}
let r=await fetch('/setpass',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'p='+encodeURIComponent(np.value)});
np.value='';ust.textContent=r.ok?'password changed — re-login on next action':'change failed'}
function shot(){scr.src='/screen.bmp?t='+Date.now()}
function upl(){let f=fwf.files[0];if(!f){ust.textContent='pick a .bin first';return}
let x=new XMLHttpRequest();x.open('POST','/update');prog.style.display='block';
x.upload.onprogress=e=>{bar.style.width=(e.loaded/e.total*100)+'%'};
x.onload=()=>{ust.textContent=x.status==200?'OK — device rebooting…':'failed: '+x.responseText};
let fd=new FormData();fd.append('f',f);x.send(fd)}
load();setInterval(load,2000);shot();
</script></body></html>)HTML";

// ---- JSON state ----
static String webJson() {
    String j; j.reserve(3600);   // one allocation; avoids a realloc cascade from the +='s below
    j = "{\"fw\":\"" FW_VERSION "\",\"ip\":\"" + WiFi.localIP().toString() +
        "\",\"up\":" + String(millis() / 1000) + ",\"packs\":[";
    for (int t = 0; t < 2; t++) {
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

// Stream the live LVGL framebuffer as a 24-bit BMP. The canvas is rotated/column-major:
// landscape pixel (lx,ly) lives at fb[lx*Ht + (Ht-1-ly)]. BMP is top-down (negative height), BGR.
// WiFiClient.write() can do partial sends when the TCP buffer is full; loop until all sent
static void clientWriteAll(WiFiClient &c, const uint8_t *p, size_t n) {
    size_t sent = 0; uint32_t t0 = millis();
    while (sent < n && c.connected()) {
        size_t w = c.write(p + sent, n - sent);
        if (w) { sent += w; t0 = millis(); }
        else { if (millis() - t0 > 3000) break; delay(1); }
    }
}
static void handleScreen() {
    if (!webAuth()) return;
    const uint16_t *fb = gfx->getFramebuffer();
    if (!fb) { webServer.send(500, "text/plain", "no framebuffer"); return; }
    const int W = Wd, H = Ht;
    const uint32_t imgSize = (uint32_t)W * H * 3, fileSize = 54 + imgSize;
    uint8_t hdr[54]; memset(hdr, 0, sizeof(hdr));
    hdr[0] = 'B'; hdr[1] = 'M';
    hdr[2] = fileSize; hdr[3] = fileSize >> 8; hdr[4] = fileSize >> 16; hdr[5] = fileSize >> 24;
    hdr[10] = 54; hdr[14] = 40;
    hdr[18] = W & 0xFF; hdr[19] = W >> 8;
    int32_t nh = -H; hdr[22] = nh; hdr[23] = nh >> 8; hdr[24] = nh >> 16; hdr[25] = nh >> 24;
    hdr[26] = 1; hdr[28] = 24;
    hdr[34] = imgSize; hdr[35] = imgSize >> 8; hdr[36] = imgSize >> 16; hdr[37] = imgSize >> 24;
    webServer.setContentLength(fileSize);
    webServer.send(200, "image/bmp", "");
    WiFiClient client = webServer.client();
    WiFi.setSleep(false);          // modem-sleep latency stalls the 460KB stream → truncation; disable while sending
    clientWriteAll(client, hdr, 54);
    static uint8_t row[Wd * 3];
    for (int ly = 0; ly < H; ly++) {
        int o = 0;
        for (int lx = 0; lx < W; lx++) {
            uint16_t px = fb[(int32_t)lx * H + (H - 1 - ly)];
            uint8_t r = (px >> 11) & 0x1f, g = (px >> 5) & 0x3f, b = px & 0x1f;
            row[o++] = (b << 3) | (b >> 2);   // BMP pixel order is B,G,R
            row[o++] = (g << 2) | (g >> 4);
            row[o++] = (r << 3) | (r >> 2);
        }
        clientWriteAll(client, row, W * 3);
    }
    WiFi.setSleep(true);
}

static void webBegin() {
    if (webStarted) return;
    webServer.on("/", []() { if (!webAuth()) return; webServer.send_P(200, "text/html", WEB_PAGE); });
    webServer.on("/screen.bmp", handleScreen);
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
        if (!webServer.hasArg("idx") || !webServer.hasArg("val")) { webServer.send(400, "text/plain", "missing arg"); return; }
        int b = webServer.arg("bms").toInt() & 1, idx = webServer.arg("idx").toInt();
        if (idx < 0 || idx >= NSET) { webServer.send(400, "text/plain", "bad idx"); return; }
        bool ok = setPut(b, SETDEFS[idx], webServer.arg("val").toFloat());   // setPut clamps to the setting's vmin/vmax
        webServer.send(ok ? 200 : 500, "text/plain", ok ? "ok" : "write failed");
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
            if (!webServer.authenticate(WEB_USER, webPass)) { Update.abort(); return; }   // abort, don't leave a half-written image
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
    ArduinoOTA.onEnd([]() { otaActive = false; });
    ArduinoOTA.onError([](ota_error_t e) { otaActive = false; });
    ArduinoOTA.begin();
    webStarted = true;
}

static void webLoop() {
    if (!webStarted) return;
    webServer.handleClient();
    ArduinoOTA.handle();
}
