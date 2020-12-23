#include <stdio.h>
#include <string.h>

void picknextthree(char *dst, char *src) {
    memcpy(dst, src + 1, 3);
    memmove(src + 1, src + 4, 5);
    src[6] = 0;
}

int destination(const char *circle) {
    int d = circle[0] - 1;
    if (d < '1') d = '9';
    while (strchr(circle, d) == NULL) {
        d -= 1;
        if (d < '1') d = '9';
    }
    int dindex = 1;
    while (circle[dindex] != d) dindex++;
    return dindex;
}

void placecups(char *circle, const char *three, int dindex) {
    memmove(circle + dindex + 4, circle + dindex + 1, 5 - dindex);
    memcpy(circle + dindex + 1, three, 3);
}

void rotate(char *circle) {
    int tmp = circle[0];
    memmove(circle, circle + 1, 8);
    circle[8] = tmp;
}

void crabmove(char *circle) {
    char next[4] = {0};
    picknextthree(next, circle);
    int dindex = destination(circle);
    placecups(circle, next, dindex);
    rotate(circle);
}

int main(void) {
    //char circle[] = "389125467"; // test data
    char circle[] = "952316487"; // puzzle data
    printf("initial labeling: %s\n", circle);
    for (int k = 0; k < 10; k++) {
        crabmove(circle);
    }
    printf("current labeling after 10 moves: %s\n", circle);
    for (int k = 10; k < 100; k++) {
        crabmove(circle);
    }
    printf("current labeling (after 100 total moves): %s\n", circle);
}
