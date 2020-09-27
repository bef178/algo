/**
 * Date on Gregorian calendar
 */

#include <assert.h>

static const int32 DAYS_OVER_MONTH_365[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int32 DAYS_OVER_MONTH_366[] = {
        31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static boolean isLeapYear(int32 year) {
    if (year % 100 == 0) {
        return year % 400 == 0;
    }
    return year % 4 == 0;
}

static const int32 * getDaysOverMonthsByYear(int32 year) {
    return isLeapYear(year) ? DAYS_OVER_MONTH_366 : DAYS_OVER_MONTH_365;
}

static int32 daysToDayOfWeek(int64 days) {
    int32 from = 4; // 1970-01-01 is Thursday
    from = (int32) ((from + days) % 7);
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

public
boolean TimeUtil_breakDays(const int64 days,
        int32 * outYear, int32 * outDayOfYear,
        int32 * outMonthOfYear, int32 * outDayOfMonth,
        int32 * outWeekOfYear, int32 * outDayOfWeek) {
    if (days < MIN_DAYS || days >= MAX_DAYS) {
        return false;
    }

    // rebase to 2000-01-01
    int64 i = days - (Y1 * 30 + 7);

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

    const int32 year = 2000 + 400 * n400 + 100 * n100 + 4 * n4 + 1 * n1;
    if (outYear != NULL) {
        *outYear = year;
    }

    const int32 dayOfYear = j;
    if (outDayOfYear != NULL) {
        *outDayOfYear = dayOfYear;
    }

    const int32 * daysOverMonths = getDaysOverMonthsByYear(year);
    int32 m = 0;
    while (j >= daysOverMonths[m]) {
        j -= daysOverMonths[m];
        m++;
    }

    if (outMonthOfYear != NULL) {
        *outMonthOfYear = m;
    }

    if (outDayOfMonth != NULL) {
        *outDayOfMonth = j;
    }

    if (outWeekOfYear != NULL) {
        *outWeekOfYear = (daysToDayOfWeek(days - dayOfYear) + dayOfYear) / 7;
    }

    if (outDayOfWeek != NULL) {
        *outDayOfWeek = daysToDayOfWeek(days);
    }

    return true;
}

public
int64 TimeUtil_totalDays(const int32 year, const int32 dayOfYear) {
    assert(dayOfYear >= 0 && dayOfYear < (isLeapYear(year) ? 366 : 355));
    // align to year 0 to avoid overflow
    int32 numLeapYears = year > 0
            ? (1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400)
            : (year / 4 - year / 100 + year / 400);
    return -719528 + 1L * 365 * year + numLeapYears + dayOfYear;
}

public
int32 TimeUtil_toDayOfYear(const int32 year, const int32 monthOfYear, const int32 dayOfMonth) {
    assert(monthOfYear >= 0 && monthOfYear < 12);

    const int32 * daysOverMonths = getDaysOverMonthsByYear(year);
    assert(dayOfMonth >= 0 && dayOfMonth < daysOverMonths[monthOfYear]);

    int32 dayOfYear = dayOfMonth;
    for (int32 i = 0; i < monthOfYear; i++) {
        dayOfYear += daysOverMonths[i];
    }
    return dayOfYear;
}

public
int TimeUtil_toUtcString(int64 timestamp, byte * dst) {
    int64 days;
    int32 millisecondOfDay;
    TimeUtil_breakMilliseconds(timestamp, &days, &millisecondOfDay);

    int32 year, monthOfYear, dayOfMonth;
    TimeUtil_breakDays(days, &year, NULL, &monthOfYear, &dayOfMonth, NULL, NULL);

    int32 hh, mm, ss, sss;
    TimeUtil_breakMillisecondOfDay(millisecondOfDay, &hh, &mm, &ss, &sss);

    return sprintf(dst, "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ",
            year, monthOfYear + 1, dayOfMonth + 1, hh, mm, ss, sss);
}
