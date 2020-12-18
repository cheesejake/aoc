#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quit(const char *msg) {
    if (msg) fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

struct numberStack { long long unsigned u[100]; int n; };
struct charStack { char c[100]; int n; };

void npush(struct numberStack *n, long long unsigned u) {
    n->u[n->n] = u;
    n->n += 1;
}

void cpush(struct charStack *c, char ch) {
    c->c[c->n] = ch;
    c->n += 1;
}

long long unsigned ntop(struct numberStack *n) {
    if (n->n == 0) quit("empty number stack");
    return n->u[n->n - 1];
}

char ctop(struct charStack *c) {
    if (c->n == 0) quit("empty char stack");
    return c->c[c->n - 1];
}

long long unsigned npop(struct numberStack *n) {
    if (n->n == 0) quit("Empty number stack");
    n->n -= 1;
    return n->u[n->n];
}

char cpop(struct charStack *c) {
    if (c->n == 0) quit("Empty char stack");
    c->n -= 1;
    return c->c[c->n];
}

void reduce(struct numberStack *n, struct charStack *c) {
    if ((c->n >= 1) && (n->n >= 2)) {
        char lop = ctop(c);
        if ((lop == '+') || (lop == '*')) {
            long long unsigned a = npop(n);
            long long unsigned b = npop(n);
            if (lop == '+') npush(n, a+b);
            if (lop == '*') npush(n, a*b);
            cpop(c);
        }
    }
}

long long unsigned evaluate(const char *p) {
    long long unsigned ret;
    struct numberStack ns[1] = {0};
    struct charStack cs[1] = {0};
    while (*p) {
        while (*p == ' ') p++; // skip whitespace
             if (*p == '+') cpush(cs, '+');
        else if (*p == '*') cpush(cs, '*');
        else if (*p == '(') cpush(cs, '(');
        else if (*p == '1') { npush(ns, 1); reduce(ns, cs); }
        else if (*p == '2') { npush(ns, 2); reduce(ns, cs); }
        else if (*p == '3') { npush(ns, 3); reduce(ns, cs); }
        else if (*p == '4') { npush(ns, 4); reduce(ns, cs); }
        else if (*p == '5') { npush(ns, 5); reduce(ns, cs); }
        else if (*p == '6') { npush(ns, 6); reduce(ns, cs); }
        else if (*p == '7') { npush(ns, 7); reduce(ns, cs); }
        else if (*p == '8') { npush(ns, 8); reduce(ns, cs); }
        else if (*p == '9') { npush(ns, 9); reduce(ns, cs); }
        else if (*p == ')') { char ck = cpop(cs); if (ck != '(') quit("bad expression"); reduce(ns, cs); }
        p++;
    }
    while (cs->n) {
        unsigned long long a = npop(ns);
        long long unsigned b = npop(ns);
        char op = cpop(cs);
        if (op == '+') npush(ns, a+b);
        if (op == '*') npush(ns, a*b);
    }
    ret = npop(ns);
    return ret;
}

int main(int argc, char **argv) {
    if (argc != 2) quit("syntax: ./a.out <filename>");
    FILE *f = fopen(argv[1], "r");
    if (!f) quit("open error");
    char buf[250] = {0};
    long long unsigned total = 0;
    while (fgets(buf, sizeof buf, f)) {
        buf[strcspn(buf, "\n")] = 0;
        long long unsigned res = evaluate(buf);
        total += res;
    }
    fclose(f);
    printf("Day 18, part 1: %llu\n", total);
}
