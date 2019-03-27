/**
 * Date and Time
 *
 * 1d = 86400s
 * 1s = 1000ms = 1e9ns
 *
 * int32 as d: 2^31d = 2.14e9d = 5.87e6y
 * int32 as s: 2^31s = 2.48e4d = 68.0y
 * int32 as ms: 2^31ms = 24.8d
 * int32 as ns: 2^31ns = 2.14e3ms = 2.14s
 * int64 as ns: 2^63ns = 9.22e9s = 1.06e5d = 292y
 */

static const int NUM_DAYS_PER_400_YEARS = 400 * 365 + 100 - 3;

static const int NUM_DAYS_PER_MONTHS_365[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int NUM_DAYS_PER_MONTHS_366[] = {
        31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static boolean isLeapYear(int year) {
    if (year % 100 == 0) {
        return year % 400 == 0;
    }
    return year % 4 == 0;
}

typedef struct FastDate {
    int y;
    int m;
    int d;
} FastDate;

int FastDate_getDayOfWeek(int d) {
    return (d % 7 + 3 + 7) % 7;
}

void FastDate_set(FastDate * self, int d) {
    int y = 1970;
    int i = d / NUM_DAYS_PER_400_YEARS;
    d -= i * NUM_DAYS_PER_400_YEARS;
    y += i * 400;
    while (true) {
        int numDaysPerYear = (isLeapYear(y) ? 366 : 365);
        if (d < numDaysPerYear) {
            break;
        }
        d -= numDaysPerYear;
        y++;
    }

    int m = 0;
    const int * numDaysPerMonths = (isLeapYear(y)
        ? NUM_DAYS_PER_MONTHS_366
        : NUM_DAYS_PER_MONTHS_365);
    for (int i = 0; i < 12; i++) {
        if (d >= numDaysPerMonths[i]) {
            d -= numDaysPerMonths[i];
            m++;
        }
    }

    self->y = y;
    self->m = m + 1;
    self->d = d + 1;
}
