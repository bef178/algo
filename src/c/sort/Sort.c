interface
typedef struct Sort {

    /**
     * elements in { a[l], a[l+1], ..., a[r-1] }
     */
    void (*sort)(int* a, int l, int r);
} Sort;

