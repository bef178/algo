#ifndef _INCLUDED_TIMEUTIL
#define _INCLUDED_TIMEUTIL

public
boolean TimeUtil_breakMilliseconds(const int64 milliseconds,
        int64 * outDays, int32 * outMillisecondOfDay);

public
boolean TimeUtil_breakMillisecondOfDay(const int32 millisecondOfDay,
        int32 * outHour, int32 * outMinute, int32 * outSecond, int32 * outMillisecond);

public
int64 totalMilliseconds(int64 days, int32 millisecondOfDay);

public
int32 TimeUtil_toMillisecondOfDay(int32 hh, int32 mm, int32 ss, int32 sss);

public
boolean TimeUtil_breakDays(const int64 days,
        int32 * outYear, int32 * outDayOfYear,
        int32 * outMonthOfYear, int32 * outDayOfMonth,
        int32 * outWeekOfYear, int32 * outDayOfWeek);

public
int64 TimeUtil_totalDays(const int32 year, const int32 dayOfYear);

public
int32 TimeUtil_toDayOfYear(const int32 year, const int32 monthOfYear, const int32 dayOfMonth);

#endif // _INCLUDED_TIMEUTIL
