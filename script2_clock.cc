/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_clock.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= SCRIPT2_5

#include <ctime>

#include "t_binary.h"
#include "t_clock.h"

#if SEAM == SCRIPT2_5
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

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

SI4 MonthByDay(SI4 day, SI4 year) {
  const SI2 *cursor, *stop;
  if (day < 1) return 0;
  if (year & 3) {  // 3 = 0b'11 which is a much faster way to do modulo 4.
    cursor = ClockLastDayOfMonthLeapYear();
  } else {
    cursor = ClockLastDayOfMonth();
  }
  stop = cursor + 11;
  while (cursor <= stop)
    if (day < *cursor++) return (SI4)(stop - cursor);
  return 0;
}

template <typename SI>
CClock* ClockInit(CClock& clock, SI t) {
  // Algorithm:
  // 1. Using manual modulo convert in the following order:
  //   a. Year based on seconds per year.
  //   b. Day of year based on seconds per day.
  //   c. Month based on day of year and leap year.
  //   d. Hour.
  //   e. Minute.
  //   f. Second.
  SI4 value = (SI4)(t / kSecondsPerYear);
  t -= value * kSecondsPerYear;
  clock.year = value + ClockEpoch();
  value = (SI4)(t / kSecondsPerDay);
  t -= value * kSecondsPerDay;
  clock.day = value;
  value = (SI4)(t / kSecondsPerHour);
  t -= value * kSecondsPerHour;
  clock.hour = value;
  value = (SI4)(t / kSecondsPerMinute);
  clock.minute = value;
  clock.second = (SI4)(t - value * kSecondsPerMinute);
  return &clock;
}

SI2 ClockEpoch() { return kClockEpochInit; }

CClock* ClockInit(CClock& clock, TM4 t) { return ClockInit<TM4>(clock, t); }

CClock* ClockInit(CClock& clock, TM8 t) { return ClockInit<TM8>(clock, t); }

TME& StopwatchInit(TME& tss, TM4 t, UI4 ticks) {
  tss.seconds = t;
  tss.ticks = ticks;
  return tss;
}

CClock* ClockInit(CClock& clock) {
  time_t t;
  time(&t);
  return ClockInit<time_t>(clock, t);
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

TM4 ClockSeconds (CClock& clock) {
  return (clock.year - kClockEpochInit) * kSecondsPerYear +
    (clock.day - 1) * kSecondsPerDay + clock.hour * kSecondsPerHour +
    clock.minute * kSecondsPerMinute + clock.second;
}

TM4 ClockTM4(CClock& clock) { return ClockSeconds(clock); }

TM8 ClockTM8(CClock& clock) { return (TM8)ClockSeconds(clock); }

SI4 ClockMonthDayCount(TM4 t) {
  TClock<TM4> date(t);
  static const CH1 days_per_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};
  CClock& clock = date.Clock();
  if ((clock.year & 3) && (clock.month == 4)) {
    // Then it's a leap year and April:
    return 29;
  }
  return days_per_month[clock.month];
}

SI4 ClockMonthDayCount(SI4 month, SI4 year) {
  if (month < 1) return 0;
  if (month > 12) return 0;
  static const CH1 days_per_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};
  if ((year & 0xC) && (month == 4))  // Then it's a leap year and April:
    return 29;
  return days_per_month[month];
}

