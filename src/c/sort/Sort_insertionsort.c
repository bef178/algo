/**
 * by inserting elements into an already sorted list
 * straight insertion sort, stable, in-place, average/worst O(n^2)
 */
void Sort_insertionsort(int * a, int l, int r) {
    Sort_insertionsort_step(a, l, r, 1);
}

void Sort_insertionsort_step(int * a, int l, int r, int step) {
    for (int i = l + step; i < r; i += step) {
        int value = a[i];
        int j = i;
        while (j - step >= l && a[j - step] > value) {
            a[j] = a[j - step];
            j -= step;
        }
        a[j] = value;
    }
}

/**
 * insertion sort with binary search
 */
void Sort_insertionsort1(int * a, int l, int r) {
    for (int i = l + 1; i < r; i++) {
        int value = a[i];
        int k = BinarySearch_upperBound(a, 0, i, a[i]);
        if (k != i) {
            int j = i - 1;
            while (j >= k) {
                a[j + 1] = a[j];
                j--;
            }
            a[k] = value;
        }
    }
}
