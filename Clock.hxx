// Copyright Kabuki Starship <kabukistarship.com>.
#include "Clock.hpp"
#if SEAM >= SCRIPT2_CLOCK
//
#include <ctime>
#include "Uniprinter.hpp"
#if SEAM == SCRIPT2_CLOCK
#include "_Debug.hxx"
#else
#include "_Release.hxx"
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

ISB ClockEpoch() { return AClockEpochInit; }

AClock* ClockInit(AClock& clock, ISC t) { return TClockInit<ISC>(clock, t); }

AClock* ClockInit(AClock& clock, ISD t) { return TClockInit<ISD>(clock, t); }

TMD& StopwatchInit(TMD& tss, ISC t, IUC ticks) {
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

ISD ClockNow() {
  time_t t;
  time(&t);
  if (t > SecondsPerEpoch) ClockEpochUpdate();
  return ISD(t);
}

ISC ClockSeconds(AClock& clock) {
  return (clock.year - AClockEpochInit) * SecondsPerYear +
         (clock.day - 1) * cSecondsPerDay + clock.hour * SecondsPerHour +
         clock.minute * SecondsPerMinute + clock.second;
}

ISC ClockISC(AClock& clock) { return ClockSeconds(clock); }

ISD ClockISD(AClock& clock) { return ISD(ClockSeconds(clock)); }

ISN ClockMonthDayCount(ISC t) {
  TClock<ISC> date(t);
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

ISN ClockCompare(ISC time_a, ISC time_b) {
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

ISC TimeMake(AClock& time) { return (ISC)mktime(TPtr<tm>(&time)); }

const ISB* ClockDaysInMonth() {
  static const ISB cDaysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};
  return cDaysInMonth;
}

ISN ClockDaysInMonth(ISN month, ISN year) {
  if ((year & 3) == 0) {
    if (month == 4) return 29;
  }
  if (month < 1 || month > 12) return 0;
  return ClockDaysInMonth()[month - 1];
}

ISN ClockDayOfYear(ISN year, ISN month, ISN day) {
  if (day < 1 || day > ClockDaysInMonth(month, year) || month < 1 || month > 12)
    return 0;
  if (month == 1) {
    return day;
  }
  if (year & 3) return ClockLastDayOfMonthLeapYear()[month - 2] + 1 + day;
  return ClockLastDayOfMonth()[month - 2] + 1 + day;
}

ISC ClockTimeTMS(ISN year, ISN month, ISN day, ISN hour, ISN minute,
                 ISN second) {
  return TClockTime<ISC>(year, month, day, hour, minute, second);
}

ISD ClockTimeTME(ISN year, ISN month, ISN day, ISN hour, ISN minute,
                 ISN second) {
  return TClockTime<ISC>(year, month, day, hour, minute, second);
}

#if USING_UTF8 == YES_0
CHA* SPrint(CHA* origin, CHA* stop, const AClock& clock) {
  return TSPrint<CHA>(origin, stop, clock);
}

CHA* SPrint(CHA* origin, CHA* stop, const TMD& t) {
  return TSPrint<CHA>(origin, stop, t);
}

CHA* ClockPrint(CHA* origin, CHA* stop, ISC t) {
  AClock clock;
  ClockInit(clock, t);
  return TSPrint<CHA>(origin, stop, clock);
}

CHA* ClockPrint(CHA* origin, CHA* stop, ISD t) {
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

const CHA* SScan(const CHA* string, TMD& t) { return TSScan<CHA>(string, t); }

const CHA* ScanTime(const CHA* string, ISC& t) {
  return TScanTime<CHA, ISC>(string, t);
}

const CHA* ScanTime(const CHA* string, ISD& t) {
  return TScanTime<CHA, ISD>(string, t);
}

#endif
#if USING_UTF16 == YES_0

CHB* SPrint(CHB* origin, CHB* stop, const AClock& clock) {
  return TSPrint<CHB>(origin, stop, clock);
}

CHB* SPrint(CHB* origin, CHB* stop, const TMD& t) {
  return TSPrint<CHB>(origin, stop, t);
}

CHB* ClockPrint(CHB* origin, CHB* stop, ISC t) {
  return TClockPrint<CHB, ISC>(origin, stop, t);
}

CHB* ClockPrint(CHB* origin, CHB* stop, ISD t) {
  return TClockPrint<CHB, ISD>(origin, stop, t);
}

CHC* SPrint(CHC* origin, CHC* stop, const AClock& clock) {
  return TSPrint<CHC>(origin, stop, clock);
}

CHC* SPrint(CHC* origin, CHC* stop, const TMD& t) {
  return TSPrint<CHC>(origin, stop, t);
}

CHC* ClockPrint(CHC* origin, CHC* stop, ISC t) {
  return TClockPrint<CHC, ISC>(origin, stop, t);
}

CHC* ClockPrint(CHC* origin, CHC* stop, ISD t) {
  return TClockPrint<CHC, ISD>(origin, stop, t);
}

const CHB* SScan(const CHB* string, AClock& clock) {
  return TSScan<CHB>(string, clock);
}

const CHB* SScan(const CHB* string, TMD& result) {
  return TSScan<CHB>(string, result);
}

const CHB* ScanTime(const CHB* string, ISN& hour, ISN& minute, ISN& second) {
  return TScanTime<CHB>(string, hour, minute, second);
}

const CHB* ScanTime(const CHB* string, ISC& result) {
  return TScanTime<CHB, ISC>(string, result);
}

const CHB* ScanTime(const CHB* string, ISD& result) {
  return TScanTime<CHB, ISD>(string, result);
}
#endif

#if USING_UTF32 == YES_0

CHC* SPrint(CHC* origin, CHC* stop, AClock& clock) {
  return TSPrint<CHC>(origin, stop, clock);
}

CHC* SPrint(CHC* origin, CHC* stop, ISC& t) {
  return TSPrint<CHC>(origin, stop, t);
}

const CHC* ScanTime(const CHC* string, ISN& hour, ISN& minute, ISN& second) {
  return TScanTime<CHC>(string, hour, minute, second);
}

const CHC* SScan(const CHC* string, AClock& time) {
  return TSScan<CHC>(string, time);
}

const CHC* SScan(const CHC* string, TMD& result) {
  return TSScan<CHC>(string, result);
}

const CHC* ScanTime(const CHC* string, ISC& result) {
  return TScanTime<CHC, ISC>(string, result);
}

const CHC* ScanTime(const CHC* string, ISD& result) {
  return TScanTime<CHC, ISD>(string, result);
}

#endif

}  //< namespace _

#endif  //< #if SEAM >= SCRIPT2_CLOCK
