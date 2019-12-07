#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects the Amplifier Controller Software
// to be in the first command line parameter
// $ ./a.out 07-test1.txt
//
// or, to use helping tools
// $ ./a.out 07-test1.txt | sort -gk7

int execute(int *intcode, int n, int signal, int input) {
    //printf("executing with signal %d and input %d\n", signal, input);
    int k = 0, kk = 0;
    int result = 0;
    int op3 = 0;
    while (k < n) {
        int tmp, tmp1, tmp2;
        int ma = intcode[k] / 100 % 10;
        int mb = intcode[k] / 1000 % 10;
        //printf("\nIP @ %d ==> %d %d %d %d\n", k, intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
        switch (intcode[k] % 100) {
            default: printf("Something went wrong.\n");
                     exit(EXIT_FAILURE);
                     break;
            case 1: //printf("%d [%d][%d][%d] ==> ", intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
                    tmp = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    tmp += mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                    //printf("changing [%d] to %d\n", intcode[k + 3], tmp);
                    intcode[intcode[k + 3]] = tmp;
                    kk = 4;
                    break;
            case 2: //printf("%d [%d][%d][%d] ==> ", intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
                    tmp = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    tmp *= mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                    //printf("changing [%d] to %d\n", intcode[k + 3], tmp);
                    intcode[intcode[k + 3]] = tmp;
                    kk = 4;
                    break;
            case 3: //printf("%d [%d] ==> ", intcode[k], intcode[k + 1]);
                         if (op3 == 0) tmp = signal;
                    else if (op3 == 1) tmp = input;
                    else {
                        printf("Something went wrong.\n");
                        exit(EXIT_FAILURE);
                    }
                    op3++;
                    //printf("changing [%d] to %d\n", intcode[k + 1], tmp);
                    intcode[intcode[k + 1]] = tmp;
                    kk = 2;
                    break;
            case 4: //printf("%d [%d]\n", intcode[k], intcode[k + 1]);
                    tmp = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    result = tmp;
                    //printf("RESULT from [%d]: %d\n", intcode[k + 1], tmp);
                    kk = 2;
                    break;
            case 5: //printf("%d [%d][%d]\n", intcode[k], intcode[k + 1], intcode[k + 2]);
                    tmp = ma ? intcode[k +  1] : intcode[intcode[k + 1]];
                    if (tmp != 0) {
                        k = mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                        //printf("changing IP to %d\n", k);
                        k -= 3;
                    }
                    kk = 3;
                    break;
            case 6: //printf("%d [%d][%d]\n", intcode[k], intcode[k + 1], intcode[k + 2]);
                    tmp = ma ? intcode[k +  1] : intcode[intcode[k + 1]];
                    if (tmp == 0) {
                        k = mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                        //printf("changing IP to %d\n", k);
                        k -= 3;
                    }
                    kk = 3;
                    break;
            case 7: //printf("%d [%d][%d][%d]\n", intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
                    tmp1 = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    tmp2 = mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                    tmp = (tmp1 < tmp2);
                    //printf("changing [%d] to %d\n", intcode[k + 3], tmp);
                    intcode[intcode[k + 3]] = tmp;
                    kk = 4;
                    break;
            case 8: //printf("%d [%d][%d][%d]\n", intcode[k], intcode[k + 1], intcode[k + 2], intcode[k + 3]);
                    tmp1 = ma ? intcode[k + 1] : intcode[intcode[k + 1]];
                    tmp2 = mb ? intcode[k + 2] : intcode[intcode[k + 2]];
                    tmp = (tmp1 == tmp2);
                    //printf("changing [%d] to %d\n", intcode[k + 3], tmp);
                    intcode[intcode[k + 3]] = tmp;
                    kk = 4;
                    break;
            case 99: //printf("%d\n", intcode[k]);
                     k = n;
                     kk = 1;
                     break;
        }
        k += kk;
    }
    //printf("Output is %d\n", result);
    return result;
}

#define INPUTSIZE 1300                 // enough for my input

int main(int argc, char **argv) {
    (void)argc;                        // argc unused, avoid warning
    int orgcode[INPUTSIZE];
    int intcode[INPUTSIZE];
    int n = 0;
    FILE *test = fopen(argv[1], "r");
    while (fscanf(test, "%d", &orgcode[n]) == 1) {
        getc(test);                    // read & ignore comma (or newline)
        n++;
    }
    fclose(test);

#if 1
    for (int pa = 0; pa < 5; pa++) {
        for (int pb = 0; pb < 5; pb++) {
            if (pb == pa) continue;
            for (int pc = 0; pc < 5; pc++) {
                if (pc == pa) continue;
                if (pc == pb) continue;
                for (int pd = 0; pd < 5; pd++) {
                    if (pd == pa) continue;
                    if (pd == pb) continue;
                    if (pd == pc) continue;
                    for (int pe = 0; pe < 5; pe++) {
                        int v;
                        if (pe == pa) continue;
                        if (pe == pb) continue;
                        if (pe == pc) continue;
                        if (pe == pd) continue;
                        memmove(intcode, orgcode, sizeof orgcode);
                        v = execute(intcode, n, pa, 0);
                        memmove(intcode, orgcode, sizeof orgcode);
                        v = execute(intcode, n, pb, v);
                        memmove(intcode, orgcode, sizeof orgcode);
                        v = execute(intcode, n, pc, v);
                        memmove(intcode, orgcode, sizeof orgcode);
                        v = execute(intcode, n, pd, v);
                        memmove(intcode, orgcode, sizeof orgcode);
                        v = execute(intcode, n, pe, v);
                        printf("Max thruster signal from phase %d%d%d%d%d: %d\n",
                              pa, pb, pc, pd, pe, v);
                    }
                }
            }
        }
    }
#else
    execute(orgcode, n, 4, 0);
#endif

    return 0;
}
