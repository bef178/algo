#include <assert.h>

static boolean isAcceptableError(float x, float y) {
    float error = x - y;
    if (error < 0) {
        error = -error;
    }
    return error <= 0.0001;
}

float bisectionalSqrt(float c) {
    assert(c >= 0.0f);
    float last = 0.0f;
    float l = 0.0f;
    float r = c;
    while (true) {
        float m = l + (r - l) / 2;
        if (m * m > c) {
            r = m;
        } else {
            l = m;
        }
        if (isAcceptableError(m, last)) {
            return m;
        }
        last = m;
    }
}

// wanted: x = c ^ (1 / 2)
// the curve: y = x ^ 2 - c
// at the point(x0, y0) the tangent line: y = k * x + d, where k = 2 * x0
// so d = y0 - 2 * x0 ^ 2
// so the angent line: y = 2 * x0 * x + y0 - 2 * x0 ^ 2
// at the point(x1, 0) the tangent line meets x-axis, x1 is a better value
// 0 = 2 * x0 * x1 + y0 - 2 * x0 ^ 2
// so x1 = (2 * x0 ^ 2 - y0) / (2 * x0)
// the point(x0, y0) is on the curve, so y0 = x0 ^ 2 - c
// so x1 = (x0 + c / x0) / 2
float newtonSqrt(float c) {
    assert(c >= 0.0f);
    float last = 0.0f; // initial guess
    while (true) {
        float x = (last + c / last) * 0.5f;
        if (isAcceptableError(x, last)) {
            return x;
        }
        last = x;
    }
}

/**
 * 1 / sqrt(x) from Quake III Arena
 */
float invSqrt(float x) {
    float x2 = 0.5f * x;
    int32 i = *(int32 *) &x; // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);
    x = *(float *) &i; // initial guess for Newton's method
    x = x * (1.5f - (x2 * x * x)); // 1st iteration
    x = x * (1.5f - (x2 * x * x)); // 2nd iteration, this can be removed
    return x;
}
