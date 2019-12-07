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

#define INPUTSIZE 1300                 // enough for my input

struct VM {
    int code[INPUTSIZE];
    int ip;
    int status; // 0: reset, 1: running, 2:input, 3:stopped
    int value;
};

void execute(struct VM *m) {
    for (;;) {
        int kk;
        int tmp, tmp1, tmp2;
        int ma = m->code[m->ip] / 100 % 10;
        int mb = m->code[m->ip] / 1000 % 10;
        switch (m->code[m->ip] % 100) {
            default: printf("Something went wrong.\n");
                     exit(EXIT_FAILURE);
                     break;
            case 1: //printf("%d [%d][%d][%d] ==> ", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2], m->code[m->ip + 3]);
                    tmp = ma ? m->code[m->ip + 1] : m->code[m->code[m->ip + 1]];
                    tmp += mb ? m->code[m->ip + 2] : m->code[m->code[m->ip + 2]];
                    //printf("changing [%d] to %d\n", m->code[m->ip + 3], tmp);
                    m->code[m->code[m->ip + 3]] = tmp;
                    kk = 4;
                    break;
            case 2: //printf("%d [%d][%d][%d] ==> ", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2], m->code[m->ip + 3]);
                    tmp = ma ? m->code[m->ip + 1] : m->code[m->code[m->ip + 1]];
                    tmp *= mb ? m->code[m->ip + 2] : m->code[m->code[m->ip + 2]];
                    //printf("changing [%d] to %d\n", m->code[m->ip + 3], tmp);
                    m->code[m->code[m->ip + 3]] = tmp;
                    kk = 4;
                    break;
            case 3: if (m->status == 1) { m->status = 2; return; }
                    m->status = 1;
                    tmp = m->value;
                    //printf("changing [%d] to %d\n", m->code[m->ip + 1], tmp);
                    m->code[m->code[m->ip + 1]] = tmp;
                    kk = 2;
                    break;
            case 4: //printf("%d [%d][%d]\n", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2]);
                    tmp = ma ? m->code[m->ip + 1] : m->code[m->code[m->ip + 1]];
                    m->value = tmp;
                    //printf("RESULT from [%d]: %d\n", m->code[m->ip + 1], tmp);
                    kk = 2;
                    break;
            case 5: //printf("%d [%d][%d]\n", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2]);
                    tmp = ma ? m->code[m->ip +  1] : m->code[m->code[m->ip + 1]];
                    if (tmp != 0) {
                        m->ip = mb ? m->code[m->ip + 2] : m->code[m->code[m->ip + 2]];
                        //printf("changing IP to %d\n", m->ip);
                        m->ip -= 3;
                    }
                    kk = 3;
                    break;
            case 6: //printf("%d [%d][%d]\n", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2]);
                    tmp = ma ? m->code[m->ip +  1] : m->code[m->code[m->ip + 1]];
                    if (tmp == 0) {
                        m->ip = mb ? m->code[m->ip + 2] : m->code[m->code[m->ip + 2]];
                        //printf("changing IP to %d\n", m->ip);
                        m->ip -= 3;
                    }
                    kk = 3;
                    break;
            case 7: //printf("%d [%d][%d][%d]\n", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2], m->code[m->ip + 3]);
                    tmp1 = ma ? m->code[m->ip + 1] : m->code[m->code[m->ip + 1]];
                    tmp2 = mb ? m->code[m->ip + 2] : m->code[m->code[m->ip + 2]];
                    tmp = (tmp1 < tmp2);
                    //printf("changing [%d] to %d\n", m->code[m->ip + 3], tmp);
                    m->code[m->code[m->ip + 3]] = tmp;
                    kk = 4;
                    break;
            case 8: //printf("%d [%d][%d][%d]\n", m->code[m->ip], m->code[m->ip + 1], m->code[m->ip + 2], m->code[m->ip + 3]);
                    tmp1 = ma ? m->code[m->ip + 1] : m->code[m->code[m->ip + 1]];
                    tmp2 = mb ? m->code[m->ip + 2] : m->code[m->code[m->ip + 2]];
                    tmp = (tmp1 == tmp2);
                    //printf("changing [%d] to %d\n", m->code[m->ip + 3], tmp);
                    m->code[m->code[m->ip + 3]] = tmp;
                    kk = 4;
                    break;
            case 99: //printf("%d\n", m->code[m->ip]);
                     m->status = 3;
                     return;
                     break;
        }
        m->ip += kk;
    }
}

int loopback(struct VM *vm, int *phase) {
    for (int k = 0; k < 5; k++) {
        vm[k].status = 1;
        execute(vm + k);               // stop when asked for phase setting
        vm[k].value = phase[k];        // answer with setting
        execute(vm + k);               // restart; stop when asking for value
    }

    int currvm = 0;
    vm[4].value = 0; // make sure input for process A is correct
    while (vm[currvm].status == 2) {
        vm[currvm].value = vm[(currvm + 4) % 5].value;
        execute(vm + currvm);
        currvm = (currvm + 1) % 5;
    }
    return vm[4].value;
}

int main(int argc, char **argv) {
    (void)argc;                        // argc unused, avoid warning
    int orgcode[INPUTSIZE];
    struct VM vm[5] = {0};
    int n = 0;
    FILE *test = fopen(argv[1], "r");
    while (fscanf(test, "%d", &orgcode[n]) == 1) {
        getc(test);                    // read & ignore comma (or newline)
        n++;
    }
    fclose(test);

    int phase[5];
    for (phase[0] = 5; phase[0] < 10; phase[0]++) {
        for (phase[1] = 5; phase[1] < 10; phase[1]++) {
            if (phase[1] == phase[0]) continue;
            for (phase[2] = 5; phase[2] < 10; phase[2]++) {
                if (phase[2] == phase[0]) continue;
                if (phase[2] == phase[1]) continue;
                for (phase[3] = 5; phase[3] < 10; phase[3]++) {
                    if (phase[3] == phase[0]) continue;
                    if (phase[3] == phase[1]) continue;
                    if (phase[3] == phase[2]) continue;
                    for (phase[4] = 5; phase[4] < 10; phase[4]++) {
                        int v;
                        if (phase[4] == phase[0]) continue;
                        if (phase[4] == phase[1]) continue;
                        if (phase[4] == phase[2]) continue;
                        if (phase[4] == phase[3]) continue;
                        vm[0].ip = 0; memmove(vm[0].code, orgcode, sizeof orgcode);
                        vm[1].ip = 0; memmove(vm[1].code, orgcode, sizeof orgcode);
                        vm[2].ip = 0; memmove(vm[2].code, orgcode, sizeof orgcode);
                        vm[3].ip = 0; memmove(vm[3].code, orgcode, sizeof orgcode);
                        vm[4].ip = 0; memmove(vm[4].code, orgcode, sizeof orgcode);
                        v = loopback(vm, phase);
                        printf("Max thruster signal from phase %d%d%d%d%d: %d\n",
                              phase[0], phase[1], phase[2], phase[3], phase[4], v);
                    }
                }
            }
        }
    }

    return 0;
}
