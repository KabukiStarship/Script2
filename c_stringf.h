/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \c_stringf.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef SCRIPT2_STRINGF_H
#define SCRIPT2_STRINGF_H 1

#include "c_avalue.h"

namespace _ {

/* Utility class for printing numbers. */
struct LIB_MEMBER Valuef {
  SIW count;    //< Width of the item in bytes or columns.
  AValue item;  //< The type and value.

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

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  LIB_INLINE void* Value();

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  LIB_INLINE void* Ptr();

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  LIB_INLINE UIW Word();
};

/* Utility class for printing a POD type in hex. */
struct Hexf {
  Valuef valuef;  //< Stores the ASCII Type, it's value, and the byte count.

  Hexf(const void* item, SIW size);
  /* Stores the given item to the buffer and stores the size. */
  Hexf(const void* item);
  Hexf(SI1 item);
  Hexf(UI1 item);
  Hexf(SI2 item);
  Hexf(UI2 item);
  Hexf(SI4 item);
  Hexf(UI4 item);
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
  Valuef valuef;  //< Stores the ASCII Type, it's value, and the byte count.

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
  Valuef valuef;  //< The type, value and CH1, CH2, or CH4 count.

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
  enum { kLengthMax = 31 };

 private:
  const void* string_;          // Pointer to a string or the buffer_.
  SIW type_,                    //< The ASCII String Type, 1-3, of the string_.
      count_;                   //< The count.
  CH1 buffer_[kLengthMax + 1];  //< Strand buffer for the token.

 public:
  /* Default constructor sets the count but doesn't write a nil-term char to the
  buffer. */
  Stringf();

  /* Sets the string_ to the given pointer and stores the count. */
  Stringf(const CH1* item);
#if USING_UTF16 == YES_0
  Stringf(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  Stringf(const CH4* item);
#endif

  /* Prints the item to the buffer_, stores the count, and sets the string_ to
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

  /* Sets the string_ to the given pointer and stores the count. */
  Stringf(const CH1* item, SIW count);
#if USING_UTF16 == YES_0
  Stringf(const CH2* item, SIW count);
#endif
#if USING_UTF32 == YES_0
  Stringf(const CH4* item, SIW count);
#endif

  /* Prints the item to the buffer_, stores the count, and sets the string_ to
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

  /* Gets the string_. */
  LIB_INLINE const CH1* ST1();

  /* Gets the string_. */
  LIB_INLINE const CH2* ST2();

  /* Gets the string_. */
  LIB_INLINE const CH4* ST3();

  /* Gets the type_. */
  LIB_INLINE SIW Type() const;

  /* Gets the count_. */
  LIB_INLINE SIW Count() const;

  /* Saves the pointer to the string_. */
  LIB_INLINE void Print(const CH1* item);
#if USING_UTF16 == YES_0
  LIB_INLINE void Print(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  LIB_INLINE void Print(const CH4* item);
#endif

  /* Prints the given item to the buffer_. */
  LIB_INLINE void Print(CH1 item);
#if USING_UTF16 == YES_0
  LIB_INLINE void Print(CH2 item);
#endif
#if USING_UTF32 == YES_0
  LIB_INLINE void Print(CH4 item);
#endif
  LIB_INLINE void Print(SI4 item);
  LIB_INLINE void Print(UI4 item);
  LIB_INLINE void Print(SI8 item);
  LIB_INLINE void Print(UI8 item);
#if USING_FP4 == YES_0
  LIB_INLINE void Print(FP4 item);
#endif
#if USING_FP8 == YES_0
  LIB_INLINE void Print(FP8 item);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Centerf {
  Stringf stringf;  //< Pointer to a pointer to utf.

  /* Prints the item to the value. */
  Centerf(CH1 item, SIW count = kCOutColumnCountDefault);
  Centerf(const CH1* start, SIW count = kCOutColumnCountDefault);
#if USING_UTF16 == YES_0
  Centerf(CH2 item, SIW count = kCOutColumnCountDefault);
  Centerf(const CH2* item, SIW count = kCOutColumnCountDefault);
#endif
#if USING_UTF32 == YES_0
  Centerf(CH4 item, SIW count = kCOutColumnCountDefault);
  Centerf(const CH4* item, SIW count = kCOutColumnCountDefault);
#endif
  Centerf(SI4 item, SIW count = kCOutColumnCountDefault);

  Centerf(UI4 item, SIW count = kCOutColumnCountDefault);
  Centerf(SI8 item, SIW count = kCOutColumnCountDefault);
  Centerf(UI8 item, SIW count = kCOutColumnCountDefault);

#if USING_FP4 == YES_0
  Centerf(FP4 item, SIW count = kCOutColumnCountDefault);
#endif
#if USING_FP8 == YES_0
  Centerf(FP8 item, SIW count = kCOutColumnCountDefault);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Rightf {
  Stringf stringf;  //< Pointer to a pointer to utf.

  /* Prints the item to the value. */
  Rightf(CH1 item, SIW count = kCOutColumnCountDefault);
  Rightf(const CH1* item, SIW count = kCOutColumnCountDefault);
#if USING_UTF16 == YES_0
  Rightf(CH2 item, SIW count = kCOutColumnCountDefault);
  Rightf(const CH2* item, SIW count = kCOutColumnCountDefault);
#endif
#if USING_UTF32 == YES_0
  Rightf(CH4 item, SIW count = kCOutColumnCountDefault);
  Rightf(const CH4* item, SIW count = kCOutColumnCountDefault);
#endif
  Rightf(SI4 item, SIW count = kCOutColumnCountDefault);
  Rightf(UI4 item, SIW count = kCOutColumnCountDefault);
  Rightf(SI8 item, SIW count = kCOutColumnCountDefault);
  Rightf(UI8 item, SIW count = kCOutColumnCountDefault);

#if USING_FP4 == YES_0
  Rightf(FP4 item, SIW count = kCOutColumnCountDefault);
#endif
#if USING_FP8 == YES_0
  Rightf(FP8 item, SIW count = kCOutColumnCountDefault);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct LIB_MEMBER Linef {
  Valuef valuef;  //< Pointer to a pointer to utf.

  /* Constructors a horizontal line of the character. */
  Linef(CH1 item, SIW count = kCOutColumnCountDefault);

  /* Constructors a horizontal line of the given string. */
  Linef(const CH1* start = nullptr, SIW count = kCOutColumnCountDefault);
};

/* Utility class for printing a Heading with formatting with operator<<. */
struct LIB_MEMBER Headingf {
  Stringf caption;
  const CH1 *style, *caption2, *caption3;

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CH1* caption, const CH1* style = nullptr,
           SIW count = kCOutColumnCountDefault, const CH1* caption2 = nullptr,
           const CH1* caption3 = nullptr);
};

/* Utility class for indenting text with operator<<. */
struct LIB_MEMBER Indentf {
  SIW indent_count;  //< Number of spaces to indent.

  /* Constructs the value from the delta between start and stop. */
  Indentf(SIW indent_count);
};

}  // namespace _

#endif
