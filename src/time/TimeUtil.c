/**
 * Date and Time on Gregorian calendar
 *
 * Age of the universe: 1.38e10y
 * 1d = 86400s
 * 1s = 1000ms = 1e9ns
 *
 * 2^31 = 2.14e9
 * 2^63 = 9.22e18
 *
 * 2^31d = 2.14e9d = 5.87e6y
 * 2^31s = 2.48e4d = 68.0y
 * 2^31ms = 24.8d
 * 2^31ns = 2.14e3ms = 2.14s

 * 2^63s = 1.06e14d = 2.92e11y
 * 2^63ms = 9.22e15s = 1.06e11d = 2.92e8y
 * 2^63us = 9.22e12s = 1.06e8d = 2.92e5y
 * 2^63ns = 9.22e9s = 1.06e5d = 292y
 */

#include <assert.h>

static const int32 MILLISECONDS_PER_SECOND = 1000;
static const int32 MILLISECONDS_PER_MINUTE = 1000 * 60; // MILLISECONDS_PER_SECOND * 60;
static const int32 MILLISECONDS_PER_HOUR = 1000 * 60 * 60; // MILLISECONDS_PER_MINUTE * 60;
static const int32 MILLISECONDS_PER_DAY = 1000 * 60 * 60 * 24; // MILLISECONDS_PER_HOUR * 24;

public
boolean TimeUtil_breakMilliseconds(const int64 milliseconds,
        int64 * outDays, int32 * outMillisecondOfDay) {
    int32 i = (int32) (milliseconds % MILLISECONDS_PER_DAY);
    if (i < 0) {
        i += MILLISECONDS_PER_DAY;
    }
    if (outDays != NULL) {
        *outDays = (milliseconds - i) / MILLISECONDS_PER_DAY;
    }
    if (outMillisecondOfDay != NULL) {
        *outMillisecondOfDay = i;
    }
    return true;
}

public
boolean TimeUtil_breakMillisecondOfDay(const int32 millisecondOfDay,
        int32 * outHour, int32 * outMinute, int32 * outSecond, int32 * outMillisecond) {
    if (millisecondOfDay < 0 || millisecondOfDay > MILLISECONDS_PER_DAY) {
        return false;
    }

    if (millisecondOfDay == MILLISECONDS_PER_DAY) {
        // troublesome leap second
        if (outHour != NULL) {
            *outHour = 23;
        }
        if (outMinute != NULL) {
            *outMinute = 59;
        }
        if (outSecond != NULL) {
            *outSecond = 60;
        }
        if (outMillisecond != NULL) {
            *outMillisecond = 0;
        }
    } else {
        if (outHour != NULL) {
            *outHour = (millisecondOfDay / MILLISECONDS_PER_HOUR) % 24;
        }
        if (outMinute != NULL) {
            *outMinute = (millisecondOfDay / MILLISECONDS_PER_MINUTE) % 60;
        }
        if (outSecond != NULL) {
            *outSecond = (millisecondOfDay / MILLISECONDS_PER_SECOND) % 60;
        }
        if (outMillisecond != NULL) {
            *outMillisecond = millisecondOfDay % MILLISECONDS_PER_SECOND;
        }
    }
    return true;
}

public
int64 totalMilliseconds(int64 days, int32 millisecondOfDay) {
    assert(millisecondOfDay >= 0 && millisecondOfDay < MILLISECONDS_PER_DAY);
    return MILLISECONDS_PER_DAY * days + millisecondOfDay;
}

public
int32 TimeUtil_toMillisecondOfDay(int32 hh, int32 mm, int32 ss, int32 sss) {
    assert(hh >= 0 && hh < 60);
    assert(mm >= 0 && mm < 60);
    assert(ss >= 0 && ss < 60);
    assert(sss >= 0 && sss < 1000);
    return MILLISECONDS_PER_HOUR * hh + MILLISECONDS_PER_MINUTE * mm
            + MILLISECONDS_PER_SECOND * ss + sss;
}
