#include <stdio.h>

int main(void) {
    unsigned a = 0x111000;
    unsigned b = 0x001110;
    printf(" a << 1 + b : 0x%x\n", a<<1+b);
    printf("(a << 1)+ b : 0x%x\n", (a<<1)+b);
    printf(" a <<(1 + b): 0x%x\n", a<<(1+b));
    return 0;
}
