#ifndef _INCLUDED_INT64
#define _INCLUDED_INT64

typedef int (Int64_comparef)(int64, int64);
typedef int32 (Int64_hashf)(int64);

int Int64_compare(int64, int64);
int32 Int64_hash(int64);

#endif // _INCLUDED_INT64
