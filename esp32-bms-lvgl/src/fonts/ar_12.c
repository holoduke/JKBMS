/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --font /tmp/NotoArabic.ttf --size 12 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x600-0x6FF,0xFE70-0xFEFF -o src/fonts/ar_12.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef AR_12
#define AR_12 1
#endif

#if AR_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd, 0x80,

    /* U+002C "," */
    0x58,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xc0,

    /* U+0030 "0" */
    0x76, 0xe3, 0x18, 0xc6, 0x33, 0x70,

    /* U+0031 "1" */
    0x2e, 0x92, 0x49, 0x20,

    /* U+0032 "2" */
    0x66, 0xc2, 0x11, 0x19, 0x90, 0xf8,

    /* U+0033 "3" */
    0x76, 0xc2, 0x36, 0xc, 0x21, 0xf0,

    /* U+0034 "4" */
    0x8, 0x30, 0x61, 0x46, 0x89, 0x3f, 0x84, 0x8,

    /* U+0035 "5" */
    0xff, 0xe1, 0xf, 0x84, 0x21, 0xf0,

    /* U+0036 "6" */
    0x1b, 0x21, 0xf, 0xc6, 0x31, 0x70,

    /* U+0037 "7" */
    0xff, 0xf0, 0x42, 0x8, 0x61, 0xc, 0x20,

    /* U+0038 "8" */
    0x66, 0xe3, 0xb7, 0x6e, 0x31, 0xf8,

    /* U+0039 "9" */
    0x66, 0xe3, 0x19, 0xb4, 0x23, 0xf0,

    /* U+003A ":" */
    0xc6,

    /* U+0600 "؀" */
    0x0, 0x30, 0x1, 0x3f, 0xfe,

    /* U+0601 "؁" */
    0x20, 0x0, 0xdf, 0xff, 0xc0, 0x1,

    /* U+0602 "؂" */
    0xe0, 0x5, 0x0, 0x3f, 0xfe,

    /* U+0603 "؃" */
    0x0, 0x6, 0x0, 0x57, 0xff, 0xf0,

    /* U+0604 "؄" */
    0x0, 0x0, 0x3, 0x0, 0x0, 0x9, 0x0, 0x3,
    0x9, 0x0, 0x4, 0x99, 0x0, 0x4, 0x7e, 0x7f,
    0xfe, 0x0, 0x80, 0x2, 0x0,

    /* U+0605 "؅" */
    0x70, 0x5, 0x3f, 0xe0,

    /* U+0606 "؆" */
    0x9d, 0xb9, 0x43, 0x32, 0x85, 0xc, 0x8, 0x0,

    /* U+0607 "؇" */
    0x91, 0x41, 0xc2, 0x36, 0x85, 0xc, 0x8, 0x0,

    /* U+0608 "؈" */
    0x0, 0xc, 0x7, 0x10, 0x22, 0x58, 0x89, 0xe1,
    0xf8, 0x80, 0x83, 0x4, 0x7, 0xe0,

    /* U+0609 "؉" */
    0xd0, 0x20, 0x81, 0x4, 0x8, 0x25, 0x4a,

    /* U+060A "؊" */
    0xd0, 0x8, 0x8, 0x4, 0x4, 0x2, 0x2, 0x51,
    0x2b,

    /* U+060B "؋" */
    0x20, 0x0, 0x64, 0xa5, 0xe3, 0xf0, 0x8, 0x40,

    /* U+060C "،" */
    0x2c,

    /* U+060D "؍" */
    0x22, 0x4c,

    /* U+060E "؎" */
    0x60, 0x24, 0x9, 0x5, 0xff,

    /* U+060F "؏" */
    0x71, 0x2, 0x7, 0xc6, 0x18, 0x27, 0x71, 0xc3,
    0x8f, 0xf0,

    /* U+0610 "ؐ" */
    0x6e, 0x80,

    /* U+0611 "ؑ" */
    0x3e, 0x0,

    /* U+0612 "ؒ" */
    0xd5, 0xa0,

    /* U+0613 "ؓ" */
    0x7f, 0x66,

    /* U+0614 "ؔ" */
    0x17, 0xc0,

    /* U+0615 "ؕ" */
    0x46, 0xe0,

    /* U+0616 "ؖ" */
    0x31, 0x94, 0xf0,

    /* U+0617 "ؗ" */
    0x57,

    /* U+0618 "ؘ" */
    0xc0,

    /* U+0619 "ؙ" */
    0xf8,

    /* U+061A "ؚ" */
    0x40,

    /* U+061B "؛" */
    0x5c, 0x3c,

    /* U+061C "؜" */
    0x0,

    /* U+061E "؞" */
    0x43, 0x80,

    /* U+061F "؟" */
    0x7c, 0x20, 0x82, 0x18, 0x6, 0x30,

    /* U+0620 "ؠ" */
    0x7, 0xc, 0x8, 0x86, 0x81, 0xc2, 0x7c, 0x0,
    0x10, 0x18,

    /* U+0621 "ء" */
    0x68, 0x87, 0xc0,

    /* U+0622 "آ" */
    0x70, 0x22, 0x22, 0x22, 0x22,

    /* U+0623 "أ" */
    0xec, 0x55, 0x55,

    /* U+0624 "ؤ" */
    0x68, 0x60, 0x6, 0x99, 0xf3, 0xe8,

    /* U+0625 "إ" */
    0x49, 0x24, 0x92, 0xa, 0x30,

    /* U+0626 "ئ" */
    0x60, 0x47, 0x6c, 0x8, 0xcc, 0x83, 0x81, 0xc2,
    0x7c,

    /* U+0627 "ا" */
    0xff,

    /* U+0628 "ب" */
    0x0, 0x70, 0x6, 0x0, 0xe0, 0x37, 0xf8, 0x0,
    0x1, 0x80,

    /* U+0629 "ة" */
    0x50, 0x46, 0xf9, 0x96,

    /* U+062A "ت" */
    0xe, 0x0, 0xe, 0x0, 0xc0, 0x1c, 0x6, 0xff,
    0x0,

    /* U+062B "ث" */
    0x6, 0x0, 0x0, 0x38, 0x0, 0x38, 0x3, 0x0,
    0x70, 0x1b, 0xfc,

    /* U+062C "ج" */
    0xf0, 0x1c, 0xe3, 0xc, 0x10, 0x22, 0x40, 0x40,
    0x7c,

    /* U+062D "ح" */
    0xf0, 0x1c, 0xe3, 0xc, 0x10, 0x20, 0x40, 0x40,
    0x7c,

    /* U+062E "خ" */
    0x10, 0x3, 0xc0, 0x73, 0x8c, 0x30, 0x40, 0x81,
    0x1, 0x1, 0xf0,

    /* U+062F "د" */
    0x10, 0x86, 0x10, 0xf8,

    /* U+0630 "ذ" */
    0x20, 0x4, 0x21, 0x84, 0x3e,

    /* U+0631 "ر" */
    0x31, 0x11, 0x2e, 0x80,

    /* U+0632 "ز" */
    0x20, 0x3, 0x11, 0x12, 0xc0,

    /* U+0633 "س" */
    0x0, 0xc, 0x0, 0x10, 0x22, 0x60, 0x99, 0x83,
    0xfa, 0x8, 0xc, 0x60, 0x1f, 0x0,

    /* U+0634 "ش" */
    0x0, 0x60, 0x1, 0xc0, 0x0, 0x0, 0x3, 0x2,
    0x24, 0x8, 0x98, 0x26, 0x60, 0xfe, 0x82, 0x3,
    0x18, 0x7, 0xc0, 0x0,

    /* U+0635 "ص" */
    0x0, 0x1c, 0x4, 0x46, 0x9, 0xc, 0x1e, 0x38,
    0x3f, 0x90, 0x40, 0x31, 0x80, 0x1e, 0x0,

    /* U+0636 "ض" */
    0x0, 0xc, 0x0, 0x0, 0x0, 0x70, 0x11, 0x18,
    0x24, 0x30, 0x78, 0xe0, 0xfe, 0x41, 0x0, 0xc6,
    0x0, 0x78, 0x0,

    /* U+0637 "ط" */
    0x20, 0x10, 0x8, 0x4, 0x2, 0x71, 0xc4, 0xc2,
    0x43, 0xfe, 0x0,

    /* U+0638 "ظ" */
    0x20, 0x10, 0x9, 0x4, 0x2, 0x71, 0xc4, 0xc2,
    0x43, 0xfe, 0x0,

    /* U+0639 "ع" */
    0x71, 0x2, 0x7, 0xc6, 0x18, 0x20, 0x40, 0x81,
    0x80, 0xf0,

    /* U+063A "غ" */
    0x30, 0x1, 0xc4, 0x8, 0x1f, 0x18, 0x60, 0x81,
    0x2, 0x6, 0x3, 0xc0,

    /* U+063B "ػ" */
    0x0, 0xc0, 0x50, 0x1c, 0x1c, 0x6, 0x0, 0xc8,
    0x12, 0x2, 0xc0, 0x9f, 0xc0,

    /* U+063C "ؼ" */
    0x0, 0x0, 0x70, 0x30, 0x18, 0x3, 0x20, 0x48,
    0xb, 0x2, 0x7f, 0x0, 0x1, 0xc0, 0x0, 0xc,
    0x0,

    /* U+063D "ؽ" */
    0x0, 0x67, 0xc, 0x8, 0x8c, 0x83, 0x81, 0xc2,
    0x7c,

    /* U+063E "ؾ" */
    0x7, 0x5c, 0x8, 0x8c, 0x83, 0x81, 0xc2, 0x7c,

    /* U+063F "ؿ" */
    0x20, 0x7, 0x5c, 0x8, 0x8c, 0x83, 0x81, 0xc2,
    0x7c,

    /* U+0640 "ـ" */
    0xf0,

    /* U+0641 "ف" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0x60, 0x13, 0x2,
    0x60, 0x7e, 0x1, 0x7f, 0xc0,

    /* U+0642 "ق" */
    0x7, 0x0, 0x0, 0x0, 0x60, 0x4e, 0x26, 0x1f,
    0x1, 0xc1, 0x3f, 0x0,

    /* U+0643 "ك" */
    0x0, 0x80, 0x41, 0x21, 0x10, 0x4c, 0x66, 0x3,
    0x83, 0x7f, 0x0,

    /* U+0644 "ل" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x60, 0xc1, 0x83,
    0x89, 0xe0,

    /* U+0645 "م" */
    0x79, 0x20, 0x9e, 0x82, 0x8, 0x20, 0x80,

    /* U+0646 "ن" */
    0x18, 0x0, 0x10, 0x18, 0x30, 0x60, 0xe2, 0x78,

    /* U+0647 "ه" */
    0x46, 0x79, 0x96,

    /* U+0648 "و" */
    0x69, 0x9f, 0x3e, 0x80,

    /* U+0649 "ى" */
    0x7, 0xc, 0x8, 0x8c, 0x83, 0x81, 0xc2, 0x7c,

    /* U+064A "ي" */
    0x7, 0xc, 0x8, 0x86, 0x81, 0xc2, 0x7c, 0x0,
    0x0, 0x14,

    /* U+064B "ً" */
    0x77, 0x0,

    /* U+064C "ٌ" */
    0x3f, 0x74,

    /* U+064D "ٍ" */
    0xfc,

    /* U+064E "َ" */
    0x38,

    /* U+064F "ُ" */
    0x6f, 0x0,

    /* U+0650 "ِ" */
    0xc0,

    /* U+0651 "ّ" */
    0x5c,

    /* U+0652 "ْ" */
    0xfc,

    /* U+0653 "ٓ" */
    0xf0,

    /* U+0654 "ٔ" */
    0xec,

    /* U+0655 "ٕ" */
    0xec,

    /* U+0656 "ٖ" */
    0xc0,

    /* U+0657 "ٗ" */
    0x7b, 0x0,

    /* U+0658 "٘" */
    0x2c,

    /* U+0659 "ٙ" */
    0xe0,

    /* U+065A "ٚ" */
    0xa8,

    /* U+065B "ٛ" */
    0x54,

    /* U+065C "ٜ" */
    0x80,

    /* U+065D "ٝ" */
    0xd9, 0x80,

    /* U+065E "ٞ" */
    0x6a, 0x80,

    /* U+065F "ٟ" */
    0x6b, 0x80,

    /* U+0660 "٠" */
    0x30,

    /* U+0661 "١" */
    0xaf, 0x55,

    /* U+0662 "٢" */
    0x4, 0x7d, 0x8c, 0x21, 0x8, 0x0,

    /* U+0663 "٣" */
    0x96, 0x5f, 0xd0, 0x41, 0x4, 0x10,

    /* U+0664 "٤" */
    0x66, 0x21, 0xc4, 0x42, 0xf,

    /* U+0665 "٥" */
    0x76, 0xe3, 0x18, 0xb8,

    /* U+0666 "٦" */
    0xf0, 0x84, 0x21, 0x8, 0x21,

    /* U+0667 "٧" */
    0xc6, 0x89, 0x11, 0x62, 0x85, 0xc, 0x8,

    /* U+0668 "٨" */
    0x10, 0x30, 0xa1, 0x42, 0xc8, 0x91, 0x63,

    /* U+0669 "٩" */
    0x74, 0xa4, 0xf1, 0x84, 0x21,

    /* U+066A "٪" */
    0xd1, 0x22, 0x44, 0x99,

    /* U+066B "٫" */
    0xd8,

    /* U+066C "٬" */
    0x6c,

    /* U+066D "٭" */
    0x0, 0xc7, 0x8c, 0x48,

    /* U+066E "ٮ" */
    0x0, 0x70, 0x6, 0x0, 0xe0, 0x37, 0xf8,

    /* U+066F "ٯ" */
    0x3, 0x2, 0x71, 0x30, 0xf8, 0xe, 0x9, 0xf8,

    /* U+0670 "ٰ" */
    0xc0,

    /* U+0671 "ٱ" */
    0x6e, 0x4, 0x44, 0x44, 0x44, 0x40,

    /* U+0672 "ٲ" */
    0x6b, 0xb4, 0x92, 0x49, 0x20,

    /* U+0673 "ٳ" */
    0x22, 0x22, 0x22, 0x22, 0x2, 0xf6,

    /* U+0674 "ٴ" */
    0xec,

    /* U+0675 "ٵ" */
    0x24, 0xb8, 0x88, 0x88, 0x88,

    /* U+0676 "ٶ" */
    0x11, 0x6, 0x6, 0x4a, 0x5e, 0x17, 0x20,

    /* U+0677 "ٷ" */
    0x69, 0xac, 0x80, 0x31, 0x24, 0x9e, 0x9, 0xc4,
    0x0,

    /* U+0678 "ٸ" */
    0x0, 0x80, 0x40, 0x8, 0x0, 0x7, 0x3, 0x0,
    0x82, 0x30, 0x83, 0x20, 0x4c, 0x21, 0xf0,

    /* U+0679 "ٹ" */
    0x8, 0x1, 0xc0, 0x78, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1c, 0x1, 0x80, 0x38, 0xd, 0xfe, 0x0,

    /* U+067A "ٺ" */
    0x6, 0x0, 0x0, 0x18, 0x0, 0x38, 0x3, 0x0,
    0x70, 0x1b, 0xfc,

    /* U+067B "ٻ" */
    0x0, 0x70, 0x6, 0x0, 0xe0, 0x37, 0xf8, 0x0,
    0x1, 0x80, 0x0, 0x6, 0x0,

    /* U+067C "ټ" */
    0xe, 0x0, 0xe, 0x0, 0xc0, 0x1c, 0x6, 0xff,
    0x1, 0x80, 0x30,

    /* U+067D "ٽ" */
    0xe, 0x0, 0x0, 0x18, 0x0, 0x38, 0x3, 0x0,
    0x70, 0x1b, 0xfc,

    /* U+067E "پ" */
    0x0, 0x70, 0x6, 0x0, 0xe0, 0x37, 0xf8, 0x0,
    0x3, 0x80, 0x0, 0x4, 0x0,

    /* U+067F "ٿ" */
    0xe, 0x0, 0x0, 0x38, 0x0, 0x38, 0x3, 0x0,
    0x70, 0x1b, 0xfc,

    /* U+0680 "ڀ" */
    0x0, 0x70, 0x6, 0x0, 0xe0, 0x37, 0xf8, 0x0,
    0x3, 0x80, 0x0, 0xe, 0x0,

    /* U+0681 "ځ" */
    0x10, 0x40, 0x40, 0xf, 0x1, 0xce, 0x30, 0xc1,
    0x2, 0x4, 0x4, 0x7, 0xc0,

    /* U+0682 "ڂ" */
    0x10, 0x0, 0x40, 0xf, 0x1, 0xce, 0x30, 0xc1,
    0x2, 0x4, 0x4, 0x7, 0xc0,

    /* U+0683 "ڃ" */
    0xf0, 0x1c, 0xc2, 0x8, 0x13, 0xa0, 0x60, 0x3e,

    /* U+0684 "ڄ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x11, 0x22, 0x40, 0x40,
    0x7c,

    /* U+0685 "څ" */
    0x10, 0x0, 0xe0, 0xf, 0x1, 0xce, 0x30, 0xc1,
    0x2, 0x4, 0x4, 0x7, 0xc0,

    /* U+0686 "چ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x12, 0xa2, 0x40, 0x42,
    0x7c,

    /* U+0687 "ڇ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x13, 0xa7, 0x40, 0x40,
    0x7c,

    /* U+0688 "ڈ" */
    0x43, 0xbc, 0x0, 0x0, 0x2, 0x10, 0xc2, 0x1f,
    0x0,

    /* U+0689 "ډ" */
    0x10, 0x86, 0x10, 0xf9, 0x44,

    /* U+068A "ڊ" */
    0x10, 0x86, 0x10, 0xf8, 0x4,

    /* U+068B "ڋ" */
    0x43, 0xbc, 0x0, 0x0, 0x2, 0x10, 0xc2, 0x1f,
    0x1, 0x0,

    /* U+068C "ڌ" */
    0x50, 0x4, 0x21, 0x84, 0x3e,

    /* U+068D "ڍ" */
    0x10, 0x86, 0x10, 0xf8, 0xe,

    /* U+068E "ڎ" */
    0x22, 0x80, 0x21, 0xc, 0x21, 0xf0,

    /* U+068F "ڏ" */
    0x51, 0x0, 0x21, 0xc, 0x21, 0xf0,

    /* U+0690 "ڐ" */
    0x50, 0x14, 0x1, 0x8, 0x61, 0xf, 0x80,

    /* U+0691 "ڑ" */
    0x21, 0x9c, 0x0, 0x0, 0x2, 0x10, 0x84, 0x66,
    0x0,

    /* U+0692 "ڒ" */
    0x52, 0x0, 0x31, 0x11, 0x2e, 0x80,

    /* U+0693 "ړ" */
    0x0, 0x84, 0x23, 0x3a, 0x40,

    /* U+0694 "ڔ" */
    0x1, 0x11, 0x36, 0xc0, 0x40,

    /* U+0695 "ڕ" */
    0x31, 0x11, 0x2e, 0x83, 0x20,

    /* U+0696 "ږ" */
    0x21, 0x1d, 0x36, 0x80, 0x40,

    /* U+0697 "ڗ" */
    0x70, 0x3, 0x11, 0x12, 0xc0,

    /* U+0698 "ژ" */
    0x20, 0x50, 0x3, 0x11, 0x12, 0xc0,

    /* U+0699 "ڙ" */
    0x55, 0x0, 0x31, 0x11, 0x2c,

    /* U+069A "ښ" */
    0x0, 0x60, 0x0, 0x0, 0x0, 0xc0, 0x89, 0x2,
    0x26, 0x9, 0x98, 0x3f, 0xa0, 0x80, 0xc6, 0x21,
    0xf0, 0x0,

    /* U+069B "ڛ" */
    0x0, 0xc, 0x0, 0x10, 0x22, 0x60, 0x99, 0x83,
    0xfa, 0x8, 0xc, 0x65, 0x1f, 0x0, 0x0, 0x20,

    /* U+069C "ڜ" */
    0x0, 0x60, 0x1, 0xc0, 0x0, 0x0, 0x3, 0x2,
    0x24, 0x8, 0x98, 0x26, 0x60, 0xfe, 0x82, 0x3,
    0x19, 0x47, 0xc0, 0x0, 0x8,

    /* U+069D "ڝ" */
    0x0, 0x1c, 0x4, 0x46, 0x9, 0xc, 0x1e, 0x38,
    0x3f, 0x90, 0x40, 0x31, 0x80, 0x1e, 0x1c,

    /* U+069E "ڞ" */
    0x0, 0xc, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0,
    0x1, 0xc0, 0x44, 0x60, 0x90, 0xc1, 0xe3, 0x83,
    0xf9, 0x4, 0x3, 0x18, 0x1, 0xe0, 0x0,

    /* U+069F "ڟ" */
    0x24, 0x10, 0xa, 0x84, 0x2, 0x71, 0xc4, 0xc2,
    0x43, 0xfe, 0x0,

    /* U+06A0 "ڠ" */
    0x30, 0x0, 0xe0, 0x7, 0x10, 0x20, 0x7c, 0x61,
    0x82, 0x4, 0x8, 0x18, 0xf, 0x0,

    /* U+06A1 "ڡ" */
    0x0, 0xc0, 0x26, 0x4, 0xc0, 0xfc, 0x2, 0xff,
    0x80,

    /* U+06A2 "ڢ" */
    0x0, 0xc0, 0x26, 0x4, 0xc0, 0xfc, 0x2, 0xff,
    0x80, 0x0, 0x20,

    /* U+06A3 "ڣ" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0x60, 0x13, 0x2,
    0x60, 0x7e, 0x1, 0x7f, 0xc0, 0x0, 0x1, 0x0,

    /* U+06A4 "ڤ" */
    0x0, 0x40, 0x1c, 0x0, 0x0, 0x0, 0xc, 0x2,
    0x60, 0x4c, 0xf, 0xc0, 0x2f, 0xf8,

    /* U+06A5 "ڥ" */
    0x0, 0xc0, 0x26, 0x4, 0xc0, 0xfc, 0x2, 0xff,
    0x80, 0x0, 0x6, 0x0, 0xc0,

    /* U+06A6 "ڦ" */
    0x0, 0xe0, 0x1c, 0x0, 0x0, 0x0, 0xc, 0x2,
    0x60, 0x4c, 0xf, 0xc0, 0x2f, 0xf8,

    /* U+06A7 "ڧ" */
    0x2, 0x0, 0x0, 0x0, 0x60, 0x4e, 0x26, 0x1f,
    0x1, 0xc1, 0x3f, 0x0,

    /* U+06A8 "ڨ" */
    0x2, 0x3, 0x80, 0x0, 0x0, 0x30, 0x27, 0x13,
    0xf, 0x80, 0xe0, 0x9f, 0x80,

    /* U+06A9 "ک" */
    0x0, 0x0, 0x70, 0x30, 0x18, 0x3, 0x20, 0x48,
    0xb, 0x2, 0x7f, 0x0,

    /* U+06AA "ڪ" */
    0x1, 0x80, 0x60, 0x8, 0x0, 0xf8, 0x0, 0x60,
    0x2, 0xff, 0xc0,

    /* U+06AB "ګ" */
    0x0, 0x40, 0x38, 0xd, 0x3, 0x60, 0x21, 0x2,
    0x20, 0x26, 0x4, 0x7f, 0x0,

    /* U+06AC "ڬ" */
    0x4, 0x80, 0x41, 0x21, 0x10, 0x4c, 0x66, 0x3,
    0x83, 0x7f, 0x0,

    /* U+06AD "ڭ" */
    0x4, 0x0, 0x2, 0xa0, 0x10, 0x48, 0x44, 0x13,
    0x19, 0x80, 0xe0, 0xdf, 0xc0,

    /* U+06AE "ڮ" */
    0x0, 0x80, 0x41, 0x21, 0x10, 0x4c, 0x66, 0x3,
    0x83, 0x7f, 0x0, 0x7, 0x0, 0x0, 0xc0,

    /* U+06AF "گ" */
    0x0, 0x80, 0xc0, 0xdc, 0xc, 0x6, 0x0, 0xc8,
    0x12, 0x2, 0xc0, 0x9f, 0xc0,

    /* U+06B0 "ڰ" */
    0x0, 0x80, 0x68, 0x37, 0x1, 0xe0, 0x6c, 0x4,
    0x20, 0x44, 0x4, 0xc0, 0x8f, 0xe0,

    /* U+06B1 "ڱ" */
    0x1, 0x0, 0xa0, 0x30, 0x33, 0x3, 0x1, 0x80,
    0x32, 0x4, 0x80, 0xb0, 0x27, 0xf0,

    /* U+06B2 "ڲ" */
    0x0, 0x80, 0xc0, 0xdc, 0xc, 0x6, 0x0, 0xc8,
    0x12, 0x2, 0xc0, 0x9f, 0xc0, 0x0, 0x78,

    /* U+06B3 "ڳ" */
    0x0, 0x80, 0xc0, 0xdc, 0xc, 0x6, 0x0, 0xc8,
    0x12, 0x2, 0xc0, 0x9f, 0xc0, 0x0, 0x30, 0x0,
    0x3, 0x0,

    /* U+06B4 "ڴ" */
    0x2, 0x0, 0x40, 0x28, 0xc, 0xc, 0xc0, 0xc0,
    0x60, 0xc, 0x81, 0x20, 0x2c, 0x9, 0xfc,

    /* U+06B5 "ڵ" */
    0x28, 0x64, 0x48, 0x10, 0x20, 0x40, 0xc1, 0x83,
    0x7, 0x13, 0xc0,

    /* U+06B6 "ڶ" */
    0x2, 0x24, 0x8, 0x10, 0x20, 0x60, 0xc1, 0x83,
    0x89, 0xe0,

    /* U+06B7 "ڷ" */
    0x10, 0x4, 0xe8, 0x10, 0x20, 0x40, 0xc1, 0x83,
    0x7, 0x13, 0xc0,

    /* U+06B8 "ڸ" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x60, 0xc1, 0x83,
    0x89, 0xe0, 0x3, 0x82, 0x0,

    /* U+06B9 "ڹ" */
    0x18, 0x0, 0x10, 0x18, 0x30, 0x60, 0xe2, 0x78,
    0x0, 0x60,

    /* U+06BA "ں" */
    0x0, 0xe, 0xc, 0x18, 0x38, 0x9e, 0x0,

    /* U+06BB "ڻ" */
    0x10, 0x30, 0xe0, 0x20, 0x30, 0x60, 0xc1, 0xc4,
    0xf0,

    /* U+06BC "ڼ" */
    0x18, 0x0, 0x1c, 0x18, 0x30, 0x71, 0xbe, 0x30,
    0x20,

    /* U+06BD "ڽ" */
    0x18, 0x38, 0x0, 0x0, 0x30, 0x60, 0xc1, 0xc4,
    0xf0,

    /* U+06BE "ھ" */
    0x10, 0x18, 0x2e, 0x2a, 0x3b, 0xfe,

    /* U+06BF "ڿ" */
    0x10, 0x3, 0xc0, 0x73, 0x8c, 0x30, 0x4a, 0x89,
    0x1, 0x9, 0xf0,

    /* U+06C0 "ۀ" */
    0x64, 0x60, 0x6, 0x79, 0x96,

    /* U+06C1 "ہ" */
    0x46, 0x79, 0x96,

    /* U+06C2 "ۂ" */
    0x64, 0x60, 0x6, 0x79, 0x96,

    /* U+06C3 "ۃ" */
    0x50, 0x46, 0xf9, 0x96,

    /* U+06C4 "ۄ" */
    0x69, 0x9f, 0xde, 0xc0,

    /* U+06C5 "ۅ" */
    0x69, 0x9f, 0xf6, 0xc0,

    /* U+06C6 "ۆ" */
    0x6, 0x0, 0x69, 0x9f, 0x3e, 0x80,

    /* U+06C7 "ۇ" */
    0x66, 0xc0, 0x6, 0xb9, 0xf3, 0xe8,

    /* U+06C8 "ۈ" */
    0x22, 0x0, 0x69, 0x9f, 0x1e, 0x80,

    /* U+06C9 "ۉ" */
    0x46, 0x0, 0x69, 0x9f, 0x3e, 0x80,

    /* U+06CA "ۊ" */
    0xe0, 0x6, 0x99, 0xf3, 0xe8,

    /* U+06CB "ۋ" */
    0x6e, 0x0, 0x69, 0x9f, 0x3e, 0x80,

    /* U+06CC "ی" */
    0x7, 0xc, 0x8, 0x8c, 0x83, 0x81, 0xc2, 0x7c,

    /* U+06CD "ۍ" */
    0x0, 0xe0, 0x20, 0x4, 0x38, 0xce, 0xc, 0x40,
    0x8c, 0x20, 0xf8,

    /* U+06CE "ێ" */
    0x0, 0x67, 0x2c, 0x8, 0x8c, 0x83, 0x81, 0xc2,
    0x7c,

    /* U+06CF "ۏ" */
    0x60, 0x6, 0x99, 0xf3, 0xe8,

    /* U+06D0 "ې" */
    0x7, 0xc, 0x8, 0x8c, 0x83, 0x81, 0xc2, 0x7c,
    0x0, 0x8, 0x0, 0x8,

    /* U+06D1 "ۑ" */
    0x7, 0xc, 0x8, 0x8c, 0x83, 0x81, 0xc2, 0x7c,
    0x0, 0x1c, 0x0, 0x8,

    /* U+06D2 "ے" */
    0x30, 0xe, 0x4, 0x82, 0x0, 0x80, 0x1f, 0xf0,

    /* U+06D3 "ۓ" */
    0x60, 0x8, 0x1, 0x80, 0x0, 0x1, 0x0, 0x70,
    0x12, 0x6, 0x0, 0xc0, 0xf, 0xf8,

    /* U+06D4 "۔" */
    0x60,

    /* U+06D5 "ە" */
    0x46, 0x79, 0x96,

    /* U+06D6 "ۖ" */
    0x20, 0xa7, 0x98,

    /* U+06D7 "ۗ" */
    0x13, 0x76,

    /* U+06D8 "ۘ" */
    0x74,

    /* U+06D9 "ۙ" */
    0x78,

    /* U+06DA "ۚ" */
    0xcf, 0x70,

    /* U+06DB "ۛ" */
    0x54,

    /* U+06DC "ۜ" */
    0x3d, 0xf8,

    /* U+06DD "۝" */
    0xf, 0xc1, 0xc0, 0xe5, 0xfe, 0x98, 0x6, 0xc0,
    0xe, 0x0, 0x18, 0x0, 0x60, 0x1, 0x80, 0x6,
    0x0, 0x1c, 0x0, 0xd8, 0x6, 0x5f, 0xe9, 0xc0,
    0xe0, 0xfc, 0x0,

    /* U+06DE "۞" */
    0x4, 0x0, 0xa0, 0x3f, 0xc3, 0x14, 0x20, 0xc6,
    0xe6, 0x6e, 0x62, 0x4, 0x31, 0xc3, 0xfc, 0xa,
    0x0, 0x40,

    /* U+06DF "۟" */
    0xd7, 0x0,

    /* U+06E0 "۠" */
    0xd7, 0x0,

    /* U+06E1 "ۡ" */
    0xf0,

    /* U+06E2 "ۢ" */
    0xd8,

    /* U+06E3 "ۣ" */
    0x3d, 0xf8,

    /* U+06E4 "ۤ" */
    0xc0,

    /* U+06E5 "ۥ" */
    0xfc,

    /* U+06E6 "ۦ" */
    0xc, 0xf0,

    /* U+06E7 "ۧ" */
    0xc, 0xf0,

    /* U+06E8 "ۨ" */
    0x57, 0x80,

    /* U+06E9 "۩" */
    0x33, 0x38, 0x73, 0x49, 0x24, 0x92, 0xfc,

    /* U+06EA "۪" */
    0x6c, 0x0,

    /* U+06EB "۫" */
    0x55, 0x0,

    /* U+06EC "۬" */
    0x80,

    /* U+06ED "ۭ" */
    0xd8,

    /* U+06EE "ۮ" */
    0x22, 0x80, 0x21, 0xc, 0x21, 0xf0,

    /* U+06EF "ۯ" */
    0x25, 0x0, 0x31, 0x11, 0x2e, 0x80,

    /* U+06F0 "۰" */
    0x30,

    /* U+06F1 "۱" */
    0xaf, 0x55,

    /* U+06F2 "۲" */
    0x4, 0x7d, 0x8c, 0x21, 0x8, 0x0,

    /* U+06F3 "۳" */
    0x96, 0x5f, 0xd0, 0x41, 0x4, 0x10,

    /* U+06F4 "۴" */
    0xb5, 0x3e, 0x84, 0x21, 0x8,

    /* U+06F5 "۵" */
    0x21, 0x94, 0xb8, 0xc6, 0xbe,

    /* U+06F6 "۶" */
    0x68, 0x8f, 0x64, 0x88,

    /* U+06F7 "۷" */
    0xc6, 0x89, 0x11, 0x62, 0x85, 0xc, 0x8,

    /* U+06F8 "۸" */
    0x10, 0x30, 0xa1, 0x42, 0xc8, 0x91, 0x63,

    /* U+06F9 "۹" */
    0x74, 0xa4, 0xf1, 0x84, 0x21,

    /* U+06FA "ۺ" */
    0x0, 0x60, 0x1, 0xc0, 0x0, 0x0, 0x3, 0x2,
    0x24, 0x8, 0x98, 0x26, 0x60, 0xfe, 0x82, 0x3,
    0x18, 0x87, 0xc0, 0x0,

    /* U+06FB "ۻ" */
    0x0, 0xc, 0x0, 0x0, 0x0, 0x70, 0x11, 0x18,
    0x24, 0x30, 0x78, 0xe0, 0xfe, 0x41, 0x0, 0xc6,
    0x30, 0x78, 0x0,

    /* U+06FC "ۼ" */
    0x30, 0x1, 0xc4, 0x8, 0x1b, 0x1c, 0x20, 0x81,
    0x32, 0x6, 0x3, 0xc0,

    /* U+06FD "۽" */
    0x68, 0x87, 0x86, 0x60,

    /* U+06FE "۾" */
    0x79, 0x20, 0x9e, 0x82, 0xaa, 0xa0, 0x80,

    /* U+06FF "ۿ" */
    0x0, 0x18, 0x28, 0x0, 0x10, 0x18, 0x2e, 0x2a,
    0x3b, 0xfe,

    /* U+FE70 "ﹰ" */
    0x77, 0x0,

    /* U+FE71 "ﹱ" */
    0x2c, 0xe0, 0x0, 0x0, 0xf,

    /* U+FE72 "ﹲ" */
    0x3f, 0x74,

    /* U+FE73 "ﹳ" */
    0x88, 0x8c, 0x70,

    /* U+FE74 "ﹴ" */
    0xfc,

    /* U+FE76 "ﹶ" */
    0x38,

    /* U+FE77 "ﹷ" */
    0x2c, 0x0, 0x0, 0x0, 0xf0,

    /* U+FE78 "ﹸ" */
    0x6f, 0x0,

    /* U+FE79 "ﹹ" */
    0x66, 0xc0, 0x0, 0x0, 0xf,

    /* U+FE7A "ﹺ" */
    0xc0,

    /* U+FE7B "ﹻ" */
    0xf2, 0xc0,

    /* U+FE7C "ﹼ" */
    0x5c,

    /* U+FE7D "ﹽ" */
    0x4e, 0x0, 0x0, 0x0, 0xf0,

    /* U+FE7E "ﹾ" */
    0xfc,

    /* U+FE7F "ﹿ" */
    0x6a, 0x60, 0x0, 0x0, 0xf,

    /* U+FE80 "ﺀ" */
    0x68, 0x87, 0xc0,

    /* U+FE81 "ﺁ" */
    0x70, 0x22, 0x22, 0x22, 0x22,

    /* U+FE82 "ﺂ" */
    0x70, 0x8, 0x42, 0x10, 0x84, 0x21, 0xc0,

    /* U+FE83 "ﺃ" */
    0xec, 0x55, 0x55,

    /* U+FE84 "ﺄ" */
    0xc8, 0xc0, 0x44, 0x44, 0x44, 0x47,

    /* U+FE85 "ﺅ" */
    0x68, 0x60, 0x6, 0x99, 0xf3, 0xe8,

    /* U+FE86 "ﺆ" */
    0x61, 0x6, 0x0, 0x1, 0x89, 0x24, 0xfc, 0xce,
    0x20,

    /* U+FE87 "ﺇ" */
    0x49, 0x24, 0x92, 0xa, 0x30,

    /* U+FE88 "ﺈ" */
    0x92, 0x49, 0x24, 0xe2, 0x4c,

    /* U+FE89 "ﺉ" */
    0x60, 0x47, 0x6c, 0x8, 0xcc, 0x83, 0x81, 0xc2,
    0x7c,

    /* U+FE8A "ﺊ" */
    0x60, 0x20, 0x18, 0x0, 0xc, 0x4, 0x1e, 0x5,
    0x86, 0x7c, 0x0,

    /* U+FE8B "ﺋ" */
    0x51, 0x80, 0xc9, 0x38,

    /* U+FE8C "ﺌ" */
    0x62, 0x18, 0x0, 0x10, 0x9b,

    /* U+FE8D "ﺍ" */
    0xff,

    /* U+FE8E "ﺎ" */
    0x92, 0x49, 0x24, 0xe0,

    /* U+FE8F "ﺏ" */
    0x0, 0x70, 0x6, 0x0, 0xe0, 0x37, 0xf8, 0x0,
    0x1, 0x80,

    /* U+FE90 "ﺐ" */
    0x80, 0x4, 0x1, 0x30, 0x38, 0xfe, 0x30, 0x0,
    0x2, 0x0,

    /* U+FE91 "ﺑ" */
    0x64, 0x9c, 0x10,

    /* U+FE92 "ﺒ" */
    0x1, 0x9, 0xb0, 0x30,

    /* U+FE93 "ﺓ" */
    0x50, 0x46, 0xf9, 0x96,

    /* U+FE94 "ﺔ" */
    0x38, 0x1, 0x4, 0x72, 0x49, 0x1c, 0xc,

    /* U+FE95 "ﺕ" */
    0xe, 0x0, 0xe, 0x0, 0xc0, 0x1c, 0x6, 0xff,
    0x0,

    /* U+FE96 "ﺖ" */
    0xf, 0x0, 0x0, 0x20, 0x1, 0x0, 0x4c, 0xe,
    0x3f, 0x8c,

    /* U+FE97 "ﺗ" */
    0xe1, 0x92, 0x70,

    /* U+FE98 "ﺘ" */
    0x50, 0x8, 0x42, 0x6c,

    /* U+FE99 "ﺙ" */
    0x6, 0x0, 0x0, 0x38, 0x0, 0x38, 0x3, 0x0,
    0x70, 0x1b, 0xfc,

    /* U+FE9A "ﺚ" */
    0x6, 0x0, 0x0, 0x1, 0x80, 0x0, 0x8, 0x0,
    0x40, 0x13, 0x3, 0x8f, 0xe3,

    /* U+FE9B "ﺛ" */
    0x63, 0x86, 0x49, 0xc0,

    /* U+FE9C "ﺜ" */
    0x22, 0x80, 0x42, 0x13, 0x60,

    /* U+FE9D "ﺝ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x10, 0x22, 0x40, 0x40,
    0x7c,

    /* U+FE9E "ﺞ" */
    0xf0, 0x7, 0xf, 0xc, 0x8c, 0x64, 0x1e, 0x61,
    0x0, 0x40, 0x1f, 0x0,

    /* U+FE9F "ﺟ" */
    0x78, 0xc, 0x67, 0x0, 0x2, 0x0,

    /* U+FEA0 "ﺠ" */
    0x78, 0x6, 0x1c, 0xe3, 0x0, 0x10,

    /* U+FEA1 "ﺡ" */
    0xf0, 0x1c, 0xe3, 0xc, 0x10, 0x20, 0x40, 0x40,
    0x7c,

    /* U+FEA2 "ﺢ" */
    0xf0, 0x7, 0xf, 0xc, 0x8c, 0x3c, 0x2, 0x1,
    0x0, 0x40, 0x1f, 0x0,

    /* U+FEA3 "ﺣ" */
    0x78, 0xc, 0x67, 0x0,

    /* U+FEA4 "ﺤ" */
    0x78, 0x6, 0x1c, 0xe3,

    /* U+FEA5 "ﺥ" */
    0x10, 0x3, 0xc0, 0x73, 0x8c, 0x30, 0x40, 0x81,
    0x1, 0x1, 0xf0,

    /* U+FEA6 "ﺦ" */
    0x10, 0x0, 0x0, 0x1e, 0x0, 0xe1, 0xe1, 0x91,
    0x87, 0x80, 0x40, 0x20, 0x8, 0x3, 0xe0,

    /* U+FEA7 "ﺧ" */
    0x60, 0x0, 0x3, 0xc0, 0x63, 0x38, 0x0,

    /* U+FEA8 "ﺨ" */
    0x60, 0x0, 0x0, 0x78, 0x6, 0x1c, 0xe3,

    /* U+FEA9 "ﺩ" */
    0x10, 0x86, 0x10, 0xf8,

    /* U+FEAA "ﺪ" */
    0x10, 0x20, 0x60, 0x40, 0xdf, 0xc0,

    /* U+FEAB "ﺫ" */
    0x20, 0x4, 0x21, 0x84, 0x3e,

    /* U+FEAC "ﺬ" */
    0x20, 0x0, 0x40, 0x81, 0x81, 0x3, 0x7f,

    /* U+FEAD "ﺭ" */
    0x31, 0x11, 0x2e, 0x80,

    /* U+FEAE "ﺮ" */
    0x30, 0x41, 0x7, 0x33, 0x88, 0x0,

    /* U+FEAF "ﺯ" */
    0x20, 0x3, 0x11, 0x12, 0xc0,

    /* U+FEB0 "ﺰ" */
    0x60, 0x0, 0xc, 0x10, 0x41, 0xcc, 0xe2, 0x0,

    /* U+FEB1 "ﺱ" */
    0x0, 0xc, 0x0, 0x10, 0x22, 0x60, 0x99, 0x83,
    0xfa, 0x8, 0xc, 0x60, 0x1f, 0x0,

    /* U+FEB2 "ﺲ" */
    0x0, 0x4, 0x2, 0x24, 0x2, 0x24, 0x83, 0x66,
    0x83, 0xfb, 0x82, 0x0, 0xc2, 0x0, 0x7c, 0x0,

    /* U+FEB3 "ﺳ" */
    0x1, 0x80, 0x59, 0x2c, 0x9f, 0xf0,

    /* U+FEB4 "ﺴ" */
    0x0, 0x82, 0x4c, 0x24, 0xc2, 0x4c, 0xdf, 0xf0,

    /* U+FEB5 "ﺵ" */
    0x0, 0x60, 0x1, 0xc0, 0x0, 0x0, 0x3, 0x2,
    0x24, 0x8, 0x98, 0x26, 0x60, 0xfe, 0x82, 0x3,
    0x18, 0x7, 0xc0, 0x0,

    /* U+FEB6 "ﺶ" */
    0x0, 0x60, 0x0, 0x70, 0x0, 0x0, 0x0, 0x4,
    0x2, 0x24, 0x2, 0x24, 0x83, 0x66, 0x83, 0xfb,
    0x82, 0x0, 0xc2, 0x0, 0x7c, 0x0,

    /* U+FEB7 "ﺷ" */
    0x4, 0x5, 0x0, 0x0, 0x12, 0x4b, 0x25, 0xb3,
    0xfe,

    /* U+FEB8 "ﺸ" */
    0x4, 0x0, 0xa0, 0x0, 0x0, 0x8, 0x26, 0xc2,
    0x4c, 0x24, 0xcd, 0xff,

    /* U+FEB9 "ﺹ" */
    0x0, 0x1c, 0x4, 0x46, 0x9, 0xc, 0x1e, 0x38,
    0x3f, 0x90, 0x40, 0x31, 0x80, 0x1e, 0x0,

    /* U+FEBA "ﺺ" */
    0x0, 0x1c, 0x1, 0x11, 0x0, 0x90, 0x90, 0x78,
    0xc8, 0x3f, 0xfc, 0x10, 0x3, 0x18, 0x0, 0x78,
    0x0,

    /* U+FEBB "ﺻ" */
    0x1, 0xc4, 0x44, 0x90, 0xb6, 0x3d, 0xf8,

    /* U+FEBC "ﺼ" */
    0x1, 0xc1, 0x11, 0x9, 0x8, 0xd8, 0xcd, 0xff,
    0x80,

    /* U+FEBD "ﺽ" */
    0x0, 0xc, 0x0, 0x0, 0x0, 0x70, 0x11, 0x18,
    0x24, 0x30, 0x78, 0xe0, 0xfe, 0x41, 0x0, 0xc6,
    0x0, 0x78, 0x0,

    /* U+FEBE "ﺾ" */
    0x0, 0xc, 0x0, 0x0, 0x0, 0x7, 0x0, 0x44,
    0x40, 0x24, 0x24, 0x1e, 0x32, 0xf, 0xff, 0x4,
    0x0, 0xc6, 0x0, 0x1e, 0x0, 0x0,

    /* U+FEBF "ﺿ" */
    0x1, 0x80, 0x0, 0x7, 0x11, 0x12, 0x42, 0xd8,
    0xf7, 0xe0,

    /* U+FEC0 "ﻀ" */
    0x1, 0x80, 0x0, 0x0, 0x70, 0x44, 0x42, 0x42,
    0x36, 0x33, 0x7f, 0xe0,

    /* U+FEC1 "ﻁ" */
    0x20, 0x10, 0x8, 0x4, 0x2, 0x71, 0xc4, 0xc2,
    0x43, 0xfe, 0x0,

    /* U+FEC2 "ﻂ" */
    0x20, 0x4, 0x0, 0x80, 0x10, 0x2, 0x70, 0x71,
    0xc, 0x21, 0xc, 0xff, 0xe0,

    /* U+FEC3 "ﻃ" */
    0x40, 0x40, 0x40, 0x40, 0x4e, 0x71, 0x61, 0x43,
    0xfc,

    /* U+FEC4 "ﻄ" */
    0x40, 0x10, 0x4, 0x1, 0x0, 0x4e, 0x1c, 0x46,
    0x11, 0xc, 0xff, 0xc0,

    /* U+FEC5 "ﻅ" */
    0x20, 0x10, 0x9, 0x4, 0x2, 0x71, 0xc4, 0xc2,
    0x43, 0xfe, 0x0,

    /* U+FEC6 "ﻆ" */
    0x20, 0x4, 0x0, 0x90, 0x10, 0x2, 0x70, 0x71,
    0xc, 0x21, 0xc, 0xff, 0xe0,

    /* U+FEC7 "ﻇ" */
    0x40, 0x40, 0x4c, 0x40, 0x4e, 0x71, 0x61, 0x43,
    0xfc,

    /* U+FEC8 "ﻈ" */
    0x40, 0x10, 0x4, 0xc1, 0x0, 0x4e, 0x1c, 0x46,
    0x11, 0xc, 0xff, 0xc0,

    /* U+FEC9 "ﻉ" */
    0x71, 0x2, 0x7, 0xc6, 0x18, 0x20, 0x40, 0x81,
    0x80, 0xf0,

    /* U+FECA "ﻊ" */
    0x78, 0x91, 0xa1, 0x87, 0xf8, 0x20, 0x40, 0xc4,
    0xf8,

    /* U+FECB "ﻋ" */
    0x39, 0x4, 0xb, 0xf0,

    /* U+FECC "ﻌ" */
    0x79, 0x11, 0x21, 0x8f, 0xe0,

    /* U+FECD "ﻍ" */
    0x30, 0x1, 0xc4, 0x8, 0x1f, 0x18, 0x60, 0x81,
    0x2, 0x6, 0x3, 0xc0,

    /* U+FECE "ﻎ" */
    0x10, 0x0, 0x3, 0xc4, 0x8d, 0xc, 0x3f, 0xc1,
    0x2, 0x6, 0x27, 0xc0,

    /* U+FECF "ﻏ" */
    0x10, 0x0, 0xe, 0x41, 0x2, 0xfc,

    /* U+FED0 "ﻐ" */
    0x10, 0x0, 0x3, 0xc8, 0x89, 0xc, 0x7f,

    /* U+FED1 "ﻑ" */
    0x0, 0x40, 0x0, 0x0, 0x0, 0x60, 0x13, 0x2,
    0x60, 0x7e, 0x1, 0x7f, 0xc0,

    /* U+FED2 "ﻒ" */
    0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x18, 0x80,
    0x92, 0x2, 0x4c, 0xf, 0x1f, 0xff,

    /* U+FED3 "ﻓ" */
    0x20, 0x0, 0x64, 0xa5, 0xe3, 0xf0,

    /* U+FED4 "ﻔ" */
    0x30, 0x0, 0x1, 0x84, 0x89, 0x1e, 0x7f,

    /* U+FED5 "ﻕ" */
    0x7, 0x0, 0x0, 0x0, 0x60, 0x4e, 0x26, 0x1f,
    0x1, 0xc1, 0x3f, 0x0,

    /* U+FED6 "ﻖ" */
    0x7, 0x0, 0x0, 0x0, 0x3, 0x80, 0x89, 0x11,
    0x21, 0xfc, 0x4, 0xc1, 0xf, 0xc0,

    /* U+FED7 "ﻗ" */
    0x70, 0x0, 0x64, 0xa5, 0xe3, 0xf0,

    /* U+FED8 "ﻘ" */
    0x38, 0x0, 0x1, 0x84, 0x89, 0x1e, 0x7f,

    /* U+FED9 "ﻙ" */
    0x0, 0x80, 0x41, 0x21, 0x10, 0x4c, 0x66, 0x3,
    0x83, 0x7f, 0x0,

    /* U+FEDA "ﻚ" */
    0x0, 0x80, 0x10, 0x12, 0x4, 0x40, 0x49, 0x19,
    0x20, 0x26, 0xc, 0x7f, 0x60,

    /* U+FEDB "ﻛ" */
    0x1b, 0x30, 0x82, 0x8, 0x5c,

    /* U+FEDC "ﻜ" */
    0x19, 0x88, 0x10, 0x20, 0xc1, 0xbb,

    /* U+FEDD "ﻝ" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x60, 0xc1, 0x83,
    0x89, 0xe0,

    /* U+FEDE "ﻞ" */
    0x2, 0x1, 0x0, 0x80, 0x40, 0x20, 0x10, 0x9,
    0x4, 0x83, 0xc1, 0x31, 0xf, 0x0,

    /* U+FEDF "ﻟ" */
    0x55, 0x55, 0x80,

    /* U+FEE0 "ﻠ" */
    0x44, 0x44, 0x44, 0x44, 0xf0,

    /* U+FEE1 "ﻡ" */
    0x79, 0x20, 0x9e, 0x82, 0x8, 0x20, 0x80,

    /* U+FEE2 "ﻢ" */
    0x38, 0xd3, 0x95, 0xf8, 0x10, 0x20, 0x60, 0x0,

    /* U+FEE3 "ﻣ" */
    0x18, 0x96, 0x7f,

    /* U+FEE4 "ﻤ" */
    0x18, 0x28, 0x44, 0x64, 0xff,

    /* U+FEE5 "ﻥ" */
    0x18, 0x0, 0x10, 0x18, 0x30, 0x60, 0xe2, 0x78,

    /* U+FEE6 "ﻦ" */
    0x18, 0x0, 0x0, 0x20, 0x8, 0x83, 0x20, 0xf8,
    0x33, 0x8, 0x7c, 0x0,

    /* U+FEE7 "ﻧ" */
    0x40, 0x12, 0x4e,

    /* U+FEE8 "ﻨ" */
    0x60, 0x8, 0x42, 0x6c,

    /* U+FEE9 "ﻩ" */
    0x46, 0x79, 0x96,

    /* U+FEEA "ﻪ" */
    0x10, 0x47, 0x24, 0x91, 0xc0, 0xc0,

    /* U+FEEB "ﻫ" */
    0x20, 0x61, 0x72, 0xe7, 0x7f, 0x80,

    /* U+FEEC "ﻬ" */
    0x38, 0x51, 0x22, 0xcf, 0xe8, 0x8f, 0x0,

    /* U+FEED "ﻭ" */
    0x69, 0x9f, 0x3e, 0x80,

    /* U+FEEE "ﻮ" */
    0x62, 0x49, 0x3f, 0x33, 0x88, 0x0,

    /* U+FEEF "ﻯ" */
    0x7, 0xc, 0x8, 0x8c, 0x83, 0x81, 0xc2, 0x7c,

    /* U+FEF0 "ﻰ" */
    0x84, 0x41, 0xe0, 0x58, 0x67, 0xc0,

    /* U+FEF1 "ﻱ" */
    0x7, 0xc, 0x8, 0x86, 0x81, 0xc2, 0x7c, 0x0,
    0x0, 0x14,

    /* U+FEF2 "ﻲ" */
    0x84, 0x41, 0xe0, 0x58, 0x67, 0xc0, 0x0, 0x70,

    /* U+FEF3 "ﻳ" */
    0x64, 0x9c, 0x28,

    /* U+FEF4 "ﻴ" */
    0x1, 0x9, 0xb0, 0x38,

    /* U+FEF5 "ﻵ" */
    0xf4, 0x9, 0x11, 0xa1, 0xc1, 0x87, 0x1a, 0x7c,

    /* U+FEF6 "ﻶ" */
    0xf4, 0x4, 0x44, 0x64, 0x34, 0x1c, 0xc, 0xc,
    0x73,

    /* U+FEF7 "ﻷ" */
    0x41, 0x1, 0x90, 0x24, 0x46, 0x87, 0x6, 0x1c,
    0x68, 0xf0,

    /* U+FEF8 "ﻸ" */
    0x40, 0x80, 0x64, 0x4, 0x44, 0x64, 0x34, 0x1c,
    0xc, 0xc, 0x73,

    /* U+FEF9 "ﻹ" */
    0xa, 0x24, 0x8e, 0x18, 0xe6, 0x5e, 0x1, 0x8,
    0x18,

    /* U+FEFA "ﻺ" */
    0x8, 0x12, 0x22, 0x46, 0x87, 0x6, 0xc, 0xe6,
    0x1, 0x4, 0x6, 0x0,

    /* U+FEFB "ﻻ" */
    0xa, 0x2c, 0x8e, 0x18, 0xe6, 0x7e,

    /* U+FEFC "ﻼ" */
    0x8, 0x12, 0x26, 0x46, 0x87, 0x6, 0xc, 0xe6
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 50, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 53, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 52, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 4, .adv_w = 62, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 5, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 110, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 110, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 52, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 219, .box_w = 13, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 261, .box_w = 16, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 79, .adv_w = 211, .box_w = 13, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 84, .adv_w = 254, .box_w = 15, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 412, .box_w = 24, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 111, .adv_w = 236, .box_w = 14, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 115, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 220, .box_w = 14, .box_h = 8, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 145, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 168, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 89, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 169, .adv_w = 63, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 172, .adv_w = 178, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 106, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 187, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 189, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 191, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 193, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 195, .adv_w = 0, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 197, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 199, .adv_w = 0, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 202, .adv_w = 0, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 203, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 204, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 205, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 206, .adv_w = 66, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 115, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 55, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 88, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 227, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 230, .adv_w = 47, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 47, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 89, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 244, .adv_w = 48, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 249, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 258, .adv_w = 48, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 259, .adv_w = 192, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 269, .adv_w = 81, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 192, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 302, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 311, .adv_w = 125, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 322, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 73, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 335, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 340, .adv_w = 241, .box_w = 14, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 354, .adv_w = 241, .box_w = 14, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 374, .adv_w = 257, .box_w = 15, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 389, .adv_w = 257, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 408, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 101, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 440, .adv_w = 101, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 452, .adv_w = 170, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 482, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 491, .adv_w = 149, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 499, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 508, .adv_w = 53, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 191, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 152, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 534, .adv_w = 172, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 555, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 562, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 570, .adv_w = 81, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 577, .adv_w = 149, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 585, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 595, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 597, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 599, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 600, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 601, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 603, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 604, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 605, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 606, .adv_w = 0, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 607, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 608, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 609, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 610, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 612, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 613, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 614, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 615, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 616, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 617, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 619, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 621, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 623, .adv_w = 60, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 624, .adv_w = 57, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 97, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 93, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 104, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 100, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 95, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 48, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 676, .adv_w = 48, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 192, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 152, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 696, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 697, .adv_w = 47, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 47, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 48, .box_w = 4, .box_h = 12, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 714, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 715, .adv_w = 80, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 720, .adv_w = 89, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 727, .adv_w = 115, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 736, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 751, .adv_w = 192, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 767, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 192, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 791, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 802, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 192, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 826, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 192, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 850, .adv_w = 125, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 863, .adv_w = 125, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 876, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 884, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 893, .adv_w = 125, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 906, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 915, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 924, .adv_w = 94, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 938, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 943, .adv_w = 94, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 953, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 963, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 969, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 975, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 982, .adv_w = 77, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 991, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 997, .adv_w = 73, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1002, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1007, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1012, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1017, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1022, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1028, .adv_w = 73, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1033, .adv_w = 241, .box_w = 14, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1051, .adv_w = 241, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1067, .adv_w = 241, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1088, .adv_w = 257, .box_w = 15, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1103, .adv_w = 257, .box_w = 15, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1126, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1137, .adv_w = 101, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1151, .adv_w = 191, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1160, .adv_w = 191, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1171, .adv_w = 191, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1187, .adv_w = 191, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1201, .adv_w = 191, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1214, .adv_w = 191, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1228, .adv_w = 152, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1240, .adv_w = 152, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1253, .adv_w = 170, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1265, .adv_w = 196, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1276, .adv_w = 170, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1289, .adv_w = 172, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1300, .adv_w = 172, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1313, .adv_w = 172, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1328, .adv_w = 170, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1341, .adv_w = 170, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1355, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1369, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1384, .adv_w = 170, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1402, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1417, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1428, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1438, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1449, .adv_w = 136, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1462, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1472, .adv_w = 135, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1479, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1488, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1497, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1506, .adv_w = 135, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1512, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1523, .adv_w = 81, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1528, .adv_w = 81, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1531, .adv_w = 81, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1536, .adv_w = 81, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1540, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1544, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1548, .adv_w = 89, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1554, .adv_w = 89, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1560, .adv_w = 89, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1566, .adv_w = 89, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1572, .adv_w = 89, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1577, .adv_w = 89, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1583, .adv_w = 149, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1591, .adv_w = 176, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1602, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1611, .adv_w = 89, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1616, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -7},
    {.bitmap_index = 1628, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1640, .adv_w = 181, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1648, .adv_w = 181, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1662, .adv_w = 59, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1663, .adv_w = 81, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1666, .adv_w = 0, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 13},
    {.bitmap_index = 1669, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 1671, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 14},
    {.bitmap_index = 1672, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 13},
    {.bitmap_index = 1673, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 1675, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 14},
    {.bitmap_index = 1676, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1678, .adv_w = 263, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1705, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1723, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1725, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1727, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1728, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 13},
    {.bitmap_index = 1729, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1731, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1732, .adv_w = 36, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1733, .adv_w = 67, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1735, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1737, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1739, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1746, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1748, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1750, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1751, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1752, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1758, .adv_w = 73, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1764, .adv_w = 60, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1765, .adv_w = 57, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1767, .adv_w = 97, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1773, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1779, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1784, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1789, .adv_w = 84, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1793, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1800, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1807, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1812, .adv_w = 241, .box_w = 14, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1832, .adv_w = 257, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1851, .adv_w = 101, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1863, .adv_w = 82, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1867, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1874, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1884, .adv_w = 59, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1886, .adv_w = 53, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1891, .adv_w = 74, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1893, .adv_w = 51, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1896, .adv_w = 59, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1897, .adv_w = 59, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1898, .adv_w = 53, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1903, .adv_w = 60, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1905, .adv_w = 53, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1910, .adv_w = 56, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1911, .adv_w = 53, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1913, .adv_w = 62, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1914, .adv_w = 53, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1919, .adv_w = 46, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1920, .adv_w = 53, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1925, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1928, .adv_w = 47, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1933, .adv_w = 57, .box_w = 5, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1940, .adv_w = 47, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1943, .adv_w = 57, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1949, .adv_w = 89, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1955, .adv_w = 94, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1964, .adv_w = 48, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1969, .adv_w = 57, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1974, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1983, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1994, .adv_w = 54, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1998, .adv_w = 68, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2003, .adv_w = 48, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2004, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2008, .adv_w = 192, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2018, .adv_w = 213, .box_w = 13, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2028, .adv_w = 54, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2031, .adv_w = 68, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2035, .adv_w = 81, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2039, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2046, .adv_w = 192, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2055, .adv_w = 213, .box_w = 13, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2065, .adv_w = 61, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2068, .adv_w = 74, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2072, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2083, .adv_w = 213, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2096, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2100, .adv_w = 74, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2105, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2114, .adv_w = 130, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2126, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2132, .adv_w = 123, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2138, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2147, .adv_w = 130, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2159, .adv_w = 115, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2163, .adv_w = 123, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2167, .adv_w = 125, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2178, .adv_w = 130, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2193, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2200, .adv_w = 123, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2207, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2211, .adv_w = 104, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2217, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2222, .adv_w = 104, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2229, .adv_w = 73, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2233, .adv_w = 79, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2239, .adv_w = 73, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2244, .adv_w = 79, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2252, .adv_w = 241, .box_w = 14, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2266, .adv_w = 253, .box_w = 16, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2282, .adv_w = 160, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2288, .adv_w = 173, .box_w = 12, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2296, .adv_w = 241, .box_w = 14, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2316, .adv_w = 253, .box_w = 16, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2338, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2347, .adv_w = 173, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2359, .adv_w = 257, .box_w = 15, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2374, .adv_w = 265, .box_w = 17, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2391, .adv_w = 177, .box_w = 11, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2398, .adv_w = 185, .box_w = 13, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2407, .adv_w = 257, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2426, .adv_w = 265, .box_w = 17, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2448, .adv_w = 177, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2458, .adv_w = 185, .box_w = 13, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2470, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2481, .adv_w = 161, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2494, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2503, .adv_w = 139, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2515, .adv_w = 155, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2526, .adv_w = 161, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2539, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2548, .adv_w = 139, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2560, .adv_w = 101, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2570, .adv_w = 104, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2579, .adv_w = 100, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2583, .adv_w = 102, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2588, .adv_w = 101, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2600, .adv_w = 104, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2612, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2618, .adv_w = 102, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2625, .adv_w = 191, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2638, .adv_w = 212, .box_w = 14, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2652, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2658, .adv_w = 97, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2665, .adv_w = 152, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2677, .adv_w = 158, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2691, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2697, .adv_w = 97, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2704, .adv_w = 172, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2715, .adv_w = 180, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2728, .adv_w = 81, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2733, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2739, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2749, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2763, .adv_w = 52, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2766, .adv_w = 60, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2771, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2778, .adv_w = 113, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2786, .adv_w = 104, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2789, .adv_w = 114, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2794, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2802, .adv_w = 144, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2814, .adv_w = 54, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2817, .adv_w = 68, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2821, .adv_w = 81, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2824, .adv_w = 97, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2830, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2836, .adv_w = 101, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2843, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2847, .adv_w = 94, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2853, .adv_w = 149, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2861, .adv_w = 145, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2867, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2877, .adv_w = 145, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2885, .adv_w = 61, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2888, .adv_w = 74, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2892, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2900, .adv_w = 135, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2909, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2919, .adv_w = 120, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2930, .adv_w = 115, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2939, .adv_w = 120, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2951, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2957, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x1, 0xc, 0xd, 0xe
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 5, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 6,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1536, .range_length = 29, .glyph_id_start = 17,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1566, .range_length = 226, .glyph_id_start = 46,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65136, .range_length = 5, .glyph_id_start = 272,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65142, .range_length = 135, .glyph_id_start = 277,
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
const lv_font_t ar_12 = {
#else
lv_font_t ar_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 24,          /*The maximum line height required by the font*/
    .base_line = 7,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if AR_12*/

