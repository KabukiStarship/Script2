/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /stringf.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

/* There is a different set of string printing utilities because it's a little
faster. */

#pragma once
#include <_config.h>

#ifndef SCRIPT2_STRING_CODE
#define SCRIPT2_STRING_CODE 1

#include "binary.hpp"
#include "puff.hpp"
#include "stringf.h"

namespace _ {

inline SIN STRLength(UI1 value) {
  if (value < 10) return 1;
  if (value < 100) return 2;
  return 3;
}

inline SIN STRLength(SI1 value) {
  if (value < 0) return STRLength((UI1)-value) + 1;
  return STRLength((UI1)value);
}

/* Compares the two Strings up to the given delimiter.
@param delimiter Delimiters in Script2 are equal to or less than.
@return 0 if the Strings are equal or a non-zero delta upon failure. */
template <typename CHT = CHR>
SIN TSTRCompare(const CHT* string, const CHT* other_String, CHT delimiter = 0) {
  if (!string || !other_String) return 0;

  SIN a, b, result;
  if (!string) {
    if (!other_String) return 0;
    return SIN(*string);
  }
  if (!other_String) return 0 - *string;

  a = *string;
  b = *other_String;
  if (!a) {
    if (!b) return 0;
    return b;
  }
  if (!b) {
    if (!a) return 0;
    return 0 - a;
  }
  // other_String SHOULD be a nil-terminated string without whitespace.
  while (b) {
    result = b - a;
    if (result) {
      return result;
    }
    if (a <= (SI4)delimiter) {
      return result;
    }
    ++string;
    ++other_String;
    a = *string;
    b = *other_String;
  }
  if (a > (SI4)delimiter) {
    return b - a;
  }
  return 0;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename CHT = CHR>
inline const CHT* TSTREnd(const CHT* string, CH1 delimiter = 0) {
  while (*string++ != delimiter)
    ;
  return string - 1;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename CHT = CHR>
inline CHT* TSTREnd(CHT* string, CHT delimiter = 0) {
  return const_cast<CHT*>(
      TSTREnd<CHT>(reinterpret_cast<const CHT*>(string), delimiter));
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename CHT = CHR, typename SIZ = SIN>
SIZ TSTRLength(const CHT* string) {
  return (SIZ)(TSTREnd<CHT>(string) - string);
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename CHT = CHR, typename SIZ = SIN>
inline SIZ TSTRLength(CHT* string) {
  return TSTRLength<CHT>(reinterpret_cast<const CHT*>(string));
}

/* Scans a item from the string.
@pre You must check if the string is nil before calling. */
inline const CH1* SScan(const CH1* string, CH1& item) {
  item = *string++;
  return string;
}
inline CH1* SScan(CH1* string, CH1& item) {
  return const_cast<CH1*>(SScan(const_cast<const CH1*>(string), item));
}

inline const CH1* SScan(const CH1* string, CH2& item) {
  CH4 result;
  string = SScan(string, result);
  result = item;
}
inline CH1* SScan(CH1* string, CH2& item) {
  return const_cast<CH1*>(SScan(const_cast<const CH1*>(string), item));
}

inline CH1* SScan(CH1* string, CH4& item) {
  const CH1* const_string = const_cast<const CH1*>(string);
  return const_cast<CH1*>(SScan(const_string, item));
}

#if USING_UTF16 == YES_0
inline const CH2* SScan(const CH2* string, CH1& item) {
  item = CH1(*string++);
  return string;
}
inline CH2* SScan(CH2* string, CH1& item) {
  return const_cast<CH2*>(SScan(const_cast<const CH2*>(string), item));
}
inline const CH2* SScan(const CH2* string, CH2& c) {
  c = *string++;
  return string;
}
inline CH2* SScan(CH2* string, CH2& item) {
  return const_cast<CH2*>(SScan(const_cast<const CH2*>(string), item));
}
inline CH2* SScan(CH2* string, CH4& item) {
  return const_cast<CH2*>(SScan(const_cast<const CH2*>(string), item));
}
#endif

#if USING_UTF32 == YES_0
// CH1* SScan (CH2* string, CH2& item) and
// CH1* SScan (CH1* string, CH4& item) in cstring.h

inline const CH4* SScan(const CH4* string, CH1& result) {
  result = CH1(*string++);
  return string;
}
inline CH4* SScan(CH4* string, CH1& item) {
  const CH4* const_string = const_cast<const CH4*>(string);
  return const_cast<CH4*>(SScan(const_string, item));
}

inline const CH4* SScan(const CH4* string, CH2& result) {
  result = CH2(*string++);
  return string;
}
inline CH4* SScan(CH4* string, CH2& item) {
  const CH4* const_string = const_cast<const CH4*>(string);
  return const_cast<CH4*>(SScan(const_string, item));
}
inline const CH4* SScan(const CH4* string, CH4& result) {
  result = *string++;
  return string;
}
inline CH4* SScan(CH4* string, CH4& item) {
  const CH4* const_string = const_cast<const CH4*>(string);
  return const_cast<CH4*>(SScan(const_string, item));
}
#endif

template <typename CHT>
CHT* TScanChar(CHT* cursor, CHT& c) {}

/* Converts the given item to lowercase if it is uppercase. */
template <typename CHT>
inline CHT TToLower(CHT c) {
  if (c >= 'A' && c <= 'Z') c -= 32;
  return c;
}

inline CH1 ToLower(CH1 value) { return TToLower<CH1>(value); }
inline CH2 ToLower(CH2 value) { return TToLower<CH2>(value); }
inline CH4 ToLower(CH4 value) { return TToLower<CH4>(value); }

/* Checks if the given item is whitespace. */
template <typename CHT = CHR>
inline BOL TIsWhitespace(CHT item) {
  return item <= ' ';
}

template <typename CHT>
SIN TIsYesNo(const CHT* string) {
  if (!string) return 0;
  CHT c = TToLower<CHT>(*string++);
  SIN result;
  if (c == 'y')
    result = 1;
  else if (c == 'n')
    result = -1;
  else
    return 0;
  c = *string++;
  if (TIsWhitespace<CHT>(c)) return result;
  c = TToLower<CHT>(c);
  if (c == 'o') return -(SIN)TIsWhitespace<CHT>(*string++);
  if (TToLower<CHT>(*string++) != 'e') return 0;
  if (TToLower<CHT>(*string++) != 's') return 0;
  return (SIN)TIsWhitespace<CHT>(*string++);
}

/* Checks if the given CH1 is a digit of a number_.
@return True if it is a digit. */
template <typename CHT = CHR>
BOL TIsDigit(CHT c) {
  return (c >= '0') && (c <= '9');
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename CHT = CHR>
const CHT* TScanSigned(const CHT* string, SI& item) {
  if (!string) return nullptr;
  SI sign;
  const CHT* cursor = string;
  CHT c = *cursor++;
  if (c == '-') {
    c = *string++;
    sign = -1;
  } else {
    sign = 1;
  }
  if (!TIsDigit<CHT>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<CHT>(c)) c = *cursor++;
  const CHT* stop = cursor;  // Store stop to return.
  cursor -= 2;

  c = *cursor--;
  UI value = UI(c) - '0';
  UI pow_10_ui2 = 1;

  while (cursor >= string) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (((UI)c) - '0');
    if (new_value < value) return nullptr;
    value = new_value;
  }
  item = sign * value;
  return stop;
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename CHT = CHR>
CHT* TScanSigned(CHT* string, SI& item) {
  const CHT* ptr = reinterpret_cast<const CHT*>(string);
  return const_cast<CHT*>(TScanSigned<SI, UI, CHT>(ptr, item));
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The SI to write the scanned SI. */
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, SI1& item) {
  return TScanSigned<SI1, UI1, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, SI1& item) {
  return TScanSigned<SI1, UI1, CHT>(string, item);
}
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, SI2& item) {
  return TScanSigned<SI2, UI2, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, SI2& item) {
  return TScanSigned<SI2, UI2, CHT>(string, item);
}
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, SI4& item) {
  return TScanSigned<SI4, UI4, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, SI4& item) {
  return TScanSigned<SI4, UI4, CHT>(string, item);
}
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, SI8& item) {
  return TScanSigned<SI8, UI8, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, SI8& item) {
  return TScanSigned<SI8, UI8, CHT>(string, item);
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The UI to write the scanned UI. */
template <typename UI, typename CHT = CHR>
const CHT* TScanUnsigned(const CHT* string, UI& item) {
  if (!string) return nullptr;
  const CHT* cursor = string;
  CHT c = *cursor++;
  if (!TIsDigit<CHT>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<CHT>(c)) c = *cursor++;
  const CHT* stop = cursor;  // Store stop to return.
  cursor -= 2;

  c = *cursor--;
  UI value = UI(c) - '0';
  UI pow_10_ui2 = 1;

  while (cursor >= string) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (((UI)c) - '0');
    if (new_value < value) return nullptr;
    value = new_value;
  }
  item = value;
  return stop;
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The UI to write the scanned UI. */
template <typename UI, typename CHT = CHR>
CHT* TScanUnsigned(CHT* string, UI& item) {
  const CHT* ptr = reinterpret_cast<const CHT*>(string);
  return const_cast<CHT*>(TScanUnsigned<UI, CHT>(ptr, item));
}

/* Scans item from the string.
@return Nil upon failure. */
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, UI1& item) {
  return TScanUnsigned<UI1, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, UI1& item) {
  return TScanUnsigned<UI1, CHT>(string, item);
}
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, UI2& item) {
  return TScanUnsigned<UI2, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, UI2& item) {
  return TScanUnsigned<UI2, CHT>(string, item);
}
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, UI4& item) {
  return TScanUnsigned<UI4, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, UI4& item) {
  return TScanUnsigned<UI4, CHT>(string, item);
}
template <typename CHT = CHR>
const CHT* TSScan(const CHT* string, UI8& item) {
  return TScanUnsigned<UI8, CHT>(string, item);
}
template <typename CHT = CHR>
CHT* TSScan(CHT* string, UI8& item) {
  return TScanUnsigned<UI8, CHT>(string, item);
}

/* Prints a Unicode CHT to the given socket.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param string The beginning of the socket.
@param count  The element count.
@param item   The string to print. */
template <typename CHT = CHR>
CHT* TSPrint(CHT* string, CHT* stop, CH1 item) {
  if (!string || string >= stop) return nullptr;
  *string++ = item;
  *string = 0;
  return string;
}
/* Prints a Unicode CHT to the given socket.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param string The beginning of the socket.
@param count  The element count.
@param item   The string to print. */
template <typename CHT = CHR>
CHT* TSPrint(CHT* string, SIW count, CH1 item) {
  return SPrint(string, string + count - 1, item);
}

/* Prints a Unicode CHT to the given socket.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param string The beginning of the socket.
@param count  The element count.
@param item   The string to print. */
template <typename CHT = CHR>
CHT* TSPrint(CHT* string, SIW count, CH2 item) {
  return TSPrint<CHT>(string, string + count - 1, item);
}

/* Prints the given item to the string.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param count  The number of Chars in the string buffer.
@param item   The string to print. */
template <typename CHT = CHR>
CHT* TSPrint(CHT* string, SIW count, CH4 item) {
  return TSPrint<CHT>(string, string + count - 1, item);
}
inline CH1* SPrint(CH1* string, CH1* stop, CH1 item) {
  if (!string || string >= stop) return nullptr;
  *string++ = item;
  *string = 0;
  return string;
}

inline CH1* SPrint(CH1* string, SIW size, CH1 item) {
  return SPrint(string, string + size - 1, item);
}
inline CH1* SPrint(CH1* string, SIW size, CH2 item) {
  return SPrint(string, string + size - 1, item);
}
inline CH1* SPrint(CH1* string, SIW size, CH4 item) {
  return SPrint(string, string + size - 1, item);
}

#if USING_UTF16 == YES_0
inline CH2* SPrint(CH2* string, CH2* stop, CH2 item) {
  if (!string || string >= stop) return nullptr;
  *string++ = item;
  *string = 0;
  return string;
}
inline CH2* SPrint(CH2* string, CH2* stop, CH1 item) {
  return SPrint(string, stop, CH2(item));
}
inline CH2* SPrint(CH2* string, SIW size, CH1 item) {
  return SPrint(string, string + size - 1, item);
}
inline CH2* SPrint(CH2* string, SIW size, CH2 item) {
  return SPrint(string, string + size - 1, item);
}
inline CH2* SPrint(CH2* string, SIW size, CH4 item) {
  return SPrint(string, string + size - 1, item);
}

#endif  // #if USING_UTF16 == YES_0

#if USING_UTF32 == YES_0
inline CH4* SPrint(CH4* string, CH4* stop, CH4 item) {
  if (!string || string >= stop) return nullptr;
  *string++ = item;
  *string = 0;
  return string;
}
inline CH4* SPrint(CH4* string, SIW size, CH4 item) {
  return SPrint(string, string + size - 1, item);
}
inline CH4* SPrint(CH4* string, CH4* stop, CH1 item) {
  return SPrint(string, stop, CH4(item));
}
inline CH4* SPrint(CH4* string, SIW size, CH1 item) {
  return SPrint(string, size, CH4(item));
}

inline CH4* SPrint(CH4* string, SIW size, CH2 item) {
  return SPrint(string, size, CH4(item));
}
inline CH4* SPrint(CH4* string, CH4* stop, CH2 item) {
  return SPrint(string, stop, CH4(item));
}

#endif  //< USING_UTF32 == YES_0

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term CHT upon success.
 @param string  The beginning of the socket.
 @param stop    The last CHT in the socket.
 @param item    The item to print. */
template <typename CHX, typename CHY>
CHX* TSPrintString(CHX* string, CHX* stop, const CHY* item) {
  if (!string || !item) return nullptr;

  CHA c;
  item = SScan(item, c);
  while (c) {
    string = SPrint(string, stop, c);
    if (!string) return string;
    item = SScan(item, c);
  }
  *string = 0;
  return string;
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, const CH1* item) {
  return TSPrintString<CHT, CH1>(start, stop, item);
}

#if USING_UTF16 == YES_0
/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term CHT upon success.
 @param string  The beginning of the socket.
 @param stop    The last CHT in the socket.
 @param item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename CHT = CHR>
CHT* TSPrintString(CHT* string, CHT* stop, const CH2* item) {
  return TSPrintString<CHT, CH2>(string, stop, item);
}
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, const CH2* item) {
  return TSPrintString<CHT>(start, stop, item);
}
#endif

