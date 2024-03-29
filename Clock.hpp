/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Clock.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_CLOCK
#ifndef INCLUDED_SCRIPT2_CLOCK_TEMPLATES
#define INCLUDED_SCRIPT2_CLOCK_TEMPLATES
#include "Clock.h"
#include "Stringf.hpp"
#include "Test.h"
#if SEAM == SCRIPT2_CORE
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

template<typename IS>
AClock* TClockInit(AClock& clock, IS t) {
  // Algorithm:
  // 1. Using manual modulo convert in the following order:
  //   a. Year based on seconds per year.
  //   b. Day of year based on seconds per day.
  //   c. Month based on day of year and leap year.
  //   d. Hour.
  //   e. Minute.
  //   f. Second.
  ISN value = (ISN)(t / SecondsPerYear);
  t -= IS(value) * SecondsPerYear;
  clock.year = value + ClockEpoch();
  value = (ISN)(t / cSecondsPerDay);
  t -= IS(value) * cSecondsPerDay;
  clock.day = value;
  value = (ISN)(t / SecondsPerHour);
  t -= IS(value) * SecondsPerHour;
  clock.hour = value;
  value = (ISN)(t / SecondsPerMinute);
  clock.minute = value;
  clock.second = (ISN)(t - IS(value) * SecondsPerMinute);
  return &clock;
}

template<typename IS>
IS TClockTime(ISN year, ISN month, ISN day, ISN hour, ISN minute, ISN second) {
  if (year >= (ClockEpoch() + 10)) {
    if (month >= 1 && day >= 19 && hour >= 3 && minute >= 14 && second >= 7)
      return 0;
  }
  if (month < 1 || month >= 12 || hour >= 23 || minute >= 60 || second >= 60)
    return 0;
  return (IS)((year - ClockEpoch()) * SecondsPerYear +
              ClockDayOfYear(year, month, day) * cSecondsPerDay +
              hour * SecondsPerHour + minute * SecondsPerMinute + second);
}

/*
template<typename CHT = CHR>
CHT* Print(CHT* cursor, CHT* stop, TME& t) {
  AClock c (t.seconds);
  cursor = TSPrint<CHT>(cursor, stop, c);
  cursor = TSPrint<CHT>(cursor, stop, ':');
  return TSPrint<CHT>(cursor, stop, t.ticks);
}*/

#if USING_STR

template<typename CHT = CHR>
CHT* TSPrint(CHT* cursor, CHT* stop, const AClock& clock) {
  // The way the utf functions are setup, we return a nil-term CHA so we
  // don't have to check to write a single CHA in this
  A_ASSERT(cursor);
  A_ASSERT(cursor < stop);

  cursor = TSPrint<CHT>(cursor, stop, clock.year + ClockEpoch());
  if (!cursor) return nullptr;
  *cursor++ = '-';
  cursor = TSPrint<CHT>(cursor, stop, clock.month + 1);
  if (!cursor) return nullptr;
  *cursor++ = '-';
  cursor = TSPrint<CHT>(cursor, stop, clock.day);
  if (!cursor) return nullptr;
  *cursor++ = '@';
  cursor = TSPrint<CHT>(cursor, stop, clock.hour);
  if (!cursor) return nullptr;
  *cursor++ = ':';
  cursor = TSPrint<CHT>(cursor, stop, clock.minute);
  if (!cursor) return nullptr;
  *cursor++ = ':';
  cursor = TSPrint<CHT>(cursor, stop, clock.second);
  if (!cursor) return nullptr;
  return cursor;
}

template<typename Printer>
Printer& TSPrint(Printer& o, const _::AClock& clock) {
  return o << clock.year + ClockEpoch() << '-' << clock.month + 1 << '-'
           << clock.day << '@' << clock.hour << ':' << clock.minute << ':'
           << clock.second;
}

template<typename CHT = CHR, typename Time = TMD>
CHT* TClockPrint(CHT* cursor, CHT* stop, Time t) {
  AClock clock;
  ClockInit(clock, t);
  return TSPrint<CHT>(cursor, stop, clock);
}

