#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bitsset(int n) {
    char tmp[9];
    sprintf(tmp, "%02x", n);
    int r = 0;
    for (int k = 0; k < 2; k++) {
        if (strchr("0", tmp[k])) r += 0;
        if (strchr("1248", tmp[k])) r += 1;
        if (strchr("3569ac", tmp[k])) r += 2;
        if (strchr("7bde", tmp[k])) r += 3;
        if (strchr("f", tmp[k])) r += 4;
    }
    return r;
}

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

void knothash(int *dst, const char *src) {
    unsigned list[256];
    for (size_t k = 0; k < 256; k++) list[k] = k;
    size_t curpos = 0;
    size_t skipsize = 0;
    for (int cycle = 0; cycle < 64; cycle++) {
        const char *p = src;
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
    for (int k = 0; k < 16; k++) {
        dst[k] = 0;
        for (int j = 0; j < 16; j++) {
            dst[k] ^= list[k * 16 + j];
        }
    }
}

int main(void) {
    char buf[1000];
    char key[1000];
    int hash[128][16];
    while (fgets(buf, sizeof buf, stdin)) {
        buf[strlen(buf) - 1] = 0; // remove ENTER
        for (int k = 0; k < 128; k++) {
            sprintf(key, "%s-%d", buf, k);
            knothash(hash[k], key);
        }
    }
    int blocks = 0;
    for (int k = 0; k < 128; k++) {
        int sumbits = 0;
        for (int j = 0; j < 16; j++) {
            sumbits += bitsset(hash[k][j]);
        }
        blocks += sumbits;
    }
    printf("The disk has %d blocks occupied.\n", blocks);
    return 0;
}
