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

int main(void) {
    char *tt;
    char *uu;
    tt = malloc(500000);
    uu = malloc(500000);
    strcpy(tt, "3113322113");
    for (int k = 0; k < 40; k += 2) {
        lookandsay(uu, tt);
        lookandsay(tt, uu);
    }
    printf("final length: %u\n", (unsigned)strlen(tt));
    free(tt);
    free(uu);
}
