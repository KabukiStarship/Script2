/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_utf.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_STRINGF_TEMPLATES_H
#define SCRIPT2_STRINGF_TEMPLATES_H 1

#include "c_stringf.h"
#include "t_puff.h"

namespace _ {

/* Compares the two strings up to the given delimiter.
@param delimiter Delimiters in Script2 are equal to or less than.
@return 0 if the strings are equal or a non-zero delta upon failure. */
template <typename Char = CHR>
SIN TSTRCompare(const Char* string_a, const Char* string_b,
                Char delimiter = 0) {
  if (!string_a || !string_b) return 0;

  SIN a, b, result;
  if (!string_a) {
    if (!string_b) return 0;
    return SIN(*string_a);
  }
  if (!string_b) return 0 - *string_a;

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
      return result;
    }
    if (a <= (SI4)delimiter) {
      return result;
    }
    ++string_a;
    ++string_b;
    a = *string_a;
    b = *string_b;
  }
  if (a > (SI4)delimiter) {
    return b - a;
  }
  return 0;
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

/* Converts the given hex nibble to lowercase hex. */
inline CH1 HexNibbleToLowerCase(UI1 b) {
  b = b & 0xf;
  if (b > 9) return b + ('a' - 10);
  return b + '0';
}

/* Converts the given character to lowercase if it is uppercase. */
template <typename Char>
inline Char TToLower(Char c) {
  if (c >= 'A' && c <= 'Z') c -= 32;
  return c;
}

inline CH1 ToLower(CH1 value) { return TToLower<CH1>(value); }
inline CH2 ToLower(CH2 value) { return TToLower<CH2>(value); }
inline CH4 ToLower(CH4 value) { return TToLower<CH4>(value); }

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

/* Prints the given string to the Printer. */
template <typename Printer, typename Char = CHR>
Printer& TPrintString(Printer& o, const Char* string) {
  if (!string) return o;
#if LARGEST_CHAR == 1 || SEAM < SEAM_SCRIPT2_UTF
  CH1 c = *string++;
#else
  CH4 c;
  string = Scan(string, c);
  if (!string) return o;
#endif
  while (c) {
    o << c;
#if LARGEST_CHAR == 1 || SEAM < SEAM_SCRIPT2_UTF
    c = *string++;
#else
    string = Scan(string, c);
    if (!string) return o;
#endif
  }
  return o;
}

/* Prints the given string to the Printer and returns the count of characters
printed. */
template <typename Printer, typename Char = CHR>
SIN TPrintAndCount(Printer& o, const Char* string) {
  SIN print_count = 0;
#if LARGEST_CHAR == 1 || SEAM < SEAM_SCRIPT2_UTF
  CH1 c = *string++;
#else
  CHA c;
  string = Scan(string, c);
  if (!string) return -1;
#endif
  while (c) {
#if LARGEST_CHAR == 1 || SEAM < SEAM_SCRIPT2_UTF
    c = *string++;
#else
    string = Scan(string, c);
    if (!string) return -1;
#endif
    o << c;
    ++print_count;
  }
  return print_count;
}

/* Prints the following item to the console in Hex. */
template <typename Printer>
Printer& TPrintHex(Printer& o, const void* item) {
  UIW ptr = reinterpret_cast<UIW>(item);
  return TPrintHex<Printer, UIW>(o, ptr);
}
template <typename Printer, typename SI, typename UI>
Printer& TPrintHex(Printer& o, SI item) {
  return TPrintHex<Printer, UI>(o, UI(item));
}
#if USING_FP4 == YES_0
template <typename Printer>
Printer& TPrintHex(Printer& o, FP4 item) {
  UI4 value = *reinterpret_cast<UI4*>(&item);
  return TPrintHex<Printer, UI4>(o, value);
}
#endif
#if USING_FP8 == YES_0
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
  SIW delta;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
  // We have to print the hex value backwards.
  if (byte_count < 0) {
    byte_count = -byte_count;
    delta = -1;
    cursor += byte_count - 1;
  } else {
    delta = 1;
  }
