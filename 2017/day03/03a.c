#include <stdio.h>
#include <stdlib.h>

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char buf[100];
    fgets(buf, sizeof buf, stdin);
    int x = strtol(buf, NULL, 10); // assume all OK
    int m0 = 0, m1 = 1;
    int step = 0, dist = 0;
    int group = 0;
    // calculate values in the same row/column as the 1
    while (m1 < x) {
        m0 = m1;
        if (!group) step += 2;
        m1 += step;
        if (!group) m1 -= 1;
        if (!group) dist += 1;
        group = (group + 1) % 4;
    }
    printf("dist: %d\n", dist + minimum(x - m0, m1 - x));
    return 0;
}
