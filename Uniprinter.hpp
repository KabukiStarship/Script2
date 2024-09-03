/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Uniprinter.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_STRING_CODE
#define SCRIPT2_STRING_CODE
#include "Stringf.hpp"
#if SEAM >= SCRIPT2_COUT
#include "Binary.hpp"
#include "Puff.hpp"

namespace _ {

/* Prints the given string to the Printer. */
template<typename Printer, typename CH = CHR>
Printer& TSPrintString(Printer& p, const CH* string) {
  if (!string) return p;
  CHL c = 0;
  string = SScan(string, c);
  while (c) {
    p << c;
    string = SScan(string, c);
  }
  return p;
}

/* Prints the given string to the Printer and returns the count of characters
printed. */
template<typename Printer, typename CH = CHR>
ISN TPrintAndCount(Printer& p, const CH* string) {
  if (!string) return 0;
  ISN print_count = 0;
  CHL c = 0;
  string = SScan(string, c);
  while (c) {
    p << c;
    ++print_count;
    string = SScan(string, c);
  }
  return print_count;
}


/* Prints the following value to the console in Hex. */
template<typename Printer, typename IU>
Printer& TPrintHex(Printer& p, IU value) {
  enum { cHexStringLengthSizeMax = sizeof(IU) * 2 + 3 };
  auto ui = ToUnsigned(value);
  for (ISC num_bits_shift = sizeof(IU) * 8 - 4; num_bits_shift >= 0;
    num_bits_shift -= 4) {
    p << HexNibbleToUpperCase((IUA)(ui >> num_bits_shift));
  }
  return p;
}

/* Prints the following value to the console in Hex. */
template<typename Printer>
Printer& TPrintHex(Printer& p, const void* value) {
  IUW ptr = IUW(value);
  return TPrintHex<Printer, IUW>(p, ptr);
}
template<typename Printer, typename IS, typename IU>
Printer& TPrintHex(Printer& p, IS value) {
  return TPrintHex<Printer, IU>(p, IU(value));
}
#if USING_FPC == YES_0
template<typename Printer>
Printer& TPrintHex(Printer& p, FPC value) {
  return TPrintHex<Printer, IUC>(p, *TPtr<IUC>(&value));
}
#endif
#if USING_FPD == YES_0
template<typename Printer>
Printer& TPrintHex(Printer& p, FPD value) {
  return TPrintHex<Printer, IUD>(p, *TPtr<IUD>(&value));
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
Printer& TPrintHex(Printer& p, const void* origin, ISW byte_count) {
  if (!origin) return p;
  ISW delta;
  const IUA* cursor = TPtr<const IUA>(origin);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
  // Print the hex value backwards.
  if (byte_count < 0) {
    byte_count = -byte_count;
    delta = -1;
    cursor += byte_count - 1;
  }
  else {
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
    p << HexNibbleToUpperCase(byte >> 4) << HexNibbleToUpperCase(byte & 0xf);
  }
  return p;
}

template<typename Printer>
Printer& TPrintHex(Printer& p, const void* start, const void* stop) {
  ISW delta = ISW(stop) - ISW(start);
  return TPrintHex<Printer>(p, start, delta);
}

template<typename Printer>
Printer& TPrint(Printer& p, Hexf& item) {
  return TPrintHex<Printer>(p, item.element.Value(), item.element.count);
}
/* Prints the memory beginning at start to the Printer. */
template<typename Printer>
Printer& TPrintBinary(Printer& p, const void* start, ISW byte_count) {
  if (!start) return p;
  const IUA* cursor = TPtr<const IUA>(start);
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
  ISA delta;
  if (byte_count < 0) {
    delta = -1;
    byte_count = -byte_count;
    cursor += byte_count - 1;
  }
  else {
    delta = 1;
  }
#endif
  while (--byte_count >= 0) {
    IUA c = *cursor;
    cursor += delta;
    for (ISW i = 8; i > 0; --i) {
      p << CHA('0' + (c >> 7));
      c = c << 1;
    }
  }
  return p;
}

template<typename Printer>
inline Printer& TPrintBinary(Printer& p, const void* start, const void* stop) {
  ISW delta = ISW(stop) - ISW(start);
  return TPrintBinary<Printer>(p, start, TPtr<const void>(delta));
}

template<typename Printer, typename IU>
Printer& TPrintBinary(Printer& p, IU value) {
  enum { Size = sizeof(IU) * 8 };
  auto ui = ToUnsigned(value);
  for (ISC i = Size; i > 0; --i) {
    CHA c = CHA('0' + (ui >> (Size - 1)));
    p << c;
    ui = ui << 1;
  }
  return p;
}

template<typename Printer, typename IS, typename IU>
Printer& TPrintBinary(Printer& p, IS value) {
  return TPrintBinary<Printer, IU>(p, (IU)value);
}
#if USING_FPC == YES_0
template<typename Printer>
Printer& TPrintBinary(Printer& p, FPC value) {
  return TPrintBinary<Printer, IUC>(p, *TPtr<IUC>(&value));
}
#endif
#if USING_FPC == YES_0
template<typename Printer>
Printer& TPrintBinary(Printer& p, FPD value) {
  return TPrintBinary<Printer, IUD>(p, *TPtr<IUD>(&value));
}
#endif

template<typename Printer>
Printer& TPrint(Printer& p, Binaryf& item) {
  return TPrintBinary<Printer>(p, item.element.Value(), item.element.count);
}

template<typename Printer>
Printer& TPrintAligned(Printer& p, const CHA* string, ISW char_count,
  ISW left_count, ISW dot_count, ISW right_count) {
  while (--left_count > 0) p << ' ';
  while (--char_count > 0) {
#if LARGEST_CHAR == 1 || SEAM < SCRIPT2_COUT
    p << *string++;
#else
    CHL c;
    string = SScan(string, c);
    if (!string) return p;
    p << c;
#endif
  }
  while (--dot_count > 0) p << ' ';
  while (--right_count > 0) p << ' ';
  return p;
}

template<typename Printer>
Printer& TPrintAlignedHex(Printer& p, const void* origin, ISW byte_count,
  ISW left_count, ISW dot_count, ISW right_count) {
  const CHA* cursor = TPtr<const CHA>(origin);
  while (--left_count > 0) p << ' ';
  // TPrintHex<Printer>(p, origin, byte_count >> 1);
  TPrintHex<Printer>(p, cursor, -byte_count);
  while (--dot_count > 0) p << ' ';
  while (--right_count > 0) p << ' ';
  return p;
}

/* Prints the given token aligned center the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CHA upon success.
@param token  The token to utf.
@param column_count The number_ of columns to align right to. */
template<typename Printer, typename CH = CHR>
Printer& TPrintCenter(Printer& p, const CH* value, ISW column_count = 80) {
  if (!value || column_count < 1) return p;

  const CH* token_end = TSTREnd<CH>(value);
  if (value == token_end) return p;
  ISW length = token_end - value, space_count = column_count - length;

  if (space_count > 0) {
    ISW half_count = space_count >> 1;
    space_count -= half_count;
    while (half_count-- > 0) p << ' ';
    p << value;
    while (space_count-- > 0) p << ' ';
    return p;
  }
  length = (-length) - 3;
  if (length < 0) {
    while (--length > 0) p << '.';
  }
  else {
    while (length > 0) p << *value++;
    p << "...";
  }
  return p;
}

/* Prints th given value centered unless it's count is less then 0, in which
case it will print the POD value stored in the first Word of the string. */
template<typename Printer>
Printer& TPrintCenter(Printer& p, Stringf& value) {
  ISW column_count = value.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    ISW byte_count = ATypeSizeOfPOD(DTB(value.Type())), left_count, dot_count;
    if (byte_count < 0) return p;
    byte_count = byte_count << 1;
    ISW right_count;
    if (byte_count > column_count) {
      while (--column_count > 0) p << ' ';
      return p;
    }
    else {
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
    return TPrintAlignedHex<Printer>(p, value.Value(), byte_count >> 1,
      left_count, dot_count, right_count);
  }
  ISW utf_format = _::ATypeTextFormat(value.Type());
  switch (utf_format) {
#if USING_UTF8 == YES_0
  case 1: {
    return _::TPrintCenter<Printer, CHA>(p, value.STA(), column_count);
  }
#endif
#if USING_UTF16 == YES_0
  case 2: {
    return _::TPrintCenter<Printer, CHB>(p, value.STB(), column_count);
  }
#endif
#if USING_UTF32 == YES_0
  case 3: {
    return _::TPrintCenter<Printer, CHC>(p, value.STC(), column_count);
  }
#endif
  }
  return p;
}

/* Prints the given cursor center aligned to the given column_count. */
template<typename Printer>
inline Printer& TPrint(Printer& p, Centerf& item) {
  return TPrintCenter<Printer>(p, item.element);
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CHA upon success.
@param token  The token to utf.
@param column_count The number_ of columns to align right to. */
template<typename Printer, typename CH = CHR>
Printer& TPrintRight(Printer& p, const CH* value, ISW column_count = 80) {
  if (!value || column_count < 1) return p;

  const CH* token_end = TSTREnd<CH>(value);
  if (value == token_end) return p;
  ISW length = token_end - value, space_count = column_count - length;

  if (space_count > 0) {
    while (space_count-- > 0) p << ' ';
    p << value;
    return p;
  }
  length = (-length) - 3;
  if (length < 0) {
    switch (length) {
    case 1:
      p << '.';
    case 2:
      p << "..";
    case 3:
      p << "...";
    }
  }
  else {
    while (length > 0) p << *value++;
    p << "...";
  }
  return p;
}

/* Prints the given value centered, printing it as hex if the value.Count() is
less than 0. */
template<typename Printer>
Printer& TPrintRight(Printer& p, Stringf& value) {
  ISW column_count = value.Count();
  if (column_count < 0) {  // Print hex.
    column_count = -column_count;
    ISW char_count = ATypeSizeOfPOD(DTB(value.Type()));
    if (char_count < 0) return p;

    ISW left_count, dot_count;
    if (char_count > column_count) {
      left_count = 0;
      if (column_count < 3) {
        char_count = 0;
        dot_count = column_count;
      }
      else {
        char_count = column_count - 3;
        dot_count = 3;
      }
    }
    else {
      left_count = column_count - char_count;
      dot_count = 0;
    }
    return TPrintAlignedHex<Printer>(p, value.STA(), char_count, left_count,
      dot_count, 0);
  }
  ISW count = value.Count();
  switch (_::ATypeTextFormat(value.Type())) {
#if USING_UTF8 == YES_0
  case 1: {
    return _::TPrintRight<Printer, CHA>(p, value.STA(), count);
  }
#endif
#if USING_UTF16 == YES_0
  case 2: {
    return _::TPrintRight<Printer, CHB>(p, value.STB(), count);
  }
#endif
#if USING_UTF32 == YES_0
  case 3: {
    return _::TPrintRight<Printer, CHC>(p, value.STC(), count);
  }
#endif
  }
  return p;
}

template<typename Printer>
Printer& TPrint(Printer& p, Rightf& item) {
  return TPrintRight<Printer>(p, item.element);
}

template<typename Printer, typename CH>
Printer& TPrintRepeat(Printer& p, CH c, ISW count) {
  while (--count >= 0) p << c;
  return p;
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
template<typename Printer, typename CH = CHR>
const CH* TPrintLinef(Printer& p, const CH* style = nullptr,
  ISW column_count = 80) {
  enum {
    StateScanningDifferentChars = 0,
    StateStateDuplicateChar = 1,
    BreakCount = 3,
  };
  if (!style) style = TSTRLinef<CH>();
  if (column_count < BreakCount) return nullptr;

  ISW state = StateScanningDifferentChars;
  CH current_char = *style++,  //
    prev_char = ~current_char;
  ISC hit_count = 0, column_index = 0;
  while (current_char) {
    p << current_char;
    if (current_char == '\n')
      column_index = 0;
    else
      ++column_index;
    switch (state) {
    case StateScanningDifferentChars: {
      if (current_char == prev_char && !TIsWhitespace<CH>(current_char)) {
        state = StateStateDuplicateChar;
        hit_count = 1;
      }
      break;
    }
    case StateStateDuplicateChar: {
      if (current_char != prev_char)
        state = StateScanningDifferentChars;
      else if (++hit_count >= BreakCount - 1) {
        TPrintRepeat<Printer, CH>(p, current_char,
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

template<typename Printer, typename CH = CHR>
Printer& TPrintLine(Printer& p, CH token = '-', ISW column_count = 80) {
  p << '\n';
  TPrintRepeat<Printer, CH>(p, token, column_count);
  return p << '\n';
}

template<typename Printer>
Printer& TPrint(Printer& p, Linef& value) {
  ISW type = value.element.value.Type(),  //
    utf_format = _::ATypeTextFormat(type);
  switch (utf_format) {
#if USING_UTF8 == YES_0
  case _STA: {
    _::TPrintLinef<Printer, CHA>(p, value.element.ToSTA(), value.element.count);
    break;
  }
#endif
#if USING_UTF16 == YES_0
  case _STB: {
    _::TPrintLinef<Printer, CHB>(p, value.element.ToSTB(), value.element.count);
    break;
  }
#endif
#if USING_UTF32 == YES_0
  case _STC: {
    const CHC* start = TPtr<const CHC>(value.element.value.ToPTR());
    _::TPrintLinef<Printer, CHC>(p, value.element.ToSTC(), value.element.count);
    break;
  }
#endif
  case -1: {
    switch (type & ATypePODMask) {
#if USING_UTF8 == YES_0
    case _CHA: {
      CHA c = (CHA)value.element.value.Word();
      _::TPrintLine<Printer, CHA>(p, c, value.element.count);
      break;
    }
#endif
#if USING_UTF16 == YES_0
    case _CHB: {
      CHB c = (CHB)value.element.value.Word();
      _::TPrintLine<Printer, CHB>(p, c, value.element.count);
      break;
    }
#endif
#if USING_UTF32 == YES_0
    case _CHC: {
      CHC c = (CHC)value.element.value.Word();
      _::TPrintLine<Printer, CHC>(p, c, value.element.count);
      break;
    }
#endif
    }
  }
  }
  return p;
}

template<typename CH>
const CH* TSTRHeadingf() {
  static const CH String[] = { '\n', '\n', '+', '-', '-', '-', '\n', '|', ' ',
                                NIL,  '\n', '+', '-', '-', '-', '\n', NIL };
  return String;
}

/* Prints a heading with the */
template<typename Printer, typename CH>
Printer& TPrintHeading(Printer& p, const CH* element,
  const CHA* style = nullptr, ISW column_count = 80,
  const CHA* caption2 = nullptr,
  const CHA* caption3 = nullptr) {
  if (!style) style = TSTRHeadingf<CHA>();
  style = TPrintLinef<Printer, CHA>(p, style, column_count);
  if (!style) return p;
  p << element;
  if (caption2) p << caption2;
  if (caption3) p << caption3;
  TPrintLinef<Printer, CHA>(p, style, column_count);
  return p;
}

/* Prints the a formatted header. */
template<typename Printer>
Printer& TPrint(Printer& p, Headingf& value) {
  switch (_::ATypeTextFormat(value.element.Type())) {
#if USING_UTF8 == YES_0
  case 1: {
    return _::TPrintHeading<Printer, CHA>(p, value.element.STA(), value.style,
      value.element.Count(),
      value.caption2, value.caption3);
  }
#endif
#if USING_UTF16 == YES_0
  case 2: {
    return _::TPrintHeading<Printer, CHB>(p, value.element.STB(), value.style,
      value.element.Count(),
      value.caption2, value.caption3);
  }
#endif
#if USING_UTF32 == YES_0
  case 3: {
    return _::TPrintHeading<Printer, CHC>(p, value.element.STC(), value.style,
      value.element.Count(),
      value.caption2, value.caption3);
  }
#endif
  }
  return p;
}

template<typename Printer, typename CH = CHR>
Printer& TPrintChars(Printer& p, const CH* start, const CH* stop) {
  D_ASSERT(start < stop);
  if (!start || start >= stop) return p;

  ISW size_bytes = stop - start + 1;

  p << STAPrintCharsHeader() << STAPrintCharsBorder() << Hexf(start);
  int i = 0;
  CH c;
  const CH* address_to_print = start;
  while (start <= stop) {
    p << '\n' << '|';
    for (ISC i = 0; i < 64; ++i) {
      c = *start;
      if (start++ > stop) {
        c = 'x';
      }
      else if (c < ' ') {
        address_to_print = start;
        c += APrintC0Offset;
      }
      if (c == 127) c = ' ';
      p << c;
    }
    p << "| " << Hexf(address_to_print - 1);
  }
  return p << STAPrintCharsBorder() << "Chars printed:" << size_bytes;
}

template<typename Printer, typename CH = CHR>
inline Printer& TPrintChars(Printer& p, const CH* start, ISW count) {
  return TPrintChars<Printer, CH>(p, start, start + count - 1);
}

template<typename Printer>
Printer& TPrint(Printer& p, Charsf& value) {
  auto element = value.element;
  ISW count = element.Count();
  switch (_::ATypeTextFormat(element.Type())) {
#if USING_UTF8 == YES_0
  case 1: {
    return _::TPrintChars<Printer, CHA>(p, element.ToSTA(), count);
  }
#endif
#if USING_UTF16 == YES_0
  case 2: {
    return _::TPrintChars<Printer, CHB>(p, element.ToSTB(), count);
  }
#endif
#if USING_UTF32 == YES_0
  case 3: {
    return _::TPrintChars<Printer, CHC>(p, element.ToSTC(), count);
  }
#endif
  }
  return _::TPrintChars<Printer, CHA>(
    p, TPtr<CHA>(element.Value()), count);
}

/* Prints the given cursor repeated to make a line. */
template<typename CH>
CH* TPrintHeading(CH* start, CH* stop, CH item,
  ISW count = AConsoleWidth) {
  return TPrintLinef<CH>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template<typename CH>
CH* TPrintHeading(CH* start, CH* stop, const CH* item,
  ISW count = AConsoleWidth) {
  return TPrintLinef<CH>(start, stop, item, count, nullptr, nullptr);
}

template<typename Printer>
Printer& TPrintIndent(Printer& p, ISW indent_count) {
  p << '\n';
  while (--indent_count >= 0) p << ' ';
  return p;
}

template<typename Printer>
Printer& TPrint(Printer& p, const Indentf& item) {
  return _::TPrintIndent<Printer>(p, item.indent_count);
}
} // namespace _

#if SEAM >= SCRIPT2_UNIPRINTER
namespace _ {

/* Prints the given sizef to the printer. */
template<typename Printer>
Printer& TPrint(Printer& p, Sizef& item) {
  auto value = item.size;
  if (value < 0) return p << CHA('@' + (-value));
  return p << value;
}

#if SEAM >= UNIPRINTER

// Prints an ASCII POD type to the printer.
template<typename Printer, typename DT = DTB>
Printer& TPrintATypePOD(Printer& p, DT type) {
  DT pod_type = type & ATypePODMask,    //
    vector_type = TTypeVector<DT>(type),  //
    map_type = TTypeMap<DT>(type);     //
}

/* Prints a string represntation of an ASCII Data Type to the printer.
16-bit ASCII Bit Pattern:
| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:------:|:-----:|:-----:|:-----:|
|   MOD   |   MT   |  SW   |  VT   |  POD  | */
template<typename Printer>
Printer& TPrintAType(Printer& p, DTB type) {
  auto mod_bits = type >> ATypeMODBit0;
  if (mod_bits) {
    type ^= mod_bits << ATypeMODBit0;
    p << STAATypeModifier(mod_bits) << '_';
  }
  if (type < ATypePODCount) return p << STAATypePOD(type); // POD Type
  // Processing from MOD to POD/left to right.
  auto map_type = type >> ATypeMTBit0;
  type ^= map_type << ATypeMTBit0;
  auto size_width = type >> ATypeSWBit0;
  type ^= size_width << ATypeSWBit0;
  auto vector_type = type >> ATypeVTBit0;
  type ^= vector_type << ATypeVTBit0;
  if (map_type)
    p << STAATypeMap(size_width) << '_' << STAATypePOD(map_type) << '_';
  if (!map_type && (vector_type || (!vector_type && size_width)))
    return p << STRATypesVector(vector_type | (size_width << 2))
             << '_' << STAATypePOD(type);
  if (ATypeIsCH(type) && map_type == 0) // Then it's a string, loom, or.
    return p << "ST" << ATypeSWCH(size_width);
  return p << STAATypePOD(type);
}
// NIL->CHA   -> 0x01351f =: "dez nutz!\0"
// ANY->NIL 16-bit -> 
// 0x31E0 -> 5 LSb are 0 -> Shift over 5 bits to get number bytes.
// 16-bits - 5-bits = 11 => 2^11 = 2048
/**/
template<typename Printer>
Printer& TPrintAType(Printer& p, DTC type) {
  BOL first_time = true;
  ISN count = sizeof(DTC) / sizeof(DTB);
  while (count-- > 0) {
    if (!first_time) {
      p << ' ';
      first_time = false;
    }
    TPrintAType<Printer>(p, DTB(type));
    type = type >> 16;
    if (type == 0) return p;
  }
  return p;
}
template<typename Printer>
Printer& TPrintAType(Printer& p, DTD type) {
  BOL first_time = true;
  ISN count = sizeof(DTD) / sizeof(DTB);
  while (count-- > 0) {
    if (!first_time) {
      p.Print('-');
      first_time = false;
    }
    TPrintAType<Printer>(p, DTB(type));
    type = type >> 16;
    if (type == 0) return p;
  }
  return p;
}

// Prints the value of the given type-value tuple.
template<typename Printer>
Printer& TPrintValuePOD(Printer& p, DTB type, const void* value) {
  switch (type) {
    case _NIL: return p; //< 00
    case _IUA: return p << *TPtr<const IUA>(value); //< 01
    case _ISA: return p << *TPtr<const ISA>(value); //< 02
    case _CHA: return p << *TPtr<const CHA>(value); //< 03
    case _FPB: return p << *TPtr<const FPB>(value); //< 04
    case _IUB: return p << *TPtr<const IUB>(value); //< 05
    case _ISB: return p << *TPtr<const ISB>(value); //< 06
    case _CHB: return p << *TPtr<const CHB>(value); //< 07
    case _FPC: return p << *TPtr<const FPC>(value); //< 08
    case _IUC: return p << *TPtr<const IUC>(value); //< 09
    case _ISC: return p << *TPtr<const ISC>(value); //< 10
    case _CHC: return p << *TPtr<const CHC>(value); //< 11
    case _FPD: return p << *TPtr<const FPD>(value); //< 12
    case _IUD: return p << *TPtr<const IUD>(value); //< 13
    case _ISD: return p << *TPtr<const ISD>(value); //< 14
    case _TME: return p << "TME not implemented";
      //p << *TPtr<const TME>(value); //< 15
    case _FPE: return p << "FPE not implemented";
      //p << *TPtr<const FPE>(value); //< 16
    case _IUE: return p << "IUE not implemented";
      //p << *TPtr<const IUE>(value); //< 17
    case _ISE: return p << "ISE not implemented";
      //p << *TPtr<const ISE>(value); //< 18
    case _BOL:  return p << *TPtr<const BOL>(value); //< 19
  }
  return p;
}

// Prints the value of the given type-value tuple.
//| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
//|:-------:|:------:|:-----:|:-----:|:-----:|
//|   MOD   |   MT   |  SW   |  VT   |  POD  |
template<typename Printer, typename DT = DTB>
Printer& TPrintValue(Printer & p, DT type, const void* value) {
  auto mod_bits = type >> ATypeMODBit0;
  if (mod_bits) {
    type ^= mod_bits << ATypeMODBit0;
    p << STAATypePOD(mod_bits);
  }
  if (type < ATypePODCount) return TPrintValuePOD<Printer>(p, DTB(type), value);
  auto map_type = type >> ATypeMTBit0;
  type ^= map_type << ATypeMTBit0;
  auto size_width = type >> ATypeSWBit0;
  type ^= size_width << ATypeSWBit0;
  auto vector_type = type >> ATypeVTBit0;
  type ^= vector_type << ATypeVTBit0;
  if (map_type > 0) {
    if (type < ATypePODCount) { // Map of one POD type to another.
      return p << STAATypePOD(type);
    }
  }
  p << "count_max:";
  if (vector_type == _ARY) {
    if      (size_width == 0) p << *(ISA*)(value);
    else if (size_width == 1) p << *(ISB*)(value);
    else if (size_width == 2) p << *(ISC*)(value);
    else if (size_width == 3) p << *(ISD*)(value);
    return p;
  } else if (vector_type == _SCK) {
    if (size_width == 0) {
      auto cursor = TPtr<const ISA>(value);
      p << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 1) {
      auto cursor = TPtr<const ISB>(value);
      p << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 2) {
      auto cursor = TPtr<const ISC>(value);
      p << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 3) {
      auto cursor = TPtr<const ISD>(value);
      p << *cursor++ << " count:" << *cursor;
    }
  }
  else if (vector_type == _MAT) {
    if (size_width == 0) {
      auto cursor = TPtr<const ISA>(value);
      p << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 1) {
      auto cursor = TPtr<const ISB>(value);
      p << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 2) {
      auto cursor = TPtr<const ISC>(value);
      p << *cursor++ << " count:" << *cursor;
    }
    else if (size_width == 3) {
      auto cursor = TPtr<const ISD>(value);
      p << *cursor++ << " count:" << *cursor;
    }
  }
  return p;
}

// Prints the value of the given type-value tuple.
template<typename Printer, typename DT = DTB, typename IS = ISW>
Printer& TPrintValue(Printer& p, DT type, const void* base_ptr, IS offset) {
  return TPrintValue<Printer, DT>(p, type, TPtr<void>(base_ptr, offset));
}

// Prints the value of the given type-value tuple.
template<typename Printer, typename DT, typename IS>
Printer& TPrintValue(Printer& p, TATypeValuePtr<DT> type_value) {
  return TPrintValue<Printer, DT>(p, type_value.type, type_value.value);
}

// Prints ASCII type and the value tuple.
template<typename Printer, typename DT = DTB>
Printer& TPrintATypeValue(Printer& p, DT type, const void* value) {
  return p << TPrintAType<Printer>(p, type) << ':'
           << TPrintValue<Printer, DT>(p, type, value);
}

// Prints ASCII type and the value tuple.
template<typename Printer, typename DT = DTB, typename IS = ISW>
Printer& TPrintATypeValue(Printer& p, DT type, const void* base_ptr, IS offset) {
  return TPrintATypeValue<Printer, DT>(p, type, TPtr<void>(base_ptr, offset));
}

/* A dumb templated string Printer. */
template<typename CH = CHR, typename IS = ISW>
struct TSPrinter {
  CH* start,  //< Start address.
    * stop;   //< Stop address.

  /* Default constructor does nothing. */
  TSPrinter() : start(0), stop(0) {}

  /* Initializes the UTF& from the given origin pointers.
  @param start The origin of the origin.
  @param count The number of CH(s) in the boofer. */
  TSPrinter(CH* start, ISA size) : start(start), stop(start + size - 1) {
    Reset();
  }

  /* Initializes the UTF& from the given origin pointers.
  @param start The origin of the origin.
  @param count The number of CH(s) in the boofer. */
  TSPrinter(CH* start, ISB size) : start(start), stop(start + size - 1) {
    Reset();
  }

  /* Initializes the UTF& from the given origin pointers.
  @param start The origin of the origin.
  @param count The number of CH(s) in the boofer. */
  TSPrinter(CH* start, ISC size) : start(start), stop(start + size - 1) {
    Reset();
  }

  /* Initializes the UTF& from the given origin pointers.
  @param start The origin of the origin.
  @param count The number of CH(s) in the boofer. */
  TSPrinter(CH* start, ISD size) : start(start), stop(start + size - 1) {
    Reset();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TSPrinter(CH* start, CH* stop) : start(start), stop(stop) { Reset(); }

  /* Clones the other printer. */
  TSPrinter(const TSPrinter& other)
    : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  /* Points to the end of the contiguous linear socket. */
  IUA* End() { return TPtr<IUA>(start) + (sizeof(CH) - 1); }

  IS SizeBytes() { return (IS)(stop - start + sizeof(CH)); }

  void Wipe() { RAMFill(start, stop); }

  /* Writes a nil-term CHA at the start of the string. */
  inline CH* Reset() {
    *start = 0;
    return start;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(CH* cursor) {
    start = cursor;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TSPrinter& Set(IUW* boofer) {
    IS size = *TPtr<IS>(boofer);
    IUW ptr = IUW(boofer) + sizeof(IS);
    CH* start_ptr = TPtr<CH>(ptr);
    start = start_ptr;
    stop = start_ptr + size - 1;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline void Set(const TSPrinter<CH, IS>& other) {
    start = other.start;
    stop = other.stop;
  }

  /* Finds the length of the STR in Chars. */
  inline IS SpaceLeft() { return (IS)(stop - start); }

  /* Calculates the max length of the string in Chars. */
  inline IS LengthMax() { return stop - start; }

  /* Prints a item to the string. */
  inline TSPrinter& PrintChar(CHA item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
  inline TSPrinter& PrintChar(CHB item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
  inline TSPrinter& PrintChar(CHC item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
  inline TSPrinter& Print(CHA item) { return PrintChar(item); }
  inline TSPrinter& Print(CHB item) { return PrintChar(item); }
  inline TSPrinter& Print(CHC item) { return PrintChar(item); }
  inline TSPrinter& Print(const CHA* item) {
    return Set(_::TSPrintString<CH>(start, stop, item));
  }
  inline TSPrinter& Print(const CHB* item) {
    return Set(_::TSPrintString<CH>(start, stop, item));
  }
  inline TSPrinter& Print(const CHC* item) {
    return Set(_::TSPrintString<CH>(start, stop, item));
  }
  inline TSPrinter& Print(ISC item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
  inline TSPrinter& Print(IUC item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
  inline TSPrinter& Print(ISD item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
  inline TSPrinter& Print(IUD item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
#if USING_FPC == YES_0
  inline TSPrinter& Print(FPC item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
#endif
#if USING_FPD == YES_0
  inline TSPrinter& Print(FPD item) {
    return Set(_::TSPrint<CH>(start, stop, item));
  }
#endif

  /* Prints the given pointer as hex. */
  inline TSPrinter& Hex(ISA item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(IUA item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(ISB item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(IUB item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(ISC item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(IUC item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(ISD item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
  inline TSPrinter& Hex(IUD item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
#if USING_FPC == YES_0
  inline TSPrinter& Hex(FPC item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
#endif
#if USING_FPD == YES_0
  inline TSPrinter& Hex(FPD item) {
    return Set(TSPrintHex<CH>(start, stop, item));
  }
#endif
  inline TSPrinter& Hex(const void* ptr) {
    return Set(TSPrintHex<CH>(start, stop, ptr));
  }
  inline TSPrinter& Binary(ISA item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(IUA item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(ISB item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(IUB item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(ISC item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(IUC item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(ISD item) {
    return Set(Binary<CH>(start, stop, item));
  }
  inline TSPrinter& Binary(IUD item) {
    return Set(Binary<CH>(start, stop, item));
  }
#if USING_FPC == YES_0
  inline TSPrinter& Binary(FPC item) {
    return Set(Binary<CH>(start, stop, item));
  }
#endif
#if USING_FPD == YES_0
  inline TSPrinter& Binary(FPD item) {
    return Set(Binary<CH>(start, stop, item));
  }
#endif
  /* Prints the given pointer as binary. */
  inline TSPrinter& Binary(const void* ptr) {
    IUW address = IUW(ptr);
    return Set(Binary<CH>(start, stop, address));
  }

  inline  TSPrinter<CH, IS>& Star() {}

  template<typename Printer>
  inline Printer& PrintTo(Printer& p) {
    p << "\nTSPrinter<CH" << sizeof(CH) << ", IS" << sizeof(IS) << ">{ start:";
    TPrintHex<Printer>(p, start);
    p << " stop:";
    TPrintHex<Printer>(p, stop);

    #if D_THIS
    // return TPrintChars<Printer, CH>(p, start, stop);
    #else
    return p << " }\n";
    #endif
  }
};

} // namesapce _

/* Prints the given item to the SPrinter.
@return The printer.
@param p    The printer.
@param item The item to printer. */
template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, CHA item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, const CHA* item) {
  return p.Print(item);
}

#if USING_UTF16 == YES_0
template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, CHB item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, const CHB* item) {
  return p.Print(item);
}
#endif
#if USING_UTF32 == YES_0
template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, CHC item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, const CHC* item) {
  return p.Print(item);
}
#endif

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, ISA item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, IUA item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, ISB item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, IUB item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, ISC item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, IUC item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, ISD item) {
  return p.Print(item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, IUD item) {
  return p.Print(item);
}

#if USING_FPC == YES_0
template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, FPC item) {
  return p.Print(item);
}
#endif

#if USING_FPD == YES_0
template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p, FPD item) {
  return p.Print(item);
}
#endif}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Binaryf item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

namespace _ {

/* Prints a summary of the type-value tuple with word-sized Data Type. */
template<typename Printer>
Printer& TPrint(Printer& p, ATypeValue item) {
  TPrintAType<Printer>(p, item.type);
  p << ':';
  TPrintATypeValue<Printer, DTW>(p, item.type, item->value);
  return p;
}

/* Prints an ASCII Type to the Printer. */
template<typename Printer>
Printer& TPrint(Printer& p, ATypef item) {
  return TPrintAType<Printer>(p, item.type);
}

// Prints a type and the binary with bit labels.
template<typename Printer>
Printer& TPrintATypeDebug(Printer& p, DTB type) {
  return p << "\nAType:" << ATypef(type)
           << "\n      0d" << type
           << "\n      0x" << Hexf(type)
           << "\n      0b" << Binaryf(type)
           << "\n        MD^MT ^SWVT^POD^";
}

} // namespace _

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Centerf item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Rightf item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Linef item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Hexf item) {
  return _::TSPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Charsf item) {
  return _::TSPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Sizef item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}


template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS> p,
                                         _::ATypef item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}
template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::ATypef item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::ATypeValue item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

template<typename CH, typename IS>
inline _::TSPrinter<CH, IS>& operator<<(_::TSPrinter<CH, IS>& p,
                                         _::Headingf item) {
  return _::TPrint<_::TSPrinter<CH, IS>>(p, item);
}

#endif
#endif
#endif
#endif