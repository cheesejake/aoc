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
    int linecount[2];
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
    int count = 0;
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
                        pp->linecount[0] = pp->linecount[1] = 0;
                        a->np += 1;
                    }
                    pp->usedflag |= flag;
                    count++;
                    if (pp->linecount[flag - 1] == 0) {
                        pp->linecount[flag - 1] = count;
                    }
                }
            }
        }
        line++;
    }
}

void closestdistance(char *line1, char *line2, unsigned *dist, unsigned *steps) {
    struct PointArray a[1] = {0};
    fillgrid(a, 1, line1);
    fillgrid(a, 2, line2);
    unsigned mindist = -1;
    unsigned minsteps = -1;
    for (int k = 0; k < a->np; k++) {
        if ((a->p[k].x || a->p[k].y) && (a->p[k].usedflag == 3)) {
            unsigned d = abs(a->p[k].x) + abs(a->p[k].y);
            if (d < mindist) mindist = d;
            unsigned s = a->p[k].linecount[0] + a->p[k].linecount[1];
            if (s < minsteps) minsteps = s;
        }
    }
    free(a->p);
    *dist = mindist;
    *steps = minsteps;
}

#define INPUTSIZE 1500                 // enough for my input

int main(void) {
    char line1[INPUTSIZE];
    char line2[INPUTSIZE];
    while (fgets(line1, sizeof line1, stdin)) {
        if (fgets(line2, sizeof line2, stdin)) {
            unsigned dist, steps;
            closestdistance(line1, line2, &dist, &steps);
            printf("Distance to closest intersection is %u\n", dist);
            printf("Fewest steps to reach intersection is %u\n", steps);
        }
    }
    return 0;
}
