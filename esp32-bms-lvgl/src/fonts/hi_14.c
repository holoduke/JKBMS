/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --font /tmp/NotoDeva.ttf --size 14 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x900-0x97F -o src/fonts/hi_14.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef HI_14
#define HI_14 1
#endif

#if HI_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf0,

    /* U+0022 "\"" */
    0xbb, 0xb0,

    /* U+0023 "#" */
    0x12, 0x9, 0x1f, 0xef, 0xf1, 0x61, 0xa3, 0xfc,
    0x48, 0x24, 0x0,

    /* U+0025 "%" */
    0x61, 0x2c, 0xc9, 0x22, 0x50, 0xfd, 0x82, 0x91,
    0x24, 0x49, 0x23, 0xc0,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x2d, 0x6d, 0x24, 0x93, 0x24, 0xc0,

    /* U+0029 ")" */
    0x99, 0x36, 0x49, 0x25, 0xb5, 0x80,

    /* U+002A "*" */
    0x10, 0x23, 0xf9, 0x86, 0x89, 0x0,

    /* U+002B "+" */
    0x20, 0x82, 0x3f, 0x20, 0x82, 0x0,

    /* U+002C "," */
    0xfa,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x18, 0x84, 0x63, 0x10, 0x8c, 0x42, 0x11, 0x88,
    0x40,

    /* U+0030 "0" */
    0x7b, 0x28, 0xe1, 0x86, 0x18, 0x63, 0xcd, 0xe0,

    /* U+0031 "1" */
    0x37, 0xd1, 0x11, 0x11, 0x11,

    /* U+0032 "2" */
    0x7a, 0x20, 0xc3, 0x18, 0x43, 0x18, 0xc3, 0xf0,

    /* U+0033 "3" */
    0x7c, 0x8c, 0x18, 0x23, 0x83, 0x81, 0x83, 0x87,
    0xf8,

    /* U+0034 "4" */
    0xc, 0x18, 0x51, 0xa2, 0x48, 0xb1, 0x7f, 0x4,
    0x8,

    /* U+0035 "5" */
    0xfb, 0xc, 0x30, 0xf8, 0x30, 0xc3, 0xf, 0xe0,

    /* U+0036 "6" */
    0x39, 0x8c, 0x20, 0xfb, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0037 "7" */
    0xfc, 0x30, 0xc2, 0x18, 0x43, 0x8, 0x61, 0x80,

    /* U+0038 "8" */
    0x7b, 0x38, 0xf2, 0x71, 0x68, 0xe1, 0x8d, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x28, 0xe1, 0x8f, 0xd0, 0xc3, 0x1b, 0xc0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0xa0,

    /* U+003C "<" */
    0x4, 0x66, 0x20, 0x60, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0xf, 0xc0,

    /* U+003E ">" */
    0x83, 0x83, 0x83, 0x3b, 0x88, 0x0,

    /* U+003F "?" */
    0xfc, 0x42, 0x11, 0x10, 0x80, 0x23, 0x0,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xdb, 0x6d, 0xc0,

    /* U+005C "\\" */
    0x84, 0x21, 0x84, 0x21, 0x8c, 0x21, 0xc, 0x21,
    0x8,

    /* U+005D "]" */
    0xed, 0xb6, 0xdb, 0x6d, 0xb7, 0xc0,

    /* U+005E "^" */
    0x18, 0x30, 0xb1, 0x24, 0x68, 0x40,

    /* U+005F "_" */
    0xfc,

    /* U+007B "{" */
    0x17, 0x66, 0x66, 0x4c, 0x66, 0x66, 0x63,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xc, 0x44, 0x44, 0x63, 0x64, 0x44, 0x4c,

    /* U+007E "~" */
    0x43, 0xf0,

    /* U+0900 "ऀ" */
    0x74, 0xea,

    /* U+0901 "ँ" */
    0xac, 0x5c,

    /* U+0902 "ं" */
    0xe0,

    /* U+0903 "ः" */
    0x30, 0xc,

    /* U+0904 "ऄ" */
    0x8, 0x0, 0xe0, 0x2, 0x0, 0x43, 0x9e, 0x9,
    0x1, 0x24, 0xc4, 0xc7, 0x88, 0x91, 0x92, 0x1c,
    0x40, 0x8,

    /* U+0905 "अ" */
    0x39, 0xe0, 0x90, 0x12, 0xe, 0x48, 0xf8, 0x89,
    0x19, 0x21, 0xc4, 0x0, 0x80,

    /* U+0906 "आ" */
    0x39, 0xfe, 0x9, 0x10, 0x12, 0x20, 0xe4, 0x48,
    0xf8, 0x88, 0x91, 0x19, 0x22, 0x1c, 0x44, 0x0,
    0x88,

    /* U+0907 "इ" */
    0xfe, 0x11, 0xe2, 0x4, 0xf, 0x1, 0x22, 0x78,
    0x30, 0x0,

    /* U+0908 "ई" */
    0xe, 0x10, 0x20, 0x4f, 0xe1, 0x1e, 0x30, 0x60,
    0x70, 0x13, 0x27, 0x83, 0x0, 0x0,

    /* U+0909 "उ" */
    0xff, 0x2, 0x2, 0x2, 0xcc, 0x42, 0x62, 0x32,
    0x1c,

    /* U+090A "ऊ" */
    0xff, 0xe0, 0x40, 0x8, 0x1, 0xc, 0xd8, 0x84,
    0x98, 0x91, 0x92, 0x1c, 0x40,

    /* U+090B "ऋ" */
    0xff, 0xf0, 0x20, 0x2, 0x7, 0xac, 0xf, 0xc0,
    0xe4, 0x3a, 0xc6, 0x28, 0x2, 0x70,

    /* U+090C "ऌ" */
    0xff, 0xc0, 0x40, 0x10, 0xfe, 0x4c, 0xd2, 0x36,
    0xc, 0xce, 0x12, 0x0, 0x90, 0x1c,

    /* U+090D "ऍ" */
    0x21, 0x23, 0x1e, 0x0, 0xff, 0x42, 0x42, 0x42,
    0x42, 0x44, 0x30, 0x18, 0x6, 0x2, 0x2, 0x2,

    /* U+090E "ऎ" */
    0x40, 0x3c, 0x4, 0x2, 0xff, 0x42, 0x42, 0x42,
    0x46, 0x44, 0x30, 0x1c, 0x6, 0x2, 0x2,

    /* U+090F "ए" */
    0xff, 0x42, 0x42, 0x42, 0x42, 0x44, 0x30, 0x18,
    0x6, 0x2, 0x2, 0x2,

    /* U+0910 "ऐ" */
    0x38, 0x4, 0x4, 0x2, 0xff, 0x42, 0x42, 0x42,
    0x42, 0x44, 0x30, 0x18, 0x6, 0x2, 0x2, 0x2,

    /* U+0911 "ऑ" */
    0x0, 0x42, 0x0, 0xcc, 0x0, 0xf0, 0x0, 0x3,
    0x9f, 0xe0, 0x91, 0x1, 0x22, 0xc, 0x44, 0xc7,
    0x88, 0x89, 0x11, 0x92, 0x21, 0xc4, 0x40, 0x8,
    0x80,

    /* U+0912 "ऒ" */
    0x0, 0x80, 0x1, 0xe0, 0x0, 0x20, 0x0, 0x43,
    0x9f, 0xe0, 0x91, 0x1, 0x22, 0x4c, 0x44, 0xc7,
    0x88, 0x89, 0x11, 0x92, 0x21, 0xc4, 0x40, 0x8,
    0x80,

    /* U+0913 "ओ" */
    0x0, 0x60, 0x0, 0x20, 0x0, 0x40, 0x0, 0x43,
    0x9f, 0xe0, 0x91, 0x1, 0x22, 0xc, 0x44, 0xc7,
    0x88, 0x89, 0x11, 0x92, 0x21, 0xc4, 0x40, 0x8,
    0x80,

    /* U+0914 "औ" */
    0x0, 0x60, 0x0, 0x20, 0x3, 0xc0, 0x0, 0xc3,
    0x9f, 0xe0, 0x91, 0x1, 0x22, 0xc, 0x44, 0xc7,
    0x88, 0x89, 0x11, 0x92, 0x21, 0xc4, 0x40, 0x8,
    0x80,

    /* U+0915 "क" */
    0xff, 0xe0, 0x80, 0xf0, 0x27, 0xc4, 0x64, 0x88,
    0x8f, 0x10, 0x26, 0x4, 0x0,

    /* U+0916 "ख" */
    0xff, 0xf1, 0x4, 0x13, 0xc5, 0x64, 0x74, 0x46,
    0x4c, 0x23, 0xc1, 0x8c, 0xf, 0xc0,

    /* U+0917 "ग" */
    0xff, 0x91, 0x8, 0x84, 0x46, 0x23, 0x10, 0x8,
    0x4, 0x2, 0x0,

    /* U+0918 "घ" */
    0xff, 0xa1, 0x10, 0x8e, 0x46, 0x23, 0x10, 0xf8,
    0x4, 0x2, 0x0,

    /* U+0919 "ङ" */
    0xff, 0x81, 0x7, 0x86, 0x3, 0x18, 0xe1, 0x8,
    0xc4, 0x3c, 0x0,

    /* U+091A "च" */
    0xff, 0x80, 0x80, 0x4f, 0xa3, 0x11, 0x88, 0x7c,
    0x2, 0x1, 0x0,

    /* U+091B "छ" */
    0xff, 0xc0, 0xc3, 0x31, 0x12, 0x44, 0x8e, 0xa2,
    0x18, 0x8c, 0x1e, 0x0,

    /* U+091C "ज" */
    0xff, 0xe0, 0x10, 0x2, 0x67, 0xc4, 0x48, 0xc9,
    0x9, 0x20, 0xe4, 0x0, 0x80,

    /* U+091D "झ" */
    0xff, 0xe1, 0x91, 0xf2, 0x20, 0x44, 0x8, 0xff,
    0x1, 0x22, 0x64, 0x78, 0x83, 0x80, 0x0, 0x0,

    /* U+091E "ञ" */
    0xff, 0xe0, 0x10, 0x2, 0xe, 0x44, 0x38, 0xcd,
    0xf, 0x20, 0x4, 0x0, 0x80,

    /* U+091F "ट" */
    0xfe, 0x10, 0x21, 0xc6, 0x8, 0x10, 0x32, 0x3c,

    /* U+0920 "ठ" */
    0xff, 0x84, 0x2, 0x7, 0x86, 0x62, 0x19, 0xc,
    0xc6, 0x3e, 0x0,

    /* U+0921 "ड" */
    0xff, 0x81, 0x7, 0x86, 0x3, 0x0, 0xe1, 0x8,
    0xc4, 0x3c, 0x0,

    /* U+0922 "ढ" */
    0xff, 0x8, 0x8, 0x38, 0x60, 0x4c, 0x52, 0x72,
    0x3c,

    /* U+0923 "ण" */
    0xff, 0xe8, 0x91, 0x12, 0x22, 0x44, 0x48, 0xc9,
    0xe, 0x20, 0x4, 0x0, 0x80,

    /* U+0924 "त" */
    0xff, 0x81, 0x0, 0x87, 0xc4, 0x22, 0x11, 0x8,
    0xc4, 0x32, 0x0,

    /* U+0925 "थ" */
    0xe7, 0xc9, 0x34, 0x82, 0x46, 0x22, 0x30, 0xf8,
    0x4, 0x2, 0x0,

    /* U+0926 "द" */
    0xff, 0x8, 0x38, 0x60, 0x40, 0x44, 0x66, 0x3c,
    0x4, 0x2,

    /* U+0927 "ध" */
    0x77, 0xc9, 0x24, 0x8e, 0x46, 0x22, 0x11, 0x98,
    0x74, 0x2, 0x0,

    /* U+0928 "न" */
    0xff, 0x2, 0x2, 0x2, 0x7e, 0x62, 0x2, 0x2,
    0x2,

    /* U+0929 "ऩ" */
    0xff, 0x2, 0x2, 0x2, 0x7e, 0x62, 0x2, 0x2,
    0x32, 0x0,

    /* U+092A "प" */
    0xff, 0xa1, 0x10, 0x88, 0x44, 0x23, 0x30, 0xe8,
    0x4, 0x2, 0x0,

    /* U+092B "फ" */
    0xff, 0xe8, 0x81, 0x10, 0x23, 0xc4, 0x64, 0x98,
    0x8f, 0x10, 0x26, 0x4, 0x0,

    /* U+092C "ब" */
    0xff, 0x81, 0xf, 0x8e, 0x45, 0x22, 0x50, 0xf8,
    0x4, 0x2, 0x0,

    /* U+092D "भ" */
    0xe3, 0xe4, 0x4f, 0x10, 0x44, 0x11, 0xf, 0xc3,
    0x10, 0x4, 0x1, 0x0,

    /* U+092E "म" */
    0xff, 0x91, 0x8, 0x84, 0x47, 0xe3, 0x10, 0x88,
    0x4, 0x2, 0x0,

    /* U+092F "य" */
    0xff, 0x91, 0xc, 0x84, 0x46, 0x23, 0x30, 0xf8,
    0x4, 0x2, 0x0,

    /* U+0930 "र" */
    0xfc, 0x20, 0x86, 0x71, 0x83, 0x6, 0xc,

    /* U+0931 "ऱ" */
    0xfc, 0x20, 0xb6, 0xf1, 0x83, 0x6, 0xcc,

    /* U+0932 "ल" */
    0xff, 0xc0, 0x40, 0x11, 0xfc, 0x4d, 0x12, 0x44,
    0x10, 0x84, 0x11, 0x0,

    /* U+0933 "ळ" */
    0xff, 0xe0, 0x20, 0x4, 0x1d, 0xc4, 0x64, 0x88,
    0x93, 0x11, 0xdc,

    /* U+0934 "ऴ" */
    0xff, 0xe0, 0x20, 0x4, 0x1d, 0xc4, 0x64, 0x88,
    0x93, 0x11, 0xdc, 0x0, 0x2, 0x0, 0x40, 0x8,
    0x0,

    /* U+0935 "व" */
    0xff, 0x2, 0x3e, 0x62, 0x42, 0x42, 0x3e, 0x2,
    0x2,

    /* U+0936 "श" */
    0x73, 0xd2, 0x47, 0x90, 0xa4, 0x19, 0x3c, 0x47,
    0x10, 0x64, 0xd, 0x0,

    /* U+0937 "ष" */
    0xff, 0xb1, 0x14, 0x89, 0x44, 0xa3, 0x30, 0xe8,
    0x4, 0x2, 0x0,

    /* U+0938 "स" */
    0xff, 0xc4, 0x41, 0x11, 0x44, 0x7f, 0x18, 0x42,
    0x10, 0x44, 0x9, 0x0,

    /* U+0939 "ह" */
    0xff, 0x4, 0x3c, 0x40, 0x60, 0x3c, 0x66, 0x46,
    0x64, 0x20, 0x10,

    /* U+093A "ऺ" */
    0xe0,

    /* U+093B "ऻ" */
    0x44, 0x4f, 0x44, 0x44, 0x44, 0x44,

    /* U+093C "़" */
    0xf0,

    /* U+093D "ऽ" */
    0x3a, 0x18, 0x61, 0xc7, 0x2e,

    /* U+093E "ा" */
    0xf4, 0x44, 0x44, 0x44, 0x40,

    /* U+093F "ि" */
    0x3e, 0x10, 0xc4, 0x19, 0x3, 0xf0, 0x10, 0x4,
    0x1, 0x0, 0x40, 0x10, 0x4, 0x1, 0x0, 0x40,
    0x0,

    /* U+0940 "ी" */
    0x71, 0x12, 0x24, 0x21, 0xe0, 0x81, 0x2, 0x4,
    0x8, 0x10, 0x20, 0x40,

    /* U+0941 "ु" */
    0x1c, 0x85, 0x88, 0xe0,

    /* U+0942 "ू" */
    0x71, 0x1a, 0x13, 0x80,

    /* U+0943 "ृ" */
    0x48, 0x87,

    /* U+0944 "ॄ" */
    0x7, 0x20, 0xe4, 0x3c,

    /* U+0945 "ॅ" */
    0x87, 0x37, 0x80,

    /* U+0946 "ॆ" */
    0xc1, 0xe0, 0x83,

    /* U+0947 "े" */
    0xe1, 0x84, 0x30,

    /* U+0948 "ै" */
    0xe0, 0xbc, 0x30,

    /* U+0949 "ॉ" */
    0x85, 0x33, 0x80, 0x3c, 0x41, 0x4, 0x10, 0x41,
    0x4, 0x10,

    /* U+094A "ॊ" */
    0x80, 0xe0, 0x20, 0x41, 0xe1, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0x80,

    /* U+094B "ो" */
    0xc0, 0x81, 0x4, 0x3c, 0x41, 0x4, 0x10, 0x41,
    0x4, 0x10,

    /* U+094C "ौ" */
    0xc0, 0x8d, 0xc, 0x3c, 0x41, 0x4, 0x10, 0x41,
    0x4, 0x10,

    /* U+094D "्" */
    0xe0, 0x82,

    /* U+094E "ॎ" */
    0xea, 0xaa, 0x80,

    /* U+094F "ॏ" */
    0x11, 0x33, 0xd0, 0xe1, 0xe3, 0xc2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0x80,

    /* U+0950 "ॐ" */
    0x9, 0x60, 0x44, 0x3, 0x83, 0x80, 0x24, 0x0,
    0x4e, 0x5, 0x99, 0x91, 0xc6, 0x16, 0x4e, 0x3c,
    0x0,

    /* U+0951 "॑" */
    0xe0,

    /* U+0952 "॒" */
    0xf8,

    /* U+0953 "॓" */
    0xc9, 0x80,

    /* U+0954 "॔" */
    0x69, 0x0,

    /* U+0955 "ॕ" */
    0x3, 0x27, 0xbe,

    /* U+0956 "ॖ" */
    0x8b, 0xe0,

    /* U+0957 "ॗ" */
    0x83, 0xe8, 0x1e,

    /* U+0958 "क़" */
    0xff, 0xe0, 0x80, 0xf0, 0x27, 0xc4, 0x64, 0x88,
    0x8f, 0x11, 0x26, 0x24, 0x4, 0x0,

    /* U+0959 "ख़" */
    0xff, 0xf3, 0x4, 0x33, 0xcf, 0x44, 0xe4, 0x44,
    0x4c, 0x67, 0xc3, 0xc, 0x4f, 0xc4, 0x0,

    /* U+095A "ग़" */
    0xff, 0x91, 0x8, 0x84, 0x46, 0x23, 0x10, 0x8,
    0x44, 0x22, 0x0, 0x0,

    /* U+095B "ज़" */
    0xff, 0xe0, 0x10, 0x2, 0x27, 0xc6, 0x48, 0xcd,
    0xd, 0xa0, 0xe4, 0x8, 0x81, 0x0, 0x0, 0x0,

    /* U+095C "ड़" */
    0xff, 0x81, 0x7, 0x86, 0x3, 0x0, 0xe1, 0x8,
    0xc4, 0x3c, 0x4, 0x2, 0x1, 0x0,

    /* U+095D "ढ़" */
    0xff, 0x8, 0x8, 0x38, 0x60, 0x46, 0x4b, 0x6b,
    0x1e, 0x8, 0x8, 0x8,

    /* U+095E "फ़" */
    0xff, 0xe8, 0x81, 0x10, 0x23, 0xc4, 0x64, 0x98,
    0x8f, 0x10, 0x26, 0x64, 0x0, 0x0,

    /* U+095F "य़" */
    0xff, 0x91, 0x8, 0x84, 0x44, 0x22, 0x30, 0xf8,
    0x44, 0x22, 0x10, 0x0,

    /* U+0960 "ॠ" */
    0xff, 0xf0, 0x20, 0x2, 0x7, 0xa6, 0xf, 0xc0,
    0xe4, 0x3a, 0xc6, 0x28, 0x2, 0x70, 0x4, 0x0,
    0x70,

    /* U+0961 "ॡ" */
    0xff, 0xc0, 0x20, 0x4, 0x1d, 0xc6, 0x4c, 0x99,
    0x98, 0x71, 0x88, 0x19, 0x0, 0x38, 0x4, 0x0,
    0x70,

    /* U+0962 "ॢ" */
    0xec, 0x92, 0x92, 0x4c, 0x28, 0xe,

    /* U+0963 "ॣ" */
    0xee, 0x49, 0x25, 0x8, 0xe2, 0x28, 0x1c,

    /* U+0964 "।" */
    0xff,

    /* U+0965 "॥" */
    0x99, 0x99, 0x99, 0x99,

    /* U+0966 "०" */
    0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0967 "१" */
    0x69, 0xd3, 0x6c, 0x63, 0x13,

    /* U+0968 "२" */
    0xf0, 0x20, 0x82, 0x59, 0xc1, 0x6, 0xc,

    /* U+0969 "३" */
    0xe0, 0x84, 0xe0, 0x87, 0x6e, 0x30, 0xc0,

    /* U+096A "४" */
    0x86, 0x14, 0x9e, 0x31, 0xe4, 0xd3, 0x38,

    /* U+096B "५" */
    0xc2, 0x8, 0x20, 0x99, 0xe0, 0x82, 0xc, 0x10,

    /* U+096C "६" */
    0x72, 0x8, 0x1c, 0x41, 0x24, 0xce, 0xc, 0x10,

    /* U+096D "७" */
    0x82, 0xea, 0xed, 0xd5, 0x16, 0x4e,

    /* U+096E "८" */
    0x18, 0x43, 0x18, 0x42, 0x8, 0x23, 0x78,

    /* U+096F "९" */
    0x71, 0xb2, 0x27, 0xc7, 0x6, 0x6, 0x6, 0x4,
    0x8,

    /* U+0970 "॰" */
    0x69, 0x96,

    /* U+0971 "ॱ" */
    0x30,

    /* U+0972 "ॲ" */
    0x4, 0x20, 0x4c, 0xf, 0x0, 0x3, 0x9e, 0x9,
    0x1, 0x20, 0xc4, 0xc7, 0x88, 0x91, 0x92, 0x1c,
    0x40, 0x8,

    /* U+0973 "ॳ" */
    0x0, 0x80, 0x10, 0x2, 0x1c, 0xf0, 0x48, 0x9,
    0x7, 0x24, 0x7c, 0x44, 0x8c, 0x90, 0xe2, 0x0,
    0x40,

    /* U+0974 "ॴ" */
    0x0, 0x8, 0x0, 0x10, 0x0, 0x21, 0xcf, 0xf0,
    0x48, 0x80, 0x91, 0x7, 0x22, 0x47, 0xc4, 0x44,
    0x88, 0xc9, 0x10, 0xe2, 0x20, 0x4, 0x40,

    /* U+0975 "ॵ" */
    0x0, 0x20, 0x3, 0x30, 0x3, 0xd0, 0x0, 0xe3,
    0x9f, 0xe0, 0x91, 0x1, 0x22, 0xc, 0x44, 0xc7,
    0x88, 0x89, 0x11, 0x92, 0x21, 0xc4, 0x40, 0x8,
    0x80,

    /* U+0976 "ॶ" */
    0x39, 0xe0, 0x90, 0x12, 0xe, 0x48, 0xf8, 0x89,
    0x19, 0x21, 0xc4, 0x0, 0x80, 0x0, 0x22, 0x7,
    0x80,

    /* U+0977 "ॷ" */
    0x39, 0xe0, 0x90, 0x12, 0xe, 0x48, 0xf8, 0x89,
    0x19, 0x21, 0xc4, 0x0, 0x80, 0x10, 0x3e, 0x0,
    0x40, 0xf0,

    /* U+0978 "ॸ" */
    0xff, 0x20, 0x20, 0x7c, 0xe2, 0x62, 0x2, 0x6,
    0x0,

    /* U+0979 "ॹ" */
    0xff, 0xe0, 0x10, 0x3e, 0x26, 0x46, 0x48, 0x49,
    0x7, 0x20, 0x4, 0x14, 0x81, 0x0,

    /* U+097A "ॺ" */
    0xff, 0x91, 0xc, 0x85, 0x46, 0xe3, 0x30, 0xf8,
    0x4, 0x2, 0x0,

    /* U+097B "ॻ" */
    0xff, 0x91, 0x8, 0x8c, 0x46, 0x23, 0x10, 0x8,
    0x4, 0x7e, 0x0,

    /* U+097C "ॼ" */
    0xff, 0xe0, 0x10, 0x3e, 0x26, 0x44, 0x68, 0x4d,
    0x7, 0x20, 0x4, 0x7f, 0x80,

    /* U+097D "ॽ" */
    0xf0, 0x42, 0x13, 0x10, 0x84, 0x20,

    /* U+097E "ॾ" */
    0xff, 0x81, 0x7, 0x86, 0x1, 0xe2, 0x9, 0x84,
    0x3c, 0x7f, 0x0,

    /* U+097F "ॿ" */
    0xff, 0x81, 0xf, 0x8e, 0x45, 0xa2, 0x70, 0xf8,
    0x4, 0x7e, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 87, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 115, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 190, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 74, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 30, .adv_w = 81, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 81, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 136, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 48, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 54, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 55, .adv_w = 78, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 56, .adv_w = 61, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 99, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 66, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 123, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 68, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 68, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 150, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 156, .adv_w = 125, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 159, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 165, .adv_w = 118, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 82, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 178, .adv_w = 99, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 187, .adv_w = 82, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 193, .adv_w = 125, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 199, .adv_w = 92, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 200, .adv_w = 90, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 207, .adv_w = 121, .box_w = 1, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 209, .adv_w = 88, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 216, .adv_w = 125, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 218, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -5, .ofs_y = 10},
    {.bitmap_index = 220, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -5, .ofs_y = 10},
    {.bitmap_index = 222, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -3, .ofs_y = 10},
    {.bitmap_index = 223, .adv_w = 62, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 177, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 177, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 237, .box_w = 15, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 283, .adv_w = 112, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 297, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 176, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 195, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 160, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 347, .adv_w = 127, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 363, .adv_w = 127, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 378, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 390, .adv_w = 127, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 406, .adv_w = 237, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 237, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 237, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 237, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 175, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 188, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 129, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 136, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 146, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 161, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 171, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 173, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 618, .adv_w = 172, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 133, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 132, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 167, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 131, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 149, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 119, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 715, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 129, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 745, .adv_w = 130, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 756, .adv_w = 176, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 131, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 162, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 137, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 134, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 94, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 94, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 156, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 173, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 851, .adv_w = 173, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 868, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 157, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 133, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 156, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 122, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 923, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 9},
    {.bitmap_index = 924, .adv_w = 60, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 930, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -5, .ofs_y = -3},
    {.bitmap_index = 931, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 936, .adv_w = 60, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 60, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 60, .box_w = 7, .box_h = 13, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 970, .adv_w = 0, .box_w = 7, .box_h = 4, .ofs_x = -7, .ofs_y = -4},
    {.bitmap_index = 974, .adv_w = 0, .box_w = 7, .box_h = 4, .ofs_x = -5, .ofs_y = -4},
    {.bitmap_index = 978, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -4, .ofs_y = -4},
    {.bitmap_index = 980, .adv_w = 0, .box_w = 5, .box_h = 6, .ofs_x = -4, .ofs_y = -5},
    {.bitmap_index = 984, .adv_w = 0, .box_w = 6, .box_h = 3, .ofs_x = -5, .ofs_y = 10},
    {.bitmap_index = 987, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -7, .ofs_y = 9},
    {.bitmap_index = 990, .adv_w = 0, .box_w = 5, .box_h = 4, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 993, .adv_w = 0, .box_w = 5, .box_h = 4, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 996, .adv_w = 60, .box_w = 6, .box_h = 13, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1006, .adv_w = 60, .box_w = 7, .box_h = 13, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 1018, .adv_w = 60, .box_w = 6, .box_h = 13, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1028, .adv_w = 60, .box_w = 6, .box_h = 13, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1038, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -3, .ofs_y = -4},
    {.bitmap_index = 1040, .adv_w = 64, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1043, .adv_w = 60, .box_w = 7, .box_h = 13, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 1055, .adv_w = 209, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1072, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 9},
    {.bitmap_index = 1073, .adv_w = 0, .box_w = 5, .box_h = 1, .ofs_x = -6, .ofs_y = -2},
    {.bitmap_index = 1074, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 10},
    {.bitmap_index = 1076, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -3, .ofs_y = 10},
    {.bitmap_index = 1078, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -5, .ofs_y = 10},
    {.bitmap_index = 1081, .adv_w = 0, .box_w = 6, .box_h = 2, .ofs_x = -7, .ofs_y = -3},
    {.bitmap_index = 1083, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -7, .ofs_y = -4},
    {.bitmap_index = 1086, .adv_w = 175, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1100, .adv_w = 188, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1115, .adv_w = 129, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1127, .adv_w = 171, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1143, .adv_w = 132, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1157, .adv_w = 129, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1169, .adv_w = 176, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1183, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1195, .adv_w = 195, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1212, .adv_w = 160, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1229, .adv_w = 0, .box_w = 8, .box_h = 6, .ofs_x = -7, .ofs_y = -6},
    {.bitmap_index = 1235, .adv_w = 0, .box_w = 9, .box_h = 6, .ofs_x = -7, .ofs_y = -6},
    {.bitmap_index = 1242, .adv_w = 86, .box_w = 1, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1243, .adv_w = 137, .box_w = 4, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1247, .adv_w = 125, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1252, .adv_w = 125, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1257, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1264, .adv_w = 125, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1271, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1278, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1286, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1294, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1300, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1307, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1316, .adv_w = 97, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1318, .adv_w = 72, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1319, .adv_w = 177, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1337, .adv_w = 177, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1354, .adv_w = 237, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1377, .adv_w = 237, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1402, .adv_w = 177, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1419, .adv_w = 177, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1437, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1446, .adv_w = 171, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1460, .adv_w = 134, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1471, .adv_w = 129, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1482, .adv_w = 168, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1495, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1501, .adv_w = 132, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1512, .adv_w = 131, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t hi_14 = {
#else
lv_font_t hi_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if HI_14*/

