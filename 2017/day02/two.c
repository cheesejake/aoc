#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int sum = 0;
    int values[1000];
    int n;
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
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
    }
    printf("value is %d.\n", sum);
    return 0;
}
