#include <ctype.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects the BOOST
// to be in the first command line parameter
// $ ./a.out 09-test1.txt [test value]

void quit(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

#define INPUTLENGTH 5000               // enough for my input

struct Cell {
    int loc;
    mpz_t bigdata;
};

struct VM {
    struct Cell *code;
    int ncode;
    int mcode;
    int relbase;
    int ip;
    int status; // 0: reset, 1: running, 2:input, 3:stopped
    mpz_t bigsignal;
};

int baseopcode(double opcode) {
    return ((int)opcode) % 100;
}

int mode(mpz_t opcode, int n) {
    // opcode 1002
    //         ^ mode(opcode, 1)
    //        ^ mode(opcode, 2)
    //       ^ mode(opcode, 3) --- omitted, 0
    int op = mpz_get_si(opcode);
    if (op < 0) quit("invalid opcode");
    if (n == 1) return (op / 100) % 10;
    if (n == 2) return (op / 1000) % 10;
    if (n == 3) return (op / 10000) % 10;
    if (n == 4) return (op / 100000) % 10;
    return 0;
}

struct Cell *cellat(struct VM *m, int ip) {
    for (int k = 0; k < m->ncode; k++) {
        if (m->code[k].loc == ip) return m->code + k;
    }
    if (m->ncode == m->mcode) {
        m->mcode += 10;
        m->code = realloc(m->code, m->mcode * sizeof *m->code);
    }
    m->code[m->ncode].loc = ip;
    mpz_set_ui(m->code[m->ncode].bigdata, 0);
    m->ncode++;
    return m->code + m->ncode;
}

struct Cell *modedcellat(struct VM *m, int ip, int mode) {
    struct Cell *tmp1, *tmp2;
    int itmp;
    switch (mode) {
        default: quit("bad mode in opcode");
        case 0: // position mode
                tmp1 = cellat(m, ip);
                itmp = mpz_get_si(tmp1->bigdata);
                tmp2 = cellat(m, itmp);
                break;
        case 1: // immediate mode
                tmp2 = cellat(m, ip);
                break;
        case 2: // relative mode
                tmp1 = cellat(m, ip);
                itmp = mpz_get_si(tmp1->bigdata);
                tmp2 = cellat(m, m->relbase + itmp);
                break;
    }
    if (!tmp2) {
        printf("Returning NULL from modedcellat(..., %d, %d)\n", ip, mode);
    }
    return tmp2;
}

void printcode(struct VM *m, int n) {
    printf("code: ...");
    for (int k = 0; k < n; k++) {
        struct Cell *i = cellat(m, m->ip + k);
        gmp_printf(" %Z", i->bigdata);
    }
    puts(" ...");
}

void execute(struct VM *m) {
    for (;;) {
        struct Cell *i0 = cellat(m, m->ip);
        struct Cell *ia, *ib, *ic;
        ia = modedcellat(m, m->ip + 1, mode(i0->bigdata, 1));
        ib = modedcellat(m, m->ip + 2, mode(i0->bigdata, 2));
        ic = modedcellat(m, m->ip + 3, mode(i0->bigdata, 3));
        int intopcode = mpz_get_si(i0->bigdata);
        int opcode = baseopcode(intopcode);
        if (intopcode < 0) quit("invalid opcode");

        int kk;
        mpz_t tmp;
        mpz_init(tmp);
        switch (opcode) {
            default: quit("Something went wrong.\n");
                     break;
            case 1: //c = a + b
                    printcode(m, 4);
                    mpz_add(tmp, ia->bigdata, ib->bigdata);
                    mpz_set(ic->bigdata, tmp);
                    kk = 4;
                    break;
            case 2: //c = a * b
                    printcode(m, 4);
                    mpz_mul(tmp, ia->bigdata, ib->bigdata);
                    mpz_set(ic->bigdata, tmp);
                    kk = 4;
                    break;
            case 3: //a = <input>
                    printcode(m, 2);
                    if (m->status == 1) {
                        printf("Program stopped. Awaiting input...\n");
                        m->status = 2;
                        return;
                    }
                    m->status = 1;
                    mpz_set(ia->bigdata, m->bigsignal);
                    kk = 2;
                    break;
            case 4: //<output> a
                    printcode(m, 2);
                    mpz_set(m->bigsignal, ia->bigdata);
                    gmp_printf("==> signal %Z\n", ia->bigdata);
                    kk = 2;
                    break;
            case 5: //if (a != 0) <ip> = b
                    printcode(m, 3);
                    if (mpz_cmp_si(ia->bigdata, 0) != 0)
                          m->ip = mpz_get_si(ib->bigdata) - 3;
                    kk = 3;
                    break;
            case 6: //if (a == 0) <ip> = b
                    printcode(m, 3);
                    if (mpz_cmp_si(ia->bigdata, 0) == 0)
                          m->ip = mpz_get_si(ib->bigdata) - 3;
                    kk = 3;
                    break;
            case 7: //c = (a < b)
                    printcode(m, 4);
                    if (mpz_cmp(ia->bigdata, ib->bigdata) < 0) {
                        mpz_set_ui(ic->bigdata, 1);
                    } else {
                        mpz_set_ui(ic->bigdata, 0);
                    }
                    kk = 4;
                    break;
            case 8: //c = (a == b)
                    printcode(m, 4);
                    if (mpz_cmp(ia->bigdata, ib->bigdata) == 0) {
                        mpz_set_ui(ic->bigdata, 1);
                    } else {
                        mpz_set_ui(ic->bigdata, 0);
                    }
                    kk = 4;
                    break;
            case 9: //<relbase> = <relbase> + a
                    printcode(m, 2);
                    m->relbase += mpz_get_si(ia->bigdata);
                    kk = 2;
                    break;
            case 99: //halt
                     printcode(m, 1);
                     m->status = 3;
                     return;
                     break;
        }
        m->ip += kk;
    }
}

int main(int argc, char **argv) {
    (void)argc;                        // argc unused, avoid warning
    char buf[INPUTLENGTH];
    FILE *test = fopen(argv[1], "r");
    fgets(buf, sizeof buf, test);
    fclose(test);

    char *p = buf;
    struct VM vm[1] = {0};
    mpz_init(vm->bigsignal);
    for (;;) {
        // move from buf to vm
        if (vm->ncode == vm->mcode) {
            vm->mcode += 10;
            vm->code = realloc(vm->code, vm->mcode * sizeof *vm->code);
        }
        vm->code[vm->ncode].loc = vm->ncode;
        mpz_init(vm->code[vm->ncode].bigdata);
        int negative = (*p == '-');
        if (negative) p++;
        while (isdigit((unsigned char)*p)) {
            mpz_mul_ui(vm->code[vm->ncode].bigdata, vm->code[vm->ncode].bigdata, 10);
            mpz_add_ui(vm->code[vm->ncode].bigdata, vm->code[vm->ncode].bigdata, *p++ - '0');
        }
        if (negative) mpz_neg(vm->code[vm->ncode].bigdata, vm->code[vm->ncode].bigdata);
        vm->ncode++;
        if (*p == '\n') break;
        if (*p != ',') quit("bad input");
        p++;
    }

    execute(vm);
    if (vm->status == 2) {
        mpz_set_ui(vm->bigsignal, 1);
        printf("Program is waiting input ... sending signal 1\n");
        execute(vm);
    }
    gmp_printf("FINAL RESULT %Z\n", vm->bigsignal);
    // missing mpz_clear ...

    return 0;
}
