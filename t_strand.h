/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_strand.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#ifndef SCRIPT2_TUTF
#define SCRIPT2_TUTF 1

#if SEAM >= SCRIPT2_3

#include "c_ascii.h"
#include "c_strand.h"
#include "t_object.h"
#include "t_uniprinter.h"

#if SEAM == SCRIPT2_3
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* Initializes an ASCII Strand. */
template <typename Size, typename Char>
inline Char* TStrandInit(UIW* obj, Size size) {
  UIW address = reinterpret_cast<UIW>(TObjInit<Size>(obj, size));
  return reinterpret_cast<Char*>(address + sizeof(Size));
}

/* An empty string. */
template <typename Char = CH1>
const Char* TSTREmpty() {
  static const Char kStrand[] = {NIL};
  return kStrand;
}

/* The new-line s. */
template <typename Char = CH1>
const Char* TSTRNL() {
  static const Char kStrand[] = {kLF};
  return kStrand;
}

/* Strand the reads "Error:". */
template <typename Char = CH1>
const Char* TSTRError() {
  static const Char kStrand[] = {kLF, 'E', 'r', 'r', 'o', 'r', ':', NIL};
  return kStrand;
}

/* Converts the given item to a printable CH1 if it's non-printable. */
template <typename Char = CH1>
inline Char TPrintableChar(Char item) {
  if (item < 32 || item == 127) return ' ';
  return item;
}

/* Sets the s to either the given item or empty s if input
is nil. */
template <typename Char = CH1>
inline Char* TStrandSet(Char* string) {
  if (!string) return TSTREmpty<Char>();
  return string;
}

