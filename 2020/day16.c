#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quit(const char *msg) {
    if (msg) fprintf(stderr, "%s\n", msg);
    exit(1);
}

struct Range { int lo1, hi1, lo2, hi2; };
typedef int Ticket[21];

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
            if (errors == nr) {
                error += n[tt][uu];
                n[tt][20] = 1;   // invalidate ticket for part 2
            }
        }
    }
    printf("Day 16, part 1: %d\n", error);
}

void part2(struct Range *r, int nr, Ticket *n, int nn) {
    int arrangements[20][20] = {0};
    for (int kk = 0; kk < nn; kk++) {
        if (n[kk][20] == 1) continue;  // ignore invalid tickets
        for (int row = 0; row < 20; row++) {
            for (int col = 0; col < 20; col++) {
                if (!inrange(n[kk][col], r[row])) {
                    arrangements[row][col] = 1;
                }
            }
        }
    }
    /* examine the output and keep adding restrictions :-)
    for (int kk = 0; kk < 20; kk++) if (kk != 15) arrangements[kk][18] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 18) arrangements[kk][9] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 9) arrangements[kk][13] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 14) arrangements[kk][3] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 3) arrangements[kk][2] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 5) arrangements[kk][17] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 2) arrangements[kk][19] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 1) arrangements[kk][6] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 4) arrangements[kk][16] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 0) arrangements[kk][1] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 12) arrangements[kk][5] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 8) arrangements[kk][7] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 13) arrangements[kk][10] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 16) arrangements[kk][8] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 11) arrangements[kk][4] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 7) arrangements[kk][11] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 19) arrangements[kk][0] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 6) arrangements[kk][15] = 1;
    for (int kk = 0; kk < 20; kk++) if (kk != 10) arrangements[kk][12] = 1;
    */
    // TODO: do these restrictions programatically
    printf("col       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19\n");
    for (int row = 0; row < 20; row++) {
        printf("row %2d |", row);
        for (int col = 0; col < 20; col++) {
            if (arrangements[row][col] == 0) printf(" xx");
            else printf("   ");
        }
        printf(" |\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "syntax: ./a.out <filename>\n");
        exit(EXIT_FAILURE);
    }
    struct Range validranges[20];
    int nranges = 0;
    Ticket myticket;
    Ticket nearby[250] = {0};
    int nnearbys = 0;
    parseinput(argv[1], validranges, &nranges,
                        myticket,
                        nearby, &nnearbys);
    part1(validranges, nranges, nearby, nnearbys);
    part2(validranges, nranges, nearby, nnearbys);
}
