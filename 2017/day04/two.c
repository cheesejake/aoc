#include <stdio.h>
#include <string.h>

void reorder(char *p) {
    int plen = strlen(p);
    for (int k = 0; k < plen; k++) {
        for (int j = k + 1; j < plen; j++) {
            if (p[k] > p[j]) {
                char tmp = p[k];
                p[k] = p[j];
                p[j] = tmp;
            }
        }
    }
}

int validpass(char *pass) {
    char words[100][100];
    int nwords = 0;
    // assume well-formed input
    char *p = strtok(pass, " ");
    reorder(p);
    strcpy(words[nwords++], p);
    while ((p = strtok(NULL, " \n")) != NULL) {
        reorder(p);
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
