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

struct Object {
    char name[4];
    int distance;
};

struct ObjectArray {
    struct Object o[NUMOBJECTS];
    int no;
};

struct Object *find(const char *name, struct ObjectArray *p) {
    for (int k = 0; k < p->no; k++) {
        if (strncmp(name, p->o[k].name, 3) == 0) return p->o + k;
    }
    return NULL;
}

struct Object *findoradd(const char *name, struct ObjectArray *p) {
    struct Object *tmp = find(name, p);
    if (tmp == NULL) {
        tmp = p->o + p->no;
        sprintf(p->o[p->no].name, "%.3s", name);
        p->no += 1;
    }
    return tmp;
}

int nzeroes(struct ObjectArray *p) {
    int z = 0;
    for (int k = 0; k < p->no; k++) {
        if (p->o[k].distance == 0) z++;
    }
    return z;
}

int main(void) {
    char buf[20];
    char input[NUMLINES][8] = {0};
    int numlines = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        //if (buf[3] != ')') printf("ERROR: %s", buf);
        //if (buf[7] != '\n') printf("ERROR: %s", buf);
        sprintf(input[numlines++], "%.7s", buf); // remove newline
    }
    struct ObjectArray o[1] = {0};
    for (int k = 0; k < numlines; k++) {
        findoradd(input[k], o);
        findoradd(input[k] + 4, o);
    }
    while (nzeroes(o) > 1) {
        for (int k = 0; k < numlines; k++) {
            struct Object *base = find(input[k], o);
            struct Object *stlt = find(input[k] + 4, o);
            if (base->distance && !stlt->distance) {
                stlt->distance = base->distance + 1;
            }
            if (strncmp(base->name, "COM", 3) == 0) {
                stlt->distance = 1;
            }
        }
    }
    int tot = 0;
    for (int k = 0; k < o->no; k++) {
        tot += o->o[k].distance;
    }
    printf("Total orbits: %d.\n", tot);
    return 0;
}
