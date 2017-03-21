/* sort.c */

#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define MAX_NUMBERS (1<<10)

/* Functions */

size_t read_numbers(FILE *stream, int numbers[], size_t n) {
    size_t i = 0;

    while (i < n && scanf("%d", &numbers[i]) != EOF) {
        i++;
    }

    return i;
}

void sort_numbers(int numbers[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        int j = i-1;
        while (j >= 0 && numbers[j+1] < numbers[j]) {
            int temp = numbers[j+1];
            numbers[j+1] = numbers[j];
            numbers[j] = temp;
            j--;
        }
    }
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int numbers[MAX_NUMBERS];
    size_t nsize;

    nsize = read_numbers(stdin, numbers, MAX_NUMBERS);
    sort_numbers(numbers, nsize);
    for (size_t i = 0; i < nsize; i++) {
        if (i > 0) printf(" ");
        printf("%d", numbers[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
