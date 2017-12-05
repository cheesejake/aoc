#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int min, max;
    int sum = 0;
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
        char *p = buf;
        int v;
        errno = 0;
        v = strtol(p, &p, 10);
        min = max = v;
        while (v > 0) {
            if (v > max) max = v;
            if (v < min) min = v;
            v = strtol(p, &p, 10);
        }
        sum += (max - min);
    }
    printf("value is %d.\n", sum);
    return 0;
}
