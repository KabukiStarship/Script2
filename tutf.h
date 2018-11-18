/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tutf.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__02
#ifndef INCLUDED_SCRIPT_TUTF
#define INCLUDED_SCRIPT_TUTF 1

#include "cutf.h"

#include "cascii.h"
#include "cconsole.h"
#include "ctest.h"
#include "tbinary.h"
#include "tobject.h"
#include "tsocket.h"

#if SEAM == _0_0_0__02
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

/* An empty strand. */
template <typename Char = char>
const Char* TStringEmpty() {
  static const Char kString[] = {'\0'};
  return kString;
}

/* The new-line strand. */
template <typename Char = char>
const Char* TStringNL() {
  static const Char kString[] = {'\n'};
  return kString;
}

/* String the reads "Error:". */
template <typename Char = char>
const Char* TStringError() {
  static const Char kString[] = {'\n', 'E', 'r', 'r', 'o', 'r', ':', '\0'};
  return kString;
}

/* Converts the given value to a printable char if it's non-printable. */
template <typename Char = char>
inline Char TPrintableChar(Char value) {
  if (value < 32 || value == 127) return ' ';
  return value;
}

/* Sets the strand to either the given value or empty strand if input
 * is nil. */
template <typename Char = char>
inline Char* TStringSet(Char* string) {
  if (!string) return TStringEmpty<Char>();
  return string;
}

/* Searches fro the strand line stop. */
template <typename Char = char>
const Char* TStringLineEnd(const Char* cursor, int column_count) {
  Char c;
  // Scroll to the stop of the line.
  c = *cursor++;
  while (c) {
    if (column_count-- < 0) {  // We've reached the stop.
                               // Scroll left till we hit whitespace (if any).
      while (!TIsWhitespace<Char>(c)) c = *(--cursor);
      // Then scroll past the whitespace.
      while (TIsWhitespace<Char>(c)) c = *(--cursor);
      return cursor;
      c = *cursor++;
    }
    c = *cursor++;
  }
  return cursor - 1;
}

/* Finds the stop of the line, wrapped to the given column_count.
@param column_coun In characters. */
template <typename Char = char>
const Char* TStringLineEnd(const Char* cursor, const Char* stop,
                           int column_count) {
  if (!cursor) {
    PRINTF("\nText buffer overflow!");
    return nullptr;
  }
  ASSERT(cursor < stop);
  Char c;
  // Scroll to the stop of the line.
  c = *cursor++;
  while (c) {
    if (stop > cursor) return nullptr;
    if (column_count-- < 0) {  // We've reached the stop.
      // Scroll left till we hit whitespace (if any).
      while (!TIsWhitespace<Char>(c)) c = *(--cursor);
      // Then scroll past the whitespace.
      while (TIsWhitespace<Char>(c)) c = *(--cursor);
      return cursor;
      c = *cursor++;
    }
    c = *cursor++;
  }
  return cursor - 1;
}

