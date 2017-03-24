/* stringutils.c: String Utilities */

#include "stringutils.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	string_lowercase(char *s) {
    for (char *c = s; *c; c++) {
        *c = tolower(*c);
    }
    return s;
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	string_uppercase(char *s) {
    for (char *c = s; *c; c++) {
        *c = toupper(*c);
    }
    return s;
}

/**
 * Returns whether or not the 's' string starts with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' starts with 't'
 **/
bool	string_startswith(char *s, char *t) {
    if (strlen(t) > strlen(s)) return false;
    while (*t) {
        if (*s != *t) return false;
        s++;
        t++;
    }
    return true;
}

/**
 * Returns whether or not the 's' string ends with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' ends with 't'
 **/
bool	string_endswith(char *s, char *t) {
    int lenT = strlen(t);
    int lenS = strlen(s);
    if (lenT > lenS) return false;
    s += lenS - 1;
    t += lenT - 1;
    for (int i = 0; i < lenT; i++) {
        if (*s != *t) return false;
        s--;
        t--;
    }
    return true;
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	string_chomp(char *s) {
    int lenS = strlen(s);
    char *c = s;
    c += lenS -1;
    if (*c == '\n') *c = '\0';
    return s;
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	string_strip(char *s) {
    char *cb = s;
    char *ce = s + strlen(s) - 1;
    char *w; /* writer */
    char *r; /* reader */
    while (isspace(*cb)) cb++; /* move start of string if whitespace */
    w = s;
    r = cb;
    for (; r < s + strlen(s); w++, r++) {
        *w = *r;
    }
    for (; w < s + strlen(s); w++) *w = ' ';
    while (isspace(*ce)) { /* overwrite end of string if whitespace */
        *ce = '\0';
        ce--;
    }
    return s;
}

/**
 * Reverses a string given the provided from and to pointers.
 * @param   from    Beginning of string
 * @param   to      End of string
 * @return          Pointer to beginning of modified string
 **/
static char *	string_reverse_range(char *from, char *to) {
    char *c = from;
    while (to > c) {
        char temp = *c;
        *c = *to;
        *to = temp;
        c++;
        to--;
    }
    return from;
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 * @return          Pointer to beginning of modified string
 **/
char *	string_reverse(char *s) {
    char *c = s + strlen(s) - 1;
    s = string_reverse_range(s, c);
    return s;
}

/**
 * Reverses all words in a string.
 * @param   s       String with words to reverse
 * @return          Pointer to beginning of modified string
 **/
char *	string_reverse_words(char *s) {
    s = string_reverse(s);
    char *cb = s; /* beginning of word */
    char *ce = s; /* end of word */
    while (*ce != '\0') {
        /* increment ce to end of word */
        while ((*(ce+1) != ' ') && (*(ce+1) != '\0'))  ce++;
        /* increment cb to beginning of word */
        while (isspace(*cb) && *cb != '\0') cb++;
        /* reverse word */
        cb = string_reverse_range(cb, ce);
        /* increment ce to beginning of next word */
        ce++;
        while (isspace(*ce) && *ce != '\0') ce++;
        /* set cb to beginning of next word */
        cb = ce;
    }
    return s;
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 * @return          Pointer to beginning of modified string
 **/
char *	string_translate(char *s, char *from, char *to) {
    char lookup_table[128] = { 0 };
    if (strlen(from) != strlen(to)) return s;
    for (int i = 0; *from; i++, from++, to++) {
        lookup_table[*from] = *to;
    }
    for (char *c = s; *c; c++) {
        if (lookup_table[*c]) *c = lookup_table[*c];
    }
    return s;
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int	string_to_integer(char *s, int base) {
    int returnValue = 0;
    char *c = s + strlen(s) - 1;
    int multBy = 1;
    s = string_lowercase(s);
    for (int i = 0; i < strlen(s); i++) {
        if (isalpha(*c)) {
            returnValue += (*c - 'a' + 10) * multBy;
        }
        else if (isdigit(*c)) {
            returnValue += (*c - '0') * multBy;
        }
        c--;
        multBy *= base;
    }
    return returnValue;
}
