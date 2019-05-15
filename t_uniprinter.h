/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_uniprinter.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_UNIPRINTER_T
#define SCRIPT2_UNIPRINTER_T 1

#include "c_sout.h"
#include "c_uniprinter.h"
#include "t_socket.h"
#include "t_string.h"

#if SEAM >= SCRIPT2_0
#if SEAM == SCRIPT2_0
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

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
}  // namespace _

#endif

#if SEAM >= SCRIPT2_1
#if SEAM == SCRIPT2_1
#include <cstdio>

#include "module_debug.inl"
#define BEGIN_ITOS_ALGORITHM                                         \
  static const CH1* ui_format = sizeof(UI) == 8 ? FORMAT_UI8 : "%u"; \
  TPuffItoSBegin<Char>(cursor);                                      \
  for (SI4 i = 0; i < 10; ++i) *(cursor + i) = 'x';                  \
  *(cursor + 21) = 0;                                                \
  enum { kSize = 256 };                                              \
  CH1 socket[kSize];                                                 \
  sprintf_s(socket, kSize, ui_format, value);                        \
  Printf(" Expecting %s:%i ", socket, TSTRLength<Char>(socket))
#define PRINT_PRINTED TPrintPrinted<Char>(TPuffItoSBegin<Char>())
#else
#include "module_release.inl"
#define BEGIN_ITOS_ALGORITHM
#define PRINT_PRINTED
#endif

