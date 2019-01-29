#ifndef _INCLUDED_CTYPE
#define _INCLUDED_CTYPE

#define HT 0x09
#define LF 0x0a
#define VT 0x0b
#define FF 0x0c
#define CR 0x0d
#define SP 0x20

boolean isWhiteSpace(const int ch);

boolean isLower(const int ch);

boolean isUpper(const int ch);

int toLower(int ch);

int toUpper(int ch);

#endif // _INCLUDED_CTYPE
