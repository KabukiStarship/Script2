/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_clock.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_CLOCK

#include "t_clock.h"
//
//#include "t_utf.h"
//
#include <ctime>

#if SEAM == SEAM_SCRIPT2_CLOCK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace _ {

const SI2* ClockLastDayOfMonth() {
  static const SI2 kMonthDayOfYear[12] = {31,  59,  90,  120, 151, 181,
                                          212, 243, 273, 304, 334, 365};
  return kMonthDayOfYear;
}

const SI2* ClockLastDayOfMonthLeapYear() {
  static const SI2 kMonthDayOfYearLeapYear[12] = {31,  60,  91,  121, 152, 182,
                                                  213, 244, 274, 305, 335, 366};
  return kMonthDayOfYearLeapYear;
}

SIN MonthByDay(SIN day, SIN year) {
  const SI2 *cursor, *stop;
  if (day < 1) return 0;
  if (year & 3) {  // 3 = 0b'11 which is a much faster way to do modulo 4.
    cursor = ClockLastDayOfMonthLeapYear();
  } else {
    cursor = ClockLastDayOfMonth();
  }
  stop = cursor + 11;
  while (cursor <= stop)
    if (day < *cursor++) return (SIN)(stop - cursor);
  return 0;
}

SI2 ClockEpoch() { return kClockEpochInit; }

AClock* ClockInit(AClock& clock, TM4 t) { return TClockInit<TM4>(clock, t); }

AClock* ClockInit(AClock& clock, TM8 t) { return TClockInit<TM8>(clock, t); }

TME& StopwatchInit(TME& tss, TM4 t, UI4 ticks) {
  tss.seconds = t;
  tss.ticks = ticks;
  return tss;
}

AClock* ClockInit(AClock& clock) {
  time_t t;
  time(&t);
  return TClockInit<time_t>(clock, t);
}

void ClockEpochUpdate() {
  // RoomLock();
  // kClockEpochInit += 10;
  // RoomUnlock();
}

TM8 ClockNow() {
  time_t t;
  time(&t);
  if (t > kSecondsPerEpoch) ClockEpochUpdate();
  return (TM8)t;
}

TM4 ClockSeconds(AClock& clock) {
  return (clock.year - kClockEpochInit) * kSecondsPerYear +
         (clock.day - 1) * kSecondsPerDay + clock.hour * kSecondsPerHour +
         clock.minute * kSecondsPerMinute + clock.second;
}

TM4 ClockTM4(AClock& clock) { return ClockSeconds(clock); }

TM8 ClockTM8(AClock& clock) { return (TM8)ClockSeconds(clock); }

SIN ClockMonthDayCount(TM4 t) {
  TClock<TM4> date(t);
  static const CH1 days_per_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};
  AClock& clock = date.clock;
  if ((clock.year & 3) && (clock.month == 4)) {
    // Then it's a leap year and April:
    return 29;
  }
  return days_per_month[clock.month];
}

SIN ClockMonthDayCount(SIN month, SIN year) {
  if (month < 1) return 0;
  if (month > 12) return 0;
  static const CH1 days_per_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};
  if ((year & 0xC) && (month == 4))  // Then it's a leap year and April:
    return 29;
  return days_per_month[month];
}

