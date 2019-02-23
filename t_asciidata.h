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
#if SEAM >= SCRIPT2_3
#ifndef INCLUDED_ASCIIDATA_T
#define INCLUDED_ASCIIDATA_T

#include "t_socket.h"
#include "t_strand.h"

#if SEAM == SCRIPT2_13
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

template <typename Size>
inline BOL TSizeIsValid(Size size) {
  return (size & (sizeof(Size) - 1)) == 0;
}

/* An ROM  for one of the 32 types.
C++11 variadic templates ensure there is only one copy in of the given in ROM.
*/
template <CH1 kCharA_, CH1 kCharB_, CH1 kCharC_>
inline UI4 T() {
  return ((UI4)kCharA_) & (((UI4)kCharB_) << 8) & (((UI4)kCharC_) << 16);
}

template <typename T = CH1>
T* TypeAlignUpPointer(void* pointer, SI4 type) {
  if (type <= kUI1)
    return reinterpret_cast<T*>(pointer);
  else if (type <= kFP2)
    return TAlignUp2<T>(pointer);
  else if (type <= kTM4)
    return TAlignUp<T>(pointer, 3);
  else if (type <= kFPH)
    return TAlignUp<T>(pointer, 7);
  // else it's an ASCII CObject.
  // | Code | Binary | Mask needed |
  // |:----:|:------:|:-----------:|
  // |  0   | 0b'00  |   0b'000    |
  // |  1   | 0b'01  |   0b'001    |
  // |  2   | 0b'10  |   0b'011    |
  // |  3   | 0b'11  |   0b'111    |
  UIW ptr = reinterpret_cast<UIW>(pointer), mask = (type >> 6);
  if (mask == 2) return TAlignUp<T>(pointer, 3);
  if (mask == 3) return TAlignUp<T>(pointer, 7);
  ptr += ((~ptr) + 1) & mask;
  return reinterpret_cast<T*>(ptr);
}
/*
template <typename Char = CH1>
Char* PrintTypePod(Char* cursor, Char* stop, SI4 type, const void* value) {
  if (!value) return printer << "Nil";
  switch (type & 0x1f) {
    case kNIL:
      return TPrint<Char>(cursor, stop, "Error");
    case kSI1:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI1*>(value));
    case kUI1:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI1*>(value));
    case kSI2:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI2*>(value));
    case kUI2:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI2*>(value));
    case kFP2:
      return TPrint<Char>(cursor, stop, "not_implemented");
    case kBOL:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const BOL*>(value));
    case kSI4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SI4*>(value));
    case kUI4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI4*>(value));
    case kFP4:
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
    case kFP8:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const FP8*>(value));
      // case SV8:
      //  return TPrint<Char> (cursor, stop, *reinterpret_cast<const
      //  SI8*>(value));
      // case UV8:
      //  return TPrint<Char> (cursor, stop, *reinterpret_cast<const
      //  UI8*>(value));
    case kFPH:
      return TPrint<Char>(cursor, stop, "not_implemented");
  }
  return nullptr;
}

template <typename Char = CH1>
Char* Print(Char* cursor, Char* stop, SI4 type, const void* value) {
  if (cursor == nullptr) return nullptr;
  ASSERT(cursor < stop);

  if (type <= kFPH) {
    cursor = PrintTypePod<Char>(cursor, stop, type, value);
    if (!cursor) return nullptr;
    cursor = TPrint<Char>(cursor, stop, ':');
    if (!cursor) return nullptr;
    return TPrint<Char>(cursor, stop, STRType(type));
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
    cursor = TPrint<Char>(cursor, stop, STRType(type));
    return cursor;
  }

  return PrintTypePod(utf, type & 0x1f, value) << "b:" << STRType(type);
}*/

}  // namespace _

#endif
#endif
