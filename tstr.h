/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tstr.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__03
#ifndef SCRIPT2_TUTF
#define SCRIPT2_TUTF 1

#include "cstr.h"

#include "cascii.h"
#include "cconsole.h"
#include "ctest.h"
#include "tbinary.h"
#include "tobject.h"

#if SEAM == _0_0_0__03
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

/* Initializes an ASCII String. */
template <typename Size, typename Char>
inline Char* TStringInit(UIW* obj, Size size) {
  UIW address = reinterpret_cast<UIW>(TObjInit<Size>(obj, size));
  return reinterpret_cast<Char*>(address + sizeof(Size));
}

/* An empty string. */
template <typename Char = CH1>
const Char* TStringEmpty() {
  static const Char kString[] = {'\0'};
  return kString;
}

/* The new-line s. */
template <typename Char = CH1>
const Char* TStringNL() {
  static const Char kString[] = {'\n'};
  return kString;
}

/* String the reads "Error:". */
template <typename Char = CH1>
const Char* TStringError() {
  static const Char kString[] = {'\n', 'E', 'r', 'r', 'o', 'r', ':', '\0'};
  return kString;
}

/* Converts the given value to a printable CH1 if it's non-printable. */
template <typename Char = CH1>
inline Char TPrintableChar(Char value) {
  if (value < 32 || value == 127) return ' ';
  return value;
}

/* Sets the s to either the given value or empty s if input
is nil. */
template <typename Char = CH1>
inline Char* TStringSet(Char* string_) {
  if (!string_) return TStringEmpty<Char>();
  return string_;
}