template<typename CHT = CHR>
CHT* TSPrint(CHT* cursor, CHT* stop, TME& t) {
  // The way the utf functions are setup, we return a nil-term CHA so we
  // don't have to check to write a single CHA in this
  A_ASSERT(cursor);
  A_ASSERT(cursor < stop);

  AClock clock;
  ClockInit(clock, t.seconds);
  cursor = TSPrint<CHT>(cursor, stop, clock);
  *cursor++ = ':';
  cursor = TSPrint<CHT>(cursor, stop, t.ticks);
  if (!cursor) return nullptr;
  return cursor;
}

template<typename Printer>
Printer& TSPrint(Printer& o, TME& t) {
  AClock clock;
  ClockInit(clock, t.seconds);
  return TSPrint<Printer>(o, clock) << ':' << t.ticks;
}

/* Scans a time in seconds from the given string. */
template<typename CHT = CHR>
const CHT* TScanTime(const CHT* string, ISC& hour, ISC& minute, ISC& second) {
  if (string == nullptr) return nullptr;

  D_COUT("\n\n    Scanning time:\"" << string << '\"');
  CHT c;   //< The current CHT.
  ISC h,   //< Hour.
      m,   //< Minute.
      s;   //< Second.
  if (!TScanSigned<ISC, IUC, CHT>(++string, h)) {
    D_COUT("\nInvalid hour:" << h);
    return nullptr;
  }
  string = TSTRSkipNumbers<CHT>(string);
  if (h < 0) {
    D_COUT("\nHours:" << h << " can't be negative.");
    return nullptr;
  }
  if (h > 23) {
    D_COUT("\nHours:" << h << " can't be > 23.");
    return nullptr;
  }
  D_COUT(h);
  c = *string++;
  if (!c || TIsWhitespace<CHT>(c)) {  // Case @HH
    D_COUT(" HH ");
    // Then it's a single number_, so create a TMC for the current
    // user-time hour..
    hour = h;
    return string;
  }
  c = TToLower<CHT>(c);
  if (c == 'a') {  //
    D_COUT("\nCase @HHAm\n HHam ");

    if (TToLower<CHT>(c = *string++) == 'm') c = *string++;
    if (c && !TIsWhitespace<CHT>(c)) {
      D_COUT("\nInvalid am format.");
      return nullptr;
    }
    D_COUT(" @HHAM ");
    hour = h;
    return string;
  }
  if (c == 'p') {
    D_COUT(" Case @HHpm ");
    c = *string++;
    if (TToLower<CHT>(c) == 'm') c = *string++;
    if (c && !TIsWhitespace<CHT>(c)) {
      D_COUT("\ninvalid pm format.");
      return nullptr;
    }
    D_COUT("\nCase @HHPM " << h + 12 << ":00:00");
    hour = h + 12;
    return string;
  }
  if (c != ':') {
    D_COUT("\nExpecting ':'.");
    return nullptr;
  }

  D_COUT(
      "\nCases HH:MM, HH::MMam, HH::MMpm, HH:MM:SS, HH:MM:SSam, and "
      "HH:MM:SSpm");

  if (!TScanSigned<ISC, IUC, CHT>(string, m)) return nullptr;
  string = TSTRSkipNumbers<CHT>(string);
  if (m < 0) {
    D_COUT("\nMinutes:" << m << " can't be negative!");
    return nullptr;
  }
  if (m >= 60) {
    D_COUT("\nMinutes:" << m << " can't be >= 60!");
    return nullptr;  //< 60 minutes in an hour.
  }
  D_COUT(':' << m);

  string = TSTRSkipNumbers<CHT>(string);
  c = *string++;
  if (!c || TIsWhitespace<CHT>(c)) {
    D_COUT(" HH:MM ");
    hour = h;
    minute = m;
    return string;
  }
  c = TToLower<CHT>(c);
  if (c == 'a') {
    D_COUT(" HH:MMam ");
    c = *string++;
    if (TToLower<CHT>(c) == 'm') {  // The 'm' is optional.
      c = *string++;
    }
    if (c && !TIsWhitespace<CHT>(c)) {  // The space is not.
      D_COUT("Invalid am in HH::MM AM");
      return nullptr;
    }
    hour = h;
    minute = m;
    return string;
  }
  if (c == 'p') {  //< Case HH:MM PM
    D_COUT(" HH:MMpm ");
    c = *string++;
    if (TToLower<CHT>(c) == 'm') {  //< The 'm' is optional.
      c = *string++;
    }
    if (c && !TIsWhitespace<CHT>(c)) {  //< The space is not.
      D_COUT("Invalid am in HH::MM PM");
      return nullptr;
    }
    hour = h + 12;
    minute = m;
    return string;
  }
  if (c != ':') return nullptr;

  D_COUT("\n    Cases HH:MM:SS, HH:MM:SSam, and HH:MM:SSpm");

  if (!TScanSigned<ISC, IUC, CHT>(string, s)) return nullptr;
  if (s < 0) {
    D_COUT("\nSeconds:" << s << " can't be negative!");
    return nullptr;
  }
  if (s > 60) {
    D_COUT("\nSeconds:" << s << " can't be >= 60!");
    return nullptr;
  }
  D_COUT(':' << s);
  string = TSTRSkipNumbers<CHT>(string);
  c = TToLower<CHT>(*string);
  if (!c || TIsWhitespace<CHT>(c)) {
    D_COUT(" HH:MM:SS ");
    hour = h;
    minute = m;
    second = s;
    return string;
  }
  if (c == 'a') {
    D_COUT(" HH:MM:SSam ");
    c = *string++;
    if (TToLower<CHT>(c) == 'm') {  //< The 'm' is optional.
      c = *string++;
    }
    if (!c || !TIsWhitespace<CHT>(c)) {  //< The space is not.
      D_COUT("\nInvalid am in HH::MM:SS AM");
      return nullptr;
    }
    hour = h;
    minute = m;
    second = s;
    return string;
  }
  if (c != 'p') {
    D_COUT("\nExpecting a PM but found:" << c);
    return nullptr;  // Format error!
  }
  D_COUT(" HH:MM:SSpm ");
  c = TToLower<CHT>(*string++);
  if (c == 'm') {  //< The 'm' is optional.
    c = *string++;
  }
  if (!c || !TIsWhitespace<CHT>(c)) {  //< The space is not.
    D_COUT("\nInvalid am in HH::MM:SS PM");
    return nullptr;
  }
  hour = h + 12;
  minute = m;
  second = s;
  return string;
}

