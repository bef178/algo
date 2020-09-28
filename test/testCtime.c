#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void test_Ctime_breakMilliseconds(int seconds) {
    int64 timestamp = ((int64) seconds) * 1000;

    int64 days;
    int32 millisecondOfDay;
    Ctime_breakMilliseconds(timestamp, &days, &millisecondOfDay);

    int32 year, dayOfYear, monthOfYear, dayOfMonth, weekOfYear, dayOfWeek;
    Ctime_breakDays(days, &year, &dayOfYear, &monthOfYear, &dayOfMonth, &weekOfYear, &dayOfWeek);

    int32 hh, mm, ss, sss;
    Ctime_breakMillisecondOfDay(millisecondOfDay, &hh, &mm, &ss, &sss);

    // printf("%04d-%02d-%02dT%02d:%02d:%02dZ, %d %d\n",
    //     year, monthOfYear + 1, dayOfMonth + 1,
    //     hh, mm, ss,
    //     dayOfYear, dayOfWeek);

    time_t time = (time_t) seconds;
    struct tm * expected = gmtime(&time);

    // printf("%04d-%02d-%02dT%02d:%02d:%02dZ, %d %d\n",
    //     expected->tm_year + 1900, expected->tm_mon + 1, expected->tm_mday,
    //     expected->tm_hour, expected->tm_min, expected->tm_sec,
    //     expected->tm_yday, expected->tm_wday);

    assert(year == expected->tm_year + 1900);
    assert(dayOfYear == expected->tm_yday);
    assert(monthOfYear == expected->tm_mon);
    assert(dayOfMonth == expected->tm_mday - 1);
    assert(dayOfWeek == expected->tm_wday);
    assert(hh == expected->tm_hour);
    assert(mm == expected->tm_min);
    assert(ss == expected->tm_sec);
}

void testCtime() {
    printf("testing Ctime ...\n");

    test_Ctime_breakMilliseconds(283995075);
    test_Ctime_breakMilliseconds(1230723086);
    srand((unsigned) time(NULL));

    for (int i = 0; i < 10000; i++) {
        int seconds = rand();
        test_Ctime_breakMilliseconds(seconds);
    }
}
