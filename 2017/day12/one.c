#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Group {
    int data[2100];
    int ndata;
};

void printgroups(struct Group *g, int ng) {
    for (int k = 0; k < ng; k++) {
        if (g[k].ndata) {
            printf("Group %d (%d elements): ", k, g[k].ndata);
            for (int j = 0; j < g[k].ndata; j++) {
                printf(" %d", g[k].data[j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

int intcmp(const void *aa, const void *bb) {
    const int *a = aa;
    const int *b = bb;
   return *a - *b;
}

void sortuniq(struct Group *g, int index) {
    qsort(g[index].data, g[index].ndata, sizeof 42, intcmp);
    for (int k = 1; k < g[index].ndata; k++) {
        if (g[index].data[k - 1] == g[index].data[k]) {
            for (int j = k; j < g[index].ndata - 1; j++) {
                g[index].data[j] = g[index].data[j + 1];
            }
            g[index].ndata -= 1;
        }
    }
}

struct Group *nfind(struct Group *g, int ng, int n) {
    for (int k = 0; k < ng; k++) {
        for (int j = 0; j < g[k].ndata; j++) {
            if (g[k].data[j] == n) return g + k;
        }
    }
    return NULL;
}

//if any element of g[k] is in g[j] {
int intersect(struct Group *g, int k, int j) {
    for (int i = 0; i < g[k].ndata; i++) {
        for (int h = 0; h < g[j].ndata; h++) {
            if (g[k].data[i] == g[j].data[h]) return 1;
        }
    }
    return 0;
}

int main(void) {
    struct Group *g;
    g = calloc(2100, sizeof *g);
    int ng = 0;
    char buf[1000] = {0};
    while (fgets(buf, sizeof buf, stdin)) {
        buf[strlen(buf) - 1] = 0;
        struct Group tmpg[1] = {0};
        int first = 1;
        char *p = buf;
        while (*p) {
            int n = strtol(p, &p, 10);
            if (first) p += 3;
            p += 2;
            first = 0;
            tmpg->data[tmpg->ndata++] = n;
        }
        g[ng++] = tmpg[0];
        for (unsigned k = 0; k < sizeof buf; k++) buf[k] = 0;
    }
    for (int k = 0; k < ng; k++) {
        sortuniq(g, k);
    }
    //printf("After first sortuniq():\n");
    //printgroups(g, ng);
    int moves;
    do {
        moves = 0;
        for (int k = 1; k < ng; k++) {
            for (int j = 0; j < k; j++) {
                //if any element of g[k] is in g[j] {
                if (intersect(g, k, j)) {
                    for (int ik = 0; ik < g[k].ndata; ik++) {
                        g[j].data[g[j].ndata++] = g[k].data[ik];
                    }
                    sortuniq(g, j);
                    g[k].ndata = 0;
                    moves += 1;
                }
            }
        }
    } while (moves > 0);
    //printf("After integration:\n");
    //printgroups(g, ng);
    for (int k = 0; k < ng; k++) {
        if (g[k].ndata && (g[k].data[0] == 0)) {
            printf("Group with program ID 0 has %d programs.\n", g[k].ndata);
        }
    }
    return 0;
}
