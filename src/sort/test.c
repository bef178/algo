void testSort(sort_f * sort, int * a, int l, int r) {
    ints2stdout(a, l, r);
    sort(a, l, r);
    ints2stdout(a, l, r);
}

int main() {
    int a[] = {6,5,3,1,8,7,2,4};
    int n = sizeof(a) / sizeof(int);
    testSort(&QuickSort_sort, a, 0, n);
    return 0;
}
