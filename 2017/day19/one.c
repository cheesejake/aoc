#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cango(int x) {
    if (x == ' ') return 0;
    if (x == 0) return 0;
    return 1;
}

int main(void) {
    char diagram[250][250] = {0};
    int rows = 1;
    int cols = 1;
    char buf[250] = {0};
    while (fgets(buf, sizeof buf, stdin)) {
        int tmp = strlen(buf);
        buf[tmp - 1] = 0;
        if (tmp > cols) cols = tmp;
        strcpy(diagram[rows++] + 1, buf);
        memset(buf, 0, sizeof buf);
    }
    int currow = 1, curcol = 1;
    while (diagram[currow][curcol] != '|') curcol++;
    int direction = 2; // 0=UP; 1=LEFT; 2=DOWN; 3=RIGHT
    for (;;) {
        switch (direction) {
            default: fprintf(stderr, "impossible direction. program aborted.\n");
                     exit(EXIT_FAILURE);
                     break;
            case 0: currow--; break;
            case 1: curcol--; break;
            case 2: currow++; break;
            case 3: curcol++; break;
        }
        if (!cango(diagram[currow][curcol])) {
                printf("\n\nFinished\n");
                exit(EXIT_SUCCESS);
            }
        if (isalpha((unsigned char)diagram[currow][curcol])) {
            printf("%c", diagram[currow][curcol]);
            fflush(stdout);
            continue;
        }
        if (diagram[currow][curcol] == '+') {
            int olddirection = direction - 2;
            if (olddirection < 0) olddirection += 4;
            int newdirection1 = -1;
            int newdirection2 = -1;
            if (cango(diagram[currow - 1][curcol])) newdirection1 = 0;
            if (cango(diagram[currow + 1][curcol])) newdirection1 = 2;
            if (cango(diagram[currow][curcol - 1])) newdirection1 = 1;
            if (cango(diagram[currow][curcol + 1])) newdirection1 = 3;
            if (cango(diagram[currow][curcol + 1])) newdirection2 = 3;
            if (cango(diagram[currow][curcol - 1])) newdirection2 = 1;
            if (cango(diagram[currow + 1][curcol])) newdirection2 = 2;
            if (cango(diagram[currow - 1][curcol])) newdirection2 = 0;
            if (newdirection1 == newdirection2) {
                printf("\n\nDone\n");
                exit(EXIT_SUCCESS);
            }
            if (olddirection == newdirection1) {
                direction = newdirection2;
            } else {
                direction = newdirection1;
            }
        }
    }
    return 0;
}