/* Scans the given string for a timestamp. */
template<typename CHT = CHR>
const CHT* TSScan(const CHT* string, AClock& clock) {
  D_ASSERT(string);
  D_COUT("\n    Scanning AClock:\"" << string << "\n    Scanning: ");

  string = TSTRSkimodulear<CHT>(string, '0');
  CHT c = *string,  //< The current CHT.
      delimiter;     //< The delimiter.
  const CHT* stop;  //< Might not need

  ISC hour = 0, minute = 0, second = 0;

  if (c == '@') {
    if (!(string = TScanTime<CHT>(string, hour, minute, second))) {
      D_COUT("\nCase @ invalid time");
      return nullptr;
    }
    clock.hour = hour;
    clock.minute = minute;
    clock.second = second;

    return string + 1;
  }
  if (c == '#') {
    if (!(string = TScanTime<CHT>(string, hour, minute, second))) {
      D_COUT("\nCase @ invalid time");
    }
    clock.hour += hour;
    clock.minute += minute;
    clock.second += second;

    return string + 1;
  }

  ISC value1,            //< The first date field scanned.
      value2,            //< The second date field scanned.
      value3,            //< The third date field scanned.
      is_last_year = 0;  //< Flag for if the date was last year or not.

  // SScan value1
  if (!TScanSigned<ISC, IUC, CHT>(string, value1)) {
    D_COUT("SScan error at value1");
    return nullptr;
  }
  if (value1 < 0) {
    D_COUT("Dates can't be negative.");
    return nullptr;
  }
  string = TSTRDecimalEnd<CHT>(string);
  if (!string) return nullptr;
  delimiter = *string++;
  D_COUT(value1);
  if (delimiter == '@') {
    D_COUT(" HH@ ");

    if (!(string = TScanTime<CHT>(string, hour, minute, second))) {
      D_COUT("\nInvalid time DD@");
      return nullptr;
    }
    clock.day = value1;

    return string + 1;
  }
  // SScan value2.
  string = TSTRSkimodulear<CHT>(string, '0');
  if (!TScanSigned<ISC, IUC, CHT>(string, value2)) {
    D_COUT("\n    Failed scanning value2 of date.");
    return nullptr;
  }
  if (value2 < 0) {
    D_COUT("Day can't be negative.");
    return nullptr;  //< Invalid month and day.
  }
  D_COUT(value2);
  string = TSTRDecimalEnd<CHT>(string);
  c = *string;
  if (c != delimiter) {
    D_COUT("\n    Cases MM/DD and MM/YYyy");
    if (c == '@') {
      if (!(string = TScanTime<CHT>(string, hour, minute, second))) {
        D_COUT(" invalid time ");
        return nullptr;
      }
    }
    if (!c || TIsWhitespace<CHT>(c)) {
      D_COUT("\n    Format is MM/DD and year is " << clock.year + ClockEpoch());
      // is_last_year = ((value1 >= std_tm.mon) &&
      //    (value2 >= std_tm.mday)) ? 0:1;
      clock.year += is_last_year;
      clock.month = value1 - 1;
      clock.day = value2;
      clock.hour = 0;
      clock.hour = hour;
      clock.minute = minute;
      clock.second = second;

      return string + 1;
    }
    c = TToLower<CHT>(c);
    if ((value1 < 12) && (value2 > 0) &&
        (value2 <= ClockMonthDayCount(value1))) {
      D_COUT(" MM/DD ");
      if (value1 > 11) {
        D_COUT("\nInvalid MM/DD@ month");
        return nullptr;
      }
      // We need to find out what year it is.
      AClock clock;
      ClockInit(clock);

      if (value2 > ClockMonthDayCount(clock.year - ClockEpoch(), value1)) {
        D_COUT("\nInvalid MM/DD@ day");
        return nullptr;
      }
      clock.month = value1 - 1;
      clock.day = value2;
      clock.hour = hour;
      clock.minute = minute;
      clock.second = second;
      if (!(string = TScanTime(string, hour, minute, second))) {
        D_COUT("\nInvalid MM/DD@");
        return nullptr;
      }

      return string + 1;
    }
    if ((value1 < 12) && (value2 > ClockMonthDayCount(value1))) {
      D_COUT(" MM/YYyy");
      clock.month = value1 - 1;
      clock.year = value2;
      if (!(string = TScanTime<CHT>(string, hour, minute, second))) {
        D_COUT("\nInvalid MM / YYYY@ time");
        return nullptr;
      }

      return string + 1;
    }
    D_COUT("\nInvalid MM/DD or MM/YYyy format");
    return nullptr;
  }

  // Formats MM/DD/YYyy and YYyy/MM/DD

  string = TSTRSkimodulear<CHT>(++string, '0');
  c = *string;
  // Then there are 3 values and 2 delimiters.
  if (!TIsDigit<CHT>(c) || !TScanSigned<ISC, IUC, CHT>(string, value3)) {
    D_COUT("\n    SlotRead error reading value3 of date." << CHT(c) << ": ");
    return nullptr;  //< Invalid format!
  }
  string = TSTRDecimalEnd<CHT>(string);
  D_COUT(c << value3);
  // Now we need to check what format it is in.

  c = *string;
  if (c == '@') {
    if (!(stop = TScanTime<CHT>(string, hour, minute, second))) {
      D_COUT("Invalid YYyy/MM/DD@ time.");
      return nullptr;
    }
  }
  clock.hour = hour;
  clock.minute = minute;
  clock.second = second;
  if (TIsWhitespace<CHT>(*(++string))) {
    D_COUT("No date found.");
    return nullptr;
  }
  if (value1 > 11) {  //<
    D_COUT("\n    Case YYyy/MM/DD");
    if (value2 == 0 || value2 > 12) {
      D_COUT("Invalid number of months");
      return nullptr;
    }

    if (value2 > ClockMonthDayCount(value2, value1)) {
      D_COUT("Invalid number of days");
      return nullptr;
    }  // 17/05/06

    if (value1 < 100) {
      D_COUT("\n    Case YY/MM/DD");
      value1 += 2000 - ClockEpoch();
    } else {
      D_COUT("\n    Case YYYY/MM/DD");
      value1 -= ClockEpoch();
    }

    clock.year = value1;
    clock.month = value2 - 1;
    clock.day = value3;

    return string + 1;
  }
  D_COUT("\n    Cases MM/DD/YY and MM/DD/YYYY");

  if (value1 > 11) {
    D_COUT("\nInvalid month.");
    return nullptr;
  }
  if (value2 > ClockMonthDayCount(value1, value3)) {
    D_COUT("\nInvalid day.");
    return nullptr;
  }
  clock.month = value1 - 1;
  clock.day = value2;
  if (value3 < 100) {
    D_COUT("\n    Case MM/DD/YY");
    clock.year = value3 + (2000 - ClockEpoch());
  } else {
    D_COUT("\n    Case MM/DD/YYYY");
    clock.year = value3 - ClockEpoch();
  }
  return string + 1;
}