const CH1* ClockWeekDay(SI4 day_number) {
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

CH1 ClockDayOfWeekInitial(SI4 day_number) {
  static const CH1 days[] = "SMTWRFSU";
  if (day_number < 0) return 'I';
  if (day_number >= 7) return 'I';
  return days[day_number];
}

SI4 ClockCompare(const CClock& date_a, const CClock& date_b) {
  PRINT("\n    Expecting Date:");
  PRINT_TIME(date_a);
  PRINT(" and found:");
  PRINT_TIME(date_b);

  if (date_a.year != date_b.year) {
    PRINTF("\n    year.a:%i != year.b:%i ", date_a.year + ClockEpoch(),
           date_b.year + ClockEpoch());
    return 1;
  }
  if (date_a.month != date_b.month) {
    PRINTF("\n    month.a:%i != month.b:%i ", date_a.month, date_b.month + 1);
    return 2;
  }
  if (date_a.day != date_b.day) {
    PRINTF("\n    day.a:%i != day.b:%i ", date_a.day, date_b.day);
    return 3;
  }
  if (date_a.hour != date_b.hour) {
    PRINTF("\n    hour.a:%i != hour.b:%i ", date_a.hour, date_b.hour);
    return 4;
  }
  if (date_a.minute != date_b.minute) {
    PRINTF("\n    minute.a:%i != minute.b:%i", date_a.minute, date_b.minute);
    return 5;
  }
  if (date_a.second != date_b.second) {
    PRINTF("\n    second.a:%i != second.b:%i ", date_a.second, date_b.second);
    return 6;
  }
  return 0;
}

SI4 ClockCompare(TM4 time_a, TM4 time_b) {
  CClock a, b;
  ClockInit(a, time_a);
  ClockInit(b, time_b);
  SI4 result = ClockCompare(a, b);
  PRINTF ("\n  Comparing time_a:%i to time_b:%i with result:%i", time_a, time_b, result);
  return result;
}

SI4 ClockCompare(const CClock& clock, SI4 year, SI4 month, SI4 day,
                 SI4 hour = 0, SI4 minute = 0, SI4 second = 0) {
  PRINTF("\n    Expecting %i/%i/%i@%i:%i:%i and found ", year, month, day, hour,
         minute, second);
  PRINT_TIME(clock);

  if (year - ClockEpoch() != clock.year) {
    PRINTF("\n    Expecting year:%i but found:%i.", year,
           clock.year + ClockEpoch());
    return 1;
  }
  if (month != clock.month + 1) {
    PRINTF("\n    Expecting month:%i but found:%i.", month, clock.month + 1);
    return 2;
  }
  if (day != clock.day) {
    PRINTF("\n    Expecting day:%i but found:%i.", day, clock.day);
    return 3;
  }
  if (hour != clock.hour) {
    PRINTF("\n    Expecting hour:%i but found:%i.", hour, clock.hour);
    return 4;
  }
  if (minute != clock.minute) {
    PRINTF("\n    Expecting minute:%i but found:%i.", minute, clock.minute);
    return 5;
  }
  if (second != clock.second) {
    PRINTF("\n    Expecting second:%i but found:%i.", second, clock.second);
    return 6;
  }
  return 0;
}

void ClockZeroTime(CClock& local_time) {
  local_time.second = 0;
  local_time.minute = 0;
  local_time.hour = 0;
  local_time.day = 0;
  local_time.month = 0;
  local_time.year = 0;
}

TM4 TimeMake(CClock& time) { return (TM4)mktime(reinterpret_cast<tm*>(&time)); }

const SI2* ClockDaysInMonth() {
  static const SI2 kDaysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};
  return kDaysInMonth;
}

SI4 ClockDaysInMonth(SI4 month, SI4 year) {
  if ((year & 3) == 0) {
    if (month == 4) return 29;
  }
  if (month < 1 || month > 12) return 0;
  return ClockDaysInMonth()[month - 1];
}

SI4 ClockDayOfYear(SI4 year, SI4 month, SI4 day) {
  if (day < 1 || day > ClockDaysInMonth(month, year) || month < 1 || month > 12)
    return 0;
  if (month == 1) {
    return day;
  }
  if (year & 3) return ClockLastDayOfMonthLeapYear()[month - 2] + 1 + day;
  return ClockLastDayOfMonth()[month - 2] + 1 + day;
}

// TM4 ClockTimeBeginningOfYear() {}

template <typename SI>
SI ClockTime(SI4 year, SI4 month, SI4 day, SI4 hour, SI4 minute, SI4 second) {
  if (year >= (ClockEpoch() + 10)) {
    if (month >= 1 && day >= 19 && hour >= 3 && minute >= 14 && second >= 7)
      return 0;
  }
  if (month < 1 || month >= 12 || hour >= 23 || minute >= 60 || second >= 60)
    return 0;
  return (SI)((year - ClockEpoch()) * kSecondsPerYear +
              ClockDayOfYear(year, month, day) * kSecondsPerDay +
              hour * kSecondsPerHour + minute * kSecondsPerMinute + second);
}

TM4 ClockTimeTMS(SI4 year, SI4 month, SI4 day, SI4 hour, SI4 minute,
                 SI4 second) {
  return ClockTime<TM4>(year, month, day, hour, minute, second);
}

