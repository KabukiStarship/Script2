/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \c_valuef.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#ifndef SCRIPT2_C_VALUEF
#define SCRIPT2_C_VALUEF 1

#include "c_avalue.h"

namespace _ {

/* Utility class for printing numbers. */
struct LIB_MEMBER Valuef {
  SIW count;    //< Width of the item in bytes or columns.
  AValue item;  //< The type and value.

  /* Constrcts a Nil type with an indeterminite value. */
  // Valuef(); //< This is glitching for some weird reason.

  /* Constructs a Valuef from the given item. */
  Valuef(const void* item, SIW count);
  Valuef(void* item, SIW count);
#if USING_UTF8 == YES
  Valuef(CH1 item, SIW count);
  Valuef(const CH1* item, SIW count);
#endif
#if USING_UTF16 == YES
  Valuef(CH2 item, SIW count);
  Valuef(const CH2* item, SIW count);
#endif
#if USING_UTF32 == YES
  Valuef(CH4 item, SIW count);
  Valuef(const CH4* item, SIW count);
#endif
  Valuef(SI1 item, SIW count);
  Valuef(UI1 item, SIW count);
  Valuef(SI2 item, SIW count);
  Valuef(UI2 item, SIW count);
  Valuef(SI4 item, SIW count);
  Valuef(UI4 item, SIW count);
  Valuef(SI8 item, SIW count);
  Valuef(UI8 item, SIW count);
#if USING_FP4 == YES
  Valuef(FP4 item, SIW count);
#endif
#if USING_FP8 == YES
  Valuef(FP8 item, SIW count);
#endif

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  void* Value();

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  void* Ptr();
};

/* Utility class for printing a POD type in hex. */
struct Hexf {
  Valuef valuef;  //< Stores the ASCII Type, it's value, and the byte count.

  /* Stores the given item to the buffer and store the size. */
  Hexf(const void* item);
  Hexf(const void* item, SIW size);
  Hexf(SI1 item);
  Hexf(UI1 item);
  Hexf(SI2 item);
  Hexf(UI2 item);
  Hexf(SI4 item);
  Hexf(UI4 item);
  Hexf(SI8 item);
  Hexf(UI8 item);
#if USING_FP4 == YES
  Hexf(FP4 item);
#endif
#if USING_FP8 == YES
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
#if USING_FP4 == YES
  Binaryf(FP4 item);
#endif
#if USING_FP8 == YES
  Binaryf(FP8 item);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Centerf {
  Valuef valuef;  //< Pointer to a pointer to utf.

  /* Prints the item to the value. */
  Centerf(CH1 item, SIW count = kCOutColumnsCountDefault);
  Centerf(const CH1* start, SIW count = kCOutColumnsCountDefault);
#if USING_UTF16 == YES
  Centerf(CH2 item, SIW count = kCOutColumnsCountDefault);
  Centerf(const CH2* item, SIW count = kCOutColumnsCountDefault);
#endif
#if USING_UTF32 == YES
  Centerf(CH4 item, SIW count = kCOutColumnsCountDefault);
  Centerf(const CH4* item, SIW count = kCOutColumnsCountDefault);
#endif
  Centerf(SI4 item, SIW count = kCOutColumnsCountDefault);

  Centerf(UI4 item, SIW count = kCOutColumnsCountDefault);
  Centerf(SI8 item, SIW count = kCOutColumnsCountDefault);
  Centerf(UI8 item, SIW count = kCOutColumnsCountDefault);

#if USING_FP4 == YES
  Centerf(FP4 item, SIW count = kCOutColumnsCountDefault);
#endif
#if USING_FP8 == YES
  Centerf(FP8 item, SIW count = kCOutColumnsCountDefault);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Rightf {
  Valuef valuef;  //< Pointer to a pointer to utf.

  /* Prints the item to the value. */
  Rightf(CH1 item, SIW count = kCOutColumnsCountDefault);
  Rightf(const CH1* item, SIW count = kCOutColumnsCountDefault);
#if USING_UTF16 == YES
  Rightf(CH2 item, SIW count = kCOutColumnsCountDefault);
  Rightf(const CH2* item, SIW count = kCOutColumnsCountDefault);
#endif
#if USING_UTF32 == YES
  Rightf(CH4 item, SIW count = kCOutColumnsCountDefault);
  Rightf(const CH4* item, SIW count = kCOutColumnsCountDefault);
#endif
  Rightf(SI4 item, SIW count = kCOutColumnsCountDefault);
  Rightf(UI4 item, SIW count = kCOutColumnsCountDefault);
  Rightf(SI8 item, SIW count = kCOutColumnsCountDefault);
  Rightf(UI8 item, SIW count = kCOutColumnsCountDefault);

#if USING_FP4 == YES
  Rightf(FP4 item, SIW count = kCOutColumnsCountDefault);
#endif
#if USING_FP8 == YES
  Rightf(FP8 item, SIW count = kCOutColumnsCountDefault);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct LIB_MEMBER Linef {
  Valuef valuef;  //< Pointer to a pointer to utf.

  /* Constructors a horizontal line of the character. */
  Linef(CH1 item, SIW count = kCOutColumnsCountDefault);

  /* Constructors a horizontal line of the given string. */
  Linef(const CH1* start = nullptr, SIW count = kCOutColumnsCountDefault);
};

/* Utility class for printing a vertical line with operator<<. */
struct LIB_MEMBER Headingf {
  Valuef caption;
  const CH1 *style, *caption2, *caption3;

  /* Constructors a horizontal line of the given string. */
  Headingf(const CH1* caption, const CH1* style = nullptr,
           SIW count = kCOutColumnsCountDefault, const CH1* caption2 = nullptr,
           const CH1* caption3 = nullptr);
};

struct LIB_MEMBER Charsf {
  Valuef valuef;  //< The type, value and CH1, CH2, or CH4 count.

  /* Constructs the value from the delta between start and stop. */
  Charsf(const void* start, const void* stop);
  Charsf(const void* start, SIW count);
#if USING_UTF16
  Charsf(const CH2* start, const CH2* stop);
  Charsf(const CH2* start, SIW count);
#endif
#if USING_UTF32
  Charsf(const CH4* start, const CH4* stop);
  Charsf(const CH4* start, SIW count);
#endif
};

/* Utility class for indenting text with operator<<. */
struct LIB_MEMBER Indentf {
  SIW indent_count;  //< The number of spaces to indent.

  /* Constructs the value from the delta between start and stop. */
  Indentf(SIW indent_count);
};

}  // namespace _

#endif
