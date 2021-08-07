#include <assert.h>
#include <memory.h>
#include <stdlib.h>

static void Base64Codec_testEncode(byte * src, int srcSize, byte * base64, int base64Size) {
    byte buff[64];
    memset(buff, 0, 64);

    int buffSize = Base64Codec_encode(src, 0, srcSize, buff, 0);
    assert(buffSize == base64Size);
    assert(memcmp(buff, base64, buffSize) == 0);

    buffSize = Base64Codec_decode(base64, 0, base64Size, buff, 0);
    assert(buffSize == srcSize);
    assert(memcmp(buff, src, buffSize) == 0);
}

void testBase64() {
    printf("testing Base64 ...\n");
    Base64Codec_staticInit();
    Base64Codec_testEncode("a", 1, "YQ==", 4);
    Base64Codec_testEncode("a\n", 2, "YQo=", 4);
    Base64Codec_testEncode("ab\n", 3, "YWIK", 4);
    Base64Codec_testEncode("我\n", 4, "5oiRCg==", 8);
}
