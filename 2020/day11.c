#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countneighbours(char (*x)[120], int n, int row, int col) {
    int v = 0;
    if ((row > 0)     && (col > 0)     && (x[row-1][col-1] == '#')) ++v;
    if ((row > 0)                      && (x[row-1][col] == '#'))   ++v;
    if ((row > 0)     && (col < n - 1) && (x[row-1][col+1] == '#')) ++v;
    if (                 (col > 0)     && (x[row][col-1] == '#'))   ++v;
    if (                 (col < n - 1) && (x[row][col+1] == '#'))   ++v;
    if ((row < n - 1) && (col > 0)     && (x[row+1][col-1] == '#')) ++v;
    if ((row < n - 1)                  && (x[row+1][col] == '#'))   ++v;
    if ((row < n - 1) && (col < n - 1) && (x[row+1][col+1] == '#')) ++v;
    return v;
}

void evolve(char (*dst)[120], char (*src)[120], int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; src[row][col] != 0; col++) {
            dst[row][col] = src[row][col];
            int nn = countneighbours(src, n, row, col);
            if (src[row][col] == 'L') {
                if (nn == 0) dst[row][col] = '#';
            }
            if (src[row][col] == '#') {
                if (nn >= 4) dst[row][col] = 'L';
            }
        }
    }
}

int equal(char (*a)[120], char (*b)[120], int n) {
    for (int k = 0; k < n; k++) {
        if (strcmp(a[k], b[k])) return 0;
    }
    return 1;
}

int occupied(char (*x)[120], int n) {
    int count = 0;
    for (int k = 0; k < n; k++) {
        char *p = x[k];
        while (*p) {
            count += (*p == '#');
            p++;
        }
    }
    return count;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "syntax: ./a.out <filename>\n");
        exit(EXIT_FAILURE);
    }
    char data[2][200][120] = {0};
    int n = 0;
    FILE *fid = fopen(argv[1], "r");
    char buf[500];
    while (fgets(buf, sizeof buf, fid)) {
        buf[strcspn(buf, "\r\n")] = 0;
        strcpy(data[0][n], buf);
        strcpy(data[1][n], buf);
        n++;
    }
    fclose(fid);

    int generation = 0;
    do {
        evolve(data[(generation + 1) % 2], data[generation % 2], n);
        generation++;
    } while (!equal(data[0], data[1], n));
    printf("day 11, part1: %d occupied seats.\n", occupied(data[0], n));
}
