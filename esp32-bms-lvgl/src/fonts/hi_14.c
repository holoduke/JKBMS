/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --font /tmp/dv.ttf --size 14 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x900-0x97F -o src/fonts/hi_14.c
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
    0xfe, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x24, 0xff, 0x24, 0x24, 0xff, 0x28, 0x48,
    0x48,

    /* U+0024 "$" */
    0x10, 0x71, 0x56, 0x95, 0x6, 0x7, 0x49, 0x52,
    0xf8, 0x40, 0x80,

    /* U+0025 "%" */
    0x71, 0x22, 0x88, 0xa1, 0xd0, 0x4, 0x2, 0x61,
    0x24, 0x49, 0x21, 0x80,

    /* U+0026 "&" */
    0x38, 0x48, 0x48, 0x30, 0x30, 0xda, 0x8e, 0x84,
    0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x29, 0x49, 0x24, 0x91, 0x24,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x25, 0x28,

    /* U+002A "*" */
    0x25, 0x5c, 0xa5, 0x0,

    /* U+002B "+" */
    0x10, 0x23, 0xf8, 0x81, 0x2, 0x0,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x22, 0x24, 0x48, 0x80,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x52, 0x78,

    /* U+0031 "1" */
    0x13, 0xd1, 0x11, 0x11, 0x10,

    /* U+0032 "2" */
    0x7b, 0x38, 0x41, 0x8, 0xc4, 0x20, 0xfc,

    /* U+0033 "3" */
    0x39, 0x10, 0x46, 0xc, 0x18, 0x53, 0x38,

    /* U+0034 "4" */
    0x4, 0x18, 0x51, 0x24, 0x48, 0xbf, 0x82, 0x4,

    /* U+0035 "5" */
    0xfa, 0x8, 0x3e, 0x8c, 0x10, 0x63, 0x78,

    /* U+0036 "6" */
    0x39, 0x18, 0x2e, 0xce, 0x18, 0x53, 0x78,

    /* U+0037 "7" */
    0xfc, 0x30, 0x84, 0x30, 0x82, 0x10, 0x40,

    /* U+0038 "8" */
    0x7a, 0x18, 0x5e, 0xce, 0x18, 0x73, 0x78,

    /* U+0039 "9" */
    0x7b, 0x28, 0x61, 0xcd, 0xd0, 0x62, 0x70,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x83, 0x80,

    /* U+003C "<" */
    0x2, 0x39, 0x86, 0x3, 0x1, 0xc0,

    /* U+003D "=" */
    0xfe, 0x3, 0xf8,

    /* U+003E ">" */
    0x80, 0xc0, 0x70, 0x33, 0x98, 0x0,

    /* U+003F "?" */
    0x74, 0x62, 0x11, 0x10, 0x80, 0x20,

    /* U+0040 "@" */
    0x1e, 0x31, 0x97, 0xf2, 0x5a, 0x4d, 0x26, 0x94,
    0xbe, 0x61, 0x1f, 0x0,

    /* U+0041 "A" */
    0x18, 0x18, 0x24, 0x24, 0x44, 0x7e, 0x42, 0x81,
    0x81,

    /* U+0042 "B" */
    0xf9, 0xa, 0x17, 0xc8, 0x50, 0x60, 0xc3, 0xfc,

    /* U+0043 "C" */
    0x3c, 0x63, 0xc1, 0x80, 0x80, 0x80, 0xc1, 0x62,
    0x3c,

    /* U+0044 "D" */
    0xfc, 0x86, 0x83, 0x81, 0x81, 0x81, 0x83, 0x86,
    0xfc,

    /* U+0045 "E" */
    0xfd, 0x2, 0x4, 0xf, 0xd0, 0x20, 0x40, 0xfe,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0xfe, 0x8, 0x20, 0x80,

    /* U+0047 "G" */
    0x3e, 0x31, 0xb0, 0x50, 0x8, 0x7c, 0xf, 0x6,
    0xc5, 0x3c, 0x80,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1, 0x82,

    /* U+0049 "I" */
    0xff, 0x80,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x86, 0x31, 0x70,

    /* U+004B "K" */
    0x87, 0x1a, 0x65, 0xd, 0x11, 0x23, 0x42, 0x82,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0xfc,

    /* U+004D "M" */
    0xc1, 0xe0, 0xf0, 0x74, 0x5a, 0x2c, 0xa6, 0x53,
    0x29, 0x88, 0x80,

    /* U+004E "N" */
    0xc3, 0x86, 0x8d, 0x19, 0x31, 0x62, 0xc3, 0x86,

    /* U+004F "O" */
    0x3e, 0x31, 0xb0, 0x70, 0x18, 0xc, 0x7, 0x6,
    0xc6, 0x3e, 0x0,

    /* U+0050 "P" */
    0xfa, 0x18, 0x61, 0xfa, 0x8, 0x20, 0x80,

    /* U+0051 "Q" */
    0x3e, 0x31, 0xb0, 0x70, 0x18, 0xc, 0x7, 0x6,
    0xc6, 0x3f, 0x80, 0x40,

    /* U+0052 "R" */
    0xfd, 0xe, 0xc, 0x3f, 0xd0, 0x60, 0xc1, 0x82,

    /* U+0053 "S" */
    0x3c, 0x42, 0x41, 0x20, 0x1c, 0x3, 0x41, 0x63,
    0x3e,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xe2, 0x38,

    /* U+0056 "V" */
    0x83, 0x6, 0x12, 0x24, 0x49, 0xa, 0x14, 0x10,

    /* U+0057 "W" */
    0x84, 0x31, 0x86, 0x29, 0x45, 0x25, 0x24, 0xa2,
    0x94, 0x61, 0xc, 0x21, 0x80,

    /* U+0058 "X" */
    0x84, 0x89, 0x21, 0x81, 0x6, 0x12, 0x22, 0x84,

    /* U+0059 "Y" */
    0x82, 0x89, 0x11, 0x42, 0x82, 0x4, 0x8, 0x10,

    /* U+005A "Z" */
    0xfe, 0xc, 0x10, 0x41, 0x4, 0x10, 0x60, 0xfe,

    /* U+005B "[" */
    0xea, 0xaa, 0xaa, 0xc0,

    /* U+005C "\\" */
    0x88, 0x44, 0x42, 0x22, 0x10,

    /* U+005D "]" */
    0xd5, 0x55, 0x55, 0xc0,

    /* U+005E "^" */
    0x30, 0xc4, 0xa1,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0xe0,

    /* U+0061 "a" */
    0x73, 0x20, 0x8e, 0xca, 0x66, 0xc0,

    /* U+0062 "b" */
    0x82, 0xb, 0xb3, 0x86, 0x18, 0x73, 0xb8,

    /* U+0063 "c" */
    0x7b, 0x38, 0x20, 0x87, 0x27, 0x80,

    /* U+0064 "d" */
    0x4, 0x17, 0x73, 0x86, 0x18, 0x73, 0x74,

    /* U+0065 "e" */
    0x7b, 0x38, 0x7f, 0x81, 0x17, 0x80,

    /* U+0066 "f" */
    0x74, 0xe4, 0x44, 0x44, 0x40,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x85, 0x37, 0x41, 0x4d, 0xe0,

    /* U+0068 "h" */
    0x84, 0x2d, 0x98, 0xc6, 0x31, 0x88,

    /* U+0069 "i" */
    0xbf, 0x80,

    /* U+006A "j" */
    0x45, 0x55, 0x57,

    /* U+006B "k" */
    0x82, 0x8, 0xa4, 0xa3, 0xc9, 0x22, 0x88,

    /* U+006C "l" */
    0xff, 0x80,

    /* U+006D "m" */
    0xb7, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x87, 0x3b, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0x4, 0x10,

    /* U+0072 "r" */
    0xfa, 0x49, 0x20,

    /* U+0073 "s" */
    0x74, 0x60, 0xe0, 0xc5, 0xc0,

    /* U+0074 "t" */
    0x44, 0xe4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x85, 0x14, 0x92, 0x28, 0xc1, 0x0,

    /* U+0077 "w" */
    0x8c, 0xa6, 0x53, 0x2a, 0xa5, 0x31, 0x98, 0x8c,

    /* U+0078 "x" */
    0x45, 0x23, 0x4, 0x39, 0x24, 0x40,

    /* U+0079 "y" */
    0x85, 0x14, 0x9a, 0x28, 0xc1, 0x4, 0x21, 0x80,

    /* U+007A "z" */
    0xfc, 0x21, 0x8, 0x63, 0xf, 0xc0,

    /* U+007B "{" */
    0x69, 0x24, 0xa2, 0x49, 0x26,

    /* U+007C "|" */
    0xff, 0xf8,

    /* U+007D "}" */
    0xc9, 0x24, 0x8a, 0x49, 0x2c,

    /* U+007E "~" */
    0x71, 0x9a, 0x8e,

    /* U+0900 "ऀ" */
    0x7b, 0x13, 0x0,

    /* U+0901 "ँ" */
    0x30, 0x14, 0xce,

    /* U+0902 "ं" */
    0xc0,

    /* U+0903 "ः" */
    0xc0, 0x30,

    /* U+0904 "ऄ" */
    0x10, 0x1, 0x0, 0x1e, 0x0, 0x43, 0xbe, 0x91,
    0x2, 0x21, 0xc4, 0x87, 0x90, 0x91, 0x12, 0x1c,
    0x40, 0x8,

    /* U+0905 "अ" */
    0x3b, 0xe9, 0x10, 0x22, 0xc, 0x48, 0x78, 0x89,
    0x19, 0x21, 0xc4, 0x0, 0x80,

    /* U+0906 "आ" */
    0x33, 0xfd, 0x22, 0x40, 0x89, 0xe, 0x64, 0x86,
    0x92, 0x12, 0x44, 0x49, 0xe, 0x24, 0x0, 0x90,

    /* U+0907 "इ" */
    0xff, 0x4, 0x7c, 0x80, 0x7c, 0x4, 0xec, 0x98,
    0xe8, 0x0,

    /* U+0908 "ई" */
    0xc, 0x10, 0x10, 0x8, 0xff, 0x4, 0x7c, 0x80,
    0x7c, 0x4, 0xec, 0xb0, 0xe8, 0x0,

    /* U+0909 "उ" */
    0xff, 0x82, 0x1, 0x3, 0x8, 0x64, 0x11, 0x98,
    0x78,

    /* U+090A "ऊ" */
    0xff, 0xf0, 0x40, 0x4, 0x1, 0x98, 0x86, 0x48,
    0x24, 0x66, 0xc3, 0xc0,

    /* U+090B "ऋ" */
    0xff, 0xe0, 0x80, 0xd6, 0x26, 0xc0, 0x78, 0x39,
    0x89, 0x40, 0x30, 0x5, 0xc0,

    /* U+090C "ऌ" */
    0xff, 0xe0, 0x81, 0x9c, 0x4c, 0xc9, 0x19, 0x3,
    0x10, 0x81, 0x20, 0x8, 0x1, 0x30, 0x1c, 0x0,

    /* U+090D "ऍ" */
    0x12, 0xc, 0x0, 0xff, 0x44, 0x44, 0x44, 0x44,
    0x60, 0x30, 0xc, 0x2, 0x2,

    /* U+090E "ऎ" */
    0xc0, 0x40, 0x3c, 0x4, 0xff, 0x44, 0x44, 0x44,
    0x44, 0x40, 0x30, 0x1c, 0x6, 0x2, 0x0,

    /* U+090F "ए" */
    0xff, 0x44, 0x44, 0x44, 0x44, 0x40, 0x30, 0x1c,
    0x6, 0x2, 0x0,

    /* U+0910 "ऐ" */
    0x70, 0x8, 0x4, 0x4, 0xff, 0x44, 0x44, 0x44,
    0x44, 0x40, 0x30, 0x1c, 0x6, 0x2, 0x0,

    /* U+0911 "ऑ" */
    0x0, 0x90, 0x1, 0x80, 0x0, 0x1e, 0xff, 0x8,
    0x90, 0x62, 0x43, 0x99, 0x21, 0xa4, 0x84, 0x91,
    0x12, 0x43, 0x89, 0x0, 0x24,

    /* U+0912 "ऒ" */
    0x1, 0x0, 0x4, 0x0, 0xf, 0x0, 0x4, 0x33,
    0xfd, 0x22, 0x40, 0x89, 0xe, 0x64, 0x86, 0x92,
    0x12, 0x44, 0x49, 0xe, 0x24, 0x0, 0x90,

    /* U+0913 "ओ" */
    0x1, 0xc0, 0x0, 0x80, 0x1, 0x0, 0x4, 0x33,
    0xfd, 0x22, 0x40, 0x89, 0xe, 0x24, 0x87, 0x92,
    0x12, 0x44, 0x49, 0xe, 0x24, 0x0, 0x90,

    /* U+0914 "औ" */
    0x0, 0xc0, 0x0, 0x80, 0x1d, 0x0, 0xc, 0x33,
    0xfd, 0x22, 0x40, 0x89, 0xc, 0x24, 0x8f, 0x92,
    0x12, 0x44, 0x49, 0xe, 0x24, 0x0, 0x90,

    /* U+0915 "क" */
    0xff, 0xe1, 0x1, 0xec, 0x4e, 0x48, 0x89, 0x31,
    0x1e, 0x40, 0x40, 0x8, 0x0,

    /* U+0916 "ख" */
    0xff, 0xe2, 0x18, 0x4f, 0xa, 0x65, 0x4c, 0xc7,
    0x88, 0x31, 0x8e, 0xe, 0xc0,

    /* U+0917 "ग" */
    0xff, 0x44, 0x44, 0x44, 0xc4, 0xc4, 0x44, 0x4,
    0x4,

    /* U+0918 "घ" */
    0xff, 0xc1, 0x10, 0x8e, 0x44, 0x22, 0x30, 0xe8,
    0x4, 0x2, 0x0,

    /* U+0919 "ङ" */
    0xff, 0x80, 0x87, 0xc4, 0x31, 0xf2, 0x8, 0x84,
    0x3c,

    /* U+091A "च" */
    0xff, 0x81, 0x1e, 0x86, 0x42, 0x22, 0x30, 0xe8,
    0x4, 0x2, 0x0,

    /* U+091B "छ" */
    0xff, 0xe1, 0x8, 0xe3, 0x24, 0x3d, 0x10, 0xc4,
    0x31, 0x98, 0x3c, 0x0,

    /* U+091C "ज" */
    0xff, 0xc0, 0x40, 0x12, 0x3c, 0x45, 0x9, 0x41,
    0xd0, 0x4, 0x1, 0x0,

    /* U+091D "झ" */
    0xff, 0xe0, 0x91, 0xf2, 0x20, 0x47, 0xf8, 0x9,
    0x19, 0x24, 0xc4, 0x78, 0x80, 0x0,

    /* U+091E "ञ" */
    0xff, 0xc0, 0x47, 0x91, 0x24, 0x7, 0x22, 0x47,
    0x90, 0x4, 0x1, 0x0,

    /* U+091F "ट" */
    0xff, 0x84, 0xe, 0x8, 0x8, 0x4, 0x2, 0x8,
    0x88, 0x38, 0x0,

    /* U+0920 "ठ" */
    0xff, 0x8, 0x38, 0x48, 0x84, 0x84, 0x84, 0x44,
    0x38,

    /* U+0921 "ड" */
    0xff, 0x80, 0x87, 0xc4, 0x1, 0xf2, 0x8, 0x84,
    0x3c,

    /* U+0922 "ढ" */
    0xfe, 0x8, 0xf2, 0x8, 0x13, 0xa5, 0x2e, 0x38,

    /* U+0923 "ण" */
    0xff, 0xe8, 0x91, 0x12, 0x22, 0x44, 0x48, 0x91,
    0xe, 0x20, 0x4, 0x0, 0x80,

    /* U+0924 "त" */
    0xff, 0x4, 0x4, 0x7c, 0x84, 0x84, 0x44, 0x44,
    0x24,

    /* U+0925 "थ" */
    0xef, 0xa4, 0xe4, 0x24, 0xc4, 0xcc, 0x74, 0x4,
    0x4,

    /* U+0926 "द" */
    0xfe, 0x11, 0xe6, 0x8, 0x13, 0x36, 0x1c, 0xc,

    /* U+0927 "ध" */
    0x67, 0xf9, 0x20, 0x9e, 0x48, 0x26, 0x11, 0xf8,
    0x4, 0x2, 0x0,

    /* U+0928 "न" */
    0xff, 0x81, 0x0, 0x8f, 0xc6, 0x20, 0x10, 0x8,
    0x4, 0x2, 0x0,

    /* U+0929 "ऩ" */
    0xff, 0x81, 0x0, 0x8f, 0xc6, 0x21, 0x10, 0x8,
    0x4, 0x62, 0x0,

    /* U+092A "प" */
    0xff, 0x44, 0x44, 0x44, 0x44, 0x44, 0x3c, 0x4,
    0x4,

    /* U+092B "फ" */
    0xff, 0xf4, 0x40, 0x45, 0x84, 0x64, 0x44, 0x44,
    0x44, 0x3c, 0x80, 0x40, 0x4, 0x0,

    /* U+092C "ब" */
    0xff, 0x4, 0x74, 0xa4, 0xa4, 0xdc, 0x7c, 0x4,
    0x4,

    /* U+092D "भ" */
    0xef, 0xd1, 0x38, 0x84, 0x42, 0x23, 0xf0, 0x88,
    0x4, 0x2, 0x0,

    /* U+092E "म" */
    0xff, 0x44, 0x44, 0x44, 0xfc, 0xc4, 0x4, 0x4,
    0x4,

    /* U+092F "य" */
    0xff, 0x91, 0x8, 0x84, 0x4c, 0x22, 0x30, 0xe8,
    0x4, 0x2, 0x0,

    /* U+0930 "र" */
    0xfe, 0x20, 0x40, 0x87, 0x8, 0x8, 0x8, 0x8,

    /* U+0931 "ऱ" */
    0xfe, 0x20, 0x40, 0x85, 0xc, 0x8, 0x8, 0xc8,

    /* U+0932 "ल" */
    0xff, 0x81, 0x0, 0x8c, 0x49, 0xe4, 0xd2, 0x8,
    0x84, 0x22, 0x0,

    /* U+0933 "ळ" */
    0xff, 0xc1, 0x0, 0x41, 0xb8, 0x99, 0x24, 0x49,
    0x91, 0xb8,

    /* U+0934 "ऴ" */
    0xff, 0xc1, 0x0, 0x41, 0xb8, 0x99, 0x24, 0x49,
    0x91, 0xb8, 0x0, 0x2, 0x0,

    /* U+0935 "व" */
    0xff, 0x4, 0x74, 0x84, 0x84, 0xcc, 0x7c, 0x4,
    0x4,

    /* U+0936 "श" */
    0x33, 0xd2, 0x43, 0x90, 0x24, 0x69, 0x24, 0x47,
    0x90, 0x14, 0x5, 0x0,

    /* U+0937 "ष" */
    0xff, 0x64, 0x54, 0x4c, 0x44, 0x44, 0x3c, 0x4,
    0x4,

    /* U+0938 "स" */
    0xff, 0xc4, 0x41, 0x10, 0x44, 0x7f, 0x18, 0x42,
    0x10, 0x44, 0x9, 0x0,

    /* U+0939 "ह" */
    0xfc, 0x2f, 0xa0, 0xb3, 0x28, 0xa2, 0x40, 0x80,
    0x0,

    /* U+093A "ऺ" */
    0xe0,

    /* U+093B "ऻ" */
    0x21, 0x9, 0xf2, 0x10, 0x84, 0x21, 0x8, 0x40,

    /* U+093C "़" */
    0x80,

    /* U+093D "ऽ" */
    0xfc, 0x20, 0x83, 0xc, 0x31, 0x70,

    /* U+093E "ा" */
    0xf4, 0x44, 0x44, 0x44, 0x40,

    /* U+093F "ि" */
    0x3c, 0x8, 0x61, 0x3, 0x10, 0x2f, 0x80, 0x40,
    0x8, 0x1, 0x0, 0x20, 0x4, 0x0, 0x80, 0x10,
    0x2, 0x0,

    /* U+0940 "ी" */
    0x70, 0x88, 0x88, 0x84, 0xf, 0x4, 0x4, 0x4,
    0x4, 0x4, 0x4, 0x4, 0x4,

    /* U+0941 "ु" */
    0x18, 0x18, 0x71, 0x38,

    /* U+0942 "ू" */
    0x71, 0x12, 0x14, 0xa6, 0x0,

    /* U+0943 "ृ" */
    0x72, 0x46,

    /* U+0944 "ॄ" */
    0xf1, 0xc6,

    /* U+0945 "ॅ" */
    0xcd, 0xe0,

    /* U+0946 "ॆ" */
    0x86, 0xe, 0x10, 0x80,

    /* U+0947 "े" */
    0xe3, 0x11,

    /* U+0948 "ै" */
    0xe0, 0xbc, 0x61, 0x80,

    /* U+0949 "ॉ" */
    0x93, 0x81, 0xf2, 0x10, 0x84, 0x21, 0x8, 0x40,

    /* U+094A "ॊ" */
    0x80, 0x40, 0x3c, 0x4, 0x1f, 0x4, 0x4, 0x4,
    0x4, 0x4, 0x4, 0x4, 0x4,

    /* U+094B "ो" */
    0xe0, 0x20, 0x20, 0x43, 0xe1, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0x80,

    /* U+094C "ौ" */
    0x60, 0x23, 0xa0, 0xc3, 0xe1, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0x80,

    /* U+094D "्" */
    0xc, 0x21,

    /* U+094E "ॎ" */
    0xf2, 0x49, 0x24, 0x80,

    /* U+094F "ॏ" */
    0x50, 0x99, 0xc8, 0x61, 0xe0, 0x81, 0x2, 0x4,
    0x8, 0x10, 0x20, 0x40,

    /* U+0950 "ॐ" */
    0x2, 0x1, 0x0, 0x3e, 0x18, 0x4, 0x8c, 0x12,
    0x46, 0x48, 0x31, 0x84, 0x28, 0x98, 0xe0, 0x0,

    /* U+0951 "॑" */
    0xe0,

    /* U+0952 "॒" */
    0xfe,

    /* U+0953 "॓" */
    0x90,

    /* U+0954 "॔" */
    0x60,

    /* U+0955 "ॕ" */
    0x96, 0xf0,

    /* U+0956 "ॖ" */
    0x87, 0xe0,

    /* U+0957 "ॗ" */
    0x83, 0xe8, 0xde,

    /* U+0958 "क़" */
    0xff, 0xe1, 0x1, 0xec, 0x4e, 0x48, 0x89, 0x31,
    0x1e, 0x40, 0x40, 0x28, 0x0,

    /* U+0959 "ख़" */
    0xff, 0xe2, 0x18, 0x4f, 0xa, 0x65, 0x4c, 0xc7,
    0x88, 0x31, 0x8e, 0xce, 0xc0,

    /* U+095A "ग़" */
    0xff, 0x44, 0x44, 0x44, 0xc4, 0xc4, 0x44, 0x4,
    0xc4,

    /* U+095B "ज़" */
    0xff, 0xc0, 0x40, 0x12, 0x3c, 0x45, 0x9, 0x41,
    0xd0, 0x4, 0x41, 0x0,

    /* U+095C "ड़" */
    0xff, 0x80, 0x87, 0xc4, 0x1, 0xf2, 0x8, 0x84,
    0x3c, 0x0, 0x0, 0x2, 0x0,

    /* U+095D "ढ़" */
    0xfe, 0x8, 0xf2, 0x8, 0x13, 0xa5, 0x2e, 0x38,
    0x0, 0x20,

    /* U+095E "फ़" */
    0xff, 0xf4, 0x40, 0x45, 0x84, 0x64, 0x44, 0x44,
    0x44, 0x3c, 0x80, 0x40, 0x24, 0x0,

    /* U+095F "य़" */
    0xff, 0x91, 0x8, 0x84, 0x4c, 0x22, 0x30, 0xe8,
    0x4, 0x22, 0x0,

    /* U+0960 "ॠ" */
    0xff, 0xe0, 0x80, 0xd2, 0x26, 0xc0, 0x78, 0x39,
    0x89, 0x40, 0x26, 0x5, 0x0, 0x18,

    /* U+0961 "ॡ" */
    0xff, 0xe0, 0x81, 0x9c, 0x4c, 0xc9, 0x19, 0x6,
    0x11, 0x1, 0x40, 0x6, 0x0, 0x80, 0x1c, 0x0,

    /* U+0962 "ॢ" */
    0xfe, 0x58, 0x52, 0x10, 0x50, 0xc0,

    /* U+0963 "ॣ" */
    0xfe, 0x58, 0x94, 0x18, 0x40, 0x80,

    /* U+0964 "।" */
    0xff,

    /* U+0965 "॥" */
    0xb6, 0xdb, 0x6d,

    /* U+0966 "०" */
    0x6d, 0x9d, 0x60,

    /* U+0967 "१" */
    0x69, 0x97, 0x24, 0xc4, 0x22,

    /* U+0968 "२" */
    0x78, 0x8c, 0x4, 0x4, 0x74, 0x58, 0x78, 0x4,
    0x6, 0x2,

    /* U+0969 "३" */
    0x70, 0x41, 0x1c, 0xb, 0x2b, 0x9c, 0x8, 0x10,

    /* U+096A "४" */
    0x7, 0x37, 0xc, 0x49, 0x24, 0x8c,

    /* U+096B "५" */
    0x1, 0x2, 0x3c, 0x54, 0xe7, 0x1, 0x2, 0x2,
    0x0,

    /* U+096C "६" */
    0x74, 0x20, 0xc8, 0x5f, 0xa6, 0x10, 0x40,

    /* U+096D "७" */
    0x86, 0x89, 0x89, 0x49, 0x47, 0x41, 0x22, 0x1e,

    /* U+096E "८" */
    0x0, 0x21, 0x8, 0x42, 0x8, 0x32, 0x70,

    /* U+096F "९" */
    0x64, 0xa5, 0xc4, 0x10, 0x41, 0x8, 0x0,

    /* U+0970 "॰" */
    0xf7, 0x80,

    /* U+0971 "ॱ" */
    0x80,

    /* U+0972 "ॲ" */
    0x1, 0x0, 0x38, 0x0, 0x1d, 0xf0, 0x88, 0x11,
    0x7, 0x24, 0x3c, 0x44, 0x8c, 0x90, 0xe2, 0x0,
    0x40,

    /* U+0973 "ॳ" */
    0x0, 0x80, 0x10, 0x2, 0x1d, 0xf6, 0x88, 0x11,
    0x6, 0x24, 0x3c, 0x44, 0x8c, 0x90, 0xf2, 0x0,
    0x40,

    /* U+0974 "ॴ" */
    0x0, 0x10, 0x0, 0x40, 0x1, 0xc, 0xff, 0x48,
    0x90, 0x22, 0x43, 0x89, 0x21, 0xe4, 0x84, 0x91,
    0x12, 0x43, 0x89, 0x0, 0x24,

    /* U+0975 "ॵ" */
    0x0, 0x40, 0x9, 0x0, 0x44, 0x1, 0xe3, 0x3f,
    0xa4, 0x48, 0x22, 0x46, 0x12, 0x8f, 0x94, 0x24,
    0x91, 0x24, 0x71, 0x20, 0x9, 0x0,

    /* U+0976 "ॶ" */
    0x3b, 0xe9, 0x10, 0x22, 0xc, 0x48, 0x78, 0x89,
    0x19, 0x21, 0xc4, 0x0, 0x80, 0x0, 0xc4, 0xf,
    0x0,

    /* U+0977 "ॷ" */
    0x3b, 0xe9, 0x10, 0x22, 0xc, 0x48, 0x78, 0x89,
    0x19, 0x21, 0xc4, 0x0, 0x80, 0x0, 0x7c, 0x0,
    0x81, 0xf0,

    /* U+0978 "ॸ" */
    0xff, 0x20, 0x20, 0x3c, 0x62, 0x62, 0x62, 0x2,
    0x4,

    /* U+0979 "ॹ" */
    0xff, 0xc0, 0x40, 0x10, 0x7c, 0x89, 0x11, 0x42,
    0x50, 0x64, 0x1, 0xd, 0x0, 0x80,

    /* U+097A "ॺ" */
    0xff, 0x91, 0xc, 0x85, 0x4c, 0x62, 0x30, 0xe8,
    0x4, 0x2, 0x0,

    /* U+097B "ॻ" */
    0xff, 0x44, 0x44, 0x44, 0xc4, 0xc4, 0x44, 0x4,
    0x4, 0xff,

    /* U+097C "ॼ" */
    0xff, 0xc0, 0x40, 0x12, 0x3c, 0x45, 0x9, 0x41,
    0xd0, 0x4, 0x1, 0x0, 0xf, 0xfc,

    /* U+097D "ॽ" */
    0x7a, 0x30, 0x41, 0x8, 0xc2, 0x8, 0x20,

    /* U+097E "ॾ" */
    0xff, 0x80, 0x41, 0xf0, 0x80, 0x1f, 0x10, 0x42,
    0x10, 0x78, 0x0, 0x0, 0xf, 0xfc,

    /* U+097F "ॿ" */
    0xff, 0x4, 0x74, 0xa4, 0xa4, 0xdc, 0x7c, 0x4,
    0x4, 0x0, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 51, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 41, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 67, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 162, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 25, .adv_w = 186, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 36, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 47, .adv_w = 70, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 52, .adv_w = 70, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 57, .adv_w = 105, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 61, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 67, .adv_w = 45, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 72, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 69, .adv_w = 43, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 66, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 123, .box_w = 4, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 43, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 45, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 147, .adv_w = 125, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 153, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 156, .adv_w = 125, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 162, .adv_w = 111, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 174, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 180, .adv_w = 161, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 145, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 157, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 137, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 169, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 159, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 65, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 125, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 152, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 183, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 159, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 163, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 139, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 163, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 321, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 137, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 157, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 202, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 133, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 53, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 403, .adv_w = 64, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 54, .box_w = 2, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 412, .adv_w = 97, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 415, .adv_w = 129, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 416, .adv_w = 44, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 417, .adv_w = 113, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 63, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 462, .adv_w = 121, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 49, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 51, .box_w = 2, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 473, .adv_w = 109, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 49, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 182, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 121, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 509, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 517, .adv_w = 73, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 68, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 121, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 103, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 563, .adv_w = 102, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 67, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 574, .adv_w = 48, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 576, .adv_w = 63, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 581, .adv_w = 136, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 584, .adv_w = 0, .box_w = 6, .box_h = 3, .ofs_x = -7, .ofs_y = 10},
    {.bitmap_index = 587, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -7, .ofs_y = 9},
    {.bitmap_index = 590, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = -3, .ofs_y = 11},
    {.bitmap_index = 591, .adv_w = 71, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 593, .adv_w = 169, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 169, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 221, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 121, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 650, .adv_w = 121, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 664, .adv_w = 142, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 673, .adv_w = 195, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 685, .adv_w = 176, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 165, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 714, .adv_w = 118, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 727, .adv_w = 118, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 742, .adv_w = 118, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 753, .adv_w = 118, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 768, .adv_w = 221, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 221, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 221, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 835, .adv_w = 221, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 858, .adv_w = 170, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 174, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 131, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 137, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 904, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 913, .adv_w = 134, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 153, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 948, .adv_w = 165, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 962, .adv_w = 152, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 974, .adv_w = 140, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 985, .adv_w = 140, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 994, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1003, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1011, .adv_w = 162, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1024, .adv_w = 121, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1033, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1042, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1050, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1061, .adv_w = 130, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1072, .adv_w = 130, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1083, .adv_w = 112, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 170, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1106, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1115, .adv_w = 146, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1126, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1146, .adv_w = 100, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1154, .adv_w = 100, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1173, .adv_w = 161, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1183, .adv_w = 161, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1196, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1205, .adv_w = 154, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1217, .adv_w = 117, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 145, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1247, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 9},
    {.bitmap_index = 1248, .adv_w = 65, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1256, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -6, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1263, .adv_w = 58, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1268, .adv_w = 58, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1286, .adv_w = 56, .box_w = 8, .box_h = 13, .ofs_x = -4, .ofs_y = 0},
    {.bitmap_index = 1299, .adv_w = 0, .box_w = 6, .box_h = 5, .ofs_x = -6, .ofs_y = -4},
    {.bitmap_index = 1303, .adv_w = 0, .box_w = 7, .box_h = 5, .ofs_x = -4, .ofs_y = -4},
    {.bitmap_index = 1308, .adv_w = 0, .box_w = 3, .box_h = 5, .ofs_x = -4, .ofs_y = -4},
    {.bitmap_index = 1310, .adv_w = 0, .box_w = 3, .box_h = 5, .ofs_x = -4, .ofs_y = -4},
    {.bitmap_index = 1312, .adv_w = 0, .box_w = 6, .box_h = 2, .ofs_x = -5, .ofs_y = 10},
    {.bitmap_index = 1314, .adv_w = 0, .box_w = 5, .box_h = 5, .ofs_x = -7, .ofs_y = 8},
    {.bitmap_index = 1318, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 1320, .adv_w = 0, .box_w = 5, .box_h = 5, .ofs_x = -6, .ofs_y = 8},
    {.bitmap_index = 1324, .adv_w = 65, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1332, .adv_w = 65, .box_w = 8, .box_h = 13, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 1345, .adv_w = 65, .box_w = 7, .box_h = 13, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1357, .adv_w = 65, .box_w = 7, .box_h = 13, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1369, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -3, .ofs_y = -4},
    {.bitmap_index = 1371, .adv_w = 72, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1375, .adv_w = 65, .box_w = 7, .box_h = 13, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 1387, .adv_w = 216, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1403, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 10},
    {.bitmap_index = 1404, .adv_w = 0, .box_w = 7, .box_h = 1, .ofs_x = -4, .ofs_y = -3},
    {.bitmap_index = 1405, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -5, .ofs_y = 11},
    {.bitmap_index = 1406, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -5, .ofs_y = 11},
    {.bitmap_index = 1407, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 1409, .adv_w = 0, .box_w = 6, .box_h = 2, .ofs_x = -8, .ofs_y = -3},
    {.bitmap_index = 1411, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -8, .ofs_y = -4},
    {.bitmap_index = 1414, .adv_w = 170, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1427, .adv_w = 174, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1440, .adv_w = 131, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 153, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1461, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1474, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1484, .adv_w = 170, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1498, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1509, .adv_w = 176, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1523, .adv_w = 165, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1539, .adv_w = 0, .box_w = 6, .box_h = 7, .ofs_x = -7, .ofs_y = -6},
    {.bitmap_index = 1545, .adv_w = 0, .box_w = 6, .box_h = 7, .ofs_x = -7, .ofs_y = -6},
    {.bitmap_index = 1551, .adv_w = 73, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1552, .adv_w = 112, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1555, .adv_w = 95, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1558, .adv_w = 101, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1563, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1573, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1581, .adv_w = 140, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1587, .adv_w = 143, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1596, .adv_w = 119, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1603, .adv_w = 160, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1611, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1618, .adv_w = 119, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1625, .adv_w = 61, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1627, .adv_w = 51, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1628, .adv_w = 169, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1645, .adv_w = 169, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1662, .adv_w = 221, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1683, .adv_w = 221, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1705, .adv_w = 169, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1722, .adv_w = 169, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1740, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1749, .adv_w = 153, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1763, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1774, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1784, .adv_w = 153, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1798, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1805, .adv_w = 148, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1819, .adv_w = 124, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 2304, .range_length = 128, .glyph_id_start = 96,
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
    .cmap_num = 2,
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
    .line_height = 19,          /*The maximum line height required by the font*/
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

