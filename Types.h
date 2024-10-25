/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Types.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_TYPES_DECL
#define SCRIPT2_TYPES_DECL
namespace _ {

// Packs the given ASCII Type bitfield values into a DTB.
DTB ATypePack(DTB pod, DTB vt);
DTB ATypePack(DTB pod, DTB vt, DTB sw);
DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt);
DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt, DTB mod);

// Returns true if the given type is CHA, CHB, or CHC.
BOL ATypeIsCH(DTB type);

// Returns the size of the given type in bytes.
ISA ATypeSizeOfPOD(DTB type);

/* Returns the size of the given type in bytes.
@return the size bytes of the value. */
ISW ATypeSizeBytes(const void* value, DTB type);
ISW ATypeSizeBytes(const void* value_base, ISA bytes, DTB type);

// Returns the end (byte after last byte) of the given type-value.
void* ATypeValueEnd(void* value, DTB type);

// Returns an array of the customizable POD type sizes.
const ISA* ATypeCustomSize();

// Returns an array of the user-defined type alignment masks.
const ISA* ATypeCustomAlignMask();

// Returns the custom time alignment mask for the given type.
ISA ATypeCustomAlignMask(DTA type);

/* Stores a pointer to the ASCII data type and it's value. */
struct ATypeValue {
  DTW   type;         //< ASCII data type word.
  const void* value;  //< Pointer to the value of the type.
};

// Gets the Unicode format: 0=UTF-8, 1=UTF-16, 2=UTF-32.
inline ISA ATypeTextFormat(DTW type);

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

}  //< namespace _

#endif
