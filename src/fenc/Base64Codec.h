#ifndef _INCLUDED_BASE64CODEC
#define _INCLUDED_BASE64CODEC

public
void Base64Codec_staticInit();

/**
 * return number of produced bytes
 */
public
int Base64Codec_encode(byte * src, int i, int j, byte * dst, int start);

/**
 * return number of produced bytes
 */
public
int Base64Codec_decode(byte * src, int i, int j, byte * dst, int start);

#endif // _INCLUDED_BASE64CODEC