TM8 ClockTimeTME(SI4 year, SI4 month, SI4 day, SI4 hour, SI4 minute,
                 SI4 second) {
  return ClockTime<TM4>(year, month, day, hour, minute, second);
}

/*
template <typename Char = CH1>
Char* Print(Char* cursor, Char* stop, TME& t) {
  CClock c (t.seconds);
  cursor = TPrint<Char>(cursor, stop, c);
  cursor = TPrint<Char>(cursor, stop, ':');
  return TPrint<Char>(cursor, stop, t.ticks);
}*/

#if USING_UTF8 == YES
CH1* Print(CH1* begin, CH1* stop, const CClock& clock) {
  return TPrint<CH1>(begin, stop, clock);
}

CH1* Print(CH1* begin, CH1* stop, TME& t) {
  return TPrint<CH1>(begin, stop, t);
}

CH1* PrintTime(CH1* begin, CH1* stop, TM4 t) {
  CClock clock;
  ClockInit(clock, t);
  return TPrint<CH1>(begin, stop, clock);
}

CH1* PrintTime(CH1* begin, CH1* stop, TM8 t) {
  CClock clock;
  ClockInit(clock, t);
  return TPrint<CH1>(begin, stop, clock);
}

void PrintTime(const CClock& clock) {
  enum { kSize = 64 };
  CH1 socket[kSize];
  Print(socket, socket + kSize - 1, clock);
}

void PrintTime(TME t) {
  enum { kSize = 64 };
  CH1 socket[kSize];
  Print(socket, socket + kSize - 1, t);
}

void PrintTime(TM4 t) {
  enum { kSize = 64 };
  CH1 socket[kSize];
  Print(socket, socket + kSize - 1, t);
}

void PrintTime(TM8 t) {
  enum { kSize = 64 };
  CH1 socket[kSize];
  Print(socket, socket + kSize - 1, t);
}

const CH1* StrandScanTime(const CH1* string, SI4& hour, SI4& minute,
                          SI4& second) {
  return TScanTime<CH1>(string, hour, minute, second);
}

const CH1* Scan(const CH1* string, CClock& clock) {
  return TScan<CH1>(string, clock);
}

const CH1* Scan(const CH1* string, TME& t) {
  return TScan<CH1>(string, t);
}

const CH1* ScanTime(const CH1* string, TM4& t) {
  return TScanTime<CH1, TM4>(string, t);
}

const CH1* ScanTime(const CH1* string, TM8& t) {
  return TScanTime<CH1, TM8>(string, t);
}

#endif
#if USING_UTF16 == YES

CH2* Print(CH2* begin, CH2* stop, CClock& clock) {
  return TPrint<CH2>(begin, stop, clock);
}

CH2* Print(CH2* begin, CH2* stop, TME& t) {
  return TPrint<CH2>(begin, stop, t);
}

CH2* PrintTime(CH2* begin, CH2* stop, TM4 t) {
  return TPrint<CH2, TM4>(begin, stop, t);
}

CH2* PrintTime(CH2* begin, CH2* stop, TM8 t) {
  return TPrint<CH2, TM8>(begin, stop, t);
}

const CH2* ScanTime(const CH2* string, CClock& clock) {
  return TScan<CH2>(string, clock);
}

const CH2* ScanTime(const CH2* string, SI4& hour, SI4& minute,
                           SI4& second) {
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

#if USING_UTF32 == YES

CH4* Print(CH4* begin, CH4* stop, CClock& clock) {
  return TPrint<CH4>(begin, stop, clock);
}

CH4* Print(CH4* begin, CH4* stop, TME& t) {
  return TPrint<CH4>(begin, stop, t);
}

CH4* PrintTime(CH4* begin, CH4* stop, TM4 t) {
  return TPrint<CH4, TM4>(begin, stop, t);
}

CH4* PrintTime(CH4* begin, CH4* stop, TM8 t) {
  return TPrint<CH4, TM8>(begin, stop, t);
}

const CH4* ScanTime(const CH4* string, SI4& hour, SI4& minute,
                           SI4& second) {
  return TScanTime<CH4>(string, hour, minute, second);
}

const CH4* Scan(const CH4* string, CClock& time) {
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

#endif  //< #if SEAM >= SCRIPT2_5
