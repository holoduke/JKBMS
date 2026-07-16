// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
// ============================================================================
//  Sleep animation — drawn straight to the canvas (full flush), like the original
// ============================================================================
static uint16_t c565(uint32_t hex) { return gfx->color565((hex >> 16) & 0xff, (hex >> 8) & 0xff, hex & 0xff); }
static uint16_t dimC(uint8_t r, uint8_t gg, uint8_t b, uint8_t br) { return gfx->color565((r * br) / 255, (gg * br) / 255, (b * br) / 255); }
static uint16_t wheel(float h) {
    h = fmodf(h, 1.0f); if (h < 0) h += 1.0f;
    float r = fabsf(h * 6 - 3) - 1, g = 2 - fabsf(h * 6 - 2), b = 2 - fabsf(h * 6 - 4);
    auto cl = [](float v) { return v < 0 ? 0.0f : v > 1 ? 1.0f : v; };
    return gfx->color565((uint8_t)(cl(r) * 255), (uint8_t)(cl(g) * 255), (uint8_t)(cl(b) * 255));
}
static void drawIco(int cx, int cy, float scale, float ax, float ay, float az, float hue) {
    static const float t = 1.61803f;
    static const float BV[12][3] = {{-1,t,0},{1,t,0},{-1,-t,0},{1,-t,0},{0,-1,t},{0,1,t},{0,-1,-t},{0,1,-t},{t,0,-1},{t,0,1},{-t,0,-1},{-t,0,1}};
    static const uint8_t F[20][3] = {{0,11,5},{0,5,1},{0,1,7},{0,7,10},{0,10,11},{1,5,9},{5,11,4},{11,10,2},{10,7,6},{7,1,8},{3,9,4},{3,4,2},{3,2,6},{3,6,8},{3,8,9},{4,9,5},{2,4,11},{6,2,10},{8,6,7},{9,8,1}};
    float rx[12], ry[12], rz[12]; int px[12], py[12];
    float ca = cosf(ax), sa = sinf(ax), cb = cosf(ay), sb = sinf(ay), cc = cosf(az), sc = sinf(az);
    const float d = 4.0f;
    for (int i = 0; i < 12; i++) {
        float x = BV[i][0], y = BV[i][1], z = BV[i][2];
        float y1 = y * ca - z * sa, z1 = y * sa + z * ca;
        float x2 = x * cb + z1 * sb, z2 = -x * sb + z1 * cb;
        float x3 = x2 * cc - y1 * sc, y3 = x2 * sc + y1 * cc;
        rx[i] = x3; ry[i] = y3; rz[i] = z2;
        float p = d / (d - z2);
        px[i] = cx + (int)(x3 * scale * p); py[i] = cy + (int)(y3 * scale * p);
    }
    const float lx = 0.40f, ly = 0.50f, lz = 0.77f;
    int order[20]; float fz[20]; int n = 0;
    for (int f = 0; f < 20; f++) {
        int a = F[f][0], b = F[f][1], c = F[f][2];
        long area = (long)(px[b] - px[a]) * (py[c] - py[a]) - (long)(py[b] - py[a]) * (px[c] - px[a]);
        if (area <= 0) continue;
        order[n] = f; fz[n] = rz[a] + rz[b] + rz[c]; n++;
    }
    for (int i = 1; i < n; i++) { int oo = order[i]; float ff = fz[i]; int k = i - 1; while (k >= 0 && fz[k] > ff) { fz[k+1] = fz[k]; order[k+1] = order[k]; k--; } order[k+1] = oo; fz[k+1] = ff; }
    for (int i = 0; i < n; i++) {
        int f = order[i], a = F[f][0], b = F[f][1], c = F[f][2];
        float ux = rx[b]-rx[a], uy = ry[b]-ry[a], uz = rz[b]-rz[a];
        float vx = rx[c]-rx[a], vy = ry[c]-ry[a], vz = rz[c]-rz[a];
        float nx = uy*vz-uz*vy, ny = uz*vx-ux*vz, nz = ux*vy-uy*vx;
        float nl = sqrtf(nx*nx+ny*ny+nz*nz); if (nl < 1e-3f) nl = 1;
        float diff = (nx*lx + ny*ly + nz*lz) / nl; if (diff < 0) diff = -diff;
        float br = 0.22f + 0.78f * diff; if (br > 1) br = 1;
        uint16_t base = wheel(hue + f * 0.013f);
        uint8_t rr = ((base >> 11) & 0x1f) << 3, gg = ((base >> 5) & 0x3f) << 2, bb = (base & 0x1f) << 3;
        gfx->fillTriangle(px[a], py[a], px[b], py[b], px[c], py[c], gfx->color565((uint8_t)(rr*br), (uint8_t)(gg*br), (uint8_t)(bb*br)));
    }
    uint16_t ec = dimC(0xff, 0xff, 0xff, 70);
    for (int i = 0; i < n; i++) { int f = order[i], a = F[f][0], b = F[f][1], c = F[f][2]; gfx->drawTriangle(px[a], py[a], px[b], py[b], px[c], py[c], ec); }
}
// Robot-vision power-OFF: the image collapses vertically into a bright scan line,
// flickers, retracts horizontally to a dot, then blinks out — the reverse of
// playVisionOn(). Ends with the backlight at its lowest (restored on wake).
static void playSleepAnimation() {
    const uint16_t BG = gfx->color565(0x09, 0x03, 0x02);
    const uint16_t AMBER = gfx->color565(0xff, 0xb0, 0x28), GLOW = gfx->color565(0x70, 0x40, 0x12);
    const uint16_t WHITE = gfx->color565(0xff, 0xf0, 0xd0);
    int cx = Wd / 2, cy = Ht / 2;
    uint32_t t0 = millis();                                   // vertical collapse → horizontal line
    for (;;) {
        uint32_t el = millis() - t0; float p = el / 300.0f; if (p > 1) p = 1;
        int hh = (int)((1 - p) * cy);                         // half-height shrinks to 0
        uint8_t v = (uint8_t)(60 + 195 * p);                  // brightens as it concentrates
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - hh, Wd, hh * 2 + 2, gfx->color565(v, (uint8_t)(v * 0.85f), (uint8_t)(v * 0.5f)));
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    for (int f = 0; f < 3; f++) {                             // flicker
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - 2, Wd, 4, (f & 1) ? AMBER : WHITE);
        gfx->flush(); uint32_t b = millis(); while (millis() - b < 45) delay(1);
    }
    uint32_t t1 = millis();                                   // line retracts to a dot
    for (;;) {
        uint32_t el = millis() - t1; float p = el / 360.0f; if (p > 1) p = 1;
        int hw = (int)((1 - p) * (1 - p) * (Wd / 2));         // ease-out retract
        int gh = 3 + (int)(5 * p), core = hw < 6 ? hw : 6;
        gfx->fillScreen(BG);
        gfx->fillRect(cx - hw - 2, cy - gh, (hw + 2) * 2, gh * 2, GLOW);
        gfx->fillRect(cx - hw, cy - 2, hw * 2 + 1, 4, AMBER);
        gfx->fillRect(cx - core, cy - 1, core * 2 + 1, 2, WHITE);
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    for (int f = 0; f < 2; f++) {                             // dot blinks out
        gfx->fillScreen(BG); int r = 4 - f * 2; if (r > 0) gfx->fillCircle(cx, cy, r, WHITE);
        gfx->flush(); uint32_t b = millis(); while (millis() - b < 55) delay(1);
    }
    gfx->fillScreen(BG); gfx->flush();
    ledcWrite(TFT_BL, 0); appliedB = 0;                       // backlight off (lowest) until a touch wakes us
    standby = true;
}

