/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --font /tmp/dv.ttf --size 12 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x900-0x97F -o src/fonts/hi_12.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef HI_12
#define HI_12 1
#endif

#if HI_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x28, 0x53, 0xfa, 0x44, 0x9f, 0xd4, 0x28,

    /* U+0024 "$" */
    0x27, 0xab, 0x47, 0x16, 0xb5, 0x71, 0x0,

    /* U+0025 "%" */
    0x62, 0x4a, 0x25, 0xd, 0x1, 0x30, 0xa8, 0x94,
    0x46,

    /* U+0026 "&" */
    0x30, 0x91, 0x21, 0x86, 0x12, 0xa3, 0x39,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x5a, 0xaa, 0x94,

    /* U+0029 ")" */
    0xa5, 0x55, 0x68,

    /* U+002A "*" */
    0x23, 0x4c, 0xa0,

    /* U+002B "+" */
    0x10, 0x23, 0xf8, 0x81, 0x0,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x22, 0x24, 0x44, 0x88,

    /* U+0030 "0" */
    0x7b, 0x28, 0x61, 0x86, 0x1c, 0x9e,

    /* U+0031 "1" */
    0x13, 0xd1, 0x11, 0x11,

    /* U+0032 "2" */
    0x39, 0x18, 0x43, 0x10, 0x84, 0x3f,

    /* U+0033 "3" */
    0x74, 0x42, 0x60, 0xc6, 0x2e,

    /* U+0034 "4" */
    0x8, 0x62, 0x92, 0x8b, 0xf0, 0x82,

    /* U+0035 "5" */
    0x79, 0x4, 0x1e, 0x4c, 0x14, 0xde,

    /* U+0036 "6" */
    0x39, 0x14, 0x2e, 0xc5, 0x14, 0x4e,

    /* U+0037 "7" */
    0xf8, 0x44, 0x42, 0x21, 0x8,

    /* U+0038 "8" */
    0x74, 0x62, 0xe8, 0xc6, 0x2e,

    /* U+0039 "9" */
    0x72, 0x28, 0xa2, 0x78, 0x28, 0x9c,

    /* U+003A ":" */
    0x84,

    /* U+003B ";" */
    0x86,

    /* U+003C "<" */
    0x4, 0xec, 0x18, 0x18,

    /* U+003D "=" */
    0xfc, 0xf, 0xc0,

    /* U+003E ">" */
    0x81, 0x81, 0xc6, 0xe0,

    /* U+003F "?" */
    0x74, 0x62, 0x22, 0x10, 0x4,

    /* U+0040 "@" */
    0x3c, 0x5e, 0xa5, 0xc5, 0xc9, 0xb6, 0x42, 0x3c,

    /* U+0041 "A" */
    0x10, 0x60, 0xa2, 0x44, 0x4f, 0xa1, 0x41,

    /* U+0042 "B" */
    0xfa, 0x18, 0x7e, 0x8e, 0x18, 0x7e,

    /* U+0043 "C" */
    0x3c, 0x86, 0xc, 0x8, 0x10, 0x51, 0x9e,

    /* U+0044 "D" */
    0xf9, 0xa, 0xc, 0x18, 0x30, 0x61, 0x7c,

    /* U+0045 "E" */
    0xfe, 0x8, 0x3e, 0x82, 0x8, 0x3f,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf8, 0x42, 0x10,

    /* U+0047 "G" */
    0x3c, 0x8e, 0x4, 0x78, 0x30, 0x51, 0x9d,

    /* U+0048 "H" */
    0x86, 0x18, 0x7f, 0x86, 0x18, 0x61,

    /* U+0049 "I" */
    0xff,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0xc6, 0x2e,

    /* U+004B "K" */
    0x85, 0x12, 0x45, 0xd, 0x11, 0x22, 0x42,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x1f,

    /* U+004D "M" */
    0x81, 0xc3, 0xc3, 0xa5, 0xa5, 0xa9, 0x99, 0x99,

    /* U+004E "N" */
    0xc7, 0x1a, 0x69, 0x96, 0x58, 0xe3,

    /* U+004F "O" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x51, 0x1c,

    /* U+0050 "P" */
    0xfa, 0x18, 0x61, 0xfa, 0x8, 0x20,

    /* U+0051 "Q" */
    0x38, 0x8a, 0xc, 0x18, 0x31, 0x51, 0x1d, 0x0,

    /* U+0052 "R" */
    0xfa, 0x18, 0x61, 0xfa, 0x18, 0x61,

    /* U+0053 "S" */
    0x7a, 0x38, 0x18, 0x1a, 0x18, 0x5e,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0xde,

    /* U+0056 "V" */
    0x42, 0x85, 0x11, 0x22, 0x45, 0x6, 0x8,

    /* U+0057 "W" */
    0x84, 0x51, 0x14, 0xa5, 0x29, 0x52, 0x8c, 0x63,
    0x18, 0xc4,

    /* U+0058 "X" */
    0x44, 0x88, 0xa0, 0x81, 0x5, 0x11, 0x22,

    /* U+0059 "Y" */
    0x82, 0x88, 0xa1, 0x41, 0x2, 0x4, 0x8,

    /* U+005A "Z" */
    0xfc, 0x10, 0x84, 0x21, 0x8, 0x3f,

    /* U+005B "[" */
    0xea, 0xaa, 0xac,

    /* U+005C "\\" */
    0x91, 0x24, 0x49,

    /* U+005D "]" */
    0xd5, 0x55, 0x5c,

    /* U+005E "^" */
    0x22, 0xa2,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x60,

    /* U+0061 "a" */
    0x72, 0x21, 0x9a, 0x9b, 0xb0,

    /* U+0062 "b" */
    0x84, 0x2d, 0xb8, 0xc6, 0x3e,

    /* U+0063 "c" */
    0x76, 0x61, 0xc, 0xb8,

    /* U+0064 "d" */
    0x8, 0x5b, 0xb8, 0xc7, 0x2f,

    /* U+0065 "e" */
    0x72, 0x2f, 0xa0, 0xc9, 0xc0,

    /* U+0066 "f" */
    0x74, 0xe4, 0x44, 0x44,

    /* U+0067 "g" */
    0x7e, 0x63, 0x1c, 0xbe, 0x2e,

    /* U+0068 "h" */
    0x84, 0x2d, 0x98, 0xc6, 0x31,

    /* U+0069 "i" */
    0xbf,

    /* U+006A "j" */
    0x45, 0x55, 0x70,

    /* U+006B "k" */
    0x84, 0x25, 0x4e, 0x52, 0x51,

    /* U+006C "l" */
    0xff,

    /* U+006D "m" */
    0xb7, 0x64, 0x62, 0x31, 0x18, 0x8c, 0x44,

    /* U+006E "n" */
    0xbe, 0x63, 0x18, 0xc4,

    /* U+006F "o" */
    0x76, 0xe3, 0x1d, 0xb8,

    /* U+0070 "p" */
    0xb6, 0xe3, 0x19, 0xfa, 0x10,

    /* U+0071 "q" */
    0x6e, 0xe3, 0x1c, 0xbc, 0x21,

    /* U+0072 "r" */
    0xf2, 0x49, 0x0,

    /* U+0073 "s" */
    0x74, 0x90, 0x69, 0x38,

    /* U+0074 "t" */
    0x4b, 0xa4, 0x93,

    /* U+0075 "u" */
    0x8c, 0x63, 0x19, 0xf4,

    /* U+0076 "v" */
    0x8a, 0x52, 0xa3, 0x10,

    /* U+0077 "w" */
    0x99, 0x99, 0x5a, 0x66, 0x66, 0x26,

    /* U+0078 "x" */
    0x4a, 0x8c, 0x65, 0x24,

    /* U+0079 "y" */
    0x8a, 0x54, 0xa3, 0x10, 0x88,

    /* U+007A "z" */
    0xf8, 0x88, 0x8c, 0x7c,

    /* U+007B "{" */
    0x69, 0x25, 0x12, 0x49, 0x80,

    /* U+007C "|" */
    0xff, 0xe0,

    /* U+007D "}" */
    0xc9, 0x24, 0x52, 0x4b, 0x0,

    /* U+007E "~" */
    0x72, 0xa6, 0x30,

    /* U+0900 "ऀ" */
    0x74, 0x48,

    /* U+0901 "ँ" */
    0x20, 0x5c,

    /* U+0902 "ं" */
    0x80,

    /* U+0903 "ः" */
    0xc0, 0xc0,

    /* U+0904 "ऄ" */
    0x0, 0x8, 0x3, 0xc0, 0x23, 0x38, 0x48, 0x24,
    0x3e, 0x85, 0x22, 0x8e, 0x40, 0x20,

    /* U+0905 "अ" */
    0x37, 0xa8, 0x84, 0x51, 0xe8, 0x92, 0x48, 0xe4,
    0x2,

    /* U+0906 "आ" */
    0x3b, 0xf0, 0x92, 0x19, 0x20, 0xf2, 0x45, 0x24,
    0x52, 0x39, 0x20, 0x12,

    /* U+0907 "इ" */
    0xfc, 0x2f, 0xa6, 0xeb, 0x2b, 0x3c, 0x0,

    /* U+0908 "ई" */
    0x18, 0x81, 0x3f, 0xb, 0xe9, 0xba, 0xca, 0xcf,
    0x4,

    /* U+0909 "उ" */
    0xff, 0x4, 0x4, 0xc, 0x42, 0x42, 0x26, 0x1c,

    /* U+090A "ऊ" */
    0xff, 0xe0, 0x80, 0x10, 0x7, 0xc4, 0x24, 0x84,
    0x89, 0x80, 0xe0,

    /* U+090B "ऋ" */
    0xff, 0x84, 0x1a, 0xc3, 0xe1, 0x93, 0x50, 0x30,
    0x16,

    /* U+090C "ऌ" */
    0xff, 0x4, 0x6e, 0x9a, 0x82, 0xc2, 0x64, 0x8,
    0xa, 0x6,

    /* U+090D "ऍ" */
    0x10, 0x38, 0x7, 0xf4, 0xc9, 0x92, 0x24, 0x30,
    0x30, 0x10, 0x20,

    /* U+090E "ऎ" */
    0x82, 0x7, 0x4, 0xfe, 0x69, 0xa6, 0x93, 0x3,
    0x2, 0x8, 0x20,

    /* U+090F "ए" */
    0xfe, 0x99, 0x32, 0x64, 0x8c, 0x6, 0x2, 0x4,
    0x8,

    /* U+0910 "ऐ" */
    0x30, 0x10, 0x20, 0x4f, 0xe9, 0x93, 0x26, 0x48,
    0x60, 0x60, 0x20, 0x40,

    /* U+0911 "ऑ" */
    0x1, 0x20, 0xc, 0x0, 0x3, 0xbf, 0x9, 0x21,
    0x92, 0x8f, 0x24, 0x52, 0x65, 0x23, 0x92, 0x1,
    0x20,

    /* U+0912 "ऒ" */
    0x2, 0x0, 0x10, 0x0, 0x78, 0x0, 0x43, 0xbf,
    0x84, 0x90, 0x64, 0x81, 0xe4, 0x45, 0x22, 0x29,
    0xe, 0x48, 0x2, 0x40,

    /* U+0913 "ओ" */
    0x1, 0x80, 0x4, 0x0, 0x20, 0x2, 0x3b, 0xf0,
    0x92, 0x11, 0x28, 0xf2, 0x45, 0x26, 0x52, 0x39,
    0x20, 0x12,

    /* U+0914 "औ" */
    0x1, 0xc0, 0x4, 0x1, 0xa0, 0x6, 0x3b, 0xf0,
    0x92, 0x19, 0x20, 0xf2, 0x45, 0x24, 0x52, 0x39,
    0x20, 0x12,

    /* U+0915 "क" */
    0xff, 0x88, 0x1f, 0x93, 0x29, 0x13, 0x90, 0x40,
    0x20,

    /* U+0916 "ख" */
    0xff, 0x90, 0x8b, 0xd6, 0x2e, 0xf2, 0x9, 0x8c,
    0x7a,

    /* U+0917 "ग" */
    0xfe, 0x48, 0x91, 0x26, 0x4c, 0x81, 0x2,

    /* U+0918 "घ" */
    0xff, 0xb, 0x94, 0x24, 0xce, 0x81, 0x2,

    /* U+0919 "ङ" */
    0xff, 0x2, 0x3e, 0x23, 0x9e, 0x42, 0x22, 0x1c,

    /* U+091A "च" */
    0xfe, 0xb, 0xd2, 0x24, 0xce, 0x81, 0x2,

    /* U+091B "छ" */
    0xff, 0xa2, 0x12, 0x8f, 0x44, 0x62, 0x11, 0x98,
    0x70,

    /* U+091C "ज" */
    0xff, 0x2, 0x1e, 0x9a, 0x4a, 0x4a, 0x3a, 0x2,

    /* U+091D "झ" */
    0xff, 0x82, 0x9f, 0x49, 0x23, 0x73, 0x29, 0x64,
    0xf2, 0x0, 0x0,

    /* U+091E "ञ" */
    0xff, 0x2, 0x72, 0xa, 0xe, 0x72, 0x2, 0x2,

    /* U+091F "ट" */
    0xfe, 0x21, 0xc6, 0x8, 0x10, 0xb2, 0x38,

    /* U+0920 "ठ" */
    0xfe, 0x21, 0xc6, 0xc8, 0xd0, 0xb3, 0x3c,

    /* U+0921 "ड" */
    0xff, 0x2, 0x3e, 0x20, 0x9e, 0x42, 0x22, 0x1c,

    /* U+0922 "ढ" */
    0xfe, 0x11, 0xe6, 0x9, 0xd4, 0xb7, 0x1c,

    /* U+0923 "ण" */
    0xff, 0xc4, 0xa2, 0x51, 0x25, 0x13, 0x88, 0x4,
    0x2,

    /* U+0924 "त" */
    0xfc, 0x2f, 0xa2, 0x8a, 0x24, 0x8a,

    /* U+0925 "थ" */
    0x6f, 0x49, 0x97, 0x24, 0xcf, 0x81, 0x2,

    /* U+0926 "द" */
    0xfc, 0x47, 0x20, 0x9a, 0xa7, 0x6,

    /* U+0927 "ध" */
    0xef, 0xca, 0x13, 0x28, 0x51, 0x9d, 0x2,

    /* U+0928 "न" */
    0xfe, 0x8, 0x13, 0xe6, 0x40, 0x81, 0x2,

    /* U+0929 "ऩ" */
    0xfe, 0x8, 0x13, 0xe6, 0x40, 0x81, 0x22,

    /* U+092A "प" */
    0xfd, 0x24, 0x92, 0x48, 0xe0, 0x82,

    /* U+092B "फ" */
    0xff, 0xd2, 0x4, 0xf1, 0x34, 0x49, 0xe, 0x40,
    0x80, 0x20,

    /* U+092C "ब" */
    0xfc, 0x26, 0xb2, 0xa9, 0xe0, 0x82,

    /* U+092D "भ" */
    0xcf, 0x4b, 0x91, 0x27, 0xcc, 0x81, 0x2,

    /* U+092E "म" */
    0xfe, 0x48, 0x91, 0x27, 0xcc, 0x81, 0x2,

    /* U+092F "य" */
    0xfe, 0x88, 0x96, 0x28, 0xce, 0x81, 0x2,

    /* U+0930 "र" */
    0xf9, 0x8, 0x4e, 0x20, 0x82,

    /* U+0931 "ऱ" */
    0xf9, 0x8, 0x4e, 0x20, 0x9a,

    /* U+0932 "ल" */
    0xff, 0x2, 0x2, 0x76, 0x5a, 0x92, 0x42, 0x22,

    /* U+0933 "ळ" */
    0xff, 0x4, 0x64, 0x9a, 0x92, 0x92, 0x6c,

    /* U+0934 "ऴ" */
    0xff, 0x4, 0x64, 0x9a, 0x92, 0x92, 0x6c, 0x0,
    0x10,

    /* U+0935 "व" */
    0xfc, 0x26, 0xa2, 0x89, 0xe0, 0x82,

    /* U+0936 "श" */
    0x67, 0x92, 0x72, 0xd2, 0xb2, 0xf2, 0x12, 0xa,

    /* U+0937 "ष" */
    0xfd, 0x27, 0x92, 0x48, 0xe0, 0x82,

    /* U+0938 "स" */
    0xff, 0x22, 0x22, 0x22, 0x7e, 0x42, 0x22, 0x1a,

    /* U+0939 "ह" */
    0xfc, 0x4f, 0x20, 0x72, 0x49, 0x20, 0x40,

    /* U+093A "ऺ" */
    0xe0,

    /* U+093B "ऻ" */
    0x49, 0x74, 0x92, 0x49, 0x0,

    /* U+093C "़" */
    0x80,

    /* U+093D "ऽ" */
    0x7c, 0x10, 0x41, 0x4, 0x2e,

    /* U+093E "ा" */
    0xe9, 0x24, 0x92,

    /* U+093F "ि" */
    0x71, 0x1a, 0xc, 0xc, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x4, 0x0,

    /* U+0940 "ी" */
    0x71, 0x12, 0x20, 0x20, 0xe0, 0x81, 0x2, 0x4,
    0x8, 0x10, 0x20,

    /* U+0941 "ु" */
    0x18, 0x14, 0x4e,

    /* U+0942 "ू" */
    0x72, 0x28, 0x99,

    /* U+0943 "ृ" */
    0xd2, 0x30,

    /* U+0944 "ॄ" */
    0xd1, 0x30,

    /* U+0945 "ॅ" */
    0x8b, 0x80,

    /* U+0946 "ॆ" */
    0x84, 0x1c, 0x20, 0x80,

    /* U+0947 "े" */
    0xc2, 0x21,

    /* U+0948 "ै" */
    0xc2, 0xe3,

    /* U+0949 "ॉ" */
    0x1c, 0x74, 0x92, 0x49, 0x0,

    /* U+094A "ॊ" */
    0x3, 0x3, 0x82, 0x1c, 0x20, 0x82, 0x8, 0x20,
    0x82,

    /* U+094B "ो" */
    0xc1, 0x4, 0x23, 0x88, 0x42, 0x10, 0x84, 0x20,

    /* U+094C "ौ" */
    0xe1, 0x34, 0x63, 0x88, 0x42, 0x10, 0x84, 0x20,

    /* U+094D "्" */
    0x19, 0x10,

    /* U+094E "ॎ" */
    0xea, 0xaa,

    /* U+094F "ॏ" */
    0x12, 0x46, 0x86, 0x1c, 0x20, 0x82, 0x8, 0x20,
    0x82,

    /* U+0950 "ॐ" */
    0x2, 0x2, 0x0, 0x70, 0xe0, 0x49, 0x82, 0x90,
    0xe7, 0x11, 0x45, 0x8e, 0x0,

    /* U+0951 "॑" */
    0xe0,

    /* U+0952 "॒" */
    0xfc,

    /* U+0953 "॓" */
    0x8,

    /* U+0954 "॔" */
    0x20,

    /* U+0955 "ॕ" */
    0xfc,

    /* U+0956 "ॖ" */
    0x8f, 0x80,

    /* U+0957 "ॗ" */
    0xfc, 0x5c,

    /* U+0958 "क़" */
    0xff, 0x88, 0x1f, 0x93, 0x29, 0x13, 0x90, 0x40,
    0xe0,

    /* U+0959 "ख़" */
    0xff, 0x90, 0x8b, 0xd6, 0x2e, 0xf2, 0x9, 0x8d,
    0xfa,

    /* U+095A "ग़" */
    0xfe, 0x48, 0x91, 0x26, 0x4c, 0x81, 0x22,

    /* U+095B "ज़" */
    0xff, 0x2, 0x1e, 0x9a, 0x4a, 0x4a, 0x3a, 0x42,

    /* U+095C "ड़" */
    0xff, 0x2, 0x3e, 0x20, 0x9e, 0x42, 0x22, 0x1c,
    0x18,

    /* U+095D "ढ़" */
    0xfe, 0x11, 0xe6, 0x9, 0xd4, 0xb7, 0x1c, 0x0,
    0x20,

    /* U+095E "फ़" */
    0xff, 0xd2, 0x4, 0xf1, 0x34, 0x49, 0xe, 0x40,
    0x80, 0xe0,

    /* U+095F "य़" */
    0xfe, 0x88, 0x96, 0x28, 0xce, 0x81, 0x12,

    /* U+0960 "ॠ" */
    0xff, 0x84, 0x1a, 0xc3, 0xe1, 0x93, 0x58, 0x2c,
    0x14, 0x3, 0x0,

    /* U+0961 "ॡ" */
    0xff, 0x4, 0x6e, 0x9a, 0x82, 0xc4, 0x68, 0xc,
    0x8, 0x6,

    /* U+0962 "ॢ" */
    0xdd, 0x62, 0xa2, 0xc,

    /* U+0963 "ॣ" */
    0xdd, 0x62, 0xe1, 0xc,

    /* U+0964 "।" */
    0xfe,

    /* U+0965 "॥" */
    0xb6, 0xdb, 0x68,

    /* U+0966 "०" */
    0x69, 0x96,

    /* U+0967 "१" */
    0xf6, 0xa5, 0x12, 0x0,

    /* U+0968 "२" */
    0x72, 0x60, 0x9a, 0xb1, 0xc0, 0x82, 0x4,

    /* U+0969 "३" */
    0xe1, 0x8, 0xc1, 0x6b, 0x82, 0x8,

    /* U+096A "४" */
    0x85, 0x23, 0xc, 0x49, 0x23, 0x0,

    /* U+096B "५" */
    0x82, 0x9, 0xf5, 0x78, 0x40, 0x81, 0x4,

    /* U+096C "६" */
    0x64, 0x20, 0xcb, 0x59, 0xc2, 0x8,

    /* U+096D "७" */
    0x8e, 0x49, 0x49, 0x47, 0x21, 0x33, 0x1e,

    /* U+096E "८" */
    0x0, 0x88, 0x88, 0x42, 0xe,

    /* U+096F "९" */
    0x6b, 0xbe, 0x42, 0x11, 0x0,

    /* U+0970 "॰" */
    0x55, 0x80,

    /* U+0971 "ॱ" */
    0x80,

    /* U+0972 "ॲ" */
    0x0, 0x1, 0xc0, 0xe, 0xf1, 0x11, 0x8a, 0x3d,
    0x12, 0x49, 0x1c, 0x80, 0x40,

    /* U+0973 "ॳ" */
    0x1, 0x0, 0x80, 0x46, 0xf5, 0x10, 0x8a, 0x3d,
    0x12, 0x49, 0x1c, 0x80, 0x40,

    /* U+0974 "ॴ" */
    0x0, 0x20, 0x2, 0x0, 0x23, 0xbf, 0x9, 0x21,
    0x92, 0xf, 0x24, 0x52, 0x45, 0x23, 0x92, 0x1,
    0x20,

    /* U+0975 "ॵ" */
    0x0, 0x40, 0x24, 0x1, 0xa0, 0x6, 0x3b, 0xf0,
    0x92, 0x19, 0x20, 0xf2, 0x45, 0x24, 0x52, 0x39,
    0x20, 0x12,

    /* U+0976 "ॶ" */
    0x37, 0xa8, 0x84, 0x51, 0xe8, 0x92, 0x48, 0xe4,
    0x2, 0x0, 0x11, 0x7, 0x0,

    /* U+0977 "ॷ" */
    0x37, 0xa8, 0x84, 0x51, 0xe8, 0x92, 0x48, 0xe4,
    0x2, 0x20, 0x1f, 0x8, 0x83, 0x80,

    /* U+0978 "ॸ" */
    0xfe, 0x40, 0x83, 0xc6, 0x4c, 0x81, 0x4,

    /* U+0979 "ॹ" */
    0xff, 0x2, 0x2, 0x1e, 0x4a, 0x6a, 0x3a, 0x2,
    0x28, 0x10,

    /* U+097A "ॺ" */
    0xfe, 0x88, 0x96, 0xe8, 0xce, 0x81, 0x2,

    /* U+097B "ॻ" */
    0xfe, 0x48, 0x91, 0x26, 0x4c, 0x81, 0x2, 0xfe,

    /* U+097C "ॼ" */
    0xff, 0x2, 0x1e, 0x9a, 0x4a, 0x4a, 0x3a, 0x2,
    0x0, 0xff,

    /* U+097D "ॽ" */
    0x78, 0x30, 0x41, 0x18, 0x82, 0x8,

    /* U+097E "ॾ" */
    0xff, 0x2, 0x3e, 0x20, 0x9e, 0x42, 0x22, 0x1c,
    0x0, 0xff,

    /* U+097F "ॿ" */
    0xfc, 0x26, 0xb2, 0xa9, 0xe0, 0x82, 0x3, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 35, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 57, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 139, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 107, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 18, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 31, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 35, .adv_w = 60, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 60, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 41, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 44, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 49, .adv_w = 38, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 61, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 51, .adv_w = 36, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 56, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 106, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 36, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 38, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 113, .adv_w = 108, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 117, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 120, .adv_w = 108, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 124, .adv_w = 95, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 149, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 137, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 136, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 117, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 145, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 136, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 55, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 157, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 137, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 140, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 241, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 117, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 135, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 46, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 306, .adv_w = 55, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 46, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 312, .adv_w = 83, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 314, .adv_w = 110, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 315, .adv_w = 38, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 316, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 101, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 101, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 99, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 54, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 103, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 349, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 42, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 44, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 358, .adv_w = 93, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 42, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 156, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 104, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 101, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 384, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 389, .adv_w = 62, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 86, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 58, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 104, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 90, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 132, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 88, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 422, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 57, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 431, .adv_w = 41, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 433, .adv_w = 54, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 438, .adv_w = 117, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 441, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 443, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -6, .ofs_y = 9},
    {.bitmap_index = 445, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -2, .ofs_y = 10},
    {.bitmap_index = 446, .adv_w = 61, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 448, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 145, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 190, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 490, .adv_w = 104, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 499, .adv_w = 122, .box_w = 8, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 167, .box_w = 11, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 151, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 537, .adv_w = 101, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 548, .adv_w = 101, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 559, .adv_w = 101, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 568, .adv_w = 101, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 580, .adv_w = 190, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 190, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 190, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 190, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 146, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 150, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 124, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 137, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 728, .adv_w = 131, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 750, .adv_w = 124, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 139, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 146, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 843, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 850, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 86, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 86, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 875, .adv_w = 138, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 882, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 891, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 911, .adv_w = 124, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 91, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 926, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 8},
    {.bitmap_index = 927, .adv_w = 56, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 932, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -5, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 938, .adv_w = 49, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 49, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 952, .adv_w = 48, .box_w = 7, .box_h = 12, .ofs_x = -4, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -6, .ofs_y = -3},
    {.bitmap_index = 966, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -4, .ofs_y = -3},
    {.bitmap_index = 969, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = -4, .ofs_y = -3},
    {.bitmap_index = 971, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 973, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 975, .adv_w = 0, .box_w = 5, .box_h = 5, .ofs_x = -6, .ofs_y = 7},
    {.bitmap_index = 979, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -5, .ofs_y = 8},
    {.bitmap_index = 981, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -5, .ofs_y = 8},
    {.bitmap_index = 983, .adv_w = 56, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 988, .adv_w = 56, .box_w = 6, .box_h = 12, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 997, .adv_w = 56, .box_w = 5, .box_h = 12, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 56, .box_w = 5, .box_h = 12, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 1015, .adv_w = 62, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1017, .adv_w = 56, .box_w = 6, .box_h = 12, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 185, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1039, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 8},
    {.bitmap_index = 1040, .adv_w = 0, .box_w = 6, .box_h = 1, .ofs_x = -3, .ofs_y = -2},
    {.bitmap_index = 1041, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = -5, .ofs_y = 10},
    {.bitmap_index = 1042, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -4, .ofs_y = 10},
    {.bitmap_index = 1043, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = -3, .ofs_y = 8},
    {.bitmap_index = 1044, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -7, .ofs_y = -3},
    {.bitmap_index = 1046, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -7, .ofs_y = -4},
    {.bitmap_index = 1048, .adv_w = 146, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 150, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1066, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1081, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1090, .adv_w = 109, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1099, .adv_w = 146, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1116, .adv_w = 151, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1127, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1137, .adv_w = 0, .box_w = 5, .box_h = 6, .ofs_x = -6, .ofs_y = -5},
    {.bitmap_index = 1141, .adv_w = 0, .box_w = 5, .box_h = 6, .ofs_x = -6, .ofs_y = -5},
    {.bitmap_index = 1145, .adv_w = 63, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1146, .adv_w = 96, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1149, .adv_w = 82, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1151, .adv_w = 87, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1155, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 93, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1168, .adv_w = 120, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1174, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1181, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1187, .adv_w = 137, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1194, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1199, .adv_w = 102, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 53, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1206, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1207, .adv_w = 145, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1220, .adv_w = 145, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1233, .adv_w = 190, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1250, .adv_w = 190, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1268, .adv_w = 145, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1281, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1295, .adv_w = 107, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1302, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1312, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1319, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1327, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1337, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1343, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1353, .adv_w = 107, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2}
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
const lv_font_t hi_12 = {
#else
lv_font_t hi_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if HI_12*/