template<typename CHT, typename IS>
const CHT* TScanTime(const CHT* origin, TMC& result) {
  AClock clock;
  const CHT* stop = TSScan<CHT>(origin, clock);
  result = (TMC)ClockSeconds(clock);
  return stop;
}

template<typename CHT, typename IS>
const CHT* TScanTime(const CHT* origin, TMD& result) {
  AClock clock;
  const CHT* stop = TSScan<CHT>(origin, clock);
  result = (TMD)ClockSeconds(clock);
  return stop;
}

template<typename CHT>
const CHT* TSScan(const CHT* origin, TME& result) {
  origin = TScanTime<CHT, TMC>(origin, result.seconds);
  if (!origin) return nullptr;
  if (*origin++ != ':') {
    result.ticks = 0;
    return origin - 1;
  }
  return TScanUnsigned<IUC, CHT>(origin, result.ticks);
}
#endif  // #if USING_STR

template<typename IS>
IS TClockSet(AClock* clock, IS t) {
  // Algorithm:
  // 1. Using manual modulo convert in the following order:
  //   a. Year based on seconds per year.
  //   b. Day of year based on seconds per day.
  //   c. Month based on day of year and leap year.
  //   d. Hour.
  //   e. Minute.
  //   f. Second.
  IS value = t / SecondsPerYear;
  t -= value * SecondsPerYear;
  clock->year = (ISC)(value + ClockEpoch());
  value = t / cSecondsPerDay;
  t -= value * cSecondsPerDay;
  clock->day = (ISC)value;
  value = t / SecondsPerHour;
  t -= value * SecondsPerHour;
  clock->hour = (ISC)value;
  value = t / SecondsPerMinute;
  clock->minute = (ISC)value;
  clock->second = (ISC)(t - value * SecondsPerMinute);
  return t;
}

/* A time in seconds stored as either a 32-bit or 64-bit IS.
The difference between a TClock and AClock is that that TClock stores the AClock
and the TMD or TMC. */
template<typename IS>
struct LIB_MEMBER TClock {
  AClock clock;  //< A human-readable clock.

  /* Constructs a clock from the given seconds timestamp. */
  TClock(IS t) { ClockInit(clock, t); }

  /* Prints the given */
  template<typename Printer, typename IS>
  Printer& Print(Printer& o) {
    return o << clock.Clock();
  }
};

}  //< namespace _
#if USING_CONSOLE == YES_0

inline _::COut& operator<<(_::COut& o, const _::AClock& item) {
  return _::TSPrint(o, item);
}

template<typename IS>
_::COut& operator<<(_::COut& o, _::TClock<IS> item) {
  return o << item.clock;
}
#endif

#endif
#endif