// centred bitmap text straight on the canvas (used by the boot animation)
static void ctc(const char *s, int cx, int cy, uint8_t size, uint16_t col) {
    int16_t x1, y1; uint16_t w, h; gfx->setTextSize(size); gfx->getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
    gfx->setTextColor(col); gfx->setCursor(cx - w / 2 - x1, cy - h / 2 - y1); gfx->print(s);
}
// jagged lightning bolt from (x1,y1) to (x2,y2)
static void tl(int x1, int y1, int x2, int y2, uint16_t c) {   // 2px line
    gfx->drawLine(x1, y1, x2, y2, c); gfx->drawLine(x1, y1 + 1, x2, y2 + 1, c);
}
// Round-capped thick line — gives the ninja solid, tapered limbs (not 2px sticks).
static void thickLine(int x1, int y1, int x2, int y2, int th, uint16_t c) {
    int n = abs(x2 - x1) > abs(y2 - y1) ? abs(x2 - x1) : abs(y2 - y1); if (n < 1) n = 1;
    int r = th / 2; if (r < 1) r = 1;
    for (int i = 0; i <= n; i++) gfx->fillCircle(x1 + (x2 - x1) * i / n, y1 + (y2 - y1) * i / n, r, c);
}
// Red ninja in a leaning run: hooded head + eye-slit + headband tails, solid
// tapered torso tilted forward, thick bent-knee legs (back leg kicks up behind),
// swinging bent arms. air = mid-leap (knees tucked).
static void drawNinja(int cx, int footY, float run, bool air, float sc) {
    uint16_t body = gfx->color565(0xcc, 0x22, 0x22), limb = gfx->color565(0x8c, 0x16, 0x16);
    uint16_t scarf = gfx->color565(0xff, 0x55, 0x55), blade = gfx->color565(0xcf, 0xd8, 0xe6);
    uint16_t skin = gfx->color565(0xe6, 0xc2, 0xa0);
    int hipY = footY - (int)(24 * sc), shY = footY - (int)(44 * sc);
    int lean = (int)(11 * sc), shCx = cx + lean;          // shoulders/head lean forward over the hips
    int headX = shCx + (int)(2 * sc), headY = shY - (int)(9 * sc), hr = (int)(9 * sc);
    int legTh = (int)(7 * sc), armTh = (int)(6 * sc), thigh = (int)(13 * sc), shin = (int)(13 * sc);
    float sw = sinf(run * 6.2832f);                       // stride phase (-1..1)
    // bent-knee leg. s>0 = leg reaching forward-down, s<0 = leg kicking up behind.
    auto drawLeg = [&](float s, uint16_t col) {
        float ta = s * 0.85f, bend = 0.55f + 0.85f * (0.5f - 0.5f * s);
        int kx = cx + (int)(sinf(ta) * thigh), ky = hipY + (int)(cosf(ta) * thigh);
        float sa = ta - bend;
        int fx = kx + (int)(sinf(sa) * shin), fy = ky + (int)(cosf(sa) * shin);
        thickLine(cx, hipY, kx, ky, legTh, col);
        thickLine(kx, ky, fx, fy, legTh, col);
        gfx->fillRect(fx - (int)(2 * sc), fy - (int)(2 * sc), (int)(9 * sc), (int)(4 * sc), col);
    };
    auto drawLegTuck = [&](float s, uint16_t col) {      // knees pulled up while airborne
        int kx = cx + (int)(s * 11 * sc), ky = hipY + (int)(1 * sc);
        int fx = kx + (int)(s * 3 * sc), fy = ky - (int)(11 * sc);
        thickLine(cx, hipY, kx, ky, legTh, col);
        thickLine(kx, ky, fx, fy, legTh, col);
    };
    // bent arm swinging from the (leaning) shoulder.
    auto drawArm = [&](float s, uint16_t col) {
        float ua = s * 0.95f;
        int ex = shCx + (int)(sinf(ua) * 9 * sc), ey = shY + (int)(7 * sc) + (int)(cosf(ua) * 4 * sc);
        float fa = ua + 1.15f;
        int hx = ex + (int)(sinf(fa) * 9 * sc), hy = ey + (int)(cosf(fa) * 7 * sc);
        thickLine(shCx, shY + (int)(3 * sc), ex, ey, armTh, col);
        thickLine(ex, ey, hx, hy, armTh, col);
    };
    // back limbs first (darker, behind torso); legs & arms swing opposite
    if (air) { drawLegTuck(-0.8f, limb); drawArm(-1.3f, limb); }
    else { drawLeg(-sw, limb); drawArm(sw, limb); }
    // katana across the (leaning) back
    thickLine(shCx - (int)(4 * sc), shY + (int)(1 * sc), shCx - (int)(13 * sc), shY + (int)(20 * sc), (int)(3 * sc), blade);
    // solid tapered torso, tilted forward (hips at cx, shoulders at shCx)
    gfx->fillTriangle(cx - (int)(7 * sc), hipY, cx + (int)(7 * sc), hipY, shCx + (int)(5 * sc), shY, body);
    gfx->fillTriangle(cx - (int)(7 * sc), hipY, shCx + (int)(5 * sc), shY, shCx - (int)(5 * sc), shY, body);
    gfx->fillRect(cx - (int)(7 * sc), hipY - (int)(2 * sc), (int)(14 * sc), (int)(3 * sc), gfx->color565(0x40, 0x0a, 0x0a)); // belt
    // head (hood + eye-slit + headband + flowing tails)
    gfx->fillCircle(headX, headY, hr, body);
    gfx->fillRect(headX + (int)(1 * sc), headY - (int)(1 * sc), (int)(7 * sc), (int)(3 * sc), skin);   // eye slit
    gfx->fillRect(headX - hr, headY - (int)(4 * sc), 2 * hr, (int)(3 * sc), scarf);                     // band
    for (int k = 0; k < 3; k++) { int x1 = headX - hr - (int)((4 + k * 7) * sc), y1 = headY - (int)(2 * sc) + (int)(7 * sc * sinf(run * 6.2832f * 1.5f + k)); tl(headX - hr, headY - (int)(2 * sc), x1, y1, scarf); }
    // front limbs (brighter, in front of torso)
    if (air) { drawArm(1.3f, body); drawLegTuck(0.8f, body); }
    else { drawArm(-sw, body); drawLeg(sw, body); }
}
// Draw the parallax city scene + ninja for boot time t (0..0.82 on-screen).
static int bootSx[44], bootSy[44]; static bool bootInit = false;
static void drawBootScene(float t) {
    const int W = Wd, H = Ht, groundY = 250;
    if (!bootInit) { for (int i = 0; i < 44; i++) { bootSx[i] = (i * 97) % W; bootSy[i] = (i * 53) % 70 + 4; } bootInit = true; }
    // sky gradient (dark blue → near black at top)
    for (int b = 0; b < 6; b++) gfx->fillRect(0, b * 12, W, 12, gfx->color565(3 + b, 4 + b, 10 + b * 2));
    gfx->fillRect(0, 72, W, groundY - 72, gfx->color565(7, 8, 20));
    gfx->fillCircle(W - 70, 56, 26, gfx->color565(0x40, 0x44, 0x60));      // moon
    gfx->fillCircle(W - 62, 50, 26, gfx->color565(7, 8, 20));              // crescent cut
    float scF = t * W * 0.5f;                                              // stars (far parallax)
    for (int i = 0; i < 44; i++) { int x = ((int)(bootSx[i] - scF * (0.3f + (i % 3) * 0.15f))) % W; if (x < 0) x += W; gfx->drawPixel(x, bootSy[i], dimC(0x9d, 0xb4, 0xff, 110 + (i % 4) * 35)); }
    float bc = fmodf(t * W * 1.6f, 1120);                                  // buildings (mid) + windows
    for (int i = -1; i < 16; i++) {
        int bx = (int)(i * 70 - bc), bh = 44 + (((i + 16) * 53) % 86), bw = 36 + (((i + 16) * 37) % 26);
        gfx->fillRect(bx, groundY - bh, bw, bh, gfx->color565(14, 15, 28));
        for (int wy = groundY - bh + 6; wy < groundY - 6; wy += 12)
            for (int wx = bx + 5; wx < bx + bw - 4; wx += 10)
                if (((wx * 7 + wy * 13 + i) % 5) < 2) gfx->fillRect(wx, wy, 4, 5, gfx->color565(0x6a, 0x5a, 0x20));
    }
    for (int i = 0; i < 18; i++) {                                         // speed lines (fast)
        float r = fmodf(t * 3.4f * (0.6f + (i % 5) * 0.12f) + i * 0.137f, 1.0f);
        int x = (int)((1 - r) * (W + 90)) - 90, y = (i * 113) % H, len = 26 + (int)(80 * r);
        gfx->drawFastHLine(x, y, len, dimC(0xff, 0x44, 0x44, (uint8_t)(45 + 140 * r)));
    }
    gfx->fillRect(0, groundY, W, H - groundY, gfx->color565(9, 10, 18));
    gfx->drawFastHLine(0, groundY, W, gfx->color565(0x80, 0x14, 0x14));
    float gc = fmodf(t * W * 2.8f, 40);                                    // ground dashes (fastest)
    for (int i = -1; i < W / 40 + 1; i++) gfx->drawFastHLine((int)(i * 40 - gc), groundY + 8, 20, dimC(0xff, 0x30, 0x30, 90));
    // ninja: runs in place (world scrolls), then leaps OFF the top-right
    int nx, ny; bool air;
    if (t < 0.60f) { nx = 150; ny = groundY; air = false; }
    else { float a = (t - 0.60f) / 0.22f; if (a > 1) a = 1; nx = 150 + (int)(a * (W - 60)); ny = groundY - (int)(a * (groundY + 120)); air = true; }
    drawNinja(nx, ny, t * 8.0f, air, 1.7f);
}
// Power-on: fast parallax city, a running ninja leaps off-screen, then flashes.
static void playBootAnimation() {
    uint32_t t0 = millis(); const float DUR = 3000.0f;
    for (;;) {
        float t = (millis() - t0) / DUR; if (t >= 1.0f) break;
        setBrightness((int)(20 + 80 * (t < 0.7f ? t / 0.7f : 1.0f)));
        if (t < 0.82f) drawBootScene(t);                                   // scene + leap-out
        else { float f = (t - 0.82f) / 0.18f; if (f > 1) f = 1; uint8_t w = (uint8_t)(255 * (1.0f - f) + 4); gfx->fillScreen(gfx->color565(w, w, w)); }  // one flash, fades to bg
        gfx->flush();
    }
    gfx->fillScreen(c565(C_BG)); gfx->flush();                             // hand off to the app
    setBrightness(brightness);
}
// Robot-vision power-on: a single dot swells into a full-width scan line, flickers,
// then blooms vertically into a fading flash — like an optical sensor coming online.
static void playVisionOn() {
    const uint16_t BG = gfx->color565(0x09, 0x03, 0x02);
    const uint16_t AMBER = gfx->color565(0xff, 0xb0, 0x28), GLOW = gfx->color565(0x70, 0x40, 0x12);
    const uint16_t WHITE = gfx->color565(0xff, 0xf0, 0xd0);
    int cx = Wd / 2, cy = Ht / 2;
    setBrightness(brightness);
    uint32_t t0 = millis();                                   // dot → horizontal line
    for (;;) {
        uint32_t el = millis() - t0; float p = el / 420.0f; if (p > 1) p = 1;
        int hw = (int)(p * p * (Wd / 2 - 2));                 // ease-in half-width
        int gh = 3 + (int)(5 * (1 - p));                      // glow thicker early (the dot)
        int core = hw < 6 ? hw : 6;
        gfx->fillScreen(BG);
        gfx->fillRect(cx - hw - 2, cy - gh, (hw + 2) * 2, gh * 2, GLOW);
        gfx->fillRect(cx - hw, cy - 2, hw * 2 + 1, 4, AMBER);
        gfx->fillRect(cx - core, cy - 1, core * 2 + 1, 2, WHITE);
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    for (int f = 0; f < 3; f++) {                             // quick flicker
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - 2, Wd, 4, (f & 1) ? WHITE : AMBER);
        gfx->flush(); uint32_t b = millis(); while (millis() - b < 45) delay(1);
    }
    uint32_t t1 = millis();                                   // vertical bloom + fade to black
    for (;;) {
        uint32_t el = millis() - t1; float p = el / 260.0f; if (p > 1) p = 1;
        int hh = (int)(p * cy);
        uint8_t v = (uint8_t)(255 * (1 - p) + 8);
        gfx->fillScreen(BG);
        gfx->fillRect(0, cy - hh, Wd, hh * 2, gfx->color565(v, (uint8_t)(v * 0.85f), (uint8_t)(v * 0.5f)));
        gfx->flush();
        if (p >= 1) break; delay(1);
    }
    gfx->fillScreen(BG); gfx->flush();
}
// Second act: a retro tactical-HUD boot log (Terminator-style) — amber pixel text
// on black with scanlines, status lines flipping to [ OK ], a progress bar and a
// blinking cursor, ending on READY. Built-in GFX font = chunky monospace look.
static void playHudBoot() {
    static const char *HUD[] = {
        "POWER CORE",
        "DISPLAY DRIVER",
        "TOUCH INTERFACE",
        "ESTABLISHING DATA LINK",
        "SECURING DATA LINK",
        "CONNECTING BATTERIES",
        "RECEIVING INPUT DATA",
        "WAITING FOR DATA",
        "SYSTEMS ONLINE",
    };
    const int N = sizeof(HUD) / sizeof(HUD[0]);
    const uint32_t STEP = 230, TAIL = 650, END = N * STEP + TAIL;
    const uint16_t AMBER = gfx->color565(0xff, 0xb0, 0x28), RED = gfx->color565(0xff, 0x38, 0x20);
    const uint16_t DIM = gfx->color565(0x4a, 0x16, 0x0e), BG = gfx->color565(0x09, 0x03, 0x02);
    setBrightness(brightness);
    uint32_t t0 = millis();
    for (;;) {
        uint32_t el = millis() - t0;
        gfx->fillScreen(BG);
        for (int y = (el / 70) % 3; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);   // scrolling scanlines
        // header + rule
        gfx->setTextSize(2); gfx->setTextColor(RED); gfx->setCursor(14, 12); gfx->print("JK-BMS TACTICAL MONITOR");
        gfx->drawFastHLine(14, 36, Wd - 28, RED); gfx->drawFastHLine(14, 38, Wd - 28, DIM);
        // targeting reticle, tucked in the top-right corner (clear of the status tags)
        int rx = Wd - 26, ry = 18;
        gfx->drawCircle(rx, ry, 12, AMBER); gfx->drawCircle(rx, ry, 4, RED);
        gfx->drawFastHLine(rx - 12, ry, 24, AMBER); gfx->drawFastVLine(rx, ry - 12, 24, AMBER);
        // log lines
        int shown = el / STEP; if (shown > N) shown = N;
        gfx->setTextSize(2);
        for (int i = 0; i < shown; i++) {
            int ly = 54 + i * 24;
            bool ok = el > (i + 1) * STEP + 60;                  // [ .. ] then flips to [ OK ]
            gfx->setTextColor(AMBER); gfx->setCursor(16, ly); gfx->print(HUD[i]);
            gfx->setTextColor(ok ? AMBER : RED); gfx->setCursor(Wd - 16 - 72, ly); gfx->print(ok ? "[ OK ]" : "[ .. ]");
        }
        if (shown < N && ((el / 320) & 1)) { gfx->fillRect(16, 54 + shown * 24, 13, 17, AMBER); }   // cursor
        // progress bar
        int bx = 16, by = Ht - 24, bw = Wd - 32;
        float p = (float)el / END; if (p > 1) p = 1;
        gfx->drawRect(bx, by, bw, 14, RED);
        gfx->fillRect(bx + 2, by + 2, (int)((bw - 4) * p), 10, AMBER);
        gfx->setTextSize(1); gfx->setTextColor(AMBER); gfx->setCursor(bx, by - 12);
        char pc[8]; snprintf(pc, sizeof(pc), "%d%%", (int)(p * 100)); gfx->print(pc);
        gfx->flush();
        if (el > END) break;
        delay(1);
    }
    // "READY" with dots building up one by one
    uint32_t r0 = millis();
    for (;;) {
        uint32_t el = millis() - r0; if (el > 950) break;
        gfx->fillScreen(BG);
        for (int y = (el / 70) % 3; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);
        int dots = el / 150; if (dots > 5) dots = 5;
        char buf[12] = "READY"; for (int i = 0; i < dots; i++) buf[5 + i] = '.'; buf[5 + dots] = 0;
        gfx->setTextSize(4); gfx->setTextColor(RED);
        gfx->setCursor((Wd - 5 * 24) / 2, (Ht - 32) / 2); gfx->print(buf);   // size4 → 24px/char
        gfx->flush(); delay(1);
    }
    gfx->fillScreen(c565(C_BG)); gfx->flush();   // hand off to the app
}

