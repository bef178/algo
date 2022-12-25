public
void Int64Array_swap(int64 * a, int i, int j) {
    int64 t = a[i];
    a[i] = a[j];
    a[j] = t;
}
