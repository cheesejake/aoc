#include <stdio.h>
#include <string.h>

void halfcaptcha(const char *s) {
    const char *a = s;
    const char *b = s + strlen(s) / 2;
    int sum = 0;
    while (*b) {
        if (*a == *b) sum += 2 * (*a - '0');
        a++;
        b++;
    }
    printf("sum is %d.\n", sum);
}

int main(void) {
    char buf[10000];
    fgets(buf, sizeof buf, stdin);
    buf[strlen(buf) - 1] = 0;
    halfcaptcha(buf);
    return 0;
}
