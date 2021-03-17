int Int32Array_indexOfMax(int * a, int l, int r) {
    int max = l;
    for (int i = l + 1; i < r; i++) {
        if (a[max] < a[i]) {
            max = i;
        }
    }
    return max;
}

int Int32Array_indexOfMin(int * a, int l, int r) {
    int min = l;
    for (int i = l + 1; i < r; i++) {
        if (a[min] > a[i]) {
            min = i;
        }
    }
    return min;
}

void Int32Array_swap(int* a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}
