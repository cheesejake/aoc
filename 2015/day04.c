#include <openssl/md5.h> // gcc ... -lcrypto
#include <stdio.h>
#include <string.h>

int part1(const char *key) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    int n = 1;
    for (;;) {
        union { unsigned char u[1000]; char s[1000]; } password;
        int len = sprintf(password.s, "%s%d", key, n);
        MD5(password.u, len, hash);
        if ((hash[0] == 0) && (hash[1] == 0) && (hash[2] < 16)) break;
        n++;
    }
    return n;
}

int part2(const char *key) {
    unsigned char hash[MD5_DIGEST_LENGTH];
    int n = 1;
    for (;;) {
        union { unsigned char u[1000]; char s[1000]; }  password;
        int len = sprintf(password.s, "%s%d", key, n);
        MD5(password.u, len, hash);
        if ((hash[0] == 0) && (hash[1] == 0) && (hash[2] == 0)) break;
        n++;
    }
    return n;
}

int main(void) {
    char key[100];
    fgets(key, 100, stdin);
    key[strlen(key) - 1] = 0;
    printf("DAY04-PART1: %d\n", part1(key));
    printf("DAY04-PART2: %d\n", part2(key));
    return 0;
}
