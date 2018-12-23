#ifndef _INCLUDED_HASH
#define _INCLUDED_HASH

word rehash(word hashCode);

word hash_bkdr(const byte * p, const int n);

word hash_djb(const byte * p, const int n);

#endif // _INCLUDED_HASH
