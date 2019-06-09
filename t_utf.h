/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_utf.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_TUTF
#define SCRIPT2_TUTF 1

#if USING_UTF8 == YES
#include "c_utf1.h"
#endif
#if USING_UTF16 == YES
#include "c_utf2.h"
#endif
#if USING_UTF32 == YES
#include "c_utf4.h"
#endif

#include "t_puff.h"
#include "t_socket.h"

#if SEAM == SCRIPT2_SEAM_RNG
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

template <typename Printer, typename Char = CH1>
Printer& TPrintString(Printer& o, const Char* string) {
  if (!string) return o;
  Char c = *string;
  while (c) {
    o << c;
    c = *(++string);
  }
  return o;
}

/* Compares the two strings up to the given delimiter.
@param delimiter Delimiters in Script2 are equal to or less than.
@return 0 if the strings are equal or a non-zero delta upon failure. */
template <typename Char = CH1>
SI4 TSTRCompare(const Char* string_a, const Char* string_b,
                Char delimiter = 0) {
  SI4 a, b, result;
  if (!string_a) {
    if (!string_b) return 0;
    return *string_a;
  }
  if (!string_b) return 0 - *string_a;

  PRINTF("\nComparing \"%s\" to \"%s\"", string_a, string_b);
  a = *string_a;
  b = *string_b;
  if (!a) {
    if (!b) return 0;
    return b;
  }
  if (!b) {
    if (!a) return 0;
    return 0 - a;
  }
  // string_b SHOULD be a nil-terminated string without whitespace.
  while (b) {
    result = b - a;
    if (result) {
      PRINT(" is not a hit.");
      return result;
    }
    if (a <= (SI4)delimiter) {
      PRINT(" is a partial match but a reached a delimiter first.");
      return result;
    }
    ++string_a;
    ++string_b;
    a = *string_a;
    b = *string_b;
  }
  if (a > (SI4)delimiter) {
    PRINTF(" is only a partial match but b reached a delimiter first.");
    return b - a;
  }
  return 0;
}

/* Prints the following item to the console in Hex. */
template <typename Printer, typename UI>
Printer& TPrintHex(Printer& o, UI item) {
  enum { kHexStrandLengthSizeMax = sizeof(UI) * 2 + 3 };
  auto ui = ToUnsigned(item);
  for (SI4 num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    o << HexNibbleToUpperCase((UI1)(ui >> num_bits_shift));
  }
  return o;
}
/* Prints the following item to the console in Hex. */
template <typename Printer>
Printer& TPrintHex(Printer& o, const void* item) {
  UIW ptr = reinterpret_cast<UIW>(item);
  return TPrintHex<Printer, UIW>(o, ptr);
}

/* Prints the given hex using opeator<<. */
template <typename Printer>
Printer& TPrintHex(Printer& o, const void* begin, SIW byte_count) {
  if (!begin) {
    PRINT_ERROR("!begin");
    return o;
  }
  SIW address, delta;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
  if (byte_count < 0) {
    delta = -1;
    byte_count = -byte_count;
    cursor += byte_count - 1;
  } else {
    delta = 1;
  }
  while (byte_count-- > 0) {
    UI1 byte = *cursor;
    cursor += delta;
    o << HexNibbleToUpperCase(byte & 0xf) << HexNibbleToUpperCase(byte >> 4);
  }
  return o;
}

/* Prints the given value to Binary. */
template <typename Printer, typename SI>
Printer& TPrintBinary(Printer& o, const void* begin, SI byte_count) {
  if (!begin || byte_count <= 0) return o;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
  while (--byte_count >= 0) {
    for (SI1 i = 8; i > 0; ++i) {
      UI1 c = *cursor++;
      o << (CH4)('0' + (c >> 7));
      c = c << 1;
    }
  }
  return o;
}

template <typename Printer, typename UI>
Printer& TPrintBinary(Printer& o, UI value) {
  enum { kSize = sizeof(UI) * 8 };
  for (SI4 i = kSize; i > 0; --i) {
    CH1 c = (CH1)('0' + (value >> (kSize - 1)));
    o << c;
    value = value << 1;
  }
  return o;
}

template <typename Printer, typename SI, typename UI>
Printer& TPrintBinarySigned(Printer& o, SI value) {
  return TPrintBinary<Printer, UI>(o, (UI)value);
}

/* Checks if the given character is whitespace. */
template <typename Char = CH1>
inline BOL TIsWhitespace(Char character) {
  return character <= ' ';
}

template <typename Printer, typename Char = CH1>
Printer& TPrintRepeat(Printer& o, Char c, SI4 count) {
  for (; count > 0; --count) o << Char(c);
  return o;
}

template <typename Char = CH1>
const Char* TSTRLinef() {
  static const Char kString[] = {kLF, kLF, '-', '-', '-', kLF, NIL};
  return kString;
}

/* Prints a formatted lines.

The first two chars of the string are going to be the corner and margin chars.
It's easiest to show with the examples below. Like their names implies, the
corner char is for the edges and the margin is for inside of a header block.

@code
TPrintBreak<CH1> ("\n+---\n\n| Foo\n\n+---\n", 10);

TPrintBreak<CH1> ("\n+---\n\n| Foo\n\n+---\n", 10);
//>>>
//>>> +----------
//>>> | Foo *****
//>>> +----------
//>>>

TPrintBreak<CH1> ("- \n---\n---\n\n   Foo\n\n---\n---", 10);
//>>> -----------
//>>> -----------
//>>>
//>>>    Foo
//>>>
//>>> -----------
//>>> -----------
@endcode
*/
template <typename Printer, typename Char = CH1>
const Char* TPrintLinef(Printer& o, const Char* style = nullptr,
                        SI4 column_count = 80) {
  enum {
    kBreakCount = 3,
  };
  if (!style) style = TSTRLinef<Char>();
  if (column_count < kBreakCount) return nullptr;

  Char c = *style++,  //< Current.
      p = ~c;         //< Previous.
  SI4 hit_count = 0, column_index = 0;
  while (c) {
    o << Char(c);
    ++column_index;
    if (c == kLF) {
      p = c;
      do {
        c = *style++;
        o << Char(c);
      } while (c == kLF);
      column_index = 0;
    }
    if (c == p && !TIsWhitespace<Char>(c)) {
      ++hit_count;
      if (hit_count >= kBreakCount - 1) {
        TPrintRepeat<Printer, Char>(o, c, column_count - column_index);
        column_index = hit_count = 0;
      }
    }
    p = c;
    c = *style++;
  }
  return style;
}

