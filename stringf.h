/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \c_string.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_StringF_CODLESS_HEADER
#define SCRIPT2_StringF_CODLESS_HEADER 1

#include "typevalue.h"

namespace _ {

/* Gets the header to print for PrintChars(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintCharsHeader();

/* Gets the header to print for PrintChars(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintCharsBorder();

/* Gets the header to print for PrintHex(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintHexHeader();

/* Gets the header to print for PrintHex(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintHexBorder();

/* Converts a UI1 into a two-UI1 hex representation.
@return Returns -1 if c is not a hex UI1. */
LIB_MEMBER SI4 HexToByte(UI2 hex);

/* Attempts to scan a UTF-32 CH1 from the given UTF-8 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
LIB_MEMBER const CH1* SScan(const CH1* string, CH4& character);

#if USING_UTF16 == YES_0
/* Prints a UTF-32 character to the string terminated at the stop.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param string    The start of the string.
@param stop      The last CH1 in the string buffer.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
LIB_MEMBER CH2* SPrint(CH2* string, CH2* stop, CH4 character);

/* Attempts to scan a UTF-32 CH1 from the given UTF-16 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
LIB_MEMBER const CH2* SScan(const CH2* string, CH4& character);
#endif

#if USING_UTF32 == YES_0
/* Prints a character to the string.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param stop The last character in the string buffer. */
LIB_MEMBER CH1* SPrint(CH1* string, CH1* stop, CH2 character);

/* Prints a Unicode character to the given string.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param stop   The last Char in the socket. */
LIB_MEMBER CH1* SPrint(CH1* string, CH1* stop, CH4 character);
#endif

/* Utility class for printing numbers. */
struct LIB_MEMBER Valuef {
  SIW count;        //< Width of the item in bytes or columns.
  TypeValue value;  //< The type and value.

  /* Constrcts a NIL item. */
  Valuef();

  /* Constructs a Valuef from the given item. */
  Valuef(const void* item, SIW count = 0);
  Valuef(void* item, SIW count = 0);
#if USING_UTF8 == YES_0
  Valuef(CH1 item, SIW count = 0);
  Valuef(const CH1* item, SIW count = 0);
#endif
#if USING_UTF16 == YES_0
  Valuef(CH2 item, SIW count = 0);
  Valuef(const CH2* item, SIW count = 0);
#endif
#if USING_UTF32 == YES_0
  Valuef(CH4 item, SIW count = 0);
  Valuef(const CH4* item, SIW count = 0);
#endif
  Valuef(SI1 item, SIW count = 0);
  Valuef(UI1 item, SIW count = 0);
  Valuef(SI2 item, SIW count = 0);
  Valuef(UI2 item, SIW count = 0);
  Valuef(SI4 item, SIW count = 0);
  Valuef(UI4 item, SIW count = 0);
  Valuef(SI8 item, SIW count = 0);
  Valuef(UI8 item, SIW count = 0);
#if USING_FP4 == YES_0
  Valuef(FP4 item, SIW count = 0);
#endif
#if USING_FP8 == YES_0
  Valuef(FP8 item, SIW count = 0);
#endif

  /* Gets the value.Type(). */
  SIW Type();

  /* Gets the count. */
  SIW Count();

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  void* Value();

  /* Gets the value::word_ as the specified type. */
  void* ToPtr();
  CH1* ToST1();
  CH2* ToST2();
  CH4* ToST3();
  UIW ToWord();
};

/* Utility class for printing a POD type in hex. */
struct Hexf {
  Valuef element;  //< Stores the ASCII Type, it's value, and the byte count.

