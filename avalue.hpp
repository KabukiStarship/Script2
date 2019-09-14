/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /typevalue.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_T_ASCIIDATA
#define INCLUDED_T_ASCIIDATA

#include "typevalue.h"

namespace _ {

/* Extracts the Vector type. */
template <typename DT = DT2>
inline DT TTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}
template <typename DT = DT2>
constexpr DT CTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}

/* Extracts the Map type 0-3 of the type. */
template <typename DT = DT2>
inline DT TTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}
template <typename DT = DT2>
constexpr DT CTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}

/* Creates an ASCII Vector Data Type. */
template <typename DT = DT2>
inline DT TTypeVector(DTW pod_type, DTW vector_type, DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}
template <typename DT = DT2>
constexpr DT CTypeVector(DTW pod_type, DTW vector_type,
                         DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}

/* Creates an ASCII Map Type. */
template <typename DT = DT2>
constexpr DT CTypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}
template <typename DT = DT2>
inline DT TTypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}

/* The ASCII Data Type for the given Char, kCH1, kCH2, or kCH4. */
template <typename Char = CHR, typename DT = DT2>
constexpr DT CTypeChar() {
  return DT((sizeof(Char) == 1)
                ? kCH1
                : (sizeof(Char) == 2) ? kCH2 : (sizeof(Char) == 4) ? kCH4 : 0);
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template <typename SIZ = CHR, typename DT = DT2>
constexpr DT CTypeSize() {
  return (sizeof(SIZ) == 1)
             ? kSW1
             : (sizeof(SIZ) == 2)
                   ? kSW2
                   : (sizeof(SIZ) == 4) ? kSW4 : (sizeof(SIZ) == 8) ? kSW8 : 0;
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template <typename T, typename DT = DT2>
constexpr DT CTypeSize(DT pod_type) {
  return pod_type | (CTypeSize<T>() << 7);
}

template <typename T, typename DT = DT2>
inline DT TTypeSize(DT pod_type) {
  return pod_type | (CTypeSize<T>() << 7);
}

}  // namespace _

#if SEAM >= SCRIPT2_UNIPRINTER
#include "binary.hpp"
#include "stringf.hpp"

#if SEAM == SCRIPT2_UNIPRINTER
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* Gets the alignment mask of the given type. */
inline DTW AlignmentMask(CH1 item) { return 0; }
inline DTW AlignmentMask(SI1 item) { return 0; }
inline DTW AlignmentMask(UI1 item) { return 0; }
inline DTW AlignmentMask(CH2 item) { return 1; }
inline DTW AlignmentMask(SI2 item) { return 1; }
inline DTW AlignmentMask(UI2 item) { return 1; }
inline DTW AlignmentMask(CH4 item) { return 3; }
inline DTW AlignmentMask(SI4 item) { return 3; }
inline DTW AlignmentMask(UI4 item) { return 3; }
inline DTW AlignmentMask(FP4 item) { return 3; }
inline DTW AlignmentMask(SI8 item) { return 7; }
inline DTW AlignmentMask(UI8 item) { return 7; }
inline DTW AlignmentMask(FP8 item) { return 7; }
inline DTW AlignmentMask(void* item) { return kWordLSbMask; }
inline DTW AlignmentMask(const void* item) { return kWordLSbMask; }

/* Gets the type of the given item. */
inline DTW TypeOf(CH1 item) { return kCH1; }
inline DTW TypeOf(SI1 item) { return kSI1; }
inline DTW TypeOf(UI1 item) { return kUI1; }
inline DTW TypeOf(CH2 item) { return kCH2; }
inline DTW TypeOf(SI2 item) { return kSI2; }
inline DTW TypeOf(UI2 item) { return kUI2; }
inline DTW TypeOf(CH4 item) { return kCH2; }
inline DTW TypeOf(SI4 item) { return kSI4; }
inline DTW TypeOf(UI4 item) { return kUI4; }
inline DTW TypeOf(FP4 item) { return kFP4; }
inline DTW TypeOf(SI8 item) { return kSI8; }
inline DTW TypeOf(UI8 item) { return kUI8; }
inline DTW TypeOf(FP8 item) { return kFP8; }
inline DTW TypeOf(CH1* item) { return kST1; }
inline DTW TypeOf(const CH1* item) { return kCNS_ST1; }
inline DTW TypeOf(void* item) { return kPTR; }
inline DTW TypeOf(const void* item) { return kCNS_PTR; }

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

/* Gets the alignment mask for the given POD data type. */
inline SIW TypeAlignmentMask(DTW type) {
  if (type == 0) return kWordLSbMask;
  if (type <= kUI1) return 0;
  if (type <= kFP2) return 1;
  if (type <= kTME) sizeof(SIN) - 1;
  return sizeof(SIW) - 1;
}

/* Aligns the pointer up to the word boundry required by the type. */
template <typename T = CH1>
T* TTypeAlignUp(void* pointer, SIW type) {
  SIW align_mask = TypeAlignmentMask(type & kTypePODMask);
  return reinterpret_cast<T*>(AlignUpPTR(pointer, align_mask));
}

/* Gets the size of the type in bytes.
@return A postivie size_bytes if the type is a POD type; 0 if the type is an
Object type; or -1 if the value is a STR. */
inline SIW TypeSizeOf(DTW type) {
  if (type == 0) return kWordLSbMask;
  if (type <= kUI1) return 0;
  if (type <= kFP2) return 1;
  if (type <= kTME) sizeof(SIN) - 1;
  return sizeof(SIW) - 1;
}

/* Checks if the given type is valid.
@return False if the given type is an 1-byte kLST, kMAP, kBOK, or kDIC. */
inline BOL TypeIsSupported(DTW type) { return true; }

/* Gets one f the STRTypes. */
inline const CH1* TypeSTR(DTW index) {
  if (index < 0 || index >= kINV) index = 32;
  const CH1* Strings = STRTypes();
  return Strings + (index << 2);
}

/* Extracts the UTF type.
@return 0 if the type is not a stirng type or 1, 2, or 4 if it is. */
inline SI1 TypeTextFormat(DTW type) {
  DTW core_type = type & kTypePODMask;
  if (core_type == 0) return -1;  //< then core_type < 32
  if (core_type <= kST3) {
    if (core_type == kNIL) return -1;
    return SI1(type);
  }
  if (core_type == type) return -1;  //< then core_type < 32
  if (core_type == kCH1) return 1;
  if (core_type == kCH2) return 2;
  if (core_type <= kCH4) return 3;
  return -1;
}

/* Masks off the primary type. */
inline SI1 PODType(DTW value) { return value & 0x1f; }

/* Returns true if the given type is an Array type. */
inline BOL TypeIsArray(DTW type) { return type >= kTypeCount; }

inline SIN TypeSizeWidthCode(SIN type) { return type >> 6; }

/* Extracts the Map Type. */
inline DTW TypeMap(DTW core_type, DTW map_type) {
  return core_type | (map_type << (kTypePODBitCount + 2));
}
inline DTW TypeMap(DTW core_type, DTW map_type, DTW size_width) {
  return TypeMap(core_type, map_type) | (size_width << kTypePODBitCount);
}

inline BOL TypeIsPOD(DT2 type) {
  return !((type >> 5) || ((type & kTypePODMask)));
}

}  // namespace _

#endif
#endif
