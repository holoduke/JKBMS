/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --font /System/Library/Fonts/SFArabic.ttf --size 14 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x600-0x6FF,0xFE70-0xFEFF -o src/fonts/ar_14.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef AR_14
#define AR_14 1
#endif

#if AR_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x55, 0x54, 0x70,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x24, 0x44, 0xcc, 0xcc, 0x44, 0x62,

    /* U+0029 ")" */
    0x46, 0x22, 0x23, 0x32, 0x22, 0x44,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0xc4, 0x23, 0x10, 0x8c, 0x42, 0x31, 0x0,

    /* U+003A ":" */
    0x86,

    /* U+0600 "؀" */
    0x0, 0xf, 0x0, 0xc, 0x0, 0x4, 0x0, 0x2,
    0x0, 0x1, 0x87, 0xff, 0xfc,

    /* U+0601 "؁" */
    0x38, 0x80, 0x2, 0x64, 0x0, 0x21, 0xdf, 0xfe,

    /* U+0602 "؂" */
    0x70, 0x0, 0x48, 0x0, 0x26, 0x0, 0x13, 0x0,
    0x7, 0xff, 0xf8,

    /* U+0603 "؃" */
    0x0, 0x0, 0x70, 0x0, 0xc, 0xc0, 0x4, 0xc2,
    0x0, 0x2c, 0x1f, 0xfe, 0xff, 0x0,

    /* U+0604 "؄" */
    0x0, 0x0, 0x8, 0x0, 0x0, 0x40, 0x7, 0x12,
    0x0, 0x4c, 0x90, 0x2, 0x3b, 0x0, 0x8, 0x3,
    0xff, 0xe0, 0x0,

    /* U+0605 "؅" */
    0x7f, 0xfe, 0x0, 0x8, 0x0, 0x0,

    /* U+0606 "؆" */
    0x0, 0x6, 0x2, 0x11, 0x4, 0x2, 0xd, 0x8,
    0x44, 0x24, 0x12, 0x6, 0x3, 0x0,

    /* U+0607 "؇" */
    0x0, 0x4, 0x22, 0x9, 0x84, 0x2, 0xc, 0x88,
    0x44, 0x24, 0xa, 0x6, 0x3, 0x0,

    /* U+0608 "؈" */
    0x7, 0x2, 0x6c, 0x89, 0x23, 0x47, 0xd0, 0x26,
    0x10, 0xf8,

    /* U+0609 "؉" */
    0x3, 0x88, 0x10, 0x41, 0x2, 0x8, 0x20, 0x41,
    0x14,

    /* U+060A "؊" */
    0x3, 0x88, 0x10, 0x41, 0x2, 0x8, 0x20, 0x41,
    0x34,

    /* U+060B "؋" */
    0x30, 0x40, 0xe, 0x4d, 0x13, 0xc1, 0xf, 0xe0,
    0x8, 0x20,

    /* U+060C "،" */
    0xe0,

    /* U+060D "؍" */
    0x49, 0x29, 0x0,

    /* U+060E "؎" */
    0x70, 0x13, 0x2, 0x20, 0x44, 0x7, 0xfe,

    /* U+060F "؏" */
    0x3c, 0x40, 0x40, 0x42, 0x3e, 0x70, 0xc0, 0x9e,
    0xe1, 0x41, 0xbe,

    /* U+0610 "ؐ" */
    0x2e, 0x80,

    /* U+0611 "ؑ" */
    0x7e, 0x0,

    /* U+0612 "ؒ" */
    0xc3, 0x4e,

    /* U+0613 "ؓ" */
    0x41, 0x3b, 0x30,

    /* U+0614 "ؔ" */
    0x3f,

    /* U+0615 "ؕ" */
    0x44, 0x6e,

    /* U+0616 "ؖ" */
    0x33, 0x70,

    /* U+0617 "ؗ" */
    0x57,

    /* U+0618 "ؘ" */
    0x80,

    /* U+0619 "ؙ" */
    0x6d, 0x0,

    /* U+061A "ؚ" */
    0x0,

    /* U+061B "؛" */
    0xe1,

    /* U+061C "؜" */
    0x0,

    /* U+061E "؞" */
    0x10, 0x0, 0x0, 0x0, 0x0, 0x20, 0x80,

    /* U+061F "؟" */
    0x7b, 0x38, 0x60, 0x40, 0xc1, 0x0, 0x0, 0x40,

    /* U+0620 "ؠ" */
    0x3, 0x82, 0x22, 0x11, 0xc8, 0x7c, 0xf, 0x6,
    0x7c, 0x28, 0xc, 0x0,

    /* U+0621 "ء" */
    0x32, 0x11, 0xfc, 0x0,

    /* U+0622 "آ" */
    0xe9, 0x24, 0x92, 0x40,

    /* U+0623 "أ" */
    0x52, 0x64, 0x92, 0x49, 0x20,

    /* U+0624 "ؤ" */
    0x30, 0x81, 0x88, 0x39, 0x34, 0x51, 0x3c, 0x10,
    0xbc,

    /* U+0625 "إ" */
    0x49, 0x24, 0x92, 0x41, 0x38,

    /* U+0626 "ئ" */
    0xc3, 0xe2, 0x2, 0x11, 0x88, 0xfc, 0x1e, 0x2,
    0x86, 0x3e, 0x0,

    /* U+0627 "ا" */
    0xff, 0x80,

    /* U+0628 "ب" */
    0x80, 0x70, 0x6, 0x0, 0xc0, 0x1c, 0x6, 0x7f,
    0x80, 0x0, 0x20, 0x4, 0x0,

    /* U+0629 "ة" */
    0x50, 0x8, 0xed, 0xc6, 0x2e,

    /* U+062A "ت" */
    0x0, 0x1, 0x40, 0x0, 0x40, 0x38, 0x3, 0x0,
    0x60, 0xe, 0x3, 0x3f, 0xc0,

    /* U+062B "ث" */
    0x4, 0x0, 0x0, 0x28, 0x0, 0x8, 0x7, 0x0,
    0x60, 0xc, 0x1, 0xc0, 0x67, 0xf8,

    /* U+062C "ج" */
    0xf0, 0x1c, 0xe3, 0xc, 0x13, 0x20, 0x40, 0x40,
    0x7c,

    /* U+062D "ح" */
    0xf0, 0x1c, 0xe3, 0xc, 0x10, 0x20, 0x40, 0x40,
    0x7c,

    /* U+062E "خ" */
    0x10, 0x20, 0x7, 0x80, 0xe7, 0x18, 0x60, 0x81,
    0x2, 0x2, 0x3, 0xe0,

    /* U+062F "د" */
    0x10, 0x20, 0xc1, 0x86, 0x17, 0x80,

    /* U+0630 "ذ" */
    0x10, 0x40, 0x4, 0x8, 0x30, 0x61, 0x85, 0xe0,

    /* U+0631 "ر" */
    0x18, 0x42, 0x10, 0x84, 0x5c,

    /* U+0632 "ز" */
    0x0, 0xc0, 0x30, 0x84, 0x21, 0x8, 0xb8,

    /* U+0633 "س" */
    0x0, 0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83,
    0xba, 0x8, 0xc, 0x60, 0x1f, 0x0,

    /* U+0634 "ش" */
    0x0, 0x40, 0x1, 0x0, 0xa, 0x0, 0x28, 0x0,
    0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83, 0xba,
    0x8, 0xc, 0x60, 0x1f, 0x0,

    /* U+0635 "ص" */
    0x0, 0x1c, 0x0, 0xce, 0xb, 0xc, 0x14, 0x18,
    0x3f, 0xd0, 0x40, 0x31, 0x80, 0x3e, 0x0,

    /* U+0636 "ض" */
    0x0, 0x20, 0x0, 0x40, 0x0, 0x0, 0x0, 0xe0,
    0x6, 0x70, 0x58, 0x60, 0xa0, 0xc1, 0xfe, 0x82,
    0x1, 0x8c, 0x1, 0xf0, 0x0,

    /* U+0637 "ط" */
    0x20, 0x10, 0x8, 0x4, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+0638 "ظ" */
    0x20, 0x12, 0x9, 0x4, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+0639 "ع" */
    0x3c, 0x40, 0x40, 0x64, 0x3c, 0x60, 0xc0, 0x80,
    0x80, 0x40, 0x3f,

    /* U+063A "غ" */
    0x10, 0x10, 0x0, 0x3c, 0x40, 0x40, 0x64, 0x3c,
    0x60, 0xc0, 0x80, 0x80, 0x40, 0x3f,

    /* U+063B "ػ" */
    0x1, 0x80, 0xcc, 0x7, 0x3, 0x80, 0x61, 0x6,
    0x20, 0x64, 0x6, 0x80, 0x58, 0x9, 0xfe, 0x0,

    /* U+063C "ؼ" */
    0x0, 0x60, 0x38, 0x1c, 0x3, 0x8, 0x31, 0x3,
    0x20, 0x34, 0x2, 0xc0, 0x4f, 0xf0, 0x0, 0xf,
    0x0, 0x0, 0x8, 0x0,

    /* U+063D "ؽ" */
    0x0, 0x61, 0xc1, 0x1, 0x8, 0xc4, 0x7e, 0xf,
    0x1, 0x43, 0x1f, 0x0,

    /* U+063E "ؾ" */
    0xf1, 0xc0, 0x80, 0x41, 0x18, 0x47, 0xd0, 0x74,
    0x4, 0x86, 0x1f, 0x0,

    /* U+063F "ؿ" */
    0x0, 0x0, 0xf, 0x1c, 0x8, 0x4, 0x11, 0x84,
    0x7d, 0x7, 0x40, 0x48, 0x61, 0xf0,

    /* U+0640 "ـ" */
    0xf0,

    /* U+0641 "ف" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0x68, 0x13, 0x2,
    0x60, 0x7c, 0x1, 0xc0, 0x6f, 0xf0,

    /* U+0642 "ق" */
    0xa, 0xa, 0x0, 0xe, 0x13, 0x91, 0x91, 0x8f,
    0x81, 0xc2, 0x7c,

    /* U+0643 "ك" */
    0x0, 0x40, 0x10, 0xc6, 0x11, 0x8c, 0x60, 0x18,
    0x7, 0x1, 0x7f, 0x80,

    /* U+0644 "ل" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0xc1, 0x83,
    0x6, 0xe, 0x37, 0xc0,

    /* U+0645 "م" */
    0x39, 0xb0, 0x41, 0xfa, 0x8, 0x20, 0x82, 0x0,

    /* U+0646 "ن" */
    0x10, 0x20, 0xc, 0x18, 0x30, 0x60, 0xe3, 0x7c,

    /* U+0647 "ه" */
    0x23, 0xb7, 0x18, 0xb8,

    /* U+0648 "و" */
    0x39, 0x34, 0x51, 0x3c, 0x10, 0xbc,

    /* U+0649 "ى" */
    0x3, 0x82, 0x2, 0x11, 0x88, 0xfc, 0x1e, 0x2,
    0x86, 0x3e, 0x0,

    /* U+064A "ي" */
    0x3, 0x82, 0x22, 0x11, 0xc8, 0x7c, 0xf, 0x6,
    0x7c, 0x0, 0xe, 0x0,

    /* U+064B "ً" */
    0x73, 0x80,

    /* U+064C "ٌ" */
    0x2e, 0xe0,

    /* U+064D "ٍ" */
    0x3b, 0x80,

    /* U+064E "َ" */
    0x1c,

    /* U+064F "ُ" */
    0x6f, 0x0,

    /* U+0650 "ِ" */
    0x38,

    /* U+0651 "ّ" */
    0xd, 0xe0,

    /* U+0652 "ْ" */
    0xdb, 0x0,

    /* U+0653 "ٓ" */
    0xe0,

    /* U+0654 "ٔ" */
    0xd3, 0x80,

    /* U+0655 "ٕ" */
    0xd3, 0x80,

    /* U+0656 "ٖ" */
    0xc0,

    /* U+0657 "ٗ" */
    0x7b, 0x0,

    /* U+0658 "٘" */
    0x37, 0x80,

    /* U+0659 "ٙ" */
    0xe0,

    /* U+065A "ٚ" */
    0xc8,

    /* U+065B "ٛ" */
    0x58,

    /* U+065C "ٜ" */
    0x80,

    /* U+065D "ٝ" */
    0xd9, 0x80,

    /* U+065E "ٞ" */
    0xb8, 0x0,

    /* U+065F "ٟ" */
    0x64, 0xf0,

    /* U+0660 "٠" */
    0xf0,

    /* U+0661 "١" */
    0xab, 0x55, 0x50,

    /* U+0662 "٢" */
    0x86, 0x1c, 0xee, 0xc1, 0x4, 0x10, 0x41, 0x0,

    /* U+0663 "٣" */
    0x89, 0x49, 0x49, 0x76, 0x40, 0x40, 0x60, 0x20,
    0x20, 0x20,

    /* U+0664 "٤" */
    0x3, 0xb1, 0xf, 0x19, 0x10, 0x83, 0xc0,

    /* U+0665 "٥" */
    0x39, 0x28, 0x61, 0x86, 0x37, 0x80,

    /* U+0666 "٦" */
    0xf8, 0x20, 0x82, 0x8, 0x20, 0xc1, 0x4,

    /* U+0667 "٧" */
    0xc3, 0x42, 0x42, 0x66, 0x24, 0x24, 0x24, 0x18,
    0x18, 0x18,

    /* U+0668 "٨" */
    0x18, 0x18, 0x18, 0x3c, 0x24, 0x24, 0x64, 0x42,
    0x42, 0x42,

    /* U+0669 "٩" */
    0x72, 0x68, 0x9e, 0x8, 0x20, 0x83, 0x4,

    /* U+066A "٪" */
    0x3, 0x88, 0x10, 0x41, 0x2, 0x8, 0x20, 0x41,
    0xc,

    /* U+066B "٫" */
    0x58,

    /* U+066C "٬" */
    0xe0,

    /* U+066D "٭" */
    0x25, 0x54, 0xaa, 0x90,

    /* U+066E "ٮ" */
    0x80, 0x70, 0x6, 0x0, 0xc0, 0x1c, 0x6, 0x7f,
    0x80,

    /* U+066F "ٯ" */
    0xe, 0x13, 0x91, 0x91, 0x8f, 0x81, 0xc2, 0x7c,

    /* U+0670 "ٰ" */
    0xc0,

    /* U+0671 "ٱ" */
    0x26, 0xae, 0x44, 0x44, 0x44, 0x44,

    /* U+0672 "ٲ" */
    0x32, 0x9, 0xf2, 0x10, 0x84, 0x21, 0x8, 0x40,

    /* U+0673 "ٳ" */
    0x22, 0x22, 0x22, 0x22, 0x20, 0x34, 0xf0,

    /* U+0674 "ٴ" */
    0xd3, 0x80,

    /* U+0675 "ٵ" */
    0x31, 0x29, 0x68, 0x42, 0x10, 0x84, 0x20,

    /* U+0676 "ٶ" */
    0xc, 0x10, 0x11, 0xc4, 0xc8, 0x91, 0x1e, 0x4,
    0x13, 0xc0,

    /* U+0677 "ٷ" */
    0x6d, 0xcd, 0xc0, 0x39, 0x34, 0x51, 0x3c, 0x10,
    0xbc,

    /* U+0678 "ٸ" */
    0x3, 0x1, 0x0, 0xc0, 0x70, 0x40, 0x42, 0x31,
    0x1f, 0x83, 0xc0, 0x50, 0xc7, 0xc0,

    /* U+0679 "ٹ" */
    0xe, 0x1, 0x40, 0x78, 0x0, 0x8, 0x3, 0x0,
    0x60, 0xe, 0x3, 0x7f, 0xc0,

    /* U+067A "ٺ" */
    0x4, 0x0, 0x0, 0x10, 0x0, 0x8, 0x7, 0x0,
    0x60, 0xc, 0x1, 0xc0, 0x67, 0xf8,

    /* U+067B "ٻ" */
    0x80, 0x70, 0x6, 0x0, 0xc0, 0x1c, 0x6, 0x7f,
    0x80, 0x0, 0x20, 0x4, 0x0, 0x80,

    /* U+067C "ټ" */
    0x0, 0x1, 0x40, 0x0, 0x40, 0x38, 0x3, 0x0,
    0x60, 0xe, 0x3, 0x3f, 0xc1, 0x40, 0x10, 0x0,

    /* U+067D "ٽ" */
    0xa, 0x0, 0x0, 0x10, 0x0, 0x8, 0x7, 0x0,
    0x60, 0xc, 0x1, 0xc0, 0x67, 0xf8,

    /* U+067E "پ" */
    0x80, 0x70, 0x6, 0x0, 0xc0, 0x1c, 0x6, 0x7f,
    0x80, 0x0, 0x50, 0x4, 0x0, 0x80,

    /* U+067F "ٿ" */
    0xa, 0x0, 0x0, 0x28, 0x0, 0x8, 0x7, 0x0,
    0x60, 0xc, 0x1, 0xc0, 0x67, 0xf8,

    /* U+0680 "ڀ" */
    0x80, 0x70, 0x6, 0x0, 0xc0, 0x1c, 0x6, 0x7f,
    0x80, 0x0, 0x70, 0x2, 0x1, 0x40,

    /* U+0681 "ځ" */
    0x18, 0x40, 0x60, 0xf, 0x1, 0xce, 0x30, 0xc1,
    0x2, 0x4, 0x4, 0x7, 0xc0,

    /* U+0682 "ڂ" */
    0x18, 0x0, 0x40, 0xf, 0x1, 0xce, 0x30, 0xc1,
    0x2, 0x4, 0x4, 0x7, 0xc0,

    /* U+0683 "ڃ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x13, 0xa0, 0x40, 0x40,
    0x7c,

    /* U+0684 "ڄ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x90, 0x26, 0x40, 0x40,
    0x7c,

    /* U+0685 "څ" */
    0x18, 0x0, 0x60, 0xf, 0x1, 0xce, 0x30, 0xc1,
    0x2, 0x4, 0x4, 0x7, 0xc0,

    /* U+0686 "چ" */
    0xf0, 0x1c, 0xe3, 0xd, 0x93, 0x26, 0x40, 0x40,
    0x7c,

    /* U+0687 "ڇ" */
    0xf0, 0x1c, 0xe3, 0xd, 0x92, 0x27, 0x40, 0x40,
    0x7c,

    /* U+0688 "ڈ" */
    0x20, 0xe2, 0x8e, 0x0, 0x60, 0x83, 0x6, 0x17,
    0x80,

    /* U+0689 "ډ" */
    0x10, 0x20, 0xc1, 0x86, 0x17, 0x94, 0x30,

    /* U+068A "ڊ" */
    0x10, 0x20, 0xc1, 0x86, 0x17, 0x80, 0x30, 0x0,

    /* U+068B "ڋ" */
    0x20, 0xe2, 0x8e, 0x0, 0x60, 0x83, 0x6, 0x17,
    0x80, 0x30, 0x0,

    /* U+068C "ڌ" */
    0x28, 0xa0, 0x4, 0x8, 0x30, 0x61, 0x85, 0xe0,

    /* U+068D "ڍ" */
    0x10, 0x20, 0xc1, 0x86, 0x17, 0x80, 0x78, 0x0,

    /* U+068E "ڎ" */
    0x10, 0x43, 0x80, 0x10, 0x20, 0xc1, 0x86, 0x17,
    0x80,

    /* U+068F "ڏ" */
    0x28, 0xa1, 0x0, 0x10, 0x20, 0xc1, 0x86, 0x17,
    0x80,

    /* U+0690 "ڐ" */
    0x28, 0xa3, 0x80, 0x10, 0x20, 0xc1, 0x86, 0x17,
    0x80,

    /* U+0691 "ڑ" */
    0x10, 0x61, 0x8e, 0x0, 0x20, 0x82, 0x8, 0x21,
    0x38,

    /* U+0692 "ڒ" */
    0x28, 0xc0, 0x30, 0x84, 0x21, 0x8, 0xb8,

    /* U+0693 "ړ" */
    0x18, 0x42, 0x10, 0x8b, 0x94, 0x60,

    /* U+0694 "ڔ" */
    0x18, 0x42, 0x10, 0x84, 0x5c, 0x1, 0x8,

    /* U+0695 "ڕ" */
    0x18, 0x42, 0x10, 0x84, 0x5c, 0x2, 0x88,

    /* U+0696 "ږ" */
    0x0, 0xc0, 0x30, 0x84, 0x21, 0x8, 0xb8, 0x2,
    0x10,

    /* U+0697 "ڗ" */
    0x3c, 0x1, 0x82, 0x8, 0x20, 0x82, 0x13, 0x80,

    /* U+0698 "ژ" */
    0x18, 0x3, 0x80, 0x18, 0x20, 0x82, 0x8, 0x21,
    0x38,

    /* U+0699 "ڙ" */
    0x38, 0x3, 0x80, 0x18, 0x20, 0x82, 0x8, 0x21,
    0x38,

    /* U+069A "ښ" */
    0x0, 0x40, 0x1, 0x0, 0x0, 0x40, 0x91, 0x82,
    0x46, 0x9, 0x18, 0x3b, 0xa0, 0x80, 0xc6, 0x41,
    0xf1, 0x0,

    /* U+069B "ڛ" */
    0x0, 0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83,
    0xba, 0x8, 0xc, 0x6a, 0x1f, 0x0, 0x0, 0x40,

    /* U+069C "ڜ" */
    0x0, 0x40, 0x1, 0x0, 0xa, 0x0, 0x28, 0x0,
    0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83, 0xba,
    0x8, 0xc, 0x6a, 0x1f, 0x0, 0x0, 0x40,

    /* U+069D "ڝ" */
    0x0, 0x1c, 0x0, 0xce, 0xb, 0xc, 0x14, 0x18,
    0x3f, 0xd0, 0x40, 0x31, 0x94, 0x3e, 0x28,

    /* U+069E "ڞ" */
    0x0, 0x20, 0x0, 0x20, 0x1, 0x40, 0x0, 0x0,
    0x1, 0xc0, 0xc, 0xe0, 0xb0, 0xc1, 0x41, 0x83,
    0xfd, 0x4, 0x3, 0x18, 0x3, 0xe0, 0x0,

    /* U+069F "ڟ" */
    0x24, 0x10, 0xb, 0x84, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+06A0 "ڠ" */
    0x10, 0x10, 0x28, 0x28, 0x0, 0x3c, 0x40, 0x40,
    0x64, 0x3c, 0x60, 0xc0, 0x80, 0x80, 0x40, 0x3f,

    /* U+06A1 "ڡ" */
    0x0, 0xd0, 0x26, 0x4, 0xc0, 0xf8, 0x3, 0x80,
    0xdf, 0xe0,

    /* U+06A2 "ڢ" */
    0x0, 0xd0, 0x26, 0x4, 0xc0, 0xf8, 0x3, 0x80,
    0xdf, 0xe0, 0x0, 0x6, 0x0, 0x40,

    /* U+06A3 "ڣ" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0x68, 0x13, 0x2,
    0x60, 0x7c, 0x1, 0xc0, 0x6f, 0xf0, 0x0, 0x3,
    0x0, 0x20,

    /* U+06A4 "ڤ" */
    0x0, 0x0, 0x10, 0x3, 0x0, 0x60, 0x0, 0x1,
    0xa0, 0x4c, 0x9, 0x81, 0xf0, 0x7, 0x1, 0xbf,
    0xc0,

    /* U+06A5 "ڥ" */
    0x0, 0xd0, 0x26, 0x4, 0xc0, 0xf8, 0x3, 0x80,
    0xdf, 0xe0, 0x0, 0xf, 0x0, 0x0, 0x8, 0x0,

    /* U+06A6 "ڦ" */
    0x0, 0x40, 0x18, 0x3, 0x0, 0x60, 0x0, 0x1,
    0xa0, 0x4c, 0x9, 0x81, 0xf0, 0x7, 0x1, 0xbf,
    0xc0,

    /* U+06A7 "ڧ" */
    0x4, 0x4, 0x0, 0xe, 0x13, 0x91, 0x91, 0x8f,
    0x81, 0xc2, 0x7c,

    /* U+06A8 "ڨ" */
    0x4, 0x4, 0xa, 0xa, 0x0, 0xe, 0x13, 0x91,
    0x91, 0x8f, 0x81, 0xc2, 0x7c,

    /* U+06A9 "ک" */
    0x0, 0x60, 0x38, 0x1c, 0x3, 0x8, 0x31, 0x3,
    0x20, 0x34, 0x2, 0xc0, 0x4f, 0xf0,

    /* U+06AA "ڪ" */
    0x1, 0x0, 0x18, 0x3, 0x0, 0x30, 0x3, 0xff,
    0x0, 0x4, 0x0, 0x3f, 0xfe,

    /* U+06AB "ګ" */
    0x0, 0x60, 0x18, 0xe, 0x83, 0x20, 0x61, 0x6,
    0x20, 0x24, 0x2, 0xc0, 0x4f, 0xf0,

    /* U+06AC "ڬ" */
    0xc, 0x40, 0x10, 0xc6, 0x11, 0x8c, 0x60, 0x18,
    0x7, 0x1, 0x7f, 0x80,

    /* U+06AD "ڭ" */
    0xc, 0x2, 0x90, 0x4, 0x31, 0x84, 0x63, 0x18,
    0x6, 0x1, 0xc0, 0x5f, 0xe0,

    /* U+06AE "ڮ" */
    0x0, 0x40, 0x10, 0xc6, 0x11, 0x8c, 0x60, 0x18,
    0x7, 0x1, 0x7f, 0x80, 0x1, 0xe0, 0x0, 0x4,
    0x0,

    /* U+06AF "گ" */
    0x0, 0x20, 0x18, 0x5, 0x83, 0xe0, 0x70, 0xc,
    0x20, 0xc4, 0xc, 0x80, 0xd0, 0xb, 0x1, 0x3f,
    0xc0,

    /* U+06B0 "ڰ" */
    0x0, 0x20, 0x18, 0xd, 0x82, 0x60, 0x3a, 0xc,
    0x81, 0x84, 0x18, 0x80, 0x90, 0xb, 0x1, 0x3f,
    0xc0,

    /* U+06B1 "ڱ" */
    0x1, 0x20, 0xb8, 0x5, 0x83, 0xe0, 0x70, 0xc,
    0x20, 0xc4, 0xc, 0x80, 0xd0, 0xb, 0x1, 0x3f,
    0xc0,

    /* U+06B2 "ڲ" */
    0x0, 0x20, 0x18, 0x5, 0x83, 0xe0, 0x70, 0xc,
    0x20, 0xc4, 0xc, 0x80, 0xd0, 0xb, 0x1, 0x3f,
    0xc0, 0x0, 0x14, 0x0, 0x0,

    /* U+06B3 "ڳ" */
    0x0, 0x20, 0x18, 0x5, 0x83, 0xe0, 0x70, 0xc,
    0x20, 0xc4, 0xc, 0x80, 0xd0, 0xb, 0x1, 0x3f,
    0xc0, 0x0, 0x18, 0x0, 0x0, 0x20,

    /* U+06B4 "ڴ" */
    0x6, 0x0, 0x4, 0x17, 0x0, 0xb0, 0x7c, 0xe,
    0x1, 0x84, 0x18, 0x81, 0x90, 0x1a, 0x1, 0x60,
    0x27, 0xf8,

    /* U+06B5 "ڵ" */
    0x5, 0x6, 0x2, 0x0, 0x2, 0x2, 0x2, 0x2,
    0x2, 0x82, 0x82, 0x82, 0x82, 0xc6, 0x7c,

    /* U+06B6 "ڶ" */
    0x2, 0x4, 0x0, 0x10, 0x20, 0x40, 0x81, 0x83,
    0x6, 0xc, 0x1c, 0x6f, 0x80,

    /* U+06B7 "ڷ" */
    0x2, 0x2, 0x5, 0x5, 0x0, 0x2, 0x2, 0x2,
    0x2, 0x2, 0x82, 0x82, 0x82, 0x82, 0xc6, 0x7c,

    /* U+06B8 "ڸ" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0xc1, 0x83,
    0x6, 0xe, 0x37, 0xc0, 0xa, 0x8,

    /* U+06B9 "ڹ" */
    0x10, 0x20, 0xc, 0x18, 0x30, 0x60, 0xe3, 0x7c,
    0x0, 0x40, 0x80,

    /* U+06BA "ں" */
    0x3, 0x6, 0xc, 0x18, 0x38, 0xdf, 0x0,

    /* U+06BB "ڻ" */
    0x20, 0x40, 0xe1, 0xc0, 0x10, 0x60, 0xc1, 0x83,
    0x8d, 0xf0,

    /* U+06BC "ڼ" */
    0x10, 0x20, 0xc, 0x18, 0x30, 0x60, 0xe3, 0x7c,
    0x60, 0xc0,

    /* U+06BD "ڽ" */
    0x10, 0x20, 0xa1, 0x0, 0x30, 0x60, 0xc1, 0x83,
    0x8d, 0xf0,

    /* U+06BE "ھ" */
    0x30, 0x1f, 0x9, 0xc4, 0x91, 0x8f, 0xf8,

    /* U+06BF "ڿ" */
    0x10, 0x20, 0x7, 0x80, 0xe7, 0x18, 0x6c, 0x99,
    0x32, 0x2, 0x3, 0xe0,

    /* U+06C0 "ۀ" */
    0x72, 0x1c, 0x7, 0x6e, 0x31, 0x70,

    /* U+06C1 "ہ" */
    0x23, 0xb7, 0x18, 0xb8,

    /* U+06C2 "ۂ" */
    0x72, 0x1c, 0x7, 0x6e, 0x31, 0x70,

    /* U+06C3 "ۃ" */
    0x50, 0x8, 0xed, 0xc6, 0x2e,

    /* U+06C4 "ۄ" */
    0x39, 0x34, 0x51, 0x3d, 0x9a, 0xbc,

    /* U+06C5 "ۅ" */
    0x39, 0x34, 0x4f, 0x5, 0xf1, 0xbc,

    /* U+06C6 "ۆ" */
    0x28, 0xc1, 0x0, 0x39, 0x34, 0x51, 0x3c, 0x10,
    0xbc,

    /* U+06C7 "ۇ" */
    0x18, 0xa3, 0x0, 0x39, 0x34, 0x51, 0x3c, 0x10,
    0xbc,

    /* U+06C8 "ۈ" */
    0x10, 0x40, 0xe, 0x4d, 0x14, 0x4f, 0x4, 0x2f,
    0x0,

    /* U+06C9 "ۉ" */
    0x10, 0xc2, 0x80, 0x39, 0x34, 0x51, 0x3c, 0x10,
    0xbc,

    /* U+06CA "ۊ" */
    0x28, 0xa0, 0xe, 0x4d, 0x14, 0x4f, 0x4, 0x2f,
    0x0,

    /* U+06CB "ۋ" */
    0x10, 0x42, 0x8a, 0x0, 0xe4, 0xd1, 0x44, 0xf0,
    0x42, 0xf0,

    /* U+06CC "ی" */
    0x3, 0x82, 0x2, 0x11, 0x88, 0xfc, 0x1e, 0x2,
    0x86, 0x3e, 0x0,

    /* U+06CD "ۍ" */
    0x0, 0xe0, 0x20, 0x8, 0x71, 0x82, 0x3e, 0x41,
    0xc8, 0x8, 0x86, 0xf, 0x80,

    /* U+06CE "ێ" */
    0x20, 0x61, 0xc1, 0x1, 0x8, 0xc4, 0x7e, 0xf,
    0x1, 0x43, 0x1f, 0x0,

    /* U+06CF "ۏ" */
    0x10, 0x40, 0xe, 0x4d, 0x14, 0x4f, 0x4, 0x2f,
    0x0,

    /* U+06D0 "ې" */
    0x3, 0x86, 0x22, 0x11, 0xc8, 0x7c, 0xf, 0x6,
    0x7c, 0x0, 0x4, 0x2, 0x0,

    /* U+06D1 "ۑ" */
    0x3, 0x86, 0x22, 0x11, 0xc8, 0x7c, 0xf, 0x6,
    0x7c, 0x0, 0xc, 0x2, 0x0,

    /* U+06D2 "ے" */
    0x38, 0xc, 0x1, 0x0, 0x40, 0x8, 0x0, 0xff,
    0xc0,

    /* U+06D3 "ۓ" */
    0x18, 0x4, 0x0, 0xe0, 0x1c, 0x6, 0x0, 0x80,
    0x20, 0x4, 0x0, 0x7f, 0xe0,

    /* U+06D4 "۔" */
    0xe0,

    /* U+06D5 "ە" */
    0x23, 0xb7, 0x18, 0xb8,

    /* U+06D6 "ۖ" */
    0x20, 0x49, 0xf3, 0xe0,

    /* U+06D7 "ۗ" */
    0x1, 0x8e, 0xe7, 0x0,

    /* U+06D8 "ۘ" */
    0x3f,

    /* U+06D9 "ۙ" */
    0x2d, 0xf0,

    /* U+06DA "ۚ" */
    0xce, 0xf0,

    /* U+06DB "ۛ" */
    0x6, 0x22,

    /* U+06DC "ۜ" */
    0x12, 0x77, 0x0,

    /* U+06DD "۝" */
    0x7, 0x81, 0xe1, 0xe5, 0xfe, 0x9c, 0xe, 0x80,
    0x6, 0x0, 0x18, 0x0, 0x60, 0x1, 0x80, 0x5,
    0xc0, 0xe5, 0xfe, 0x9c, 0xe, 0x7, 0xc0,

    /* U+06DE "۞" */
    0x3, 0x0, 0x12, 0x3, 0xff, 0xc, 0xc, 0x20,
    0x11, 0x8c, 0x6a, 0x49, 0x69, 0x25, 0x63, 0x18,
    0x80, 0x43, 0x87, 0xf, 0xfc, 0x7, 0x0,

    /* U+06DF "۟" */
    0xd7, 0x0,

    /* U+06E0 "۠" */
    0xf7, 0x80,

    /* U+06E1 "ۡ" */
    0xf8,

    /* U+06E2 "ۢ" */
    0x5a, 0x40,

    /* U+06E3 "ۣ" */
    0x1d, 0xf0,

    /* U+06E4 "ۤ" */
    0xf8,

    /* U+06E5 "ۥ" */
    0xfe,

    /* U+06E6 "ۦ" */
    0x8f,

    /* U+06E7 "ۧ" */
    0x4f,

    /* U+06E8 "ۨ" */
    0x37, 0x80,

    /* U+06E9 "۩" */
    0x18, 0x66, 0x81, 0x81, 0xc3, 0x42, 0x42, 0x42,
    0x42, 0x7e,

    /* U+06EA "۪" */
    0xd8,

    /* U+06EB "۫" */
    0x55, 0x0,

    /* U+06EC "۬" */
    0x80,

    /* U+06ED "ۭ" */
    0x7a,

    /* U+06EE "ۮ" */
    0x10, 0xa0, 0x6, 0x8, 0x30, 0x61, 0x78,

    /* U+06EF "ۯ" */
    0x10, 0xc8, 0x30, 0x84, 0x21, 0x8, 0xb8,

    /* U+06F0 "۰" */
    0xf0,

    /* U+06F1 "۱" */
    0xab, 0x55, 0x50,

    /* U+06F2 "۲" */
    0x86, 0x1c, 0xee, 0xc1, 0x4, 0x10, 0x41, 0x0,

    /* U+06F3 "۳" */
    0x89, 0x49, 0x49, 0x76, 0x40, 0x40, 0x60, 0x20,
    0x20, 0x20,

    /* U+06F4 "۴" */
    0xce, 0x50, 0x70, 0x5f, 0x60, 0x20, 0x20, 0x20,
    0x20,

    /* U+06F5 "۵" */
    0x20, 0x60, 0xe3, 0x64, 0x50, 0xe4, 0xc9, 0x92,
    0xd8,

    /* U+06F6 "۶" */
    0x3c, 0x81, 0x9, 0xe1, 0x4, 0x18, 0x20, 0x40,

    /* U+06F7 "۷" */
    0xc3, 0x42, 0x42, 0x66, 0x24, 0x24, 0x24, 0x18,
    0x18, 0x18,

    /* U+06F8 "۸" */
    0x18, 0x18, 0x18, 0x3c, 0x24, 0x24, 0x64, 0x42,
    0x42, 0x42,

    /* U+06F9 "۹" */
    0x72, 0x68, 0x9e, 0x8, 0x20, 0x83, 0x4,

    /* U+06FA "ۺ" */
    0x0, 0x40, 0x1, 0x0, 0xa, 0x0, 0x28, 0x0,
    0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83, 0xba,
    0x8, 0xc, 0x64, 0x1f, 0x10,

    /* U+06FB "ۻ" */
    0x0, 0x20, 0x0, 0x40, 0x0, 0x0, 0x0, 0xe0,
    0x6, 0x70, 0x58, 0x60, 0xa0, 0xc1, 0xfe, 0x82,
    0x1, 0x8c, 0x41, 0xf0, 0x80,

    /* U+06FC "ۼ" */
    0x10, 0x10, 0x0, 0x3c, 0x40, 0x40, 0x64, 0x3c,
    0x60, 0xc0, 0x88, 0x80, 0x40, 0x3f,

    /* U+06FD "۽" */
    0x32, 0x10, 0xff, 0x81, 0x4a,

    /* U+06FE "۾" */
    0x39, 0x30, 0x41, 0xfa, 0xa, 0xaa, 0x82, 0x0,

    /* U+06FF "ۿ" */
    0x0, 0x6, 0x0, 0x80, 0x3, 0x1, 0xf0, 0x9c,
    0x49, 0x18, 0xff, 0x80,

    /* U+FE70 "ﹰ" */
    0x73, 0x80,

    /* U+FE71 "ﹱ" */
    0x32, 0x1c, 0x0, 0x0, 0x1f,

    /* U+FE72 "ﹲ" */
    0x2e, 0xe0,

    /* U+FE74 "ﹴ" */
    0x3b, 0x80,

    /* U+FE76 "ﹶ" */
    0x1c,

    /* U+FE77 "ﹷ" */
    0x13, 0x0, 0x0, 0x3, 0xc0,

    /* U+FE78 "ﹸ" */
    0x6f, 0x0,

    /* U+FE79 "ﹹ" */
    0x66, 0x48, 0x0, 0x0, 0xf0,

    /* U+FE7A "ﹺ" */
    0x38,

    /* U+FE7B "ﹻ" */
    0xf0, 0xe,

    /* U+FE7C "ﹼ" */
    0xd, 0xe0,

    /* U+FE7D "ﹽ" */
    0x2e, 0xe0, 0x0, 0xf,

    /* U+FE7E "ﹾ" */
    0xdb, 0x0,

    /* U+FE7F "ﹿ" */
    0x63, 0x18, 0x0, 0x0, 0x1f,

    /* U+FE80 "ﺀ" */
    0x32, 0x11, 0xfc, 0x0,

    /* U+FE81 "ﺁ" */
    0xe9, 0x24, 0x92, 0x40,

    /* U+FE82 "ﺂ" */
    0xe0, 0x44, 0x44, 0x44, 0x30,

    /* U+FE83 "ﺃ" */
    0x52, 0x64, 0x92, 0x49, 0x20,

    /* U+FE84 "ﺄ" */
    0x48, 0x8e, 0x4, 0x44, 0x44, 0x43,

    /* U+FE85 "ﺅ" */
    0x30, 0x81, 0x88, 0x39, 0x34, 0x51, 0x3c, 0x10,
    0xbc,

    /* U+FE86 "ﺆ" */
    0x30, 0x40, 0xc1, 0x84, 0x89, 0x12, 0x1f, 0x8,
    0x33, 0xc0,

    /* U+FE87 "ﺇ" */
    0x49, 0x24, 0x92, 0x41, 0x38,

    /* U+FE88 "ﺈ" */
    0x44, 0x44, 0x44, 0x44, 0x30, 0x66, 0x80,

    /* U+FE89 "ﺉ" */
    0xc3, 0xe2, 0x2, 0x11, 0x88, 0xfc, 0x1e, 0x2,
    0x86, 0x3e, 0x0,

    /* U+FE8A "ﺊ" */
    0xc0, 0x40, 0x30, 0x0, 0x8, 0x4, 0x3e, 0x7,
    0x86, 0x3e, 0x0,

    /* U+FE8B "ﺋ" */
    0x71, 0x82, 0x49, 0xc0,

    /* U+FE8C "ﺌ" */
    0x22, 0x1c, 0x2, 0x10, 0x9b,

    /* U+FE8D "ﺍ" */
    0xff, 0x80,

    /* U+FE8E "ﺎ" */
    0x92, 0x49, 0x24, 0x60,

    /* U+FE8F "ﺏ" */
    0x80, 0x70, 0x6, 0x0, 0xc0, 0x1c, 0x6, 0x7f,
    0x80, 0x0, 0x20, 0x4, 0x0,

    /* U+FE90 "ﺐ" */
    0x80, 0x4, 0x1, 0x20, 0x9, 0x0, 0x4c, 0x6,
    0x1f, 0xec, 0x0, 0x0, 0x80, 0x4, 0x0,

    /* U+FE91 "ﺑ" */
    0x64, 0x93, 0x82, 0x40,

    /* U+FE92 "ﺒ" */
    0x21, 0x8, 0x4d, 0x80, 0x84,

    /* U+FE93 "ﺓ" */
    0x50, 0x8, 0xed, 0xc6, 0x2e,

    /* U+FE94 "ﺔ" */
    0x38, 0x0, 0x20, 0xc7, 0x89, 0x12, 0x3c, 0x6,

    /* U+FE95 "ﺕ" */
    0x0, 0x1, 0x40, 0x0, 0x40, 0x38, 0x3, 0x0,
    0x60, 0xe, 0x3, 0x3f, 0xc0,

    /* U+FE96 "ﺖ" */
    0x0, 0x0, 0x70, 0x0, 0x1, 0x0, 0x8, 0x2,
    0x40, 0x12, 0x0, 0x98, 0xc, 0x3f, 0xd8,

    /* U+FE97 "ﺗ" */
    0xf0, 0x62, 0x22, 0x2c,

    /* U+FE98 "ﺘ" */
    0x52, 0x80, 0x42, 0x10, 0x9b,

    /* U+FE99 "ﺙ" */
    0x4, 0x0, 0x0, 0x28, 0x0, 0x8, 0x7, 0x0,
    0x60, 0xc, 0x1, 0xc0, 0x67, 0xf8,

    /* U+FE9A "ﺚ" */
    0x6, 0x0, 0x0, 0x3, 0x80, 0x0, 0x8, 0x0,
    0x40, 0x12, 0x0, 0x90, 0x4, 0xc0, 0x61, 0xfe,
    0xc0,

    /* U+FE9B "ﺛ" */
    0x60, 0xf0, 0x62, 0x22, 0x2c,

    /* U+FE9C "ﺜ" */
    0x22, 0x94, 0x2, 0x10, 0x84, 0xd8,

    /* U+FE9D "ﺝ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x13, 0x20, 0x40, 0x40,
    0x7c,

    /* U+FE9E "ﺞ" */
    0xf0, 0x7, 0x8e, 0x8c, 0x4c, 0x24, 0x4e, 0x21,
    0x0, 0x40, 0x1f, 0x80,

    /* U+FE9F "ﺟ" */
    0x78, 0x3, 0xc1, 0x83, 0xe, 0x0, 0x20, 0x10,

    /* U+FEA0 "ﺠ" */
    0x7c, 0x1, 0xe0, 0x70, 0x64, 0xe0, 0xc1, 0x0,
    0x40,

    /* U+FEA1 "ﺡ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x10, 0x20, 0x40, 0x40,
    0x7c,

    /* U+FEA2 "ﺢ" */
    0xf0, 0x7, 0x8e, 0x8c, 0x4c, 0x24, 0xe, 0x1,
    0x0, 0x40, 0x1f, 0x80,

    /* U+FEA3 "ﺣ" */
    0x78, 0x3, 0xc1, 0x83, 0xe, 0x0,

    /* U+FEA4 "ﺤ" */
    0x7c, 0x1, 0xe0, 0x70, 0x64, 0xe0, 0xc0,

    /* U+FEA5 "ﺥ" */
    0x10, 0x20, 0x7, 0x80, 0xe7, 0x18, 0x60, 0x81,
    0x2, 0x2, 0x3, 0xe0,

    /* U+FEA6 "ﺦ" */
    0x8, 0x4, 0x0, 0x1e, 0x0, 0xf1, 0xd1, 0x89,
    0x84, 0x81, 0xc0, 0x20, 0x8, 0x3, 0xf0,

    /* U+FEA7 "ﺧ" */
    0x8, 0x4, 0x0, 0xf, 0x0, 0x78, 0x30, 0x61,
    0xc0,

    /* U+FEA8 "ﺨ" */
    0x8, 0x2, 0x0, 0x1, 0xf0, 0x7, 0x81, 0xc1,
    0x93, 0x83,

    /* U+FEA9 "ﺩ" */
    0x10, 0x20, 0xc1, 0x86, 0x17, 0x80,

    /* U+FEAA "ﺪ" */
    0x18, 0x8, 0x8, 0xc, 0x84, 0x84, 0x7b,

    /* U+FEAB "ﺫ" */
    0x10, 0x40, 0x4, 0x8, 0x30, 0x61, 0x85, 0xe0,

    /* U+FEAC "ﺬ" */
    0x0, 0x18, 0x0, 0x18, 0x8, 0x8, 0xc, 0x84,
    0x84, 0x7b,

    /* U+FEAD "ﺭ" */
    0x18, 0x42, 0x10, 0x84, 0x5c,

    /* U+FEAE "ﺮ" */
    0x8, 0x10, 0x20, 0x70, 0x82, 0x38, 0x0,

    /* U+FEAF "ﺯ" */
    0x0, 0xc0, 0x30, 0x84, 0x21, 0x8, 0xb8,

    /* U+FEB0 "ﺰ" */
    0x18, 0x0, 0x0, 0x40, 0x81, 0x3, 0x84, 0x11,
    0xc0,

    /* U+FEB1 "ﺱ" */
    0x0, 0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83,
    0xba, 0x8, 0xc, 0x60, 0x1f, 0x0,

    /* U+FEB2 "ﺲ" */
    0x2, 0x44, 0x82, 0x44, 0x82, 0x44, 0x83, 0xbb,
    0x82, 0x0, 0xc6, 0x0, 0x7c, 0x0,

    /* U+FEB3 "ﺳ" */
    0x0, 0x92, 0x49, 0x24, 0x9f, 0xb0,

    /* U+FEB4 "ﺴ" */
    0x24, 0x84, 0x90, 0x92, 0x7d, 0xb0,

    /* U+FEB5 "ﺵ" */
    0x0, 0x40, 0x1, 0x0, 0xa, 0x0, 0x28, 0x0,
    0x4, 0x9, 0x18, 0x24, 0x60, 0x91, 0x83, 0xba,
    0x8, 0xc, 0x60, 0x1f, 0x0,

    /* U+FEB6 "ﺶ" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0xb0, 0x0, 0x0,
    0x2, 0x44, 0x82, 0x44, 0x82, 0x44, 0x83, 0xbb,
    0x82, 0x0, 0xc6, 0x0, 0x7c, 0x0,

    /* U+FEB7 "ﺷ" */
    0x4, 0x2, 0x2, 0x81, 0x40, 0x9, 0x24, 0x92,
    0x49, 0xfb, 0x0,

    /* U+FEB8 "ﺸ" */
    0x4, 0x0, 0x80, 0x28, 0x0, 0x2, 0x48, 0x49,
    0x9, 0x27, 0xdb,

    /* U+FEB9 "ﺹ" */
    0x0, 0x1c, 0x0, 0xce, 0xb, 0xc, 0x14, 0x18,
    0x3f, 0xd0, 0x40, 0x31, 0x80, 0x3e, 0x0,

    /* U+FEBA "ﺺ" */
    0x0, 0x1c, 0x0, 0x66, 0x82, 0xc2, 0x82, 0x82,
    0x83, 0xff, 0x82, 0x0, 0xc6, 0x0, 0x7c, 0x0,

    /* U+FEBB "ﺻ" */
    0x0, 0xe0, 0x33, 0x26, 0x12, 0xc1, 0xdf, 0xe0,

    /* U+FEBC "ﺼ" */
    0x0, 0xe0, 0x19, 0x89, 0x84, 0x58, 0x2d, 0xff,
    0x80,

    /* U+FEBD "ﺽ" */
    0x0, 0x20, 0x0, 0x40, 0x0, 0x0, 0x0, 0xe0,
    0x6, 0x70, 0x58, 0x60, 0xa0, 0xc1, 0xfe, 0x82,
    0x1, 0x8c, 0x1, 0xf0, 0x0,

    /* U+FEBE "ﺾ" */
    0x0, 0x20, 0x0, 0x20, 0x0, 0x0, 0x0, 0x1c,
    0x0, 0x66, 0x82, 0xc2, 0x82, 0x82, 0x83, 0xff,
    0x82, 0x0, 0xc6, 0x0, 0x7c, 0x0,

    /* U+FEBF "ﺿ" */
    0x1, 0x0, 0x10, 0x0, 0x0, 0xe, 0x3, 0x32,
    0x61, 0x2c, 0x1d, 0xfe,

    /* U+FEC0 "ﻀ" */
    0x1, 0x0, 0x8, 0x0, 0x0, 0x1, 0xc0, 0x33,
    0x13, 0x8, 0xb0, 0x5b, 0xff,

    /* U+FEC1 "ﻁ" */
    0x20, 0x10, 0x8, 0x4, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+FEC2 "ﻂ" */
    0x20, 0x8, 0x2, 0x0, 0x80, 0x27, 0xa, 0x63,
    0x8, 0x82, 0xff, 0xc0,

    /* U+FEC3 "ﻃ" */
    0x20, 0x10, 0x8, 0x4, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+FEC4 "ﻄ" */
    0x20, 0x8, 0x2, 0x0, 0x80, 0x27, 0xa, 0x63,
    0x8, 0x82, 0xff, 0xc0,

    /* U+FEC5 "ﻅ" */
    0x20, 0x12, 0x9, 0x4, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+FEC6 "ﻆ" */
    0x20, 0x9, 0x2, 0x40, 0x80, 0x27, 0xa, 0x63,
    0x8, 0x82, 0xff, 0xc0,

    /* U+FEC7 "ﻇ" */
    0x20, 0x12, 0x9, 0x4, 0x2, 0x71, 0x4c, 0xc2,
    0x41, 0xff, 0x0,

    /* U+FEC8 "ﻈ" */
    0x20, 0x9, 0x2, 0x40, 0x80, 0x27, 0xa, 0x63,
    0x8, 0x82, 0xff, 0xc0,

    /* U+FEC9 "ﻉ" */
    0x3c, 0x40, 0x40, 0x64, 0x3c, 0x60, 0xc0, 0x80,
    0x80, 0x40, 0x3f,

    /* U+FECA "ﻊ" */
    0x7c, 0x89, 0xb1, 0xc7, 0x98, 0xe0, 0x40, 0xc0,
    0xfc,

    /* U+FECB "ﻋ" */
    0x3c, 0xc1, 0x2, 0x6, 0x1f, 0xc0,

    /* U+FECC "ﻌ" */
    0x7c, 0x46, 0x24, 0x18, 0xef,

    /* U+FECD "ﻍ" */
    0x10, 0x10, 0x0, 0x3c, 0x40, 0x40, 0x64, 0x3c,
    0x60, 0xc0, 0x80, 0x80, 0x40, 0x3f,

    /* U+FECE "ﻎ" */
    0x10, 0x20, 0x3, 0xe4, 0x4d, 0x8e, 0x3c, 0xc7,
    0x2, 0x6, 0x7, 0xe0,

    /* U+FECF "ﻏ" */
    0x10, 0x20, 0x1, 0xe6, 0x8, 0x10, 0x30, 0xfe,

    /* U+FED0 "ﻐ" */
    0x18, 0x0, 0x0, 0x7c, 0x46, 0x24, 0x18, 0xef,

    /* U+FED1 "ﻑ" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0x68, 0x13, 0x2,
    0x60, 0x7c, 0x1, 0xc0, 0x6f, 0xf0,

    /* U+FED2 "ﻒ" */
    0x0, 0x40, 0x0, 0x0, 0x8, 0xc, 0x81, 0x28,
    0x12, 0x81, 0x2c, 0xc, 0x7f, 0xf0,

    /* U+FED3 "ﻓ" */
    0x10, 0x40, 0xe, 0x4d, 0x13, 0xc1, 0xf, 0xe0,

    /* U+FED4 "ﻔ" */
    0x10, 0x20, 0x1, 0xc6, 0x48, 0x91, 0x14, 0xfe,

    /* U+FED5 "ﻕ" */
    0xa, 0xa, 0x0, 0xe, 0x13, 0x91, 0x91, 0x8f,
    0x81, 0xc2, 0x7c,

    /* U+FED6 "ﻖ" */
    0xa, 0x5, 0x0, 0x1, 0xc1, 0x34, 0x8a, 0x45,
    0x1f, 0x81, 0x61, 0x1f, 0x0,

    /* U+FED7 "ﻗ" */
    0x28, 0xa0, 0xe, 0x4d, 0x13, 0xc1, 0xf, 0xe0,

    /* U+FED8 "ﻘ" */
    0x28, 0x50, 0x1, 0xc6, 0x48, 0x91, 0x14, 0xfe,

    /* U+FED9 "ﻙ" */
    0x0, 0x40, 0x10, 0xc6, 0x11, 0x8c, 0x60, 0x18,
    0x7, 0x1, 0x7f, 0x80,

    /* U+FEDA "ﻚ" */
    0x0, 0x40, 0x4, 0xc, 0x48, 0x44, 0x8c, 0x48,
    0x4, 0x80, 0x4c, 0x4, 0x7f, 0xb0,

    /* U+FEDB "ﻛ" */
    0x0, 0x33, 0x30, 0xc0, 0xc1, 0x82, 0xb, 0xc0,

    /* U+FEDC "ﻜ" */
    0x2, 0xe, 0x18, 0x60, 0x40, 0x20, 0x30, 0x18,
    0xc, 0xf7,

    /* U+FEDD "ﻝ" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0xc1, 0x83,
    0x6, 0xe, 0x37, 0xc0,

    /* U+FEDE "ﻞ" */
    0x2, 0x1, 0x0, 0x80, 0x40, 0x20, 0x12, 0x9,
    0x4, 0x83, 0xc1, 0x31, 0x8f, 0x80,

    /* U+FEDF "ﻟ" */
    0x24, 0x92, 0x49, 0xc0,

    /* U+FEE0 "ﻠ" */
    0x21, 0x8, 0x42, 0x10, 0x84, 0xd8,

    /* U+FEE1 "ﻡ" */
    0x39, 0xb0, 0x41, 0xfa, 0x8, 0x20, 0x82, 0x0,

    /* U+FEE2 "ﻢ" */
    0x1c, 0xa, 0x8, 0x9c, 0x49, 0xdc, 0x2, 0x1,
    0x0, 0x80, 0x40, 0x0,

    /* U+FEE3 "ﻣ" */
    0xc, 0x24, 0x89, 0x1d, 0xc0,

    /* U+FEE4 "ﻤ" */
    0x18, 0x24, 0x24, 0x66, 0xbf,

    /* U+FEE5 "ﻥ" */
    0x10, 0x20, 0xc, 0x18, 0x30, 0x60, 0xe3, 0x7c,

    /* U+FEE6 "ﻦ" */
    0x10, 0x8, 0x0, 0x0, 0x48, 0x24, 0x12, 0xf,
    0x4, 0xc6, 0x3e, 0x0,

    /* U+FEE7 "ﻧ" */
    0xc, 0x32, 0x49, 0xc0,

    /* U+FEE8 "ﻨ" */
    0x21, 0x0, 0x42, 0x10, 0x9b,

    /* U+FEEA "ﻪ" */
    0x8, 0x31, 0xe2, 0x44, 0x8f, 0x1, 0x80,

    /* U+FEEB "ﻫ" */
    0x60, 0x7c, 0x4e, 0x49, 0x31, 0xfe,

    /* U+FEEC "ﻬ" */
    0x18, 0x49, 0x12, 0x4f, 0xe8, 0x99, 0x1c,

    /* U+FEED "ﻭ" */
    0x39, 0x34, 0x51, 0x3c, 0x10, 0xbc,

    /* U+FEEE "ﻮ" */
    0x30, 0x91, 0x22, 0x43, 0xe1, 0x6, 0x78,

    /* U+FEEF "ﻯ" */
    0x3, 0x82, 0x2, 0x11, 0x88, 0xfc, 0x1e, 0x2,
    0x86, 0x3e, 0x0,

    /* U+FEF0 "ﻰ" */
    0x80, 0x40, 0x21, 0xf0, 0x34, 0x31, 0xf0,

    /* U+FEF1 "ﻱ" */
    0x3, 0x82, 0x22, 0x11, 0xc8, 0x7c, 0xf, 0x6,
    0x7c, 0x0, 0xe, 0x0,

    /* U+FEF2 "ﻲ" */
    0x80, 0x40, 0x21, 0xf0, 0x3c, 0x31, 0xf0, 0x0,
    0x38,

    /* U+FEF3 "ﻳ" */
    0x64, 0x93, 0x85, 0xa0,

    /* U+FEF4 "ﻴ" */
    0x21, 0x8, 0x4d, 0x81, 0x4a,

    /* U+FEF5 "ﻵ" */
    0xf4, 0x18, 0x59, 0x34, 0x61, 0xcd, 0x7c,

    /* U+FEF6 "ﻶ" */
    0x90, 0x64, 0x4, 0x44, 0x44, 0x24, 0x24, 0x14,
    0x1c, 0xf3,

    /* U+FEF7 "ﻷ" */
    0x62, 0x8, 0x39, 0x87, 0x16, 0x4d, 0x18, 0x73,
    0x5f,

    /* U+FEF8 "ﻸ" */
    0x60, 0x80, 0x64, 0x84, 0x44, 0x44, 0x24, 0x24,
    0x14, 0x1c, 0xf3,

    /* U+FEF9 "ﻹ" */
    0x6, 0x1c, 0x49, 0x14, 0x21, 0xcd, 0x7c, 0x6,
    0x1c, 0x40,

    /* U+FEFA "ﻺ" */
    0x4, 0x84, 0x44, 0x44, 0x24, 0x24, 0x14, 0x1c,
    0xf3, 0x0, 0x60, 0x70, 0x80,

    /* U+FEFB "ﻻ" */
    0x6, 0x1c, 0x49, 0x14, 0x21, 0xcd, 0x7c,

    /* U+FEFC "ﻼ" */
    0x4, 0x84, 0x44, 0x44, 0x24, 0x24, 0x14, 0x1c,
    0xf3
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 46, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 68, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 91, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 58, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 78, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 13, .adv_w = 78, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 19, .adv_w = 53, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 84, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 51, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 281, .box_w = 17, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 351, .box_w = 21, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 289, .box_w = 17, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 61, .adv_w = 338, .box_w = 21, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 361, .box_w = 21, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 94, .adv_w = 252, .box_w = 14, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 100, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 114, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 128, .adv_w = 193, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 138, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 147, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 156, .adv_w = 97, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 166, .adv_w = 53, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 167, .adv_w = 71, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 170, .adv_w = 196, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 177, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 188, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 190, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 192, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 194, .adv_w = 0, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 197, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 198, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 200, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 202, .adv_w = 0, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 203, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 204, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 206, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 207, .adv_w = 55, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 82, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 145, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 236, .adv_w = 94, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 53, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 244, .adv_w = 53, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 249, .adv_w = 102, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 258, .adv_w = 53, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 263, .adv_w = 165, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 274, .adv_w = 53, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 276, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 289, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 294, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 307, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 321, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 330, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 339, .adv_w = 142, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 351, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 357, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 365, .adv_w = 78, .box_w = 5, .box_h = 8, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 370, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 377, .adv_w = 244, .box_w = 14, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 391, .adv_w = 244, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 412, .adv_w = 258, .box_w = 15, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 427, .adv_w = 258, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 448, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 459, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 470, .adv_w = 131, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 481, .adv_w = 131, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 495, .adv_w = 186, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 511, .adv_w = 186, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 531, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 543, .adv_w = 165, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 555, .adv_w = 165, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 569, .adv_w = 61, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 570, .adv_w = 204, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 584, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 595, .adv_w = 181, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 607, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 619, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 627, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 635, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 639, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 645, .adv_w = 165, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 656, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 668, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 670, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 672, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 674, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 675, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 677, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 678, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 680, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 682, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 683, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 685, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 687, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 688, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 690, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 692, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 693, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 694, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 695, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 696, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 698, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 700, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 702, .adv_w = 65, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 703, .adv_w = 63, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 706, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 714, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 724, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 731, .adv_w = 119, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 737, .adv_w = 111, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 744, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 754, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 764, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 771, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 780, .adv_w = 72, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 781, .adv_w = 72, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 782, .adv_w = 118, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 786, .adv_w = 201, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 795, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 803, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 804, .adv_w = 53, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 810, .adv_w = 53, .box_w = 5, .box_h = 12, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 818, .adv_w = 53, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 825, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 827, .adv_w = 53, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 834, .adv_w = 102, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 844, .adv_w = 102, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 853, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 867, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 880, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 894, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 908, .adv_w = 201, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 924, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 938, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 952, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 966, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 980, .adv_w = 142, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 993, .adv_w = 142, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1006, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1015, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1024, .adv_w = 142, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1037, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1046, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1055, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1064, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1071, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1079, .adv_w = 112, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1090, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1098, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1106, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1115, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1124, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1133, .adv_w = 78, .box_w = 6, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1142, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1149, .adv_w = 78, .box_w = 5, .box_h = 9, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1155, .adv_w = 77, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1162, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1169, .adv_w = 78, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1178, .adv_w = 78, .box_w = 6, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1186, .adv_w = 78, .box_w = 6, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1195, .adv_w = 78, .box_w = 6, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1204, .adv_w = 244, .box_w = 14, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1222, .adv_w = 244, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1238, .adv_w = 244, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1261, .adv_w = 258, .box_w = 15, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1276, .adv_w = 258, .box_w = 15, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1299, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1310, .adv_w = 131, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1326, .adv_w = 204, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1336, .adv_w = 204, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1350, .adv_w = 204, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1368, .adv_w = 204, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1385, .adv_w = 204, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1401, .adv_w = 204, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1418, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1429, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1442, .adv_w = 186, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1456, .adv_w = 225, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1469, .adv_w = 186, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1483, .adv_w = 181, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1495, .adv_w = 181, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1508, .adv_w = 181, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1525, .adv_w = 186, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1542, .adv_w = 186, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1559, .adv_w = 186, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1576, .adv_w = 186, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1597, .adv_w = 186, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1619, .adv_w = 186, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1637, .adv_w = 141, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1652, .adv_w = 141, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1665, .adv_w = 141, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1681, .adv_w = 141, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1695, .adv_w = 139, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1706, .adv_w = 139, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1713, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1723, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1733, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1743, .adv_w = 151, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1750, .adv_w = 142, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1762, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1768, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1772, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1778, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1783, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1789, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1795, .adv_w = 102, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1804, .adv_w = 102, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1813, .adv_w = 102, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1822, .adv_w = 102, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1831, .adv_w = 102, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1840, .adv_w = 102, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1850, .adv_w = 165, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1861, .adv_w = 165, .box_w = 11, .box_h = 9, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1874, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1886, .adv_w = 102, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1895, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1908, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1921, .adv_w = 196, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1930, .adv_w = 196, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1943, .adv_w = 75, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1944, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1948, .adv_w = 0, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1952, .adv_w = 0, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1956, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1957, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1959, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1961, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1963, .adv_w = 0, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1966, .adv_w = 263, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1989, .adv_w = 229, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2012, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2014, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2016, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2017, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 2019, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2021, .adv_w = 0, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2022, .adv_w = 74, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 2023, .adv_w = 92, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2024, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2025, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2027, .adv_w = 179, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 2037, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2038, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2040, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2041, .adv_w = 0, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2042, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2049, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2056, .adv_w = 65, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 2057, .adv_w = 63, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2060, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2068, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2078, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2087, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2096, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2104, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2114, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2124, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2131, .adv_w = 244, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2152, .adv_w = 258, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2173, .adv_w = 131, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2187, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2192, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2200, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2212, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2214, .adv_w = 61, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2219, .adv_w = 96, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2221, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2223, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2224, .adv_w = 61, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2229, .adv_w = 83, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2231, .adv_w = 61, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2236, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2237, .adv_w = 61, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2239, .adv_w = 84, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2241, .adv_w = 61, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2245, .adv_w = 74, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 2247, .adv_w = 61, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2252, .adv_w = 94, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2256, .adv_w = 53, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2260, .adv_w = 60, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2265, .adv_w = 53, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2270, .adv_w = 60, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2276, .adv_w = 102, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2285, .adv_w = 104, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2295, .adv_w = 53, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2300, .adv_w = 60, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2307, .adv_w = 165, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2318, .adv_w = 153, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2329, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2333, .adv_w = 68, .box_w = 5, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2338, .adv_w = 53, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2340, .adv_w = 60, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2344, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2357, .adv_w = 209, .box_w = 13, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2372, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2376, .adv_w = 68, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2381, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2386, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2394, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2407, .adv_w = 209, .box_w = 13, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2422, .adv_w = 57, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2426, .adv_w = 68, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2431, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2445, .adv_w = 209, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2462, .adv_w = 57, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2467, .adv_w = 68, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2473, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2482, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2494, .adv_w = 145, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2502, .adv_w = 156, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2511, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2520, .adv_w = 143, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2532, .adv_w = 145, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2538, .adv_w = 156, .box_w = 10, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2545, .adv_w = 142, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2557, .adv_w = 143, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2572, .adv_w = 145, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2581, .adv_w = 156, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2591, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2597, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2604, .adv_w = 110, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2612, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2622, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2627, .adv_w = 91, .box_w = 7, .box_h = 7, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2634, .adv_w = 78, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2641, .adv_w = 91, .box_w = 7, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2650, .adv_w = 244, .box_w = 14, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2664, .adv_w = 256, .box_w = 16, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2678, .adv_w = 161, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2684, .adv_w = 173, .box_w = 11, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2690, .adv_w = 244, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2711, .adv_w = 256, .box_w = 16, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2733, .adv_w = 161, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2744, .adv_w = 173, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2755, .adv_w = 258, .box_w = 15, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2770, .adv_w = 268, .box_w = 16, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2786, .adv_w = 189, .box_w = 12, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2794, .adv_w = 198, .box_w = 13, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2803, .adv_w = 258, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2824, .adv_w = 268, .box_w = 16, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2846, .adv_w = 189, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2858, .adv_w = 198, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2871, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2882, .adv_w = 177, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2894, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2905, .adv_w = 157, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2917, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2928, .adv_w = 177, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2940, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2951, .adv_w = 157, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2963, .adv_w = 131, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2974, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2983, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2989, .adv_w = 116, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2994, .adv_w = 131, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3008, .adv_w = 124, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3020, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3028, .adv_w = 116, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3036, .adv_w = 204, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3050, .adv_w = 208, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3064, .adv_w = 97, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3072, .adv_w = 105, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3080, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3091, .adv_w = 158, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3104, .adv_w = 97, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3112, .adv_w = 105, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3120, .adv_w = 181, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3132, .adv_w = 188, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3146, .adv_w = 101, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3154, .adv_w = 110, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3164, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3176, .adv_w = 149, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3190, .adv_w = 60, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3194, .adv_w = 68, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3200, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 3208, .adv_w = 150, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 3220, .adv_w = 111, .box_w = 7, .box_h = 5, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 3225, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3230, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3238, .adv_w = 150, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3250, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3254, .adv_w = 68, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3259, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3266, .adv_w = 132, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3272, .adv_w = 102, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3279, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3285, .adv_w = 104, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3292, .adv_w = 165, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3303, .adv_w = 153, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3310, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3322, .adv_w = 153, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3331, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3335, .adv_w = 68, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3340, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3347, .adv_w = 129, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3357, .adv_w = 121, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3366, .adv_w = 129, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3377, .adv_w = 121, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3387, .adv_w = 129, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3400, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3407, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x1, 0x2, 0x7, 0x8, 0x9, 0xe, 0xf,
    0x1a
};

static const uint8_t glyph_id_ofs_list_3[] = {
    0, 1, 2, 0, 3
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 27, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 9, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 1536, .range_length = 29, .glyph_id_start = 10,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1566, .range_length = 226, .glyph_id_start = 39,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65136, .range_length = 5, .glyph_id_start = 265,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_3, .list_length = 5, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    },
    {
        .range_start = 65142, .range_length = 115, .glyph_id_start = 269,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65258, .range_length = 19, .glyph_id_start = 384,
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
    .cmap_num = 6,
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
const lv_font_t ar_14 = {
#else
lv_font_t ar_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if AR_14*/

