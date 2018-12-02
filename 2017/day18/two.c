#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Code {
    char instruction[1000][100];
    int ninstructions;
};

int main(void) {
    char buf[100];
    long long int r[2][256] = {0};
    /* const */ r[0]['1'] = r[1]['1'] = 1;
    /* const */ r[0]['2'] = r[1]['2'] = 2;
    /* const */ r[0]['3'] = r[1]['3'] = 3;
    /* const */ r[0]['4'] = r[1]['4'] = 4;
    /* const */ r[0]['5'] = r[1]['5'] = 5;
    /* const */ r[0]['6'] = r[1]['6'] = 6;
    /* const */ r[0]['7'] = r[1]['7'] = 7;
    /* const */ r[0]['8'] = r[1]['8'] = 8;
    /* const */ r[0]['9'] = r[1]['9'] = 9;
    r[0]['p'] = 0;
    r[1]['p'] = 1;
    struct Code c[1] = {0};
    int sendvalue;
    int letter1, letter2;
    long long int value1 = 0;
    long long int value2 = 0;
    long long int total = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        strncpy(c->instruction[c->ninstructions++], buf, strlen(buf) - 1);
    }
    int k[2] = {0};
    int changeprogram;
    int currentprogram = 0;
    int status[2] = {0, 1}; // 0: running; 1: waiting; 2: terminated
    for (;;) {
        changeprogram = 0;
        letter1 = c->instruction[k[currentprogram]][4];
        letter2 = c->instruction[k[currentprogram]][6];
        if (isdigit((unsigned char)letter1)) {
            value1 = strtol(c->instruction[k[currentprogram]] + 4, NULL, 10);
        } else {
            value1 = r[currentprogram][letter1];
        }
        if (isdigit((unsigned char)letter2) || (letter2 == '-')) {
            value2 = strtol(c->instruction[k[currentprogram]] + 6, NULL, 10);
        } else {
            value2 = r[currentprogram][letter2];
        }
        switch (c->instruction[k[currentprogram]][0]) {
            default: fprintf(stderr, "impossible instruction; %s", c->instruction[k[currentprogram]]);
                     exit(EXIT_FAILURE);
                     break;
            case 'a': /* add */
                     r[currentprogram][letter1] += value2;
                     break;
            case 'j': /* jgz */
                     if (value1 > 0) {
                         k[currentprogram] += value2 - 1;
                     }
                     break;
            case 'm': /* mod, mul */
                     if (c->instruction[k[currentprogram]][1] == 'o') {
                         r[currentprogram][letter1] %= value2;
                     } else {
                         r[currentprogram][letter1] *= value2;
                     }
                     break;
            case 'r': /* rcv */
                     r[currentprogram][letter1] = sendvalue;
                     break;
            case 's': /* set, snd */
                     if (c->instruction[k[currentprogram]][1] == 'e') {
                         r[currentprogram][letter1] = value2;
                     } else {
                         sendvalue = value1;
                         if (currentprogram == 1) total++;
                         changeprogram = 1;
                     }
                     break;
        }
        k[currentprogram]++;
        if ((k[currentprogram] < 0) || (k[currentprogram] >= c->ninstructions)) {
            status[currentprogram] = 2;
            changeprogram = 1;
        }
        if (changeprogram) {
            if (status[currentprogram] == 0) status[currentprogram] = 1;
            currentprogram = 1 - currentprogram;
            if (status[currentprogram] == 1) status[currentprogram] = 0;
            else break;
        }
    }
    printf("Total: %lld\n", total);
    return 0;
}
