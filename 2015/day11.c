#include <stdio.h>
#include <string.h>

int seq3(const char *p) {
    const char *q = p + 2;
    while (*q) {
        if ((*q == 1+*(q-1)) && (*(q-1) == 1+*(q-2))) return 1;
        q++;
    }
    return 0;
}

int iol(const char *p) {
    if (strchr(p, 'i')) return 1;
    if (strchr(p, 'o')) return 1;
    if (strchr(p, 'l')) return 1;
    return 0;
}

int twicedouble(const char *p) {
    const char *q = p + 1;
    while (*q) {
        if (*q == *p) {
            const char *r = q + 1;
            if (*r == 0) return 0;
            const char *s = r + 1;
            if (*s == 0) return 0;
            while (*s) {
                if ((*r == *s) && (*r != *q)) {
                    return 1;
                }
                r++; s++;
            }
        }
        q++; p++;
    }
    return 0;
}

int nextseq(char *p, int n) {
    if (n == 0) return 0;
    if (p[n-1] != 'z') {
        p[n-1] += 1;
        return 1;
    }
    p[n-1] = 'a';
    return nextseq(p, n - 1);
}

// assume `a` to `z` are sequential
int part1(char *dst, const char *src) {
    strcpy(dst, src);
    while (nextseq(dst, 8)) {
        if (!seq3(dst)) continue;
        if (iol(dst)) continue;
        if (twicedouble(dst)) {
            return 0;
        }
    }
    return 1;
}

#define part2 part1 // they're the same :)

int main(void) {
    char pwd[10] = {0};
    part1(pwd, "hepxcrrq");
    printf("DAY11-PART1: '%s'\n", pwd);
    char pwd2[10] = {0};
    part2(pwd2, pwd);
    printf("DAY11-PART2: '%s'\n", pwd2);
    return 0;
}
