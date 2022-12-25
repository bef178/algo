#include <assert.h>
#include <stdio.h>
#include <string.h>

static boolean isCharsetByte(int ch) {
    // 1111 1110 and/or 1111 1111 is invalid utf8 byte
    return ch >= 0 && ch < 0xFE;
}

// a created concept; any byte not in this range should be quoted
static boolean isPlainByte(int ch) {
    return ch != DOUBLE_QUOTE && ch != COMMA && ch >= 20 && ch < 0x7F;
}

static int peek(byte * a, int n, int i) {
    if (i < n) {
        return a[i] & 0xFF;
    }
    return EOF;
}

static int peekNext(byte * a, int n, int i) {
    if (i + 1 < n) {
        return a[i + 1] & 0xFF;
    }
    return EOF;
}

#define WR_DST(ch)                  \
    do {                            \
        if (dstEnd == NULL) {         \
            dst++;                  \
        } else if (dst < dstEnd) {    \
            *dst++ = ch;            \
        } else {                    \
            return CSV_E_NOT_ENOUGH_SPACE; \
        }                           \
    } while (0);

static int parseQuotedField(byte * src, int srcSize, int * i,
        byte * dst, const byte * dstEnd) {
    const byte * dstStart = dst;
    (*i)++;
    int state = 1;
    while (true) {
        // peek() not next(), or have to step back if meet error
        int ch = peek(src, srcSize, *i);
        switch (state) {
            case 1:
                if (ch == EOF) {
                    return CSV_E_ILLEGAL_FORMAT;
                } else if (ch == DOUBLE_QUOTE) {
                    (*i)++;
                    state = 2;
                } else if (isCharsetByte(ch)) {
                    WR_DST(ch);
                    (*i)++;
                } else {
                    return CSV_E_ILLEGAL_FORMAT;
                }
                break;
            case 2:
                if (ch == DOUBLE_QUOTE) {
                    WR_DST(ch);
                    (*i)++;
                    state = 1;
                } else {
                    return dst - dstStart;
                }
                break;
        }
    }
}

static int parseUnquotedField(byte * src, int srcSize, int * i,
        byte * dst, const byte * dstEnd) {
    const byte * dstStart = dst;
    while (true) {
        int ch = peek(src, srcSize, *i);
        if (isPlainByte(ch)) {
            WR_DST(ch);
            (*i)++;
        } else {
            return dst - dstStart;
        }
    }
}

int Csv_parse(byte * src, int srcSize, byte * field, int fieldCapacity,
        int * nConsumedOutVar, int * lastSeparatorOutVar) {
    assert(src != NULL && srcSize >= 0);
    assert(fieldCapacity >= 0);

    if (field == NULL) {
        // it is dryrun
        fieldCapacity = 0;
    }

    const byte * fieldEnd = field + fieldCapacity;

    int i = 0;
    int k = peek(src, srcSize, i) == DOUBLE_QUOTE
            ? parseQuotedField(src, srcSize, &i, field, fieldEnd)
            : parseUnquotedField(src, srcSize, &i, field, fieldEnd);

    if (k < 0) {
        return k;
    }

    // consume the separator
    int ch = peek(src, srcSize, i);
    if (ch == EOF) {
        // dummy
    } else if (ch == COMMA) {
        i++;
        ch = COMMA;
    } else if (ch == CR && peekNext(src, srcSize, i) == LF) {
        i += 2;
        ch = LF;
    } else {
        return CSV_E_ILLEGAL_FORMAT;
    }

    if (nConsumedOutVar != NULL) {
        *nConsumedOutVar = i;
    }
    if (lastSeparatorOutVar != NULL) {
        *lastSeparatorOutVar = ch;
    }
    return k;
}

static int serializeField(byte * src, int srcSize, byte * dst, byte * dstEnd) {
    // validate src and find dstSize
    boolean quoted = false;
    int numEscaped = 0;
    for (int i = 0; i < srcSize; i++) {
        int ch = src[i] & 0xFF;
        if (!isCharsetByte(ch)) {
            return CSV_E_ILLEGAL_FORMAT;
        }
        if (!isPlainByte(ch)) {
            quoted = true;
            if (ch == DOUBLE_QUOTE) {
                numEscaped++;
            }
        }
    }

    const byte * dstStart = dst;
    if (quoted) {
        if (dstEnd != NULL && dstEnd - dst < srcSize + 2 + numEscaped) {
            return CSV_E_NOT_ENOUGH_SPACE;
        }
        WR_DST(DOUBLE_QUOTE);
        for (int i = 0; i < srcSize; i++) {
            if (src[i] == DOUBLE_QUOTE) {
                WR_DST(DOUBLE_QUOTE);
            }
            WR_DST(src[i]);
        }
        WR_DST(DOUBLE_QUOTE);
        return dst - dstStart;
    } else {
        if (dstEnd != NULL && dstEnd - dst < srcSize) {
            return CSV_E_NOT_ENOUGH_SPACE;
        }
        if (dst != NULL) {
            memcpy(dst, src, srcSize);
        }
        return srcSize;
    }
}

int Csv_serialize(byte * field, int fieldSize, byte * dst, int dstCapacity,
        boolean endsRecord) {
    assert(field != NULL && fieldSize >= 0);
    assert(dst == NULL || dstCapacity >= 0);

    if (dst == NULL) {
        dstCapacity = 0;
    }

    byte * dstEnd = dst + dstCapacity;

    int k = serializeField(field, fieldSize, dst, dstEnd);
    if (k < 0) {
        return k;
    }

    dst += k;
    if (endsRecord) {
        if (dstEnd != NULL && dstCapacity < k + 2) {
            return CSV_E_NOT_ENOUGH_SPACE;
        }
        WR_DST(CR);
        WR_DST(LF);
    } else {
        if (dstEnd != NULL && dstCapacity < k + 1) {
            return CSV_E_NOT_ENOUGH_SPACE;
        }
        WR_DST(COMMA);
    }
    return dst - (dstEnd - dstCapacity);
}
