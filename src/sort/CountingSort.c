#include <string.h>

/**
 * non-comparion sort
 * only suitable for situations where key range is not significantly greater than the number of items
 */
static void sort(int * a, int l, int r) {
    int max = a[l];
    int min = a[l];
    for (int i = l + 1; i < r; i++) {
        if (max < a[i]) {
            max = a[i];
        }
        if (min > a[i]) {
            min = a[i];
        }
    }

    int c[max - min + 1];
    memset(c, 0, sizeof(c));
    for (int i = l; i < r; i++) {
        c[a[i] - min]++;
    }

    for (int i = l + 1; i < r; i++) {
        c[i] += c[i - 1];
    }

    int t[r - l];
    for (int i = r - 1; i >= l; i--) {
        t[--c[a[i] - min]] = a[i];
    }

    memcpy(a + l, t, (r - l) * sizeof(int));
}

static void sort1(int * a, int l, int r) {
    int max = a[l];
    int min = a[l];
    for (int i = l + 1; i < r; i++) {
        if (max < a[i]) {
            max = a[i];
        }
        if (min > a[i]) {
            min = a[i];
        }
    }

    int c[max - min + 1];
    memset(c, 0, sizeof(c));
    for (int i = l; i < r; i++) {
        c[a[i] - min]++;
    }

    int t[r - l];
    int k = r - l - 1;
    for (int i = max - min + 1 - 1; i >= 0; i--) {
        while (c[i] != 0) {
            t[k--] = i + min;
            c[i]--;
        }
    }

    memcpy(a + l, t, (r - l) * sizeof(int));
}

sort_f * const CountingSort_sort = &sort;