template <typename Printer, typename Char = CH1>
Printer& TPrintLinef(Printer& o, Char token = '-', SI4 column_count = 80) {
  o << '\n';
  TPrintRepeat<Printer, Char>(o, token, column_count);
  return o << '\n';
}

template <typename Char = CH1>
const Char* TSTRHeadingf() {
  static const Char kStrand[] = {kLF, kLF, '+', '-', '-', '-', kLF, '|', ' ',
                                 NIL, kLF, '+', '-', '-', '-', kLF, NIL};
  return kStrand;
}

/* Prints an easy-to-read text heading with a formatting options.
@code
TPrintHeadingf<CH1> ("\n+---\0\n+---", 80, "Foo ", "Bar ",
                     TToken<CH1> (420).String ());
@endcode
*/
template <typename Printer, typename Char = CH1>
Printer& TPrintHeadingf(Printer& o, const Char* caption,
                        const Char* style = nullptr, SI4 column_count = 80,
                        const Char* caption2 = nullptr,
                        const Char* caption3 = nullptr) {
  if (!style) style = TSTRHeadingf<Char>();
  style = TPrintLinef<Printer, Char>(o, style, column_count);
  if (!style) return o;
  o << caption;
  if (caption2) o << caption2;
  if (caption3) o << caption3;
  TPrintLinef<Printer, Char>(o, style, column_count);
  return o;
}

template <typename Printer, typename Char = CH1>
Printer& TPrintChars(Printer& o, const Char* start, const Char* stop) {
  if (!start || start >= stop) return o;

  SIW size = stop - start, extra_row = ((size & 63) != 0) ? 1 : 0,
      row_count = (size >> 6) + extra_row;

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;
  o << STRSocketHeader() << STRSocketBorder() << Hex(start);
  int i = 0;
  Char c;
  while (start < stop) {
    o << '\n' << '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *start++;
      if (start > stop)
        c = 'x';
      else if (c < ' ')
        c = c + kPrintC0Offset;
      o << Char(c);
    }
    o << '|' << ' '  //
      << Hex(start);
  }
  return o << STRSocketBorder() << Hex(start + size);
}

template <typename Printer, typename Char = CH1>
Printer& TPrintChars(Printer& o, const Char* start, SIW count) {
  return TPrintChars<Printer, Char>(o, start, start + count);
}

/* Prints the given socket to the COut.
@todo I think we only need TPRintChars. */
template <typename Printer>
Printer& TPrintSocket(Printer& o, const void* begin, const void* end) {
  ASSERT(begin || end || begin <= end);

  const CH1 *address_ptr = reinterpret_cast<const CH1*>(begin),
            *address_end_ptr = reinterpret_cast<const CH1*>(end);
  SIW size = address_end_ptr - address_ptr,
      num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  size += num_bytes;
  o << STRSocketHeader() << STRSocketBorder();
  TPrintHex<Printer>(o, address_ptr);
  CH1 c;
  while (address_ptr < address_end_ptr) {
    o << kLF << '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (!c || c == kTAB)
        c = ' ';
      else if (c < ' ')
        c = kDEL;
      o << (CH4)c;
    }
    o << '|' << ' ';
    TPrintHex<Printer>(o, address_ptr);
  }
  o << STRSocketBorder();
  return TPrintHex<Printer>(o, address_ptr + size);
}

}  // namespace _

#if SEAM >= SCRIPT2_SEAM_ITOS
namespace _ {

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CH1>
const Char* TScanUnsigned(const Char* start, UI& result) {
  DASSERT(start);
  PRINTF("\n\nScanning unsigned value:%s", start);
  const Char* cursor = start;
  Char c = *cursor++;
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* stop = cursor;  // Store stop to return.
  cursor -= 2;
  PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
         (SI4)(cursor - start));

  c = *cursor--;
  UI value = (UI)(c - '0');
  UI pow_10_ui2 = 1;

  while (cursor >= start) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (((UI)c) - '0');
    if (new_value < value) return nullptr;
    value = new_value;
    PRINTF("\nvalue:%u", (UIN)value);
  }
  PRINTF("\nvalue:%u", (UIN)value);
  result = value;
  return stop;
}

