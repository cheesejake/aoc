#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Register {
    char name[100];
    long value;
};

void instruction(struct Register *data, int n,
                 char *dst, int op, int v,
                 char *src, int cond, int vv) {
    struct Register *wr, *rr;
    if ((wr = findreg(data, n, dst)) == NULL) wr = crtreg(data, &n, dst);
    if ((rr = findreg(data, n, src)) == NULL) rr = crtreg(data, &n, src);
}

int main(void) {
    struct Register *r = NULL;
    int nr = 0;
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
        char dstr[100] = "";
        char srcr[100] = "";
        long sumvalue, cmpvalue;
        int condition;
        int op = 1; /* inc; for dec, op will be -1 */
        char *src = buf;
        char *dst = dstr;
        while (*src != ' ') *dstr++ = *src++;
        src++; // skip space
        if (*src == 'd') op = -1;
        src += 4; // skip "inc " or "dec "
        sumvalue = strtol(src, &src, 10);
        src++; // skip space
        if (strncmp(src, "> ", 2) == 0) condition = 0;
        if (strncmp(src, "< ", 2) == 0) condition = 1;
        if (strncmp(src, ">= ", 3) == 0) condition = 2;
        if (strncmp(src, "== ", 3) == 0) condition = 3;
        if (strncmp(src, "<= ", 3) == 0) condition = 4;
        if (strncmp(src, "!= ", 3) == 0) condition = 5;
        cmpvalue = strtol(src, &src, 10);
        instruction(r, nr, dstr, op, sumvalue, srcr, condition, cmpvalue);
    }
    long max = r->value;
    for (int k = 0; k < nr; k++) if (r[k].value > max) max = r[k].value;
    printf("The largest value in any register is %ld.\n", max);
    return 0;
}