const CH1* ClockWeekDay(SIN day_number) {
  static const CH1* days[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday", "Saturday"};
  static const CH1 kInvalidText[] = "Invalid\0";
  if (day_number < 0) {
    return kInvalidText;
  }
  if (day_number >= 7) {
    return kInvalidText;
  }
  return days[day_number];
}

CH1 ClockDayOfWeekInitial(SIN day_number) {
  static const CH1 days[] = "SMTWRFSU";
  if (day_number < 0) return 'I';
  if (day_number >= 7) return 'I';
  return days[day_number];
}

SIN ClockCompare(const AClock& date_a, const AClock& date_b) {
  D_COUT_4("\n    Expecting Date:", date_a, " and found:", date_b);

  if (date_a.year != date_b.year) {
    D_PRINTF("\n    year.a:%i != year.b:%i ", date_a.year + ClockEpoch(),
             date_b.year + ClockEpoch());
    return 1;
  }
  if (date_a.month != date_b.month) {
    D_PRINTF("\n    month.a:%i != month.b:%i ", date_a.month, date_b.month + 1);
    return 2;
  }
  if (date_a.day != date_b.day) {
    D_PRINTF("\n    day.a:%i != day.b:%i ", date_a.day, date_b.day);
    return 3;
  }
  if (date_a.hour != date_b.hour) {
    D_PRINTF("\n    hour.a:%i != hour.b:%i ", date_a.hour, date_b.hour);
    return 4;
  }
  if (date_a.minute != date_b.minute) {
    D_PRINTF("\n    minute.a:%i != minute.b:%i", date_a.minute, date_b.minute);
    return 5;
  }
  if (date_a.second != date_b.second) {
    D_PRINTF("\n    second.a:%i != second.b:%i ", date_a.second, date_b.second);
    return 6;
  }
  return 0;
}

SIN ClockCompare(TM4 time_a, TM4 time_b) {
  AClock a, b;
  ClockInit(a, time_a);
  ClockInit(b, time_b);
  SIN result = ClockCompare(a, b);
  D_PRINTF("\n  Comparing time_a:%i to time_b:%i with result:%i", time_a,
           time_b, result);
  return result;
}

SIN ClockCompare(const AClock& clock, SIN year, SIN month, SIN day,
                 SIN hour = 0, SIN minute = 0, SIN second = 0) {
  D_PRINTF("\n    Expecting %i/%i/%i@%i:%i:%i and found ", year, month, day,
           hour, minute, second);
  D_COUT(clock);

  if (year - ClockEpoch() != clock.year) {
    D_PRINTF("\n    Expecting year:%i but found:%i.", year,
             clock.year + ClockEpoch());
    return 1;
  }
  if (month != clock.month + 1) {
    D_PRINTF("\n    Expecting month:%i but found:%i.", month, clock.month + 1);
    return 2;
  }
  if (day != clock.day) {
    D_PRINTF("\n    Expecting day:%i but found:%i.", day, clock.day);
    return 3;
  }
  if (hour != clock.hour) {
    D_PRINTF("\n    Expecting hour:%i but found:%i.", hour, clock.hour);
    return 4;
  }
  if (minute != clock.minute) {
    D_PRINTF("\n    Expecting minute:%i but found:%i.", minute, clock.minute);
    return 5;
  }
  if (second != clock.second) {
    D_PRINTF("\n    Expecting second:%i but found:%i.", second, clock.second);
    return 6;
  }
  return 0;
}

void ClockZeroTime(AClock& local_time) {
  local_time.second = 0;
  local_time.minute = 0;
  local_time.hour = 0;
  local_time.day = 0;
  local_time.month = 0;
  local_time.year = 0;
}

TM4 TimeMake(AClock& time) { return (TM4)mktime(reinterpret_cast<tm*>(&time)); }

const SI2* ClockDaysInMonth() {
  static const SI2 kDaysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};
  return kDaysInMonth;
}

SIN ClockDaysInMonth(SIN month, SIN year) {
  if ((year & 3) == 0) {
    if (month == 4) return 29;
  }
  if (month < 1 || month > 12) return 0;
  return ClockDaysInMonth()[month - 1];
}

SIN ClockDayOfYear(SIN year, SIN month, SIN day) {
  if (day < 1 || day > ClockDaysInMonth(month, year) || month < 1 || month > 12)
    return 0;
  if (month == 1) {
    return day;
  }
  if (year & 3) return ClockLastDayOfMonthLeapYear()[month - 2] + 1 + day;
  return ClockLastDayOfMonth()[month - 2] + 1 + day;
}

TM4 ClockTimeTMS(SIN year, SIN month, SIN day, SIN hour, SIN minute,
                 SIN second) {
  return TClockTime<TM4>(year, month, day, hour, minute, second);
}

TM8 ClockTimeTME(SIN year, SIN month, SIN day, SIN hour, SIN minute,
                 SIN second) {
  return TClockTime<TM4>(year, month, day, hour, minute, second);
}

