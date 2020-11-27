#include <stdio.h>

int main(void) {
    int ch, floor = 0;
    int kk = 0, k = 0;
    while ((ch = getchar()) != EOF) {
        k++;
        if (ch == '(') floor++;
        if (ch == ')') floor--;
        if (floor < 0) { kk = k; break; }
    }
    if (kk) printf("Santa first enters the basement at position %d.\n", kk);
    else printf("Santa never enters the basement.\n");
    return 0;
}
