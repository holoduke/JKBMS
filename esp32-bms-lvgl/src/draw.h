// Part of the JK BMS firmware — one translation unit; #included by main.cpp in dependency order.
static void fRect(int x, int y, int w, int h, int r, uint32_t col, lv_opa_t opa = LV_OPA_COVER) {
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_color = lv_color_hex(col); d.bg_opa = opa; d.radius = r;
    lv_area_t a = {x, y, x + w - 1, y + h - 1}; lv_draw_rect(L, &d, &a);
}
static void dRect(int x, int y, int w, int h, int r, uint32_t col) {  // border only
    lv_draw_rect_dsc_t d; lv_draw_rect_dsc_init(&d);
    d.bg_opa = LV_OPA_TRANSP; d.radius = r;
    d.border_color = lv_color_hex(col); d.border_width = 1; d.border_opa = LV_OPA_COVER;
    lv_area_t a = {x, y, x + w - 1, y + h - 1}; lv_draw_rect(L, &d, &a);
}
static void fCircle(int cx, int cy, int r, uint32_t col) { fRect(cx - r, cy - r, 2 * r, 2 * r, LV_RADIUS_CIRCLE, col); }
static void line(int x1, int y1, int x2, int y2, uint32_t col, lv_opa_t opa = LV_OPA_COVER, int wdt = 1) {
    lv_draw_line_dsc_t d; lv_draw_line_dsc_init(&d);
    d.color = lv_color_hex(col); d.opa = opa; d.width = wdt;
    d.p1.x = x1; d.p1.y = y1; d.p2.x = x2; d.p2.y = y2;
    lv_draw_line(L, &d);
}
// Graph area fill for one column: 3 stacked bands fading from the line down to the
// baseline, approximating a vertical gradient (brighter under the trace, faint below).
static void fillCol(int sx, int top, int base, uint32_t col) {
    int h = base - top; if (h <= 0) return;
    int s = h / 3;
    if (s < 1) { line(sx, top, sx, base, col, 60); return; }
    line(sx, top, sx, top + s, col, 80);
    line(sx, top + s, sx, top + 2 * s, col, 42);
    line(sx, top + 2 * s, sx, base, col, 16);
}
static void tri(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t col) {
    lv_draw_triangle_dsc_t d; lv_draw_triangle_dsc_init(&d);
    d.color = lv_color_hex(col); d.opa = LV_OPA_COVER;
    d.p[0].x = x1; d.p[0].y = y1; d.p[1].x = x2; d.p[1].y = y2; d.p[2].x = x3; d.p[2].y = y3;
    lv_draw_triangle(L, &d);
}
// --- small 10px card-title icons (drawn at the F10 title baseline) ---
static void icoBattery(int x, int y, uint32_t col) {   // capacity/energy
    dRect(x, y + 1, 11, 7, 1, col); fRect(x + 11, y + 3, 2, 3, 0, col); fRect(x + 2, y + 3, 5, 3, 0, col);
}
static void icoCells(int x, int y, uint32_t col) {     // cells = stacked bars
    for (int k = 0; k < 3; k++) fRect(x, y + 1 + k * 3, 10, 2, 1, col);
}
static void icoBolt(int x, int y, uint32_t col) {      // power = lightning bolt
    tri(x + 6, y, x + 1, y + 6, x + 5, y + 5, col);
    tri(x + 5, y + 4, x + 9, y + 4, x + 4, y + 10, col);
}
static void icoUpdate(int cx, int cy, uint32_t col) {  // download/update: down-arrow onto a tray
    line(cx, cy - 6, cx, cy + 1, col, LV_OPA_COVER, 2);
    tri(cx - 4, cy - 1, cx + 4, cy - 1, cx, cy + 4, col);
    line(cx - 5, cy + 6, cx + 5, cy + 6, col, LV_OPA_COVER, 2);
}
// Card background with a subtle top sheen (depth) + border. Replaces the flat fRect+dRect.
static void cardBg(int x, int y, int w, int h) {
    fRect(x, y, w, h, 8, C_CARD);
    fRect(x + 2, y + 2, w - 4, 7, 6, C_CARD_HI, 46);
    fRect(x + 2, y + 9, w - 4, 6, 0, C_CARD_HI, 22);
    dRect(x, y, w, h, 8, C_BORDER);
}
static void ring(int cx, int cy, int ro, int ri, int a0, int a1, uint32_t col) {
    lv_draw_arc_dsc_t d; lv_draw_arc_dsc_init(&d);
    d.color = lv_color_hex(col); d.width = ro - ri; d.opa = LV_OPA_COVER;
    d.center.x = cx; d.center.y = cy; d.radius = ro;
    d.start_angle = a0; d.end_angle = a1;
    lv_draw_arc(L, &d);
}
static void ringA(int cx, int cy, int ro, int ri, int a0, int a1, uint32_t col, lv_opa_t opa) {
    lv_draw_arc_dsc_t d; lv_draw_arc_dsc_init(&d);
    d.color = lv_color_hex(col); d.width = ro - ri; d.opa = opa;
    d.center.x = cx; d.center.y = cy; d.radius = ro;
    d.start_angle = a0; d.end_angle = a1;
    lv_draw_arc(L, &d);
}
static int textW(const char *s, const lv_font_t *f) {
    lv_point_t p; lv_text_get_size(&p, s, f, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE); return p.x;
}
static void lText(const char *s, int x, int y, const lv_font_t *f, uint32_t col) {  // top-left
    lv_draw_label_dsc_t d; lv_draw_label_dsc_init(&d);
    d.text = pool(s); d.color = lv_color_hex(col); d.font = f;
    lv_area_t a = {x, y, x + 460, y + 60}; lv_draw_label(L, &d, &a);
}
static void cText(const char *s, int cx, int cy, const lv_font_t *f, uint32_t col) {  // centred on point
    lv_point_t sz; lv_text_get_size(&sz, s, f, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
    lv_draw_label_dsc_t d; lv_draw_label_dsc_init(&d);
    d.text = pool(s); d.color = lv_color_hex(col); d.font = f;
    lv_area_t a = {cx - sz.x / 2, cy - sz.y / 2, cx - sz.x / 2 + sz.x, cy - sz.y / 2 + sz.y};
    lv_draw_label(L, &d, &a);
}

// ============================================================================
//  Widgets — gear, weather glyphs, sleep/wifi icons
// ============================================================================
static void drawGear(int cx, int cy, int r, uint32_t col, uint32_t hole) {
    for (int k = 0; k < 8; k++) {
        float a = k * (PI / 4);
        fCircle(cx + (int)((r + 2) * cosf(a)), cy + (int)((r + 2) * sinf(a)), 2, col);
    }
    fCircle(cx, cy, r, col);
    fCircle(cx, cy, (int)(r * 0.42f), hole);
}
// WMO weather code → small glyph (sun / partly / cloud / rain / snow / storm)
static int wxCat(int c) {
    if (c <= 0) return 0; if (c <= 2) return 1; if (c == 3 || c == 45 || c == 48) return 2;
    if ((c >= 71 && c <= 77) || c == 85 || c == 86) return 4; if (c >= 95) return 5; return 3;
}
// Weather glyphs drawn in the SAME geometry as the web SVG icons (a 24x26 space,
// centred at 12,13), mapped to the screen by a scale `gK` about (gCx,gCy). This makes
// the on-device icons identical in shape to the web dashboard's.
static int gCx, gCy; static float gK;
static inline int wpx(float wx) { return gCx + (int)lroundf((wx - 12.0f) * gK); }
static inline int wpy(float wy) { return gCy + (int)lroundf((wy - 13.0f) * gK); }
static inline int wpr(float r)  { int v = (int)lroundf(r * gK); return v < 1 ? 1 : v; }
static void wxSunAt(float scx, float scy, float r, uint32_t col) {   // disc + 8 rays (web sun)
    for (int a = 0; a < 8; a++) { float t = a * PI / 4;
        line(wpx(scx + (r + 2.0f) * cosf(t)), wpy(scy + (r + 2.0f) * sinf(t)),
             wpx(scx + (r + 4.5f) * cosf(t)), wpy(scy + (r + 4.5f) * sinf(t)), col); }
    fCircle(wpx(scx), wpy(scy), wpr(r), col);
}
static void wxCloudAt(uint32_t col) {   // web cloud: 3 bumps (small-left, big-mid, small-right) + flat base
    fCircle(wpx(9), wpy(13), wpr(4.2f), col);
    fCircle(wpx(14), wpy(11), wpr(5.2f), col);
    fCircle(wpx(18), wpy(14), wpr(3.6f), col);
    fRect(wpx(8), wpy(13), wpr(11), wpr(5.2f), wpr(2.6f), col);
}
static void drawWxIcon(int cx, int cy, int code, float k = 1.15f) {   // centred at (cx,cy); k scales the 24-unit glyph
    const uint32_t SUN = 0xffd43b, CLD = 0xc9d1d9, RN = 0x4aa3ff, SNW = 0xcfe6ff, BOLT = 0xffd43b;
    gCx = cx; gCy = cy; gK = k;   // 1.15 → ~28px top-bar glyph; larger k for the forecast popup
    int cat = wxCat(code);
    if (cat == 0) { wxSunAt(12, 11, 4.6f, SUN); return; }                   // clear
    if (cat == 1) { wxSunAt(8, 8, 3.0f, SUN); wxCloudAt(CLD); return; }     // partly (sun peeks, cloud over)
    wxCloudAt(CLD);                                                         // cloud base for 2..5
    if (cat == 3) for (int i = 0; i < 3; i++) { float bx = 9 + i * 4; for (int o = 0; o < 2; o++) line(wpx(bx) + o, wpy(19), wpx(bx - 1) + o, wpy(22.5f), RN); }   // rain streaks
    else if (cat == 4) for (int i = 0; i < 3; i++) { float bx = 9 + i * 4; fCircle(wpx(bx), wpy(21.5f), wpr(1.4f), SNW); }                                        // snow dots
    else if (cat == 5) { tri(wpx(13), wpy(18), wpx(9.5f), wpy(22.5f), wpx(13), wpy(20), BOLT); tri(wpx(13), wpy(20), wpx(16), wpy(20), wpx(10.5f), wpy(25.5f), BOLT); }    // filled bolt
}
static void drawBed(int cx, int cy, uint32_t col) {
    int x = cx - 13, y = cy + 5;
    fRect(x + 1, y, 2, 4, 0, col);
    fRect(x + 22, y, 2, 4, 0, col);
    fRect(x, y - 6, 26, 6, 2, col);
    fRect(x, y - 13, 3, 9, 0, col);
    fRect(x + 4, y - 9, 8, 4, 2, col);
    lText("z", x + 20, y - 18, F12, col);
}
// compact wifi glyph for the top bar; cy is the VISUAL centre (dot below, arcs fanning up),
// so it lines up with the weather glyph / temperature / clock which all centre on the same y.
static void drawWifiSmall(int cx, int cy, uint32_t color) {
    int by = cy + 6;   // dot baseline: arcs reach ~13px up → +6 centres the glyph on cy
    fCircle(cx, by, 2, color);
    const float a0 = 50.0f * (PI / 180.0f), a1 = 130.0f * (PI / 180.0f), yScale = 0.72f;
    int radii[3] = {6, 12, 18};   // larger
    for (int k = 0; k < 3; k++) {
        int r = radii[k], px = -1, py = -1;
        for (int s = 0; s <= 8; s++) {
            float a = a0 + (a1 - a0) * s / 8.0f;
            int x = cx + (int)(r * cosf(a)), y = by - (int)(r * sinf(a) * yScale);
            if (px >= 0) line(px, py, x, y, color);
            px = x; py = y;
        }
    }
}