  Hexf(const void* item, SIW size);
  /* Stores the given item to the buffer and stores the size. */
  Hexf(const void* item);
  Hexf(SI1 item);
  Hexf(UI1 item);
  Hexf(CH1 item);
  Hexf(SI2 item);
  Hexf(UI2 item);
  Hexf(CH2 item);
  Hexf(SI4 item);
  Hexf(UI4 item);
  Hexf(CH4 item);
  Hexf(SI8 item);
  Hexf(UI8 item);
#if USING_FP4 == YES_0
  Hexf(FP4 item);
#endif
#if USING_FP8 == YES_0
  Hexf(FP8 item);
#endif
};

/* Utility class for printing a POD type in binary. */
struct LIB_MEMBER Binaryf {
  Valuef element;  //< Stores the ASCII Type, it's value, and the byte count.

  /* Stores the given item to the buffer and store the size. */
  Binaryf(const void* item);
  Binaryf(const void* item, SIW size);
  Binaryf(SI1 item);
  Binaryf(UI1 item);
  Binaryf(SI2 item);
  Binaryf(UI2 item);
  Binaryf(SI4 item);
  Binaryf(UI4 item);
  Binaryf(SI8 item);
  Binaryf(UI8 item);
#if USING_FP4 == YES_0
  Binaryf(FP4 item);
#endif
#if USING_FP8 == YES_0
  Binaryf(FP8 item);
#endif
};

/* Utility class for printing blocks of characters to the console with
operator<<. */
struct LIB_MEMBER Charsf {
  Valuef element;  //< The type, value and CH1, CH2, or CH4 count.

  /* Constructs the value from the delta between start and stop. */
  Charsf(const void* start, const void* stop);
  Charsf(const void* start, SIW count);
#if USING_UTF16 == YES_0
  Charsf(const CH2* start, const CH2* stop);
  Charsf(const CH2* start, SIW count);
#endif
#if USING_UTF32 == YES_0
  Charsf(const CH4* start, const CH4* stop);
  Charsf(const CH4* start, SIW count);
#endif
};

/* Utility class for formatting text with operator<<, most commonly right and
center aligned. */
class LIB_MEMBER Stringf {
 public:
  enum {
    // Max length of the buffer in ALU words.
    kBufferWordCount =
        (sizeof(void*) == 2)
            ? 5
            : (sizeof(void*) == 4) ? 6 : (sizeof(void*) == 8) ? 5 : 1,
    // Max length of a string in characters.
    kLengthMax = kBufferWordCount * sizeof(void*) - 1,
  };

 private:
  const void* String_;  // Pointer to a string or the buffer_.
  SIW count_;           //< The count.
  DTW type_;            //< The ASCII string Type, 1-3, of the String_.
  UIW buffer_[kBufferWordCount];  //< Strand buffer for the token.

 public:
  /* Default constructor sets the count but doesn't write a nil-term char
  to the buffer. */
  Stringf();

