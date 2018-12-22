int compareInt64(int64 i, int64 j) {
    return i - j;
}

void HeapSort_sort(int * a, int l, int r) {
    MinHeap * heap = MinHeap_malloc(r - l, &compareInt64);
    for (int i = l; i < r; i++) {
        MinHeap_insert(heap, a[i]);
    }
    for (int i = l; i < r; i++) {
        a[i] = (int) MinHeap_remove(heap);
    }
    MinHeap_free(heap);
}
