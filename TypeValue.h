/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /TypeValue.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_TYPEVALUE_DECL
#define SCRIPT2_TYPEVALUE_DECL
namespace _ {

/* Gets the string representations of the given ASCII POD Type 0-31. */
const CHA* STRTypes();

/* string that reads "true". */
LIB_MEMBER const CHA* STRTrue();

/* string that reads "false". */
LIB_MEMBER const CHA* STRFalse();

/* Utility class for printing an ASCII type. */
struct Typef {
  DTW type;     //< The item type.
  CHA* string;  //< The ASCII type string.
};

Typef TypefOf();

/* Stores a pointer to the ASCII data type and it's value. */
template<typename DT>
struct TTypeValue {
  DT type;      //< The ASCII data type word.
  void* value;  //< Pointer to the value of the type.
};

/* An ASCII Type-Value tuple.
An TypeValue can only work with up to two CPU ALU words because when a CPU
multiplies two integers together the result is two ALU-sized words and thus the
CPU can only address 2 words at a time. For types that are larger that two ALU
words wide the word_ stores a pointer to that type in memory and a struct will
be needed to work with the type. */
class LIB_MEMBER TypeValue {
  DTW type_;    //< ASCII Data type.
  IUW word_,    //< First data word.
      word_2_;  //< Second data word.

 public:
  /* Stores a NIL type with indeterminite word_. */
  TypeValue();

  /* Stores the item to the word_ and the ASCII type of the item. */
  explicit TypeValue(void* item);
  explicit TypeValue(const void* item);
#if USING_UTF8 == YES_0
  explicit TypeValue(CHA item);
  explicit TypeValue(const CHA* item);
#endif
#if USING_UTF16 == YES_0
  explicit TypeValue(CHB item);
  explicit TypeValue(const CHB* item);
#endif
#if USING_UTF32 == YES_0
  explicit TypeValue(CHC item);
  explicit TypeValue(const CHC* item);
#endif
  explicit TypeValue(ISA item);
  explicit TypeValue(IUA item);
  explicit TypeValue(ISB item);
  explicit TypeValue(IUB item);
  explicit TypeValue(ISC item);
  explicit TypeValue(IUC item);
  explicit TypeValue(ISD item);
  explicit TypeValue(IUD item);
#if USING_FPC == YES_0
  explicit TypeValue(FPC item);
#endif
#if USING_FPD == YES_0
  explicit TypeValue(FPD item);
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
  CHA* ToSTA();
  CHB* ToSTB();
  CHC* ToSTC();
  IUA ToIUA();
  IUB ToIUB();
  IUN ToIUN();
  IUC ToIUC();
  IUD ToUID();

  /* Gets the first word of the word_. */
  IUW Word();

  /* Gets the second word of the value if the type is two words wide. */
  IUW Word2();

  /* Sets the word to the value. */
  void SetWord(IUW value);

  /* Sets the second word to the value. */
  void SetWord2(IUW value);

  /*Sets the type_ to cNIL with an indeterminite value. */
  void SetNIL();

  /*Sets the type_ to cNIL with an indeterminite value. */
  void SetNIL(IUW value);

  /*Sets the word_ to the given item and updates the type. */
#if USING_UTF8 == YES_0
  void Set(CHA item);
  void Set(const CHA* item);
#endif
#if USING_UTF16 == YES_0
  void Set(CHB item);
  void Set(const CHB* item);
#endif
#if USING_UTF32 == YES_0
  void Set(const CHC* item);
  void Set(CHC item);
#endif
  void Set(ISA item);
  void Set(IUA item);
  void Set(ISB item);
  void Set(IUB item);
  void Set(BOL item);
  void Set(ISC item);
  void Set(IUC item);
  void Set(ISD item);
  void Set(IUD item);
#if USING_FPC == YES_0
  void Set(FPC item);
#endif
#if USING_FPD == YES_0
  void Set(FPD item);
#endif
};

/* Utility class for printing the size of ASCII TypeValues.
@see CSizef */
struct Sizef {
  ISW size;  //< The item who's size this is.
};

}  //< namespace _

#endif
