/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Uniprinter.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_UNIPRINTER_TEMPLATES
#define SCRIPT2_UNIPRINTER_TEMPLATES
#include "Stringf.h"
#include "Types.hpp"
namespace _ {

/* Prints the given string to the Printer. */
template<typename Printer, typename CHT = CHR>
Printer& TSPrintString(Printer& o, const CHT* string) {
  if (!string) return o;
  CHL c = 0;
  string = SScan(string, c);
  while (c) {
    o << c;
    string = SScan(string, c);
  }
  return o;
}

/* Prints the given string to the Printer and returns the count of characters
printed. */
template<typename Printer, typename CHT = CHR>
ISN TPrintAndCount(Printer& o, const CHT* string) {
  if (!string) return 0;
  ISN print_count = 0;
  CHL c = 0;
  string = SScan(string, c);
  while (c) {
    o << c;
    ++print_count;
    string = SScan(string, c);
  }
  return print_count;
}

/* Prints the following value to the console in Hex. */
template<typename Printer, typename IU>
Printer& TPrintHex(Printer& o, IU value) {
  enum { cHexStringLengthSizeMax = sizeof(IU) * 2 + 3 };
  auto ui = ToUnsigned(value);
  for (ISC num_bits_shift = sizeof(IU) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    o << HexNibbleToUpperCase((IUA)(ui >> num_bits_shift));
  }
  return o;
}

/* Prints the following value to the console in Hex. */
template<typename Printer>
Printer& TPrintHex(Printer& o, const void* value) {
  IUW ptr = IUW(value);
  return TPrintHex<Printer, IUW>(o, ptr);
}
template<typename Printer, typename IS, typename IU>
Printer& TPrintHex(Printer& o, IS value) {
  return TPrintHex<Printer, IU>(o, IU(value));
}
#if USING_FPC == YES_0
template<typename Printer>
Printer& TPrintHex(Printer& o, FPC value) {
  return TPrintHex<Printer, IUC>(o, *TPtr<IUC>(&value));
}
#endif
#if USING_FPD == YES_0
template<typename Printer>
Printer& TPrintHex(Printer& o, FPD value) {
  return TPrintHex<Printer, IUD>(o, *TPtr<IUD>(&value));
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
template<typename Printer>
Printer& TPrintHex(Printer& o, const void* origin, ISW byte_count) {
  if (!origin) return o;
  ISW delta;
  const IUA* cursor = TPtr<const IUA>(origin);
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

template<typename Printer>
Printer& TPrintHex(Printer& o, const void* start, const void* stop) {
  ISW delta = ISW(stop) - ISW(start);
  return TPrintHex<Printer>(o, start, delta);
}

/* Prints the memory beginning at start to the Printer. */
template<typename Printer>
Printer& TPrintBinary(Printer& o, const void* start, ISW byte_count) {
  if (!start) return o;
  const IUA* cursor = TPtr<const IUA>(start);
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

template<typename Printer>
inline Printer& TPrintBinary(Printer& o, const void* start, const void* stop) {
  ISW delta = ISW(stop) - ISW(start);
  return TPrintBinary<Printer>(o, start, TPtr<const void>(delta));
}

template<typename Printer, typename IU>
Printer& TPrintBinary(Printer& o, IU value) {
  enum { cSize = sizeof(IU) * 8 };
  auto ui = ToUnsigned(value);
  for (ISC i = cSize; i > 0; --i) {
    CHA c = CHA('0' + (ui >> (cSize - 1)));
    o << c;
    ui = ui << 1;
  }
  return o;
}

template<typename Printer, typename IS, typename IU>
Printer& TPrintBinary(Printer& o, IS value) {
  return TPrintBinary<Printer, IU>(o, (IU)value);
}
#if USING_FPC == YES_0
template<typename Printer>
Printer& TPrintBinary(Printer& o, FPC value) {
  return TPrintBinary<Printer, IUC>(o, *TPtr<IUC>(&value));
}
#endif
#if USING_FPC == YES_0
template<typename Printer>
Printer& TPrintBinary(Printer& o, FPD value) {
  return TPrintBinary<Printer, IUD>(o, *TPtr<IUD>(&value));
}
#endif

template<typename Printer>
Printer& TPrintAligned(Printer& o, const CHA* string, ISW char_count,
                       ISW left_count, ISW dot_count, ISW right_count) {
  while (--left_count > 0) o << ' ';
  while (--char_count > 0) {
#if LARGEST_CHAR == 1 || SEAM < SCRIPT2_CORE
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
template<typename Printer, typename CHT = CHR>
Printer& TPrintCenter(Printer& o, const CHT* value, ISW column_count = 80) {
  if (!value || column_count < 1) return o;

  const CHT* token_end = TSTREnd<CHT>(value);
  if (value == token_end) return o;
  ISW length = token_end - value, space_count = column_count - length;

  if (space_count > 0) {
    ISW half_count = space_count >> 1;
    space_count -= half_count;
    while (half_count-- > 0) o << ' ';
    o << value;
    while (space_count-- > 0) o << ' ';
    return o;
  }
  length = (-length) - 3;
  if (length < 0) {
    while (--length > 0) o << '.';
  } else {
    while (length > 0) o << *value++;
    o << "...";
  }
  return o;
}

template<typename Printer>
Printer& TPrintAlignedHex(Printer& o, const void* origin, ISW byte_count,
                          ISW left_count, ISW dot_count, ISW right_count) {
  const CHA* cursor = TPtr<const CHA>(origin);
  while (--left_count > 0) o << ' ';
  // TPrintHex<Printer>(o, origin, byte_count >> 1);
  TPrintHex<Printer>(o, cursor, -byte_count);
  while (--dot_count > 0) o << ' ';
  while (--right_count > 0) o << ' ';
  return o;
}

/* Prints th given value centered unless it's count is less then 0, in which
case it will print the POD value stored in the first Word of the string. */
template<typename Printer>
Printer& TPrintCenter(Printer& o, Stringf& value) {
  ISW column_count = value.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    ISW byte_count = TypeSizeOf(value.Type()), left_count, dot_count;
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
    return TPrintAlignedHex<Printer>(o, value.Value(), byte_count >> 1,
                                     left_count, dot_count, right_count);
  }
  ISW utf_format = _::TypeTextFormat(value.Type());
  switch (utf_format) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintCenter<Printer, CHA>(o, value.STA(), column_count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintCenter<_::COut, CHB>(o, value.STB(), column_count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintCenter<Printer, CHC>(o, value.STC(), column_count);
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
template<typename Printer, typename CHT = CHR>
Printer& TPrintRight(Printer& o, const CHT* value, ISW column_count = 80) {
  if (!value || column_count < 1) return o;

  const CHT* token_end = TSTREnd<CHT>(value);
  if (value == token_end) return o;
  ISW length = token_end - value, space_count = column_count - length;

  if (space_count > 0) {
    while (space_count-- > 0) o << ' ';
    o << value;
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
    while (length > 0) o << *value++;
    o << "...";
  }
  return o;
}

/* Prints the given value centered, printing it as hex if the value.Count() is
less than 0. */
template<typename Printer>
Printer& TPrintRight(Printer& o, Stringf& value) {
  ISW column_count = value.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    ISW char_count = TypeSizeOf(value.Type());
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
    return TPrintAlignedHex<Printer>(o, value.STA(), char_count, left_count,
                                     dot_count, 0);
  }
  ISW count = value.Count();
  switch (_::TypeTextFormat(value.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintRight<Printer, CHA>(o, value.STA(), count);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintRight<Printer, CHB>(o, value.STB(), count);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintRight<Printer, CHC>(o, value.STC(), count);
    }
#endif
  }
  return o;
}

template<typename Printer>
Printer& TPrintIndent(Printer& o, ISW indent_count) {
  o << '\n';
  while (--indent_count >= 0) o << ' ';
  return o;
}

template<typename Printer, typename CHT>
Printer& TPrintRepeat(Printer& o, CHT c, ISW count) {
  while (--count >= 0) o << c;
  return o;
}

template<typename CHT = CHR>
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
template<typename Printer, typename CHT = CHR>
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

template<typename Printer, typename CHT = CHR>
Printer& TPrintLine(Printer& o, CHT token = '-', ISW column_count = 80) {
  o << '\n';
  TPrintRepeat<Printer, CHT>(o, token, column_count);
  return o << '\n';
}

template<typename Printer>
Printer& TPrintLinef(Printer& o, Linef& value) {
  ISW type = value.element.value.Type(),  //
      utf_format = _::TypeTextFormat(type);
  switch (utf_format) {
#if USING_UTF8 == YES_0
    case _STA: {
      _::TPrintLinef<Printer, CHA>(o, value.element.ToSTA(), value.element.count);
      break;
    }
#endif
#if USING_UTF16 == YES_0
    case _STB: {
      _::TPrintLinef<Printer, CHB>(o, value.element.ToSTB(), value.element.count);
      break;
    }
#endif
#if USING_UTF32 == YES_0
    case _STC: {
      const CHC* start = TPtr<const CHC>(value.element.value.ToPTR());
      _::TPrintLinef<Printer, CHC>(o, value.element.ToSTC(), value.element.count);
      break;
    }
#endif
    case -1: {
      switch (type & ATypePODMask) {
#if USING_UTF8 == YES_0
        case _CHA: {
          CHA c = (CHA)value.element.value.Word();
          _::TPrintLine<Printer, CHA>(o, c, value.element.count);
          break;
        }
#endif
#if USING_UTF16 == YES_0
        case _CHB: {
          CHB c = (CHB)value.element.value.Word();
          _::TPrintLine<Printer, CHB>(o, c, value.element.count);
          break;
        }
#endif
#if USING_UTF32 == YES_0
        case _CHC: {
          CHC c = (CHC)value.element.value.Word();
          _::TPrintLine<Printer, CHC>(o, c, value.element.count);
          break;
        }
#endif
      }
    }
  }
  return o;
}

template<typename CHT = CHR>
const CHT* TSTRHeadingf() {
  static const CHT kString[] = {'\n', '\n', '+', '-', '-', '-', '\n', '|', ' ',
                                NIL,  '\n', '+', '-', '-', '-', '\n', NIL};
  return kString;
}

/* Prints a heading with the */
template<typename Printer, typename CHT>
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

/* Prints the a formatted header. */
template<typename Printer>
Printer& TPrintHeadingf(Printer& o, Headingf& value) {
  switch (_::TypeTextFormat(value.element.Type())) {
#if USING_UTF8 == YES_0
    case 1: {
      return _::TPrintHeadingf<Printer, CHA>(o, value.element.STA(), value.style,
                                             value.element.Count(),
                                             value.caption2, value.caption3);
    }
#endif
#if USING_UTF16 == YES_0
    case 2: {
      return _::TPrintHeadingf<Printer, CHB>(o, value.element.STB(), value.style,
                                             value.element.Count(),
                                             value.caption2, value.caption3);
    }
#endif
#if USING_UTF32 == YES_0
    case 3: {
      return _::TPrintHeadingf<Printer, CHC>(o, value.element.STC(), value.style,
                                             value.element.Count(),
                                             value.caption2, value.caption3);
    }
#endif
  }
  return o;
}

template<typename Printer, typename CHT = CHR>
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
        c += APrintC0Offset;
      }
      if (c == 127) c = ' ';
      o << c;
    }
    o << "| " << Hexf(address_to_print - 1);
  }
  return o << STRPrintCharsBorder() << "Chars printed:" << size_bytes;
}

template<typename Printer, typename CHT = CHR>
inline Printer& TPrintChars(Printer& o, const CHT* start, ISW count) {
  return TPrintChars<Printer, CHT>(o, start, start + count - 1);
}

template<typename Printer>
Printer& TPrintChars(Printer& o, Charsf& value) {
  Valuef& element = value.element;
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
      o, TPtr<CHA>(element.Value()), count);
}

/* Prints a string represntation of an 8-bit ASCII Data Type to the printer. */
template<typename Printer>
Printer& TPrintType(Printer& o, DTA type) {
  if (type < 32) return o << STRTypePOD(type); // POD Type
  DTW type_pod = type & 0x1f,
    type_vector = (type & DTVHT) >> 5;
  // |     b7     |    b6:b5    |   b4:b0   |
  // |:----------:|:-----------:|:---------:|
  // | Size Width | Vector Type |  POD Type |
  if (type >> 7) { // SW bit asserted, there is a 16-bit size_width
    return o << STRTypeVector(type_vector) << 'B' << '_'
      << STRTypePOD(type_pod);
  }

  return o << STRTypeVector(type_vector) << 'A' << '_'
    << STRTypePOD(type_pod);
}

template<typename Printer>
Printer& TPrintTypeVector(Printer& o, DTB type) {
  if (type >> 9 != 0) return o;
}

/* Prints a string represntation of an ASCII Data Type to the printer.
16-bit ASCII Bit Pattern:
| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:------:|:-----:|:-----:|:-----:|
|   MOD   |   MT   |  SW   |  VT   |  POD  | */
template<typename Printer>
Printer& TPrintType(Printer& o, DTB type) {
  // Processing from MOD to POD/left to right.
  o << "0b" << Binaryf(type) << ' ';
  auto mod_bits    = type >> ATypeMODBit0;
  if (mod_bits != 0) {
    o << STRTypeModifier(mod_bits) << '_';
    type ^= mod_bits << ATypeMODBit0;
  }
  auto map_type = type >> ATypeMTBit0;
  if (map_type != 0) {
    o << STRTypePOD(map_type) << "_";
    type ^= map_type << ATypeMTBit0;
  }
  if (type < ATypePODCount) return o << STRTypePOD(type); // POD Type
  auto size_width = type >> ATypeSWBit0;
  type ^= size_width << ATypeSWBit0;
  auto vector_type = type >> ATypeVTBit0;
  type ^= vector_type << ATypeVTBit0;
  if (!vector_type && !size_width) // Vector of Homo-tuple.
    o << STRTypeVector(vector_type) << '_';
  if (ATypeIsCH(type)) { // Then it's a string, loom, or 
    
  }
  return o << STRTypePOD(type);
}
template<typename Printer>
Printer& TPrintType(Printer& o, DTC type) {
  BOL first_time = true;
  ISN count = sizeof(DTC) / sizeof(DTB);
  while(count-- > 0) {
    if (!first_time) {
      o << ' ';
      first_time = false;
    }
    TPrintType<Printer>(o, DTB(type));
    type = type >> 16;
  }
  return o;
}
template<typename Printer>
Printer& TPrintType(Printer& o, DTD type) {
  BOL first_time = true;
  ISN count = sizeof(DTC) / sizeof(DTB);
  while (count-- > 0) {
    if (!first_time) {
      o << '-';
      first_time = false;
    }
    TPrintType<Printer>(o, DTB(type));
    type = type >> 16;
  }
  return o;
}

/* Prints a summary of the type-value tuple with word-sized Data Type. */
template<typename Printer>
Printer& TPrintType(Printer& o, TypeWordValue item) {
  return TPrintType<Printer>(o, item.type);
}

// Prints an ASCII POD type to the printer.
template<typename Printer, typename DT = DTB>
Printer& TPrintTypePOD(Printer& o, DT type) {
  DT pod_type = type & ATypePODMask,    //
    vector_type = TTypeVector<DT>(type),  //
    map_type = TTypeMap<DT>(type);     //
}

// Prints the value of the given type-value tuple.
template<typename Printer>
Printer& TPrintValuePOD(Printer& o, DTB type, const void* value) {
  switch (type) {
    case _NIL:
      return o;
    case _IUA:
      return o << *TPtr<const IUA>(value);
    case _ISA:
      return o << *TPtr<const ISA>(value);
    case _CHA:
      return o << *TPtr<const CHA>(value);
    case _FPB:
      return o << *TPtr<const FPB>(value);
    case _IUB:
      return o << *TPtr<const IUB>(value);
    case _ISB:
      return o << *TPtr<const ISB>(value);
    case _CHB:
      return o << *TPtr<const CHB>(value);
    case _FPC:
      return o << *TPtr<const FPC>(value);
    case _IUC:
      return o << *TPtr<const IUC>(value);
    case _ISC:
      return o << *TPtr<const ISC>(value);
    case _CHC:
      return o << *TPtr<const CHC>(value);
    case _FPD:
      return o << *TPtr<const FPD>(value);
    case _IUD:
      return o << *TPtr<const IUD>(value);
    case _ISD:
      return o << *TPtr<const ISD>(value);
    case _TME:
      return o << "TME not implemented";
      //o << *TPtr<const TME>(value);
    case _FPE:
      return o << "FPE not implemented";
      //o << *TPtr<const FPE>(value);
    case _IUE:
      return o << "IUE not implemented";
      //o << *TPtr<const IUE>(value);
    case _ISE:
      return o << "ISE not implemented";
      //o << *TPtr<const ISE>(value);
    case _BOL:
      return o << *TPtr<const BOL>(value);
  }
  return o;
}

// Prints the value of the given type-value tuple.
//| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
//|:-------:|:------:|:-----:|:-----:|:-----:|
//|   MOD   |   MT   |  SW   |  VTS  |  POD  |
template<typename Printer, typename DT = DTB>
Printer& TPrintValue(Printer & o, DT type, const void* value) {
  if (type < ATypePODCount) return TPrintValuePOD<Printer>(o, DTB(type), value);
  auto mod_bits = type >> ATypeMODBit0;
  type ^= mod_bits << ATypeMODBit0;
  auto map_type = type >> ATypeMTBit0;
  type ^= map_type << ATypeMTBit0;
  if (map_type > 0) {
    if (type < ATypePODCount) { // Map of one POD type to another.
      return o << STRTypePOD(type);
    }
  }
  auto size_width = type >> ATypeSWBit0;
  type ^= size_width << ATypeSWBit0;
  auto vector_type = type >> ATypeVTBit0;
  type ^= vector_type << ATypeVTBit0;
  o << "count_max:";
  if (vector_type == _ARY) {
    if      (size_width == 0) o << *(ISA*)(value);
    else if (size_width == 1) o << *(ISB*)(value);
    else if (size_width == 2) o << *(ISC*)(value);
    else if (size_width == 3) o << *(ISD*)(value);
    return o;
  } else if (vector_type == _STK) {
    if (size_width == 0) {
      auto cursor = TPtr<const ISA>(value);
      o << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 1) {
      auto cursor = TPtr<const ISB>(value);
      o << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 2) {
      auto cursor = TPtr<const ISC>(value);
      o << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 3) {
      auto cursor = TPtr<const ISD>(value);
      o << *cursor++ << " count:" << *cursor;
    }
  }
  else if (vector_type == _MAT) {
    if (size_width == 0) {
      auto cursor = TPtr<const ISA>(value);
      o << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 1) {
      auto cursor = TPtr<const ISB>(value);
      o << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 2) {
      auto cursor = TPtr<const ISC>(value);
      o << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 3) {
      auto cursor = TPtr<const ISD>(value);
      o << *cursor++ << " count:" << *cursor;
    }
  }
  return o;
}

// Prints the value of the given type-value tuple.
template<typename Printer, typename DT = DTB, typename IS = ISW>
Printer& TPrintValue(Printer& o, DT type, const void* base_ptr, IS offset) {
  return TPrintValue<Printer, DT>(o, type, TPtr<void>(base_ptr, offset));
}

// Prints the value of the given type-value tuple.
template<typename Printer, typename DT, typename IS>
Printer& TPrintValue(Printer& o, TTypeValue<DT> type_value) {
  return TPrintValue<Printer, DT>(o, type_value.type, type_value.value);
}

// Prints ASCII type and the value tuple.
template<typename Printer, typename DT = DTB>
Printer& TPrintTypeValue(Printer& o, DT type, const void* value) {
  return o << TPrintType<Printer>(o, type) << ':' 
           << TPrintValue<Printer, DT>(o, type, value);
}

// Prints ASCII type and the value tuple.
template<typename Printer, typename DT = DTB, typename IS = ISW>
Printer& TPrintTypeValue(Printer& o, DT type, const void* base_ptr, IS offset) {
  return TPrintTypeValue<Printer, DT>(o, type, TPtr<void>(base_ptr, offset));
}

}  //< namespace _

#endif
