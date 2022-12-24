#ifndef _INCLUDED_INT32
#define _INCLUDED_INT32

int32 Int32_hash(int32 d);

int32 Int32_max(int32 i, int32 j);
int32 Int32_min(int32 i, int32 j);
int32 Int32_minOf3(int32 i, int32 j, int32 k);

int32 Int32_rol(int32 d, int numBits);
int32 Int32_ror(int32 d, int numBits);
int32 Int32_rorp(int32 d, int i, int j, int numBits);
int32 Int32_shr(int32 d, int numBits);

#endif // _INCLUDED_INT32
