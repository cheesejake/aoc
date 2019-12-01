#include <stdio.h>
#include <stdlib.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

int distance(char *list) {
    int x = 0, y = 0;
    int direction = 0;                 // North, up
    while (1) {
        switch (*list) {
            case 'R': direction = (direction + 1) % 4; break;
            case 'L': direction = (direction + 3) % 4; break;
            default: fprintf(stderr, "bad input, program aborted");
                     exit(EXIT_FAILURE);
        }
        int blocks = strtol(list + 1, &list, 10);
        switch (direction) {
            default: x += blocks; break;
            case 1: y += blocks; break;
            case 2: x -= blocks; break;
            case 3: y -= blocks; break;
        }
        if (*list == ',') list++;
        if (*list == ' ') list++;
        if (*list == '\n') break;
    }
    if (x < 0) x = 0 - x;
    if (y < 0) y = 0 - y;
    return x + y;
}

struct Point { int x; int y; };
int pointvisited(int x, int y, struct Point *p, int np) {
    for (int k = 0; k < np; k++) {
        if ((p[k].x == x) && (p[k].y == y)) return 1;
    }
    return 0;
}
int distance2(char *list) {
    struct Point p[10000];
    p[0].x = 0; p[0].y = 0;
    int np = 1;
    int x = 0, y = 0;
    int direction = 0;
    while (1) {
        switch (*list) {
            default: direction = (direction + 1) % 4; break;
            case 'L': direction = (direction + 3) % 4; break;
        }
        int blocks = strtol(list + 1, &list, 10);
        for (int k = 0; k < blocks; k++) {
            switch (direction) {
                default: x += 1; break;
                case 1: y += 1; break;
                case 2: x -= 1; break;
                case 3: y -= 1; break;
            }
            if (pointvisited(x, y, p, np)) {
                if (x < 0) x = 0 - x;
                if (y < 0) y = 0 - y;
                return x + y;
            }
            p[np].x = x;
            p[np].y = y;
            np++;
        }
        if (*list == ',') list++;
        if (*list == ' ') list++;
        if (*list == '\n') break;
    }
    fprintf(stderr, "no point is visited twice.\n");
    return 0;
}

int main(void) {
    char buf[10000];                   // large enough
    while (fgets(buf, sizeof buf, stdin)) {
        int d1 = distance(buf);
        printf("Easter Bunny HQ is %d blocks away.\n", d1);
        int d2 = distance2(buf);
        printf("Easter Bunny HQ actually is %d blocks away.\n", d2);
    }
    return 0;
}
