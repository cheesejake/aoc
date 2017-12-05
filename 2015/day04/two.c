#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    char key[100];
    fgets(key, sizeof key, stdin);
    key[strlen(key) - 1] = 0;

    int n = 1;
    for (;;) {
        union { unsigned char u[1000]; char s[1000]; }  password;
        int len = sprintf(password.s, "%s%d", key, n);
        MD5(password.u, len, hash);
        if ((hash[0] == 0) && (hash[1] == 0) && (hash[2] == 0)) break;
        n++;
    }
    printf("%d\n", n);
    return 0;
}
