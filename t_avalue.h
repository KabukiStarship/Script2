/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_ascii.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_T_ASCIIDATA
#define INCLUDED_T_ASCIIDATA

#include "c_avalue.h"

namespace _ {

template <DTW core_type, DTW map_type, DTW size_width = 0>
DTW TTypeMap() {
  return TypeMap(core_type, map_type) | (size_width << kTypeBitCount);
}
}  // namespace _

#if SEAM >= SEAM_SCRIPT2_UTF
#include "t_socket.h"
#include "t_utf.h"

#if SEAM == SEAM_SCRIPT2_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

template <typename SIZ>
inline BOL TSizeIsValid(SIZ size) {
  return (size & (sizeof(SIZ) - 1)) == 0;
}

/* An ROM  for one of the 32 types.
C++11 variadic templates ensure there is only one copy in of the given in ROM.
*/
template <CH1 kCharA_, CH1 kCharB_, CH1 kCharC_>
inline UI4 T() {
  return ((UI4)kCharA_) & (((UI4)kCharB_) << 8) & (((UI4)kCharC_) << 16);
}

template <typename T = CH1>
T* TTypeAlignUp(void* pointer, SIW type) {
  SIW align_mask = TypeAlignmentMask(type & kTypePODMask);
  return reinterpret_cast<T*>(AlignUp(pointer, align_mask));
}
/*
template <typename Char = CHR>
Char* PrintTypePod(Char* cursor, Char* stop, SIN type, const void* value) {
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
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SIN*>(value));
    case kUI4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const UI4*>(value));
    case kFP4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const FP4*>(value));
    case kTM4:
      return TPrint<Char>(cursor, stop, *reinterpret_cast<const SIN*>(value));
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

template <typename Char = CHR>
Char* Print(Char* cursor, Char* stop, SIN type, const void* value) {
  if (cursor == nullptr) return nullptr;
  A_ASSERT(cursor < stop);

  if (type <= kFPH) {
    cursor = PrintTypePod<Char>(cursor, stop, type, value);
    if (!cursor) return nullptr;
    cursor = TPrint<Char>(cursor, stop, ':');
    if (!cursor) return nullptr;
    return TPrint<Char>(cursor, stop, STRType(type));
  }

  if (!TypeIsSupported(type)) return TPrint<Char>(cursor, stop, "illegal_type");

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
