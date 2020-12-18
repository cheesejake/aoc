#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quit(const char *msg) {
    if (msg) printf("%s\n", msg);
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

long long unsigned evaluate(const char *p, const char *prec) {
    long long unsigned ret;
    struct numberStack ns[1] = {0};
    struct charStack cs[1] = {0};
    while (*p) {
        while (*p == ' ') p++; // skip whitespace
        switch (*p) {
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
                npush(ns, *p - '0');
                break;
            case '(': cpush(cs, '('); break;
            case ')':
                while (cs->c[cs->n - 1] != '(') {
                    long long unsigned a, b;
                    a = npop(ns);
                    b = npop(ns);
                    char c = cpop(cs);
                    if (c == '+') npush(ns, a + b);
                    if (c == '*') npush(ns, a * b);
                }
                if ((cs->n > 0) && (cs->c[cs->n - 1] == '(')) {
                    cpop(cs); // discard '('
                }
                break;
            default: // + or *
                while ((cs->n >= 1)
                        && ((cs->c[cs->n - 1] != *prec) || (0))
                        && (cs->c[cs->n - 1] != '(')) {
                    long long unsigned a, b;
                    a = npop(ns);
                    b = npop(ns);
                    char c = cpop(cs);
                    if (c == '+') npush(ns, a + b);
                    if (c == '*') npush(ns, a * b);
                }
                cpush(cs, *p);
                break; // unneeded because I left default as last
        }
        p++;
    }
    while (cs->n) {
        long long unsigned a, b;
        a = npop(ns);
        b = npop(ns);
        char c = cpop(cs);
        if (c == '+') npush(ns, a + b);
        if (c == '*') npush(ns, a * b);
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
    long long unsigned total2 = 0;
    while (fgets(buf, sizeof buf, f)) {
        buf[strcspn(buf, "\n")] = 0;
        long long unsigned res = evaluate(buf, "");
        total += res;
        long long unsigned res2 = evaluate(buf, "*+");
        total2 += res2;
    }
    fclose(f);
    printf("Day 18, part 1: %llu\n", total);
    printf("Day 18, part 2: %llu\n", total2);
}
