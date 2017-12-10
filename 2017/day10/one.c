#include <stdio.h>
#include <stdlib.h>

void reverse(int *list, size_t n, size_t start, size_t length) {
    int alpha = start;
    int omega = start + length - 1;
    while (alpha < omega) {
        int tmp = list[alpha % n];
        list[alpha % n] = list[omega % n];
        list[omega % n] = tmp;
        alpha++;
        omega--;
    }
}

#ifndef LISTLEN
#define LISTLEN 256
#endif

int main(void) {
    int list[LISTLEN];
    for (size_t k = 0; k < LISTLEN; k++) list[k] = k;
    size_t curpos = 0;
    size_t skipsize = 0;
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
        char *p = buf;
        while (*p) {
            size_t length = strtoul(p, &p, 10); p++; // skip comma or ENTER
            reverse(list, sizeof list / sizeof *list, curpos, length);
            curpos += length + skipsize;
            skipsize++;
        }
    }
    printf("Product of first two numbers is %d.\n", list[0] * list[1]);
    return 0;
}
