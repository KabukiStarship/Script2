/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_utf4.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#ifndef INCLUDED_SCRIPTPRINT_UTF32
#define INCLUDED_SCRIPTPRINT_UTF32

#include "c_uniprinter.h"

#if SEAM >= SCRIPT2_3

#include "c_ascii.h"
#include "c_object.h"

#if USING_UTF32 == YES

namespace _ {

/* UTF-32 printing utilities
@ingroup ASCII CH1*
*/

/* Strand Factory that prints the string upon destruction.
SI4 COutHeap4 (CObject& obj, SIW function, void* arg); */

/* Checks if the given character is whitespace.
 */
SDK /*inline*/ BOL IsWhitespace(CH4 character);

/* Converts the given item to a printable CH4 if it's non-printable. */
SDK /*inline*/ CH4 PrintableChar(CH4 item);

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH4. */
SDK /*inline*/ const CH4* STREnd(const CH4* start);

/* Gets the length of the given CH4.
@return  Returns -1 if the text CH4 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH4. */
SDK /*inline*/ SI4 StrandLength(const CH4* start);

/* Returns a pointer to the CH4 at the stop of the line. */
SDK /*inline*/ const CH4* StrandLineEnd(const CH4* start,
                                        SI4 count = kTokenLongest);

/* Returns the pointer to the next CH4 in the CH4 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the text CH4. */
SDK /*inline*/ const CH4* StrandDecimalEnd(const CH4* start);

/* Skips the leading zeros of a token_ if there are any. */
SDK /*inline*/ const CH4* STRSkipChar(const CH4* start, CH4 skip_char);

/* Skips all the spaces at the start of the CH4. */
SDK /*inline*/ const CH4* STRSkipSpaces(const CH4* start);

/* Skips all the spaces at the start of the CH4.
@param  start Beginning address of the read socket.
@param  stop   The stop address of the input socket.
@return A pointer to the stop of the text read or if no text read. */
SDK /*inline*/ const CH4* STRSkipSpaces(const CH4* start, const CH4* text_end);

/* Compares the source and query CH4 as nil-terminated strings. */
SDK /*inline*/ const CH4* STREquals(const CH4* start, const CH4* token);

/* Compares the source and query CH4 as nil-terminated strings. */
SDK /*inline*/ const CH4* STREquals(const CH4* start, const CH4* stop,
                                    const CH4* query);

/* Searches the given item for the given string.
@param  start  The CH4 to search.
@param  query The CH4 to search for.
@return Returns nil if the parsing failed and a pointer to the first CH4
after the stop of the text upon success. */
SDK /*inline*/ const CH4* STRFind(const CH4* string, const CH4* item);

/* Prints the given item to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param  start The beginning address of the socket.
@param  stop  The stop address of the socket.
@param  item  The item to print. */
#if USING_UTF8 == YES
CH4* Print(CH4* start, CH4* stop, const CH1* item);
#endif
#if USING_UTF16 == YES
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, const CH2* item);
#endif
CH4* Print(CH4* start, CH4* stop, const CH4* item);
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, UI4 item);
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, SI4 item);
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, UI8 item);
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, SI8 item);
#if USING_FP4 == YES
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, FP8 item);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param  The potentially unsafe  to write. */
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, const CH4*,
                                SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, CH4 character,
                                SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, UI4 valu,
                                SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, SI4 item,
                                SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, UI8 item,
                                SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, SI8 item,
                                SI4 count = kTokenLongest);
#if USING_FP4 == YES
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, FP4 item,
                                SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
SDK /*inline*/ CH4* PrintCenter(CH4* start, CH4* stop, FP8 item,
                                SI4 count = kTokenLongest);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param  The potentially unsafe  to write. */
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, const CH4*,
                               SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, CH4 character,
                               SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, UI4 item,
                               SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, SI4 item,
                               SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, UI8 item,
                               SI4 count = kTokenLongest);
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, SI8 item,
                               SI4 count = kTokenLongest);
#if USING_FP4 == YES
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, FP4 item,
                               SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
