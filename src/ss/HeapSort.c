void HeapSort_sort(int * a, int l, int r) {
    Heap * heap = Heap_malloc(r - l, &Int64_compare);
    for (int i = l; i < r; i++) {
        Heap_insert(heap, a[i]);
    }
    for (int i = l; i < r; i++) {
        a[i] = (int) Heap_remove(heap);
    }
    Heap_free(heap);
}
