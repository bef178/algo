void MergeSort_sort(int * a, int l, int r) {
    if (l >= r - 1) {
        return;
    }
    int m = l + (r - l) / 2;
    MergeSort_sort(a, l, m);
    MergeSort_sort(a, m, r);

    int p[r - l];
    int i = l;
    int j = m;
    int k = 0;
    while (i < m && j < r) {
        p[k++] = a[i] <= a[j]
            ? a[i++]
            : a[j++];
    }
    while (i < m) {
        p[k++] = a[i++];
    }
    while (j < r) {
        p[k++] = a[j++];
    }
    for (i = l, k = 0; i < r; i++, k++) {
        a[i] = p[k];
    }
}
