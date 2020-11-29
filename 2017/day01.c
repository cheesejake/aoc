#include <stdio.h>
#include <string.h>

// captcha
int part1(const char *s) {
    int sum = 0;
    const char *t = s;
    const char *u = s + 1;
    while (*u) {
        if (*t == *u) sum += *t - '0';
        t++;
        u++;
    }
    if (*t == *s) sum += *t - '0';
    return sum;
}

// halfcaptcha
int part2(const char *s) {
    const char *a = s;
    const char *b = s + strlen(s) / 2;
    int sum = 0;
    while (*b) {
        if (*a == *b) sum += 2 * (*a - '0');
        a++;
        b++;
    }
    return sum;
}

int main(void) {
    char buf[10000];
    fgets(buf, sizeof buf, stdin);
    buf[strlen(buf) - 1] = 0;
    printf("DAY01-PART1: %d\n", part1(buf));
    printf("DAY01-PART2: %d\n", part2(buf));
}
