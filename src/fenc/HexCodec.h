#ifndef _INCLUDED_HEXCODEC
#define _INCLUDED_HEXCODEC

public
void HexCodec_encode1byte(int srcByte, byte * dst, int start);

public
int HexCodec_decode1byte(byte * src, int i);

#endif // _INCLUDED_HEXCODEC
