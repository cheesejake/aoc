#include <stdio.h>

int main(void) {
    int ch, floor = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '(') floor++;
        if (ch == ')') floor--;
    }
    printf("Santa goes to floor %d.\n", floor);
    return 0;
}
