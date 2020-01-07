/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /uniprinter.hpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#ifndef SCRIPT2_UNIPRINTER_CODE
#define SCRIPT2_UNIPRINTER_CODE 1

#include "stringf.h"
#include "typevalue.hpp"

namespace _ {

/* Prints the given string to the Printer. */
template <typename Printer, typename CHT = CHR>
Printer& TSPrintString(Printer& o, const CHT* string) {
  if (!string) return o;
  CHL c;
  string = SScan(string, c);
  while (c) {
    o << c;
    string = SScan(string, c);
  }
  return o;
}

/* Prints the given string to the Printer and returns the count of characters
printed. */
template <typename Printer, typename CHT = CHR>
ISN TPrintAndCount(Printer& o, const CHT* string) {
  if (!string) return 0;
  ISN print_count = 0;
  CHL c;
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
  enum { cHexStrandLengthSizeMax = sizeof(UI) * 2 + 3 };
  auto ui = ToUnsigned(item);
  for (ISC num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    o << HexNibbleToUpperCase((IUA)(ui >> num_bits_shift));
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
#if USING_FPC == YES_0
template <typename Printer>
Printer& TPrintHex(Printer& o, FPC item) {
  IUC value = *reinterpret_cast<IUC*>(&item);
  return TPrintHex<Printer, IUC>(o, value);
}
#endif
#if USING_FPD == YES_0
template <typename Printer>
Printer& TPrintHex(Printer& o, FPD item) {
  IUD value = *reinterpret_cast<IUD*>(&item);
  return TPrintHex<Printer, IUD>(o, value);
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
Printer& TPrintHex(Printer& o, const void* origin, ISW byte_count) {
  if (!origin) return o;
  ISW delta;
  const IUA* cursor = reinterpret_cast<const IUA*>(origin);
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
    IUA byte = *cursor;
    cursor += delta;
#else
    IUA byte = *cursor++;
#endif
    o << HexNibbleToUpperCase(byte >> 4) << HexNibbleToUpperCase(byte & 0xf);
  }
  return o;
}

template <typename Printer>
Printer& TPrintHex(Printer& o, const void* start, const void* stop) {
  ISW delta = reinterpret_cast<ISW>(stop) - reinterpret_cast<ISW>(start);
  return TPrintHex<Printer>(o, start, delta);
}

/* Prints the memory beginning at start to the Printer. */
template <typename Printer>
Printer& TPrintBinary(Printer& o, const void* start, ISW byte_count) {
  if (!start) return o;
  const IUA* cursor = reinterpret_cast<const IUA*>(start);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
  ISA delta;
  if (byte_count < 0) {
    delta = -1;
    byte_count = -byte_count;
    cursor += byte_count - 1;
  } else {
    delta = 1;
  }
#endif
  while (--byte_count >= 0) {
    IUA c = *cursor;
    cursor += delta;
    for (ISW i = 8; i > 0; --i) {
      o << CHA('0' + (c >> 7));
      c = c << 1;
    }
  }
  return o;
}

template <typename Printer>
inline Printer& TPrintBinary(Printer& o, const void* start, const void* stop) {
  ISW delta = reinterpret_cast<ISW>(stop) - reinterpret_cast<ISW>(start);
  return TPrintBinary<Printer>(o, start, reinterpret_cast<const void*>(delta));
}

template <typename Printer, typename UI>
Printer& TPrintBinary(Printer& o, UI item) {
  enum { cSize = sizeof(UI) * 8 };
  auto ui = ToUnsigned(item);
  for (ISC i = cSize; i > 0; --i) {
    CHA c = CHA('0' + (ui >> (cSize - 1)));
    o << c;
    ui = ui << 1;
  }
  return o;
}

template <typename Printer, typename SI, typename UI>
Printer& TPrintBinary(Printer& o, SI item) {
  return TPrintBinary<Printer, UI>(o, (UI)item);
}
#if USING_FPC == YES_0
template <typename Printer>
Printer& TPrintBinary(Printer& o, FPC item) {
  IUC value = *reinterpret_cast<IUC*>(&item);
  return TPrintBinary<Printer, IUC>(o, value);
}
#endif
#if USING_FPC == YES_0
template <typename Printer>
Printer& TPrintBinary(Printer& o, FPD item) {
  IUD value = *reinterpret_cast<IUD*>(&item);
  return TPrintBinary<Printer, IUD>(o, value);
}
#endif

template <typename Printer>
Printer& TPrintAligned(Printer& o, const CHA* string, ISW char_count,
                       ISW left_count, ISW dot_count, ISW right_count) {
  while (--left_count > 0) o << ' ';
  while (--char_count > 0) {
#if LARGEST_CHAR == 1 || SEAM < SCRIPT2_UNIPRINTER
    o << *string++;
#else
    CHL c;
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
pointer to the nil-term CHA upon success.
@param token  The token to utf.
@param column_count The number_ of columns to align right to. */
template <typename Printer, typename CHT = CHR>
Printer& TPrintCenter(Printer& o, const CHT* item, ISW column_count = 80) {
  if (!item || column_count < 1) return o;

  const CHT* token_end = TSTREnd<CHT>(item);
  if (item == token_end) return o;
  ISW length = token_end - item, space_count = column_count - length;

  if (space_count > 0) {
    ISW half_count = space_count >> 1;
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
Printer& TPrintAlignedHex(Printer& o, const void* origin, ISW byte_count,
                          ISW left_count, ISW dot_count, ISW right_count) {
  const CHA* cursor = reinterpret_cast<const CHA*>(origin);
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
  ISW column_count = item.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    ISW byte_count = TypeSizeOf(item.Type()), left_count, dot_count;
    if (byte_count < 0) return o;
    byte_count = byte_count << 1;
    ISW right_count;
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
  ISW utf_format = _::TypeTextFormat(item.Type());
  switch (utf_format) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintCenter<Printer, CHA>(o, item.STA(), column_count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintCenter<_::COut, CHB>(o, item.STB(), column_count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintCenter<Printer, CHC>(o, item.STC(), column_count);
    }
#endif
  }
  return o;
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CHA upon success.
@param token  The token to utf.
@param column_count The number_ of columns to align right to. */
template <typename Printer, typename CHT = CHR>
Printer& TPrintRight(Printer& o, const CHT* item, ISW column_count = 80) {
  if (!item || column_count < 1) return o;

  const CHT* token_end = TSTREnd<CHT>(item);
  if (item == token_end) return o;
  ISW length = token_end - item, space_count = column_count - length;

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
  ISW column_count = item.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    ISW char_count = TypeSizeOf(item.Type());
    if (char_count < 0) return o;

    ISW left_count, dot_count;
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
    return TPrintAlignedHex<Printer>(o, item.STA(), char_count, left_count,
                                     dot_count, 0);
  }
  ISW count = item.Count();
  switch (_::TypeTextFormat(item.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintRight<Printer, CHA>(o, item.STA(), count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintRight<Printer, CHB>(o, item.STB(), count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintRight<Printer, CHC>(o, item.STC(), count);
    }
#endif
  }
  return o;
}

template <typename Printer>
Printer& TPrintIndent(Printer& o, ISW indent_count) {
  o << '\n';
  while (--indent_count >= 0) o << ' ';
  return o;
}

template <typename Printer, typename CHT>
Printer& TPrintRepeat(Printer& o, CHT c, ISW count) {
  while (--count >= 0) o << c;
  return o;
}

template <typename CHT = CHR>
const CHT* TSTRLinef() {
  static const CHT kString[] = {'\n', '\n', '-', '-', '-', '\n', NIL};
  return kString;
}

/* Prints a formatted lines.

The first two chars of the string are going to be the corner and margin chars.
It's easiest to show with the examples below. Like their names implies, the
corner char is for the edges and the margin is for inside of a header block.

@code
TPrintBreak<CHA> ("\n+---\n\n| Foo\n\n+---\n", 10);

TPrintBreak<CHA> ("\n+---\n\n| Foo\n\n+---\n", 10);
//>>>
//>>> +----------
//>>> | Foo *****
//>>> +----------
//>>>

TPrintBreak<CHA> ("- \n---\n---\n\n   Foo\n\n---\n---", 10);
//>>> -----------
//>>> -----------
//>>>
//>>>    Foo
//>>>
//>>> -----------
//>>> -----------
@endcode
*/
template <typename Printer, typename CHT = CHR>
const CHT* TPrintLinef(Printer& o, const CHT* style = nullptr,
                       ISW column_count = 80) {
  enum {
    cStateScanningDifferentChars = 0,
    cStateStateDuplicateChar = 1,
    cBreakCount = 3,
  };
  if (!style) style = TSTRLinef<CHT>();
  if (column_count < cBreakCount) return nullptr;

  ISW state = cStateScanningDifferentChars;
  CHT current_char = *style++,  //
      prev_char = ~current_char;
  ISC hit_count = 0, column_index = 0;
  while (current_char) {
    o << current_char;
    if (current_char == '\n')
      column_index = 0;
    else
      ++column_index;
    switch (state) {
      case cStateScanningDifferentChars: {
        if (current_char == prev_char && !TIsWhitespace<CHT>(current_char)) {
          state = cStateStateDuplicateChar;
          hit_count = 1;
        }
        break;
      }
      case cStateStateDuplicateChar: {
        if (current_char != prev_char)
          state = cStateScanningDifferentChars;
        else if (++hit_count >= cBreakCount - 1) {
          TPrintRepeat<Printer, CHT>(o, current_char,
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

template <typename Printer, typename CHT = CHR>
Printer& TPrintLine(Printer& o, CHT token = '-', ISW column_count = 80) {
  o << '\n';
  TPrintRepeat<Printer, CHT>(o, token, column_count);
  return o << '\n';
}

template <typename Printer>
Printer& TPrintLinef(Printer& o, Linef& item) {
  ISW type = item.element.value.Type(),  //
      utf_format = _::TypeTextFormat(type);
  switch (utf_format) {
#if USING_UTF8 == YES_0
    case cSTA: {
      _::TPrintLinef<Printer, CHA>(o, item.element.ToSTA(), item.element.count);
      break;
    }
#endif
#if USING_UTF16 == YES_0
    case cSTB: {
      _::TPrintLinef<Printer, CHB>(o, item.element.ToSTB(), item.element.count);
      break;
    }
#endif
#if USING_UTF32 == YES_0
    case cSTC: {
      const CHC* start =
          reinterpret_cast<const CHC*>(item.element.value.ToPTR());
      _::TPrintLinef<Printer, CHC>(o, item.element.ToSTC(), item.element.count);
      break;
    }
#endif
    case -1: {
      switch (type & cTypePODMask) {
#if USING_UTF8 == YES_0
        case cCHA: {
          CHA c = (CHA)item.element.value.Word();
          _::TPrintLine<Printer, CHA>(o, c, item.element.count);
          break;
        }
#endif
#if USING_UTF16 == YES_0
        case cCHB: {
          CHB c = (CHB)item.element.value.Word();
          _::TPrintLine<Printer, CHB>(o, c, item.element.count);
          break;
        }
#endif
#if USING_UTF32 == YES_0
        case cCHC: {
          CHC c = (CHC)item.element.value.Word();
          _::TPrintLine<Printer, CHC>(o, c, item.element.count);
          break;
        }
#endif
      }
    }
  }
  return o;
}

template <typename CHT = CHR>
const CHT* TSTRHeadingf() {
  static const CHT kStrand[] = {'\n', '\n', '+', '-', '-', '-', '\n', '|', ' ',
                                NIL,  '\n', '+', '-', '-', '-', '\n', NIL};
  return kStrand;
}

/* Prints a heading with the */
template <typename Printer, typename CHT>
Printer& TPrintHeadingf(Printer& o, const CHT* element,
                        const CHA* style = nullptr, ISW column_count = 80,
                        const CHA* caption2 = nullptr,
                        const CHA* caption3 = nullptr) {
  if (!style) style = TSTRHeadingf<CHA>();
  style = TPrintLinef<Printer, CHA>(o, style, column_count);
  if (!style) return o;
  o << element;
  if (caption2) o << caption2;
  if (caption3) o << caption3;
  TPrintLinef<Printer, CHA>(o, style, column_count);
  return o;
}

/* Prints the given  */
template <typename Printer>
Printer& TPrintHeadingf(Printer& o, Headingf& item) {
  switch (_::TypeTextFormat(item.element.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintHeadingf<Printer, CHA>(o, item.element.STA(), item.style,
                                             item.element.Count(),
                                             item.caption2, item.caption3);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintHeadingf<Printer, CHB>(o, item.element.STB(), item.style,
                                             item.element.Count(),
                                             item.caption2, item.caption3);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintHeadingf<Printer, CHC>(o, item.element.STC(), item.style,
                                             item.element.Count(),
                                             item.caption2, item.caption3);
    }
#endif
  }
  return o;
}

template <typename Printer, typename CHT = CHR>
Printer& TPrintChars(Printer& o, const CHT* start, const CHT* stop) {
  if (!start || start >= stop) return o;

  ISW size_bytes = stop - start + 1;

  o << STRPrintCharsHeader() << STRPrintCharsBorder() << Hexf(start);
  int i = 0;
  CHT c;
  const CHT* address_to_print = start;
  while (start <= stop) {
    o << '\n' << '|';
    for (ISC i = 0; i < 64; ++i) {
      c = *start;
      if (start++ > stop) {
        c = 'x';
      } else if (c < ' ') {
        address_to_print = start;
        c += cPrintC0Offset;
      }
      o << c;
    }
    o << "| " << Hexf(address_to_print - 1);
  }
  return o << STRPrintCharsBorder() << "Chars printed:" << size_bytes;
}

template <typename Printer, typename CHT = CHR>
inline Printer& TPrintChars(Printer& o, const CHT* start, ISW count) {
  return TPrintChars<Printer, CHT>(o, start, start + count - 1);
}

template <typename Printer>
Printer& TPrintChars(Printer& o, Charsf& item) {
  Valuef& element = item.element;
  ISW count = element.Count();
  switch (_::TypeTextFormat(element.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintChars<Printer, CHA>(o, element.ToSTA(), count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintChars<Printer, CHB>(o, element.ToSTB(), count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintChars<Printer, CHC>(o, element.ToSTC(), count);
    }
#endif
  }
  return _::TPrintChars<Printer, CHA>(
      o, reinterpret_cast<CHA*>(element.Value()), count);
}

template <typename Printer, typename DT = DT2>
Printer& TPrintTypePOD(Printer& o, DT type) {
  DT pod_type = type & cTypePODMask,        //
      vector_type = TTypeVector<DT>(type),  //
      map_type = TTypeMap<DT>(type);        //
}

template <typename Printer, typename DT = DT2>
Printer& TPrintType(Printer& o, DT type) {
  DT pod_type = type & cTypePODMask;
  if (pod_type == 0) return o << "BGN" << (type >> cTypePODBitCount);
  DT vector_type = TTypeVector<DT>(type);
  if (vector_type) {
    return o << STRType(vector_type) << '_' << STRType(pod_type);
  }
  DT map_type = TTypeMap<DT>(type);
  if (map_type) {
    return o << STRType(map_type) << '_' << STRType(pod_type);
  }
  return o;
}

template <typename Printer, typename DT = DT2>
Printer& TPrintValue(Printer& o, DT type, void* item) {}

}  // namespace _

#endif
