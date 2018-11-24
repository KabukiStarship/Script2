/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cutf1.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= _0_0_0__02
#ifndef INCLUDED_SCRIPTUTF8
#define INCLUDED_SCRIPTUTF8

#include "casciidata.h"
#include "cclock.h"

#ifndef USING_UTF8
#define USING_UTF8 YES
#endif

#if USING_UTF8 == YES

namespace _ {

/* UTF-8 printing utilities.
@ingroup UTF1
*/

/* Checks if the given character is whitespace. */
API BOL IsWhitespace(char character);

/* Converts the given value to a printable char if it's non-printable. */
API char PrintableChar(char value);

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
char. */
API const char* StringEnd(const char* text);

/* Gets the length of the given char.
@return  Returns -1 if the text char is nil.
@warning This function is only safe to use on ROM strings with a nil-term
char. */
API int StringLength(const char* text);

/* Clones the given string_.
@param  A nil-terminated string_ in ROM.
@return Returns a new copy you must delete.
API char* StringClone(const char* text); */

/* Returns a pointer to the char at the stop of the line. */
API const char* StringLineEnd(const char* text, int column_count);

/* Returns a pointer to the char at the stop of the row. */
API const char* StringLineEnd(const char* text, const char* text_end,
                              int column_count);

/* Returns the pointer to the next char in the char that is not an ASCII
number_.
@return A pointer to the next non-number_ in the text char. */
API const char* StringDecimalStop(const char* text, const char* text_end);

/* Returns the pointer to the next char in the char that is not an ASCII
number_.
@return A pointer to the next non-number_ in the text char. */
API const char* StringDecimalStop(const char* text);

/* Skips the leading zeros of a number_ if there are any. */
API const char* TStringSkipChar(const char* text, char skip_char);

/* Skips all the spaces at the start of the char. */
API const char* StringSkipSpaces(const char* text);

/* Skips all the spaces at the start of the char.
@param  start Beginning address of the read socket.
@param  stop   The stop address of the input socket.
@return A pointer to the stop of the text read or if no text read. */
API const char* StringSkipSpaces(const char* text, const char* text_end);

/* Compares the source and query char as nil-terminated strings. */
API const char* StringEquals(const char* text_a, const char* text_b);

/* Compares the source and query char as nil-terminated strings. */
API const char* StringEquals(const char* text, const char* text_end,
                             const char* query);

/* Searches the given char for the given char.
@param  text      The char to search.
@param  query      The char to search for.
@return Returns nil if the parsing failed and a pointer to the first char
after the stop of the text upon success. */
API const char* StringFind(const char* text, const char* query);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param  start  The beginning address of the socket.
@param  stop    The stop address of the socket.
@param  string_ The potentially unsafe string_ to write. */
API char* Print(char* start, char* stop, const char* string_);

/* Writes the give char to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The value to write. */
API char* Print(char* start, char* stop, char character);

/* Writes the give char to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* Print(char* start, char* stop, UI4 value);

/* Writes the give char to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* Print(char* start, char* stop, SI4 value);

/* Writes the give char to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* Print(char* start, char* stop, UI8 value);

/* Writes the give char to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* Print(char* start, char* stop, SI8 value);

#if SEAM >= _0_0_0__03

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintCenter(char* start, char* stop, FLT value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintCenter(char* start, char* stop, DBL value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintRight(char* start, char* stop, FLT value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintRight(char* start, char* stop, DBL value, int column_count);

#endif  //< _0_0_0__01

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string_ The potentially unsafe string_ to write. */
API char* PrintCenter(char* start, char* stop, const char* string_,
                      int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start Beginning address of the socket.
@param stop The stop address of the socket.
@param character The value to write. */
API char* PrintCenter(char* start, char* stop, char character,
                      int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintCenter(char* start, char* stop, UI4 valu, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintCenter(char* start, char* stop, SI4 value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintCenter(char* start, char* stop, UI8 value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintCenter(char* start, char* stop, SI8 value, int column_count);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string_ The potentially unsafe string_ to write. */
API char* PrintRight(char* start, char* stop, const char* string_,
                     int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The value to write. */
API char* PrintRight(char* start, char* stop, char character, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintRight(char* start, char* stop, UI4 value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintRight(char* start, char* stop, SI4 value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintRight(char* start, char* stop, UI8 value, int column_count);

/* Writes the give char to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintRight(char* start, char* stop, SI8 value, int column_count);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string_ The potentially unsafe string_ to write. */
API char* PrintHex(char* start, char* stop, const void* pointer);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, SI1 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, UI2 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, SI2 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, UI4 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, SI4 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, UI8 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, SI8 value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, FLT value);

/* Writes the give char to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintHex(char* start, char* stop, DBL value);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param pointer The pointer to utf to hex. */
API char* PrintBinary(char* start, char* stop, const void* pointer);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, UI1 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, SI1 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, UI2 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, SI2 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, UI4 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, SI4 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, UI8 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, SI8 value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, FLT value);

/* Writes the give char to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char* PrintBinary(char* start, char* stop, DBL value);

/* Prints the given memory socket to the text socket. */
API char* PrintSocket(char* start, char* stop, const void* begin, size_t size);

/* Prints out the contents of the address to the utf socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param start The beginning of the write socket.
@param stop   The stop of the write socket.
@param start The beginning of the read socket.
@param stop  The stop of the read socket. */
API char* PrintSocket(char* start, char* stop, const void* begin,
                      const void* end);

/* Prints a line of the given column_count.
@return Returns a pointer to the next char after the stop of the read number_ or
nil upon failure.
@param start The beginning of the write socket.
@param stop   The stop of the write socket.
@param token The token to utf.
@param column_count The number_ of tokens to utf. */
API char* PrintLine(char* cursor, char* stop, char token, int column_count);

/* Prints a line of the given column_count.
@return Returns a pointer to the next char after the stop of the read number_ or
nil upon failure.
@param start  The beginning of the write socket.
@param stop    The stop of the write socket.
@param string_ The string_ to utf.
@param column_count The number_ of columns. */
API char* TPrintLineString(char* cursor, char* stop, const char* string_,
                           int column_count);

/* Converts the given string_ to a 8-bit signed integer.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param  text A nil-terminated string_ in ROM.
@param  result  The result of the conversion. */
API const char* Scan(const char* start, SI1& result);

/* Converts the given string_ to a 8-bit signed integer.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param  text A nil-terminated string_ in ROM.
@param  result  The result of the conversion. */
API const char* Scan(const char* text, SI1& result);

/* Converts the given string_ to a 8-bit unsigned integer.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param  text A nil-terminated string_ in ROM.
@param  result  The result of the conversion. */
API const char* Scan(const char* text, UI1& result);

/* Converts the given string_ to a 16-bit signed integer.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, SI2& result);

/* Converts the given string_ to a 16-bit unsigned integer.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, UI2& result);

/* Converts the given string_ to a 32-bit signed integer.
@param  text A nil-terminated string_ in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, SI4& result);

/* Converts the given string_ to a 32-bit unsigned integer.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, UI4& result);

/* Converts the given string_ to a 64-bit signed integer.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, SI8& result);

/* Converts the given string_ to a 64-bit unsigned integer.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, UI8& result);

/* Converts the given string_ to a 32-bit floating-point number_.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, FLT& result);

/* Converts the given string_ to a 64-bit floating-point number_.
@param  text  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char after the stop
of the read number_ or nil upon failure. */
API const char* Scan(const char* text, DBL& result);

/* AsciiFactory Prints the socket to the console as a UTF-8 string_. */
UIW* COutUtf8(UIW* socket, SIW size);

/* Prints the socket to the console as a UTF-8 string_. */
void COutAutoUtf8(UIW* socket);

/* Utility class for printing strings.
This class only stores the stop of socket pointer and a pointer to the write
start. It is up the user to store start of socket pointer and if they would
like to replace the start with the beginning of socket pointer when they
are done printing.
*/
struct API UTF1 {
  char *start,  //< Write start pointer.
      *stop;    //< End of socket pointer.

  /* Initializes the Utf& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF1(char* start, size_t size);

  /* Initializes the Utf& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF1(char* start, char* stop);

  /* Clones the other utf. */
  UTF1(const UTF1& other);

  /* Sets the start pointer to the new_pointer. */
  inline UTF1& Set(char* new_pointer);

  /* Prints the given value as hex. */
  inline UTF1& Hex(SI1 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(UI1 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(SI2 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(UI2 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(SI4 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(UI4 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(SI8 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(UI8 value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(FLT value);

  /* Prints the given value as hex. */
  inline UTF1& Hex(DBL value);

  /* Prints the given pointer as hex. */
  inline UTF1& Hex(const void* pointer);

  /* Prints the given value as binary. */
  inline UTF1& Binary(SI1 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(UI1 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(SI2 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(UI2 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(SI4 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(UI4 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(SI8 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(UI8 value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(FLT value);

  /* Prints the given value as binary. */
  inline UTF1& Binary(DBL value);

  /* Prints the given pointer as binary. */
  inline UTF1& Binary(const void* pointer);
};

/* Utility class for printing numbers. */
class Utf8Text {
 public:
  /* Default constructor does nothing. */
  Utf8Text();

  /* Prints the value to the text socket. */
  Utf8Text(char character);

  /* Prints the value to the text socket. */
  Utf8Text(SI4 value);

  /* Prints the value to the text socket. */
  Utf8Text(UI4 value);

  /* Prints the value to the text socket. */
  Utf8Text(SI8 value);

  /* Prints the value to the text socket. */
  Utf8Text(UI8 value);

#if SEAM >= _0_0_0__03
  /* Prints the value to the text socket. */
  Utf8Text(FLT value);

  /* Prints the value to the text socket. */
  Utf8Text(DBL value);
#endif
  /* Gets the number_ string_. */
  const char* String();

 private:
  enum { kSize = 24 };

  char string_[kSize * sizeof(char) + 1];  //< String socket.
};

/* Utility class for printing hex with operator<<. */
class Utf8Center {
 public:
  /* Prints the value to the text socket. */
  Utf8Center(const char* string_, int column_count);

  /* Prints the value to the text socket. */
  Utf8Center(SI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Center(UI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Center(SI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Center(UI8 value, int column_count);

#if SEAM >= _0_0_0__03
  /* Prints the value to the text socket. */
  Utf8Center(FLT value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Center(DBL value, int column_count);
#endif

  /* Gets the number_ string_. */
  const char* String();

  /* Gets the column_count. */
  int GetColumnCount();

 private:
  const char* string_;  //< Pointer to the string_.
  Utf8Text number_;     //< Pointer to a pointer to utf.
  int column_count;     //< Number of columns to center.
};

/* Utility class for printing hex with operator<<. */
class Utf8Right {
 public:
  /* Prints the value to the text socket. */
  Utf8Right(const char* string_, int column_count);

  /* Prints the value to the text socket. */
  Utf8Right(SI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Right(UI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Right(SI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Right(UI8 value, int column_count);

#if SEAM >= _0_0_0__03
  /* Prints the value to the text socket. */
  Utf8Right(FLT value, int column_count);

  /* Prints the value to the text socket. */
  Utf8Right(DBL value, int column_count);
#endif

  /* Gets the number_ string_. */
  const char* String();

  /* Gets the column_count. */
  int GetColumnCount();

 private:
  const char* string_;  //< Pointer to the string_.
  Utf8Text number_;     //< Pointer to a pointer to utf.
  int column_count;     //< Number of columns to center.
};

/* Utility class for printing a single char token line with operator<<. */
struct API Utf8Line {
  char token;        //< Character to utf.
  int column_count;  //< Column count.

  /* Constructor. */
  Utf8Line(char token, int column_count);
};

/* Utility class for printing a string_ line with operator<<. */
struct API Utf8LineString {
  const char* string_;  //< Character to utf.
  int column_count;     //< Column count.

  /* Constructor. */
  Utf8LineString(const char* string_, int column_count);
};

// class API Utf8String {
// public:
//  /* Constructs a bank UTF-8 string_ with dynamic memory. */
//  Utf8String();
//
//  /* Calls the destructor if there is one. */
//  ~Utf8String();
//
// private:
//};

}  // namespace _

/* Writes a nil-terminated UTF-8 or ASCII string_ to the utf.
@param  utf The utf.
@param  value   The value to utf.
@return The utf. */
API _::UTF1& operator<<(_::UTF1& utf, const char* string_);

/* Writes the given value to the utf.
@param  utf The utf.
@param  value   The value to utf.
@return The utf. */
API _::UTF1& operator<<(_::UTF1& utf, char value);

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
API _::UTF1& operator<<(_::UTF1& utf, UI1 value);

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
API _::UTF1& operator<<(_::UTF1& utf, SI2 value);

/* Writes the given value to the utf.
@param  utf The utf.
@param  value The value to write to the utf.
@return The utf. */
API _::UTF1& operator<<(_::UTF1& utf, UI2 value);

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, SI4 value);

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, UI4 value);

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, SI8 value);

/* Writes the given value to the utf.
@return The utf.
@desc
@param  utf The utf.
@param  value The value to write to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, UI8 value);

#if SEAM >= _0_0_0__01
/* Writes the given value to the utf.
@return The utf.
@desc
@param  utf The utf.
@param  value The value to write to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, FLT value);

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  value The value to write to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, DBL value);
#endif

/* Writes the given value to the utf.
@return The utf.
@param  utf The utf.
@param  item The item to write to utf. */
API _::UTF1& operator<<(_::UTF1& utf, _::Utf8Center item);

/* Writes the given value to the utf justified right.
@return The utf.
@param  utf The utf.
@param  item The item to utf. */
API _::UTF1& operator<<(_::UTF1& utf, _::Utf8Right item);

/* Prints a line of the given column_count to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, _::Utf8Line line);

/* Prints a line string_ of the given column_count to the utf. */
API _::UTF1& operator<<(_::UTF1& utf, _::Utf8LineString line);

#endif  //< #if USING_UTF8
#endif  //< #if INCLUDED_SCRIPTUTF8
#endif  //< #if SEAM >= _0_0_0__02
