#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

#include "jfctype.h"
#include "jstring.h"

/**
 * Helper for character priority: Alphanumeric (1) < Kana (2) < Kanji (3)
 */
static int get_char_category(const unsigned char c) {
    if (c == '\0') return 0;
    if (iskanji(c)) return 3;
    if (c >= 0xA1 && c <= 0xDF) return 2; /* Half-width Kana */
    return 1; /* Alphanumeric */
}

int jstrcmp(const unsigned char *string1, const unsigned char *string2) {
    if (string1 == string2) return 0;
    if (string1 == NULL) return -1;
    if (string2 == NULL) return 1;
    while (*string1 != '\0' || *string2 != '\0') {
        int cat1 = get_char_category(*string1);
        int cat2 = get_char_category(*string2);

        /* 1. Compare character categories */
        if (cat1 != cat2) {
            return cat1 - cat2;
        }

        /* 2. Compare actual values within the same category */
        if (cat1 == 3) {
            /* Compare Kanji (2 bytes) */
            uint16_t val1 = (uint16_t)((*string1 << 8) | *(string1 + 1));
            uint16_t val2 = (uint16_t)((*string2 << 8) | *(string2 + 1));
            
            if (val1 != val2) {
                return (val1 > val2) ? 1 : -1;
            }

            /* Handle spec where 2nd byte null terminates string */
            if (*(string1 + 1) == '\0' || *(string2 + 1) == '\0') break;

            string1 += 2;
            string2 += 2;
        } else {
            /* Compare Single-byte */
            if (*string1 != *string2) {
                return (int)*string1 - (int)*string2;
            }
            string1++;
            string2++;
        }
    }

    return 0;
}

int jstrncmp(const unsigned char *string1, const unsigned char *string2, int n) {
    /* If n is 0, strings are considered equal up to 0 characters */
    if (n <= 0) return 0;
    if (string1 == string2) return 0;
    if (string1 == NULL) return -1;
    if (string2 == NULL) return 1;
    while (n > 0 && (*string1 != '\0' || *string2 != '\0')) {
        int cat1 = get_char_category(*string1);
        int cat2 = get_char_category(*string2);

        /* 1. Compare categories (Alphanumeric < Kana < Kanji) */
        if (cat1 != cat2) {
            return cat1 - cat2;
        }

        /* 2. Compare actual values within the same category */
        if (cat1 == 3) {
            /* Compare Kanji (2 bytes as 1 character) */
            uint16_t val1 = (uint16_t)((*string1 << 8) | *(string1 + 1));
            uint16_t val2 = (uint16_t)((*string2 << 8) | *(string2 + 1));

            if (val1 != val2) {
                return (val1 > val2) ? 1 : -1;
            }

            /* Per spec: if 2nd byte is '\0', string ends */
            if (*(string1 + 1) == '\0' || *(string2 + 1) == '\0') break;

            string1 += 2;
            string2 += 2;
        } else {
            /* Compare Single-byte */
            if (*string1 != *string2) {
                return (int)*string1 - (int)*string2;
            }
            string1++;
            string2++;
        }

        /* Decrement character count */
        n--;
    }

    return 0;
}

/**
 * Searches for the last occurrence of character 'c' in the Shift_JIS string.
 */
unsigned char *jstrrchr(const unsigned char *string, int c) {
    if (string == NULL) return NULL;

    unsigned char *last_match = NULL;
    uint16_t search_char = (uint16_t)c;
    unsigned char c_high = (unsigned char)((search_char >> 8) & 0xFF);
    unsigned char c_low  = (unsigned char)(search_char & 0xFF);

    /* Special case: searching for the null terminator */
    if (c_high == 0 && c_low == '\0') {
        while (*string != '\0') {
            if (iskanji(*string)) {
                if (*(string + 1) == '\0') return (unsigned char*)string;
                string += 2;
            } else {
                string++;
            }
        }
        return (unsigned char*)string;
    }

    while (*string != '\0') {
        if (iskanji(*string)) {
            /* Multi-byte character detected */
            if (c_high != 0) {
                /* Compare as 2-byte sequence */
                if (*string == c_high && *(string + 1) == c_low) {
                    last_match = (unsigned char*)string;
                }
            }
            
            /* Per spec: if 2nd byte is '\0', string ends */
            if (*(string + 1) == '\0') break;
            
            string += 2;
        } else {
            /* Single-byte character detected */
            if (c_high == 0 && *string == c_low) {
                last_match = (unsigned char*)string;
            }
            string++;
        }
    }

    return last_match;
}

/**
 * Searches for the first occurrence of character 'c' in the Shift_JIS string.
 */
unsigned char *jstrchr(const unsigned char *string, int c) {
    if (string == NULL) return NULL;

    uint16_t search_char = (uint16_t)c;
    unsigned char c_high = (unsigned char)((search_char >> 8) & 0xFF);
    unsigned char c_low  = (unsigned char)(search_char & 0xFF);

    while (*string != '\0') {
        if (iskanji(*string)) {
            /* Multi-byte character detected */
            if (c_high != 0) {
                /* Compare as 2-byte sequence */
                if (*string == c_high && *(string + 1) == c_low) {
                    return (unsigned char*)string;
                }
            }
            
            /* Per spec: if 2nd byte is '\0', the character is invalid/end */
            if (*(string + 1) == '\0') return NULL;
            
            string += 2;
        } else {
            /* Single-byte character detected */
            if (c_high == 0 && *string == c_low) {
                return (unsigned char*)string;
            }
            string++;
        }
    }

    /* Standard strchr behavior: find null terminator if requested */
    if (c_high == 0 && c_low == '\0') {
        return (unsigned char*)string;
    }

    return NULL;
}

/**
 * Shift_JIS aware case-insensitive string comparison.
 */
 int jstricmp(const unsigned char *string1, const unsigned char *string2) {
    if (string1 == string2) return 0;
    if (string1 == NULL) return -1;
    if (string2 == NULL) return 1;
    while (*string1 != '\0' || *string2 != '\0') {
        int cat1 = get_char_category(*string1);
        int cat2 = get_char_category(*string2);

        /* 1. Compare categories first */
        if (cat1 != cat2) {
            return cat1 - cat2;
        }

        /* 2. Compare actual values within the same category */
        if (cat1 == 3) {
            /* Multi-byte Comparison (Kanji: Case-insensitivity doesn't apply) */
            uint16_t val1 = (uint16_t)((*string1 << 8) | *(string1 + 1));
            uint16_t val2 = (uint16_t)((*string2 << 8) | *(string2 + 1));
            
            if (val1 != val2) {
                return (val1 > val2) ? 1 : -1;
            }

            /* Per spec: if 2nd byte is '\0', treat as string end */
            if (*(string1 + 1) == '\0' || *(string2 + 1) == '\0') break;

            string1 += 2;
            string2 += 2;
        } else {
            /* Single-byte Comparison */
            unsigned char c1 = *string1;
            unsigned char c2 = *string2;

            /* Apply case-insensitivity only to ASCII range */
            if (cat1 == 1) {
                c1 = (unsigned char)tolower(c1);
                c2 = (unsigned char)tolower(c2);
            }

            if (c1 != c2) {
                return (int)c1 - (int)c2;
            }
            string1++;
            string2++;
        }
    }

    return 0;
}