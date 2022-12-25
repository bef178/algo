#ifndef _INCLUDED_UTF8CODEC
#define _INCLUDED_UTF8CODEC

public
int Utf8Codec_encode(int32 * ucs4, int i, int j, byte * utf8, int start);

public
int Utf8Codec_decode(byte * utf8, int i, int j, int32 * ucs4, int start);

#endif // _INCLUDED_UTF8CODEC
