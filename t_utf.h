/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_utf.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_UTF
#ifndef SCRIPT2_TUTF
#define SCRIPT2_TUTF 1

#include "t_puff.h"
#include "t_socket.h"
#include "t_stringf.h"

#if SEAM == SEAM_SCRIPT2_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

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

template <typename T, typename Char = CHR>
Char* TPrintHex(Char* start, Char* stop, const void* begin, SIW size_bytes) {
  Char* end = start + (size_bytes * 2);
  if (!start || size_bytes <= 0 || end < start) return nullptr;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
  while (size_bytes-- > 0) {
    UI1 byte = *cursor++;
    *start++ = HexNibbleToUpperCase(byte >> 4);
    *start++ = HexNibbleToUpperCase(byte & 0xf);
  }
  *start = 0;
  return start;
}

/* Prints a hex value to the Console. */
template <typename Char, typename UI>
Char* TPrintHex(Char* start, Char* stop, UI value) {
  enum { kHexStrandLengthSizeMax = sizeof(UI) * 2 + 3 };

  if (!start || start + kHexStrandLengthSizeMax >= stop) return nullptr;

  *start++ = '0';
  *start++ = 'x';
  auto v = ToUnsigned(value);
  for (SI4 num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    *start++ = HexNibbleToUpperCase((UI1)(v >> num_bits_shift));
  }
  *start = 0;
  return start;
}

