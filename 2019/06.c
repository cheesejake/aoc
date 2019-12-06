#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// in my input all objects have names with three symbols

// program expects input in stdin
// $ ./a.out <06-input.txt
// $ echo -e 'COM)FOO\nFOO)BAR' | ./a.out

#define NUMLINES 1500                  // enough for my input
#define NUMOBJECTS (NUMLINES * 2)

struct Vertex {
    char name[4];
    int *list;
    int nlist;
};

struct VertexArray {
    struct Vertex v[NUMOBJECTS];
    int nv;
};

int find(const char *name, struct VertexArray *p) {
    for (int k = 0; k < p->nv; k++) {
        if (strncmp(name, p->v[k].name, 3) == 0) return k;
    }
    return -1;
}

int findoradd(const char *name, struct VertexArray *p) {
    int tmp = find(name, p);
    if (tmp == -1) {
        tmp = p->nv;
        sprintf(p->v[p->nv].name, "%.3s", name);
        p->nv += 1;
    }
    return tmp;
}

int totalorbits(struct VertexArray *v, const char *com, int base) {
    int ret = base;
    int b = find(com, v);
    for (int k = 0; k < v->v[b].nlist; k++) {
        ret += totalorbits(v, v->v[v->v[b].list[k]].name, base + 1);
    }
    return ret;
}

int main(void) {
    char input[NUMLINES][8] = {0};
    int numlines = 0;
    char buf[20];
    while (fgets(buf, sizeof buf, stdin)) {
        //if (buf[3] != ')') printf("ERROR: %s", buf);
        //if (buf[7] != '\n') printf("ERROR: %s", buf);
        sprintf(input[numlines++], "%.7s", buf); // remove newline
    }
    struct VertexArray v[1] = {0};
    for (int k = 0; k < numlines; k++) {
        findoradd(input[k], v);
        findoradd(input[k] + 4, v);
    }
    for (int k = 0; k < numlines; k++) {
        int base = find(input[k], v);
        int stlt = find(input[k] + 4, v);
        v->v[base].list = realloc(v->v[base].list, (v->v[base].nlist + 1) * sizeof *v->v[base].list);
        v->v[base].list[v->v[base].nlist] = stlt;
        v->v[base].nlist += 1;
    }
    int tot = totalorbits(v, "COM", 0);
    printf("Total orbits: %d.\n", tot);
    for (int k = 0; k < v->nv; k++) free(v->v[k].list);
    return 0;
}
