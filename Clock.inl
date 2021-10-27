/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Clock.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CLOCK
#include "Clock.hpp"
//
#include <ctime>
#include "Stringf.hpp"
#if SEAM == SCRIPT2_CLOCK
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
using namespace _;
namespace _ {

const ISB* ClockLastDayOfMonth() {
  static const ISB kMonthDayOfYear[12] = {31,  59,  90,  120, 151, 181,
                                          212, 243, 273, 304, 334, 365};
  return kMonthDayOfYear;
}

const ISB* ClockLastDayOfMonthLeapYear() {
  static const ISB kMonthDayOfYearLeapYear[12] = {31,  60,  91,  121, 152, 182,
                                                  213, 244, 274, 305, 335, 366};
  return kMonthDayOfYearLeapYear;
}

ISN MonthByDay(ISN day, ISN year) {
  const ISB *cursor, *stop;
  if (day < 1) return 0;
  if (year & 3) {  // 3 = 0b'11 which is a much faster way to do modulo 4.
    cursor = ClockLastDayOfMonthLeapYear();
  } else {
    cursor = ClockLastDayOfMonth();
  }
  stop = cursor + 11;
  while (cursor <= stop)
    if (day < *cursor++) return (ISN)(stop - cursor);
  return 0;
}

ISB ClockEpoch() { return cClockEpochInit; }

AClock* ClockInit(AClock& clock, TMC t) { return TClockInit<TMC>(clock, t); }

AClock* ClockInit(AClock& clock, TMD t) { return TClockInit<TMD>(clock, t); }

TME& StopwatchInit(TME& tss, TMC t, IUC ticks) {
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
  // cClockEpochInit += 10;
  // RoomUnlock();
}

TMD ClockNow() {
  time_t t;
  time(&t);
  if (t > cSecondsPerEpoch) ClockEpochUpdate();
  return (TMD)t;
}

TMC ClockSeconds(AClock& clock) {
  return (clock.year - cClockEpochInit) * cSecondsPerYear +
         (clock.day - 1) * cSecondsPerDay + clock.hour * cSecondsPerHour +
         clock.minute * cSecondsPerMinute + clock.second;
}

TMC ClockTMC(AClock& clock) { return ClockSeconds(clock); }

TMD ClockTMD(AClock& clock) { return (TMD)ClockSeconds(clock); }

ISN ClockMonthDayCount(TMC t) {
  TClock<TMC> date(t);
  static const CHA days_per_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};
  AClock& clock = date.clock;
  if ((clock.year & 3) && (clock.month == 4)) {
    // Then it's a leap year and April:
    return 29;
  }
  return days_per_month[clock.month];
}

ISN ClockMonthDayCount(ISN month, ISN year) {
  if (month < 1) return 0;
  if (month > 12) return 0;
  static const CHA days_per_month[12] = {31, 28, 31, 30, 31, 30,
                                         31, 31, 30, 31, 30, 31};
  if ((year & 0xC) && (month == 4))  // Then it's a leap year and April:
    return 29;
  return days_per_month[month];
}

