#include <stdio.h>
#include <stdlib.h>

int fuel4mass(int mass) {
    if (mass < 3) return 0;
    int tmp = mass / 3 - 2;
    if (tmp <= 0) return 0;
    return tmp + fuel4mass(tmp);
}

int main(void) {
    int total = 0;
    char buf[100];
    while (fgets(buf, sizeof buf, stdin)) {
        int mass = strtol(buf, 0, 10);
        total += fuel4mass(mass);
    }
    printf("fuel requirements for all modules and fuel: %d\n", total);
}
