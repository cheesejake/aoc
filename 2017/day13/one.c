#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Scanner {
    int range;
    int pos;
    int direction;
};

int main(void) {
    struct Scanner scan[200] = {0};
    int maxdepth = 0;
    int severity = 0;
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
        char *p = buf;
        int depth = strtol(p, &p, 10);
        if (depth > maxdepth) maxdepth = depth;
        p++;
        int range = strtol(p, NULL, 10);
        scan[depth].range = range;
        scan[depth].direction = 1;
    }
    for (int ps = 0; ps <= maxdepth; ps++) {
        if (scan[ps].direction) {
            if (scan[ps].pos == 0) {
                severity += ps * scan[ps].range;
            }
        }
        for (int k = 0; k < 200; k++) {
            if (scan[k].direction) {
                scan[k].pos += scan[k].direction;
                if (scan[k].pos == -1) {
                    scan[k].pos = 1;
                    scan[k].direction = 1;
                }
                if (scan[k].pos == scan[k].range) {
                    scan[k].pos = scan[k].range - 2;
                    scan[k].direction = -1;
                }
            }
        }
    }
    printf("severity of %d.\n", severity);
    return 0;
}
