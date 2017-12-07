#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Program {
    char name[100];
    int weight;
    char supporter[100];
};

struct Program *ptrarrr(struct Program *p, int np, const char *name) {
    struct Program *r = NULL;
    for (int k = 0; k < np; k++) {
        if (strcmp(name, p[k].name) == 0) {
            r = p + k;
            break;
        }
    }
    return r;
}

void process(struct Program *p, int *npp, char *s) {
    int np = *npp;
    char basename[100] = "";
    int baseweight = 0;
    char *ps = s;
    char *pn = basename;
    while (isalpha((unsigned char)*ps)) {
        *pn++ = *ps++;
    }
    ps++; // skip space
    ps++; // skip parenthesis
    baseweight = strtol(ps, &ps, 10);
    ps++; // skip parenthesis
    struct Program *q;
    if ((q = ptrarrr(p, np, basename)) == NULL) {
        strcpy(p[np].name, basename);
        p[np].weight = baseweight;
        np++;
    } else {
        q->weight = baseweight;
    }
    if (*ps != '\n') ps += 4; // skip " -> "
    while (*ps != '\n') {
        char topname[100] = "";
        char *pt = topname;
        while (isalpha((unsigned char)*ps)) {
            *pt++ = *ps++;
        }
        struct Program *qq;
        if ((qq = ptrarrr(p, np, topname)) == NULL) {
            strcpy(p[np].name, topname);
            strcpy(p[np].supporter, basename);
            np++;
        } else {
            strcpy(qq->supporter, basename);
        }
        if (*ps == ',') ps += 2;
    }
    *npp = np;
}

int main(void) {
    char buf[1000];
    struct Program p[20000];
    int np = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        process(p, &np, buf);
    }
    for (int k = 0; k < np; k++) {
        if (p[k].supporter[0] == 0) printf("base program: %s\n", p[k].name);
    }
    return 0;
}
