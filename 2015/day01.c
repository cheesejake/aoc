#include <stdio.h>

int part1(const char *data) {
    int floor = 0;
    while (*data) {
        if (*data == '(') floor++;
        if (*data == ')') floor--;
        data++;
    }
    //printf("DAY01-PART1: Santa goes to floor %d.\n", floor);
    return floor;
}

int part2(const char *data) {
    int floor = 0;
    int kk = 0, k = 0;
    while (*data) {
        k++;
        if (*data == '(') floor++;
        if (*data == ')') floor--;
        if (floor < 0) { kk = k; break; }
        data++;
    }
    return kk;
}

int main(void) {
    char data[10000];
    char *p = data;
    while ((*p = getchar()) != EOF) p++;
    *p = 0;

    printf("DAY01-PART1: Santa goes to floor %d.\n", part1(data));

    int b = part2(data);
    printf("DAY01-PART2: ");
    if (b) {
        printf("Santa enters the basement at position %d.\n", b);
    } else {
        printf("Santa never enters the basement.\n");
    }
}
