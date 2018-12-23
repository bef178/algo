#ifndef _INCLUDED_UTF8
#define _INCLUDED_UTF8

const byte * utf8Glyph_getHead(const byte * p);

boolean utf8Glyph_isHead(const byte * p);

int utf8Glyph_size(const byte * utf8);

int utf8_toUcs4(const byte * utf8, int32 * ucs4);

#endif // _INCLUDED_UTF8
