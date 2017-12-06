#include <stdio.h>
#include <stdlib.h>

#define BANKSIZE 16
#define MAXITER 10000

struct Bank {
    int bank[BANKSIZE];
};

void cycle(struct Bank *b, int dstindex) {
    int srcindex = dstindex - 1;
    for (int k = 0; k < BANKSIZE; k++) b[dstindex].bank[k] = b[srcindex].bank[k];
    int maxindex = 0;
    int maxvalue = b[srcindex].bank[0];
    for (int k = 1; k < BANKSIZE; k++) {
        if (b[srcindex].bank[k] > maxvalue) {
            maxvalue = b[srcindex].bank[k];
            maxindex = k;
        }
    }
    b[dstindex].bank[maxindex] = 0;
    while (maxvalue) {
        maxindex = (maxindex + 1) % BANKSIZE;
        b[dstindex].bank[maxindex] += 1;
        maxvalue--;
    }
}

int beq(struct Bank *a, struct Bank *b) {
    for (int k = 0; k < BANKSIZE; k++) {
        if (a->bank[k] != b->bank[k]) return 0;
    }
    return 1;
}

int main(void) {
    struct Bank *b = malloc(sizeof *b); // assume all ok
    int nb = 1;
    for (int k = 0; k < BANKSIZE; k++) scanf("%d", &b[0].bank[k]); // assume all ok

    int cycles = 0;
    for (;;) {
        struct Bank *tmp = realloc(b, (nb + 1) * sizeof *tmp); // assume ok
        b = tmp;
        cycle(b, nb);
        cycles++;
        for (int k = 0; k < nb; k++) {
            if (beq(b + k, b + nb)) {
                printf("Loop size is %d.\n", nb - k);
                exit(EXIT_SUCCESS);
            }
        }
        if (cycles == MAXITER) {
            printf("Program aborted after %d redistributions.\n", MAXITER);
            exit(EXIT_FAILURE);
        }
        nb++;
    }
    return 0;
}
