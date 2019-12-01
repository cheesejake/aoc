#include <stdio.h>
#include <stdlib.h>

// assume well-formed input, in range values, or that
// everything 'works'

int main(void) {
    int total = 0;
    char buf[100];                     // more than enough space
    while (fgets(buf, sizeof buf, stdin)) {
        int mass = strtol(buf, 0, 10); // error checking missing
        total += mass / 3 - 2;         // integer (truncating) division
    }
    printf("fuel requirements for all modules: %d\n", total);
    return 0;
}
