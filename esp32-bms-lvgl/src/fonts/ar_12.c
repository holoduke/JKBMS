/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --font /System/Library/Fonts/SFArabic.ttf --size 12 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x600-0x6FF,0xFE70-0xFEFF -o src/fonts/ar_12.c
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
    0xaa, 0xa0, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x69, 0x49, 0x26, 0x48, 0x80,

    /* U+0029 ")" */
    0x48, 0x92, 0x49, 0x6a, 0x0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x12, 0x22, 0x44, 0x48, 0x80,

    /* U+003A ":" */
    0x84,

    /* U+0600 "؀" */
    0x0, 0x1c, 0x0, 0x40, 0x0, 0x80, 0x1, 0x8f,
    0xff, 0xe0,

    /* U+0601 "؁" */
    0x31, 0x0, 0x12, 0x40, 0x8, 0x6f, 0xfc,

    /* U+0602 "؂" */
    0x60, 0x1, 0x20, 0x2, 0x40, 0x7, 0xff, 0xf0,

    /* U+0603 "؃" */
    0x0, 0x3, 0x0, 0x2, 0x40, 0x12, 0x20, 0xa,
    0x1f, 0xff, 0xf0,

    /* U+0604 "؄" */
    0x0, 0x0, 0x20, 0x6, 0x24, 0x1, 0x24, 0x80,
    0x23, 0x70, 0x6, 0x1, 0xff, 0xe0, 0x0,

    /* U+0605 "؅" */
    0x7f, 0xf8, 0x0, 0x80, 0x0,

    /* U+0606 "؆" */
    0x0, 0x30, 0x84, 0x88, 0x10, 0xd1, 0x24, 0x48,
    0x60, 0xc0,

    /* U+0607 "؇" */
    0x10, 0x22, 0x44, 0x8, 0x68, 0x92, 0x24, 0x30,
    0x60,

    /* U+0608 "؈" */
    0x6, 0x4, 0xb2, 0x49, 0xf4, 0x13, 0x18, 0xf8,

    /* U+0609 "؉" */
    0x8a, 0x21, 0x4, 0x21, 0x4, 0x25,

    /* U+060A "؊" */
    0x8a, 0x21, 0x4, 0x21, 0x4, 0x29,

    /* U+060B "؋" */
    0x1, 0x80, 0x64, 0xa5, 0xe1, 0xf0, 0x8, 0x40,

    /* U+060C "،" */
    0xe0,

    /* U+060D "؍" */
    0x5a, 0x80,

    /* U+060E "؎" */
    0x60, 0x24, 0x9, 0x3, 0xff,

    /* U+060F "؏" */
    0x79, 0x2, 0x7, 0xe7, 0x18, 0x27, 0x71, 0xc3,
    0x78,

    /* U+0610 "ؐ" */
    0x2f, 0x80,

    /* U+0611 "ؑ" */
    0x77, 0x80,

    /* U+0612 "ؒ" */
    0xca, 0x20,

    /* U+0613 "ؓ" */
    0x42, 0xe3,

    /* U+0614 "ؔ" */
    0x1c,

    /* U+0615 "ؕ" */
    0x46, 0xe0,

    /* U+0616 "ؖ" */
    0x33, 0x70,

    /* U+0617 "ؗ" */
    0x4c,

    /* U+0618 "ؘ" */
    0x80,

    /* U+0619 "ؙ" */
    0x78,

    /* U+061A "ؚ" */
    0xc0,

    /* U+061B "؛" */
    0xe2,

    /* U+061C "؜" */
    0x0,

    /* U+061E "؞" */
    0x30, 0x0, 0x0, 0x2, 0x10,

    /* U+061F "؟" */
    0x74, 0x63, 0x6, 0x10, 0x40, 0x20,

    /* U+0620 "ؠ" */
    0x7, 0x8, 0x88, 0x86, 0xc2, 0x7c, 0x30, 0x10,

    /* U+0621 "ء" */
    0x68, 0xcf,

    /* U+0622 "آ" */
    0xe9, 0x24, 0x92,

    /* U+0623 "أ" */
    0x53, 0x24, 0x92, 0x48,

    /* U+0624 "ؤ" */
    0x32, 0xc, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+0625 "إ" */
    0x49, 0x24, 0x92, 0xb, 0x0,

    /* U+0626 "ئ" */
    0xc0, 0x86, 0xc8, 0x90, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+0627 "ا" */
    0xff,

    /* U+0628 "ب" */
    0x80, 0x60, 0x18, 0x7, 0x3, 0x7f, 0x80, 0x0,
    0xc0,

    /* U+0629 "ة" */
    0x6, 0x6, 0xf9, 0x9e,

    /* U+062A "ت" */
    0xc, 0x0, 0x8, 0x6, 0x1, 0x80, 0x70, 0x37,
    0xf8,

    /* U+062B "ث" */
    0x0, 0x0, 0x0, 0xc0, 0x0, 0x80, 0x60, 0x18,
    0x7, 0x3, 0x7f, 0x80,

    /* U+062C "ج" */
    0xe0, 0x73, 0x10, 0x92, 0x48, 0x30, 0x7c,

    /* U+062D "ح" */
    0xe0, 0x73, 0x10, 0x82, 0x8, 0x30, 0x7c,

    /* U+062E "خ" */
    0x0, 0x40, 0x38, 0x1c, 0xc4, 0x20, 0x82, 0xc,
    0x1f,

    /* U+062F "د" */
    0x30, 0x83, 0x18, 0xf8,

    /* U+0630 "ذ" */
    0x30, 0xc, 0x20, 0xc6, 0x3e,

    /* U+0631 "ر" */
    0x31, 0x11, 0x13, 0xe0,

    /* U+0632 "ز" */
    0x30, 0x31, 0x11, 0x13, 0xe0,

    /* U+0633 "س" */
    0x0, 0x18, 0x49, 0x84, 0x98, 0x77, 0x84, 0x7,
    0x80,

    /* U+0634 "ش" */
    0x0, 0x80, 0x8, 0x1, 0x40, 0x1, 0x84, 0x98,
    0x49, 0x87, 0x78, 0x40, 0x78, 0x0,

    /* U+0635 "ص" */
    0x0, 0x70, 0x4, 0x61, 0x43, 0xe, 0x18, 0x7f,
    0x46, 0x1, 0xe0, 0x0,

    /* U+0636 "ض" */
    0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0xe0, 0x8,
    0xc2, 0x86, 0x1c, 0x30, 0xfe, 0x8c, 0x3, 0xc0,
    0x0,

    /* U+0637 "ط" */
    0x20, 0x20, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+0638 "ظ" */
    0x20, 0x24, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+0639 "ع" */
    0x38, 0x81, 0x3, 0x63, 0x88, 0x20, 0x40, 0xc0,
    0x7c,

    /* U+063A "غ" */
    0x0, 0x20, 0x1, 0xc4, 0x8, 0x1b, 0x1c, 0x41,
    0x2, 0x6, 0x3, 0xe0,

    /* U+063B "ػ" */
    0x6, 0x0, 0xc1, 0x81, 0x8, 0x44, 0x12, 0x5,
    0x2, 0x7e, 0x0,

    /* U+063C "ؼ" */
    0x0, 0x0, 0xc1, 0x81, 0x8, 0x44, 0x12, 0x5,
    0x2, 0x7e, 0x0, 0x6, 0x1, 0x0,

    /* U+063D "ؽ" */
    0xc0, 0xc7, 0x8, 0x88, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+063E "ؾ" */
    0x63, 0x82, 0x11, 0x8, 0xe4, 0x1b, 0x8, 0xf8,

    /* U+063F "ؿ" */
    0x0, 0x0, 0x38, 0xe0, 0x84, 0x42, 0x39, 0x6,
    0xc2, 0x3e, 0x0,

    /* U+0640 "ـ" */
    0xe0,

    /* U+0641 "ف" */
    0x0, 0x0, 0x20, 0x0, 0x6, 0x82, 0x60, 0x98,
    0x3f, 0x1, 0x7f, 0x80,

    /* U+0642 "ق" */
    0x0, 0x18, 0x0, 0x61, 0x32, 0x67, 0xe3, 0x7c,

    /* U+0643 "ك" */
    0x1, 0x1, 0x9, 0x89, 0x99, 0x81, 0x81, 0x7e,

    /* U+0644 "ل" */
    0x4, 0x10, 0x41, 0x4, 0x18, 0x61, 0x87, 0x17,
    0x80,

    /* U+0645 "م" */
    0x32, 0x43, 0xf8, 0x42, 0x10, 0x80,

    /* U+0646 "ن" */
    0x0, 0x0, 0x61, 0x86, 0x1c, 0x5e,

    /* U+0647 "ه" */
    0x6f, 0x99, 0xe0,

    /* U+0648 "و" */
    0x32, 0x52, 0xf0, 0x8b, 0x80,

    /* U+0649 "ى" */
    0x7, 0x8, 0x88, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+064A "ي" */
    0x7, 0x8, 0x98, 0x8e, 0x82, 0xc2, 0x7c, 0x8,
    0x8,

    /* U+064B "ً" */
    0x3c,

    /* U+064C "ٌ" */
    0x7f, 0x0,

    /* U+064D "ٍ" */
    0x6c,

    /* U+064E "َ" */
    0xc0,

    /* U+064F "ُ" */
    0x6d, 0x0,

    /* U+0650 "ِ" */
    0xc0,

    /* U+0651 "ّ" */
    0x74,

    /* U+0652 "ْ" */
    0xf0,

    /* U+0653 "ٓ" */
    0xe0,

    /* U+0654 "ٔ" */
    0xec,

    /* U+0655 "ٕ" */
    0xec,

    /* U+0656 "ٖ" */
    0xc0,

    /* U+0657 "ٗ" */
    0x3b, 0x0,

    /* U+0658 "٘" */
    0x98,

    /* U+0659 "ٙ" */
    0xc0,

    /* U+065A "ٚ" */
    0xe0,

    /* U+065B "ٛ" */
    0xb0,

    /* U+065C "ٜ" */
    0x80,

    /* U+065D "ٝ" */
    0xd9, 0x0,

    /* U+065E "ٞ" */
    0xb0,

    /* U+065F "ٟ" */
    0x7c,

    /* U+0660 "٠" */
    0xe0,

    /* U+0661 "١" */
    0xa5, 0x55,

    /* U+0662 "٢" */
    0x45, 0x17, 0x90, 0x41, 0x2, 0x8,

    /* U+0663 "٣" */
    0x93, 0x27, 0xb2, 0x4, 0x8, 0x10, 0x20,

    /* U+0664 "٤" */
    0x7c, 0x87, 0x68, 0x87,

    /* U+0665 "٥" */
    0x76, 0xe3, 0x18, 0xb8,

    /* U+0666 "٦" */
    0xf0, 0x84, 0x21, 0x8, 0x21,

    /* U+0667 "٧" */
    0x44, 0x89, 0x12, 0x42, 0x85, 0xa, 0x8,

    /* U+0668 "٨" */
    0x10, 0x50, 0xa1, 0x44, 0x88, 0x91, 0x22,

    /* U+0669 "٩" */
    0x74, 0xa5, 0xf0, 0x84, 0x21,

    /* U+066A "٪" */
    0x8a, 0x21, 0x4, 0x21, 0x4, 0x23,

    /* U+066B "٫" */
    0xe0,

    /* U+066C "٬" */
    0x68,

    /* U+066D "٭" */
    0x25, 0x5d, 0xf2, 0x0,

    /* U+066E "ٮ" */
    0x80, 0x60, 0x18, 0x7, 0x3, 0x7f, 0x80,

    /* U+066F "ٯ" */
    0xc, 0x26, 0x4c, 0xfc, 0x6f, 0x80,

    /* U+0670 "ٰ" */
    0xc0,

    /* U+0671 "ٱ" */
    0x26, 0xe4, 0x44, 0x44, 0x44,

    /* U+0672 "ٲ" */
    0x7b, 0xa4, 0x92, 0x48,

    /* U+0673 "ٳ" */
    0x22, 0x22, 0x22, 0x22, 0x3, 0xf0,

    /* U+0674 "ٴ" */
    0xec,

    /* U+0675 "ٵ" */
    0x3a, 0xb8, 0x88, 0x88, 0x80,

    /* U+0676 "ٶ" */
    0x8, 0x41, 0x8c, 0x49, 0x27, 0x82, 0x13, 0x80,

    /* U+0677 "ٷ" */
    0x5a, 0x80, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+0678 "ٸ" */
    0x6, 0x4, 0x6, 0x0, 0x7, 0x8, 0x88, 0x8e,
    0x83, 0xc2, 0x7c,

    /* U+0679 "ٹ" */
    0x8, 0x3, 0x81, 0xe0, 0x0, 0x80, 0x60, 0x1c,
    0x5, 0xfe,

    /* U+067A "ٺ" */
    0x0, 0x0, 0x0, 0xc0, 0x0, 0x80, 0x60, 0x18,
    0x7, 0x3, 0x7f, 0x80,

    /* U+067B "ٻ" */
    0x80, 0x60, 0x18, 0x7, 0x3, 0x7f, 0x80, 0x0,
    0x40, 0x30,

    /* U+067C "ټ" */
    0xc, 0x0, 0x8, 0x6, 0x1, 0x80, 0x70, 0x37,
    0xf8, 0x50, 0xc, 0x0,

    /* U+067D "ٽ" */
    0x0, 0x3, 0x0, 0xc0, 0x0, 0x80, 0x60, 0x18,
    0x7, 0x3, 0x7f, 0x80,

    /* U+067E "پ" */
    0x80, 0x60, 0x18, 0x7, 0x3, 0x7f, 0x80, 0x0,
    0xc0, 0x10,

    /* U+067F "ٿ" */
    0x0, 0x3, 0x0, 0xc0, 0x0, 0x80, 0x60, 0x18,
    0x7, 0x3, 0x7f, 0x80,

    /* U+0680 "ڀ" */
    0x80, 0x60, 0x18, 0x7, 0x3, 0x7f, 0x80, 0x0,
    0xc0, 0x30,

    /* U+0681 "ځ" */
    0x10, 0x83, 0x38, 0x1c, 0xc4, 0x20, 0x82, 0xc,
    0x1f,

    /* U+0682 "ڂ" */
    0x10, 0x41, 0x0, 0xe0, 0x73, 0x10, 0x82, 0x8,
    0x30, 0x7c,

    /* U+0683 "ڃ" */
    0xe0, 0x73, 0x10, 0x82, 0x28, 0x30, 0x7c,

    /* U+0684 "ڄ" */
    0xe0, 0x73, 0x10, 0x92, 0x49, 0x30, 0x7c,

    /* U+0685 "څ" */
    0x10, 0x43, 0x80, 0xe0, 0x73, 0x10, 0x82, 0x8,
    0x30, 0x7c,

    /* U+0686 "چ" */
    0xe0, 0x73, 0x10, 0xaa, 0x49, 0x30, 0x7c,

    /* U+0687 "ڇ" */
    0xe0, 0x73, 0x10, 0xba, 0x8, 0x30, 0x7c,

    /* U+0688 "ڈ" */
    0x21, 0x8c, 0x1, 0x4, 0x31, 0xf0,

    /* U+0689 "ډ" */
    0x30, 0x83, 0x18, 0xf9, 0x84,

    /* U+068A "ڊ" */
    0x30, 0x83, 0x18, 0xf8, 0x4,

    /* U+068B "ڋ" */
    0x21, 0x8c, 0x1, 0x4, 0x31, 0xf0, 0xc,

    /* U+068C "ڌ" */
    0x30, 0xc, 0x20, 0xc6, 0x3e,

    /* U+068D "ڍ" */
    0x30, 0x83, 0x18, 0xf8, 0xe,

    /* U+068E "ڎ" */
    0x21, 0x80, 0x61, 0x6, 0x31, 0xf0,

    /* U+068F "ڏ" */
    0x30, 0x0, 0x61, 0x6, 0x31, 0xf0,

    /* U+0690 "ڐ" */
    0x31, 0x80, 0x61, 0x6, 0x31, 0xf0,

    /* U+0691 "ڑ" */
    0x21, 0x9c, 0x1, 0x8, 0x42, 0x37, 0x0,

    /* U+0692 "ڒ" */
    0x3, 0x3, 0x11, 0x11, 0x3e,

    /* U+0693 "ړ" */
    0x11, 0x11, 0x3e, 0xcc,

    /* U+0694 "ڔ" */
    0x31, 0x11, 0x13, 0xe0, 0x40,

    /* U+0695 "ڕ" */
    0x31, 0x11, 0x13, 0xe0, 0xa4,

    /* U+0696 "ږ" */
    0x30, 0x31, 0x11, 0x13, 0xe0, 0x60,

    /* U+0697 "ڗ" */
    0x30, 0x31, 0x11, 0x13, 0xe0,

    /* U+0698 "ژ" */
    0x2, 0x70, 0x31, 0x11, 0x13, 0xe0,

    /* U+0699 "ڙ" */
    0x3, 0x70, 0x31, 0x11, 0x13, 0xe0,

    /* U+069A "ښ" */
    0x0, 0x80, 0x8, 0x0, 0x18, 0x49, 0x84, 0x98,
    0x77, 0x84, 0x87, 0x88,

    /* U+069B "ڛ" */
    0x0, 0x18, 0x49, 0x84, 0x98, 0x77, 0x84, 0x7,
    0x90, 0x0, 0x80,

    /* U+069C "ڜ" */
    0x0, 0x80, 0x8, 0x1, 0x40, 0x1, 0x84, 0x98,
    0x49, 0x87, 0x78, 0x40, 0x79, 0x0, 0x8,

    /* U+069D "ڝ" */
    0x0, 0x70, 0x4, 0x61, 0x43, 0xe, 0x18, 0x7f,
    0x46, 0x1, 0xe2, 0x0,

    /* U+069E "ڞ" */
    0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x7,
    0x0, 0x46, 0x14, 0x30, 0xe1, 0x87, 0xf4, 0x60,
    0x1e, 0x0,

    /* U+069F "ڟ" */
    0x24, 0x28, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+06A0 "ڠ" */
    0x10, 0x0, 0xc0, 0x3, 0x88, 0x10, 0x36, 0x38,
    0x82, 0x4, 0xc, 0x7, 0xc0,

    /* U+06A1 "ڡ" */
    0x1, 0xa0, 0x98, 0x26, 0xf, 0xc0, 0x5f, 0xe0,

    /* U+06A2 "ڢ" */
    0x1, 0xa0, 0x98, 0x26, 0xf, 0xc0, 0x5f, 0xe0,
    0x0, 0x30,

    /* U+06A3 "ڣ" */
    0x0, 0x0, 0x20, 0x0, 0x6, 0x82, 0x60, 0x98,
    0x3f, 0x1, 0x7f, 0x80, 0x0, 0xc0,

    /* U+06A4 "ڤ" */
    0x1, 0x0, 0x0, 0x18, 0x0, 0x1, 0xa0, 0x98,
    0x26, 0xf, 0xc0, 0x5f, 0xe0,

    /* U+06A5 "ڥ" */
    0x1, 0xa0, 0x98, 0x26, 0xf, 0xc0, 0x5f, 0xe0,
    0x0, 0x28, 0x4, 0x0,

    /* U+06A6 "ڦ" */
    0x1, 0x80, 0x0, 0x18, 0x0, 0x1, 0xa0, 0x98,
    0x26, 0xf, 0xc0, 0x5f, 0xe0,

    /* U+06A7 "ڧ" */
    0x0, 0x10, 0x0, 0x61, 0x32, 0x67, 0xe3, 0x7c,

    /* U+06A8 "ڨ" */
    0x8, 0x0, 0x30, 0x0, 0xc2, 0x64, 0xcf, 0xc6,
    0xf8,

    /* U+06A9 "ک" */
    0x0, 0x0, 0xc1, 0x81, 0x8, 0x44, 0x12, 0x5,
    0x2, 0x7e, 0x0,

    /* U+06AA "ڪ" */
    0x6, 0x1, 0x80, 0xc0, 0x1f, 0xe0, 0x2, 0x0,
    0x7f, 0xf8,

    /* U+06AB "ګ" */
    0x0, 0x80, 0xc1, 0xa1, 0xb0, 0xc4, 0x32, 0xd,
    0x2, 0x7e, 0x0,

    /* U+06AC "ڬ" */
    0x9, 0x1, 0x9, 0x89, 0x99, 0x81, 0x81, 0x7e,

    /* U+06AD "ڭ" */
    0x8, 0x19, 0x1, 0x9, 0x89, 0x99, 0x81, 0x81,
    0x7e,

    /* U+06AE "ڮ" */
    0x1, 0x1, 0x9, 0x89, 0x99, 0x81, 0x81, 0x7e,
    0x0, 0x18, 0x8,

    /* U+06AF "گ" */
    0x0, 0x0, 0xc1, 0xe0, 0xc0, 0x84, 0x22, 0x9,
    0x2, 0x81, 0x3f, 0x0,

    /* U+06B0 "ڰ" */
    0x1, 0x83, 0x42, 0xe0, 0xd0, 0xd8, 0x62, 0x19,
    0x6, 0x81, 0x3f, 0x0,

    /* U+06B1 "ڱ" */
    0x4, 0x4, 0xc1, 0xe0, 0xc0, 0x84, 0x22, 0x9,
    0x2, 0x81, 0x3f, 0x0,

    /* U+06B2 "ڲ" */
    0x0, 0x0, 0xc1, 0xe0, 0xc0, 0x84, 0x22, 0x9,
    0x2, 0x81, 0x3f, 0x0, 0x3, 0x80,

    /* U+06B3 "ڳ" */
    0x0, 0x0, 0xc1, 0xe0, 0xc0, 0x84, 0x22, 0x9,
    0x2, 0x81, 0x3f, 0x0, 0x1, 0x0, 0x80,

    /* U+06B4 "ڴ" */
    0x8, 0x2, 0x2, 0x60, 0xf0, 0x60, 0x42, 0x11,
    0x4, 0x81, 0x40, 0x9f, 0x80,

    /* U+06B5 "ڵ" */
    0xa, 0x18, 0x10, 0x20, 0x40, 0x81, 0x2, 0x85,
    0xa, 0x16, 0x27, 0x80,

    /* U+06B6 "ڶ" */
    0x4, 0x0, 0x41, 0x4, 0x10, 0x61, 0x86, 0x1c,
    0x5e,

    /* U+06B7 "ڷ" */
    0x4, 0x8, 0x28, 0x0, 0x40, 0x81, 0x2, 0x5,
    0xa, 0x14, 0x2c, 0x4f, 0x0,

    /* U+06B8 "ڸ" */
    0x4, 0x10, 0x41, 0x4, 0x18, 0x61, 0x87, 0x17,
    0x80, 0x30, 0x0,

    /* U+06B9 "ڹ" */
    0x0, 0x0, 0x61, 0x86, 0x1c, 0x5e, 0x0, 0xc0,

    /* U+06BA "ں" */
    0x6, 0x18, 0x61, 0xc5, 0xe0,

    /* U+06BB "ڻ" */
    0x20, 0xc3, 0x1, 0x86, 0x18, 0x71, 0x78,

    /* U+06BC "ڼ" */
    0x30, 0x8, 0x61, 0x86, 0x17, 0x94, 0x30,

    /* U+06BD "ڽ" */
    0x30, 0x41, 0x1, 0x86, 0x18, 0x71, 0x78,

    /* U+06BE "ھ" */
    0x40, 0xf1, 0x32, 0x57, 0x3f, 0x80,

    /* U+06BF "ڿ" */
    0x0, 0x40, 0x38, 0x1c, 0xc4, 0x2a, 0x92, 0x4c,
    0x1f,

    /* U+06C0 "ۀ" */
    0x68, 0x66, 0x69, 0x9f,

    /* U+06C1 "ہ" */
    0x6f, 0x99, 0xe0,

    /* U+06C2 "ۂ" */
    0x68, 0x66, 0x69, 0x9f,

    /* U+06C3 "ۃ" */
    0x6, 0x6, 0xf9, 0x9e,

    /* U+06C4 "ۄ" */
    0x32, 0x52, 0xf4, 0xeb, 0x80,

    /* U+06C5 "ۅ" */
    0x32, 0x52, 0xf7, 0x8b, 0x80,

    /* U+06C6 "ۆ" */
    0x31, 0x80, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+06C7 "ۇ" */
    0x10, 0x4, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+06C8 "ۈ" */
    0x21, 0x0, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+06C9 "ۉ" */
    0x31, 0x80, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+06CA "ۊ" */
    0x30, 0xc, 0x94, 0xbc, 0x22, 0xe0,

    /* U+06CB "ۋ" */
    0x10, 0xc, 0x3, 0x25, 0x2f, 0x8, 0xb8,

    /* U+06CC "ی" */
    0x7, 0x8, 0x88, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+06CD "ۍ" */
    0x1, 0xc0, 0x8e, 0x20, 0x8e, 0x20, 0xcc, 0x21,
    0xf0,

    /* U+06CE "ێ" */
    0xc0, 0xc7, 0x8, 0x88, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+06CF "ۏ" */
    0x0, 0x80, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+06D0 "ې" */
    0x7, 0x8, 0x98, 0x8e, 0x83, 0xc2, 0x7c, 0x10,
    0x10, 0x10,

    /* U+06D1 "ۑ" */
    0x7, 0x8, 0x98, 0x8e, 0x83, 0xc2, 0x7c, 0x0,
    0x0, 0x10,

    /* U+06D2 "ے" */
    0x30, 0x20, 0x20, 0x10, 0xf, 0xf8,

    /* U+06D3 "ۓ" */
    0x30, 0x10, 0x4, 0x6, 0x4, 0x4, 0x2, 0x1,
    0xff,

    /* U+06D4 "۔" */
    0xc0,

    /* U+06D5 "ە" */
    0x6f, 0x99, 0xe0,

    /* U+06D6 "ۖ" */
    0x28, 0xe7, 0x80,

    /* U+06D7 "ۗ" */
    0x33, 0x70,

    /* U+06D8 "ۘ" */
    0x3c,

    /* U+06D9 "ۙ" */
    0x35, 0x20,

    /* U+06DA "ۚ" */
    0x8f, 0x70,

    /* U+06DB "ۛ" */
    0x46, 0x80,

    /* U+06DC "ۜ" */
    0x1d, 0xf0,

    /* U+06DD "۝" */
    0xf, 0x7, 0xe, 0x9f, 0xa6, 0x6, 0x80, 0x18,
    0x1, 0x80, 0x18, 0x1, 0x60, 0x69, 0xfa, 0x70,
    0xe0, 0xf0,

    /* U+06DE "۞" */
    0x2, 0x0, 0x28, 0xf, 0xf8, 0x60, 0xc2, 0x2,
    0x33, 0x9a, 0x94, 0xac, 0xe6, 0x20, 0x21, 0xc7,
    0xf, 0xf8, 0xc, 0x0,

    /* U+06DF "۟" */
    0xf0,

    /* U+06E0 "۠" */
    0xfc,

    /* U+06E1 "ۡ" */
    0xf0,

    /* U+06E2 "ۢ" */
    0x7a,

    /* U+06E3 "ۣ" */
    0x1b, 0xc0,

    /* U+06E4 "ۤ" */
    0xf0,

    /* U+06E5 "ۥ" */
    0xf6,

    /* U+06E6 "ۦ" */
    0xdc,

    /* U+06E7 "ۧ" */
    0xdc,

    /* U+06E8 "ۨ" */
    0x53, 0x0,

    /* U+06E9 "۩" */
    0x10, 0xda, 0xc, 0x14, 0x48, 0x91, 0x22, 0x7c,

    /* U+06EA "۪" */
    0xd0,

    /* U+06EB "۫" */
    0xf0,

    /* U+06EC "۬" */
    0x80,

    /* U+06ED "ۭ" */
    0x7a,

    /* U+06EE "ۮ" */
    0x20, 0x80, 0x21, 0x86, 0x3e,

    /* U+06EF "ۯ" */
    0x3, 0x3, 0x11, 0x11, 0x3e,

    /* U+06F0 "۰" */
    0xe0,

    /* U+06F1 "۱" */
    0xa5, 0x55,

    /* U+06F2 "۲" */
    0x45, 0x17, 0x90, 0x41, 0x2, 0x8,

    /* U+06F3 "۳" */
    0x93, 0x27, 0xb2, 0x4, 0x8, 0x10, 0x20,

    /* U+06F4 "۴" */
    0xbb, 0x8f, 0xd0, 0x41, 0x4, 0x10,

    /* U+06F5 "۵" */
    0x63, 0x95, 0x38, 0xd6, 0xba,

    /* U+06F6 "۶" */
    0x39, 0x4, 0x4f, 0x30, 0x84, 0x10,

    /* U+06F7 "۷" */
    0x44, 0x89, 0x12, 0x42, 0x85, 0xa, 0x8,

    /* U+06F8 "۸" */
    0x10, 0x50, 0xa1, 0x44, 0x88, 0x91, 0x22,

    /* U+06F9 "۹" */
    0x74, 0xa5, 0xf0, 0x84, 0x21,

    /* U+06FA "ۺ" */
    0x0, 0x80, 0x8, 0x1, 0x40, 0x1, 0x84, 0x98,
    0x49, 0x87, 0x78, 0x48, 0x78, 0x80,

    /* U+06FB "ۻ" */
    0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0xe0, 0x8,
    0xc2, 0x86, 0x1c, 0x30, 0xfe, 0x8c, 0x3, 0xc2,
    0x0,

    /* U+06FC "ۼ" */
    0x0, 0x20, 0x1, 0xc4, 0x8, 0x1b, 0x1c, 0x41,
    0x22, 0x46, 0x3, 0xe0,

    /* U+06FD "۽" */
    0x78, 0x8f, 0x6, 0x60,

    /* U+06FE "۾" */
    0x32, 0x43, 0xf8, 0x5a, 0xd0, 0x80,

    /* U+06FF "ۿ" */
    0x8, 0x31, 0x3, 0xc4, 0xc9, 0x5c, 0xfe,

    /* U+FE70 "ﹰ" */
    0x3c,

    /* U+FE71 "ﹱ" */
    0x65, 0x0, 0x38,

    /* U+FE72 "ﹲ" */
    0x7f, 0x0,

    /* U+FE74 "ﹴ" */
    0x6c,

    /* U+FE76 "ﹶ" */
    0xc0,

    /* U+FE77 "ﹷ" */
    0x28, 0x1, 0xc0,

    /* U+FE78 "ﹸ" */
    0x6d, 0x0,

    /* U+FE79 "ﹹ" */
    0x66, 0xc0, 0x0, 0xf,

    /* U+FE7A "ﹺ" */
    0xc0,

    /* U+FE7B "ﹻ" */
    0xe1, 0x0,

    /* U+FE7C "ﹼ" */
    0x74,

    /* U+FE7D "ﹽ" */
    0x6a, 0x0, 0x0, 0xf0,

    /* U+FE7E "ﹾ" */
    0xf0,

    /* U+FE7F "ﹿ" */
    0x66, 0x0, 0x0, 0xf0,

    /* U+FE80 "ﺀ" */
    0x68, 0xcf,

    /* U+FE81 "ﺁ" */
    0xe9, 0x24, 0x92,

    /* U+FE82 "ﺂ" */
    0xe0, 0x44, 0x44, 0x46,

    /* U+FE83 "ﺃ" */
    0x53, 0x24, 0x92, 0x48,

    /* U+FE84 "ﺄ" */
    0x48, 0xc4, 0x44, 0x44, 0x46,

    /* U+FE85 "ﺅ" */
    0x32, 0xc, 0x64, 0xa5, 0xe1, 0x17, 0x0,

    /* U+FE86 "ﺆ" */
    0x30, 0x83, 0xc, 0x49, 0x27, 0xc6, 0xf0,

    /* U+FE87 "ﺇ" */
    0x49, 0x24, 0x92, 0xb, 0x0,

    /* U+FE88 "ﺈ" */
    0x44, 0x44, 0x44, 0x46, 0x6, 0xe0,

    /* U+FE89 "ﺉ" */
    0xc0, 0x86, 0xc8, 0x90, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+FE8A "ﺊ" */
    0xc0, 0x80, 0xc0, 0x0, 0x80, 0x87, 0xc2, 0x7c,

    /* U+FE8B "ﺋ" */
    0x69, 0x92, 0x4e,

    /* U+FE8C "ﺌ" */
    0x22, 0x18, 0x42, 0x11, 0x40,

    /* U+FE8D "ﺍ" */
    0xff,

    /* U+FE8E "ﺎ" */
    0x92, 0x49, 0x26,

    /* U+FE8F "ﺏ" */
    0x80, 0x60, 0x18, 0x7, 0x3, 0x7f, 0x80, 0x0,
    0xc0,

    /* U+FE90 "ﺐ" */
    0x80, 0x10, 0x12, 0x2, 0x60, 0x47, 0xf4, 0x0,
    0x2, 0x0,

    /* U+FE91 "ﺑ" */
    0x24, 0x9c, 0x10,

    /* U+FE92 "ﺒ" */
    0x21, 0x9, 0xa0, 0x10,

    /* U+FE93 "ﺓ" */
    0x6, 0x6, 0xf9, 0x9e,

    /* U+FE94 "ﺔ" */
    0x50, 0x1, 0xc, 0xd2, 0x4f, 0x7,

    /* U+FE95 "ﺕ" */
    0xc, 0x0, 0x8, 0x6, 0x1, 0x80, 0x70, 0x37,
    0xf8,

    /* U+FE96 "ﺖ" */
    0x14, 0x0, 0x2, 0x0, 0x40, 0x48, 0x9, 0x81,
    0x1f, 0xd0,

    /* U+FE97 "ﺗ" */
    0x60, 0x22, 0x22, 0xc0,

    /* U+FE98 "ﺘ" */
    0x2, 0x80, 0x42, 0x13, 0x40,

    /* U+FE99 "ﺙ" */
    0x0, 0x0, 0x0, 0xc0, 0x0, 0x80, 0x60, 0x18,
    0x7, 0x3, 0x7f, 0x80,

    /* U+FE9A "ﺚ" */
    0x0, 0x1, 0x0, 0x50, 0x0, 0x8, 0x1, 0x1,
    0x20, 0x26, 0x4, 0x7f, 0x40,

    /* U+FE9B "ﺛ" */
    0x2, 0x60, 0x22, 0x22, 0xc0,

    /* U+FE9C "ﺜ" */
    0x20, 0x14, 0x2, 0x10, 0x9a,

    /* U+FE9D "ﺝ" */
    0xe0, 0x73, 0x10, 0x92, 0x48, 0x30, 0x7c,

    /* U+FE9E "ﺞ" */
    0xf0, 0x39, 0xd6, 0x29, 0x30, 0x30, 0x3f,

    /* U+FE9F "ﺟ" */
    0x70, 0x8, 0x7, 0x18, 0xe0, 0x0, 0x8,

    /* U+FEA0 "ﺠ" */
    0x70, 0x4, 0x1, 0xc3, 0x4e, 0x18, 0x0, 0x20,

    /* U+FEA1 "ﺡ" */
    0xe0, 0x73, 0x10, 0x82, 0x8, 0x30, 0x7c,

    /* U+FEA2 "ﺢ" */
    0xf0, 0x39, 0xd6, 0x28, 0x30, 0x30, 0x3f,

    /* U+FEA3 "ﺣ" */
    0x70, 0x8, 0x7, 0x18, 0xe0,

    /* U+FEA4 "ﺤ" */
    0x70, 0x4, 0x1, 0xc3, 0x4e, 0x18,

    /* U+FEA5 "ﺥ" */
    0x0, 0x40, 0x38, 0x1c, 0xc4, 0x20, 0x82, 0xc,
    0x1f,

    /* U+FEA6 "ﺦ" */
    0x0, 0x20, 0x7, 0x81, 0xce, 0xb1, 0x41, 0x81,
    0x81, 0xf8,

    /* U+FEA7 "ﺧ" */
    0x0, 0x8, 0x0, 0x70, 0x8, 0x7, 0x18, 0xe0,

    /* U+FEA8 "ﺨ" */
    0x0, 0x4, 0x0, 0xe, 0x0, 0x80, 0x38, 0x69,
    0xc3,

    /* U+FEA9 "ﺩ" */
    0x30, 0x83, 0x18, 0xf8,

    /* U+FEAA "ﺪ" */
    0x10, 0x41, 0x22, 0x8b, 0xd0,

    /* U+FEAB "ﺫ" */
    0x30, 0xc, 0x20, 0xc6, 0x3e,

    /* U+FEAC "ﺬ" */
    0x10, 0x1, 0x4, 0x12, 0x28, 0xbd,

    /* U+FEAD "ﺭ" */
    0x31, 0x11, 0x13, 0xe0,

    /* U+FEAE "ﺮ" */
    0x10, 0x41, 0x7, 0x33, 0x80,

    /* U+FEAF "ﺯ" */
    0x30, 0x31, 0x11, 0x13, 0xe0,

    /* U+FEB0 "ﺰ" */
    0x30, 0x1, 0x4, 0x10, 0x73, 0x38,

    /* U+FEB1 "ﺱ" */
    0x0, 0x18, 0x49, 0x84, 0x98, 0x77, 0x84, 0x7,
    0x80,

    /* U+FEB2 "ﺲ" */
    0x84, 0x92, 0x12, 0x48, 0x76, 0xa1, 0x0, 0x78,
    0x0,

    /* U+FEB3 "ﺳ" */
    0x0, 0x92, 0x49, 0x3f, 0x70,

    /* U+FEB4 "ﺴ" */
    0x24, 0x84, 0x93, 0xed, 0x0,

    /* U+FEB5 "ﺵ" */
    0x0, 0x80, 0x8, 0x1, 0x40, 0x1, 0x84, 0x98,
    0x49, 0x87, 0x78, 0x40, 0x78, 0x0,

    /* U+FEB6 "ﺶ" */
    0x0, 0x80, 0x0, 0x0, 0x14, 0x0, 0x0, 0x84,
    0x92, 0x12, 0x48, 0x76, 0xa1, 0x0, 0x78, 0x0,

    /* U+FEB7 "ﺷ" */
    0x4, 0x2, 0x2, 0x80, 0x12, 0x49, 0x27, 0xee,

    /* U+FEB8 "ﺸ" */
    0x4, 0x0, 0x0, 0x28, 0x0, 0x2, 0x48, 0x49,
    0x3e, 0xd0,

    /* U+FEB9 "ﺹ" */
    0x0, 0x70, 0x4, 0x61, 0x43, 0xe, 0x18, 0x7f,
    0x46, 0x1, 0xe0, 0x0,

    /* U+FEBA "ﺺ" */
    0x0, 0x70, 0x2, 0x28, 0x50, 0xa1, 0xc2, 0x87,
    0xfe, 0x30, 0x7, 0x80, 0x0,

    /* U+FEBB "ﺻ" */
    0x1, 0x80, 0x92, 0x44, 0xa1, 0xff, 0x80,

    /* U+FEBC "ﺼ" */
    0x1, 0x80, 0x48, 0x91, 0x14, 0x2f, 0xfe,

    /* U+FEBD "ﺽ" */
    0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0xe0, 0x8,
    0xc2, 0x86, 0x1c, 0x30, 0xfe, 0x8c, 0x3, 0xc0,
    0x0,

    /* U+FEBE "ﺾ" */
    0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x1c, 0x0,
    0x8a, 0x14, 0x28, 0x70, 0xa1, 0xff, 0x8c, 0x1,
    0xe0, 0x0,

    /* U+FEBF "ﺿ" */
    0x2, 0x0, 0x80, 0x0, 0x6, 0x2, 0x49, 0x12,
    0x87, 0xfe,

    /* U+FEC0 "ﻀ" */
    0x2, 0x0, 0x40, 0x0, 0x0, 0xc0, 0x24, 0x48,
    0x8a, 0x17, 0xff,

    /* U+FEC1 "ﻁ" */
    0x20, 0x20, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+FEC2 "ﻂ" */
    0x20, 0x10, 0x8, 0x5, 0xc3, 0x91, 0x88, 0x85,
    0xff,

    /* U+FEC3 "ﻃ" */
    0x20, 0x20, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+FEC4 "ﻄ" */
    0x20, 0x10, 0x8, 0x5, 0xc3, 0x91, 0x88, 0x85,
    0xff,

    /* U+FEC5 "ﻅ" */
    0x20, 0x24, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+FEC6 "ﻆ" */
    0x20, 0x12, 0x8, 0x5, 0xc3, 0x91, 0x88, 0x85,
    0xff,

    /* U+FEC7 "ﻇ" */
    0x20, 0x24, 0x20, 0x2e, 0x39, 0x31, 0x21, 0xfe,

    /* U+FEC8 "ﻈ" */
    0x20, 0x12, 0x8, 0x5, 0xc3, 0x91, 0x88, 0x85,
    0xff,

    /* U+FEC9 "ﻉ" */
    0x38, 0x81, 0x3, 0x63, 0x88, 0x20, 0x40, 0xc0,
    0x7c,

    /* U+FECA "ﻊ" */
    0x79, 0x22, 0x8c, 0xce, 0xc, 0x1f,

    /* U+FECB "ﻋ" */
    0x39, 0x4, 0x18, 0xfc,

    /* U+FECC "ﻌ" */
    0x79, 0x12, 0x84, 0xec,

    /* U+FECD "ﻍ" */
    0x0, 0x20, 0x1, 0xc4, 0x8, 0x1b, 0x1c, 0x41,
    0x2, 0x6, 0x3, 0xe0,

    /* U+FECE "ﻎ" */
    0x0, 0x40, 0x1e, 0x48, 0xa3, 0x33, 0x83, 0x7,
    0xc0,

    /* U+FECF "ﻏ" */
    0x10, 0x40, 0xe, 0x41, 0x6, 0x3f,

    /* U+FED0 "ﻐ" */
    0x10, 0x40, 0x1e, 0x44, 0xa1, 0x3b,

    /* U+FED1 "ﻑ" */
    0x0, 0x0, 0x20, 0x0, 0x6, 0x82, 0x60, 0x98,
    0x3f, 0x1, 0x7f, 0x80,

    /* U+FED2 "ﻒ" */
    0x0, 0x0, 0x10, 0x0, 0x40, 0xc8, 0x25, 0x4,
    0xb0, 0x73, 0xff,

    /* U+FED3 "ﻓ" */
    0x1, 0x0, 0x64, 0xa5, 0xe1, 0xf0,

    /* U+FED4 "ﻔ" */
    0x0, 0x0, 0xc, 0x49, 0x23, 0x3f,

    /* U+FED5 "ﻕ" */
    0x0, 0x18, 0x0, 0x61, 0x32, 0x67, 0xe3, 0x7c,

    /* U+FED6 "ﻖ" */
    0xc, 0x0, 0xc, 0x12, 0x92, 0x9f, 0xc6, 0x7c,

    /* U+FED7 "ﻗ" */
    0x30, 0xc, 0x94, 0xbc, 0x3e,

    /* U+FED8 "ﻘ" */
    0x0, 0xc0, 0xc, 0x49, 0x23, 0x3f,

    /* U+FED9 "ﻙ" */
    0x1, 0x1, 0x9, 0x89, 0x99, 0x81, 0x81, 0x7e,

    /* U+FEDA "ﻚ" */
    0x1, 0x0, 0x41, 0x92, 0x24, 0x99, 0x20, 0x4c,
    0x11, 0xfa,

    /* U+FEDB "ﻛ" */
    0xc, 0xc4, 0x18, 0x10, 0x20, 0xbc,

    /* U+FEDC "ﻜ" */
    0xc, 0x61, 0x2, 0x2, 0x2, 0x6, 0x7a,

    /* U+FEDD "ﻝ" */
    0x4, 0x10, 0x41, 0x4, 0x18, 0x61, 0x87, 0x17,
    0x80,

    /* U+FEDE "ﻞ" */
    0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x84, 0x86,
    0x84, 0x78,

    /* U+FEDF "ﻟ" */
    0x24, 0x92, 0x4e,

    /* U+FEE0 "ﻠ" */
    0x21, 0x8, 0x42, 0x10, 0x9a,

    /* U+FEE1 "ﻡ" */
    0x32, 0x43, 0xf8, 0x42, 0x10, 0x80,

    /* U+FEE2 "ﻢ" */
    0x18, 0x24, 0x64, 0xbb, 0x80, 0x80, 0x80, 0x80,

    /* U+FEE3 "ﻣ" */
    0x18, 0x92, 0x7e,

    /* U+FEE4 "ﻤ" */
    0x38, 0x51, 0x35, 0xf0,

    /* U+FEE5 "ﻥ" */
    0x0, 0x0, 0x61, 0x86, 0x1c, 0x5e,

    /* U+FEE6 "ﻦ" */
    0x0, 0x0, 0x0, 0x84, 0x84, 0x86, 0x84, 0x78,

    /* U+FEE7 "ﻧ" */
    0x60, 0x92, 0x70,

    /* U+FEE8 "ﻨ" */
    0x21, 0x0, 0x42, 0x13, 0x40,

    /* U+FEEA "ﻪ" */
    0x10, 0xcd, 0x24, 0xf0, 0x70,

    /* U+FEEB "ﻫ" */
    0x40, 0xf1, 0x32, 0x57, 0x3f, 0x80,

    /* U+FEEC "ﻬ" */
    0x30, 0xa4, 0x92, 0xfd, 0xa3, 0x80,

    /* U+FEED "ﻭ" */
    0x32, 0x52, 0xf0, 0x8b, 0x80,

    /* U+FEEE "ﻮ" */
    0x31, 0x24, 0x9f, 0x1b, 0xc0,

    /* U+FEEF "ﻯ" */
    0x7, 0x8, 0x88, 0x8e, 0x83, 0xc2, 0x7c,

    /* U+FEF0 "ﻰ" */
    0x80, 0x80, 0x87, 0xc2, 0x7c,

    /* U+FEF1 "ﻱ" */
    0x7, 0x8, 0x98, 0x8e, 0x82, 0xc2, 0x7c, 0x8,
    0x8,

    /* U+FEF2 "ﻲ" */
    0x80, 0x80, 0x87, 0xc2, 0x7c, 0x0, 0x8,

    /* U+FEF3 "ﻳ" */
    0x24, 0x9c, 0x38,

    /* U+FEF4 "ﻴ" */
    0x21, 0x9, 0xa0, 0x28,

    /* U+FEF5 "ﻵ" */
    0xe8, 0x62, 0x93, 0xd, 0xbf,

    /* U+FEF6 "ﻶ" */
    0xe8, 0x11, 0x22, 0x42, 0x85, 0x6, 0x7a,

    /* U+FEF7 "ﻷ" */
    0xc4, 0x32, 0x18, 0xb4, 0xc3, 0x6f, 0xc0,

    /* U+FEF8 "ﻸ" */
    0x41, 0x1, 0xa0, 0x44, 0x89, 0xa, 0x14, 0x19,
    0xe8,

    /* U+FEF9 "ﻹ" */
    0xc, 0x72, 0xd3, 0xd, 0xbf, 0x2, 0x38,

    /* U+FEFA "ﻺ" */
    0xa, 0x24, 0x92, 0x28, 0xa1, 0xbd, 0x1, 0xc,
    0x0,

    /* U+FEFB "ﻻ" */
    0xc, 0x72, 0xd3, 0xd, 0xbf,

    /* U+FEFC "ﻼ" */
    0xa, 0x24, 0x92, 0x28, 0xa1, 0xbd
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 39, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 58, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 50, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 67, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 12, .adv_w = 67, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 17, .adv_w = 46, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 72, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 24, .adv_w = 44, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 241, .box_w = 15, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 301, .box_w = 18, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 248, .box_w = 15, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 290, .box_w = 17, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 61, .adv_w = 310, .box_w = 19, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 216, .box_w = 12, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 81, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 91, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 100, .adv_w = 166, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 108, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 114, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 120, .adv_w = 83, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 128, .adv_w = 45, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 129, .adv_w = 60, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 131, .adv_w = 168, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 136, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 145, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 147, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 149, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 151, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 153, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 154, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 156, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 158, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 159, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 160, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 161, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 162, .adv_w = 47, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 70, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 124, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 97, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 183, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 185, .adv_w = 45, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 188, .adv_w = 45, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 192, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 199, .adv_w = 45, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 204, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 212, .adv_w = 45, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 213, .adv_w = 173, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 222, .adv_w = 85, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 226, .adv_w = 173, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 235, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 247, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 254, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 261, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 270, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 274, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 279, .adv_w = 67, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 283, .adv_w = 67, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 288, .adv_w = 209, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 297, .adv_w = 209, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 311, .adv_w = 221, .box_w = 13, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 323, .adv_w = 221, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 340, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 348, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 356, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 365, .adv_w = 113, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 377, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 388, .adv_w = 160, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 402, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 410, .adv_w = 141, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 418, .adv_w = 141, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 429, .adv_w = 53, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 430, .adv_w = 174, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 442, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 450, .adv_w = 155, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 458, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 467, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 473, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 479, .adv_w = 85, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 482, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 487, .adv_w = 141, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 494, .adv_w = 141, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 503, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 504, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 506, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 507, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 508, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 510, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 511, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 512, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 513, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 514, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 515, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 516, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 517, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 519, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 520, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 521, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 522, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 523, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 524, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 526, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 527, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 528, .adv_w = 56, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 529, .adv_w = 54, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 531, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 537, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 544, .adv_w = 84, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 548, .adv_w = 102, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 552, .adv_w = 95, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 557, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 564, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 571, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 576, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 582, .adv_w = 62, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 583, .adv_w = 62, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 584, .adv_w = 101, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 588, .adv_w = 173, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 595, .adv_w = 132, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 601, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 602, .adv_w = 45, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 607, .adv_w = 45, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 611, .adv_w = 45, .box_w = 4, .box_h = 11, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 617, .adv_w = 67, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 618, .adv_w = 45, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 623, .adv_w = 87, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 631, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 638, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 649, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 659, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 671, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 681, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 693, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 705, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 715, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 727, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 737, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 746, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 756, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 763, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 770, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 780, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 794, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 800, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 805, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 810, .adv_w = 96, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 817, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 822, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 827, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 833, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 839, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 845, .adv_w = 67, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 852, .adv_w = 67, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 857, .adv_w = 67, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 861, .adv_w = 66, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 866, .adv_w = 67, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 871, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 877, .adv_w = 67, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 882, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 888, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 894, .adv_w = 209, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 906, .adv_w = 209, .box_w = 12, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 917, .adv_w = 209, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 932, .adv_w = 221, .box_w = 13, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 944, .adv_w = 221, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 962, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 970, .adv_w = 113, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 983, .adv_w = 174, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 991, .adv_w = 174, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1001, .adv_w = 174, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1015, .adv_w = 174, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1028, .adv_w = 174, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1040, .adv_w = 174, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1053, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1061, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1070, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1081, .adv_w = 193, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1091, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1102, .adv_w = 155, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1110, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1119, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1130, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1142, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1154, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1166, .adv_w = 160, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1180, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1195, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1208, .adv_w = 121, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1220, .adv_w = 121, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1229, .adv_w = 121, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1242, .adv_w = 121, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1253, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1261, .adv_w = 119, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1266, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1273, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1280, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1287, .adv_w = 129, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1293, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1302, .adv_w = 85, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1306, .adv_w = 85, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1309, .adv_w = 85, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1313, .adv_w = 85, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1317, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1322, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1327, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1334, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1341, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1348, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1355, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1361, .adv_w = 87, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1368, .adv_w = 141, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1375, .adv_w = 141, .box_w = 10, .box_h = 7, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1384, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1392, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1399, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1409, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1419, .adv_w = 168, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1425, .adv_w = 168, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1434, .adv_w = 64, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1435, .adv_w = 85, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1438, .adv_w = 0, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1441, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1443, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1444, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1446, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1448, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1450, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1452, .adv_w = 226, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1470, .adv_w = 196, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1490, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1491, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1492, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1493, .adv_w = 0, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1494, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1496, .adv_w = 0, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1497, .adv_w = 63, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1498, .adv_w = 79, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1499, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1500, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1502, .adv_w = 153, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1510, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1511, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1512, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1513, .adv_w = 0, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1514, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1519, .adv_w = 67, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1524, .adv_w = 56, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1525, .adv_w = 54, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1527, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1533, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1540, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1546, .adv_w = 112, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1551, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1557, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1564, .adv_w = 109, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1571, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1576, .adv_w = 209, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1590, .adv_w = 221, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1607, .adv_w = 113, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1619, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1623, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1629, .adv_w = 129, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1636, .adv_w = 69, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1637, .adv_w = 53, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1640, .adv_w = 82, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1642, .adv_w = 69, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1643, .adv_w = 69, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1644, .adv_w = 53, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1647, .adv_w = 71, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1649, .adv_w = 53, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1653, .adv_w = 69, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1654, .adv_w = 53, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1656, .adv_w = 72, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1657, .adv_w = 53, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1661, .adv_w = 63, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1662, .adv_w = 53, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1666, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1668, .adv_w = 45, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1671, .adv_w = 52, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1675, .adv_w = 45, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1679, .adv_w = 52, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1684, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1691, .adv_w = 90, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1698, .adv_w = 45, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1703, .adv_w = 52, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1709, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1717, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1725, .adv_w = 49, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1728, .adv_w = 58, .box_w = 5, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1733, .adv_w = 45, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1734, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1737, .adv_w = 173, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1746, .adv_w = 180, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1756, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1759, .adv_w = 58, .box_w = 5, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1763, .adv_w = 85, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1767, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1773, .adv_w = 173, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1782, .adv_w = 180, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1792, .adv_w = 49, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1796, .adv_w = 58, .box_w = 5, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1801, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1813, .adv_w = 180, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1826, .adv_w = 49, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1831, .adv_w = 58, .box_w = 5, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1836, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1843, .adv_w = 123, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1850, .adv_w = 125, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1857, .adv_w = 133, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1865, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1872, .adv_w = 123, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1879, .adv_w = 125, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1884, .adv_w = 133, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1890, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1899, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1909, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1917, .adv_w = 133, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1926, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1930, .adv_w = 110, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1935, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1940, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1946, .adv_w = 69, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1950, .adv_w = 78, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1955, .adv_w = 67, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1960, .adv_w = 78, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1966, .adv_w = 209, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1975, .adv_w = 220, .box_w = 14, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1984, .adv_w = 138, .box_w = 9, .box_h = 4, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1989, .adv_w = 148, .box_w = 11, .box_h = 3, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 1994, .adv_w = 209, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2008, .adv_w = 220, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2024, .adv_w = 138, .box_w = 9, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2032, .adv_w = 148, .box_w = 11, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2042, .adv_w = 221, .box_w = 13, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2054, .adv_w = 229, .box_w = 14, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2067, .adv_w = 162, .box_w = 10, .box_h = 5, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2074, .adv_w = 170, .box_w = 11, .box_h = 5, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2081, .adv_w = 221, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2098, .adv_w = 229, .box_w = 14, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2116, .adv_w = 162, .box_w = 10, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2126, .adv_w = 170, .box_w = 11, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2137, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2145, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2154, .adv_w = 127, .box_w = 8, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2162, .adv_w = 135, .box_w = 9, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2171, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2179, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2188, .adv_w = 127, .box_w = 8, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2196, .adv_w = 135, .box_w = 9, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2205, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2214, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2220, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2224, .adv_w = 99, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2228, .adv_w = 113, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2240, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2249, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2255, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2261, .adv_w = 174, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2273, .adv_w = 179, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2284, .adv_w = 83, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2290, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2296, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2304, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2312, .adv_w = 83, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2317, .adv_w = 90, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2323, .adv_w = 155, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2331, .adv_w = 162, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2341, .adv_w = 87, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2347, .adv_w = 94, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2354, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2363, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2373, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2376, .adv_w = 58, .box_w = 5, .box_h = 8, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2381, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2387, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2395, .adv_w = 95, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2398, .adv_w = 110, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2402, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2408, .adv_w = 129, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2416, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2419, .adv_w = 58, .box_w = 5, .box_h = 7, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 2424, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2429, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2435, .adv_w = 88, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2441, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2446, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2451, .adv_w = 141, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2458, .adv_w = 132, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 2463, .adv_w = 141, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2472, .adv_w = 131, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2479, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2482, .adv_w = 58, .box_w = 5, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 2486, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2491, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2498, .adv_w = 104, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2505, .adv_w = 111, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2514, .adv_w = 104, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2521, .adv_w = 110, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2530, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2535, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1}
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
const lv_font_t ar_12 = {
#else
lv_font_t ar_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if AR_12*/