namespace _ {

template <typename Char = CH1>
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

template <typename Char = CH1>
Char* TPuffItoSBegin(Char* start = nullptr) {
  static Char* buffer_begin = 0;
  if (start) {
    buffer_begin = start;
    return start;
  }
  return buffer_begin;
}

template <typename Char = CH1>
void TPrintPrinted(Char* start) {
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

/* Prints a hex value to a socket fater than using a Printer. */
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
template <typename Printer, typename SI>
Printer& TPrintBinary(Printer& o, const void* begin, SI byte_count) {
  if (!begin || byte_count <= 0) return o;
  const UI1* cursor = begin;
  while (--byte_count >= 0) {
    for (SI1 i = 8; i > 0; ++i) {
      UI1 c = *cursor++;
      o << (CHN)('0' + (c >> 7));
      c = c << 1;
    }
  }
  return o;
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
@warning This function DOES NOT do any error checking!  */
template <typename Char = CH1>
inline Char* TPrintDecimal(Char* socket, Char value) {
  *reinterpret_cast<Char*>(socket) = '0' + value;
  PRINT_PRINTED;
  return socket;
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking! */
template <typename T = CH1>
inline T* TWrite(T* socket, T value) {
  *socket++ = value;
  return socket;
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking! */
template <typename Char = CH1>
inline Char* TWriteChar(Char* socket, Char value) {
  *socket++ = value;
  PRINT_PRINTED;
  return socket;
}

/* Utility function for printing a char with any Unicode conversion. */
inline CH1* Write(CH1* cursor, CH1 c) { return TWriteChar<CH1>(cursor, c); }

inline CH2* Write(CH2* cursor, CH2 c) { return TWriteChar<CH2>(cursor, c); }

inline CH4* Write(CH4* cursor, CH4 c) { return TWriteChar<CH4>(cursor, c); }

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

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CH1>
Char* TScanUnsigned(Char* start, UI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TScanUnsigned<UI, Char>(ptr, result));
}
/* Prints two chars to the console.
@warning This function DOES NOT do any error checking! */
template <typename Char = CH1>
inline Char* TPrintNil(Char* start) {
  *start = 0;
  return start;
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

inline void PrintCharPair(CH1* socket, UI2 value) {
#if ALIGN_MEMORY
  socket[0] = (CH1)(value >> 8);
  socket[1] = (CH1)(value);
#else
  *((UI2*)socket) = value;
#endif
  using Char = CH1;
  PRINT_PRINTED;
}

inline void PrintCharPair(CH2* cursor, UI2 decimal_pair) {
  TPrint2Decimals<CH2>(cursor, decimal_pair);
}

inline void PrintCharPair(CH4* cursor, UI2 decimal_pair) {
  TPrint2Decimals<CH4>(cursor, decimal_pair);
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
        cursor = TWriteChar<Char>(cursor, '1');
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
      cursor = TWriteChar<Char>(cursor, '0' + digit6);
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
        cursor = TWriteChar<Char>(cursor, '1');
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

#if SEAM >= SCRIPT2_4
#if SEAM == SCRIPT2_4
#include "module_debug.inl"
#define PRINT_FLOAT_BINARY(integer, decimals, decimal_count) \
  Print("\nBinary:\"");                                      \
  TPrintBinary(value);                                       \
  PrintNL()
#else
#include "module_release.inl"
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

template <typename Char = CH1>
Char* TPrint3(Char* socket, Char* stop, Char a, Char b, Char c) {
  if (!socket || socket + 3 >= stop) return nullptr;
  *socket++ = a;
  *socket++ = b;
  *socket++ = c;
  return socket;
}

/* Masks off the given bits starting at b0. */
template <typename I, SIN kMSb_, SIN kLSb_>
I TMiddleBits(I value) {
  // The goal is to not allow for undefined shifting behavior and not pay for
  // the error checking.
  //                              b15 ---vv--- b8
  // Example: TMiddleBits<SI4, 15, 7> (0xff00)
  //          Expecting 0xff
  // right_shift_count = 32 - 16 = 16
  enum {
    kSize = sizeof(I) * 8,
    kMSbNatural = (kMSb_ < 0) ? 0 : kMSb_,
    kLSbLNatural = (kLSb_ < 0) ? 0 : kLSb_,
    kRightShiftTemp1 = kSize - kMSbNatural + 1,
    kRightShiftTemp2 = (kRightShiftTemp1 >= kSize) ? 0 : kRightShiftTemp1,
    kLeftShift = (kRightShiftTemp2 < kLSb_) ? 0 : kRightShiftTemp2,
    kRightShift = (kRightShiftTemp2 < kLSb_) ? 0 : kRightShiftTemp2,
  };
  return (value << kRightShift) >> kLeftShift;
}

/* A decimal number in floating-point format.
To use this class the sizeof (Float) must equal the sizeof (UI) and sizeof (SI).
*/
template <typename Float = FPW, typename SI = SI4, typename UI = UIW>
class TBinary {
 public:
  enum {
    kSizeMax = 8,
    kSize = sizeof(Float) >= kSizeMax ? 0 : sizeof(Float),
    kSizeBits = kSize * 8,
    kMSb = kSizeBits - 1,
    kStrandLengthMax = 24,
    kExponentSizeBits =
        (sizeof(Float) == 2)
            ? 5
            : (sizeof(Float) == 4) ? 8 : (sizeof(Float) == 8) ? 11 : 15,
    kCoefficientSize = kSizeBits - kExponentSizeBits - 1,
    kMantissaSize = kSizeBits - kExponentSizeBits - 1,
    kExponentMaskUnshifted =
        (sizeof(kSize) == 2)
            ? 0xf
            : (sizeof(kSize) == 4) ? 0x7f : (sizeof(kSize) == 8) ? 0x3FF : 0,
    kExponentBias = kExponentMaskUnshifted + kCoefficientSize,
    kExponentMin = -kExponentBias,
  };

  // Constructs an uninitialized floating-point number_.
  TBinary() {}

  inline static UI Coefficient(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  // Converts a Float to a TBinary
  TBinary(Float value) {
    UI ui = *reinterpret_cast<UI*>(&value);

    UI biased_e = TMiddleBits<UI, kMSb - 1, kMantissaSize - 1>(ui);
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

    SI index = (k >> 3) + 1;

    k = -(-((SI)348) + (index << 3));
    // decimal exponent no need lookup table.

    DASSERT(index < 87);

    const UI* f_lut = Pow10IntegralLUT();
    const SI2* e_lut = reinterpret_cast<const SI2*>(BinaryPow10Exponents());
    return TBinary(f_lut[index], e_lut[index]);
  }

  TBinary Minus(const TBinary<Float, SI, UI>& value) const {
    DASSERT(e == value.e);
    DASSERT(f >= value.f);
    return TBinary(f - value.f, e);
  }

  static void PrintDebugInfo() {
    PRINTF(
        "\nkSize:%i kSizeBits:%i kMSbIndex:%i kStrandLengthMax:%i"
        "\nkExponentSizeBits:%i kCoefficientSize:%i kMantissaSize:%i"
        "\nkExponentMaskUnshifted:%i kExponentBias:%i ExponentMin ():%i\n\n",
        kSize, kSizeBits, kMSb, kStrandLengthMax, kExponentSizeBits,
        kCoefficientSize, kMantissaSize, (SI4)kExponentMaskUnshifted,
        (SI4)kExponentBias, (SI4)kExponentMin);
  }

 private:
  UI f;
  SI e;

  static inline void Multiply(TBinary& result, TBinary& a, TBinary& b) {}

  static constexpr SIW LUTCount() {
    // @todo Figure out the LUT sizes for Half and Single precision FP numbers.
    return (sizeof(Float) == 4) ? 83 : (sizeof(Float) == 8) ? 83 : 0;
  }

  static const UI* Pow10IntegralLUT() {
    const void* ptr =
        (sizeof(UI) == 4)
            ? Binary32Pow10IntegralPortions()
            : (sizeof(UI) == 8) ? Binary64Pow10IntegralPortions() : nullptr;
    return reinterpret_cast<const UI*>(ptr);
  }

  static void AlignLUT(CH1* begin, SIW size) {
    DASSERT(size);
    SIW lut_count = LUTCount();
    if (size != ((100 + lut_count) * 2 + lut_count * 8)) return;
    UI2* ui2_ptr = reinterpret_cast<UI2*>(begin);

    for (CH1 tens = '0'; tens <= '9'; ++tens)
      for (SI4 ones = '0'; ones <= '9'; ++ones)
#if ENDIAN == LITTLE
        *ui2_ptr++ = (tens << 8) | ones;
#else
        *ui2_ptr++ = (ones << 8) | tens;
#endif
    const UI2* e_lut = BinaryPow10Exponents();
    for (SI4 i = 0; i < 87; ++i) *ui2_ptr = e_lut[i];

    UI8* ui8_ptr = reinterpret_cast<UI8*>(ui2_ptr);
    const UI* f_lut = Pow10IntegralLUT();
    for (SI4 i = 0; i < 87; ++i) *ui8_ptr = f_lut[i];
  }

  template <typename Char = CH1>
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
    return TBinary(f << (kMSb - index), e - (kMSb - index));
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
    UI l_f = f,   //< Local copy of f.
        l_e = e;  //< Local copy of e.
    TBinary pl = TBinary((l_f << 1) + 1, ((SI)l_e) - 1).NormalizeBoundary();
    SI4 kShiftCount = (kMantissaSize >= 8) ? 0 : kMantissaSize;
    const UI kHiddenBit = ((UI)1) << kShiftCount;
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
    return 0;
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
    return 0;
  }

  /* Prints the integer portion of the floating-point number_.
  @return Nil upon failure or a pointer to the nil-term Char upon success. */
  template <typename Char = CH1>
  static Char* DigitGen(Char* cursor, Char* stop, const TBinary& w,
                        const TBinary& m_plus, UI delta, SI& k) {
    TBinary one(((UI)1) << (-m_plus.e), m_plus.e), wp_w = m_plus.Minus(w);
    UI4 d, pow_10, p_1 = static_cast<UI4>(m_plus.f >> -one.e);
    UI p_2 = m_plus.f & (one.f - 1);
    SI kappa;
    pow_10 = Pow10(p_1, kappa);
    const UI* f_lut = Pow10IntegralLUT();
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
        UI pow_10_f = f_lut[kappa];
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
        UI pow_10_f = f_lut[-kappa];
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
      *nil_term_char = NIL;
      return nil_term_char;
    } else if (0 < kk && kk <= 21) {  // 1234e-2 -> 12.34
      SocketShiftUp(&socket[kk + 1], LastByte(&socket[kk]), length - kk);
      socket[kk] = '.';
      nil_term_char = &socket[length + 1];
      *nil_term_char = NIL;
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

using Binary32 = TBinary<FP4, SI4, UI4>;
using Binary64 = TBinary<FP8, SI4, UI8>;

template <typename Char = CH1>
Char* TPrint(Char* begin, Char* stop, FP4 value) {
  return TBinary<FP4, SI4, UI4>::template Print<Char>(begin, stop, value);
}

template <typename Char = CH1>
Char* TPrint(Char* begin, SIW size, FP4 value) {
  return TPrint<Char>(begin, begin + size - 1, value);
}

template <typename Char = CH1>
Char* TPrint(Char* begin, Char* stop, FP8 value) {
  return TBinary<FP8, SI8, UI8>::template Print<Char>(begin, stop, value);
}

template <typename Char = CH1>
Char* TPrint(Char* begin, SIW size, FP8 value) {
  return TPrint<Char>(begin, begin + size - 1, value);
}

template <typename Char = CH1>
Char* TScan(const Char* start, FP4& result) {
  return nullptr;
}

template <typename Char = CH1>
Char* TScan(const Char* start, FP8& result) {
  return nullptr;
}

#ifndef SCRIPT2
enum {
  NIL = 0,
  kLF = '\n',
};
#endif
}  // namespace _
#endif

#if SEAM >= SCRIPT2_3
#if SEAM == SCRIPT2_3
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

template <typename Printer, typename Char = CH1>
Printer& TPrintChars(Printer& o, const Char* start, const Char* stop) {
  if (!start || start >= stop) return o;

  SIW size = stop - start, extra_row = ((size & 63) != 0) ? 1 : 0,
      row_count = (size >> 6) + extra_row;

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;
  PRINTF("\n\nExpecting start:0x%llx\n", start);
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

/* Prints the given socket to the SOut. */
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

/* Prints the given socket to the SOut.
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
      o << (CHN)c;
    }
    o << '|' << ' ';
    TPrintHex<Printer>(o, address_ptr);
  }
  o << STRSocketBorder();
  return TPrintHex<Printer>(o, address_ptr + size);
}

}  // namespace _
#endif
#endif
