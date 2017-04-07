/* freq.c */

#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "    -f FORMAT        Output format (KEY, KEY_VALUE, VALUE, VALUE_KEY)\n");
    fprintf(stderr, "    -l LOAD_FACTOR   Load factor for hash table\n");
    exit(status);
}

void freq_stream(FILE *stream, double load_factor, DumpMode mode) {
    Map* map = map_create(0, load_factor);
    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stream)) {
        char* c = strtok (buffer," \t\n");
        while (c != NULL) {
            Entry* searchEntry = map_search(map, c);
            if (searchEntry) { 
                Value addValue = searchEntry->value;
                addValue.number += 1;
                map_insert(map, c, addValue, NUMBER);
            }
            else {
                Value addValue;
                addValue.number = 1;
                map_insert(map, c, addValue, NUMBER);
            }
            c = strtok(NULL, " \t\n");
        }
    }
    map_dump(map, stdout, mode);
    map_delete(map);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    DumpMode FORMAT = VALUE_KEY;
    double LOAD_FACTOR = 0.9;
    int argind = 1;
    char* lf;
    char* format;
    while (argind < argc && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            case 'f':
                format = argv[argind++];
                if (!strcmp(format, "KEY"))
                    FORMAT = KEY;
                else if (!strcmp(format, "KEY_VALUE"))
                    FORMAT = KEY_VALUE;
                else if (!strcmp(format, "VALUE"))
                    FORMAT = VALUE;
                else
                    FORMAT = VALUE_KEY;
                break;
            case 'l':
                lf = argv[argind++];
                sscanf(lf, "%lf", &LOAD_FACTOR);
                break;
            default:
                usage(1);
                break;
        }
    }
                
    /* Compute frequencies of data from stdin */
    freq_stream(stdin, LOAD_FACTOR, FORMAT);

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
