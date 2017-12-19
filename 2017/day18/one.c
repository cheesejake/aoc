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
    long long int r[256] = {0};
    /* const */ r['1'] = 1;
    /* const */ r['2'] = 2;
    /* const */ r['3'] = 3;
    /* const */ r['4'] = 4;
    /* const */ r['5'] = 5;
    /* const */ r['6'] = 6;
    /* const */ r['7'] = 7;
    /* const */ r['8'] = 8;
    /* const */ r['9'] = 9;
    struct Code c[1] = {0};
    int sndvalue;
    int letter1, letter2;
    long long int value1 = 0;
    long long int value2 = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        strncpy(c->instruction[c->ninstructions++], buf, strlen(buf) - 1);
    }
    int k = 0;
    for (;;) {
        letter1 = c->instruction[k][4];
        letter2 = c->instruction[k][6];
        if (isdigit((unsigned char)letter1)) {
            value1 = strtol(c->instruction[k] + 4, NULL, 10);
        } else {
            value1 = r[letter1];
        }
        if (isdigit((unsigned char)letter2) || (letter2 == '-')) {
            value2 = strtol(c->instruction[k] + 6, NULL, 10);
        } else {
            value2 = r[letter2];
        }
        switch (c->instruction[k][0]) {
            default: fprintf(stderr, "impossible instruction; %s", c->instruction[k]);
                     exit(EXIT_FAILURE);
                     break;
            case 'a': /* add */
                     r[letter1] += value2;
                     break;
            case 'j': /* jgz */
                     if (value1 > 0) {
                         k += value2 - 1;
                     }
                     break;
            case 'm': /* mod, mul */
                     if (c->instruction[k][1] == 'o') {
                         r[letter1] %= value2;
                     } else {
                         r[letter1] *= value2;
                     }
                     break;
            case 'r': /* rcv */
                     if (r[letter1] != 0) {
                         printf("Last frequency played was %d.\n", sndvalue);
                         exit(EXIT_SUCCESS);
                     }
                     break;
            case 's': /* set, snd */
                     if (c->instruction[k][1] == 'e') {
                         r[letter1] = value2;
                     } else {
                         sndvalue = r[letter1];
                     }
                     break;
        }
        k++;
        if ((k < 0) || (k >= c->ninstructions)) {
            printf("Program terminatted abruptly.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("value is %d.\n", sndvalue);
    return 0;
}
