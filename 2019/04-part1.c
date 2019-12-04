#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects data to be in stdin, call it like below
// $ ./a.out <04.txt
// $ echo -e "000010-000099" | ./a.out

void normalize(char *p) {
    char *p2 = p + 1;
    while (*p2) {
        if (*p2 < *p) *p2 = *p;
        p++;
        p2++;
    }
}

int possible(char *p) {
    int adjacent = 0;
    char *p2 = p + 1;
    while (*p2) {
        if (*p2 == *p) adjacent = 1;
        p++;
        p2++;
    }
    return adjacent;
}

void increment(char *p, int n) {
    if (p[n] == '9') { p[n] = '0'; increment(p, n - 1); }
    else p[n] += 1;
}

int possiblepasses(char *lo, char *hi) {
    int count = 0;
    while (strcmp(lo, hi) <= 0) {
        normalize(lo);
        if (strcmp(lo, hi) <= 0) count += possible(lo);
        increment(lo, 5);
    }
    return count;
}

int main(void) {
    char lo[7] = {0}, hi[7] = {0};
    int nlo = 0, nhi = 0;
    int ch;
    while ((ch = getchar()) != '-') lo[nlo++] = ch;
    while ((ch = getchar()) != '\n') hi[nhi++] = ch;
    int count = possiblepasses(lo, hi);
    printf("There are %d possible different passwords.\n", count);
    return 0;
}
