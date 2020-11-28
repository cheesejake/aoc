#include <stdio.h>
#include <stdlib.h>

unsigned long long wneeded(char *box) {
    unsigned long l, w, h, top;
    // assume string is well-formatted, no overflows
    l = strtoul(box, &box, 10); box++; // skip 'x'
    w = strtoul(box, &box, 10); box++; // skip 'x'
    h = strtoul(box, &box, 10);
    top = l;
    if (w > top) top = w;
    if (h > top) top = h;
    unsigned long long total = l * w * h / top;
    total += 2 * l * w;
    total += 2 * l * h;
    total += 2 * w * h;
    return total;
}

unsigned long long part1(char (*data)[40], unsigned n) {
    unsigned long long total = 0;
    for (unsigned k = 0; k < n; k++) {
        total += wneeded(data[k]);
    }
    return total;
}

unsigned long long rneeded(char *box) {
    unsigned long l, w, h, top;
    // assume string is well-formatted, no overflows
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

unsigned long long part2(char (*data)[40], unsigned n) {
    unsigned long long total = 0;
    for (unsigned k = 0; k < n; k++) {
        total += rneeded(data[k]);
    }
    return total;
}

int main(void) {
    char data[2000][40];
    unsigned ndata = 0;
    while (fgets(data[ndata], 40, stdin)) {
        ndata++;
    }
    printf("DAY02-PART1: order %llu square feet of wrapping paper.\n", part1(data, ndata));
    printf("DAY02-PART2: order %llu feet of ribbon.\n", part2(data, ndata));
}