/* Checks if the given CH1 is a digit of a number_.
@return True if it is a digit. */
template <typename Char = CH1>
BOL TIsDigit(Char c) {
  return (c >= '0') && (c <= '9');
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline const Char* TSTREnd(const Char* start, CH1 delimiter = 0) {
  while (*start++ != delimiter)
    ;
  return start - 1;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline Char* TSTREnd(Char* start, Char delimiter = 0) {
  return const_cast<Char*>(
      TSTREnd(reinterpret_cast<const Char*>(start), delimiter));
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1, typename I = SI4>
I TSTRLength(const Char* start) {
  DASSERT(start);
  return (I)(TSTREnd<Char>(start) - start);
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1, typename I = SI4>
inline I TSTRLength(Char* start) {
  return TSTRLength<Char>(reinterpret_cast<const Char*>(start));
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

template <typename Char = const CH1>
Char* TSTRDecimalEnd(Char* start) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TSTRDecimalEnd<Char>(ptr));
}

}  // namespace _
#endif

#if SEAM >= SCRIPT2_SEAM_UTF
#if SEAM == SCRIPT2_SEAM_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* The highest possible signed integer value of the given type SI. */
template <typename SI>
inline SI TSignedMax() {
  return ((~(SI)0) << 4) >> 1;
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CH1>
Char* TPrint(Char* start, Char* stop, CH1 item) {
  return Print(start, stop, item);
}
/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CH1>
Char* TPrint(Char* start, SIW count, CH1 item) {
  return Print(start, start + count - 1, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CH1>
Char* TPrint(Char* start, SIW count, CH2 item) {
  return TPrint<Char>(start, start + count - 1, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count The element count.
@param   item  The string to print. */
template <typename Char = CH1>
Char* TPrint(Char* start, SIW count, CH4 item) {
  return TPrint<Char>(start, start + count - 1, item);
}

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   start  The beginning of the socket.
 @param   stop   The last Char in the socket.
 @param   item   The item to print. */
template <typename Char = CH1>
Char* TPrint(Char* start, Char* stop, const CH1* item) {
  if (!start || start >= stop || !item) return nullptr;

  if (start >= stop) return nullptr;

  CH1 c = *item++;
  while (c) {
    start = Print(start, stop, c);
    if (!start || start >= stop) return nullptr;
    c = *item++;
  }
  *start = 0;
  return start;
}

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   start  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename Char = CH1>
Char* TPrint(Char* start, Char* stop, const CH2* item) {
  if (!start || start >= stop || !item) return nullptr;

  CH2 c = *item++;
  while (c) {
    start = Print(start, stop, c);
    if (!start || start >= stop) return nullptr;
    c = *item++;
  }
  if (start) *start = 0;
  return start;
}

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   start  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename Char = CH1>
Char* TPrint(Char* start, Char* stop, const CH4* item) {
  if (!start || start >= stop || !item) return nullptr;

  if (start >= stop) return nullptr;

  CH4 c = *item++;
  while (c) {
    start = Print(start, stop, c);
    if (!start || start >= stop) return nullptr;
    c = *item++;
  }
  *start = 0;
  return start;
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CH1>
Char* TPrint(Char* start, SIW size, const CH1* item) {
  return TPrint<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CH1>
Char* TPrint(Char* start, SIW size, const CH2* item) {
  return TPrint<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CH1>
Char* TPrint(Char* start, SIW size, const CH4* item) {
  return TPrint<Char>(start, start + size - 1, item);
}

template <typename Char>
void TPrint1(Char* start, Char token) {
  *start++ = token;
  *start++ = 0;
}

template <typename Char>
void TPrint3(Char* start, Char token) {
  *start++ = token;
  *start++ = token;
  *start++ = token;
  *start++ = 0;
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
template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, SI1 value) {
  return TPrintHex<Char, UI1>(start, stop, (UI1)value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, UI1 value) {
  return TPrintHex<Char, UI1>(start, stop, value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, SI2 value) {
  return TPrintHex<Char, UI2>(start, stop, (UI2)value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, UI2 value) {
  return TPrintHex<Char, UI2>(start, stop, value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, SI4 value) {
  return TPrintHex<Char, UI4>(start, stop, (UI4)value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, UI4 value) {
  return TPrintHex<Char, UI4>(start, stop, value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, SI8 value) {
  return TPrintHex<Char, UI8>(start, stop, (UI8)value);
}

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, UI8 value) {
  return TPrintHex<Char, UI8>(start, stop, value);
}

#if USING_FP4 == YES
template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, FP4 value) {
  return TPrintHex<Char, UI4>(start, stop, ToUnsigned(value));
}
#endif

#if USING_FP8 == YES
template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, FP8 value) {
  return TPrintHex<Char, UI8>(start, stop, ToUnsigned(value));
}
#endif

template <typename Char = CH1>
inline Char* TPrintHex(Char* start, Char* stop, const void* ptr) {
  return TPrintHex<Char, UIW>(start, stop, ToUnsigned(ptr));
}

/* Prints the given value to Binary. */
template <typename Char = CH1, typename UI>
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
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, SI1 value) {
  return TPrintBinary<Char, UI1>(start, stop, (UI1)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, UI1 value) {
  return TPrintBinary<Char, UI1>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, SI2 value) {
  return TPrintBinary<Char, UI2>(start, stop, (UI2)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, UI2 value) {
  return TPrintBinary<Char, UI2>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, SI4 value) {
  return TPrintBinary<Char, UI4>(start, stop, (UI4)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, UI4 value) {
  return TPrintBinary<Char, UI4>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, SI8 value) {
  return TPrintBinary<Char, UI8>(start, stop, (UI8)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* start, Char* stop, UI8 value) {
  return TPrintBinary<Char, UI8>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
Char* TPrintBinary(Char* start, Char* stop, FP4 value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<Char, UI4>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
Char* TPrintBinary(Char* start, Char* stop, FP8 value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<Char, UI8>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
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

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CH1>
Char* TScanUnsigned(Char* start, UI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TScanUnsigned<UI, Char>(ptr, result));
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char = CH1>
const Char* TScanSigned(const Char* start, SI& result) {
  DASSERT(start);
  SI sign;
  const Char* cursor = start;
  Char c = *cursor++;
  if (c == '-') {
    PRINTF("\nScanning negative backwards:\"");
    c = *start++;
    sign = -1;
  } else {
    PRINTF("\nScanning positive backwards:\"");
    sign = 1;
  }
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* stop = cursor;  // Store stop to return.
  cursor -= 2;
  PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
         (SI4)(cursor - start));

  c = *cursor--;
  UI value = (UI)(c - '0');
  UI pow_10_ui2 = 1;

  while (cursor >= start) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (((UI)c) - '0');
    if (new_value < value) return nullptr;
    value = new_value;
    PRINTF("\nvalue:%u", (UIN)value);
  }
  result = sign * value;
  return stop;
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char = CH1>
Char* TScanSigned(Char* start, SI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TScanSigned<SI, UI, Char>(ptr));
}

template <typename Char = CH1>
Char* TPrintChars(Char* begin, Char* end, const Char* start, const Char* stop) {
  if (!start || start >= stop || !end || end >= begin) return nullptr;

  SIW size = stop - start, extra_row = ((size & 63) != 0) ? 1 : 0,
      row_count = (size >> 6) + extra_row;

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;

  begin = Print(begin, end, STRSocketHeader());
  begin = Print(begin, end, STRSocketBorder());
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
  begin = Print(begin, end, STRSocketBorder());
  begin = PrintHex(begin, end, start + size);
  return begin;
}

template <typename Char = CH1>
Char* TPrint3(Char* socket, Char* stop, Char a, Char b, Char c) {
  if (!socket || socket + 3 >= stop) return nullptr;
  *socket++ = a;
  *socket++ = b;
  *socket++ = c;
  return socket;
}

template <typename Char = CH1>
Char* TScan(const Char* start, FP4& result) {
  return nullptr;
}

template <typename Char = CH1>
Char* TScan(const Char* start, FP8& result) {
  return nullptr;
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Printer, typename Char = CH1>
Printer& TPrintRight(Printer& o, const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1) return o;

  const Char* token_end = TSTREnd<Char>(item);
  if (item == token_end) return o;
  SIW length = token_end - item, space_count = column_count - length;

  if (space_count > 0) {
    while (space_count-- > 0) o << ' ';
    o << item;
    return o;
  }
  length = (-length) - 3;
  if (length < 0) {
    switch (length) {
      case 1:
        o << '.';
      case 2:
        o << '.' << '.';
      case 3:
        o << '.' << '.' << '.';
    }
  } else {
    while (length > 0) o << *item++;
    o << '.' << '.' << '.';
  }
  return o;
}

/* Prints the given token aligned center the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Printer, typename Char = CH1>
Printer& TPrintCenter(Printer& o, const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1) return o;

  const Char* token_end = TSTREnd<Char>(item);
  if (item == token_end) return o;
  SIW length = token_end - item, space_count = column_count - length;

  if (space_count > 0) {
    SIW half_count = space_count >> 1;
    space_count -= half_count;
    while (half_count-- > 0) o << ' ';
    o << item;
    while (space_count-- > 0) o << ' ';
    return o;
  }
  length = (-length) - 3;
  if (length < 0) {
    if (length == 1)
      o << '.';
    else if (length == 2)
      o << '.' << '.';
    else if (length == 3)
      o << '.' << '.' << '.';
  } else {
    while (length > 0) o << *item++;
    o << '.' << '.' << '.';
  }
  return o;
}

/* Prints the given socket to the COut. */
template <typename Char = CH1>
Char* TPrintSocket(Char* cursor, Char* stop, const void* begin,
                   const void* end) {
  ASSERT(begin || cursor || cursor < stop);

  Char* buffer_begin = cursor;
  const Char *address_ptr = reinterpret_cast<const Char*>(begin),
             *address_end_ptr = reinterpret_cast<const Char*>(end);
  SIW size = address_end_ptr - address_ptr,
      num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - cursor) <= num_bytes) {
    PRINTF("\n    ERROR: buffer overflow trying to fit %i in %i bytes!",
           (SI4)num_bytes, (SI4)(stop - cursor));
    return nullptr;
  }
  size += num_bytes;
  cursor = TPrint<Char>(cursor, stop, STRSocketHeader());
  cursor = TPrint<Char>(cursor, stop, STRSocketBorder());
  cursor = TPrintHex<Char>(cursor, stop, address_ptr);

  PRINTF("\nBuffer space left:%i", (SI4)(stop - cursor));
  Char c;
  while (address_ptr < address_end_ptr) {
    *cursor++ = kLF;
    *cursor++ = '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (!c || c == kTAB)
        c = ' ';
      else if (c < ' ')
        c = kDEL;
      *cursor++ = c;
    }
    *cursor++ = '|';
    *cursor++ = ' ';
    cursor = TPrintHex<Char>(cursor, stop, address_ptr);
  }
  cursor = TPrint<Char>(cursor, stop, STRSocketBorder());
  return TPrintHex<Char>(cursor, stop, address_ptr + size);
}

/* An empty string. */
template <typename Char = CH1>
const Char* TSTREmpty() {
  static const Char kStrand[] = {NIL};
  return kStrand;
}

/* The new-line s. */
template <typename Char = CH1>
const Char* TSTRNL() {
  static const Char kStrand[] = {kLF};
  return kStrand;
}

/* Strand the reads "Error:". */
template <typename Char = CH1>
const Char* TSTRError() {
  static const Char kStrand[] = {kLF, 'E', 'r', 'r', 'o', 'r', ':', NIL};
  return kStrand;
}

/* Converts the given item to a printable CH1 if it's non-printable. */
template <typename Char = CH1>
inline Char TCharPrintable(Char item) {
  if (item < 32 || item == 127) return ' ';
  return item;
}

/* Sets the s to either the given item or empty s if input
is nil. */
template <typename Char = CH1>
inline Char* TSTRSet(Char* string) {
  if (!string) return TSTREmpty<Char>();
  return string;
}

/* Searches fro the s line stop.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
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
template <typename Char = CH1>
Char* TSTRLineEnd(Char* cursor, SI4 column_count = 80) {
  return const_cast<Char*>(
      TSTRLineEnd(reinterpret_cast<const Char*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CH1>
const Char* TSTRLineEnd(const Char* cursor, const Char* stop,
                        SI4 column_count = 80) {
  if (!cursor) {
    PRINTF("\nText buffer overflow!");
    return nullptr;
  }
  ASSERT(cursor < stop);
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
template <typename Char = CH1>
inline Char* TSTRLineEnd(Char* cursor, Char* stop, SI4 column_count = 80) {
  return const_cast<const Char*>(
      TSTRLineEnd<Char>(reinterpret_cast<const Char*>(cursor),
                        reinterpret_cast<const Char*>(stop), column_count));
}

/* Finds the stop of the decimals in the s, if there are any.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
const Char* TSTRDecimalEnd(const Char* cursor, const Char* stop) {
  ASSERT(cursor);
  ASSERT(cursor <= stop);
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
template <typename Char = CH1>
inline Char* TSTRDecimalEnd(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TSTRDecimalEnd<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop)));
}

/* Skips the given Char in a s if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
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

/* Skips the given Char in a s if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
inline Char* TSTRSkipChar(Char* cursor, Char skip_char) {
  return const_cast<const Char*>(
      TSTRSkipChar<Char>(reinterpret_cast<const Char*>(cursor), skip_char));
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
const Char* TSTRSkipSpaces(const Char* cursor) {
  if (!cursor) return nullptr;
  Char c = *cursor;
  while (TIsWhitespace<Char>(c)) {
    PRINT('.');
    if (!c) return cursor;  //< This isn't an error as far as I can see.
    ++cursor;
    c = *cursor;
  }
  return cursor;
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
Char* TSTRSkipSpaces(Char* cursor) {
  return const_cast<Char*>(TSTRSkipSpaces<Char>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param  cursor  The first Char in the buffer.
@param  query   A query string.  */
template <typename Char = CH1>
const Char* TSTRFind(const Char* start, const Char* query) {
  ASSERT(start);
  ASSERT(query);

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
template <typename Char = CH1>
inline Char* TSTRFind(Char* string, const Char* query) {
  return const_cast<Char*>(
      TSTRFind<Char>(reinterpret_cast<const Char*>(string),
                     reinterpret_cast<const Char*>(query)));
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip. */
template <typename Char = CH1>
const Char* TSTRSkipSpaces(const Char* cursor, const Char* stop) {
  if (!cursor) return nullptr;
  if (cursor > stop) return nullptr;
  PRINTF("\nSkipping spaces: ");
  Char c = *cursor;
  while (IsWhitespace(c)) {
    PRINT('.');
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
template <typename Char = CH1>
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
template <typename Char = CH1>
const Char* TSTREquals(const Char* string_a, const Char* string_b) {
  ASSERT(string_a);
  ASSERT(string_b);
  PRINTF("\nComparing \"%s\" to \"%s\"", string_a, string_b);

  Char a = *string_a, b = *string_b;
  while (a) {
    PRINT(a);
    if (a != b) {  // Not a hit.
      PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      PRINTF("\nFound hit at 0x%p", string_a);
      return string_a;
    }
    a = *(++string_a);
    b = *(++string_b);
  }
  if (b) {
    PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  PRINTF("\nFound hit at 0x%p", string_a);
  return string_a;  //< Find hit!
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a.
*/
template <typename Char = CH1>
inline Char* TSTREquals(Char* string_a, const Char* string_b) {
  return const_cast<Char*>(
      TSTREquals<Char>(reinterpret_cast<const Char*>(string_a),
                       reinterpret_cast<const Char*>(string_b)));
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CH1>
const Char* TSTREquals(const Char* cursor, const Char* stop,
                       const Char* query) {
  if (!cursor) return nullptr;
  ASSERT(cursor < stop);
  if (!query) return nullptr;

  PRINTF("\nComparing \"%s\" to \"%s\"", cursor, query);

  Char a = *cursor, b = *query;
  while (a) {
    PRINT(a);
    if (a != b) {  // Not a hit.
      PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      PRINTF("\nFound hit at 0x%p", cursor);
      return cursor;
    }
    if (cursor > stop) {
      return nullptr;
    }
    a = *(++cursor);
    b = *(++query);
  }
  if (b) {
    PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  PRINTF("\nFound hit at 0x%p.", cursor);
  return cursor;
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CH1>
Char* TSTREquals(Char* cursor, Char* stop, const Char* query) {
  return const_cast<Char*>(TSTREquals(reinterpret_cast<const Char*>(cursor),
                                      reinterpret_cast<const Char*>(stop),
                                      query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CH1>
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
template <typename Char = CH1>
BOL TSTRIsntEmpty(Char* cursor) {
  return TSTRIsntEmpty<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
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
template <typename Char = CH1>
BOL TSTRIsntEmpty(Char* cursor, const Char* stop) {
  return TSTRIsntEmpty(reinterpret_cast<const Char*>(cursor),
                       reinterpret_cast<const Char*>(stop));
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the Char after the last Char in the
given range.
@param  cursor  The first Char in the buffer.
@param  lower_bounds
@param  upper bounds*/
template <typename Char = CH1>
const Char* TSTRSkipCharsInRange(const Char* cursor, Char lower_bounds,
                                 Char upper_bounds) {
  ASSERT(cursor);
  ASSERT(lower_bounds < upper_bounds);
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
template <typename Char = CH1>
Char* TSTRSkipCharsInRange(Char* cursor, Char lower_bounds, Char upper_bounds) {
  return const_cast<Char*>(TSTRSkipCharsInRange(
      reinterpret_cast<const Char*>(cursor), lower_bounds, upper_bounds));
}

/* Skips the numbers in the given range. */
template <typename Char = CH1>
inline const Char* TSTRSkipNumbers(const Char* cursor) {
  return const_cast<Char*>(TSTRSkipCharsInRange<Char>(
      reinterpret_cast<const Char*>(cursor), '0', '9'));
}
/* Skips the numbers in the given range. */
template <typename Char = CH1>
inline Char* TSTRSkipNumbers(Char* cursor) {
  return const_cast<Char*>(
      TSTRSkipNumbers<Char>(reinterpret_cast<const Char*>(cursor)));
}

/* Prints the given item aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param  item  The item to utf.
@param  column_count The token_ of columns to align right to. */
template <typename Char = CH1>
Char* TPrintRight(Char* cursor, Char* stop, const Char* item,
                  SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;
  PRINTF("\ncursor:%p end:%p", cursor, stop);

  if (!cursor || column_count < 1) return nullptr;

  if (cursor + column_count > stop) {
    PRINT("\nBuffer overflow!");
    return nullptr;
  }

  auto item_end = TSTREnd<Char>(item);
  Char c;  //< Temp variable.
  if (item == item_end) return cursor;
  SIW length = item_end - item;

  // If the length is less than the column_count we need to print ".", "..",
  // "..." or nothing and chop off some of the item.
  SIW count = column_count - length;
  PRINTF("\n\nPrinting \"%s\":%i aligned right %i columns count:%i", item,
         (SI4)length, column_count, count);
  if (count < 0) {
    SIW dot_count = length + count;
    PRINTF(" dot_count:%i", (int)dot_count);
    if (dot_count <= 3) {
      PRINTF("\n Wrote dots:\"");
      while (dot_count-- > 0) {
        *cursor++ = '.';
        PRINT('.');
      }
      PRINT('\"');
      *cursor = 0;
      return cursor;
    }
    stop = cursor + column_count;
    *stop-- = 0;
    *stop-- = '.';
    *stop-- = '.';
    *stop-- = '.';
    item_end = item + column_count - 4;
    PRINTF("\n Wrote with dots backwards:\"...");
    while (item_end > item) {
      c = *item_end--;
      *stop-- = c;
      PRINT(c);
    }
    c = *item_end--;
    *stop-- = c;
    PRINT(c);
    PRINTF("\"");
    return cursor + column_count;
  }
  PRINTF("\ncursor:0x%p end:0x%p item:0x%p token_end:0x%p", cursor, stop, item,
         item_end);
  // In order to keep the current cache lines we're going to utf
  // backwards back from the token_end.
  PRINTF("\n Wrote backwards:\"");
  stop = cursor + column_count;
  --item_end;   //< This is pointed at the nil-term CH1
  *stop-- = 0;  //< and there is no need to load a 0.
  while (item_end >= item) {
    c = *item_end--;
    *stop-- = c;
    PRINT(c);
  }
  while (stop >= cursor) {
    *stop-- = ' ';
    PRINT(' ');
  }
  PRINTF("\"\nWrote:\"%s\"", cursor);
  return cursor + column_count;
}

/* Prints the given cursor center aligned to the given column_count. */
template <typename Char = CH1>
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string,
                   SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;

  // We need to leave at least one space to the left and right of
  SI4 length = TSTRLength<Char>(string);
  PRINTF("\n\nPrinting \"%s\":%i centered to %i columns", string, length,
         column_count);
  SI4 delta;
  if (length <= column_count) {
    delta = (column_count - length) >> 1;  //< >> 1 to /2
    length = column_count - length - delta;
    PRINTF("\nlength:%i offset:%i", length, delta);

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
template <typename Char = CH1>
Char* TPrintLinef(Char* start, Char* stop, Char item, SI4 count = 80,
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
template <typename Char = CH1>
Char* TPrintLinef(Char* start, Char* stop, const Char* item, SI4 count = 80,
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
template <typename Char = CH1>
Char* TPrintHeadingf(Char* start, Char* stop, Char item, SI4 count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CH1>
Char* TPrintHeadingf(Char* start, Char* stop, const Char* item,
                     SI4 count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints a cursor to the given buffer without */
template <typename Char = CH1>
Char* TPrintWrap(Char* cursor, Char* stop, const Char* string,
                 SI4 column_count = 80) {
  if (!cursor || cursor <= stop || !string) return nullptr;
  if (column_count < 3) {
    PRINT("\nFix me!");
  }
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

/* Converts the given Char to lowercase. */
template <typename Char = CH1>
Char TLowercase(Char c) {
  if ((c & 0x3f) == 3) return c - 64;
  return c;
}

/* Initializes an ASCII Strand. */
template <typename SIZ, typename Char>
inline Char* TStrandInit(UIW* obj, SIZ size) {
  UIW address = reinterpret_cast<UIW>(AArrayInit<SIZ>(obj, size));
  return reinterpret_cast<Char*>(address + sizeof(SIZ));
}

/* ASCII TKN (Token). */
template <typename Char = CH1, SIN kTokenLongest_ = kTokenLongest>
class TToken {
 public:
  enum { kLengthMax = kTokenLongest_ };

  TToken(CH1 item = 0, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    auto cursor = strand_;
    *cursor = item;
    *cursor = 0;
  }

  TToken(const CH1* item, SI4 count = kTokenLongest_)
      : string_(item), count_(count) {
    if (!item) *strand_ = 0;
  }

  TToken(CH2 item = 0, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    auto cursor = strand_;
    *cursor = item;
    *cursor = 0;
  }

  TToken(CH4 item = 0, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    auto cursor = strand_;
    *cursor = item;
    *cursor = 0;
  }

  TToken(const CH4* item, SI4 count = kTokenLongest_)
      : string_(item), count_(count) {
    if (!item) *strand_ = 0;
  }

  TToken(SI4 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(UI4 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(SI8 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(UI8 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

#if USING_FP4 == YES
  /* Prints the item to the token_. */
  TToken(FP4 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }
#endif

#if USING_FP8 == YES
  /* Prints the item to the token_. */
  TToken(FP8 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }
#endif

  /* Gets the string_. */
  inline const Char* String() { return string_; }

  /* Gets the strand_. */
  inline Char* Strand() { return strand_; }

  /* Gets the string_ or the strand_ if the string_ is nil. */
  inline const Char* Get() {
    const Char* ptr = string_;
    return ptr ? ptr : strand_;
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
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH1* item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH2 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH2* item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH4* item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI8 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI8 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

#if USING_FP4 == YES
  /* Prints the given item to the strand_. */
  inline Char* Print(FP4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }
#endif
#if USING_FP8 == YES
  /* Prints the given item to the strand_. */
  inline Char* Print(FP8 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }
#endif

 private:
  // Pointer to a token too big to fit in the strand_.
  const Char* string_;
  SI4 count_;                        //< The count.
  Char strand_[kTokenLongest_ + 1];  //< Strand buffer for the token.
};

/* Utility class for printing hex with operator<<. */
template <typename Char = CH1>
struct TCenter {
  TToken<Char> token;  //< Pointer to a pointer to utf.

  /* Prints the item to the . */
  TCenter(CH1 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(const CH1* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(CH2 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(const CH2* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(CH4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(const CH4* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(SI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(UI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(SI8 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(UI8 item, SI4 count = 80) : token(item, count) {}

#if USING_FP4 == YES
  /* Prints the item to the token_. */
  TCenter(FP4 item, SI4 count = 80) : token(item, count) {}
#endif
#if USING_FP8 == YES
  /* Prints the item to the token_. */
  TCenter(FP8 item, SI4 count = 80) : token(item, count) {}
#endif
};

/* Utility class for printing hex with operator<<. */
template <typename Char = CH1>
struct TRight {
  TToken<Char> token;  //< Pointer to a pointer to utf.

  /* Prints the item to the token_. */
  TRight(CH1 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(const CH1* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(CH2 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(const CH2* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(CH4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(const CH4* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(SI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(UI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(SI8 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(UI8 item, SI4 count = 80) : token(item, count) {}

#if USING_FP4 == YES
  /* Prints the item to the token_. */
  TRight(FP4 item, SI4 count = 80) : token(item, count) {}
#endif
#if USING_FP8 == YES
  /* Prints the item to the token_. */
  TRight(FP8 item, SI4 count = 80) : token(item, count) {}
#endif
};

/* Utility class for printing a string line with operator<<. */
template <typename Char = CH1>
struct TLinef {
  TToken<Char> token;

  TLinef(CH1 item, SI4 count = 80) : token(item, count) {}

  TLinef(const CH1* item, SI4 count = 80) : token(item, count) {}

  TLinef(CH2 item, SI4 count = 80) : token(item, count) {}

  TLinef(const CH2* item, SI4 count = 80) : token(item, count) {}

  TLinef(CH4 item, SI4 count = 80) : token(item, count) {}

  TLinef(const CH4* item, SI4 count = 80) : token(item, count) {}
};

/* Utility class for printing a single Char token line with operator<<. */
template <typename Char = CH1>
struct THeadingf {
  TToken<Char> token;
  const Char *style, *caption2, *caption3;

  THeadingf(const CH1* caption, const CH1* style = nullptr,
            SI4 column_count = kTokenLongest, const CH1* caption2 = nullptr,
            const CH1* caption3 = nullptr) {
    TPrintHeadingf<CH1>(caption, style, column_count, caption2, caption3);
  }

  THeadingf(const CH2* caption, const CH2* style = nullptr,
            SI4 column_count = kTokenLongest, const CH2* caption2 = nullptr,
            const CH2* caption3 = nullptr) {
    TPrintHeadingf<CH2>(caption, style, column_count, caption2, caption3);
  }

  THeadingf(const CH4* caption, const CH4* style = nullptr,
            SI4 column_count = kTokenLongest, const CH4* caption2 = nullptr,
            const CH4* caption3 = nullptr) {
    TPrintHeadingf<CH4>(caption, style, column_count, caption2, caption3);
  }
};

/* Universal Text Formatter (UTF).
The UTF only stores the start and stop pointers allowing the length to be
storred on the stack or hard-coded using instructions. If you want an normal
string-like class please use the TStrand, which auto-grows from stack to heap.
*/
template <typename Char = CH1, typename SIZ = SI4>
struct TUTF {
  Char *start,  //< Start address.
      *stop;    //< Stop address.

  /* Default constructor does nothing. */
  TUTF() {}

  /* Initializes the UTF& from the given begin pointers.
  @param start The begin of the begin.
  @param count The number of Char(s) in the buffer. */
  TUTF(Char* start, SIZ count)
      : start(start), stop(TPtr<Char>(start, count - 1)) {
    DASSERT(start);
    Reset();
  }

  /* Initializes the UTF& from the given begin pointers.
  @param begin The begin address of a word-aligned socket.
  @param count The size in bytes. */
  TUTF(UIW* begin, SIZ size)
      : start(reinterpret_cast<Char*>(begin)),
        stop(TPtr<Char>(begin, size - 1)) {
    DASSERT(start);
    Reset();
  }

  /* Initializes the UTF& from the given begin pointers.
  @param begin The begin address of a word-aligned socket.*/
  TUTF(UIW* begin)
      : start(TSTRStart<Char, SIZ>(begin)), stop(TSTRStop<Char, SIZ>(begin)) {
    DASSERT(begin);
    Reset();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TUTF(Char* start, Char* stop) : start(start), stop(stop) {
    DASSERT(start);
    DASSERT(start < stop);
    Reset();
  }

  /* Clones the other utf. */
  TUTF(const TUTF& other)
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
  inline TUTF& Set(Char* cursor) {
    DASSERT(cursor);
    start = cursor;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TUTF& Set(UIW* buffer) {
    DASSERT(buffer);
    SIZ size = *reinterpret_cast<SIZ*>(buffer);
    UIW ptr = reinterpret_cast<UIW>(buffer) + sizeof(SIZ);
    Char* start_ptr = reinterpret_cast<Char*>(ptr);
    start = start_ptr;
    stop = start_ptr + size - 1;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline void Set(TUTF<Char> other) {
    start = other.start;
    stop = other.stop;
  }

  /* Finds the length of the STR in Chars. */
  inline SIZ SpaceLeft() { return (SIZ)(stop - start); }

  /* Calculates the max length of the string in Chars. */
  inline SIZ LengthMax() { return stop - start; }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH1 item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH2 item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH4 item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH1 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH2 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH4 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH1* item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH2* item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH4* item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints the given item. */
  inline TUTF& Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

  /* Prints the given item. */
  inline TUTF& Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

  /* Prints the given item. */
  inline TUTF& Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

  /* Prints the given item. */
  inline TUTF& Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
  /* Prints the given item.
  @return A UTF. */
  inline TUTF& Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
#endif
#if USING_FP8 == YES
  /* Prints the given item.
  @return A UTF. */
  inline TUTF& Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
#endif

  /* Prints the given item. */
  inline TUTF& Print(TRight<Char> item) {
    return Set(::_::TPrintRight<Char>(start, stop, item.token.String(),
                                      item.token.Count()));
  }

  /* Prints the given item. */
  inline TUTF& Print(TCenter<Char> item) {
    return Set(::_::TPrintCenter<Char>(start, stop, item.token.String(),
                                       item.token.Count()));
  }

  /* Prints the given item. */
  inline TUTF& Print(TLinef<Char> item) {
    return Set(::_::TPrintLinef<Char>(start, stop, item.token.String(),
                                      item.token.Count()));
  }

  /* Prints the given item. */
  inline TUTF& Print(THeadingf<Char> item) {
    return Set(::_::TPrintLinef<Char>(start, stop, item.token.String(),
                                      item.token.Count()));
  }

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(Hex item) {
    return TPrintHex<Char>(*this, item.Begin(), item.Size());
  }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI1 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI1 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI2 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI2 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI4 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI4 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI8 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI8 item) { return Set(TPrintHex<Char>(start, stop, item)); }

#if USING_FP4 == YES
  /* Prints the given item as hex. */
  inline TUTF& Hex(FP4 item) { return Set(TPrintHex<Char>(start, stop, item)); }
#endif
#if USING_FP8 == YES
  /* Prints the given item as hex. */
  inline TUTF& Hex(FP8 item) { return Set(TPrintHex<Char>(start, stop, item)); }
#endif

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(const void* ptr) {
    return Set(TPrintHex<Char>(start, stop, ptr));
  }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI1 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI1 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI2 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI2 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI4 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI4 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI8 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI8 item) { return Set(Binary<Char>(start, stop, item)); }

#if USING_FP4 == YES
  /* Prints the given item as binary. */
  inline TUTF& Binary(FP4 item) { return Set(Binary<Char>(start, stop, item)); }
#endif
#if USING_FP8 == YES
  /* Prints the given item as binary. */
  inline TUTF& Binary(FP8 item) { return Set(Binary<Char>(start, stop, item)); }
#endif
  /* Prints the given pointer as binary. */
  inline TUTF& Binary(const void* ptr) {
    UIW address = reinterpret_cast<UIW>(ptr);
    return Set(Binary<Char>(start, stop, address));
  }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
#if DEBUG_SEAM
    o << "\nTUTF<CH" << sizeof(Char) << ", SI" << sizeof(SIZ) << ">{ start:";
    TPrintHex<Printer>(o, start);
    o << " stop:";
    TPrintHex<Printer>(o, stop);
    o << " }\n";
    TPrintSocket<Printer>(o, start, End());
    return TPrintChars<Printer, Char>(o, start, stop);
#endif
    return o;
  }
};

/* Returns the first CH1 in the cursor socket. */
template <typename Char = CH1, typename SIZ = SI4>
inline Char* TSTRStart(UIW* start) {
  UIW address = reinterpret_cast<UIW>(start) + sizeof(SIZ);
  return reinterpret_cast<Char*>(address);
}

/* Searches for the stop of the strand. */
template <typename Char = CH1, typename SIZ = SI4>
inline Char* TSTRStop(void* begin) {
  SIZ size = *reinterpret_cast<SIZ*>(begin);
  UIW address = reinterpret_cast<UIW>(begin);
  Char* ptr = reinterpret_cast<Char*>(address + sizeof(SIZ));
  return ptr + (size >> TBitShiftCount<Char>()) - 1;
}

/* Searches for the stop of the strand. */
template <typename Char = CH1, typename SIZ = SI4>
inline Char* TSTRStop(void* begin, SIW size_bytes) {
  UIW address = reinterpret_cast<UIW>(begin);
  Char* ptr = reinterpret_cast<Char*>(address + sizeof(SIZ));
  return ptr + (size_bytes >> TBitShiftCount<Char>()) - 1;
}

/* Queries the given s for the given query. */
template <typename Char = CH1>
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
      PRINTF(" is not a hit.");
      return result;
    }
    if (!a) {
      PRINTF(" is a partial match but !a.");
      return result;
    }
    if (++cursor >= stop) {
      PRINTF(" but buffer overflowed!");
      return result;
    }
    ++query;
    a = *cursor;
    b = *query;
  }
  if (a && !TIsWhitespace<Char>(a)) {
    PRINTF(" is only a partial match but found %s", (a ? "a" : "space"));
    return b - a;
  }
  PRINTF(" is a match!");
  return 0;
}

}  // namespace _

/* Prints the given item to the UTF.
@return The utf.
@param  utf The utf.
@param  item   The item to utf. */
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, CH1 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const CH1* item) {
  return utf.Print(item);
}

#if USING_UTF16 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, CH2 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const CH2* item) {
  return utf.Print(item);
}
#endif
#if USING_UTF32 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, CH4 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const CH4* item) {
  return utf.Print(item);
}
#endif

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI1 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI1 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI2 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI2 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI4 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI4 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI8 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI8 item) {
  return utf.Print(item);
}

#if USING_FP4 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, FP4 item) {
  return utf.Print(item);
}
#endif
#if USING_FP8 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, FP8 item) {
  return utf.Print(item);
}
#endif

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TCenter<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TRight<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TLinef<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::THeadingf<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TToken<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Hex& item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Chars1& item) {
  return TPrintChars<Printer>(utf, item.start, item.stop);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Nil& socket) {
  utf.Set(socket.Start(), socket.Stop());
  return *this;
}

template <typename Char = CH1, SIW kSize_>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TSocket<kSize_>& socket) {
  utf.Set(socket.Start(), socket.Stop());
  return *this;
}
#endif
#endif