#endif
  while (--byte_count >= 0) {
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
    UI1 byte = *cursor;
    cursor += delta;
#else
    UI1 byte = *cursor++;
#endif
    o << HexNibbleToUpperCase(byte >> 4) << HexNibbleToUpperCase(byte & 0xf);
  }
  return o;
}

template <typename Printer>
Printer& TPrintHex(Printer& o, const void* start, const void* stop) {
  SIW delta = reinterpret_cast<SIW>(stop) - reinterpret_cast<SIW>(start);
  return TPrintHex<Printer>(o, start, delta);
}

/* Prints the memory beginning at start to the Printer. */
template <typename Printer>
Printer& TPrintBinary(Printer& o, const void* start, SIW byte_count) {
  if (!start) return o;
  const UI1* cursor = reinterpret_cast<const UI1*>(start);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
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
inline Printer& TPrintBinary(Printer& o, const void* start, const void* stop) {
  SIW delta = reinterpret_cast<SIW>(stop) - reinterpret_cast<SIW>(start);
  return TPrintBinary<Printer>(o, start, reinterpret_cast<const void*>(delta));
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
#if USING_FP4 == YES_0
template <typename Printer>
Printer& TPrintBinary(Printer& o, FP4 item) {
  UI4 value = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<Printer, UI4>(o, value);
}
#endif
#if USING_FP4 == YES_0
template <typename Printer>
Printer& TPrintBinary(Printer& o, FP8 item) {
  UI8 value = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<Printer, UI8>(o, value);
}
#endif

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR>
inline const Char* TSTREnd(const Char* start, CH1 delimiter = 0) {
  while (*start++ != delimiter)
    ;
  return start - 1;
}

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR>
inline Char* TSTREnd(Char* start, Char delimiter = 0) {
  return const_cast<Char*>(
      TSTREnd<Char>(reinterpret_cast<const Char*>(start), delimiter));
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR, typename SIZ = SIN>
SIZ TSTRLength(const Char* start) {
  D_ASSERT(start);
  return (SIZ)(TSTREnd<Char>(start) - start);
}

/* Gets the length of the given CH1.
@return  Returns -1 if the text CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
template <typename Char = CHR, typename SIZ = SIN>
inline SIZ TSTRLength(Char* start) {
  return TSTRLength<Char>(reinterpret_cast<const Char*>(start));
}

/* Prints the given token aligned center the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Printer, typename Char = CHR>
Printer& TPrintCenter(Printer& o, const Char* item, SIW column_count = 80) {
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
    while (--length > 0) o << '.';
  } else {
    while (length > 0) o << *item++;
    o << "...";
  }
  return o;
}

template <typename Printer>
Printer& TPrintAligned(Printer& o, const CH1* string, SIW char_count,
                       SIW left_count, SIW dot_count, SIW right_count) {
  while (--left_count > 0) o << ' ';
  while (--char_count > 0) {
#if LARGEST_CHAR == 1 || SEAM < SEAM_SCRIPT2_UTF
    o << *string++;
#else
    CHA c;
    string = Scan(string, c);
    if (!string) return o;
    o << c;
#endif
  }
  while (--dot_count > 0) o << ' ';
  while (--right_count > 0) o << ' ';
  return o;
}

template <typename Printer>
Printer& TPrintAlignedHex(Printer& o, const CH1* begin, SIW byte_count,
                          SIW left_count, SIW dot_count, SIW right_count) {
  while (--left_count > 0) o << ' ';
  TPrintHex<Printer>(o, begin, byte_count);
  while (--dot_count > 0) o << ' ';
  while (--right_count > 0) o << ' ';
  return o;
}

/* Prints th given Stringf centered unless it's count is less then 0, in which
case it will print the POD value stored in the first Word of the String. */
template <typename Printer>
Printer& TPrintCenter(Printer& o, Stringf& item) {
  SIW column_count = item.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    SIW type_width = TypeSizeOf(item.Type()), left_count, dot_count,
        right_count;
    if (type_width < 0) return o;
    if (type_width > column_count) {
      left_count = 0;
      right_count = 0;
      if (column_count < 3) {
        type_width = 0;
        dot_count = column_count;
      } else {
        type_width = column_count - 3;
        dot_count = 3;
      }
    } else {
      left_count = (column_count - type_width) >> 1;
      dot_count = 0;
      right_count = column_count - left_count;
    }
    return TPrintAlignedHex<Printer>(o, item.ST1(), type_width, left_count,
                                     dot_count, right_count);
  }
  SIW utf_format = _::TypeTextFormat(item.Type());
  switch (utf_format) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintCenter<Printer, CH1>(o, item.ST1(), column_count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintCenter<_::COut, CH2>(o, item.ST2(), column_count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintCenter<Printer, CH4>(o, item.ST3(), column_count);
    }
#endif
  }
  return o;
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Printer, typename Char = CHR>
Printer& TPrintRight(Printer& o, const Char* item, SIW column_count = 80) {
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
        o << "..";
      case 3:
        o << "...";
    }
  } else {
    while (length > 0) o << *item++;
    o << "...";
  }
  return o;
}

/* Prints th given Stringf centered, printing it as hex if the item.Count() is
less than 0. */
template <typename Printer>
Printer& TPrintRight(Printer& o, Stringf& item) {
  SIW column_count = item.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    SIW char_count = TypeSizeOf(item.Type());
    if (char_count < 0) return o;

    SIW left_count, dot_count;
    if (char_count > column_count) {
      left_count = 0;
      if (column_count < 3) {
        char_count = 0;
        dot_count = column_count;
      } else {
        char_count = column_count - 3;
        dot_count = 3;
      }
    } else {
      left_count = column_count - char_count;
      dot_count = 0;
    }
    return TPrintAlignedHex<Printer>(o, item.ST1(), char_count, left_count,
                                     dot_count, 0);
  }
  SIW count = item.Count();
  switch (_::TypeTextFormat(item.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintRight<Printer, CH1>(o, item.ST1(), count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintRight<Printer, CH2>(o, item.ST2(), count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintRight<Printer, CH4>(o, item.ST3(), count);
    }
#endif
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
template <typename Char = CHR>
inline BOL TIsWhitespace(Char character) {
  return character <= ' ';
}

template <typename Printer, typename Char>
Printer& TPrintRepeat(Printer& o, Char c, SIW count) {
  while (--count >= 0) o << c;
  return o;
}

template <typename Char = CHR>
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
template <typename Printer, typename Char = CHR>
const Char* TPrintLinef(Printer& o, const Char* style = nullptr,
                        SIW column_count = 80) {
  enum {
    kStateScanningDifferentChars = 0,
    kStateStateDuplicateChar = 1,
    kBreakCount = 3,
  };
  if (!style) style = TSTRLinef<Char>();
  if (column_count < kBreakCount) return nullptr;

  SIW state = kStateScanningDifferentChars;
  Char current_char = *style++,  //
      prev_char = ~current_char;
  SI4 hit_count = 0, column_index = 0;
  while (current_char) {
    o << current_char;
    if (current_char == '\n')
      column_index = 0;
    else
      ++column_index;
    switch (state) {
      case kStateScanningDifferentChars: {
        if (current_char == prev_char && !TIsWhitespace<Char>(current_char)) {
          state = kStateStateDuplicateChar;
          hit_count = 1;
        }
        break;
      }
      case kStateStateDuplicateChar: {
        if (current_char != prev_char)
          state = kStateScanningDifferentChars;
        else if (++hit_count >= kBreakCount - 1) {
          TPrintRepeat<Printer, Char>(o, current_char,
                                      column_count - column_index);
          column_index = hit_count = 0;
        }
        break;
      }
    }
    prev_char = current_char;
    current_char = *style++;
  }
  return style;
}

template <typename Printer, typename Char = CHR>
Printer& TPrintLine(Printer& o, Char token = '-', SIW column_count = 80) {
  o << '\n';
  TPrintRepeat<Printer, Char>(o, token, column_count);
  return o << '\n';
}

template <typename Printer>
Printer& TPrintLinef(Printer& o, Linef& item) {
  SIW type = item.element.value.Type(),  //
      utf_format = _::TypeTextFormat(type);
  switch (utf_format) {
#if USING_UTF8 == YES_0
    case kST1: {
      _::TPrintLinef<Printer, CH1>(o, item.element.ST1(), item.element.count);
      break;
    }
#endif
#if USING_UTF16 == YES_0
    case kST2: {
      _::TPrintLinef<Printer, CH2>(o, item.element.ST2(), item.element.count);
      break;
    }
#endif
#if USING_UTF32 == YES_0
    case kST3: {
      const CH4* start = reinterpret_cast<const CH4*>(item.element.value.Ptr());
      _::TPrintLinef<Printer, CH4>(o, item.element.ST3(), item.element.count);
      break;
    }
#endif
    case -1: {
      switch (type & kTypePODMask) {
#if USING_UTF8 == YES_0
        case kCH1: {
          CH1 c = (CH1)item.element.value.Word();
          _::TPrintLine<Printer, CH1>(o, c, item.element.count);
          break;
        }
#endif
#if USING_UTF16 == YES_0
        case kCH2: {
          CH2 c = (CH2)item.element.value.Word();
          _::TPrintLine<Printer, CH2>(o, c, item.element.count);
          break;
        }
#endif
#if USING_UTF32 == YES_0
        case kCH4: {
          CH4 c = (CH4)item.element.value.Word();
          _::TPrintLine<Printer, CH4>(o, c, item.element.count);
          break;
        }
#endif
      }
    }
  }
  return o;
}

template <typename Char = CHR>
const Char* TSTRHeadingf() {
  static const Char kStrand[] = {kLF, kLF, '+', '-', '-', '-', kLF, '|', ' ',
                                 NIL, kLF, '+', '-', '-', '-', kLF, NIL};
  return kStrand;
}

/* Prints a heading with the */
template <typename Printer, typename Char>
Printer& TPrintHeadingf(Printer& o, const Char* element,
                        const CH1* style = nullptr, SIW column_count = 80,
                        const CH1* caption2 = nullptr,
                        const CH1* caption3 = nullptr) {
  if (!style) style = TSTRHeadingf<CH1>();
  style = TPrintLinef<Printer, CH1>(o, style, column_count);
  if (!style) return o;
  o << element;
  if (caption2) o << caption2;
  if (caption3) o << caption3;
  TPrintLinef<Printer, CH1>(o, style, column_count);
  return o;
}

/* Prints the given  */
template <typename Printer>
Printer& TPrintHeadingf(Printer& o, Headingf& item) {
  switch (_::TypeTextFormat(item.element.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintHeadingf<Printer, CH1>(o, item.element.ST1(), item.style,
                                             item.element.Count(),
                                             item.caption2, item.caption3);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintHeadingf<Printer, CH2>(o, item.element.ST2(), item.style,
                                             item.element.Count(),
                                             item.caption2, item.caption3);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintHeadingf<Printer, CH4>(o, item.element.ST3(), item.style,
                                             item.element.Count(),
                                             item.caption2, item.caption3);
    }
#endif
  }
  return o;
}

template <typename Printer, typename Char = CHR>
Printer& TPrintChars(Printer& o, const Char* start, const Char* stop) {
  if (!start || start >= stop) return o;

  SIW size_bytes = stop - start + 1;

  o << STRPrintCharsHeader() << STRPrintCharsBorder() << Hexf(start);
  int i = 0;
  Char c;
  const Char* address_to_print = start;
  while (start <= stop) {
    o << '\n' << '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *start;
      if (start++ > stop) {
        c = 'x';
      } else if (c < ' ') {
        address_to_print = start;
        c += kPrintC0Offset;
      }
      o << c;
    }
    o << "| " << Hexf(address_to_print - 1);
  }
  return o << STRPrintCharsBorder() << "Chars printed:" << size_bytes;
}

template <typename Printer, typename Char = CHR>
inline Printer& TPrintChars(Printer& o, const Char* start, SIW count) {
  return TPrintChars<Printer, Char>(o, start, start + count - 1);
}

template <typename Printer>
Printer& TPrintChars(Printer& o, Charsf& item) {
  Valuef& element = item.element;
  SIW count = element.Count();
  switch (_::TypeTextFormat(element.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintChars<Printer, CH1>(o, element.ST1(), count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintChars<Printer, CH2>(o, element.ST2(), count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintChars<Printer, CH4>(o, element.ST3(), count);
    }
#endif
  }
  return _::TPrintChars<Printer, CH1>(
      o, reinterpret_cast<CH1*>(element.Value()), count);
}

template <typename Char>
Char* TScanChar(Char* cursor, Char& c) {}

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
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char = CHR>
const Char* TScanSigned(const Char* start, SI& result) {
  if (!start) return nullptr;
  SI sign;
  const Char* cursor = start;
  Char c = *cursor++;
  if (c == '-') {
    c = *start++;
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

  while (cursor >= start) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (((UI)c) - '0');
    if (new_value < value) return nullptr;
    value = new_value;
  }
  result = sign * value;
  return stop;
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char = CHR>
Char* TScanSigned(Char* start, SI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TScanSigned<SI, UI, Char>(ptr, result));
}

/* Scans the given socket for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The SI to write the scanned SI. */
template <typename Char = CHR>
const Char* TScan(const Char* start, SI1& result) {
  return TScanSigned<SI1, UI1, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, SI1& result) {
  return TScanSigned<SI1, UI1, Char>(start, result);
}
template <typename Char = CHR>
const Char* TScan(const Char* start, SI2& result) {
  return TScanSigned<SI2, UI2, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, SI2& result) {
  return TScanSigned<SI2, UI2, Char>(start, result);
}
template <typename Char = CHR>
const Char* TScan(const Char* start, SI4& result) {
  return TScanSigned<SI4, UI4, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, SI4& result) {
  return TScanSigned<SI4, UI4, Char>(start, result);
}
template <typename Char = CHR>
const Char* TScan(const Char* start, SI8& result) {
  return TScanSigned<SI8, UI8, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, SI8& result) {
  return TScanSigned<SI8, UI8, Char>(start, result);
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CHR>
const Char* TScanUnsigned(const Char* start, UI& result) {
  if (!start) return nullptr;
  const Char* cursor = start;
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

  while (cursor >= start) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (((UI)c) - '0');
    if (new_value < value) return nullptr;
    value = new_value;
  }
  result = value;
  return stop;
}

/* Scans the given socket for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = CHR>
Char* TScanUnsigned(Char* start, UI& result) {
  const Char* ptr = reinterpret_cast<const Char*>(start);
  return const_cast<Char*>(TScanUnsigned<UI, Char>(ptr, result));
}

/* Scans the given socket for a UI1
@return Nil if there is no UI to scan.
@param socket The beginning of the socket.
@param result The UI to write the scanned UI. */
template <typename Char = CHR>
const Char* TScan(const Char* start, UI1& result) {
  return TScanUnsigned<UI1, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, UI1& result) {
  return TScanUnsigned<UI1, Char>(start, result);
}
template <typename Char = CHR>
const Char* TScan(const Char* start, UI2& result) {
  return TScanUnsigned<UI2, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, UI2& result) {
  return TScanUnsigned<UI2, Char>(start, result);
}
template <typename Char = CHR>
const Char* TScan(const Char* start, UI4& result) {
  return TScanUnsigned<UI4, Char>(start, result);
}
template <typename Char = CHR>
Char* TScan(Char* start, UI4& result) {
  return TScanUnsigned<UI4, Char>(start, result);
}
template <typename Char = CHR>
const Char* TScan(const Char* start, UI8& result) {
  return TScanUnsigned<UI8, Char>(start, result);
}
template <typename Char = CHR>
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
template <typename Char = CHR>
Char* TPrint(Char* start, Char* stop, CH1 item) {
  if (!start || start >= stop) return nullptr;
  *start++ = item;
  *start = 0;
  return start;
}
/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CHR>
Char* TPrint(Char* start, SIW count, CH1 item) {
  return Print(start, start + count - 1, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count  The element count.
@param   item   The string to print. */
template <typename Char = CHR>
Char* TPrint(Char* start, SIW count, CH2 item) {
  return TPrint<Char>(start, start + count - 1, item);
}

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start The beginning of the socket.
@param   count The element count.
@param   item  The string to print. */
template <typename Char = CHR>
Char* TPrint(Char* start, SIW count, CH4 item) {
  return TPrint<Char>(start, start + count - 1, item);
}

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   start  The beginning of the socket.
 @param   stop   The last Char in the socket.
 @param   item   The item to print. */
template <typename Char = CHR>
Char* TPrintString(Char* start, Char* stop, const CH1* item) {
  if (!start || start >= stop || !item) return nullptr;

  if (start >= stop) return nullptr;

  CH1 c = *item++;
  while (c) {
    *start++ = c;
    if (start >= stop) return nullptr;
    c = *item++;
  }
  *start = 0;
  return start;
}

template <typename Char = CHR>
inline Char* TPrint(Char* start, Char* stop, const CH1* item) {
  return TPrintString<Char>(start, stop, item);
}

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   start  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename Char = CHR>
Char* TPrintString(Char* start, Char* stop, const CH2* item) {
  if (!start || start >= stop || !item) return nullptr;

  CH2 c = *item++;
  while (c) {
    start = Print(start, stop, c);
    if (!start) return nullptr;
    c = *item++;
  }
  if (start) *start = 0;
  return start;
}

template <typename Char = CHR>
inline Char* TPrint(Char* start, Char* stop, const CH2* item) {
  return TPrintString<Char>(start, stop, item);
}

/* Prints a Unicode item to the given socket.
 @return  Nil upon failure or a pointer to the nil-term Char upon success.
 @param   start  The beginning of the socket.
 @param   stop    The last Char in the socket.
 @param   item    The item to print.
 @warning This algorithm is designed to fail if the socket is not a valid socket
 with one or more bytes in it, or if item is nil. */
template <typename Char = CHR>
Char* TPrintString(Char* start, Char* stop, const CH4* item) {
  if (!start || start >= stop || !item) return nullptr;

  CH4 c = *item++;
  while (c) {
    start = Print(start, stop, c);
    if (!start || start >= stop) return nullptr;
    c = *item++;
  }
  *start = 0;
  return start;
}

template <typename Char = CHR>
inline Char* TPrint(Char* start, Char* stop, const CH4* item) {
  return TPrintString<Char>(start, stop, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
inline Char* TPrint(Char* start, SIW size, const CH1* item) {
  return TPrintString<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
Char* TPrint(Char* start, SIW size, const CH2* item) {
  return TPrintString<Char>(start, start + size - 1, item);
}

/* Prints a Unicode string to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   start    The beginning of the socket.
@param   size      The size of the socket in Char(s).
@param   item      The string to print.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it, or if string is nil. */
template <typename Char = CHR>
Char* TPrint(Char* start, SIW size, const CH4* item) {
  return TPrintString<Char>(start, start + size - 1, item);
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

/* Skips the given Char in a s if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
inline Char* TSTRSkipChar(Char* cursor, Char skip_char) {
  return const_cast<const Char*>(
      TSTRSkipChar<Char>(reinterpret_cast<const Char*>(cursor), skip_char));
}

}  // namespace _

#endif
