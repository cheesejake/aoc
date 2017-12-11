#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void axial2cube(int dr, int dq, int *x, int *y, int *z) {
    *x = dr;
    *z = dq;
    *y = -*x-*z;
}

int distance(int dr1, int dq1, int dr2, int dq2) {
    int x1, y1, z1, x2, y2, z2;
    axial2cube(dr1, dq1, &x1, &y1, &z1);
    axial2cube(dr2, dq2, &x2, &y2, &z2);
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

void process(char *data) {
    int dr = 0, dq = 0;
    int skip;
    while (*data) {
             if (strncmp(data, "ne", 2) == 0) { dr += 1; dq -= 1; skip = 2; }
        else if (strncmp(data, "sw", 2) == 0) { dr -= 1; dq += 1; skip = 2; }
        else if (strncmp(data, "nw", 2) == 0) { dr -= 1;          skip = 2; }
        else if (strncmp(data, "se", 2) == 0) { dr += 1;          skip = 2; }
        else if (strncmp(data, "n",  1) == 0) {          dq -= 1; skip = 1; }
        else if (strncmp(data, "s",  1) == 0) {          dq += 1; skip = 1; }
        else { fprintf(stderr, "invalid input.\n"); exit(EXIT_FAILURE); }
        data += skip;
        if (*data == ',') data++;
    }
    printf("final position (%d, %d)... ", dr, dq);
    printf("at a distance of %d hexagons.\n", distance(dr, dq, 0, 0));
}

int main(void) {
    char buf[32000];
    while (fgets(buf, sizeof buf, stdin)) {
        buf[strlen(buf) - 1] = 0;
        process(buf);
    }
    return 0;
}
