#ifndef _INCLUDED_TIMEUTIL
#define _INCLUDED_TIMEUTIL

public
boolean TimeUtil_breakMilliseconds(const int64 milliseconds,
        int64 * outDays, int32 * outMillisecondOfDay);

public
int64 TimeUtil_totalMilliseconds(int64 days, int32 millisecondOfDay);

public
boolean TimeUtil_breakMillisecondOfDay(const int32 millisecondOfDay,
        int32 * outHour, int32 * outMinute, int32 * outSecond, int32 * outMillisecond);

public
int32 TimeUtil_toMillisecondOfDay(int32 hour, int32 minute, int32 second, int32 millisecond);

public
boolean TimeUtil_breakDays(const int64 days,
        int32 * outYear, int32 * outDayOfYear,
        int32 * outMonthOfYear, int32 * outDayOfMonth,
        int32 * outWeekOfYear, int32 * outDayOfWeek);

public
int64 TimeUtil_totalDays(const int32 year, const int32 dayOfYear);

public
int32 TimeUtil_toDayOfYear(const int32 year, const int32 monthOfYear, const int32 dayOfMonth);

public
int TimeUtil_toUtcString(const long timestamp, byte * dst);

#endif // _INCLUDED_TIMEUTIL
