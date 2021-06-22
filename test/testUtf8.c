#include <assert.h>
#include <memory.h>

static void Utf8Codec_test(int32 ucs4, byte * utf8, int n) {
    byte buff[8];

    int numProduced = Utf8Codec_encode(&ucs4, 0, 1, buff, 0);
    assert(numProduced == n);
    assert(memcmp(buff, utf8, numProduced) == 0);

    numProduced = Utf8Codec_decode(utf8, 0, n, (int32 *) buff, 0);
    assert(numProduced == 1);
    assert(*(int32 *)buff == ucs4);
}

void testUtf8() {
    printf("testing Utf8 ...\n");

    int32 ucs4 = 0x2F81A;
    byte utf8[8];
    utf8[0] = 0xF0;
    utf8[1] = 0xAF;
    utf8[2] = 0xA0;
    utf8[3] = 0x9A;
    Utf8Codec_test(ucs4, utf8, 4);

    ucs4 = 27721;
    utf8[0] = 0xE6;
    utf8[1] = 0xB1;
    utf8[2] = 0x89;
    Utf8Codec_test(ucs4, utf8, 3);

    ucs4 = 20320;
    utf8[0] = 0xE4;
    utf8[1] = 0xBD;
    utf8[2] = 0xA0;
    Utf8Codec_test(ucs4, utf8, 3);

    ucs4 = 'a';
    utf8[0] = 'a';
    Utf8Codec_test(ucs4, utf8, 1);
}
