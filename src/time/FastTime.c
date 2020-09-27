/**
 * FastTime
 *
 * essentially a time span, start point defaults to 1970-01-01T00:00:00Z
 *
 * int64 as milliseconds: 2^63ms = 9.22e15s = 1.06e11d = 2.92e8y
 * int32 as years: 2^31y = 2.14e9y
 */

#include <assert.h>
#include <stdlib.h>

public
typedef struct FastTime {
    const int64 s3;
} FastTime;

public
FastTime * FastTime_malloc(int64 s3) {
    FastTime * self = calloc(1, sizeof(FastTime));
    *((int64 *) (self + 0)) = s3;
    return self;
}

public
void FastTime_free(FastTime * self) {
    free(self);
}

public
FastTime * FastTime_addMilliseconds(FastTime * self, int64 milliseconds) {
    return FastTime_malloc(self->s3 + milliseconds);
}

public
int FastTime_toDateString(FastTime * self, byte * dst) {
    return TimeUtil_toUtcString(self->s3, dst);
}
