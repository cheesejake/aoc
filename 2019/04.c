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

int possible2(char *p) {
    char pp[10] = {0};
    for (int k = 0; k < 6; k++) pp[p[k] - '0'] += 1;
    for (int k = 0; k < 10; k++) if (pp[k] == 2) return 1;
    return 0;
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

int possiblepasses2(char *lo, char *hi) {
    int count = 0;
    while (strcmp(lo, hi) <= 0) {
        normalize(lo);
        if (strcmp(lo, hi) <= 0) count += possible2(lo);
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
    char lobak[7], hibak[7];
    strcpy(lobak, lo);
    strcpy(hibak, hi);
    int count = possiblepasses(lo, hi);
    int count2 = possiblepasses2(lobak, hibak);
    printf("There are %d possible different passwords.\n", count);
    printf("There are %d possible different passwords with the new rule.\n", count2);
    return 0;
}
