#include <stdio.h>

void hanoi(int n, int from, int to, int via) {
    if (n > 0) {
        hanoi(n - 1, from, via, to);
        printf("move #%d from %d to %d\n", n, from, to);
        hanoi(n - 1, via, to, from);
    }
    return;
}
