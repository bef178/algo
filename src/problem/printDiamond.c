#include <stdio.h>

static int abs(int i) {
    return i >= 0 ? i : -1;
}

void printDiamond(int radius) {
    radius--;
    for (int j = 0; j < radius * 2 + 1; j++) {
        for (int i = 0; i < radius * 2 + 1; i++) {
            int d = radius - abs(radius - i) - abs(radius - j);
            if (d >= 0) {
                printf("%c", 'A' + d);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
