/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_utf2.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#ifndef INCLUDED_SCRIPTPRINT_UTF16
#define INCLUDED_SCRIPTPRINT_UTF16

#include "c_uniprinter.h"

#if SEAM >= SCRIPT2_3

#include "c_ascii.h"
#include "c_object.h"

#if USING_UTF16 == YES

namespace _ {

/* ASCII printing utilities
@ingroup UTF
*/

/* UTF-16 printing utilities
@ingroup ASCII CH1*
*/

/* Strand Factory that prints the string upon destruction.
SI4 COutHeap4 (CObject& obj, SIW function, void* arg); */

/* Checks if the given character is whitespace.
 */
SDK BOL IsWhitespace(CH2 character);

/* Converts the given item to a printable CH2 if it's non-printable. */
SDK CH2 PrintableChar(CH2 item);

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH2. */
SDK const CH2* STREnd(const CH2* text);

/* Gets the length of the given CH2.
@return  Returns -1 if the text CH2 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH2. */
SDK SI4 StrandLength(const CH2* text);

/* Returns a pointer to the CH2 at the stop of the line. */
SDK const CH2* StrandLineEnd(const CH2* start, SI4 count = 80);

/* Returns the pointer to the next CH2 in the CH2 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the text CH2. */
SDK const CH2* StrandDecimalEnd(const CH2* start);

/* Returns the pointer to the next CH2 in the CH2 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the text CH2. */
SDK const CH2* StrandDecimalEnd(const CH2* start);

/* Skips the leading zeros of a token_ if there are any. */
SDK const CH2* STRSkipChar(const CH2* start, CH2 skip_char);

/* Skips all the spaces at the start of the CH2. */
SDK const CH2* STRSkipSpaces(const CH2* start);

/* Compares the source and query CH2 as nil-terminated strings.
@return Nil if the given strings aren't equivalant or a pointer to the end of
the token. */
SDK const CH2* STREquals(const CH2* start, const CH2* token);

/* Searches the given CH2 for the given CH2.
@param  text      The CH2 to search.
@param  query      The CH2 to search for.
@return Returns nil if the parsing failed and a pointer to the first CH2
after the stop of the text upon success. */
SDK const CH2* STRFind(const CH2* start, const CH2* query);

/* Prints the given item to the utf socket. */
#if USING_UTF8 == YES
SDK CH2* Print(CH2* start, CH2* stop, const CH1* item);
#endif

SDK CH2* Print(CH2* start, CH2* stop, const CH2* item);

#if USING_UTF32 == YES
SDK CH2* Print(CH2* start, CH2* stop, const CH4* item);
#endif
SDK CH2* Print(CH2* start, CH2* stop, UI4 item);
SDK CH2* Print(CH2* start, CH2* stop, SI4 item);
SDK CH2* Print(CH2* start, CH2* stop, UI8 item);
SDK CH2* Print(CH2* start, CH2* stop, SI8 item);
#if USING_FP4 == YES
SDK CH2* Print(CH2* start, CH2* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK CH2* Print(CH2* start, CH2* stop, FP8 item);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string The potentially unsafe string to write. */
SDK CH2* PrintCenter(CH2* start, CH2* stop, const CH2* string, SI4 count = 80);
SDK CH2* PrintCenter(CH2* start, CH2* stop, CH2 character, SI4 count = 80);
SDK CH2* PrintCenter(CH2* start, CH2* stop, UI4 valu, SI4 count = 80);
SDK CH2* PrintCenter(CH2* start, CH2* stop, SI4 item, SI4 count = 80);
SDK CH2* PrintCenter(CH2* start, CH2* stop, UI8 item, SI4 count = 80);
SDK CH2* PrintCenter(CH2* start, CH2* stop, SI8 item, SI4 count = 80);
#if USING_FP4 == YES
SDK CH2* PrintCenter(CH2* start, CH2* stop, FP4 item, SI4 count = 80);
#endif
#if USING_FP8 == YES
SDK CH2* PrintCenter(CH2* start, CH2* stop, FP8 item, SI4 count = 80);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param string The potentially unsafe string to write. */
SDK CH2* PrintRight(CH2* start, CH2* stop, const CH2* string, SI4 count = 80);
SDK CH2* PrintRight(CH2* start, CH2* stop, CH2 character, SI4 count = 80);
SDK CH2* PrintRight(CH2* start, CH2* stop, UI4 item, SI4 count = 80);
SDK CH2* PrintRight(CH2* start, CH2* stop, SI4 item, SI4 count = 80);
SDK CH2* PrintRight(CH2* start, CH2* stop, UI8 item, SI4 count = 80);
SDK CH2* PrintRight(CH2* start, CH2* stop, SI8 item, SI4 count = 80);
#if USING_FP4 == YES
SDK CH2* PrintRight(CH2* start, CH2* stop, FP4 item, SI4 count = 80);
#endif
#if USING_FP8 == YES
SDK CH2* PrintRight(CH2* start, CH2* stop, FP8 item, SI4 count = 80);
#endif

/* Prints the given uten to the UTF socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start   The beginning address of the socket.
@param stop     The stop address of the socket.
@param pointer The pointer to utf. */
SDK CH2* PrintHex(CH2* start, CH2* stop, const void* pointer);
SDK CH2* PrintHex(CH2* start, CH2* stop, UI1 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, SI1 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, UI2 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, SI2 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, UI4 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, SI4 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, UI8 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, SI8 item);

#if SEAM >= SCRIPT2_4
SDK CH2* PrintHex(CH2* start, CH2* stop, FP4 item);
SDK CH2* PrintHex(CH2* start, CH2* stop, FP8 item);
#endif

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param pointer The pointer to utf to hex. */
SDK CH2* PrintBinary(CH2* start, CH2* stop, const void* pointer);
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI1 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI1 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI2 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI2 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI4 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI4 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, UI8 item);
SDK CH2* PrintBinary(CH2* start, CH2* stop, SI8 item);
#if USING_FP4 == YES
SDK CH2* PrintBinary(CH2* start, CH2* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK CH2* PrintBinary(CH2* start, CH2* stop, FP8 item);
#endif

/* Prints out the contents of the address to the printer socket. */
SDK CH2* PrintChars(CH2* start, CH2* stop, const void* begin, const void* end);

/* Prints out the contents of the address to the printer socket. */
SDK CH2* PrintChars(CH2* start, CH2* stop, const void* begin, SIW size);

/* Prints a line of the given count. */
SDK CH2* PrintLinef(CH2* start, CH2* stop, CH2 token, SI4 count = 80);

/* Prints a line of the given count. */
SDK CH2* PrintLinef(CH2* start, CH2* stop, const CH2* string, SI4 count = 80);

/* Prints a item repeated the given count. */
SDK CH2* PrintRepeat(CH2* start, CH2* stop, CH2 token, SI4 count = 80);

/* Prints a item repeated the given count. */
SDK CH2* PrintRepeat(CH2* start, CH2* stop, const CH2* string, SI4 count = 80);

/* Prints the socket to the console as a UTF-8 string.
void COut2(UIW* socket); */

/* Prints the socket to the console as a UTF-8 string.
void COutAuto2(UIW* socket); */

/* Converts the given string to a 8-bit signed integer.
@param  text A nil-terminated string in ROM.
@param  result  The result of the conversion.
@return Returns a pointer to the next CH2 after the stop
of the read token_ or nil upon failure. */
SDK const CH2* Scan(const CH2* start, SI1& result);
SDK const CH2* Scan(const CH2* text, SI1& result);
SDK const CH2* Scan(const CH2* text, UI1& result);
SDK const CH2* Scan(const CH2* text, SI2& result);
SDK const CH2* Scan(const CH2* text, UI2& result);
SDK const CH2* Scan(const CH2* text, SI4& result);
SDK const CH2* Scan(const CH2* text, UI4& result);
SDK const CH2* Scan(const CH2* text, SI8& result);
SDK const CH2* Scan(const CH2* text, UI8& result);
#if SEAM >= SCRIPT2_4
SDK const CH2* Scan(const CH2* text, FP4& result);
SDK const CH2* Scan(const CH2* text, FP8& result);
#endif

/* Utility class for printing numbers. */
class Token2 {
 public:
  /* Constructs a Token1 from the given item. */
  Token2(const CH1* item = nullptr, SI4 count = kTokenLongest);

  /* Constructs a Token1 from the given item. */
  Token2(CH1 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token2(CH2 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token2(const CH2* item, SI4 count = kTokenLongest);

#if USING_UTF32
  /* Constructs a Token1 from the given item. */
  Token2(CH4 item, SI4 count = kTokenLongest);

  /* Constructs a Token1 from the given item. */
  Token2(const CH4* item, SI4 count = kTokenLongest);
#endif

  /* Prints the item to the strand_. */
  Token2(SI4 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token2(UI4 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token2(SI8 item, SI4 count = kTokenLongest);

  /* Prints the item to the strand_. */
  Token2(UI8 item, SI4 count = kTokenLongest);

#if USING_FP4 == YES
  /* Prints the item to the strand_. */
  Token2(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  /* Prints the item to the strand_. */
  Token2(FP8 item, SI4 count = kTokenLongest);
#endif

  /* Gets the string_. */
  const CH2* String();

  /* Gets the strand_. */
  CH2* Strand();

  /* Gets the number string_ or the strand_ if the string_ is nil. */
  const CH2* Get();

  /* Sets the string_ to the new string.
  @return Nil upon failure or the string upon success. */
  const CH2* Set(const CH2* string);

  /* Gets the count. */
  SI4 Count();

  /* Prints the given item to the strand_. */
  /*inline*/ CH2* Print(CH1 item);
  /*inline*/ CH2* Print(const CH1* item);
#if USING_UTF16 == YES
  /*inline*/ CH2* Print(CH2 item);
  /*inline*/ CH2* Print(const CH2* item);
#endif
#if USING_UTF32 == YES
  /*inline*/ CH2* Print(const CH4* item);
  /*inline*/ CH2* Print(CH4 item);
#endif
  /*inline*/ CH2* Print(SI4 item);
  /*inline*/ CH2* Print(UI4 item);
  /*inline*/ CH2* Print(SI8 item);
  /*inline*/ CH2* Print(UI8 item);

#if USING_FP4 == YES
  /*inline*/ CH2* Print(FP4 item);
#endif
#if USING_FP8 == YES
  /*inline*/ CH2* Print(FP8 item);
#endif

 private:
  // A String too long to fit in the strand.
  const CH2* string_;
  SI4 count_;  //< Either kTokenLongest or an abstract variable.
  CH2 strand_[kTokenLongest + 1];  //< Strand socket.
};

/* Utility class for printing hex with operator<<. */
struct Right2 {
  Token2 token;

  /* Prints the item to the token_. */
  Right2(CH1 item, SI4 count = 80);
  Right2(const CH1* item, SI4 count = 80);
  Right2(CH2 item, SI4 count = 80);
  Right2(const CH2* item, SI4 count = 80);
#if USING_UTF32
  Right2(CH4 item, SI4 count = 80);
  Right2(const CH4* item, SI4 count = 80);
#endif
  Right2(SI4 item, SI4 count = 80);
  Right2(UI4 item, SI4 count = 80);
  Right2(SI8 item, SI4 count = 80);
  Right2(UI8 item, SI4 count = 80);

#if USING_FP4 == YES
  Right2(FP4 item, SI4 count = 80);
#endif
#if USING_FP8 == YES
  Right2(FP8 item, SI4 count = 80);
#endif
};

/* Utility class for printing items center-aligned with operator<<. */
struct Center2 {
  Token2 token;

  /* Prints the item to the token_ center aligned to the given count. */
  Center2(CH1 item, SI4 count = 80);
  Center2(const CH1* item, SI4 count = 80);
  Center2(CH2 item, SI4 count = 80);
  Center2(const CH2* item, SI4 count = 80);
#if USING_UTF32
  Center2(CH4 item, SI4 count = 80);
  Center2(const CH4* item, SI4 count = 80);
#endif
  Center2(SI4 item, SI4 count = 80);
  Center2(UI4 item, SI4 count = 80);
  Center2(SI8 item, SI4 count = 80);
  Center2(UI8 item, SI4 count = 80);
#if USING_FP4 == YES
  Center2(FP4 item, SI4 count = 80);
#endif
#if USING_FP8 == YES
  Center2(FP8 item, SI4 count = 80);
#endif

 private:
  const CH2* string_;  //< Pointer to the string.
  SI4 count_;          //< Number of columns to center.
  Token2 token_;
};

/* Utility class for printing a horizontal line with operator<<. */
struct SDK Linef2 {
  Token2 token;

  /* Constructors a horizontal line of the given string. */
  Linef2(const CH1* item, SI4 count = 80);

  /* Constructors a horizontal line of the given string. */
  Linef2(CH1 item, SI4 count = 80);

  /* Constructors a horizontal line of the given string. */
  Linef2(CH2 item, SI4 count = 80);

  /* Constructors a horizontal line of the given string. */
  Linef2(const CH2* string = nullptr, SI4 count = 80);
};

/* Utility class for printing a Headingf with operator<<. */
struct SDK Headingf2 {
  Token2 caption;
  const CH2 *style, *caption2, *caption3;

  /* Constructors a horizontal line of the given string. */
  Headingf2(const CH2* caption, const CH2* style = nullptr, SI4 count = 80,
            const CH2* caption2 = nullptr, const CH2* caption3 = nullptr);
};

struct SDK Chars2 {
  const CH2 *start,  //< Start character address.
      *stop;         //< Stop character address.

  Chars2(const CH2* start, const CH2* stop);
};

/* Utility class for printing strings.
This class only stores the stop of socket pointer and a pointer to the write
start. It is up the user to store start of socket pointer and if they would
like to replace the start with the beginning of socket pointer when they
are done printing. */
struct SDK UTF2 {
  CH2 *start,  //< Start of the array.
      *stop;   //< Stop of the array.

  /* Initializes the UTF& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF2(CH2* start, SIW size);

  /* Initializes the UTF& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF2(CH2* start, CH2* stop);

  /* Clones the other utf. */
  UTF2(const UTF2& other);

  /* Sets the start pointer to the new_pointer. */
  /*inline*/ UTF2& Set(CH2* new_start);

  /* Prints a item to the strand. */
  /*inline*/ UTF2& PrintChar(CH1 item);
  /*inline*/ UTF2& Print(CH1 item);
  /*inline*/ UTF2& Print(const CH1* item);
  /*inline*/ UTF2& PrintChar(CH2 item);
  /*inline*/ UTF2& Print(CH2 item);
  /*inline*/ UTF2& Print(const CH2* item);
  /*inline*/ UTF2& PrintChar(CH4 item);
  /*inline*/ UTF2& Print(CH4 item);
  /*inline*/ UTF2& Print(const CH4* item);
  /*inline*/ UTF2& Print(SI4 item);
  /*inline*/ UTF2& Print(UI4 item);
  /*inline*/ UTF2& Print(SI8 item);
  /*inline*/ UTF2& Print(UI8 item);
  /*inline*/ UTF2& Print(Right2 item);
  /*inline*/ UTF2& Print(Center2 item);
  /*inline*/ UTF2& Print(Linef2 item);
  /*inline*/ UTF2& Print(Headingf2 item);
  /*inline*/ UTF2& Print(Chars2 item);

  /*inline*/ UTF2& Print(::_::Hex item);

  /* Prints the given item as hex. */
  /*inline*/ UTF2& Hex(SI1 item);
  /*inline*/ UTF2& Hex(UI1 item);
  /*inline*/ UTF2& Hex(SI2 item);
  /*inline*/ UTF2& Hex(UI2 item);
  /*inline*/ UTF2& Hex(SI4 item);
  /*inline*/ UTF2& Hex(UI4 item);
  /*inline*/ UTF2& Hex(SI8 item);
  /*inline*/ UTF2& Hex(UI8 item);
  /*inline*/ UTF2& Hex(const void* item);
  /*inline*/ UTF2& Hex(const void* item, SIW size_bytes);

  /* Prints the given item as binary. */
  /*inline*/ UTF2& Binary(SI1 item);
  /*inline*/ UTF2& Binary(UI1 item);
  /*inline*/ UTF2& Binary(SI2 item);
  /*inline*/ UTF2& Binary(UI2 item);
  /*inline*/ UTF2& Binary(SI4 item);
  /*inline*/ UTF2& Binary(UI4 item);

  /* Prints the given item as binary. */
  /*inline*/ UTF2& Binary(SI8 item);

  /* Prints the given item as binary. */
  /*inline*/ UTF2& Binary(UI8 item);

#if USING_FP4 == YES
  /* Prints the given item. */
  /*inline*/ UTF2& Print(FP4 item);
  /* Prints the given item as hex. */
  /*inline*/ UTF2& Hex(FP4 item);
  /* Prints the given item as binary. */
  /*inline*/ UTF2& Binary(FP4 item);
#endif
#if USING_FP8 == YES
  /* Prints the given item. */
  /*inline*/ UTF2& Print(FP8 item);
  /* Prints the given item as hex. */
  /*inline*/ UTF2& Hex(FP8 item);
  /* Prints the given item as binary. */
  /*inline*/ UTF2& Binary(FP8 item);
#endif

  /* Prints the given pointer as binary. */
  /*inline*/ UTF2& Binary(const void* item);
};

#if USING_STR == UTF16
using Token = Token2;
using Right = Right2;
using Center = Center2;
using Columns = Linef2;
using Rows = Headingf2;
#endif

}  // namespace _

SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Char4 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, CH4 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::UTF2& p);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, const CH1* string);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, const CH2* string);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, const CH4* item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, UI1 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, SI2 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, UI2 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, SI4 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, UI4 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, SI8 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, UI8 item);
#if USING_FP4 == YES
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, FP4 item);
#endif
#if USING_FP8 == YES
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, FP8 item);
#endif
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Hex item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Center2 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Right2 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Linef2 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Headingf2 item);
SDK /*inline*/ ::_::UTF2& operator<<(::_::UTF2& o, ::_::Chars2 item);

#endif  //< #if USING_UTF16
#endif
#endif
