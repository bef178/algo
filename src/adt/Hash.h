#ifndef _INCLUDED_HASH
#define _INCLUDED_HASH

word Hash_rehash(word hashCode);

word Hash_bkdr(const byte * p, const int n);

word Hash_djb(const byte * p, const int n);

#endif // _INCLUDED_HASH
