#include <ctype.h>

/*
 * X68000 XC Library compatible jfctype functions.
 * Returns non-zero if the condition is met, 0 otherwise.
 */

/* 1. Check for Alphabetic or Katakana character */
int isalkana(int c) {
    /* isalpha covers A-Z, a-z. 0xA6-0xDF covers half-width Katakana letters. */
    if (isalpha(c) || (c >= 0xA6 && c <= 0xDF)) {
        return 1;
    }
    return 0;
}

/* 2. Check for English or Katakana punctuation */
int ispnkana(int c) {
    /* ispunct covers ASCII symbols. 0xA1-0xA5 covers half-width Katakana punctuation. */
    if (ispunct(c) || (c >= 0xA1 && c <= 0xA5)) {
        return 1;
    }
    return 0;
}

/* 3. Check for Alphanumeric or Katakana character */
int isalnmkana(int c) {
    /* isalnum covers A-Z, a-z, 0-9. 0xA6-0xDF covers half-width Katakana letters. */
    if (isalnum(c) || (c >= 0xA6 && c <= 0xDF)) {
        return 1;
    }
    return 0;
}

/* 4. Check for Printable character (including space) */
int isprkana(int c) {
    /* isprint covers 0x20-0x7E. 0xA1-0xDF covers half-width Katakana range. */
    if (isprint(c) || (c >= 0xA1 && c <= 0xDF)) {
        return 1;
    }
    return 0;
}

/* 5. Check for Printable character (excluding space) */
int isgrkana(int c) {
    /* isgraph covers 0x21-0x7E. 0xA1-0xDF covers half-width Katakana range. */
    if (isgraph(c) || (c >= 0xA1 && c <= 0xDF)) {
        return 1;
    }
    return 0;
}

/*
 * X68000 XC Library compatible functions for Katakana (1-byte).
 * These assume a Shift-JIS or JIS X 0201 encoding context.
 */

/* 1. Check for Katakana letter or Katakana punctuation */
int iskana(int c) {
    /* 0xA1 to 0xDF covers the entire half-width Katakana range. */
    if (c >= 0xA1 && c <= 0xDF) {
        return 1;
    }
    return 0;
}

/* 2. Check for Katakana punctuation only */
int iskpun(int c) {
    /* 0xA1 to 0xA5 covers symbols like '｡', '｢', '｣', '､', '･'. */
    if (c >= 0xA1 && c <= 0xA5) {
        return 1;
    }
    return 0;
}

/* 3. Check for Katakana letter only */
int iskmoji(int c) {
    /* 0xA6 to 0xDF covers characters from 'ｦ' to 'ﾟ'. */
    if (c >= 0xA6 && c <= 0xDF) {
        return 1;
    }
    return 0;
}

/*
 * X68000 XC Library compatible functions for Multi-byte (Kanji) characters.
 * These follow the Shift-JIS encoding rules as specified in the documentation.
 */

/* 1. Check if the character is the 1st byte of a Shift-JIS code */
int iskanji(int c) {
    /* * Range 1: 0x81 to 0x9F
     * Range 2: 0xE0 to 0xEF (Note: some systems go up to 0xFC, but we follow the spec provided)
     */
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xEF)) {
        return 1;
    }
    return 0;
}

/* 2. Check if the character is the 2nd byte of a Shift-JIS code */
int iskanji2(int c) {
    /*
     * Range 1: 0x40 to 0x7F
     * Range 2: 0x80 to 0xFC
     */
    if ((c >= 0x40 && c <= 0x7F) || (c >= 0x80 && c <= 0xFC)) {
        return 1;
    }
    return 0;
}

/*
 * X68000 XC Library compatible functions for Full-width characters (Shift-JIS).
 * Input 'c' is expected to be a 16-bit value (e.g., 0x8260 for 'ａ').
 */

/* 1. Check for Full-width Alphabetic character (Upper or Lower) */
int jisalpha(int c) {
    /* Range: 0x8260-0x8279 (A-Z) and 0x8281-0x829A (a-z) */
    if ((c >= 0x8260 && c <= 0x8279) || (c >= 0x8281 && c <= 0x829A)) {
        return 1;
    }
    return 0;
}

/* 2. Check for Full-width Uppercase character */
int jisupper(int c) {
    /* Range: 0x8260 to 0x8279 */
    if (c >= 0x8260 && c <= 0x8279) {
        return 1;
    }
    return 0;
}

/* 3. Check for Full-width Lowercase character */
int jislower(int c) {
    /* Range: 0x8281 to 0x829A */
    if (c >= 0x8281 && c <= 0x829A) {
        return 1;
    }
    return 0;
}

