#ifndef _INCLUDED_BASE64
#define _INCLUDED_BASE64

public
void Base64_init();

/**
 * return number of produced bytes
 */
public
int Base64_encode(byte * src, int i, int j, byte * dst, int start);

/**
 * return number of produced bytes
 */
public
int Base64_decode(byte * src, int i, int j, byte * dst, int start);

#endif // _INCLUDED_BASE64