/* Prints a hex value to a text socket. */
template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI1 value) {
  return TPrintHex<Char, UI1>(start, stop, (UI1)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI1 value) {
  return TPrintHex<Char, UI1>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI2 value) {
  return TPrintHex<Char, UI2>(start, stop, (UI2)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI2 value) {
  return TPrintHex<Char, UI2>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI4 value) {
  return TPrintHex<Char, UI4>(start, stop, (UI4)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI4 value) {
  return TPrintHex<Char, UI4>(start, stop, value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, SI8 value) {
  return TPrintHex<Char, UI8>(start, stop, (UI8)value);
}

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, UI8 value) {
  return TPrintHex<Char, UI8>(start, stop, value);
}

#if USING_FP4 == YES_0
template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, FP4 value) {
  return TPrintHex<Char, UI4>(start, stop, ToUnsigned(value));
}
#endif
#if USING_FP8 == YES_0
template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, FP8 value) {
  return TPrintHex<Char, UI8>(start, stop, ToUnsigned(value));
}
#endif

template <typename Char = CHR>
inline Char* TPrintHex(Char* start, Char* stop, const void* ptr) {
  return TPrintHex<Char, UIW>(start, stop, ToUnsigned(ptr));
}

/* Prints the given value to Binary. */
template <typename Char = CHR, typename UI>
Char* TPrintBinary(Char* start, Char* stop, UI value) {
  if (start + sizeof(UI) * 8 >= stop) {
    return nullptr;
  }

  for (SI4 i = 0; i < sizeof(UI) * 8; ++i) {
    *start++ = (Char)('0' + (value >> (sizeof(UI) * 8 - 1)));
    value = value << 1;
  }
  *start = 0;
  return start;
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI1 value) {
  return TPrintBinary<Char, UI1>(start, stop, (UI1)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI1 value) {
  return TPrintBinary<Char, UI1>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI2 value) {
  return TPrintBinary<Char, UI2>(start, stop, (UI2)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI2 value) {
  return TPrintBinary<Char, UI2>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI4 value) {
  return TPrintBinary<Char, UI4>(start, stop, (UI4)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI4 value) {
  return TPrintBinary<Char, UI4>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, SI8 value) {
  return TPrintBinary<Char, UI8>(start, stop, (UI8)value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
inline Char* TPrintBinary(Char* start, Char* stop, UI8 value) {
  return TPrintBinary<Char, UI8>(start, stop, value);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
Char* TPrintBinary(Char* start, Char* stop, FP4 value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<Char, UI4>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
Char* TPrintBinary(Char* start, Char* stop, FP8 value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<Char, UI8>(start, stop, ui);
}

/* Prints the given value to Binary. */
template <typename Char = CHR>
Char* TPrintBinary(Char* start, Char* stop, const void* ptr) {
  UIW address = *reinterpret_cast<UIW*>(&ptr);
  return TPrintBinary<Char, UIW>(start, stop, address);
}

/* Prints a single decimal to the socket.
@warning This function DOES NOT do any error checking! */
template <typename T = CH1>
inline T* TWrite(T* socket, T value) {
  *socket++ = value;
  return socket;
}

template <typename Char = CHR>
Char* TPrintChars(Char* begin, Char* end, const Char* start, const Char* stop) {
  if (!start || start >= stop || !end || end >= begin) return nullptr;

  SIW size = stop - start,                     //
      extra_row = ((size & 63) != 0) ? 1 : 0,  //
      row_count = (size >> 6) + extra_row;     //

  SIW num_bytes = 81 * (row_count + 2);
  size += num_bytes;

  begin = Print(begin, end, STRPrintCharsHeader());
  begin = Print(begin, end, STRPrintCharsBorder());
  begin = PrintHex(begin, end, start);

  Char c;
  while (start < stop) {
    *begin++ = '\n';
    *begin++ = '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *start++;
      if (start > stop)
        c = 'x';
      else if (c < ' ')
        c = c + kPrintC0Offset;
      begin = Print(begin, end, c);
    }
    *begin++ = '|';
    *begin++ = ' ';
    begin = PrintHex(begin, end, start);
  }
  begin = Print(begin, end, STRPrintCharsBorder());
  begin = PrintHex(begin, end, start + size);
  return begin;
}

template <typename Char = CHR>
Char* TScan(const Char* start, FP4& result) {
  return nullptr;
}

template <typename Char = CHR>
Char* TScan(const Char* start, FP8& result) {
  return nullptr;
}

#if SEAM >= SEAM_SCRIPT2_FTOS
#endif

/* Prints the given socket to the COut. */
template <typename Char = CHR>
Char* TPrintSocket(Char* start, Char* stop, const void* begin,
                   const void* end) {
  const Char *read = reinterpret_cast<const Char*>(begin),
             *read_end = reinterpret_cast<const Char*>(end);
  if (!start || start >= stop || !begin || read > read_end) return nullptr;

  Char* buffer_begin = start;
  SIW size = read_end - read, num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  if ((stop - start) <= num_bytes) {
    D_PRINTF("\nERROR: buffer overflow trying to fit %i in %i bytes!",
             (SI4)num_bytes, (SI4)(stop - start));
    return nullptr;
  }
  size += num_bytes;
  start = TPrintString<Char>(start, stop, STRPrintCharsHeader());
  start = TPrintString<Char>(start, stop, STRPrintCharsBorder());
  start = TPrintHex<Char>(start, stop, read);

  D_PRINTF("\nBuffer space left:%i", (SI4)(stop - start));
  Char c;
  while (read < read_end) {
    *start++ = kLF;
    *start++ = '|';
    for (SI4 i = 0; i < 64; ++i) {
      c = *read++;
      if (read > read_end)
        c = 'x';
      else if (!c || c == kTAB)
        c = ' ';
      else if (c < ' ')
        c = kDEL;
      *start++ = c;
    }
    *start++ = '|';
    *start++ = ' ';
    start = TPrintHex<Char>(start, stop, read);
  }
  start = TPrintString<Char>(start, stop, STRPrintCharsBorder());
  return TPrintHex<Char>(start, stop, read + size);
}

/* An empty string. */
template <typename Char = CHR>
const Char* TSTREmpty() {
  static const Char kStrand[] = {NIL};
  return kStrand;
}

/* The new-line s. */
template <typename Char = CHR>
const Char* TSTRNL() {
  static const Char kStrand[] = {kLF};
  return kStrand;
}

/* Strand the reads "Error:". */
template <typename Char = CHR>
const Char* TSTRError() {
  static const Char kStrand[] = {kLF, 'E', 'r', 'r', 'o', 'r', ':', NIL};
  return kStrand;
}

/* Converts the given item to a printable CH1 if it's non-printable. */
template <typename Char = CHR>
inline Char TCharPrintable(Char item) {
  if (item < 32 || item == 127) return ' ';
  return item;
}

/* Sets the s to either the given item or empty s if input
is nil. */
template <typename Char = CHR>
inline Char* TSTRSet(Char* string) {
  if (!string) return TSTREmpty<Char>();
  return string;
}

/* Searches fro the s line stop.
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
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
template <typename Char = CHR>
Char* TSTRLineEnd(Char* cursor, SI4 column_count = 80) {
  return const_cast<Char*>(
      TSTRLineEnd(reinterpret_cast<const Char*>(cursor), column_count));
}

/* Finds the stop of the line, wrapped to the given column_count.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param column_coun In characters. */
template <typename Char = CHR>
const Char* TSTRLineEnd(const Char* cursor, const Char* stop,
                        SI4 column_count = 80) {
  if (!cursor) {
    D_PRINTF("\nText buffer overflow!");
    return nullptr;
  }
  A_ASSERT(cursor < stop);
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
template <typename Char = CHR>
inline Char* TSTRLineEnd(Char* cursor, Char* stop, SI4 column_count = 80) {
  return const_cast<const Char*>(
      TSTRLineEnd<Char>(reinterpret_cast<const Char*>(cursor),
                        reinterpret_cast<const Char*>(stop), column_count));
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
const Char* TSTRSkipSpaces(const Char* cursor) {
  if (!cursor) return nullptr;
  Char c = *cursor;
  while (TIsWhitespace<Char>(c)) {
    D_COUT('.');
    if (!c) return cursor;  //< This isn't an error as far as I can see.
    ++cursor;
    c = *cursor;
  }
  return cursor;
}

/* Scrolls over any whitespace.
@param  cursor  The first Char in the buffer. */
template <typename Char = CHR>
Char* TSTRSkipSpaces(Char* cursor) {
  return const_cast<Char*>(TSTRSkipSpaces<Char>(cursor));
}

/* Attempts to find the given query.
@return Nil upon failed search or a pointer to the stop of the cursor query.
@param  cursor  The first Char in the buffer.
@param  query   A query string.  */
template <typename Char = CHR>
const Char* TSTRFind(const Char* start, const Char* query) {
  A_ASSERT(start);
  A_ASSERT(query);

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
template <typename Char = CHR>
inline Char* TSTRFind(Char* string, const Char* query) {
  return const_cast<Char*>(
      TSTRFind<Char>(reinterpret_cast<const Char*>(string),
                     reinterpret_cast<const Char*>(query)));
}

/* Strand skip spaces.
@return Nil if there are no spaces to skip. */
template <typename Char = CHR>
const Char* TSTRSkipSpaces(const Char* cursor, const Char* stop) {
  if (!cursor) return nullptr;
  if (cursor > stop) return nullptr;
  D_PRINTF("\nSkipping spaces: ");
  Char c = *cursor;
  while (IsWhitespace(c)) {
    D_COUT('.');
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
template <typename Char = CHR>
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
template <typename Char = CHR>
const Char* TSTREquals(const Char* string_a, const Char* string_b) {
  A_ASSERT(string_a);
  A_ASSERT(string_b);
  D_PRINTF("\nComparing \"%s\" to \"%s\"", string_a, string_b);

  Char a = *string_a, b = *string_b;
  while (a) {
    D_COUT(a);
    if (a != b) {  // Not a hit.
      D_PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      D_PRINTF("\nFound hit at 0x%p", string_a);
      return string_a;
    }
    a = *(++string_a);
    b = *(++string_b);
  }
  if (b) {
    D_PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  D_PRINTF("\nFound hit at 0x%p", string_a);
  return string_a;  //< Find hit!
}

/* Checks if the two strings are the same.
@return Nil upon strings not being the same or a pointer to the stop of the
equivalent s upon success.
@param  string_a  A cursor to compare to string_b.
@param  string_b  A cursor to compare to string_a.
*/
template <typename Char = CHR>
inline Char* TSTREquals(Char* string_a, const Char* string_b) {
  return const_cast<Char*>(
      TSTREquals<Char>(reinterpret_cast<const Char*>(string_a),
                       reinterpret_cast<const Char*>(string_b)));
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CHR>
const Char* TSTREquals(const Char* cursor, const Char* stop,
                       const Char* query) {
  if (!cursor) return nullptr;
  A_ASSERT(cursor < stop);
  if (!query) return nullptr;

  D_PRINTF("\nComparing \"%s\" to \"%s\"", cursor, query);

  Char a = *cursor, b = *query;
  while (a) {
    D_COUT(a);
    if (a != b) {  // Not a hit.
      D_PRINTF("\nBut it's not a hit");
      return nullptr;
    }
    if (b == 0) {  // Hit!
      D_PRINTF("\nFound hit at 0x%p", cursor);
      return cursor;
    }
    if (cursor > stop) {
      return nullptr;
    }
    a = *(++cursor);
    b = *(++query);
  }
  if (b) {
    D_PRINTF("\nNot a hit: no nil-term Char found");
    return nullptr;
  }
  D_PRINTF("\nFound hit at 0x%p.", cursor);
  return cursor;
}

/* Compares the two strings to see if the are equal.
@return Nil of the two strings aren't equal or a pointer to the stop of the
s upon success. */
template <typename Char = CHR>
Char* TSTREquals(Char* cursor, Char* stop, const Char* query) {
  return const_cast<Char*>(TSTREquals(reinterpret_cast<const Char*>(cursor),
                                      reinterpret_cast<const Char*>(stop),
                                      query));
}

/* Checks if the given s isn't empty.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@desc A s is defined as empty if it is NIL or all whitespace. */
template <typename Char = CHR>
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
template <typename Char = CHR>
BOL TSTRIsntEmpty(Char* cursor) {
  return TSTRIsntEmpty<Char>(reinterpret_cast<const Char*>(cursor));
}

/* Checks to see if the cursor isn't empty or whitespace.
@return False if the s is empty and true otherwise.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer. */
template <typename Char = CHR>
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
template <typename Char = CHR>
BOL TSTRIsntEmpty(Char* cursor, const Char* stop) {
  return TSTRIsntEmpty(reinterpret_cast<const Char*>(cursor),
                       reinterpret_cast<const Char*>(stop));
}

/* Prints the given item aligned right the given column_count.
@return Nil if any of the pointers are nil or if column_count < 1, and a
pointer to the nil-term CH1 upon success.
@param  cursor  The first Char in the buffer.
@param  stop    The last Char in the buffer.
@param  item  The item to utf.
@param  column_count The token_ of columns to align right to. */
template <typename Char = CHR>
Char* TPrintRight(Char* cursor, Char* stop, const Char* item,
                  SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;
  D_PRINTF("\ncursor:%p end:%p", cursor, stop);

  if (!cursor || column_count < 1) return nullptr;

  if (cursor + column_count > stop) {
    D_COUT("\nBuffer overflow!");
    return nullptr;
  }

  auto item_end = TSTREnd<Char>(item);
  Char c;  //< Temp variable.
  if (item == item_end) return cursor;
  SIW length = item_end - item;

  // If the length is less than the column_count we need to print ".", "..",
  // "..." or nothing and chop off some of the item.
  SIW count = column_count - length;
  D_PRINTF("\n\nPrinting \"%s\":%i aligned right %i columns count:%i", item,
           (SI4)length, column_count, count);
  if (count < 0) {
    SIW dot_count = length + count;
    D_PRINTF(" dot_count:%i", (int)dot_count);
    if (dot_count <= 3) {
      D_PRINTF("\n Wrote dots:\"");
      while (dot_count-- > 0) {
        *cursor++ = '.';
        D_COUT('.');
      }
      D_COUT('\"');
      *cursor = 0;
      return cursor;
    }
    stop = cursor + column_count;
    *stop-- = 0;
    *stop-- = '.';
    *stop-- = '.';
    *stop-- = '.';
    item_end = item + column_count - 4;
    D_PRINTF("\n Wrote with dots backwards:\"...");
    while (item_end > item) {
      c = *item_end--;
      *stop-- = c;
      D_COUT(c);
    }
    c = *item_end--;
    *stop-- = c;
    D_COUT(c);
    D_PRINTF("\"");
    return cursor + column_count;
  }
  D_PRINTF("\ncursor:0x%p end:0x%p item:0x%p token_end:0x%p", cursor, stop,
           item, item_end);
  // In order to keep the current cache lines we're going to utf
  // backwards back from the token_end.
  D_PRINTF("\n Wrote backwards:\"");
  stop = cursor + column_count;
  --item_end;   //< This is pointed at the nil-term CH1
  *stop-- = 0;  //< and there is no need to load a 0.
  while (item_end >= item) {
    c = *item_end--;
    *stop-- = c;
    D_COUT(c);
  }
  while (stop >= cursor) {
    *stop-- = ' ';
    D_COUT(' ');
  }
  D_PRINTF("\"\nWrote:\"%s\"", cursor);
  return cursor + column_count;
}

/* Prints the given cursor center aligned to the given column_count. */
template <typename Char = CHR>
Char* TPrintCenter(Char* cursor, Char* stop, const Char* string,
                   SI4 column_count = 80) {
  if (!cursor || cursor >= stop) return nullptr;

  // We need to leave at least one space to the left and right of
  SI4 length = TSTRLength<Char>(string);
  D_PRINTF("\n\nPrinting \"%s\":%i centered to %i columns", string, length,
           column_count);
  SI4 delta;
  if (length <= column_count) {
    delta = (column_count - length) >> 1;  //< >> 1 to /2
    length = column_count - length - delta;
    D_PRINTF("\nlength:%i offset:%i", length, delta);

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
template <typename Char = CHR>
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
template <typename Char = CHR>
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
template <typename Char = CHR>
Char* TPrintHeadingf(Char* start, Char* stop, Char item, SIW count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints the given cursor repeated to make a line. */
template <typename Char = CHR>
Char* TPrintHeadingf(Char* start, Char* stop, const Char* item,
                     SIW count = 80) {
  return TPrintLinef<Char>(start, stop, item, count, nullptr, nullptr);
}

/* Prints a cursor to the given buffer without */
template <typename Char = CHR>
Char* TPrintWrap(Char* cursor, Char* stop, const Char* string,
                 SIW column_count = 80) {
  if (!cursor || cursor <= stop || !string) return nullptr;
  if (column_count < 2) return cursor;

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

/* Returns the first CH1 in the cursor socket. */
template <typename Char = CHR, typename SIZ = SI4>
inline Char* TSTRStart(UIW* start) {
  UIW address = reinterpret_cast<UIW>(start) + sizeof(SIZ);
  return reinterpret_cast<Char*>(address);
}

/* Searches for the stop of the strand. */
template <typename Char = CHR, typename SIZ = SI4>
inline Char* TSTRStop(void* begin) {
  SIZ size = *reinterpret_cast<SIZ*>(begin);
  UIW address = reinterpret_cast<UIW>(begin);
  Char* ptr = reinterpret_cast<Char*>(address + sizeof(SIZ));
  return ptr + (size >> TBitShiftCount<Char>()) - 1;
}

/* Searches for the stop of the strand. */
template <typename Char = CHR, typename SIZ = SI4>
inline Char* TSTRStop(void* begin, SIW size_bytes) {
  UIW address = reinterpret_cast<UIW>(begin);
  Char* ptr = reinterpret_cast<Char*>(address + sizeof(SIZ));
  return ptr + (size_bytes >> TBitShiftCount<Char>()) - 1;
}

/* Utility class for printing numbers. */
template <typename Char = CHR, SIN kLengthMax = 31>
class TStringf {
  SIW count_;
  Char string_[kLengthMax + 1];  //< Strand buffer for the token.

 public:
  enum { kLengthMax = kLengthMax };

  TStringf(CH1 item = 0, SI4 count = kLengthMax)
      : string_(string_), count_(count) {
    auto cursor = string_;
    *cursor = item;
    *cursor = 0;
  }

  TStringf(const CH1* item, SI4 count = kLengthMax)
      : string_(item), count_(count) {
    if (!item) *string_ = 0;
  }

  TStringf(CH2 item = 0, SI4 count = kLengthMax)
      : string_(string_), count_(count) {
    auto cursor = string_;
    *cursor = item;
    *cursor = 0;
  }

  TStringf(const CH2* item, SI4 count = kLengthMax)
      : string_(item), count_(count) {
    if (!item) *string_ = 0;
  }

  TStringf(CH4 item = 0, SI4 count = kLengthMax)
      : string_(string_), count_(count) {
    auto cursor = string_;
    *cursor = item;
    *cursor = 0;
  }

  TStringf(const CH4* item, SI4 count = kLengthMax)
      : string_(item), count_(count) {
    if (!item) *string_ = 0;
  }

#if CPU_WORD_SIZE < 64
  TStringf(SI4 item, SI4 count = kLengthMax) : string_(string_), count_(count) {
    TPrint<Char>(string_, string_ + kLengthMax, item);
  }

  /* Prints the item to the token_. */
  TStringf(UI4 item, SI4 count = kLengthMax) : string_(string_), count_(count) {
    TPrint<Char>(string_, string_ + kLengthMax, item);
  }
#endif

  /* Prints the item to the token_. */
  TStringf(SI8 item, SI4 count = kLengthMax) : string_(string_), count_(count) {
    TPrint<Char>(string_, string_ + kLengthMax, item);
  }

  /* Prints the item to the token_. */
  TStringf(UI8 item, SI4 count = kLengthMax) : string_(string_), count_(count) {
    TPrint<Char>(string_, string_ + kLengthMax, item);
  }

#if USING_FP4 == YES_0
  /* Prints the item to the token_. */
  TStringf(FP4 item, SI4 count = kLengthMax) : string_(string_), count_(count) {
    TPrint<Char>(string_, string_ + kLengthMax, item);
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the item to the token_. */
  TStringf(FP8 item, SI4 count = kLengthMax) : string_(string_), count_(count) {
    TPrint<Char>(string_, string_ + kLengthMax, item);
  }
#endif

  /* Gets the string_. */
  inline const Char* String() { return string_; }

  /* Gets the strand_. */
  inline Char* Strand() { return string_; }

  /* Gets the string_ or the strand_ if the string_ is nil. */
  inline const Char* Get() {
    const Char* ptr = string_;
    return ptr ? ptr : string_;
  }

  /* Sets the string_ to the new string.
  @return Nil upon failure or the string upon success. */
  inline const CH1* Set(const CH1* string) {
    if (!string) return string;
  }

  /* Gets the count. */
  inline SI4 Count() { return count_; }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH1 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH1* item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH2 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH2* item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(CH4 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(const CH4* item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI4 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI4 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(SI8 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

  /* Prints the given item to the strand_. */
  inline Char* Print(UI8 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }

#if USING_FP4 == YES_0
  /* Prints the given item to the strand_. */
  inline Char* Print(FP4 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item to the strand_. */
  inline Char* Print(FP8 item) {
    auto cursor = _::TPrint<Char>(string_, kLengthMax, item);
    string_ = nullptr;
    return cursor;
  }
#endif
};

/* Universal Text Formatter (UTF).
The UTF only stores the start and stop pointers allowing the length to be
storred on the stack or hard-coded using instructions. If you want an normal
string-like class please use the TStrand, which auto-grows from stack to heap.
*/
template <typename Char = CHR, typename SIZ = SI4>
struct TUTF {
  Char *start,  //< Start address.
      *stop;    //< Stop address.

  /* Default constructor does nothing. */
  TUTF() {}

  /* Initializes the UTF& from the given begin pointers.
  @param start The begin of the begin.
  @param count The number of Char(s) in the buffer. */
  TUTF(Char* start, SIZ count) : start(start), stop(start + count - 1) {
    D_ASSERT(start);
    D_ASSERT(count >= 0);
    Reset();
  }

  /* Initializes the UTF& from the given begin pointers.
  @param begin The begin address of a word-aligned socket.
  @param count The number of Char(s) in the buffer. */
  TUTF(UIW* begin, SIZ count)
      : start(reinterpret_cast<Char*>(begin)),
        stop(TPtr<Char>(begin, count - 1)) {
    D_ASSERT(start);
    Reset();
  }

  /* Initializes the UTF& from the given begin pointers.
  @param begin The begin address of a word-aligned socket.*/
  TUTF(UIW* begin)
      : start(TSTRStart<Char, SIZ>(begin)), stop(TSTRStop<Char, SIZ>(begin)) {
    D_ASSERT(begin);
    Reset();
  }

  /* Initializes the array pointers from the given start and stop pointers.
  @param start The start of the array.
  @param stop   The stop of the array. */
  TUTF(Char* start, Char* stop) : start(start), stop(stop) {
    D_ASSERT(start);
    D_ASSERT(start < stop);
    Reset();
  }

  /* Clones the other utf. */
  TUTF(const TUTF& other)
      : start(other.start), stop(other.stop) {  // Nothing to do here!.
  }

  UI1* End() { return reinterpret_cast<UI1*>(start) + (sizeof(Char) - 1); }

  SIZ SizeBytes() { return (SIZ)(stop - start + sizeof(Char)); }

  void Wipe() { SocketWipe(start, stop); }

  /* Writes a nil-term CH1 at the start of the strand. */
  inline Char* Reset() {
    *start = 0;
    return start;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TUTF& Set(Char* cursor) {
    D_ASSERT(cursor);
    start = cursor;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline TUTF& Set(UIW* buffer) {
    D_ASSERT(buffer);
    SIZ size = *reinterpret_cast<SIZ*>(buffer);
    UIW ptr = reinterpret_cast<UIW>(buffer) + sizeof(SIZ);
    Char* start_ptr = reinterpret_cast<Char*>(ptr);
    start = start_ptr;
    stop = start_ptr + size - 1;
    return *this;
  }

  /* Sets the start pointer to the new_pointer. */
  inline void Set(TUTF<Char> other) {
    start = other.start;
    stop = other.stop;
  }

  /* Finds the length of the STR in Chars. */
  inline SIZ SpaceLeft() { return (SIZ)(stop - start); }

  /* Calculates the max length of the string in Chars. */
  inline SIZ LengthMax() { return stop - start; }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH1 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH2 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& PrintChar(CH4 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH1 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH2 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(CH4 item) { return PrintChar(item); }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH1* item) {
    return Set(_::TPrintString<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH2* item) {
    return Set(_::TPrintString<Char>(start, stop, item));
  }

  /* Prints a CH1 to the strand. */
  inline TUTF& Print(const CH4* item) {
    return Set(_::TPrintString<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TUTF& Print(SI4 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TUTF& Print(UI4 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TUTF& Print(SI8 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

  /* Prints the given item. */
  inline TUTF& Print(UI8 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }

#if USING_FP4 == YES_0
  /* Prints the given item.
  @return A UTF. */
  inline TUTF& Print(FP4 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item.
  @return A UTF. */
  inline TUTF& Print(FP8 item) {
    return Set(_::TPrint<Char>(start, stop, item));
  }
#endif

  /* Prints the given item. */
  inline TUTF& Print(Hexf item) { return TPrintHex<TUTF>(*this, item.element); }

  /* Prints the given item. */
  inline TUTF& Print(Rightf item) {
    return TPrintRight<TUTF>(*this, item.element);
  }

  /* Prints the given item. */
  inline TUTF& Print(Centerf item) {
    return TPrintCenter<TUTF>(*this, item.element);
  }

  /* Prints the given item. */
  inline TUTF& Print(Linef item) { return TPrintLinef<TUTF>(*this, item); }

  /* Prints the given item. */
  inline TUTF& Print(Headingf item) {
    return TPrintHeadingf<TUTF>(*this, item);
  }

  /* Prints the given pointer as hex. */
  inline TUTF& Hex(Hexf item) {
    return TPrintHex<Char>(*this, item.element.Ptr(), item.element.count);
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

#if USING_FP4 == YES_0
  /* Prints the given item as hex. */
  inline TUTF& Hex(FP4 item) { return Set(TPrintHex<Char>(start, stop, item)); }
#endif
#if USING_FP8 == YES_0
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

#if USING_FP4 == YES_0
  /* Prints the given item as binary. */
  inline TUTF& Binary(FP4 item) { return Set(Binary<Char>(start, stop, item)); }
#endif
#if USING_FP8 == YES_0
  /* Prints the given item as binary. */
  inline TUTF& Binary(FP8 item) { return Set(Binary<Char>(start, stop, item)); }
#endif
  /* Prints the given pointer as binary. */
  inline TUTF& Binary(const void* ptr) {
    UIW address = reinterpret_cast<UIW>(ptr);
    return Set(Binary<Char>(start, stop, address));
  }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    o << "\nTUTF<CH" << sizeof(Char) << ", SI" << sizeof(SIZ) << ">{ start:";
    TPrintHex<Printer>(o, start);
    o << " stop:";
    TPrintHex<Printer>(o, stop);
    return o << " }\n";

#if DEBUG_THIS
    TPrintSocket<Printer>(o, start, End());
    return TPrintChars<Printer, Char>(o, start, stop);
#endif
  }
};

/* Queries the given s for the given query. */
template <typename Char = CHR>
SI4 TSTRQuery(const Char* cursor, const Char* stop, const Char* query) {
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
      D_PRINTF(" is not a hit.");
      return result;
    }
    if (!a) {
      D_PRINTF(" is a partial match but !a.");
      return result;
    }
    if (++cursor >= stop) {
      D_PRINTF(" but buffer overflowed!");
      return result;
    }
    ++query;
    a = *cursor;
    b = *query;
  }
  if (a && !TIsWhitespace<Char>(a)) {
    D_PRINTF(" is only a partial match but found %s", (a ? "a" : "space"));
    return b - a;
  }
  D_PRINTF(" is a match!");
  return 0;
}

}  // namespace _

/* Prints the given item to the UTF.
@return The utf.
@param  utf The utf.
@param  item   The item to utf. */
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, CH1 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, const CH1* item) {
  return utf.Print(item);
}

#if USING_UTF16 == YES_0
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, CH2 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, const CH2* item) {
  return utf.Print(item);
}
#endif
#if USING_UTF32 == YES_0
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, CH4 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, const CH4* item) {
  return utf.Print(item);
}
#endif

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI1 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI1 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI2 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI2 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI4 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI4 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, SI8 item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, UI8 item) {
  return utf.Print(item);
}

#if USING_FP4 == YES_0
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, FP4 item) {
  return utf.Print(item);
}
#endif

#if USING_FP8 == YES_0
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, FP8 item) {
  return utf.Print(item);
}
#endif

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Centerf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Centerf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Rightf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Rightf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Linef item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Linef& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Headingf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Headingf& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TStringf<Char> item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::TStringf<Char>& item) {
  return utf.Print(item);
}

template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Hexf item) {
  return utf.Print(item);
}
template <typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Hexf& item) {
  return utf.Print(item);
}

template <typename Printer, typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Charsf item) {
  return utf.Print(item);
}
template <typename Printer, typename Char = CHR>
inline _::TUTF<Char>& operator<<(_::TUTF<Char>& utf, _::Charsf& item) {
  return utf.Print(item);
}
#endif
#endif
