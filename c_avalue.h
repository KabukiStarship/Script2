/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /c_avalue.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_ASCIIDATA_C
#define SCRIPT2_ASCIIDATA_C

namespace _ {

/* List of the 32 ASCII Data Types from the Script2 Specification.
@link ./spec/data/readme.md
@todo Wishlist item: Can we make a type that tells the AValue to delete dynamic
memory?
*/
typedef enum AsciiTypes {
  kNIL = 0,  //< 00. Nil/void type or a BigNum (BGN) of 1 to 2047 bytes wide.
  kST1,      //< 01. Nil-terminated string Type 1 (UTF-8).
  kST2,      //< 02. Nil-terminated string Type 2 (UTF-16).
  kST3,      //< 03. Nil-terminated string Type 3 (UTF-32).
  kSI1,      //< 04. 8-bit signed integer.
  kUI1,      //< 05. 8-bit unsigned integer.
  kCH1,      //< 06. 8-bit character.
  kCH2,      //< 07. 16-bit character.
  kSI2,      //< 08. 16-bit signed integer.
  kUI2,      //< 09. 16-bit unsigned integer.
  kFP2,      //< 10. 16-bit floating-point number.
  kBOL,      //< 11. Boolean value at least 16-bits wide.
  kCH4,      //< 12. 32-bit character.
  kSI4,      //< 13. 32-bit signed integer.
  kUI4,      //< 14. 32-bit unsigned integer.
  kFP4,      //< 15. 32-bit floating-point number.
  kTM4,      //< 16. 32-bit second since epoch timestamp.
  kTME,      //< 17. 64-bit sub-second timestamp with TM4 and an UI4 tick.
  kTM8,      //< 18. 64-bit second since epoch timestamp.
  kSI8,      //< 19. 64-bit signed integer.
  kUI8,      //< 20. 64-bit unsigned integer.
  kFP8,      //< 21. 64-bit floating-point number.
  kSIH,      //< 22. 128-bit (Hexadeca-byte) signed integer.
  kUIH,      //< 23. 128-bit (Hexadeca-byte) unsigned integer.
  kFPH,      //< 24. 128-bit (Hexadeca-byte) floating-point number.
  kSIV,      //< 25. Word-sized signed MSb-encoded varint.
  kUIV,      //< 26. Word-sized unsigned MSb-encoded varint.
  kPTC,      //< 27. Word-sized const pointer.
  kPTR,      //< 28. Word-sized pointer.
  kOPD,      //< 29. Word-sized pointer to an Operand object.
  kAJT,      //< 30. Two-pointer Automatic Object (Autoject).
  kVAL,      //< 31. An ASCII type-value tuple stored as 3 words.
} AsciiType;

enum {
  kRS1 = 97,  //< 97. A type-value tuple list with 16-bit signed size_bytes.
  kRS2 = 98,  //< 98. A type-value tuple list with 32-bit signed size_bytes.
  kRS4 = 99,  //< 99. A type-value tuple list with 64-bit signed size_bytes.
  kINV = 64,  //< The number of Ascii Data Type base types.
  kTypeBitCount = 5,      //< Bit
  kTypeCount = 32,        //< The starting index of invalid types.
  kTypePODMask = 32 - 1,  //< The starting index of invalid types.
};

enum {
  kTYP = 0,  //< 0. Class or POD type.
  kTY2 = 1,  //< 1. size_width of size_bytes is 16-bits wide.
  kTY4 = 2,  //< 2. size_width of size_bytes is 32-bits wide.
  kTY8 = 3,  //< 3. size_width of size_bytes is 64-bits wide.
};

enum {
  kPOD = 0,  //< A POD type.
  kARY = 1,  //< Array of POD types.
  kVEC = 2,  //< Vector of POD types.
  kMAT = 3,  //< Matrix of POD types.
};

/* Gets the string representations of the given ASCII Data Type 0-31. */
LIB_INLINE const CH1* STRTypes();

/* Gets one f the STRTypes. */
LIB_INLINE const CH1* STRType(DTW index);

/* Array of bytes of the sizes of POD types. */
LIB_INLINE const SI1* TypeBasicSizes();

/* Extracts the UTF type.
@return 0 if the type is not a stirng type or 1, 2, or 4 if it is. */
LIB_INLINE SI1 TypeTextFormat(DTW type);

/* Gets one of the */
LIB_INLINE SI1 TypeSizeOf(DTW index);

/* Gets the alignment mask for the given POD data type. */
LIB_INLINE SIW TypeAlignmentMask(SIW index);

/* Checks if the given type is valid.
@return False if the given type is an 8-bit kLST, kMAP, kBOK, or kDIC. */
LIB_INLINE BOL TypeIsSupported(DTW type);

/* Extracts the unicode format of the given type if is a text type. */
SI1 TypeTextFormat(DTW type);

/* Masks off the primary type. */
LIB_INLINE SI1 TypeBase(DTW value);

/* Returns true if the given type is an Array type. */
LIB_INLINE BOL TypeIsArray(DTW type);

LIB_INLINE SIN TypeSizeWidthCode(SIN type);

/* Maps the givn  */
LIB_INLINE DTW TypeMap(DTW core_type, DTW map_type);

/* Maps the givn  */
LIB_INLINE DTW TypeMap(DTW core_type, DTW map_type, DTW size_width);

/* An ASCII Type-Value tuple. */
class LIB_MEMBER AValue {
  DTW type_;      //< The ASCII Data type.
  UIW value_[2];  //< Two data words.

