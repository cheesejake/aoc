#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MemCell {
    long long unsigned index;
    long long unsigned value;
};

struct Memory {
    struct MemCell *data;
    unsigned reserved;
    unsigned used;
};

void domask(const char *p, long long unsigned *o, long long unsigned *a) {
    *o = 0;
    *a = 0;
    for (int k = 0; p[k] && (p[k] != '\n'); k++) {
        *o <<= 1;
        *a <<= 1;
             if (p[k] == '0') { *o += 0; *a += 0; }
        else if (p[k] == '1') { *o += 1; *a += 1; }
        else if (p[k] == 'X') { *o += 0; *a += 1; }
        else fprintf(stderr, "invalid mask value in '%s'\n", p);
    }
}

struct MemCell *findmem(struct Memory *m, long long unsigned v) {
    for (unsigned k = 0; k < m->used; k++) {
        if (m->data[k].index == v) return m->data + k;
    }
    return 0;
}

struct MemCell *addcell(struct Memory *m, long long unsigned v) {
    if (m->used == m->reserved) {
        unsigned newsize = m->reserved * 2 + 2;
        void *tmp = realloc(m->data, newsize * sizeof *m->data);
        if (!tmp) {
            fprintf(stderr, "no memory\n");
            exit(EXIT_FAILURE);
        }
        m->data = tmp;
        m->reserved = newsize;
    }
    m->data[m->used++].index = v;
    return m->data + m->used - 1;
}

void domem(struct Memory *mem, const char *p,
           long long unsigned o, long long unsigned a) {
    long long unsigned p1, p2;
    if (sscanf(p, "mem[%llu] = %llu", &p1, &p2) != 2) {
        fprintf(stderr, "bad input\n");
    }
    struct MemCell *index = findmem(mem, p1);
    if (index == NULL) {
        index = addcell(mem, p1);
    }
    index->value = (p2 & a) | o;
}

long long unsigned p1(const char *f) {
    struct Memory mem[1] = {0};
    long long unsigned mask_or = 0, mask_and = 0xfffffffffULL;
    FILE *fid = fopen(f, "r");
    char buf[100];
    while (fgets(buf, sizeof buf, fid)) {
        if (buf[1] == 'a') domask(buf + 7, &mask_or, &mask_and);
        else               domem(mem, buf, mask_or, mask_and);
    }
    fclose(fid);
    long long unsigned t = 0;
    for (unsigned k = 0; k < mem->used; k++) {
        t += mem->data[k].value;
    }
    free(mem->data);
    printf("used %llu/%llu cells\n", mem->used, mem->reserved);
    return t;
}

void do2mem(struct Memory *mem, long long unsigned a,
            long long unsigned v, const char *m, int len,
            long long unsigned amask, long long unsigned omask) {
    if (len == 36) {
        struct MemCell *index;
        long long unsigned aunmasked = (a & amask) | omask;
        index = findmem(mem, aunmasked);
        if (index == NULL) {
            index = addcell(mem, aunmasked);
        }
        index->value = v;
        //printf("a = %llu; v = %llu\n", a, v);
        //printf("m = '%s'\n", m);
        //printf("amask = 0x%llx; omask = 0x%llx\n", amask, omask);
    } else {
        if (m[len] == '0') do2mem(mem, a, v, m, len+1, 2*amask+1, 2*omask+0);
        if (m[len] == '1') do2mem(mem, a, v, m, len+1, 2*amask+1, 2*omask+1);
        if (m[len] == 'X') {
            do2mem(mem, a, v, m, len+1, 2*amask+0, 2*omask+0);
            do2mem(mem, a, v, m, len+1, 2*amask+1, 2*omask+1);
        }
    }
}

long long unsigned p2(const char *f) {
    struct Memory mem[1] = {0};
    char mask[37];
    FILE *fid = fopen(f, "r");
    char buf[100];
    while (fgets(buf, sizeof buf, fid)) {
        if (buf[1] == 'a') {
            sprintf(mask, "%.36s", buf + 7);
        } else {
            long long unsigned p1, p2;
            sscanf(buf, "mem[%llu] = %llu", &p1, &p2);
            do2mem(mem, p1, p2, mask, 0, 0, 0);
        }
    }
    fclose(fid);
    long long unsigned t = 0;
    for (unsigned k = 0; k < mem->used; k++) {
        t += mem->data[k].value;
    }
    free(mem->data);
    printf("used %llu/%llu cells\n", mem->used, mem->reserved);
    return t;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "syntax: ./a.out <inputfilename>\n");
        exit(EXIT_FAILURE);
    }
    printf("day 14, part 1: %llu\n", p1(argv[1]));
    printf("day 14, part 2: %llu\n", p2(argv[1]));
    return 0;
}
