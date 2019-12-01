#include <stdio.h>
#include <stdlib.h>

// assume well-formed input, in range values, or that
// everything 'works'

int fuel4mass(int mass) {
    if (mass < 3) return 0;
    int tmp = mass / 3 - 2;            // integer (truncating) division
    if (tmp <= 0) return 0;
    return tmp + fuel4mass(tmp);       // recurse
}

int main(void) {
    int total = 0;
    char buf[100];                     // more than enough space
    while (fgets(buf, sizeof buf, stdin)) {
        int mass = strtol(buf, 0, 10); // missing error checking
        total += fuel4mass(mass);      // assume no overflow
    }
    printf("fuel requirements for all modules and fuel: %d\n", total);
    return 9;
}
