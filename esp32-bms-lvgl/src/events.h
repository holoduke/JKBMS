// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
// ============================================================================
//  LVGL glue
// ============================================================================
static uint32_t millis_cb(void) { return millis(); }
static void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    gfx->blit(area->x1, area->y1, lv_area_get_width(area), lv_area_get_height(area), (uint16_t *)px_map);
    gfxDirty = true;
    lv_disp_flush_ready(disp);
}
static void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data) {
    uint16_t x, y;
    if (touch.touched()) { touch.readData(&x, &y); data->point.x = x; data->point.y = y; data->state = LV_INDEV_STATE_PRESSED; }
    else data->state = LV_INDEV_STATE_RELEASED;
}

static lv_obj_t *scr;
static void invArea(int x1, int y1, int x2, int y2);

// ============================================================================
//  PIN lock — 6-digit numpad. Shows automatically once auto-lock arms; while the
//  screensaver is up it stays until a touch, then this appears (lockShowing()).
// ============================================================================
static bool lockShowing() { return locked && !idleActiveNow(); }   // armed + not behind the screensaver
// Full-screen numpad: PIN dots on top, a 3x4 grid of square keys filling the width/height,
// and a message strip at the bottom. k 0-8 = "1".."9", 9 = backspace, 10 = "0", 11 = cancel.
#define LK_TOP 26            // dots strip on top
#define LK_BOT 34            // reserved bottom message strip
#define LK_M 4               // outer margin / gap between keys
static void lockKeyRect(int k, int *x, int *y, int *w, int *h) {
    int gw = Wd - 2 * LK_M, gh = Ht - LK_TOP - LK_BOT;
    int cw = (gw - 2 * LK_M) / 3, ch = (gh - 3 * LK_M) / 4;
    *x = LK_M + (k % 3) * (cw + LK_M); *y = LK_TOP + (k / 3) * (ch + LK_M); *w = cw; *h = ch;
}
static const char *lockKeyLabel(int k) {
    static const char *L9[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    if (k < 9) return L9[k]; if (k == 10) return "0"; if (k == 9) return "<"; return "X";
}
static void renderLockPad(bool setMode) {
    fRect(0, 0, Wd, Ht, 0, C_BG);
    uint32_t now = millis();
    bool wrong = lockWrongUntil > now;
    for (int i = 0; i < 6; i++) {           // PIN progress dots, top strip
        int px = Wd / 2 - 5 * 14 + i * 28, py = 13;
        if (i < lockEntryLen) fCircle(px, py, 6, wrong ? C_BAD : C_ACCENT);
        else ring(px, py, 6, 5, 0, 360, C_BORDER);
    }
    int nKeys = setMode ? 12 : 11;          // cancel (k=11) only when setting a new PIN
    for (int k = 0; k < nKeys; k++) {
        int x, y, w, h; lockKeyRect(k, &x, &y, &w, &h);
        bool back = (k == 9), cancel = (k == 11);
        fRect(x, y, w, h, 8, C_CARD);                              // square (slightly rounded) key
        dRect(x, y, w, h, 8, cancel ? C_BAD : C_BORDER);
        fRect(x + 8, y + h - 4, w - 16, 2, 0, cancel ? C_BAD : C_ACCENT);   // accent underline → futuristic
        cText(lockKeyLabel(k), x + w / 2, y + h / 2, F28, cancel ? C_BAD : (back ? C_MUTED : C_TEXT));
    }
    // bottom message strip — defaults to "Enter PIN", turns red on a wrong attempt
    const char *msg = wrong ? T(K_WRONG_PIN) : setMode ? T(K_SET_PIN) : T(K_ENTER_PIN);
    cText(msg, Wd / 2, Ht - LK_BOT / 2, F16, wrong ? C_BAD : C_ACCENT);
}
static void lockCommit(bool setMode) {      // called when the 6th digit lands
    if (setMode) { strncpy(lockPin, lockEntry, sizeof(lockPin) - 1); lockPin[sizeof(lockPin) - 1] = 0;
                   lockSetMode = false; lockEntryLen = 0; lockEntry[0] = 0; saveSettings();
                   if (view != V_SETTINGS) locked = true; }   // PIN set from the dashboard lock icon → lock right away
    else if (strcmp(lockEntry, lockPin) == 0) { locked = false; lockEntryLen = 0; lockEntry[0] = 0; }
    else { lockWrongUntil = millis() + 1500; lockEntryLen = 0; lockEntry[0] = 0; }   // wrong → clear, retry
}
static void handleLockKey(int x, int y, bool setMode) {
    lockWrongUntil = 0;
    int nKeys = setMode ? 12 : 11;
    for (int k = 0; k < nKeys; k++) {
        int kx, ky, kw, kh; lockKeyRect(k, &kx, &ky, &kw, &kh);
        if (x < kx || x >= kx + kw || y < ky || y >= ky + kh) continue;
        if (k == 11) { lockSetMode = false; lockEntryLen = 0; lockEntry[0] = 0; return; }   // cancel (set mode)
        if (k == 9) { if (lockEntryLen > 0) lockEntry[--lockEntryLen] = 0; return; }         // backspace
        char d = (k == 10) ? '0' : (char)('1' + k);
        if (lockEntryLen < 6) { lockEntry[lockEntryLen++] = d; lockEntry[lockEntryLen] = 0; }
        if (lockEntryLen == 6) lockCommit(setMode);
        return;
    }
}

static void draw_cb(lv_event_t *e) {
    L = lv_event_get_layer(e);
    tpi = 0;
    if (updProgress != -1) { renderUpdating(); return; }   // self-update in progress takes over the whole display
    if (lockSetMode) { renderLockPad(true); return; }      // setting a new PIN (from dashboard lock icon or settings)
    if (lockShowing()) { renderLockPad(false); return; }   // unlock screen takes over the whole display
    if (view == V_SETTINGS) renderSettings();
    else renderBms();
}
static bool pressHandled = false, gMoved = false, gAnchored = false, gSettle = false;
static bool saverShowing = false, swallowTap = false;   // screensaver active / wake-tap should not also act on the UI
static int gStartY = 0, gBaseScroll = 0, gLastY = 0;
static uint32_t gLastT = 0;
static float gVel = 0;              // finger velocity px/ms during a drag
// kinetic (momentum) scroll
static float flingVel = 0;          // scroll velocity px/ms
static int *flingVar = nullptr, flingMax = 0, flingTop = 0, flingBot = 0;
static uint32_t flingLast = 0;      // last fling step time (for frame-rate-independent momentum)
static volatile bool gTouchDown = false;   // finger currently down (set in press/release)
// While the user is actively scrolling/flinging, skip the blocking background work
// (Modbus poll, NVS writes, network loops) so touch sampling + rendering stay smooth.
static inline bool uiBusy() { return gTouchDown || flingVel != 0; }
// scroll context for the current tab (nullptr = nothing scrolls here)
static int *scrollCtx(int *maxS, int *top, int *bot) {
    if (view == V_SETTINGS && subTab == ST_SYSTEM) { *maxS = sysMaxScroll(); *top = LIST_TOP; *bot = Ht; return &sysScroll; }
    if (view == V_SETTINGS && subTab == ST_BMS && editIdx < 0) { *maxS = bmsMaxScroll(); *top = LIST_TOP; *bot = Ht; return &bmsScroll; }
    if (view == V_SETTINGS && subTab == ST_WIFI) { *maxS = wMaxScroll(); *top = wListTop(); *bot = wRescanY() - 4; return &wifiScroll; }
    return nullptr;
}
// Keyboard keys act on PRESS (immediate). The System list drag-scrolls on PRESSING.
// Everything else acts on RELEASE — and only if the finger didn't drag — so
// scrolling never accidentally toggles a setting.
static void unsave() {   // instantly undo dim / eco on interaction
    if (appliedB != brightness) { setBrightness(brightness); appliedB = brightness; }
    if (ecoActive) { ecoActive = false; if (dataTimer) lv_timer_set_period(dataTimer, 220); if (barTimer) lv_timer_set_period(barTimer, 130); }
}
static void press_cb(lv_event_t *e) {
    lastActivity = millis();
    gTouchDown = true;
    if (saverShowing) swallowTap = true;   // this touch only wakes the screensaver; don't act on the UI underneath
    if (standby) return;
    unsave();
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    gMoved = false; gAnchored = false; gSettle = false; gVel = 0; flingVel = 0;   // grab cancels any momentum
    // PIN lock takes all taps as numpad input. While the screensaver is up (saverShowing),
    // this tap only wakes it — the lock pad appears on the next touch.
    if (locked && !saverShowing) { handleLockKey(p.x, p.y, false); pressHandled = true; lv_obj_invalidate(scr); return; }
    if (lockSetMode) { handleLockKey(p.x, p.y, true); pressHandled = true; lv_obj_invalidate(scr); return; }
    // Act on PRESS (not release) for discrete targets that have nothing to scroll, so they
    // respond on first touch instead of needing a clean release (which a 40ms flush or a few
    // px of finger jitter can otherwise eat): the settings keyboard/editor, and on the
    // dashboard the top-bar buttons + any open modal.
    if (view == V_SETTINGS) {
        if (kbActive || editIdx >= 0) { handleTap(p.x, p.y); pressHandled = true; lv_obj_invalidate(scr); }
    } else if (p.y <= 44 || wxPopup || updPopup || updProgress != -1) {
        handleTap(p.x, p.y); pressHandled = true; lv_obj_invalidate(scr);
    }
}
static void pressing_cb(lv_event_t *e) {
    lastActivity = millis();             // finger still down → keep activity fresh (also feeds the stuck-touch failsafe)
    if (standby || pressHandled || kbActive) return;
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    int maxS = 0, top = 0, bot = 0; int *scrollVar = scrollCtx(&maxS, &top, &bot);
    if (!gAnchored) {                    // first sample — but the touch IC often returns a STALE point
        gStartY = p.y; gBaseScroll = scrollVar ? *scrollVar : 0; gAnchored = true;   // (left from the previous lift)
        gLastY = p.y; gLastT = millis(); gVel = 0; gSettle = true; return;            // so re-anchor on the next one
    }
    if (gSettle) {                       // 2nd sample: discard the possibly-stale first → anchor here for real
        gSettle = false;
        gStartY = p.y; gBaseScroll = scrollVar ? *scrollVar : 0;
        gLastY = p.y; gLastT = millis(); gVel = 0; return;
    }
    if (abs(p.y - gLastY) > 120) return; // single-sample teleport = touch glitch → ignore, don't scroll
    int dy = p.y - gStartY;
    if (abs(dy) > 10) gMoved = true;     // a real drag suppresses the release tap (10px tolerates tap jitter)
    uint32_t tn = millis();              // track finger velocity for momentum
    if (tn > gLastT) gVel = 0.6f * gVel + 0.4f * ((float)(p.y - gLastY) / (tn - gLastT));
    gLastY = p.y; gLastT = tn;
    if (gMoved && scrollVar) {           // scroll only where there's a list
        int ns = gBaseScroll - dy;
        if (ns < 0) ns = 0; if (ns > maxS) ns = maxS;
        if (ns != *scrollVar) { *scrollVar = ns; lastActivity = millis(); invArea(0, top, Wd - 1, bot); }
    }
}
static void release_cb(lv_event_t *e) {
    lastActivity = millis();
    gTouchDown = false;
    if (standby) { standby = false; appliedB = brightness; setBrightness(brightness); unsave(); lv_obj_invalidate(scr); return; }  // wake
    if (swallowTap) { swallowTap = false; gMoved = false; return; }   // first tap only dismissed the screensaver
    if (pressHandled) { pressHandled = false; return; }   // keyboard handled on press
    if (gMoved) {                                         // was a scroll → fling, don't toggle
        gMoved = false;
        int maxS = 0, top = 0, bot = 0; int *sv = scrollCtx(&maxS, &top, &bot);
        if (sv && millis() - gLastT < 140 && fabsf(gVel) > 0.04f) {   // released while moving → momentum
            flingVel = -gVel; if (flingVel > 2.5f) flingVel = 2.5f; if (flingVel < -2.5f) flingVel = -2.5f;
            flingVar = sv; flingMax = maxS; flingTop = top; flingBot = bot; flingLast = 0;
        }
        return;
    }
    lv_indev_t *indev = lv_indev_active(); if (!indev) return;
    lv_point_t p; lv_indev_get_point(indev, &p);
    handleTap(p.x, p.y);
    if (dirtyFull) lv_obj_invalidate(scr);
    else lv_obj_invalidate_area(scr, &dirtyRect);
}
// momentum scroll: decays the released velocity until it stops or hits an edge
static void fling_cb(lv_timer_t *t) {
    if (!flingVar || fabsf(flingVel) < 0.03f) { flingVel = 0; flingLast = 0; return; }
    uint32_t now = millis();
    uint32_t dt = flingLast ? (now - flingLast) : 30; if (dt > 100) dt = 100;   // frame-rate-independent (panel flush time varies)
    flingLast = now;
    int ns = *flingVar + (int)(flingVel * dt);           // velocity is px/ms → × elapsed ms
    if (ns < 0) { ns = 0; flingVel = 0; }
    if (ns > flingMax) { ns = flingMax; flingVel = 0; }
    if (ns != *flingVar) { *flingVar = ns; invArea(0, flingTop, Wd - 1, flingBot); }
    flingVel *= powf(0.90f, dt / 30.0f);                 // friction, normalised to a 30ms step
}
// The Arduino_Canvas is a persistent full framebuffer: regions we don't
// invalidate keep their previous pixels. So we redraw selectively —
//   • tab strip at high rate  → smooth auto-switch bar
//   • live values slower       → tiles/ring/cells/power graph
//   • capacity graph (static)  → only on a BMS switch
// A full AA repaint of the whole screen is ~220ms; this keeps each repaint small.
static void invArea(int x1, int y1, int x2, int y2) {
    lv_area_t a = {x1, y1, x2, y2}; lv_obj_invalidate_area(scr, &a);
}
// Poll the live BMSes; when a pack's online/offline state flips, repaint the tab
// row (red ↔ accent) and the body (stale ↔ live) so the UI tracks reconnects.
// Core-1 reaction to the core-0 poll: the actual Modbus read happens in netTask; here we
// only repaint when the cached state the user sees has changed (no blocking work).
static void bmsPoll_cb(lv_timer_t *t) {
    histSample();        // append a 5-min point when due — on core 1, same core as the graph/energy readers
    energyIntegrate();   // accumulate lifetime kWh (dt-integrated, so the 500ms cadence is fine)
    static bool was0 = false, was1 = false; static int lastHc = -1;
    bool l0 = bmsLive[0], l1 = numBms >= 2 ? bmsLive[1] : false;
    int hc = histCount[view];
    if (standby || view == V_SETTINGS) { was0 = l0; was1 = l1; lastHc = hc; return; }   // track silently; view switch repaints in full
    if (l0 != was0 || l1 != was1) {            // a pack went online/offline
        was0 = l0; was1 = l1;
        invArea(6, 4, TAB2_X + TAB_W, 36);     // tab colours
        invArea(0, 36, Wd - 1, Ht - 1);        // body: stale ↔ live values
    }
    if (hc != lastHc) {                         // a new 5-min history sample landed → refresh the capacity canvas (power is on the 1s tick)
        lastHc = hc;
        renderCapCanvas();
        invArea(196, 118, Wd - 1, 313);        // power + capacity graph slots
    }
}
static void barTick_cb(lv_timer_t *t) {
    if (standby || view == V_SETTINGS || idleActiveNow()) return;
    if (!autoSwitch || numBms < 2 || millis() < manualUntil) return;   // paused/off/single-pack → bar not moving, skip flush
    invArea(6, 4, TAB2_X + TAB_W, 36);
}
// Drives the liveness spinner at high fps — repaints only the ring annulus. Pauses when
// in settings/standby/screensaver or once the screen auto-dims (nobody watching → save power).
static void spin_cb(lv_timer_t *t) {
    if (standby || view == V_SETTINGS || idleActiveNow()) return;
    if (appliedB <= DIM_LEVEL) return;                 // dimmed (user away) → don't burn the panel
    if (!(demoMode || bmsLive[view])) return;          // only when the shown pack is live
    if (bms[view].i <= 0.5f) return;                   // only while charging (spinner indicates charge in progress)
    invArea(18, 96, 182, 260);                          // ring + spinner box → renderBms repaints it
}
static void dataTick_cb(lv_timer_t *t) {
    uint32_t now = millis();
    if (updProgress != -1) { lv_obj_invalidate(scr); }   // self-update overlay → keep the progress bar fresh
    simStep(now);
    if (pwrSample() && !standby && view != V_SETTINGS && !idleActiveNow()) {   // new power point → refresh ONLY the power canvas (capacity changes every 5min, not every second)
        renderPwrCanvas(); invArea(196, 118, Wd - 1, 313);
    }
    if (!uiBusy()) {   // NVS writes block for tens of ms — never mid-scroll/fling
        if (cfgDirty && now - cfgDirtyAt > 1500) { cfgDirty = false; saveSettings(); }   // persist settings
        if (wxDirty) { wxDirty = false; saveWeather(); }   // flush a new forecast (flagged by core-0 wxFetch) — prefs must stay core-1-only
        // History rides a ~30-min cadence (not every 5-min sample) to spare NVS flash —
        // the full ring stays in RAM, so we only lose the last <30 min on an unclean reboot.
        static uint32_t lastHistSave = 0;
        if (histDirty && now - histDirtyAt > 2000 && (!lastHistSave || now - lastHistSave > 1800000UL)) {
            histDirty = false; lastHistSave = now; saveHistory();   // ~12 KB write: was 288×/day, now ~48×/day
        }
    }
    // ---- power saving (escalates with idle time; any touch resets it) ----
    uint32_t idle = now - lastActivity;
    if (gTouchDown && idle > 8000) gTouchDown = false;   // failsafe: a missed release shouldn't wedge uiBusy() (would block NVS saves forever)
    // auto-lock: arm after the inactivity timeout (needs a PIN set). The pad appears
    // automatically, or after the screensaver is touched (see lockShowing/press_cb).
    if (lockAfterSec > 0 && lockPin[0] && !locked && !lockSetMode && idle > (uint32_t)lockAfterSec * 1000UL) {
        locked = true; lockEntryLen = 0; lockEntry[0] = 0; lockWrongUntil = 0; lv_obj_invalidate(scr);
    }
    if (!standby) {                                                 // (sleep keeps the backlight off)
        int tB = (dimAfterSec && idle > (uint32_t)dimAfterSec * 1000UL) ? DIM_LEVEL : brightness;
        if (tB != appliedB) { setBrightness(tB); appliedB = tB; }   // auto-dim
    }
    // eco throttles the UI to 1fps when idle. While auto-switch is rotating we keep full
    // fps so the cycling stays smooth — UNTIL the screen auto-dims (truly idle), then we
    // throttle anyway to stop flushing the panel continuously for nobody.
    bool eco = ecoMode && !standby && idle > ECO_IDLE_MS &&
               (!(autoSwitch && numBms >= 2) || appliedB <= DIM_LEVEL);
    if (eco != ecoActive) {                                          // low-fps when idle
        ecoActive = eco;
        if (dataTimer) lv_timer_set_period(dataTimer, eco ? 1000 : 220);
        if (barTimer) lv_timer_set_period(barTimer, eco ? 1000 : 250);
    }
    if (autoSleepMin > 0 && !standby && idle > (uint32_t)autoSleepMin * 60000UL) { pendingSleep = true; return; }
    if (standby || view == V_SETTINGS || idleActiveNow()) return;   // idle screen owns the canvas
    // the clock + weather glyph live outside any data-driven dirty region → repaint the strip on a slow tick
    static uint32_t lastClkInv = 0;
    if (now - lastClkInv >= 15000) { lastClkInv = now; invArea(226, 4, BED_X - 2, 35); }
    if (numBms >= 2 && autoSwitch && now >= manualUntil && now - lastSwitch >= intervalMs) {
        int other = view ^ 1;
        // only flip to the other pack if it's available (demo mode shows both;
        // in live mode skip a BMS that isn't answering — if both are down, stay put)
        bool otherOk = demoMode || bmsLive[other];
        lastSwitch = now;
        if (otherOk) {
            switchView(other);
            invArea(0, 36, Wd - 1, Ht - 1);        // full body: new BMS + new graphs
        }
        return;
    }
    // Repaint the whole value area in ONE coherent frame every other tick (~440 ms).
    // The panel flushes the full canvas regardless of dirty size, so batching the three
    // sections costs the same one flush instead of three staggered ones — fewer flushes
    // and every field shares the same timestamp. The auto-switch bar (y<36) is outside
    // this region and keeps animating on its own faster timer.
    static uint8_t vtick = 0;
    if (++vtick >= 2) { vtick = 0; invArea(0, 36, Wd - 1, 313); }
}
static void wifiTick_cb(lv_timer_t *t) {
    if (wifiPoll() && view == V_SETTINGS && !standby) lv_obj_invalidate(scr);
}

