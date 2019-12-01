#include <stdio.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

int fuel(int mass) {
    if (mass < 9) return 0;
    int tmp = mass / 3 - 2;
    return tmp + fuel(tmp);            // recurse
}

int main(void) {
    int mass, total1 = 0, total2 = 0;
    while (scanf("%d", &mass) == 1) {
        total1 += mass / 3 - 2;         // integer (truncating) division
        total2 += fuel(mass);
    }
    printf("fuel requirements for all modules: %d\n", total1);
    printf("fuel requirements for all modules and fuel: %d\n", total2);
    return 0;
}
