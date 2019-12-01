#include <stdio.h>
#include <stdlib.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

int fuel4mass(int mass) {
    if (mass < 3) return 0;
    int tmp = mass / 3 - 2;            // integer (truncating) division
    if (tmp <= 0) return 0;
    return tmp + fuel4mass(tmp);       // recurse
}

int main(void) {
    int mass, total = 0;
    while (scanf("%d", &mass) == 1) {
        total += fuel4mass(mass);      // assume no overflow
    }
    printf("fuel requirements for all modules and fuel: %d\n", total);
    return 0;
}
