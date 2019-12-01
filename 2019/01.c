#include <stdio.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects data to be in stdin, call it like below
// $ ./a.out <01.txt
// $ echo 100756 | ./a.out

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
    printf("Fuel requirements for all modules: %d\n", total1);
    printf("Fuel requirements for all modules and fuel: %d\n", total2);
    return 0;
}
