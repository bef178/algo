/**
 * Uri Codec
 */

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

static
boolean * UriCodec_SHOULD_ENCODE = NULL;

public
void UriCodec_init() {
    if (UriCodec_SHOULD_ENCODE == NULL) {
        UriCodec_SHOULD_ENCODE = calloc(128, sizeof(byte));
        // byte * UNRESERVED = "-_.~"; // safe
        byte * GEN_DELIMS = ":/?#[]@";
        for (int i = 0; GEN_DELIMS[i] != '\0'; i++) {
            UriCodec_SHOULD_ENCODE[GEN_DELIMS[i]] = true;
        }
        byte * SUB_DELIMS = "!$&'()*+,;=";
        for (int i = 0; SUB_DELIMS[i] != '\0'; i++) {
            UriCodec_SHOULD_ENCODE[SUB_DELIMS[i]] = true;
        }
    }
}

public
void UriCodec_finalize() {
    if (UriCodec_SHOULD_ENCODE != NULL) {
        free(UriCodec_SHOULD_ENCODE);
        UriCodec_SHOULD_ENCODE = NULL;
    }
}

static
int UriCodec_encode1byte(int srcByte, byte * dst, int start) {
    assert(srcByte >= 0 && srcByte <= 0xFF);
    assert(start >= 0);
    if (srcByte >= 0x20 && srcByte < 0x7F && !UriCodec_SHOULD_ENCODE[srcByte]) {
        if (dst != NULL) {
            dst[start] = srcByte;
        }
        return 1;
    } else {
        if (dst != NULL) {
            dst[start++] = '%';
            Hexdig_encode1byte(srcByte, dst, start);
        }
        return 3;
    }
}

/**
 * return num produced bytes of dst
 */
public
int UriCodec_encode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    // dst can be null
    assert(start >= 0);

    int k = start;
    while (i < j) {
        k += UriCodec_encode1byte(src[i++], dst, k);
    }
    return k - start;
}

static
int UriCodec_decode1byte(byte * src, int i, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(start >= 0);
    int srcByte = src[i++] & 0xFF;
    if (srcByte == '%') {
        if (dst != NULL) {
            dst[start] = Hexdig_decode1byte(src, i);
        }
        return 3;
    } else {
        if (dst != NULL) {
            dst[start] = (byte) srcByte;
        }
        return 1;
    }
}

/**
 * return num produced bytes of src
 */
public
int UriCodec_decode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    // dst can be null
    assert(start >= 0);

    int k = start;
    while (i < j) {
        i += UriCodec_decode1byte(src, i, dst, k++);
        assert(i <= j);
    }
    return k - start;
}
