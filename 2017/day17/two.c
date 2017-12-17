#include <stdio.h>
#include <stdlib.h>

#define FINAL_VALUE 50000000

int main(void) {
    char buf[100];
    fgets(buf, sizeof buf, stdin);
    int input = strtol(buf, NULL, 10);
    printf("input is %d.\n", input);
    int ring[2] = {0};
    int curpos = 0;
    int nring = 1;
    for (int k = 1; k <= FINAL_VALUE; k++) {
        curpos = (curpos + input) % nring + 1;
        if (curpos == 0) { printf("zero moved! Back to the drawing board!\n"); exit(EXIT_FAILURE); }
        if (curpos == 1) { ring[1] = k; }
        nring++;
    }
    printf("the value after 0 is %d.\n", ring[1]);
}
