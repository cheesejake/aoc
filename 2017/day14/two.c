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

void tobin(int *dst, int src) {
    if (src > 127) { *dst = 1; src -= 128; } else { *dst = 0; }
    dst++;
    if (src > 63) { *dst = 1; src -= 64; } else { *dst = 0; }
    dst++;
    if (src > 31) { *dst = 1; src -= 32; } else { *dst = 0; }
    dst++;
    if (src > 15) { *dst = 1; src -= 16; } else { *dst = 0; }
    dst++;
    if (src > 7) { *dst = 1; src -= 8; } else { *dst = 0; }
    dst++;
    if (src > 3) { *dst = 1; src -= 4; } else { *dst = 0; }
    dst++;
    if (src > 1) { *dst = 1; src -= 2; } else { *dst = 0; }
    dst++;
    if (src > 0) { *dst = 1; src -= 1; } else { *dst = 0; }
}

void floodzero(int grid[128][128], int row, int col) {
    if (grid[row][col] == 0) return;
    grid[row][col] = 0;
    if (row > 0) floodzero(grid, row - 1, col);
    if (row < 127) floodzero(grid, row + 1, col);
    if (col > 0) floodzero(grid, row, col - 1);
    if (col < 127) floodzero(grid, row, col + 1);
}

int main(void) {
    char buf[1000];
    char key[1000];
    int hash[128][16];
    int grid[128][128] = {0};
    while (fgets(buf, sizeof buf, stdin)) {
        buf[strlen(buf) - 1] = 0; // remove ENTER
        for (int k = 0; k < 128; k++) {
            sprintf(key, "%s-%d", buf, k);
            knothash(hash[k], key);
        }
    }
    for (int k = 0; k < 128; k++) {
        for (int j = 0; j < 16; j++) {
            int bin[8];
            tobin(bin, hash[k][j]);
            for (int m = 0; m < 8; m++) {
                grid[k][j * 8 + m] = bin[m];
            }
        }
    }
    int group = 0;
    for (int row = 0; row < 128; row++) {
        for (int col = 0; col < 128; col++) {
            if (grid[row][col]) {
                floodzero(grid, row, col);
                group += 1;
            }
        }
    }
    printf("The grid has %d groups.\n", group);
    return 0;
}
