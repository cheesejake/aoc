#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Scanner {
    int range;
    int pos;
    int direction;
};

void movescanners(struct Scanner *s, int n) {
    for (int k = 0; k < n; k++) {
        if (s->direction) {
            s->pos += s->direction;
            if (s->pos == -1) {
                s->pos = 1;
                s->direction = 1;
            }
            if (s->pos == s->range) {
                s->pos = s->range - 2;
                s->direction = -1;
            }
        }
        s++;
    }
}

void copyscanner(struct Scanner *dst, struct Scanner *src, int n) {
    for (int k = 0; k < n; k++) {
        *dst++ = *src++;
    }
}

int main(void) {
    struct Scanner scan[200];
    struct Scanner scab[200] = {0};
    int maxdepth = 0;
    char buf[1000];
    int caught;
    int delay = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        char *p = buf;
        int depth = strtol(p, &p, 10);
        if (depth > maxdepth) maxdepth = depth;
        p++;
        int range = strtol(p, NULL, 10);
        scab[depth].range = range;
        scab[depth].direction = 1;
    }
    do {
        delay += 1;
        caught = 0;
        movescanners(scab, 200);
        copyscanner(scan, scab, 200); // scan = scab;
        for (int ps = 0; ps <= maxdepth; ps++) {
            if (scan[ps].direction) {
                if (scan[ps].pos == 0) {
                    caught = 1;
                    break;
                }
            }
            movescanners(scan, 200);
        }
    } while (caught);
    printf("delay %d picoseconds.\n", delay);
    return 0;
}
