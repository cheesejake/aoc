#include <stdio.h>
#include <stdlib.h>

unsigned long long needed(char *box) {
    unsigned long l, w, h, top;
    // assume string is well-formatted
    l = strtoul(box, &box, 10); box++; // skip 'x'
    w = strtoul(box, &box, 10); box++; // skip 'x'
    h = strtoul(box, &box, 10);
    top = l;
    if (w > top) top = w;
    if (h > top) top = h;
    unsigned long long total = l + w + h - top;
    total *= 2;
    total += l * w * h;
    return total;
}

int main(void) {
    char buf[1000];
    unsigned long long total = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        total += needed(buf);
    }
    printf("order %llu feet of ribbon.\n", total);
    return 0;
}
