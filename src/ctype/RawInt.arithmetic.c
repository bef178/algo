#include <assert.h>
#include <memory.h>
#include <stdlib.h>

/**
 * adc: 带进位的加法
 */
static
byte adc(byte augend, byte addend, boolean * cf) {
    byte sum = (byte) (augend + addend + (*cf ? 1 : 0));
    if (augend >= 0 && addend >= 0) {
        *cf = false;
    } else if (augend < 0 && addend < 0) {
        *cf = true;
    } else if (sum >= 0) {
        *cf = true;
    } else {
        *cf = false;
    }
    return sum;
}

/**
 * augend += addend
 */
public
void RawInt_adc(byte * augend, int augendStart, int augendEnd,
        byte * addend, int addendStart, int addendEnd,
        boolean * cf) {
    byte addendSignByte = addend[addendStart] >= 0 ? 0 : -1;
    for (int offset = 0; offset < augendEnd - augendStart; offset++) {
        int i = augendEnd - 1 - offset;
        int j = addendEnd - 1 - offset;
        byte addend1 = (j >= addendStart) ? addend[j] : addendSignByte;
        augend[i] = adc(augend[i], addend1, cf);
    }
}

public
void RawInt_adc8(byte * augend, int augendStart, int augendEnd, int64 addend) {
    byte buffer[8];
    RawInt_mov8(buffer, 0, 8, addend);
    boolean cf = false;
    RawInt_adc(augend, augendStart, augendEnd, buffer, 0, 8, &cf);
}

/**
 * raw = -raw
 */
public
void RawInt_neg(byte * raw, int rawStart, int rawEnd) {
    for (int i = rawStart; i < rawEnd; i++) {
        raw[i] = ~raw[i];
    }
    RawInt_adc8(raw, rawStart, rawEnd, 1);
}

/**
 * minuend -= subtrahend
 */
public
void RawInt_sbc(byte * minuend, int minuendStart, int minuendEnd,
        byte * subtrahend, int subtrahendStart, int subtrahendEnd,
        boolean * cf) {
    if (*cf) {
        RawInt_adc8(minuend, minuendStart, minuendEnd, -1);
        *cf = false;
    }

    int addendSize = subtrahendEnd - subtrahendStart;
    byte addend[addendSize];
    RawInt_mov(addend, 0, addendSize, subtrahend, subtrahendStart, subtrahendEnd);
    RawInt_neg(addend, 0, addendSize);

    RawInt_adc(minuend, minuendStart, minuendEnd, addend, 0, addendSize, cf);
}
