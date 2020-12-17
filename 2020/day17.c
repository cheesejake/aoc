#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HALFSIZE 20
#define FULLSIZE (2 * (HALFSIZE) + 1)

void quit(const char *msg) {
    if (msg) fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

char srcgrid[FULLSIZE][FULLSIZE][FULLSIZE];
char dstgrid[FULLSIZE][FULLSIZE][FULLSIZE];

char *addr(char r[FULLSIZE][FULLSIZE][FULLSIZE], int x, int y, int z) {
    return &r[x + HALFSIZE][y + HALFSIZE][z + HALFSIZE];
}

int neighbors(char r[FULLSIZE][FULLSIZE][FULLSIZE], int x, int y, int z) {
    int count = 0;
    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            for (int dz = -1; dz < 2; dz++) {
                count += *addr(r, x+dx, y+dy, z+dz);
            }
        }
    }
    return count - *addr(r, x, y, z);
}

int active(char r[FULLSIZE][FULLSIZE][FULLSIZE]) {
    int count = 0;
    for (int x = -HALFSIZE + 1; x < HALFSIZE; x++) {
        for (int y = -HALFSIZE + 1; y < HALFSIZE; y++) {
            for (int z = -HALFSIZE + 1; z < HALFSIZE; z++) {
                count += *addr(r, x, y, z);
            }
        }
    }
    return count;
}

int main(int argc, char **argv) {
    if (argc != 2) quit("syntax: ./a.out <filename>");
    FILE *fid = fopen(argv[1], "r");
    if (!fid) quit("cannot open input file");
    char buf[20];
    int x = 0, y = 0, z = 0;
    while (fgets(buf, sizeof buf, fid)) {
        char *p = buf;
        while (*p != '\n') {
            *addr(dstgrid, x, y, z) = (*p == '#');
            x++;
            p++;
        }
        y++;
        x = 0;
    }
    fclose(fid);
    for (int cycle = 0; cycle < 6; cycle++) {
        memcpy(srcgrid, dstgrid, sizeof srcgrid);
        for (x = -HALFSIZE + 1; x < HALFSIZE; x++) {
            for (y = -HALFSIZE + 1; y < HALFSIZE; y++) {
                for (z = -HALFSIZE + 1; z < HALFSIZE; z++) {
                    int n = neighbors(srcgrid, x, y, z);
                    switch (*addr(srcgrid, x, y, z)) {
                        default: quit("Bad value in grid");
                                 break; // unnecessary break
                        case 0: if (n == 3) {
                                    *addr(dstgrid, x, y, z) = 1;
                                }
                                break;
                        case 1: if ((n < 2) || (n > 3)) {
                                    *addr(dstgrid, x, y, z) = 0;
                                }
                                break;
                    }
                }
            }
        }
    }
    printf("Day 17, part 1: %d\n", active(dstgrid));
}
