#include <stdio.h>
#include <string.h>

int captcha(const char *s) {
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

int main(void) {
    char buf[10000];
    fgets(buf, sizeof buf, stdin);
    buf[strlen(buf) - 1] = 0;
    printf("captcha is %d.\n", captcha(buf));
    return 0;
}
