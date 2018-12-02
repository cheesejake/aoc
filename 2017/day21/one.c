#include <stdio.h>
#include <stdlib.h>

struct Rule {
    int srclen;
    int srcbits;
    unsigned src;
    unsigned dst;
};

void fillrule(struct Rule *dst, const char *p) {
    dst->src = dst->dst = 0;
    while (*p != ' ') {
        if ((*p == '.') || (*p == '#')) {
            dst->src <<= 1;
            dst->src |= (*p == '#');
            dst->srcbits += (*p == '#');
            dst->srclen += 1;
        }
        p++;
    }
    p += 4; // skip " => "
    while (*p != '\n') {
        if ((*p == '.') || (*p == '#')) {
            dst->dst <<= 1;
            dst->dst |= (*p == '#');
        }
        p++;
    }
}

int bit(unsigned x, int n) {
    while (n--) x >>= 1;
    return x & 1;
}

int findpattern(int data[100][100], int row, int col, struct Rule *r, int nr, int psize) {
    if (psize == 2) {
        return 0;
    } else {
        return 1;
    }
}

int main(void) {
    struct Rule r[120] = {0};
    int rules = 0;
    int grid[2][100][100] = {0};
    int rows = 3;
    int cols = 3;
    grid[0][0][0] = 0; grid[0][0][1] = 1; grid[0][0][2] = 0;
    grid[0][1][0] = 0; grid[0][1][1] = 0; grid[0][1][2] = 1;
    grid[0][2][0] = 1; grid[0][2][1] = 1; grid[0][2][2] = 1;
    char buf[100];
    while (fgets(buf, sizeof buf, stdin)) {
        fillrule(r + rules, buf);
        rules++;
    }
    for (int g = 0; g < 5; g++) {
        if (rows % 2 == 0) {
            for (int row = 0; row < rows; row += 2) {
                for (int col = 0; col < cols; col += 2) {
                    int ri = findpattern(grid[0], row, col, r, rules, 2);
                    for (int dstrow = 0; dstrow < 3; dstrow++) {
                        for (int dstcol = 0; dstcol < 3; dstcol++) {
                            grid[1][row*3 + dstrow][col*3 + dstcol] = bit(r[ri].dst, dstrow * 3 + dstcol);
                        }
                    }
                }
            }
            rows = (rows / 2) * 3;
            cols = (cols / 2) * 3;
        } else {
            for (int row = 0; row < rows; row += 3) {
                for (int col = 0; col < cols; col += 3) {
                    int ri = findpattern(grid[0], row, col, r, rules, 3);
                    for (int dstrow = 0; dstrow < 4; dstrow++) {
                        for (int dstcol = 0; dstcol < 4; dstcol++) {
                            grid[1][row*4 + dstrow][col*4 + dstcol] = bit(r[ri].dst, dstrow * 4 + dstcol);
                        }
                    }
                }
            }
            rows = (rows / 3) * 4;
            cols = (cols / 3) * 4;
        }
    }
    return 0;
}