// ============================================================================
//  Idle / "no battery detected" screens (gfx-direct, animated; chosen in Settings)
// ============================================================================
static bool idleActiveNow() {
    if (idleScreen == 0 || standby || kbActive) return false;    // no screensaver selected / asleep / typing
    if (view != V_BMS1 && view != V_BMS2) return false;          // only over a dashboard view
    uint32_t idleFor = millis() - lastActivity;
    if (saverAfterSec > 0 && idleFor > (uint32_t)saverAfterSec * 1000UL) {   // timed screensaver (regardless of data)
        if (saverShowSec <= 0) return true;                                 // classic: stays until a tap
        // Loop mode: after the saver shows for saverShowSec it auto-returns to the dashboard for
        // another saverAfterSec, then re-triggers — no touch needed. Phase within the repeating
        // (show saverShowSec, then dashboard saverAfterSec) cycle that starts at first activation.
        uint32_t X = (uint32_t)saverAfterSec * 1000UL, Y = (uint32_t)saverShowSec * 1000UL;
        uint32_t phase = (idleFor - X) % (X + Y);
        return phase < Y;                                                   // first Y of each cycle = screensaver, rest = dashboard
    }
    if (demoMode) return false;                                  // demo always has data → only the timed saver applies
    for (int t = 0; t < numBms; t++) if (bmsLive[t]) return false;   // a pack is answering → keep the real UI
    return idleFor > IDLE_DELAY;                                 // no data + settle after the last touch
}
static void idleText(int x, int y, const char *s, uint8_t sz, uint16_t c) {
    gfx->setTextSize(sz); gfx->setTextColor(c); gfx->setCursor(x, y); gfx->print(s);
}
// 1) Looping tactical HUD — scanlines, cycling status lines, link bar, reticle.
static void renderHudIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x09, 0x03, 0x02), AMBER = gfx->color565(0xff, 0xb0, 0x28);
    const uint16_t RED = gfx->color565(0xff, 0x38, 0x20), DIM = gfx->color565(0x4a, 0x16, 0x0e);
    gfx->fillScreen(BG);
    for (int y = (ms / 70) % 3; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);
    idleText(14, 12, "SECURITY INTERFACE MONITOR", 2, RED);
    gfx->drawFastHLine(14, 36, Wd - 28, RED); gfx->drawFastHLine(14, 38, Wd - 28, DIM);
    int rx = Wd - 26, ry = 18; float a = ms * 0.004f;            // sweeping reticle, tucked in the top-right corner
    gfx->drawCircle(rx, ry, 12, AMBER); gfx->drawCircle(rx, ry, 4, RED);
    gfx->drawLine(rx, ry, rx + (int)(12 * cosf(a)), ry + (int)(12 * sinf(a)), AMBER);
    static const char *L[] = {"SCANNING BATTERY BUS", "PROBING BMS NODES", "NO BATTERY DETECTED"};
    int shown = ((ms / 700) % 5) + 1; if (shown > 3) shown = 3;
    for (int i = 0; i < shown; i++) {
        int ly = 56 + i * 24; bool last = (i == shown - 1);
        idleText(16, ly, L[i], 2, AMBER);
        char dots[4] = "   "; int nd = (ms / 300) % 4; for (int d = 0; d < nd && d < 3; d++) dots[d] = '.';
        idleText(Wd - 16 - 72, ly, last ? dots : "[ -- ]", 2, last ? RED : AMBER);
    }
    // prominent waiting banner (pulsing)
    if (((ms / 450) & 1)) {
        char wd[24] = "WAITING FOR DATA"; int nd = (ms / 300) % 4; int l = strlen(wd);
        for (int d = 0; d < nd && d < 3; d++) wd[l + d] = '.';
        idleText(Wd / 2 - (strlen(wd) * 18) / 2, 160, wd, 3, RED);
    }
    int bx = 16, by = Ht - 24, bw = Wd - 32;                     // looping link bar
    gfx->drawRect(bx, by, bw, 14, RED);
    float p = (ms % 1800) / 1800.0f;
    gfx->fillRect(bx + 2, by + 2, (int)((bw - 4) * p), 10, AMBER);
    idleText(bx, by - 14, "BATTERY DATA LINK", 1, AMBER);
    if (((ms / 500) & 1)) idleText(Wd - 80, by - 14, "tap for menu", 1, DIM);
}
// 2) System-initialisation screen — grid, ring %, four loaders, hex stream.
static void renderInitIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x03, 0x05, 0x0c), CY = gfx->color565(0x3d, 0xf0, 0xa8);
    const uint16_t BL = gfx->color565(0x12, 0x2a, 0x40), TX = gfx->color565(0xcf, 0xe6, 0xff);
    const uint16_t OK = gfx->color565(0x46, 0xff, 0x6a), RD = gfx->color565(0xff, 0x3a, 0x2a);
    gfx->fillScreen(BG);
    for (int x = 0; x < Wd; x += 30) gfx->drawFastVLine(x, 0, Ht, BL);      // grid
    for (int y = 0; y < Ht; y += 30) gfx->drawFastHLine(0, y, Wd, BL);
    idleText(14, 8, "BATTERY LINK INITIALISATION", 2, CY);
    // 7 fake init steps complete, then the battery connect stalls and fails at 95%
    static const char *NM[8] = {"BOOT VECTOR", "KERNEL MODULES", "SECURE ENCLAVE", "AES-256 KEYRING",
                                "PACKET INSPECTOR", "TELEMETRY DECODER", "BUS ARBITRATION", "CONNECTING TO BATTERY"};
    const int N = 8;
    uint32_t CYCLE = 13000, t = ms % CYCLE, LOAD = 9000;
    bool failed = (t >= LOAD);
    float prog = failed ? 95.0f : 95.0f * t / LOAD;            // climbs 0→95, then halts
    for (int i = 0; i < N; i++) {
        float lo = (i < 7) ? i * 85.0f / 7.0f : 85.0f;         // first 7 share 0..85%, battery is 85..100%
        float hi = (i < 7) ? (i + 1) * 85.0f / 7.0f : 100.0f;
        if (prog < lo) break;                                  // reveal one row at a time
        float fill = (prog - lo) / (hi - lo); if (fill > 1) fill = 1; if (fill < 0) fill = 0;
        // centered block: label | bar | status
        int y = 34 + i * 20, lblX = 66, bx = 216, bw = 150, bh = 8;
        bool isBat = (i == 7);
        idleText(lblX, y, NM[i], 1, TX);
        gfx->drawRect(bx, y - 1, bw, bh, BL);
        gfx->fillRect(bx + 1, y, (int)((bw - 2) * fill), bh - 2, (isBat && failed) ? RD : CY);
        int stx = bx + bw + 10;
        if (isBat && failed) idleText(stx, y, "FAIL", 1, RD);
        else if (fill >= 1.0f) idleText(stx, y, "OK", 1, OK);
        else { char d[4] = "   "; int nd = (ms / 200) % 4; for (int k = 0; k < nd && k < 3; k++) d[k] = '.'; idleText(stx, y, d, 1, CY); }
    }
    char pc[6]; snprintf(pc, sizeof(pc), "%d%%", (int)(prog + 0.5f));   // big % centered below loaders
    idleText((Wd - (int)strlen(pc) * 18) / 2, 208, pc, 3, failed ? RD : TX);
    if (failed && ((ms / 400) & 1)) {                          // fail banner, centered below the %
        const char *f = "FAILED TO INITIALIZE";
        idleText((Wd - (int)strlen(f) * 12) / 2, 250, f, 2, RD);
    }
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, BL);
}
// 3) Sensor radar / scope standby — rotating sweep, blips, scrolling waveform.
static void renderRadarIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x02, 0x08, 0x05), GR = gfx->color565(0x12, 0x3a, 0x22);
    const uint16_t GRN = gfx->color565(0x3d, 0xf0, 0x90), TX = gfx->color565(0xbf, 0xe6, 0xcf);
    const uint16_t OK = gfx->color565(0x46, 0xff, 0x6a);
    gfx->fillScreen(BG);
    idleText(14, 12, "BATTERY SENSOR ARRAY", 2, GRN);
    // --- radar, confined to the left half so it never overlaps the log ---
    int cx = 98, cy = 192, R = 90; float a = ms * 0.003f;
    for (int r = R / 3; r <= R; r += R / 3) gfx->drawCircle(cx, cy, r, GR);  // rings
    gfx->drawLine(cx - R, cy, cx + R, cy, GR); gfx->drawLine(cx, cy - R, cx, cy + R, GR);
    for (int k = 0; k < R; k += 3) gfx->drawLine(cx, cy, cx + (int)(k * cosf(a)), cy + (int)(k * sinf(a)), GRN);  // sweep
    for (int i = 0; i < 4; i++) {                               // fading blips
        float ba = i * 1.9f, br = 26 + (i * 21) % (R - 18);
        float age = fmodf(a - ba, 6.2832f); if (age < 0) age += 6.2832f;
        if (age < 1.2f) gfx->fillCircle(cx + (int)(br * cosf(ba)), cy + (int)(br * sinf(ba)), 3, GRN);
    }
    // --- right column: mini scope + secure-link log ---
    int lx = 200, gx = lx, gw = Wd - lx - 10, gy = 40, gh = 44;
    gfx->drawRect(gx, gy, gw, gh, GR);
    int px = -1, py = -1;
    for (int i = 0; i < gw - 4; i++) {
        float v = sinf((i + ms * 0.08f) * 0.16f) * 0.5f + sinf((i + ms * 0.05f) * 0.4f) * 0.2f;
        int wx = gx + 2 + i, wy = gy + gh / 2 - (int)(v * (gh / 2 - 4));
        if (px >= 0) gfx->drawLine(px, py, wx, wy, GRN); px = wx; py = wy;
    }
    static const char *L[] = {"SERIAL LINK 115200", "AES-256 ENCRYPTION", "BMS HANDSHAKE 0x90EB",
                              "DECRYPTING TELEMETRY", "CRC16 VALIDATION", "CONNECTING TO BATTERY"};
    const int N = 6;
    const uint16_t RD = gfx->color565(0xff, 0x3a, 0x2a);
    uint32_t CYCLE = 9000, t = ms % CYCLE, LOAD = 6000;          // load ~6s, then fail held ~3s, loop
    bool failed = (t >= LOAD);
    int shown = failed ? N : (int)(t / (LOAD / N)) + 1; if (shown > N) shown = N;
    int rxs = Wd - 10;
    for (int i = 0; i < shown; i++) {
        int ly = 96 + i * 20; bool isLast = (i == N - 1);
        idleText(lx, ly, L[i], 1, TX);
        char dots[4] = "   "; int nd = (ms / 200) % 4; for (int d = 0; d < nd && d < 3; d++) dots[d] = '.';
        if (isLast && failed) idleText(rxs - 24, ly, "FAIL", 1, RD);
        else if (i < shown - 1) idleText(rxs - 12, ly, "OK", 1, OK);  // done → green
        else idleText(rxs - 18, ly, dots, 1, GRN);                    // in progress
    }
    if (failed && ((ms / 400) & 1)) {                           // red FAILED below the list (~3s window)
        const char *f = "FAILED";
        idleText(lx + ((Wd - lx) - (int)strlen(f) * 12) / 2, 96 + N * 20 + 10, f, 2, RD);
    }
    idleText(14, Ht - 14, "no battery signal", 1, GR);
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, GR);
}
// 4) Retro arcade GAME OVER — dead-battery sprite, blinking INSERT COIN, jokes.
static void renderArcadeIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0, 0, 0), RED = gfx->color565(0xff, 0x30, 0x28);
    const uint16_t WHT = gfx->color565(0xf0, 0xf0, 0xf0), YEL = gfx->color565(0xff, 0xd0, 0x30);
    const uint16_t GRY = gfx->color565(0x66, 0x6c, 0x78), DIM = gfx->color565(0x1c, 0x1c, 0x1c);
    gfx->fillScreen(BG);
    for (int y = 0; y < Ht; y += 3) gfx->drawFastHLine(0, y, Wd, DIM);     // scanlines
    idleText(10, 8, "1UP", 1, RED); idleText(40, 8, "00000000", 1, WHT);
    idleText(Wd - 96, 8, "HI 00009999", 1, WHT);
    const char *go = "GAME OVER"; int sh = (ms / 120) % 2;                 // tiny shake
    uint16_t goCol = wheel((ms % 60000) / 60000.0f);                       // slow full-hue cycle (~60s)
    idleText((Wd - (int)strlen(go) * 30) / 2, 64 + sh, go, 5, goCol);
    // dead battery sprite (X eyes + flat mouth)
    int cx = Wd / 2, bw = 80, bh = 42, bx = cx - bw / 2, by = 132;
    gfx->drawRect(bx, by, bw, bh, GRY); gfx->drawRect(bx + 1, by + 1, bw - 2, bh - 2, GRY);
    gfx->fillRect(bx + bw, by + bh / 2 - 7, 6, 14, GRY);
    int e1 = bx + 24, e2 = bx + bw - 24, ey = by + 16;
    for (int o = 0; o < 2; o++) {
        gfx->drawLine(e1 - 6, ey - 6 + o, e1 + 6, ey + 6 + o, WHT); gfx->drawLine(e1 - 6, ey + 6 + o, e1 + 6, ey - 6 + o, WHT);
        gfx->drawLine(e2 - 6, ey - 6 + o, e2 + 6, ey + 6 + o, WHT); gfx->drawLine(e2 - 6, ey + 6 + o, e2 + 6, ey - 6 + o, WHT);
    }
    gfx->drawLine(cx - 9, by + bh - 9, cx + 9, by + bh - 9, WHT);          // flat mouth
    if (((ms / 450) & 1)) { const char *ic = "INSERT COIN TO CONTINUE"; idleText((Wd - (int)strlen(ic) * 12) / 2, 210, ic, 2, YEL); }
    static const char *J[] = {"NO BATTERY DETECTED", "PLAYER 1 (BMS) HAS LEFT", "HAVE YOU TRIED PLUGGING IT IN?",
                              "DATA: NONE   VIBES: OK", "GIT GUD - CONNECT A BATTERY"};
    const char *j = J[(ms / 2200) % 5];
    idleText((Wd - (int)strlen(j) * 6) / 2, 244, j, 1, GRY);
    idleText(10, Ht - 14, "CREDIT 00", 1, YEL);
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, DIM);
}
// 5) Maximum-security control room — dial gauges, bar meters, threat graph, status.
static void renderSecurityIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x02, 0x06, 0x0c), GRID = gfx->color565(0x0b, 0x18, 0x26);
    const uint16_t CY = gfx->color565(0x32, 0xd8, 0xff), GN = gfx->color565(0x3d, 0xf0, 0x8a);
    const uint16_t AM = gfx->color565(0xff, 0xc0, 0x30), RD = gfx->color565(0xff, 0x44, 0x3a);
    const uint16_t TX = gfx->color565(0xbf, 0xd8, 0xe6), DIM = gfx->color565(0x16, 0x2a, 0x3a);
    gfx->fillScreen(BG);
    for (int x = 0; x < Wd; x += 24) gfx->drawFastVLine(x, 0, Ht, GRID);
    for (int y = 0; y < Ht; y += 24) gfx->drawFastHLine(0, y, Wd, GRID);
    idleText(14, 6, "MAXIMUM SECURITY MONITOR", 2, CY);
    idleText(Wd - 92, 8, "ARMED", 1, RD);
    if (((ms / 500) & 1)) gfx->fillCircle(Wd - 16, 13, 5, RD);
    // --- three dial gauges ---
    const char *GL[3] = {"CPU", "ENCRYPT", "UPLINK"}; uint16_t GC[3] = {CY, GN, AM}; float GP[3] = {0, 1.3f, 2.6f};
    for (int i = 0; i < 3; i++) {
        int cx = 80 + i * 160, cy = 92, r = 38;
        float v = 0.5f + 0.45f * sinf(ms * 0.001f + GP[i]);
        int fillTo = 180 + (int)(v * 180);
        for (int d = 180; d <= 360; d += 6) { float a = d * 0.01745f; gfx->fillCircle(cx + (int)(r * cosf(a)), cy + (int)(r * sinf(a)), 2, (d <= fillTo) ? GC[i] : DIM); }
        float na = (180 + v * 180) * 0.01745f;
        gfx->drawLine(cx, cy, cx + (int)((r - 6) * cosf(na)), cy + (int)((r - 6) * sinf(na)), GC[i]);
        gfx->fillCircle(cx, cy, 3, GC[i]);
        char val[6]; snprintf(val, sizeof(val), "%d%%", (int)(v * 100));
        idleText(cx - (int)strlen(val) * 3, cy + 8, val, 1, GC[i]);
        idleText(cx - (int)strlen(GL[i]) * 3, cy + 20, GL[i], 1, TX);
    }
    // --- threat-analysis scrolling graph ---
    int gx = 14, gy = 138, gw = 212, gh = 88;
    gfx->drawRect(gx, gy, gw, gh, DIM); idleText(gx + 6, gy + 4, "THREAT ANALYSIS", 1, TX);
    int px = -1, py = -1;
    for (int i = 0; i < gw - 4; i++) {
        float v = sinf((i + ms * 0.09f) * 0.13f) * 0.4f + sinf((i + ms * 0.05f) * 0.5f) * 0.18f;
        int sx = gx + 2 + i, sy = gy + gh / 2 + 6 - (int)(v * (gh / 2 - 10));
        if (px >= 0) gfx->drawLine(px, py, sx, sy, GN); px = sx; py = sy;
    }
    // --- vertical bar meters ---
    for (int i = 0; i < 6; i++) {
        int bx = 240 + i * 38, base = 226, h = 18 + (int)(58 * (0.5f + 0.5f * sinf(ms * 0.0022f + i * 0.9f)));
        uint16_t c = h > 64 ? RD : h > 42 ? AM : GN;
        gfx->drawRect(bx, base - 78, 22, 78, DIM);
        gfx->fillRect(bx + 2, base - h, 18, h, c);
    }
    idleText(240, 138, "SECTOR INTEGRITY", 1, TX);
    // --- status strip ---
    idleText(14, 240, "FIREWALL: ACTIVE", 1, GN);
    idleText(168, 240, "INTRUSION: NONE", 1, GN);
    idleText(320, 240, "CIPHER: AES-256", 1, CY);
    if (((ms / 400) & 1)) idleText(14, 258, "LOCKDOWN ENGAGED", 1, RD);
    idleText(180, 258, "BIOMETRIC LOCK OK", 1, GN);
    idleText(14, Ht - 14, "MAXIMUM SECURITY // ALL SYSTEMS NOMINAL", 1, DIM);
    if (((ms / 500) & 1)) idleText(Wd - 78, Ht - 14, "tap for menu", 1, DIM);
}
// 6) Nexus — battery command centre, "all systems nominal". Rotating reactor-core rings with
// orbiting satellites, live bar meters, a waveform, a drifting particle field, and a scrolling
// ticker of normal operating messages. No error/fault text — everything reads healthy.
static void renderNexusIdle(uint32_t ms) {
    const uint16_t BG = gfx->color565(0x02, 0x06, 0x0c), GRID = gfx->color565(0x08, 0x14, 0x1e);
    const uint16_t CY = gfx->color565(0x32, 0xd8, 0xff), GN = gfx->color565(0x3d, 0xf0, 0xa8);
    const uint16_t AM = gfx->color565(0xff, 0xc0, 0x30), TX = gfx->color565(0xbf, 0xd8, 0xe6);
    const uint16_t DIM = gfx->color565(0x14, 0x2a, 0x3a), STAR = gfx->color565(0x1c, 0x3a, 0x4e);
    gfx->fillScreen(BG);
    // drifting particle field (deterministic per index → cheap, no state)
    for (int i = 0; i < 46; i++) {
        int x = (i * 97 + (ms / 40) * (1 + (i & 3))) % Wd;
        int y = (i * 53) % Ht;
        gfx->drawPixel(x, y, STAR);
    }
    // slow parallax grid
    for (int x = -(int)((ms / 60) % 32); x < Wd; x += 32) gfx->drawFastVLine(x, 22, Ht - 22, GRID);
    for (int y = 24; y < Ht; y += 32) gfx->drawFastHLine(0, y, Wd, GRID);
    // header
    idleText(14, 8, "BATTERY COMMAND CENTER", 2, CY);
    if (((ms / 500) & 1)) gfx->fillCircle(Wd - 74, 13, 4, GN);
    idleText(Wd - 64, 8, "ONLINE", 1, GN);
    gfx->drawFastHLine(14, 26, Wd - 28, DIM);
    // --- reactor core: three counter-rotating ring arcs + orbiting satellites ---
    int cx = 92, cy = 168, r0 = 30, r1 = 48, r2 = 66;
    uint16_t rc[3] = {CY, GN, AM}; int rr[3] = {r2, r1, r0};
    float spd[3] = {0.0016f, -0.0026f, 0.004f}, span[3] = {4.2f, 3.4f, 5.2f};
    for (int k = 0; k < 3; k++) {
        float a0 = ms * spd[k] + k * 2.1f;
        int steps = 26;
        for (int s = 0; s < steps; s++) {
            float a = a0 + (span[k] * s / steps);
            gfx->fillCircle(cx + (int)(rr[k] * cosf(a)), cy + (int)(rr[k] * sinf(a)), 2, rc[k]);
        }
    }
    for (int i = 0; i < 3; i++) {                       // orbiting satellites
        float a = -ms * 0.0022f + i * 2.094f;
        gfx->fillCircle(cx + (int)(80 * cosf(a)), cy + (int)(80 * sinf(a) * 0.9f), 3, i == 0 ? CY : i == 1 ? GN : AM);
    }
    float pw = 0.5f + 0.5f * sinf(ms * 0.005f);         // pulsing core
    gfx->fillCircle(cx, cy, 10 + (int)(pw * 4), GN);
    gfx->fillCircle(cx, cy, 5, TX);
    idleText(cx - 30, cy + r2 + 8, "CORE LINK OK", 1, GN);
    // --- right column: live bar meters (all healthy) ---
    const char *ML[6] = {"PACK VOLTAGE", "PACK CURRENT", "CELL BALANCE", "MOSFET TEMP", "STATE OF CHG", "DATA LINK"};
    int bx = 210, bw = 210, by = 40, bh = 9;
    for (int i = 0; i < 6; i++) {
        int y = by + i * 24;
        float v = 0.45f + 0.42f * sinf(ms * 0.0015f + i * 0.8f);
        uint16_t c = (i == 4) ? GN : (i == 3 ? AM : CY);   // temp amber, SOC green, rest cyan — all nominal
        idleText(bx, y, ML[i], 1, TX);
        gfx->drawRect(bx, y + 9, bw, bh, DIM);
        gfx->fillRect(bx + 1, y + 10, (int)((bw - 2) * v), bh - 2, c);
        char pc[6]; snprintf(pc, sizeof(pc), "%d%%", (int)(v * 100));
        idleText(bx + bw + 6, y + 2, pc, 1, c);
    }
    // --- waveform strip under the meters ---
    int gx = bx, gy = by + 6 * 24 + 2, gw = bw, gh = 40;
    gfx->drawRect(gx, gy, gw, gh, DIM);
    int px = -1, py = -1;
    for (int i = 0; i < gw - 4; i++) {
        float v = sinf((i + ms * 0.09f) * 0.15f) * 0.42f + sinf((i + ms * 0.05f) * 0.42f) * 0.18f;
        int wx = gx + 2 + i, wy = gy + gh / 2 - (int)(v * (gh / 2 - 4));
        if (px >= 0) gfx->drawLine(px, py, wx, wy, GN); px = wx; py = wy;
    }
    // --- pulsing "ALL SYSTEMS NOMINAL" banner (left, under the core) ---
    if (((ms / 500) & 1)) idleText(14, Ht - 42, "ALL SYSTEMS NOMINAL", 1, GN);
    // --- scrolling ticker of normal operating messages (no errors) ---
    static const char *TK =
        "TELEMETRY STREAM 115200   //   AES-256 SECURE LINK   //   CELLS BALANCED   //   THERMALS NOMINAL   //   "
        "SOC ESTIMATOR LOCKED   //   COULOMB COUNTER SYNCED   //   BUS VOLTAGE STABLE   //   MOSFETS ENGAGED   //   "
        "CRC16 VERIFIED   //   HANDSHAKE 0x90EB OK   //   WATCHDOG HEALTHY   //   ALL PACKS RESPONDING   //   ";
    int tkw = (int)strlen(TK) * 6;                     // size-1 char = 6px
    int off = (ms / 30) % tkw;
    gfx->fillRect(0, Ht - 16, Wd, 16, gfx->color565(0x04, 0x0a, 0x12));
    idleText(-off, Ht - 12, TK, 1, CY);
    idleText(-off + tkw, Ht - 12, TK, 1, CY);          // second copy → seamless wrap
    if (((ms / 500) & 1)) idleText(Wd - 78, 8, "", 1, DIM);   // (reticle space reserved)
}
static void renderIdleFrame() {
    uint32_t ms = millis();
    if (idleScreen == 1) renderHudIdle(ms);
    else if (idleScreen == 2) renderInitIdle(ms);
    else if (idleScreen == 3) renderRadarIdle(ms);
    else if (idleScreen == 4) renderArcadeIdle(ms);
    else if (idleScreen == 6) renderNexusIdle(ms);
    else renderSecurityIdle(ms);
}

