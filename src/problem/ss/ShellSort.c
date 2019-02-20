/**
 * shell sort, a.k.a diminishing increment sort
 * with inner insertion sort
 */
void ShellSort_sort(int * a, int l, int r) {
    static const int gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 }; // Ciura, 2001
    for (int k = 0; k < sizeof(gaps) / sizeof(int); k++) {
        int gap = gaps[k];
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
