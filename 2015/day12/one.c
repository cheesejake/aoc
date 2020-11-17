#include <ctype.h>
#include <stdio.h>

int main(void) {
    int ch;
    int sign = 1;
    long long number = 0;
    long long total = 0;
    do {
        ch = getchar();
        putchar(ch);fflush(stdout);
        if (isdigit((unsigned char)ch)) {
            number *= 10;
            number += ch - '0';
        } else {
            if (ch == '-') {
                sign = -1;
            } else {
                if (number) {
                    printf(" <== adding %lld...\n", sign * number);
                    total += sign * number;
                }
                sign = 1;
                number = 0;
            }
        }
    } while (ch != EOF);
    printf("total is %lld.\n", total);
}