 public:
  /* Stores a NIL type with indeterminite value_. */
  AValue();

  /* Stores the item to the value_ and the ASCII type of the item. */
  explicit AValue(void* item);
  explicit AValue(const void* item);
#if USING_UTF8 == YES_0
  explicit AValue(CH1 item);
  explicit AValue(const CH1* item);
#endif
#if USING_UTF16 == YES_0
  explicit AValue(CH2 item);
  explicit AValue(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  explicit AValue(CH4 item);
  explicit AValue(const CH4* item);
#endif
  explicit AValue(SI1 item);
  explicit AValue(UI1 item);
  explicit AValue(SI2 item);
  explicit AValue(UI2 item);
  explicit AValue(SI4 item);
  explicit AValue(UI4 item);
  explicit AValue(SI8 item);
  explicit AValue(UI8 item);
#if USING_FP4 == YES_0
  explicit AValue(FP4 item);
#endif
#if USING_FP8 == YES_0
  explicit AValue(FP8 item);
#endif

  /* Stores the item to the value_ and the ASCII type. */
  AValue(UIW item, DTW type);

  /* Gets the type_. */
  DTW Type();

  /* Gets the type of */
  DTW UnicodeFormat();

  /* Gets a void pointer to the value_. */
  void* Value();

  /* Gets the pointer contained in value_[0]. */
  void* Ptr();
  CH1* ST1();
  CH2* ST2();
  CH4* ST3();

  /* Gets the first word of the value_. */
  UIW Word();

  /*Sets the type_ to kNIL with an indeterminite value. */
  LIB_INLINE void SetNIL();

  /*Sets the type_ to kNIL with an indeterminite value. */
  LIB_INLINE void SetNIL(UIW value);

  /*Sets the value_ to the given item and updates the type. */
#if USING_UTF8 == YES_0
  LIB_INLINE void Set(CH1 item);
  LIB_INLINE void Set(const CH1* item);
#endif
#if USING_UTF16 == YES_0
  LIB_INLINE void Set(CH2 item);
  LIB_INLINE void Set(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  LIB_INLINE void Set(const CH4* item);
  LIB_INLINE void Set(CH4 item);
#endif
  LIB_INLINE void Set(SI1 item);
  LIB_INLINE void Set(UI1 item);
  LIB_INLINE void Set(SI2 item);
  LIB_INLINE void Set(UI2 item);
  LIB_INLINE void Set(BOL item);
  LIB_INLINE void Set(SI4 item);
  LIB_INLINE void Set(UI4 item);
  LIB_INLINE void Set(SI8 item);
  LIB_INLINE void Set(UI8 item);
#if USING_FP4 == YES_0
  LIB_INLINE void Set(FP4 item);
#endif
#if USING_FP8 == YES_0
  LIB_INLINE void Set(FP8 item);
#endif
};

}  // namespace _

#endif
