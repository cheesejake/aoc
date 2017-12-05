#include <stdio.h>
#include <string.h>

int vowel3(const char *s) {
    int v = 0;
    while (*s) {
        if (*s == 'a') v++;
        if (*s == 'e') v++;
        if (*s == 'i') v++;
        if (*s == 'o') v++;
        if (*s == 'u') v++;
        s++;
        if (v == 3) break;
    }
    return (v >= 3);
}

int dblltr(const char *s) {
    const char *t = s + 1;
    while (*t) {
        if (*s == *t) return 1;
        s++;
        t++;
    }
    return 0;
}

int abcdpqxy(const char *s) {
    const char *t = s + 1;
    while (*t) {
        if ((*s == 'a') && (*t == 'b')) return 1;
        if ((*s == 'c') && (*t == 'd')) return 1;
        if ((*s == 'p') && (*t == 'q')) return 1;
        if ((*s == 'x') && (*t == 'y')) return 1;
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
        if (!vowel3(buf)) continue;
        if (!dblltr(buf)) continue;
        if (abcdpqxy(buf)) continue;
        nice++;
    }
    printf("There are %d nice strings.\n", nice);
    return 0;
}
