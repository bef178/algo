#ifndef _INCLUDED_RAWINT
#define _INCLUDED_RAWINT

extern
const int NUM_BITS_PER_BYTE;

public
int RawInt_getEffectiveStartIndex(byte * a, int i, int j);

public
int RawInt_cmp(byte * one, int oneStart, int oneEnd,
        byte * another, int anotherStart, int anotherEnd);

public
int RawInt_cmp8(byte * one, int oneStart, int oneEnd, int64 value);

public
void RawInt_mov(byte * dst, int dstStart, int dstEnd, byte * src, int srcStart, int srcEnd);

public
void RawInt_mov8(byte * dst, int dstStart, int dstEnd, int64 value);

public
int64 RawInt_toInt64(byte * a, int i, int j);

public
void RawInt_print(byte * a, int i, int j);

public
void RawInt_shl(byte * a, int i, int j, int numBits);

public
void RawInt_shr(byte * a, int i, int j, int numBits);

/**
 * shift arithmetic left
 */
public
void RawInt_sal(byte * a, int i, int j, int numBits);

public
void RawInt_sar(byte * a, int i, int j, int numBits);

/**
 * augend += addend
 */
public
void RawInt_adc(byte * augend, int augendStart, int augendEnd,
        byte * addend, int addendStart, int addendEnd);

public
void RawInt_adc8(byte * augend, int augendStart, int augendEnd, int64 addend);

public
void RawInt_neg(byte * raw, int rawStart, int rawEnd);

/**
 * minuend -= subtrahend
 */
public
void RawInt_sbc(byte * minuend, int minuendStart, int minuendEnd,
        byte * subtrahend, int subtrahendStart, int subtrahendEnd);

public
void RawInt_mul(byte * multiplicand, int multiplicandStart, int multiplicandEnd,
        byte * multiplier, int multiplierStart, int multiplierEnd,
        byte * product, int productStart, int productEnd);

public
boolean RawInt_div(byte * dividend, int dividendStart, int dividendEnd,
        byte * divisor, int divisorStart, int divisorEnd,
        byte * quotient, int quotientStart, int quotientEnd,
        byte * remainder, int remainderStart, int remainderEnd);

#endif // _INCLUDED_RAWINT
