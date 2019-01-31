/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_utf2.h
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
#ifndef INCLUDED_SCRIPTPRINT_UTF16
#define INCLUDED_SCRIPTPRINT_UTF16

#include "c_object.h"

#if USING_UTF16 == YES

namespace _ {

/* UTF-16 printing utilities
@ingroup ASCII CH1*
*/

/* Strand Factory that prints the string upon destruction. */
SI4 COutHeap4 (CObject& obj, SIW function, void* arg);

/* Checks if the given character is whitespace.
 */
SDK BOL IsWhitespace(CH2 character);

/* Converts the given item to a printable CH2 if it's non-printable. */
SDK CH2 PrintableChar(CH2 item);

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH2. */
SDK const CH2* StrandEnd(const CH2* text);

/* Gets the length of the given CH2.
@return  Returns -1 if the text CH2 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH2. */
SDK SI4 StrandLength(const CH2* text);

/* Clones the given string.
@param  A nil-terminated string in ROM.
@return Returns a new copy you must delete. */
SDK CH2* StrandClone(const CH2* text);

/* Returns a pointer to the CH2 at the stop of the line. */
SDK const CH2* StrandLineEnd(const CH2* text, SI4 count = kTokenCount);

/* Returns the pointer to the next CH2 in the CH2 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the text CH2. */
SDK const CH2* StrandDecimalEnd(const CH2* start);

/* Returns the pointer to the next CH2 in the CH2 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the text CH2. */
SDK const CH2* StrandDecimalEnd(const CH2* start);

/* Skips the leading zeros of a token_ if there are any. */
SDK const CH2* StrandSkipChar(const CH2* text, CH2 skip_char);

/* Skips all the spaces at the start of the CH2. */
SDK const CH2* StrandSkipSpaces(const CH2* text);

/* Compares the source and query CH2 as nil-terminated strings. */
SDK const CH2* StrandEquals(const CH2* text_a, const CH2* text_b);

/* Searches the given CH2 for the given CH2.
@param  text      The CH2 to search.
@param  query      The CH2 to search for.
@return Returns nil if the parsing failed and a pointer to the first CH2
after the stop of the text upon success. */
SDK const CH2* StrandFind(const CH2* start, const CH2* query);

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param  start  The beginning address of the socket.
@param  stop    The stop address of the socket.
@param  string The potentially unsafe string to write. */
SDK CH2* Print(CH2* start, CH2* stop, const CH2* string);

/* Writes the give CH2 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* Print(CH2* start, CH2* stop, UI4 item);

/* Writes the give CH2 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* Print(CH2* start, CH2* stop, SI4 item);

/* Writes the give CH2 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* Print(CH2* start, CH2* stop, UI8 item);

/* Writes the give CH2 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* Print(CH2* start, CH2* stop, SI8 item);

#if SEAM >= SCRIPT2_4
/* Writes the give CH2 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* Print(CH2* start, CH2* stop, FLT item);

/* Writes the give CH2 to the given socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* Print(CH2* start, CH2* stop, DBL item);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string The potentially unsafe string to write. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, const CH2* string,
                     SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start Beginning address of the socket.
@param stop The stop address of the socket.
@param character The item to write. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, CH2 character, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, UI4 valu, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, SI4 item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, UI8 item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, SI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, FLT item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, DBL item, SI4 count = kTokenCount);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string The potentially unsafe string to write. */
SDK CH2* PrintRight(CH2* start, CH2* stop, const CH2* string,
                    SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start     Beginning address of the socket.
@param stop       The stop address of the socket.
@param character The item to write. */
SDK CH2* PrintRight(CH2* start, CH2* stop, CH2 character, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintRight(CH2* start, CH2* stop, UI4 item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintRight(CH2* start, CH2* stop, SI4 item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintRight(CH2* start, CH2* stop, UI8 item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintRight(CH2* start, CH2* stop, SI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintRight(CH2* start, CH2* stop, FLT item, SI4 count = kTokenCount);

/* Writes the give CH2 to the given socket center.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintRight(CH2* start, CH2* stop, DBL item, SI4 count = kTokenCount);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start   The beginning address of the socket.
@param stop     The stop address of the socket.
@param pointer The pointer to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, const void* pointer);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, UI1 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, SI1 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, UI2 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, SI2 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, UI4 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, SI4 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, UI8 item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, SI8 item);

#if SEAM >= SCRIPT2_4
/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, FLT item);

/* Writes the give CH2 to the given socket in hex form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, DBL item);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param pointer The pointer to utf to hex. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, const void* pointer);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI1 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI1 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI2 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI2 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI4 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI4 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI8 item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI8 item);

#if SEAM >= SCRIPT2_4
/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, FLT item);

/* Writes the give CH2 to the given socket in binary form.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning address of the socket.
@param stop The stop address of the socket.
@param item The item to utf. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, DBL item);
#endif

/* Prints out the contents of the address to the printer socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param start The beginning of the read socket.
@param stop  The stop of the read socket. */
SDK CH2* PrintChars(CH2* start, CH2* stop, const void* begin, const void* end);

/* Prints out the contents of the address to the printer socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param start The beginning of the read socket.
@param size  The size of the read socket. */
SDK CH2* PrintChars(CH2* start, CH2* stop, const void* begin, SIW size);

/* Prints a line of the given count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param token The token to utf.
@param count The token_ of tokens to utf. */
SDK CH2* PrintLine(CH2* start, CH2* stop, CH2 token, SI4 count = kTokenCount);

/* Prints a line of the given count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning of the write socket.
@param stop   The stop of the write socket.
@param string The string to utf.
@param count  The token_ of columns. */
SDK CH2* PrintLine(CH2* start, CH2* stop, const CH2* string, SI4 count = kTokenCount);

/* Prints a item repeated the given count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param token The token to utf.
@param count The token_ of tokens to utf. */
SDK CH2* PrintRepeat (CH2* start, CH2* stop, CH2 token, SI4 count = kTokenCount);

/* Prints a item repeated the given count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning of the write socket.
@param stop   The stop of the write socket.
@param string The string to utf.
@param count  The token_ of columns. */
SDK CH2* PrintRepeat (CH2* start, CH2* stop, const CH2* string, SI4 count = kTokenCount);

/* Prints the socket to the console as a UTF-8 string. */
void COut2(UIW* socket);

/* Prints the socket to the console as a UTF-8 string. */
void COutAuto2(UIW* socket);

/* Converts the given string to a 8-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* start, SI1& result);

/* Converts the given string to a 8-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, SI1& result);

/* Converts the given string to a 8-bit unsigned integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, UI1& result);

/* Converts the given string to a 16-bit signed integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, SI2& result);

/* Converts the given string to a 16-bit unsigned integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, UI2& result);

/* Converts the given string to a 32-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, SI4& result);

/* Converts the given string to a 32-bit unsigned integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, UI4& result);

/* Converts the given string to a 64-bit signed integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, SI8& result);

/* Converts the given string to a 64-bit unsigned integer.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, UI8& result);

#if SEAM >= SCRIPT2_4
/* Converts the given string to a 32-bit floating-point token_.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, FLT& result);

/* Converts the given string to a 64-bit floating-point token_.
@param  text  A nil-terminated string in ROM.
@param  result The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* text, DBL& result);
#endif

/* ASCII printing utilities
@ingroup UTF
*/

/* Utility class for printing strings.
This class only stores the stop of socket pointer and a pointer to the write
start. It is up the user to store start of socket pointer and if they would
like to replace the start with the beginning of socket pointer when they
are done printing.
*/
struct SDK UTF2 {
  CH2 *start,  //< Start of the array.
      *stop;   //< Stop of the array.

  /* Initializes the UTF& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF2(CH2* start, size_t size);

  /* Initializes the UTF& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF2(CH2* start, CH2* stop);

  /* Clones the other utf. */
  UTF2(const UTF2& other);

  /* Sets the start pointer to the new_pointer. */
  inline UTF2& Set(CH2* new_pointer);

  /* Prints the given item as hex. */
  inline UTF2& Hex(SI1 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(UI1 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(SI2 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(UI2 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(SI4 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(UI4 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(SI8 item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(UI8 item);

#if SEAM >= SCRIPT2_4
  /* Prints the given item as hex. */
  inline UTF2& Hex(FLT item);

  /* Prints the given item as hex. */
  inline UTF2& Hex(DBL item);
#endif

  /* Prints the given pointer as hex. */
  inline UTF2& Hex(const void* pointer);

  /* Prints the given item as binary. */
  inline UTF2& Binary(SI1 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(UI1 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(SI2 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(UI2 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(SI4 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(UI4 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(SI8 item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(UI8 item);

#if SEAM >= SCRIPT2_4
  /* Prints the given item as binary. */
  inline UTF2& Binary(FLT item);

  /* Prints the given item as binary. */
  inline UTF2& Binary(DBL item);
#endif

  /* Prints the given pointer as binary. */
  inline UTF2& Binary(const void* pointer);
};

/* Utility class for printing numbers. */
class Token2 {
 public:

   /* Prints the item to the strand_. */
   Token2 (CH2 item = 0, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token2 (const CH2* item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token2(SI4 item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token2(UI4 item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token2(SI8 item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token2(UI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
  /* Prints the item to the strand_. */
  Token2(FLT item, SI4 count = kTokenCount);

  /* Prints the item to the strand_. */
  Token2(DBL item, SI4 count = kTokenCount);
#endif

  /* Gets the number string or the strand_. */
  const CH2* String();

  /* Gets the count. */
  SI4 Count ();

 private:

  // A String too long to fit in the strand.
  const CH2* string_;
  SI4 count_;                 //< Either kTokenCount or an abstract variable.
  CH2 strand_[kTokenCount];  //< Strand socket.
};

/* Utility class for printing hex with operator<<. */
struct Right2 {

  Token2 token;  //< Pointer to a pointer to utf.

  /* Prints the item to the token_. */
  Right2(const CH2* string, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right2(SI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right2(UI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right2(SI8 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right2(UI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
  /* Prints the item to the token_. */
  Right2(FLT item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Right2(DBL item, SI4 count = kTokenCount);
#endif
};

/* Utility class for printing hex with operator<<. */
struct Center2 {

  Token2 token;  //< Pointer to a pointer to utf.

  /* Prints the item to the token_. */
  Center2 (const CH2* string, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center2 (SI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center2 (UI4 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center2 (SI8 item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center2 (UI8 item, SI4 count = kTokenCount);

#if SEAM >= SCRIPT2_4
  /* Prints the item to the token_. */
  Center2 (FLT item, SI4 count = kTokenCount);

  /* Prints the item to the token_. */
  Center2 (DBL item, SI4 count = kTokenCount);
#endif

  /* Gets the token_ string. */
  const CH2* String ();

  /* Gets the count. */
  SI4 Count ();

private:
  const CH2* string_; //< Pointer to the string.
  SI4 count_;         //< Number of columns to center.
  Token2 token_;      //< Pointer to a pointer to utf.
};

/* Utility class for printing a horizontal line with operator<<. */
struct SDK TokenLine2 {

  Token2 token;  //< Pointer to a pointer to utf.

  /* Constructors a horizontal line of token. */
  TokenLine2 (CH2 token, SI4 count = kTokenCount);

  /* Constructors a horizontal line of the given string. */
  TokenLine2 (const CH2* string, SI4 count = kTokenCount);
};

/* Utility class for printing a vertical line with operator<<. */
struct SDK Repeat2 {

  Token2 token;  //< Pointer to a pointer to utf.

  /* Constructors a horizontal line of token. */
  Repeat2 (CH2 token, SI4 count = kTokenCount);

  /* Constructors a horizontal line of the given string. */
  Repeat2 (const CH2* string, SI4 count = kTokenCount);
};

#if SCRIPT2_CHAR_SIZE == UTF16
using Token = Token2;
using Right = Right2;
using Center = Center2;
using Columns= TokenLine2;
using Rows = Repeat2;
using Hex = Hex2;
#endif

}  // namespace _

SDK inline ::_::UTF2& operator<<(::_::UTF2& o, const CH2* string);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, CH2 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, UI1 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, SI2 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, UI2 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, SI4 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, UI4 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, SI8 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, UI8 item);

#if SEAM >= SCRIPT2_4

SDK inline ::_::UTF2& operator<<(::_::UTF2& o, FLT item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, DBL item);
#endif

SDK inline ::_::UTF2& operator<<(::_::UTF2& o, ::_::Center2 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, ::_::Right2 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, ::_::TokenLine2 item);
SDK inline ::_::UTF2& operator<<(::_::UTF2& o, ::_::Repeat2 item);

#endif  //< #if USING_UTF16
#endif  //< #if INCLUDED_SCRIPTPRINT_UTF16
#endif  //< #if SEAM >= SCRIPT2_3