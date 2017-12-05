#include <stdio.h>
#include <string.h>

int pair(const char *s) {
    char p[3] = "";
    const char *t = s + 1;
    while (*t) {
        p[0] = *s;
        p[1] = *t;
        if (strstr(t + 1, p)) return 1;
        s++;
        t++;
    }
    return 0;
}

int repeat(const char *s) {
    const char *t = s + 2;
    while (*t) {
        if (*s == *t) return 1;
        s++;
        t++;
    }
    return 0;
}

int main(void) {
    char buf[1000];
    int nice = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        buf[strlen(buf) - 1] = 0;
        if (!pair(buf)) continue;
        if (!repeat(buf)) continue;
        nice++;
    }
    printf("There are %d nice strings.\n", nice);
    return 0;
}
