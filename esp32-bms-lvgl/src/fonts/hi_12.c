/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --font /tmp/NotoDeva.ttf --size 12 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x900-0x97F -o src/fonts/hi_12.c
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
    0xfd, 0x80,

    /* U+0022 "\"" */
    0xdd, 0x50,

    /* U+0023 "#" */
    0x14, 0x29, 0xf9, 0x22, 0x5f, 0xca, 0x14,

    /* U+0025 "%" */
    0x40, 0x52, 0x29, 0x15, 0x5, 0x70, 0xac, 0x96,
    0x4e,

    /* U+0027 "'" */
    0xf4,

    /* U+0028 "(" */
    0x4b, 0x49, 0x24, 0x99, 0x20,

    /* U+0029 ")" */
    0x99, 0x24, 0xda, 0x4b, 0x40,

    /* U+002A "*" */
    0x20, 0x8f, 0x8c, 0x50, 0x0,

    /* U+002B "+" */
    0x21, 0x9, 0xf2, 0x10,

    /* U+002C "," */
    0x58,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0x84, 0x23, 0x10, 0x84, 0x62, 0x10, 0x80,

    /* U+0030 "0" */
    0x66, 0xa3, 0x18, 0xc6, 0x33, 0x70,

    /* U+0031 "1" */
    0x2e, 0x92, 0x49, 0x20,

    /* U+0032 "2" */
    0x67, 0x86, 0x31, 0x11, 0x10, 0xf8,

    /* U+0033 "3" */
    0x31, 0x70, 0xc2, 0x30, 0x30, 0x43, 0xf8,

    /* U+0034 "4" */
    0x8, 0x63, 0x8a, 0x4b, 0x2f, 0xc2, 0x8,

    /* U+0035 "5" */
    0xf7, 0xa1, 0xf, 0xc, 0x23, 0xf0,

    /* U+0036 "6" */
    0x33, 0x21, 0xf, 0xc6, 0x31, 0x70,

    /* U+0037 "7" */
    0xff, 0xf0, 0xc2, 0x18, 0x41, 0xc, 0x20,

    /* U+0038 "8" */
    0x66, 0xe3, 0xa6, 0x4e, 0x31, 0xf0,

    /* U+0039 "9" */
    0x66, 0xa3, 0x19, 0xb4, 0x22, 0xf0,

    /* U+003A ":" */
    0xb0, 0xc,

    /* U+003B ";" */
    0xb0, 0xa, 0x80,

    /* U+003C "<" */
    0x9, 0xb1, 0x83, 0x4,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0x6, 0xc, 0x36, 0x40,

    /* U+003F "?" */
    0x6b, 0x11, 0x26, 0x0, 0x60,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x70,

    /* U+005C "\\" */
    0x42, 0x10, 0xc2, 0x10, 0x86, 0x10, 0x84, 0x10,

    /* U+005D "]" */
    0xd5, 0x55, 0x57,

    /* U+005E "^" */
    0x10, 0xc2, 0x9a, 0x47, 0x10,

    /* U+005F "_" */
    0xf8,

    /* U+007B "{" */
    0x32, 0x22, 0x2e, 0xe2, 0x22, 0x23,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x89, 0x24, 0xda, 0x49, 0x40,

    /* U+007E "~" */
    0xc1, 0xc0,

    /* U+0900 "ऀ" */
    0x74, 0xaa,

    /* U+0901 "ँ" */
    0xac, 0xdc,

    /* U+0902 "ं" */
    0x80,

    /* U+0903 "ः" */
    0x88,

    /* U+0904 "ऄ" */
    0x0, 0x8, 0x3, 0x80, 0x23, 0x3a, 0x48, 0x24,
    0x22, 0x8f, 0x24, 0x8e, 0x40, 0x20,

    /* U+0905 "अ" */
    0x73, 0x84, 0x82, 0x52, 0x28, 0xf2, 0x48, 0xe4,
    0x2,

    /* U+0906 "आ" */
    0x73, 0xf8, 0x49, 0x2, 0x49, 0x22, 0x48, 0xf2,
    0x24, 0x90, 0xe4, 0x80, 0x24,

    /* U+0907 "इ" */
    0xfc, 0x47, 0x10, 0x70, 0x20, 0xbc, 0x18,

    /* U+0908 "ई" */
    0x1c, 0x41, 0x4, 0xfc, 0x47, 0x10, 0x78, 0x20,
    0x9c, 0x10,

    /* U+0909 "उ" */
    0xfe, 0x8, 0x10, 0xcc, 0xc8, 0x99, 0x1c,

    /* U+090A "ऊ" */
    0xff, 0xc1, 0x0, 0x40, 0x60, 0xcf, 0x91, 0x26,
    0x48, 0xe6,

    /* U+090B "ऋ" */
    0xff, 0xe0, 0x81, 0xd6, 0xe, 0xc0, 0xf8, 0x6b,
    0x19, 0x40, 0x2f,

    /* U+090C "ऌ" */
    0xff, 0x81, 0x0, 0x8f, 0xe4, 0x92, 0x8, 0x98,
    0x68, 0x3, 0x80,

    /* U+090D "ऍ" */
    0x0, 0x48, 0x70, 0xf, 0xe8, 0x91, 0x22, 0x4c,
    0xc0, 0x60, 0x60, 0x41, 0x80,

    /* U+090E "ऎ" */
    0x0, 0x80, 0xe0, 0x2f, 0xe8, 0x91, 0x22, 0x4c,
    0xd0, 0xc0, 0xc0, 0x40, 0x81, 0x0,

    /* U+090F "ए" */
    0xfe, 0x89, 0x12, 0x24, 0xcc, 0xc, 0x6, 0x4,
    0x8,

    /* U+0910 "ऐ" */
    0x30, 0x10, 0x20, 0x2f, 0xe8, 0x91, 0x22, 0x48,
    0xc0, 0x60, 0x60, 0x40, 0x80,

    /* U+0911 "ऑ" */
    0x0, 0x98, 0x3, 0x80, 0x0, 0xf7, 0xf0, 0x92,
    0x4, 0x92, 0xcc, 0x99, 0xe4, 0x49, 0x21, 0x89,
    0x0, 0x48,

    /* U+0912 "ऒ" */
    0x0, 0x0, 0x8, 0x0, 0x70, 0x0, 0x43, 0x3f,
    0xa4, 0x90, 0x24, 0x82, 0x24, 0x8f, 0x22, 0x49,
    0xe, 0x48, 0x2, 0x40,

    /* U+0913 "ओ" */
    0x1, 0xc0, 0x2, 0x0, 0x8, 0x0, 0x47, 0xbf,
    0x84, 0x90, 0x64, 0x91, 0xe4, 0xc9, 0x22, 0x49,
    0xc, 0x48, 0x2, 0x40,

    /* U+0914 "औ" */
    0x1, 0xc0, 0x2, 0x0, 0x78, 0x0, 0xc7, 0xbf,
    0x84, 0x90, 0x64, 0x91, 0xe4, 0xc9, 0x22, 0x49,
    0xc, 0x48, 0x2, 0x40,

    /* U+0915 "क" */
    0xff, 0xc1, 0x3, 0xc1, 0x1c, 0x44, 0x93, 0x23,
    0x48, 0x10,

    /* U+0916 "ख" */
    0xff, 0xc4, 0x21, 0x79, 0xf2, 0x6c, 0x99, 0xe3,
    0x8, 0x3e,

    /* U+0917 "ग" */
    0xfe, 0x48, 0x93, 0x26, 0x44, 0x81, 0x2,

    /* U+0918 "घ" */
    0xff, 0x89, 0x13, 0xa4, 0x49, 0x8d, 0x2,

    /* U+0919 "ङ" */
    0xff, 0x8, 0x38, 0x21, 0x3c, 0x44, 0x44, 0x38,

    /* U+091A "च" */
    0xff, 0x2, 0xfa, 0x22, 0x22, 0x26, 0x1a, 0x2,

    /* U+091B "छ" */
    0xff, 0x83, 0x1b, 0x89, 0x26, 0xd2, 0x9, 0x18,
    0x78,

    /* U+091C "ज" */
    0xff, 0x80, 0x83, 0xc9, 0x24, 0xd3, 0x68, 0xe4,
    0x2,

    /* U+091D "झ" */
    0xff, 0x84, 0x9e, 0x48, 0x27, 0x10, 0x78, 0x24,
    0xf2, 0x18, 0x0,

    /* U+091E "ञ" */
    0xff, 0x80, 0x8e, 0x40, 0xa4, 0x73, 0x28, 0xe4,
    0x2,

    /* U+091F "ट" */
    0xfe, 0x10, 0x21, 0xc4, 0x8, 0x10, 0x1e,

    /* U+0920 "ठ" */
    0xfe, 0x10, 0x21, 0xe6, 0x68, 0x59, 0x9e,

    /* U+0921 "ड" */
    0xfe, 0x10, 0xe1, 0x3, 0x80, 0x91, 0x1c,

    /* U+0922 "ढ" */
    0xfe, 0x10, 0xe3, 0x4, 0xca, 0x5d, 0x9e,

    /* U+0923 "ण" */
    0xff, 0xa4, 0x92, 0x49, 0x24, 0x91, 0xc8, 0x4,
    0x2,

    /* U+0924 "त" */
    0xfe, 0x8, 0x13, 0xe4, 0x48, 0x91, 0x12,

    /* U+0925 "थ" */
    0x77, 0x52, 0x52, 0x32, 0x62, 0x3e, 0x2, 0x2,

    /* U+0926 "द" */
    0xfe, 0x10, 0xe2, 0x4, 0x9, 0x8f, 0x2, 0x4,

    /* U+0927 "ध" */
    0xef, 0x4a, 0x13, 0x24, 0x49, 0x9f, 0x2,

    /* U+0928 "न" */
    0xfe, 0x8, 0x13, 0xe6, 0x40, 0x81, 0x2,

    /* U+0929 "ऩ" */
    0xfe, 0x8, 0x17, 0xe6, 0x40, 0x81, 0x12,

    /* U+092A "प" */
    0xfe, 0x89, 0x12, 0x24, 0x47, 0x81, 0x2,

    /* U+092B "फ" */
    0xff, 0xd1, 0x4, 0x41, 0x1c, 0x44, 0x8f, 0x20,
    0x48, 0x10,

    /* U+092C "ब" */
    0xfe, 0x8, 0xf3, 0x25, 0x49, 0x9f, 0x2,

    /* U+092D "भ" */
    0x67, 0xc8, 0x9c, 0x42, 0x23, 0xf1, 0x88, 0x4,
    0x2,

    /* U+092E "म" */
    0xfe, 0xc9, 0x93, 0x2f, 0xcc, 0x81, 0x2,

    /* U+092F "य" */
    0xfe, 0x48, 0x96, 0x24, 0x47, 0x81, 0x2,

    /* U+0930 "र" */
    0xf8, 0x85, 0xe6, 0x30, 0xc2,

    /* U+0931 "ऱ" */
    0xf8, 0x85, 0xe6, 0x30, 0xca,

    /* U+0932 "ल" */
    0xff, 0x81, 0x0, 0x8f, 0xc5, 0xa2, 0x11, 0x88,
    0x64,

    /* U+0933 "ळ" */
    0xff, 0x81, 0xc, 0x89, 0xb4, 0x8a, 0x44, 0xdc,

    /* U+0934 "ऴ" */
    0xff, 0x81, 0xd, 0x89, 0xb4, 0x8a, 0xc4, 0xdc,
    0x0, 0x0, 0x10, 0x0,

    /* U+0935 "व" */
    0xfe, 0x8, 0xf2, 0x24, 0x49, 0x9f, 0x2,

    /* U+0936 "श" */
    0xe7, 0x92, 0xf2, 0x12, 0xe2, 0x62, 0x32, 0x1a,

    /* U+0937 "ष" */
    0xfe, 0xc9, 0x52, 0xa4, 0xc7, 0x81, 0x2,

    /* U+0938 "स" */
    0xff, 0x99, 0xc, 0x9c, 0x47, 0xe3, 0x10, 0xc8,
    0x24,

    /* U+0939 "ह" */
    0xfe, 0x19, 0xf2, 0x7, 0x88, 0x91, 0x24, 0x20,
    0x20,

    /* U+093A "ऺ" */
    0xe0,

    /* U+093B "ऻ" */
    0x49, 0x74, 0x92, 0x49, 0x0,

    /* U+093C "़" */
    0x80,

    /* U+093D "ऽ" */
    0x3a, 0x8, 0x20, 0xa4, 0xe0,

    /* U+093E "ा" */
    0xe9, 0x24, 0x92,

    /* U+093F "ि" */
    0x38, 0x46, 0x42, 0x41, 0xe0, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40,

    /* U+0940 "ी" */
    0x62, 0x48, 0xa2, 0x1c, 0x20, 0x82, 0x8, 0x20,
    0x82,

    /* U+0941 "ु" */
    0x1a, 0x14, 0x4e,

    /* U+0942 "ू" */
    0x72, 0x68, 0xd8,

    /* U+0943 "ृ" */
    0xc, 0x8f,

    /* U+0944 "ॄ" */
    0xc, 0x87, 0x47,

    /* U+0945 "ॅ" */
    0x8c, 0xdc,

    /* U+0946 "ॆ" */
    0x83, 0x86, 0x10,

    /* U+0947 "े" */
    0xc2, 0x11,

    /* U+0948 "ै" */
    0xc2, 0xf1,

    /* U+0949 "ॉ" */
    0x4b, 0xc0, 0x71, 0x8, 0x42, 0x10, 0x84,

    /* U+094A "ॊ" */
    0x1, 0x7, 0x2, 0x1c, 0x20, 0x82, 0x8, 0x20,
    0x82,

    /* U+094B "ो" */
    0xe1, 0x4, 0x23, 0x88, 0x42, 0x10, 0x84, 0x20,

    /* U+094C "ौ" */
    0xe1, 0x3c, 0x63, 0x88, 0x42, 0x10, 0x84, 0x20,

    /* U+094D "्" */
    0xc2, 0x10,

    /* U+094E "ॎ" */
    0xea, 0xaa,

    /* U+094F "ॏ" */
    0x12, 0x67, 0x86, 0x1c, 0x70, 0x82, 0x8, 0x20,
    0x82,

    /* U+0950 "ॐ" */
    0x1c, 0x82, 0x40, 0x71, 0xc0, 0x49, 0x82, 0x9b,
    0x66, 0x39, 0x4b, 0x9e, 0x0,

    /* U+0951 "॑" */
    0xc0,

    /* U+0952 "॒" */
    0xf0,

    /* U+0953 "॓" */
    0xb4,

    /* U+0954 "॔" */
    0x68,

    /* U+0955 "ॕ" */
    0x97, 0xf0,

    /* U+0956 "ॖ" */
    0x8f, 0x80,

    /* U+0957 "ॗ" */
    0xf4, 0x5c,

    /* U+0958 "क़" */
    0xff, 0xc1, 0x3, 0x41, 0x1c, 0x44, 0x93, 0x23,
    0x49, 0x10,

    /* U+0959 "ख़" */
    0xff, 0xc8, 0x23, 0x7b, 0xb2, 0xcc, 0x99, 0xe3,
    0x9, 0x3e, 0x40, 0x0,

    /* U+095A "ग़" */
    0xfe, 0x89, 0x16, 0x2c, 0x48, 0x81, 0x22,

    /* U+095B "ज़" */
    0xff, 0x80, 0x83, 0xc9, 0x24, 0x93, 0x68, 0xe4,
    0x2, 0x10, 0x0,

    /* U+095C "ड़" */
    0xfe, 0x10, 0xe1, 0x3, 0x80, 0x91, 0x1c, 0x0,
    0x20,

    /* U+095D "ढ़" */
    0xfe, 0x10, 0xe3, 0x4, 0xca, 0xdd, 0x9e, 0x0,
    0x20,

    /* U+095E "फ़" */
    0xff, 0xd1, 0x4, 0x41, 0x1c, 0x44, 0x8f, 0x20,
    0x49, 0x10,

    /* U+095F "य़" */
    0xfe, 0x89, 0x16, 0x24, 0x4f, 0x81, 0x22,

    /* U+0960 "ॠ" */
    0xff, 0xe0, 0x81, 0xd6, 0xe, 0xc0, 0xf8, 0x6b,
    0x19, 0x40, 0x2f, 0x0, 0x80, 0x1c,

    /* U+0961 "ॡ" */
    0xff, 0x80, 0x80, 0x20, 0xfc, 0x49, 0x10, 0x42,
    0x30, 0x52, 0x3, 0x80, 0x80, 0x18,

    /* U+0962 "ॢ" */
    0xfe, 0xd8, 0xd4, 0xc,

    /* U+0963 "ॣ" */
    0xf9, 0x5a, 0x22, 0x30, 0x60,

    /* U+0964 "।" */
    0xfe,

    /* U+0965 "॥" */
    0x99, 0x99, 0x99, 0x90,

    /* U+0966 "०" */
    0x76, 0xe3, 0x37, 0x0,

    /* U+0967 "१" */
    0xe9, 0xf6, 0xc4, 0x31, 0x30,

    /* U+0968 "२" */
    0xe1, 0x11, 0xe6, 0x31,

    /* U+0969 "३" */
    0xf1, 0x17, 0x11, 0x63, 0x10,

    /* U+096A "४" */
    0xc9, 0x27, 0x8c, 0x31, 0x24, 0x8c,

    /* U+096B "५" */
    0x2, 0x8, 0x20, 0x99, 0xc1, 0x82, 0xc,

    /* U+096C "६" */
    0x64, 0x20, 0xc8, 0x4d, 0xe3, 0x8,

    /* U+096D "७" */
    0x82, 0xea, 0xdf, 0x45, 0x93, 0x80,

    /* U+096E "८" */
    0x11, 0x88, 0x8c, 0x42, 0x2f,

    /* U+096F "९" */
    0x62, 0x49, 0x3c, 0x60, 0xc1, 0x82, 0x8,

    /* U+0970 "॰" */
    0x6b, 0xb6,

    /* U+0971 "ॱ" */
    0x80,

    /* U+0972 "ॲ" */
    0xc, 0x81, 0xe0, 0x1, 0xee, 0x9, 0x2, 0x4b,
    0x13, 0x3c, 0x49, 0xc, 0x40, 0x10,

    /* U+0973 "ॳ" */
    0x1, 0x0, 0x8c, 0xe1, 0x20, 0x94, 0x8a, 0x3c,
    0x92, 0x39, 0x0, 0x80,

    /* U+0974 "ॴ" */
    0x0, 0x20, 0x1, 0xc, 0xfe, 0x12, 0x40, 0x92,
    0x48, 0x92, 0x3c, 0x89, 0x24, 0x39, 0x20, 0x9,
    0x0,

    /* U+0975 "ॵ" */
    0x0, 0x40, 0x13, 0x0, 0x74, 0x0, 0x67, 0xbf,
    0x84, 0x90, 0x64, 0x91, 0xe4, 0x49, 0x21, 0xc9,
    0x0, 0x48, 0x2, 0x40,

    /* U+0976 "ॶ" */
    0x73, 0x84, 0x82, 0x52, 0x28, 0xf2, 0x48, 0xe4,
    0x2, 0x0, 0x8, 0x83, 0x80,

    /* U+0977 "ॷ" */
    0x73, 0x84, 0x82, 0x52, 0x28, 0xf2, 0x48, 0xe4,
    0x2, 0x1, 0xf, 0x7, 0xc0,

    /* U+0978 "ॸ" */
    0xfe, 0x40, 0x83, 0xc6, 0x40, 0x81, 0x0,

    /* U+0979 "ॹ" */
    0xff, 0x80, 0x87, 0xc9, 0x24, 0x91, 0xc8, 0x4,
    0x52, 0x10, 0x0,

    /* U+097A "ॺ" */
    0xfe, 0x48, 0xd7, 0xa4, 0xc7, 0x81, 0x2,

    /* U+097B "ॻ" */
    0xfe, 0x48, 0x93, 0x26, 0x40, 0x81, 0x3e,

    /* U+097C "ॼ" */
    0xff, 0x80, 0x83, 0xc9, 0x26, 0x51, 0xc8, 0x4,
    0xfe,

    /* U+097D "ॽ" */
    0xe1, 0x11, 0x64, 0x44,

    /* U+097E "ॾ" */
    0xfe, 0x8, 0xf1, 0x3, 0xc8, 0x8f, 0x3e,

    /* U+097F "ॿ" */
    0xfe, 0x9, 0xf3, 0x25, 0x4f, 0x81, 0x3e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 50, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 75, .box_w = 1, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 99, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 163, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 63, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 22, .adv_w = 70, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 27, .adv_w = 70, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 32, .adv_w = 117, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 37, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 41, .adv_w = 53, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 67, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 43, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 85, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 52, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 106, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 106, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 106, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 106, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 58, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 58, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 118, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 122, .adv_w = 107, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 125, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 129, .adv_w = 101, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 70, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 139, .adv_w = 85, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 147, .adv_w = 70, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 150, .adv_w = 107, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 155, .adv_w = 79, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 156, .adv_w = 77, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 162, .adv_w = 104, .box_w = 1, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 164, .adv_w = 75, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 169, .adv_w = 107, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 171, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 173, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -4, .ofs_y = 8},
    {.bitmap_index = 175, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -2, .ofs_y = 9},
    {.bitmap_index = 176, .adv_w = 53, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 177, .adv_w = 151, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 151, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 203, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 96, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 220, .adv_w = 96, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 230, .adv_w = 107, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 151, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 167, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 137, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 269, .adv_w = 109, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 282, .adv_w = 109, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 296, .adv_w = 109, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 305, .adv_w = 109, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 318, .adv_w = 203, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 203, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 203, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 203, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 150, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 161, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 127, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 138, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 147, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 475, .adv_w = 147, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 99, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 143, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 127, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 102, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 544, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 151, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 139, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 134, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 148, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 639, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 651, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 134, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 104, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 691, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = -2, .ofs_y = 8},
    {.bitmap_index = 692, .adv_w = 52, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = -4, .ofs_y = -2},
    {.bitmap_index = 698, .adv_w = 93, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 703, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 52, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 52, .box_w = 6, .box_h = 12, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -6, .ofs_y = -4},
    {.bitmap_index = 730, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = -4, .ofs_y = -4},
    {.bitmap_index = 733, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 735, .adv_w = 0, .box_w = 4, .box_h = 6, .ofs_x = -3, .ofs_y = -5},
    {.bitmap_index = 738, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -4, .ofs_y = 9},
    {.bitmap_index = 740, .adv_w = 0, .box_w = 5, .box_h = 4, .ofs_x = -6, .ofs_y = 7},
    {.bitmap_index = 743, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -5, .ofs_y = 7},
    {.bitmap_index = 745, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = -5, .ofs_y = 8},
    {.bitmap_index = 747, .adv_w = 52, .box_w = 5, .box_h = 11, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 52, .box_w = 6, .box_h = 12, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 52, .box_w = 5, .box_h = 12, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 771, .adv_w = 52, .box_w = 5, .box_h = 12, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 781, .adv_w = 55, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 52, .box_w = 6, .box_h = 12, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 180, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 805, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = -2, .ofs_y = 8},
    {.bitmap_index = 806, .adv_w = 0, .box_w = 4, .box_h = 1, .ofs_x = -5, .ofs_y = -2},
    {.bitmap_index = 807, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -3, .ofs_y = 9},
    {.bitmap_index = 808, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = -2, .ofs_y = 9},
    {.bitmap_index = 809, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = -4, .ofs_y = 8},
    {.bitmap_index = 811, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = -6, .ofs_y = -2},
    {.bitmap_index = 813, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -6, .ofs_y = -4},
    {.bitmap_index = 815, .adv_w = 150, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 161, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 837, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 855, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 864, .adv_w = 110, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 873, .adv_w = 151, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 167, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 904, .adv_w = 137, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 918, .adv_w = 0, .box_w = 6, .box_h = 5, .ofs_x = -6, .ofs_y = -5},
    {.bitmap_index = 922, .adv_w = 0, .box_w = 7, .box_h = 5, .ofs_x = -6, .ofs_y = -5},
    {.bitmap_index = 927, .adv_w = 74, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 117, .box_w = 4, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 932, .adv_w = 107, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 936, .adv_w = 107, .box_w = 4, .box_h = 9, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 941, .adv_w = 107, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 107, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 950, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 107, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 969, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 975, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 980, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 987, .adv_w = 83, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 989, .adv_w = 61, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 990, .adv_w = 151, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1004, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1016, .adv_w = 203, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1033, .adv_w = 203, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1053, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1066, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1079, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1086, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1097, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1104, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1120, .adv_w = 92, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1124, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1131, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0}
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

