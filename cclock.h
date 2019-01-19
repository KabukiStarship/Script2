/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cclock.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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
#ifndef INCLUDED_SCRIPTCCLOCK
#define INCLUDED_SCRIPTCCLOCK

namespace _ {

/* A time in seconds and optional microseconds format that is compatible with
the C++ standard library.
Data structure is identical to std::tm with the execution that it has an
additional microseconds from begin of second variable.
*/
struct SDK CClock {
  SI4 second,  //< Second of the minute [0, 59].
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
struct TME {
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
SDK inline SI2 ClockEpoch();

/* Lookup table for converting from day-of-year to month. */
SDK inline const SI2* ClockLastDayOfMonth();

/* Lookup table for converting from day-of-year to month. */
SDK inline const SI2* ClockLastDayOfMonthLeapYear();

/* Returns which month the given day is in based on the year. */
SDK inline SI4 MonthByDay(SI4 day, SI4 year);

/* Initializes the clock from the given timestamp. */
SDK CClock* ClockInit(CClock& clock, TM4 time);

/* Initializes the clock from the given timestamp. */
SDK CClock* ClockInit(CClock& clock, TM8 time);

/* Initializes the clock from the given 64-bit microsecond timestamp. */
SDK TME& StopwatchInit(TME& clock, TM4 t, UI4 ticks);

/* Initializes the clock from the given timestamp. */
SDK CClock* ClockInit(CClock& clock);

/* Gets the current microsecond timestamp. */
SDK inline TM8 ClockNow();

/* Creates a timestamp from the given seconds Clock. */
SDK TM4 ClockSeconds (CClock& clock);

/* Calculates the seconds from epoch from the clock and stores it to the result.
 */
SDK inline TM4 ClockTM4(CClock& clock);

/* Calculates the seconds from epoch from the clock and stores it to the result.
 */
SDK inline TM8 ClockTM8(CClock& clock);

/* Gets the number_ of days in a months.
    @todo Maybe get some open-source date utility? */
SDK SI4 ClockMonthDayCount(TM4 t);

/* Gets the number_ of days in a months.
@param month The month index 0-11.
@param year   */
SDK SI4 ClockMonthDayCount(SI4 month, SI4 year);

/* Gets the abbreviated day of the week CH1 of the given day number_ 1-7. */
SDK const CH1* ClockWeekDay(SI4 day_number);

/* Gets the abbreviated day of the week CH1 of the given day number_ 1-7. */
SDK CH1 ClockDayOfWeekInitial(SI4 day_number);

/* Compares the two the time and prints the results. */
SDK SI4 ClockCompare(TM4 a, TM4 b);

/* Compares the two the time and prints the results. */
SDK SI4 ClockCompare(TM4 a, TM4 b);

/* Compares the two the time and prints the results. */
SDK SI4 ClockCompare(const CClock& clock, const CClock& other);

/* Compares the given TM4 to the time and prints the results. */
SDK SI4 ClockCompare(const CClock& clock, SI4 year, SI4 month, SI4 day,
                     SI4 hour, SI4 minute, SI4 second);

/* Zeros out the struct values.
    @param calendar_time A calendar time struct to zero out. */
SDK void ClockZeroTime(CClock& seconds);

/* Creates a 32-bit seconds timestamp.  */
SDK TM4 ClockTimeTMS(SI4 year, SI4 month, SI4 day, SI4 hour = 0, SI4 minute = 0,
                     SI4 second = 0);

/* Creates a 64-bit seconds timestamp.  */
SDK TM8 ClockTimeTME(SI4 year, SI4 month, SI4 day, SI4 hour = 0, SI4 minute = 0,
                     SI4 second = 0);

#if USING_UTF8 == YES
/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH1* Print(CH1* begin, CH1* stop, const CClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param stop   The stop of the write socket.
@param t     The 64-bit stopwatch timestamp. */
SDK CH1* Print(CH1* begin, CH1* stop, TME& t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH1* PrintTime(CH1* begin, CH1* stop, TM4 time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH1* PrintTime(CH1* begin, CH1* stop, TM8 time);

/* Prints the given timestamp to the stdout. */
SDK void PrintTime(const CClock& clock);

/* Prints the given timestamp to the stdout. */
SDK void PrintTime(TME t);

/* Prints the given timestamp to the stdout. */
SDK void PrintTime(TM4 t);

/* Prints the given timestamp to the stdout. */
SDK void PrintTime(TM8 t);

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

@param input  The CH1 to parse.
@param hour   The location to write the number_ of hours to.
@param minute The location to write the number_ of minutes to.
@param Second The location to write the number_ of seconds to. */
SDK const CH1* ScanTime(const CH1* string_, SI4& hour, SI4& minute,
                               SI4& second);

/* Converts a keyboard input to CH1 and deletes the CH1.
@return Nil upon socket failure or CH1 directly after the stop of the
timestamp upon success.
*/
SDK const CH1* Scan(const CH1* string_, CClock& clock);

/* Converts a keyboard input to a TME. */
SDK const CH1* Scan(const CH1* string_, TME& result);

/* Converts a keyboard input to a TM4. */
SDK const CH1* ScanTime(const CH1* string_, TM4& result);

/* Converts a keyboard input to a TM8. */
SDK const CH1* ScanTime(const CH1* string_, TM8& result);

#endif  //< #if USING_UTF8 == YES

#if USING_UTF16 == YES

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH2* Print(CH2* begin, CH2* stop, CClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH2* Print(CH2* begin, CH2* stop, TME& t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH2* PrintTime(CH2* begin, CH2* stop, TM4 time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH2* Print(CH2* begin, CH2* stop, TM8 time);

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
SDK const CH2* ScanTime(const CH2* string_, SI4& hour, SI4& minute,
                               SI4& second);

/* Converts a keyboard input to CH2 and deletes the CH2.
@return Nil upon socket failure or CH2 directly after the stop of the
timestamp upon success.
*/
SDK const CH2* Scan(const CH2* string_, CClock& result);

/* Converts a keyboard input to a TME. */
SDK const CH2* Scan(const CH2* string_, TME& result);

/* Converts a keyboard input to a TM4. */
SDK const CH2* ScanTime(const CH2* string_, TM4& result);

/* Converts a keyboard input to a TM8. */
SDK const CH2* ScanTime(const CH2* string_, TM8& result);

#endif  //< #if USING_UTF16 == YES
#if USING_UTF32 == YES
/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH4* Print(CH4* begin, CH4* stop, CClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH4* Print(CH4* begin, CH4* stop, TME& time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH4* PrintTime(CH4* begin, CH4* stop, TM4 time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
SDK CH4* PrintTime(CH4* begin, CH4* stop, TM8 time);

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
SDK const CH4* ScanTime(const CH4* input, SI4& hour, SI4& minute,
                               SI4& second);

/* Converts a keyboard input to CH1 and deletes the CH1.
 */
SDK const CH4* Scan(const CH4* input, CClock& time);

/* Converts a keyboard input to a TM4. */
SDK const CH4* Scan(const CH4* input, TME& result);

/* Converts a keyboard input to a TM4. */
SDK const CH4* ScanTime(const CH4* input, TM4& result);

/* Converts a keyboard input to a TM4. */
SDK const CH4* ScanTime(const CH4* input, TM8& result);

#endif  //< #if USING_UTF32 == YES
}  // namespace _

#undef PRINT
#undef PRINTF
#endif  //< #ifndef INCLUDED_SCRIPTCCLOCK
#endif  //< #if SEAM >= _0_0_0__05
