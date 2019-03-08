#ifndef _INCLUDED_UTF8
#define _INCLUDED_UTF8

boolean Utf8_isFirstByte(const byte k);

int Utf8_codePointSize(const byte utf8FirstByte);

int Utf8_toUcs4(const byte * utf8, int32 * ucs4);

#endif // _INCLUDED_UTF8
