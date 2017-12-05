#include <stdio.h>
#include <stdlib.h>

enum directions { RIGHT, UP, LEFT, DOWN };

int bruteforce(int n) {
    int mat[101][101] = {0};
    int row = 50, col = 50;
    int value = 1;
    mat[row][col] = value;
    enum directions dir = RIGHT;
    while (value <= n) {
        switch (dir) {
            default: fprintf(stderr, "Impossible error.\n");
                     exit(EXIT_FAILURE);
                     break;
            case RIGHT: col += 1;
                        if (mat[row-1][col] == 0) dir = UP;
                        break;
            case UP: row -= 1;
                     if (mat[row][col-1] == 0) dir = LEFT;
                     break;
            case LEFT: col -= 1;
                     if (mat[row+1][col] == 0) dir = DOWN;
                     break;
            case DOWN: row += 1;
                     if (mat[row][col+1] == 0) dir = RIGHT;
                     break;
        }
        value = -mat[row][col];
        for (int rr = -1; rr < 2; rr++) {
            for (int cc = -1; cc < 2; cc++) {
                value += mat[row + rr][col + cc];
            }
        }
        mat[row][col] = value;
    }
    return value;
}

int main(void) {
    char buf[100];
    fgets(buf, sizeof buf, stdin);
    int x = strtol(buf, NULL, 10);
    int ans = bruteforce(x);
    printf("answer: %d\n", ans);
    return 0;
}
