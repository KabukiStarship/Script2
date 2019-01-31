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

#include "c_cout.h"
#include "c_binary.h"

namespace _ {

template <typename Char>
void TPrintStrand (const Char* string) {
  if (!string) return;
  Char c = *string;
  while (c) {
    Print (c);
    c = *(++string);
  }
}

template<typename Char>
void TPrintRepeat (Char token, SI4 count) {
  while (count-- > 0) Print (token);
}

template<typename Char>
void TPrintRepeat (const CH1* string, SI4 count, CH1 delimiter) {
  const CH1* cursor = string;
  CH1 c = *cursor++;
  if (!c) return;
  Print (c);
  do {
    CH1 c = *cursor++;
    if (!c) {
      cursor = string;
      c = *cursor++;
    }
    if (delimiter) Print (delimiter);
  } while (--count > 0);
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Char = CH1>
void TPrintRight (const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1)
    return;

  auto token_end = StrandEnd (item);
  if (item == token_end) return;
  SIW length = token_end - item,
    space_count = column_count - length;
  
  if (space_count > 0) {
    while (space_count-- > 0) Print (' ');
    Print (item);
    return;
  }
  length = (-length) - 3;
  if (length < 0) {
    if (length == 1) Print ('.');
    else if (length == 2) TPrintRepeat ('.', 2);
    else if (length == 3) TPrintRepeat ('.', 3);
  } else {
    while (length > 0) Print (*item++);
    TPrintRepeat<Char> ('.', 3);
  }
}

/* Prints the given token aligned center the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Char = CH1>
void TPrintCenter (const Char* item, SI4 column_count = 80) {
  if (!item || column_count < 1)
    return;

  auto token_end = StrandEnd (item);
  if (item == token_end) return;
  SIW length = token_end - item,
    space_count = column_count - length;
  
  if (space_count > 0) {
    SIW half_count = space_count >> 1;
    space_count -= half_count;
    while (half_count-- > 0) Print (' ');
    Print (item);
    while (space_count-- > 0) Print (' ');
    return;
  }
  length = (-length) - 3;
  if (length < 0) {
    if (length == 1) Print ('.');
    else if (length == 2) TPrintRepeat ('.', 2);
    else if (length == 3) TPrintRepeat ('.', 3);
  } else {
    while (length > 0) Print (*item++);
    TPrintRepeat<Char> ('.', 3);
  }
}

template<typename Char>
void TPrintLine (Char token, SI4 column_count, Char first_token) {
  Print ('\n');
  if (column_count > 1) Print (first_token);
  while (column_count-- > 0) Print (token);
}

template<typename Char>
void TPrintLine (const Char* token, SI4 column_count, Char first_token) {
  Print ('\n');
  if (column_count > 1) Print (first_token);
  while (column_count-- > 0) Print (token);
}

template<typename Char>
void TPrintHeading (const Char* heading_a, const Char* heading_b, SI4 row_count,
  SI4 column_count, Char token, Char first_token) {
  if (row_count < 1 || column_count < 1)
    while (row_count-- > 0) Print ('\n');
  PrintLine (token, column_count, '+');
  Print ("\n| ");
  Print (heading_a);
  Print (heading_b);
  PrintLine (token, column_count, '+');
  Print ('\n');
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

template<typename Char>
void TPrintChars(const Char* start, const Char* stop) {
  if (!start || start >= stop) return;
  SIW size = stop - start,
      extra_row = ((size & 63) != 0) ? 1 : 0,
      row_count = (size >> 6) + extra_row;

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;
  Print(StrandSocketHeader ());
  Print(StrandSocketBorder ());

  PrintHex(start);

  Char c;
  while (start <= stop) {
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
  Print (StrandSocketBorder ());
  PrintHex(start + size);
}

}  // namespace _

#endif
