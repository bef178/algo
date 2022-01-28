/**
 * Date and Time
 *
 * refer to ISO-8601
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
static const int32 MILLISECONDS_PER_MINUTE = MILLISECONDS_PER_SECOND * 60;
static const int32 MILLISECONDS_PER_HOUR = MILLISECONDS_PER_MINUTE * 60;
static const int32 MILLISECONDS_PER_DAY = MILLISECONDS_PER_HOUR * 24;

public
boolean Ctime_breakMilliseconds(const int64 millisecondsSinceEpoch,
        int64 * outDaysSinceEpoch, int32 * outMillisecondOfDay) {
    int32 i = (int32) (millisecondsSinceEpoch % MILLISECONDS_PER_DAY);
    if (i < 0) {
        i += MILLISECONDS_PER_DAY;
    }
    if (outDaysSinceEpoch != NULL) {
        *outDaysSinceEpoch = (millisecondsSinceEpoch - i) / MILLISECONDS_PER_DAY;
    }
    if (outMillisecondOfDay != NULL) {
        *outMillisecondOfDay = i;
    }
    return true;
}

public
int64 Ctime_totalMilliseconds(const int64 daysSinceEpoch, const int32 millisecondOfDay) {
    assert(millisecondOfDay >= 0 && millisecondOfDay < MILLISECONDS_PER_DAY);
    return MILLISECONDS_PER_DAY * daysSinceEpoch + millisecondOfDay;
}

public
void Ctime_breakMillisecondOfDay(const int32 millisecondOfDay,
        int32 * outHour, int32 * outMinute, int32 * outSecond, int32 * outMillisecond) {
    assert(millisecondOfDay >= 0 && millisecondOfDay <= MILLISECONDS_PER_DAY);

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
}

public
int32 Ctime_toMillisecondOfDay(int32 hh, int32 mm, int32 ss, int32 sss) {
    assert(hh >= 0 && hh < 60);
    assert(mm >= 0 && mm < 60);
    assert(ss >= 0 && ss < 60);
    assert(sss >= 0 && sss < 1000);
    return MILLISECONDS_PER_HOUR * hh + MILLISECONDS_PER_MINUTE * mm
            + MILLISECONDS_PER_SECOND * ss + sss;
}

/*******************
 * Date
 */

#include <assert.h>

