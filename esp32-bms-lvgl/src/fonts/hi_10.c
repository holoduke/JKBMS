/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --font /tmp/dv.ttf --size 10 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x900-0x97F -o src/fonts/hi_10.c
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
    0xfa,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x51, 0x4f, 0xd4, 0xfa, 0x4a, 0x0,

    /* U+0024 "$" */
    0x23, 0xad, 0x46, 0x1a, 0xce, 0x20,

    /* U+0025 "%" */
    0x45, 0x52, 0xc2, 0x82, 0xe6, 0x53, 0x80,

    /* U+0026 "&" */
    0x71, 0x45, 0x18, 0x9a, 0x27, 0x80,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x6a, 0xaa, 0x40,

    /* U+0029 ")" */
    0xa5, 0x56, 0x80,

    /* U+002A "*" */
    0x4f, 0x60,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x29, 0x25, 0x20,

    /* U+0030 "0" */
    0x76, 0xe3, 0x18, 0xed, 0xc0,

    /* U+0031 "1" */
    0x2e, 0x92, 0x48,

    /* U+0032 "2" */
    0x72, 0x42, 0x22, 0x63, 0xe0,

    /* U+0033 "3" */
    0x74, 0x44, 0x41, 0xc5, 0xc0,

    /* U+0034 "4" */
    0x11, 0x95, 0x29, 0x7c, 0x40,

    /* U+0035 "5" */
    0x74, 0x3d, 0x10, 0xc5, 0xc0,

    /* U+0036 "6" */
    0x32, 0x6d, 0x98, 0xa5, 0xc0,

    /* U+0037 "7" */
    0xf8, 0x44, 0x42, 0x11, 0x0,

    /* U+0038 "8" */
    0x76, 0x72, 0xe8, 0xc5, 0xc0,

    /* U+0039 "9" */
    0x74, 0xa5, 0x37, 0x49, 0x80,

    /* U+003A ":" */
    0x88,

    /* U+003B ";" */
    0x8c,

    /* U+003C "<" */
    0xb, 0xa0, 0xe0, 0x80,

    /* U+003D "=" */
    0xf8, 0x3e,

    /* U+003E ">" */
    0x83, 0x6, 0xc8, 0x0,

    /* U+003F "?" */
    0x69, 0x12, 0x40, 0x40,

    /* U+0040 "@" */
    0x3c, 0xae, 0xad, 0x5a, 0xaf, 0x8f, 0x0,

    /* U+0041 "A" */
    0x21, 0x45, 0x14, 0xfa, 0x28, 0x80,

    /* U+0042 "B" */
    0xf4, 0xa5, 0xc9, 0xc7, 0xc0,

    /* U+0043 "C" */
    0x7b, 0x18, 0x20, 0x87, 0x17, 0x80,

    /* U+0044 "D" */
    0xfa, 0x28, 0x61, 0x86, 0x2f, 0x80,

    /* U+0045 "E" */
    0xfc, 0x21, 0xf8, 0x43, 0xe0,

    /* U+0046 "F" */
    0xfc, 0x21, 0xe8, 0x42, 0x0,

    /* U+0047 "G" */
    0x79, 0x18, 0x27, 0x87, 0x17, 0x80,

    /* U+0048 "H" */
    0x8c, 0x63, 0xf8, 0xc6, 0x20,

    /* U+0049 "I" */
    0xfe,

    /* U+004A "J" */
    0x11, 0x11, 0x99, 0x60,

    /* U+004B "K" */
    0x8a, 0x4a, 0x38, 0x92, 0x28, 0x80,

    /* U+004C "L" */
    0x88, 0x88, 0x88, 0xf0,

    /* U+004D "M" */
    0x87, 0x3c, 0xf5, 0xb6, 0xda, 0x40,

    /* U+004E "N" */
    0x8e, 0x73, 0x5a, 0xce, 0x20,

    /* U+004F "O" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0050 "P" */
    0xf4, 0x63, 0xe8, 0x42, 0x0,

    /* U+0051 "Q" */
    0x7b, 0x38, 0x61, 0x87, 0x27, 0x40,

    /* U+0052 "R" */
    0xf4, 0x63, 0xe8, 0xc6, 0x20,

    /* U+0053 "S" */
    0x74, 0x60, 0xc1, 0xc5, 0xc0,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x80,

    /* U+0055 "U" */
    0x8c, 0x63, 0x18, 0xc5, 0xc0,

    /* U+0056 "V" */
    0x85, 0x24, 0x92, 0x30, 0xc1, 0x0,

    /* U+0057 "W" */
    0x88, 0xcc, 0x95, 0x4a, 0xa5, 0x53, 0x30, 0x88,

    /* U+0058 "X" */
    0x49, 0x23, 0x8, 0x31, 0x24, 0x80,

    /* U+0059 "Y" */
    0x8c, 0x54, 0x42, 0x10, 0x80,

    /* U+005A "Z" */
    0xf8, 0x44, 0x44, 0x43, 0xe0,

    /* U+005B "[" */
    0xea, 0xaa, 0xc0,

    /* U+005C "\\" */
    0x92, 0x24, 0x88,

    /* U+005D "]" */
    0xd5, 0x55, 0xc0,

    /* U+005E "^" */
    0x26, 0x90,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0xc0,

    /* U+0061 "a" */
    0x79, 0x3d, 0xf0,

    /* U+0062 "b" */
    0x88, 0xe9, 0x99, 0xe0,

    /* U+0063 "c" */
    0x79, 0x89, 0x70,

    /* U+0064 "d" */
    0x11, 0x79, 0x99, 0x70,

    /* U+0065 "e" */
    0x74, 0xbd, 0x7, 0x0,

    /* U+0066 "f" */
    0x6b, 0xa4, 0x90,

    /* U+0067 "g" */
    0x79, 0x99, 0x79, 0x60,

    /* U+0068 "h" */
    0x88, 0xf9, 0x99, 0x90,

    /* U+0069 "i" */
    0xbe,

    /* U+006A "j" */
    0x45, 0x55, 0xc0,

    /* U+006B "k" */
    0x88, 0x9a, 0xea, 0x90,

    /* U+006C "l" */
    0xfe,

    /* U+006D "m" */
    0xef, 0x26, 0x4c, 0x99, 0x20,

    /* U+006E "n" */
    0xbd, 0x99, 0x90,

    /* U+006F "o" */
    0x74, 0x63, 0x17, 0x0,

    /* U+0070 "p" */
    0xe9, 0x99, 0xe8, 0x80,

    /* U+0071 "q" */
    0x79, 0x99, 0x71, 0x10,

    /* U+0072 "r" */
    0xf2, 0x48,

    /* U+0073 "s" */
    0xe8, 0x4a, 0xe0,

    /* U+0074 "t" */
    0x4b, 0xa4, 0x98,

    /* U+0075 "u" */
    0x99, 0x99, 0xf0,

    /* U+0076 "v" */
    0x94, 0x94, 0xc2, 0x0,

    /* U+0077 "w" */
    0x93, 0x69, 0xd3, 0x64, 0x80,

    /* U+0078 "x" */
    0x96, 0x26, 0x90,

    /* U+0079 "y" */
    0x99, 0x52, 0x22, 0x40,

    /* U+007A "z" */
    0xf3, 0x2c, 0xf0,

    /* U+007B "{" */
    0x69, 0x28, 0x92, 0x60,

    /* U+007C "|" */
    0xff, 0x80,

    /* U+007D "}" */
    0xc9, 0x22, 0x92, 0xc0,

    /* U+007E "~" */
    0x66, 0x60,

    /* U+0900 "ऀ" */
    0x72,

    /* U+0901 "ँ" */
    0x29, 0x60,

    /* U+0902 "ं" */
    0x80,

    /* U+0903 "ः" */
    0x90,

    /* U+0904 "ऄ" */
    0x0, 0x18, 0x6, 0x77, 0x12, 0x3e, 0x8a, 0x4a,
    0x32,

    /* U+0905 "अ" */
    0x77, 0x12, 0x3e, 0x8a, 0x4a, 0x32,

    /* U+0906 "आ" */
    0x6f, 0xc9, 0x23, 0x4a, 0x72, 0x94, 0x9d, 0x20,

    /* U+0907 "इ" */
    0xff, 0xcb, 0x14, 0xd3, 0x80,

    /* U+0908 "ई" */
    0x31, 0x9, 0xff, 0x5b, 0x5c, 0xe0,

    /* U+0909 "उ" */
    0xfc, 0x43, 0x22, 0x48, 0xc0,

    /* U+090A "ऊ" */
    0xff, 0x88, 0xd, 0x91, 0x24, 0xa1, 0x80,

    /* U+090B "ऋ" */
    0xff, 0xb5, 0x17, 0x83, 0x22, 0xe0, 0x58,

    /* U+090C "ऌ" */
    0xff, 0x9a, 0xd4, 0x25, 0x82, 0x3, 0x0,

    /* U+090D "ऍ" */
    0x0, 0x6f, 0xd2, 0x49, 0x2, 0x6, 0x8,

    /* U+090E "ऎ" */
    0x40, 0xcf, 0xd2, 0x49, 0x2, 0x6, 0x8,

    /* U+090F "ए" */
    0xfd, 0x24, 0x90, 0x20, 0x60, 0x80,

    /* U+0910 "ऐ" */
    0x20, 0x41, 0x3f, 0x49, 0x24, 0xc, 0x8, 0x20,

    /* U+0911 "ऑ" */
    0x0, 0x80, 0xc6, 0xfc, 0x92, 0x34, 0xa7, 0x29,
    0x49, 0xd2,

    /* U+0912 "ऒ" */
    0x0, 0x1, 0x80, 0x19, 0xbf, 0x24, 0x8d, 0x29,
    0xca, 0x52, 0x74, 0x80,

    /* U+0913 "ओ" */
    0x7, 0x0, 0x40, 0x9, 0xbf, 0x24, 0x8d, 0x29,
    0xc9, 0xd2, 0x4, 0x80,

    /* U+0914 "औ" */
    0x3, 0x1, 0xa0, 0x19, 0xbf, 0x24, 0x8d, 0x29,
    0xc9, 0xd2, 0x4, 0x80,

    /* U+0915 "क" */
    0xfe, 0xfa, 0x54, 0xa7, 0x2, 0x0,

    /* U+0916 "ख" */
    0xff, 0x2e, 0xb2, 0x6e, 0x46, 0x3a,

    /* U+0917 "ग" */
    0xfd, 0x24, 0xb2, 0x48, 0x20,

    /* U+0918 "घ" */
    0xfe, 0x2c, 0xa6, 0x68, 0x20,

    /* U+0919 "ङ" */
    0xfe, 0xf1, 0x15, 0xc4, 0x87, 0x0,

    /* U+091A "च" */
    0xff, 0xa4, 0xa6, 0x68, 0x20,

    /* U+091B "छ" */
    0xff, 0x4c, 0x74, 0x4c, 0x44, 0x38,

    /* U+091C "ज" */
    0xfe, 0xa, 0x72, 0xa3, 0x40, 0x80,

    /* U+091D "झ" */
    0xff, 0x7a, 0x92, 0x6e, 0x72, 0x72,

    /* U+091E "ञ" */
    0xfe, 0xc8, 0x54, 0xe7, 0x40, 0x80,

    /* U+091F "ट" */
    0xfd, 0xc8, 0x20, 0x89, 0xc0,

    /* U+0920 "ठ" */
    0xfd, 0xc9, 0x22, 0x89, 0xc0,

    /* U+0921 "ड" */
    0xfe, 0xf1, 0x5, 0xc4, 0x87, 0x0,

    /* U+0922 "ढ" */
    0xfd, 0xc8, 0x26, 0xe9, 0xc0,

    /* U+0923 "ण" */
    0xff, 0x92, 0x92, 0x92, 0x62, 0x2,

    /* U+0924 "त" */
    0xfc, 0x27, 0xa2, 0x48, 0xa0,

    /* U+0925 "थ" */
    0x7d, 0xae, 0xa2, 0x78, 0x20,

    /* U+0926 "द" */
    0xfb, 0xa1, 0x6f, 0x18,

    /* U+0927 "ध" */
    0x6e, 0xc9, 0x92, 0x27, 0xc0, 0x80,

    /* U+0928 "न" */
    0xfc, 0x2f, 0x92, 0x8, 0x20,

    /* U+0929 "ऩ" */
    0xfc, 0x2f, 0x92, 0x9, 0x20,

    /* U+092A "प" */
    0xfa, 0xaa, 0x62,

    /* U+092B "फ" */
    0xff, 0x3a, 0x54, 0xa7, 0x2, 0x0,

    /* U+092C "ब" */
    0xfd, 0xaa, 0xba, 0x78, 0x20,

    /* U+092D "भ" */
    0xdf, 0x24, 0xbe, 0x48, 0x20,

    /* U+092E "म" */
    0xfd, 0x24, 0xbe, 0x48, 0x20,

    /* U+092F "य" */
    0xfe, 0x48, 0x92, 0x63, 0x40, 0x80,

    /* U+0930 "र" */
    0xf9, 0x8, 0x82, 0x8,

    /* U+0931 "ऱ" */
    0xf9, 0x8, 0xc4, 0x58,

    /* U+0932 "ल" */
    0xfe, 0x9, 0x94, 0xe8, 0x4c, 0x80,

    /* U+0933 "ळ" */
    0xfe, 0x13, 0xf5, 0x2f, 0xc0,

    /* U+0934 "ऴ" */
    0xfe, 0x13, 0xf5, 0x2f, 0xc0, 0x4, 0x0,

    /* U+0935 "व" */
    0xfd, 0xa8, 0x92, 0x78, 0x20,

    /* U+0936 "श" */
    0x6e, 0xc9, 0x95, 0x25, 0x42, 0x80,

    /* U+0937 "ष" */
    0xfe, 0xad, 0x27, 0x8,

    /* U+0938 "स" */
    0xfe, 0x48, 0x97, 0xe4, 0x46, 0x80,

    /* U+0939 "ह" */
    0xff, 0xa0, 0xe9, 0x41, 0x0,

    /* U+093A "ऺ" */
    0xe0,

    /* U+093B "ऻ" */
    0x4b, 0xa4, 0x92,

    /* U+093C "़" */
    0x80,

    /* U+093D "ऽ" */
    0xe8, 0x86, 0x2e,

    /* U+093E "ा" */
    0xe9, 0x24, 0x80,

    /* U+093F "ि" */
    0x70, 0x89, 0xf, 0x4, 0x8, 0x10, 0x20, 0x40,

    /* U+0940 "ी" */
    0xe2, 0x40, 0x87, 0x8, 0x20, 0x82, 0x8,

    /* U+0941 "ु" */
    0x39, 0xf0,

    /* U+0942 "ू" */
    0xe4, 0xba,

    /* U+0943 "ृ" */
    0xec,

    /* U+0944 "ॄ" */
    0xfc,

    /* U+0945 "ॅ" */
    0xe,

    /* U+0946 "ॆ" */
    0x87, 0x10,

    /* U+0947 "े" */
    0xc8, 0x80,

    /* U+0948 "ै" */
    0xdc, 0x80,

    /* U+0949 "ॉ" */
    0xbf, 0xa4, 0x92,

    /* U+094A "ॊ" */
    0x86, 0xc, 0x71, 0x8, 0x42, 0x10,

    /* U+094B "ो" */
    0xe1, 0x4, 0x71, 0x8, 0x42, 0x10,

    /* U+094C "ौ" */
    0x62, 0x8c, 0x71, 0x8, 0x42, 0x10,

    /* U+094D "्" */
    0x88, 0x80,

    /* U+094E "ॎ" */
    0xea, 0xa0,

    /* U+094F "ॏ" */
    0x24, 0x9c, 0x71, 0x8, 0x42, 0x10,

    /* U+0950 "ॐ" */
    0x4, 0x9, 0x3, 0xe, 0x61, 0x54, 0xe9, 0x2c,
    0x60,

    /* U+0951 "॑" */
    0xc0,

    /* U+0952 "॒" */
    0xf8,

    /* U+0953 "॓" */
    0x90,

    /* U+0954 "॔" */
    0x60,

    /* U+0955 "ॕ" */
    0xbc,

    /* U+0956 "ॖ" */
    0xf0,

    /* U+0957 "ॗ" */
    0xff,

    /* U+0958 "क़" */
    0xfe, 0xfa, 0x54, 0xa7, 0xa, 0x0,

    /* U+0959 "ख़" */
    0xff, 0x2e, 0xb2, 0x6e, 0x46, 0xba,

    /* U+095A "ग़" */
    0xfd, 0x24, 0xb2, 0x49, 0x20,

    /* U+095B "ज़" */
    0xfe, 0xa, 0x72, 0xa3, 0x50, 0x80,

    /* U+095C "ड़" */
    0xfe, 0xf1, 0x5, 0xc4, 0x87, 0x4, 0x0,

    /* U+095D "ढ़" */
    0xfd, 0xc8, 0x26, 0xe9, 0xc1, 0x0,

    /* U+095E "फ़" */
    0xff, 0x3a, 0x54, 0xa7, 0xa, 0x0,

    /* U+095F "य़" */
    0xfe, 0x48, 0x92, 0x63, 0x44, 0x80,

    /* U+0960 "ॠ" */
    0xff, 0xb5, 0x17, 0x83, 0x62, 0xa0, 0x58, 0xc,

    /* U+0961 "ॡ" */
    0xff, 0x9a, 0xd4, 0x45, 0x3, 0x4, 0x4,

    /* U+0962 "ॢ" */
    0xf9, 0xa2, 0x30,

    /* U+0963 "ॣ" */
    0xf9, 0xa2, 0x30,

    /* U+0964 "।" */
    0xfc,

    /* U+0965 "॥" */
    0xb6, 0xdb, 0x40,

    /* U+0966 "०" */
    0xf7, 0x80,

    /* U+0967 "१" */
    0x75, 0xa4, 0x80,

    /* U+0968 "२" */
    0x70, 0x26, 0x94, 0x70, 0x20, 0x40,

    /* U+0969 "३" */
    0x62, 0x6d, 0x62, 0x10,

    /* U+096A "४" */
    0x8b, 0x94, 0xa7, 0x0,

    /* U+096B "५" */
    0x4, 0xac, 0xc1, 0x4,

    /* U+096C "६" */
    0xe8, 0x4b, 0xd2, 0x10,

    /* U+096D "७" */
    0x9a, 0x55, 0xd1, 0x38,

    /* U+096E "८" */
    0x12, 0x48, 0x86,

    /* U+096F "९" */
    0xea, 0xe4, 0x22, 0x0,

    /* U+0970 "॰" */
    0x74,

    /* U+0971 "ॱ" */
    0x80,

    /* U+0972 "ॲ" */
    0x5, 0x7, 0x77, 0x12, 0x3e, 0x8a, 0x4a, 0x32,

    /* U+0973 "ॳ" */
    0x2, 0x2, 0x77, 0x12, 0x9e, 0x8a, 0x4a, 0x32,

    /* U+0974 "ॴ" */
    0x0, 0x80, 0x26, 0xfc, 0x92, 0x34, 0xa7, 0x29,
    0x49, 0xd2,

    /* U+0975 "ॵ" */
    0x1, 0x1, 0x20, 0x39, 0xbf, 0x24, 0x8d, 0x29,
    0xc9, 0xd2, 0x4, 0x80,

    /* U+0976 "ॶ" */
    0x77, 0x12, 0x3e, 0x8a, 0x4a, 0x32, 0x0, 0x3c,

    /* U+0977 "ॷ" */
    0x77, 0x12, 0x3e, 0x8a, 0x4a, 0x32, 0x0, 0x3c,
    0x3c,

    /* U+0978 "ॸ" */
    0xfd, 0x7, 0x32, 0x8, 0x40,

    /* U+0979 "ॹ" */
    0xfe, 0x8, 0x74, 0xa5, 0x46, 0x8c, 0x8,

    /* U+097A "ॺ" */
    0xfe, 0x48, 0xf2, 0x63, 0x40, 0x80,

    /* U+097B "ॻ" */
    0xfd, 0x24, 0xb2, 0x48, 0x2f, 0xc0,

    /* U+097C "ॼ" */
    0xfe, 0xa, 0x72, 0xa3, 0x40, 0xbf, 0x80,

    /* U+097D "ॽ" */
    0xe1, 0x16, 0x44,

    /* U+097E "ॾ" */
    0xfe, 0xf1, 0x5, 0xc4, 0x87, 0x3f, 0x80,

    /* U+097F "ॿ" */
    0xfd, 0xaa, 0xba, 0x78, 0x2f, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 36, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 29, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 48, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 3, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 15, .adv_w = 133, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 26, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 29, .adv_w = 50, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 32, .adv_w = 50, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 75, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 37, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 41, .adv_w = 32, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 51, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 43, .adv_w = 30, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 47, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 88, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 30, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 32, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 97, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 96, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 103, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 118, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 113, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 103, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 121, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 114, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 46, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 109, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 91, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 131, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 114, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 99, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 144, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 99, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 38, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 258, .adv_w = 45, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 38, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 264, .adv_w = 69, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 266, .adv_w = 92, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 267, .adv_w = 31, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 268, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 84, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 79, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 84, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 45, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 86, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 293, .adv_w = 86, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 35, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 37, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 301, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 35, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 130, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 86, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 86, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 322, .adv_w = 86, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 326, .adv_w = 52, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 71, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 48, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 86, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 75, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 110, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 73, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 74, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 353, .adv_w = 73, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 48, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 360, .adv_w = 34, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 362, .adv_w = 45, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 366, .adv_w = 97, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 368, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = -5, .ofs_y = 7},
    {.bitmap_index = 369, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -5, .ofs_y = 6},
    {.bitmap_index = 371, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -2, .ofs_y = 7},
    {.bitmap_index = 372, .adv_w = 51, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 373, .adv_w = 121, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 121, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 158, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 87, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 102, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 140, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 126, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 433, .adv_w = 84, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 440, .adv_w = 84, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 447, .adv_w = 84, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 453, .adv_w = 84, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 461, .adv_w = 158, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 122, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 125, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 98, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 103, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 114, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 118, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 109, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 103, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 91, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 116, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 87, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 83, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 106, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 121, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 89, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 105, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 93, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 101, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 72, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 72, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 105, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 670, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 677, .adv_w = 89, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 84, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 76, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 703, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 5},
    {.bitmap_index = 704, .adv_w = 46, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -5, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 77, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 41, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 41, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 40, .box_w = 6, .box_h = 9, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -4, .ofs_y = -2},
    {.bitmap_index = 731, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -3, .ofs_y = -2},
    {.bitmap_index = 733, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -3, .ofs_y = -2},
    {.bitmap_index = 734, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -3, .ofs_y = -2},
    {.bitmap_index = 735, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = -3, .ofs_y = 6},
    {.bitmap_index = 736, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -5, .ofs_y = 5},
    {.bitmap_index = 738, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 6},
    {.bitmap_index = 740, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -4, .ofs_y = 6},
    {.bitmap_index = 742, .adv_w = 46, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 46, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 46, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 46, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 765, .adv_w = 52, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 767, .adv_w = 46, .box_w = 5, .box_h = 9, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 782, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = -2, .ofs_y = 7},
    {.bitmap_index = 783, .adv_w = 0, .box_w = 5, .box_h = 1, .ofs_x = -3, .ofs_y = -2},
    {.bitmap_index = 784, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -4, .ofs_y = 7},
    {.bitmap_index = 785, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = -4, .ofs_y = 7},
    {.bitmap_index = 786, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = -3, .ofs_y = 7},
    {.bitmap_index = 787, .adv_w = 0, .box_w = 4, .box_h = 1, .ofs_x = -6, .ofs_y = -2},
    {.bitmap_index = 788, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = -6, .ofs_y = -3},
    {.bitmap_index = 789, .adv_w = 122, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 125, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 103, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 819, .adv_w = 91, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 825, .adv_w = 121, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 101, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 126, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 845, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 852, .adv_w = 0, .box_w = 4, .box_h = 5, .ofs_x = -5, .ofs_y = -4},
    {.bitmap_index = 855, .adv_w = 0, .box_w = 4, .box_h = 5, .ofs_x = -5, .ofs_y = -4},
    {.bitmap_index = 858, .adv_w = 52, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 68, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 864, .adv_w = 72, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 97, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 100, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 881, .adv_w = 102, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 85, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 114, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 893, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 85, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 44, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 901, .adv_w = 36, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 902, .adv_w = 121, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 121, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 158, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 121, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 948, .adv_w = 121, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 957, .adv_w = 89, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 969, .adv_w = 101, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 975, .adv_w = 94, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 981, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 988, .adv_w = 82, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 106, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 998, .adv_w = 89, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1}
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

