// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_CLOCK_DECL
#define CRABS_CLOCK_DECL 1
#include <_Config.h>
#if SEAM >= CRABS_CLOCK
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

enum {
  TMDSecondsBitCount = 28,    //< Number of bits in the TMD seconds timestamp.
  TMDTicksBitCount   = 8,     //< Number of bits in the TMD subsecond ticker.
  TMDIdBitCount      = 28,    //< Number of bits in the TMD source id.
  // Bit 0 of the TMD seconds timestamp.
  TMDSecondsBit0     = TMDTicksBitCount + TMDIdBitCount,
  // Bit 0 of the TMD ticks timestamp.
  TMDTicksBit0       = TMDIdBitCount,
};

/* A 64-bit Subsecond Id ASCII TMD.
@see ~/_Spec/Data/Types/Timestamps.md */
struct LIB_MEMBER TMT {
  IUC ticks,    //< Subsecond spin ticker.
      seconds;  //< 64-bit Subsecond ID ASCII TMD Seconds, Ticker, and Id.

  // Creates a TMD from the given seconds, ticks, and id
  TMT(ISC seconds, IUC tick = 0);

  // Creates a TMD from the given word.
  TMT(IUD value);

  // Creates a TMD from the given word.
  TMT(ISD value);
};

/* A 64-bit Subsecond Id ASCII TMD.
@see ~/_Spec/Data/Types/Timestamps.md */
struct LIB_MEMBER TMD {
  ISD value;  //< 64-bit Subsecond ID ASCII TMD Seconds, Ticker, and Id.

  // Creates a TMD from the given seconds, ticks, and id
  TMD(ISC seconds, ISC tick = 0, ISC id = 0);

  // Creates a TMD from the given word.
  TMD(IUD value);

  // Creates a TMD from the given word.
  TMD(ISD value);

  // Gets the seconds bits of the TMD.
  ISC Seconds();

  // Gets the ticks bits of the TMD.
  ISC Ticks();

  // Gets the id portion of the TMD.
  ISC Id();
};

enum {
  TMESecondsBitCount = 34,  //< Number of bits in the TME seconds timestamp.
  TMETicksBitCount = 16,    //< Number of bits in the TME subsecond ticker.
  TMEIdBitCount = 78,    //< Number of bits in the TME source id.
  // Bit 0 of the TMD seconds timestamp.
  TMESecondsBit0 = TMETicksBitCount + TMEIdBitCount,
  // Bit 0 of the MSB of the TMD seconds timestamp.
  TMESecondsMSBit0 = TMEIdBitCount - 64,
  // Bit 0 of the TME ticks timestamp.
  TMETicksBit0 = TMEIdBitCount,
  TMETicksMSBit0 = TMETicksBit0 - 64,
};

/* A 128-bit Subsecond Id ASCII TMD.
@see ~/_Spec/Data/Timestamps.md */
struct LIB_MEMBER TME {
  ISD lsb,    //< Seconds since epoch.
      msb;    //< Ticks since epoch.

  /* Creates a TME from the given seconds, ticks, and id */
  TME(ISD seconds, ISD tick = 0, ISD id_msb = 0, ISD id_lsb = 0);

  // Gets the seconds bits of the TME.
  ISC Seconds();

  // Gets the ticks bits of the TME.
  ISC Ticks();

  // Gets the id LSB portion of the TME.
  ISD IdLSB();

  // Gets the id MSB portion of the TME.
  ISC IdMSB();
};

enum ClockConstants {
  SecondsPerMinute = 60,                    //< Number of seconds in an minute.
  SecondsPerHour = 60 * SecondsPerMinute,   //< Number of seconds in an hour.
  SecondsPerDay = 24 * SecondsPerHour,      //< Number of seconds in an day.
  SecondsPerYear = SecondsPerDay * 365,     //< Number of seconds in an year.
  SecondsPerEpoch = 10 * SecondsPerYear,    //< Number of seconds in an year.
  DaysInJanuary = 31,                       //< Number of days in January.
  DaysInFebruary = 28,                      //< Number of days in February.
  DaysInMarch = 31,                         //< Number of days in March.
  DaysInApril = 30,                         //< Number of days in April.
  DaysInMay = 31,                           //< Number of days in May.
  DaysInJune = 30,                          //< Number of days in June.
  DaysInJuly = 31,                          //< Number of days in July.
  DaysInAugust = 31,                        //< Number of days in August.
  DaysInSeptember = 30,                     //< Number of days in September.
  DaysInOctober = 31,                       //< Number of days in October.
  DaysInNovember = 30,                      //< Number of days in November.
  DaysInDecember = 31,                      //< Number of days in December.
};

/* Gets the 32-bit ISC clock epoch. */
ISC ClockEpoch();

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

#if USING_STA == YES_0
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
LIB_MEMBER const CHA* SScan(const CHA*, TMT& result);

/* Converts a keyboard input to a ISC. */
LIB_MEMBER const CHA* ScanTime(const CHA*, ISC& result);

/* Converts a keyboard input to a ISD. */
LIB_MEMBER const CHA* ScanTime(const CHA*, ISD& result);

#endif  //< #if USING_STA == YES_0

#if USING_STB == YES_0

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

#endif  //< #if USING_STB == YES_0
#if USING_STC == YES_0
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

#endif  //< #if USING_STC == YES_0
}  //< namespace _

#endif
#endif
