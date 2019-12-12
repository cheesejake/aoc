#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quit(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void data2map(unsigned char *dst, char *src) {
    while (*src) {
        if (*src == '#') *dst = 1;
        src++;
        dst++;
    }
}

#define MAXINPUT 100                   // enough for my input

struct AsteroidMap {
    unsigned char *data; // not a string
    int mdata, ndata;
    int nrows, ncols;
};

void readdata(struct AsteroidMap *m) {
    char buf[MAXINPUT];
    for (;;) {
        if (!fgets(buf, sizeof buf, stdin)) break;
        int len = strspn(buf, "#.");
        if (m->ncols == 0) m->ncols = len;
        if (len != m->ncols) quit("data error");
        m->nrows++;
        m->data = realloc(m->data, m->nrows * m->ncols * sizeof *m->data);
        data2map(&m->data[(m->nrows - 1) * m->ncols], buf);
    }
}

int count(struct AsteroidMap *m, int x, int y) {
    (void)x; (void)y;
    unsigned char (*foo)[m->nrows][m->ncols] = (void*)m->data;
    for (int row = 0; row < m->nrows; row++) {
        for (int col = 0; col < m->ncols; col++) {
            if ((*foo)[row][col] == 1) putchar('#');
            else                       putchar(' ');
        }
        putchar('\n');
    }
    return 42;
}

int main(void) {
    struct AsteroidMap m[1] = {0};
    readdata(m);
    count(m, 0, 0);
    for (int row = 0; row < m->nrows; row++) {
        for (int col = 0; col < m->ncols; col++) {
//            printf("count at (%d, %d): %d\n", row, col, count(m, row, col));
        }
    }
}
