#include <stdio.h>

int score(const char *src) {
    int garbage = 0;
    int level = 0;
    int sum = 0;
    while (*src) {
        if (!garbage && (*src == '{')) { level++; sum += level; }
        if (!garbage && (*src == '}')) { level--; }
        if (*src == '<') garbage = 1;
        if (*src == '>') garbage = 0;
        if (*src == '!') src++;
        src++;
    }
    return sum;
}

int main(void) {
    char buf[20000];
    while (fgets(buf, sizeof buf, stdin)) {
        printf("stream score is %d.\n", score(buf));
    }
    return 0;
}
