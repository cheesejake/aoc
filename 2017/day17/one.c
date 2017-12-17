#include <stdio.h>
#include <stdlib.h>

#define FINAL_VALUE 2017

void printring(int *ring, int n, int p) {
    for (int k = 0; k < n; k++) {
        if (k == p) putchar('(');
        printf("%d", ring[k]);
        if (k == p) putchar(')');
        if (k < n) putchar(' ');
    }
    puts("");
}

int main(void) {
    char buf[100];
    fgets(buf, sizeof buf, stdin);
    int input = strtol(buf, NULL, 10);
    printf("input is %d.\n", input);
    int ring[FINAL_VALUE + 1] = {0};
    int curpos = 0;
    int nring = 1;
    printring(ring, nring, 0);
    for (int k = 1; k <= FINAL_VALUE; k++) {
        curpos = (curpos + input) % nring + 1;
        for (int j = FINAL_VALUE; j > curpos; j--) ring[j] = ring[j - 1];
        ring[curpos] = k;
        nring++;
        if (k < 10) printring(ring, nring, curpos);
    }
    printf("the value after 2017 is %d.\n", ring[(curpos + 1) % (FINAL_VALUE + 1)]);
}
