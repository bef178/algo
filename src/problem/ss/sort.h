#ifndef _INCLUDED_SORT
#define _INCLUDED_SORT

/**
 * a[l,r)
 */
typedef void (sort_f)(int * a, int l, int r);

void InsertionSort_sort(int * a, int l, int r);

void SelectionSort_sort(int * a, int l, int r);

void BubbleSort_sort(int * a, int l, int r);

void HeapSort_sort(int * a, int l, int r);

void MergeSort_sort(int * a, int l, int r);

void QuickSort_sort(int * a, int l, int r);

void ShellSort_sort(int * a, int l, int r);

extern sort_f * const CountingSort_sort;

void RadixSort_leastSignificantDigit(int * a, int l, int r);

#endif // _INCLUDED_SORT