#if USING_UTF32 == YES_0
/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term CHT upon success.
 @param start  The beginning of the socket.
 @param stop    The last CHT in the socket.
 @param item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename CHT = CHR>
CHT* TSPrintString(CHT* start, CHT* stop, const CH4* item) {
  return TSPrintString<CHT, CH4>(start, stop, item);
}

template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, CHT* stop, const CH4* item) {
  return TSPrintString<CHT>(start, stop, item);
}
#endif

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param start    The beginning of the socket.
@param size      The size of the socket in CHT(s).
@param item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename CHT = CHR>
inline CHT* TSPrint(CHT* start, SIW size, const CH1* item) {
  return TSPrintString<CHT>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param start    The beginning of the socket.
@param size      The size of the socket in CHT(s).
@param item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename CHT = CHR>
CHT* TSPrint(CHT* start, SIW size, const CH2* item) {
  return TSPrintString<CHT>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param start    The beginning of the socket.
@param size      The size of the socket in CHT(s).
@param item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename CHT = CHR>
CHT* TSPrint(CHT* start, SIW size, const CH4* item) {
  return TSPrintString<CHT>(start, start + size - 1, item);
}

/* Finds the end of a decimal number of the given string.
@return Nil if the string doesn't contain a decimal or is nil.
@param start The start of the string to search. */
template <typename CHT = const CH1>
const CHT* TSTRDecimalEnd(const CHT* start) {
  if (!start) return start;
  CHT c = *start++;
  if (c == '-') c = *start++;
  if (c < '0' || c > '9') return nullptr;
  c = *start++;
  while (TIsDigit<CHT>(c)) {
    c = *start++;
    if (c <= 0) return start - 1;
  }
  return start - 1;
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the CHT after the last CHT in the
given range.
@param cursor  The first CHT in the buffer.
@param lower_bounds
@param upper bounds*/
template <typename CHT = CHR>
const CHT* TSTRSkimodulearsInRange(const CHT* cursor, CHT lower_bounds,
                                   CHT upper_bounds) {
  A_ASSERT(cursor);
  A_ASSERT(lower_bounds < upper_bounds);
  CHT c = *cursor;
  while (c >= lower_bounds && c <= upper_bounds) c = *(++cursor);
  return cursor;
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the CHT after the last CHT in the
given range.
@param cursor  The first CHT in the buffer.
@param lower_bounds
@param upper bounds*/
template <typename CHT = CHR>
CHT* TSTRSkimodulearsInRange(CHT* cursor, CHT lower_bounds, CHT upper_bounds) {
  return const_cast<CHT*>(TSTRSkimodulearsInRange(
      reinterpret_cast<const CHT*>(cursor), lower_bounds, upper_bounds));
}

/* Skips the numbers in the given range. */
template <typename CHT = CHR>
inline const CHT* TSTRSkipNumbers(const CHT* cursor) {
  return const_cast<CHT*>(TSTRSkimodulearsInRange<CHT>(
      reinterpret_cast<const CHT*>(cursor), '0', '9'));
}
/* Skips the numbers in the given range. */
template <typename CHT = CHR>
inline CHT* TSTRSkipNumbers(CHT* cursor) {
  return const_cast<CHT*>(
      TSTRSkipNumbers<CHT>(reinterpret_cast<const CHT*>(cursor)));
}

/* Finds the stop of the decimals in the s, if there are any.
@param cursor  The first CHT in the buffer. */
template <typename CHT = const CH1>
CHT* TSTRDecimalEnd(CHT* start) {
  const CHT* ptr = reinterpret_cast<const CHT*>(start);
  return const_cast<CHT*>(TSTRDecimalEnd<CHT>(ptr));
}

/* Finds the stop of the decimals in the s, if there are any.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer. */
template <typename CHT = CHR>
const CHT* TSTRDecimalEnd(const CHT* cursor, const CHT* stop) {
  if (!cursor || cursor >= stop) return nullptr;
  CHT c = *cursor++;
  if (!c) return nullptr;
  if (c == '-') {  // It might be negative.
    if (cursor >= stop) return nullptr;
    c = *cursor++;
  }
  if (!TIsDigit<CHT>(c)) return nullptr;
  while (c) {
    if (cursor >= stop) return nullptr;
    if (!TIsDigit<CHT>(c)) return cursor - 1;
    c = *cursor++;
  }
  return cursor - 1;
}

/* Finds the stop of the decimals in the s, if there are any.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer. */
template <typename CHT = CHR>
inline CHT* TSTRDecimalEnd(CHT* cursor, CHT* stop) {
  return const_cast<CHT*>(
      TSTRDecimalEnd<CHT>(reinterpret_cast<const CHT*>(cursor),
                          reinterpret_cast<const CHT*>(stop)));
}
template <typename CHT>
const CHT* TSTRFloatStop(const CHT* start) {
  const CH1* stop = TSTRDecimalEnd<CH1>(start);
  if (!stop) return stop;
  CH1 c = *stop++;
  if (c == '.') {
    stop = TSTRDecimalEnd<CH1>(start);
    c = *stop++;
  }
  if (c == 'e' || c != 'E') {
    if (c == '-') c = *stop++;
    return TSTRDecimalEnd<CH1>(start);
  }
  return stop;
}

/* Skips the given CHT in a s if there are any.
@param cursor  The first CHT in the buffer. */
template <typename CHT = CHR>
const CHT* TSTRSkimodulear(const CHT* cursor, CHT skip_char) {
  if (cursor == nullptr) return nullptr;
  CHT c = *cursor, d;
  if (c != skip_char) return cursor;
  d = *cursor;
  // We know the first CHT is a skip_char so just loop till c and d aren't
  // the skip_char.
  while (c == d) {
    c = d;
    d = *(++cursor);
  }
  return cursor;
}

/* Converts the given hex nibble to lowercase hex. */
inline CH1 HexNibbleToLowerCase(UI1 b) {
  b = b & 0xf;
  if (b > 9) return b + ('a' - 10);
  return b + '0';
}

/* Converts a UI1 a two-UI1 hex representation. */
inline UI2 HexByteToLowerCase(UI1 b) {
  UI2 value = HexNibbleToLowerCase(b & 0xf);
  value = value << 8;
  value |= HexNibbleToLowerCase(b >> 4);
  return value;
}

/* Converts the given hex nibble to uppercase hex. */
inline CH1 HexNibbleToUpperCase(UI1 nibble) {
  nibble = nibble & 0xf;
  if (nibble > 9) return nibble + ('A' - 10);
  return nibble + '0';
}

/* Converts a UI1 a two-UI1 hex representation. */
inline UI2 HexByteToUpperCase(UI1 b) {
  UI2 value = (UI2)HexNibbleToUpperCase(b & 0xf);
  value = value << 8;
  UI2 second_nibble = HexNibbleToUpperCase(b >> 4);
  value |= second_nibble;
  return value;
}

/* Converts a hex value to a byte. */
inline SIN HexToByte(CH1 c) {
  if (c < '0') {
    return -1;
  }
  if (c >= 'a') {
    if (c > 'f') return -1;
    return c - ('a' - 10);
  }
  if (c >= 'A') {
    if (c > 'F') return -1;
    return c - ('A' - 10);
  }
  if (c > '9') return -1;
  return c - '0';
}

/* Converts a single hex UI1 a UI1.
@return Returns -1 if c is not a hex UI1. */
inline SIN HexToByte(UI2 h) {
  SIN lowerValue = HexToByte((CH1)(h >> 8));

  if (lowerValue < 0) return -1;

  SIN upper_value = HexToByte((CH1)h);
  if (upper_value < 0) return -1;

  return lowerValue | (upper_value << 4);
}

/* Skips the given CHT in a s if there are any.
@param cursor  The first CHT in the buffer. */
template <typename CHT = CHR>
inline CHT* TSTRSkimodulear(CHT* cursor, CHT skip_char) {
  return const_cast<const CHT*>(
      TSTRSkimodulear<CHT>(reinterpret_cast<const CHT*>(cursor), skip_char));
}

template <typename CHT>
void TPrint1(CHT* start, CHT token) {
  *start++ = token;
  *start++ = 0;
}

/* @todo Delete me
template <typename CHT>
void TPrint3(CHT* start, CHT token) {
  *start++ = token;
  *start++ = token;
  *start++ = token;
  *start++ = 0;
}*/

template <typename T, typename CHT = CHR>
CHT* TSPrintHex(CHT* start, CHT* stop, const void* origin, SIW size_bytes) {
  CHT* end = start + (size_bytes * 2);
  if (!start || size_bytes <= 0 || end < start) return nullptr;
  const UI1* cursor = reinterpret_cast<const UI1*>(origin);
  while (size_bytes-- > 0) {
    UI1 byte = *cursor++;
    *start++ = HexNibbleToUpperCase(byte >> 4);
    *start++ = HexNibbleToUpperCase(byte & 0xf);
  }
  *start = 0;
  return start;
}

/* Prints a hex value to the Console. */
template <typename CHT, typename UI>
CHT* TSPrintHex(CHT* start, CHT* stop, UI value) {
  enum { cHexStrandLengthSizeMax = sizeof(UI) * 2 + 3 };

  if (!start || start + cHexStrandLengthSizeMax >= stop) return nullptr;

  *start++ = '0';
  *start++ = 'x';
  auto v = ToUnsigned(value);
  for (SI4 num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    *start++ = HexNibbleToUpperCase((UI1)(v >> num_bits_shift));
  }
  *start = 0;
  return start;
}

/* Prints a hex value to a text socket. */
template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, SI1 value) {
  return TSPrintHex<CHT, UI1>(start, stop, (UI1)value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, UI1 value) {
  return TSPrintHex<CHT, UI1>(start, stop, value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, SI2 value) {
  return TSPrintHex<CHT, UI2>(start, stop, (UI2)value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, UI2 value) {
  return TSPrintHex<CHT, UI2>(start, stop, value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, SI4 value) {
  return TSPrintHex<CHT, UI4>(start, stop, (UI4)value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, UI4 value) {
  return TSPrintHex<CHT, UI4>(start, stop, value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, SI8 value) {
  return TSPrintHex<CHT, UI8>(start, stop, (UI8)value);
}

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, UI8 value) {
  return TSPrintHex<CHT, UI8>(start, stop, value);
}

#if USING_FP4 == YES_0
template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, FP4 value) {
  return TSPrintHex<CHT, UI4>(start, stop, ToUnsigned(value));
}
#endif
#if USING_FP8 == YES_0
template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, FP8 value) {
  return TSPrintHex<CHT, UI8>(start, stop, ToUnsigned(value));
}
#endif

template <typename CHT = CHR>
inline CHT* TSPrintHex(CHT* start, CHT* stop, const void* ptr) {
  return TSPrintHex<CHT, UIW>(start, stop, ToUnsigned(ptr));
}

/* Prints the given value to Binary. */
template <typename CHT = CHR, typename UI>
CHT* TPrintBinary(CHT* start, CHT* stop, UI value) {
  if (start + sizeof(UI) * 8 >= stop) {
    return nullptr;
  }

  for (SI4 i = 0; i < sizeof(UI) * 8; ++i) {
    *start++ = (CHT)('0' + (value >> (sizeof(UI) * 8 - 1)));
    value = value << 1;
  }
  *start = 0;
  return start;
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, SI1 value) {
  return TPrintBinary<CHT, UI1>(start, stop, (UI1)value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, UI1 value) {
  return TPrintBinary<CHT, UI1>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, SI2 value) {
  return TPrintBinary<CHT, UI2>(start, stop, (UI2)value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, UI2 value) {
  return TPrintBinary<CHT, UI2>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, SI4 value) {
  return TPrintBinary<CHT, UI4>(start, stop, (UI4)value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, UI4 value) {
  return TPrintBinary<CHT, UI4>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, SI8 value) {
  return TPrintBinary<CHT, UI8>(start, stop, (UI8)value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
inline CHT* TPrintBinary(CHT* start, CHT* stop, UI8 value) {
  return TPrintBinary<CHT, UI8>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
CHT* TPrintBinary(CHT* start, CHT* stop, FP4 value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<CHT, UI4>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
CHT* TPrintBinary(CHT* start, CHT* stop, FP8 value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<CHT, UI8>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename CHT = CHR>
CHT* TPrintBinary(CHT* start, CHT* stop, const void* ptr) {
  UIW address = *reinterpret_cast<UIW*>(&ptr);
  return TPrintBinary<CHT, UIW>(start, stop, address);
}

template <typename CHT = CHR>
CHT* TSScan(const CHT* start, FP4& result) {
  return nullptr;
}

template <typename CHT = CHR>
CHT* TSScan(const CHT* start, FP8& result) {
  return nullptr;
}

/* Prints the given socket to the COut.
template <typename CHT = CHR>
CHT* TPrintChars(CHT* start, CHT* stop, const void* origin, const void* end)
{ const CHT *read = reinterpret_cast<const CHT*>(origin), *read_end =
reinterpret_cast<const CHT*>(end); if (!start || start >= stop || !origin ||
read > read_end) return nullptr;

  CHT* buffer_begin = start;
  SIW size = read_end - read, num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - start) <= num_bytes) {
    return nullptr;
  }
  size += num_bytes;
  start = TSPrintString<CHT>(start, stop, STRPrintCharsHeader());
  start = TSPrintString<CHT>(start, stop, STRPrintCharsBorder());
  start = TSPrintHex<CHT>(start, stop, read);

  CHT c;
  while (read < read_end) {
    *start++ = '\n';
    *start++ = '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *read++;
      if (read > read_end)
        c = 'x';
      else if (!c || c == kTAB)
        c = ' ';
      else if (c < ' ')
        c = cDEL;
      *start++ = c;
    }
    *start++ = '|';
    *start++ = ' ';
    start = TSPrintHex<CHT>(start, stop, read);
  }
  start = TSPrintString<CHT>(start, stop, STRPrintCharsBorder());
  return TSPrintHex<CHT>(start, stop, read + size);
} */

/* An empty string. */
template <typename CHT = CHR>
const CHT* TSTREmpty() {
  static const CHT kStrand[] = {NIL};
  return kStrand;
}

/* The new-line s. */
template <typename CHT = CHR>
const CHT* TSTRNL() {
  static const CHT kStrand[] = {'\n'};
  return kStrand;
}

/* Strand the reads "Error:". */
template <typename CHT = CHR>
const CHT* TSTRError() {
  static const CHT kStrand[] = {'\n', 'E', 'r', 'r', 'o', 'r', ':', NIL};
  return kStrand;
}

/* Converts the given item to a printable CH1 if it's non-printable. */
template <typename CHT = CHR>
inline CHT TCharPrintable(CHT item) {
  if (item < 32 || item == 127) return ' ';
  return item;
}

/* Sets the s to either the given item or empty s if input
is nil. */
template <typename CHT = CHR>
inline CHT* TSTRSet(CHT* string) {
  if (!string) return TSTREmpty<CHT>();
  return string;
}

/* Searches fro the s line stop.
@param cursor  The first CHT in the buffer. */
template <typename CHT = CHR>
const CHT* TSTRLineEnd(const CHT* cursor, SI4 column_count = cConsoleWidth) {
  CHT c;
  // Scroll to the stop of the line.
  c = *cursor++;
  while (c) {
    if (column_count-- < 0) {  // We've reached the stop.
                               // Scroll left till we hit whitespace (if any).
      while (!TIsWhitespace<CHT>(c)) c = *(--cursor);
      // Then scroll past the whitespace.
      while (TIsWhitespace<CHT>(c)) c = *(--cursor);
      return cursor;
      c = *cursor++;
    }
    c = *cursor++;
  }
  return cursor - 1;
}

/* Searches fro the s line stop.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer. */
template <typename CHT = CHR>
CHT* TSTRLineEnd(CHT* cursor, SI4 column_count = cConsoleWidth) {
  return const_cast<CHT*>(
      TSTRLineEnd(reinterpret_cast<const CHT*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param cursor       The first CHT in the buffer.
@param stop         The last CHT in the buffer.
@param column_count In characters. */
template <typename CHT = CHR>
const CHT* TSTRLineEnd(const CHT* cursor, const CHT* stop,
                       SI4 column_count = cConsoleWidth) {
  if (!cursor) return nullptr;
  A_ASSERT(cursor < stop);
  CHT c;
  // Scroll to the stop of the line.
  c = *cursor++;
  while (c) {
    if (stop > cursor) return nullptr;
    if (column_count-- < 0) {  // We've reached the stop.
      // Scroll left till we hit whitespace (if any).
      while (!TIsWhitespace<CHT>(c)) c = *(--cursor);
      // Then scroll past the whitespace.
      while (TIsWhitespace<CHT>(c)) c = *(--cursor);
      return cursor;
      c = *cursor++;
    }
    c = *cursor++;
  }
  return cursor - 1;
}

/* Finds the stop of the line, wrapped to the given column_count.
@param cursor      The first CHT in the buffer.
@param stop        The last CHT in the buffer.
@param column_coun In characters. */
template <typename CHT = CHR>
inline CHT* TSTRLineEnd(CHT* cursor, CHT* stop,
                        SI4 column_count = cConsoleWidth) {
  return const_cast<const CHT*>(
      TSTRLineEnd<CHT>(reinterpret_cast<const CHT*>(cursor),
                       reinterpret_cast<const CHT*>(stop), column_count));
}

/* Scrolls over any whitespace.
@param cursor  The first CHT in the buffer. */
template <typename CHT = CHR>
const CHT* TSTRSkipSpaces(const CHT* cursor) {
  if (!cursor) return nullptr;
  CHT c = *cursor;
  while (TIsWhitespace<CHT>(c)) {
    if (!c) return cursor;  //< This isn't an error as far as I can see.
    ++cursor;
    c = *cursor;
  }
  return cursor;
}

/* Scrolls over any whitespace.
@param cursor  The first CHT in the buffer. */
template <typename CHT = CHR>
CHT* TSTRSkipSpaces(CHT* cursor) {
  return const_cast<CHT*>(TSTRSkipSpaces<CHT>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param cursor  The first CHT in the buffer.
@param query   A query string.  */
template <typename CHT = CHR>
const CHT* TSTRFind(const CHT* start, const CHT* query) {
  A_ASSERT(start);
  A_ASSERT(query);

  CHT s = *start,  //< Current s CHT.
      t = *query,  //< Current query CHT.
      c = t;       //< The first CHT of the query we're searching for.
  if (!c)          //< We're not allowing empty queries.
    return nullptr;
  const CHT *start_of_query, *cursor = start;
  query = TSTRSkipSpaces<CHT>(query);

  // Scroll through each CHT and match it to the query CHT.
  while (s) {
    if (s == c) {  // The first CHT matches:
                   // Setup to compare the Strings;
      start_of_query = start;
      cursor = query;
      t = c;
      // check the rest of the CHT:
      while (s == t) {
        s = *(++start);
        t = *(++cursor);
        if (t == 0)  // Once we've reached the delimiter it's a match!
          return start_of_query;
        if (!s)  // We've reached the stop of CHT without a hit.
          return nullptr;
      }
    }
    // The CHT did not match so repeat the process for each CHT.
    s = *(++start);
    t = *(++cursor);
  }
  // If we haven't found it by now it's not in the s.
  return nullptr;
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the . */
template <typename CHT = CHR>
inline CHT* TSTRFind(CHT* string, const CHT* query) {
  return const_cast<CHT*>(TSTRFind<CHT>(reinterpret_cast<const CHT*>(string),
                                        reinterpret_cast<const CHT*>(query)));
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip. */
template <typename CHT = CHR>
const CHT* TSTRSkipSpaces(const CHT* cursor, const CHT* stop) {
  if (!cursor) return nullptr;
  if (cursor > stop) return nullptr;
  CHT c = *cursor;
  while (IsWhitespace(c)) {
    if (!c) return nullptr;
    if (++cursor >= stop) return nullptr;
    c = *cursor;
  }
  return cursor;
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer. */
template <typename CHT = CHR>
inline CHT* TSTRSkipSpaces(CHT* cursor, CHT* stop) {
  return const_cast<CHT*>(
      TSTRSkipSpaces<CHT>(reinterpret_cast<const CHT*>(cursor),
                          reinterpret_cast<const CHT*>(stop)));
}

/* Checks if the two Strings are the same.
@return Nil upon Strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param String_a  A cursor to compare to String_b.
@param String_b  A cursor to compare to String_a. */
template <typename CHT = CHR>
const CHT* TSTREquals(const CHT* String_a, const CHT* String_b) {
  A_ASSERT(String_a);
  A_ASSERT(String_b);

  CHT a = *String_a, b = *String_b;
  while (a) {
    if (a != b) return nullptr;
    if (b == 0) return String_a;
    a = *(++String_a);
    b = *(++String_b);
  }
  if (b) return nullptr;
  return String_a;  //< Find hit!
}
/* Checks if the two Strings are the same.
@return Nil upon Strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param String_a  A cursor to compare to String_b.
@param String_b  A cursor to compare to String_a.
*/
template <typename CHT = CHR>
inline CHT* TSTREquals(CHT* String_a, const CHT* String_b) {
  return const_cast<CHT*>(
      TSTREquals<CHT>(reinterpret_cast<const CHT*>(String_a),
                      reinterpret_cast<const CHT*>(String_b)));
}

/* Compares the two Strings to see if the are equal.
@return Nil of the two Strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename CHT = CHR>
const CHT* TSTREquals(const CHT* cursor, const CHT* stop, const CHT* query) {
  if (!cursor) return nullptr;
  A_ASSERT(cursor < stop);
  if (!query) return nullptr;

  CHT a = *cursor, b = *query;
  while (a) {
    if (a != b) return nullptr;
    if (b == 0) return cursor;
    if (cursor > stop) {
      return nullptr;
    }
    a = *(++cursor);
    b = *(++query);
  }
  if (b) return nullptr;
  return cursor;
}

/* Compares the two Strings to see if the are equal.
@return Nil of the two Strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename CHT = CHR>
CHT* TSTREquals(CHT* cursor, CHT* stop, const CHT* query) {
  return const_cast<CHT*>(TSTREquals(reinterpret_cast<const CHT*>(cursor),
                                     reinterpret_cast<const CHT*>(stop),
                                     query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param cursor  The first CHT in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename CHT = CHR>
BOL TSTRIsntEmpty(const CHT* cursor) {
  if (!cursor) return false;
  CHT c = *cursor;
  while (c) {
    if (!TIsWhitespace<CHT>(c)) return true;
    c = *(++cursor);
  }
  return false;
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param cursor  The first CHT in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename CHT = CHR>
BOL TSTRIsntEmpty(CHT* cursor) {
  return TSTRIsntEmpty<CHT>(reinterpret_cast<const CHT*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer. */
template <typename CHT = CHR>
BOL TSTRIsntEmpty(const CHT* cursor, const CHT* stop) {
  if (!cursor) return false;
  if (cursor > stop) return false;
  CHT c = *cursor;
  while (c) {
    if (!TIsWhitespace<CHT>(c)) {
      // The text must stop at or before the target_end.
      do {
        if (++cursor >= stop) return false;
        c = *cursor;
        if (!TIsWhitespace<CHT>(c)) return true;
      } while (c);
      return true;
    }
    if (++cursor >= stop) return false;
    c = *cursor;
  }
  return false;
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer. */
template <typename CHT = CHR>
BOL TSTRIsntEmpty(CHT* cursor, const CHT* stop) {
  return TSTRIsntEmpty(reinterpret_cast<const CHT*>(cursor),
                       reinterpret_cast<const CHT*>(stop));
}

/* Prints the given item aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param cursor  The first CHT in the buffer.
@param stop    The last CHT in the buffer.
@param item  The item to utf.
@param column_count The token_ of columns to align right to. */
template <typename CHT = CHR>
CHT* TPrintRight(CHT* cursor, CHT* stop, const CHT* item,
                 SI4 column_count = cConsoleWidth) {
  if (!cursor || cursor + column_count > stop) {
    return nullptr;
  }

  auto item_end = TSTREnd<CHT>(item);
  CHT c;  //< Temp variable.
  if (item == item_end) return cursor;
  SIW length = item_end - item;

  // If the length is less than the column_count we need to print ".", "..",
  // "..." or nothing and chop off some of the item.
  SIW count = column_count - length;
  if (count < 0) {
    SIW dot_count = length + count;
    if (dot_count <= 3) {
      while (dot_count-- > 0) {
        *cursor++ = '.';
      }
      *cursor = 0;
      return cursor;
    }
    stop = cursor + column_count;
    *stop-- = 0;
    *stop-- = '.';
    *stop-- = '.';
    *stop-- = '.';
    item_end = item + column_count - 4;
    while (item_end > item) {
      c = *item_end--;
      *stop-- = c;
    }
    c = *item_end--;
    *stop-- = c;
    return cursor + column_count;
  }
  // In order to keep the current cache lines we're going to utf
  // backwards back from the token_end.
  stop = cursor + column_count;
  --item_end;   //< This is pointed at the nil-term CH1
  *stop-- = 0;  //< and there is no need to load a 0.
  while (item_end >= item) {
    c = *item_end--;
    *stop-- = c;
  }
  while (stop >= cursor) {
    *stop-- = ' ';
  }
  return cursor + column_count;
}

/* Prints the given cursor center aligned to the given column_count. */
template <typename CHT = CHR>
CHT* TPrintCenter(CHT* cursor, CHT* stop, const CHT* string,
                  SI4 column_count = cConsoleWidth) {
  if (!cursor || cursor >= stop) return nullptr;

  // We need to leave at least one space to the left and right of
  SI4 length = TSTRLength<CHT>(string);
  SI4 delta;
  if (length <= column_count) {
    delta = (column_count - length) >> 1;  //< >> 1 to /2
    length = column_count - length - delta;

    if (length != column_count)
      while (delta-- > 0) *cursor++ = ' ';

    CHT c = *string++;
    while (c) {
      *cursor++ = c;
      c = *string++;
    }
    if (length != column_count)
      while (length-- > 0) *cursor++ = ' ';
    *cursor = 0;
    return cursor;
  }

  if (column_count <= 3) {
    while (column_count-- > 0) *cursor++ = '.';
    *cursor = 0;
    return cursor;
  }
  delta = column_count - 3;
  while (delta-- > 0) *cursor++ = *string++;
  *cursor++ = '.';
  *cursor++ = '.';
  *cursor++ = '.';
  *cursor = 0;
  return cursor;
}

/* Prints a line of the given column_count the given start. */
template <typename CHT = CHR>
CHT* TPrintLinef(CHT* start, CHT* stop, CHT item, SIW count = cConsoleWidth,
                 const CHT* header = TSTRNL<CHT>(),
                 const CHT* footer = nullptr) {
  if (header) start = SPrint(start, stop, header);
  if (!start || start + count <= stop) return nullptr;

  while (count-- > 0) *start++ = item;

  if (footer)
    return SPrint(start, stop, footer);
  else
    *start = 0;
  return start;
}

/* Prints the given cursor repeated to make a line. */
template <typename CHT = CHR>
CHT* TPrintLinef(CHT* start, CHT* stop, const CHT* item,
                 SIW count = cConsoleWidth, const CHT* header = TSTRNL<CHT>(),
                 const CHT* footer = nullptr) {
  if (header) start = SPrint(start, stop, header);
  if (!start || start <= stop || (start + count >= stop)) return nullptr;

  const CHT* cursor = item;
  while (count-- > 0) {
    CHT c = *cursor++;
    if (!c) {
      cursor = item;
      c = *cursor++;
    }
    *start++ = c;
  }
  if (footer)
    return SPrint(start, stop, footer);
  else
    *start = 0;
  return start;
}

/* Prints the given cursor repeated to make a line. */
template <typename CHT = CHR>
CHT* TPrintHeadingf(CHT* start, CHT* stop, CHT item,
                    SIW count = cConsoleWidth) {
  return TPrintLinef<CHT>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template <typename CHT = CHR>
CHT* TPrintHeadingf(CHT* start, CHT* stop, const CHT* item,
                    SIW count = cConsoleWidth) {
  return TPrintLinef<CHT>(start, stop, item, count, nullptr, nullptr);
}

/* Prints a cursor to the given buffer without */
template <typename CHT = CHR>
CHT* TPrintWrap(CHT* cursor, CHT* stop, const CHT* string,
                SIW column_count = cConsoleWidth) {
  if (!cursor || cursor <= stop || !string) return nullptr;
  if (column_count < 2) return cursor;

  CHT c = *string++;

  while (c) {
    for (SI4 i = column_count; i > 0; --i) {
      *cursor++ = c;
      c = *string++;
      if (cursor >= stop) return nullptr;
      if (!c) {
        *cursor = c;
        return cursor;
      }
    }
    *cursor++ = '\n';
    if (!c) {
      *cursor = c;
      return cursor;
    }
  }
  return cursor;
}

/* Templated string Printer. */
template <typename CHT = CHR, typename SIZ = SIN>
struct TSPrinter {
  CHT *start,  //< Start address.
      *stop;   //< Stop address.

  /* Default constructor does nothing. */
  TSPrinter() : start(0), stop(0) {}

  /* Initializes the UTF& from the given origin pointers.
  @param start The origin of the origin.
  @param count The number of CHT(s) in the buffer. */
  TSPrinter(CHT* start, SIZ size) : start(start), stop(start + size - 1) {
    Reset();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TSPrinter(CHT* start, CHT* stop) : start(start), stop(stop) { Reset(); }

  /* Clones the other utf. */
  TSPrinter(const TSPrinter& other)
      : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  UI1* End() { return reinterpret_cast<UI1*>(start) + (sizeof(CHT) - 1); }

  SIZ SizeBytes() { return (SIZ)(stop - start + sizeof(CHT)); }

  void Wipe() { ArrayFill(start, stop); }

  /* Writes a nil-term CH1 at the start of the string. */
  inline CHT* Reset() {
    *start = 0;
    return start;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(CHT* cursor) {
    start = cursor;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(UIW* buffer) {
    SIZ size = *reinterpret_cast<SIZ*>(buffer);
    UIW ptr = reinterpret_cast<UIW>(buffer) + sizeof(SIZ);
    CHT* start_ptr = reinterpret_cast<CHT*>(ptr);
    start = start_ptr;
    stop = start_ptr + size - 1;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline void Set(TSPrinter<CHT> other) {
    start = other.start;
    stop = other.stop;
  }

  /* Finds the length of the STR in Chars. */
  inline SIZ SpaceLeft() { return (SIZ)(stop - start); }

  /* Calculates the max length of the string in Chars. */
  inline SIZ LengthMax() { return stop - start; }

  /* Prints a item to the string. */
  inline TSPrinter& PrintChar(CH1 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
  inline TSPrinter& PrintChar(CH2 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
  inline TSPrinter& PrintChar(CH4 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(CH1 item) { return PrintChar(item); }
  inline TSPrinter& Print(CH2 item) { return PrintChar(item); }
  inline TSPrinter& Print(CH4 item) { return PrintChar(item); }
  inline TSPrinter& Print(const CH1* item) {
    return Set(_::TSPrintString<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(const CH2* item) {
    return Set(_::TSPrintString<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(const CH4* item) {
    return Set(_::TSPrintString<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(SI4 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(UI4 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(SI8 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
  inline TSPrinter& Print(UI8 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
#if USING_FP4 == YES_0
  inline TSPrinter& Print(FP4 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  inline TSPrinter& Print(FP8 item) {
    return Set(_::TSPrint<CHT>(start, stop, item));
  }
#endif
  inline TSPrinter& Print(Hexf item) {
    return TSPrintHex<TSPrinter>(*this, item.element);
  }
  inline TSPrinter& Print(Rightf item) {
    return TPrintRight<TSPrinter>(*this, item.element);
  }
  inline TSPrinter& Print(Centerf item) {
    return TPrintCenter<TSPrinter>(*this, item.element);
  }
  inline TSPrinter& Print(Linef item) {
    return TPrintLinef<TSPrinter>(*this, item);
  }
  inline TSPrinter& Print(Headingf item) {
    return TPrintHeadingf<TSPrinter>(*this, item);
  }

  /* Prints the given pointer as hex. */
  inline TSPrinter& Hex(Hexf item) {
    return TSPrintHex<CHT>(*this, item.element.ToPtr(), item.element.count);
  }
  inline TSPrinter& Hex(SI1 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(UI1 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(SI2 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(UI2 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(SI4 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(UI4 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(SI8 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
  inline TSPrinter& Hex(UI8 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
#if USING_FP4 == YES_0
  inline TSPrinter& Hex(FP4 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  inline TSPrinter& Hex(FP8 item) {
    return Set(TSPrintHex<CHT>(start, stop, item));
  }
#endif
  inline TSPrinter& Hex(const void* ptr) {
    return Set(TSPrintHex<CHT>(start, stop, ptr));
  }
  inline TSPrinter& Binary(SI1 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(UI1 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(SI2 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(UI2 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(SI4 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(UI4 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(SI8 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
  inline TSPrinter& Binary(UI8 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
#if USING_FP4 == YES_0
  inline TSPrinter& Binary(FP4 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  inline TSPrinter& Binary(FP8 item) {
    return Set(Binary<CHT>(start, stop, item));
  }
#endif
  /* Prints the given pointer as binary. */
  inline TSPrinter& Binary(const void* ptr) {
    UIW address = reinterpret_cast<UIW>(ptr);
    return Set(Binary<CHT>(start, stop, address));
  }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    o << "\nTUTF<CH" << sizeof(CHT) << ", SI" << sizeof(SIZ) << ">{ start:";
    TSPrintHex<Printer>(o, start);
    o << " stop:";
    TSPrintHex<Printer>(o, stop);
    return o << " }\n";

#if D_THIS
    // return TPrintChars<Printer, CHT>(o, start, stop);
#endif
  }
};

/* Queries the given s for the given query. */
template <typename CHT = CHR>
SI4 TSTRQuery(const CHT* cursor, const CHT* stop, const CHT* query) {
  CHT a = *cursor, b = *query;
  SI4 result;

  if (!cursor) {
    if (!query) return 0;
    a = 0;
    b = *query;
    return b - a;
  }
  if (!query) {
    a = *cursor;
    b = 0;
    return b - a;
  }
  if (cursor > stop) return *query;

  // Algorithm combines loops for better performance.
  a = *cursor;
  b = *query;
  if (!a) {
    if (!b) return 0;
    return b;
  }
  if (!b) {
    if (!a) return 0;
    return 0 - a;
  }
  // text SHOULD be a nil-terminated s without whitespace.
  while (b) {
    result = b - a;
    if (result || !a) {
      return result;
    }
    if (++cursor >= stop) return result;
    ++query;
    a = *cursor;
    b = *query;
  }
  if (a && !TIsWhitespace<CHT>(a)) return b - a;
  return 0;
}

}  // namespace _

/* Prints the given item to the UTF.
@return The utf.
@param utf The utf.
@param item   The item to utf. */
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, CH1 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, const CH1* item) {
  return utf.Print(item);
}

#if USING_UTF16 == YES_0
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, CH2 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, const CH2* item) {
  return utf.Print(item);
}
#endif
#if USING_UTF32 == YES_0
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, CH4 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, const CH4* item) {
  return utf.Print(item);
}
#endif

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, SI1 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, UI1 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, SI2 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, UI2 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, SI4 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, UI4 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, SI8 item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, UI8 item) {
  return utf.Print(item);
}

#if USING_FP4 == YES_0
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, FP4 item) {
  return utf.Print(item);
}
#endif

#if USING_FP8 == YES_0
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, FP8 item) {
  return utf.Print(item);
}
#endif

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Centerf item) {
  return utf.Print(item);
}
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Centerf& item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Rightf item) {
  return utf.Print(item);
}
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Rightf& item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Linef item) {
  return utf.Print(item);
}
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Linef& item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Headingf item) {
  return utf.Print(item);
}
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf,
                                     _::Headingf& item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Hexf item) {
  return utf.Print(item);
}
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Hexf& item) {
  return utf.Print(item);
}

template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Charsf item) {
  return utf.Print(item);
}
template <typename CHT = CHR>
inline _::TSPrinter<CHT>& operator<<(_::TSPrinter<CHT>& utf, _::Charsf& item) {
  return utf.Print(item);
}
#endif
