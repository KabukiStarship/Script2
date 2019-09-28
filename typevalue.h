/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /typevalue.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#ifndef SCRIPT2_ASCIIDATA_C
#define SCRIPT2_ASCIIDATA_C

namespace _ {

/* Gets the string representations of the given ASCII POD Type 0-31. */
const CH1* STRTypes();

/* string that reads "true". */
LIB_MEMBER const CH1* STRTrue();

/* string that reads "false". */
LIB_MEMBER const CH1* STRFalse();

/* An ASCII Type-Value tuple.
An TypeValue can only work with up to two CPU ALU words because when a CPU
multiplies two integers together the result is two ALU-sized words and thus the
CPU can only address 2 words at a time. For types that are larger that two ALU
words wide the word_ stores a pointer to that type in memory and a struct will
be needed to work with the type. */
class LIB_MEMBER TypeValue {
  DTW type_;    //< ASCII Data type.
  UIW word_,    //< First data word.
      word_2_;  //< Second data word.

 public:
  /* Stores a NIL type with indeterminite word_. */
  TypeValue();

  /* Stores the item to the word_ and the ASCII type of the item. */
  explicit TypeValue(void* item);
  explicit TypeValue(const void* item);
#if USING_UTF8 == YES_0
  explicit TypeValue(CH1 item);
  explicit TypeValue(const CH1* item);
#endif
#if USING_UTF16 == YES_0
  explicit TypeValue(CH2 item);
  explicit TypeValue(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  explicit TypeValue(CH4 item);
  explicit TypeValue(const CH4* item);
#endif
  explicit TypeValue(SI1 item);
  explicit TypeValue(UI1 item);
  explicit TypeValue(SI2 item);
  explicit TypeValue(UI2 item);
  explicit TypeValue(SI4 item);
  explicit TypeValue(UI4 item);
  explicit TypeValue(SI8 item);
  explicit TypeValue(UI8 item);
#if USING_FP4 == YES_0
  explicit TypeValue(FP4 item);
#endif
#if USING_FP8 == YES_0
  explicit TypeValue(FP8 item);
#endif
  TypeValue(const void* item, DTW type);

  /* Gets the type_. */
  DTW Type();

  /* Gets the Unicode string format if any. */
  DTW UnicodeFormat();

  /* Gets a pointer to the word_. */
  void* WordPTR();

  /* Gets the value as the return type. */
  void* ToPTR();
  CH1* ToST1();
  CH2* ToST2();
  CH4* ToST3();
  UI1 ToUI1();
  UI2 ToUI2();
  UIN ToUIN();
  UI4 ToUI4();
  UI8 ToUI8();

  /* Gets the first word of the word_. */
  UIW Word();

  /* Gets the second word of the value if the type is two words wide. */
  UIW Word2();

  /* Sets the word to the value. */
  void SetWord(UIW value);

  /* Sets the second word to the value. */
  void SetWord2(UIW value);

  /*Sets the type_ to kNIL with an indeterminite value. */
  void SetNIL();

  /*Sets the type_ to kNIL with an indeterminite value. */
  void SetNIL(UIW value);

  /*Sets the word_ to the given item and updates the type. */
#if USING_UTF8 == YES_0
  void Set(CH1 item);
  void Set(const CH1* item);
#endif
#if USING_UTF16 == YES_0
  void Set(CH2 item);
  void Set(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  void Set(const CH4* item);
  void Set(CH4 item);
#endif
  void Set(SI1 item);
  void Set(UI1 item);
  void Set(SI2 item);
  void Set(UI2 item);
  void Set(BOL item);
  void Set(SI4 item);
  void Set(UI4 item);
  void Set(SI8 item);
  void Set(UI8 item);
#if USING_FP4 == YES_0
  void Set(FP4 item);
#endif
#if USING_FP8 == YES_0
  void Set(FP8 item);
#endif
};

struct AType {
  DTW type;  //< The ASCII Data Type.

  /* Stores teh type. */
  AType(DTW type);
};

}  // namespace _

#endif
