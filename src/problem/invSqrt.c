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
