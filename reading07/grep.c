/* grep.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s PATTERN FILE...\n", PROGRAM_NAME);
    exit(status);
}

void grep_stream(FILE *stream, const char *search) {
    char buffer[BUFSIZ];

    while (fgets(buffer, BUFSIZ, stream)) {
        if (strstr(buffer, search) != NULL) {
            fputs(buffer, stdout);
        }
    }
}

void grep_file(const char *path, const char *search) {
    FILE *fs = fopen(path, "r");
    if (fs == NULL) {
        fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
        return;
    }
    grep_stream(fs, search);
    fclose(fs);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;
    char *search;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }

    /* capture search expression */
    search = argv[argind++];
    /* Process each file */
    if (argind == argc) {
        grep_stream(stdin, search);
    } else {
        while (argind < argc) {
            char *path = argv[argind++];
            if (strcmp(path, "-") == 0) {
                grep_stream(stdin, search);
            } else {
                grep_file(path, search);
            }
        }
    }

    return EXIT_SUCCESS;
}
