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
    int smalldata;
    mpz_t bigdata;
};

struct VM {
    struct Cell *code;
    int ncode;
    int mcode;
    int relbase;
    int ip;
    int status; // 0: reset, 1: running, 2:input, 3:stopped
    int smallsignal; // if 0 use bigsignal (which can be 0)
    mpz_t bigsignal;
};

void printcode(struct VM *m, int n, const char *msg) {
    printf("code ... %d (%s)", m->code[m->ip].smalldata, msg);
    if (n > 1) gmp_printf(" %Zd", m->code[m->ip + 1].bigdata);
    if (n > 2) gmp_printf(" %Zd", m->code[m->ip + 2].bigdata);
    if (n > 3) gmp_printf(" %Zd", m->code[m->ip + 3].bigdata);
    printf(" ...\n");
}

int baseopcode(unsigned opcode) {
    return (opcode) % 100;
}

int mode(int opcode, int n) {
    // opcode 1002
    //         ^ mode(opcode, 1)
    //        ^ mode(opcode, 2)
    //       ^ mode(opcode, 3) --- omitted, 0
    if (opcode < 0) quit("invalid opcode");
    if (n == 1) return (opcode / 100) % 10;
    if (n == 2) return (opcode / 1000) % 10;
    if (n == 3) return (opcode / 10000) % 10;
    if (n == 4) return (opcode / 100000) % 10;
    return 0;
}

struct Cell *cellat(struct VM *m, int address) {
    for (int k = 0; k < m->ncode; k++) {
        if (m->code[k].loc == address) {
            gmp_printf("cellat(..., %d) returns index %d (%Zd)\n", address, k, m->code[k].bigdata);
            return m->code + k;
        }
    }
    if (m->ncode == m->mcode) {
        m->mcode += 10;
        m->code = realloc(m->code, m->mcode * sizeof *m->code);
    }
    m->code[m->ncode].loc = address;
    m->code[m->ncode].smalldata = 0;
    mpz_init(m->code[m->ncode].bigdata);
    mpz_set_ui(m->code[m->ncode].bigdata, 0);
    printf("cellat(..., %d) created index %d (0)\n", address, m->ncode);
    return m->code + m->ncode++;
}

struct Cell *modedcellat(struct VM *m, int ip, int mode) {
    struct Cell *tmp1, *tmp2;
    int itmp;
    switch (mode) {
        default: quit("bad mode in opcode");
        case 0: // position mode
                tmp1 = cellat(m, ip);
                itmp = tmp1->smalldata;
                tmp2 = cellat(m, itmp);
                break;
        case 1: // immediate mode
                itmp = ip;
                tmp1 = tmp2 = cellat(m, ip);
                break;
        case 2: // relative mode
                tmp1 = cellat(m, ip);
                itmp = tmp1->smalldata;
                tmp2 = cellat(m, m->relbase + itmp);
                break;
    }
    if (!tmp2) {
        printf("Returning NULL from modedcellat(..., %d, %d)\n", ip, mode);
    }
    return tmp2;
}

