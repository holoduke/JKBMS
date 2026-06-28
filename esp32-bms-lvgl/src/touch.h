// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
// ---- touch handling (logic) ----
static void handleTap(int x, int y) {
    dirtyFull = true;   // most taps change the whole screen unless noted below
    if (updProgress != -1) { if (updProgress == -2) updProgress = -1; return; }   // updating: ignore taps (tap dismisses a failure)
    if (updPopup) {   // update modal: "Update now" button or tap-elsewhere to close
        int bx, by, bw, bh; updBtnRect(&bx, &by, &bw, &bh);
        if (x >= bx && x < bx + bw && y >= by && y < by + bh) { updPopup = false; updGo = true; }
        else updPopup = false;
        return;
    }
    if (view == V_SETTINGS) {
        if (infoPopup) { infoPopup = false; return; }
        if (editIdx >= 0) {                                  // numeric keypad modal
            const SetDef &d = numDef(editIdx);
            for (int k = 0; k < 16; k++) {
                int kx, ky, kw, kh; keyRect(k, &kx, &ky, &kw, &kh);
                if (x < kx || x >= kx + kw || y < ky || y >= ky + kh) continue;
                int len = strlen(editStr);
                if (k == 14) { editIdx = -1; }                                   // Cancel
                else if (k == 15) {                                             // Save → clamp, write, verify
                    bool hasNum = editStr[0] && !(editStr[0] == '-' && editStr[1] == 0);   // ignore empty / lone "-"
                    if (hasNum && setPut(editBms, d, atof(editStr))) markCfg();
                    editIdx = -1;
                } else if (k == 3) { if (len) editStr[len - 1] = 0; }           // DEL
                else if (k == 7) { editStr[0] = 0; }                            // CLR
                else if (k == 11) {                                            // +/-
                    if (editStr[0] == '-') memmove(editStr, editStr + 1, len);
                    else if (len < 10) { memmove(editStr + 1, editStr, len + 1); editStr[0] = '-'; }
                } else if (k == 12) { if (!strchr(editStr, '.') && len < 10) { editStr[len] = '.'; editStr[len + 1] = 0; } }  // '.'
                else if (len < 10) { editStr[len] = KEYLBL[k][0]; editStr[len + 1] = 0; }   // digit
                return;
            }
            return;
        }
        if (kbActive) {
            if (x >= CLOSE_X - 12 && y <= 44) { kbActive = false; return; }
            int code = kbProcess(false, x, y);
            if (code > 0) { if (wifiPassLen < 32) { wifiPass[wifiPassLen++] = (char)code; wifiPass[wifiPassLen] = 0; } }
            else if (code == -1) { if (wifiPassLen > 0) wifiPass[--wifiPassLen] = 0; }
            else if (code == -2) kbMode = (kbMode + 1) % 3;
            else if (code == -4) {                              // OK → commit, depending on what we were editing
                kbActive = false;
                if (kbTarget == KBT_WUSER) { if (wifiPassLen) { strncpy(webUser, wifiPass, sizeof(webUser) - 1); webUser[sizeof(webUser) - 1] = 0; markCfg(); } }
                else if (kbTarget == KBT_WPASS) { if (wifiPassLen) { strncpy(webPass, wifiPass, sizeof(webPass) - 1); webPass[sizeof(webPass) - 1] = 0; markCfg(); } }
                else wifiTryConnect();
            }
            return;
        }
        if (x >= CLOSE_X - 12 && y <= 44) { switchView(V_BMS1); manualUntil = millis() + PAUSE_MS; lastSwitch = millis(); return; }
        if (y >= 44 && y < 74) {
            for (int i = 0; i < 3; i++) { int tx, tw; subTabGeom(i, &tx, &tw);
                if (x >= tx && x < tx + tw) { subTab = i; if (i == ST_WIFI && netCount == 0) wifiStartScan(); return; } }
            return;
        }
        if (subTab == ST_SYSTEM) {
            if (y < LIST_TOP) return;
            int idx = (y + sysScroll - LIST_TOP) / SROW_STEP;
            int ry = LIST_TOP + idx * SROW_STEP - sysScroll;
            if (idx < 0 || idx >= SYS_ROWS || y < ry || y >= ry + SROW_H) return;
            switch (idx) {
                case 0: autoSwitch = !autoSwitch; break;
                case 1: intervalMs = intervalMs == 3000 ? 5000 : intervalMs == 5000 ? 10000 : 3000; break;
                case 2: brightness += (x < Wd / 2) ? -10 : 10; brightness = constrain(brightness, 10, 100); setBrightness(brightness); appliedB = brightness; break;
                case 3: autoSleepMin = autoSleepMin == 0 ? 2 : autoSleepMin == 2 ? 5 : autoSleepMin == 5 ? 30 : autoSleepMin == 30 ? 120 : 0; break;
                case 4: ecoMode = !ecoMode; break;
                case 5: dimAfterSec = dimAfterSec == 0 ? 30 : dimAfterSec == 30 ? 60 : dimAfterSec == 60 ? 300 : 0; break;
                case 6: tempF = !tempF; break;
                case 7: fmt12 = !fmt12; break;
                case 8: wifiAuto = !wifiAuto; WiFi.setAutoReconnect(wifiAuto); break;
                case 9: simSpeed = simSpeed == 1 ? 2 : simSpeed == 2 ? 5 : 1; break;
                case 10: infoPopup = true; return;   // full redraw for the popup
                case 12: demoMode = !demoMode; if (demoMode) simInit(); bmsRead(); break;   // toggle sim vs live BMS, re-poll
                case 13: idleScreen = (idleScreen + 1) % 6; break;   // cycle screensaver (Off / HUD / Init / Radar / Arcade / Security)
                case 14: saverAfterSec = saverAfterSec == 0 ? 30 : saverAfterSec == 30 ? 60 : saverAfterSec == 60 ? 300 : saverAfterSec == 300 ? 1800 : saverAfterSec == 1800 ? 3600 : 0; break;   // 30s/1m/5m/30m/1h
                case 15: lockAfterSec = lockAfterSec == 0 ? 30 : lockAfterSec == 30 ? 60 : lockAfterSec == 60 ? 300 : lockAfterSec == 300 ? 1800 : lockAfterSec == 1800 ? 3600 : 0;
                         if (lockAfterSec > 0 && !lockPin[0]) { lockSetMode = true; lockEntry[0] = 0; lockEntryLen = 0; lockWrongUntil = 0; markCfg(); return; }   // no PIN yet → set one now (else auto-lock can't engage)
                         break;   // auto-lock: 30s/1m/5m/30m/1h
                case 16: lockSetMode = true; lockEntry[0] = 0; lockEntryLen = 0; lockWrongUntil = 0; markCfg(); return;   // set a new PIN (modal numpad)
                case 17: infoPopup = true; return;                   // Web address → full system-info popup (shows IP + login)
                case 18: strncpy(wifiPass, webUser, sizeof(wifiPass) - 1); wifiPass[sizeof(wifiPass) - 1] = 0; wifiPassLen = strlen(wifiPass); kbMode = 0; kbTarget = KBT_WUSER; kbActive = true; return;   // edit web username
                case 19: wifiPass[0] = 0; wifiPassLen = 0; kbMode = 0; kbTarget = KBT_WPASS; kbActive = true; return;   // set a new web password
                case 20: g_lang = (g_lang + 1) % LANG_COUNT; markCfg(); return;   // cycle UI language (dirtyFull already set → full repaint)
                default: return;                      // firmware row: no-op
            }
            markCfg(); markRowAt(ry);
        } else if (subTab == ST_BMS) {
            if (y < LIST_TOP) return;
            int idx = (y + bmsScroll - LIST_TOP) / SROW_STEP;
            int ry = LIST_TOP + idx * SROW_STEP - bmsScroll;
            if (idx < 0 || idx >= bmsRowCount() || y < ry || y >= ry + SROW_H) return;
            int b = cfgBms;
            bool live = !demoMode && bmsLive[b];
            if (idx == 0) { numBms = numBms == 2 ? 1 : 2;                                              // toggle 1 / 2 packs
                            if (numBms < 2) { cfgBms = 0; bmsLive[1] = false; if (view == V_BMS2) { view = V_BMS1; renderGraphs(); } }
                            bmsScroll = 0; markCfg(); return; }                                        // full redraw
            if (idx == 1) { if (numBms >= 2) { cfgBms ^= 1; bmsScroll = 0; } return; }                 // configure pack 1/2 (only with 2)
            if (idx == 2) { bmsPin[b * 2] = nextPin(bmsPin[b * 2]); bmsBegin(); markCfg(); markRowAt(ry); return; }        // UART TX pin
            if (idx == 3) { bmsPin[b * 2 + 1] = nextPin(bmsPin[b * 2 + 1]); bmsBegin(); markCfg(); markRowAt(ry); return; } // UART RX pin
            if (!live) return;                                                                        // offline/demo: nothing below
            int si = idx - BMS_FIXED;                                                                 // live section
            if (si == 0) { bmsCharge[b] = !bmsCharge[b]; if (!bmsSet(b, REG_CHG_SW, bmsCharge[b] ? 1 : 0)) bmsCharge[b] = !bmsCharge[b]; markCfg(); markRowAt(ry); return; }
            if (si == 1) { bmsDischarge[b] = !bmsDischarge[b]; if (!bmsSet(b, REG_DIS_SW, bmsDischarge[b] ? 1 : 0)) bmsDischarge[b] = !bmsDischarge[b]; markCfg(); markRowAt(ry); return; }
            if (si == 2) { bmsBalancer[b] = !bmsBalancer[b]; if (!bmsSet(b, REG_BAL_SW, bmsBalancer[b] ? 1 : 0)) bmsBalancer[b] = !bmsBalancer[b]; markCfg(); markRowAt(ry); return; }
            if (setOk[b]) {
                int pi = si - 3;
                // Only the main 4-byte (UINT32) settings are writable; the packed tail
                // fields (bitmask flags, heating, sleep-hours) are display-only.
                if (pi >= 0 && pi < NSET) { editIdx = pi; editBms = b; editStr[0] = 0; }   // open keypad (full redraw)
            }
        } else {   // ST_WIFI
            int top = wListTop(), vbot = wRescanY() - 4;
            if (y >= top && y <= vbot) {
                int idx = (y + wifiScroll - top) / WROW_STEP;
                int ry2 = top + idx * WROW_STEP - wifiScroll;
                if (idx >= 0 && idx < netCount && y >= ry2 && y < ry2 + WROW_H) {
                    wifiSel = idx;
                    if (netEnc[wifiSel]) { wifiPass[0] = 0; wifiPassLen = 0; kbMode = 0; kbTarget = KBT_WIFI; kbActive = true; }
                    else wifiTryConnect();
                }
                return;
            }
            int ry = wRescanY();
            if (y >= ry && y < ry + 28) wifiStartScan();
        }
        return;
    }
    // dashboard
    if (wxPopup) { wxPopup = false; return; }   // any tap dismisses the forecast popup
    // top bar — generous hit zones (corners are hard to hit precisely)
    manualUntil = millis() + PAUSE_MS;
    if (y <= 44) {
        if (x >= TAB1_X && x < TAB1_X + TAB_W) { switchView(V_BMS1); lastSwitch = millis(); }
        else if (numBms >= 2 && x >= TAB2_X && x < TAB2_X + TAB_W) { switchView(V_BMS2); lastSwitch = millis(); }
        else if (x >= GEAR_X - 10) { cfgBms = (view == V_BMS2 && numBms >= 2) ? 1 : 0; view = V_SETTINGS; kbActive = false; infoPopup = false; }  // keep last sub-tab
        else if (updAvail && updBoxR > updBoxL && x >= updBoxL && x <= updBoxR) updPopup = true;                   // update icon → update modal
        else if (x >= BED_X - 8) {                                                                                  // lock icon, left of the gear
            lockEntryLen = 0; lockEntry[0] = 0; lockWrongUntil = 0;
            if (lockPin[0]) locked = true;        // PIN set → lock now (unlock pad takes over)
            else lockSetMode = true;              // no PIN yet → set one first; lockCommit then locks (see events.h)
        }
        else if (wxOk && wxBoxR > wxBoxL && x >= wxBoxL && x <= wxBoxR) wxPopup = true;                            // weather glyph → forecast popup
    }
}

