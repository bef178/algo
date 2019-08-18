#ifndef _INCLUDED_INT64
#define _INCLUDED_INT64

int32 hash32(int32);

int32 rol(int32, int);
int32 ror(int32, int);
int32 rorp(int32, int i, int j, int offset);
int32 shr(int32, int);

typedef int (Int64_comparef)(int64, int64);
typedef int32 (Int64_hashf)(int64);

int Int64_compare(int64, int64);
int32 Int64_hash(int64);

#endif // _INCLUDED_INT64
