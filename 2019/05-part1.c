#include <stdio.h>
#include <stdlib.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects TEST to be in specified command line parameter
// and data following it
// $ ./a.out 05-test1.dat 1

#define INPUTSIZE 2600                 // enough for my input

int main(int argc, char **argv) {
    argc = 2;
    int intcode[INPUTSIZE];
    int n = 0;
    FILE *test = fopen(argv[1], "r");
    while (fscanf(test, "%d", &intcode[n]) == 1) {
        getc(test);                    // read & ignore comma (or newline)
        n++;
    }
    fclose(test);

    int k = 0, kk = 0;
    while (k < n) {
        int tmp;
        int ma = intcode[k] / 100 % 10;
        int mb = intcode[k] / 1000 % 10;
        printf("\nIP @ %d ==> %d %d %d %d\n", k, intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
        switch (intcode[k] % 100) {
            default: printf("Something went wrong.\n");
                     exit(EXIT_FAILURE);
                     break;
            case 1: printf("%d [%d][%d][%d] ==> ", intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
                    tmp = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    tmp += mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                    printf("changing [%d] to %d\n", intcode[k + 3], tmp);
                    intcode[intcode[k + 3]] = tmp;
                    kk = 4;
                    break;
            case 2: printf("%d [%d][%d][%d] ==> ", intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
                    tmp = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    tmp *= mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                    printf("changing [%d] to %d\n", intcode[k + 3], tmp);
                    intcode[intcode[k + 3]] = tmp;
                    kk = 4;
                    break;
            case 3: printf("%d [%d] ==> ", intcode[k], intcode[k + 1]);
                    tmp = atoi(argv[argc++]);
                    printf("changing [%d] to %d\n", intcode[k + 1], tmp);
                    intcode[intcode[k + 1]] = tmp;
                    kk = 2;
                    break;
            case 4: printf("%d [%d]\n", intcode[k], intcode[k + 1]);
                    tmp = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    printf("RESULT from [%d]: %d\n", intcode[k + 1], tmp);
                    kk = 2;
                    break;
            case 99: printf("%d\n", intcode[k]);
                     k = n;
                     kk = 1;
                     break;
        }
        k += kk;
    }
    return 0;
}