/* Finds the stop of the decimals in the strand, if there are any.
The stop of */
template <typename Char = char>
const Char* TStringDecimalEnd(const Char* cursor, const Char* stop) {
  ASSERT(cursor);
  ASSERT(cursor <= stop);
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

/* Skips the given Char in a strand if there are any.. */
template <typename Char = char>
const Char* TStringSkipChar(const Char* cursor, Char skip_char) {
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

template <typename Char = char>
Char* TStringSkipChar(Char* cursor, Char skip_char) {
  return const_cast<Char*>(TStringSkipChar<Char>(cursor, skip_char));
}

template <typename Char = char>
const Char* TStringSkipSpaces(const Char* cursor) {
  if (!cursor) return nullptr;
  Char c = *cursor;
  while (TIsWhitespace<Char>(c)) {
    PRINT('.');
    if (!c) return cursor;  //< This isn't an error as far as I can see.
    ++cursor;
    c = *cursor;
  }
  return cursor;
}

/* Attempts to find the given strand.
@return Nil upon failed search or a pointer to the stop of the . */
template <typename Char = char>
const Char* TStringFind(const Char* string, const Char* query) {
  ASSERT(string);
  ASSERT(query);

  Char strand = *string,  //< Current strand Char.
      t = *query,         //< Current query Char.
      c = t;              //< The first Char of the query we're searching for.
  if (c == 0)             //< We're not allowing empty queries.
    return nullptr;
  const Char *start_of_query, *start = string;
  query = TStringSkipSpaces<Char>(query);

  // Scroll through each Char and match it to the query Char.
  while (strand) {
    if (strand == c) {  // The first Char matches:
                        // Setup to compare the strings;
      start_of_query = string;
      start = query;
      t = c;
      // check the rest of the Char:
      while (strand == t) {
        strand = *(++string);
        t = *(++start);
        if (t == 0)  // Once we've reached the delimiter it's a match!
          return start_of_query;
        if (!strand)  // We've reached the stop of Char without a hit.
          return nullptr;
      }
    }
    // The Char did not match so repeat the process for each Char.
    strand = *(++string);
    t = *(++start);
  }
  // If we haven't found it by now it's not in the strand.
  return nullptr;
}

/* String skip spaces.
@return Nil if there are no spaces to skip. */
template <typename Char = char>
const Char* TStringSkipSpaces(const Char* cursor, const Char* stop) {
  if (!cursor) return nullptr;
  if (cursor > stop) return nullptr;
  PRINTF("\nSkipping spaces: ");
  Char c = *cursor;
  while (IsWhitespace(c)) {
    PRINT('.');
    if (!c) return nullptr;
    if (++cursor >= stop) return nullptr;
    c = *cursor;
  }
  return cursor;
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent strand upon success. */
template <typename Char = char>
const Char* TStringEquals(const Char* text_a, const Char* text_b) {
  ASSERT(text_a);
  ASSERT(text_b);
  PRINTF("\nComparing \"%s\" to \"%s\"", text_a, text_b);

  Char a = *text_a, b = *text_b;
  while (a) {
    PRINT(a);
    if (a != b) {  // Not a hit.
      PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      PRINTF("\nFound hit at 0x%p", text_a);
      return text_a;
    }
    a = *(++text_a);
    b = *(++text_b);
  }
  if (b) {
    PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  PRINTF("\nFound hit at 0x%p", text_a);
  return text_a;  //< Find hit!
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
strand upon success. */
template <typename Char = char>
const Char* TStringEquals(const Char* cursor, const Char* stop,
                          const Char* query) {
  if (!cursor) return nullptr;
  ASSERT(cursor < stop);
  if (!query) return nullptr;

  PRINTF("\nComparing \"%s\" to \"%s\"", cursor, query);

  Char a = *cursor, b = *query;
  while (a) {
    PRINT(a);
    if (a != b) {  // Not a hit.
      PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      PRINTF("\nFound hit at 0x%p", cursor);
      return cursor;
    }
    if (cursor > stop) {
      return nullptr;
    }
    a = *(++cursor);
    b = *(++query);
  }
  if (b) {
    PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  PRINTF("\nFound hit at 0x%p.", cursor);
  return cursor;
}

/* Checks if the given strand isn't empty.
@return False if the strand is empty and true otherwise.
@desc A strand is defined as empty if it is NIL or all whitespace. */
template <typename Char = char>
BOL TStringIsntEmpty(const Char* string) {
  if (!string) return false;
  Char c = *string;
  while (c) {
    if (!TIsWhitespace<Char>(c)) return true;
    c = *(++string);
  }
  return false;
}

/* Checks to see if the string isn't empty or whitespace. */
template <typename Char = char>
BOL TStringIsntEmpty(const Char* cursor, const Char* stop) {
  if (!cursor) return false;
  if (cursor > stop) return false;
  Char c = *cursor;
  while (c) {
    if (!TIsWhitespace<Char>(c)) {
      // The text must stop at or before the target_end.
      do {
        if (++cursor >= stop) return false;
        c = *cursor;
        if (!TIsWhitespace<Char>(c)) return true;
      } while (c);
      return true;
    }
    if (++cursor >= stop) return false;
    c = *cursor;
  }
  return false;
}

/* Skips all the chars in a given range. */
template <typename Char = char>
const Char* TStringSkipCharsInRange(const Char* cursor, Char lower_bounds,
                                    Char upper_bounds) {
  ASSERT(cursor);
  ASSERT(lower_bounds < upper_bounds);
  Char c = *cursor;
  while (c >= lower_bounds && c <= upper_bounds) c = *(++cursor);
  return cursor;
}

/* Skips the numbers in the given range. */
template <typename Char = char>
inline const Char* TStringSkipNumbers(const Char* cursor) {
  return TStringSkipCharsInRange<Char>(cursor, '0', '9');
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term char upon success.
@param  strand The begin of the begin.
@param  stop    The stop of the begin.
@param  token  The token to utf.
@param  column_count The number of columns to align right to. */
template <typename Char = char>
Char* TPrintRight(Char* cursor, Char* stop, const Char* token,
                  int column_count) {
  ASSERT(token);
  PRINTF("\ncursor:%p end:%p", cursor, stop);
  ASSERT(cursor <= stop);

  if (cursor == nullptr || column_count < 1) return nullptr;

  if (cursor + column_count > stop) {
    PRINT("\nBuffer overflow!");
    return nullptr;
  }

  const Char* token_end = TStringEnd<Char>(token);
  Char c;  //< Temp variable.
  if (token == token_end) return cursor;
  SIW length = token_end - token;

  PRINTF("\n\nPrinting \"%s\":%i aligned right %i columns", token, (int)length,
         column_count);

  // If the length is less than the column_count we need to utf ".", "..",
  // "..." or nothing and chop off some of the token.
  SIW count = column_count - length;
  if (count < 0) {
    if (count > -3) {
      PRINTF("\n Wrote dots:\"");
      while (count++ < 0) {
        *cursor++ = '.';
        PRINT('.');
      }
      PRINT('\"');
      *cursor = 0;
      return cursor;
    }
    stop = cursor + column_count;
    *stop-- = 0;
    *stop-- = '.';
    *stop-- = '.';
    *stop-- = '.';
    token_end = token + column_count - 4;
    PRINTF("\n Wrote with dots backwards:\"...");
    while (token_end >= token) {
      c = *token_end--;
      *stop-- = c;
      PRINT(c);
    }
    c = *token_end--;
    *stop-- = c;
    PRINT(c);
    PRINTF("\"");
    return cursor + column_count;
  }
  PRINTF("\ncursor:0x%p end:0x%p token:0x%p token_end:0x%p", cursor, stop,
         token, token_end);
  // In order to keep the current cache lines we're going to utf
  // backwards back from the token_end.
  PRINTF("\n Wrote backwards:\"");
  stop = cursor + column_count;
  --token_end;  //< This is pointed at the nil-term char
  *stop-- = 0;  //< and there is no need to load a 0.
  while (token_end >= token) {
    c = *token_end--;
    *stop-- = c;
    PRINT(c);
  }
  while (stop >= cursor) {
    *stop-- = ' ';
    PRINT(' ');
  }
  PRINTF("\"\nWrote:\"%s\"", cursor);
  return cursor + column_count;
}

/* Prints the given string center aligned to the given column_count. */
template <typename Char = char>
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string,
                   int column_count) {
  ASSERT(cursor);
  ASSERT(cursor < stop);

  // We need to leave at least one space to the left and right of
  int length = TStringLength<Char>(string), offset;
  PRINTF("\n\n    Printing \"%s\":%i column_count:%i", string, length,
         column_count);

  if (column_count < length) {
    offset = length - column_count;
    if (offset > 3) {
      offset = 3;
    }
    column_count -= offset;
    while (column_count-- > 0) {
      *cursor++ = *string++;
    }
    while (offset-- > 0) {
      *cursor++ = '.';
    }
    *cursor = 0;
    return cursor;
  }
  offset = (column_count - length) >> 1;  //< >> 1 to /2
  length = column_count - length - offset;
  PRINTF("\n    length:%i offset:%i", length, offset);

  while (length-- > 0) *cursor++ = ' ';

  char c = *string++;
  while (c) {
    *cursor++ = c;
    c = *string++;
  }
  while (offset-- > 0) *cursor++ = ' ';
  *cursor = 0;
  PRINTF("\n    Printed:\"%s\"", string);
  return cursor;
}

/* Prints a line of the given column_count the given begin. */
template <typename Char = char>
Char* TPrintLine(Char* cursor, Char* stop, Char token, int column_count) {
  ASSERT(cursor);
  ASSERT(cursor < stop);
  int l_column_count = column_count;
  if (cursor + l_column_count + 1 >= stop) return nullptr;

  *cursor++ = '\n';

  while (l_column_count-- > 0) *cursor++ = token;

  *cursor = 0;
  return cursor;
}

/* Prints the given string repeated to make a line. */
template <typename Char = char>
Char* PrintLineString(Char* cursor, Char* stop, const Char* string,
                      int column_count) {
  ASSERT(cursor);
  ASSERT(cursor < stop);
  if (cursor + column_count + 1 > stop) return nullptr;

  while (column_count-- > 0) {
    char c = *string++;
    if (!c) {
      cursor = 0;
    }
    *cursor++ = c;
  }
  *cursor = 0;
  return cursor;
}

/* Prints the given socket to the COut. */
template <typename Char = char>
Char* TPrintSocket(Char* cursor, Char* stop, const void* begin,
                   const void* end) {
  ASSERT(begin);
  ASSERT(cursor);
  ASSERT(cursor < stop);

  Char* buffer_begin = cursor;
  const Char *address_ptr = reinterpret_cast<const Char*>(begin),
             *address_end_ptr = reinterpret_cast<const Char*>(end);
  size_t size = address_end_ptr - address_ptr,
         num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - cursor) <= num_bytes) {
    PRINTF("\n    ERROR: buffer overflow trying to fit %i in %i bytes!",
           (int)num_bytes, (int)(stop - cursor));
    return nullptr;
  }
  size += num_bytes;
  *cursor++ = '\n';
  *cursor++ = '|';

  //  columns
  *cursor++ = '0';
  cursor = TPrintRight<Char>(cursor, stop, Utf8Text(8).String(), 8);
  *cursor++ = ' ';
  for (int i = 16; i <= 56; i += 8)
    cursor = PrintRight(cursor, stop, Utf8Text(i).String(), 8);
  for (int j = 6; j > 0; --j) *cursor++ = ' ';
  *cursor++ = '|';
  *cursor++ = '\n';
  *cursor++ = '|';
  for (int j = 8; j > 0; --j) {
    *cursor++ = '+';
    for (int k = 7; k > 0; --k) *cursor++ = '-';
  }
  *cursor++ = '|';
  *cursor++ = ' ';

  cursor = TPrintHex<Char>(cursor, stop, reinterpret_cast<UIW>(address_ptr));

  PRINTF("\nBuffer space left:%i", (int)(stop - cursor));
  Char c;
  while (address_ptr < address_end_ptr) {
    *cursor++ = '\n';
    *cursor++ = '|';
    for (int i = 0; i < 64; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (!c || c == TAB)
        c = ' ';
      else if (c < ' ')
        c = DEL;
      *cursor++ = c;
    }
    *cursor++ = '|';
    *cursor++ = ' ';
    cursor = TPrintHex<Char>(cursor, stop, reinterpret_cast<UIW>(address_ptr));
  }
  *cursor++ = '\n';
  *cursor++ = '|';
  for (int j = 8; j > 0; --j) {
    *cursor++ = '+';
    for (int k = 7; k > 0; --k) {
      *cursor++ = '-';
    }
  }
  *cursor++ = '|';
  *cursor++ = ' ';
  return TPrintHex<Char>(cursor, stop,
                         reinterpret_cast<UIW>(address_ptr) + size);
}

/* . */
template <typename Char = char>
Char TLowercase(Char c) {
  if ((c & 0x3f) == 3) return c - 64;
  return c;
}

/* A UTF-8, UTF-16, or UTF-32 Text token without any whitespace. */
template <typename Char = char>
class TToken {
 public:
  /* Default constructor does nothing. */
  TToken() { *string = 0; }

  /* Prints the value to the text begin. */
  TToken(Char character) { TPrint<Char>(string, string + kSize, character); }

  /* Prints the value to the text begin. */
  TToken(const Char* string) { TPrint<Char>(string, string + kSize, string); }

  /* Prints the value to the text begin. */
  TToken(SI4 value) { TPrint<Char>(string, string + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(UI4 value) { TPrint<Char>(string, string + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(SI8 value) { TPrint<Char>(string, string + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(UI8 value) { TPrint<Char>(string, string + kSize, value); }

#if SEAM >= _0_0_0__03
  /* Prints the value to the text begin. */
  TToken(FLT value) { TPrint<Char>(string, string + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(DBL value) { TPrint<Char>(string, string + kSize, value); }
#endif
  /* Gets the number strand. */
  const Char* String() { return string; }

 private:
  enum { kSize = 31 };

  Char string[kSize * sizeof(Char) + 1];  //< String begin.
};

/* Utility class for printing hex with operator<<. */
template <typename Char = char>
class TCenter {
 public:
  /* Prints the value to the text begin. */
  TCenter(const Char* string, int column_count)
      : string(TStringSet<Char>(string)), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(SI4 value, int column_count)
      : string(nullptr), number(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(UI4 value, int column_count)
      : string(nullptr), number(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(SI8 value, int column_count)
      : string(nullptr), number(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(UI8 value, int column_count)
      : string(nullptr), number(value), column_count(column_count) {
    // Nothing to do here!
  }

#if SEAM >= _0_0_0__03
  /* Prints the value to the text begin. */
  TCenter(FLT value, int column_count)
      : string(nullptr), number(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(DBL value, int column_count)
      : string(nullptr), number(value), column_count(column_count) {
    // Nothing to do here!
  }
#endif

  /* Gets the number strand. */
  const Char* String() { return string; }

  /* Gets the column_count. */
  int GetColumnCount() { return column_count; }

 private:
  const Char* string;   //< Pointer to the strand.
  TToken<Char> number;  //< Pointer to a pointer to utf.
  int column_count;     //< Number of columns to center.
};

/* Utility class for printing hex with operator<<. */
template <typename Char = char>
class TRight {
 public:
  /* Prints the value to the text begin. */
  TRight(const Char* string, int column_count)
      : string_(TStringSet<Char>(string)), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(SI4 value, int column_count)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(UI4 value, int column_count)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(SI8 value, int column_count)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(UI8 value, int column_count)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

#if SEAM >= _0_0_0__03
  /* Prints the value to the text begin. */
  TRight(FLT value, int column_count)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(DBL value, int column_count)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }
#endif
  /* Gets the number strand. */
  const Char* String() { return string_; }

  /* Gets the column_count. */
  int GetColumnCount() { return column_count_; }

 private:
  const Char* string_;   //< Pointer to the strand.
  TToken<Char> number_;  //< Pointer to a pointer to utf.
  int column_count_;     //< Number of columns to center.
};

/* Utility class for printing a single Char token line with operator<<. */
template <typename Char = char>
struct API TLine {
  Char token;        //< Character to utf.
  int column_count;  //< Column count.

  /* Constructor. */
  TLine(Char token, int column_count)
      : token(token), column_count(column_count) {}
};

/* Utility class for printing a strand line with operator<<. */
template <typename Char = char>
struct API TLineString {
  const Char* string;  //< Character to utf.
  int column_count;    //< Column count.

  /* Constructor. */
  TLineString(const Char* string, int column_count)
      : string(string), column_count(column_count) {}
};

/* AsciiFactory prints the begin to the console without deleting the
begin.
@return If (size == 0 && begin) then nil indicating success deleting the
factory. If passing in a argument it will have to get passed through the obj.
*/
template <typename Size = int, typename Char = char>
UIW* TCOut(UIW* start, SIW function, void* arg) {
  if (function < kFactoryClone)
    return TObjectFactory<Size>(start, function, arg);

  if (!start) {
    if (!arg) return nullptr;
    Size size = *reinterpret_cast<Size*>(arg);
    if (size <= 0) size = (Size)kObjSizeDefault;
  }

  Size size = *reinterpret_cast<Size*>(arg);
  if (size > 0) {
    size = TObjSizeRound<Size>(size);
  }
  if (start) return TObjClone<Size>(start);
  UIW address = reinterpret_cast<UIW>(start) + sizeof(Size);
  Print(reinterpret_cast<const char*>(address));
  return start;
}

/* AsciiFactory prints the begin to the console and deletes the
begin. */
template <typename Size = int, typename Char = char>
UIW* TCOutAuto(UIW* start, SIW function, void* arg) {
  UIW* result = TCOut<Char, Size>(start, function, arg);
  if (!start) return result;
  delete[] start;
  return nullptr;
}

/* Returns the first char in the string socket. */
template <typename Char = char, typename Size = int>
inline Char* TStringStart(UIW* start) {
  ASSERT(start);
  UIW address = reinterpret_cast<UIW>(start) + sizeof(Size);
  return reinterpret_cast<Char*>(address);
}

/* Searches for the stop of the strand. */
template <typename Char = char, typename Size = int>
inline Char* TStringStop(UIW* start) {
  ASSERT(start);

  UIW address = reinterpret_cast<UIW>(start) + sizeof(Size);
  Size size = *reinterpret_cast<Size*>(start);
  // Char* begin = reinterpret_cast<Char*>(address);
  return reinterpret_cast<Char*>(address) + (size >> TBitShiftCount<Size>()) -
         1;
}

/* Searches for the stop of the strand. */
template <typename Char = char, typename Size = int>
inline void TStringStop(CObject obj) {
  return TStringStop<Char, Size>(obj);
}

/* Universal Text Formatter.
This class only stores the stop of begin pointer and a pointer to the write
begin. It is up the user to store begin of begin pointer and if they would
like to replace the begin with the beginning of begin pointer when they are
done printing. */
template <typename Char = char, typename Size = intptr_t>
struct TUTF {
  Char *start,  //< Write begin pointer.
      *stop;    //< End of begin pointer.

  /* Initializes the Utf& from the given begin pointers.
  @param begin The beginning of the begin.
  @param stop   The stop of the begin. */
  TUTF(Char* start, Size size)
      : start(start), stop(TPtr<Char>(start, size - 1)) {
    ASSERT(start);
    ASSERT(ObjSizeIsValid<Size>(size, 8));
  }

  /* Initializes the Utf& from the given begin pointers.
  @param begin The beginning of the begin.
  @param stop   The stop of the begin. */
  TUTF(UIW* start, Size size)
      : start(reinterpret_cast<Char*>(start)),
        stop(TPtr<Char>(start, size - 1)) {
    ASSERT(start);
    ASSERT(ObjSizeIsValid<Size>(size, 8));
  }

  /* Initializes the Utf& from the given begin pointers.
  @param begin The beginning of the begin.
  @param stop   The stop of the begin. */
  TUTF(Char* start, Char* stop) : start(start), stop(stop) {}

  /* Constructs a UTF from the given ASCII Object Buffer. */
  TUTF(UIW* obj)
      : start(reinterpret_cast<Char*>(obj)),
        stop(reinterpret_cast<Char*>(obj) + *reinterpret_cast<Size*>(obj) - 1) {
  }

  /* Clones the other utf. */
  TUTF(const TUTF& other)
      : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  /* Sets the begin pointer to the new_pointer. */
  inline TUTF& Set(Char* new_pointer) {
    if (!new_pointer) return *this;
    start = new_pointer;
    return *this;
  }

  /* Sets the begin pointer to the new_pointer. */
  inline TUTF& Set(UIW* new_pointer) {
    return Set(reinterpret_cast<Char*>(new_pointer));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI1 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI1 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI2 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI2 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI4 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI4 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI8 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI8 value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

#if SEAM >= _0_0_0__03
  /* Prints the given value as hex. */
  inline TUTF& Hex(FLT value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(DBL value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }
#endif

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(const void* value) {
    return Set(TPrintHex<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI1 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI1 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI2 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI2 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI4 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI4 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI8 value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI8 value) {
    return Set(Binary<Char>(start, stop, value));
  }

#if SEAM >= _0_0_0__03
  /* Prints the given value as binary. */
  inline TUTF& Binary(FLT value) {
    return Set(Binary<Char>(start, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(DBL value) {
    return Set(Binary<Char>(start, stop, value));
  }
#endif
  /* Prints the given pointer as binary. */
  inline TUTF& Binary(const void* value) {
    return Set(Binary<Char>(start, stop, value));
  }
};

/* A Unicode String ASCII Object.
template <typename Char, typename Size>
struct TString {
  Size size;  //< Size of the ASCII Object.

  TString () { *Begin () = 0; }

  TString (const char* init) {
    Char* begin = Begin ();
    TPrint<Char> (begin, begin + );
  }


  Char* Start () {
    return reinterpret_cast<Char*> (reinterpret_cast<UIW>(this) + sizeof (Size)
      );
  }
}; */

template <typename Size, typename Char>
Char* TStrandInit(UIW* obj, Size size) {
  ASSERT(obj);
  ASSERT(size > 0);
  ASSERT((size & kWordBitsMask) == 0);
  *reinterpret_cast<UIW*>(obj) = size;
  return reinterpret_cast<Char*>(reinterpret_cast<UIW>(obj) + sizeof(Size));
}

/* A ASCII Factory String that can auto-grow from the obj to the heap.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string of overloads, the objects get destructed
in the opposite order then where called, which is a obj push pop operation.
For this reason the factory is programmable.

# Statically Allocated Strings

If it is null then the factory is treated as statically allocated factory.

@code
TStrand<> (TCOut<>) << "Hello world!";
@endcode

# Dynamic Allocated Strings

Strings that use dynamic memory use the DCOutAuto factory:

@code
TStrand<UI4> (TCOutAuto<>) << "Hello world!";
@endcode
*/
template <typename Size = int, typename Char = char, SIW kLengthMax_ = 64>
class TStrand : public TUTF<Char> {
 public:
  enum {
    kLengthMax =
        kLengthMax_,  //< Max length of a string that can fit in the socket_.
    kSize = kLengthMax * sizeof(Char),  //< The size of the strand in bytes.
  };

  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory ASCII Factory to call when the Strand overflows. */
  TStrand(AsciiFactory factory = TCOutAuto<Char>)
      : TUTF<Char>(TStrandInit<Size, Char>(socket_.Words(), socket_.kSize),
                   socket_.Begin() + kLengthMax - 1),
        obj_(socket_.Words (), factory) {
    _::Printf("\nTStrand(AsciiFactory factory)"
      "\nsocket_.Begin():0x%p socket_.End():0x%p"
      "\nTUTF<Char>::start:0x%p TUTF<Char>::stop:0x%p"
      "\nsizeof(Size):%i Char count max:%i end space:%i\n",
      socket_.Begin (), socket_.End (), TUTF<Char>::stop, TUTF<Char>::start,
      (int)(reinterpret_cast<UIW> (TUTF<Char>::start) - reinterpret_cast<UIW>(socket_.Begin ())),
      (int)(TUTF<Char>::stop - TUTF<Char>::start),
      (int)(reinterpret_cast<UIW> (socket_.End ()) - reinterpret_cast<UIW>(TUTF<Char>::stop)));
    Terminate();
  }

  /* Constructs a strand from dynamic memory.
  @param size    Object size IN BYTES.
  @param factory Non-nil ASCII Factory. */
  TStrand(Size size, AsciiFactory factory = TCOutAuto<Char>) {
    _::Print(__FUNCTION__);
    ASSERT(factory);
    UIW* socket = factory(nullptr, size, nullptr);
    obj_.Set(socket, factory);
    obj_.SetBegin(socket);
    TUTF<Char>::Set(socket, size);
    Terminate();
  }

  /* Constructs the pointers to the buffer_.
  @param begin   Buffer begin address.
  @param size    Object size IN BYTES.
  @param factory ASCII Factory.  */
  TStrand(UIW* begin, Size size, AsciiFactory factory = nullptr)
      : TUTF<Char>(begin, size), obj_(size, begin, factory) {
    _::Print(
        "\nTStrand(UIW* begin, Size size, AsciiFactory factory = nullptr)");
    ASSERT(begin);
    Terminate();
  }

  /* Gets the UTF. */
  TUTF<Char> Print() {
    Size size = TObjSize<Size>(obj_);
    Char* start_ptr = reinterpret_cast<Char*>(
        reinterpret_cast<UIW>(obj_.start) + sizeof(Size));
    return TUTF<Char>(start_ptr, start_ptr + (size >> TBitShiftCount<Size>()));
  }

  /* Prints a char to the strand.
  @param item The item to utf.
  @return A UTF. */
  template <typename T>
  TUTF<Char> Print(T item) {
    UIW start = reinterpret_cast<UIW>(obj_.Begin());
    Size size = *reinterpret_cast<Size*>(start);
    ASSERT((size & kAlignMask) == 0);
    Char *cursor = reinterpret_cast<Char*>(start + sizeof(Size)),
         *stop = cursor + (size >> TBitShiftCount<Size>()) - 1;
    cursor = TPrint<Char>(cursor, stop, item);
    if (!cursor) return TUTF<Char>(reinterpret_cast<Char*>(start), stop);
    return TUTF<Char>(cursor, stop);
  }

  /* Prints a char to the strand.
  @return A UTF. */
  inline TUTF<Char> Print(Char c) { return TPrint<Char>(c); }

  /* Prints a char to the strand.
  @return A UTF. */
  inline TUTF<Char> Print(const Char* string) {
    return Print<const Char*>(string);
  }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(SI4 value) { return TPrint<SI4>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(UI4 value) { return TPrint<UI4>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(SI8 value) { return TPrint<SI8>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(UI8 value) { return TPrint<UI8>(value); }

#if SEAM >= _0_0_0__03
  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(FLT value) { return TPrint<FLT>(value); }

  /* Prints the given value.
  @return A UTF. */
  inline TUTF<Char> Print(DBL value) { return TPrint<DBL>(value); }
#endif

  /* Returns the stop of the begin. */
  inline Char* Stop() { return TStringStop<Char, Size>(obj_.Begin()); }

  /* Returns the stop of the begin. */
  inline char* End() { return TObjEnd<Size>(obj_); }

  /* Writes a nil-term char at the stop of the strand. */
  inline void Terminate() {
    *Stop() = 0;
  }

  /* Gets the begin of the Console begin. */
  inline TObject<Size>& Obj() { return obj_; }

 private:
  TObject<Size> obj_;      //< ASCII Obj.
  TSocket<kSize> socket_;  //< An optional socket for obj-to-heap growth.
};

using Strand1 = TStrand<char>;
using Strand2 = TStrand<char16_t>;
using Strand4 = TStrand<char32_t>;

/* Prints the given AsciiFactory. */
template <typename Char = char>
TUTF<Char> Print(AsciiFactory factory) {
  return TStrand<Char>(factory);
}

/* Queries the given strand for the given query. */
template <typename Char = char>
int StringQuery(const Char* cursor, const Char* stop, const Char* query) {
  Char a = *cursor, b = *query;
  int result;

  if (!cursor) {
    if (!query) return 0;
    a = 0;
    b = *query;
    return b - a;
  }
  if (!query) {
    a = *cursor;
    b = 0;
    return b - a;
  }
  if (cursor > stop) return *query;

  // Algorithm combines loops for better performance.
  a = *cursor;
  b = *query;
  if (!a) {
    if (!b) return 0;
    return b;
  }
  if (!b) {
    if (!a) return 0;
    return 0 - a;
  }
  // text SHOULD be a nil-terminated strand without whitespace.
  while (b) {
    result = b - a;
    if (result) {
      PRINTF(" is not a hit.");
      return result;
    }
    if (!a) {
      PRINTF(" is a partial match but !a.");
      return result;
    }
    if (++cursor >= stop) {
      PRINTF(" but buffer overflowed!");
      return result;
    }
    ++query;
    a = *cursor;
    b = *query;
  }
  if (a && !TIsWhitespace<Char>(a)) {
    PRINTF(" is only a partial match but found %s", (a ? "a" : "space"));
    return b - a;
  }
  PRINTF(" is a match!");
  return 0;
}

/* Returns the static default printer that doesn't work in multi-threaded or
interrupt situations.
If you are using more than one thread or interrupts, the*/
template <typename Char = char>
TUTF<Char> TCOut() {
  static TUTF<Char> serial_out(TCOut<Char>);
  return serial_out;
}

}  // namespace _

/* Writes a nil-terminated UTF-8 or ASCII strand to the utf.
@return The utf.
@param  utf The utf.
@param  value   The value to utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, const Char* string) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, string));
}

/* Writes a nil-terminated UTF-8 or ASCII strand to the utf.
@return The utf.
@param  utf The utf.
@param  value   The value to utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TStrand<Char>& utf, const Char* string) {
  Char* start = utf.start,
    *stop = utf.stop,
    * cursor = 0;
  if (!start || !stop) return utf;
  try {
    while (!cursor) {
      cursor = _::TPrint<Char> (start, stop, string);
    }
  }
  catch (...) {}
  return utf;
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value   The value to utf.
@return The utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, Char c) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, c));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI1 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI2 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI2 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI4 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value)fd);
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI4 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI8 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI8 value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

#if SEAM >= _0_0_0__03
/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, FLT value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, DBL value) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, value));
}
#endif

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  item The item to write to utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TCenter<Char> item) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, item));
}

/* Writes the given value to the utf justified right.
@return The utf.
@param  utf The utf.
@param  item The item to utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TRight<Char> item) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, item));
}

/* Prints a line of the given column_count to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TLine<Char> line) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, line));
}

/* Prints a line strand of the given column_count to the utf. */
template <typename Char = char>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TLineString<Char> line) {
  return utf.Set(_::TPrint<Char>(utf.start, utf.stop, line));
}

#endif  //< #if INCLUDED_SCRIPT_TUTF
#endif  //< #if SEAM >= _0_0_0__02
