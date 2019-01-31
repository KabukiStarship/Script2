/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_utf4.h
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
#if SEAM >= SCRIPT2_3
#ifndef INCLUDED_SCRIPTPRINT_UTF32
#define INCLUDED_SCRIPTPRINT_UTF32

#include "c_object.h"

#if USING_UTF32 == YES

namespace _ {

/* UTF-32 printing utilities
@ingroup ASCII CH1*
*/

/* Strand Factory that prints the string upon destruction. */
SI4 COutHeap4 (CObject& obj, SIW function, void* arg);

/* Checks if the given character is whitespace.
 */
SDK BOL IsWhitespace(CH4 character);

/* Converts the given item to a printable CH4 if it's non-printable. */
SDK CH4 PrintableChar(CH4 item);

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH4. */
SDK const CH4* StrandEnd(const CH4* start);

/* Gets the length of the given CH4.
@return  Returns -1 if the text CH4 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH4. */
SDK SI4 StrandLength(const CH4* start);

/* Returns a pointer to the CH4 at the stop of the line. */
SDK const CH4* StrandLineEnd(const CH4* start, SI4 count = kTokenCount);

/* Returns the pointer to the next CH4 in the CH4 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the text CH4. */
SDK const CH4* StrandDecimalEnd(const CH4* start);

/* Skips the leading zeros of a token_ if there are any. */
SDK const CH4* StrandSkipChar(const CH4* start, CH4 skip_char);

/* Skips all the spaces at the start of the CH4. */
SDK const CH4* StrandSkipSpaces(const CH4* start);

/* Skips all the spaces at the start of the CH4.
@param  start Beginning address of the read socket.
@param  stop   The stop address of the input socket.
@return A pointer to the stop of the text read or if no text read. */
SDK const CH4* StrandSkipSpaces(const CH4* start, const CH4* text_end);

/* Compares the source and query CH4 as nil-terminated strings. */
SDK const CH4* StrandEquals(const CH4* text_a, const CH4* text_b);

/* Compares the source and query CH4 as nil-terminated strings. */
SDK const CH4* StrandEquals(const CH4* start, const CH4* stop,
                            const CH4* query);

/* Searches the given item for the given string.
@param  start  The CH4 to search.
@param  query The CH4 to search for.
@return Returns nil if the parsing failed and a pointer to the first CH4
after the stop of the text upon success. */
SDK const CH4* StrandFind(const CH4* string, const CH4* item);

/* Prints the given item to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param  start  The beginning address of the socket.
@param  stop    The stop address of the socket.
@param   The potentially unsafe  to write. */
SDK CH4* Print(CH4* start, CH4* stop, const CH4* );

/* Writes the give item to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* Print(CH4* start, CH4* stop, UI4 item);

/* Writes the give item to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* Print(CH4* start, CH4* stop, SI4 item);

/* Writes the give CH4 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* Print(CH4* start, CH4* stop, UI8 item);

/* Writes the give CH4 to the given socket
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* Print(CH4* start, CH4* stop, SI8 item);

#if SEAM >= SCRIPT2_4
/* Writes the give CH4 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* Print(CH4* start, CH4* stop, FLT item);

/* Writes the give CH4 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* Print(CH4* start, CH4* stop, DBL item);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param  The potentially unsafe  to write. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, const CH4* ,
                     SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start Beginning address of the socket.
@param stop The stop address of the socket.
@param character The item to write. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, CH4 character, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, UI4 valu, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, SI4 item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, UI8 item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, SI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, FLT item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintCenter(CH4* start, CH4* stop, DBL item, SI4 count = kTokenCount);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param  The potentially unsafe  to write. */
SDK CH4* PrintRight(CH4* start, CH4* stop, const CH4* ,
                    SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The item to write. */
SDK CH4* PrintRight(CH4* start, CH4* stop, CH4 character, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintRight(CH4* start, CH4* stop, UI4 item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintRight(CH4* start, CH4* stop, SI4 item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintRight(CH4* start, CH4* stop, UI8 item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintRight(CH4* start, CH4* stop, SI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintRight(CH4* start, CH4* stop, FLT item, SI4 count = kTokenCount);

/* Writes the give CH4 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintRight(CH4* start, CH4* stop, DBL item, SI4 count = kTokenCount);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start   The beginning address of the socket.
@param stop     The stop address of the socket.
@param pointer The pointer to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, const void* begin);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, UI1 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, SI1 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, UI2 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, SI2 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, UI4 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, SI4 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, UI8 item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, SI8 item);

#if SEAM >= SCRIPT2_4
/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, FLT item);

/* Writes the give CH4 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintHex(CH4* start, CH4* stop, DBL item);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param begin   The begin address to print to hex. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, const void* begin);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, UI1 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, SI1 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, UI2 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, SI2 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, UI4 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, SI4 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, UI8 item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, SI8 item);

#if SEAM >= SCRIPT2_4
/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, FLT item);

/* Writes the give CH4 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to print. */
SDK CH4* PrintBinary(CH4* start, CH4* stop, DBL item);
#endif

/* Prints the given memory socket to the token_.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The begin address of the write socket.
@param stop   The stop of the write socket.
@param begin The begin address of the read socket.
@param size  The size of the socket in bytes. */
SDK CH4* PrintChars(CH4* start, CH4* stop, const void* begin, size_t size);

/* Prints out the contents of the address to the printer socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The begin address of the write socket.
@param stop   The stop of the write socket.
@param start The begin address of the read socket.
@param end  The stop of the read socket. */
SDK CH4* PrintChars(CH4* start, CH4* stop, const void* begin, const void* end);

/* Prints out the contents of the address to the printer socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The begin address of the write socket.
@param stop   The stop of the write socket.
@param start The begin address of the read socket.
@param size  The size of the read socket. */
SDK CH4* PrintChars(CH4* start, CH4* stop, const void* begin, size_t size);

/* Prints th given type or type-item.
@return Nil upon failure or a pointer to the terminator upon success.
@param printer The printer to print to.
@param type    The type to print.
@param item    The item to print or nil. */
SDK CH4* Print(CH4* start, CH4* stop, SI4 type, const void* item);

/* Prints a horizontal line of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The begin address of the write socket.
@param stop  The stop of the write socket.
@param token The token to print.
@param count The token_ of tokens to print. */
SDK CH4* PrintLine(CH4* cursor, CH4* stop, CH4 token, SI4 count = kTokenCount);

/* Prints a horizontal line of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The begin address of the write socket.
@param stop   The stop of the write socket.
@param  The  to print.
@param count The token_ of columns. */
SDK CH4* PrintLine(CH4* cursor, CH4* stop, const CH4* ,
                          SI4 count = kTokenCount);

/* Prints a vertical lines of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The begin address of the write socket.
@param stop  The stop of the write socket.
@param token The token to print.
@param count The token_ of tokens to print. */
SDK CH4* PrintRepeat (CH4* cursor, CH4* stop, CH4 token, SI4 count = kTokenCount);

/* Prints a vertical line of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The begin address of the write socket.
@param stop   The stop of the write socket.
@param  The  to print.
@param count The token_ of columns. */
SDK CH4* PrintRepeat (CH4* cursor, CH4* stop, const CH4* ,
  SI4 count = kTokenCount);

/* Prints the socket to the console as a UTF-8 .
void COut4(UIW* socket); */

/* Prints the socket to the console as a UTF-8 .
void COutAuto4(UIW* socket); */

/* Converts the given  to a 8-bit signed integer.
@param  start A nil-terminated  in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, SI1& result);

/* Converts the given  to a 8-bit unsigned integer.
@param  start   A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, UI1& result);

/* Converts the given  to a 16-bit signed integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, SI2& result);

/* Converts the given  to a 16-bit unsigned integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, UI2& result);

/* Converts the given  to a 32-bit signed integer.
@param  start A nil-terminated  in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, SI4& result);

/* Converts the given  to a 32-bit unsigned integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, UI4& result);

/* Converts the given  to a 64-bit signed integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, SI8& result);

/* Converts the given  to a 64-bit unsigned integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, UI8& result);

#if SEAM >= SCRIPT2_4
/* Converts the given  to a 32-bit floating-point token_.
@param  start A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, FLT& result);

/* Converts the given  to a 64-bit floating-point token_.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* start, DBL& result);
#endif

/* Converts the given  to a 8-bit signed integer.
@param  start A nil-terminated  in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, SI1& result);

/* Converts the given  to a 8-bit unsigned integer.
@param  start A nil-terminated  in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, UI1& result);

/* Converts the given  to a 16-bit signed integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, SI2& result);

/* Converts the given  to a 16-bit unsigned integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, UI2& result);

/* Converts the given  to a 32-bit signed integer.
@param  start A nil-terminated  in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, SI4& result);

/* Converts the given  to a 32-bit unsigned integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, UI4& result);

/* Converts the given  to a 64-bit signed integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, SI8& result);

/* Converts the given  to a 64-bit unsigned integer.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, UI8& result);

#if SEAM >= SCRIPT2_4
/* Converts the given  to a 32-bit floating-point token_.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, FLT& result);

/* Converts the given  to a 64-bit floating-point token_.
@param  start  A nil-terminated  in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK const CH4* Scan(const CH4* text, DBL& result);
#endif

/* Universal Text Formatter (UTF) 8 is a utility class for printing UTF-8
strings.
This class only stores the stop of socket pointer and a pointer to the
write start. It is up the user to store start of socket pointer and if they
would like to replace the start with the beginning of socket pointer when they
are done printing.
*/
struct SDK UTF4 {
  CH4 *start,  //< Start of the array.
      *stop;   //< Stop fo the array.

  /* Initializes the UTF& from the given socket pointers.
  @param start The begin address of the socket.
  @param stop   The stop of the socket. */
  UTF4(CH4* start, size_t size);

  /* Initializes the UTF& from the given socket pointers.
  @param start The begin address of the socket.
  @param stop   The stop of the socket. */
  UTF4(CH4* start, CH4* stop);

  /* Clones the other utf. */
  UTF4(const UTF4& other);

  /* Sets the start pointer to the new_pointer. */
  inline UTF4& Set(CH4* new_pointer);

  /* Prints the given item as hex. */
  inline UTF4& Hex(SI1 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(UI1 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(SI2 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(UI2 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(SI4 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(UI4 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(SI8 item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(UI8 item);

#if SEAM >= SCRIPT2_4
  /* Prints the given item as hex. */
  inline UTF4& Hex(FLT item);

  /* Prints the given item as hex. */
  inline UTF4& Hex(DBL item);
#endif

  /* Prints the given pointer as hex. */
  inline UTF4& Hex(const void* pointer);

  /* Prints the given item as binary. */
  inline UTF4& Binary(SI1 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(UI1 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(SI2 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(UI2 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(SI4 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(UI4 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(SI8 item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(UI8 item);

#if SEAM >= SCRIPT2_4
  /* Prints the given item as binary. */
  inline UTF4& Binary(FLT item);

  /* Prints the given item as binary. */
  inline UTF4& Binary(DBL item);
#endif

  /* Prints the given pointer as binary. */
  inline UTF4& Binary(const void* pointer);
};

/* Utility class for printing numbers. */
class Token4 {
 public:

   /* Prints the item to the strand_. */
   Token4 (CH4 item = 0, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token4 (const CH4* item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token4(SI4 item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token4(UI4 item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token4(SI8 item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token4(UI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
  /* Prints the item to the strand_. */
  Token4(FLT item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token4(DBL item, SI4 count = kTokenCount);
#endif

  /* Gets the  if it non-nil else the strand_. */
  const CH4* String();

  /* Gets the count. */
  SI4 Count ();

 private:

  // String too big to fit in the strand_.
  const CH4* string_;
  SI4 count_;               //< Either kTokenCount or an abstract variable.
  CH4 strand_[kTokenCount]; //< Strand socket.
};

/* Utility class for printing hex with operator<<. */
struct Right4 {
  Token4 token;

  /* Prints the item to the token_. */
  Right4(const CH4* , SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right4(SI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right4(UI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right4(SI8 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right4(UI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
  /* Prints the item to the token_. */
  Right4(FLT item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right4(DBL item, SI4 count = kTokenCount);
#endif
};

/* Utility class for printing hex with operator<<. */
struct Center4 {
  Token4 token;

  /* Prints the item to the token_. */
  Center4 (const CH4*, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center4 (SI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center4 (UI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center4 (SI8 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center4 (UI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
  /* Prints the item to the token_. */
  Center4 (FLT item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center4 (DBL item, SI4 count = kTokenCount);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct SDK TokenLine4 {
  Token4 token;

  /* Constructors a horizontal line of token. */
  TokenLine4 (CH4 item, SI4 count = kTokenCount);

  /* Constructors a horizontal line of the given string. */
  TokenLine4 (const CH4* string, SI4 count = kTokenCount);
};

/* Utility class for printing a vertical line with operator<<. */
struct SDK Repeat4 {
  Token4 token;  //< Pointer to a pointer to print.

  /* Constructors a horizontal line of token. */
  Repeat4 (CH4 item, SI4 count = kTokenCount);

  /* Constructors a horizontal line of the given string. */
  Repeat4 (const CH4* item, SI4 count = kTokenCount);
};

#if SCRIPT2_CHAR_SIZE == UTF32
using Token = Token4;
using Right = Right4;
using Center = Center4;
using Columns= TokenLine4;
using Rows = Repeat4;
using Hex = Hex4;
#endif

}  // namespace _

SDK ::_::UTF4& operator<<(::_::UTF4& printer, const CH4* );
SDK ::_::UTF4& operator<<(::_::UTF4& printer, CH4 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, UI1 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, SI2 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, UI2 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, SI4 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, UI4 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, SI8 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, UI8 item);

#if SEAM >= SCRIPT2_4

SDK ::_::UTF4& operator<<(::_::UTF4& printer, FLT item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, DBL item);
#endif

SDK ::_::UTF4& operator<<(::_::UTF4& printer, ::_::Center4 item);
SDK ::_::UTF4& operator<<(::_::UTF4& printer, ::_::Right4 item);
SDK::_::UTF4& operator<<(::_::UTF4& printer, ::_::TokenLine4 item);
SDK::_::UTF4& operator<<(::_::UTF4& printer, ::_::Repeat4 item);

#endif  //< #if USING_UTF32 == YES
#endif  //< #if INCLUDED_SCRIPTPRINT_UTF32
#endif  //< #if SEAM >= SCRIPT2_3
