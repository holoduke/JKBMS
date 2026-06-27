/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --font /tmp/NotoArabic.ttf --size 10 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x600-0x6FF,0xFE70-0xFEFF -o src/fonts/ar_10.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef AR_10
#define AR_10 1
#endif

#if AR_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfa,

    /* U+002C "," */
    0x60,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+0030 "0" */
    0x72, 0x73, 0x94, 0xa5, 0xc0,

    /* U+0031 "1" */
    0x74, 0x92, 0x48,

    /* U+0032 "2" */
    0x78, 0x42, 0x22, 0x23, 0xe0,

    /* U+0033 "3" */
    0xf8, 0x42, 0x60, 0x87, 0xe0,

    /* U+0034 "4" */
    0x18, 0xa2, 0x92, 0x89, 0xe0, 0x80,

    /* U+0035 "5" */
    0xf8, 0x8f, 0x11, 0xe0,

    /* U+0036 "6" */
    0x3a, 0x15, 0xf4, 0xa5, 0xe0,

    /* U+0037 "7" */
    0xf8, 0x44, 0x23, 0x10, 0x80,

    /* U+0038 "8" */
    0x7a, 0x56, 0xe4, 0xc5, 0xe0,

    /* U+0039 "9" */
    0x72, 0x72, 0xf0, 0x85, 0xc0,

    /* U+003A ":" */
    0x44,

    /* U+0600 "؀" */
    0x0, 0x20, 0xb, 0xff, 0x80,

    /* U+0601 "؁" */
    0xef, 0xfb, 0x40, 0x20,

    /* U+0602 "؂" */
    0xc0, 0x18, 0x3, 0xff, 0x80,

    /* U+0603 "؃" */
    0x0, 0x18, 0x3, 0x7f, 0xfe,

    /* U+0604 "؄" */
    0x0, 0x0, 0x10, 0x0, 0x1, 0x0, 0xc, 0x90,
    0x1, 0x69, 0x0, 0x13, 0xe7, 0xff, 0x80, 0x80,
    0x8, 0x0,

    /* U+0605 "؅" */
    0x70, 0x19, 0xfe,

    /* U+0606 "؆" */
    0xb2, 0x89, 0xd4, 0x60, 0x80, 0x0,

    /* U+0607 "؇" */
    0xa1, 0xc4, 0xd4, 0x30, 0x80, 0x0,

    /* U+0608 "؈" */
    0x0, 0x20, 0xc4, 0x14, 0xe4, 0x9c, 0x7c, 0x82,
    0x18, 0x81, 0xe0,

    /* U+0609 "؉" */
    0x85, 0x8, 0x84, 0x46, 0xa0,

    /* U+060A "؊" */
    0x81, 0x40, 0x82, 0x4, 0x11, 0x6a, 0x80,

    /* U+060B "؋" */
    0x20, 0x2d, 0x71, 0xe0, 0x20,

    /* U+060C "،" */
    0xc0,

    /* U+060D "؍" */
    0x2d, 0x40,

    /* U+060E "؎" */
    0x60, 0x48, 0x24, 0x2f, 0xf0,

    /* U+060F "؏" */
    0x62, 0x8, 0x1c, 0xc2, 0xec, 0x61, 0xf8,

    /* U+0610 "ؐ" */
    0x7e, 0x0,

    /* U+0611 "ؑ" */
    0x3e, 0x0,

    /* U+0612 "ؒ" */
    0xfc,

    /* U+0613 "ؓ" */
    0x85, 0xf0,

    /* U+0614 "ؔ" */
    0xf,

    /* U+0615 "ؕ" */
    0xbc,

    /* U+0616 "ؖ" */
    0x31, 0x9e,

    /* U+0617 "ؗ" */
    0x9c,

    /* U+0618 "ؘ" */
    0x40,

    /* U+0619 "ؙ" */
    0xa8,

    /* U+061A "ؚ" */
    0xc0,

    /* U+061B "؛" */
    0xc8,

    /* U+061C "؜" */
    0x0,

    /* U+061E "؞" */
    0x54,

    /* U+061F "؟" */
    0x78, 0x84, 0x20, 0x20,

    /* U+0620 "ؠ" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x18, 0x30,

    /* U+0621 "ء" */
    0xf2, 0x70,

    /* U+0622 "آ" */
    0x8c, 0x24, 0x92, 0x40,

    /* U+0623 "أ" */
    0x64, 0x55, 0x50,

    /* U+0624 "ؤ" */
    0x48, 0x46, 0xaa, 0xe2, 0xc0,

    /* U+0625 "إ" */
    0xaa, 0xaa, 0xa0,

    /* U+0626 "ئ" */
    0x40, 0x8c, 0x20, 0xc8, 0xd0, 0x71, 0xbc,

    /* U+0627 "ا" */
    0xfe,

    /* U+0628 "ب" */
    0x80, 0xc0, 0x60, 0x2f, 0xe0, 0x0, 0x40,

    /* U+0629 "ة" */
    0x60, 0x46, 0x99, 0xe0,

    /* U+062A "ت" */
    0xc, 0x0, 0x60, 0x30, 0x17, 0xf0,

    /* U+062B "ث" */
    0x8, 0x0, 0x3, 0x0, 0x18, 0xc, 0x5, 0xfc,

    /* U+062C "ج" */
    0xe0, 0x73, 0x10, 0x82, 0x48, 0x30, 0x7c,

    /* U+062D "ح" */
    0xe0, 0x72, 0x10, 0x82, 0xc, 0x1f,

    /* U+062E "خ" */
    0x10, 0xe, 0x7, 0x21, 0x8, 0x20, 0xc1, 0xf0,

    /* U+062F "د" */
    0x22, 0x11, 0xf0,

    /* U+0630 "ذ" */
    0x20, 0x22, 0x11, 0xe0,

    /* U+0631 "ر" */
    0x4, 0x95, 0x80,

    /* U+0632 "ز" */
    0x61, 0x12, 0x54,

    /* U+0633 "س" */
    0x0, 0x10, 0x49, 0x84, 0x98, 0x77, 0x84, 0x7,
    0x80,

    /* U+0634 "ش" */
    0x0, 0x80, 0x14, 0x0, 0x10, 0x1, 0x4, 0x98,
    0x49, 0x87, 0x68, 0x40, 0x78, 0x0,

    /* U+0635 "ص" */
    0x0, 0x70, 0x26, 0x61, 0x43, 0xf, 0xe8, 0x40,
    0x3c, 0x0,

    /* U+0636 "ض" */
    0x0, 0x20, 0x0, 0x0, 0x1c, 0x9, 0x98, 0x50,
    0xc3, 0xfa, 0x10, 0xf, 0x0,

    /* U+0637 "ط" */
    0x20, 0x20, 0x20, 0x2e, 0x31, 0x21, 0xfe,

    /* U+0638 "ظ" */
    0x20, 0x24, 0x20, 0x2e, 0x31, 0x21, 0xfe,

    /* U+0639 "ع" */
    0x62, 0x8, 0x1c, 0xc2, 0x8, 0x30, 0x7c,

    /* U+063A "غ" */
    0x20, 0x6, 0x20, 0x81, 0xcc, 0x20, 0x83, 0x7,
    0xc0,

    /* U+063B "ػ" */
    0x3, 0x0, 0x81, 0x80, 0x88, 0x24, 0xb, 0x4,
    0xfc,

    /* U+063C "ؼ" */
    0x1, 0x83, 0x1, 0x10, 0x48, 0x14, 0x9, 0xf8,
    0x0, 0x18, 0x4, 0x0,

    /* U+063D "ؽ" */
    0x0, 0xcc, 0x20, 0xc8, 0xd0, 0x71, 0xbc,

    /* U+063E "ؾ" */
    0x6, 0xd0, 0x64, 0x68, 0x38, 0xde, 0x0,

    /* U+063F "ؿ" */
    0x26, 0xd0, 0x64, 0x68, 0x38, 0xde, 0x0,

    /* U+0640 "ـ" */
    0xe0,

    /* U+0641 "ف" */
    0x1, 0x0, 0x0, 0xd0, 0x98, 0x3c, 0x5, 0xfc,

    /* U+0642 "ق" */
    0xa, 0x0, 0x30, 0x98, 0xf0, 0x71, 0xbc,

    /* U+0643 "ك" */
    0x1, 0x1, 0x9, 0x89, 0x91, 0x81, 0x7e,

    /* U+0644 "ل" */
    0x4, 0x10, 0x41, 0x4, 0x18, 0x61, 0x89, 0xe0,

    /* U+0645 "م" */
    0x70, 0x9d, 0x8, 0x42, 0x0,

    /* U+0646 "ن" */
    0x10, 0x0, 0x61, 0x86, 0x37, 0x80,

    /* U+0647 "ه" */
    0x46, 0x99, 0xe0,

    /* U+0648 "و" */
    0x6a, 0xae, 0x2c,

    /* U+0649 "ى" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0,

    /* U+064A "ي" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0, 0x28,

    /* U+064B "ً" */
    0xd8,

    /* U+064C "ٌ" */
    0x7f, 0x0,

    /* U+064D "ٍ" */
    0x1b, 0x0,

    /* U+064E "َ" */
    0xc0,

    /* U+064F "ُ" */
    0x6f, 0x0,

    /* U+0650 "ِ" */
    0x18,

    /* U+0651 "ّ" */
    0xfc,

    /* U+0652 "ْ" */
    0xf0,

    /* U+0653 "ٓ" */
    0xe0,

    /* U+0654 "ٔ" */
    0xe8,

    /* U+0655 "ٕ" */
    0xe8,

    /* U+0656 "ٖ" */
    0x80,

    /* U+0657 "ٗ" */
    0x7b, 0x0,

    /* U+0658 "٘" */
    0x70,

    /* U+0659 "ٙ" */
    0xe0,

    /* U+065A "ٚ" */
    0xb0,

    /* U+065B "ٛ" */
    0x30,

    /* U+065C "ٜ" */
    0xc0,

    /* U+065D "ٝ" */
    0xd9, 0x80,

    /* U+065E "ٞ" */
    0xaa, 0x80,

    /* U+065F "ٟ" */
    0x6b, 0x80,

    /* U+0660 "٠" */
    0xc0,

    /* U+0661 "١" */
    0xa5, 0x54,

    /* U+0662 "٢" */
    0x97, 0x44, 0x44, 0x40,

    /* U+0663 "٣" */
    0x82, 0x67, 0x90, 0x41, 0x4, 0x0,

    /* U+0664 "٤" */
    0x6c, 0x86, 0x88, 0xf0,

    /* U+0665 "٥" */
    0x69, 0x99, 0x60,

    /* U+0666 "٦" */
    0xf0, 0x84, 0x21, 0x8, 0x20,

    /* U+0667 "٧" */
    0x85, 0x24, 0x94, 0x30, 0xc3, 0x0,

    /* U+0668 "٨" */
    0x10, 0xc3, 0xc, 0x49, 0x28, 0x40,

    /* U+0669 "٩" */
    0x6a, 0xaf, 0x11, 0x10,

    /* U+066A "٪" */
    0x8a, 0x24, 0x48, 0xa0,

    /* U+066B "٫" */
    0x58,

    /* U+066C "٬" */
    0xa8,

    /* U+066D "٭" */
    0x21, 0x1c, 0xe0, 0x0,

    /* U+066E "ٮ" */
    0x80, 0xc0, 0x60, 0x2f, 0xe0,

    /* U+066F "ٯ" */
    0xc, 0x26, 0x3c, 0x1c, 0x6f, 0x0,

    /* U+0670 "ٰ" */
    0x80,

    /* U+0671 "ٱ" */
    0x6f, 0x84, 0x92, 0x48,

    /* U+0672 "ٲ" */
    0x6b, 0x84, 0x92, 0x48,

    /* U+0673 "ٳ" */
    0x22, 0x22, 0x22, 0x22, 0x46,

    /* U+0674 "ٴ" */
    0xe8,

    /* U+0675 "ٵ" */
    0x2a, 0x88, 0x88, 0x88,

    /* U+0676 "ٶ" */
    0x12, 0x16, 0xaa, 0xe2, 0xc0,

    /* U+0677 "ٷ" */
    0x4a, 0xb2, 0x65, 0x29, 0xc2, 0x60,

    /* U+0678 "ٸ" */
    0x1, 0x1, 0x0, 0x40, 0xc0, 0x80, 0xc2, 0x31,
    0x4, 0xc6, 0x3c, 0x0,

    /* U+0679 "ٹ" */
    0xc, 0x6, 0x7, 0x0, 0x0, 0x0, 0x6, 0x3,
    0x1, 0x7f, 0x0,

    /* U+067A "ٺ" */
    0x8, 0x0, 0x2, 0x0, 0x18, 0xc, 0x5, 0xfc,

    /* U+067B "ٻ" */
    0x80, 0xc0, 0x60, 0x2f, 0xe0, 0x0, 0x40, 0x20,

    /* U+067C "ټ" */
    0xc, 0x0, 0x60, 0x30, 0x17, 0xf0, 0x60, 0x20,

    /* U+067D "ٽ" */
    0xc, 0x0, 0x2, 0x0, 0x18, 0xc, 0x5, 0xfc,

    /* U+067E "پ" */
    0x80, 0xc0, 0x60, 0x2f, 0xe0, 0x0, 0x60, 0x20,

    /* U+067F "ٿ" */
    0xc, 0x0, 0x3, 0x0, 0x18, 0xc, 0x5, 0xfc,

    /* U+0680 "ڀ" */
    0x80, 0xc0, 0x60, 0x2f, 0xe0, 0x0, 0x60, 0x30,

    /* U+0681 "ځ" */
    0x20, 0x82, 0x0, 0xe0, 0x72, 0x10, 0x82, 0xc,
    0x1f,

    /* U+0682 "ڂ" */
    0x10, 0x1, 0x0, 0xe0, 0x72, 0x10, 0x82, 0xc,
    0x1f,

    /* U+0683 "ڃ" */
    0xfc, 0x46, 0x20, 0x9a, 0xc, 0x1f,

    /* U+0684 "ڄ" */
    0xe0, 0x72, 0x10, 0x92, 0x4c, 0x1f,

    /* U+0685 "څ" */
    0x10, 0x3, 0x0, 0xe0, 0x72, 0x10, 0x82, 0xc,
    0x1f,

    /* U+0686 "چ" */
    0xf0, 0x33, 0x10, 0x9a, 0x4c, 0xf,

    /* U+0687 "ڇ" */
    0xf0, 0x33, 0x10, 0x9a, 0x6c, 0xf,

    /* U+0688 "ڈ" */
    0x46, 0x60, 0x0, 0x22, 0x11, 0xf0,

    /* U+0689 "ډ" */
    0x22, 0x11, 0xe6, 0x40,

    /* U+068A "ڊ" */
    0x22, 0x11, 0xf0, 0x20,

    /* U+068B "ڋ" */
    0x46, 0x60, 0x0, 0x22, 0x11, 0xf0, 0x20,

    /* U+068C "ڌ" */
    0x60, 0x22, 0x11, 0xe0,

    /* U+068D "ڍ" */
    0x22, 0x11, 0xf0, 0x50,

    /* U+068E "ڎ" */
    0x26, 0x2, 0x21, 0x1e,

    /* U+068F "ڏ" */
    0x62, 0x2, 0x21, 0x1e,

    /* U+0690 "ڐ" */
    0x66, 0x2, 0x21, 0x1e,

    /* U+0691 "ڑ" */
    0x4d, 0x80, 0x1, 0x25, 0x40,

    /* U+0692 "ڒ" */
    0x28, 0x2, 0x4a, 0xc0,

    /* U+0693 "ړ" */
    0x42, 0x22, 0xe2,

    /* U+0694 "ڔ" */
    0x4, 0x95, 0x82,

    /* U+0695 "ڕ" */
    0x4, 0x95, 0x83,

    /* U+0696 "ږ" */
    0x26, 0xa8, 0x10,

    /* U+0697 "ڗ" */
    0x61, 0x12, 0x54,

    /* U+0698 "ژ" */
    0x4c, 0x22, 0x4a, 0x80,

    /* U+0699 "ڙ" */
    0x6c, 0x22, 0x4a, 0x80,

    /* U+069A "ښ" */
    0x0, 0x80, 0x1, 0x0, 0x10, 0x49, 0x84, 0x98,
    0x76, 0x84, 0x7, 0x88,

    /* U+069B "ڛ" */
    0x0, 0x10, 0x49, 0x84, 0x98, 0x77, 0x84, 0x7,
    0x94, 0x0, 0x80,

    /* U+069C "ڜ" */
    0x0, 0x80, 0x14, 0x0, 0x10, 0x1, 0x4, 0x98,
    0x49, 0x87, 0x68, 0x40, 0x79, 0x40, 0x8,

    /* U+069D "ڝ" */
    0x0, 0x70, 0x26, 0x61, 0x43, 0xf, 0xe8, 0x40,
    0x3c, 0x70,

    /* U+069E "ڞ" */
    0x0, 0x20, 0x1, 0x80, 0x0, 0x0, 0xe0, 0x4c,
    0xc2, 0x86, 0x1f, 0xd0, 0x80, 0x78, 0x0,

    /* U+069F "ڟ" */
    0x24, 0x2a, 0x20, 0x2e, 0x31, 0x21, 0xfe,

    /* U+06A0 "ڠ" */
    0x21, 0x40, 0x18, 0x82, 0x7, 0x30, 0x82, 0xc,
    0x1f,

    /* U+06A1 "ڡ" */
    0x3, 0x42, 0x60, 0xf0, 0x17, 0xf0,

    /* U+06A2 "ڢ" */
    0x3, 0x42, 0x60, 0xf0, 0x17, 0xf0, 0x0, 0x20,

    /* U+06A3 "ڣ" */
    0x1, 0x0, 0x0, 0xd0, 0x98, 0x3c, 0x5, 0xfc,
    0x0, 0x1, 0x0,

    /* U+06A4 "ڤ" */
    0x1, 0x0, 0x0, 0xe0, 0x0, 0x34, 0x26, 0xf,
    0x1, 0x7f, 0x0,

    /* U+06A5 "ڥ" */
    0x3, 0x42, 0x60, 0xf0, 0x17, 0xf0, 0x0, 0xa,
    0x2,

    /* U+06A6 "ڦ" */
    0x2, 0x80, 0x0, 0xa0, 0x0, 0x34, 0x26, 0xf,
    0x1, 0x7f, 0x0,

    /* U+06A7 "ڧ" */
    0x4, 0x0, 0x30, 0x98, 0xf0, 0x71, 0xbc,

    /* U+06A8 "ڨ" */
    0x4, 0x14, 0x0, 0x61, 0x31, 0xe0, 0xe3, 0x78,

    /* U+06A9 "ک" */
    0x1, 0x83, 0x1, 0x10, 0x48, 0x14, 0x9, 0xf8,

    /* U+06AA "ڪ" */
    0x6, 0xc, 0x4, 0x1, 0xf0, 0xf, 0xf8,

    /* U+06AB "ګ" */
    0x3, 0x83, 0x81, 0x40, 0x48, 0x14, 0x9, 0xf8,

    /* U+06AC "ڬ" */
    0x8, 0x1, 0x9, 0x9, 0x89, 0x91, 0xc1, 0x7e,

    /* U+06AD "ڭ" */
    0x8, 0x1c, 0x1, 0x9, 0x9, 0x89, 0x91, 0xc1,
    0x7e,

    /* U+06AE "ڮ" */
    0x1, 0x1, 0x9, 0x89, 0x91, 0x81, 0x7e, 0x0,
    0x18, 0x8,

    /* U+06AF "گ" */
    0x0, 0x1, 0x83, 0x60, 0xc0, 0x44, 0x12, 0x5,
    0x2, 0x7e, 0x0,

    /* U+06B0 "ڰ" */
    0x1, 0x1, 0x3, 0xe0, 0xe0, 0x50, 0x12, 0x5,
    0x2, 0x7e, 0x0,

    /* U+06B1 "ڱ" */
    0x6, 0x1, 0x83, 0xc0, 0x80, 0x44, 0x12, 0x5,
    0x82, 0x7e, 0x0,

    /* U+06B2 "ڲ" */
    0x0, 0x1, 0x83, 0x60, 0xc0, 0x44, 0x12, 0x5,
    0x2, 0x7e, 0x0, 0x6, 0x0,

    /* U+06B3 "ڳ" */
    0x0, 0x1, 0x83, 0x60, 0xc0, 0x44, 0x12, 0x5,
    0x2, 0x7e, 0x0, 0x2, 0x1, 0x0,

    /* U+06B4 "ڴ" */
    0x4, 0x3, 0x0, 0xc1, 0xe0, 0x40, 0x22, 0x9,
    0x2, 0xc1, 0x3f, 0x0,

    /* U+06B5 "ڵ" */
    0x10, 0x90, 0x41, 0x4, 0x10, 0x61, 0x86, 0x27,
    0x80,

    /* U+06B6 "ڶ" */
    0x4, 0x50, 0x41, 0x4, 0x18, 0x61, 0x89, 0xe0,

    /* U+06B7 "ڷ" */
    0x10, 0x13, 0x41, 0x4, 0x10, 0x61, 0x86, 0x27,
    0x80,

    /* U+06B8 "ڸ" */
    0x4, 0x10, 0x41, 0x4, 0x18, 0x61, 0x89, 0xe3,
    0x4,

    /* U+06B9 "ڹ" */
    0x10, 0x0, 0x61, 0x86, 0x37, 0x80, 0x10,

    /* U+06BA "ں" */
    0x0, 0x18, 0x61, 0x8d, 0xe0,

    /* U+06BB "ڻ" */
    0x30, 0xc3, 0x2, 0x86, 0x18, 0xde,

    /* U+06BC "ڼ" */
    0x10, 0x0, 0xe1, 0x86, 0x18, 0x9c, 0x30,

    /* U+06BD "ڽ" */
    0x10, 0xa0, 0x2, 0x86, 0x18, 0x63, 0x78,

    /* U+06BE "ھ" */
    0x10, 0x78, 0xb9, 0xdf, 0xe0,

    /* U+06BF "ڿ" */
    0x10, 0xf, 0x3, 0x31, 0x9, 0xa4, 0xc0, 0xf0,

    /* U+06C0 "ۀ" */
    0x64, 0x60, 0x46, 0x99, 0xe0,

    /* U+06C1 "ہ" */
    0x46, 0x99, 0xe0,

    /* U+06C2 "ۂ" */
    0x64, 0x60, 0x46, 0x99, 0xe0,

    /* U+06C3 "ۃ" */
    0x60, 0x46, 0x99, 0xe0,

    /* U+06C4 "ۄ" */
    0x6a, 0xfe, 0xac,

    /* U+06C5 "ۅ" */
    0x6a, 0x9e, 0xec,

    /* U+06C6 "ۆ" */
    0x64, 0x6, 0xaa, 0xe2, 0xc0,

    /* U+06C7 "ۇ" */
    0x4c, 0x6, 0xaa, 0xe2, 0xc0,

    /* U+06C8 "ۈ" */
    0x20, 0x65, 0xd7, 0x1e,

    /* U+06C9 "ۉ" */
    0x42, 0x6, 0xaa, 0xe2, 0xc0,

    /* U+06CA "ۊ" */
    0xa0, 0x6a, 0xae, 0x2c,

    /* U+06CB "ۋ" */
    0x4a, 0x6, 0xaa, 0xe2, 0xc0,

    /* U+06CC "ی" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0,

    /* U+06CD "ۍ" */
    0x3, 0x82, 0x1, 0x18, 0xc4, 0x12, 0x18, 0xf0,

    /* U+06CE "ێ" */
    0x20, 0xcc, 0x20, 0xc8, 0xd0, 0x71, 0xbc,

    /* U+06CF "ۏ" */
    0x40, 0x6a, 0xae, 0x2c,

    /* U+06D0 "ې" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0, 0x10,
    0x20,

    /* U+06D1 "ۑ" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0, 0x28,
    0x20,

    /* U+06D2 "ے" */
    0x30, 0x28, 0x30, 0x10, 0x7, 0xf8,

    /* U+06D3 "ۓ" */
    0x40, 0x40, 0x10, 0x4, 0x5, 0x6, 0x82, 0x0,
    0xff,

    /* U+06D4 "۔" */
    0xe0,

    /* U+06D5 "ە" */
    0x46, 0x99, 0xe0,

    /* U+06D6 "ۖ" */
    0x45, 0xf0,

    /* U+06D7 "ۗ" */
    0x2f, 0x80,

    /* U+06D8 "ۘ" */
    0x3c,

    /* U+06D9 "ۙ" */
    0x78,

    /* U+06DA "ۚ" */
    0xfc,

    /* U+06DB "ۛ" */
    0x70,

    /* U+06DC "ۜ" */
    0x1b, 0xc0,

    /* U+06DD "۝" */
    0x1f, 0x7, 0xc, 0x9f, 0xc6, 0x6, 0x80, 0x18,
    0x1, 0x80, 0x18, 0x1, 0x80, 0x16, 0x6, 0x5f,
    0xc3, 0xc, 0xf, 0x0,

    /* U+06DE "۞" */
    0x18, 0x3f, 0x98, 0xd9, 0x3d, 0x5e, 0x4d, 0x8c,
    0xfe, 0x18, 0x0,

    /* U+06DF "۟" */
    0xf0,

    /* U+06E0 "۠" */
    0xfc,

    /* U+06E1 "ۡ" */
    0x48,

    /* U+06E2 "ۢ" */
    0x58,

    /* U+06E3 "ۣ" */
    0x1b, 0xc0,

    /* U+06E4 "ۤ" */
    0x60,

    /* U+06E5 "ۥ" */
    0xa8,

    /* U+06E6 "ۦ" */
    0x5c,

    /* U+06E7 "ۧ" */
    0x5c,

    /* U+06E8 "ۨ" */
    0x5b, 0x0,

    /* U+06E9 "۩" */
    0x3, 0xe3, 0x94, 0xa5, 0x3f,

    /* U+06EA "۪" */
    0xc8,

    /* U+06EB "۫" */
    0x48,

    /* U+06EC "۬" */
    0xc0,

    /* U+06ED "ۭ" */
    0x58,

    /* U+06EE "ۮ" */
    0x4a, 0x2, 0x21, 0x1f,

    /* U+06EF "ۯ" */
    0x54, 0x2, 0x4a, 0xc0,

    /* U+06F0 "۰" */
    0xc0,

    /* U+06F1 "۱" */
    0xa5, 0x54,

    /* U+06F2 "۲" */
    0x97, 0x44, 0x44, 0x40,

    /* U+06F3 "۳" */
    0x82, 0x67, 0x90, 0x41, 0x4, 0x0,

    /* U+06F4 "۴" */
    0xb5, 0x1c, 0x84, 0x21, 0x0,

    /* U+06F5 "۵" */
    0x6, 0x69, 0x9d, 0xf0,

    /* U+06F6 "۶" */
    0x68, 0x86, 0x48, 0x80,

    /* U+06F7 "۷" */
    0x85, 0x24, 0x94, 0x30, 0xc3, 0x0,

    /* U+06F8 "۸" */
    0x10, 0xc3, 0xc, 0x49, 0x28, 0x40,

    /* U+06F9 "۹" */
    0x6a, 0xaf, 0x11, 0x10,

    /* U+06FA "ۺ" */
    0x0, 0x80, 0x14, 0x0, 0x10, 0x1, 0x4, 0x98,
    0x49, 0x87, 0x68, 0x40, 0x78, 0x80,

    /* U+06FB "ۻ" */
    0x0, 0x20, 0x0, 0x0, 0x1c, 0x9, 0x98, 0x50,
    0xc3, 0xfa, 0x10, 0xf, 0x8,

    /* U+06FC "ۼ" */
    0x20, 0x6, 0x20, 0x91, 0x8c, 0x24, 0x83, 0x7,
    0xc0,

    /* U+06FD "۽" */
    0x68, 0x87, 0x86,

    /* U+06FE "۾" */
    0x70, 0x9d, 0x8, 0x5a, 0x10,

    /* U+06FF "ۿ" */
    0x10, 0x40, 0x0, 0x83, 0xc5, 0xce, 0xff,

    /* U+FE70 "ﹰ" */
    0xd8,

    /* U+FE71 "ﹱ" */
    0xd8, 0x0, 0x7,

    /* U+FE72 "ﹲ" */
    0x7f, 0x0,

    /* U+FE73 "ﹳ" */
    0x92, 0x30,

    /* U+FE74 "ﹴ" */
    0x1b, 0x0,

    /* U+FE76 "ﹶ" */
    0xc0,

    /* U+FE77 "ﹷ" */
    0xc0, 0x0, 0x38,

    /* U+FE78 "ﹸ" */
    0x6f, 0x0,

    /* U+FE79 "ﹹ" */
    0x66, 0xc0, 0x0, 0x0, 0xf0,

    /* U+FE7A "ﹺ" */
    0x18,

    /* U+FE7B "ﹻ" */
    0xe7, 0x0,

    /* U+FE7C "ﹼ" */
    0xfc,

    /* U+FE7D "ﹽ" */
    0xee, 0x0, 0x0, 0xf,

    /* U+FE7E "ﹾ" */
    0xf0,

    /* U+FE7F "ﹿ" */
    0x66, 0x0, 0x0, 0x7,

    /* U+FE80 "ﺀ" */
    0xf2, 0x70,

    /* U+FE81 "ﺁ" */
    0x8c, 0x24, 0x92, 0x40,

    /* U+FE82 "ﺂ" */
    0x86, 0x4, 0x44, 0x44, 0x70,

    /* U+FE83 "ﺃ" */
    0x64, 0x55, 0x50,

    /* U+FE84 "ﺄ" */
    0x48, 0x44, 0x44, 0x44, 0x47,

    /* U+FE85 "ﺅ" */
    0x48, 0x46, 0xaa, 0xe2, 0xc0,

    /* U+FE86 "ﺆ" */
    0x62, 0x0, 0xc5, 0x49, 0xe6, 0xe0,

    /* U+FE87 "ﺇ" */
    0xaa, 0xaa, 0xa0,

    /* U+FE88 "ﺈ" */
    0x92, 0x49, 0x3c, 0x90,

    /* U+FE89 "ﺉ" */
    0x40, 0x8c, 0x20, 0xc8, 0xd0, 0x71, 0xbc,

    /* U+FE8A "ﺊ" */
    0x40, 0x40, 0x0, 0x80, 0x87, 0xc2, 0x7c,

    /* U+FE8B "ﺋ" */
    0xa8, 0x57,

    /* U+FE8C "ﺌ" */
    0x62, 0x10, 0x2, 0x13, 0xe0,

    /* U+FE8D "ﺍ" */
    0xfe,

    /* U+FE8E "ﺎ" */
    0x92, 0x49, 0x38,

    /* U+FE8F "ﺏ" */
    0x80, 0xc0, 0x60, 0x2f, 0xe0, 0x0, 0x40,

    /* U+FE90 "ﺐ" */
    0x80, 0x10, 0xa, 0x7, 0x3f, 0x30, 0x0, 0x10,
    0x0,

    /* U+FE91 "ﺑ" */
    0x56, 0x10,

    /* U+FE92 "ﺒ" */
    0x44, 0xf0, 0x40,

    /* U+FE93 "ﺓ" */
    0x60, 0x46, 0x99, 0xe0,

    /* U+FE94 "ﺔ" */
    0x50, 0x1, 0x1c, 0xd2, 0x4f, 0x7,

    /* U+FE95 "ﺕ" */
    0xc, 0x0, 0x60, 0x30, 0x17, 0xf0,

    /* U+FE96 "ﺖ" */
    0xc, 0x0, 0x2, 0x0, 0x40, 0xe7, 0xe6,

    /* U+FE97 "ﺗ" */
    0xa0, 0x93, 0x80,

    /* U+FE98 "ﺘ" */
    0x60, 0x26, 0xf0,

    /* U+FE99 "ﺙ" */
    0x8, 0x0, 0x3, 0x0, 0x18, 0xc, 0x5, 0xfc,

    /* U+FE9A "ﺚ" */
    0xc, 0x0, 0x0, 0x30, 0x0, 0x8, 0x1, 0x3,
    0x9f, 0x98,

    /* U+FE9B "ﺛ" */
    0x54, 0x12, 0x70,

    /* U+FE9C "ﺜ" */
    0x26, 0x2, 0x6f,

    /* U+FE9D "ﺝ" */
    0xe0, 0x73, 0x10, 0x82, 0x48, 0x30, 0x7c,

    /* U+FE9E "ﺞ" */
    0xe0, 0x38, 0xe2, 0x48, 0x72, 0x20, 0x60, 0x7c,

    /* U+FE9F "ﺟ" */
    0x70, 0x33, 0x38, 0x0, 0x80,

    /* U+FEA0 "ﺠ" */
    0x70, 0x18, 0xe7, 0x30, 0x4, 0x0,

    /* U+FEA1 "ﺡ" */
    0xe0, 0x72, 0x10, 0x82, 0xc, 0x1f,

    /* U+FEA2 "ﺢ" */
    0xfc, 0x71, 0x24, 0x38, 0x10, 0x30, 0x3e,

    /* U+FEA3 "ﺣ" */
    0x70, 0x33, 0x38,

    /* U+FEA4 "ﺤ" */
    0x70, 0x18, 0xe7, 0x30,

    /* U+FEA5 "ﺥ" */
    0x10, 0xe, 0x7, 0x21, 0x8, 0x20, 0xc1, 0xf0,

    /* U+FEA6 "ﺦ" */
    0x10, 0x0, 0x7, 0xe3, 0x89, 0x21, 0xc0, 0x81,
    0x81, 0xf0,

    /* U+FEA7 "ﺧ" */
    0x40, 0x7, 0x3, 0x33, 0x80,

    /* U+FEA8 "ﺨ" */
    0x40, 0x1, 0xc0, 0x63, 0x9c, 0xc0,

    /* U+FEA9 "ﺩ" */
    0x22, 0x11, 0xf0,

    /* U+FEAA "ﺪ" */
    0x20, 0x81, 0x4, 0xec,

    /* U+FEAB "ﺫ" */
    0x20, 0x22, 0x11, 0xe0,

    /* U+FEAC "ﺬ" */
    0x20, 0x2, 0x8, 0x10, 0x4e, 0xc0,

    /* U+FEAD "ﺭ" */
    0x4, 0x95, 0x80,

    /* U+FEAE "ﺮ" */
    0x1, 0x8, 0x74, 0x40,

    /* U+FEAF "ﺯ" */
    0x61, 0x12, 0x54,

    /* U+FEB0 "ﺰ" */
    0x40, 0x0, 0x42, 0x1d, 0x10,

    /* U+FEB1 "ﺱ" */
    0x0, 0x10, 0x49, 0x84, 0x98, 0x77, 0x84, 0x7,
    0x80,

    /* U+FEB2 "ﺲ" */
    0x0, 0x10, 0x12, 0x48, 0x49, 0x21, 0xdb, 0x84,
    0x1, 0xe0, 0x0,

    /* U+FEB3 "ﺳ" */
    0x1, 0x29, 0x69, 0xff,

    /* U+FEB4 "ﺴ" */
    0x2, 0x25, 0x12, 0xd7, 0xf0,

    /* U+FEB5 "ﺵ" */
    0x0, 0x80, 0x14, 0x0, 0x10, 0x1, 0x4, 0x98,
    0x49, 0x87, 0x68, 0x40, 0x78, 0x0,

    /* U+FEB6 "ﺶ" */
    0x0, 0x80, 0x5, 0x0, 0x0, 0x0, 0x4, 0x4,
    0x92, 0x12, 0x48, 0x76, 0xe3, 0x0, 0x78, 0x0,

    /* U+FEB7 "ﺷ" */
    0x8, 0x14, 0x1, 0x1, 0x29, 0x69, 0xfe,

    /* U+FEB8 "ﺸ" */
    0x8, 0xa, 0x0, 0x0, 0x44, 0xa2, 0x5a, 0xfe,

    /* U+FEB9 "ﺹ" */
    0x0, 0x70, 0x26, 0x61, 0x43, 0xf, 0xe8, 0x40,
    0x3c, 0x0,

    /* U+FEBA "ﺺ" */
    0x0, 0x70, 0x13, 0x28, 0x50, 0xa1, 0xff, 0x84,
    0x1, 0xe0, 0x0,

    /* U+FEBB "ﺻ" */
    0x7, 0x26, 0x56, 0x3f, 0xe0,

    /* U+FEBC "ﺼ" */
    0x7, 0x13, 0x25, 0x8b, 0xff,

    /* U+FEBD "ﺽ" */
    0x0, 0x20, 0x0, 0x0, 0x1c, 0x9, 0x98, 0x50,
    0xc3, 0xfa, 0x10, 0xf, 0x0,

    /* U+FEBE "ﺾ" */
    0x0, 0x20, 0x0, 0x0, 0x7, 0x1, 0x32, 0x85,
    0xa, 0x1f, 0xf8, 0x40, 0x1e, 0x0,

    /* U+FEBF "ﺿ" */
    0x2, 0x0, 0x1, 0xc9, 0x95, 0x8f, 0xf8,

    /* U+FEC0 "ﻀ" */
    0x2, 0x0, 0x0, 0x71, 0x32, 0x58, 0xbf, 0xf0,

    /* U+FEC1 "ﻁ" */
    0x20, 0x20, 0x20, 0x2e, 0x31, 0x21, 0xfe,

    /* U+FEC2 "ﻂ" */
    0x20, 0x10, 0x8, 0x5, 0xc3, 0x11, 0xb, 0xfe,

    /* U+FEC3 "ﻃ" */
    0x40, 0x81, 0x2, 0xe7, 0x28, 0x7f, 0x0,

    /* U+FEC4 "ﻄ" */
    0x40, 0x40, 0x40, 0x5c, 0x72, 0x42, 0xff,

    /* U+FEC5 "ﻅ" */
    0x20, 0x24, 0x20, 0x2e, 0x31, 0x21, 0xfe,

    /* U+FEC6 "ﻆ" */
    0x20, 0x12, 0x8, 0x5, 0xc3, 0x11, 0xb, 0xfe,

    /* U+FEC7 "ﻇ" */
    0x40, 0x91, 0x2, 0xe7, 0x28, 0x7f, 0x0,

    /* U+FEC8 "ﻈ" */
    0x40, 0x48, 0x40, 0x5c, 0x72, 0x42, 0xff,

    /* U+FEC9 "ﻉ" */
    0x62, 0x8, 0x1c, 0xc2, 0x8, 0x30, 0x7c,

    /* U+FECA "ﻊ" */
    0x71, 0x43, 0x1f, 0x82, 0x8, 0x1e,

    /* U+FECB "ﻋ" */
    0x32, 0x10, 0xdf, 0x0,

    /* U+FECC "ﻌ" */
    0x39, 0x23, 0x3f,

    /* U+FECD "ﻍ" */
    0x20, 0x6, 0x20, 0x81, 0xcc, 0x20, 0x83, 0x7,
    0xc0,

    /* U+FECE "ﻎ" */
    0x30, 0x7, 0x14, 0x31, 0xf8, 0x20, 0x81, 0xe0,

    /* U+FECF "ﻏ" */
    0x20, 0xc, 0x84, 0x37, 0xc0,

    /* U+FED0 "ﻐ" */
    0x20, 0x3, 0x92, 0x33, 0xf0,

    /* U+FED1 "ﻑ" */
    0x1, 0x0, 0x0, 0xd0, 0x98, 0x3c, 0x5, 0xfc,

    /* U+FED2 "ﻒ" */
    0x0, 0x80, 0x0, 0x6, 0x41, 0x28, 0x25, 0x7,
    0x9f, 0xf8,

    /* U+FED3 "ﻓ" */
    0x20, 0x69, 0x71, 0xe0,

    /* U+FED4 "ﻔ" */
    0x20, 0x3, 0x12, 0x5b, 0xf0,

    /* U+FED5 "ﻕ" */
    0xa, 0x0, 0x30, 0x98, 0xf0, 0x71, 0xbc,

    /* U+FED6 "ﻖ" */
    0xe, 0x0, 0xc, 0xa, 0x92, 0x8f, 0x82, 0xc4,
    0x78,

    /* U+FED7 "ﻗ" */
    0x50, 0x69, 0x71, 0xe0,

    /* U+FED8 "ﻘ" */
    0x50, 0x3, 0x12, 0x5b, 0xf0,

    /* U+FED9 "ﻙ" */
    0x1, 0x1, 0x9, 0x89, 0x91, 0x81, 0x7e,

    /* U+FEDA "ﻚ" */
    0x1, 0x0, 0x40, 0x92, 0x24, 0x91, 0x20, 0x47,
    0xec,

    /* U+FEDB "ﻛ" */
    0x1b, 0x10, 0x41, 0xb, 0xc0,

    /* U+FEDC "ﻜ" */
    0x11, 0x88, 0x18, 0x20, 0x4e, 0xc0,

    /* U+FEDD "ﻝ" */
    0x4, 0x10, 0x41, 0x4, 0x18, 0x61, 0x89, 0xe0,

    /* U+FEDE "ﻞ" */
    0x4, 0x4, 0x4, 0x4, 0x4, 0x84, 0x87, 0x8c,
    0x78,

    /* U+FEDF "ﻟ" */
    0x55, 0x5c,

    /* U+FEE0 "ﻠ" */
    0x44, 0x44, 0x44, 0xf0,

    /* U+FEE1 "ﻡ" */
    0x70, 0x9d, 0x8, 0x42, 0x0,

    /* U+FEE2 "ﻢ" */
    0x31, 0x2e, 0xaf, 0x82, 0x8, 0x10,

    /* U+FEE3 "ﻣ" */
    0x32, 0x53, 0x70,

    /* U+FEE4 "ﻤ" */
    0x30, 0x91, 0x25, 0xf0,

    /* U+FEE5 "ﻥ" */
    0x10, 0x0, 0x61, 0x86, 0x37, 0x80,

    /* U+FEE6 "ﻦ" */
    0x10, 0x0, 0x4, 0x84, 0x87, 0x84, 0x78,

    /* U+FEE7 "ﻧ" */
    0x45, 0x70,

    /* U+FEE8 "ﻨ" */
    0x40, 0x44, 0xf0,

    /* U+FEE9 "ﻩ" */
    0x46, 0x99, 0xe0,

    /* U+FEEA "ﻪ" */
    0x10, 0xcd, 0x24, 0xf0, 0x70,

    /* U+FEEB "ﻫ" */
    0x21, 0xe5, 0xdd, 0xfc,

    /* U+FEEC "ﻬ" */
    0x39, 0xa4, 0xbf, 0x48, 0xe0,

    /* U+FEED "ﻭ" */
    0x6a, 0xae, 0x2c,

    /* U+FEEE "ﻮ" */
    0x62, 0xa4, 0xf3, 0x70,

    /* U+FEEF "ﻯ" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0,

    /* U+FEF0 "ﻰ" */
    0x80, 0x87, 0x82, 0x7c,

    /* U+FEF1 "ﻱ" */
    0x6, 0x10, 0x64, 0x68, 0x38, 0xde, 0x0, 0x28,

    /* U+FEF2 "ﻲ" */
    0x80, 0x87, 0x82, 0x7c, 0x0, 0x28,

    /* U+FEF3 "ﻳ" */
    0x24, 0xe1, 0xc0,

    /* U+FEF4 "ﻴ" */
    0x26, 0xf0, 0x60,

    /* U+FEF5 "ﻵ" */
    0x40, 0x68, 0x11, 0x21, 0xc1, 0x85, 0x1e,

    /* U+FEF6 "ﻶ" */
    0x80, 0xd0, 0x22, 0x42, 0x83, 0x6, 0x37,

    /* U+FEF7 "ﻷ" */
    0xc2, 0xc, 0x82, 0x68, 0x61, 0x8a, 0x78,

    /* U+FEF8 "ﻸ" */
    0x41, 0x1, 0x20, 0x44, 0x85, 0x6, 0xc, 0x6e,

    /* U+FEF9 "ﻹ" */
    0x14, 0xb4, 0x63, 0x2b, 0xd0, 0x84, 0x0,

    /* U+FEFA "ﻺ" */
    0x10, 0x49, 0x14, 0x30, 0xcd, 0xe0, 0x82, 0x0,

    /* U+FEFB "ﻻ" */
    0xa, 0x26, 0x86, 0x18, 0xa7, 0x80,

    /* U+FEFC "ﻼ" */
    0x8, 0x11, 0x21, 0x41, 0x83, 0x1b, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 42, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 44, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 44, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 3, .adv_w = 52, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 4, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 92, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 92, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 44, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 182, .box_w = 11, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 59, .adv_w = 217, .box_w = 14, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 63, .adv_w = 176, .box_w = 11, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 68, .adv_w = 211, .box_w = 13, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 344, .box_w = 20, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 197, .box_w = 12, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 94, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 183, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 117, .adv_w = 109, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 140, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 134, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 137, .adv_w = 148, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 88, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 149, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 151, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 153, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 154, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 156, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 157, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 158, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 160, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 161, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 162, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 163, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 164, .adv_w = 55, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 46, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 73, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 179, .adv_w = 68, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 39, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 39, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 193, .adv_w = 40, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 196, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 203, .adv_w = 40, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 211, .adv_w = 68, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 160, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 236, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 242, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 250, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 61, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 260, .adv_w = 61, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 263, .adv_w = 201, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 272, .adv_w = 201, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 286, .adv_w = 214, .box_w = 13, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 296, .adv_w = 214, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 309, .adv_w = 129, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 129, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 84, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 330, .adv_w = 84, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 339, .adv_w = 142, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 142, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 360, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 367, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 374, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 381, .adv_w = 44, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 159, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 397, .adv_w = 143, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 412, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 417, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 423, .adv_w = 68, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 429, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 436, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 444, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 445, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 447, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 449, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 450, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 452, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 453, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 454, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 455, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 456, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 457, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 458, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 459, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 461, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 462, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 463, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 464, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 465, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 466, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 468, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 470, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 472, .adv_w = 50, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 473, .adv_w = 47, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 77, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 87, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 79, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 40, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 518, .adv_w = 40, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 160, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 127, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 534, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 535, .adv_w = 39, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 39, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 40, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 548, .adv_w = 32, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 549, .adv_w = 67, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 558, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 564, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 576, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 603, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 611, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 627, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 104, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 652, .adv_w = 104, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 661, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 667, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 673, .adv_w = 104, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 682, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 688, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 694, .adv_w = 78, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 704, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 708, .adv_w = 78, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 715, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 723, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 64, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 740, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 744, .adv_w = 61, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 747, .adv_w = 61, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 750, .adv_w = 61, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 753, .adv_w = 61, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 756, .adv_w = 61, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 759, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 763, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 767, .adv_w = 201, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 779, .adv_w = 201, .box_w = 12, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 790, .adv_w = 201, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 805, .adv_w = 214, .box_w = 13, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 815, .adv_w = 214, .box_w = 13, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 830, .adv_w = 129, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 84, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 846, .adv_w = 159, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 852, .adv_w = 159, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 860, .adv_w = 159, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 871, .adv_w = 159, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 159, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 891, .adv_w = 159, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 909, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 917, .adv_w = 142, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 925, .adv_w = 164, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 932, .adv_w = 142, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 143, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 948, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 957, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 967, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 978, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 989, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1000, .adv_w = 142, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1013, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1027, .adv_w = 142, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1039, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1048, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1056, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1065, .adv_w = 113, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1074, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1081, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1086, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1092, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1099, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1106, .adv_w = 112, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 107, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1119, .adv_w = 68, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1124, .adv_w = 68, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1127, .adv_w = 68, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1132, .adv_w = 68, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1139, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1142, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1147, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1152, .adv_w = 74, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1156, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1161, .adv_w = 74, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1165, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1170, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1177, .adv_w = 147, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1185, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1192, .adv_w = 74, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1196, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 1205, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1214, .adv_w = 151, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1220, .adv_w = 151, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1229, .adv_w = 49, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1230, .adv_w = 68, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1233, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 1235, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 1237, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 1238, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 1239, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 1240, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 1241, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1243, .adv_w = 219, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1263, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1274, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1275, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1276, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1277, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 1278, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1280, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1281, .adv_w = 30, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1282, .adv_w = 56, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1283, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1284, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1286, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1291, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1292, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1293, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1294, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1295, .adv_w = 78, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1299, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1303, .adv_w = 50, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1304, .adv_w = 47, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1306, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1316, .adv_w = 82, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1321, .adv_w = 91, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1325, .adv_w = 70, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1329, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1335, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1341, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1345, .adv_w = 201, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1359, .adv_w = 214, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1372, .adv_w = 84, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1381, .adv_w = 68, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1384, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1389, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1396, .adv_w = 49, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1397, .adv_w = 44, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1400, .adv_w = 61, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1402, .adv_w = 43, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1404, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1406, .adv_w = 49, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1407, .adv_w = 44, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1410, .adv_w = 50, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1412, .adv_w = 44, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1417, .adv_w = 47, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1418, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1420, .adv_w = 52, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1421, .adv_w = 44, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1425, .adv_w = 39, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1426, .adv_w = 44, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1430, .adv_w = 68, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1432, .adv_w = 39, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1436, .adv_w = 48, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1441, .adv_w = 39, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1444, .adv_w = 48, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1454, .adv_w = 78, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1460, .adv_w = 40, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1463, .adv_w = 48, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1467, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1474, .adv_w = 121, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1481, .adv_w = 45, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1483, .adv_w = 57, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1488, .adv_w = 40, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1489, .adv_w = 48, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1492, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1499, .adv_w = 177, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1508, .adv_w = 45, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1510, .adv_w = 57, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1513, .adv_w = 68, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1517, .adv_w = 81, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1523, .adv_w = 160, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1529, .adv_w = 177, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1536, .adv_w = 51, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1539, .adv_w = 61, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1542, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1550, .adv_w = 177, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1560, .adv_w = 51, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1563, .adv_w = 61, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1566, .adv_w = 104, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1573, .adv_w = 108, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1581, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1586, .adv_w = 103, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1592, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1598, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1605, .adv_w = 96, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1608, .adv_w = 103, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1612, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1620, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1630, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1635, .adv_w = 103, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1641, .adv_w = 78, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1644, .adv_w = 87, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1648, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1652, .adv_w = 87, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1658, .adv_w = 61, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1661, .adv_w = 66, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1665, .adv_w = 61, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1668, .adv_w = 66, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1673, .adv_w = 201, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1682, .adv_w = 211, .box_w = 14, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1693, .adv_w = 133, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1697, .adv_w = 144, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1702, .adv_w = 201, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1716, .adv_w = 211, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1732, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1739, .adv_w = 144, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1747, .adv_w = 214, .box_w = 13, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1757, .adv_w = 221, .box_w = 14, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1768, .adv_w = 148, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1773, .adv_w = 154, .box_w = 10, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1778, .adv_w = 214, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1791, .adv_w = 221, .box_w = 14, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1805, .adv_w = 148, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1812, .adv_w = 154, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1820, .adv_w = 129, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1827, .adv_w = 134, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1835, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1842, .adv_w = 116, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1849, .adv_w = 129, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1856, .adv_w = 134, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1864, .adv_w = 111, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1871, .adv_w = 116, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1878, .adv_w = 84, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1885, .adv_w = 87, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1891, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1895, .adv_w = 85, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1898, .adv_w = 84, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1907, .adv_w = 87, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1915, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1920, .adv_w = 85, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1925, .adv_w = 159, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1933, .adv_w = 176, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1943, .adv_w = 74, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1947, .adv_w = 81, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1952, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1959, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1968, .adv_w = 74, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1972, .adv_w = 81, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1977, .adv_w = 143, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1984, .adv_w = 150, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1993, .adv_w = 68, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1998, .adv_w = 81, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2004, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2012, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2021, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2023, .adv_w = 50, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2027, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2032, .adv_w = 95, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2038, .adv_w = 87, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2041, .adv_w = 95, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2045, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2051, .adv_w = 120, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2058, .adv_w = 45, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2060, .adv_w = 57, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2063, .adv_w = 68, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2066, .adv_w = 81, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2071, .adv_w = 95, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2075, .adv_w = 84, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2080, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2083, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2087, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2094, .adv_w = 121, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2098, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2106, .adv_w = 121, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2112, .adv_w = 51, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2115, .adv_w = 61, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2118, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2125, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2132, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2139, .adv_w = 100, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2147, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2154, .adv_w = 100, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2162, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2168, .adv_w = 100, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t ar_10 = {
#else
lv_font_t ar_10 = {
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



#endif /*#if AR_10*/

