#include <stdio.h>
#include <stdlib.h>

struct House {
    int row;
    int col;
};

int main(void) {
    struct House *grid;
    size_t ngrid = 0;
    int ch;
    int row[2] = {0};
    int col[2] = {0};
    grid = malloc(10000 * sizeof *grid);
    ngrid = 1;
    grid[0].row = 0;
    grid[0].col = 0;
    unsigned who = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '^') row[who]--;
        if (ch == 'v') row[who]++;
        if (ch == '<') col[who]--;
        if (ch == '>') col[who]++;
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
    }
    free(grid);
    printf("They deliver presents to %zu houses.\n", ngrid);
    return 0;
}
