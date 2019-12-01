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

int main(void) {
    char buf[10000];                   // large enough
    while (fgets(buf, sizeof buf, stdin)) {
        int d = distance(buf);
        printf("Easter Bunny HQ is %d blocks away.\n", d);
    }
    return 0;
}
