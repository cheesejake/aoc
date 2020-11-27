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

int main(void) {
    int foo = 1;
    for (int p0 = 'a'; p0 <= 'z'; p0++) {
        for (int p1 = 'a'; p1 <= 'z'; p1++) {
            for (int p2 = 'a'; p2 <= 'z'; p2++) {
                for (int p3 = 'a'; p3 <= 'z'; p3++) {
                    for (int p4 = 'a'; p4 <= 'z'; p4++) {
                        for (int p5 = 'a'; p5 <= 'z'; p5++) {
                            for (int p6 = 'a'; p6 <= 'z'; p6++) {
                                for (int p7 = 'a'; p7 <= 'z'; p7++) {
                                    if (foo) {
                                        foo = 0;
                                        p0 = 'h';
                                        p1 = 'e';
                                        p2 = 'p';
                                        p3 = 'x';
                                        p4 = 'c';
                                        p5 = 'r';
                                        p6 = 'r';
                                        p7 = 'q';
                                    }
                                    char p[] = {p0, p1, p2, p3, p4, p5, p6, p7, 0};
                                    if (!seq3(p)) continue;
                                    if (iol(p)) continue;
                                    if (twicedouble(p)) {
                                        printf("next password: '%s'\n", p);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
