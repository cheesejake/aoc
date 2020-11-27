#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Wire {
    char name[50];
    _Bool hasvalue;
    unsigned value;
};

struct Input {
    int inputtype; // 0: (empty); 1: gate; 2: wire; 3; value
    union {
        struct Gate *gate;
        struct Wire *wire;
        unsigned value;
    } input;
};

struct Instruction {
    struct Input *input[2];
    int gatetype; // 1=and; 2=lshift; 4=not; 8=or; 16=rshift
    struct Wire *output;
};

struct Circuit {
    struct Instruction *data;
    size_t ndata;
};

void parseline(const char *line, struct Circuit *c) {
    const char *p = line;
    // ... i0, i1, gt, wo
    struct Input *i0 = malloc(sizeof *i0);
    struct Input *i1 = malloc(sizeof *i1);
    int gt;
    struct Wire *wo = malloc(sizeof *wo);
    if (isupper((unsigned char)*line)) {
        // NOT
        i0->inputtype = 1;
    } else {
        if (isdigit((unsigned char)*line)) {
            // value
            i0->inputtype = 3;
            i0->input.value = strtoul(p, &p, 10);
        } else {
            // wire
            i0->inputtype = 2;
            i0->input.wire = strtoul(p, &p, 10);
        }
    }

    struct Instruction *tmp = realloc(c->data, (c->ndata + 1) * sizeof *tmp);
    if (!tmp) {
        fprintf(stderr, "no memory. Aborted.\n");
        exit(EXIT_FAILURE);
    }
    c->data = tmp;
    c[c->ndata].input[0] = i0;
    c[c->ndata].input[1] = i1;
    c[c->ndata].gatetype = gt;
    c[c->ndata].output = wo;
}

int main(void) {
    struct Circuit c[1] = {0};
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {
        buf[strlen(buf) - 1] = 0;
        parseline(buf, c);
    }
    return 0;
}
