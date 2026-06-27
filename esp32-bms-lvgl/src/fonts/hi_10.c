/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --font /tmp/NotoDeva.ttf --size 10 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x900-0x97F -o src/fonts/hi_10.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef HI_10
#define HI_10 1
#endif

#if HI_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x55, 0x4c,

    /* U+0022 "\"" */
    0xb4,

    /* U+0023 "#" */
    0x29, 0xf2, 0x8a, 0x51, 0x40,

    /* U+0025 "%" */
    0xc9, 0x53, 0x41, 0x52, 0xa9, 0xc0,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x6a, 0xaa, 0x90,

    /* U+0029 ")" */
    0xa5, 0x55, 0xa0,

    /* U+002A "*" */
    0x2f, 0x6d,

    /* U+002B "+" */
    0x44, 0xf4, 0x40,

    /* U+002C "," */
    0x50,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x22, 0x24, 0x44, 0x48,

    /* U+0030 "0" */
    0x72, 0x73, 0x9c, 0xa5, 0xc0,

    /* U+0031 "1" */
    0x74, 0x92, 0x48,

    /* U+0032 "2" */
    0x70, 0x42, 0x22, 0x23, 0xe0,

    /* U+0033 "3" */
    0xf0, 0x44, 0xe0, 0x87, 0xc0,

    /* U+0034 "4" */
    0x11, 0x94, 0xa9, 0x3c, 0x40,

    /* U+0035 "5" */
    0xe8, 0x8f, 0x11, 0xe0,

    /* U+0036 "6" */
    0x3a, 0x11, 0xf4, 0xa5, 0xc0,

    /* U+0037 "7" */
    0xf8, 0x44, 0x22, 0x11, 0x80,

    /* U+0038 "8" */
    0x7a, 0x54, 0xe4, 0xe5, 0xc0,

    /* U+0039 "9" */
    0x72, 0x72, 0xf0, 0x8d, 0xc0,

    /* U+003A ":" */
    0xc4,

    /* U+003B ";" */
    0x50, 0x14,

    /* U+003C "<" */
    0x3, 0xcc, 0x30,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0xc, 0x36, 0x80,

    /* U+003F "?" */
    0xe1, 0x24, 0x40, 0x40,

    /* U+005B "[" */
    0xea, 0xaa, 0xb0,

    /* U+005C "\\" */
    0x44, 0x44, 0x22, 0x22, 0x11,

    /* U+005D "]" */
    0xd5, 0x55, 0x70,

    /* U+005E "^" */
    0x22, 0x94, 0x90,

    /* U+005F "_" */
    0xf0,

    /* U+007B "{" */
    0x24, 0x9c, 0xc9, 0x20,

    /* U+007C "|" */
    0xff, 0xc0,

    /* U+007D "}" */
    0x92, 0x47, 0xa4, 0x90,

    /* U+007E "~" */
    0xf0,

    /* U+0900 "ऀ" */
    0x75, 0x40,

    /* U+0901 "ँ" */
    0xab, 0x80,

    /* U+0902 "ं" */
    0x80,

    /* U+0903 "ः" */
    0x90,

    /* U+0904 "ऄ" */
    0x10, 0x1c, 0x2, 0x77, 0x12, 0xb2, 0x4e, 0x72,
    0x2,

    /* U+0905 "अ" */
    0x77, 0x12, 0xb2, 0xce, 0x72, 0x2,

    /* U+0906 "आ" */
    0x77, 0xc5, 0x22, 0x4a, 0x72, 0x74, 0x81, 0x20,

    /* U+0907 "इ" */
    0xff, 0x21, 0xe1, 0x78, 0xc0,

    /* U+0908 "ई" */
    0x31, 0x9, 0xfe, 0x41, 0xc2, 0xe0, 0x0,

    /* U+0909 "उ" */
    0xfc, 0x21, 0xa2, 0x48, 0xe0,

    /* U+090A "ऊ" */
    0xff, 0x8, 0x18, 0x8e, 0x4a, 0x3a,

    /* U+090B "ऋ" */
    0xff, 0x84, 0x1e, 0xc3, 0xa6, 0xa0, 0x5c,

    /* U+090C "ऌ" */
    0xfe, 0x13, 0xf5, 0xa8, 0x4f, 0x3, 0x80,

    /* U+090D "ऍ" */
    0x28, 0xef, 0xd2, 0x49, 0x26, 0x4, 0x8, 0x20,

    /* U+090E "ऎ" */
    0x30, 0x2f, 0xd2, 0x49, 0x62, 0x6, 0x8, 0x20,

    /* U+090F "ए" */
    0xfd, 0x24, 0x96, 0x60, 0x60, 0x82,

    /* U+0910 "ऐ" */
    0x30, 0x40, 0xbf, 0x49, 0x25, 0x8, 0x18, 0x20,

    /* U+0911 "ऑ" */
    0x2, 0x40, 0x90, 0x1d, 0xdf, 0x14, 0x8d, 0x29,
    0xc9, 0xd2, 0x4, 0x80,

    /* U+0912 "ऒ" */
    0x4, 0x1, 0xc0, 0x9, 0xdf, 0x14, 0xa9, 0x29,
    0xc9, 0xd2, 0x4, 0x80,

    /* U+0913 "ओ" */
    0x3, 0x0, 0x40, 0x9, 0xdf, 0x14, 0xaf, 0x29,
    0x49, 0xd2, 0x4, 0x80,

    /* U+0914 "औ" */
    0x3, 0x0, 0xc0, 0x9, 0xdf, 0x14, 0xaf, 0x29,
    0x49, 0xd2, 0x4, 0x80,

    /* U+0915 "क" */
    0xff, 0x70, 0x9e, 0x92, 0xf2, 0x10,

    /* U+0916 "ख" */
    0xff, 0x93, 0x9a, 0x49, 0x22, 0x70, 0xf8,

    /* U+0917 "ग" */
    0xfd, 0x24, 0xb2, 0x8, 0x20,

    /* U+0918 "घ" */
    0xfe, 0x26, 0x92, 0x78, 0x20,

    /* U+0919 "ङ" */
    0xfd, 0xc4, 0x9e, 0x89, 0xe0,

    /* U+091A "च" */
    0xfe, 0xb, 0xd1, 0x23, 0xc0, 0x80,

    /* U+091B "छ" */
    0xff, 0x6c, 0x8a, 0x6e, 0x46, 0x78,

    /* U+091C "ज" */
    0xff, 0x2, 0x5e, 0x4a, 0x3a, 0x2,

    /* U+091D "झ" */
    0xff, 0x72, 0x82, 0x7e, 0x1a, 0xf2, 0x10,

    /* U+091E "ञ" */
    0xff, 0x2, 0x3a, 0x4e, 0x3a, 0x2,

    /* U+091F "ट" */
    0xf2, 0x68, 0x87,

    /* U+0920 "ठ" */
    0xfc, 0x87, 0x22, 0x89, 0xc0,

    /* U+0921 "ड" */
    0xfd, 0xc4, 0x1e, 0x89, 0xe0,

    /* U+0922 "ढ" */
    0xfc, 0x47, 0x2e, 0xa9, 0xc0,

    /* U+0923 "ण" */
    0xff, 0x4a, 0x4a, 0x4a, 0x32, 0x2,

    /* U+0924 "त" */
    0xfc, 0x27, 0xa2, 0x49, 0xa0,

    /* U+0925 "थ" */
    0x6f, 0x29, 0x92, 0x23, 0xc0, 0x80,

    /* U+0926 "द" */
    0xf8, 0xbd, 0x7, 0x8, 0x0,

    /* U+0927 "ध" */
    0xfe, 0xa6, 0x92, 0x78, 0x20,

    /* U+0928 "न" */
    0xfc, 0x2f, 0x92, 0x8, 0x20,

    /* U+0929 "ऩ" */
    0xfc, 0x2f, 0x92, 0x9, 0x20,

    /* U+092A "प" */
    0xfd, 0x24, 0x92, 0x78, 0x20,

    /* U+092B "फ" */
    0xff, 0xa4, 0x13, 0xc9, 0x27, 0x90, 0x40,

    /* U+092C "ब" */
    0xfd, 0xe6, 0xaa, 0x78, 0x20,

    /* U+092D "भ" */
    0xef, 0x48, 0x93, 0xe2, 0x40, 0x80,

    /* U+092E "म" */
    0xfd, 0x24, 0xbe, 0x48, 0x20,

    /* U+092F "य" */
    0xfd, 0x24, 0x92, 0x78, 0x20,

    /* U+0930 "र" */
    0xf8, 0x9c, 0x82, 0xc,

    /* U+0931 "ऱ" */
    0xf8, 0x9c, 0x82, 0x2c,

    /* U+0932 "ल" */
    0xfe, 0x9, 0xf4, 0xa4, 0x44, 0x80,

    /* U+0933 "ळ" */
    0xff, 0x4, 0x7e, 0x92, 0x92, 0x6c,

    /* U+0934 "ऴ" */
    0xff, 0x4, 0x7e, 0x92, 0x92, 0x6c, 0x20,

    /* U+0935 "व" */
    0xfd, 0xe4, 0x92, 0x78, 0x20,

    /* U+0936 "श" */
    0x6e, 0xa8, 0x57, 0x22, 0x42, 0x80,

    /* U+0937 "ष" */
    0xfd, 0xa5, 0x92, 0x78, 0x20,

    /* U+0938 "स" */
    0xfe, 0x4b, 0x97, 0xe6, 0x46, 0x80,

    /* U+0939 "ह" */
    0xfd, 0xe4, 0x1e, 0x49, 0x22, 0x0,

    /* U+093A "ऺ" */
    0xe0,

    /* U+093B "ऻ" */
    0x4b, 0xa4, 0x92,

    /* U+093C "़" */
    0x80,

    /* U+093D "ऽ" */
    0x74, 0x29, 0xd7,

    /* U+093E "ा" */
    0xe9, 0x24, 0x80,

    /* U+093F "ि" */
    0x38, 0x89, 0xf, 0x4, 0x8, 0x10, 0x20, 0x40,

    /* U+0940 "ी" */
    0xe5, 0x24, 0x71, 0x8, 0x42, 0x10,

    /* U+0941 "ु" */
    0x3e, 0x5e,

    /* U+0942 "ू" */
    0xe4, 0xf8,

    /* U+0943 "ृ" */
    0xd3, 0x80,

    /* U+0944 "ॄ" */
    0xc8, 0x66,

    /* U+0945 "ॅ" */
    0x8b, 0x80,

    /* U+0946 "ॆ" */
    0x86, 0x10,

    /* U+0947 "े" */
    0xc4, 0x80,

    /* U+0948 "ै" */
    0xdc, 0x80,

    /* U+0949 "ॉ" */
    0x99, 0x77, 0x22, 0x22, 0x20,

    /* U+094A "ॊ" */
    0x87, 0x4, 0x71, 0x8, 0x42, 0x10,

    /* U+094B "ो" */
    0xc4, 0x27, 0x22, 0x22, 0x20,

    /* U+094C "ौ" */
    0x67, 0x4, 0x71, 0x8, 0x42, 0x10,

    /* U+094D "्" */
    0xc4,

    /* U+094E "ॎ" */
    0xea, 0xa0,

    /* U+094F "ॏ" */
    0x27, 0x8c, 0x73, 0x88, 0x42, 0x10,

    /* U+0950 "ॐ" */
    0xd, 0x7, 0xe, 0x1, 0x71, 0xca, 0x5c, 0xe0,

    /* U+0951 "॑" */
    0xc0,

    /* U+0952 "॒" */
    0xe0,

    /* U+0953 "॓" */
    0x94,

    /* U+0954 "॔" */
    0x68,

    /* U+0955 "ॕ" */
    0xfc,

    /* U+0956 "ॖ" */
    0xf0,

    /* U+0957 "ॗ" */
    0xff,

    /* U+0958 "क़" */
    0xff, 0x70, 0x9e, 0x92, 0xf2, 0x50,

    /* U+0959 "ख़" */
    0xff, 0x93, 0x9a, 0x49, 0x22, 0x72, 0xf8,

    /* U+095A "ग़" */
    0xfd, 0x24, 0xb2, 0x9, 0x20,

    /* U+095B "ज़" */
    0xff, 0x2, 0x5e, 0x4a, 0x3a, 0x2, 0x20,

    /* U+095C "ड़" */
    0xfd, 0xc4, 0x1e, 0x89, 0xe0, 0x8,

    /* U+095D "ढ़" */
    0xfc, 0x47, 0x2e, 0xa9, 0xc0, 0x8,

    /* U+095E "फ़" */
    0xff, 0xa4, 0x13, 0xc9, 0x27, 0x92, 0x40,

    /* U+095F "य़" */
    0xfd, 0x24, 0x92, 0x79, 0x20,

    /* U+0960 "ॠ" */
    0xff, 0x84, 0x1e, 0x83, 0xc6, 0xa0, 0x5c, 0x8,
    0x7,

    /* U+0961 "ॡ" */
    0xfe, 0x13, 0xf5, 0xa8, 0x4d, 0x3, 0x3,

    /* U+0962 "ॢ" */
    0xfd, 0x54, 0x30,

    /* U+0963 "ॣ" */
    0xfa, 0xa4, 0xc3,

    /* U+0964 "।" */
    0xfc,

    /* U+0965 "॥" */
    0xb6, 0xdb, 0x40,

    /* U+0966 "०" */
    0x69, 0x96,

    /* U+0967 "१" */
    0xf5, 0xc4, 0x48,

    /* U+0968 "२" */
    0xe1, 0x1e, 0x21,

    /* U+0969 "३" */
    0xe1, 0x61, 0xf2, 0x10,

    /* U+096A "४" */
    0x8a, 0x88, 0xa5, 0x38,

    /* U+096B "५" */
    0x84, 0x2c, 0xe1, 0x8,

    /* U+096C "६" */
    0xe8, 0x6a, 0x71, 0x10,

    /* U+096D "७" */
    0xb5, 0x66, 0x97, 0x0,

    /* U+096E "८" */
    0x12, 0x48, 0x87,

    /* U+096F "९" */
    0x75, 0xbc, 0xc1, 0x8, 0x0,

    /* U+0970 "॰" */
    0xf7, 0x80,

    /* U+0971 "ॱ" */
    0x80,

    /* U+0972 "ॲ" */
    0x9, 0x9, 0x7, 0x77, 0xa, 0x32, 0xce, 0x72,
    0x2,

    /* U+0973 "ॳ" */
    0x2, 0x2, 0x77, 0xa, 0x32, 0xce, 0x72, 0x2,

    /* U+0974 "ॴ" */
    0x0, 0x80, 0x27, 0x7c, 0x52, 0x34, 0xa7, 0x27,
    0x48, 0x12,

    /* U+0975 "ॵ" */
    0x1, 0x1, 0xe0, 0x9, 0xdf, 0x14, 0xaf, 0x29,
    0x49, 0xd2, 0x4, 0x80,

    /* U+0976 "ॶ" */
    0x77, 0x12, 0xb2, 0xce, 0x72, 0x2, 0x0, 0x1c,

    /* U+0977 "ॷ" */
    0x77, 0x12, 0xb2, 0xce, 0x72, 0x2, 0x2, 0x1c,
    0x1c,

    /* U+0978 "ॸ" */
    0xfd, 0xf, 0x12, 0x8, 0x0,

    /* U+0979 "ॹ" */
    0xff, 0x1e, 0x52, 0x4a, 0x3a, 0x2a, 0x10,

    /* U+097A "ॺ" */
    0xfd, 0x26, 0xb6, 0x78, 0x20,

    /* U+097B "ॻ" */
    0xfd, 0x2c, 0xb2, 0x9, 0xe0,

    /* U+097C "ॼ" */
    0xff, 0x1e, 0x5a, 0x4a, 0x3a, 0x7e,

    /* U+097D "ॽ" */
    0xe1, 0x16, 0x44,

    /* U+097E "ॾ" */
    0xfd, 0xe4, 0x2e, 0x7b, 0xe0,

    /* U+097F "ॿ" */
    0xfd, 0xe6, 0x9a, 0x79, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 42, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 62, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 82, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 105, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 136, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 53, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 16, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 19, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 22, .adv_w = 97, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 24, .adv_w = 89, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 27, .adv_w = 44, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 28, .adv_w = 56, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 29, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 71, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 88, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 48, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 48, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 85, .adv_w = 89, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 88, .adv_w = 89, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 90, .adv_w = 89, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 93, .adv_w = 84, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 100, .adv_w = 71, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 105, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 108, .adv_w = 89, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 111, .adv_w = 66, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 112, .adv_w = 64, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 116, .adv_w = 86, .box_w = 1, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 118, .adv_w = 63, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 122, .adv_w = 89, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 123, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -4, .ofs_y = 7},
    {.bitmap_index = 125, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -4, .ofs_y = 7},
    {.bitmap_index = 127, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -2, .ofs_y = 7},
    {.bitmap_index = 128, .adv_w = 44, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 129, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 126, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 169, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 157, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 164, .adv_w = 89, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 125, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 140, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 189, .adv_w = 91, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 197, .adv_w = 91, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 205, .adv_w = 91, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 211, .adv_w = 91, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 219, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 125, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 135, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 106, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 115, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 122, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 124, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 320, .adv_w = 123, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 82, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 119, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 106, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 85, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 366, .adv_w = 102, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 126, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 116, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 98, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 67, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 67, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 124, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 124, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 441, .adv_w = 91, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 87, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 469, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 5},
    {.bitmap_index = 470, .adv_w = 43, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -3, .ofs_y = -2},
    {.bitmap_index = 474, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 43, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 43, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 43, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -5, .ofs_y = -3},
    {.bitmap_index = 496, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 498, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 500, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 502, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -4, .ofs_y = 6},
    {.bitmap_index = 504, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -5, .ofs_y = 6},
    {.bitmap_index = 506, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 6},
    {.bitmap_index = 508, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 6},
    {.bitmap_index = 510, .adv_w = 43, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 43, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 43, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 43, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = -2, .ofs_y = -2},
    {.bitmap_index = 533, .adv_w = 45, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 43, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 150, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 549, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = -2, .ofs_y = 7},
    {.bitmap_index = 550, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = -4, .ofs_y = -2},
    {.bitmap_index = 551, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -3, .ofs_y = 6},
    {.bitmap_index = 552, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -2, .ofs_y = 6},
    {.bitmap_index = 553, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = -3, .ofs_y = 6},
    {.bitmap_index = 554, .adv_w = 0, .box_w = 4, .box_h = 1, .ofs_x = -5, .ofs_y = -2},
    {.bitmap_index = 555, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = -5, .ofs_y = -3},
    {.bitmap_index = 556, .adv_w = 125, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 135, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 122, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 581, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 587, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 593, .adv_w = 126, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 140, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 614, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 621, .adv_w = 0, .box_w = 5, .box_h = 4, .ofs_x = -5, .ofs_y = -4},
    {.bitmap_index = 624, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -5, .ofs_y = -4},
    {.bitmap_index = 627, .adv_w = 62, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 98, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 89, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 633, .adv_w = 89, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 636, .adv_w = 89, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 643, .adv_w = 89, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 89, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 655, .adv_w = 89, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 89, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 89, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 667, .adv_w = 69, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 669, .adv_w = 51, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 670, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 169, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 717, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 726, .adv_w = 91, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 122, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 738, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 120, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 76, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 1, 2, 3, 0, 4
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 6, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 6, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    },
    {
        .range_start = 39, .range_length = 25, .glyph_id_start = 6,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 91, .range_length = 5, .glyph_id_start = 31,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 123, .range_length = 4, .glyph_id_start = 36,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 2304, .range_length = 128, .glyph_id_start = 40,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 5,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t hi_10 = {
#else
lv_font_t hi_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if HI_10*/