#if USING_UTF8 == YES_0
CH1* Print(CH1* begin, CH1* stop, const AClock& clock) {
  return TPrint<CH1>(begin, stop, clock);
}

CH1* Print(CH1* begin, CH1* stop, TME& t) {
  return TPrint<CH1>(begin, stop, t);
}

CH1* ClockPrint(CH1* begin, CH1* stop, TM4 t) {
  AClock clock;
  ClockInit(clock, t);
  return TPrint<CH1>(begin, stop, clock);
}

CH1* ClockPrint(CH1* begin, CH1* stop, TM8 t) {
  AClock clock;
  ClockInit(clock, t);
  return TPrint<CH1>(begin, stop, clock);
}

const CH1* ScanTime(const CH1* string, SIN& hour, SIN& minute, SIN& second) {
  return TScanTime<CH1>(string, hour, minute, second);
}

const CH1* Scan(const CH1* string, AClock& clock) {
  return TScan<CH1>(string, clock);
}

const CH1* Scan(const CH1* string, TME& t) { return TScan<CH1>(string, t); }

const CH1* ScanTime(const CH1* string, TM4& t) {
  return TScanTime<CH1, TM4>(string, t);
}

const CH1* ScanTime(const CH1* string, TM8& t) {
  return TScanTime<CH1, TM8>(string, t);
}

#endif
#if USING_UTF16 == YES_0

CH2* Print(CH2* begin, CH2* stop, AClock& clock) {
  return TPrint<CH2>(begin, stop, clock);
}

CH2* Print(CH2* begin, CH2* stop, TME& t) {
  return TPrint<CH2>(begin, stop, t);
}

CH2* ClockPrint(CH2* begin, CH2* stop, TM4 t) {
  return TClockPrint<CH2, TM4>(begin, stop, t);
}

CH2* ClockPrint(CH2* begin, CH2* stop, TM8 t) {
  return TClockPrint<CH2, TM8>(begin, stop, t);
}

const CH2* Scan(const CH2* string, AClock& clock) {
  return TScan<CH2>(string, clock);
}

const CH2* ScanTime(const CH2* string, SIN& hour, SIN& minute, SIN& second) {
  return TScanTime<CH2>(string, hour, minute, second);
}

const CH2* Scan(const CH2* string, TME& result) {
  return TScan<CH2>(string, result);
}

const CH2* ScanTime(const CH2* string, TM4& result) {
  return TScanTime<CH2, TM4>(string, result);
}

const CH2* ScanTime(const CH2* string, TM8& result) {
  return TScanTime<CH2, TM8>(string, result);
}
#endif

#if USING_UTF32 == YES_0

CH4* Print(CH4* begin, CH4* stop, AClock& clock) {
  return TPrint<CH4>(begin, stop, clock);
}

CH4* Print(CH4* begin, CH4* stop, TME& t) {
  return TPrint<CH4>(begin, stop, t);
}

CH4* ClockPrint(CH4* begin, CH4* stop, TM4 t) {
  return TClockPrint<CH4, TM4>(begin, stop, t);
}

CH4* ClockPrint(CH4* begin, CH4* stop, TM8 t) {
  return TClockPrint<CH4, TM8>(begin, stop, t);
}

const CH4* ScanTime(const CH4* string, SIN& hour, SIN& minute, SIN& second) {
  return TScanTime<CH4>(string, hour, minute, second);
}

const CH4* Scan(const CH4* string, AClock& time) {
  return TScan<CH4>(string, time);
}

const CH4* Scan(const CH4* string, TME& result) {
  return TScan<CH4>(string, result);
}

const CH4* ScanTime(const CH4* string, TM4& result) {
  return TScanTime<CH4, TM4>(string, result);
}

const CH4* ScanTime(const CH4* string, TM8& result) {
  return TScanTime<CH4, TM8>(string, result);
}

#endif

}  // namespace _

#endif  //< #if SEAM >= SEAM_SCRIPT2_CLOCK
