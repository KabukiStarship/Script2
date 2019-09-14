/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /uniprinter.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_UNIPRINTER_CODE_HEADER
#define SCRIPT2_UNIPRINTER_CODE_HEADER 1

#include "stringf.h"
#include "typevalue.hpp"

namespace _ {

/* Prints the given string to the Printer. */
template <typename Printer, typename Char = CHR>
Printer& TSPrintString(Printer& o, const Char* string) {
  if (!string) return o;
  CHA c;
  string = SScan(string, c);
  while (c) {
    o << c;
    string = SScan(string, c);
  }
  return o;
}

/* Prints the given string to the Printer and returns the count of characters
printed. */
template <typename Printer, typename Char = CHR>
SIN TPrintAndCount(Printer& o, const Char* string) {
  if (!string) return 0;
  SIN print_count = 0;
  CHA c;
  string = SScan(string, c);
  while (c) {
    o << c;
    ++print_count;
    string = SScan(string, c);
  }
  return print_count;
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
Printer& TPrintHex(Printer& o, const void* origin, SIW byte_count) {
  if (!origin) return o;
  SIW delta;
  const UI1* cursor = reinterpret_cast<const UI1*>(origin);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
  // We have to print the hex value backwards.
  if (byte_count < 0) {
    byte_count = -byte_count;
    delta = -1;
    cursor += byte_count - 1;
  } else {
    delta = 1;
  }
#else
  if (byte_count < 0) byte_count = -byte_count;
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

template <typename Printer>
Printer& TPrintAligned(Printer& o, const CH1* string, SIW char_count,
                       SIW left_count, SIW dot_count, SIW right_count) {
  while (--left_count > 0) o << ' ';
  while (--char_count > 0) {
#if LARGEST_CHAR == 1 || SEAM < SCRIPT2_UNIPRINTER
    o << *string++;
#else
    CHA c;
    string = SScan(string, c);
    if (!string) return o;
    o << c;
#endif
  }
  while (--dot_count > 0) o << ' ';
  while (--right_count > 0) o << ' ';
  return o;
}

/* Prints the given token aligned center the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param token  The token to utf.
@param column_count The number_ of columns to align right to. */
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
Printer& TPrintAlignedHex(Printer& o, const void* origin, SIW byte_count,
                          SIW left_count, SIW dot_count, SIW right_count) {
  const CH1* cursor = reinterpret_cast<const CH1*>(origin);
  while (--left_count > 0) o << ' ';
  // TPrintHex<Printer>(o, origin, byte_count >> 1);
  TPrintHex<Printer>(o, cursor, -byte_count);
  while (--dot_count > 0) o << ' ';
  while (--right_count > 0) o << ' ';
  return o;
}

/* Prints th given Stringf centered unless it's count is less then 0, in which
case it will print the POD value stored in the first Word of the string. */
template <typename Printer>
Printer& TPrintCenter(Printer& o, Stringf& item) {
  SIW column_count = item.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    SIW byte_count = TypeSizeOf(item.Type()), left_count, dot_count;
    if (byte_count < 0) return o;
    byte_count = byte_count << 1;
    SIW right_count;
    if (byte_count > column_count) {
      while (--column_count > 0) o << ' ';
      return o;
    } else {
      left_count = (column_count - byte_count) >> 1;
      dot_count = 0;
      right_count = column_count - left_count - byte_count;
    }
    /*
    D_COUT(
        "\nTPrintAlignedHex:"
        "\n    column_count:" << column_count <<
        "\n      byte_count:" << byte_count <<
        "\n      left_count:" << left_count <<
        "\n       dot_count:" << dot_count <<
        "\n     right_count:" << right_count);*/
    return TPrintAlignedHex<Printer>(o, item.Value(), byte_count >> 1,
                                     left_count, dot_count, right_count);
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
@param token  The token to utf.
@param column_count The number_ of columns to align right to. */
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

template <typename Printer, typename Char>
Printer& TPrintRepeat(Printer& o, Char c, SIW count) {
  while (--count >= 0) o << c;
  return o;
}

template <typename Char = CHR>
const Char* TSTRLinef() {
  static const Char kString[] = {'\n', '\n', '-', '-', '-', '\n', NIL};
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
      _::TPrintLinef<Printer, CH1>(o, item.element.ToST1(), item.element.count);
      break;
    }
#endif
#if USING_UTF16 == YES_0
    case kST2: {
      _::TPrintLinef<Printer, CH2>(o, item.element.ToST2(), item.element.count);
      break;
    }
#endif
#if USING_UTF32 == YES_0
    case kST3: {
      const CH4* start =
          reinterpret_cast<const CH4*>(item.element.value.ToPTR());
      _::TPrintLinef<Printer, CH4>(o, item.element.ToST3(), item.element.count);
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
  static const Char kStrand[] = {'\n', '\n', '+', '-', '-', '-', '\n', '|', ' ',
                                 NIL,  '\n', '+', '-', '-', '-', '\n', NIL};
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
      return _::TPrintChars<Printer, CH1>(o, element.ToST1(), count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintChars<Printer, CH2>(o, element.ToST2(), count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintChars<Printer, CH4>(o, element.ToST3(), count);
    }
#endif
  }
  return _::TPrintChars<Printer, CH1>(
      o, reinterpret_cast<CH1*>(element.Value()), count);
}

template <typename Printer, typename DT = DT2>
Printer& TPrintTypeNamePOD(Printer& o, DT type) {
  DT pod_type = type & kTypePODMask,        //
      vector_type = TTypeVector<DT>(type),  //
      map_type = TTypeMap<DT>(type);        //
}

template <typename Printer, typename DT = DT2>
Printer& TPrintTypeName(Printer& o, DT type) {
  DT pod_type = type & kTypePODMask;
  if (pod_type == 0) return o << "BGN" << (type >> kTypePODBitCount);
  DT vector_type = TTypeVector<DT>(type);
  if (vector_type) {
    return o << TypeSTR(vector_type) << '_' << TypeSTR(pod_type);
  }
  DT map_type = TTypeMap<DT>(type);
  if (map_type) {
    return o << TypeSTR(map_type) << '_' << TypeSTR(pod_type);
  }
  return o;
}

template <typename Printer, typename DT = DT2>
Printer& TPrintValue(Printer& o, DT type, void* item) {}

}  // namespace _

#endif
