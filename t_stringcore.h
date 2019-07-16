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

#ifndef SCRIPT2_T_STRING
#define SCRIPT2_T_STRING 1

#include "c_utf.h"

#if SEAM == SEAM_SCRIPT2_RGN
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

template <typename Printer, typename Char = CH1>
SIN TPrintAndCount(Printer& o, const Char* string) {
  SIN print_count = 0;
  Char c;
  while ((c = *string++) != 0) {
    o << c;
    ++print_count;
  }
  return print_count;
}

/* Compares the two strings up to the given delimiter.
@param delimiter Delimiters in Script2 are equal to or less than.
@return 0 if the strings are equal or a non-zero delta upon failure. */
template <typename Char = CH1>
SIN TSTRCompare(const Char* string_a, const Char* string_b,
                Char delimiter = 0) {
  SIN a, b, result;
  if (!string_a) {
    if (!string_b) return 0;
    return *string_a;
  }
  if (!string_b) return 0 - *string_a;

  D_PRINTF("\nComparing \"%s\" to \"%s\"", string_a, string_b);
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
      D_COUT(" is not a hit.");
      return result;
    }
    if (a <= (SI4)delimiter) {
      D_COUT(" is a partial match but a reached a delimiter first.");
      return result;
    }
    ++string_a;
    ++string_b;
    a = *string_a;
    b = *string_b;
  }
  if (a > (SI4)delimiter) {
    D_PRINTF(" is only a partial match but b reached a delimiter first.");
    return b - a;
  }
  return 0;
}

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
#if USING_FP4 == YES
inline UI4 ToUnsigned(FP4 value) { return *reinterpret_cast<UI4*>(&value); }
#endif
#if USING_FP8 == YES
inline UI8 ToUnsigned(FP8 value) { return *reinterpret_cast<UI8*>(&value); }
#endif

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
template <typename Printer, typename SI, typename UI>
Printer& TPrintHex(Printer& o, SI item) {
  return TPrintHex<Printer, UI>(o, (UI)item);
}
#if USING_FP4 == YES
template <typename Printer>
Printer& TPrintHex(Printer& o, FP4 item) {
  UI4 value = *reinterpret_cast<UI4*>(&item);
  return TPrintHex<Printer, UI4>(o, value);
}
#endif
#if USING_FP8 == YES
template <typename Printer>
Printer& TPrintHex(Printer& o, FP8 item) {
  UI8 value = *reinterpret_cast<UI8*>(&item);
  return TPrintHex<Printer, UI8>(o, value);
}
#endif
/* Prints the given hex memory block or POD value depending on the sign of the
byte_count.

If the byte_count is less than zero the value will be treated like a POD type,
which will need to get printed backwards on Big-endian systems. The purpose of
little endian is that it's easier to read the hex values when you print them,
which is frutrating because of how simple the conversion code is. If the
byte_count is greater than zero then the memory will be printed sequentially
one byte at a time. */
template <typename Printer>
Printer& TPrintHex(Printer& o, const void* begin, SIW byte_count) {
  if (!begin) return o;
  SIW address, delta;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
#if CPU_ENDIAN == LITTLE_ENDIAN
  if (byte_count < 0) {
    delta = -1;
    cursor -= byte_count + 1;
  } else {
    delta = 1;
  }
#else
  delta = 1;
#endif
  while (byte_count-- > 0) {
    UI1 byte = *cursor;
    cursor += delta;
    o << HexNibbleToUpperCase(byte & 0xf) << HexNibbleToUpperCase(byte >> 4);
  }
  return o;
}

template <typename Printer>
Printer& TPrintHex(Printer& o, const void* start, const void* stop) {
  SIW delta = reinterpret_cast<SIW>(stop) - reinterpret_cast<SIW>(start);
  return TPrintHex<Printer>(o, start, delta);
}

/* Prints the given value to Binary. */
template <typename Printer, typename SI>
Printer& TPrintBinary(Printer& o, const void* begin, SI byte_count) {
  if (!begin) return o;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
#if CPU_ENDIAN == LITTLE_ENDIAN
  SI1 delta;
  if (byte_count < 0) {
    delta = -1;
    byte_count = -byte_count;
    cursor += byte_count - 1;
  } else {
    delta = 1;
  }
#endif
  while (--byte_count >= 0) {
    UI1 c = *cursor;
    cursor += delta;
    for (SIW i = 8; i > 0; --i) {
      o << (CH1)('0' + (c >> 7));
      c = c << 1;
    }
  }
  return o;
}
template <typename Printer>
Printer& TPrintBinary(Printer& o, const void* start, const void* stop) {
  return TPrintBinary<Printer>(o, start, TDelta<>(start, stop));
}

template <typename Printer, typename UI>
Printer& TPrintBinary(Printer& o, UI item) {
  enum { kSize = sizeof(UI) * 8 };
  auto ui = ToUnsigned(item);
  for (SI4 i = kSize; i > 0; --i) {
    CH1 c = (CH1)('0' + (ui >> (kSize - 1)));
    o << c;
    ui = ui << 1;
  }
  return o;
}

