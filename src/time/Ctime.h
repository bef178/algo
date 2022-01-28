#ifndef _INCLUDED_CTIME
#define _INCLUDED_CTIME

/**
 * Date and Time
 */

public
void Ctime_breakMilliseconds(const int64 millisecondsSinceEpoch,
        int64 * outDaysSinceEpoch, int32 * outMillisecondOfDay);

public
int64 Ctime_totalMilliseconds(const int64 daysSinceEpoch, const int32 millisecondOfDay);

public
void Ctime_breakMillisecondOfDay(const int32 millisecondOfDay,
        int32 * outHour, int32 * outMinute, int32 * outSecond, int32 * outMillisecond);

public
int32 Ctime_toMillisecondOfDay(int32 hh, int32 mm, int32 ss, int32 sss);

public
boolean Ctime_isLeapYear(int32 year);

public
int32 Ctime_toDayOfWeek(int64 daysSinceEpoch);

/**
 * all out values are indices, starting from 0
 * year 1970 month-of-year 0 day-of-month 0 equals 1970-01-01, year 0000 equals 1 B.C
 * day-of-week 0 is Sunday
 * week-of-year 0 is the week with day-of-year 0 in it
 */
public
boolean Ctime_breakDays(const int64 daysSinceEpoch,
        int32 * outYear, int32 * outDayOfYear,
        int32 * outMonthOfYear, int32 * outDayOfMonth,
        int32 * outWeekOfYear, int32 * outDayOfWeek);

public
int64 Ctime_totalDays(const int32 year, const int32 dayOfYear);

public
int32 Ctime_toDayOfYear(const int32 monthOfYear, const int32 dayOfMonth, const boolean isLeapYear);

/**
 * will take at least 24 bytes in dst
 */
public
int Ctime_toUtcString(const int64 timestamp, byte * dst);

#endif // _INCLUDED_CTIME
