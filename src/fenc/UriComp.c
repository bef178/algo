/**
 * Uri Component
 */

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

static
boolean * UriComp_encoding = NULL;

public
void UriComp_init() {
    if (UriComp_encoding == NULL) {
        UriComp_encoding = calloc(128, sizeof(byte));
        // byte * UNRESERVED = "-_.~"; // safe
        byte * GEN_DELIMS = ":/?#[]@";
        for (int i = strlen(GEN_DELIMS); i-- > 0;) {
            UriComp_encoding[GEN_DELIMS[i]] = true;
        }
        byte * SUB_DELIMS = "!$&'()*+,;=";
        for (int i = strlen(SUB_DELIMS); i-- > 0;) {
            UriComp_encoding[SUB_DELIMS[i]] = true;
        }
    }
}

public
void UriComp_finalize() {
    if (UriComp_encoding != NULL) {
        free(UriComp_encoding);
        UriComp_encoding = NULL;
    }
}

static
int UriComp_encode1byte(int aByte, byte * dst, int k) {
    assert(aByte >= 0 && aByte <= 0xFF);
    assert(dst != NULL);
    assert(k >= 0);
    if (aByte >= 0x20 && aByte < 0x7F && !UriComp_encoding[aByte]) {
        dst[k] = aByte;
        return 1;
    } else {
        dst[k++] = '%';
        Hexdig_encode1byte(aByte, dst, k);
        return 3;
    }
}

public
int UriComp_encode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(dst != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numProduced = UriComp_encode1byte(src[i++], dst, k);
        k += numProduced;
    }
    return k - start;
}

static
int UriComp_decode1byte(byte * src, int i, byte * aByte) {
    assert(src != NULL);
    assert(i >= 0);
    *aByte = src[i++];
    if (*aByte == '%') {
        *aByte = Hexdig_decode1byte(src, i);
        return 3;
    } else {
        return 1;
    }
}

public
int UriComp_decode(byte * src, int i, int j, byte * dst, int start) {
    assert(src != NULL);
    assert(i >= 0);
    assert(j >= i);
    assert(dst != NULL);
    assert(start >= 0);

    int k = start;
    while (i < j) {
        int numConsumed = UriComp_decode1byte(src, i, dst + k);
        i += numConsumed;
        k++;
        assert(i <= j);
    }
    return k - start;
}
