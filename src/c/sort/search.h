#ifndef _INCLUDED_SEARCH
#define _INCLUDED_SEARCH

/**
 * a[l,r)
 */
typedef int (search_f)(int * a, int l, int r, int v);

extern search_f * const BinarySearch_firstMeet;

int BinarySearch_lowerBound(int * a, int l, int r, int v);
int BinarySearch_upperBound(int * a, int l, int r, int v);

#endif // _INCLUDED_SEARCH
