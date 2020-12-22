#include <stdio.h>
#include <stdlib.h>

struct Hand {
    int vals[100];
    int first;
    int next;
};

void addcard(struct Hand *h, int val) {
    h->vals[h->next % 100] = val;
    h->next++;
}

int removecard(struct Hand *h) {
    int ret = h->vals[h->first % 100];
    h->first += 1;
    return ret;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        FILE *f = fopen(argv[1], "r");
        struct Hand p[2] = {0};
        struct Hand *destin = p;
        char buf[100];
        while (fgets(buf, sizeof buf, f)) {
            if (*buf == '\n') { destin = p + 1; continue; }
            if (*buf == 'P') continue;
            int val = strtol(buf, 0, 10); // assume ok
            addcard(destin, val);
        }
        fclose(f);
        while ((p[0].first != p[0].next) && (p[1].first != p[1].next)) {
           int v0 = removecard(p + 0);
           int v1 = removecard(p + 1);
           if (v0 > v1) {
               addcard(p + 0, v0);
               addcard(p + 0, v1);
           } else {
               addcard(p + 1, v1);
               addcard(p + 1, v0);
           }
        }
        printf("game over\n");
        if (p[0].first == p[0].next) {
            printf("Player 2 won\n");
            destin = p + 1;
        } else {
            printf("Player 1 won\n");
            destin = p;
        }
        long long unsigned ncards = ((destin->next + 100) - destin->first) % 100;
        long long unsigned score = 0;
        while (ncards) {
            int v = removecard(destin);
            score += ncards * v;
            ncards--;
        }
        printf("Final score: %llu\n", score);
    } else {
        printf("syntax: ./a.out <filename>\n");
    }
    return 0;
}
