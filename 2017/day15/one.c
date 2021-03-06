#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

long long unsigned next(long long unsigned last, long long unsigned mul, long long unsigned mod) {
    return (last * mul) % mod;
}

int main(void) {
    long long unsigned a;
    long long unsigned b;
    char buf[100], *p;
    fgets(buf, sizeof buf, stdin);
    p = buf;
    while (!isdigit((unsigned char)*p)) p++;
    a = strtoul(p, NULL, 10);
    fgets(buf, sizeof buf, stdin);
    p = buf;
    while (!isdigit((unsigned char)*p)) p++;
    b = strtoul(p, NULL, 10);
    long long unsigned count = 0;
    for (long long unsigned k = 0; k < 40000000; k++) {
        a = next(a, 16807, 2147483647);
        b = next(b, 48271, 2147483647);
        if ((a & 0xffff) == (b & 0xffff)) count += 1;
    }
    printf("The judges final count was %llu.\n", count);
    return 0;
}
