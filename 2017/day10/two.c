#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(unsigned *list, size_t n, size_t start, size_t length) {
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

#define LISTLEN 256

int main(void) {
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
        unsigned list[LISTLEN];
        for (size_t k = 0; k < LISTLEN; k++) list[k] = k;
        size_t curpos = 0;
        size_t skipsize = 0;
        buf[strlen(buf) - 1] = 0; // remove ENTER
        for (int cycle = 0; cycle < 64; cycle++) {
            char *p = buf;
            size_t length;
            while (*p) {
                length = *p++;
                reverse(list, sizeof list / sizeof *list, curpos, length);
                curpos += length + skipsize;
                skipsize++;
            }
            length = 17;
            reverse(list, sizeof list / sizeof *list, curpos, length);
            curpos += length + skipsize;
            skipsize++;
            length = 31;
            reverse(list, sizeof list / sizeof *list, curpos, length);
            curpos += length + skipsize;
            skipsize++;
            length = 73;
            reverse(list, sizeof list / sizeof *list, curpos, length);
            curpos += length + skipsize;
            skipsize++;
            length = 47;
            reverse(list, sizeof list / sizeof *list, curpos, length);
            curpos += length + skipsize;
            skipsize++;
            length = 23;
            reverse(list, sizeof list / sizeof *list, curpos, length);
            curpos += length + skipsize;
            skipsize++;
        }
        int dense[16] = {0};
        for (int k = 0; k < 16; k++) {
            for (int j = 0; j < 16; j++) {
                dense[k] ^= list[k * 16 + j];
            }
        }
        printf("The Knot Hash is '");
        for (int k = 0; k < 16; k++) {
            printf("%02x", dense[k]);
        }
        printf("'\n");
    }
    return 0;
}
