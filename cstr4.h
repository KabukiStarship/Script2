/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cstr4.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__03
#ifndef INCLUDED_SCRIPTPRINT_UTF32
#define INCLUDED_SCRIPTPRINT_UTF32

#include "clock.h"

#if USING_UTF32 == YES

namespace _ {

/* UTF-8 printing utilities
@ingroup Utf
*/

/* Checks if the given character is whitespace.
 */
API BOL IsWhitespace(CH4 character);

/* Converts the given value to a printable CH4 if it's non-printable. */
API CH4 PrintableChar(CH4 value);

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH4. */
API const CH4* TStringEnd(const CH4* begin);

/* Gets the length of the given CH4.
@return  Returns -1 if the text CH4 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH4. */
API int TStringLength(const CH4* begin);

/* Clones the given string_.
@param  A nil-terminated string_ in ROM.
@return Returns a new copy you must delete. */
API CH4* StringClone(const CH4* begin);

/* Returns a pointer to the CH4 at the stop of the line. */
API const CH4* StringLineEnd(const CH4* begin, int column_count);

/* Returns the pointer to the next CH4 in the CH4 that is not an ASCII
number_.
@return A pointer to the next non-number_ in the text CH4. */
API const CH4* TStringDecimalEnd(const CH4* begin);

/* Skips the leading zeros of a number_ if there are any. */
API const CH4* TStringSkipChar(const CH4* begin, CH4 skip_char);

/* Skips all the spaces at the begin of the CH4. */
API const CH4* StringSkipSpaces(const CH4* begin);

/* Skips all the spaces at the begin of the CH4.
@param  begin Beginning address of the read socket.
@param  stop   The stop address of the input socket.
@return A pointer to the stop of the text read or if no text read. */
API const CH4* StringSkipSpaces(const CH4* begin,
                                     const CH4* text_end);

/* Compares the source and query CH4 as nil-terminated strings. */
API const CH4* StringEquals(const CH4* text_a,
                                 const CH4* text_b);

/* Compares the source and query CH4 as nil-terminated strings. */
API const CH4* StringEquals(const CH4* begin, const CH4* stop,
                                 const CH4* query);

/* Searches the given CH4 for the given CH4.
@param  begin  The CH4 to search.
@param  query The CH4 to search for.
@return Returns nil if the parsing failed and a pointer to the first CH4
after the stop of the text upon success. */
API const CH4* StringFind(const CH4* begin, const CH4* query);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param  begin  The beginning address of the socket.
@param  stop    The stop address of the socket.
@param  string_ The potentially unsafe string_ to write. */
API CH4* Print(CH4* start, CH4* stop, const CH4* string_);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The value to write. */
API CH4* Print(CH4* start, CH4* stop, CH4 character);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* Print(CH4* start, CH4* stop, UI4 value);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* Print(CH4* start, CH4* stop, SI4 value);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* Print(CH4* start, CH4* stop, UI8 value);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* Print(CH4* start, CH4* stop, SI8 value);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* Print(CH4* start, CH4* stop, FLT value);

/* Writes the give CH4 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* Print(CH4* start, CH4* stop, DBL value);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string_ The potentially unsafe string_ to write. */
API CH4* PrintCenter(CH4* start, CH4* stop,
                          const CH4* string_, int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin Beginning address of the socket.
@param stop The stop address of the socket.
@param character The value to write. */
API CH4* PrintCenter(CH4* start, CH4* stop, CH4 character,
                          int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintCenter(CH4* start, CH4* stop, UI4 valu,
                          int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintCenter(CH4* start, CH4* stop, SI4 value,
                          int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintCenter(CH4* start, CH4* stop, UI8 value,
                          int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintCenter(CH4* start, CH4* stop, SI8 value,
                          int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintCenter(CH4* start, CH4* stop, FLT value,
                          int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintCenter(CH4* start, CH4* stop, DBL value,
                          int column_count);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string_ The potentially unsafe string_ to write. */
API CH4* PrintRight(CH4* start, CH4* stop,
                         const CH4* string_, int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The value to write. */
API CH4* PrintRight(CH4* start, CH4* stop, CH4 character,
                         int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintRight(CH4* start, CH4* stop, UI4 value,
                         int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintRight(CH4* start, CH4* stop, SI4 value,
                         int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintRight(CH4* start, CH4* stop, UI8 value,
                         int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintRight(CH4* start, CH4* stop, SI8 value,
                         int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintRight(CH4* start, CH4* stop, FLT value,
                         int column_count);

/* Writes the give CH4 to the given socket center.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintRight(CH4* start, CH4* stop, DBL value,
                         int column_count);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin   The beginning address of the socket.
@param stop     The stop address of the socket.
@param pointer The pointer to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, const void* pointer);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, UI1 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, SI1 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, UI2 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, SI2 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, UI4 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, SI4 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, UI8 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, SI8 value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, FLT value);

/* Writes the give CH4 to the given socket in hex form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* PrintHex(CH4* start, CH4* stop, DBL value);

/* Prints the given string_ to the utf socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin  The beginning address of the socket.
@param stop    The stop address of the socket.
@param pointer The pointer to utf to hex. */
API CH4* TPrintBinary(CH4* start, CH4* stop,
                           const void* pointer);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, UI1 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, SI1 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, UI2 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, SI2 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, UI4 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, SI4 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, UI8 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, SI8 value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, FLT value);

/* Writes the give CH4 to the given socket in binary form.
@return Returns nil upon socket overflow and a pointer to the nil-term CH4
upon success.
@param begin The beginning address of the socket.
@param stop The stop address of the socket.
@param value The value to utf. */
API CH4* TPrintBinary(CH4* start, CH4* stop, DBL value);

/* Prints the given memory socket to the text socket.
@param begin The beginning of the write socket.
@param stop   The stop of the write socket.
@param begin The beginning of the read socket.
@param size  The size of the socket in bytes. */
API CH4* PrintSocket(CH4* start, CH4* stop, const void* begin,
                          size_t size);

/* Prints out the contents of the address to the printer socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param stop   The stop of the write socket.
@param begin The beginning of the read socket.
@param end  The stop of the read socket. */
API CH4* PrintSocket(CH4* start, CH4* stop, const void* begin,
                          const void* end);

/* Prints out the contents of the address to the printer socket.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param begin The beginning of the write socket.
@param stop   The stop of the write socket.
@param begin The beginning of the read socket.
@param size  The size of the read socket. */
API CH4* PrintSocket(CH4* start, CH4* stop, const void* begin,
                          size_t size);

/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop
of the read number_ or nil upon failure.
@param printer The printer to utf to.
@param type    The type to utf.
@param value   The value to utf or nil. */
API CH4* Print(CH4* start, CH4* stop, SIN type,
                    const void* value);

/* Prints a line of the given column_count.
@return Returns a pointer to the next CH4 after the stop of the read
number_ or nil upon failure.
@param begin The beginning of the write socket.
@param stop  The stop of the write socket.
@param token The token to utf.
@param column_count The number_ of tokens to utf. */
API CH4* PrintLine(CH4* cursor, CH4* stop, CH4 token,
                        int column_count);

/* Prints a line of the given column_count.
@return Returns a pointer to the next CH4 after the stop of the read
number_ or nil upon failure.
@param begin  The beginning of the write socket.
@param stop   The stop of the write socket.
@param string_ The string_ to utf.
@param column_count The number_ of columns. */
API CH4* TPrintLineString(CH4* cursor, CH4* stop,
                               const CH4* string_, int column_count);

/* Prints the socket to the console as a UTF-8 string_. */
void COutUtf32(UIW* socket);

/* Prints the socket to the console as a UTF-8 string_. */
void COutAutoUtf32(UIW* socket);

/* Converts the given string_ to a 8-bit signed integer.
@param  begin A nil-terminated string_ in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, SI1& result);

/* Converts the given string_ to a 8-bit unsigned integer.
@param  begin   A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, UI1& result);

/* Converts the given string_ to a 16-bit signed integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, SI2& result);

/* Converts the given string_ to a 16-bit unsigned integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, UI2& result);

/* Converts the given string_ to a 32-bit signed integer.
@param  begin A nil-terminated string_ in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, SI4& result);

/* Converts the given string_ to a 32-bit unsigned integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, UI4& result);

/* Converts the given string_ to a 64-bit signed integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, SI8& result);

/* Converts the given string_ to a 64-bit unsigned integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, UI8& result);

/* Converts the given string_ to a 32-bit floating-point number_.
@param  begin A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, FLT& result);

/* Converts the given string_ to a 64-bit floating-point number_.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* begin, DBL& result);
/* Converts the given string_ to a 8-bit signed integer.
@param  begin A nil-terminated string_ in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, SI1& result);

/* Converts the given string_ to a 8-bit unsigned integer.
@param  begin A nil-terminated string_ in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, UI1& result);

/* Converts the given string_ to a 16-bit signed integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, SI2& result);

/* Converts the given string_ to a 16-bit unsigned integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, UI2& result);

/* Converts the given string_ to a 32-bit signed integer.
@param  begin A nil-terminated string_ in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, SI4& result);

/* Converts the given string_ to a 32-bit unsigned integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, UI4& result);

/* Converts the given string_ to a 64-bit signed integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, SI8& result);

/* Converts the given string_ to a 64-bit unsigned integer.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, UI8& result);

/* Converts the given string_ to a 32-bit floating-point number_.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, FLT& result);

/* Converts the given string_ to a 64-bit floating-point number_.
@param  begin  A nil-terminated string_ in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read number_ or nil upon failure. */
API const CH4* Scan(const CH4* text, DBL& result);

/* Universal Text Formatter (UTF) 8 is a utility class for printing UTF-8
strings.
This class only stores the stop of socket pointer and a pointer to the
write begin. It is up the user to store begin of socket pointer and if they
would like to replace the begin with the beginning of socket pointer when they
are done printing.
*/
struct API UTF4 {
  CH4 *begin,  //< Write begin pointer.
      *stop;        //< End of socket pointer.

  /* Initializes the Utf& from the given socket pointers.
  @param begin The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF4(CH4* begin, size_t size);

  /* Initializes the Utf& from the given socket pointers.
  @param begin The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF4(CH4* start, CH4* stop);

  /* Clones the other utf. */
  UTF4(const UTF4& other);

  /* Sets the begin pointer to the new_pointer. */
  inline UTF4& Set(CH4* new_pointer);

  /* Prints the given value as hex. */
  inline UTF4& Hex(SI1 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(UI1 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(SI2 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(UI2 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(SI4 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(UI4 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(SI8 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(UI8 value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(FLT value);

  /* Prints the given value as hex. */
  inline UTF4& Hex(DBL value);

  /* Prints the given pointer as hex. */
  inline UTF4& Hex(const void* pointer);

  /* Prints the given value as binary. */
  inline UTF4& Binary(SI1 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(UI1 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(SI2 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(UI2 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(SI4 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(UI4 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(SI8 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(UI8 value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(FLT value);

  /* Prints the given value as binary. */
  inline UTF4& Binary(DBL value);

  /* Prints the given pointer as binary. */
  inline UTF4& Binary(const void* pointer);
};

/* Utility class for printing numbers. */
class Text4 {
 public:
  /* Default constructor does nothing. */
  Text4();

  /* Prints the value to the text socket. */
  Text4(CH4 character);

  /* Prints the value to the text socket. */
  Text4(SI4 value);

  /* Prints the value to the text socket. */
  Text4(UI4 value);

  /* Prints the value to the text socket. */
  Text4(SI8 value);

  /* Prints the value to the text socket. */
  Text4(UI8 value);

  /* Prints the value to the text socket. */
  Text4(FLT value);

  /* Prints the value to the text socket. */
  Text4(DBL value);

  /* Gets the number_ string_. */
  const CH4* GetString();

 private:
  enum { kSize = 24 };

  CH4 string_[kSize * sizeof(CH4) + 1];  //< String socket.
};

/* Utility class for printing hex with operator<<. */
class Utf32Center {
 public:
  /* Prints the value to the text socket. */
  Utf32Center(const CH4* string_, int column_count);

  /* Prints the value to the text socket. */
  Utf32Center(SI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Center(UI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Center(SI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Center(UI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Center(FLT value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Center(DBL value, int column_count);

  /* Gets the number_ string_. */
  const CH4* GetString();

  /* Gets the column_count. */
  int GetColumnCount();

 private:
  const CH4* string_;  //< Pointer to the string_.
  Text4 number_;            //< Pointer to a pointer to utf.
  int column_count;         //< Number of columns to center.
};

/* Utility class for printing hex with operator<<. */
class Utf32Right {
 public:
  /* Prints the value to the text socket. */
  Utf32Right(const CH4* string_, int column_count);

  /* Prints the value to the text socket. */
  Utf32Right(SI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Right(UI4 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Right(SI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Right(UI8 value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Right(FLT value, int column_count);

  /* Prints the value to the text socket. */
  Utf32Right(DBL value, int column_count);

  /* Gets the number_ string_. */
  const CH4* GetString();

  /* Gets the column_count. */
  int GetColumnCount();

 private:
  const CH4* string_;  //< Pointer to the string_.
  Text4 number_;            //< Pointer to a pointer to utf.
  int column_count;         //< Number of columns to center.
};

}  // namespace _

/* Writes a nil-terminated UTF-8 or ASCII string_ to the utf.
@param  printer The printer.
@param  value   The value to utf.
@return The printer. */
API _::UTF4& operator<<(_::UTF4& printer, const CH4* string_);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value   The value to utf.
@return The printer. */
API _::UTF4& operator<<(_::UTF4& printer, CH4 value);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value The value to write to the utf.
@return The printer. */
API _::UTF4& operator<<(_::UTF4& printer, UI1 value);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value The value to write to the utf.
@return The printer. */
API _::UTF4& operator<<(_::UTF4& printer, SI2 value);

/* Writes the given value to the utf.
@param  printer The printer.
@param  value The value to write to the utf.
@return The printer. */
API _::UTF4& operator<<(_::UTF4& printer, UI2 value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, SI4 value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, UI4 value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, SI8 value);

/* Writes the given value to the utf.
@return The printer.
@desc
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, UI8 value);

/* Writes the given value to the utf.
@return The printer.
@desc
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, FLT value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, DBL value);

/* Writes the given value to the utf.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf justified center. */
API _::UTF4& operator<<(_::UTF4& printer, _::Utf32Center item);

/* Writes the given value to the utf justified right.
@return The printer.
@param  printer The printer.
@param  value The value to write to the utf. */
API _::UTF4& operator<<(_::UTF4& printer, _::Utf32Right item);

#endif  //< #if USING_UTF32 == YES
#endif  //< #if INCLUDED_SCRIPTPRINT_UTF32
#endif  //< #if SEAM >= _0_0_0__03
