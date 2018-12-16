#ifndef _INCLUDED_SEARCH
#define _INCLUDED_SEARCH

/**
 * a[l,r)
 */
typedef int (search_f)(int * a, int l, int r, int v);

extern search_f * const BinarySearch_upperBound;
extern search_f * const BinarySearch_lowerBound;

#endif // _INCLUDED_SEARCH
