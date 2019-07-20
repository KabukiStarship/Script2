/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_clock.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_CLOCK
#ifndef SCRIPT2_CLOCK_C
#define SCRIPT2_CLOCK_C

namespace _ {

/* A time in seconds and optional microseconds format that is compatible with
the C++ standard library.
Data structure is identical to std::tm with the execution that it has an
additional microseconds from begin of second variable.
*/
struct LIB_MEMBER AClock {
  SIN second,  //< Second of the minute [0, 59].
      minute,  //< Minute of the hour [0, 59].
      hour,    //< Hour of the day [0, 23].
      day,     //< Day of the month [1, 31].
      month,   //< Months since December [0, 11].
      year;    //< Number of years since epoch [-1902, 1970] U [1970, 2038].
};

/* A sub-second timestamp composed of a kTM4 and a kUI4 tick.
Operation of the TME is intended for two scenarios:
1. Processor has a real microsecond timer stored as a 24-bit value.
2. Processor is an x86 and timer gets updated with a tread or OS.
In the real microsecond timer scenario the processor will just
take the unsigned in value and copy it to the kUI4 member. In the
case of the OS having a variable update tick period, the ticker will
work best if the value gets incremented using the ++operator and you will
need to use modulo updates_per_second unless the timer is set to 64 updates
per second or some other power of 2 in which case bit masking is the
tool of choice. For desktop operating systems other threads may hijack the
OS scheduler. */
struct LIB_MEMBER TME {
  TM4 seconds;  //< Seconds since epoch.
  UI4 ticks;    //< Ticks since epoch.
};

enum ClockConstants {
  kClockEpochInit = 1970,                    //< Initial clock epoch.
  kSecondsPerMinute = 60,                    //< Number of seconds in an minute.
  kSecondsPerHour = 60 * kSecondsPerMinute,  //< Number of seconds in an hour.
  kSecondsPerDay = 24 * kSecondsPerHour,     //< Number of seconds in an day.
  kSecondsPerYear = kSecondsPerDay * 365,    //< Number of seconds in an year.
  kSecondsPerEpoch = 10 * kSecondsPerYear,   //< Number of seconds in an year.
  kDaysInJanuary = 31,                       //< Number of days in January.
  kDaysInFebruary = 28,                      //< Number of days in February.
  kDaysInMarch = 31,                         //< Number of days in March.
  kDaysInApril = 30,                         //< Number of days in April.
  kDaysInMay = 31,                           //< Number of days in May.
  kDaysInJune = 30,                          //< Number of days in June.
  kDaysInJuly = 31,                          //< Number of days in July.
  kDaysInAugust = 31,                        //< Number of days in August.
  kDaysInSeptember = 30,                     //< Number of days in September.
  kDaysInOctober = 31,                       //< Number of days in October.
  kDaysInNovember = 30,                      //< Number of days in November.
  kDaysInDecember = 31,                      //< Number of days in December.
};

/* Gets the 32-bit kTM4 clock epoch. */
LIB_INLINE SI2 ClockEpoch();

/* Lookup table for converting from day-of-year to month. */
LIB_INLINE const SI2* ClockLastDayOfMonth();

/* Lookup table for converting from day-of-year to month. */
LIB_INLINE const SI2* ClockLastDayOfMonthLeapYear();

/* Returns which month the given day is in based on the year. */
LIB_INLINE SIN MonthByDay(SIN day, SIN year);

/* Initializes the clock from the given timestamp. */
LIB_MEMBER AClock* ClockInit(AClock& clock, TM4 time);

/* Initializes the clock from the given timestamp. */
LIB_MEMBER AClock* ClockInit(AClock& clock, TM8 time);

/* Initializes the clock from the given 64-bit microsecond timestamp. */
LIB_MEMBER TME& StopwatchInit(TME& clock, TM4 t, UI4 ticks);

/* Initializes the clock from the given timestamp. */
LIB_MEMBER AClock* ClockInit(AClock& clock);

/* Gets the current microsecond timestamp. */
LIB_INLINE TM8 ClockNow();

/* Creates a timestamp from the given seconds Clock. */
LIB_MEMBER TM4 ClockSeconds(AClock& clock);

/* Calculates the seconds from epoch from the clock and stores it to the result.
 */
LIB_INLINE TM4 ClockTM4(AClock& clock);

/* Calculates the seconds from epoch from the clock and stores it to the result.
 */
LIB_INLINE TM8 ClockTM8(AClock& clock);

/* Gets the number_ of days in a months.
    @todo Maybe get some open-source date utility? */
LIB_MEMBER SIN ClockMonthDayCount(TM4 t);

/* Gets the number_ of days in a months.
@param month The month index 0-11.
@param year   */
LIB_MEMBER SIN ClockMonthDayCount(SIN month, SIN year);

/* Gets the abbreviated day of the week CH1 of the given day number_ 1-7. */
LIB_MEMBER const CH1* ClockWeekDay(SIN day_number);

/* Gets the abbreviated day of the week CH1 of the given day number_ 1-7. */
LIB_MEMBER CH1 ClockDayOfWeekInitial(SIN day_number);

/* Compares the two the time and prints the results. */
LIB_MEMBER SIN ClockCompare(TM4 a, TM4 b);

/* Compares the two the time and prints the results. */
LIB_MEMBER SIN ClockCompare(TM4 a, TM4 b);

/* Compares the two the time and prints the results. */
LIB_MEMBER SIN ClockCompare(const AClock& clock, const AClock& other);

/* Compares the given TM4 to the time and prints the results. */
LIB_MEMBER SIN ClockCompare(const AClock& clock, SIN year, SIN month, SIN day,
                            SIN hour, SIN minute, SIN second);

/* Zeros out the struct values.
    @param calendar_time A calendar time struct to zero out. */
LIB_MEMBER void ClockZeroTime(AClock& seconds);

/* Creates a 32-bit seconds timestamp.  */
LIB_MEMBER TM4 ClockTimeTMS(SIN year, SIN month, SIN day, SIN hour = 0,
                            SIN minute = 0, SIN second = 0);

/* Creates a 64-bit seconds timestamp.  */
LIB_MEMBER TM8 ClockTimeTME(SIN year, SIN month, SIN day, SIN hour = 0,
                            SIN minute = 0, SIN second = 0);

#if USING_UTF8 == YES_0
/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH1* Print(CH1* begin, CH1* stop, const AClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param stop   The stop of the write socket.
@param t     The 64-bit stopwatch timestamp. */
LIB_MEMBER CH1* Print(CH1* begin, CH1* stop, TME& t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH1* ClockPrint(CH1* begin, CH1* stop, TM4 time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH1* ClockPrint(CH1* begin, CH1* stop, TM8 time);

/* Reads a time or time delta from a a CH1 starting with an '@' sign.
@brief
@code
@4        (This is 4AM)
@4PM      (No space required)
@4:20P    (Or M)
@4:20 PM
@16:20
@4:20 am
@4:20a.m.
@4:20:00
@4:20:00AM
@16:20:00
@endcode

@param string A nil-terminated string.
@param hour   The location to write the number_ of hours to.
@param minute The location to write the number_ of minutes to.
@param Second The location to write the number_ of seconds to. */
LIB_MEMBER const CH1* ScanTime(const CH1* string, SIN& hour, SIN& minute,
                               SIN& second);

/* Converts a keyboard input to CH1 and deletes the CH1.
@return Nil upon socket failure or CH1 directly after the stop of the
timestamp upon success.
*/
LIB_MEMBER const CH1* Scan(const CH1*, AClock& clock);

/* Converts a keyboard input to a TME. */
LIB_MEMBER const CH1* Scan(const CH1*, TME& result);

/* Converts a keyboard input to a TM4. */
LIB_MEMBER const CH1* ScanTime(const CH1*, TM4& result);

/* Converts a keyboard input to a TM8. */
LIB_MEMBER const CH1* ScanTime(const CH1*, TM8& result);

#endif  //< #if USING_UTF8 == YES_0

#if USING_UTF16 == YES_0

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH2* Print(CH2* begin, CH2* stop, AClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH2* Print(CH2* begin, CH2* stop, TME& t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH2* ClockPrint(CH2* begin, CH2* stop, TM4 time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH2* ClockPrint(CH2* begin, CH2* stop, TM8 time);

/* Reads a time or time delta from a a CH2 starting with an '@' sign.

# Legal Time Formats

@code
@4        (This is 4AM)
@4PM      (No space required)
@4:20P    (Or M)
@4:20 PM
@16:20
@4:20 am
@4:20a.m.
@4:20:00
@4:20:00AM
@16:20:00
@endcode

@param input  The CH2 to parse.
@param hour   The location to write the number_ of hours to.
@param minute The location to write the number_ of minutes to.
@param Second The location to write the number_ of seconds to. */
LIB_MEMBER const CH2* ScanTime(const CH2*, SIN& hour, SIN& minute, SIN& second);

/* Converts a keyboard input to CH2 and deletes the CH2.
@return Nil upon socket failure or CH2 directly after the stop of the
timestamp upon success.
*/
LIB_MEMBER const CH2* Scan(const CH2*, AClock& result);

/* Converts a keyboard input to a TME. */
LIB_MEMBER const CH2* Scan(const CH2*, TME& result);

/* Converts a keyboard input to a TM4. */
LIB_MEMBER const CH2* ScanTime(const CH2*, TM4& result);

/* Converts a keyboard input to a TM8. */
LIB_MEMBER const CH2* ScanTime(const CH2*, TM8& result);

#endif  //< #if USING_UTF16 == YES_0
#if USING_UTF32 == YES_0
/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH4* Print(CH4* begin, CH4* stop, AClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH4* Print(CH4* begin, CH4* stop, TME& time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH4* ClockPrint(CH4* begin, CH4* stop, TM4 time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CH4* ClockPrint(CH4* begin, CH4* stop, TM8 time);

/* Reads a time or time delta from a a CH1 starting with an '@' sign..
@param input  The CH1 to parse.
@param hour   The location to write the number_ of hours to.
@param minute The location to write the number_ of minutes to.
@param Second The location to write the number_ of seconds to.
@return The offset The stop of where the parser exited successfully at.

@code
@4        (This is 4AM)
@4PM      (No space required)
@4:20P    (Or M)
@4:20 PM
@16:20
@4:20 am
@4:20a.m.
@4:20:00
@4:20:00AM
@16:20:00
@endcode
*/
LIB_MEMBER const CH4* ScanTime(const CH4* input, SIN& hour, SIN& minute,
                               SIN& second);

/* Converts a keyboard input to CH1 and deletes the CH1.
 */
LIB_MEMBER const CH4* Scan(const CH4* input, AClock& time);

/* Converts a keyboard input to a TM4. */
LIB_MEMBER const CH4* Scan(const CH4* input, TME& result);

/* Converts a keyboard input to a TM4. */
LIB_MEMBER const CH4* ScanTime(const CH4* input, TM4& result);

/* Converts a keyboard input to a TM4. */
LIB_MEMBER const CH4* ScanTime(const CH4* input, TM8& result);

#endif  //< #if USING_UTF32 == YES_0
}  // namespace _

#endif
#endif
