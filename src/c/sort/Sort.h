#ifndef _INCLUDED_SORT
#define _INCLUDED_SORT

/**
 * a[l,r)
 */
typedef void (sort_f)(int * a, int l, int r);

void Sort_bubblesort(int * a, int l, int r);

void Sort_countingsort(int * a, int l, int r);

void Sort_heapsort(int * a, int l, int r);

void Sort_insertionsort(int * a, int l, int r);
void Sort_insertionsort_step(int * a, int l, int r, int step);
void Sort_insertionsort1(int * a, int l, int r);

void Sort_mergesort(int * a, int l, int r);

void Sort_quicksort(int * a, int l, int r);

void Sort_radixsort(int * a, int l, int r);

void Sort_selectionsort(int * a, int l, int r);

void Sort_shellsort(int * a, int l, int r);

#endif // _INCLUDED_SORT
