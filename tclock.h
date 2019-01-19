/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /clock.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-8 Cale McCollough <calemccollough@gmail.com>;
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= _0_0_0__05
#ifndef INCLUDED_SCRIPT2_TCLOCK
#define INCLUDED_SCRIPT2_TCLOCK

#include "cclock.h"

#include "ctest.h"
#include "tstr.h"

#if SEAM == _0_0_0__05
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif
namespace _ {

#if USING_UTF

template <typename Char = CH1>
Char* TPrint(Char* cursor, Char* stop, const CClock& clock) {
  // The way the utf functions are setup, we return a nil-term CH1 so we
  // don't have to check to write a single CH1 in this
  ASSERT(cursor);
  ASSERT(cursor < stop);

  cursor = Print(cursor, stop, clock.year + ClockEpoch());
  if (!cursor) return nullptr;
  *cursor++ = '-';
  cursor = Print(cursor, stop, clock.month + 1);
  if (!cursor) return nullptr;
  *cursor++ = '-';
  cursor = Print(cursor, stop, clock.day);
  if (!cursor) return nullptr;
  *cursor++ = '@';
  cursor = Print(cursor, stop, clock.hour);
  if (!cursor) return nullptr;
  *cursor++ = ':';
  cursor = Print(cursor, stop, clock.minute);
  if (!cursor) return nullptr;
  *cursor++ = ':';
  cursor = Print(cursor, stop, clock.second);
  if (!cursor) return nullptr;
  return cursor;
}

template <typename Char = CH1, typename Time = TM8>
Char* TPrint(Char* cursor, Char* stop, Time t) {
  CClock clock;
  ClockInit(clock, t);
  return TPrint<Char>(cursor, stop, clock);
}

template <typename Char = CH1>
Char* TPrint(Char* cursor, Char* stop, TME& t) {
  // The way the utf functions are setup, we return a nil-term CH1 so we
  // don't have to check to write a single CH1 in this
  ASSERT(cursor);
  ASSERT(cursor < stop);

  CClock clock;
  ClockInit(clock, t.seconds);
  cursor = TPrint<Char>(cursor, stop, clock);
  *cursor++ = ':';
  cursor = Print(cursor, stop, t.ticks);
  if (!cursor) return nullptr;
  return cursor;
}

/* Scans a time in seconds from the given string. */
template <typename Char = CH1>
const Char* TScanTime(const Char* string, SI4& hour, SI4& minute,
                            SI4& second) {
  if (string == nullptr) return nullptr;

  PRINTF("\n\n    Scanning time:%s", string);
  Char c;  //< The current Char.
  SI4 h,   //< Hour.
      m,   //< Minute.
      s;   //< Second.
  if (!TScanSigned<SI4, UI4, Char>(++string, h)) {
    PRINTF("\nInvalid hour:%i", h);
    return nullptr;
  }
  string = TStringSkipNumbers<Char>(string);
  if (h < 0) {
    PRINTF("\nHours:%i can't be negative.", h);
    return nullptr;
  }
  if (h > 23) {
    PRINTF("\nHours:%i can't be > 23.", h);
    return nullptr;
  }
  PRINT(h);
  c = *string++;
  if (!c || TIsWhitespace<Char>(c)) {  // Case @HH
    PRINT(" HH ");
    // Then it's a single number_, so create a TM4 for the current
    // user-time hour..
    hour = h;
    return string;
  }
  c = TLowercase<Char>(c);
  if (c == 'a') {  //
    PRINT("\nCase @HHAm\n HHam ");

    if (TLowercase<Char>(c = *string++) == 'm') c = *string++;
    if (c && !TIsWhitespace<Char>(c)) {
      PRINT("\nInvalid am format.");
      return nullptr;
    }
    PRINT(" @HHAM ");
    hour = h;
    return string;
  }
  if (c == 'p') {
    PRINT(" Case @HHpm ");
    c = *string++;
    if (TLowercase<Char>(c) == 'm') c = *string++;
    if (c && !TIsWhitespace<Char>(c)) {
      PRINT("\ninvalid pm format.");
      return nullptr;
    }
    PRINTF("\nCase @HHPM %i:00:00", h + 12);
    hour = h + 12;
    return string;
  }
  if (c != ':') {
    PRINTF("\nExpecting ':'.");
    return nullptr;
  }

  PRINTF(
      "\nCases HH:MM, HH::MMam, HH::MMpm, HH:MM:SS, HH:MM:SSam, and "
      "HH:MM:SSpm");

  if (!TScanSigned<SI4, UI4, Char>(string, m)) return nullptr;
  string = TStringSkipNumbers<Char>(string);
  if (m < 0) {
    PRINTF("\nMinutes:%i can't be negative!", m);
    return nullptr;
  }
  if (m >= 60) {
    PRINTF("\nMinutes:%i can't be >= 60!", m);
    return nullptr;  //< 60 minutes in an hour.
  }
  PRINTF(":%i", m);

  string = TStringSkipNumbers<Char>(string);
  c = *string++;
  if (!c || TIsWhitespace<Char>(c)) {
    PRINT(" HH:MM ");
    hour = h;
    minute = m;
    return string;
  }
  c = TLowercase<Char>(c);
  if (c == 'a') {
    PRINT(" HH:MMam ");
    c = *string++;
    if (TLowercase<Char>(c) == 'm') {  // The 'm' is optional.
      c = *string++;
    }
    if (c && !TIsWhitespace<Char>(c)) {  // The space is not.
      PRINT("Invalid am in HH::MM AM");
      return nullptr;
    }
    hour = h;
    minute = m;
    return string;
  }
  if (c == 'p') {  //< Case HH:MM PM
    PRINT(" HH:MMpm ");
    c = *string++;
    if (TLowercase<Char>(c) == 'm') {  //< The 'm' is optional.
      c = *string++;
    }
    if (c && !TIsWhitespace<Char>(c)) {  //< The space is not.
      PRINT("Invalid am in HH::MM PM");
      return nullptr;
    }
    hour = h + 12;
    minute = m;
    return string;
  }
  if (c != ':') return nullptr;

  PRINT("\n    Cases HH:MM:SS, HH:MM:SSam, and HH:MM:SSpm");

  if (!TScanSigned<SI4, UI4, Char>(string, s)) return nullptr;
  if (s < 0) {
    PRINTF("\nSeconds:%i can't be negative!", s);
    return nullptr;
  }
  if (s > 60) {
    PRINTF("\nSeconds:%i can't be >= 60!", s);
    return nullptr;
  }
  PRINTF(":%i", s);
  string = TStringSkipNumbers<Char>(string);
  c = TLowercase<Char>(*string);
  if (!c || TIsWhitespace<Char>(c)) {
    PRINTF(" HH:MM:SS ");
    hour = h;
    minute = m;
    second = s;
    return string;
  }
  if (c == 'a') {
    PRINT(" HH:MM:SSam ");
    c = *string++;
    if (TLowercase<Char>(c) == 'm') {  //< The 'm' is optional.
      c = *string++;
    }
    if (!c || !TIsWhitespace<Char>(c)) {  //< The space is not.
      PRINT("\nInvalid am in HH::MM:SS AM");
      return nullptr;
    }
    hour = h;
    minute = m;
    second = s;
    return string;
  }
  if (c != 'p') {
    PRINTF("\nExpecting a PM but found:%c", c);
    return nullptr;  // Format error!
  }
  PRINTF(" HH:MM:SSpm ");
  c = TLowercase<Char>(*string++);
  if (c == 'm') {  //< The 'm' is optional.
    c = *string++;
  }
  if (!c || !TIsWhitespace<Char>(c)) {  //< The space is not.
    PRINT("\nInvalid am in HH::MM:SS PM");
    return nullptr;
  }
  hour = h + 12;
  minute = m;
  second = s;
  return string;
}

/* Scans the given string for a timestamp. */
template <typename Char = CH1>
const Char* TScan(const Char* string, CClock& clock) {
  DASSERT(string);
  PRINTF("\n    Scanning CClock: %s\n    Scanning: ", string);

  string = TStringSkipChar<Char>(string, '0');
  Char c = *string,  //< The current Char.
      delimiter;     //< The delimiter.
  const Char* stop;  //< Might not need

  SI4 hour = 0, minute = 0, second = 0;

  if (c == '@') {
    if (!(string = TScanTime<Char>(string, hour, minute, second))) {
      PRINT("\nCase @ invalid time");
      return nullptr;
    }
    clock.hour = hour;
    clock.minute = minute;
    clock.second = second;

    return string + 1;
  }
  if (c == '#') {
    if (!(string = TScanTime<Char>(string, hour, minute, second))) {
      PRINT("\nCase @ invalid time");
    }
    clock.hour += hour;
    clock.minute += minute;
    clock.second += second;

    return string + 1;
  }

  SI4 value1,            //< The first date field scanned.
      value2,            //< The second date field scanned.
      value3,            //< The third date field scanned.
      is_last_year = 0;  //< Flag for if the date was last year or not.

  // Scan value1
  if (!TScanSigned<SI4, UI4, Char>(string, value1)) {
    PRINT("Scan error at value1");
    return nullptr;
  }
  if (value1 < 0) {
    PRINT("Dates can't be negative.");
    return nullptr;
  }
  string = TStringDecimalEnd<Char>(string);
  if (!string) return nullptr;
  delimiter = *string++;
  PRINTF("%i%c", value1);
  if (delimiter == '@') {
    PRINT(" HH@ ");

    if (!(string = TScanTime<Char>(string, hour, minute, second))) {
      PRINT("\nInvalid time DD@");
      return nullptr;
    }
    clock.day = value1;

    return string + 1;
  }
  // Scan value2.
  string = TStringSkipChar<Char>(string, '0');
  if (!TScanSigned<SI4, UI4, Char>(string, value2)) {
    PRINT("\n    Failed scanning value2 of date.");
    return nullptr;
  }
  if (value2 < 0) {
    PRINT("Day can't be negative.");
    return nullptr;  //< Invalid month and day.
  }
  PRINTF("%i", value2);
  string = TStringDecimalEnd<Char>(string);
  c = *string;
  if (c != delimiter) {
    PRINT("\n    Cases MM/DD and MM/YYyy");
    if (c == '@') {
      if (!(string = TScanTime<Char>(string, hour, minute, second))) {
        PRINT(" invalid time ");
        return nullptr;
      }
    }
    if (!c || TIsWhitespace<Char>(c)) {
      PRINTF("\n    Format is MM/DD and year is %i", clock.year + ClockEpoch());
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
    c = TLowercase<Char>(c);
    if ((value1 < 12) && (value2 > 0) &&
        (value2 <= ClockMonthDayCount(value1))) {
      PRINT(" MM/DD ");
      if (value1 > 11) {
        PRINT("\nInvalid MM/DD@ month");
        return nullptr;
      }
      // We need to find out what year it is.
      CClock clock;
      ClockInit(clock);

      if (value2 > ClockMonthDayCount(clock.year - ClockEpoch(), value1)) {
        PRINT("\nInvalid MM/DD@ day");
        return nullptr;
      }
      clock.month = value1 - 1;
      clock.day = value2;
      clock.hour = hour;
      clock.minute = minute;
      clock.second = second;
      if (!(string = TScanTime(string, hour, minute, second))) {
        PRINT("\nInvalid MM/DD@");
        return nullptr;
      }

      return string + 1;
    }
    if ((value1 < 12) && (value2 > ClockMonthDayCount(value1))) {
      PRINT(" MM/YYyy");
      clock.month = value1 - 1;
      clock.year = value2;
      if (!(string = TScanTime<Char>(string, hour, minute, second))) {
        PRINT("\nInvalid MM / YYYY@ time");
        return nullptr;
      }

      return string + 1;
    }
    PRINT("\nInvalid MM/DD or MM/YYyy format");
    return nullptr;
  }

  // Formats MM/DD/YYyy and YYyy/MM/DD

  string = TStringSkipChar<Char>(++string, '0');
  c = *string;
  // Then there are 3 values and 2 delimiters.
  if (!TIsDigit<Char>(c) || !TScanSigned<SI4, UI4, Char>(string, value3)) {
    PRINTF("\n    SlotRead error reading value3 of date. %c: ", c);
    return nullptr;  //< Invalid format!
  }
  string = TStringDecimalEnd<Char>(string);
  PRINTF("%c%i", c, value3);
  // Now we need to check what format it is in.

  c = *string;
  if (c == '@') {
    if (!(stop = TScanTime<Char>(string, hour, minute, second))) {
      PRINT("Invalid YYyy/MM/DD@ time.");
      return nullptr;
    }
  }
  clock.hour = hour;
  clock.minute = minute;
  clock.second = second;
  if (TIsWhitespace<Char>(*(++string))) {
    PRINT("No date found.");
    return nullptr;
  }
  if (value1 > 11) {  //<
    PRINT("\n    Case YYyy/MM/DD");
    if (value2 == 0 || value2 > 12) {
      PRINTF("Invalid number of months");
      return nullptr;
    }

    if (value2 > ClockMonthDayCount(value2, value1)) {
      PRINT("Invalid number of days");
      return nullptr;
    }  // 17/05/06

    if (value1 < 100) {
      PRINT("\n    Case YY/MM/DD");
      value1 += 2000 - ClockEpoch();
    } else {
      PRINT("\n    Case YYYY/MM/DD");
      value1 -= ClockEpoch();
    }

    clock.year = value1;
    clock.month = value2 - 1;
    clock.day = value3;

    return string + 1;
  }
  PRINT("\n    Cases MM/DD/YY and MM/DD/YYYY");

  if (value1 > 11) {
    PRINT("\nInvalid month.");
    return nullptr;
  }
  if (value2 > ClockMonthDayCount(value1, value3)) {
    PRINT("\nInvalid day.");
    return nullptr;
  }
  clock.month = value1 - 1;
  clock.day = value2;
  if (value3 < 100) {
    PRINT("\n    Case MM/DD/YY");
    clock.year = value3 + (2000 - ClockEpoch());
  } else {
    PRINT("\n    Case MM/DD/YYYY");
    clock.year = value3 - ClockEpoch();
  }
  return string + 1;
}

template <typename Char, typename SI>
const Char* TScanTime(const Char* begin, TM4& result) {
  CClock clock;
  const Char* stop = TScan<Char>(begin, clock);
  result = (TM4)ClockSeconds(clock);
  return stop;
}

template <typename Char, typename SI>
const Char* TScanTime (const Char* begin, TM8& result) {
  CClock clock;
  const Char* stop = TScan<Char> (begin, clock);
  result = (TM8)ClockSeconds (clock);
  return stop;
}

template <typename Char>
const Char* TScan(const Char* begin, TME& result) {
  begin = TScanTime<Char, TM4>(begin, result.seconds);
  if (!begin) return nullptr;
  if (*begin++ != ':') {
    result.ticks = 0;
    return begin - 1;
  }
  return TScanUnsigned<UI4, Char>(begin, result.ticks);
}
#endif  // #if USING_UTF

template <typename SI>
SI TClockSet(CClock* clock, SI t) {
  // Algorithm:
  // 1. Using manual modulo convert in the following order:
  //   a. Year based on seconds per year.
  //   b. Day of year based on seconds per day.
  //   c. Month based on day of year and leap year.
  //   d. Hour.
  //   e. Minute.
  //   f. Second.
  SI value = t / kSecondsPerYear;
  t -= value * kSecondsPerYear;
  clock->year = (SI4)(value + ClockEpoch());
  value = t / kSecondsPerDay;
  t -= value * kSecondsPerDay;
  clock->day = (SI4)value;
  value = t / kSecondsPerHour;
  t -= value * kSecondsPerHour;
  clock->hour = (SI4)value;
  value = t / kSecondsPerMinute;
  clock->minute = (SI4)value;
  clock->second = (SI4)(t - value * kSecondsPerMinute);
  return t;
}

/* A time in seconds stored as either a 32-bit or 64-bit SI.
The difference between a TClock and CClock is that that TClock stores the CClock
and the TM8 or TM4. */
template <typename SI>
class SDK TClock {
 public:
  /* Constructs a clock with the set to Epoch. */
  TClock() {}

  /* Constructs a clock from the given seconds timestamp. */
  TClock(SI t) : t_(t) { ClockInit(clock_, t_); }

  CClock& Clock() { return clock_; }

  /* Sets the time to the given timestamp. */
  void Set(SI t) { t_ = TClockSet<TM4>(clock_, t); }

  inline SI Plus(SI t_2) const { return t_ + t_2; }

  inline SI Minus(SI t_2) const { return t_ - t_2; }

 private:
  CClock clock_;
  SI t_;
};

}  // namespace _

#endif  //< #ifndef INCLUDED_SCRIPT2_TCLOCK
#endif  //< #if SEAM >= _0_0_0__05
