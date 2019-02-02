/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_ascii_data.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_13
#ifndef INCLUDED_SCRIPTTYPES
#define INCLUDED_SCRIPTTYPES

#include "c_socket.h"
#include "t_strand.h"

#if SEAM == SCRIPT2_13
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

/* @tag Comment may be wrapped around
like this.
@tag Or comment may be
      wrapped around like this.
*/

namespace _ {

/* A type-value tuple. */
struct SDK TypeValue {
  SI4 type;           //< ASCII Type.
  const void* value;  //< Pointer to the value data.

  /* Stores the type and value. */
  TypeValue(SI4 type, const void* value = nullptr);
};

/* List of the 32 ASCII Data Types.
    Types are organized with types that are allowed in text B-Sequences first,
    followed by objects which get created in text using Script Operations. */
typedef enum AsciiTypes {
  kNIL = 0,  //< 0.  kNIL/nil/void type.
  kSI1,      //< 1.  8-bit signed integer.
  kUI1,      //< 2.  8-bit unsigned integer.
  kSI2,      //< 3.  16-bit signed integer.
  kUI2,      //< 4.  16-bit unsigned integer.
  kHLF,      //< 5.  16-bit floating-point number_.
  kBOL,      //< 6.  32-bit non-zero true boolean as signed integer.
  kint,      //< 7.  32-bit signed integer.
  kUI4,      //< 8.  32-bit unsigned integer.
  kFLT,      //< 9.  32-bit floating-point number_.
  kTM4,      //< 10. 32-bit second since epoch timestamp.
  kTME,      //< 11. 64-bit sub-second timestamp with kTM4 and an kUI4 tick.
  kTM8,      //< 12. 64-bit second since epoch timestamp.
  kSI8,      //< 13. 64-bit signed integer.
  kUI8,      //< 14. 64-bit unsigned integer.
  kDBL,      //< 15. 64-bit floating-point number_.
  kSIH,      //< 16. 128-bit (Hexadeca-bit) signed integer.
  kUIH,      //< 17. 128-bit (Hexadeca-bit) unsigned integer.
  kDEC,      //< 18. 128-bit (Hexadeca-bit) floating-point number_.
  kUIX,      //< 19. 2^(6+X)-bit unsigned integer, where 0 <= X <= 7.
  kADR,      //< 20. UTF-8 Operand stack address.
  kSTR,      //< 21. A UTF-8 .
  kTKN,      //< 22. A UTF-8  token without whitespace.
  kBSQ,      //< 23. B-Sequence.
  kOBJ,      //< 24. N-UI1 object.
  kLOM,      //< 25. A loom of UTF-8, UTF-16, or UTF-32 strings.
  kTBL,      //< 26. A hash table.
  kEXP,      //< 27. Script Expression.
  kLST,      //< 28. Set or multiset of Type-Value tuples.
  kMAP,      //< 29. One-to-one map of Integer-{Type-Value} records.
  kBOK,      //< 30. Many-to-one multimap of Key-{Type-Value} records.
  kDIC,      //< 31. One-to-one map of Key-{Type-Value} records.
} AsciiType;

/* Checks if the given type is valid.
    @return False if the given type is an 8-bit kLST, kMAP, kBOK, or kDIC. */
inline BOL TypeIsValid(SI4 type) {
  if (type >= kLST && type <= kDIC ||
      (type >= (kADR + 32) && type <= (kTKN + 32)))
    return false;
  return true;
}

/* Aligns the given pointer to the correct word boundary for the type. */
SDK void* TypeAlign(SI4 type, void* value);

/* An ROM  for one of the 32 types.
    C++11 variadic templates ensure there is only one copy in of the given
     in ROM. */
template <CH1 kCharA_, CH1 kCharB_, CH1 kCharC_>
inline UI4 T() {
  return ((UI4)kCharA_) & (((UI4)kCharB_) << 8) & (((UI4)kCharC_) << 16);
}

template <typename Char = CH1>
const Char** TTypeStrands() {
  static const Char* kNames[] = {
      "kNIL",  //<  0
      "kSI1",  //<  1
      "kUI1",  //<  2
      "kSI2",  //<  3
      "kUI2",  //<  4
      "kHLF",  //<  5
      "kBOL",  //<  6
      "SVI",   //<  7
      "UVI",   //<  8
      "kint",  //<  9
      "kUI4",  //< 10
      "kFLT",  //< 11
      "kTM4",  //< 12
      "kTM8",  //< 13
      "kSI8",  //< 14
      "kUI8",  //< 15
      "kDBL",  //< 16
      "SV8",   //< 17
      "UV8",   //< 18
      "kDEC",  //< 19
      "kUIX",  //< 20
      "kADR",  //< 23
      "kSTR",  //< 24
      "kTKN",  //< 25
      "kOBJ",  //< 21
      "kLOM",  //< 25
      "kBSQ",  //< 26
      "ESC",   //< 27
      "kLST",  //< 28
      "kBOK",  //< 29
      "kDIC",  //< 30
      "kMAP",  //< 31
  };
  return kNames;
}

template <typename T = CH1>
T* TypeAlignUpPointer(void* pointer, SI4 type) {
  if (type <= kUI1)
    return reinterpret_cast<T*>(pointer);
  else if (type <= kHLF)
    return AlignUpPointer2<T>(pointer);
  else if (type <= kTM4)
    return AlignUpPointer4<T>(pointer);
  else if (type <= kDEC)
    return AlignUpPointer8<T>(pointer);
  // else it's an ASCII CObject.
  // | Code | Binary | Mask needed |
  // |:----:|:------:|:-----------:|
  // |  0   | 0b'00  |   0b'000    |
  // |  1   | 0b'01  |   0b'001    |
  // |  2   | 0b'10  |   0b'011    |
  // |  3   | 0b'11  |   0b'111    |
  UIW ptr = reinterpret_cast<UIW>(pointer), mask = (type >> 6);
  if (mask == 2) return AlignUpPointer4<T>(pointer);
  if (mask == 3) return AlignUpPointer8<T>(pointer);
  ptr += ((~ptr) + 1) & mask;
  return reinterpret_cast<T*>(ptr);
}

template <typename Char = CH1>
Char* PrintTypePod(Char* cursor, Char* stop, SI4 type, const void* value) {
  if (!value) return printer << "Nil";
  switch (type & 0x1f) {
    case kNIL:
      return TPrint<Char>("Error");
    case kSI1:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI1*>(value));
    case kUI1:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI1*>(value));
    case kSI2:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI2*>(value));
    case kUI2:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI2*>(value));
    case kHLF:
      return TPrint<Char>(cursor, stop, "not_implemented");
    case kBOL:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const BOL*>(value));
    case kint:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI4*>(value));
    case kUI4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI4*>(value));
    case kFLT:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const FP4*>(value));
    case kTM4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI4*>(value));
    case kTM8:
    case kTM8:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI8*>(value));
    case kSI8:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI8*>(value));
    case kUI8:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI8*>(value));
    case kDBL:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const FP8*>(value));
      // case SV8:
      //  return TPrint<Char> (cursor, stop, *reinterpret_cast<const
      //  SI8*>(value));
      // case UV8:
      //  return TPrint<Char> (cursor, stop, *reinterpret_cast<const
      //  UI8*>(value));
    case kDEC:
      return TPrint<Char>(cursor, stop, "not_implemented");
  }
  return nullptr;
}

