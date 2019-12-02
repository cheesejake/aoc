#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects data to be in stdin, call it like below
// $ ./a.out <02.txt
// $ echo 1,0,0,0,99 | ./a.out

int main(void) {
    int basememory[250];               // enough for my input
    int n = 0;
    while (scanf("%d", &basememory[n]) == 1) {
        getchar();                     // read & ignore comma (or newline)
        n++;
    }
    for (int noun = 0; noun < 100; noun++) {
        for (int verb = 0; verb < 100; verb++) {
            int intcode[150];
            memmove(intcode, basememory, n * sizeof *basememory);
            intcode[1] = noun;
            intcode[2] = verb;
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
            if (((noun == 12) && (verb == 2)) || (intcode[0] == 19690720)) {
                printf("Value left at position 0 with noun=%d and verb=%d: %d\n", noun, verb, intcode[0]);
            }
        }
    }
    return 0;
}
