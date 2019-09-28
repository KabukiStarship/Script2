/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /uniprinter.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

/* There is a different set of string printing utilities because it's a little
faster. */

#pragma once
#include <_config.h>

#ifndef SCRIPT2_STRING_CODE_HEADER
#define SCRIPT2_STRING_CODE_HEADER 1

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
template <typename Char = CHR>
SIN TSTRCompare(const Char* string, const Char* other_String,
                Char delimiter = 0) {
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
template <typename Char = CHR>
inline const Char* TSTREnd(const Char* string, CH1 delimiter = 0) {
  while (*string++ != delimiter)
    ;
  return string - 1;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename Char = CHR>
inline Char* TSTREnd(Char* string, Char delimiter = 0) {
  return const_cast<Char*>(
      TSTREnd<Char>(reinterpret_cast<const Char*>(string), delimiter));
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename Char = CHR, typename SIZ = SIN>
SIZ TSTRLength(const Char* string) {
  return (SIZ)(TSTREnd<Char>(string) - string);
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM Strings with a nil-term
CH1. */
template <typename Char = CHR, typename SIZ = SIN>
inline SIZ TSTRLength(Char* string) {
  return TSTRLength<Char>(reinterpret_cast<const Char*>(string));
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
// CH1* SScan (CH1* string, CH4& item) in c_string.h

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

template <typename Char>
Char* TScanChar(Char* cursor, Char& c) {}

/* Converts the given item to lowercase if it is uppercase. */
template <typename Char>
inline Char TToLower(Char c) {
  if (c >= 'A' && c <= 'Z') c -= 32;
  return c;
}

inline CH1 ToLower(CH1 value) { return TToLower<CH1>(value); }
inline CH2 ToLower(CH2 value) { return TToLower<CH2>(value); }
inline CH4 ToLower(CH4 value) { return TToLower<CH4>(value); }

/* Checks if the given item is whitespace. */
template <typename Char = CHR>
inline BOL TIsWhitespace(Char item) {
  return item <= ' ';
}

template <typename Char>
SIN TIsYesNo(const Char* string) {
  if (!string) return 0;
  Char c = TToLower<Char>(*string++);
  SIN result;
  if (c == 'y')
    result = 1;
  else if (c == 'n')
    result = -1;
  else
    return 0;
  c = *string++;
  if (TIsWhitespace<Char>(c)) return result;
  c = TToLower<Char>(c);
  if (c == 'o') return -(SIN)TIsWhitespace<Char>(*string++);
  if (TToLower<Char>(*string++) != 'e') return 0;
  if (TToLower<Char>(*string++) != 's') return 0;
  return (SIN)TIsWhitespace<Char>(*string++);
}

/* Checks if the given CH1 is a digit of a number_.
@return True if it is a digit. */
template <typename Char = CHR>
BOL TIsDigit(Char c) {
  return (c >= '0') && (c <= '9');
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char = CHR>
const Char* TScanSigned(const Char* string, SI& item) {
  if (!string) return nullptr;
  SI sign;
  const Char* cursor = string;
  Char c = *cursor++;
  if (c == '-') {
    c = *string++;
    sign = -1;
  } else {
    sign = 1;
  }
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* stop = cursor;  // Store stop to return.
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
template <typename SI = SIW, typename UI = UIW, typename Char = CHR>
Char* TScanSigned(Char* string, SI& item) {
  const Char* ptr = reinterpret_cast<const Char*>(string);
  return const_cast<Char*>(TScanSigned<SI, UI, Char>(ptr, item));
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The SI to write the scanned SI. */
template <typename Char = CHR>
const Char* TSScan(const Char* string, SI1& item) {
  return TScanSigned<SI1, UI1, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, SI1& item) {
  return TScanSigned<SI1, UI1, Char>(string, item);
}
template <typename Char = CHR>
const Char* TSScan(const Char* string, SI2& item) {
  return TScanSigned<SI2, UI2, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, SI2& item) {
  return TScanSigned<SI2, UI2, Char>(string, item);
}
template <typename Char = CHR>
const Char* TSScan(const Char* string, SI4& item) {
  return TScanSigned<SI4, UI4, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, SI4& item) {
  return TScanSigned<SI4, UI4, Char>(string, item);
}
template <typename Char = CHR>
const Char* TSScan(const Char* string, SI8& item) {
  return TScanSigned<SI8, UI8, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, SI8& item) {
  return TScanSigned<SI8, UI8, Char>(string, item);
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param item The UI to write the scanned UI. */
template <typename UI, typename Char = CHR>
const Char* TScanUnsigned(const Char* string, UI& item) {
  if (!string) return nullptr;
  const Char* cursor = string;
  Char c = *cursor++;
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* stop = cursor;  // Store stop to return.
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
template <typename UI, typename Char = CHR>
Char* TScanUnsigned(Char* string, UI& item) {
  const Char* ptr = reinterpret_cast<const Char*>(string);
  return const_cast<Char*>(TScanUnsigned<UI, Char>(ptr, item));
}

/* Scans item from the string.
@return Nil upon failure. */
template <typename Char = CHR>
const Char* TSScan(const Char* string, UI1& item) {
  return TScanUnsigned<UI1, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, UI1& item) {
  return TScanUnsigned<UI1, Char>(string, item);
}
template <typename Char = CHR>
const Char* TSScan(const Char* string, UI2& item) {
  return TScanUnsigned<UI2, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, UI2& item) {
  return TScanUnsigned<UI2, Char>(string, item);
}
template <typename Char = CHR>
const Char* TSScan(const Char* string, UI4& item) {
  return TScanUnsigned<UI4, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, UI4& item) {
  return TScanUnsigned<UI4, Char>(string, item);
}
template <typename Char = CHR>
const Char* TSScan(const Char* string, UI8& item) {
  return TScanUnsigned<UI8, Char>(string, item);
}
template <typename Char = CHR>
Char* TSScan(Char* string, UI8& item) {
  return TScanUnsigned<UI8, Char>(string, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param string The beginning of the socket.
@param count  The element count.
@param item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, Char* stop, CH1 item) {
  if (!string || string >= stop) return nullptr;
  *string++ = item;
  *string = 0;
  return string;
}
/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param string The beginning of the socket.
@param count  The element count.
@param item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, SIW count, CH1 item) {
  return SPrint(string, string + count - 1, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param string The beginning of the socket.
@param count  The element count.
@param item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, SIW count, CH2 item) {
  return TSPrint<Char>(string, string + count - 1, item);
}

/* Prints the given item to the string.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param count  The number of Chars in the string buffer.
@param item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, SIW count, CH4 item) {
  return TSPrint<Char>(string, string + count - 1, item);
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
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param string  The beginning of the socket.
 @param stop    The last Char in the socket.
 @param item    The item to print. */
template <typename Char, typename CHE>
Char* TSPrintString(Char* string, Char* stop, const CHE* item) {
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

template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, const CH1* item) {
  return TSPrintString<Char, CH1>(start, stop, item);
}

#if USING_UTF16 == YES_0
/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param string  The beginning of the socket.
 @param stop    The last Char in the socket.
 @param item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename Char = CHR>
Char* TSPrintString(Char* string, Char* stop, const CH2* item) {
  return TSPrintString<Char, CH2>(string, stop, item);
}
template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, const CH2* item) {
  return TSPrintString<Char>(start, stop, item);
}
#endif

#if USING_UTF32 == YES_0
/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param start  The beginning of the socket.
 @param stop    The last Char in the socket.
 @param item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename Char = CHR>
Char* TSPrintString(Char* start, Char* stop, const CH4* item) {
  return TSPrintString<Char, CH4>(start, stop, item);
}

template <typename Char = CHR>
inline Char* TSPrint(Char* start, Char* stop, const CH4* item) {
  return TSPrintString<Char>(start, stop, item);
}
#endif

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param start    The beginning of the socket.
@param size      The size of the socket in Char(s).
@param item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, const CH1* item) {
  return TSPrintString<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param start    The beginning of the socket.
@param size      The size of the socket in Char(s).
@param item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
Char* TSPrint(Char* start, SIW size, const CH2* item) {
  return TSPrintString<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param start    The beginning of the socket.
@param size      The size of the socket in Char(s).
@param item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
Char* TSPrint(Char* start, SIW size, const CH4* item) {
  return TSPrintString<Char>(start, start + size - 1, item);
}

/* Finds the end of a decimal number of the given string.
@return Nil if the string doesn't contain a decimal or is nil.
@param start The start of the string to search. */
template <typename Char = const CH1>
const Char* TSTRDecimalEnd(const Char* start) {
  if (!start) return start;
  Char c = *start++;
  if (c == '-') c = *start++;
  if (c < '0' || c > '9') return nullptr;
  c = *start++;
  while (TIsDigit<Char>(c)) {
    c = *start++;
    if (c <= 0) return start - 1;
  }
  return start - 1;
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the Char after the last Char in the
given range.
@param cursor  The first Char in the buffer.
@param lower_bounds
@param upper bounds*/
template <typename Char = CHR>
const Char* TSTRSkimodulearsInRange(const Char* cursor, Char lower_bounds,
                                    Char upper_bounds) {
  A_ASSERT(cursor);
  A_ASSERT(lower_bounds < upper_bounds);
  Char c = *cursor;
  while (c >= lower_bounds && c <= upper_bounds) c = *(++cursor);
  return cursor;
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the Char after the last Char in the
given range.
@param cursor  The first Char in the buffer.
@param lower_bounds
@param upper bounds*/
template <typename Char = CHR>
Char* TSTRSkimodulearsInRange(Char* cursor, Char lower_bounds,
                              Char upper_bounds) {
  return const_cast<Char*>(TSTRSkimodulearsInRange(
      reinterpret_cast<const Char*>(cursor), lower_bounds, upper_bounds));
}

/* Skips the numbers in the given range. */
template <typename Char = CHR>
inline const Char* TSTRSkipNumbers(const Char* cursor) {
  return const_cast<Char*>(TSTRSkimodulearsInRange<Char>(
      reinterpret_cast<const Char*>(cursor), '0', '9'));
}
/* Skips the numbers in the given range. */
template <typename Char = CHR>
inline Char* TSTRSkipNumbers(Char* cursor) {
  return const_cast<Char*>(
      TSTRSkipNumbers<Char>(reinterpret_cast<const Char*>(cursor)));
}

/* Finds the stop of the decimals in the s, if there are any.
@param cursor  The first Char in the buffer. */
template <typename Char = const CH1>
Char* TSTRDecimalEnd(Char* start) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TSTRDecimalEnd<Char>(ptr));
}

/* Finds the stop of the decimals in the s, if there are any.
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRDecimalEnd(const Char* cursor, const Char* stop) {
  if (!cursor || cursor >= stop) return nullptr;
  Char c = *cursor++;
  if (!c) return nullptr;
  if (c == '-') {  // It might be negative.
    if (cursor >= stop) return nullptr;
    c = *cursor++;
  }
  if (!TIsDigit<Char>(c)) return nullptr;
  while (c) {
    if (cursor >= stop) return nullptr;
    if (!TIsDigit<Char>(c)) return cursor - 1;
    c = *cursor++;
  }
  return cursor - 1;
}

/* Finds the stop of the decimals in the s, if there are any.
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer. */
template <typename Char = CHR>
inline Char* TSTRDecimalEnd(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TSTRDecimalEnd<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop)));
}
template <typename Char>
const Char* TSTRFloatStop(const Char* start) {
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

/* Skips the given Char in a s if there are any.
@param cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRSkimodulear(const Char* cursor, Char skip_char) {
  if (cursor == nullptr) return nullptr;
  Char c = *cursor, d;
  if (c != skip_char) return cursor;
  d = *cursor;
  // We know the first Char is a skip_char so just loop till c and d aren't
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

/* Skips the given Char in a s if there are any.
@param cursor  The first Char in the buffer. */
template <typename Char = CHR>
inline Char* TSTRSkimodulear(Char* cursor, Char skip_char) {
  return const_cast<const Char*>(
      TSTRSkimodulear<Char>(reinterpret_cast<const Char*>(cursor), skip_char));
}

template <typename Char>
void TPrint1(Char* start, Char token) {
  *start++ = token;
  *start++ = 0;
}

/* @todo Delete me
template <typename Char>
void TPrint3(Char* start, Char token) {
  *start++ = token;
  *start++ = token;
  *start++ = token;
  *start++ = 0;
}*/

template <typename T, typename Char = CHR>
Char* TSPrintHex(Char* start, Char* stop, const void* origin, SIW size_bytes) {
  Char* end = start + (size_bytes * 2);
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
template <typename Char, typename UI>
Char* TSPrintHex(Char* start, Char* stop, UI value) {
  enum { kHexStrandLengthSizeMax = sizeof(UI) * 2 + 3 };

  if (!start || start + kHexStrandLengthSizeMax >= stop) return nullptr;

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
template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, SI1 value) {
  return TSPrintHex<Char, UI1>(start, stop, (UI1)value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, UI1 value) {
  return TSPrintHex<Char, UI1>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, SI2 value) {
  return TSPrintHex<Char, UI2>(start, stop, (UI2)value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, UI2 value) {
  return TSPrintHex<Char, UI2>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, SI4 value) {
  return TSPrintHex<Char, UI4>(start, stop, (UI4)value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, UI4 value) {
  return TSPrintHex<Char, UI4>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, SI8 value) {
  return TSPrintHex<Char, UI8>(start, stop, (UI8)value);
}

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, UI8 value) {
  return TSPrintHex<Char, UI8>(start, stop, value);
}

#if USING_FP4 == YES_0
template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, FP4 value) {
  return TSPrintHex<Char, UI4>(start, stop, ToUnsigned(value));
}
#endif
#if USING_FP8 == YES_0
template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, FP8 value) {
  return TSPrintHex<Char, UI8>(start, stop, ToUnsigned(value));
}
#endif

template <typename Char = CHR>
inline Char* TSPrintHex(Char* start, Char* stop, const void* ptr) {
  return TSPrintHex<Char, UIW>(start, stop, ToUnsigned(ptr));
}

/* Prints the given value to Binary. */
template <typename Char = CHR, typename UI>
Char* TPrintBinary(Char* start, Char* stop, UI value) {
  if (start + sizeof(UI) * 8 >= stop) {
    return nullptr;
  }

  for (SI4 i = 0; i < sizeof(UI) * 8; ++i) {
    *start++ = (Char)('0' + (value >> (sizeof(UI) * 8 - 1)));
    value = value << 1;
  }
  *start = 0;
  return start;
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI1 value) {
  return TPrintBinary<Char, UI1>(start, stop, (UI1)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI1 value) {
  return TPrintBinary<Char, UI1>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI2 value) {
  return TPrintBinary<Char, UI2>(start, stop, (UI2)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI2 value) {
  return TPrintBinary<Char, UI2>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI4 value) {
  return TPrintBinary<Char, UI4>(start, stop, (UI4)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI4 value) {
  return TPrintBinary<Char, UI4>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI8 value) {
  return TPrintBinary<Char, UI8>(start, stop, (UI8)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI8 value) {
  return TPrintBinary<Char, UI8>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
Char* TPrintBinary(Char* start, Char* stop, FP4 value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<Char, UI4>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
Char* TPrintBinary(Char* start, Char* stop, FP8 value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<Char, UI8>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
Char* TPrintBinary(Char* start, Char* stop, const void* ptr) {
  UIW address = *reinterpret_cast<UIW*>(&ptr);
  return TPrintBinary<Char, UIW>(start, stop, address);
}

template <typename Char = CHR>
Char* TSScan(const Char* start, FP4& result) {
  return nullptr;
}

template <typename Char = CHR>
Char* TSScan(const Char* start, FP8& result) {
  return nullptr;
}

/* Prints the given socket to the COut.
template <typename Char = CHR>
Char* TPrintChars(Char* start, Char* stop, const void* origin, const void* end)
{ const Char *read = reinterpret_cast<const Char*>(origin), *read_end =
reinterpret_cast<const Char*>(end); if (!start || start >= stop || !origin ||
read > read_end) return nullptr;

  Char* buffer_begin = start;
  SIW size = read_end - read, num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - start) <= num_bytes) {
    return nullptr;
  }
  size += num_bytes;
  start = TSPrintString<Char>(start, stop, STRPrintCharsHeader());
  start = TSPrintString<Char>(start, stop, STRPrintCharsBorder());
  start = TSPrintHex<Char>(start, stop, read);

  Char c;
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
        c = kDEL;
      *start++ = c;
    }
    *start++ = '|';
    *start++ = ' ';
    start = TSPrintHex<Char>(start, stop, read);
  }
  start = TSPrintString<Char>(start, stop, STRPrintCharsBorder());
  return TSPrintHex<Char>(start, stop, read + size);
} */

/* An empty string. */
template <typename Char = CHR>
const Char* TSTREmpty() {
  static const Char kStrand[] = {NIL};
  return kStrand;
}

/* The new-line s. */
template <typename Char = CHR>
const Char* TSTRNL() {
  static const Char kStrand[] = {'\n'};
  return kStrand;
}

/* Strand the reads "Error:". */
template <typename Char = CHR>
const Char* TSTRError() {
  static const Char kStrand[] = {'\n', 'E', 'r', 'r', 'o', 'r', ':', NIL};
  return kStrand;
}

/* Converts the given item to a printable CH1 if it's non-printable. */
template <typename Char = CHR>
inline Char TCharPrintable(Char item) {
  if (item < 32 || item == 127) return ' ';
  return item;
}

/* Sets the s to either the given item or empty s if input
is nil. */
template <typename Char = CHR>
inline Char* TSTRSet(Char* string) {
  if (!string) return TSTREmpty<Char>();
  return string;
}

/* Searches fro the s line stop.
@param cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRLineEnd(const Char* cursor, SI4 column_count = kConsoleWidth) {
  Char c;
  // Scroll to the stop of the line.
  c = *cursor++;
  while (c) {
    if (column_count-- < 0) {  // We've reached the stop.
                               // Scroll left till we hit whitespace (if any).
      while (!TIsWhitespace<Char>(c)) c = *(--cursor);
      // Then scroll past the whitespace.
      while (TIsWhitespace<Char>(c)) c = *(--cursor);
      return cursor;
      c = *cursor++;
    }
    c = *cursor++;
  }
  return cursor - 1;
}

/* Searches fro the s line stop.
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer. */
template <typename Char = CHR>
Char* TSTRLineEnd(Char* cursor, SI4 column_count = kConsoleWidth) {
  return const_cast<Char*>(
      TSTRLineEnd(reinterpret_cast<const Char*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param cursor       The first Char in the buffer.
@param stop         The last Char in the buffer.
@param column_count In characters. */
template <typename Char = CHR>
const Char* TSTRLineEnd(const Char* cursor, const Char* stop,
                        SI4 column_count = kConsoleWidth) {
  if (!cursor) return nullptr;
  A_ASSERT(cursor < stop);
  Char c;
  // Scroll to the stop of the line.
  c = *cursor++;
  while (c) {
    if (stop > cursor) return nullptr;
    if (column_count-- < 0) {  // We've reached the stop.
      // Scroll left till we hit whitespace (if any).
      while (!TIsWhitespace<Char>(c)) c = *(--cursor);
      // Then scroll past the whitespace.
      while (TIsWhitespace<Char>(c)) c = *(--cursor);
      return cursor;
      c = *cursor++;
    }
    c = *cursor++;
  }
  return cursor - 1;
}

/* Finds the stop of the line, wrapped to the given column_count.
@param cursor      The first Char in the buffer.
@param stop        The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CHR>
inline Char* TSTRLineEnd(Char* cursor, Char* stop,
                         SI4 column_count = kConsoleWidth) {
  return const_cast<const Char*>(
      TSTRLineEnd<Char>(reinterpret_cast<const Char*>(cursor),
                        reinterpret_cast<const Char*>(stop), column_count));
}

/* Scrolls over any whitespace.
@param cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRSkipSpaces(const Char* cursor) {
  if (!cursor) return nullptr;
  Char c = *cursor;
  while (TIsWhitespace<Char>(c)) {
    if (!c) return cursor;  //< This isn't an error as far as I can see.
    ++cursor;
    c = *cursor;
  }
  return cursor;
}

/* Scrolls over any whitespace.
@param cursor  The first Char in the buffer. */
template <typename Char = CHR>
Char* TSTRSkipSpaces(Char* cursor) {
  return const_cast<Char*>(TSTRSkipSpaces<Char>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param cursor  The first Char in the buffer.
@param query   A query string.  */
template <typename Char = CHR>
const Char* TSTRFind(const Char* start, const Char* query) {
  A_ASSERT(start);
  A_ASSERT(query);

  Char s = *start,  //< Current s Char.
      t = *query,   //< Current query Char.
      c = t;        //< The first Char of the query we're searching for.
  if (!c)           //< We're not allowing empty queries.
    return nullptr;
  const Char *start_of_query, *cursor = start;
  query = TSTRSkipSpaces<Char>(query);

  // Scroll through each Char and match it to the query Char.
  while (s) {
    if (s == c) {  // The first Char matches:
                   // Setup to compare the Strings;
      start_of_query = start;
      cursor = query;
      t = c;
      // check the rest of the Char:
      while (s == t) {
        s = *(++start);
        t = *(++cursor);
        if (t == 0)  // Once we've reached the delimiter it's a match!
          return start_of_query;
        if (!s)  // We've reached the stop of Char without a hit.
          return nullptr;
      }
    }
    // The Char did not match so repeat the process for each Char.
    s = *(++start);
    t = *(++cursor);
  }
  // If we haven't found it by now it's not in the s.
  return nullptr;
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the . */
template <typename Char = CHR>
inline Char* TSTRFind(Char* string, const Char* query) {
  return const_cast<Char*>(
      TSTRFind<Char>(reinterpret_cast<const Char*>(string),
                     reinterpret_cast<const Char*>(query)));
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip. */
template <typename Char = CHR>
const Char* TSTRSkipSpaces(const Char* cursor, const Char* stop) {
  if (!cursor) return nullptr;
  if (cursor > stop) return nullptr;
  Char c = *cursor;
  while (IsWhitespace(c)) {
    if (!c) return nullptr;
    if (++cursor >= stop) return nullptr;
    c = *cursor;
  }
  return cursor;
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip.
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer. */
template <typename Char = CHR>
inline Char* TSTRSkipSpaces(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TSTRSkipSpaces<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop)));
}

/* Checks if the two Strings are the same.
@return Nil upon Strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param String_a  A cursor to compare to String_b.
@param String_b  A cursor to compare to String_a. */
template <typename Char = CHR>
const Char* TSTREquals(const Char* String_a, const Char* String_b) {
  A_ASSERT(String_a);
  A_ASSERT(String_b);

  Char a = *String_a, b = *String_b;
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
template <typename Char = CHR>
inline Char* TSTREquals(Char* String_a, const Char* String_b) {
  return const_cast<Char*>(
      TSTREquals<Char>(reinterpret_cast<const Char*>(String_a),
                       reinterpret_cast<const Char*>(String_b)));
}

/* Compares the two Strings to see if the are equal.
@return Nil of the two Strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CHR>
const Char* TSTREquals(const Char* cursor, const Char* stop,
                       const Char* query) {
  if (!cursor) return nullptr;
  A_ASSERT(cursor < stop);
  if (!query) return nullptr;

  Char a = *cursor, b = *query;
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
template <typename Char = CHR>
Char* TSTREquals(Char* cursor, Char* stop, const Char* query) {
  return const_cast<Char*>(TSTREquals(reinterpret_cast<const Char*>(cursor),
                                      reinterpret_cast<const Char*>(stop),
                                      query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CHR>
BOL TSTRIsntEmpty(const Char* cursor) {
  if (!cursor) return false;
  Char c = *cursor;
  while (c) {
    if (!TIsWhitespace<Char>(c)) return true;
    c = *(++cursor);
  }
  return false;
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CHR>
BOL TSTRIsntEmpty(Char* cursor) {
  return TSTRIsntEmpty<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer. */
template <typename Char = CHR>
BOL TSTRIsntEmpty(const Char* cursor, const Char* stop) {
  if (!cursor) return false;
  if (cursor > stop) return false;
  Char c = *cursor;
  while (c) {
    if (!TIsWhitespace<Char>(c)) {
      // The text must stop at or before the target_end.
      do {
        if (++cursor >= stop) return false;
        c = *cursor;
        if (!TIsWhitespace<Char>(c)) return true;
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
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer. */
template <typename Char = CHR>
BOL TSTRIsntEmpty(Char* cursor, const Char* stop) {
  return TSTRIsntEmpty(reinterpret_cast<const Char*>(cursor),
                       reinterpret_cast<const Char*>(stop));
}

/* Prints the given item aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param cursor  The first Char in the buffer.
@param stop    The last Char in the buffer.
@param item  The item to utf.
@param column_count The token_ of columns to align right to. */
template <typename Char = CHR>
Char* TPrintRight(Char* cursor, Char* stop, const Char* item,
                  SI4 column_count = kConsoleWidth) {
  if (!cursor || cursor + column_count > stop) {
    return nullptr;
  }

  auto item_end = TSTREnd<Char>(item);
  Char c;  //< Temp variable.
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
template <typename Char = CHR>
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string,
                   SI4 column_count = kConsoleWidth) {
  if (!cursor || cursor >= stop) return nullptr;

  // We need to leave at least one space to the left and right of
  SI4 length = TSTRLength<Char>(string);
  SI4 delta;
  if (length <= column_count) {
    delta = (column_count - length) >> 1;  //< >> 1 to /2
    length = column_count - length - delta;

    if (length != column_count)
      while (delta-- > 0) *cursor++ = ' ';

    Char c = *string++;
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
template <typename Char = CHR>
Char* TPrintLinef(Char* start, Char* stop, Char item, SIW count = kConsoleWidth,
                  const Char* header = TSTRNL<Char>(),
                  const Char* footer = nullptr) {
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
template <typename Char = CHR>
Char* TPrintLinef(Char* start, Char* stop, const Char* item,
                  SIW count = kConsoleWidth,
                  const Char* header = TSTRNL<Char>(),
                  const Char* footer = nullptr) {
  if (header) start = SPrint(start, stop, header);
  if (!start || start <= stop || (start + count >= stop)) return nullptr;

  const Char* cursor = item;
  while (count-- > 0) {
    Char c = *cursor++;
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
template <typename Char = CHR>
Char* TPrintHeadingf(Char* start, Char* stop, Char item,
                     SIW count = kConsoleWidth) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CHR>
Char* TPrintHeadingf(Char* start, Char* stop, const Char* item,
                     SIW count = kConsoleWidth) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints a cursor to the given buffer without */
template <typename Char = CHR>
Char* TPrintWrap(Char* cursor, Char* stop, const Char* string,
                 SIW column_count = kConsoleWidth) {
  if (!cursor || cursor <= stop || !string) return nullptr;
  if (column_count < 2) return cursor;

  Char c = *string++;

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
template <typename Char = CHR, typename SIZ = SIN>
struct TSPrinter {
  Char *start,  //< Start address.
      *stop;    //< Stop address.

  /* Default constructor does nothing. */
  TSPrinter() {}

  /* Initializes the UTF& from the given origin pointers.
  @param start The origin of the origin.
  @param count The number of Char(s) in the buffer. */
  TSPrinter(Char* start, SIZ size) : start(start), stop(start + size - 1) {
    Reset();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TSPrinter(Char* start, Char* stop) : start(start), stop(stop) { Reset(); }

  /* Clones the other utf. */
  TSPrinter(const TSPrinter& other)
      : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  UI1* End() { return reinterpret_cast<UI1*>(start) + (sizeof(Char) - 1); }

  SIZ SizeBytes() { return (SIZ)(stop - start + sizeof(Char)); }

  void Wipe() { ArrayFill(start, stop); }

  /* Writes a nil-term CH1 at the start of the string. */
  inline Char* Reset() {
    *start = 0;
    return start;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(Char* cursor) {
    start = cursor;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(UIW* buffer) {
    SIZ size = *reinterpret_cast<SIZ*>(buffer);
    UIW ptr = reinterpret_cast<UIW>(buffer) + sizeof(SIZ);
    Char* start_ptr = reinterpret_cast<Char*>(ptr);
    start = start_ptr;
    stop = start_ptr + size - 1;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline void Set(TSPrinter<Char> other) {
    start = other.start;
    stop = other.stop;
  }

  /* Finds the length of the STR in Chars. */
  inline SIZ SpaceLeft() { return (SIZ)(stop - start); }

  /* Calculates the max length of the string in Chars. */
  inline SIZ LengthMax() { return stop - start; }

  /* Prints a item to the string. */
  inline TSPrinter& PrintChar(CH1 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
  inline TSPrinter& PrintChar(CH2 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
  inline TSPrinter& PrintChar(CH4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
  inline TSPrinter& Print(CH1 item) { return PrintChar(item); }
  inline TSPrinter& Print(CH2 item) { return PrintChar(item); }
  inline TSPrinter& Print(CH4 item) { return PrintChar(item); }
  inline TSPrinter& Print(const CH1* item) {
    return Set(_::TSPrintString<Char>(start, stop, item));
  }
  inline TSPrinter& Print(const CH2* item) {
    return Set(_::TSPrintString<Char>(start, stop, item));
  }
  inline TSPrinter& Print(const CH4* item) {
    return Set(_::TSPrintString<Char>(start, stop, item));
  }
  inline TSPrinter& Print(SI4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
  inline TSPrinter& Print(UI4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
  inline TSPrinter& Print(SI8 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
  inline TSPrinter& Print(UI8 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
#if USING_FP4 == YES_0
  inline TSPrinter& Print(FP4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  inline TSPrinter& Print(FP8 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
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
    return TSPrintHex<Char>(*this, item.element.ToPtr(), item.element.count);
  }
  inline TSPrinter& Hex(SI1 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(UI1 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(SI2 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(UI2 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(SI4 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(UI4 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(SI8 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
  inline TSPrinter& Hex(UI8 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
#if USING_FP4 == YES_0
  inline TSPrinter& Hex(FP4 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  inline TSPrinter& Hex(FP8 item) {
    return Set(TSPrintHex<Char>(start, stop, item));
  }
#endif
  inline TSPrinter& Hex(const void* ptr) {
    return Set(TSPrintHex<Char>(start, stop, ptr));
  }
  inline TSPrinter& Binary(SI1 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(UI1 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(SI2 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(UI2 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(SI4 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(UI4 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(SI8 item) {
    return Set(Binary<Char>(start, stop, item));
  }
  inline TSPrinter& Binary(UI8 item) {
    return Set(Binary<Char>(start, stop, item));
  }
#if USING_FP4 == YES_0
  inline TSPrinter& Binary(FP4 item) {
    return Set(Binary<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  inline TSPrinter& Binary(FP8 item) {
    return Set(Binary<Char>(start, stop, item));
  }
#endif
  /* Prints the given pointer as binary. */
  inline TSPrinter& Binary(const void* ptr) {
    UIW address = reinterpret_cast<UIW>(ptr);
    return Set(Binary<Char>(start, stop, address));
  }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    o << "\nTUTF<CH" << sizeof(Char) << ", SI" << sizeof(SIZ) << ">{ start:";
    TSPrintHex<Printer>(o, start);
    o << " stop:";
    TSPrintHex<Printer>(o, stop);
    return o << " }\n";

#if D_THIS
    // return TPrintChars<Printer, Char>(o, start, stop);
#endif
  }
};

/* Queries the given s for the given query. */
template <typename Char = CHR>
SI4 TSTRQuery(const Char* cursor, const Char* stop, const Char* query) {
  Char a = *cursor, b = *query;
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
  if (a && !TIsWhitespace<Char>(a)) return b - a;
  return 0;
}

}  // namespace _

/* Prints the given item to the UTF.
@return The utf.
@param utf The utf.
@param item   The item to utf. */
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, CH1 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      const CH1* item) {
  return utf.Print(item);
}

#if USING_UTF16 == YES_0
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, CH2 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      const CH2* item) {
  return utf.Print(item);
}
#endif
#if USING_UTF32 == YES_0
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, CH4 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      const CH4* item) {
  return utf.Print(item);
}
#endif

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, SI1 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, UI1 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, SI2 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, UI2 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, SI4 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, UI4 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, SI8 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, UI8 item) {
  return utf.Print(item);
}

#if USING_FP4 == YES_0
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, FP4 item) {
  return utf.Print(item);
}
#endif

#if USING_FP8 == YES_0
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, FP8 item) {
  return utf.Print(item);
}
#endif

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::Centerf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::Centerf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, _::Rightf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::Rightf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, _::Linef item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, _::Linef& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::Headingf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::Headingf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, _::Hexf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, _::Hexf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf, _::Charsf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::Charsf& item) {
  return utf.Print(item);
}
#endif
