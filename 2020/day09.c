#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("syntax: ./a.out <input file>\n");
        exit(EXIT_FAILURE);
    }
    char buf[40];
    long long unsigned input[1100] = {0};
    int n = 0;
    FILE *fid = fopen(argv[1], "r");
    while (fgets(buf, sizeof buf, fid)) {
        buf[strcspn(buf, "\n")] = 0;
        input[n++] = strtoull(buf, 0, 10);
    }
    fclose(fid);

    for (int k = 25; k < n; k++) {
        int lo, hi;
        for (lo = k -25; lo < k - 1; lo++)
        for (hi = lo+1; hi < k; hi++) {
            if (input[lo] + input[hi] == input[k]) { hi = lo = 10000; }
        }
        if (lo < n) printf("Part1: %llu\n", input[k]);
    }

    long long unsigned search = 1721308972; // solution from my input
    int sumlo = 0, sumhi = 0;
    long long unsigned total = input[0];
    while (total != search) {
        if (total < search) {
            total += input[++sumhi];
        } else {
            total -= input[sumlo++];
        }
    }
    long long unsigned minx = input[sumlo];
    long long unsigned maxx = input[sumlo];
    for (int k = sumlo; k <= sumhi; k++) {
        if (input[k] < minx) minx = input[k];
        if (input[k] > maxx) maxx = input[k];
    }
    printf("Part2: %llu\n", minx + maxx);
    return 0;
}
