/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_uniprinter.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

/* There is a different set of string printing utilities because it's a little
faster. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_UNIPRINTER_HEADER_WITH_TEMPLATES
#define SCRIPT2_UNIPRINTER_HEADER_WITH_TEMPLATES 1

#include "c_string.h"
#include "t_puff.h"
#if SEAM == SCRIPT2_UNIPRINTER
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* Compares the two strings up to the given delimiter.
@param delimiter Delimiters in Script2 are equal to or less than.
@return 0 if the strings are equal or a non-zero delta upon failure. */
template <typename Char = CHR>
SIN TSTRCompare(const Char* string, const Char* other_string,
                Char delimiter = 0) {
  if (!string || !other_string) return 0;

  SIN a, b, result;
  if (!string) {
    if (!other_string) return 0;
    return SIN(*string);
  }
  if (!other_string) return 0 - *string;

  a = *string;
  b = *other_string;
  if (!a) {
    if (!b) return 0;
    return b;
  }
  if (!b) {
    if (!a) return 0;
    return 0 - a;
  }
  // other_string SHOULD be a nil-terminated string without whitespace.
  while (b) {
    result = b - a;
    if (result) {
      return result;
    }
    if (a <= (SI4)delimiter) {
      return result;
    }
    ++string;
    ++other_string;
    a = *string;
    b = *other_string;
  }
  if (a > (SI4)delimiter) {
    return b - a;
  }
  return 0;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR>
inline const Char* TSTREnd(const Char* string, CH1 delimiter = 0) {
  while (*string++ != delimiter)
    ;
  return string - 1;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR>
inline Char* TSTREnd(Char* string, Char delimiter = 0) {
  return const_cast<Char*>(
      TSTREnd<Char>(reinterpret_cast<const Char*>(string), delimiter));
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR, typename SIZ = SIN>
SIZ TSTRLength(const Char* string) {
  D_ASSERT(string);
  return (SIZ)(TSTREnd<Char>(string) - string);
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR, typename SIZ = SIN>
inline SIZ TSTRLength(Char* string) {
  return TSTRLength<Char>(reinterpret_cast<const Char*>(string));
}

inline SI1 ToSigned(CH1 value) { return (SI1)value; }
inline SI2 ToSigned(CH2 value) { return (SI2)value; }
inline SI4 ToSigned(CH4 value) { return (SI4)value; }
inline SIN ToSigned(CHN value) { return (SIN)value; }
inline SI1 ToSigned(UI1 value) { return (SI1)value; }
inline SI2 ToSigned(UI2 value) { return (SI2)value; }
inline SI4 ToSigned(UI4 value) { return (SI4)value; }
inline SI8 ToSigned(UI8 value) { return (SI8)value; }
inline SI1 ToSigned(SI1 value) { return (SI1)value; }
inline SI2 ToSigned(SI2 value) { return (SI2)value; }
inline SI4 ToSigned(SI4 value) { return (SI4)value; }
inline SI8 ToSigned(SI8 value) { return (SI8)value; }
inline SIW ToSigned(const void* value) { return reinterpret_cast<SIW>(value); }
#if USING_FP4 == YES_0
inline SI4 ToSigned(FP4 value) { return *reinterpret_cast<SI4*>(&value); }
#endif
#if USING_FP8 == YES_0
inline SI8 ToSigned(FP8 value) { return *reinterpret_cast<SI8*>(&value); }
#endif

/* Utility functions for converting POD types to unsigned for printing. */
inline UI1 ToUnsigned(CH1 value) { return (UI1)value; }
inline UI2 ToUnsigned(CH2 value) { return (UI2)value; }
inline UI4 ToUnsigned(CH4 value) { return (UI4)value; }
inline UIN ToUnsigned(CHN value) { return (UIN)value; }
inline UI1 ToUnsigned(SI1 value) { return (UI1)value; }
inline UI2 ToUnsigned(SI2 value) { return (UI2)value; }
inline UI4 ToUnsigned(SI4 value) { return (UI4)value; }
inline UI8 ToUnsigned(SI8 value) { return (UI4)value; }
inline UI1 ToUnsigned(UI1 value) { return (UI1)value; }
inline UI2 ToUnsigned(UI2 value) { return (UI2)value; }
inline UI4 ToUnsigned(UI4 value) { return (UI4)value; }
inline UI8 ToUnsigned(UI8 value) { return (UI8)value; }
inline UIW ToUnsigned(const void* value) {
  return reinterpret_cast<UIW>(value);
}
#if USING_FP4 == YES_0
inline UI4 ToUnsigned(FP4 value) { return *reinterpret_cast<UI4*>(&value); }
#endif
#if USING_FP8 == YES_0
inline UI8 ToUnsigned(FP8 value) { return *reinterpret_cast<UI8*>(&value); }
#endif

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
  UI value = (UI)(c - '0');
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
  UI value = (UI)(c - '0');
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

/* The highest possible signed integer value of the given type SI. */
template <typename SI>
inline SI TSignedMax() {
  return ((~(SI)0) << 4) >> 1;
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   string The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, Char* stop, CH1 item) {
  if (!string || string >= stop) return nullptr;
  *string++ = item;
  *string = 0;
  return string;
}
/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   string The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, SIW count, CH1 item) {
  return Print(string, string + count - 1, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   string The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CHR>
Char* TSPrint(Char* string, SIW count, CH2 item) {
  return TSPrint<Char>(string, string + count - 1, item);
}

/* Prints the given item to the string.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   count  The number of Chars in the string buffer.
@param   item   The string to print. */
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
 @param   string  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print. */
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
  if (string >= stop) return nullptr;
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
 @param   string  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print.
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
 @param   start  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print.
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
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
inline Char* TSPrint(Char* start, SIW size, const CH1* item) {
  return TSPrintString<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
Char* TSPrint(Char* start, SIW size, const CH2* item) {
  return TSPrintString<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
Char* TSPrint(Char* start, SIW size, const CH4* item) {
  return TSPrintString<Char>(start, start + size - 1, item);
}

/* Finds the end of a decimal number of the given string.
@return Nil if the string doesn't contain a decimal or is nil.
@param  start The start of the string to search. */
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
@param  cursor  The first Char in the buffer.
@param  lower_bounds
@param  upper bounds*/
template <typename Char = CHR>
const Char* TSTRSkipCharsInRange(const Char* cursor, Char lower_bounds,
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
@param  cursor  The first Char in the buffer.
@param  lower_bounds
@param  upper bounds*/
template <typename Char = CHR>
Char* TSTRSkipCharsInRange(Char* cursor, Char lower_bounds, Char upper_bounds) {
  return const_cast<Char*>(TSTRSkipCharsInRange(
      reinterpret_cast<const Char*>(cursor), lower_bounds, upper_bounds));
}

/* Skips the numbers in the given range. */
template <typename Char = CHR>
inline const Char* TSTRSkipNumbers(const Char* cursor) {
  return const_cast<Char*>(TSTRSkipCharsInRange<Char>(
      reinterpret_cast<const Char*>(cursor), '0', '9'));
}
/* Skips the numbers in the given range. */
template <typename Char = CHR>
inline Char* TSTRSkipNumbers(Char* cursor) {
  return const_cast<Char*>(
      TSTRSkipNumbers<Char>(reinterpret_cast<const Char*>(cursor)));
}

/* Finds the stop of the decimals in the s, if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = const CH1>
Char* TSTRDecimalEnd(Char* start) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TSTRDecimalEnd<Char>(ptr));
}

/* Finds the stop of the decimals in the s, if there are any.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
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
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
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
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRSkipChar(const Char* cursor, Char skip_char) {
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
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
inline Char* TSTRSkipChar(Char* cursor, Char skip_char) {
  return const_cast<const Char*>(
      TSTRSkipChar<Char>(reinterpret_cast<const Char*>(cursor), skip_char));
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
Char* TPrintHex(Char* start, Char* stop, const void* begin, SIW size_bytes) {
  Char* end = start + (size_bytes * 2);
  if (!start || size_bytes <= 0 || end < start) return nullptr;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
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
Char* TPrintHex(Char* start, Char* stop, UI value) {
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
inline Char* TPrintHex(Char* start, Char* stop, SI1 value) {
  return TPrintHex<Char, UI1>(start, stop, (UI1)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI1 value) {
  return TPrintHex<Char, UI1>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI2 value) {
  return TPrintHex<Char, UI2>(start, stop, (UI2)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI2 value) {
  return TPrintHex<Char, UI2>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI4 value) {
  return TPrintHex<Char, UI4>(start, stop, (UI4)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI4 value) {
  return TPrintHex<Char, UI4>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI8 value) {
  return TPrintHex<Char, UI8>(start, stop, (UI8)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI8 value) {
  return TPrintHex<Char, UI8>(start, stop, value);
}

#if USING_FP4 == YES_0
template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, FP4 value) {
  return TPrintHex<Char, UI4>(start, stop, ToUnsigned(value));
}
#endif
#if USING_FP8 == YES_0
template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, FP8 value) {
  return TPrintHex<Char, UI8>(start, stop, ToUnsigned(value));
}
#endif

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, const void* ptr) {
  return TPrintHex<Char, UIW>(start, stop, ToUnsigned(ptr));
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

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking! */
template <typename T = CH1>
inline T* TWrite(T* socket, T value) {
  *socket++ = value;
  return socket;
}

template <typename Char = CHR>
Char* TPrintChars(Char* begin, Char* end, const Char* start, const Char* stop) {
  if (!start || start >= stop || !end || end >= begin) return nullptr;

  SIW size = stop - start,                     //
      extra_row = ((size & 63) != 0) ? 1 : 0,  //
      row_count = (size >> 6) + extra_row;     //

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;

  begin = Print(begin, end, STRPrintCharsHeader());
  begin = Print(begin, end, STRPrintCharsBorder());
  begin = PrintHex(begin, end, start);

  Char c;
  while (start < stop) {
    *begin++ = '\n';
    *begin++ = '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *start++;
      if (start > stop)
        c = 'x';
      else if (c < ' ')
        c = c + kPrintC0Offset;
      begin = Print(begin, end, c);
    }
    *begin++ = '|';
    *begin++ = ' ';
    begin = PrintHex(begin, end, start);
  }
  begin = Print(begin, end, STRPrintCharsBorder());
  begin = PrintHex(begin, end, start + size);
  return begin;
}

template <typename Char = CHR>
Char* TSScan(const Char* start, FP4& result) {
  return nullptr;
}

template <typename Char = CHR>
Char* TSScan(const Char* start, FP8& result) {
  return nullptr;
}

/* Prints the given socket to the COut. */
template <typename Char = CHR>
Char* TPrintSocket(Char* start, Char* stop, const void* begin,
                   const void* end) {
  const Char *read = reinterpret_cast<const Char*>(begin),
             *read_end = reinterpret_cast<const Char*>(end);
  if (!start || start >= stop || !begin || read > read_end) return nullptr;

  Char* buffer_begin = start;
  SIW size = read_end - read, num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - start) <= num_bytes) {
    D_COUT("\nERROR: buffer overflow trying to fit "
           << num_bytes << " in " << stop - start << " bytes!");
    return nullptr;
  }
  size += num_bytes;
  start = TSPrintString<Char>(start, stop, STRPrintCharsHeader());
  start = TSPrintString<Char>(start, stop, STRPrintCharsBorder());
  start = TPrintHex<Char>(start, stop, read);

  D_COUT("\nBuffer space left:" << stop - start);
  Char c;
  while (read < read_end) {
    *start++ = kLF;
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
    start = TPrintHex<Char>(start, stop, read);
  }
  start = TSPrintString<Char>(start, stop, STRPrintCharsBorder());
  return TPrintHex<Char>(start, stop, read + size);
}

/* An empty string. */
template <typename Char = CHR>
const Char* TSTREmpty() {
  static const Char kStrand[] = {NIL};
  return kStrand;
}

/* The new-line s. */
template <typename Char = CHR>
const Char* TSTRNL() {
  static const Char kStrand[] = {kLF};
  return kStrand;
}

/* Strand the reads "Error:". */
template <typename Char = CHR>
const Char* TSTRError() {
  static const Char kStrand[] = {kLF, 'E', 'r', 'r', 'o', 'r', ':', NIL};
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
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRLineEnd(const Char* cursor, SI4 column_count = 80) {
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
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CHR>
Char* TSTRLineEnd(Char* cursor, SI4 column_count = 80) {
  return const_cast<Char*>(
      TSTRLineEnd(reinterpret_cast<const Char*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CHR>
const Char* TSTRLineEnd(const Char* cursor, const Char* stop,
                        SI4 column_count = 80) {
  if (!cursor) {
    D_COUT("\nText buffer overflow!");
    return nullptr;
  }
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
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CHR>
inline Char* TSTRLineEnd(Char* cursor, Char* stop, SI4 column_count = 80) {
  return const_cast<const Char*>(
      TSTRLineEnd<Char>(reinterpret_cast<const Char*>(cursor),
                        reinterpret_cast<const Char*>(stop), column_count));
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRSkipSpaces(const Char* cursor) {
  if (!cursor) return nullptr;
  Char c = *cursor;
  while (TIsWhitespace<Char>(c)) {
    D_COUT('.');
    if (!c) return cursor;  //< This isn't an error as far as I can see.
    ++cursor;
    c = *cursor;
  }
  return cursor;
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
Char* TSTRSkipSpaces(Char* cursor) {
  return const_cast<Char*>(TSTRSkipSpaces<Char>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param  cursor  The first Char in the buffer.
@param  query   A query string.  */
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
                   // Setup to compare the strings;
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
  D_COUT("\nSkipping spaces: ");
  Char c = *cursor;
  while (IsWhitespace(c)) {
    D_COUT('.');
    if (!c) return nullptr;
    if (++cursor >= stop) return nullptr;
    c = *cursor;
  }
  return cursor;
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CHR>
inline Char* TSTRSkipSpaces(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TSTRSkipSpaces<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop)));
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a. */
template <typename Char = CHR>
const Char* TSTREquals(const Char* string_a, const Char* string_b) {
  A_ASSERT(string_a);
  A_ASSERT(string_b);

  D_COUT("\nComparing \"" << string_a << "\" to \"" << string_b << "\"");

  Char a = *string_a, b = *string_b;
  while (a) {
    D_COUT(a);
    if (a != b) {  // Not a hit.
      D_COUT("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      D_COUT("\nFound hit at 0x" << Hexf(string_a));
      return string_a;
    }
    a = *(++string_a);
    b = *(++string_b);
  }
  if (b) {
    D_COUT("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  D_COUT("\nFound hit at 0x" << Hexf(string_a));
  return string_a;  //< Find hit!
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a.
*/
template <typename Char = CHR>
inline Char* TSTREquals(Char* string_a, const Char* string_b) {
  return const_cast<Char*>(
      TSTREquals<Char>(reinterpret_cast<const Char*>(string_a),
                       reinterpret_cast<const Char*>(string_b)));
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CHR>
const Char* TSTREquals(const Char* cursor, const Char* stop,
                       const Char* query) {
  if (!cursor) return nullptr;
  A_ASSERT(cursor < stop);
  if (!query) return nullptr;

  D_COUT("\nComparing \"" << cursor << "\" to \"" << query << '\"');

  Char a = *cursor, b = *query;
  while (a) {
    D_COUT(a);
    if (a != b) {  // Not a hit.
      D_COUT("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      D_COUT("\nFound hit at 0x" << Hexf(cursor));
      return cursor;
    }
    if (cursor > stop) {
      return nullptr;
    }
    a = *(++cursor);
    b = *(++query);
  }
  if (b) {
    D_COUT("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  D_COUT("\nFound hit at 0x" << Hexf(cursor));
  return cursor;
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CHR>
Char* TSTREquals(Char* cursor, Char* stop, const Char* query) {
  return const_cast<Char*>(TSTREquals(reinterpret_cast<const Char*>(cursor),
                                      reinterpret_cast<const Char*>(stop),
                                      query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
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
@param  cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CHR>
BOL TSTRIsntEmpty(Char* cursor) {
  return TSTRIsntEmpty<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
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
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CHR>
BOL TSTRIsntEmpty(Char* cursor, const Char* stop) {
  return TSTRIsntEmpty(reinterpret_cast<const Char*>(cursor),
                       reinterpret_cast<const Char*>(stop));
}

/* Prints the given item aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param  item  The item to utf.
@param  column_count The token_ of columns to align right to. */
template <typename Char = CHR>
Char* TPrintRight(Char* cursor, Char* stop, const Char* item,
                  SI4 column_count = 80) {
  if (!cursor || cursor + column_count > stop) {
    D_COUT("\nBuffer overflow!");
    return nullptr;
  }

  auto item_end = TSTREnd<Char>(item);
  Char c;  //< Temp variable.
  if (item == item_end) return cursor;
  SIW length = item_end - item;

  // If the length is less than the column_count we need to print ".", "..",
  // "..." or nothing and chop off some of the item.
  SIW count = column_count - length;
  D_COUT("\n\nPrinting \"" << item << "\":" << length << " aligned right "
                           << column_count << " columns count:" << count);
  if (count < 0) {
    SIW dot_count = length + count;
    D_COUT(" dot_count:%i" << dot_count);
    if (dot_count <= 3) {
      D_COUT("\n Wrote dots:\"");
      while (dot_count-- > 0) {
        *cursor++ = '.';
        D_COUT('.');
      }
      D_COUT('\"');
      *cursor = 0;
      return cursor;
    }
    stop = cursor + column_count;
    *stop-- = 0;
    *stop-- = '.';
    *stop-- = '.';
    *stop-- = '.';
    item_end = item + column_count - 4;
    D_COUT("\n Wrote with dots backwards:\"...");
    while (item_end > item) {
      c = *item_end--;
      *stop-- = c;
      D_COUT(c);
    }
    c = *item_end--;
    *stop-- = c;
    D_COUT(c << '\"');
    return cursor + column_count;
  }
  D_COUT("\ncursor:0x" << Hexf(cursor) << " end:0x" << Hexf(stop) << " item:0x"
                       << Hexf(item) << " token_end:0x" << Hexf(item_end));
  // In order to keep the current cache lines we're going to utf
  // backwards back from the token_end.
  D_COUT("\n Wrote backwards:\"");
  stop = cursor + column_count;
  --item_end;   //< This is pointed at the nil-term CH1
  *stop-- = 0;  //< and there is no need to load a 0.
  while (item_end >= item) {
    c = *item_end--;
    *stop-- = c;
    D_COUT(c);
  }
  while (stop >= cursor) {
    *stop-- = ' ';
    D_COUT(' ');
  }
  D_COUT("\"\nWrote:\"" << cursor << "\"");
  return cursor + column_count;
}

/* Prints the given cursor center aligned to the given column_count. */
template <typename Char = CHR>
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string,
                   SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;

  // We need to leave at least one space to the left and right of
  SI4 length = TSTRLength<Char>(string);
  D_COUT("\n\nPrinting \"" << string << "\":" << length << " centered to "
                           << column_count << " columns");
  SI4 delta;
  if (length <= column_count) {
    delta = (column_count - length) >> 1;  //< >> 1 to /2
    length = column_count - length - delta;
    D_COUT("\nlength:" << length << " delta:" << delta);

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
Char* TPrintLinef(Char* start, Char* stop, Char item, SIW count = 80,
                  const Char* header = TSTRNL<Char>(),
                  const Char* footer = nullptr) {
  if (header) start = Print(start, stop, header);
  if (!start || start + count <= stop) return nullptr;

  while (count-- > 0) *start++ = item;

  if (footer)
    return Print(start, stop, footer);
  else
    *start = 0;
  return start;
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CHR>
Char* TPrintLinef(Char* start, Char* stop, const Char* item, SIW count = 80,
                  const Char* header = TSTRNL<Char>(),
                  const Char* footer = nullptr) {
  if (header) start = Print(start, stop, header);
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
    return Print(start, stop, footer);
  else
    *start = 0;
  return start;
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CHR>
Char* TPrintHeadingf(Char* start, Char* stop, Char item, SIW count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CHR>
Char* TPrintHeadingf(Char* start, Char* stop, const Char* item,
                     SIW count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints a cursor to the given buffer without */
template <typename Char = CHR>
Char* TPrintWrap(Char* cursor, Char* stop, const Char* string,
                 SIW column_count = 80) {
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
    *cursor++ = kLF;
    if (!c) {
      *cursor = c;
      return cursor;
    }
  }
  return cursor;
}

/* Utility class for printing numbers. */
template <typename Char = CHR, SIN kLengthMax = 31>
class TStringf {
  SIW count_;
  Char string_[kLengthMax + 1];  //< Strand buffer for the token.

 public:
  enum { kLengthMax = kLengthMax };

  TStringf(CH1 item = 0, SIW count = kLengthMax)
      : string_(string_), count_(count) {
    auto cursor = string_;
    *cursor = item;
    *cursor = 0;
  }

  TStringf(const CH1* item, SIW count = kLengthMax)
      : string_(item), count_(count) {
    if (!item) *string_ = 0;
  }

  TStringf(CH2 item = 0, SIW count = kLengthMax)
      : string_(string_), count_(count) {
    auto cursor = string_;
    *cursor = item;
    *cursor = 0;
  }

  TStringf(const CH2* item, SIW count = kLengthMax)
      : string_(item), count_(count) {
    if (!item) *string_ = 0;
  }

  TStringf(CH4 item = 0, SIW count = kLengthMax)
      : string_(string_), count_(count) {
    auto cursor = string_;
    *cursor = item;
    *cursor = 0;
  }

  TStringf(const CH4* item, SIW count = kLengthMax)
      : string_(item), count_(count) {
    if (!item) *string_ = 0;
  }

#if CPU_WORD_SIZE != CPU_64_BIT
  TStringf(SI4 item, SIW count = kLengthMax) : string_(string_), count_(count) {
    TSPrint<Char>(string_, string_ + kLengthMax, item);
  }

  /* Prints the item to the token_. */
  TStringf(UI4 item, SIW count = kLengthMax) : string_(string_), count_(count) {
    TSPrint<Char>(string_, string_ + kLengthMax, item);
  }
#endif

  /* Prints the item to the token_. */
  TStringf(SI8 item, SIW count = kLengthMax) : string_(string_), count_(count) {
    TSPrint<Char>(string_, string_ + kLengthMax, item);
  }

  /* Prints the item to the token_. */
  TStringf(UI8 item, SIW count = kLengthMax) : string_(string_), count_(count) {
    TSPrint<Char>(string_, string_ + kLengthMax, item);
  }

#if USING_FP4 == YES_0
  /* Prints the item to the token_. */
  TStringf(FP4 item, SIW count = kLengthMax) : string_(string_), count_(count) {
    TSPrint<Char>(string_, string_ + kLengthMax, item);
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the item to the token_. */
  TStringf(FP8 item, SIW count = kLengthMax) : string_(string_), count_(count) {
    TSPrint<Char>(string_, string_ + kLengthMax, item);
  }
#endif

  /* Gets the string_. */
  inline const Char* String() { return string_; }

  /* Gets the strand_. */
  inline Char* Strand() { return string_; }

  /* Gets the string_ or the strand_ if the string_ is nil. */
  inline const Char* Get() {
    const Char* ptr = string_;
    return ptr ? ptr : string_;
  }

  /* Sets the string_ to the new string.
  @return Nil upon failure or the string upon success. */
  inline const CH1* Set(const CH1* string) {
    if (!string) return string;
  }

  /* Gets the count. */
  inline SI4 Count() { return count_; }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH1 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH1* item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH2 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH2* item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH4 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH4* item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI4 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI4 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI8 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI8 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

#if USING_FP4 == YES_0
  /* Prints the given item to the strand_. */
  inline Char* Print(FP4 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item to the strand_. */
  inline Char* Print(FP8 item) {
    auto cursor = _::TSPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }
#endif
};

/* Templated String Printer. */
template <typename Char = CHR, typename SIZ = SI4>
struct TSPrinter {
  Char *start,  //< Start address.
      *stop;    //< Stop address.

  /* Default constructor does nothing. */
  TSPrinter() {}

  /* Initializes the UTF& from the given begin pointers.
  @param start The begin of the begin.
  @param count The number of Char(s) in the buffer. */
  TSPrinter(Char* start, SIZ size) : start(start), stop(start + size - 1) {
    D_ASSERT(start);
    D_ASSERT(size >= 0);
    Reset();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TSPrinter(Char* start, Char* stop) : start(start), stop(stop) {
    D_ASSERT(start);
    D_ASSERT(start < stop);
    Reset();
  }

  /* Clones the other utf. */
  TSPrinter(const TSPrinter& other)
      : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  UI1* End() { return reinterpret_cast<UI1*>(start) + (sizeof(Char) - 1); }

  SIZ SizeBytes() { return (SIZ)(stop - start + sizeof(Char)); }

  void Wipe() { SocketWipe(start, stop); }

  /* Writes a nil-term CH1 at the start of the strand. */
  inline Char* Reset() {
    *start = 0;
    return start;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(Char* cursor) {
    D_ASSERT(cursor);
    start = cursor;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(UIW* buffer) {
    D_ASSERT(buffer);
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

  /* Prints a CH1 to the strand. */
  inline TSPrinter& PrintChar(CH1 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& PrintChar(CH2 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& PrintChar(CH4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& Print(CH1 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& Print(CH2 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& Print(CH4 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& Print(const CH1* item) {
    return Set(_::TSPrintString<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& Print(const CH2* item) {
    return Set(_::TSPrintString<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TSPrinter& Print(const CH4* item) {
    return Set(_::TSPrintString<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TSPrinter& Print(SI4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TSPrinter& Print(UI4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TSPrinter& Print(SI8 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TSPrinter& Print(UI8 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }

#if USING_FP4 == YES_0
  /* Prints the given item.
  @return A UTF. */
  inline TSPrinter& Print(FP4 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item.
  @return A UTF. */
  inline TSPrinter& Print(FP8 item) {
    return Set(_::TSPrint<Char>(start, stop, item));
  }
#endif

  /* Prints the given item. */
  inline TSPrinter& Print(Hexf item) {
    return TPrintHex<TSPrinter>(*this, item.element);
  }

  /* Prints the given item. */
  inline TSPrinter& Print(Rightf item) {
    return TPrintRight<TSPrinter>(*this, item.element);
  }

  /* Prints the given item. */
  inline TSPrinter& Print(Centerf item) {
    return TPrintCenter<TSPrinter>(*this, item.element);
  }

  /* Prints the given item. */
  inline TSPrinter& Print(Linef item) {
    return TPrintLinef<TSPrinter>(*this, item);
  }

  /* Prints the given item. */
  inline TSPrinter& Print(Headingf item) {
    return TPrintHeadingf<TSPrinter>(*this, item);
  }

  /* Prints the given pointer as hex. */
  inline TSPrinter& Hex(Hexf item) {
    return TPrintHex<Char>(*this, item.element.Ptr(), item.element.count);
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(SI1 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(UI1 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(SI2 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(UI2 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(SI4 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(UI4 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(SI8 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

  /* Prints the given item as hex. */
  inline TSPrinter& Hex(UI8 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }

#if USING_FP4 == YES_0
  /* Prints the given item as hex. */
  inline TSPrinter& Hex(FP4 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item as hex. */
  inline TSPrinter& Hex(FP8 item) {
    return Set(TPrintHex<Char>(start, stop, item));
  }
#endif

  /* Prints the given pointer as hex. */
  inline TSPrinter& Hex(const void* ptr) {
    return Set(TPrintHex<Char>(start, stop, ptr));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(SI1 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(UI1 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(SI2 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(UI2 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(SI4 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(UI4 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(SI8 item) {
    return Set(Binary<Char>(start, stop, item));
  }

  /* Prints the given item as binary. */
  inline TSPrinter& Binary(UI8 item) {
    return Set(Binary<Char>(start, stop, item));
  }

#if USING_FP4 == YES_0
  /* Prints the given item as binary. */
  inline TSPrinter& Binary(FP4 item) {
    return Set(Binary<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item as binary. */
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
    TPrintHex<Printer>(o, start);
    o << " stop:";
    TPrintHex<Printer>(o, stop);
    return o << " }\n";

#if D_THIS
    TPrintSocket<Printer>(o, start, End());
    return TPrintChars<Printer, Char>(o, start, stop);
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
    if (result) {
      D_COUT(" is not a hit.");
      return result;
    }
    if (!a) {
      D_COUT(" is a partial match but !a.");
      return result;
    }
    if (++cursor >= stop) {
      D_COUT(" but buffer overflowed!");
      return result;
    }
    ++query;
    a = *cursor;
    b = *query;
  }
  if (a && !TIsWhitespace<Char>(a)) {
    D_COUT(" is only a partial match but found " << (a ? "a" : "space"));
    return b - a;
  }
  D_COUT(" is a match!");
  return 0;
}

}  // namespace _

/* Prints the given item to the UTF.
@return The utf.
@param  utf The utf.
@param  item   The item to utf. */
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
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::TStringf<Char> item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TSPrinter<Char>& operator<<(_::TSPrinter<Char>& utf,
                                      _::TStringf<Char>& item) {
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
