#include <stdio.h>
#include <stdlib.h>

struct House {
    int row;
    int col;
};

unsigned part1(const char *ch) {
    struct House *grid;
    unsigned ngrid = 0;
    int row = 0;
    int col = 0;
    grid = malloc(10000 * sizeof *grid);
    ngrid = 1;
    grid[0].row = row;
    grid[0].col = col;
    while (*ch) {
        if (*ch == '^') row--;
        if (*ch == 'v') row++;
        if (*ch == '<') col--;
        if (*ch == '>') col++;
        int visited = 0;
        for (size_t k = 0; k < ngrid; k++) {
            if ((grid[k].row == row) && (grid[k].col == col)) {
                visited = 1;
                break;
            }
        }
        if (!visited) {
            grid[ngrid].row = row;
            grid[ngrid].col = col;
            ngrid += 1;
        }
        ch++;
    }
    free(grid);
    return ngrid;
}

unsigned part2(const char *ch) {
    struct House *grid;
    unsigned ngrid = 0;
    int row[2] = {0};
    int col[2] = {0};
    grid = malloc(10000 * sizeof *grid);
    ngrid = 1;
    grid[0].row = 0;
    grid[0].col = 0;
    unsigned who = 0;
    while (*ch) {
        if (*ch == '^') row[who]--;
        if (*ch == 'v') row[who]++;
        if (*ch == '<') col[who]--;
        if (*ch == '>') col[who]++;
        int visited = 0;
        for (size_t k = 0; k < ngrid; k++) {
            if ((grid[k].row == row[who]) && (grid[k].col == col[who])) {
                visited = 1;
                break;
            }
        }
        if (!visited) {
            grid[ngrid].row = row[who];
            grid[ngrid].col = col[who];
            ngrid += 1;
        }
        who = !who;
        ch++;
    }
    free(grid);
    return ngrid;
}

int main(void) {
    char data[10000];
    char *p = data;
    int ch;
    while ((ch = getchar()) != EOF) {
        *p++ = ch;
    }
    *p = 0;
    printf("DAY03-PART1: Santa visitd %u houses.\n", part1(data));
    printf("DAY03-PART2: They deliver presents to %u houses.\n", part2(data));
    return 0;
}
