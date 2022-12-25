#ifndef _INCLUDED_CASCII
#define _INCLUDED_CASCII

#define HT 0x09
#define LF 0x0a
#define VT 0x0b
#define FF 0x0c
#define CR 0x0d

#define SP 0x20

#define DOUBLE_QUOTE 0x22
#define SINGLE_QUOTE 0x27
#define COMMA 0x2c
#define BACK_QUOTE 0x60

boolean isPrintable(const int ch);

boolean isVisible(const int ch);

boolean isWhitespace(const int ch);

boolean isLower(const int ch);

boolean isUpper(const int ch);

int toLower(int ch);

int toUpper(int ch);

#endif // _INCLUDED_CASCII
