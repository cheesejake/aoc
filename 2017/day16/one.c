#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dance(char *line, int maxlen, char *moves) {
    char *p = moves;
    int len;
    int p1, p2;
    char tmpp;
    char tmp1, tmp2;
    char *pp1, *pp2;
    while (*p) {
        switch (*p++) {
            default: printf("impossible move in input. program aborted.\n");
                     printf("move is %c (%d)\n", p[-1], p[-1]);
                     printf("next few moves are: %.50s\n", p);
                     exit(EXIT_FAILURE);
                     break;
            case 's': len = strtol(p, &p, 10);
                      p++; // skip comma
                      char tmpline[1000];
                      sprintf(tmpline, "%s%.*s", line + maxlen - len, maxlen - len, line);
                      strcpy(line, tmpline);
                      break;
            case 'x': p1 = strtol(p, &p, 10);
                      p++; // skip /
                      p2 = strtol(p, &p, 10);
                      p++; // skip comma
                      tmpp = line[p1];
                      line[p1] = line[p2];
                      line[p2] = tmpp;
                      break;
            case 'p': tmp1 = *p++; p++;
                      tmp2 = *p++; p++;
                      pp1 = strchr(line, tmp1);
                      pp2 = strchr(line, tmp2);
                      tmpp = *pp1;
                      *pp1 = *pp2;
                      *pp2 = tmpp;
                      break;
        }
    }
}

int main(void) {
    //char line[] = "abcde";
    char line[] = "abcdefghijklmnop";
    char *buf = calloc(100000, 1);
    while (fgets(buf, 100000, stdin)) {
        buf[strlen(buf) - 1] = 0;
        dance(line, strlen(line), buf);
        memset(buf, 0, 100000);
    }
    free(buf);
    printf("final arrangement: %s.\n", line);
    return 0;
}