static const int32 DAYS_OVER_MONTH_365[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int32 DAYS_OVER_MONTH_366[] = {
        31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static
const int32 * getDaysPerMonths(boolean isLeapYear) {
    return isLeapYear ? DAYS_OVER_MONTH_366 : DAYS_OVER_MONTH_365;
}

public
boolean Ctime_isLeapYear(int32 year) {
    if (year % 100 == 0) {
        return year % 400 == 0;
    }
    return year % 4 == 0;
}

public
int32 Ctime_toDayOfWeek(int64 daysSinceEpoch) {
    int32 from = 4; // 1970-01-01 is Thursday
    from = (int32) ((from + daysSinceEpoch) % 7);
    if (from < 0) {
        from += 7;
    }
    return from;
}

// int32 years
static int64 MIN_DAYS = -784353015833L;
static int64 MAX_DAYS = 784351576777L;

static const int32 Y1 = 365;
static const int32 Y4 = 1461; // Y1 * 4 + 1
static const int32 Y100 = 36524; // Y4 * 25 - 1
static const int32 Y400 = 146097; // Y100 * 4 + 1


/**
 * year starts from 1970
 * dayOfYear, monthOfYear, dayOfMonth, weekOfYear, dayOfWeek each starts from 0
 * weekOfYear: 0: the week containing the first Sunday of this year
 */
public
void Ctime_breakDays(const int64 daysSinceEpoch,
        int32 * outYear, int32 * outDayOfYear,
        int32 * outMonthOfYear, int32 * outDayOfMonth,
        int32 * outWeekOfYear, int32 * outDayOfWeek) {
    assert(daysSinceEpoch < MIN_DAYS || daysSinceEpoch >= MAX_DAYS);

    // rebase to 2000-01-01
    int64 i = daysSinceEpoch - 10957; // 10957: Y1 * 30 + 7
    int32 year = 2000;

    int32 n400 = (int32) (i / Y400);
    i -= Y400 * n400;
    if (i < 0) {
        n400--;
        i += Y400;
    }

    int32 j = (int32) i;

    int32 n100 = j / Y100;
    if (n100 == 4) {
        n100--;
    }
    j -= Y100 * n100;

    int32 n4 = j / Y4;
    j -= Y4 * n4;

    int32 n1 = j / Y1;
    if (n1 == 4) {
        n1--;
    }
    j -= Y1 * n1;
    if (n1 > 0) {
        j--;
    }

    year += 400 * n400 + 100 * n100 + 4 * n4 + 1 * n1;
    if (j < 0) {
        year--;
        j += Ctime_isLeapYear(year) ? 366 : 365;
    }
    if (outYear != NULL) {
        *outYear = year;
    }

    const int32 dayOfYear = j;
    if (outDayOfYear != NULL) {
        *outDayOfYear = dayOfYear;
    }

    const int32 * daysPerMonths = getDaysPerMonths(Ctime_isLeapYear(year));
    int32 m = 0;
    while (j >= daysPerMonths[m]) {
        j -= daysPerMonths[m];
        m++;
    }

    if (outMonthOfYear != NULL) {
        *outMonthOfYear = m;
    }

    if (outDayOfMonth != NULL) {
        *outDayOfMonth = j;
    }

    if (outWeekOfYear != NULL) {
        *outWeekOfYear = (Ctime_toDayOfWeek(daysSinceEpoch - dayOfYear) + dayOfYear) / 7;
    }

    if (outDayOfWeek != NULL) {
        *outDayOfWeek = Ctime_toDayOfWeek(daysSinceEpoch);
    }
}

public
int64 Ctime_totalDays(const int32 year, const int32 dayOfYear) {
    assert(dayOfYear >= 0 && dayOfYear < (Ctime_isLeapYear(year) ? 366 : 355));
    // align to year 0 to avoid overflow
    int32 numLeapYears = year > 0
            ? (1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400)
            : (year / 4 - year / 100 + year / 400);
    return -719528 + 1L * 365 * year + numLeapYears + dayOfYear; // 719528: Y400 * 5 - 10957
}

public
int32 Ctime_toDayOfYear(const int32 monthOfYear, const int32 dayOfMonth, const boolean isLeapYear) {
    assert(monthOfYear >= 0 && monthOfYear < 12);

    const int32 * daysPerMonths = getDaysPerMonths(isLeapYear);
    assert(dayOfMonth >= 0 && dayOfMonth < daysPerMonths[monthOfYear]);

    int32 dayOfYear = dayOfMonth;
    for (int32 i = 0; i < monthOfYear; i++) {
        dayOfYear += daysPerMonths[i];
    }
    return dayOfYear;
}

/**
 * take 24 bytes
 */
public
int Ctime_toUtcString(int64 millisecondsSinceEpoch, byte * dst) {
    int64 daysSinceEpoch;
    int32 millisecondOfDay;
    Ctime_breakMilliseconds(millisecondsSinceEpoch, &daysSinceEpoch, &millisecondOfDay);

    int32 year, monthOfYear, dayOfMonth;
    Ctime_breakDays(daysSinceEpoch, &year, NULL, &monthOfYear, &dayOfMonth, NULL, NULL);

    int32 hh, mm, ss, sss;
    Ctime_breakMillisecondOfDay(millisecondOfDay, &hh, &mm, &ss, &sss);

    return sprintf(dst, "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ",
            year, monthOfYear + 1, dayOfMonth + 1, hh, mm, ss, sss);
}