/* 4. Check for Full-width Digit (0-9) */
int jisdigit(int c) {
    /* Range: 0x824F to 0x8258 */
    if (c >= 0x824F && c <= 0x8258) {
        return 1;
    }
    return 0;
}

/* 5. Check for Full-width Katakana */
int jiskata(int c) {
    /* Range: 0x8340 to 0x8396 (Excluding specific symbols) */
    if (c >= 0x8340 && c <= 0x8396) {
        return 1;
    }
    return 0;
}

/* 6. Check for Full-width Hiragana */
int jishira(int c) {
    /* Range: 0x829F to 0x82F1 */
    if (c >= 0x829F && c <= 0x82F1) {
        return 1;
    }
    return 0;
}

/* 7. Check for Full-width Punctuation/Symbols */
int jiskigou(int c) {
    /* Various symbol blocks in Shift-JIS (e.g., 0x8141-0x81AC) */
    if (c >= 0x8141 && c <= 0x81AC) {
        return 1;
    }
    return 0;
}

/* 8. Check for Full-width Space (IDEOGRAPHIC SPACE) */
int jisspace(int c) {
    /* Shift-JIS Code for '　' is 0x8140 */
    if (c == 0x8140) {
        return 1;
    }
    return 0;
}

/*
 * X68000 XC Library compatible functions for JIS Kanji Levels.
 * Input 'c' is expected to be a 16-bit Shift-JIS value (e.g., 0x889F).
 */

/* 1. Check for any Full-width (Zen-kaku) character */
int jiszen(int c) {
    /* * In Shift-JIS, the first byte determines if it is a multi-byte character.
     * We can reuse the iskanji logic for the upper 8 bits of 'c'.
     */
    int first_byte = (c >> 8) & 0xFF;
    if ((first_byte >= 0x81 && first_byte <= 0x9F) || 
        (first_byte >= 0xE0 && first_byte <= 0xEF)) {
        return 1;
    }
    return 0;
}

/* 2. Check for Non-Kanji symbols (JIS Level 0 symbols/space) */
int jisl0(int c) {
    /* Range: 0x8140 to 0x84BE (Includes symbols, Greek, Cyrillic, etc.) */
    if (c >= 0x8140 && c <= 0x84BE) {
        return 1;
    }
    return 0;
}

/* 3. Check for JIS Level 1 Kanji (JIS Dai-ichi Suijun) */
int jisl1(int c) {
    /* Range: 0x889F to 0x9872 */
    if (c >= 0x889F && c <= 0x9872) {
        return 1;
    }
    return 0;
}

/* 4. Check for JIS Level 2 Kanji (JIS Dai-ni Suijun) */
int jisl2(int c) {
    /* Range: 0x989F to 0xEAA4 */
    if (c >= 0x989F && c <= 0xEAA4) {
        return 1;
    }
    return 0;
}

/*
 * X68000 XC Library compatible conversion functions.
 * Based on the provided specifications for bit manipulation and SJIS ranges.
 */

/* 1. Convert half-width (8-bit) to full-width (16-bit Shift-JIS) */
int hantozen(int c) {
    int hiragana_flag = (c & 0x10000); // Check if bit 16 is 1
    int code = c & 0xFFFF;             // Extract the character code part

    // Handle ASCII Range: 0x20 to 0x7E
    if (code >= 0x20 && code <= 0x7E) {
        if (code == 0x20) return 0x8140; // Space
        return code + 0x811F;            // Simple mapping to full-width ASCII
    }

    // Handle Half-width Katakana: 0xA1 to 0xDF
    if (code >= 0xA1 && code <= 0xDF) {
        // Basic mapping for Katakana. 
        // If bit 16 is 1, return the Hiragana equivalent (usually SJIS 0x829F range)
        // A full implementation would use a lookup table for exact mapping.
        if (hiragana_flag) {
            /* Example logic for Hiragana conversion */
            return (code - 0xA1) + 0x829F; 
        } else {
            /* Example logic for Katakana conversion */
            return (code - 0xA1) + 0x8340;
        }
    }

    return c; // Return original if no conversion possible
}

/* 2. Convert full-width (16-bit) to half-width (8-bit) */
int zentohan(int c) {
    /* * Spec: For voiced/semi-voiced marks, the mark code is in bits 8-15,
     * and the base Katakana code is in bits 0-7.
     */
    int upper = (c >> 8) & 0xFF;
    int lower = c & 0xFF;

    // Example logic for converting full-width Katakana back to half-width
    if (upper == 0x83) { // Simplified Katakana block check
        return lower - 0x3F; // Approximate mapping
    }

    // If it's a character that cannot be converted, return original value
    return c;
}