SDK /*inline*/ CH4* PrintRight(CH4* start, CH4* stop, FP8 item,
                               SI4 count = kTokenLongest);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start   The beginning address of the socket.
@param stop     The stop address of the socket.
@param pointer The pointer to print. */
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, const void* begin);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, UI1 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, SI1 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, UI2 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, SI2 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, UI4 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, SI4 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, UI8 item);
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, SI8 item);
#if USING_FP4 == YES
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK /*inline*/ CH4* PrintHex(CH4* start, CH4* stop, FP8 item);
#endif

/* Prints the given  to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param begin   The begin address to print to hex. */
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, const void* begin);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, UI1 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, SI1 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, UI2 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, SI2 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, UI4 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, SI4 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, UI8 item);
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, SI8 item);

#if USING_FP4 == YES
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK /*inline*/ CH4* PrintBinary(CH4* start, CH4* stop, FP8 item);
#endif

/* Prints out the contents of the address to the printer socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The start address of the buffer.
@param stop   The stop of the write socket.
@param start The begin address of the read socket.
@param end  The stop of the read socket. */
SDK /*inline*/ CH4* PrintChars(CH4* start, CH4* stop, const void* begin,
                               const void* end);

/* Prints the given memory socket to the token_.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The start address of the buffer.
@param stop  The stop of the write socket.
@param begin The begin address of the read socket.
@param size  The size of the socket in bytes. */
SDK /*inline*/ CH4* PrintChars(CH4* start, CH4* stop, const void* begin,
                               SIW size);

/* Prints th given type or type-item.
@return Nil upon failure or a pointer to the terminator upon success.
@param printer The printer to print to.
@param type    The type to print.
@param item    The item to print or nil. */
SDK /*inline*/ CH4* Print(CH4* start, CH4* stop, SI4 type, const void* item);

/* Prints a horizontal line of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The start address of the buffer.
@param stop  The stop of the write socket.
@param item The token to print.
@param count The token_ of tokens to print. */
SDK /*inline*/ CH4* PrintLinef(CH4* cursor, CH4* stop, CH4 item,
                               SI4 count = kTokenLongest);

/* Prints a horizontal line of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The start address of the buffer.
@param stop   The stop of the write socket.
@param  item The  to print.
@param count The token_ of columns. */
SDK /*inline*/ CH4* PrintLinef(CH4* cursor, CH4* stop, const CH4* item,
                               SI4 count = kTokenLongest);

/* Prints a vertical lines of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The start address of the buffer.
@param stop  The stop of the write socket.
@param item  The token to print.
@param count The token_ of tokens to print. */
SDK /*inline*/ CH4* PrintRepeat(CH4* cursor, CH4* stop, CH4 item,
                                SI4 count = kTokenLongest);

/* Prints a vertical line of the given character count.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The start address of the buffer.
@param stop   The stop of the write socket.
@param  The  to print.
@param count The token_ of columns. */
SDK /*inline*/ CH4* PrintRepeat(CH4* cursor, CH4* stop, const CH4*,
                                SI4 count = kTokenLongest);

/* Prints the socket to the console as a UTF-8 .
void COut4(UIW* socket); */

/* Prints the socket to the console as a UTF-8 .
void COutAuto4(UIW* socket); */

/* Converts the given  to a 8-bit signed integer.
@param  start A nil-terminated  in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH4 after the stop
of the read token_ or nil upon failure. */
SDK /*inline*/ const CH4* Scan(const CH4* start, SI1& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, UI1& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, SI2& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, UI2& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, SI4& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, UI4& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, SI8& result);
SDK /*inline*/ const CH4* Scan(const CH4* start, UI8& result);
#if USING_FP4 == YES
SDK /*inline*/ const CH4* Scan(const CH4* text, FP4& result);
#endif
#if USING_FP8 == YES
SDK /*inline*/ const CH4* Scan(const CH4* text, FP8& result);
#endif

