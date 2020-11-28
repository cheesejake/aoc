#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tx(int *x) { *x = !*x; }
void t0(int *x) { *x = 0; }
void t1(int *x) { *x = 1; }

void work(int g[1000][1000], int r1, int c1, int r2, int c2, void (*fx)(int*)) {
    if (r1 > r2) { int tmp = r1; r1 = r2; r2 = tmp; }
    if (c1 > c2) { int tmp = c1; c1 = c2; c2 = tmp; }
    for (int r = r1; r <= r2; r++) {
        for (int c = c1; c <= c2; c++) {
            fx(&g[r][c]);
        }
    }
}

int part1(char (*data)[80], unsigned ndata) {
    int grid[1000][1000] = {0};
    char buf[80];
    void (*fx)(int*);
    for (unsigned k = 0; k < ndata; k++) {
        strcpy(buf, data[k]);
        char *src;
        if (strncmp(buf, "toggle ", 7) == 0) { fx = tx; src = buf + 7; }
        if (strncmp(buf, "turn on ", 8) == 0) { fx = t1; src = buf + 8; }
        if (strncmp(buf, "turn off ", 9) == 0) { fx = t0; src = buf + 9; }
        int row1 = strtol(src, &src, 10); src++; // skip comma
        int col1 = strtol(src, &src, 10); src += 9; // skip " through "
        int row2 = strtol(src, &src, 10); src++; // skip comma
        int col2 = strtol(src, &src, 10);
        work(grid, row1, col1, row2, col2, fx);
    }
    int non = 0;
    for (int row = 0; row < 1000; row++) {
        for (int col = 0; col < 1000; col++) {
            if (grid[row][col]) non++;
        }
    }
    return non;
}

void tx_2(int *x) { *x += 2; }
void t0_2(int *x) { if (*x) *x -= 1; }
void t1_2(int *x) { *x += 1; }

int part2(char (*data)[80], unsigned ndata) {
    int grid[1000][1000] = {0};
    char buf[80];
    void (*fx)(int*);
    for (unsigned k = 0; k < ndata; k++) {
        strcpy(buf, data[k]);
        char *src;
        if (strncmp(buf, "toggle ", 7) == 0) { fx = tx_2; src = buf + 7; }
        if (strncmp(buf, "turn on ", 8) == 0) { fx = t1_2; src = buf + 8; }
        if (strncmp(buf, "turn off ", 9) == 0) { fx = t0_2; src = buf + 9; }
        int row1 = strtol(src, &src, 10); src++; // skip comma
        int col1 = strtol(src, &src, 10); src += 9; // skip " through "
        int row2 = strtol(src, &src, 10); src++; // skip comma
        int col2 = strtol(src, &src, 10);
        work(grid, row1, col1, row2, col2, fx);
    }
    int lum = 0;
    for (int row = 0; row < 1000; row++) {
        for (int col = 0; col < 1000; col++) {
            lum += grid[row][col];
        }
    }
    return lum;
}

int main(void) {
    char data[500][80];
    unsigned ndata = 0;
    while (fgets(data[ndata], 80, stdin)) {
        ndata++;
    }
    printf("DAY06-PART1: There are %d light on.\n", part1(data, ndata));
    printf("DAY06-PART2: Total brightness is %d.\n", part2(data, ndata));
    return 0;
}
