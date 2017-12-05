#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *list;
    int nlist, mlist;
    int n;

    nlist = 0;
    mlist = 86;
    list = malloc(mlist * sizeof *list); // assume OK
    while (scanf("%d", &n) == 1) {
        if (nlist == mlist) {
            // grow array
            mlist *= 2;
            int *tmp = realloc(list, mlist * sizeof *tmp);
            if (!tmp) {
                fprintf(stderr, "Not enough memory. Program aborted.\n");
                exit(EXIT_FAILURE);
            }
            list = tmp;
        }
        list[nlist++] = n;
    }
    int pos = 0;
    int steps = 0;
    while ((pos >= 0) && (pos < nlist)) {
        int jump = list[pos];
        if (jump >= 3) list[pos] -= 1;
        else           list[pos] += 1;
        pos += jump;
        steps += 1;
    }
    free(list);
    printf("The exit is reached in %d steps.\n", steps);
    return 0;
}
