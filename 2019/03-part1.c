#include <stdio.h>
#include <stdlib.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects data to be in stdin, call it like below
// $ ./a.out <03.txt
// $ echo -e "R8,U5,L5,D3\nU7,R6,D4,L4" | ./a.out

struct Point {
    int x, y;
    int usedflag;
};
struct PointArray {
    struct Point *p;
    int mp, np;
};

struct Point *findintersection(int x, int y, struct PointArray *a) {
    for (int k = 0; k < a->np; k++) {
        if ((a->p[k].x == x) && (a->p[k].y == y)) return a->p + k;
    }
    return NULL;
}

void fillgrid(struct PointArray *a, int flag, char *line) {
    int x = 0, y = 0;
    int deltax, deltay;
    while (*line) {
        switch (*line) {
            default: deltax = 0; deltay = 0; break;
            case 'R': deltax = 1; deltay = 0; break;
            case 'U': deltax = 0; deltay = 1; break;
            case 'L': deltax = -1; deltay = 0; break;
            case 'D': deltax = 0; deltay = -1; break;
        }
        if (deltax || deltay) {
            int len = strtol(line + 1, &line, 10);
            for (int k = 0; k < len; k++) {
                x += deltax;
                y += deltay;
                if (x || y) {
                    struct Point *pp = findintersection(x, y, a);
                    if (!pp) {
                        if (a->np == a->mp) {
                            a->mp = a->mp * 2 + 1;
                            a->p = realloc(a->p, a->mp * sizeof *a->p);
                        }
                        pp = a->p + a->np;
                        pp->x = x;
                        pp->y = y;
                        a->np += 1;
                    }
                    pp->usedflag |= flag;
                }
            }
        }
        line++;
    }
}

unsigned closestdistance(char *line1, char *line2) {
    struct PointArray a[1] = {0};
    fillgrid(a, 1, line1);
    fillgrid(a, 2, line2);
    unsigned mindist = -1;
    for (int k = 0; k < a->np; k++) {
        if ((a->p[k].x || a->p[k].y) && (a->p[k].usedflag == 3)) {
            unsigned d = abs(a->p[k].x) + abs(a->p[k].y);
            if (d < mindist) mindist = d;
        }
    }
    free(a->p);
    return mindist;
}

#define INPUTSIZE 1500                 // enough for my input

int main(void) {
    char line1[INPUTSIZE];
    char line2[INPUTSIZE];
    while (fgets(line1, sizeof line1, stdin)) {
        if (fgets(line2, sizeof line2, stdin)) {
            unsigned dist = closestdistance(line1, line2);
            printf("Distance to closest intersection is %u\n", dist);
        }
    }
    return 0;
}
