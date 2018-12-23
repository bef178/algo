#ifndef _INCLUDED_CSTRING
#define _INCLUDED_CSTRING

int str_concatenate(byte * dst, const byte * src, const int n);

int str_compare(const byte * s1, const byte * s2, const int n);

int str_copy(byte * dst, const byte * src, const int n);

int str_indexOf(const byte * s, const byte * p);

int str_length(const byte * s);

int str_substring(byte * dst, const byte * src, int i, int j);

/**
 * trim 'white spaces' from head
 * returns where the trimmed string @s 'should' start
 */
byte * str_trimFore(byte * s);

/**
 * trim 'white spaces' from tail
 * indicate where '\0' should be, instead of write it to string @s
 * returns where the trimmed string @s 'should' end
 */
byte * str_trimHind(byte * s);

#endif // _INCLUDED_CSTRING
