#ifndef _INCLUDED_INT32ARRAY
#define _INCLUDED_INT32ARRAY

int Int32Array_equals(int * a, int l, int r, int * a1, int l1, int r1);

int Int32Array_indexOfMax(int * a, int l, int r);

int Int32Array_indexOfMin(int * a, int l, int r);

void Int32Array_print(int * a, int l, int r);

void Int32Array_reverse(int * a, int l, int r);

void Int32Array_rotateR(int * a, int l, int r, int k);

void Int32Array_shuffle(int * a, int l, int r);

void Int32Array_sort5(int * a, int l, int r);

void Int32Array_swap(int * a, int i, int j);

#endif // _INCLUDED_INT32ARRAY
