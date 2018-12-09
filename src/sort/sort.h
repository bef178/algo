#ifndef _INCLUDED_SORT
#define _INCLUDED_SORT

/**
 * a[l,r)
 */
typedef void (sort_f)(int * a, int l, int r);

void isort(int * a, int l, int r);
void isort1(int * a, int l, int r);
void isort2(int * a, int l, int r);

#endif // _INCLUDED_SORT