/* Searches fro the s line stop.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
const Char* TSTRLineEnd(const Char* cursor, SI4 column_count = 80) {
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
Char* TSTRLineEnd(Char* cursor, SI4 column_count = 80) {
  return const_cast<Char*>(
      TSTRLineEnd(reinterpret_cast<const Char*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CH1>
const Char* TSTRLineEnd(const Char* cursor, const Char* stop,
                        SI4 column_count = 80) {
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
inline Char* TSTRLineEnd(Char* cursor, Char* stop, SI4 column_count = 80) {
  return const_cast<const Char*>(
      TSTRLineEnd<Char>(reinterpret_cast<const Char*>(cursor),
                        reinterpret_cast<const Char*>(stop), column_count));
}

/* Finds the stop of the decimals in the s, if there are any.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
const Char* TSTRDecimalEnd(const Char* cursor, const Char* stop) {
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
inline Char* TSTRDecimalEnd(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TSTRDecimalEnd<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop)));
}

/* Skips the given Char in a s if there are any.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
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
template <typename Char = CH1>
inline Char* TSTRSkipChar(Char* cursor, Char skip_char) {
  return const_cast<const Char*>(
      TSTRSkipChar<Char>(reinterpret_cast<const Char*>(cursor), skip_char));
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CH1>
const Char* TSTRSkipSpaces(const Char* cursor) {
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
Char* TSTRSkipSpaces(Char* cursor) {
  return const_cast<Char*>(TSTRSkipSpaces<Char>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param  cursor  The first Char in the buffer.
@param  query   A query string.  */
template <typename Char = CH1>
const Char* TSTRFind(const Char* start, const Char* query) {
  ASSERT(start);
  ASSERT(query);

  Char s = *start,  //< Current s Char.
      t = *query,   //< Current query Char.
      c = t;        //< The first Char of the query we're searching for.
  if (!c)           //< We're not allowing empty queries.
    return nullptr;
  const Char *start_of_query, *cursor = start;
  query = TSTRSkipSpaces<Char>(query);

  // Scroll through each Char and match it to the query Char.
  while (s) {
    if (s == c) {  // The first Char matches:
                   // Setup to compare the strings;
      start_of_query = start;
      cursor = query;
      t = c;
      // check the rest of the Char:
      while (s == t) {
        s = *(++start);
        t = *(++cursor);
        if (t == 0)  // Once we've reached the delimiter it's a match!
          return start_of_query;
        if (!s)  // We've reached the stop of Char without a hit.
          return nullptr;
      }
    }
    // The Char did not match so repeat the process for each Char.
    s = *(++start);
    t = *(++cursor);
  }
  // If we haven't found it by now it's not in the s.
  return nullptr;
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the . */
template <typename Char = CH1>
inline Char* TSTRFind(Char* string, const Char* query) {
  return const_cast<Char*>(
      TSTRFind<Char>(reinterpret_cast<const Char*>(string),
                     reinterpret_cast<const Char*>(query)));
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip. */
template <typename Char = CH1>
const Char* TSTRSkipSpaces(const Char* cursor, const Char* stop) {
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

/* Strand skip spaces.
@return Nil if there are no spaces to skip.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
inline Char* TSTRSkipSpaces(Char* cursor, Char* stop) {
  return const_cast<Char*>(
      TSTRSkipSpaces<Char>(reinterpret_cast<const Char*>(cursor),
                           reinterpret_cast<const Char*>(stop)));
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a. */
template <typename Char = CH1>
const Char* TSTREquals(const Char* string_a, const Char* string_b) {
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
inline Char* TSTREquals(Char* string_a, const Char* string_b) {
  return const_cast<Char*>(
      TSTREquals<Char>(reinterpret_cast<const Char*>(string_a),
                       reinterpret_cast<const Char*>(string_b)));
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CH1>
const Char* TSTREquals(const Char* cursor, const Char* stop,
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

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CH1>
Char* TSTREquals(Char* cursor, Char* stop, const Char* query) {
  return const_cast<Char*>(TSTREquals(reinterpret_cast<const Char*>(cursor),
                                      reinterpret_cast<const Char*>(stop),
                                      query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CH1>
BOL TSTRIsntEmpty(const Char* cursor) {
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
BOL TSTRIsntEmpty(Char* cursor) {
  return TSTRIsntEmpty<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CH1>
BOL TSTRIsntEmpty(const Char* cursor, const Char* stop) {
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
BOL TSTRIsntEmpty(Char* cursor, const Char* stop) {
  return TSTRIsntEmpty(reinterpret_cast<const Char*>(cursor),
                       reinterpret_cast<const Char*>(stop));
}

/* Skips all the chars in a given range.
@return Nil upon failure or a pointer to the Char after the last Char in the
given range.
@param  cursor  The first Char in the buffer.
@param  lower_bounds
@param  upper bounds*/
template <typename Char = CH1>
const Char* TSTRSkipCharsInRange(const Char* cursor, Char lower_bounds,
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
Char* TSTRSkipCharsInRange(Char* cursor, Char lower_bounds, Char upper_bounds) {
  return const_cast<Char*>(TSTRSkipCharsInRange(
      reinterpret_cast<const Char*>(cursor), lower_bounds, upper_bounds));
}

/* Skips the numbers in the given range. */
template <typename Char = CH1>
inline const Char* TSTRSkipNumbers(const Char* cursor) {
  return const_cast<Char*>(TSTRSkipCharsInRange<Char>(
      reinterpret_cast<const Char*>(cursor), '0', '9'));
}
/* Skips the numbers in the given range. */
template <typename Char = CH1>
inline Char* TSTRSkipNumbers(Char* cursor) {
  return const_cast<Char*>(
      TSTRSkipNumbers<Char>(reinterpret_cast<const Char*>(cursor)));
}

/* Prints the given item aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param  item  The item to utf.
@param  column_count The token_ of columns to align right to. */
template <typename Char = CH1>
Char* TPrintRight(Char* cursor, Char* stop, const Char* item,
                  SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;
  PRINTF("\ncursor:%p end:%p", cursor, stop);

  if (!cursor || column_count < 1) return nullptr;

  if (cursor + column_count > stop) {
    PRINT("\nBuffer overflow!");
    return nullptr;
  }

  auto item_end = TSTREnd<Char>(item);
  Char c;  //< Temp variable.
  if (item == item_end) return cursor;
  SIW length = item_end - item;

  // If the length is less than the column_count we need to print ".", "..",
  // "..." or nothing and chop off some of the item.
  SIW count = column_count - length;
  PRINTF("\n\nPrinting \"%s\":%i aligned right %i columns count:%i", item,
         (SI4)length, column_count, count);
  if (count < 0) {
    SIW dot_count = length + count;
    PRINTF(" dot_count:%i", (int)dot_count);
    if (dot_count <= 3) {
      PRINTF("\n Wrote dots:\"");
      while (dot_count-- > 0) {
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
    item_end = item + column_count - 4;
    PRINTF("\n Wrote with dots backwards:\"...");
    while (item_end > item) {
      c = *item_end--;
      *stop-- = c;
      PRINT(c);
    }
    c = *item_end--;
    *stop-- = c;
    PRINT(c);
    PRINTF("\"");
    return cursor + column_count;
  }
  PRINTF("\ncursor:0x%p end:0x%p item:0x%p token_end:0x%p", cursor, stop, item,
         item_end);
  // In order to keep the current cache lines we're going to utf
  // backwards back from the token_end.
  PRINTF("\n Wrote backwards:\"");
  stop = cursor + column_count;
  --item_end;   //< This is pointed at the nil-term CH1
  *stop-- = 0;  //< and there is no need to load a 0.
  while (item_end >= item) {
    c = *item_end--;
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
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string,
                   SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;

  // We need to leave at least one space to the left and right of
  SI4 length = TSTRLength<Char>(string);
  PRINTF("\n\nPrinting \"%s\":%i centered to %i columns", string, length,
         column_count);
  SI4 delta;
  if (length <= column_count) {
    delta = (column_count - length) >> 1;  //< >> 1 to /2
    length = column_count - length - delta;
    PRINTF("\nlength:%i offset:%i", length, delta);

    if (length != column_count)
      while (delta-- > 0) *cursor++ = ' ';

    Char c = *string++;
    while (c) {
      *cursor++ = c;
      c = *string++;
    }
    if (length != column_count)
      while (length-- > 0) *cursor++ = ' ';
    *cursor = 0;
    return cursor;
  }

  if (column_count <= 3) {
    while (column_count-- > 0) *cursor++ = '.';
    *cursor = 0;
    return cursor;
  }
  delta = column_count - 3;
  while (delta-- > 0) *cursor++ = *string++;
  *cursor++ = '.';
  *cursor++ = '.';
  *cursor++ = '.';
  *cursor = 0;
  return cursor;
}

/* Prints a line of the given column_count the given start. */
template <typename Char = CH1>
Char* TPrintLinef(Char* start, Char* stop, Char item, SI4 count = 80,
                  const Char* header = TSTRNL<Char>(),
                  const Char* footer = nullptr) {
  if (header) start = Print(start, stop, header);
  if (!start || start + count <= stop) return nullptr;

  while (count-- > 0) *start++ = item;

  if (footer)
    return Print(start, stop, footer);
  else
    *start = 0;
  return start;
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CH1>
Char* TPrintLinef(Char* start, Char* stop, const Char* item, SI4 count = 80,
                  const Char* header = TSTRNL<Char>(),
                  const Char* footer = nullptr) {
  if (header) start = Print(start, stop, header);
  if (!start || start <= stop || (start + count >= stop)) return nullptr;

  const Char* cursor = item;
  while (count-- > 0) {
    Char c = *cursor++;
    if (!c) {
      cursor = item;
      c = *cursor++;
    }
    *start++ = c;
  }
  if (footer)
    return Print(start, stop, footer);
  else
    *start = 0;
  return start;
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CH1>
Char* TPrintHeadingf(Char* start, Char* stop, Char item, SI4 count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CH1>
Char* TPrintHeadingf(Char* start, Char* stop, const Char* item,
                     SI4 count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints a cursor to the given buffer without */
template <typename Char = CH1>
Char* TPrintWrap(Char* cursor, Char* stop, const Char* string,
                 SI4 column_count = 80) {
  if (!cursor || cursor <= stop || !string) return nullptr;
  if (column_count < 3) {
    PRINT("\nFix me!");
  }
  Char c = *string++;

  while (c) {
    for (SI4 i = column_count; i > 0; --i) {
      *cursor++ = c;
      c = *string++;
      if (cursor >= stop) return nullptr;
      if (!c) {
        *cursor = c;
        return cursor;
      }
    }
    *cursor++ = kLF;
    if (!c) {
      *cursor = c;
      return cursor;
    }
  }
  return cursor;
}

/* Prints the given socket to the SOut. */
template <typename Char = CH1>
Char* TPrintSocket(Char* start, Char* stop, const void* begin,
                   const void* end) {
  DASSERT(start && start < stop && begin && end);
  if (!start || stop < start || !begin || end <= begin) return nullptr;

  Char* buffer_begin = start;
  const CH1 *address_ptr = reinterpret_cast<const CH1*>(begin),
            *address_end_ptr = reinterpret_cast<const CH1*>(end);
  SIW size = address_end_ptr - address_ptr,
      num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - start) <= num_bytes) {
    PRINTF("\nERROR: Buffer overflow trying to fit %i in %i bytes!",
           (SIN)num_bytes, (SIN)(stop - start));
    return nullptr;
  }

  size += num_bytes;
  start = TPrint<Char>(start, stop, STRSocketHeader());
  start = TPrint<Char>(start, stop, STRSocketBorder());
  start = TPrintHex<Char>(start, stop, address_ptr);

  PRINTF("\nBuffer space left:%i", (SIN)(stop - start));
  CH1 c;
  while (address_ptr < address_end_ptr) {
    *start++ = kLF;
    *start++ = '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (!c || c == kTAB)
        c = ' ';
      else if (c < ' ')
        c = kDEL;
      *start++ = c;
    }
    *start++ = '|';
    *start++ = ' ';
    start = TPrintHex<Char>(start, stop, address_ptr);
  }
  start = TPrint<Char>(start, stop, STRSocketBorder());
  return TPrintHex<Char>(start, stop, address_ptr + size);
}

/* Prints the given socket to the SOut. */
template <typename Printer>
Printer& TPrintSocket(Printer& o, const void* begin, const void* end) {
  ASSERT(begin || end || begin <= end);

  const CH1 *address_ptr = reinterpret_cast<const CH1*>(begin),
            *address_end_ptr = reinterpret_cast<const CH1*>(end);
  SIW size = address_end_ptr - address_ptr,
      num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  size += num_bytes;
  o << STRSocketHeader() << STRSocketBorder();
  TPrintHex<Printer>(o, address_ptr);
  CH1 c;
  while (address_ptr < address_end_ptr) {
    o << kLF << '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (!c || c == kTAB)
        c = ' ';
      else if (c < ' ')
        c = kDEL;
      o << (CHN)c;
    }
    o << '|' << ' ';
    TPrintHex<Printer>(o, address_ptr);
  }
  o << STRSocketBorder();
  return TPrintHex<Printer>(o, address_ptr + size);
}

/* Converts the given Char to lowercase. */
template <typename Char = CH1>
Char TLowercase(Char c) {
  if ((c & 0x3f) == 3) return c - 64;
  return c;
}

/* ASCII TKN (Token). */
template <typename Char = CH1, SIN kTokenLongest_ = kTokenLongest>
class TToken {
 public:
  enum { kLengthMax = kTokenLongest_ };

  TToken(CH1 item = 0, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    auto cursor = strand_;
    *cursor = item;
    *cursor = 0;
  }

  TToken(const CH1* item, SI4 count = kTokenLongest_)
      : string_(item), count_(count) {
    if (!item) *strand_ = 0;
  }

  TToken(CH2 item = 0, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    auto cursor = strand_;
    *cursor = item;
    *cursor = 0;
  }

  TToken(CH4 item = 0, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    auto cursor = strand_;
    *cursor = item;
    *cursor = 0;
  }

  TToken(const CH4* item, SI4 count = kTokenLongest_)
      : string_(item), count_(count) {
    if (!item) *strand_ = 0;
  }

  TToken(SI4 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(UI4 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(SI8 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(UI8 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

#if SEAM >= SCRIPT2_4
  /* Prints the item to the token_. */
  TToken(FP4 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }

  /* Prints the item to the token_. */
  TToken(FP8 item, SI4 count = kTokenLongest_)
      : string_(string_), count_(count) {
    Print(strand_, strand_ + kTokenLongest_, item);
  }
#endif

  /* Gets the string_. */
  const Char* String() { return string_; }

  /* Gets the strand_. */
  Char* Strand() { return strand_; }

  /* Gets the string_ or the strand_ if the string_ is nil. */
  const Char* Get() {
    const Char* ptr = string_;
    return ptr ? ptr : strand_;
  }

  /* Sets the string_ to the new string.
  @return Nil upon failure or the string upon success. */
  const CH1* Set(const CH1* string) {
    if (!string) return string;
  }

  /* Gets the count. */
  SI4 Count() { return count_; }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH1 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH1* item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH2 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH2* item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH4* item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI8 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI8 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }

#if USING_FP4 == YES
  /* Prints the given item to the strand_. */
  inline Char* Print(FP4 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }
#endif
#if USING_FP8 == YES
  /* Prints the given item to the strand_. */
  inline Char* Print(FP8 item) {
    auto cursor = ::_::Print(strand_, kTokenLongest_, item);
    if (!cursor) return cursor;
    string_ = nullptr;
    return cursor;
  }
#endif

 private:
  // Pointer to a token too big to fit in the strand_.
  const Char* string_;
  SI4 count_;                        //< The count.
  Char strand_[kTokenLongest_ + 1];  //< Strand buffer for the token.
};

/* Utility class for printing hex with operator<<. */
template <typename Char = CH1>
struct TCenter {
  TToken<Char> token;  //< Pointer to a pointer to utf.

  /* Prints the item to the . */
  TCenter(CH1 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(const CH1* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(CH2 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(const CH2* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(CH4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the . */
  TCenter(const CH4* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(SI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(UI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(SI8 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TCenter(UI8 item, SI4 count = 80) : token(item, count) {}

#if USING_FP4 == YES
  /* Prints the item to the token_. */
  TCenter(FP4 item, SI4 count = 80) : token(item, count) {}
#endif
#if USING_FP8 == YES
  /* Prints the item to the token_. */
  TCenter(FP8 item, SI4 count = 80) : token(item, count) {}
#endif
};

/* Utility class for printing hex with operator<<. */
template <typename Char = CH1>
struct TRight {
  TToken<Char> token;  //< Pointer to a pointer to utf.

  /* Prints the item to the token_. */
  TRight(CH1 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(const CH1* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(CH2 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(const CH2* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(CH4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(const CH4* item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(SI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(UI4 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(SI8 item, SI4 count = 80) : token(item, count) {}

  /* Prints the item to the token_. */
  TRight(UI8 item, SI4 count = 80) : token(item, count) {}

#if USING_FP4 == YES
  /* Prints the item to the token_. */
  TRight(FP4 item, SI4 count = 80) : token(item, count) {}
#endif
#if USING_FP8 == YES
  /* Prints the item to the token_. */
  TRight(FP8 item, SI4 count = 80) : token(item, count) {}
#endif
};

/* Utility class for printing a string line with operator<<. */
template <typename Char = CH1>
struct TLinef {
  TToken<Char> token;

  TLinef(CH1 item, SI4 count = 80) : token(item, count) {}

  TLinef(const CH1* item, SI4 count = 80) : token(item, count) {}

  TLinef(CH2 item, SI4 count = 80) : token(item, count) {}

  TLinef(const CH2* item, SI4 count = 80) : token(item, count) {}

  TLinef(CH4 item, SI4 count = 80) : token(item, count) {}

  TLinef(const CH4* item, SI4 count = 80) : token(item, count) {}
};

/* Utility class for printing a single Char token line with operator<<. */
template <typename Char = CH1>
struct THeadingf {
  TToken<Char> token;
  const Char *style, *caption2, *caption3;

  THeadingf(const CH1* caption, const CH1* style = nullptr,
            SI4 column_count = kTokenLongest, const CH1* caption2 = nullptr,
            const CH1* caption3 = nullptr) {
    TPrintHeadingf<CH1>(caption, style, column_count, caption2, caption3);
  }

  THeadingf(const CH2* caption, const CH2* style = nullptr,
            SI4 column_count = kTokenLongest, const CH2* caption2 = nullptr,
            const CH2* caption3 = nullptr) {
    TPrintHeadingf<CH2>(caption, style, column_count, caption2, caption3);
  }

  THeadingf(const CH4* caption, const CH4* style = nullptr,
            SI4 column_count = kTokenLongest, const CH4* caption2 = nullptr,
            const CH4* caption3 = nullptr) {
    TPrintHeadingf<CH4>(caption, style, column_count, caption2, caption3);
  }
};

/* Universal Text Formatter (UTF).
The UTF only stores the start and stop pointers allowing the length to be
storred on the stack or hard-coded using instructions. If you want an normal
string-like class please use the TStrand, which auto-grows from stack to heap.
*/
template <typename Char = CH1, typename Size = SI4>
struct TUTF {
  Char *start,  //< Start address.
      *stop;    //< Stop address.

  /* Initializes the UTF& from the given begin pointers.
  @param start The beginning of the begin.
  @param count The number of Char(s) in the buffer. */
  TUTF(Char* start, Size count)
      : start(start), stop(TPtr<Char>(start, count - 1)) {
    DASSERT(start);
    Init();
  }

  /* Initializes the UTF& from the given begin pointers.
  @param begin The beginning address of a word-aligned socket.
  @param count The size in bytes. */
  TUTF(UIW* begin, Size size)
      : start(reinterpret_cast<Char*>(begin)),
        stop(TPtr<Char>(begin, size - 1)) {
    DASSERT(start);
    Init();
  }

  /* Initializes the UTF& from the given begin pointers.
  @param begin The beginning address of a word-aligned socket.*/
  TUTF(UIW* begin)
      : start(TSTRStart<Char, Size>(begin)), stop(TSTRStop<Char, Size>(begin)) {
    DASSERT(begin);
    Init();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TUTF(Char* start, Char* stop) : start(start), stop(stop) {
    DASSERT(start);
    DASSERT(start < stop);
    Init();
  }

  /* Clones the other utf. */
  TUTF(const TUTF& other)
      : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  UI1* End() { return reinterpret_cast<UI1*>(start) + (sizeof(Char) - 1); }

  Size SizeBytes() { return (Size)(stop - start + sizeof(Char)); }

  void Wipe() { SocketWipe(start, stop); }

  /* Writes a nil-term CH1 at the start of the strand. */
  inline Char* Init() {
    *start = 0;
    return start;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TUTF& Set(Char* new_pointer) {
    if (!new_pointer) {
      PRINT("\nError printing:");
      return *this;
    }
    start = new_pointer;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TUTF& Set(UIW* new_pointer) {
    return Set(reinterpret_cast<Char*>(new_pointer));
  }

  /* Finds the length of the STR in Chars. */
  inline Size Length() { return TSTRLength<Char, Size>(start); }

  /* Calculates the max length of the string in Chars. */
  inline Size LengthMax() { return stop - start; }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH1 item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH2 item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH4 item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH1 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH2 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH4 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH1* item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH2* item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH4* item) {
    return Set(::_::Print(start, stop, item));
  }

  /* Prints the given item. */
  inline TUTF& Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

  /* Prints the given item. */
  inline TUTF& Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

  /* Prints the given item. */
  inline TUTF& Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

  /* Prints the given item. */
  inline TUTF& Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
  /* Prints the given item.
  @return A UTF. */
  inline TUTF& Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
#endif
#if USING_FP8 == YES
  /* Prints the given item.
  @return A UTF. */
  inline TUTF& Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
#endif

  /* Prints the given item. */
  inline TUTF& Print(TRight<Char> item) {
    return Set(::_::TPrintRight<Char>(start, stop, item.token.String(),
                                      item.token.Count()));
  }

  /* Prints the given item. */
  inline TUTF& Print(TCenter<Char> item) {
    return Set(::_::TPrintCenter<Char>(start, stop, item.token.String(),
                                       item.token.Count()));
  }

  /* Prints the given item. */
  inline TUTF& Print(TLinef<Char> item) {
    return Set(::_::TPrintLinef<Char>(start, stop, item.token.String(),
                                      item.token.Count()));
  }

  /* Prints the given item. */
  inline TUTF& Print(THeadingf<Char> item) {
    return Set(::_::TPrintLinef<Char>(start, stop, item.token.String(),
                                      item.token.Count()));
  }

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(Hex item) {
    return TPrintHex<Char>(*this, item.begin, item.size_bytes);
  }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI1 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI1 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI2 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI2 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI4 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI4 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(SI8 item) { return Set(TPrintHex<Char>(start, stop, item)); }

  /* Prints the given item as hex. */
  inline TUTF& Hex(UI8 item) { return Set(TPrintHex<Char>(start, stop, item)); }

#if USING_FP4 == YES
  /* Prints the given item as hex. */
  inline TUTF& Hex(FP4 item) { return Set(TPrintHex<Char>(start, stop, item)); }
#endif
#if USING_FP8 == YES
  /* Prints the given item as hex. */
  inline TUTF& Hex(FP8 item) { return Set(TPrintHex<Char>(start, stop, item)); }
#endif

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(const void* ptr) {
    return Set(TPrintHex<Char>(start, stop, ptr));
  }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI1 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI1 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI2 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI2 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI4 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI4 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(SI8 item) { return Set(Binary<Char>(start, stop, item)); }

  /* Prints the given item as binary. */
  inline TUTF& Binary(UI8 item) { return Set(Binary<Char>(start, stop, item)); }

#if USING_FP4 == YES
  /* Prints the given item as binary. */
  inline TUTF& Binary(FP4 item) { return Set(Binary<Char>(start, stop, item)); }
#endif
#if USING_FP8 == YES
  /* Prints the given item as binary. */
  inline TUTF& Binary(FP8 item) { return Set(Binary<Char>(start, stop, item)); }
#endif
  /* Prints the given pointer as binary. */
  inline TUTF& Binary(const void* ptr) {
    UIW address = reinterpret_cast<UIW>(ptr);
    return Set(Binary<Char>(start, stop, address));
  }

  template <typename Printer>
  Printer& PrintTo(Printer& o) {
    o << "\nTUTF<CH" << sizeof(Char) << ", SI" << sizeof(Size) << ">{ start:";
    TPrintHex<Printer>(o, start);
    o << " stop:";
    TPrintHex<Printer>(o, stop);
    o << " }\n";
    TPrintSocket<Printer>(o, start, End());
    return TPrintChars<Printer, Char>(o, start, stop);
  }
};

/* Returns the first CH1 in the cursor socket. */
template <typename Char = CH1, typename Size = SI4>
inline Char* TSTRStart(UIW* start) {
  UIW address = reinterpret_cast<UIW>(start) + sizeof(Size);
  return reinterpret_cast<Char*>(address);
}

/* Searches for the stop of the strand. */
template <typename Char = CH1, typename Size = SI4>
inline Char* TSTRStop(void* begin) {
  Size size = *reinterpret_cast<Size*>(begin);
  UIW address = reinterpret_cast<UIW>(begin);
  Char* ptr = reinterpret_cast<Char*>(address + sizeof(Size));
  return ptr + (size >> TBitShiftCount<Char>()) - 1;
}

/* Searches for the stop of the strand. */
template <typename Char = CH1, typename Size = SI4>
inline Char* TSTRStop(void* begin, SIW size_bytes) {
  UIW address = reinterpret_cast<UIW>(begin);
  Char* ptr = reinterpret_cast<Char*>(address + sizeof(Size));
  return ptr + (size_bytes >> TBitShiftCount<Char>()) - 1;
}

/* Searches for the stop of the string. */
template <typename Char = CH1, typename Size = SI4>
inline Char* TSTRStop(CObject obj) {
  return TSTRStop<Char, Size>(obj);
}

/* An ASCII Object composed of a UTF-8/ASCII, UTF-16, or UTF-32 cursor.*/
template <typename Size, typename Char>
struct TCSTR {
  Size size;  //< Size of the ASCII Object.
};

/* AsciiFactory prints the begin to the console without deleting the begin.
@return If (size == 0 && begin) then nil indicating success deleting the
factory. If passing in a argument it will have to get passed through the obj.
*/
template <typename Size = SI4, typename Char = CH1>
SI4 TCOut(CObject& obj, SIW function, void* arg) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  UIW address = reinterpret_cast<UIW>(begin) + sizeof(Size);
  Print(reinterpret_cast<const Char*>(address));
  return 0;
}

/* AsciiFactory prints the begin to the console and deletes the
obj.begin. */
template <typename Char = CH1>
SI4 TCOutHeap(CObject& obj, SIW fun, void* arg) {
  UIW* begin = obj.begin;
  if (!begin) return kFactoryNilOBJ;
  UIW address = reinterpret_cast<UIW>(begin) + sizeof(SI4);
  Print(reinterpret_cast<const Char*>(address));
  delete[] begin;
  return 0;
}

/* Queries the given s for the given query. */
template <typename Char = CH1>
SI4 TStrandQuery(const Char* cursor, const Char* stop, const Char* query) {
  Char a = *cursor, b = *query;
  SI4 result;

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
template <typename Char = CH1, typename Size = SIW>
TUTF<Char> TCOut() {
  static TUTF<Char> serial_out(TCOut<Char>);
  return serial_out;
}

}  // namespace _

/* Prints the given item to the UTF.
@return The utf.
@param  utf The utf.
@param  item   The item to utf. */
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, CH1 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const CH1* item) {
  return utf.Print(item);
}

#if USING_UTF16 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, CH2 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const CH2* item) {
  return utf.Print(item);
}
#endif
#if USING_UTF32 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, CH4 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, const CH4* item) {
  return utf.Print(item);
}
#endif

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI1 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI1 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI2 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI2 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI4 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI4 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, SI8 item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, UI8 item) {
  return utf.Print(item);
}

#if USING_FP4 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, FP4 item) {
  return utf.Print(item);
}
#endif
#if USING_FP8 == YES
template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, FP8 item) {
  return utf.Print(item);
}
#endif

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TCenter<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TRight<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TLinef<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::THeadingf<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf,
                                   ::_::TToken<Char> item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Hex& item) {
  return utf.Print(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Chars1& item) {
  return TPrintChars<Printer>(utf, item.start, item.stop);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Char1& item) {
  return utf.PrintChar(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Char2& item) {
  return utf.PrintChar(item);
}

template <typename Char = CH1>
inline ::_::TUTF<Char>& operator<<(::_::TUTF<Char>& utf, ::_::Char4& item) {
  return utf.PrintChar(item);
}

template <typename Char>
void TPrint1(Char* start, Char token) {
  *start++ = token;
  *start++ = 0;
}

template <typename Char>
void TPrint3(Char* start, Char token) {
  *start++ = token;
  *start++ = token;
  *start++ = token;
  *start++ = 0;
}

#if SEAM >= SCRIPT2_6
#if SEAM == SCRIPT2_6
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif
namespace _ {

/* Utility class for printing blocks of Unicode characters. */
template <typename Char = CH1>
struct TChars {
  Char *start,  //< Start character adddress.
      *stop;    //< Stop character address.

  /* Foo: Masters of Bar. */
  TChars(Char* start, Char*) : start(start), stop(stop) {}
};

/* An ASCII Strand that can auto-grow from stack to heap.

The count of the string is defined as the maximimum chars that can fit in the
buffer, including the nil-term CH1.

This class is designed to take advantage of the behavior of the C++ operator
overloads. When you have a string of overloads, the objects get destructed
in the opposite order then where called.

# Initialization

A Strand may be initialed to print to the socket_ or to a dynamically allocated
string. This behavior is configured with the constructors. The AsciiFactory can
either be configured using the class template argument kFactory1_. If the
obj_.Factory () is nil then it will get replaced with the foo.

@code
TStrand<> (TCOut<>).Star ("Hello ") << "world!";
@endcode

# Dynamic Allocated Strands

Strands that use dynamic memory use the DCOutAuto factory:

@code
TStrand<UI4> (TCOutHeap<>) << "Hello world!";
@endcode
*/
template <typename Char = CH1, SI4 kCount_ = kStrandCountDefault>
class TStrand {
 public:
  enum {
    kSizeMax = 0x7ffffff8,  //< Max size in bytes.
    kCountMin = (sizeof(Char) == 1)
                    ? 4
                    : (sizeof(Char) == 2)
                          ? 2
                          : (sizeof(Char) == 4) ? 1 : 0,  //< Min element count.
  };

 private:
  enum {
    kLengthUpperLimit = kSizeMax / sizeof(Char) - 1,  //< Max element of chars.
    kCountLB =
        (kCount_ < kCountMin) ? kCountMin : kCount_,  //< Temp lower-buonds.
  };

 public:
  enum {
    // kCount_ bounded inside the min and max range.
    kCount = (kCountLB >= kLengthUpperLimit) ? kLengthUpperLimit - 1 : kCountLB,
    kLengthMax = kCount - 1,
    // OBJ size in bytes.
    kSize = sizeof(SI4) + kCount * sizeof(Char),
  };

  /* Constructs a Strand that auto-grows from stack to heap.
  @param factory ASCII Factory to call when the Strand overflows. */
  TStrand()
      : obj_(kSize, socket_.Words(), FactoryStack),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
  }

  /* Constructs the utf_ pointers to point to the obj start and stop.
  The utf_ pointers will only point to the start and stop of the obj if
  the obj is an address and the size is in bounds. If the size is out of
  bounds then the utf_ will point to the start and stop of the socket_.
  If the obj is nil than a dynamic ASCII OBJ will be created using the
  FactoryStack; if the size is less than the minimum size or greater than the
  maximum size then the socket_ will be used.
  @param obj  Buffer obj address.
  @param size Object size IN BYTES. */
  TStrand(UIW* obj, SI4 size)
      : obj_(size, obj, FactoryStack),
        utf_(obj, socket_.Stop<SI4, Char, SI4>(kCount)) {}

  /* Constructs a Strand and prints the given item. */
  TStrand(CH1 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(const CH1* item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

#if USING_UTF16 == YES
  /* Constructs a Strand and prints the given item. */
  TStrand(CH2 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(const CH2* item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }
#endif

#if USING_UTF32 == YES
  /* Constructs a Strand and prints the given item. */
  TStrand(CH4 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }
#endif
  /* Constructs a Strand and prints the given item. */
  TStrand(const CH4* item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI1 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI1 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI2 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI2 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI4 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI4 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(SI8 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  /* Constructs a Strand and prints the given item. */
  TStrand(UI8 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

#if USING_FP4 == YES
  /* Constructs a Strand and prints the given item. */
  TStrand(FP4 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }
#endif
#if USING_FP8 == YES
  /* Constructs a Strand and prints the given item. */
  TStrand(FP8 item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }
#endif

  /* Constructs a Strand and prints the given item. */
  TStrand(Hex item)
      : obj_(socket_.Words(), socket_.SizeBytes()),
        utf_(socket_.Start<SI4, Char>(), socket_.Stop<SI4, Char, SI4>(kCount)) {
    Print(item);
  }

  void Wipe() { utf_.Wipe(); }

  void PrintConstants() {
    PRINTF(
        "\nTStrand constants: kCount_:%i kSizeMax:%i kLengthUpperLimit:%i "
        "kCountMin:%i kLengthMax:%i kCountLB:%i kCount:%i kSize:%i\n\n",
        kCount_, kSizeMax, kLengthUpperLimit, kCountMin, kLengthMax, kCountLB,
        kCount, kSize);
  }

  /* Gets the UTF. */
  TUTF<Char>& Star() { return utf_; }

  /* @todo I had the auto-grow code in a template but I could not figure out
  which function wasn't working so I had to copy paste. This needs to get
  changed back to a template as soon as it's fixed thanks. */

  /* Prints a CH1 to the strand.
  @return A UTF. */
  TStrand& PrintChar(CH1 item) { return Print<CH1>(item); }
  TStrand& Print(CH1 item) { return PrintChar(item); }

  TStrand& Print(const CH1* item) { return Print<const CH1*>(item); }

#if USING_UTF16
  TStrand& PrintChar(CH2 item) { return Print<CH2>(item); }
  TStrand& Print(CH2 item) { return PrintChar(item); }

  TStrand& Print(const CH2* item) { return Print<const CH2*>(item); }
#endif
#if USING_UTF32
  TStrand& PrintChar(CH4 item) { return Print<CH4>(item); }
  TStrand& Print(CH4 item) { return PrintChar(item); }

  TStrand& Print(const CH4* item) { return Print<const CH4*>(item); }
#endif
  TStrand& Print(SI4 item) { return Print<SI4>(item); }

  TStrand& Print(UI4 item) { return Print<UI4>(item); }

  TStrand& Print(SI8 item) { return Print<SI8>(item); }

  TStrand& Print(UI8 item) { return Print<UI8>(item); }

#if USING_FP4 == YES
  TStrand& Print(FP4 item) { return Print<FP4>(item); }
#endif
#if USING_FP8 == YES
  TStrand& Print(FP8 item) { return Print<FP8>(item); }
#endif

  /* Returns the begin of the obj. */
  inline Char* Start() { return TSTRStart<Char, SI4>(obj_.Begin()); }

  /* Returns the stop of the obj. */
  inline Char* Stop() { return TSTRStop<Char, SI4>(obj_.Begin()); }

  /* Returns the stop of the obj. */
  inline CH1* End() { return TObjEnd<SI4>(obj_); }

  /* Searches for the given querry, returning the end Char of the qeurry in this
  string. */
  inline Char* Find(const Char* querry) { return TSTRFind(Start(), querry); }

  /* Checks if this Strand to the other string are equivalent.
  @return Nil if they strings are not equivalent and a pointer to the next CH1
  after the end of the equivalent part of this strand upon success. */
  inline Char Equals(const Char* other) { return TSTRFind(Start(), other); }

  /* Checks to see if the utf_ is using static memory. */
  inline BOL IsStatic() { return socket_.Contains(utf_.cursor); }

  /* Gets the obj of the Console obj. */
  inline TObject<SI4>& CObj() { return obj_; }

  /* Prints to the given printer. */
  template <typename Printer>
  Printer& PrintTo(Printer& o) {
    Char char_size_char = (Char)('0' + sizeof(Char));
    Char *start = utf_.start, *stop = utf_.stop;
    o << "\nTStrand<CH" << char_size_char << '>';
    obj_.PrintTo<Printer>(o);
    return utf_.PrintTo<Printer>(o);
  }

  template <typename T>
  TStrand& Print(T item) {
    Char *start = utf_.start,  //
        *stop = utf_.stop;
    PRINTF("\n\nAttempting to print:\"");
    PRINT(item);
    PRINT('\"');
    PrintTo<SOut>(SOut().Star());
    auto cursor = ::_::Print(start, stop, item);
    if (!cursor) {
      *utf_.start = 0;  //< Replace the delimiter so we can copy the string.
      SIW count = stop - start;
      do {
        PRINT("\nPrint failed, attempting to auto-grow from ");
        AsciiFactory af = obj_.Factory(), af2 = FactoryStack;
        DASSERT(af);
        if (af == FactoryStack) {
          PRINT("stack-to-heap.");
          af = af2;
          obj_.SetFactory(af);
        } else {
          PRINT("heap-to-heap.");
        }
        SI4 result = ObjDo(obj_.CObj(), kFactoryGrow);
        if (result) {
          PRINTF("\nFactory exited with Error:%i:\"%s\".\n", result,
                 STRAsciiFactoryError(result));
          return *this;
        }
        start = TSTRStart<Char>(obj_.Begin()),
        stop = start + ((count + 1) << 1);
        utf_.stop = stop;

        // Reset the
        cursor = ::_::Print(start, stop, item);
        PRINTF("\nRe-printed:\"%s\"\n", start);
        if (!cursor) PRINT(" Print failed again.");
      } while (!cursor);
    } else {
      PRINTF("\nPrinted:\"%s\"\n", utf_.start);
    }
    utf_.start = cursor;
    return *this;
  }

  static SI4 FactoryStack(CObject& obj, SIW function, void* arg) {
    PRINT("\n\nEntering TStack FactoryStack");
    return Factory(obj, function, arg, kStack);
  }

  static SI4 FactoryHeap(CObject& obj, SIW function, void* arg) {
    PRINT("\n\nEntering TStack FactoryHeap");
    return Factory(obj, function, arg, kHeap);
  }

 private:
  TObject<SI4> obj_;            //< ASCII CObject.
  TUTF<Char> utf_;              //< UTF for the strand.
  TSocket<SI4, kSize> socket_;  //< A socket on the stack.

  /* Strand factory.
   */
  static SI4 Factory(CObject& obj, SIW function, void* arg, BOL using_heap) {
    PRINT("\nEntering Strand.Factory.");
    SI4 size;
    UIW *begin = obj.begin, *temp;
    if (!begin) return kFactoryNilOBJ;
    switch (function) {
      case kFactoryDestroy: {
        PRINT("Destroy:");
        begin = obj.begin;
        if (!begin) return kFactoryNilOBJ;
        if (using_heap)
          delete[] begin;
        else
          obj.factory = FactoryStack;
        break;
      }
      case kFactoryNew: {
        PRINT("New:");
        if (!arg) return kFactoryNilArg;
        size = TAlignUpSigned<SI4>(*reinterpret_cast<SI4*>(arg));
        if ((~size) == 0) return kFactorySizeInvalid;
        try {
          auto new_size = size >> kWordBitCount;
          PRINTF("\nAttempting to print %i.", (SIN)new_size);
          begin = new UIW[new_size];
        } catch (std::bad_alloc exception) {
          return kFactoryCantGrow;
        }
        *reinterpret_cast<SI4*>(begin) = size;
        obj.begin = begin;
        obj.factory = FactoryStack;
        break;
      }
      case kFactoryGrow: {
        PRINT("Grow:");
        UIW* new_begin = TObjGrowDouble<SI4>(begin);
        if (!new_begin) return kFactoryCantGrow;
        TUTF<Char> utf(new_begin);
        PRINTF(" new count:%i utf.LengthMax():%i", TObjSize<SI4>(new_begin),
               utf.LengthMax());
        utf << TSTRStart<Char>(begin);
        PRINTF("\nCopying \"%s\" with result:\"%s\"", TSTRStart<Char>(begin),
               TSTRStart<Char>(new_begin));
        if (using_heap) delete[] begin;
        obj.begin = new_begin;
        break;
      }
      case kFactoryClone: {
        PRINT("Clone:");
        if (!arg) return kFactoryNilArg;
        CObject* other = reinterpret_cast<CObject*>(arg);
        begin = obj.begin;
        size = *reinterpret_cast<SI4*>(begin);
        UIW* obj = TObjClone<SI4>(begin, size);
        if (!obj) return kFactoryCantGrow;
        other->begin = obj;
        other->factory = other->factory;
        break;
      }
      case kFactoryInfo: {
        PRINT("Info:");
        // 1. Load the pointer to store the string to.
        const CH1** ptr = reinterpret_cast<const CH1**>(arg);
        *ptr = "Strand";
        break;
      }
    }
    PRINT("\nSuccess!");
    return 0;
  }
};

/*
#if USING_UTF1 == YES
using Strand1 = TStrand<CH1>;
#endif
#if USING_UTF2 == YES
using Strand2 = TStrand<CH2>;
#endif
#if USING_UTF4 == YES
using Strand4 = TStrand<CH4>;
#endif*/

}  // namespace _

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::TStrand<Char, kCount_>& o) {
  return o;
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, const CH1* string) {
  return strand.Print(string);
}

#if USING_UTF16 == YES
template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator*(
    ::_::TStrand<Char, kCount_>& strand, const CH2* string) {
  return strand.Print(string);
}
#endif

#if USING_UTF32 == YES
template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator*(
    ::_::TStrand<Char, kCount_>& strand, const CH4* string) {
  return strand.Print(string);
}
#endif

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, Char c) {
  return strand.Print(c);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, UI1 item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, SI2 item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, UI2 item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, SI4 item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, UI4 item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, SI8 item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, UI8 item) {
  return strand.Print(item);
}

#if USING_FP4 == YES

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, FP4 item) {
  return strand.Print(item);
}
#endif
#if USING_FP8 == YES

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, FP8 item) {
  return strand.Print(item);
}
#endif

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::Hex item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::Char1 item) {
  return strand.PrintChar(item.value);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::TCenter<Char> item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::TRight<Char> item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::TLinef<Char> item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::THeadingf<Char> item) {
  return strand.Print(item);
}

template <typename Char, SI4 kCount_>
inline ::_::TStrand<Char, kCount_>& operator<<(
    ::_::TStrand<Char, kCount_>& strand, ::_::TChars<Char> item) {
  return strand.Print(item);
}

#endif
#endif
#endif
