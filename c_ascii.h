/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_ascii.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_SEAM_ROOM
#ifndef SCRIPT2_ASCIIDATA_C
#define SCRIPT2_ASCIIDATA_C

namespace _ {

/* List of the 32 ASCII Data Types.

# ASCII Data

Types are organized with types that are allowed in text B-Sequences first,
followed by objects which get created in text using Script Operations.

## Parsing Rules

ASCII Data Types are setup so they are easy to parse. In order to parse the data
we need a bit pattern that facilitates the transition from scanning one data
type to another.

### 16-bit ASCII Type Bit Pattern

|   b9:b8   |  b15:b10  |  b7:b6   | b5:b0 |
|:---------:|:---------:|:--------:|:-----:|
| Bit-depth | Map class | Map type | Class |
*/
typedef enum AsciiTypes {
  kNIL = 0,   //< 0.  kNIL/nil/void type.
  kSI1,       //< 1.  8-bit signed integer.
  kUI1,       //< 2.  8-bit unsigned integer.
  kCH1,       //< 3.  UTF-8 character (CH1), string (ST1), or token (TK1).
  kSI2,       //< 4.  16-bit signed integer.
  kUI2,       //< 5.  16-bit unsigned integer.
  kCH2,       //< 6.  UTF-16 character (CH2), string (ST2), or token (TK2).
  kFP2,       //< 7.  16-bit floating-point number.
  kBOL,       //< 8.  32-bit non-zero true boolean.
  kSI4,       //< 9.  32-bit signed integer.
  kUI4,       //< 10. 32-bit unsigned integer.
  kCH4,       //< 11. 32-bit character (CH2), string (ST2), or token (TK2).
  kFP4,       //< 12. 32-bit floating-point number.
  kSI8,       //< 16. 64-bit signed integer.
  kUI8,       //< 17. 64-bit unsigned integer.
  kFP8,       //< 18. 64-bit floating-point number.
  kSIH,       //< 19. 128-bit (Hexadeca-UI1) signed integer.
  kUIH,       //< 20. 128-bit (Hexadeca-UI1) unsigned integer.
  kFPH,       //< 21. 128-bit (Hexadeca-UI1) floating-point number.
  kTM4,       //< 13. 32-bit second since epoch timestamp.
  kTME,       //< 14. 64-bit sub-second timestamp with TM4 and an UI4 tick.
  kTM8,       //< 15. 64-bit second since epoch timestamp.
  kOB1,       //< 22. 8-bit ASCII Object
  kBNM,       //< 23. 1 to 64-byte Signed or Unsigned Integer.
  kTKN,       //< 24. An ASCII Strand without any Whitespace.
  kADR,       //< 25. An ASCII Strand Abstract Stack Address.
  kREC,       //< 26. An ASCII Strand-Wildcard tuple.
  kOBJ,       //< 27. ASCII object that begins with a signed integer type.
  kLST,       //< 28. Set or multiset of Type-Value tuples.
  kSLT,       //< 29. An interprocess ring-buffer.
  kBSQ,       //< 24. B-Sequence or address (ADR) based on MSb.
  kEXP,       //< 31. Script^2 Expression.
  kINV,       //< 32. Invalid type.
  kLM1,       //< 33. An associative array of strings with SI4 size_bytes.
  kLM2,       //< 34. An associative array of strings with SI4 size_bytes.
  kLM4,       //< 35. An associative array of strings with SI4 size_bytes.
  kPT2 = 54,  //< 54. 16-bit pointer. |
  kPC2 = 55,  //< 56. 16-bit const pointer. |
  kPT4 = 56,  //< 57. 32-bit pointer. |
  kPC4 = 57,  //< 58. 32-bit const pointer. |
  kPT8 = 58,  //< 59. 64-bit pointer. |
  kPC8 = 59,  //< 59. 64-bit const pointer. |
  kOA2 = 60,  //< 60. A 16-bit RamFactory and pointer to an object.
  kOA4 = 61,  //< 61. A 32-bit RamFactory and pointer to an object.
  kOA8 = 62,  //< 62. A 64-bit RamFactory and pointer to an object.
  kWLD = 63,  //< 63. A one-byte-type-value tuple.
} AsciiType;

enum {
  kAsciiPODCount = 48

};

enum {
  kCOP = 0,  //< 0. Class or POD type.
  kOB2 = 1,  //< 1. size_width of size_bytes is 16-bits wide.
  kOB4 = 2,  //< 2. size_width of size_bytes is 32-bits wide.
  kOB8 = 3,  //< 3. size_width of size_bytes is 64-bits wide.
};

enum {
  kARY = 0,  //< Array of POD types.
  kVEC = 1,  //< Vector of POD types.
  kMAT = 2,  //< Matrix of POD types.
  kMAP = 3,  //< Map of one of the types to another.
};
}  // namespace _

#if SEAM >= SCRIPT2_SEAM_UTF
namespace _ {

/* Gets the string representations of the given ASCII Data Type 0-31. */
inline const CH1* STRType();

/* Array of bytes of the sizes of POD types. */
inline const SI1* TypePODSizes();

/* Gets one of the */
inline SI1 TypePODSize(SIN index);

/* Gets a string representation of the given ASCII Data Type 0-31. */
inline const CH1* STRType(SI4 index);

/* Checks if the given type is valid.
@return False if the given type is an 8-bit kLST, kMAP, kBOK, or kDIC. */
inline BOL TypeIsValid(SI4 type);

/* Aligns the given pointer to the correct word boundary for the type. */
SDK void* TypeAlign(SI4 type, void* value);

enum {
  kTypeCount = 32,  //< The starting index of invalid types.
};

/* Masks off the lower 5-LSb to get the type. */
SDK inline UI1 TypeMask(UI1 value);

/* Returns true if the given type is an Array type. */
SDK inline BOL TypeIsArray(SI4 type);

/* Returns true if the given type is a kBOK type. */
SDK inline BOL TypeIsSet(SI4 type);

/* Returns the size or max size of the given type. */
SDK SI4 TypeFixedSize(SI4 type);

/* Gets the next address that a data type may be stored at. */
SDK void* TypeAlign(SI4 type, void* value);

/* Writes the given value to the socket. */
SDK CH1* Write(CH1* begin, CH1* stop, SI4 type, const void* source);

/* Returns true if the given type is an ASCII AArray. */
SDK inline BOL TypeIsObj(SI4 type);

/* Returns true if the given type is a  type. */
SDK inline BOL TypeIsStrand(SI4 type);

/* Checks if the given type is UTF-16.
@param  type The type to check.
@return True if the given type is UTF-16. */
SDK inline BOL TypeIsUTF16(SI4 type);

SDK inline SI4 TypeSizeWidthCode(SI4 type);
}  // namespace _

#if USING_UTF8 == YES
namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop of the read number or
nil upon failure.
@param utf   The utf to utf to.
@param type  The type to utf.
@param value The value to utf or nil. */
SDK CH1* Print(CH1* begin, CH1* stop, SI4 type, const void* value);
}  // namespace _

#endif

#if USING_UTF16 == YES
namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop of the read number or
nil upon failure.
@param utf   The utf to utf to.
@param type  The type to utf.
@param value The value to utf or nil. */
SDK CH2* Print(CH2* begin, CH2* stop, SI4 type, const void* value);
}  // namespace _
#endif
#if USING_UTF32 == YES

namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop
of the read number or nil upon failure.
@param printer The printer to utf to.
@param type    The type to utf.
@param value   The value to utf or nil. */
SDK CH2* Print(CH2* begin, CH2* stop, SI4 type, const void* value);

}  // namespace _
#endif

#endif
#endif
#endif
