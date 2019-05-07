/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_utf1.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef INCLUDED_SCRIPT2_UTF8
#define INCLUDED_SCRIPT2_UTF8

#include "c_uniprinter.h"

#if SEAM >= SCRIPT2_3

#include "c_ascii.h"
#include "c_object.h"

#ifndef USING_UTF8
#define USING_UTF8 YES
#endif

#if USING_UTF8 == YES

namespace _ {

/* UTF-8 printing utilities.
@ingroup ASCII STR and TKN
*/

/* Strand Factory that prints the string upon destruction.
SI4 COutHeap1(CObject& obj, SIW function, void* arg); */

/* Checks if the given character is whitespace. */
SDK BOL IsWhitespace(CH1 character);

/* Converts the given item to a printable CH1 if it's non-printable. */
SDK CH1 PrintableChar(CH1 item);

/* Scrolls over to the next FP8 quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
SDK const CH1* STREnd(const CH1* start);

/* Gets the length of the given CH1.
@return  Returns -1 if the string CH1 is nil.
@warning This function is only safe to use on ROM strings with a nil-term
CH1. */
SDK SI4 StrandLength(const CH1* start);

/* Clones the given string.
@param  A nil-terminated string in ROM.
@return Returns a new copy you must delete.
SDK CH1* StrandClone(const CH1* start); */

/* Returns a pointer to the CH1 at the stop of the line. */
SDK const CH1* StrandLineEnd(const CH1* start, SI4 count = kTokenLongest);

/* Returns a pointer to the CH1 at the stop of the row. */
SDK const CH1* StrandLineEnd(const CH1* start, const CH1* stop,
                             SI4 count = kTokenLongest);

/* Returns the pointer to the next CH1 in the CH1 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the string CH1. */
SDK const CH1* StrandDecimalStop(const CH1* start, const CH1* stop);

/* Returns the pointer to the next CH1 in the CH1 that is not an ASCII
token_.
@return A pointer to the next non-token_ in the string CH1. */
SDK const CH1* StrandDecimalStop(const CH1* start);

/* Skips the leading zeros of a token_ if there are any. */
SDK const CH1* STRSkipChar(const CH1* start, CH1 skip_char);

/* Skips all the spaces at the start of the CH1. */
SDK const CH1* STRSkipSpaces(const CH1* start);

/* Skips all the spaces at the start of the CH1.
@return Nil upon failure or a pointer to the terminator upon success.
@param  start Beginning address of the read socket.
@param  stop   The stop address of the input socket. */
SDK const CH1* STRSkipSpaces(const CH1* start, const CH1* stop);

/* Compares the source and query CH1 as nil-terminated strings. */
SDK const CH1* STREquals(const CH1* start, const CH1* begin);

/* Compares the source and query CH1 as nil-terminated strings. */
SDK const CH1* STREquals(const CH1* start, const CH1* stop, const CH1* query);

/* Searches the given CH1 for the given CH1.
@return Nil upon failure or a pointer to the terminator upon success.
@param  string The CH1 to search.
@param  query  The CH1 to search for. */
SDK const CH1* STRFind(const CH1* start, const CH1* query);

/* Prints the given string to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param  start  The beginning address of the socket.
@param  stop    The stop address of the socket.
@param  string The potentially unsafe string to write. */
SDK CH1* Print(CH1* start, CH1* stop, const CH1* item);

#if USING_UTF16 == YES
SDK CH1* Print(CH1* start, CH1* stop, const CH2* item);
#endif

#if USING_UTF32 == YES
SDK CH1* Print(CH1* start, CH1* stop, const CH4* item);
#endif
SDK CH1* Print(CH1* start, CH1* stop, UI4 item);
SDK CH1* Print(CH1* start, CH1* stop, SI4 item);
SDK CH1* Print(CH1* start, CH1* stop, UI8 item);
SDK CH1* Print(CH1* start, CH1* stop, SI8 item);

#if USING_FP4 == YES
SDK CH1* PrintCenter(CH1* start, CH1* stop, FP4 item,
                     SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
SDK CH1* PrintCenter(CH1* start, CH1* stop, FP8 item,
                     SI4 count = kTokenLongest);
#endif
SDK CH1* PrintRight(CH1* start, CH1* stop, FP4 item, SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, FP8 item, SI4 count = kTokenLongest);

#endif  //< SCRIPT2_1

/* Prints the given item to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param item The potentially unsafe item to write. */
SDK CH1* PrintCenter(CH1* start, CH1* stop, const CH1* item,
                     SI4 count = kTokenLongest);
SDK CH1* PrintCenter(CH1* start, CH1* stop, CH1 character,
                     SI4 count = kTokenLongest);
SDK CH1* PrintCenter(CH1* start, CH1* stop, UI4 item,
                     SI4 count = kTokenLongest);
SDK CH1* PrintCenter(CH1* start, CH1* stop, SI4 item,
                     SI4 count = kTokenLongest);
SDK CH1* PrintCenter(CH1* start, CH1* stop, UI8 item,
                     SI4 count = kTokenLongest);
SDK CH1* PrintCenter(CH1* start, CH1* stop, SI8 item,
                     SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, const CH1* item,
                    SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, CH1 character,
                    SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, UI4 item, SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, SI4 item, SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, UI8 item, SI4 count = kTokenLongest);
SDK CH1* PrintRight(CH1* start, CH1* stop, SI8 item, SI4 count = kTokenLongest);

/* Prints the given item to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param item The potentially unsafe item to write. */
SDK CH1* PrintHex(CH1* start, CH1* stop, const void* pointer);
SDK CH1* PrintHex(CH1* start, CH1* stop, SI1 item);
SDK CH1* PrintHex(CH1* start, CH1* stop, UI2 item);
SDK CH1* PrintHex(CH1* start, CH1* stop, SI2 item);
SDK CH1* PrintHex(CH1* start, CH1* stop, UI4 item);
SDK CH1* PrintHex(CH1* start, CH1* stop, SI4 item);
SDK CH1* PrintHex(CH1* start, CH1* stop, UI8 item);
SDK CH1* PrintHex(CH1* start, CH1* stop, SI8 item);
#if USING_FP4 == YES
SDK CH1* PrintHex(CH1* start, CH1* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK CH1* PrintHex(CH1* start, CH1* stop, FP8 item);
#endif

/* Prints the given item to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start  The beginning address of the socket.
@param stop    The stop address of the socket.
@param pointer The pointer to utf to hex. */
SDK CH1* PrintBinary(CH1* start, CH1* stop, const void* pointer);
SDK CH1* PrintBinary(CH1* start, CH1* stop, UI1 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, SI1 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, UI2 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, SI2 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, UI4 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, SI4 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, UI8 item);
SDK CH1* PrintBinary(CH1* start, CH1* stop, SI8 item);
#if USING_FP4 == YES
SDK CH1* PrintBinary(CH1* start, CH1* stop, FP4 item);
#endif
#if USING_FP8 == YES
SDK CH1* PrintBinary(CH1* start, CH1* stop, FP8 item);
#endif

/* Prints the given memory socket to the item socket. */
SDK CH1* PrintChars(CH1* start, CH1* stop, const void* begin, SIW size);

/* Prints out the contents of the address to the utf socket.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param start The beginning of the read socket.
@param stop  The stop of the read socket. */
SDK CH1* PrintChars(CH1* start, CH1* stop, const void* begin, const void* end);

/* Prints a line of the given count of columns.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param token The token to utf.
@param count The token_ of tokens to utf. */
SDK CH1* PrintLinef(CH1* cursor, CH1* stop, CH1 token,
                    SI4 count = kTokenLongest);

/* Prints a line of the given count of columns.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param item  The item to utf.
@param count The token_ of columns. */
SDK CH1* PrintLinef(CH1* cursor, CH1* stop, const CH1* item,
                    SI4 count = kTokenLongest);

/* Prints a line of the given count of columns.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param token The token to utf.
@param count The token_ of tokens to utf. */
SDK CH1* PrintRepeat(CH1* cursor, CH1* stop, CH1 token,
                     SI4 count = kTokenLongest);

/* Prints a line of the given count of columns.
@return Nil upon failure or a pointer to the terminator upon success.
@param start The beginning of the write socket.
@param stop  The stop of the write socket.
@param item  The item to utf.
@param count The token_ of columns. */
SDK CH1* PrintRepeat(CH1* cursor, CH1* stop, const CH1* item,
                     SI4 count = kTokenLongest);

/* Converts the given string to a 8-bit signed integer.
@return Null upon failure or a pointer to the UI1 after the last
UI1 written.
@param  string A nil-terminated string in ROM.
@param  result The result of the conversion. */
SDK const CH1* Scan(const CH1* start, SI1& result);
SDK const CH1* Scan(const CH1* start, SI1& result);
SDK const CH1* Scan(const CH1* start, UI1& result);
SDK const CH1* Scan(const CH1* start, SI2& result);
SDK const CH1* Scan(const CH1* start, UI2& result);
SDK const CH1* Scan(const CH1* start, SI4& result);
SDK const CH1* Scan(const CH1* start, UI4& result);
SDK const CH1* Scan(const CH1* start, SI8& result);
SDK const CH1* Scan(const CH1* start, UI8& result);
#if USING_FP4 == YES
SDK const CH1* Scan(const CH1* start, FP4& result);
#endif
#if USING_FP8 == YES
SDK const CH1* Scan(const CH1* start, FP8& result);
#endif

/* AsciiFactory Prints the socket to the console as a UTF-8 string.
UIW* COutUTF8(UIW* socket, SIW function, void* arg); */

/* Prints the socket to the console as a UTF-8 string.
UIW* COutAutoUTF8(UIW* socket, SIW function, void* arg); */

/* Utility class for printing numbers. */
class Token1 {
 public:
  /* Constructs a Token1 from the given item. */
  Token1(const CH1* item = nullptr, SI4 count = kTokenLongest);
  Token1(CH1 item, SI4 count = kTokenLongest);
#if USING_UTF16 == YES
  Token1(CH2 item, SI4 count = kTokenLongest);
  Token1(const CH2* item, SI4 count = kTokenLongest);
#endif
#if USING_UTF32 == YES
  Token1(CH4 item, SI4 count = kTokenLongest);
  Token1(const CH4* item, SI4 count = kTokenLongest);
#endif
  Token1(SI4 item, SI4 count = kTokenLongest);
  Token1(UI4 item, SI4 count = kTokenLongest);
  Token1(SI8 item, SI4 count = kTokenLongest);
  Token1(UI8 item, SI4 count = kTokenLongest);
#if USING_FP4 == YES
  Token1(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  Token1(FP8 item, SI4 count = kTokenLongest);
#endif

  /* Gets the count. */
  SI4 Count();

  /* Gets the token_ string. */
  const CH1* String();

  /* Gets the token_ strand_. */
  CH1* Strand();

  /* Gets the token_ strand_. */
  const CH1* Get();

  /* Sets the string_ to the new string.
  @return Nil upon failure or the string upon success. */
  const CH1* Set(const CH1* start);

  /* Prints the given item to the strand_. */
  /*inline*/ CH1* Print(CH1 item);
  /*inline*/ CH1* Print(const CH1* item);
#if USING_UTF16 == YES
  /*inline*/ CH1* Print(CH2 item);
  /*inline*/ CH1* Print(const CH2* item);
#endif
#if USING_UTF32 == YES
  /*inline*/ CH1* Print(const CH4* item);
  /*inline*/ CH1* Print(CH4 item);
#endif
  /*inline*/ CH1* Print(SI4 item);
  /*inline*/ CH1* Print(UI4 item);
  /*inline*/ CH1* Print(SI8 item);
  /*inline*/ CH1* Print(UI8 item);
#if USING_FP4 == YES
  /*inline*/ CH1* Print(FP4 item);
#endif
#if USING_FP8 == YES
  /*inline*/ CH1* Print(FP8 item);
#endif

 private:
  // Pointer to a token too big to fit in the strand_.
  const CH1* string_;
  SI4 count_;  //< Either kTokenLongest or an abstract variable.
  CH1 strand_[kTokenLongest + 1];  //< Strand socket.
};

/* Utility class for printing hex with operator<<. */
struct Center1 {
  Token1 token;  //< Pointer to a pointer to utf.

  /* Prints the item to the token. */
  Center1(CH1 item, SI4 count = kTokenLongest);
  Center1(const CH1* start, SI4 count = kTokenLongest);
#if USING_UTF16 == YES
  Center1(CH2 item, SI4 count = kTokenLongest);
  Center1(const CH2* item, SI4 count = kTokenLongest);
#endif
#if USING_UTF32 == YES
  Center1(CH4 item, SI4 count = kTokenLongest);
  Center1(const CH4* item, SI4 count = kTokenLongest);
#endif
  Center1(SI4 item, SI4 count = kTokenLongest);

  Center1(UI4 item, SI4 count = kTokenLongest);
  Center1(SI8 item, SI4 count = kTokenLongest);
  Center1(UI8 item, SI4 count = kTokenLongest);

#if USING_FP4 == YES
  Center1(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  Center1(FP8 item, SI4 count = kTokenLongest);
#endif
};

/* Utility class for printing hex with operator<<. */
struct Right1 {
  Token1 token;  //< Pointer to a pointer to utf.

  /* Prints the item to the token. */
  Right1(CH1 item, SI4 count = kTokenLongest);
  Right1(const CH1* item, SI4 count = kTokenLongest);
#if USING_UTF16 == YES
  Right1(CH2 item, SI4 count = kTokenLongest);
  Right1(const CH2* item, SI4 count = kTokenLongest);
#endif
#if USING_UTF32 == YES
  Right1(CH4 item, SI4 count = kTokenLongest);
  Right1(const CH4* item, SI4 count = kTokenLongest);
#endif
  Right1(SI4 item, SI4 count = kTokenLongest);
  Right1(UI4 item, SI4 count = kTokenLongest);
  Right1(SI8 item, SI4 count = kTokenLongest);
  Right1(UI8 item, SI4 count = kTokenLongest);

#if USING_FP4 == YES
  Right1(FP4 item, SI4 count = kTokenLongest);
#endif
#if USING_FP8 == YES
  Right1(FP8 item, SI4 count = kTokenLongest);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct SDK Linef1 {
  Token1 token;  //< Pointer to a pointer to utf.

  /* Constructors a horizontal line of the given string. */
  Linef1(CH1 item, SI4 count = kTokenLongest);

  /* Constructors a horizontal line of the given string. */
  Linef1(const CH1* start = nullptr, SI4 count = kTokenLongest);
};

/* Utility class for printing a vertical line with operator<<. */
struct SDK Headingf1 {
  Token1 caption;
  const CH1 *style, *caption2, *caption3;

  /* Constructors a horizontal line of the given string. */
  Headingf1(const CH1* caption, const CH1* style = nullptr,
            SI4 count = kTokenLongest, const CH1* caption2 = nullptr,
            const CH1* caption3 = nullptr);
};

struct SDK Char1 {
  CH1 value;  //< A Unicode value.

  Char1(CH1 ch);  //< Stores the value.
};

// Utility function for force printing a CH1 using operator overloads.
SDK Char1 ToCharStruct(CH1 value);

struct SDK Chars1 {
  const CH1 *start,  //< Start character address.
      *stop;         //< Stop character address.

  Chars1(const CH1* start, const CH1* stop);
};

/* Utility class for printing strings.
This class only stores the stop of socket pointer and a pointer to the write
start. It is up the user to store start of socket pointer and if they would
like to replace the start with the beginning of socket pointer when they
are done printing. */
struct SDK UTF1 {
  CH1 *start,  //< Start of the array.
      *stop;   //< Stop of the array.

  /* Initializes the UTF& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF1(CH1* start, SIW size);

  /* Initializes the UTF& from the given socket pointers.
  @param start The beginning of the socket.
  @param stop   The stop of the socket. */
  UTF1(CH1* start, CH1* stop);

  UTF1(const UTF1& other);

  /* Sets the start to the new_start.
  @return *this. */
  /*inline*/ UTF1& Set(CH1* new_start);

  /* Prints the given item. */
  /*inline*/ UTF1& Print(CH1 item);
  /*inline*/ UTF1& Print(CH2 item);
  /*inline*/ UTF1& Print(CH4 item);
  /*inline*/ UTF1& Print(const CH1* item);
  /*inline*/ UTF1& Print(const CH2* item);
  /*inline*/ UTF1& Print(const CH4* item);
  /*inline*/ UTF1& Print(SI4 item);
  /*inline*/ UTF1& Print(UI4 item);
  /*inline*/ UTF1& Print(SI8 item);
  /*inline*/ UTF1& Print(UI8 item);

  /*inline*/ UTF1& Print(::_::Hex item);

  /*inline*/ UTF1& Print(Right1 item);
  /*inline*/ UTF1& Print(Center1 item);
  /*inline*/ UTF1& Print(Linef1 item);
  /*inline*/ UTF1& Print(Headingf1 item);
  /*inline*/ UTF1& Print(Chars1 chars);

  /* Prints the given item as hex. */
  /*inline*/ UTF1& Hex(SI1 item);
  /*inline*/ UTF1& Hex(UI1 item);
  /*inline*/ UTF1& Hex(SI2 item);
  /*inline*/ UTF1& Hex(UI2 item);
  /*inline*/ UTF1& Hex(SI4 item);
  /*inline*/ UTF1& Hex(UI4 item);
  /*inline*/ UTF1& Hex(SI8 item);
  /*inline*/ UTF1& Hex(UI8 item);
  /*inline*/ UTF1& Hex(const void* pointer);

  /* Prints the given item as binary. */
  /*inline*/ UTF1& Binary(SI1 item);
  /*inline*/ UTF1& Binary(UI1 item);
  /*inline*/ UTF1& Binary(SI2 item);
  /*inline*/ UTF1& Binary(UI2 item);
  /*inline*/ UTF1& Binary(SI4 item);
  /*inline*/ UTF1& Binary(UI4 item);
  /*inline*/ UTF1& Binary(SI8 item);
  /*inline*/ UTF1& Binary(UI8 item);
  /*inline*/ UTF1& Binary(const void* pointer);

#if USING_FP4 == YES
  /*inline*/ UTF1& Print(FP4 item);
  /*inline*/ UTF1& Hex(FP4 item);
  /*inline*/ UTF1& Binary(FP4 item);
#endif
#if USING_FP8 == YES
  /*inline*/ UTF1& Print(FP8 item);
  /*inline*/ UTF1& Hex(FP8 item);
  /*inline*/ UTF1& Binary(FP8 item);
#endif
};

#if USING_STR == UTF8
using CToken = Token1;
using CRight = Right1;
using CCenter = Center1;
using CColumns = Linef1;
using CRows = Headingf1;
#endif

}  // namespace _

SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::UTF1& o);

SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, CH1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, const CH1* item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, UI1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, SI2 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, UI2 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, SI4 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, UI4 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, SI8 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, UI8 item);
#if USING_FP4 == YES
SDK ::_::UTF1& operator<<(::_::UTF1& utf, FP4 item);
#endif
#if USING_FP8 == YES
SDK ::_::UTF1& operator<<(::_::UTF1& utf, FP8 item);
#endif
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Hex item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Center1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Right1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Linef1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Linef1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Char1 item);
SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf, ::_::Chars1 item);
// SDK /*inline*/ ::_::UTF1& operator<<(::_::UTF1& utf,
//                                 const ::_::Wildcard& type_value);
#endif
#endif