/* Searches fro the s line stop.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
const Char* TStringLineEnd(const Char* cursor, int column_count = 80) {
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

/* Searches fro the s line stop.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
Char* TStringLineEnd(Char* cursor, int column_count = 80) {
  return const_cast<Char*>(
      TStringLineEnd(reinterpret_cast<const Char*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CH1>
const Char* TStringLineEnd(const Char* cursor, const Char* stop,
                           int column_count = 80) {
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

/* Finds the stop of the line, wrapped to the given column_count.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CH1>
inline Char* TStringLineEnd(Char* cursor, Char* stop, int column_count = 80) {
  return const_cast<const Char*>(
      TStringLineEnd<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop), column_count));
}

/* Finds the stop of the decimals in the s, if there are any.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
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

/* Finds the stop of the decimals in the s, if there are any.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
inline Char* TStringDecimalEnd(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TStringDecimalEnd<Char>(reinterpret_cast<const Char*>(cursor),
                              reinterpret_cast<const Char*>(stop)));
}

/* Skips the given Char in a s if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
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

/* Skips the given Char in a s if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
inline Char* TStringSkipChar(Char* cursor, Char skip_char) {
  return const_cast<const Char*>(
      TStringSkipChar<Char>(reinterpret_cast<const Char*>(cursor), skip_char));
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
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

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
Char* TStringSkipSpaces(Char* cursor) {
  return const_cast<Char*>(TStringSkipSpaces<Char>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param  cursor  The first Char in the buffer.
@param  query   A query string.  */
template <typename Char = CH1>
const Char* TStringFind(const Char* cursor, const Char* query) {
  ASSERT(cursor);
  ASSERT(query);

  Char s = *cursor,  //< Current s Char.
      t = *query,    //< Current query Char.
      c = t;         //< The first Char of the query we're searching for.
  if (!c)            //< We're not allowing empty queries.
    return nullptr;
  const Char *start_of_query, *begin = cursor;
  query = TStringSkipSpaces<Char>(query);

  // Scroll through each Char and match it to the query Char.
  while (s) {
    if (s == c) {  // The first Char matches:
                   // Setup to compare the strings;
      start_of_query = cursor;
      begin = query;
      t = c;
      // check the rest of the Char:
      while (s == t) {
        s = *(++cursor);
        t = *(++begin);
        if (t == 0)  // Once we've reached the delimiter it's a match!
          return start_of_query;
        if (!s)  // We've reached the stop of Char without a hit.
          return nullptr;
      }
    }
    // The Char did not match so repeat the process for each Char.
    s = *(++cursor);
    t = *(++begin);
  }
  // If we haven't found it by now it's not in the s.
  return nullptr;
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the . */
template <typename Char = CH1>
inline Char* TStringFind(Char* string, const Char* query) {
  return const_cast<Char*>(
      TStringFind<Char>(reinterpret_cast<const Char*>(string),
                        reinterpret_cast<const Char*>(query)));
}

/* String skip spaces.
@return Nil if there are no spaces to skip. */
template <typename Char = CH1>
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

/* String skip spaces.
@return Nil if there are no spaces to skip.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
inline Char* TStringSkipSpaces(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TStringSkipSpaces<Char>(reinterpret_cast<const Char*>(cursor),
                              reinterpret_cast<const Char*>(stop)));
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a. */
template <typename Char = CH1>
const Char* TStringEquals(const Char* string_a, const Char* string_b) {
  ASSERT(string_a);
  ASSERT(string_b);
  PRINTF("\nComparing \"%s\" to \"%s\"", string_a, string_b);

  Char a = *string_a, b = *string_b;
  while (a) {
    PRINT(a);
    if (a != b) {  // Not a hit.
      PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      PRINTF("\nFound hit at 0x%p", string_a);
      return string_a;
    }
    a = *(++string_a);
    b = *(++string_b);
  }
  if (b) {
    PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  PRINTF("\nFound hit at 0x%p", string_a);
  return string_a;  //< Find hit!
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a.
*/
template <typename Char = CH1>
inline Char* TStringEquals(Char* string_a, const Char* string_b) {
  return const_cast<Char*>(
      TStringEquals<Char>(reinterpret_cast<const Char*>(string_a),
                          reinterpret_cast<const Char*>(string_b)));
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CH1>
const Char* TStringEquals(const Char* cursor, const Char* stop, Char* query) {
  if (!cursor) return nullptr;
  ASSERT(cursor < stop);
  if (!query) return nullptr;

  PRINTF("\nComparing \"%s\" to \"%s\"", cursor, query);

  const Char a = *cursor, b = *query;
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

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CH1>
Char* TStringEquals(Char* cursor, Char* stop, Char* query) {
  return const_cast<Char*>(TStringEquals(reinterpret_cast<const Char*>(cursor),
                                         reinterpret_cast<const Char*>(stop),
                                         query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CH1>
BOL TStringIsntEmpty(const Char* cursor) {
  if (!cursor) return false;
  Char c = *cursor;
  while (c) {
    if (!TIsWhitespace<Char>(c)) return true;
    c = *(++cursor);
  }
  return false;
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CH1>
BOL TStringIsntEmpty(Char* cursor) {
  return TStringIsntEmpty<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
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

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
BOL TStringIsntEmpty(Char* cursor, const Char* stop) {
  return TStringIsntEmpty(reinterpret_cast<const Char*>(cursor),
                          reinterpret_cast<const Char*>(stop));
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the Char after the last Char in the
given range.
@param  cursor  The first Char in the buffer.
@param  lower_bounds
@param  upper bounds*/
template <typename Char = CH1>
const Char* TStringSkipCharsInRange(const Char* cursor, Char lower_bounds,
                                    Char upper_bounds) {
  ASSERT(cursor);
  ASSERT(lower_bounds < upper_bounds);
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
template <typename Char = CH1>
Char* TStringSkipCharsInRange(Char* cursor, Char lower_bounds,
                              Char upper_bounds) {
  return const_cast<Char*>(TStringSkipCharsInRange(
      reinterpret_cast<const Char*>(cursor), lower_bounds, upper_bounds));
}

/* Skips the numbers in the given range. */
template <typename Char = CH1>
inline Char* TStringSkipNumbers(Char* cursor) {
  return const_cast<Char*>(TStringSkipCharsInRange<Char>(
      reinterpret_cast<const Char*>(cursor), '0', '9'));
}

/* Prints the given token aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param  token  The token to utf.
@param  column_count The number_ of columns to align right to. */
template <typename Char = CH1>
Char* TPrintRight(Char* cursor, Char* stop, const Char* token,
                  int column_count = 80) {
  ASSERT(token);
  PRINTF("\ncursor:%p end:%p", cursor, stop);
  ASSERT(cursor <= stop);

  if (!cursor || column_count < 1) return nullptr;

  if (cursor + column_count > stop) {
    PRINT("\nBuffer overflow!");
    return nullptr;
  }

  auto token_end = TStringEnd<Char>(token);
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
  --token_end;  //< This is pointed at the nil-term CH1
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

/* Prints the given cursor center aligned to the given column_count. */
template <typename Char = CH1>
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string_,
                   int column_count = 80) {
  ASSERT(cursor);
  ASSERT(cursor < stop);

  // We need to leave at least one space to the left and right of
  int length = TStringLength<Char>(string_), offset;
  PRINTF("\n\n    Printing \"%s\":%i column_count:%i", string_, length,
         column_count);

  if (column_count < length) {
    offset = length - column_count;
    if (offset > 3) {
      offset = 3;
    }
    column_count -= offset;
    while (column_count-- > 0) {
      *cursor++ = *string_++;
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

  CH1 c = *string_++;
  while (c) {
    *cursor++ = c;
    c = *string_++;
  }
  while (offset-- > 0) *cursor++ = ' ';
  *cursor = 0;
  PRINTF("\n    Printed:\"%s\"", string_);
  return cursor;
}

/* Prints a line of the given column_count the given begin. */
template <typename Char = CH1>
Char* TPrintLine(Char* cursor, const Char* stop, Char token,
                 int column_count = 80) {
  ASSERT(cursor);
  ASSERT(cursor < stop);
  int l_column_count = column_count;
  if (cursor + l_column_count + 1 >= stop) return nullptr;

  *cursor++ = '\n';

  while (l_column_count-- > 0) *cursor++ = token;

  *cursor = 0;
  return cursor;
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CH1>
Char* TPrintLineString(Char* cursor, Char* stop, const Char* string_,
                       int column_count = 80) {
  ASSERT(cursor);
  ASSERT(cursor < stop);
  if (cursor + column_count + 1 > stop) return nullptr;

  while (column_count-- > 0) {
    CH1 c = *string_++;
    if (!c) {
      cursor = 0;
    }
    *cursor++ = c;
  }
  *cursor = 0;
  return cursor;
}

/* Prints a cursor to the given buffer without */
template <typename Char = CH1>
Char* TPrintWrap(Char* cursor, Char* stop, const Char* string_,
                 int column_count = 80) {
  ASSERT(cursor && cursor < stop && string_);
  if (column_count < 3) {
  }
  Char c = *string_++;

  while (c) {
    for (int i = column_count; i > 0; --i) {
      *cursor++ = c;
      c = *string_++;
      if (cursor >= stop) return nullptr;
      if (!c) {
        *cursor = c;
        return cursor;
      }
    }
    *cursor++ = '\n';
    if (!c) {
      *cursor = c;
      return cursor;
    }
  }
  return cursor;
}

/* A UTF-8, UTF-16, or UTF-32 Text token without any whitespace. */
template <typename Char = CH1>
class TToken {
 public:
  /* Default constructor does nothing. */
  TToken() { *string_ = 0; }

  /* Prints the value to the text begin. */
  TToken(Char character) { TPrint<Char>(string_, string_ + kSize, character); }

  /* Prints the value to the text begin. */
  TToken(const Char* string_) {
    TPrint<Char>(string_, string_ + kSize, string_);
  }

  /* Prints the value to the text begin. */
  TToken(SI4 value) { TPrint<Char>(string_, string_ + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(UI4 value) { TPrint<Char>(string_, string_ + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(SI8 value) { TPrint<Char>(string_, string_ + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(UI8 value) { TPrint<Char>(string_, string_ + kSize, value); }

#if SEAM >= _0_0_0__03
  /* Prints the value to the text begin. */
  TToken(FLT value) { TPrint<Char>(string_, string_ + kSize, value); }

  /* Prints the value to the text begin. */
  TToken(DBL value) { TPrint<Char>(string_, string_ + kSize, value); }
#endif
  /* Gets the number_ s. */
  const Char* String() { return string_; }

 private:
  enum { kSize = 31 };

  Char string_[kSize * sizeof(Char) + 1];  //< String buffer for the token.
};

/* Prints the given socket to the COut. */
template <typename Char = CH1>
Char* TPrintSocket(Char* cursor, Char* stop, const void* begin,
                   const void* end) {
  ASSERT(begin || cursor || cursor < stop);

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
  cursor = TPrintRight<Char>(cursor, stop, TToken<Char>(8).String(), 8);
  *cursor++ = ' ';
  for (int i = 16; i <= 56; i += 8)
    cursor = TPrintRight<Char>(cursor, stop, TToken<Char>(i).String(), 8);
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

/* Converts the given Char to lowercase. */
template <typename Char = CH1>
Char TLowercase(Char c) {
  if ((c & 0x3f) == 3) return c - 64;
  return c;
}

/* Universal Text Formatter.
This class only stores the stop of begin pointer and a pointer to the write
begin. It is up the user to store begin of begin pointer and if they would
like to replace the begin with the beginning of begin pointer when they are
done printing. */
template <typename Char = CH1, typename Size = SIN>
struct TUTF {
  Char *begin,  //< Start address.
      *stop;    //< Stop address.

  /* Initializes the Utf& from the given begin pointers.
  @param begin The beginning of the begin.
  @param stop   The stop of the begin. */
  TUTF(Char* begin, Size size)
      : begin(begin), stop(TPtr<Char>(begin, size - 1)) {
    ASSERT(begin);
  }

  /* Initializes the Utf& from the given begin pointers.
  @param begin The beginning of the begin.
  @param stop   The stop of the begin. */
  TUTF(UIW* begin, Size size)
      : begin(reinterpret_cast<Char*>(begin)),
        stop(TPtr<Char>(begin, size - 1)) {
    ASSERT(begin);
  }

  /* Initializes the Utf& from the given begin pointers.
  @param begin The beginning of the begin.
  @param stop   The stop of the begin. */
  TUTF(Char* begin, Char* stop) : begin(begin), stop(stop) {}

  /* Clones the other utf. */
  TUTF(const TUTF& other)
      : begin(other.begin), stop(other.stop) {  // Nothing to do here!.
  }

  /* Sets the begin pointer to the new_pointer. */
  inline TUTF& Set(Char* new_pointer) {
    if (!new_pointer) return *this;
    begin = new_pointer;
    return *this;
  }

  /* Sets the begin pointer to the new_pointer. */
  inline TUTF& Set(UIW* new_pointer) {
    return Set(reinterpret_cast<Char*>(new_pointer));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI1 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI1 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI2 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI2 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI4 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI4 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(SI8 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(UI8 value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

#if SEAM >= _0_0_0__03
  /* Prints the given value as hex. */
  inline TUTF& Hex(FLT value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as hex. */
  inline TUTF& Hex(DBL value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }
#endif

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(const void* value) {
    return Set(TPrintHex<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI1 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI1 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI2 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI2 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI4 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI4 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(SI8 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(UI8 value) {
    return Set(Binary<Char>(begin, stop, value));
  }

#if SEAM >= _0_0_0__03
  /* Prints the given value as binary. */
  inline TUTF& Binary(FLT value) {
    return Set(Binary<Char>(begin, stop, value));
  }

  /* Prints the given value as binary. */
  inline TUTF& Binary(DBL value) {
    return Set(Binary<Char>(begin, stop, value));
  }
#endif
  /* Prints the given pointer as binary. */
  inline TUTF& Binary(const void* ptr) {
    UIW address = reinterpret_cast<UIW>(ptr);
    return Set(Binary<Char>(begin, stop, address));
  }
};

/* Utility class for printing hex with operator<<. */
template <typename Char = CH1>
class TCenter {
 public:
  /* Prints the value to the text begin. */
  TCenter(const Char* string_, int column_count = 80)
      : string_(TStringSet<const Char>(string_)), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(SI4 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(UI4 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(SI8 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(UI8 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count(column_count) {
    // Nothing to do here!
  }

#if SEAM >= _0_0_0__04
  /* Prints the value to the text begin. */
  TCenter(FLT value, int column_count = 80)
      : string_ (nullptr), number_(value), column_count(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TCenter(DBL value, int column_count = 80)
      : string_ (nullptr), number_(value), column_count(column_count) {
    // Nothing to do here!
  }
#endif

  /* Gets the number_ s. */
  const Char* String() { return string_; }

  /* Gets the column_count. */
  int GetColumnCount() { return column_count; }

  TUTF<Char>& Print(TUTF<Char>& utf) {
    if (string_) {
      return utf.Set(
          _::TPrintCenter<Char>(utf.begin, utf.stop, string_, column_count));
    }
    return utf.Set(_::TPrintCenter<Char>(utf.begin, utf.stop, number_.String(),
                                         column_count));
  }

 private:
  const Char* string_;   //< Pointer to the s.
  TToken<Char> number_;  //< Pointer to a pointer to utf.
  int column_count;      //< Number of columns to center.
};

/* Utility class for printing hex with operator<<. */
template <typename Char = CH1>
class TRight {
 public:
  /* Prints the value to the text begin. */
  TRight(const Char* string_, int column_count = 80)
      : string_(TStringSet<Char>(string_)), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(SI4 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(UI4 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(SI8 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(UI8 value, int column_count = 80)
      : string_(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

#if SEAM >= _0_0_0__04
  /* Prints the value to the text begin. */
  TRight(FLT value, int column_count = 80)
      : cursor(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }

  /* Prints the value to the text begin. */
  TRight(DBL value, int column_count = 80)
      : cursor(nullptr), number_(value), column_count_(column_count) {
    // Nothing to do here!
  }
#endif
  /* Gets the number_ s. */
  const Char* String() { return string_; }

  /* Gets the column_count. */
  int GetColumnCount() { return column_count_; }

  TUTF<Char>& Print(TUTF<Char>& utf) {
    if (string_)
      return utf.Set(
          _::TPrintRight<Char>(utf.begin, utf.stop, string_, column_count_));
    return utf.Set(_::TPrintRight<Char>(utf.begin, utf.stop, number_.String(),
                                        column_count_));
  }

 private:
  const Char* string_;   //< Pointer to the s.
  TToken<Char> number_;  //< Pointer to a pointer to utf.
  int column_count_;     //< Number of columns to center.
};

/* Utility class for printing a single Char token line with operator<<. */
template <typename Char = CH1>
struct API TLineChar {
  Char token;        //< Character to utf.
  int column_count;  //< Column count.

  /* Constructor. */
  TLineChar(Char token, int column_count = 80)
      : token(token), column_count(column_count) {}
};

/* Utility class for printing a s line with operator<<. */
template <typename Char = CH1>
struct API TLineString {
  const Char* string_;  //< Character to utf.
  int column_count;     //< Column count.

  /* Constructor. */
  TLineString(const Char* string_, int column_count = 80)
      : string_(string_), column_count(column_count) {}

  TUTF<Char>& Print(TUTF<Char>& utf) {}
};

/* Returns the first CH1 in the cursor socket. */
template <typename Char = CH1, typename Size = int>
inline Char* TStringStart(UIW* begin) {
  ASSERT(begin);
  UIW address = reinterpret_cast<UIW>(begin) + sizeof(Size);
  return reinterpret_cast<Char*>(address);
}

/* Searches for the stop of the s. */
template <typename Char = CH1, typename Size = int>
inline Char* TStringStop(UIW* begin) {
  ASSERT(begin);

  UIW address = reinterpret_cast<UIW>(begin) + sizeof(Size);
  Size size = *reinterpret_cast<Size*>(begin);
  // Char* begin = reinterpret_cast<Char*>(address);
  return reinterpret_cast<Char*>(address) + (size >> TBitShiftCount<Size>()) -
         1;
}

/* Searches for the stop of the string. */
template <typename Char = CH1, typename Size = int>
inline Char* TStringStop(CObject obj) {
  return TStringStop<Char, Size>(obj);
}

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor.*/
template <typename Size, typename Char>
struct TCSTR {
  Size size;  //< Size of the ASCII Object.
};

template <typename Char, typename Size>
Char* TStringBegin(TCSTR<Char, Size>* string_) {
  ASSERT(string_);
}

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor.*/
template <typename Size, typename Char>
class TSTR {
 public:
  /* Constructs a string from a raw buffer pointer. */
  TSTR(UIW* obj) : obj_(reinterpret_cast<TCSTR<Size, Char>*>(obj)) {}

  /* Gets the Start, meaning the first Char, of the string. */
  Char* Start() {
    UIW ptr = reinterpret_cast<UIW>(obj_);
    return reinterpret_cast<Char*>(ptr + sizeof(Size));
  }

  /* Prints this object to the COut. */
  inline void Print() { _::Print(Start()); }

 private:
  TCSTR<Size, Char>* obj_;  //< Pointer to an ASCII STR.
};

/* AsciiFactory prints the begin to the console without deleting the begin.
@return If (size == 0 && begin) then nil indicating success deleting the
factory. If passing in a argument it will have to get passed through the obj.
*/
template <typename Size = int, typename Char = CH1>
int TCOut(CObject& obj, SIW function, void* arg) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  UIW address = reinterpret_cast<UIW>(begin) + sizeof(Size);
  Print(reinterpret_cast<const Char*>(address));
  return 0;
}

/* AsciiFactory prints the begin to the console and deletes the
obj.begin. */
template <typename Size = int, typename Char = CH1>
int TCOutHeap(CObject& obj, SIW fun, void* arg) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  UIW address = reinterpret_cast<UIW>(begin) + sizeof(Size);
  Print(reinterpret_cast<const Char*>(address));
  delete[] begin;
  return 0;
}

/* Queries the given s for the given query. */
template <typename Char = CH1>
int TStringQuery(const Char* cursor, const Char* stop, const Char* query) {
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
  // text SHOULD be a nil-terminated s without whitespace.
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
template <typename Char = CH1, typename Size = intptr_t>
TUTF<Char> TCOut() {
  static TUTF<Char> serial_out(TCOut<Char>);
  return serial_out;
}

}  // namespace _

/* Writes a nil-terminated UTF-8 or ASCII s to the utf.
@return The utf.
@param  utf The utf.
@param  value   The value to utf. */
template <typename Char = CH1, typename Size = intptr_t>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, const Char* string_) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, string_));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value   The value to utf.
@return The utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, Char c) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, c));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI1 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI2 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI2 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI4 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI4 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI8 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI8 value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

#if SEAM >= _0_0_0__03
/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, FLT value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
template <typename Char = CH1>
_::TUTF<Char>& operator<<(_::TUTF<Char>& utf, DBL value) {
  return utf.Set(_::TPrint<Char>(utf.begin, utf.stop, value));
}
#endif

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  item The item to write to utf. */
template <typename Char = CH1>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TCenter<Char> item) {
  return item.Print(utf);
}

/* Writes the given value to the utf justified right.
@return The utf.
@param  utf The utf.
@param  item The item to utf. */
template <typename Char = CH1>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TRight<Char> item) {
  return item.Print(utf);
}

/* Prints a TLineChar<Char> to the UTF. */
template <typename Char = CH1>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TLineChar<Char> line) {
  return line.Print(utf);
}

/* Prints a TLineString<Char> to the UTF. */
template <typename Char = CH1>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf,
                                 _::TLineString<Char> line) {
  return line.Print(utf);
}

/* Prints a TLineString<Char> to the UTF. */
template <typename Char = CH1>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TToken<Char> token) {
  return token.Print(utf);
}

#endif  //< #if SCRIPT2_TUTF
#endif  //< #if SEAM >= _0_0_0__03
