#include <stdio.h>
#include <stdlib.h>

struct threed {
    long long int x;
    long long int y;
    long long int z;
};

struct Particle {
    struct threed pos;
    struct threed speed;
    struct threed accel;
    long long unsigned zdist;
    int deleted;
};

int readparticle(struct Particle *pp) {
    char buf[1000];
    if (!fgets(buf, sizeof buf, stdin)) return 0;
    char *p = buf;
    p += 3; //skip 'p=<'
    pp->pos.x = strtoll(p, &p, 10);
    p += 1; // skip ','
    pp->pos.y = strtoll(p, &p, 10);
    p += 1; // skip ','
    pp->pos.z = strtoll(p, &p, 10);
    p += 6; // skip '>, v=<'
    pp->speed.x = strtoll(p, &p, 10);
    p += 1; // skip ','
    pp->speed.y = strtoll(p, &p, 10);
    p += 1; // skip ','
    pp->speed.z = strtoll(p, &p, 10);
    p += 6; // skip '>, a=<'
    pp->accel.x = strtoll(p, &p, 10);
    p += 1; // skip ','
    pp->accel.y = strtoll(p, &p, 10);
    p += 1; // skip ','
    pp->accel.z = strtoll(p, &p, 10);
    return 1;
}

void moveparticles(struct Particle *p, int n) {
    for (int k = 0; k < n; k++) {
        if (!p[k].deleted) {
            p[k].speed.x += p[k].accel.x;
            p[k].speed.y += p[k].accel.y;
            p[k].speed.z += p[k].accel.z;
            p[k].pos.x += p[k].speed.x;
            p[k].pos.y += p[k].speed.y;
            p[k].pos.z += p[k].speed.z;
            p[k].zdist = abs(p[k].pos.x) + abs(p[k].pos.y) + abs(p[k].pos.z);
        }
    }
}

int destroycollisions(struct Particle *p, int nparticles) {
    for (int k = 0; k < nparticles; k++) {
        if (p[k].deleted == 1) continue;
        for (int j = k + 1; j < nparticles; j++) {
            if (p[j].deleted == 1) continue;
            if (p[k].zdist == p[j].zdist) {
                if (p[k].pos.x == p[j].pos.x) {
                    if (p[k].pos.y == p[j].pos.y) {
                        if (p[k].pos.z == p[j].pos.z) {
                            p[k].deleted = p[j].deleted = 2;
                        }
                    }
                }
            }
        }
    }
    int n = 0;
    for (int k = 0; k < nparticles; k++) {
        if (p[k].deleted == 2) {
            p[k].deleted = 1;
            n++;
        }
    }
    return n;
}

int main(void) {
    struct Particle p[1100] = {0};
    int nparticles = 0;
    int liveparticles = 0;
    while (readparticle(p + nparticles)) { nparticles++; }
    liveparticles = nparticles;
    liveparticles -= destroycollisions(p, nparticles);
    //printf("read %d particles.\n", nparticles);
    long long unsigned k = 0;
    for (;;) {
        k++;
        moveparticles(p, nparticles);
        liveparticles -= destroycollisions(p, nparticles);
        if (k % 1000 == 0) {
            printf("live particle at %llu is %d.\n", k, liveparticles);
        }
    }
    return 0;
}
