#include <stdio.h>
#include <stdlib.h>

#define ALLOCATION_SIZE 30000000

struct NumberPair {
    int lastturn, prevturn;
};

void addnumber(struct NumberPair *data, int turn, int value) {
    if (value >= ALLOCATION_SIZE) {
        fprintf(stderr, "not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    data[value].prevturn = data[value].lastturn;
    data[value].lastturn = turn;
//    printf("turn %6d: added %d\n", turn, value);
}

int main(void) {
    struct NumberPair *data = calloc(ALLOCATION_SIZE, sizeof *data);
    int last, turn = 1;
    addnumber(data, turn++, last=0);
    addnumber(data, turn++, last=3);
    addnumber(data, turn++, last=6);
    while (turn <= 30000000) {
        if (data[last].prevturn == 0) {
            last = 0;
        } else {
            last = data[last].lastturn - data[last].prevturn;
        }
        addnumber(data, turn++, last);
        if (turn - 1 == 2020) {
            printf("day 15, part 1: %d\n", last);
        }
    }
    printf("day 15, part 2: %d\n", last);
    free(data);
    return 0;
}