template <typename Char = CH1>
Char* Print(Char* cursor, Char* stop, SI4 type, const void* value) {
  if (cursor == nullptr) return nullptr;
  ASSERT(cursor < stop);

  if (type <= kDEC) {
    cursor = PrintTypePod<Char>(cursor, stop, type, value);
    if (!cursor) return nullptr;
    cursor = TPrint<Char>(cursor, stop, ':');
    if (!cursor) return nullptr;
    return TPrint<Char>(cursor, stop, TypeStrand<Char>(type));
  }

  if (!TypeIsValid(type)) return TPrint<Char>(cursor, stop, "illegal_type");

  if (TypeIsStrand(type)) {
    cursor = TPrint<Char>(cursor, stop, '\"');
    if (!cursor) return nullptr;
    cursor = TPrint<Char>(cursor, stop, *reinterpret_cast<const CH1*>(value));
    if (!cursor) return nullptr;
    cursor = TPrint<Char>(cursor, stop, reinterpret_cast<const CH1*>(value));
    if (!cursor) return nullptr;
    cursor = TPrint<Char>(cursor, stop, "\":");
    if (!cursor) return nullptr;
    return cursor = TPrint<Char>(cursor, stop, TypeStrand(type));
  }

  return PrintTypePod(utf, type & 0x1f, value) << "b:" << TypeStrand(type);
}

#if USING_UTF8
namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop of the read number_ or
nil upon failure.
@param utf The utf to utf to.
@param type    The type to utf.
@param value   The value to utf or nil. */
SDK CH1* Print(CH1* begin, CH1* stop, SI4 type, const void* value);
}  // namespace _
/* Writes the given value to the utf justified right.
@return The utf.
@param  utf The utf.
@param  item The item to utf. */
SDK ::_::UTF1& operator<<(::_::UTF1& utf, const ::_::TypeValue& type_value);
#endif
#if USING_UTF16
namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop of the read number_ or
nil upon failure.
@param utf The utf to utf to.
@param type    The type to utf.
@param value   The value to utf or nil. */
SDK CH2* Print(CH2* begin, CH2* stop, SI4 type,
                    const void* value);
}  // namespace _
/* Writes the given value to the utf justified right.
@return The utf.
@param  utf The utf.
@param  item The item to utf. */
SDK ::_::UTF2& operator<<(::_::UTF2& utf, const ::_::TypeValue& type_value);
#endif
#if USING_UTF32

namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next CH1 after the stop
of the read number_ or nil upon failure.
@param printer The printer to utf to.
@param type    The type to utf.
@param value   The value to utf or nil. */
SDK CH2* Print(CH2* begin, CH2* stop, SI4 type,
                    const void* value);
}  // namespace _
/* Writes the given value to the utf justified right.
@return The utf.
@param  utf The utf.
@param  item The item to utf. */
SDK ::_::UTF4& operator<<(::_::UTF4& utf, const ::_::TypeValue& type_value);
#endif

}  // namespace _

#endif  //< INCLUDED_SCRIPTTYPES
#endif  //< #if SEAM >= SCRIPT2_13