const CHA* ClockWeekDay(ISN day_number) {
  static const CHA* days[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday", "Saturday"};
  static const CHA cInvalidText[] = "Invalid\0";
  if (day_number < 0) {
    return cInvalidText;
  }
  if (day_number >= 7) {
    return cInvalidText;
  }
  return days[day_number];
}

CHA ClockDayOfWeekInitial(ISN day_number) {
  static const CHA days[] = "SMTWRFSU";
  if (day_number < 0) return 'I';
  if (day_number >= 7) return 'I';
  return days[day_number];
}

ISN ClockCompare(const AClock& date_a, const AClock& date_b) {
  D_COUT("\n    Expecting Date:" << date_a << " and found:" << date_b);

  if (date_a.year != date_b.year) {
    D_COUT("\n    year.a:" << date_a.year + ClockEpoch()
                           << " != year.b:" << date_b.year + ClockEpoch());
    return 1;
  }
  if (date_a.month != date_b.month) {
    D_COUT("\n    month.a:" << date_a.month
                            << " != month.b:" << date_b.month + 1 << " ");
    return 2;
  }
  if (date_a.day != date_b.day) {
    D_COUT("\n    day.a:" << date_a.day << " != day.b:" << date_b.day << " ");
    return 3;
  }
  if (date_a.hour != date_b.hour) {
    D_COUT("\n    hour.a:" << date_a.hour << " != hour.b:" << date_b.hour
                           << " ");
    return 4;
  }
  if (date_a.minute != date_b.minute) {
    D_COUT("\n    minute.a:" << date_a.minute
                             << " != minute.b:" << date_b.minute);
    return 5;
  }
  if (date_a.second != date_b.second) {
    D_COUT("\n    second.a:" << date_a.second
                             << " != second.b:" << date_b.second);
    return 6;
  }
  return 0;
}

ISN ClockCompare(TMC time_a, TMC time_b) {
  AClock a, b;
  ClockInit(a, time_a);
  ClockInit(b, time_b);
  ISN result = ClockCompare(a, b);
  D_COUT("\n  Comparing time_a:" << time_a << " to time_b:" << time_b
                                 << " with result:" << result);
  return result;
}

ISN ClockCompare(const AClock& clock, ISN year, ISN month, ISN day,
                 ISN hour = 0, ISN minute = 0, ISN second = 0) {
  D_COUT("\n    Expecting " << year << '/"' << month << '/"' << day << '@'
                            << hour << ':' << minute << ':' << second
                            << " and found " << clock);

  if (year - ClockEpoch() != clock.year) {
    D_COUT("\n    Expecting year:" << year << " but found:"
                                   << clock.year + ClockEpoch() << '.');
    return 1;
  }
  if (month != clock.month + 1) {
    D_COUT("\n    Expecting month:" << month << " but found:" << clock.month + 1
                                    << '.');
    return 2;
  }
  if (day != clock.day) {
    D_COUT("\n    Expecting day:" << day << " but found:" << clock.day << '.');
    return 3;
  }
  if (hour != clock.hour) {
    D_COUT("\n    Expecting hour:" << hour << " but found:" << clock.hour
                                   << '.');
    return 4;
  }
  if (minute != clock.minute) {
    D_COUT("\n    Expecting minute:" << minute << " but found:" << clock.minute
                                     << '.');
    return 5;
  }
  if (second != clock.second) {
    D_COUT("\n    Expecting second:" << second << " but found:" << clock.second
                                     << '.');
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

TMC TimeMake(AClock& time) { return (TMC)mktime(reinterpret_cast<tm*>(&time)); }

const ISB* CloccDaysInMonth() {
  static const ISB cDaysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};
  return cDaysInMonth;
}

ISN CloccDaysInMonth(ISN month, ISN year) {
  if ((year & 3) == 0) {
    if (month == 4) return 29;
  }
  if (month < 1 || month > 12) return 0;
  return CloccDaysInMonth()[month - 1];
}

ISN ClockDayOfYear(ISN year, ISN month, ISN day) {
  if (day < 1 || day > CloccDaysInMonth(month, year) || month < 1 || month > 12)
    return 0;
  if (month == 1) {
    return day;
  }
  if (year & 3) return ClockLastDayOfMonthLeapYear()[month - 2] + 1 + day;
  return ClockLastDayOfMonth()[month - 2] + 1 + day;
}

TMC ClockTimeTMS(ISN year, ISN month, ISN day, ISN hour, ISN minute,
                 ISN second) {
  return TClockTime<TMC>(year, month, day, hour, minute, second);
}

TMD ClockTimeTME(ISN year, ISN month, ISN day, ISN hour, ISN minute,
                 ISN second) {
  return TClockTime<TMC>(year, month, day, hour, minute, second);
}

#if USING_UTF8 == YES_0
CHA* SPrint(CHA* origin, CHA* stop, const AClock& clock) {
  return TSPrint<CHA>(origin, stop, clock);
}

CHA* Print(CHA* origin, CHA* stop, TMC& t) {
  return TSPrint<CHA>(origin, stop, t);
}

CHA* ClockPrint(CHA* origin, CHA* stop, TMC t) {
  AClock clock;
  ClockInit(clock, t);
  return TSPrint<CHA>(origin, stop, clock);
}

CHA* ClockPrint(CHA* origin, CHA* stop, TMD t) {
  AClock clock;
  ClockInit(clock, t);
  return TSPrint<CHA>(origin, stop, clock);
}

const CHA* ScanTime(const CHA* string, ISN& hour, ISN& minute, ISN& second) {
  return TScanTime<CHA>(string, hour, minute, second);
}

const CHA* SScan(const CHA* string, AClock& clock) {
  return TSScan<CHA>(string, clock);
}

const CHA* SScan(const CHA* string, TMC& t) { return TSScan<CHA>(string, t); }

const CHA* ScanTime(const CHA* string, TMC& t) {
  return TScanTime<CHA, TMC>(string, t);
}

const CHA* ScanTime(const CHA* string, TMD& t) {
  return TScanTime<CHA, TMD>(string, t);
}

#endif
#if USING_UTF16 == YES_0

CHB* SPrint(CHB* origin, CHB* stop, AClock& clock) {
  return TSPrint<CHB>(origin, stop, clock);
}

CHB* SPrint(CHB* origin, CHB* stop, TMC& t) {
  return TSPrint<CHB>(origin, stop, t);
}

CHB* ClockPrint(CHB* origin, CHB* stop, TMC t) {
  return TClockPrint<CHB, TMC>(origin, stop, t);
}

CHB* ClockPrint(CHB* origin, CHB* stop, TMD t) {
  return TClockPrint<CHB, TMD>(origin, stop, t);
}

const CHB* SScan(const CHB* string, AClock& clock) {
  return TSScan<CHB>(string, clock);
}

const CHB* ScanTime(const CHB* string, ISN& hour, ISN& minute, ISN& second) {
  return TScanTime<CHB>(string, hour, minute, second);
}

const CHB* SScan(const CHB* string, TMC& result) {
  return TSScan<CHB>(string, result);
}

const CHB* ScanTime(const CHB* string, TMC& result) {
  return TScanTime<CHB, TMC>(string, result);
}

const CHB* ScanTime(const CHB* string, TMD& result) {
  return TScanTime<CHB, TMD>(string, result);
}
#endif

#if USING_UTF32 == YES_0

CHC* SPrint(CHC* origin, CHC* stop, AClock& clock) {
  return TSPrint<CHC>(origin, stop, clock);
}

CHC* SPrint(CHC* origin, CHC* stop, TMC& t) {
  return TSPrint<CHC>(origin, stop, t);
}

CHC* ClockPrint(CHC* origin, CHC* stop, TMC t) {
  return TClockPrint<CHC, TMC>(origin, stop, t);
}

CHC* ClockPrint(CHC* origin, CHC* stop, TMD t) {
  return TClockPrint<CHC, TMD>(origin, stop, t);
}

const CHC* ScanTime(const CHC* string, ISN& hour, ISN& minute, ISN& second) {
  return TScanTime<CHC>(string, hour, minute, second);
}

const CHC* SScan(const CHC* string, AClock& time) {
  return TSScan<CHC>(string, time);
}

const CHC* SScan(const CHC* string, TMC& result) {
  return TSScan<CHC>(string, result);
}

const CHC* ScanTime(const CHC* string, TMC& result) {
  return TScanTime<CHC, TMC>(string, result);
}

const CHC* ScanTime(const CHC* string, TMD& result) {
  return TScanTime<CHC, TMD>(string, result);
}

#endif

}  //< namespace _

#endif  //< #if SEAM >= SCRIPT2_CLOCK
