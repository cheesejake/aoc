#include <stdio.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

int main(void) {
    int mass, total = 0;
    while (scanf("%d", &mass) == 1) {
        total += mass / 3 - 2;         // integer (truncating) division
    }
    printf("fuel requirements for all modules: %d\n", total);
    return 0;
}
