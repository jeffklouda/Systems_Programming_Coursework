/* lsort.c */

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "  -n   Numerical sort\n");
    fprintf(stderr, "  -q   Quick sort\n");
    exit(status);
}

void lsort(FILE *stream, bool numeric, bool quicksort) {
    char buffer[BUFSIZ];
    struct list* l = list_create();
    struct node* read;
    node_compare f = node_compare_string;
    while (fgets(buffer, BUFSIZ, stream)) {
        list_push_back(l, buffer);
    }
    if (numeric){
        f = node_compare_number;
    }
    if (quicksort){
        list_qsort(l, f);
    }
    else{
        list_msort(l, f);
    }
    read = l->head;
    while (read) {
        printf("%s", read->string);
        read = read->next;
    }     
}

/* Main Execution */

int main(int argc, char *argv[]) {
    bool numeric = false;
    bool quicksort = false;
    /* Parse command line arguments */
    int argind = 1;
    while (argind < argc && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            case 'n':
                numeric = true;
                break;
            case 'q':
                quicksort = true;
                break;
            default:
                usage(1);
                break;
        }
    }
    /* Sort using list */
    lsort(stdin, numeric, quicksort);
    return EXIT_SUCCESS;
}

