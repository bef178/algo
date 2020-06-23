#ifndef _INCLUDED_UTF8
#define _INCLUDED_UTF8

public
int Utf8_encode(int32 * ucs4, int i, int j, byte * utf8, int start);

public
int Utf8_decode(byte * utf8, int i, int j, int32 * ucs4, int start);

#endif // _INCLUDED_UTF8
