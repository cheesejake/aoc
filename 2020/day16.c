#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quit(const char *msg) {
    if (msg) fprintf(stderr, "%s\n", msg);
    exit(1);
}

struct Range { int lo1, hi1, lo2, hi2; };
typedef int Ticket[20];

void parseinput(const char *filename, struct Range *r, int *nr,
                Ticket t, Ticket *n, int *nn) {
    char buf[100], *p;
    FILE *h = fopen(filename, "r");
    if (!h) quit("fopen error");
    do {
        fgets(buf, sizeof buf, h);
        p = strchr(buf, ':');
        if (p) {
           r[*nr].lo1 = strtol(p + 1, &p, 10);
           r[*nr].hi1 = strtol(p + 1, &p, 10);
           r[*nr].lo2 = strtol(p + 3, &p, 10);
           r[*nr].hi2 = strtol(p + 1, &p, 10);
           *nr += 1;
        }
    } while (buf[0] != '\n');
    do {
        fgets(buf, sizeof buf, h);
        if (isdigit((unsigned char)buf[0])) {
            t[0] = strtol(buf, &p, 10);
            for (int k = 1; k < *nr; k++) {
                t[k] = strtol(p + 1, &p, 10);
            }
        }
    } while (buf[0] != '\n');
    while (fgets(buf, sizeof buf, h)) {
        if (isdigit((unsigned char)buf[0])) {
            n[*nn][0] = strtol(buf, &p, 10);
            for (int k = 1; k < *nr; k++) {
                n[*nn][k] = strtol(p + 1, &p, 10);
            }
            *nn += 1;
        }
    }
    fclose(h);
}

int inrange(int value, struct Range r) {
    if ((r.lo1 <= value) && (value <= r.hi1)) return 1;
    if ((r.lo2 <= value) && (value <= r.hi2)) return 1;
    return 0;
}

void part1(struct Range *r, int nr, Ticket *n, int nn) {
    int error = 0;
    for (int tt = 0; tt < nn; tt++) {
        for (int uu = 0; uu < nr; uu++) {
            int errors = 0;
            for (int vv = 0; vv < nr; vv++) {
                if (!inrange(n[tt][uu], r[vv])) {
                    errors++;
                }
            }
            if (errors == nr) error += n[tt][uu];
        }
    }
    printf("Day 16, part 1: %d\n", error);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "syntax: ./a.out <filename>\n");
        exit(EXIT_FAILURE);
    }
    struct Range validranges[20];
    int nranges = 0;
    Ticket myticket;
    Ticket nearby[250];
    int nnearbys = 0;
    parseinput(argv[1], validranges, &nranges,
                        myticket,
                        nearby, &nnearbys);
    part1(validranges, nranges, nearby, nnearbys);
}
