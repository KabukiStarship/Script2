/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_cout.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#ifndef SCRIPT2_COUT
#define SCRIPT2_COUT 1

#include "c_binary.h"
#include "c_cout.h"

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

template <typename Char>
const Char* TPrintLineffDefault() {
  static const Char kString[] = {'\n', '-', '-', '-', NIL};
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
const Char* TPrintLinef(const Char* style = TPrintLineffDefault<Char>(),
                        SI4 column_count = 80) {
  enum {
    kBreakCount = 3,
  };
  if (!style || column_count < kBreakCount) return nullptr;

  Char c = *style++,  //< Current.
      p = ~c;         //< Previous.
  SI4 hit_count = 0, column_cursor = 0;
  while (c) {
    while (c == '\n') {
      Print(c);
      p = c;
      c = *style++;
    }
    if (c == p) {
      ++hit_count;
      if (hit_count >= kBreakCount) {
        hit_count = 0;
        for (SI4 i = column_count - column_cursor; i > 0; --i) Print(c);
        column_cursor = 0;
      }
    } else {
      Print(c);
      ++column_cursor;
    }
    p = c;
    c = *style++;
  }
  return ++style;
}

template <typename Char>
const Char* TPrintLine(Char token = '-', SI4 column_count = 80) {
  Char style[4];
  Char* cursor = style;
  *cursor++ = token;
  *cursor++ = token;
  *cursor++ = token;
  *cursor++ = 0;
  return TPrintLinef(style, column_count);
}

/* Prints an easy-to-read text heading with a formatting options.
@code
TPrintHeadingf<CH1> ("\n+---\0\n+---", 80, "Foo ", "Bar ",
                     TToken<CH1> (420).String ());
@endcode
*/
template <typename Char>
void TPrintHeadingf(const Char* caption,
                    const Char* style = THeadingfDefault<Char>(),
                    SI4 column_count = 80, const Char* caption2 = nullptr,
                    const Char* caption3 = nullptr) {
  if (!caption || !style) return;
  style = TPrintLinef(style, column_count);
  if (!style) return;
  Print(caption);
  if (!caption2) Print(caption2);
  if (!caption3) Print(caption3);
  return TPrintLinef(style, column_count);
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Char = CH1>
void TPrintRight(const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1) return;

  auto token_end = StrandEnd(item);
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

  auto token_end = StrandEnd(item);
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
    TPrintHeadingf<Char>('.', 3);
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
    Print('\n');
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
