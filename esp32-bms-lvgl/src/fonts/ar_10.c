/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: --font /System/Library/Fonts/SFArabic.ttf --size 10 --bpp 1 --format lvgl --no-compress --no-kerning --range 0x20-0x7F,0x600-0x6FF,0xFE70-0xFEFF -o src/fonts/ar_10.c
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

    /* U+0022 "\"" */
    0xf0,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x6a, 0xa9,

    /* U+0029 ")" */
    0x49, 0x12, 0x92,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x22, 0x24, 0x44, 0x88,

    /* U+003A ":" */
    0x88,

    /* U+0600 "؀" */
    0x0, 0x70, 0x8, 0x0, 0x8f, 0xff,

    /* U+0601 "؁" */
    0x32, 0x0, 0xa4, 0x2, 0x37, 0xf8,

    /* U+0602 "؂" */
    0x60, 0xa, 0x0, 0xa0, 0xf, 0xff,

    /* U+0603 "؃" */
    0x0, 0xc, 0x1, 0x24, 0x2, 0x8f, 0xff, 0xe0,

    /* U+0604 "؄" */
    0x0, 0x2, 0x1, 0x94, 0x5, 0x28, 0x9, 0xbf,
    0xf8, 0x0,

    /* U+0605 "؅" */
    0xff, 0xe0, 0x0,

    /* U+0606 "؆" */
    0x18, 0x21, 0x2, 0x34, 0x85, 0xc, 0x8,

    /* U+0607 "؇" */
    0x10, 0x22, 0x62, 0x4, 0x69, 0xa, 0x18, 0x10,

    /* U+0608 "؈" */
    0xc, 0x12, 0xd2, 0x4f, 0x42, 0x3c,

    /* U+0609 "؉" */
    0x90, 0x88, 0x84, 0x42, 0xa0,

    /* U+060A "؊" */
    0x90, 0x88, 0x84, 0x42, 0x20,

    /* U+060B "؋" */
    0x30, 0x69, 0x71, 0xe0, 0x20,

    /* U+060C "،" */
    0x60,

    /* U+060D "؍" */
    0xaa,

    /* U+060E "؎" */
    0x60, 0xa0, 0xa0, 0xff,

    /* U+060F "؏" */
    0x72, 0x8, 0x1e, 0xc2, 0xec, 0x7e,

    /* U+0610 "ؐ" */
    0x58,

    /* U+0611 "ؑ" */
    0x70,

    /* U+0612 "ؒ" */
    0x98, 0x80,

    /* U+0613 "ؓ" */
    0x4, 0xc2,

    /* U+0614 "ؔ" */
    0x70,

    /* U+0615 "ؕ" */
    0xbc,

    /* U+0616 "ؖ" */
    0x5c,

    /* U+0617 "ؗ" */
    0x20,

    /* U+0618 "ؘ" */
    0x80,

    /* U+0619 "ؙ" */
    0x50,

    /* U+061A "ؚ" */
    0x80,

    /* U+061B "؛" */
    0x50, 0x30,

    /* U+061C "؜" */
    0x0,

    /* U+061E "؞" */
    0x20, 0x0, 0x8, 0x80,

    /* U+061F "؟" */
    0x74, 0xa0, 0x82, 0x0, 0x80,

    /* U+0620 "ؠ" */
    0xe, 0x22, 0x44, 0x68, 0x4f, 0x8c, 0x0,

    /* U+0621 "ء" */
    0xe8, 0xf8,

    /* U+0622 "آ" */
    0xe9, 0x24, 0x90,

    /* U+0623 "أ" */
    0x53, 0x24, 0x92, 0x40,

    /* U+0624 "ؤ" */
    0x22, 0xc, 0xa5, 0x38, 0x5c,

    /* U+0625 "إ" */
    0x49, 0x24, 0x92, 0x98,

    /* U+0626 "ئ" */
    0xc2, 0x31, 0x24, 0x8e, 0x17, 0x80,

    /* U+0627 "ا" */
    0xfe,

    /* U+0628 "ب" */
    0x81, 0x81, 0x81, 0x7e, 0x0, 0x8,

    /* U+0629 "ة" */
    0x60, 0x69, 0x9f,

    /* U+062A "ت" */
    0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+062B "ث" */
    0x0, 0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+062C "ج" */
    0xe0, 0x66, 0x10, 0x92, 0xc, 0x1f,

    /* U+062D "ح" */
    0xe0, 0x66, 0x10, 0x82, 0xc, 0x1f,

    /* U+062E "خ" */
    0x10, 0xe, 0x6, 0x61, 0x8, 0x20, 0xc1, 0xf0,

    /* U+062F "د" */
    0x10, 0x83, 0x17, 0x80,

    /* U+0630 "ذ" */
    0x0, 0x4, 0x20, 0xc5, 0xe0,

    /* U+0631 "ر" */
    0x24, 0x97, 0x80,

    /* U+0632 "ز" */
    0x0, 0x92, 0x5e,

    /* U+0633 "س" */
    0x9, 0x62, 0x58, 0xee, 0x20, 0x70, 0x0,

    /* U+0634 "ش" */
    0x1, 0x0, 0x0, 0x20, 0x25, 0x89, 0x63, 0xb8,
    0x81, 0xc0,

    /* U+0635 "ص" */
    0x0, 0xc1, 0x66, 0x30, 0xc7, 0xe8, 0x80, 0xe0,
    0x0,

    /* U+0636 "ض" */
    0x1, 0x0, 0x0, 0x3, 0x5, 0x98, 0xc3, 0x1f,
    0xa2, 0x3, 0x80,

    /* U+0637 "ط" */
    0x20, 0x40, 0x81, 0x63, 0x24, 0x7f, 0x0,

    /* U+0638 "ظ" */
    0x20, 0x50, 0x81, 0x63, 0x24, 0x7f, 0x0,

    /* U+0639 "ع" */
    0x74, 0x20, 0x6c, 0x42, 0xf,

    /* U+063A "غ" */
    0x60, 0x1d, 0x8, 0x1b, 0x10, 0x83, 0xc0,

    /* U+063B "ػ" */
    0x4, 0x3, 0xc, 0x18, 0x8c, 0x82, 0x82, 0x7e,

    /* U+063C "ؼ" */
    0x3, 0xc, 0x18, 0x8c, 0x82, 0x82, 0x7e, 0x0,
    0x10, 0x10,

    /* U+063D "ؽ" */
    0x1, 0x9c, 0x44, 0x88, 0xf0, 0x9e, 0x0,

    /* U+063E "ؾ" */
    0xce, 0x22, 0x44, 0x78, 0x4f, 0x0,

    /* U+063F "ؿ" */
    0x40, 0x67, 0x8, 0x48, 0x47, 0x42, 0x3c,

    /* U+0640 "ـ" */
    0xe0,

    /* U+0641 "ف" */
    0x6, 0x0, 0x6, 0x89, 0x87, 0x81, 0x7e,

    /* U+0642 "ق" */
    0x18, 0x1, 0x85, 0xa6, 0x78, 0x5e,

    /* U+0643 "ك" */
    0x2, 0x4, 0x4c, 0xd8, 0x30, 0x5f, 0x0,

    /* U+0644 "ل" */
    0x8, 0x42, 0x10, 0xc6, 0x31, 0x70,

    /* U+0645 "م" */
    0x25, 0x1f, 0x88, 0x88,

    /* U+0646 "ن" */
    0x20, 0x63, 0x18, 0xb8,

    /* U+0647 "ه" */
    0x69, 0x9f,

    /* U+0648 "و" */
    0x32, 0x94, 0xe1, 0x70,

    /* U+0649 "ى" */
    0xe, 0x22, 0x44, 0x78, 0x4f, 0x0,

    /* U+064A "ي" */
    0xe, 0x22, 0x44, 0x68, 0x4f, 0x88, 0x0,

    /* U+064B "ً" */
    0xa0,

    /* U+064C "ٌ" */
    0xb5, 0x0,

    /* U+064D "ٍ" */
    0x50,

    /* U+064E "َ" */
    0x80,

    /* U+064F "ُ" */
    0x50,

    /* U+0650 "ِ" */
    0x40,

    /* U+0651 "ّ" */
    0x30,

    /* U+0652 "ْ" */
    0xf0,

    /* U+0653 "ٓ" */
    0xe0,

    /* U+0654 "ٔ" */
    0xf0,

    /* U+0655 "ٕ" */
    0xf0,

    /* U+0656 "ٖ" */
    0x80,

    /* U+0657 "ٗ" */
    0x28,

    /* U+0658 "٘" */
    0x30,

    /* U+0659 "ٙ" */
    0xc0,

    /* U+065A "ٚ" */
    0xa8,

    /* U+065B "ٛ" */
    0x58,

    /* U+065C "ٜ" */
    0x80,

    /* U+065D "ٝ" */
    0xa0,

    /* U+065E "ٞ" */
    0x80,

    /* U+065F "ٟ" */
    0x7c,

    /* U+0660 "٠" */
    0xc0,

    /* U+0661 "١" */
    0xa5, 0x54,

    /* U+0662 "٢" */
    0x8e, 0x6c, 0x84, 0x21, 0x0,

    /* U+0663 "٣" */
    0x95, 0x56, 0xd0, 0x41, 0x4, 0x0,

    /* U+0664 "٤" */
    0x2c, 0x86, 0xc8, 0xf0,

    /* U+0665 "٥" */
    0x69, 0x99, 0x60,

    /* U+0666 "٦" */
    0xe2, 0x22, 0x22, 0x10,

    /* U+0667 "٧" */
    0x8a, 0x52, 0xa5, 0x18, 0xc0,

    /* U+0668 "٨" */
    0x31, 0x94, 0xa4, 0xa6, 0x20,

    /* U+0669 "٩" */
    0x69, 0x9f, 0x11, 0x10,

    /* U+066A "٪" */
    0x90, 0x88, 0x84, 0x42, 0x60,

    /* U+066B "٫" */
    0xc0,

    /* U+066C "٬" */
    0xc0,

    /* U+066D "٭" */
    0x27, 0xde, 0x40,

    /* U+066E "ٮ" */
    0x81, 0x81, 0x81, 0x7e,

    /* U+066F "ٯ" */
    0x18, 0x5a, 0x67, 0x85, 0xe0,

    /* U+0670 "ٰ" */
    0xc0,

    /* U+0671 "ٱ" */
    0x6f, 0xa4, 0x92, 0x40,

    /* U+0672 "ٲ" */
    0x6b, 0xa4, 0x92, 0x40,

    /* U+0673 "ٳ" */
    0x49, 0x24, 0x93, 0x9c,

    /* U+0674 "ٴ" */
    0xf0,

    /* U+0675 "ٵ" */
    0x3b, 0xc9, 0x24,

    /* U+0676 "ٶ" */
    0x18, 0x8c, 0xa5, 0x38, 0x5c,

    /* U+0677 "ٷ" */
    0x53, 0x4, 0x65, 0x29, 0xc2, 0xe0,

    /* U+0678 "ٸ" */
    0x4, 0x10, 0x30, 0x71, 0x12, 0x23, 0xc2, 0x78,

    /* U+0679 "ٹ" */
    0x10, 0x18, 0x18, 0x81, 0x81, 0x81, 0x7e,

    /* U+067A "ٺ" */
    0x0, 0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+067B "ٻ" */
    0x81, 0x81, 0x81, 0x7e, 0x0, 0x0, 0x0,

    /* U+067C "ټ" */
    0x18, 0x0, 0x81, 0x81, 0x81, 0x7e, 0x18, 0x18,

    /* U+067D "ٽ" */
    0x18, 0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+067E "پ" */
    0x81, 0x81, 0x81, 0x7e, 0x0, 0x18, 0x0,

    /* U+067F "ٿ" */
    0x18, 0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+0680 "ڀ" */
    0x81, 0x81, 0x81, 0x7e, 0x0, 0x18, 0x18,

    /* U+0681 "ځ" */
    0x30, 0x83, 0x38, 0x19, 0x88, 0x20, 0xc1, 0xf0,

    /* U+0682 "ڂ" */
    0x10, 0x0, 0x38, 0x19, 0x84, 0x20, 0x83, 0x7,
    0xc0,

    /* U+0683 "ڃ" */
    0xe0, 0x66, 0x10, 0xb2, 0xc, 0x1f,

    /* U+0684 "ڄ" */
    0xe0, 0x66, 0x10, 0x82, 0x4c, 0x1f,

    /* U+0685 "څ" */
    0x10, 0xc0, 0x38, 0x19, 0x84, 0x20, 0x83, 0x7,
    0xc0,

    /* U+0686 "چ" */
    0xe0, 0x66, 0x10, 0xb2, 0x4c, 0x1f,

    /* U+0687 "ڇ" */
    0xe0, 0x66, 0x10, 0x82, 0x8c, 0x1f,

    /* U+0688 "ڈ" */
    0x21, 0x8c, 0x1, 0x6, 0x2f,

    /* U+0689 "ډ" */
    0x10, 0x83, 0x17, 0xb0, 0x80,

    /* U+068A "ڊ" */
    0x10, 0x83, 0x17, 0x80, 0x80,

    /* U+068B "ڋ" */
    0x21, 0x8c, 0x1, 0x6, 0x2f, 0x1, 0x0,

    /* U+068C "ڌ" */
    0x10, 0x4, 0x20, 0xc5, 0xe0,

    /* U+068D "ڍ" */
    0x10, 0x83, 0x17, 0x80, 0x40,

    /* U+068E "ڎ" */
    0x0, 0xc, 0x21, 0x6, 0x2f,

    /* U+068F "ڏ" */
    0x30, 0x0, 0x21, 0x6, 0x2f,

    /* U+0690 "ڐ" */
    0x30, 0xc, 0x21, 0x6, 0x2f,

    /* U+0691 "ڑ" */
    0x23, 0x30, 0x11, 0x13, 0xe0,

    /* U+0692 "ڒ" */
    0x68, 0x92, 0x5e,

    /* U+0693 "ړ" */
    0x11, 0x11, 0x3e, 0x40,

    /* U+0694 "ڔ" */
    0x24, 0x97, 0x80,

    /* U+0695 "ڕ" */
    0x24, 0x97, 0x86,

    /* U+0696 "ږ" */
    0x0, 0x92, 0x5e, 0x0,

    /* U+0697 "ڗ" */
    0x4, 0x92, 0x5e,

    /* U+0698 "ژ" */
    0x40, 0x92, 0x4b, 0xc0,

    /* U+0699 "ڙ" */
    0x60, 0x92, 0x4b, 0xc0,

    /* U+069A "ښ" */
    0x1, 0x0, 0x40, 0x96, 0x25, 0x8e, 0xe2, 0x47,
    0x10,

    /* U+069B "ڛ" */
    0x9, 0x62, 0x58, 0xee, 0x20, 0x72, 0x0, 0x40,

    /* U+069C "ڜ" */
    0x1, 0x0, 0x0, 0x20, 0x25, 0x89, 0x63, 0xb8,
    0x81, 0xc8, 0x1, 0x0,

    /* U+069D "ڝ" */
    0x0, 0xc1, 0x66, 0x30, 0xc7, 0xe8, 0x80, 0xe1,
    0x0,

    /* U+069E "ڞ" */
    0x1, 0x0, 0x10, 0x0, 0x0, 0x60, 0xb3, 0x18,
    0x63, 0xf4, 0x40, 0x70, 0x0,

    /* U+069F "ڟ" */
    0x28, 0x40, 0x81, 0x63, 0x24, 0x7f, 0x0,

    /* U+06A0 "ڠ" */
    0x23, 0x80, 0xe8, 0x40, 0xd8, 0x84, 0x1e,

    /* U+06A1 "ڡ" */
    0x6, 0x89, 0x87, 0x81, 0x7e,

    /* U+06A2 "ڢ" */
    0x6, 0x89, 0x87, 0x81, 0x7e, 0x0, 0x8,

    /* U+06A3 "ڣ" */
    0x6, 0x0, 0x6, 0x89, 0x87, 0x81, 0x7e, 0x0,
    0x8,

    /* U+06A4 "ڤ" */
    0x0, 0x6, 0x0, 0x6, 0x89, 0x87, 0x81, 0x7e,

    /* U+06A5 "ڥ" */
    0x6, 0x89, 0x87, 0x81, 0x7e, 0x0, 0x10, 0x0,

    /* U+06A6 "ڦ" */
    0x6, 0x6, 0x0, 0x6, 0x89, 0x87, 0x81, 0x7e,

    /* U+06A7 "ڧ" */
    0x8, 0x1, 0x85, 0xa6, 0x78, 0x5e,

    /* U+06A8 "ڨ" */
    0x8, 0x70, 0x6, 0x16, 0x99, 0xe1, 0x78,

    /* U+06A9 "ک" */
    0x3, 0xc, 0x18, 0x8c, 0x82, 0x82, 0x7e,

    /* U+06AA "ڪ" */
    0x4, 0x4, 0xc, 0xf, 0xe0, 0xf, 0xfc,

    /* U+06AB "ګ" */
    0x1, 0x6, 0x1a, 0x8, 0x84, 0x82, 0x7e,

    /* U+06AC "ڬ" */
    0x12, 0x4, 0x4c, 0xd8, 0x30, 0x5f, 0x0,

    /* U+06AD "ڭ" */
    0x10, 0x34, 0x8, 0x99, 0xb0, 0x60, 0xbe,

    /* U+06AE "ڮ" */
    0x2, 0x4, 0x4c, 0xd8, 0x30, 0x5f, 0x0, 0x0,
    0x20,

    /* U+06AF "گ" */
    0x2, 0xf, 0xc, 0x18, 0x8c, 0x82, 0x82, 0x7e,

    /* U+06B0 "ڰ" */
    0x1, 0x7, 0x1e, 0x1a, 0x8, 0x84, 0x82, 0x7e,

    /* U+06B1 "ڱ" */
    0x0, 0x12, 0xf, 0xc, 0x18, 0x8c, 0x82, 0x82,
    0x7e,

    /* U+06B2 "ڲ" */
    0x2, 0xf, 0xc, 0x18, 0x8c, 0x82, 0x82, 0x7e,
    0x0, 0x38,

    /* U+06B3 "ڳ" */
    0x2, 0xf, 0xc, 0x18, 0x8c, 0x82, 0x82, 0x7e,
    0x0, 0x10, 0x10,

    /* U+06B4 "ڴ" */
    0x0, 0x12, 0xf, 0xc, 0x18, 0x8c, 0x82, 0x82,
    0x7e,

    /* U+06B5 "ڵ" */
    0x14, 0x20, 0x2, 0x8, 0x20, 0xa2, 0x8a, 0x27,
    0x0,

    /* U+06B6 "ڶ" */
    0x8, 0x2, 0x10, 0x86, 0x31, 0x8b, 0x80,

    /* U+06B7 "ڷ" */
    0x8, 0x50, 0x2, 0x8, 0x20, 0xa2, 0x8a, 0x27,
    0x0,

    /* U+06B8 "ڸ" */
    0x8, 0x42, 0x10, 0xc6, 0x31, 0x70, 0x8,

    /* U+06B9 "ڹ" */
    0x20, 0x63, 0x18, 0xb8, 0x4,

    /* U+06BA "ں" */
    0xc, 0x63, 0x17, 0x0,

    /* U+06BB "ڻ" */
    0x43, 0x18, 0x18, 0xc6, 0x2e,

    /* U+06BC "ڼ" */
    0x20, 0x23, 0x18, 0xc5, 0xc4,

    /* U+06BD "ڽ" */
    0x21, 0x10, 0x18, 0xc6, 0x2e,

    /* U+06BE "ھ" */
    0x71, 0x75, 0x7f,

    /* U+06BF "ڿ" */
    0x10, 0xe, 0x6, 0x61, 0xb, 0x24, 0xc1, 0xf0,

    /* U+06C0 "ۀ" */
    0x64, 0x6, 0x99, 0xf0,

    /* U+06C1 "ہ" */
    0x69, 0x9f,

    /* U+06C2 "ۂ" */
    0x64, 0x6, 0x99, 0xf0,

    /* U+06C3 "ۃ" */
    0x60, 0x69, 0x9f,

    /* U+06C4 "ۄ" */
    0x32, 0x9c, 0xa7, 0x70,

    /* U+06C5 "ۅ" */
    0x32, 0x9c, 0xee, 0x0,

    /* U+06C6 "ۆ" */
    0x51, 0xc, 0xa5, 0x38, 0x5c,

    /* U+06C7 "ۇ" */
    0x21, 0x10, 0x65, 0x29, 0xc2, 0xe0,

    /* U+06C8 "ۈ" */
    0x20, 0x65, 0x57, 0x1e,

    /* U+06C9 "ۉ" */
    0x20, 0x8c, 0xa5, 0x38, 0x5c,

    /* U+06CA "ۊ" */
    0x70, 0xc, 0xa5, 0x38, 0x5c,

    /* U+06CB "ۋ" */
    0x23, 0x80, 0x65, 0x29, 0xc2, 0xe0,

    /* U+06CC "ی" */
    0xe, 0x22, 0x44, 0x78, 0x4f, 0x0,

    /* U+06CD "ۍ" */
    0x7, 0x8, 0xc8, 0x47, 0x42, 0x3c,

    /* U+06CE "ێ" */
    0x1, 0x9c, 0x44, 0x88, 0xf0, 0x9e, 0x0,

    /* U+06CF "ۏ" */
    0x20, 0xc, 0xa5, 0x38, 0x5c,

    /* U+06D0 "ې" */
    0xe, 0x22, 0x44, 0x68, 0x4f, 0x0, 0x0,

    /* U+06D1 "ۑ" */
    0xe, 0x22, 0x44, 0x68, 0x4f, 0x8, 0x0,

    /* U+06D2 "ے" */
    0x30, 0x40, 0x80, 0xff,

    /* U+06D3 "ۓ" */
    0x30, 0x40, 0x20, 0x30, 0x40, 0x80, 0xff,

    /* U+06D4 "۔" */
    0xc0,

    /* U+06D5 "ە" */
    0x69, 0x9f,

    /* U+06D6 "ۖ" */
    0x43, 0xfe,

    /* U+06D7 "ۗ" */
    0x6f, 0x80,

    /* U+06D8 "ۘ" */
    0x3c,

    /* U+06D9 "ۙ" */
    0x68,

    /* U+06DA "ۚ" */
    0xfc,

    /* U+06DB "ۛ" */
    0x4a, 0x0,

    /* U+06DC "ۜ" */
    0x53, 0xc0,

    /* U+06DD "۝" */
    0x7f, 0xaf, 0xe6, 0x1a, 0x1, 0x80, 0x60, 0x18,
    0x5, 0xfe, 0x61, 0x87, 0x80,

    /* U+06DE "۞" */
    0x4, 0x1, 0x80, 0xfe, 0x10, 0x46, 0x4d, 0x55,
    0x59, 0x31, 0x8c, 0x3f, 0x81, 0x80,

    /* U+06DF "۟" */
    0xf0,

    /* U+06E0 "۠" */
    0xfc,

    /* U+06E1 "ۡ" */
    0xb0,

    /* U+06E2 "ۢ" */
    0x78,

    /* U+06E3 "ۣ" */
    0xe0,

    /* U+06E4 "ۤ" */
    0xf0,

    /* U+06E5 "ۥ" */
    0xb8,

    /* U+06E6 "ۦ" */
    0xb0,

    /* U+06E7 "ۧ" */
    0x9c,

    /* U+06E8 "ۨ" */
    0xc,

    /* U+06E9 "۩" */
    0x7a, 0x18, 0x52, 0x49, 0x27, 0x80,

    /* U+06EA "۪" */
    0x30,

    /* U+06EB "۫" */
    0xa0,

    /* U+06EC "۬" */
    0x80,

    /* U+06ED "ۭ" */
    0x78,

    /* U+06EE "ۮ" */
    0x30, 0x4, 0x20, 0xc5, 0xe0,

    /* U+06EF "ۯ" */
    0x4c, 0x92, 0x5e,

    /* U+06F0 "۰" */
    0xc0,

    /* U+06F1 "۱" */
    0xa5, 0x54,

    /* U+06F2 "۲" */
    0x8e, 0x6c, 0x84, 0x21, 0x0,

    /* U+06F3 "۳" */
    0x95, 0x56, 0xd0, 0x41, 0x4, 0x0,

    /* U+06F4 "۴" */
    0xbf, 0x2e, 0x84, 0x21, 0x0,

    /* U+06F5 "۵" */
    0x21, 0x95, 0x1a, 0xd7, 0x60,

    /* U+06F6 "۶" */
    0x68, 0x87, 0x48, 0x80,

    /* U+06F7 "۷" */
    0x8a, 0x52, 0xa5, 0x18, 0xc0,

    /* U+06F8 "۸" */
    0x31, 0x94, 0xa4, 0xa6, 0x20,

    /* U+06F9 "۹" */
    0x69, 0x9f, 0x11, 0x10,

    /* U+06FA "ۺ" */
    0x1, 0x0, 0x0, 0x20, 0x25, 0x89, 0x63, 0xb8,
    0x91, 0xc4,

    /* U+06FB "ۻ" */
    0x1, 0x0, 0x0, 0x3, 0x5, 0x98, 0xc3, 0x1f,
    0xa2, 0x3, 0x88,

    /* U+06FC "ۼ" */
    0x60, 0x1d, 0x8, 0x1b, 0x14, 0x83, 0xc0,

    /* U+06FD "۽" */
    0x68, 0x8f, 0xa,

    /* U+06FE "۾" */
    0x25, 0x1f, 0x8b, 0x80,

    /* U+06FF "ۿ" */
    0x10, 0xc0, 0x1c, 0x5d, 0x5f, 0xc0,

    /* U+FE70 "ﹰ" */
    0xa0,

    /* U+FE71 "ﹱ" */
    0xd8, 0x1, 0xc0,

    /* U+FE72 "ﹲ" */
    0xb5, 0x0,

    /* U+FE74 "ﹴ" */
    0x50,

    /* U+FE76 "ﹶ" */
    0x80,

    /* U+FE77 "ﹷ" */
    0xc0, 0xe,

    /* U+FE78 "ﹸ" */
    0x50,

    /* U+FE79 "ﹹ" */
    0x22, 0x0, 0x7,

    /* U+FE7A "ﹺ" */
    0x40,

    /* U+FE7B "ﹻ" */
    0xe3, 0x0,

    /* U+FE7C "ﹼ" */
    0x30,

    /* U+FE7D "ﹽ" */
    0x18, 0x1, 0xc0,

    /* U+FE7E "ﹾ" */
    0xf0,

    /* U+FE7F "ﹿ" */
    0x66, 0x0, 0x7,

    /* U+FE80 "ﺀ" */
    0xe8, 0xf8,

    /* U+FE81 "ﺁ" */
    0xe9, 0x24, 0x90,

    /* U+FE82 "ﺂ" */
    0xe9, 0x24, 0x98,

    /* U+FE83 "ﺃ" */
    0x53, 0x24, 0x92, 0x40,

    /* U+FE84 "ﺄ" */
    0x53, 0x24, 0x92, 0x60,

    /* U+FE85 "ﺅ" */
    0x22, 0xc, 0xa5, 0x38, 0x5c,

    /* U+FE86 "ﺆ" */
    0x22, 0xc, 0xa5, 0x3c, 0x5c,

    /* U+FE87 "ﺇ" */
    0x49, 0x24, 0x92, 0x98,

    /* U+FE88 "ﺈ" */
    0x49, 0x24, 0x9b, 0x98,

    /* U+FE89 "ﺉ" */
    0xc2, 0x31, 0x24, 0x8e, 0x17, 0x80,

    /* U+FE8A "ﺊ" */
    0xc1, 0x0, 0x4, 0x8, 0xf0, 0x9e, 0x0,

    /* U+FE8B "ﺋ" */
    0x6c, 0x93, 0xc0,

    /* U+FE8C "ﺌ" */
    0x51, 0x25, 0x40,

    /* U+FE8D "ﺍ" */
    0xfe,

    /* U+FE8E "ﺎ" */
    0xaa, 0xac,

    /* U+FE8F "ﺏ" */
    0x81, 0x81, 0x81, 0x7e, 0x0, 0x8,

    /* U+FE90 "ﺐ" */
    0x80, 0x40, 0xa0, 0x4f, 0xd0, 0x0, 0x40,

    /* U+FE91 "ﺑ" */
    0x57, 0x20,

    /* U+FE92 "ﺒ" */
    0x4a, 0x84,

    /* U+FE93 "ﺓ" */
    0x60, 0x69, 0x9f,

    /* U+FE94 "ﺔ" */
    0x0, 0x84, 0x6d, 0x38, 0x60,

    /* U+FE95 "ﺕ" */
    0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+FE96 "ﺖ" */
    0x18, 0x0, 0x20, 0x10, 0x28, 0x13, 0xf4,

    /* U+FE97 "ﺗ" */
    0xc1, 0x25, 0x80,

    /* U+FE98 "ﺘ" */
    0xa1, 0x2a,

    /* U+FE99 "ﺙ" */
    0x0, 0x18, 0x0, 0x81, 0x81, 0x81, 0x7e,

    /* U+FE9A "ﺚ" */
    0x0, 0xc, 0x0, 0x10, 0x8, 0x14, 0x9, 0xfa,

    /* U+FE9B "ﺛ" */
    0x5c, 0x24, 0xb0,

    /* U+FE9C "ﺜ" */
    0x4a, 0x84, 0xa8,

    /* U+FE9D "ﺝ" */
    0xe0, 0x66, 0x10, 0x92, 0xc, 0x1f,

    /* U+FE9E "ﺞ" */
    0xe0, 0xe2, 0x92, 0x8e, 0xc, 0x1f,

    /* U+FE9F "ﺟ" */
    0x70, 0x31, 0x38, 0x0, 0x0,

    /* U+FEA0 "ﺠ" */
    0x70, 0x18, 0x77, 0x30, 0x0, 0x0,

    /* U+FEA1 "ﺡ" */
    0xe0, 0x66, 0x10, 0x82, 0xc, 0x1f,

    /* U+FEA2 "ﺢ" */
    0xe0, 0xe2, 0x92, 0x8e, 0xc, 0x1f,

    /* U+FEA3 "ﺣ" */
    0x70, 0x31, 0x38,

    /* U+FEA4 "ﺤ" */
    0x70, 0x18, 0x77, 0x30,

    /* U+FEA5 "ﺥ" */
    0x10, 0xe, 0x6, 0x61, 0x8, 0x20, 0xc1, 0xf0,

    /* U+FEA6 "ﺦ" */
    0x30, 0xe, 0xe, 0x29, 0x28, 0xe0, 0xc1, 0xf0,

    /* U+FEA7 "ﺧ" */
    0x30, 0x7, 0x3, 0x13, 0x80,

    /* U+FEA8 "ﺨ" */
    0x10, 0x1, 0xc0, 0x61, 0xdc, 0xc0,

    /* U+FEA9 "ﺩ" */
    0x10, 0x83, 0x17, 0x80,

    /* U+FEAA "ﺪ" */
    0x0, 0x41, 0x24, 0xfc,

    /* U+FEAB "ﺫ" */
    0x0, 0x4, 0x20, 0xc5, 0xe0,

    /* U+FEAC "ﺬ" */
    0x0, 0x0, 0x4, 0x12, 0x4f, 0xc0,

    /* U+FEAD "ﺭ" */
    0x24, 0x97, 0x80,

    /* U+FEAE "ﺮ" */
    0x22, 0x36, 0xc0,

    /* U+FEAF "ﺯ" */
    0x0, 0x92, 0x5e,

    /* U+FEB0 "ﺰ" */
    0x60, 0x22, 0x36, 0xc0,

    /* U+FEB1 "ﺱ" */
    0x9, 0x62, 0x58, 0xee, 0x20, 0x70, 0x0,

    /* U+FEB2 "ﺲ" */
    0x9, 0x51, 0x2a, 0x3a, 0xc4, 0x7, 0x0,

    /* U+FEB3 "ﺳ" */
    0x55, 0x5e, 0xc0,

    /* U+FEB4 "ﺴ" */
    0x54, 0xab, 0xa8,

    /* U+FEB5 "ﺵ" */
    0x1, 0x0, 0x0, 0x20, 0x25, 0x89, 0x63, 0xb8,
    0x81, 0xc0,

    /* U+FEB6 "ﺶ" */
    0x1, 0x0, 0x0, 0x8, 0x4, 0xa8, 0x95, 0x1d,
    0x62, 0x3, 0x80,

    /* U+FEB7 "ﺷ" */
    0x10, 0x0, 0x15, 0x57, 0xb0,

    /* U+FEB8 "ﺸ" */
    0x10, 0x0, 0x2, 0xa5, 0x5d, 0x40,

    /* U+FEB9 "ﺹ" */
    0x0, 0xc1, 0x66, 0x30, 0xc7, 0xe8, 0x80, 0xe0,
    0x0,

    /* U+FEBA "ﺺ" */
    0x0, 0xc0, 0xb2, 0x8c, 0x28, 0xff, 0x88, 0x7,
    0x0,

    /* U+FEBB "ﺻ" */
    0x6, 0x49, 0x51, 0xfe,

    /* U+FEBC "ﺼ" */
    0x6, 0x24, 0x94, 0x5f, 0xf0,

    /* U+FEBD "ﺽ" */
    0x1, 0x0, 0x0, 0x3, 0x5, 0x98, 0xc3, 0x1f,
    0xa2, 0x3, 0x80,

    /* U+FEBE "ﺾ" */
    0x1, 0x0, 0x0, 0x0, 0xc0, 0xb2, 0x8c, 0x28,
    0xff, 0x88, 0x7, 0x0,

    /* U+FEBF "ﺿ" */
    0xc, 0x0, 0x6, 0x49, 0x51, 0xfe,

    /* U+FEC0 "ﻀ" */
    0xc, 0x0, 0x1, 0x89, 0x25, 0x17, 0xfc,

    /* U+FEC1 "ﻁ" */
    0x20, 0x40, 0x81, 0x63, 0x24, 0x7f, 0x0,

    /* U+FEC2 "ﻂ" */
    0x20, 0x20, 0x20, 0x2c, 0x32, 0x22, 0xff,

    /* U+FEC3 "ﻃ" */
    0x41, 0x4, 0x16, 0x65, 0x1f, 0x80,

    /* U+FEC4 "ﻄ" */
    0x40, 0x81, 0x2, 0xc6, 0x48, 0xbf, 0x80,

    /* U+FEC5 "ﻅ" */
    0x20, 0x50, 0x81, 0x63, 0x24, 0x7f, 0x0,

    /* U+FEC6 "ﻆ" */
    0x20, 0x28, 0x20, 0x2c, 0x32, 0x22, 0xff,

    /* U+FEC7 "ﻇ" */
    0x41, 0x44, 0x16, 0x65, 0x1f, 0x80,

    /* U+FEC8 "ﻈ" */
    0x40, 0xa1, 0x2, 0xc6, 0x48, 0xbf, 0x80,

    /* U+FEC9 "ﻉ" */
    0x74, 0x20, 0x6c, 0x42, 0xf,

    /* U+FECA "ﻊ" */
    0x72, 0x8c, 0xb8, 0x41, 0xe0,

    /* U+FECB "ﻋ" */
    0x3a, 0x11, 0xf0,

    /* U+FECC "ﻌ" */
    0x79, 0x23, 0x3f,

    /* U+FECD "ﻍ" */
    0x60, 0x1d, 0x8, 0x1b, 0x10, 0x83, 0xc0,

    /* U+FECE "ﻎ" */
    0x20, 0x1c, 0xa3, 0x2e, 0x10, 0x78,

    /* U+FECF "ﻏ" */
    0x10, 0xe, 0x84, 0x7c,

    /* U+FED0 "ﻐ" */
    0x30, 0x7, 0x92, 0x33, 0xf0,

    /* U+FED1 "ﻑ" */
    0x6, 0x0, 0x6, 0x89, 0x87, 0x81, 0x7e,

    /* U+FED2 "ﻒ" */
    0x2, 0x0, 0x21, 0xd1, 0x28, 0x53, 0xfc,

    /* U+FED3 "ﻓ" */
    0x60, 0x69, 0x71, 0xe0,

    /* U+FED4 "ﻔ" */
    0x60, 0x1d, 0x25, 0x7c,

    /* U+FED5 "ﻕ" */
    0x18, 0x1, 0x85, 0xa6, 0x78, 0x5e,

    /* U+FED6 "ﻖ" */
    0x18, 0x0, 0x61, 0x2a, 0x53, 0xe1, 0x3c,

    /* U+FED7 "ﻗ" */
    0x60, 0x69, 0x71, 0xe0,

    /* U+FED8 "ﻘ" */
    0x60, 0x1d, 0x25, 0x7c,

    /* U+FED9 "ﻙ" */
    0x2, 0x4, 0x4c, 0xd8, 0x30, 0x5f, 0x0,

    /* U+FEDA "ﻚ" */
    0x2, 0x2, 0x12, 0x92, 0x82, 0x82, 0x7d,

    /* U+FEDB "ﻛ" */
    0x9, 0x90, 0x41, 0xf, 0xc0,

    /* U+FEDC "ﻜ" */
    0x8, 0xc4, 0x18, 0x20, 0x4e, 0xc0,

    /* U+FEDD "ﻝ" */
    0x8, 0x42, 0x10, 0xc6, 0x31, 0x70,

    /* U+FEDE "ﻞ" */
    0x8, 0x20, 0x82, 0xa, 0x28, 0xe2, 0x70,

    /* U+FEDF "ﻟ" */
    0x55, 0x58,

    /* U+FEE0 "ﻠ" */
    0x49, 0x24, 0xa8,

    /* U+FEE1 "ﻡ" */
    0x25, 0x1f, 0x88, 0x88,

    /* U+FEE2 "ﻢ" */
    0x18, 0x51, 0xa5, 0xe8, 0x10, 0x20, 0x0,

    /* U+FEE3 "ﻣ" */
    0x32, 0x53, 0x70,

    /* U+FEE4 "ﻤ" */
    0x31, 0x44, 0xbf,

    /* U+FEE5 "ﻥ" */
    0x20, 0x63, 0x18, 0xb8,

    /* U+FEE6 "ﻦ" */
    0x20, 0x80, 0xa2, 0x8e, 0x27, 0x0,

    /* U+FEE7 "ﻧ" */
    0xc5, 0x70,

    /* U+FEE8 "ﻨ" */
    0x41, 0x2a,

    /* U+FEEA "ﻪ" */
    0x11, 0xb4, 0xe1, 0x80,

    /* U+FEEB "ﻫ" */
    0x71, 0x75, 0x7f,

    /* U+FEEC "ﻬ" */
    0x32, 0x95, 0xf5, 0x18,

    /* U+FEED "ﻭ" */
    0x32, 0x94, 0xe1, 0x70,

    /* U+FEEE "ﻮ" */
    0x32, 0x94, 0xf1, 0x70,

    /* U+FEEF "ﻯ" */
    0xe, 0x22, 0x44, 0x78, 0x4f, 0x0,

    /* U+FEF0 "ﻰ" */
    0x81, 0x1e, 0x13, 0xc0,

    /* U+FEF1 "ﻱ" */
    0xe, 0x22, 0x44, 0x68, 0x4f, 0x88, 0x0,

    /* U+FEF2 "ﻲ" */
    0x81, 0x1e, 0x13, 0xc2, 0x0,

    /* U+FEF3 "ﻳ" */
    0x24, 0xb0, 0x40,

    /* U+FEF4 "ﻴ" */
    0x4a, 0x8a,

    /* U+FEF5 "ﻵ" */
    0xd1, 0x95, 0x25, 0xf0,

    /* U+FEF6 "ﻶ" */
    0xe8, 0x24, 0x8a, 0x28, 0xaf, 0x40,

    /* U+FEF7 "ﻷ" */
    0xc8, 0x91, 0x97, 0x35, 0xf0,

    /* U+FEF8 "ﻸ" */
    0xc6, 0x85, 0x25, 0x28, 0xdd,

    /* U+FEF9 "ﻹ" */
    0x19, 0x53, 0x35, 0xf4, 0x8c,

    /* U+FEFA "ﻺ" */
    0x14, 0xa4, 0xa5, 0x1b, 0xb8, 0x84, 0x0,

    /* U+FEFB "ﻻ" */
    0x19, 0x53, 0x35, 0xf0,

    /* U+FEFC "ﻼ" */
    0x9, 0x24, 0x8a, 0x28, 0x6f, 0x40
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 33, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 49, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 65, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 3, .adv_w = 41, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 56, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 6, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 9, .adv_w = 38, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 60, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 14, .adv_w = 36, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 201, .box_w = 12, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 21, .adv_w = 251, .box_w = 15, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 27, .adv_w = 207, .box_w = 12, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 241, .box_w = 15, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 41, .adv_w = 258, .box_w = 15, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 51, .adv_w = 180, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 54, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 138, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 69, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 50, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 92, .adv_w = 140, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 102, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 103, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 104, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 106, .adv_w = 0, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 108, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 109, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 110, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 111, .adv_w = 0, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 112, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 113, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 114, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 115, .adv_w = 39, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 59, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 104, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 81, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 134, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 38, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 38, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 148, .adv_w = 38, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 152, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 38, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 165, .adv_w = 71, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 187, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 193, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 201, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 56, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 213, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 216, .adv_w = 174, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 223, .adv_w = 174, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 233, .adv_w = 185, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 242, .adv_w = 185, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 253, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 272, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 279, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 297, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 304, .adv_w = 118, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 310, .adv_w = 118, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 317, .adv_w = 44, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 145, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 331, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 101, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 344, .adv_w = 83, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 348, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 352, .adv_w = 71, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 73, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 358, .adv_w = 118, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 364, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 371, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 372, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 374, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 375, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 376, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 377, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 378, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 379, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 380, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 381, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 382, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 383, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 384, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 385, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 386, .adv_w = 0, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 387, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 388, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 389, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 390, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 391, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 392, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 393, .adv_w = 46, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 394, .adv_w = 45, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 70, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 85, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 414, .adv_w = 79, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 82, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 99, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 438, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 439, .adv_w = 84, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 442, .adv_w = 144, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 110, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 451, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 452, .adv_w = 38, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 38, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 38, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 464, .adv_w = 55, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 465, .adv_w = 38, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 473, .adv_w = 73, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 479, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 487, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 508, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 516, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 530, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 544, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 552, .adv_w = 102, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 561, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 567, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 573, .adv_w = 102, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 582, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 588, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 594, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 604, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 609, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 616, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 626, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 56, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 646, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 649, .adv_w = 56, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 653, .adv_w = 55, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 656, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 659, .adv_w = 56, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 663, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 666, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 670, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 674, .adv_w = 174, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 683, .adv_w = 174, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 691, .adv_w = 174, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 703, .adv_w = 185, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 712, .adv_w = 185, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 725, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 94, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 739, .adv_w = 145, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 145, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 751, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 760, .adv_w = 145, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 145, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 776, .adv_w = 145, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 790, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 797, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 161, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 129, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 841, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 849, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 866, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 876, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 887, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 101, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 905, .adv_w = 101, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 912, .adv_w = 101, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 921, .adv_w = 101, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 928, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 933, .adv_w = 99, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 937, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 942, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 947, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 952, .adv_w = 108, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 955, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 963, .adv_w = 71, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 967, .adv_w = 71, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 969, .adv_w = 71, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 973, .adv_w = 71, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 976, .adv_w = 73, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 980, .adv_w = 73, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 984, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 989, .adv_w = 73, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 995, .adv_w = 73, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 999, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1004, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1009, .adv_w = 73, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1015, .adv_w = 118, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1021, .adv_w = 118, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1027, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1034, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1039, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1046, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1053, .adv_w = 140, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 140, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1064, .adv_w = 53, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1065, .adv_w = 71, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1067, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1069, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1071, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1072, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1073, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1074, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1076, .adv_w = 0, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1078, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1091, .adv_w = 164, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1105, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1106, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1107, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1108, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1109, .adv_w = 0, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1110, .adv_w = 0, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1111, .adv_w = 53, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1112, .adv_w = 66, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1113, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1114, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1115, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1121, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1122, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1123, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1124, .adv_w = 0, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1125, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1130, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1133, .adv_w = 46, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1134, .adv_w = 45, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1141, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1147, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1152, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1157, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1161, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1166, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1171, .adv_w = 82, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1175, .adv_w = 174, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1185, .adv_w = 185, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1196, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1203, .adv_w = 67, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1206, .adv_w = 83, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1210, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1216, .adv_w = 57, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1217, .adv_w = 44, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1220, .adv_w = 69, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1222, .adv_w = 57, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1223, .adv_w = 57, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1224, .adv_w = 44, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 60, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1227, .adv_w = 44, .box_w = 4, .box_h = 6, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1230, .adv_w = 57, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1231, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1233, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1234, .adv_w = 44, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1237, .adv_w = 53, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1238, .adv_w = 44, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1241, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1243, .adv_w = 38, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1246, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1249, .adv_w = 38, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1253, .adv_w = 43, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 73, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1262, .adv_w = 75, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1267, .adv_w = 38, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1271, .adv_w = 43, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1275, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1281, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1288, .adv_w = 41, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1291, .adv_w = 49, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1294, .adv_w = 38, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1295, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1297, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1303, .adv_w = 150, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1310, .adv_w = 41, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1312, .adv_w = 49, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1314, .adv_w = 71, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1317, .adv_w = 79, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1322, .adv_w = 144, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1328, .adv_w = 150, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1335, .adv_w = 41, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1338, .adv_w = 49, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1340, .adv_w = 144, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1347, .adv_w = 150, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1355, .adv_w = 41, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1358, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1361, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1367, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1373, .adv_w = 104, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1378, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1384, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1390, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1396, .adv_w = 104, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1399, .adv_w = 111, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1403, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1411, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1419, .adv_w = 104, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1424, .adv_w = 111, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1430, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1434, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1438, .adv_w = 79, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1443, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 57, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1452, .adv_w = 65, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1455, .adv_w = 56, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1458, .adv_w = 65, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1462, .adv_w = 174, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1469, .adv_w = 183, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1476, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1479, .adv_w = 123, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1482, .adv_w = 174, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1492, .adv_w = 183, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1503, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1508, .adv_w = 123, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1514, .adv_w = 185, .box_w = 11, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1523, .adv_w = 191, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1532, .adv_w = 135, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1536, .adv_w = 141, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1541, .adv_w = 185, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1552, .adv_w = 191, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1564, .adv_w = 135, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1570, .adv_w = 141, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1577, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1584, .adv_w = 126, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1591, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1597, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1604, .adv_w = 120, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1611, .adv_w = 126, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1618, .adv_w = 106, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1624, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1631, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1636, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1641, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1644, .adv_w = 83, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1647, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1654, .adv_w = 88, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1660, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1664, .adv_w = 83, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1669, .adv_w = 145, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1676, .adv_w = 149, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1683, .adv_w = 69, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1687, .adv_w = 75, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1691, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1697, .adv_w = 113, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1704, .adv_w = 69, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1708, .adv_w = 75, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1712, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1719, .adv_w = 135, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1726, .adv_w = 72, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1731, .adv_w = 78, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1737, .adv_w = 101, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1743, .adv_w = 106, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1750, .adv_w = 43, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1752, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1755, .adv_w = 83, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1759, .adv_w = 107, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1766, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1769, .adv_w = 92, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1772, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1776, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1782, .adv_w = 41, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1784, .adv_w = 49, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1786, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1790, .adv_w = 94, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1793, .adv_w = 73, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1797, .adv_w = 73, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1801, .adv_w = 75, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1805, .adv_w = 118, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1811, .adv_w = 110, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1815, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1822, .adv_w = 109, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1827, .adv_w = 41, .box_w = 3, .box_h = 6, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1830, .adv_w = 49, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1832, .adv_w = 87, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1836, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1842, .adv_w = 87, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1847, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1852, .adv_w = 87, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1857, .adv_w = 92, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1864, .adv_w = 87, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1868, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t ar_10 = {
#else
lv_font_t ar_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if AR_10*/