template <typename Printer, typename SI, typename UI>
Printer& TPrintBinary(Printer& o, SI item) {
  return TPrintBinary<Printer, UI>(o, (UI)item);
}
#if USING_FP4 == YES
template <typename Printer>
Printer& TPrintBinary(Printer& o, FP4 item) {
  UI4 value = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<Printer, UI4>(o, value);
}
#endif
#if USING_FP4 == YES
template <typename Printer>
Printer& TPrintBinary(Printer& o, FP8 item) {
  UI8 value = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<Printer, UI8>(o, value);
}
#endif

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline const Char* TSTREnd(const Char* start, CH1 delimiter = 0) {
  while (*start++ != delimiter)
    ;
  return start - 1;
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

template <typename Printer>
Printer& TPrintIndent(Printer& o, SIW indent_count) {
  o << '\n';
  while (--indent_count >= 0) o << ' ';
  return o;
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
                        SIW column_count = 80) {
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
Printer& TPrintLinef(Printer& o, Char token = '-', SIW column_count = 80) {
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
                        const CH1* style = nullptr, SIW column_count = 80,
                        const CH1* caption2 = nullptr,
                        const CH1* caption3 = nullptr) {
  if (!style) style = TSTRHeadingf<CH1>();
  style = TPrintLinef<Printer, CH1>(o, style, column_count);
  if (!style) return o;
  o << caption;
  if (caption2) o << caption2;
  if (caption3) o << caption3;
  TPrintLinef<Printer, CH1>(o, style, column_count);
  return o;
}

template <typename Printer, typename Char = CH1>
Printer& TPrintChars(Printer& o, const Char* start, const Char* stop) {
  if (!start || start >= stop) return o;

  SIW size = stop - start, extra_row = ((size & 63) != 0) ? 1 : 0,
      row_count = (size >> 6) + extra_row;

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;
  o << STRPrintCharsHeader() << STRPrintCharsBorder() << "0x" << Hexf(start);
  int i = 0;
  Char c;
  while (start <= stop) {
    o << '\n' << '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *start++;
      if (start > stop)
        c = 'x';
      else if (c < ' ')
        c = c + kPrintC0Offset;
      o << Char(c);
    }
    o << "| 0x" << Hexf(start);
  }
  return o << STRPrintCharsBorder() << "0x" << Hexf(start + size);
}

template <typename Printer, typename Char = CH1>
Printer& TPrintChars(Printer& o, const Char* start, SIW count) {
  return TPrintChars<Printer, Char>(o, start, start + count - 1);
}

template <typename Char>
Char* TScanChar(Char* cursor, Char& c) {}

template <typename Char>
Char TToLower(Char c) {
  if (c >= 'A' && c <= 'Z') c -= 32;
  return c;
}

template <typename Char>
SIN TIsYesNo(const Char* string) {
  if (!string) return 0;
  CHR c = TToLower<Char>(*string++);
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
}  // namespace _

#if SEAM == SEAM_SCRIPT2_RNG
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char = CH1>
const Char* TScanSigned(const Char* start, SI& result) {
  D_ASSERT(start);
  SI sign;
  const Char* cursor = start;
  Char c = *cursor++;
  if (c == '-') {
    D_COUT("\nScanning negative backwards:\"");
    c = *start++;
    sign = -1;
  } else {
    D_COUT("\nScanning positive backwards:\"");
    sign = 1;
  }
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* stop = cursor;  // Store stop to return.
  cursor -= 2;
  D_PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
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
    D_PRINTF("\nvalue:%u", (UIN)value);
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
  return const_cast<Char*>(TScanSigned<SI, UI, Char>(ptr, result));
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename Char = CH1>
const Char* TScan(const Char* start, SI1& result) {
  return TScanSigned<SI1, UI1, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, SI1& result) {
  return TScanSigned<SI1, UI1, Char>(start, result);
}
template <typename Char = CH1>
const Char* TScan(const Char* start, SI2& result) {
  return TScanSigned<SI2, UI2, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, SI2& result) {
  return TScanSigned<SI2, UI2, Char>(start, result);
}
template <typename Char = CH1>
const Char* TScan(const Char* start, SI4& result) {
  return TScanSigned<SI4, UI4, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, SI4& result) {
  return TScanSigned<SI4, UI4, Char>(start, result);
}
template <typename Char = CH1>
const Char* TScan(const Char* start, SI8& result) {
  return TScanSigned<SI8, UI8, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, SI8& result) {
  return TScanSigned<SI8, UI8, Char>(start, result);
}

/* Checks if the given CH1 is a digit of a number_.
@return True if it is a digit. */
template <typename Char = CH1>
BOL TIsDigit(Char c) {
  return (c >= '0') && (c <= '9');
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CH1>
const Char* TScanUnsigned(const Char* start, UI& result) {
  D_ASSERT(start);
  D_PRINTF("\n\nScanning unsigned value:%s", start);
  const Char* cursor = start;
  Char c = *cursor++;
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* stop = cursor;  // Store stop to return.
  cursor -= 2;
  D_PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
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
    D_PRINTF("\nvalue:%u", (UIN)value);
  }
  D_PRINTF("\nvalue:%u", (UIN)value);
  result = value;
  return stop;
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

/* Scans the given socket for a UI1
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename Char = CH1>
const Char* TScan(const Char* start, UI1& result) {
  return TScanUnsigned<UI1, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, UI1& result) {
  return TScanUnsigned<UI1, Char>(start, result);
}
template <typename Char = CH1>
const Char* TScan(const Char* start, UI2& result) {
  return TScanUnsigned<UI2, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, UI2& result) {
  return TScanUnsigned<UI2, Char>(start, result);
}
template <typename Char = CH1>
const Char* TScan(const Char* start, UI4& result) {
  return TScanUnsigned<UI4, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, UI4& result) {
  return TScanUnsigned<UI4, Char>(start, result);
}
template <typename Char = CH1>
const Char* TScan(const Char* start, UI8& result) {
  return TScanUnsigned<UI8, Char>(start, result);
}
template <typename Char = CH1>
Char* TScan(Char* start, UI8& result) {
  return TScanUnsigned<UI8, Char>(start, result);
}

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

}  // namespace _

#endif
