/**
 * by inserting into an already sorted list
 */

/**
 * straight insertion sort
 * average O(n^2)
 * stable
 * in-place
 */
void isort(int * a, int l, int r) {
    for (int i = l + 1; i < r; i++) {
        int t = a[i];
        int j = i - 1;
        while (j >= l && a[j] > t) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
    }
}

// shell insertion sort, a.k.a diminishing increment sort
void isort1(int * a, int l, int r) {
    for (int gap = (r - l) / 2; gap > 0; gap /= 2) {
        for (int i = l + gap; i < r; i++) {
            int t = a[i];
            int j = i - gap;
            while (j >= l && a[j] > t) {
                a[j + gap] = a[j];
                j -= gap;
            }
            a[j + gap] = t;
        }
    }
}

// insertion sort with binary sort
void isort2(int * a, int l, int r) {
    for (int i = l + 1; i < r; i++) {
        int t = a[i];
        int k = BinarySearch_upperBound(a, 0, i, a[i]);
        if (k != i) {
            int j = i - 1;
            while (j >= k) {
                a[j + 1] = a[j];
                j--;
            }
            a[k] = t;
        }
    }
}
