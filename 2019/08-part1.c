#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// assume everything 'works'
// ie: well-formed input, values in range, no overflows

// program expects the image data to be in stdin
// and the image size as parameters
// $ ./a.out 3 2 <08-test1.txt

#define MAXLAYERS 102                  // enough for my input
#define MAXWIDTH 32                    // enough for my input
#define MAXHEIGHT 8                    // enough for my input

struct Layer {
    int data[MAXHEIGHT][MAXWIDTH];
};

struct SIF {
    int width, height;
    int nlayers;
    struct Layer layers[MAXLAYERS];
};

int layercount(struct Layer *layer, int xx, int yy, int val) {
    int k = 0;
    for (int x = 0; x < xx; x++) {
        for (int y = 0; y < yy; y++) {
            if (layer->data[y][x] == val) k++;
        }
    }
    return k;
}

int main(int argc, char **argv) {
    (void)argc;                        // suppress warning
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    struct SIF sif[1] = {0};
    sif->width = width;
    sif->height = height;
    sif->nlayers = 0;
    int x = 0, y = 0;
    int tmp;
    while ((tmp = getchar()) != EOF) {
        if ((tmp < '0') || (tmp > '9')) break;
        sif->layers[sif->nlayers].data[y][x] = tmp - '0';
        x++;
        if (x == width) {
            x = 0;
            y++;
            if (y == height) {
                y = 0;
                sif->nlayers++;
            }
        }
    }
    int cnt[MAXLAYERS][10];
    int minlayercount = width * height + 1;
    int min0layer = MAXLAYERS;
    for (int k = 0; k < sif->nlayers; k++) {
        for (int digit = 0; digit < 3; digit++) {
            cnt[k][digit] = layercount(sif->layers + k, sif->width, sif->height, digit);
        }
        if (cnt[k][0] < minlayercount) {
            minlayercount = cnt[k][0];
            min0layer = k;
        }
    }
    printf("Result is %d.\n", cnt[min0layer][1] * cnt[min0layer][2]);
    return 0;
}
