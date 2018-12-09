void swap(int * a, int i, int j) {
    a[i] += a[j];
    a[j] = a[i] - a[j];
    a[j] = a[i] - a[j];
}

int min(int i, int j) {
    return i <= j ? i : j;
}

int max(int i, int j) {
    return i >= j ? i : j;
}
