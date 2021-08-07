#include <assert.h>

static void Int32Array_fillFirst5(int* a, int a0, int a1, int a2, int a3, int a4) {
    a[0] = a0;
    a[1] = a1;
    a[2] = a2;
    a[3] = a3;
    a[4] = a4;
}

void Int32Array_sort5int(int* a1, int l, int r) {
    assert(a1 != NULL);
    assert(l >= 0);
    assert(r - l == 5);

    a1 += l;
    int a = a1[0];
    int b = a1[1];
    int c = a1[2];
    int d = a1[3];
    int e = a1[4];

    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }

    if (c > d) {
        int t = c;
        c = d;
        d = t;
    }

    if (b > d) {
        // a,b <=> c,d
        int t = a;
        a = c;
        c = t;
        t = b;
        b = d;
        d = t;
    }

    // now there is [a,b,d] and [c,d] and [e]
    // insert e into [a,b,d]
    if (b <= e) {
        if (d <= e) {
            // [a,b,d,e]
            // insert c into [a,b]
            if (a <= c) {
                if (b <= c) {
                    // [a,b,c,d,e]
                    Int32Array_fillFirst5(a1, a, b, c, d, e);
                } else {
                    // [a,c,b,d,e]
                    Int32Array_fillFirst5(a1, a, c, b, d, e);
                }
            } else {
                // [c,a,b,d,e]
                Int32Array_fillFirst5(a1, c, a, b, d, e);
            }
        } else {
            // [a,b,e,d]
            // insert c into [a,b,e], binary search
            if (b <= c) {
                if (c <= e) {
                    // [a,b,c,e,d]
                    Int32Array_fillFirst5(a1, a, b, c, e, d);
                } else {
                    // [a,b,e,c,d]
                    Int32Array_fillFirst5(a1, a, b, e, c, d);
                }
            } else {
                if (a <= c) {
                    // [a,c,b,e,d]
                    Int32Array_fillFirst5(a1, a, c, b, e, d);
                } else {
                    // [c,a,b,e,d]
                    Int32Array_fillFirst5(a1, c, a, b, e, d);
                }
            }
        }
    } else {
        if (a <= e) {
            // [a,e,b,d]
            // insert c into [a,e,b]
            if (c <= e) {
                if (a <= c) {
                    // [a,c,e,b,d]
                    Int32Array_fillFirst5(a1, a, c, e, b, d);
                } else {
                    // [c,a,e,b,d]
                    Int32Array_fillFirst5(a1, c, a, e, b, d);
                }
            } else {
                if (b <= c) {
                    // [a,e,b,c,d]
                    Int32Array_fillFirst5(a1, a, e, b, c, d);
                } else {
                    // [a,e,c,b,d]
                    Int32Array_fillFirst5(a1, a, e, c, b, d);
                }
            }
        } else {
            // [e,a,b,d]
            // insert c into [e,a,b]
            if (a <= c) {
                if (b <= c) {
                    // [e,a,b,c,d]
                    Int32Array_fillFirst5(a1, e, a, b, c, d);
                } else {
                    // [e,a,c,b,d]
                    Int32Array_fillFirst5(a1, e, a, c, b, d);
                }
            } else {
                if (c <= e) {
                    // [c,e,a,b,d]
                    Int32Array_fillFirst5(a1, c, e, a, b, d);
                } else {
                    // [e,c,a,b,d]
                    Int32Array_fillFirst5(a1, e, c, a, b, d);
                }
            }
        }
    }
}
