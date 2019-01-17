/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tbinary.h
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

#ifndef INCLUDED_SCRIPTTBINARY
#define INCLUDED_SCRIPTTBINARY 1

#if defined(_MSC_VER) && defined(_M_AMD64)
#include <intrin.h>
#endif

#include "cbinary.h"

#include "cconsole.h"
#include "tsocket.h"

#if SEAM >= _0_0_0__00
#if SEAM == _0_0_0__00
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

/* Prints the given string. */
namespace _ {
template <typename Char>
void TPrintString(const Char* string) {
  if (!string) return;
  Char c = *string;
  while (c) {
    Print(c);
    c = *(++string);
  }
}

/* Compares the two strings up to the given delimiter.
@return SI4 0 if the strings are equal or a non-zero delta upon failure.
@param  string_a String A.
@param  string_b String B.
@param  delimiter The delimiter.*/
template <typename Char = const CH1>
SI4 TStringCompare(const Char* string_a, const Char* string_b,
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
    if (!a) return 0;  //< I like !t code rather than !c code. :-)
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
}  // namespace _

#endif

#if SEAM >= _0_0_0__01
#if SEAM == _0_0_0__01
#include "test_debug.inl"
#define BEGIN_ITOS_ALGORITHM                                         \
  static const CH1* ui_format = sizeof(UI) == 8 ? FORMAT_UI8 : "%u"; \
  TPuffItoSBegin<Char>(cursor);                                      \
  for (SI4 i = 0; i < 10; ++i) *(cursor + i) = 'x';                  \
  *(cursor + 21) = 0;                                                \
  enum { kSize = 256 };                                              \
  CH1 socket[kSize];                                                 \
  sprintf_s(socket, kSize, ui_format, value);                        \
  Printf(" Expecting %s:%i ", socket, TStringLength<Char>(socket))
#define PRINT_PRINTED TPrintPrinted<Char>(TPuffItoSBegin<Char>())
#else
#include "test_release.inl"
#define BEGIN_ITOS_ALGORITHM
#define PRINT_PRINTED
#endif

namespace _ {

template <typename Char>
SIW TPrintAndCount(const Char* string) {
  if (!string) return 0;
  SI4 print_count = 0;
  Char c = *string;
  while (c) {
    Print(c);
    ++print_count;
    c = *(++string);
  }
  return print_count;
}

template <typename Char>
Char* TPuffItoSBegin(Char* cursor = nullptr) {
  static Char* buffer_begin = 0;
  if (cursor) {
    buffer_begin = cursor;
    return cursor;
  }
  return buffer_begin;
}

template <typename Char>
void TPrintPrinted(Char* cursor) {
  Print("\n    Printed \"");
  SIW print_count = TPrintAndCount<Char>(TPuffItoSBegin<Char>());
  Print('\"', ':');
  Print(print_count);
}

/* Unsigned Not-a-number_ is any number_ that can't be aligned up properly. */
template <typename UI>
inline UI TUnsignedNaN() {
  return (~(UI)0);  // -sizeof (UIW) - 2;
}

/* The highest possible signed integer value of the given type SI. */
template <typename SI>
inline SI TSignedMax() {
  return ((~(SI)0) << 4) >> 1;
}

/* Signed Not-a-number_ is the lowest possible signed integer value. */
template <typename SI, typename UI>
inline SI TSignedNaN() {
  return (SI)(((UI)1) << (sizeof(SI) * 8 - 1));
}

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline const Char* TStringEnd(const Char* cursor, Char delimiter = 0) {
  ASSERT(cursor);
  while (*cursor++ != delimiter)
    ;
  return cursor - 1;
}

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1>
inline Char* TStringEnd(Char* cursor, Char delimiter = 0) {
  return const_cast<Char*>(
      TStringEnd(reinterpret_cast<const Char*>(cursor), delimiter));
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1, typename I = SI4>
I TStringLength(const Char* cursor) {
  ASSERT(cursor);
  return (I)(TStringEnd<Char>(cursor) - cursor);
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CH1, typename I = SI4>
inline I TStringLength(Char* cursor) {
  return TStringLength<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Prints a Unicode string to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   cursor    The beginning of the socket.
 @param   stop       The last UI1 in the socket.
 @param   string    The string to utf.
 @param   delimiter The delimiter to utf (usually nil).
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if string is nil. */
template <typename Char = CH1>
Char* TPrint(Char* cursor, Char* stop, const Char* string, Char delimiter = 0) {
  ASSERT(cursor);
  ASSERT(string);

  if (cursor >= stop) return nullptr;

  Char c = *string++;
  while (c) {
    *cursor++ = c;
    if (cursor >= stop) return nullptr;
    c = *string++;
  }
  *cursor = delimiter;
  return cursor;
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   string    The string to utf.
@param   delimiter The delimiter to utf (usually nil).
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CH1>
Char* TPrint(Char* cursor, SIW size, const Char* string, Char delimiter = 0) {
  return TPrint<Char>(cursor, cursor + size - 1, string, delimiter);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   string    The string to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
template <typename Char = CH1>
Char* TPrint(Char* cursor, SIW size, Char character) {
  return TPrint<Char>(cursor, cursor + size, character);
}

inline UI1 ShiftRight(UI1 value, UI1 count) { return value >> count; }
inline UI2 ShiftRight(UI2 value, UI2 count) { return value >> count; }
inline UI4 ShiftRight(UI4 value, UI4 count) { return value >> count; }
inline UI8 ShiftRight(UI8 value, UI8 count) { return value >> count; }

/* Prints a hex value to the Console. */
template <typename Char, typename UI>
Char* TPrintHexTest(Char* cursor, Char* stop, UI value) {
  enum { kHexStringLengthSizeMax = sizeof(UI) * 2 + 3 };

  ASSERT(cursor);
  if (cursor + kHexStringLengthSizeMax >= stop) return nullptr;

  *cursor++ = '0';
  *cursor++ = 'x';
  for (SI4 num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    UI shifted_value = ShiftRight(value, num_bits_shift);
    *cursor++ = HexNibbleToUpperCase((UI1)shifted_value);
  }
  *cursor = 0;
  return cursor;
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, SI1 value) {
  return TPrintHexTest<Char, UI1>(cursor, stop, (UI1)value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, UI1 value) {
  return TPrintHexTest<Char, UI1>(cursor, stop, value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, SI2 value) {
  return TPrintHexTest<Char, UI2>(cursor, stop, (UI2)value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, UI2 value) {
  return TPrintHexTest<Char, UI2>(cursor, stop, value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, SI4 value) {
  return TPrintHexTest<Char, UI4>(cursor, stop, (UI4)value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, UI4 value) {
  return TPrintHexTest<Char, UI4>(cursor, stop, value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, SI8 value) {
  return TPrintHexTest<Char, UI8>(cursor, stop, (UI8)value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, UI8 value) {
  return TPrintHexTest<Char, UI8>(cursor, stop, value);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHexTest<Char, UI8>(cursor, stop, ui);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHexTest<Char, UI8>(cursor, stop, ui);
}

/* Prints a hex value to the Console. */
template <typename Char = CH1>
inline Char* TPrintHex(Char* cursor, Char* stop, const void* ptr) {
  UIW address = reinterpret_cast<UIW>(ptr);
  return TPrintHexTest<Char, UIW>(cursor, stop, address);
}

/* Prints the given value to Binary. */
template <typename Char = CH1, typename UI>
Char* TPrintBinary(Char* cursor, Char* stop, UI value) {
  if (cursor + sizeof(UI8) * 8 >= stop) {
    return nullptr;
  }

  for (SI4 i = 0; i < sizeof(UI) * 8; ++i) {
    *cursor++ = (Char)('0' + (value >> (sizeof(UI) * 8 - 1)));
    value = value << 1;
  }
  *cursor = 0;
  return cursor;
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, SI1 value) {
  return TPrintBinary<Char, UI1>(cursor, stop, (UI1)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, UI1 value) {
  return TPrintBinary<Char, UI1>(cursor, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, SI2 value) {
  return TPrintBinary<Char, UI2>(cursor, stop, (UI2)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, UI2 value) {
  return TPrintBinary<Char, UI2>(cursor, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, SI4 value) {
  return TPrintBinary<Char, UI4>(cursor, stop, (UI4)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, UI4 value) {
  return TPrintBinary<Char, UI4>(cursor, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, SI8 value) {
  return TPrintBinary<Char, UI8>(cursor, stop, (UI8)value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
inline Char* TPrintBinary(Char* cursor, Char* stop, UI8 value) {
  return TPrintBinary<Char, UI8>(cursor, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
Char* TPrintBinary(Char* cursor, Char* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<Char, UI4>(cursor, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
Char* TPrintBinary(Char* cursor, Char* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<Char, UI8>(cursor, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CH1>
Char* TPrintBinary(Char* cursor, Char* stop, const void* ptr) {
  UIW address = *reinterpret_cast<UIW*>(&ptr);
  return TPrintBinary<Char, UIW>(cursor, stop, address);
}

/* Checks if the given character is whitespace. */
template <typename Char = CH1>
inline BOL TIsWhitespace(Char character) {
  return character <= ' ';
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking and if the SEAM ==
_0_0_0 (1), then this function will utf debug data. */
template <typename Char = CH1>
inline Char* TPrintDecimal(Char* socket, Char value) {
  *reinterpret_cast<Char*>(socket) = '0' + value;
  PRINT_PRINTED;
  return socket;
}

/* Prints a single decimal to the socket.
If the SEAM == _0_0_0 (1), then this function will utf debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = CH1>
inline Char* TPrintChar(Char* socket, Char value) {
  *socket++ = value;
  PRINT_PRINTED;
  return socket;
}

/* Prints a single decimal to the socket.
If the SEAM == _0_0_0 (1), then this function will utf debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = CH1>
inline Char* TPrintChar(Char* socket, Char* stop, Char value) {
  if (!socket || socket >= stop) return nullptr;
  *socket++ = value;
  PRINT_PRINTED;
  return socket;
}

/* Prints a Unicode Char to the given socket.
@return Nil upon failure or a pointer to the nil-term Char upon success.
@param  cursor    The beginning of the socket.
@param  size      The size of the socket in Char(s).
@param  character The Char to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
template <typename Char = CH1>
Char* TPrintChar(Char* cursor, SIW size, Char character) {
  return ::_::Print(cursor, cursor + size - 1, character);
}

inline CH1* PrintChar(CH1* cursor, CH1 c) { return TPrintChar<CH1>(cursor, c); }

inline CH2* PrintChar(CH2* cursor, CH2 c) { return TPrintChar<CH2>(cursor, c); }

inline CH4* PrintChar(CH4* cursor, CH4 c) { return TPrintChar<CH4>(cursor, c); }

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
  ASSERT(start);
  PRINTF("\nScanning unsigned value:%s", start);
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
    PRINTF("\nvalue:%u", (uint)value);
  }
  PRINTF("\nvalue:%u", (uint)value);
  result = value;
  return stop;
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CH1>
Char* TScanUnsigned(Char* cursor, UI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(cursor);
  return const_cast<Char*>(TScanUnsigned<UI, Char>(ptr, result));
}
/* Prints two chars to the console.
@warning This function DOES NOT do any error checking! */
template <typename Char = CH1>
inline Char* TPrintNil(Char* cursor) {
  *cursor = 0;
  return cursor;
}

/* Prints a two decimals to the socket.
If the SEAM == _0_0_0 (1), then this function will utf debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = CH1>
inline Char* TPrint2Decimals(Char* socket, UI2 decimal_pair) {
  enum { kSizeBits = sizeof(Char) * 8 };
  socket[0] = (Char)(decimal_pair >> 8);
  CH1 c = (CH1)decimal_pair;
  socket[1] = (Char)(c);
  PRINT_PRINTED;
  return socket;
}

inline CH1* PrintCharPair(CH1* socket, UI2 value) {
#if ALIGN_MEMORY
  socket[0] = (CH1)(value >> 8);
  socket[1] = (CH1)(value);
#else
  *((UI2*)socket) = value;
#endif
  using Char = CH1;
  PRINT_PRINTED;
  return socket;
}

inline CH2* PrintCharPair(CH2* cursor, UI2 decimal_pair) {
  return TPrint2Decimals<CH2>(cursor, decimal_pair);
}

inline CH4* PrintCharPair(CH4* cursor, UI2 decimal_pair) {
  return TPrint2Decimals<CH4>(cursor, decimal_pair);
}

/* Prints 8 decimals to the given socket with given LUT.*/
template <typename Char = CH1>
Char* TPrint8Decimals(Char* cursor, UI4 value, const UI2* lut) {
  PRINT("\n    Printing 8 decimals:");
  PRINT(value);
  UI2 pow_10_ui2 = 10000, digits6and5 = (UI2)(value / pow_10_ui2),
      digits2and1 = value - pow_10_ui2 * digits6and5;
  pow_10_ui2 = 100;
  UI2 digits8and7 = digits6and5 / pow_10_ui2,
      digits4and3 = digits2and1 / pow_10_ui2;
  digits6and5 -= pow_10_ui2 * digits8and7;
  digits2and1 -= pow_10_ui2 * digits4and3;
  PrintCharPair(cursor, lut[digits8and7]);
  PrintCharPair(cursor + 2, lut[digits6and5]);
  PrintCharPair(cursor + 4, lut[digits4and3]);
  PrintCharPair(cursor + 6, lut[digits2and1]);
  PRINT_PRINTED;
  return cursor + 8;
}

template <typename Char = CH1>
inline void TPrint8or16Decimals(Char* cursor, UI4 lsd, const UI2* lut,
                                UI4 middle_sd, UI4 delta) {
  if (delta == 8) {
    PRINTF("\n    Printing less than 17 decimals:");
    TPrint8Decimals<Char>(cursor, lsd, lut);
  } else {
    PRINTF("\n    Printing more than 16 decimals:");
    TPrint8Decimals<Char>(cursor, middle_sd, lut);
    TPrint8Decimals<Char>(cursor + 8, lsd, lut);
  }
}

inline UI4 ValueUI4(UI4 value) { return value; }
inline UI4 ValueUI4(UI8 value) { return (UI4)value; }

/* Prints the give value to the given socket as a Unicode string.
@return Nil upon socket overflow and a pointer to the nil-term Char upon
success.
@param  cursor The beginning of the socket.
@param  stop    The stop address of the socket. */
template <typename UI = UI8, typename Char = CH1>
Char* TPrintUnsigned(Char* cursor, Char* stop, UI value) {
  BEGIN_ITOS_ALGORITHM;

  if (!cursor || cursor >= stop) return nullptr;

  Char* nil_ptr;
  UI2 pow_10_ui2, delta = 0;
  UI4 pow_10_ui4;
  const UI2* lut = BinaryLUTDecimals();

  // The best way to understand how the numbers are getting converted is that
  // numbers get broken up into up to 8 pairs of 100, in each pair of 10000
  // there will be a Most Significant Decimal (MSD) pair and a Least
  // Significant Decimal (LSD) pair. The digits2and1 and digits6and5 will
  // always be the LSD and digits4and3 and digits8and7 will always be the MSD.

  if (value < 10) {
    PRINT("\n    Range:[0, 9] length:1 ");
  Print1:
    nil_ptr = cursor + delta + 1;
    if (nil_ptr >= stop) return nullptr;
    TPrintDecimal<Char>(cursor, (Char)value);
    return TPrintNil<Char>(cursor + delta + 1);
  } else if (value < 100) {
  Print2:
    PRINT("\n    Range:[10, 99] length:2 ");
    nil_ptr = cursor + delta + 2;
    if (cursor + delta + 2 >= stop) return nullptr;
    PrintCharPair(cursor, lut[value]);
    return TPrintNil<Char>(cursor + delta + 2);
  } else {
    if ((value >> 10) == 0) {
      pow_10_ui2 = 1000;
      if (value >= pow_10_ui2) {
      Print4A:
        PRINT("\n    Range:[1000, 1023] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= stop) return nullptr;
        UI2 digits2and1 = (UI2)(value - pow_10_ui2);
#if CPU_ENDIAN == LITTLE_ENDIAN
        cursor[0] = '1';
        cursor[1] = '0';
#else
        cursor[0] = '0';
        cursor[1] = '1';
#endif
        PrintCharPair(cursor + 2, lut[digits2and1]);
        return TPrintNil<Char>(nil_ptr);
      }
    Print3:
      PRINT("\n    Range:[100, 999] length:3");
      nil_ptr = cursor + delta + 3;
      if (nil_ptr >= stop) return nullptr;
      UI2 digits2and1 = (UI2)value, pow_10_ui2 = 100;
      Char digit = (Char)(digits2and1 / pow_10_ui2);
      digits2and1 -= ((UI2)digit) * pow_10_ui2;
      TPrintDecimal<Char>(cursor, digit);
      PrintCharPair(cursor + 1, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 14) == 0) {
      pow_10_ui2 = 10000;
      if (value >= pow_10_ui2) {
      Print5A:
        PRINT("\n    Range:[10000, 16383] length:5");
        nil_ptr = cursor + delta + 5;
        if (nil_ptr >= stop) return nullptr;
        cursor = TPrintChar<Char>(cursor, '1');
        value -= pow_10_ui2;
      } else {
      Print4:
        PRINT("\n    Range:[1024, 9999] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= stop) return nullptr;
        TPrintNil<Char>(nil_ptr);
      }
      pow_10_ui2 = 100;
      UI2 digits2and1 = (UI2)value, digits4and3 = digits2and1 / pow_10_ui2;
      digits2and1 -= digits4and3 * pow_10_ui2;
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 17) == 0) {
      if (value >= 100000) {
      Print6A:
        PRINT("\n    Range:[65536, 131071] length:6");
        goto Print6;
      }
    Print5:
      PRINT("\n    Range:[10000, 65535] length:5");
      nil_ptr = cursor + delta + 5;
      if (nil_ptr >= stop) return nullptr;
      UI4 value_ui4 = ValueUI4(value);
      pow_10_ui2 = 10000;
      Char digit6 = (UI1)(value_ui4 / pow_10_ui2);
      value_ui4 -= pow_10_ui2 * digit6;
      cursor = TPrintChar<Char>(cursor, '0' + digit6);
      pow_10_ui2 = 100;
      UI2 digits4and3 = ((UI2)value_ui4) / pow_10_ui2,
          digits2and1 = (UI2)(value_ui4 - digits4and3 * pow_10_ui2);
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 20) == 0) {
      pow_10_ui4 = 1000000;
      if (value >= pow_10_ui4) {
      Print7A:
        PRINT("\n    Range:[100000, 1048575] length:7");
        nil_ptr = cursor + delta + 7;
        if (nil_ptr >= stop) return nullptr;
        cursor = PrintChar(cursor, '1');
        value -= pow_10_ui4;
      } else {
      Print6:
        PRINT("\n    Range:[131072, 999999] length:6");
        nil_ptr = cursor + delta + 6;
        if (nil_ptr >= stop) return nullptr;
        TPrintNil<Char>(nil_ptr);
      }
      UI4 value_ui4 = (UI4)value;
      pow_10_ui2 = 10000;
      UI2 digits6and5 = (UI2)(value_ui4 / pow_10_ui2),
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      UI2 digits8and7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digits8and7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      PrintCharPair(cursor, lut[digits6and5]);
      PrintCharPair(cursor + 2, lut[digits4and3]);
      PrintCharPair(cursor + 4, lut[digits2and1]);
      return nil_ptr;
    } else if ((value >> 24) == 0) {
      pow_10_ui4 = 10000000;  //< 10^7
      if (value >= pow_10_ui4) {
        PRINT("\n    Range:[10000000, 16777216] length:8");
        return TPrint8Decimals<Char>(cursor, ValueUI4(value), lut);
      }
    Print7:
      PRINT("\n    Range:[1048576, 9999999] length:7");
      nil_ptr = cursor + delta + 7;
      if (nil_ptr >= stop) return nullptr;
      UI2 pow_10_ui2 = 10000;
      UI4 value_ui4 = ValueUI4(value);
      UI2 digits6and5 = value_ui4 / pow_10_ui2,
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      UI2 digit7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digit7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      TPrintDecimal(cursor, (Char)(digit7));
      PrintCharPair(cursor + 1, lut[digits6and5]);
      PrintCharPair(cursor + 3, lut[digits4and3]);
      PrintCharPair(cursor + 5, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else {
      UI4 comparator = 100000000;  // 10^8
      UI msd = (value >= (~(UI4)0)) ? value / comparator
                                    : ValueUI4(value) / comparator;
      UI4 lsd = (UI4)(value - comparator * msd), middle_sd;
      if (msd >= comparator) {
        delta = 16;
        value = msd / comparator;
        middle_sd = ValueUI4(msd - value * comparator);
        PRINT(value);
        PRINT('_');
        PRINT(middle_sd);
        PRINT('_');
        PRINT(lsd);
      } else {
        value = msd;
        middle_sd = 0;
        delta = 8;
        PRINT(value);
        PRINT('_');
        PRINT(lsd);
      }
      if (value < 10) {
        TPrint8or16Decimals<Char>(cursor + 1, lsd, lut, middle_sd, delta);
        goto Print1;
      } else if (value < 100) {
        TPrint8or16Decimals<Char>(cursor + 2, lsd, lut, middle_sd, delta);
        goto Print2;
      }
      if ((value >> 10) == 0) {
        pow_10_ui2 = 1000;
        if (value >= pow_10_ui2) {
          TPrint8or16Decimals<Char>(cursor + 4, lsd, lut, middle_sd, delta);
          goto Print4A;
        }
        TPrint8or16Decimals<Char>(cursor + 3, lsd, lut, middle_sd, delta);
        goto Print3;
      } else if ((value >> 13) == 0) {
        pow_10_ui2 = 10000;
        if (value >= pow_10_ui2) {
          TPrint8or16Decimals<Char>(cursor + 5, lsd, lut, middle_sd, delta);
          goto Print5A;
        }
        TPrint8or16Decimals<Char>(cursor + 4, lsd, lut, middle_sd, delta);
        goto Print4;
      } else if ((value >> 17) == 0) {
        pow_10_ui4 = 100000;
        if (value >= pow_10_ui4) {
          TPrint8or16Decimals<Char>(cursor + 6, lsd, lut, middle_sd, delta);
          goto Print6A;
        }
        TPrint8or16Decimals<Char>(cursor + 5, lsd, lut, middle_sd, delta);
        goto Print5;
      } else if ((value >> 20) == 0) {
        pow_10_ui4 = 1000000;
        if (value >= pow_10_ui4) {
          TPrint8or16Decimals<Char>(cursor + 7, lsd, lut, middle_sd, delta);
          goto Print7A;
        }
        TPrint8or16Decimals<Char>(cursor + 6, lsd, lut, middle_sd, delta);
        goto Print6;
      } else {
        comparator = 10000000;
        if (value >= comparator) {
          TPrint8Decimals<Char>(cursor, ValueUI4(value), lut);
          TPrint8Decimals<Char>(cursor + 8, lsd, lut);
          return TPrintNil<Char>(cursor + 16);
        }
        TPrint8or16Decimals<Char>(cursor + 7, lsd, lut, middle_sd, delta);
        goto Print7;
      }
    }
  }
  return nullptr;  //< Unreachable.
}

template <typename UI = UI8, typename Char = CH1>
inline Char* TPrintUnsigned(Char* socket, SI4 size, UI value) {
  return TPrintUnsigned<UI, Char>(socket, socket + size - 1, value);
}

/* Writes the give value to the given socket as an ASCII string.
@return Nil upon socket overflow and a pointer to the nil-term Char upon
success.
@param  utf The text formatter to utf to.
@param value The value to write. */
template <typename SI = SI8, typename UI = UI8, typename Char = CH1>
inline Char* TPrintSigned(Char* socket, Char* stop, SI value) {
  if (value >= 0) {
    return TPrintUnsigned<UI, Char>(socket, stop, (UI)value);
  }
  *socket++ = '-';
  return TPrintUnsigned<UI, Char>(socket, stop, (UI)(-(SI)value));
}

/* Writes the give value to the given socket as an ASCII string.
@return Nil upon socket overflow and a pointer to the nil-term Char upon
success.
@param  utf The text formatter to utf to.
@param value The value to write. */
template <typename SI = SI8, typename UI = UI8, typename Char = CH1>
inline Char* TPrintSigned(Char* socket, SI4 size, SI value) {
  return TPrintSigned<SI, UI, Char>(socket, socket + size - 1, value);
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char>
const Char* TScanSigned(const Char* start, SI& result) {
  ASSERT(start);
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
    PRINTF("\nvalue:%u", (uint)value);
  }
  result = sign * value;
  return stop;
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char>
Char* TScanSigned(Char* cursor, SI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(cursor);
  return const_cast<Char*>(TScanSigned<SI, UI, Char>(ptr));
}
}  // namespace _
#endif  //< #if SEAM >= _0_0_0__01

#if SEAM >= _0_0_0__02
#if SEAM == _0_0_0__02
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif
namespace _ {

/* Finds the end of a decimal number starting at the given cursor.
@return Nil if the string doesn't contain a decimal or is nil.
@param  cursor The start of the string to search. */
template <typename Char = const CH1>
const Char* TStringDecimalEnd(const Char* cursor) {
  if (!cursor) return cursor;
  Char c = *cursor++;
  if (c == '-') c = *cursor++;
  if (c < '0' || c > '9') return nullptr;
  c = *cursor++;
  while (TIsDigit<Char>(c)) {
    c = *cursor++;
    if (c <= 0) return cursor - 1;
  }
  return cursor - 1;
}

template <typename Char = const CH1>
Char* TStringDecimalEnd(Char* cursor) {
  const Char* ptr = reinterpret_cast<const Char*>(cursor);
  return const_cast<Char*>(TStringDecimalEnd<Char>(ptr));
}
}  // namespace _
#endif

#if SEAM >= _0_0_0__04
#if SEAM == _0_0_0__04
#include "test_debug.inl"
#define PRINT_FLOAT_BINARY(integer, decimals, decimal_count) \
  Print("\nBinary:\"");                                      \
  TPrintBinary(value);                                       \
  Print('\n')
#else
#include "test_release.inl"
#define PRINT_FLOAT_BINARY(integer, decimals, decimal_count)
#endif
namespace _ {

/* Searches for the highest MSb asserted.
@return -1 */
template <typename UI>
SI4 TMSbAssertedReverse(UI value) {
  for (SI4 i = sizeof(UI) * 8 - 1; i > 0; --i)
    if ((value >> i) != 0) return i;
  return -1;
}

template <typename Char>
Char* TPrint3(Char* socket, Char* stop, Char a, Char b, Char c) {
  if (!socket || socket + 3 >= stop) return nullptr;
  *socket++ = a;
  *socket++ = b;
  *socket++ = c;
}

/* A decimal number in floating-point format.
To use this class template the sizeof (Float) must equal the sizeof (UI) and
sizeof (SI). */
template <typename Float = FPW, typename UI = UIW, typename SI = SI4>
class TBinary {
 public:
  enum {
    kSize = sizeof(Float),
    kSizeBits = kSize * 8,
    kMSbIndex = kSizeBits - 1,
    kStringLengthMax = 24,
    kExponentSizeBits =
        (sizeof(Float) == 2)
            ? 5
            : (sizeof(Float) == 4) ? 8 : (sizeof(Float) == 8) ? 11 : 15,
    kCoefficientSize = kSizeBits - kExponentSizeBits - 1,
    kMantissaSize = kSizeBits - kExponentSizeBits - 2,
    kExponentMaskUnshifted = (~((UI)0)) >> (kSizeBits - kExponentSizeBits),
    kExponentBias = kExponentMaskUnshifted + kCoefficientSize,
    kExponentMin = -kExponentBias,
  };

  // Constructs an uninitialized floating-point number_.
  TBinary() {}

  inline static UI Coefficient(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  // Converts a Float to a TBinary
  TBinary(Float binary) {
    UI ui = *reinterpret_cast<UI*>(&binary);
    UI4 biased_e = (UI4)(ui << 1);  //< Get rid of sign bit.
    // Get rid of the integral portion.
    biased_e = biased_e >> (kSizeBits - kExponentSizeBits);
    // Get rid of the sign and exponent.
    UI coefficient = Coefficient(ui);
    if (biased_e != 0) {
      f = coefficient + (((UI)1) << kExponentSizeBits);
      e = biased_e - kExponentBias;
    } else {
      f = coefficient;
      e = kExponentMin + 1;
    }
  }

  TBinary(UI f, SI e) : f(f), e(e) {}

  TBinary(const TBinary a, const TBinary b) {}

  inline static UI Exponent(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  template <typename Char = CH1>
  static Char* Print(Char* socket, Char* stop, Float value) {
    // Not handling NaN and inf
    if (IsNaN(value)) {
      if (stop - socket < 4) return nullptr;
      socket[0] = 'N';
      socket[1] = 'a';
      socket[2] = 'N';
      socket[3] = 0;
      return socket + 4;
    }
    if (IsInfinite(value)) {
      if (stop - socket < 4) return nullptr;
      UI f = *reinterpret_cast<UI*>(&value);
      socket[0] = (f >> (sizeof(UI) * 8 - 1)) ? '-' : '+';
      socket[1] = 'i';
      socket[2] = 'n';
      socket[3] = 'f';
      socket[4] = 0;
      return socket + 5;
    }

    if (value == 0) {
      return TPrint3<Char>(socket, stop, (Char)'0', (Char)'.', (Char)'0');
    }
    if (value < 0) {
      *socket++ = '-';
      value = -value;
    }
    SI k;
    Char* cursor = Print<Char>(socket, stop, value, k);
    if (!cursor) return cursor;
    return Standardize<Char>(socket, stop, cursor - socket, k);
  }

  template <typename UI = UIW>
  static inline UI NaNUnsigned() {
    UI nan = 0;
    return ~nan;
  }

  template <typename SI, typename UI>
  static inline SI NaNSigned() {
    UI nan = 1;
    return (SI)(nan << (sizeof(UI) * 8 - 1));
  }

  static TBinary IEEE754Pow10(SI e, SI& k) {
    // SI k = static_cast<SI>(ceil((-61 - e) *
    // 0.30102999566398114))

    // + 374; dk must be positive to perform ceiling function on positive
    // values.
    Float scalar = sizeof(Float) == 8 ? 0.30102999566398114 : 0.301029995f,
          dk = (-61 - e) * scalar + 347;
    k = static_cast<SI>(dk);
    if (k != dk) ++k;

    SI index = static_cast<UI4>((k >> 3) + 1);

    k = -(-348 + static_cast<SI>(index << 3));
    // decimal exponent no need lookup table.

    ASSERT(index < 87);

    // Save exponents pointer and offset to avoid creating base pointer again.
    UI new_f = IEEE754LUTF(index);
    SI new_e = (SI)IEEE754LUTE(index);
    return TBinary(new_f, new_e);
  }

  TBinary<Float, UI, SI> Minus(const TBinary<Float, UI, SI>& value) const {}

  void Print() {
    PRINTF(
        "\nkSize:%i kSizeBits:%i kMSbIndex:%i kStringLengthMax:%i"
        "\nkExponentSizeBits:%i kCoefficientSize:%i kMantissaSize:%i"
        "\nkExponentMaskUnshifted:%i kExponentBias:%i kExponentMin:%i\n\n",
        kSize, kSizeBits, kMSbIndex, kStringLengthMax, kExponentSizeBits,
        kCoefficientSize, kMantissaSize, kExponentMaskUnshifted, kExponentBias,
        kExponentMin);
  }

 private:
  UI f;
  SI e;

  static inline void Multiply(TBinary& result, TBinary& a, TBinary& b) {}

  template <typename Char>
  static Char* Print(Char* socket, Char* stop, Float value, SI& k) {
    TBinary v(value);
    TBinary lower_estimate, upper_estimate;
    v.NormalizedBoundaries(lower_estimate, upper_estimate);

    TBinary c_mk = IEEE754Pow10(upper_estimate.e, k);

    TBinary W(v.NormalizeBoundary(), c_mk);
    TBinary w_plus(upper_estimate, c_mk), w_minus(lower_estimate, c_mk);
    w_minus.f++;
    w_plus.f--;
    return DigitGen<Char>(socket, stop, W, w_plus, w_plus.f - w_minus.f, k);
  }

  TBinary NormalizeBoundary() const {
    // SI msba = MSbAsserted(0);
#if defined(_MSC_VER) && defined(_M_AMD64)
    unsigned long index;  //< This is Microsoft's fault.
    _BitScanReverse64(&index, f);
    return TBinary(f << (kMSbIndex - index), e - (kMSbIndex - index));
#else
    TBinary res = *this;
    UI kDpHiddenBit = ((UI)1) << kMantissaSize;  // 0x0010000000000000;
    while (!(res.f & (kDpHiddenBit << 1))) {
      res.f <<= 1;
      --res.e;
    }
    res.f <<= (kDiySignificandSize - kCoefficientSize - 2);
    res.e = res.e - (kDiySignificandSize - kCoefficientSize - 2);
    return res;
#endif
  }

  // static const UI  kDpExponentMask = 0x7FF0000000000000,
  //   kDpSignificandMask = 0x000FFFFFFFFFFFFF,

  // Normalizes the boundaries.
  void NormalizedBoundaries(TBinary& m_minus, TBinary& m_plus) const {
    UI l_f,   //< Local copy of f.
        l_e;  //< Local copy of e.
    TBinary pl = TBinary((l_f << 1) + 1, ((SI)l_e) - 1).NormalizeBoundary();
    const UI kHiddenBit = ((UI)1) << kMantissaSize;  //< 0x0010000000000000
    TBinary mi = (f == kHiddenBit) ? TBinary((l_f << 2) - 1, e - 2)
                                   : TBinary((l_f << 1) - 1, e - 1);
    mi.f <<= mi.e - pl.e;
    mi.e = pl.e;
    m_plus = pl;
    m_minus = mi;
  }

  // Rounds the Grisu estimation closer to the inside of the squeeze.
  static UI4 Round(UI4 lsd, UI delta, UI rest, UI ten_kappa, UI wp_w) {
    while (rest < wp_w && (delta - rest) >= ten_kappa &&
           (rest + ten_kappa < wp_w ||  /// closer
            (wp_w - rest) > (rest + ten_kappa - wp_w))) {
      --lsd;
      rest += ten_kappa;
    }
    return lsd;
  }

  static inline UI4 Pow10(UI4 p_1, SI4& kappa) {
    UI4 pow_10 = 10;
    if (p_1 < pow_10) {
      kappa = 1;
      return pow_10;
    } else if (p_1 < (pow_10 = 100)) {
      kappa = 2;
      return pow_10;
    } else if ((p_1 >> 10) == 0) {
      pow_10 = 1000;
      if (p_1 >= pow_10) goto Kappa4;
      kappa = 3;
      return pow_10;
    } else if (!(p_1 >> 13)) {
    Kappa4:
      pow_10 = 10000;
      if (p_1 >= pow_10) goto Kappa5;
      kappa = 4;
      return pow_10;
    } else if (!(p_1 >> 17)) {
    Kappa5:
      pow_10 = 100000;
      if (p_1 >= pow_10) goto Kappa6;
      kappa = 5;
      return pow_10;
    } else if (!(p_1 >> 20)) {
    Kappa6:
      pow_10 = 1000000;
      if (p_1 >= pow_10) goto Kappa7;
      kappa = 6;
      return pow_10;
    } else if (!(p_1 >> 24)) {
    Kappa7:
      pow_10 = 10000000;
      if (p_1 >= pow_10) goto Kappa8;
      kappa = 7;
      return pow_10;
    } else if (!(p_1 >> 27)) {
    Kappa8:
      pow_10 = 100000000;
      if (p_1 >= pow_10) goto Kappa9;
      kappa = 8;
      pow_10 = pow_10;
    } else {  // if (!(p_1 >> 30)) {
    Kappa9:
      pow_10 = 1000000000;
      kappa = 9;
      return pow_10;
    }
  }

  static inline UI4 Pow10(UI4 p_1, SI8& kappa) {
    UI4 pow_10 = 10;
    if (p_1 < pow_10) {
      kappa = 1;
      return pow_10;
    } else if (p_1 < (pow_10 = 100)) {
      kappa = 2;
      return pow_10;
    } else if ((p_1 >> 10) == 0) {
      pow_10 = 1000;
      if (p_1 >= pow_10) goto Kappa4;
      kappa = 3;
      return pow_10;
    } else if (!(p_1 >> 13)) {
    Kappa4:
      pow_10 = 10000;
      if (p_1 >= pow_10) goto Kappa5;
      kappa = 4;
      return pow_10;
    } else if (!(p_1 >> 17)) {
    Kappa5:
      pow_10 = 100000;
      if (p_1 >= pow_10) goto Kappa6;
      kappa = 5;
      return pow_10;
    } else if (!(p_1 >> 20)) {
    Kappa6:
      pow_10 = 1000000;
      if (p_1 >= pow_10) goto Kappa7;
      kappa = 6;
      return pow_10;
    } else if (!(p_1 >> 24)) {
    Kappa7:
      pow_10 = 10000000;
      if (p_1 >= pow_10) goto Kappa8;
      kappa = 7;
      return pow_10;
    } else {  // if (!(p_1 >> 27)) {
    Kappa8:
      pow_10 = 100000000;
      kappa = 8;
      pow_10 = pow_10;
    }
  }

  /* Prints the integer portion of the floating-point number_.
  @return Nil upon failure or a pointer to the nil-term Char upon success. */
  template <typename Char>
  static Char* DigitGen(Char* cursor, Char* stop, const TBinary& w,
                        const TBinary& m_plus, UI delta, SI& k) {
    TBinary one(((UI)1) << (-m_plus.e), m_plus.e), wp_w = m_plus.Minus(w);
    UI4 d, pow_10, p_1 = static_cast<UI4>(m_plus.f >> -one.e);
    UI p_2 = m_plus.f & (one.f - 1);
    SI kappa;
    pow_10 = Pow10(p_1, kappa);
    while (kappa > 0) {
      UI4 d;
      d = p_1 / pow_10;
      p_1 -= d * pow_10;

      if (cursor >= stop) return nullptr;

      if (d) cursor = TPrintDecimal<Char>(cursor, d);

      --kappa;
      UI tmp = (static_cast<UI>(p_1) << -one.e) + p_2;

      if (tmp <= delta) {
        k += kappa;
        UI pow_10_f = IEEE754LUTF(kappa);
        d = Round(d, delta, tmp, pow_10_f << -one.e, wp_w.f);
        return cursor;
      }
    }

    for (;;) {  // kappa = 0
      p_2 *= 10;
      delta *= 10;
      d = static_cast<UI4>(p_2 >> -one.e);
      if (cursor >= stop) return nullptr;
      if (d) *cursor++ = '0' + d;
      p_2 &= one.f - 1;
      --kappa;
      if (p_2 < delta) {
        k += kappa;
        UI pow_10_f = IEEE754LUTF(-kappa);
        d = Round(d, delta, p_2, one.f, wp_w.f * pow_10_f);
        return cursor;
      }
    }

    switch (kappa) {  // Load integer pow_10 from the i-cache.
      case 1:
        d = p_1;
        p_1 = 0;
        return cursor;
      case 2:
        pow_10 = 10;
        return cursor;
      case 3:
        pow_10 = 100;
        return cursor;
      case 4:
        pow_10 = 1000;
        return cursor;
      case 5:
        pow_10 = 10000;
        return cursor;
      case 6:
        pow_10 = 100000;
        return cursor;
      case 7:
        pow_10 = 1000000;
        return cursor;
      case 8:
        pow_10 = 10000000;
        return cursor;
      case 9:
        pow_10 = 100000000;
        return cursor;
      case 10:
        pow_10 = 1000000000;
        return cursor;
    }
    return cursor;
  }

  /* Converts the Grisu2 output to a standardized/easier-to-read format. */
  template <typename Char = CH1>
  static Char* Standardize(Char* socket, Char* stop, SIW length, SI k) {
    const SIW kk = length + k;  // 10^(kk-1) <= v < 10^kk
    Char* nil_term_char;
    if (length <= kk && kk <= 21) {  // 1234e7 -> 12340000000
      for (SIW i = length; i < kk; i++) socket[i] = '0';
      socket[kk] = '.';
      socket[kk + 1] = '0';
      nil_term_char = &socket[kk + 2];
      *nil_term_char = '\0';
      return nil_term_char;
    } else if (0 < kk && kk <= 21) {  // 1234e-2 -> 12.34
      SocketShiftUp(&socket[kk + 1], LastByte(&socket[kk]), length - kk);
      socket[kk] = '.';
      nil_term_char = &socket[length + 1];
      *nil_term_char = '\0';
      return nil_term_char;
    } else if (-6 < kk && kk <= 0) {  // 1234e-6 -> 0.001234
      const SIW offset = 2 - kk;
      SocketShiftUp(&socket[offset], LastByte(&socket[0]), length);
      socket[0] = '0';
      socket[1] = '.';
      for (SIW i = 2; i < offset; i++) socket[i] = '0';
      nil_term_char = &socket[length + offset];
      *nil_term_char = 0;
      return nil_term_char;
    } else if (length == 1) {
      // 1e30
      socket[1] = 'e';
      return TPrintSigned<SIW, UIW, Char>(socket + 2, stop, kk - 1);
    }
    // else 1234e30 -> 1.234e33
    SocketShiftUp(&socket[2], LastByte(&socket[1]), length - 1);

    *(++socket)++ = '.';
    *socket++ = 'e';
    return TPrintSigned<SIW, UIW, Char>(socket + length + 2, stop, kk - 1);
  }
};

using Binary32 = TBinary<FLT, UI4>;
using Binary64 = TBinary<DBL, UI8>;

template <typename Char = CH1>
Char* TPrint(Char* begin, Char* stop, FLT value) {
  return TBinary<FLT, UI4, SI4>::template Print<Char>(begin, stop, value);
}

template <typename Char = CH1>
Char* TPrintFloat(Char* begin, SIW size, FLT value) {
  return TPrint<Char>(begin, begin + size - 1, value);
}

template <typename Char = CH1>
Char* TPrint(Char* begin, Char* stop, DBL value) {
  return TBinary<DBL, UI8, SI8>::template Print<Char>(begin, stop, value);
}

template <typename Char = CH1>
Char* TPrint(Char* begin, SIW size, DBL value) {
  return TPrint<Char>(begin, begin + size - 1, value);
}

}  // namespace _
#undef PRINT_FLOAT_BINARY
#endif

#endif  //< #if INCLUDED_SCRIPTTBINARY
