#ifndef _INCLUDED_CTIME
#define _INCLUDED_CTIME

public
boolean Ctime_breakMilliseconds(const int64 milliseconds,
        int64 * outDays, int32 * outMillisecondOfDay);

public
int64 Ctime_totalMilliseconds(int64 days, int32 millisecondOfDay);

public
boolean Ctime_breakMillisecondOfDay(const int32 millisecondOfDay,
        int32 * outHour, int32 * outMinute, int32 * outSecond, int32 * outMillisecond);

public
int32 Ctime_toMillisecondOfDay(int32 hh, int32 mm, int32 ss, int32 sss);

public
boolean Ctime_breakDays(const int64 days,
        int32 * outYear, int32 * outDayOfYear,
        int32 * outMonthOfYear, int32 * outDayOfMonth,
        int32 * outWeekOfYear, int32 * outDayOfWeek);

public
int64 Ctime_totalDays(const int32 year, const int32 dayOfYear);

public
int32 Ctime_toDayOfYear(const int32 year, const int32 monthOfYear, const int32 dayOfMonth);

public
int Ctime_toUtcString(const int64 timestamp, byte * dst);

#endif // _INCLUDED_CTIME
