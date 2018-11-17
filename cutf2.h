/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cutf2.h
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
#ifndef INCLUDED_SCRIPTPRINT_UTF16
#define INCLUDED_SCRIPTPRINT_UTF16

#include "clock.h"

#if USING_UTF16

namespace _ {

/* UTF-8 printing utilities
@ingroup Utf
*/

/* Checks if the given character is whitespace.
 */
API BOL IsWhitespace(char16_t character);

/* Converts the given value to a printable char16_t if it's non-printable. */
API char16_t PrintableChar(char16_t value);

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
char16_t. */
API const char16_t* TStringEnd(const char16_t* text);

/* Gets the length of the given char16_t.
@return  Returns -1 if the text char16_t is nil.
@warning This function is only safe to use on ROM strings with a nil-term
char16_t. */
API int TStringLength(const char16_t* text);

/* Clones the given string.
@param  A nil-terminated string in ROM.
@return Returns a new copy you must delete. */
API char16_t* StringClone(const char16_t* text);

/* Returns a pointer to the char16_t at the stop of the line. */
API const char16_t* StringLineEnd(const char16_t* text, int column_count);

/* Returns the pointer to the next char16_t in the char16_t that is not an ASCII
number.
@return A pointer to the next non-number in the text char16_t. */
API const char16_t* TStringDecimalEnd(const char16_t* start);

/* Returns the pointer to the next char16_t in the char16_t that is not an ASCII
number.
@return A pointer to the next non-number in the text char16_t. */
API const char16_t* TStringDecimalEnd(const char16_t* start);

/* Skips the leading zeros of a number if there are any. */
API const char16_t* TStringSkipChar(const char16_t* text, char16_t skip_char);

/* Skips all the spaces at the start of the char16_t. */
API const char16_t* StringSkipSpaces(const char16_t* text);

/* Compares the source and query char16_t as nil-terminated strings. */
API const char16_t* StringEquals(const char16_t* text_a,
                                 const char16_t* text_b);

/* Searches the given char16_t for the given char16_t.
@param  text      The char16_t to search.
@param  query      The char16_t to search for.
@return Returns nil if the parsing failed and a pointer to the first char16_t
after the stop of the text upon success. */
API const char16_t* StringFind(const char16_t* start, const char16_t* query);

/* Prints the given string to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param  start  The beginning address of the socket.
@param  stop    The stop address of the socket.
@param  string The potentially unsafe string to write. */
API char16_t* Print(char16_t* start, char16_t* stop, const char16_t* string);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The value to write. */
API char16_t* Print(char16_t* start, char16_t* stop, char16_t character);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* Print(char16_t* start, char16_t* stop, UI4 value);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* Print(char16_t* start, char16_t* stop, SI4 value);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* Print(char16_t* start, char16_t* stop, UI8 value);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* Print(char16_t* start, char16_t* stop, SI8 value);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* Print(char16_t* start, char16_t* stop, FLT value);

/* Writes the give char16_t to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* Print(char16_t* start, char16_t* stop, DBL value);

/* Prints the given string to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string The potentially unsafe string to write. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop,
                          const char16_t* string, int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start Beginning address of the socket.
@param stop The stop address of the socket.
@param character The value to write. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, char16_t character,
                          int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, UI4 valu,
                          int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, SI4 value,
                          int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, UI8 value,
                          int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, SI8 value,
                          int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, FLT value,
                          int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintCenter(char16_t* start, char16_t* stop, DBL value,
                          int column_count);

/* Prints the given string to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string The potentially unsafe string to write. */
API char16_t* PrintRight(char16_t* start, char16_t* stop,
                         const char16_t* string, int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The value to write. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, char16_t character,
                         int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, UI4 value,
                         int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, SI4 value,
                         int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, UI8 value,
                         int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, SI8 value,
                         int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, FLT value,
                         int column_count);

/* Writes the give char16_t to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintRight(char16_t* start, char16_t* stop, DBL value,
                         int column_count);

/* Prints the given string to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start   The beginning address of the socket.
@param stop     The stop address of the socket.
@param pointer The pointer to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, const void* pointer);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, UI1 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, SI1 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, UI2 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, SI2 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, UI4 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, SI4 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, UI8 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, SI8 value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, FLT value);

/* Writes the give char16_t to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* PrintHex(char16_t* start, char16_t* stop, DBL value);

/* Prints the given string to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param pointer The pointer to utf to hex. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop,
                           const void* pointer);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI1 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI1 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI2 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI2 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI4 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI4 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI8 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI8 value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, FLT value);

/* Writes the give char16_t to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term char16_t
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API char16_t* TPrintBinary(char16_t* start, char16_t* stop, DBL value);

/* Prints out the contents of the address to the printer socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param start The beginning of the write socket.
@param stop   The stop of the write socket.
@param start The beginning of the read socket.
@param stop  The stop of the read socket. */
API char16_t* PrintSocket(char16_t* start, char16_t* stop, const void* start,
                          const void* stop);

/* Prints out the contents of the address to the printer socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param start The beginning of the write socket.
@param stop   The stop of the write socket.
@param start The beginning of the read socket.
@param size  The size of the read socket. */
API char16_t* PrintSocket(char16_t* start, char16_t* stop, const void* start,
                          size_t size);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param start The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
API char16_t* Print(char16_t* start, char16_t* stop, TMS t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param start The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
API char16_t* Print(char16_t* start, char16_t* stop, TME t);

/* Writes the given time to the text socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param start The beginning of the write socket.
@param time  The time to utf.
@param stop   The stop of the write socket. */
API char16_t* Print(char16_t* start, char16_t* stop, Tss t);

/* Prints a line of the given column_count.
@return Returns a pointer to the next char16_t after the stop of the read number
or nil upon failure.
@param start The beginning of the write socket.
@param stop   The stop of the write socket.
@param token The token to utf.
@param column_count The number of tokens to utf. */
API char16_t* PrintLine(char16_t* cursor, char16_t* stop, char16_t token,
                        int column_count);

/* Prints a line of the given column_count.
@return Returns a pointer to the next char16_t after the stop of the read number
or nil upon failure.
@param start  The beginning of the write socket.
@param stop    The stop of the write socket.
@param string The string to utf.
@param column_count The number of columns. */
API char16_t* PrintLineString(char16_t* cursor, char16_t* stop,
                              const char16_t* string, int column_count);

/* Prints the socket to the console as a UTF-8 string. */
void COutUtf16(UIW* socket);

/* Prints the socket to the console as a UTF-8 string. */
void COutAutoUtf16(UIW* socket);

/* Converts the given string to a 8-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* start, SI1& result);

/* Converts the given string to a 8-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, SI1& result);

/* Converts the given string to a 8-bit unsigned integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, UI1& result);

/* Converts the given string to a 16-bit signed integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, SI2& result);

/* Converts the given string to a 16-bit unsigned integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, UI2& result);

/* Converts the given string to a 32-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, SI4& result);

/* Converts the given string to a 32-bit unsigned integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, UI4& result);

/* Converts the given string to a 64-bit signed integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, SI8& result);

/* Converts the given string to a 64-bit unsigned integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, UI8& result);

/* Converts the given string to a 32-bit floating-point number.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, FLT& result);

/* Converts the given string to a 64-bit floating-point number.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next char16_t after the stop
of the read number or nil upon failure. */
API const char16_t* Scan(const char16_t* text, DBL& result);

/* ASCII printing utilities
@ingroup Utf
*/

/* Utility class for printing strings.
This class only stores the stop of socket pointer and a pointer to the write
start. It is up the user to store start of socket pointer and if they would
like to replace the start with the beginning of socket pointer when they
are done printing.
*/
struct API UTF2 {
  char16_t *start,  //< Write start pointer.
      *stop;        //< End of socket pointer.

  /* Initializes the Utf& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF2(char16_t* start, size_t size);

  /* Initializes the Utf& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF2(char16_t* start, char16_t* stop);

  /* Clones the other utf. */
  UTF2(const UTF2& other);

  /* Sets the start pointer to the new_pointer. */
  inline UTF2& Set(char16_t* new_pointer);

  /* Prints the given value as hex. */
  inline UTF2& Hex(SI1 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(UI1 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(SI2 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(UI2 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(SI4 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(UI4 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(SI8 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(UI8 value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(FLT value);

  /* Prints the given value as hex. */
  inline UTF2& Hex(DBL value);

  /* Prints the given pointer as hex. */
  inline UTF2& Hex(const void* pointer);

  /* Prints the given value as binary. */
  inline UTF2& Binary(SI1 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(UI1 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(SI2 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(UI2 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(SI4 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(UI4 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(SI8 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(UI8 value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(FLT value);

  /* Prints the given value as binary. */
  inline UTF2& Binary(DBL value);

  /* Prints the given pointer as binary. */
  inline UTF2& Binary(const void* pointer);
};

/* Utility class for printing numbers. */
class Text2 {
 public:
  /* Default constructor does nothing. */
  Text2();

  /* Prints the value to the text socket. */
  Text2(char16_t character);

  /* Prints the value to the text socket. */
  Text2(SI4 value);

  /* Prints the value to the text socket. */
  Text2(UI4 value);

  /* Prints the value to the text socket. */
  Text2(SI8 value);

  /* Prints the value to the text socket. */
  Text2(UI8 value);

  /* Prints the value to the text socket. */
  Text2(FLT value);

  /* Prints the value to the text socket. */
  Text2(DBL value);

  /* Gets the number string. */
  const char16_t* GetString();

 private:
  enum { kSize = 24 };

  char16_t string[kSize * sizeof(char16_t) + 1];  //< String socket.
};

/* Utility class for printing hex with operator<<. */
class Utf16Center {
 public:
  /* Prints the value to the text socket. */
  Utf16Center(const char16_t* string, int column_count);

  /* Prints the value to the text socket. */
  Utf16Center(SI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Center(UI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Center(SI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Center(UI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Center(FLT value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Center(DBL value, int column_count);

  /* Gets the number string. */
  const char16_t* GetString();

  /* Gets the column_count. */
  int GetColumnCount();

 private:
  const char16_t* string;  //< Pointer to the string.
  Text2 number;            //< Pointer to a pointer to utf.
  int column_count;        //< Number of columns to center.
};

/* Utility class for printing hex with operator<<. */
class Utf16Right {
 public:
  /* Prints the value to the text socket. */
  Utf16Right(const char16_t* string, int column_count);

  /* Prints the value to the text socket. */
  Utf16Right(SI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Right(UI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Right(SI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Right(UI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Right(FLT value, int column_count);

  /* Prints the value to the text socket. */
  Utf16Right(DBL value, int column_count);

  /* Gets the number string. */
  const char16_t* GetString();

  /* Gets the column_count. */
  int GetColumnCount();

 private:
  const char16_t* string;  //< Pointer to the string.
  Text2 number;            //< Pointer to a pointer to utf.
  int column_count;        //< Number of columns to center.
};

}  // namespace _

/* Writes a nil-terminated UTF-8 or ASCII string to the utf.
@param  printer The printer.
@param  value   The value to utf.
@return The printer. */
API _::UTF2& operator<<(_::UTF2& printer, const char16_t* string);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value   The value to utf.
@return The printer. */
API _::UTF2& operator<<(_::UTF2& printer, char16_t value);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value The value to write to the utf.
@return The printer. */
API _::UTF2& operator<<(_::UTF2& printer, UI1 value);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value The value to write to the utf.
@return The printer. */
API _::UTF2& operator<<(_::UTF2& printer, SI2 value);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value The value to write to the utf.
@return The printer. */
API _::UTF2& operator<<(_::UTF2& printer, UI2 value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, SI4 value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, UI4 value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, SI8 value);

/* Writes the given value to the utf.
@return The printer.
@desc
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, UI8 value);

/* Writes the given value to the utf.
@return The printer.
@desc
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, FLT value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, DBL value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf justified center. */
API _::UTF2& operator<<(_::UTF2& printer, _::Utf16Center item);

/* Writes the given value to the utf justified right.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF2& operator<<(_::UTF2& printer, _::Utf16Right item);

#endif  //< #if USING_UTF16
#endif  //< #if INCLUDED_SCRIPTPRINT_UTF16
#endif  //< #if SEAM >= _0_0_0__02
