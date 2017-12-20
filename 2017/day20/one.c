#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct threed {
    int x;
    int y;
    int z;
};

struct Particle {
    int pid;
    struct threed pos;
    struct threed speed;
    struct threed accel;
};

int readparticle(struct Particle *pp) {
    char buf[1000];
    if (!fgets(buf, sizeof buf, stdin)) return 0;
    char *p = buf;
    p += 3; //skip 'p=<'
    pp->pos.x = strtod(p, &p);
    p += 1; // skip ','
    pp->pos.y = strtod(p, &p);
    p += 1; // skip ','
    pp->pos.z = strtod(p, &p);
    p += 6; // skip '>, v=<'
    pp->speed.x = strtod(p, &p);
    p += 1; // skip ','
    pp->speed.y = strtod(p, &p);
    p += 1; // skip ','
    pp->speed.z = strtod(p, &p);
    p += 6; // skip '>, a=<'
    pp->accel.x = strtod(p, &p);
    p += 1; // skip ','
    pp->accel.y = strtod(p, &p);
    p += 1; // skip ','
    pp->accel.z = strtod(p, &p);
    return 1;
}

double speed3d(const struct Particle *p) {
    double v = 0;
    v += p->speed.x * p->speed.x;
    v += p->speed.y * p->speed.y;
    v += p->speed.z * p->speed.z;
    return sqrt(v);
}

double accel3d(const struct Particle *p) {
    double v = 0;
    v += p->accel.x * p->accel.x;
    v += p->accel.y * p->accel.y;
    v += p->accel.z * p->accel.z;
    return sqrt(v);
}

int fxcmp(const void *aa, const void *bb) {
    const struct Particle *a = aa;
    const struct Particle *b = bb;
    if (accel3d(a) < accel3d(b)) return -1;
    if (accel3d(a) > accel3d(b)) return +1;
    if (speed3d(a) < speed3d(b)) return -1;
    if (speed3d(a) > speed3d(b)) return +1;
    return 0;
}

int main(void) {
    struct Particle p[1100] = {0};
    int nparticles = 0;
    while (readparticle(p + nparticles)) { p[nparticles].pid = nparticles; nparticles++; }
    //printf("read %d particles.\n", nparticles);
    qsort(p, nparticles, sizeof *p, fxcmp);
    printf("closest partiicle is %d.\n", p->pid);
    return 0;
}
