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
        byte * addend, int addendStart, int addendEnd) {
    boolean cf = false;
    byte addendSignByte = addend[addendStart] >= 0 ? 0 : -1;
    for (int d = 0; d < augendEnd - augendStart; d++) {
        int i = augendEnd - 1 - d;
        int j = addendEnd - 1 - d;
        byte addend1 = (j >= addendStart) ? addend[j] : addendSignByte;
        augend[i] = adc(augend[i], addend1, &cf);
    }
}

public
void RawInt_adc8(byte * augend, int augendStart, int augendEnd, int64 addend) {
    byte buffer[8];
    RawInt_mov8(buffer, 0, 8, addend);
    RawInt_adc(augend, augendStart, augendEnd, buffer, 0, 8);
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
        byte * subtrahend, int subtrahendStart, int subtrahendEnd) {
    int addendSize = subtrahendEnd - subtrahendStart;
    byte addend[addendSize];
    RawInt_mov(addend, 0, addendSize, subtrahend, subtrahendStart, subtrahendEnd);
    RawInt_neg(addend, 0, addendSize);

    RawInt_adc(minuend, minuendStart, minuendEnd, addend, 0, addendSize);
}

/**
 * multiplicand * multiplier = product
 * unsigned
 */
public
void RawInt_mul(
        byte * multiplicand, int multiplicandStart, int multiplicandEnd,
        byte * multiplier, int multiplierStart, int multiplierEnd,
        byte * product, int productStart, int productEnd) {
    multiplicand += multiplicandStart;
    int multiplicandSize = multiplicandEnd - multiplicandStart;
    multiplier += multiplierStart;
    int multiplierSize = multiplierEnd - multiplierStart;
    product += productStart;
    int productSize = productEnd - productStart;
    memset(product, 0, productSize);

    for (int j = multiplierSize - 1; j >= 0; j--) {
        int jv = multiplier[j] & 0xFF;
        if (jv == 0) {
            continue;
        }
        for (int i = multiplicandSize - 1; i >= 0; i--) {
            int k = productSize - 1 - (multiplierSize - 1 - j + multiplicandSize - 1 - i);
            if (k < 0) {
                break;
            }
            int iv = multiplicand[i] & 0xFF;
            if (iv == 0) {
                continue;
            }
            RawInt_adc8(product, 0, k + 1, jv * iv);
        }
    }
}

static
int numLeadingClearBits(byte * a, int i, int j) {
    int n = 0;
    while (i < j) {
        if (a[i] == 0) {
            n += 8;
            i++;
            continue;
        } else {
            int mask = 1 << 7;
            while ((a[i] & mask) == 0) {
                n++;
                mask >>= 1;
            }
        }
        break;
    }
    return n;
}

/**
 * dividend / divisor = quotient ... remainder
 * unsigned
 */
public
boolean RawInt_div(byte * dividend, int dividendStart, int dividendEnd,
        byte * divisor, int divisorStart, int divisorEnd,
        byte * quotient, int quotientStart, int quotientEnd,
        byte * remainder, int remainderStart, int remainderEnd) {
    if (RawInt_cmp8(divisor, divisorStart, divisorEnd, 0) == 0) {
        return false;
    }

    if (RawInt_cmp8(dividend, dividendStart, dividendEnd, 0) == 0) {
        RawInt_mov8(quotient, quotientStart, quotientEnd, 0);
        RawInt_mov8(remainder, remainderStart, remainderEnd, 0);
        return true;
    }

    if (RawInt_cmp(dividend, dividendStart, dividendEnd, divisor, divisorStart, divisorEnd) < 0) {
        RawInt_mov8(quotient, quotientStart, quotientEnd, 0);
        RawInt_mov(remainder, remainderStart, remainderEnd, dividend, dividendStart, dividendEnd);
        return true;
    }
    memset(quotient + quotientStart, 0, quotientEnd - quotientStart);

    int n = dividendEnd - RawInt_getEffectiveStartIndex(dividend, dividendStart, dividendEnd);

    byte a1[n];
    RawInt_mov(a1, 0, n, dividend, dividendStart, dividendEnd);

    byte a2[n];
    RawInt_mov(a2, 0, n, divisor, divisorStart, divisorEnd);

    int bitOffset = numLeadingClearBits(a2, 0, n) - numLeadingClearBits(a1, 0, n);
    RawInt_shl(a2, 0, n, bitOffset);

    while (true) {
        if (RawInt_cmp(a1, 0, n, a2, 0, n) >= 0) {
            RawInt_sbc(a1, 0, n, a2, 0, n);
            if (bitOffset < 64) {
                RawInt_adc8(quotient, quotientStart, quotientEnd, 1 << bitOffset);
            } else {
                byte a[n];
                RawInt_mov8(a, 0, n, 1);
                RawInt_shl(a, 0, n, bitOffset);
                RawInt_adc(quotient, quotientStart, quotientEnd, a, 0, n);
            }
        } else {
            if (bitOffset == 0) {
                break;
            }
            RawInt_sar(a2, 0, n, 1);
            bitOffset--;
        }
    }
    RawInt_mov(remainder, remainderStart, remainderEnd, a1, 0, n);
    return true;
}