void execute(struct VM *m) {
    for (;;) {
        struct Cell *i0 = cellat(m, m->ip);
        struct Cell *ia, *ib, *ic;
        int intopcode = i0->smalldata;
        int opcode = baseopcode(intopcode);
        if (intopcode < 0) quit("invalid opcode");

        int kk;
        switch (opcode) {
            default: quit("Something went wrong.\n");
                     break;
            case 1: //c = a + b
                    printcode(m, 4, "c = a + b");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    ib = modedcellat(m, m->ip + 2, mode(i0->smalldata, 2));
                    ic = modedcellat(m, m->ip + 3, mode(i0->smalldata, 3));
                    mpz_add(ic->bigdata, ia->bigdata, ib->bigdata);
                    ic->smalldata = mpz_get_si(ic->bigdata);
                    kk = 4;
                    break;
            case 2: //c = a * b
                    printcode(m, 4, "c = a * b");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    ib = modedcellat(m, m->ip + 2, mode(i0->smalldata, 2));
                    ic = modedcellat(m, m->ip + 3, mode(i0->smalldata, 3));
                    mpz_mul(ic->bigdata, ia->bigdata, ib->bigdata);
                    ic->smalldata = mpz_get_si(ic->bigdata);
                    kk = 4;
                    break;
            case 3: //a = <input>
                    if (m->status == 1) {
                        printcode(m, 2, "a = <input>");
                        printf("Program paused for input...\n");
                        m->status = 2;
                        return;
                    }
                    printcode(m, 2, "a = <input>");
                    m->status = 1;
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    if (m->smallsignal) {
                        mpz_set_si(ia->bigdata, m->smallsignal);
                        ia->smalldata = m->smallsignal;
                    } else {
                        mpz_set(ia->bigdata, m->bigsignal);
                        ia->smalldata = mpz_get_si(ia->bigdata);
                    }
                    kk = 2;
                    break;
            case 4: //<output> a
                    printcode(m, 2, "<output> a");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    mpz_set(m->bigsignal, ia->bigdata);
                    gmp_printf("==> signal %Zd\n", ia->bigdata);
                    kk = 2;
                    break;
            case 5: //if (a != 0) <ip> = b
                    printcode(m, 3, "if (a != 0) <ip> = b");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    ib = modedcellat(m, m->ip + 2, mode(i0->smalldata, 2));
                    if (mpz_cmp_si(ia->bigdata, 0) != 0)
                          m->ip = mpz_get_si(ib->bigdata) - 3;
                    kk = 3;
                    break;
            case 6: //if (a == 0) <ip> = b
                    printcode(m, 3, "if (a == 0) <ip> = b");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    ib = modedcellat(m, m->ip + 2, mode(i0->smalldata, 2));
                    if (mpz_cmp_si(ia->bigdata, 0) == 0)
                          m->ip = mpz_get_si(ib->bigdata) - 3;
                    kk = 3;
                    break;
            case 7: //c = (a < b)
                    printcode(m, 4, "c = (a < b)");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    ib = modedcellat(m, m->ip + 2, mode(i0->smalldata, 2));
                    ic = modedcellat(m, m->ip + 3, mode(i0->smalldata, 3));
                    if (mpz_cmp(ia->bigdata, ib->bigdata) < 0) {
                        mpz_set_ui(ic->bigdata, 1);
                        ic->smalldata = 1;
                    } else {
                        mpz_set_ui(ic->bigdata, 0);
                        ic->smalldata = 0;
                    }
                    kk = 4;
                    break;
            case 8: //c = (a == b)
                    printcode(m, 4, "c = (a == b)");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    ib = modedcellat(m, m->ip + 2, mode(i0->smalldata, 2));
                    ic = modedcellat(m, m->ip + 3, mode(i0->smalldata, 3));
                    if (mpz_cmp(ia->bigdata, ib->bigdata) == 0) {
                        mpz_set_ui(ic->bigdata, 1);
                        ic->smalldata = 1;
                    } else {
                        mpz_set_ui(ic->bigdata, 0);
                        ic->smalldata = 0;
                    }
                    kk = 4;
                    break;
            case 9: //<relbase> = <relbase> + a
                    printcode(m, 2, "<relbase> = <relbase> + a");
                    ia = modedcellat(m, m->ip + 1, mode(i0->smalldata, 1));
                    m->relbase += mpz_get_si(ia->bigdata);
                    kk = 2;
                    break;
            case 99: //halt
                     printcode(m, 1, "halt");
                     m->status = 3;
                     return;
                     break;
        }
        m->ip += kk;
    }
}

void input2vm(struct VM *m, const char *input) {
    const char *p = input;
    for (;;) {
        // move from input to m
        if (m->ncode == m->mcode) {
            m->mcode += 100;
            struct Cell *tmp;
            tmp = realloc(m->code, m->mcode * sizeof *m->code);
            if (!tmp) quit("realloc failed");
            m->code = tmp;
        }
        m->code[m->ncode].loc = m->ncode;
        m->code[m->ncode].smalldata = 0;
        mpz_init(m->code[m->ncode].bigdata);
        int negative = (*p == '-');
        if (negative) p++;
        while (isdigit((unsigned char)*p)) {
            m->code[m->ncode].smalldata *= 10;
            m->code[m->ncode].smalldata += *p - '0';
            mpz_mul_ui(m->code[m->ncode].bigdata, m->code[m->ncode].bigdata, 10);
            mpz_add_ui(m->code[m->ncode].bigdata, m->code[m->ncode].bigdata, *p - '0');
            p++;
        }
        if (negative) mpz_neg(m->code[m->ncode].bigdata, m->code[m->ncode].bigdata);
        if (negative) m->code[m->ncode].smalldata *= -1;
        m->ncode++;
        if (*p == '\n') break;
        if (*p != ',') quit("bad input");
        p++;
    }
}

int main(int argc, char **argv) {
    (void)argc;                        // argc unused, avoid warning
    struct VM vm[1] = {0};
    mpz_init(vm->bigsignal);

    char buf[INPUTLENGTH];
    FILE *test = fopen(argv[1], "r");
    fgets(buf, sizeof buf, test);
    fclose(test);
    input2vm(vm, buf);

    vm->status = 1;
    execute(vm);
    while (vm->status == 2) {
        printf("Program is waiting input ... sending signal 1\n");
        vm->smallsignal = 1;
        //vm->smallsignal = 0; mpz_set_ui(vm->bigsignal, 1);
        execute(vm);
    }
    gmp_printf("FINAL RESULT %Zd (%d)\n", vm->bigsignal, vm->smallsignal);

    // clean up
    for (int k = 0; k < vm->ncode; k++) {
        mpz_clear(vm->code[k].bigdata);
    }
    mpz_clear(vm->bigsignal);

    return 0;
}
