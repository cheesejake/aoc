#include <stdio.h>
#include <stdlib.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects data to be in stdin, call it like below
// $ ./a.out <02.txt
// $ echo 1,0,0,0,99 | ./a.out

#define INPUTSIZE 250                  // enough for my input

int main(void) {
    int intcode[INPUTSIZE];
    int n = 0;
    while (scanf("%d", &intcode[n]) == 1) {
        getchar();                     // read & ignore comma (or newline)
        n++;
    }
    intcode[1] = 12;
    intcode[2] = 2;
    for (int k = 0; k < n; k += 4) {
        switch (intcode[k]) {
            default: printf("Something went wrong.\n");
                     exit(EXIT_FAILURE);
                     break;
            case 1: intcode[intcode[k + 3]] = intcode[intcode[k + 1]] + intcode[intcode[k + 2]];
                    break;
            case 2: intcode[intcode[k + 3]] = intcode[intcode[k + 1]] * intcode[intcode[k + 2]];
                    break;
            case 99: k = n;
                     break;
        }
    }
    printf("Value left at position 0: %d\n", intcode[0]);
    return 0;
}
