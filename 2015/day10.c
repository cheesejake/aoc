#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lookandsay(char *dst, const char *src) {
    while (*src) {
        unsigned k = 1;
        while (*src == src[1]) { k++; src++; }
        dst += sprintf(dst, "%u%c", k, *src);
        src++;
    }
}

unsigned part1(const char *start) {
    unsigned retval;
    char *tt;
    char *uu;
    tt = malloc(500000);
    uu = malloc(500000);
    strcpy(tt, start);
    for (int k = 0; k < 40; k += 2) {
        lookandsay(uu, tt);
        lookandsay(tt, uu);
    }
    retval = strlen(tt);
    free(tt);
    free(uu);
    return retval;
}

unsigned part2(const char *start) {
    unsigned retval;
    char *tt;
    char *uu;
    tt = malloc(5000000);
    uu = malloc(5000000);
    strcpy(tt, start);
    for (int k = 0; k < 50; k += 2) {
        lookandsay(uu, tt);
        lookandsay(tt, uu);
    }
    retval = strlen(tt);
    free(tt);
    free(uu);
    return retval;
}

int main(void) {
    printf("DAY10-PART1: final length: %u\n", part1("3113322113"));
    printf("DAY10-PART2: final length: %u\n", part2("3113322113"));
    return 0;
}
