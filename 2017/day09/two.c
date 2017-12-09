#include <stdio.h>

int trash(const char *src) {
    int garbage = 0;
    int k = 0;
    while (*src) {
        if (!garbage) {
            if (*src == '<') garbage = 1;
        } else {
            if (*src == '>') {
                garbage = 0;
            } else {
                if (*src == '!') src++;
                else k++;
            }
        }
        src++;
    }
    return k;
}

int main(void) {
    char buf[20000];
    while (fgets(buf, sizeof buf, stdin)) {
        printf("stream trash is %d.\n", trash(buf));
    }
    return 0;
}