  /* Sets the String_ to the given pointer and stores the count. */
  Stringf(const CH1* item);
#if USING_UTF16 == YES_0
  Stringf(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  Stringf(const CH4* item);
#endif

  /* Prints the item to the buffer_, stores the count, and sets the String_ to
  the buffer_. */
  Stringf(CH1 item);
  Stringf(CH2 item);
  Stringf(CH4 item);
  Stringf(SI4 item);
  Stringf(UI4 item);
  Stringf(SI8 item);
  Stringf(UI8 item);
#if USING_FP4 == YES_0
  Stringf(FP4 item);
#endif
#if USING_FP8 == YES_0
  Stringf(FP8 item);
#endif

  /* Sets the String_ to the given pointer and stores the count. */
  Stringf(const CH1* item, SIW count);
#if USING_UTF16 == YES_0
  Stringf(const CH2* item, SIW count);
#endif
#if USING_UTF32 == YES_0
  Stringf(const CH4* item, SIW count);
#endif

  /* Prints the item to the buffer_, stores the count, and sets the String_ to
  the buffer_. */
  Stringf(CH1 item, SIW count);
  Stringf(CH2 item, SIW count);
  Stringf(CH4 item, SIW count);
  Stringf(SI4 item, SIW count);
  Stringf(UI4 item, SIW count);
  Stringf(SI8 item, SIW count);
  Stringf(UI8 item, SIW count);
#if USING_FP4 == YES_0
  Stringf(FP4 item, SIW count);
#endif
#if USING_FP8 == YES_0
  Stringf(FP8 item, SIW count);
#endif
  Stringf(TypeValue item, SIW count = kConsoleWidth);

  UIW Word();

  /* Gets a void pointer to the value_. */
  void* Value();

  /* Gets the pointer contained in value_[0]. */
  void* Ptr();

  /* Gets the String_. */
  const CH1* ST1();
  const CH2* ST2();
  const CH4* ST3();

  /* Gets the type_. */
  SIW Type() const;

  /* Gets the count_. */
  SIW Count() const;

  /* Saves the pointer to the String_. */
  void Print(const CH1* item);
#if USING_UTF16 == YES_0
  void Print(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  void Print(const CH4* item);
#endif

  /* Prints the given item to the buffer_. */
  void Print(CH1 item);
#if USING_UTF16 == YES_0
  void Print(CH2 item);
#endif
#if USING_UTF32 == YES_0
  void Print(CH4 item);
#endif
  void Print(SI4 item);
  void Print(UI4 item);
  void Print(SI8 item);
  void Print(UI8 item);
#if USING_FP4 == YES_0
  void Print(FP4 item);
#endif
#if USING_FP8 == YES_0
  void Print(FP8 item);
#endif

  /* Prints a timestamp to the buffer_. */
  void PrintTM4(TM4 item);
  void PrintTME(TM4 item, UI4 subsecond_tick);
  void PrintTM8(TM8 item);

  void Print(TypeValue item);

  /* Stores the item to the first word of the buffer and the negative of the
  count. */
  void Hex(CH1 item, SIW count = 80);
#if USING_UTF16 == YES_0
  void Hex(CH2 item, SIW count = 80);
#endif
#if USING_UTF32 == YES_0
  void Hex(CH4 item, SIW count = 80);
#endif
  void Hex(SI1 item, SIW count = 80);
  void Hex(UI1 item, SIW count = 80);
  void Hex(SI2 item, SIW count = 80);
  void Hex(UI2 item, SIW count = 80);
  void Hex(SI4 item, SIW count = 80);
  void Hex(UI4 item, SIW count = 80);
  void Hex(SI8 item, SIW count = 80);
  void Hex(UI8 item, SIW count = 80);
#if USING_FP4 == YES_0
  void Hex(FP4 item, SIW count = 80);
#endif
#if USING_FP8 == YES_0
  void Hex(FP8 item, SIW count = 80);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Centerf {
  Stringf element;  //< Pointer to a pointer to utf.

  /* Does nothing. */
  Centerf();

  /* Prints the item to the value. */
  Centerf(CH1 item, SIW count = kConsoleWidth);
  Centerf(const CH1* start, SIW count = kConsoleWidth);
#if USING_UTF16 == YES_0
  Centerf(CH2 item, SIW count = kConsoleWidth);
  Centerf(const CH2* item, SIW count = kConsoleWidth);
#endif
#if USING_UTF32 == YES_0
  Centerf(CH4 item, SIW count = kConsoleWidth);
  Centerf(const CH4* item, SIW count = kConsoleWidth);
#endif
  Centerf(SI4 item, SIW count = kConsoleWidth);

  Centerf(UI4 item, SIW count = kConsoleWidth);
  Centerf(SI8 item, SIW count = kConsoleWidth);
  Centerf(UI8 item, SIW count = kConsoleWidth);

#if USING_FP4 == YES_0
  Centerf(FP4 item, SIW count = kConsoleWidth);
#endif
#if USING_FP8 == YES_0
  Centerf(FP8 item, SIW count = kConsoleWidth);
#endif

  /* Stores the item to the first word of the buffer and the negative of the
  count. */
  Centerf& Hex(CH1 item, SIW count = 80);
#if USING_UTF16 == YES_0
  Centerf& Hex(CH2 item, SIW count = 80);
#endif
#if USING_UTF32 == YES_0
  Centerf& Hex(CH4 item, SIW count = 80);
#endif
  Centerf& Hex(SI1 item, SIW count = 80);
  Centerf& Hex(UI1 item, SIW count = 80);
  Centerf& Hex(SI2 item, SIW count = 80);
  Centerf& Hex(UI2 item, SIW count = 80);
  Centerf& Hex(SI4 item, SIW count = 80);
  Centerf& Hex(UI4 item, SIW count = 80);
  Centerf& Hex(SI8 item, SIW count = 80);
  Centerf& Hex(UI8 item, SIW count = 80);
#if USING_FP4 == YES_0
  Centerf& Hex(FP4 item, SIW count = 80);
#endif
#if USING_FP8 == YES_0
  Centerf& Hex(FP8 item, SIW count = 80);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Rightf {
  Stringf element;  //< Pointer to a pointer to utf.

  /* Does nothing. */
  Rightf();

  /* Prints the item to the value. */
  Rightf(CH1 item, SIW count = kConsoleWidth);
  Rightf(const CH1* item, SIW count = kConsoleWidth);
#if USING_UTF16 == YES_0
  Rightf(CH2 item, SIW count = kConsoleWidth);
  Rightf(const CH2* item, SIW count = kConsoleWidth);
#endif
#if USING_UTF32 == YES_0
  Rightf(CH4 item, SIW count = kConsoleWidth);
  Rightf(const CH4* item, SIW count = kConsoleWidth);
#endif
  Rightf(SI4 item, SIW count = kConsoleWidth);
  Rightf(UI4 item, SIW count = kConsoleWidth);
  Rightf(SI8 item, SIW count = kConsoleWidth);
  Rightf(UI8 item, SIW count = kConsoleWidth);

#if USING_FP4 == YES_0
  Rightf(FP4 item, SIW count = kConsoleWidth);
#endif
#if USING_FP8 == YES_0
  Rightf(FP8 item, SIW count = kConsoleWidth);
#endif

  /* Stores the item to the first word of the buffer and the negative of the
  count. */
  Rightf& Hex(CH1 item, SIW count = 80);
#if USING_UTF16 == YES_0
  Rightf& Hex(CH2 item, SIW count = 80);
#endif
#if USING_UTF32 == YES_0
  Rightf& Hex(CH4 item, SIW count = 80);
#endif
  Rightf& Hex(SI1 item, SIW count = 80);
  Rightf& Hex(UI1 item, SIW count = 80);
  Rightf& Hex(SI2 item, SIW count = 80);
  Rightf& Hex(UI2 item, SIW count = 80);
  Rightf& Hex(SI4 item, SIW count = 80);
  Rightf& Hex(UI4 item, SIW count = 80);
  Rightf& Hex(SI8 item, SIW count = 80);
  Rightf& Hex(UI8 item, SIW count = 80);
#if USING_FP4 == YES_0
  Rightf& Hex(FP4 item, SIW count = 80);
#endif
#if USING_FP8 == YES_0
  Rightf& Hex(FP8 item, SIW count = 80);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct LIB_MEMBER Linef {
  Valuef element;  //< Pointer to a pointer to utf.

  /* Constructors a horizontal line of the character. */
  Linef(CH1 item, SIW count = kConsoleWidth);

  /* Constructors a horizontal line of the given string. */
  Linef(const CH1* start = nullptr, SIW count = kConsoleWidth);
};

/* Utility class for printing a Heading with formatting with operator<<. */
struct LIB_MEMBER Headingf {
  Stringf element;
  const CH1 *style, *caption2, *caption3;

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CH1* caption);

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CH1* caption, const CH1* caption2);

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CH1* caption, const CH1* caption2,
           const CH1* caption3 = nullptr, const CH1* style = nullptr,
           SIW count = kConsoleWidth);
};

/* Utility class for indenting text with operator<<. */
struct LIB_MEMBER Indentf {
  SIW indent_count;  //< Number of spaces to indent.

  /* Constructs the value from the delta between start and stop. */
  Indentf(SIW indent_count);
};

}  // namespace _

#endif
