#include <assert.h>
#include <memory.h>
#include <inttypes.h>

static
void test_RawInt_mov8_1(int64 expectedValue, byte * expectedBytes, int expectedBytesCount) {
    byte actualBytes[expectedBytesCount];
    RawInt_mov8(actualBytes, 0, expectedBytesCount, expectedValue);
    assert(memcmp(actualBytes, expectedBytes, expectedBytesCount) == 0);

    int64 actualValue = RawInt_toInt64(expectedBytes, 0, expectedBytesCount);
    assert(actualValue == expectedValue);
}

void test_RawInt_mov() {
    printf("testing RawInt_mov ...\n");

    int64 expectedValue = 1;
    byte expectedBytes[] = { 0, 1 };
    test_RawInt_mov8_1(expectedValue, expectedBytes, 2);

    int64 expectedValue1 = 11223344;
    byte expectedBytes1[] = { 0, 0, 0, 0, 0, 0xAB, 0x41, 0x30 };
    test_RawInt_mov8_1(expectedValue1, expectedBytes1, 8);

    int64 expectedValue2 = 11223344556677LL;
    byte expectedBytes2[] = { 0, 0, 0x0A, 0x35, 0x23, 0x77, 0x2A, 0x85 };
    test_RawInt_mov8_1(expectedValue2, expectedBytes2, 8);

    int64 expectedValue3 = 666;
    byte expectedBytes3[] = { 0, 0, 2, 0x9A };
    test_RawInt_mov8_1(expectedValue3, expectedBytes3, 4);
}

void test_RawInt_shl() {
    printf("testing RawInt_shl ...\n");

    int64 value = 666;

    byte actualBytes[4];
    RawInt_mov8(actualBytes, 0, 4, value);
    RawInt_shl(actualBytes, 0, 4, 3);

    byte expectedBytes[4];
    RawInt_mov8(expectedBytes, 0, 4, value << 3);

    assert(memcmp(actualBytes, expectedBytes, 4) == 0);
}

void test_RawInt_sar() {
    printf("testing RawInt_sar ...\n");

    int64 value = -666;

    byte actualBytes[4];
    RawInt_mov8(actualBytes, 0, 4, value);
    RawInt_sar(actualBytes, 0, 4, 3);

    byte expectedBytes[4];
    RawInt_mov8(expectedBytes, 0, 4, value >> 3);

    assert(memcmp(actualBytes, expectedBytes, 4) == 0);
}

void test_RawInt_adc() {
    printf("testing RawInt_adc ...\n");

    int value1 = 679234892;
    int value2 = 12345;

    byte a1[8];
    RawInt_mov8(a1, 0, 8, value1);
    byte a2[4];
    RawInt_mov8(a2, 0, 4, value2);

    RawInt_adc(a1, 0, 8, a2, 0, 4);
    assert(RawInt_toInt64(a1, 0, 8) == value1 + value2);

    RawInt_sbc(a1, 0, 8, a2, 0, 4);
    int64 difference = RawInt_toInt64(a1, 0, 8);
    assert(difference == value1);
}

void test_RawInt_mul() {
    printf("testing RawInt_mul ...\n");

    int64 value1 = 679234892;
    int value2 = 12345;

    byte a1[8];
    RawInt_mov8(a1, 0, 8, value1);
    byte a2[4];
    RawInt_mov8(a2, 0, 4, value2);
    byte a3[8];

    RawInt_mul(a1, 0, 8, a2, 0, 4, a3, 0, 8);

    assert(RawInt_toInt64(a3, 0, 8) == value1 * value2);
}

void testRawInt() {
    test_RawInt_mov();
    test_RawInt_shl();
    test_RawInt_sar();
    test_RawInt_adc();
    test_RawInt_mul();
}
