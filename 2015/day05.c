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

int part1(char (*data)[20], unsigned n) {
    char buf[100];
    int nice = 0;
    for (unsigned k = 0; k < n; k++) {
        strcpy(buf, data[k]);
        if (!vowel3(buf)) continue;
        if (!dblltr(buf)) continue;
        if (abcdpqxy(buf)) continue;
        nice++;
    }
    return nice;
}

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

int part2(char (*data)[20], unsigned n) {
    char buf[100];
    int nice = 0;
    for (unsigned k = 0; k < n; k++) {
        strcpy(buf, data[k]);
        if (!pair(buf)) continue;
        if (!repeat(buf)) continue;
        nice++;
    }
    return nice;
}

int main(void) {
    char data[1200][20];
    unsigned ndata = 0;
    while (fgets(data[ndata], 20, stdin)) {
        data[ndata][strlen(data[ndata]) - 1] = 0;
        ndata++;
    }
    printf("DAY05-PART1: There are %d nice strings.\n", part1(data, ndata));
    printf("DAY05-PART2: There are %d nice strings.\n", part2(data, ndata));
    return 0;
}
