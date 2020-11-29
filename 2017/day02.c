#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int part1(char *buf) {
    int min, max;
    int sum = 0;
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
    return sum;
}

int part2(char *buf) {
    int sum = 0;
    int values[1000];
    int n;
    char *p = buf;
    int v;
    n = 0;
    v = strtol(p, &p, 10);
    while (v > 0) {
        values[n++] = v;
        v = strtol(p, &p, 10);
    }
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            int v1 = values[a];
            int v2 = values[b];
            if (v2 > v1) {
                int tmp = v1;
                v1 = v2;
                v2 = tmp;
            }
            if (v1 % v2 == 0) sum += v1/v2;
        }
    }
    return sum;
}

int main(void) {
    int sum1 = 0, sum2 = 0;
    char buffer[1000];
    while (fgets(buffer, sizeof buffer, stdin)) {
        sum1 += part1(buffer);
        sum2 += part2(buffer);
    }
    printf("DAY02-PART1: %d\n", sum1);
    printf("DAY02-PART2: %d\n", sum2);
}
