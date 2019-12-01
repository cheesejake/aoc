#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int total = 0;
    char buf[100];
    while (fgets(buf, sizeof buf, stdin)) {
        int mass = strtol(buf, 0, 10);
        total += mass / 3 - 2;
    }
    printf("fuel requirements for all modules: %d\n", total);
}
