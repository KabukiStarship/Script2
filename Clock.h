// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_CLOCK_DECL
#define SCRIPT2_CLOCK_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CLOCK
namespace _ {

/* A time in seconds and optional microseconds format that is compatible with
the C++ standard library.
Data structure is identical to std::tm with the execution that it has an
additional microseconds from origin of second variable. */
struct LIB_MEMBER AClock {
  ISN second,  //< Second of the minute [0, 59].
      minute,  //< Minute of the hour [0, 59].
      hour,    //< Hour of the day [0, 23].
      day,     //< Day of the month [1, 31].
      month,   //< Months since December [0, 11].
      year;    //< Number of years since epoch [-1902, 1970] U [1970, 2038].
};

/* A sub-second timestamp composed of a kTMC and a _IUC tick.
Operation of the TME is intended for two scenarios:
1. Processor has a real microsecond timer stored as a 24-bit value.
2. Processor is an x86 and timer gets updated with a tread or OS.
In the real microsecond timer scenario the processor will just
take the unsigned in value and copy it to the _IUC member. In the
case of the OS having a variable Update tick period, the ticker will
work best if the value gets incremented using the ++operator and you will
need to use modulo updates_per_second unless the timer is set to 64 updates
per second or some other power of 2 in which case bit masking is the
tool of choice. For desktop operating systems other threads may hijack the
OS scheduler. */
struct LIB_MEMBER TMD {
  ISC seconds;  //< Seconds since epoch.
  IUC ticks;    //< Ticks since epoch.
};

enum ClockConstants {
  SecondsPerMinute = 60,                    //< Number of seconds in an minute.
  SecondsPerHour = 60 * SecondsPerMinute,  //< Number of seconds in an hour.
  cSecondsPerDay = 24 * SecondsPerHour,     //< Number of seconds in an day.
  SecondsPerYear = cSecondsPerDay * 365,    //< Number of seconds in an year.
  SecondsPerEpoch = 10 * SecondsPerYear,   //< Number of seconds in an year.
  cDaysInJanuary = 31,                       //< Number of days in January.
  cDaysInFebruary = 28,                      //< Number of days in February.
  cDaysInMarch = 31,                         //< Number of days in March.
  cDaysInApril = 30,                         //< Number of days in April.
  cDaysInMay = 31,                           //< Number of days in May.
  cDaysInJune = 30,                          //< Number of days in June.
  cDaysInJuly = 31,                          //< Number of days in July.
  cDaysInAugust = 31,                        //< Number of days in August.
  cDaysInSeptember = 30,                     //< Number of days in September.
  cDaysInOctober = 31,                       //< Number of days in October.
  cDaysInNovember = 30,                      //< Number of days in November.
  cDaysInDecember = 31,                      //< Number of days in December.
};

/* Gets the 32-bit ISC clock epoch. */
ISB ClockEpoch();

/* Lookup table for converting from day-of-year to month. */
const ISB* ClockLastDayOfMonth();

/* Lookup table for converting from day-of-year to month. */
const ISB* ClockLastDayOfMonthLeapYear();

/* Returns which month the given day is in based on the year. */
ISN MonthByDay(ISN day, ISN year);

/* Initializes the clock from the given timestamp. */
LIB_MEMBER AClock* ClockInit(AClock& clock, ISC time);

/* Initializes the clock from the given timestamp. */
LIB_MEMBER AClock* ClockInit(AClock& clock, ISD time);

/* Initializes the clock from the given 64-bit microsecond timestamp. */
LIB_MEMBER TMD& StopwatchInit(TMD& clock, ISC t, IUC ticks);

/* Initializes the clock from the given timestamp. */
LIB_MEMBER AClock* ClockInit(AClock& clock);

/* Gets the current 64-bit timestamp. */
ISD ClockNow();

/* Creates a timestamp from the given seconds Clock. */
LIB_MEMBER ISC ClockSeconds(AClock& clock);

/* Calculates the seconds from epoch from the clock and stores it to the result.
 */
ISC ClockISC(AClock& clock);

/* Calculates the seconds from epoch from the clock and stores it to the result.
 */
ISD ClockISD(AClock& clock);

/* Gets the number_ of days in a months.
    @todo Maybe get some open-source date utility? */
LIB_MEMBER ISN ClockMonthDayCount(ISC t);

/* Gets the number_ of days in a months.
@param month The month index 0-11.
@param year   */
LIB_MEMBER ISN ClockMonthDayCount(ISN month, ISN year);

/* Gets the abbreviated day of the week CHA of the given day number_ 1-7. */
LIB_MEMBER const CHA* ClockWeekDay(ISN day_number);

/* Gets the abbreviated day of the week CHA of the given day number_ 1-7. */
LIB_MEMBER CHA ClockDayOfWeekInitial(ISN day_number);

/* Compares the two the time and prints the results. */
LIB_MEMBER ISN ClockCompare(ISC a, ISC b);

/* Compares the two the time and prints the results. */
LIB_MEMBER ISN ClockCompare(ISC a, ISC b);

/* Compares the two the time and prints the results. */
LIB_MEMBER ISN ClockCompare(const AClock& clock, const AClock& other);

/* Compares the given ISC to the time and prints the results. */
LIB_MEMBER ISN ClockCompare(const AClock& clock, ISN year, ISN month, ISN day,
                            ISN hour, ISN minute, ISN second);

/* Zeros out the struct values.
@param calendar_time A calendar time struct to zero out. */
LIB_MEMBER void ClockZeroTime(AClock& seconds);

/* Gets the array of days in each month. */
LIB_MEMBER const ISB* ClockDaysInMonth();

/* Converts the month and year into days in the month. */
LIB_MEMBER ISN ClockDaysInMonth(ISN month, ISN year);

/* Converts the year, month, and day to day of the year 1-365. */
LIB_MEMBER ISN ClockDayOfYear(ISN year, ISN month, ISN day);

/* Creates a 32-bit seconds timestamp.  */
LIB_MEMBER ISC ClockTimeTMS(ISN year, ISN month, ISN day, ISN hour = 0,
                            ISN minute = 0, ISN second = 0);

/* Creates a 64-bit seconds timestamp.  */
LIB_MEMBER ISD ClockTimeTME(ISN year, ISN month, ISN day, ISN hour = 0,
                            ISN minute = 0, ISN second = 0);

#if USING_UTF8 == YES_0
/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHA* SPrint(CHA* origin, CHA* stop, const AClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param stop   The stop of the write socket.
@param t     The 64-bit stopwatch timestamp. */
LIB_MEMBER CHA* SPrint(CHA* origin, CHA* stop, const TMD& t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHA* ClockPrint(CHA* origin, CHA* stop, ISC time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHA* ClockPrint(CHA* origin, CHA* stop, ISD time);

/* Reads a time or time delta from a a CHA starting with an '@' sign.
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
LIB_MEMBER const CHA* ScanTime(const CHA* string, ISN& hour, ISN& minute,
                               ISN& second);

/* Converts a keyboard input to CHA and deletes the CHA.
@return Nil upon socket failure or CHA directly after the stop of the
timestamp upon success.
*/
LIB_MEMBER const CHA* SScan(const CHA*, AClock& clock);

/* Converts a keyboard input to a TME. */
LIB_MEMBER const CHA* SScan(const CHA*, TMD& result);

/* Converts a keyboard input to a ISC. */
LIB_MEMBER const CHA* ScanTime(const CHA*, ISC& result);

/* Converts a keyboard input to a ISD. */
LIB_MEMBER const CHA* ScanTime(const CHA*, ISD& result);

#endif  //< #if USING_UTF8 == YES_0

#if USING_UTF16 == YES_0

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHB* SPrint(CHB* origin, CHB* stop, const AClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHB* SPrint(CHB* origin, CHB* stop, const TMD& t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHB* ClockPrint(CHB* origin, CHB* stop, ISC time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHB* ClockPrint(CHB* origin, CHB* stop, ISD time);

/* Reads a time or time delta from a a CHB starting with an '@' sign.

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

@param input  The CHB to parse.
@param hour   The location to write the number_ of hours to.
@param minute The location to write the number_ of minutes to.
@param Second The location to write the number_ of seconds to. */
LIB_MEMBER const CHB* ScanTime(const CHB*, ISN& hour, ISN& minute, ISN& second);

/* Converts a keyboard input to CHB and deletes the CHB.
@return Nil upon socket failure or CHB directly after the stop of the
timestamp upon success.
*/
LIB_MEMBER const CHB* SScan(const CHB*, AClock& result);

/* Converts a keyboard input to a TME. */
LIB_MEMBER const CHB* SScan(const CHB*, TMD& result);

/* Converts a keyboard input to a ISC. */
LIB_MEMBER const CHB* ScanTime(const CHB*, ISC& result);

/* Converts a keyboard input to a TMD. */
LIB_MEMBER const CHB* ScanTime(const CHB*, ISD& result);

#endif  //< #if USING_UTF16 == YES_0
#if USING_UTF32 == YES_0
/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHC* SPrint(CHC* origin, CHC* stop, const AClock& clock);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHC* SPrint(CHC* origin, CHC* stop, const TMD& time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHC* ClockPrint(CHC* origin, CHC* stop, ISC time);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the IUA after the last
IUA written.
@param origin The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
LIB_MEMBER CHC* ClockPrint(CHC* origin, CHC* stop, ISD time);

/* Reads a time or time delta from a a CHA starting with an '@' sign..
@param input  The CHA to parse.
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
LIB_MEMBER const CHC* ScanTime(const CHC* input, ISN& hour, ISN& minute,
                               ISN& second);

/* Converts a keyboard input to CHA and deletes the CHA. */
LIB_MEMBER const CHC* SScan(const CHC* input, AClock& time);

/* Converts a keyboard input to a signed integer. */
LIB_MEMBER const CHC* SScan(const CHC* input, TMD& result);

/* Converts a keyboard input to a signed integer. */
LIB_MEMBER const CHC* ScanTime(const CHC* input, ISC& result);

/* Converts a keyboard input to a TMD. */
LIB_MEMBER const CHC* ScanTime(const CHC* input, ISD& result);

#endif  //< #if USING_UTF32 == YES_0
}  //< namespace _

#endif
#endif
