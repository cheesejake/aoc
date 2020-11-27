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
    int row = 0;
    int col = 0;
    grid = malloc(10000 * sizeof *grid);
    ngrid = 1;
    grid[0].row = row;
    grid[0].col = col;
    while ((ch = getchar()) != EOF) {
        if (ch == '^') row--;
        if (ch == 'v') row++;
        if (ch == '<') col--;
        if (ch == '>') col++;
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
    }
    free(grid);
    printf("Santa visitd %zu houses.\n", ngrid);
    return 0;
}
