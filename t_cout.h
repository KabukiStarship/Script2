/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_cout.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#ifndef SCRIPT2_COUT
#define SCRIPT2_COUT 1

#include "c_binary.h"
#include "c_cout.h"
#include "t_string.h"

namespace _ {

#ifndef SCRIPT2
enum {
  NIL = 0,
  kLF = '\n',
};
#endif

template <typename Char>
void TPrintString(const Char* string) {
  if (!string) return;
  Char c = *string;
  while (c) {
    Print(c);
    c = *(++string);
  }
}
template <typename Char>
void TPrintRepeat(Char c, SI4 count) {
  for (; count > 0; --count) Print(c);
}

template <typename Char>
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
template <typename Char>
const Char* TPrintLinef(const Char* style = nullptr, SI4 column_count = 80) {
  enum {
    kBreakCount = 3,
  };
  if (!style) style = TSTRLinef<Char>();
  if (column_count < kBreakCount) return nullptr;

  Char c = *style++,  //< Current.
      p = ~c;         //< Previous.
  SI4 hit_count = 0, column_index = 0;
  while (c) {
    Print(c);
    ++column_index;
    if (c == kLF) {
      p = c;
      do {
        c = *style++;
        Print(c);
      } while (c == kLF);
      column_index = 0;
    }
    if (c == p && !TIsWhitespace<Char>(c)) {
      ++hit_count;
      if (hit_count >= kBreakCount - 1) {
        TPrintRepeat<Char>(c, column_count - column_index);
        column_index = hit_count = 0;
      }
    }
    p = c;
    c = *style++;
  }
  return style;
}

template <typename Char>
void TPrintLinef(Char token = '-', SI4 column_count = 80) {
  PrintChar(kLF);
  TPrintRepeat<Char>(token, column_count);
  PrintChar(kLF);
}

template <typename Char>
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
template <typename Char>
void TPrintHeadingf(const Char* caption, const Char* style = nullptr,
                    SI4 column_count = 80, const Char* caption2 = nullptr,
                    const Char* caption3 = nullptr) {
  if (!style) style = TSTRHeadingf<Char>();
  style = TPrintLinef<Char>(style, column_count);
  if (!style) return;
  Print(caption);
  if (caption2) Print(caption2);
  if (caption3) Print(caption3);
  TPrintLinef<Char>(style, column_count);
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Char = CH1>
void TPrintRight(const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1) return;

  const Char* token_end = TSTREnd<Char>(item);
  if (item == token_end) return;
  SIW length = token_end - item, space_count = column_count - length;

  if (space_count > 0) {
    while (space_count-- > 0) Print(' ');
    Print(item);
    return;
  }
  length = (-length) - 3;
  if (length < 0) {
    switch (length) {
      case 1:
        Print('.');
      case 2:
        Print('.', '.');
      case 3:
        Print('.', '.', '.');
    }
  } else {
    while (length > 0) Print(*item++);
    Print('.', '.', '.');
  }
}

/* Prints the given token aligned center the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Char = CH1>
void TPrintCenter(const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1) return;

  const Char* token_end = TSTREnd<Char>(item);
  if (item == token_end) return;
  SIW length = token_end - item, space_count = column_count - length;

  if (space_count > 0) {
    SIW half_count = space_count >> 1;
    space_count -= half_count;
    while (half_count-- > 0) Print(' ');
    Print(item);
    while (space_count-- > 0) Print(' ');
    return;
  }
  length = (-length) - 3;
  if (length < 0) {
    if (length == 1)
      Print('.');
    else if (length == 2)
      Print('.', '.');
    else if (length == 3)
      Print('.', '.', '.');
  } else {
    while (length > 0) Print(*item++);
    Print('.', '.', '.');
  }
}

template <typename UI>
void TPrintBinary(UI value) {
  enum { kSize = sizeof(UI) * 8 };

  for (SI4 i = kSize; i > 0; --i) {
    CH1 c = (CH1)('0' + (value >> (kSize - 1)));
    Print(c);
    value = value << 1;
  }
}

template <typename SI, typename UI>
void TPrintBinarySigned(SI value) {
  return TPrintBinary<UI>((UI)value);
}

/* Prints the following value to the console in Hex. */
template <typename UI>
void TPrintHexConsole(UI value) {
  enum { kHexStrandLengthSizeMax = sizeof(UI) * 2 + 3 };
  for (SI4 num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4)
    Print(HexNibbleToUpperCase((UI1)(value >> num_bits_shift)));
}

template <typename Char>
void TPrintChars(const Char* start, const Char* stop) {
  if (!start || start >= stop) return;
  SIW size = stop - start, extra_row = ((size & 63) != 0) ? 1 : 0,
      row_count = (size >> 6) + extra_row;

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;
  Print(StrandSocketHeader());
  Print(StrandSocketBorder());

  PrintHex(start);

  Char c;
  while (start < stop) {
    PrintNL();
    Print('|');
    for (SI4 i = 0; i < 64; ++i) {
      c = *start++;
      if (start > stop)
        c = 'x';
      else if (c < ' ')
        c = c + kPrintC0Offset;
      PrintChar(c);
    }
    Print('|', ' ');
    PrintHex(start);
  }
  Print(StrandSocketBorder());
  PrintHex(start + size);
}

template <typename Char>
void TPrintChars(const Char* start, SIW count) {
  return TPrintChars(start, start + count);
}

}  // namespace _

#endif
