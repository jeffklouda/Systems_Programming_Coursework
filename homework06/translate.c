/* translate.c: string translator */

#include "stringutils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

enum {
    STRIP = 1<<1,
    REV_LINE = 1<<2,
    REV_WORDS = 1<<3,
    LOWER = 1<<4,
    UPPER = 1<<5
};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s     Strip whitespace\n");
    fprintf(stderr, "   -r     Reverse line\n");
    fprintf(stderr, "   -w     Reverse words in line\n");
    fprintf(stderr, "   -l     Convert to lowercase\n");
    fprintf(stderr, "   -u     Convert to uppercase\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, int mode) {
    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stream)) {
        string_chomp(buffer);
        /* Translate */
        if (source && target) string_translate(buffer, source, target);
        /* Post-translation filters */
        if (mode & STRIP) string_strip(buffer); /* I AM ERROR */
        if (mode & REV_LINE) string_reverse(buffer);
        if (mode & REV_WORDS) string_reverse_words(buffer);
        if (mode & LOWER) string_lowercase(buffer);
        if (mode & UPPER) string_uppercase(buffer);
        
        fputs(buffer, stdout);
        putc('\n', stdout);
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int mode = 0;
    char *source = NULL;
    char *target = NULL;
    /* Parse command line arguments */
    int argind = 1;
    PROGRAM_NAME = argv[0];
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            case 's':
                mode |= STRIP;
                break;
            case 'r':
                mode |= REV_LINE;
                break;
            case 'w':
                mode |= REV_WORDS;
                break;
            case 'l':
                mode |= LOWER;
                break;
            case 'u':
                mode |= UPPER;
                break;
            default:
                usage(1);
                break;
        }
    }

    if (argind < argc - 1) {
        source = argv[argind];
        argind++;
        target = argv[argind];
    }

    /* Translate Stream */
    
    translate_stream(stdin, source, target, mode);

    return EXIT_SUCCESS;
}
