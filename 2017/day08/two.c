#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long maxever = LONG_MIN;

struct Register {
    char name[100];
    long value;
};

struct Stack {
    struct Register *data;
    int n;
};

void printstack(struct Stack *data) {
    printf("Stack:\n");
    for (int k = 0; k < data->n; k++) {
        printf("%03d: %s ==> %ld\n", k, data->data[k].name, data->data[k].value);
    }
}

struct Register *findreg(struct Stack *data, char *t) {
    for (int k = 0; k < data->n; k++) {
        if (strcmp(data->data[k].name, t) == 0) return data->data + k;
    }
    return NULL;
}

struct Register *crtreg(struct Stack *data, char *t) {
    struct Register *tmp = realloc(data->data, (data->n + 1) * sizeof *tmp);
    data->data = tmp;
    strcpy(data->data[data->n].name, t);
    data->data[data->n].value = 0;
    data->n += 1;
    return data->data + (data->n - 1);
}

void instruction(struct Stack *data,
                 char *dst, int op, int v,
                 char *src, int cond, int vv) {
    struct Register *wr, *rr;
    if ((wr = findreg(data, dst)) == NULL) wr = crtreg(data, dst);
    if ((rr = findreg(data, src)) == NULL) rr = crtreg(data, src);
    switch (cond) {
        default: fprintf(stderr, "Impossible error @ line %d.\n", __LINE__);
                 exit(EXIT_FAILURE);
                 break;
        case 0: if (rr->value > vv) wr->value += v * op;
                break;
        case 1: if (rr->value < vv) wr->value += v * op;
                break;
        case 2: if (rr->value >= vv) wr->value += v * op;
                break;
        case 3: if (rr->value == vv) wr->value += v * op;
                break;
        case 4: if (rr->value <= vv) wr->value += v * op;
                break;
        case 5: if (rr->value != vv) wr->value += v * op;
                break;
    }
    if (wr->value > maxever) maxever = wr->value;
}

int main(void) {
    struct Stack s[1] = {0};
    char buf[1000];
    while (fgets(buf, sizeof buf, stdin)) {         /* dstr inc 5 if srcr > 1 */
        char *src = buf;
        char *dst;
        char dstr[100] = "";
        char srcr[100] = "";
        long sumvalue, cmpvalue;
        int condition;
        int op = 1; /* inc; for dec, op will be -1 */

        dst = dstr;
        while (*src != ' ') *dst++ = *src++;
        if (src[1] == 'd') op = -1;
        src += 5; // skip " inc " or " dec "
        sumvalue = strtol(src, &src, 10);
        src += 4; // skip " if "
        dst = srcr;
        while (*src != ' ') *dst++ = *src++;
        if (strncmp(src, " > ", 3) == 0) condition = 0;
        if (strncmp(src, " < ", 3) == 0) condition = 1;
        if (strncmp(src, " >= ", 4) == 0) condition = 2;
        if (strncmp(src, " == ", 4) == 0) condition = 3;
        if (strncmp(src, " <= ", 4) == 0) condition = 4;
        if (strncmp(src, " != ", 4) == 0) condition = 5;
        while (*++src != ' ') /* void */; /* skip whitespace and comparison */
        cmpvalue = strtol(src, &src, 10);

        //printf("instruction: %s", buf);
        instruction(s, dstr, op, sumvalue, srcr, condition, cmpvalue);
        //printstack(s);
    }

    long max = s->data[0].value;
    for (int k = 1; k < s->n; k++) if (s->data[k].value > max) max = s->data[k].value;
    printf("The largest value ever was %ld.\n", maxever);
    return 0;
}
