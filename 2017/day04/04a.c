#include <stdio.h>
#include <string.h>

int validpass(char *pass) {
    char words[100][100];
    int nwords = 0;
    // assume well-formed input
    char *p = strtok(pass, " ");
    strcpy(words[nwords++], p);
    while ((p = strtok(NULL, " \n")) != NULL) {
        for (int k = 0; k < nwords; k++) {
            if (strcmp(p, words[k]) == 0) return 0;
        }
        strcpy(words[nwords++], p);
    }
    return 1;
}

int main(void) {
    char buf[1000];
    int total = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        total += validpass(buf);
    }
    printf("There are %d valid passphrases.\n", total);
    return 0;
}