/* Utility class for printing numbers. */
class Token4 {
 public:
  /* Prints the item to the strand_. */
  Token4(CH4 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token4(const CH4* item = nullptr, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token4(SI4 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token4(UI4 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token4(SI8 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token4(UI8 item, SI4 count = kTokenLongest);

#if USING_FP4 == YES
  /* Prints the item to the strand_. */
  Token4(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  /* Prints the item to the strand_. */
  Token4(FP8 item, SI4 count = kTokenLongest);
#endif

  /* Gets the string_. */
  const CH4* String();

  /* Sets the string_ to the new string.
  @return Nil upon failure or the string upon success. */
  const CH4* SetString(const CH4* string);

  /* Gets the strand_. */
  CH4* Strand();

  /* Gets the number string_ or the strand_ if the string_ is nil. */
  const CH4* Get();

  /* Gets the count. */
  SI4 Count();

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(CH1 item);

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(const CH1* item);

#if USING_UTF16 == YES
  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(CH2 item);

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(const CH2* item);
#endif
#if USING_UTF32 == YES
  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(const CH4* item);

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(CH4 item);
#endif
  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(SI4 item);

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(UI4 item);

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(SI8 item);

  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(UI8 item);

#if USING_FP4 == YES
  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(FP4 item);
#endif
#if USING_FP8 == YES
  /* Prints the given item to the strand_. */
  /*inline*/ CH4* Print(FP8 item);
#endif

 private:
  // String too big to fit in the strand_.
  const CH4* string_;
  SI4 count_;  //< Either kTokenLongest or an abstract variable.
  CH4 strand_[kTokenLongest + 1];  //< Strand socket.
};

/* Utility class for printing right-aligned with operator<<. */
struct Right4 {
  Token4 token;

  /* Prints the item to the token_. */
  Right4(const CH4*, SI4 count = kTokenLongest);

  /* Prints the item to the token_. */
  Right4(SI4 item, SI4 count = kTokenLongest);

  /* Prints the item to the token_. */
  Right4(UI4 item, SI4 count = kTokenLongest);

  /* Prints the item to the token_. */
  Right4(SI8 item, SI4 count = kTokenLongest);

  /* Prints the item to the token_. */
  Right4(UI8 item, SI4 count = kTokenLongest);

#if USING_FP4 == YES
  /* Prints the item to the token_. */
  Right4(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  /* Prints the item to the token_. */
  Right4(FP8 item, SI4 count = kTokenLongest);
#endif
};

/* Utility class for printing center-aligned with operator<<. */
struct Center4 {
  Token4 token;

  /* Prints the item to the token. */
  Center4(const CH4*, SI4 count = kTokenLongest);
  Center4(SI4 item, SI4 count = kTokenLongest);
  Center4(UI4 item, SI4 count = kTokenLongest);
  Center4(SI8 item, SI4 count = kTokenLongest);
  Center4(UI8 item, SI4 count = kTokenLongest);
#if USING_FP4 == YES
  Center4(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  Center4(FP8 item, SI4 count = kTokenLongest);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct SDK Linef4 {
  Token4 token;

  /* Constructors a horizontal line of the given string. */
  Linef4(const CH4* string = nullptr, SI4 count = kTokenLongest);

  /* Constructors a horizontal line of the given string. */
  Linef4(CH4 item, SI4 count = kTokenLongest);
};

/* Utility class for printing a vertical line with operator<<. */
struct SDK Headingf4 {
  Token4 caption;
  Linef4 style;
  const CH4 *caption2, *caption3;

  /* Constructors a horizontal line of the given string. */
  Headingf4(const CH4* caption, const CH4* style = nullptr,
            SI4 count = kTokenLongest, const CH4* caption2 = nullptr,
            const CH4* caption3 = nullptr);
};

struct SDK Char4 {
  CH4 value;  //< A Unicode value.

  Char4(CH4 value);  //< Stores value.
};

struct SDK Chars4 {
  const CH4 *start,  //< Start character address.
      *stop;         //< Stop character address.

  Chars4(const CH4* start, const CH4* stop);
};

/* Universal Text Formatter (UTF) 8 is a utility class for printing UTF-8
strings.
This class only stores the stop of socket pointer and a pointer to the
write start. It is up the user to store start of socket pointer and if they
would like to replace the start with the beginning of socket pointer when they
are done printing. */
struct SDK UTF4 {
  CH4 *start,  //< Start of the array.
      *stop;   //< Stop of the array.

  UTF4(CH4* start, SIW size_bytes);
  UTF4(CH4* start, CH4* stop);

  UTF4(const UTF4& other);

  /* Sets the start pointer to the new_pointer if it's not nil. */
  /*inline*/ UTF4& Set(CH4* new_pointer);

  /* Prints a item to the strand. */
  /*inline*/ UTF4& Print(CH1 item);
  /*inline*/ UTF4& Print(CH2 item);
  /*inline*/ UTF4& Print(CH4 item);
  /*inline*/ UTF4& Print(const CH1* item);
  /*inline*/ UTF4& Print(const CH2* item);
  /*inline*/ UTF4& Print(const CH4* item);
  /*inline*/ UTF4& Print(SI4 item);
  /*inline*/ UTF4& Print(UI4 item);
  /*inline*/ UTF4& Print(SI8 item);
  /*inline*/ UTF4& Print(UI8 item);

#if SEAM >= SCRIPT2_4
  /*inline*/ UTF4& Print(FP4 item);
  /*inline*/ UTF4& Print(FP8 item);
#endif
  /*inline*/ UTF4& Print(Right4 item);
  /*inline*/ UTF4& Print(Center4 item);
  /*inline*/ UTF4& Print(Linef4 item);
  /*inline*/ UTF4& Print(Headingf4 item);
  /*inline*/ UTF4& Print(::_::Hex item);

  /* Prints the given item as hex. */
  /*inline*/ UTF4& Hex(SI1 item);
  /*inline*/ UTF4& Hex(UI1 item);
  /*inline*/ UTF4& Hex(SI2 item);
  /*inline*/ UTF4& Hex(UI2 item);
  /*inline*/ UTF4& Hex(SI4 item);
  /*inline*/ UTF4& Hex(UI4 item);

  /* Prints the given item as hex. */
  /*inline*/ UTF4& Hex(SI8 item);
  /*inline*/ UTF4& Hex(UI8 item);
#if USING_FP4 == YES
  /*inline*/ UTF4& Hex(FP4 item);
#endif
#if USING_FP8 == YES
  /*inline*/ UTF4& Hex(FP8 item);
#endif
  /*inline*/ UTF4& Hex(const void* pointer);

  /* Prints the given item as binary. */
  /*inline*/ UTF4& Binary(SI1 item);
  /*inline*/ UTF4& Binary(UI1 item);
  /*inline*/ UTF4& Binary(SI2 item);
  /*inline*/ UTF4& Binary(UI2 item);
  /*inline*/ UTF4& Binary(SI4 item);
  /*inline*/ UTF4& Binary(UI4 item);
  /*inline*/ UTF4& Binary(SI8 item);
  /*inline*/ UTF4& Binary(UI8 item);

#if USING_FP4 == YES
  /*inline*/ UTF4& Binary(FP4 item);
#endif
#if USING_FP8 == YES
  /*inline*/ UTF4& Binary(FP8 item);
#endif

  /* Prints the given pointer as binary. */
  /*inline*/ UTF4& Binary(const void* pointer);
};

#if USING_STR == UTF32
using Token = Token4;
using Right = Right4;
using Center = Center4;
using Columns = Linef4;
using Rows = Headingf4;
#endif

}  // namespace _

SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::UTF4& item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, const CH4* item);

SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, CH4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, UI1 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, SI2 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, UI2 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, SI4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, UI4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, SI8 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, UI8 item);

#if USING_FP4 == YES
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, FP4 item);
#endif
#if USING_FP8 == YES
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, FP8 item);
#endif

SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Hex item);

SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Center4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Right4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Linef4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Headingf4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Char4 item);
SDK /*inline*/ ::_::UTF4& operator<<(::_::UTF4& o, ::_::Chars4 item);

#endif  //< #if USING_UTF32 == YES
#endif
#endif
