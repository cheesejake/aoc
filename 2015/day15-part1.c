#include <stdio.h>

/*
 * Sprinkles: capacity 2, durability 0, flavor -2, texture 0, calories 3
 * Butterscotch: capacity 0, durability 5, flavor -3, texture 0, calories 3
 * Chocolate: capacity 0, durability 0, flavor 5, texture -1, calories 8
 * Candy: capacity 0, durability -1, flavor 0, texture 5, calories 8
 */

struct Properties {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

long long calcscore(struct Properties *p, int a, int b, int c, int d) {
    long long tca = a*p[0].capacity + b*p[1].capacity + c*p[2].capacity + d*p[3].capacity;
    long long tdu = a*p[0].durability + b*p[1].durability + c*p[2].durability + d*p[3].durability;
    long long tfl = a*p[0].flavor + b*p[1].flavor + c*p[2].flavor + d*p[3].flavor;
    long long tte = a*p[0].texture + b*p[1].texture + c*p[2].texture + d*p[3].texture;
    long long result = (tca>0?tca:0) * (tdu>0?tdu:0) * (tfl>0?tfl:0) * (tte>0?tte:0);
    return result;
}

int main(void) {
    struct Properties ing[4] = {{2, 0, -2, 0, 3},
                                {0, 5, -3, 0, 3},
                                {0, 0, 5, -1, 8},
                                {0, -1, 0, 5, 8}};
    int teaspoons[4] = {100};
    long long maxscore = -1;
    for (int sp = 0; sp <= 100; sp++) {
        for (int bu = 0; bu <= 100; bu++) {
            for (int ch = 0; ch <= 100; ch++) {
                if (sp + bu + ch <= 100) {
                    int ca = 100 - sp - bu - ch;
                    long long score = calcscore(ing, sp, bu, ch, ca);
                    if (score > maxscore) {
                        maxscore = score;
                        printf("Obtained score of %lld with %d, %d, %d, and %d.\n",
                              maxscore, sp, bu, ch, ca);
                    }
                }
            }
        }
    }
}
