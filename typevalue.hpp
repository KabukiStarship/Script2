/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /TypeValue.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>

#ifndef INCLUDED_TYPEVALUE_CODE
#define INCLUDED_TYPEVALUE_CODE

#include "TypeValue.h"

namespace _ {

/* Gets the size of type T. */
template<typename T>
constexpr Sizef CSizef () {
  Sizef result;
  switch (sizeof(T)) {
    case 1: {
      result.size = -1;
      break;
    }
    case 2: {
      result.size = -2;
      break;
    }
    case 4: {
      result.size = -3;
      break;
    }
    case 8: {
      result.size = -4;
      break;
    }
    case 16: {
      result.size = -5;
      break;
    }
    case 32: {
      result.size = -6;
      break;
    }
    case 64: {
      result.size = -7;
      break;
    }
    case 128: {
      result.size = -8;
      break;
    }
    default: {
      result.size = sizeof(T);
      break;
    }
  }
  return result;
}

/* Prints the given sizef to the printer. */
template<typename Printer>
Printer& TSizefPrint(Printer& printer, Sizef sizef) {
  auto value = sizef.size;
  if (value < 0) return printer << CHA('@' + (-value));
  return printer << value;
}

/* An 8-bit, 16-bit, or 32-bit ASCII Data Type. */
template<typename DT>
class TType {
 public:

  DT type;  //< The ASCII Data Type.

  /* Stores teh type. */
  TType(DT type) : type(type) {}
};

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

/* The ASCII Data Type for the given CHT, cCHA, cCHB, or cCHC. */
template <typename CHT = CHR, typename DT = DT2>
constexpr DT CTypeChar() {
  return DT((sizeof(CHT) == 1)
                ? cCHA
                : (sizeof(CHT) == 2) ? cCHB : (sizeof(CHT) == 4) ? cCHC : 0);
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template <typename ISZ = CHR, typename DT = DT2>
constexpr DT CTypeSize() {
  return (sizeof(ISZ) == 1)
             ? cSW1 
             : (sizeof(ISZ) == 2)
                   ? cSW2
                   : (sizeof(ISZ) == 4) ? cSW4 : (sizeof(ISZ) == 8) ? cSW8 : 0;
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

#if SEAM >= SCRIPT2_CORE
#include "Binary.hpp"
#include "Stringf.hpp"

#if SEAM == SCRIPT2_CORE
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif

namespace _ {

/* Gets the alignment mask of the given type. */
inline DTW AlignmentMask(CHA item) { return 0; }
inline DTW AlignmentMask(ISA item) { return 0; }
inline DTW AlignmentMask(IUA item) { return 0; }
inline DTW AlignmentMask(CHB item) { return 1; }
inline DTW AlignmentMask(ISB item) { return 1; }
inline DTW AlignmentMask(IUB item) { return 1; }
inline DTW AlignmentMask(CHC item) { return 3; }
inline DTW AlignmentMask(ISC item) { return 3; }
inline DTW AlignmentMask(IUC item) { return 3; }
inline DTW AlignmentMask(FPC item) { return 3; }
inline DTW AlignmentMask(ISD item) { return 7; }
inline DTW AlignmentMask(IUD item) { return 7; }
inline DTW AlignmentMask(FPD item) { return 7; }
inline DTW AlignmentMask(void* item) { return cWordLSbMask; }
inline DTW AlignmentMask(const void* item) { return cWordLSbMask; }

/* Gets the type of the given item. */
inline DTW TypeOf(CHA item) { return cCHA; }
inline DTW TypeOf(ISA item) { return cISA; }
inline DTW TypeOf(IUA item) { return cIUA; }
inline DTW TypeOf(CHB item) { return cCHB; }
inline DTW TypeOf(ISB item) { return cISB; }
inline DTW TypeOf(IUB item) { return cIUB; }
inline DTW TypeOf(CHC item) { return cCHB; }
inline DTW TypeOf(ISC item) { return cISC; }
inline DTW TypeOf(IUC item) { return cIUC; }
inline DTW TypeOf(FPC item) { return cFPC; }
inline DTW TypeOf(ISD item) { return cISD; }
inline DTW TypeOf(IUD item) { return cIUD; }
inline DTW TypeOf(FPD item) { return cFPD; }
inline DTW TypeOf(CHA* item) { return cSTA; }
inline DTW TypeOf(const CHA* item) { return cCNS_STA; }
inline DTW TypeOf(void* item) { return cPTR; }
inline DTW TypeOf(const void* item) { return cCNS_PTR; }

template <typename ISZ>
inline BOL TSizeIsValid(ISZ size) {
  return (size & (sizeof(ISZ) - 1)) == 0;
}

/* An ROM  for one of the 32 types.
C++11 variadic templates ensure there is only one copy in of the given in ROM.
*/
template <CHA CharA, CHA CharB, CHA CharC>
inline IUC T() {
  return ((IUC)CharA) & (((IUC)CharB) << 8) & (((IUC)CharC) << 16);
}

/* Gets the alignment mask for the given POD data type. */
inline ISW TypeAlignmentMask(DTW type) {
  if (type == 0) return cWordLSbMask;
  if (type <= cIUA) return 0;
  if (type <= cFPB) return 1;
  if (type <= cTME) sizeof(ISN) - 1;
  return sizeof(ISW) - 1;
}

/* Aligns the pointer up to the word boundry required by the type. */
template <typename T = CHA>
T* TTypeAlignUp(void* pointer, ISW type) {
  ISW align_mask = TypeAlignmentMask(type & cTypePODMask);
  return reinterpret_cast<T*>(AlignUpPTR(pointer, align_mask));
}

/* Gets the size of the type in bytes.
@return A postivie size_bytes if the type is a POD type; 0 if the type is an
Object type; or -1 if the value is a STR. */
inline ISW TypeSizeOf(DTW type) {
  if (type == 0) return cWordLSbMask;
  if (type <= cIUA) return 0;
  if (type <= cFPB) return 1;
  if (type <= cTME) sizeof(ISN) - 1;
  return sizeof(ISW) - 1;
}

/* Checks if the given type is valid.
@return False if the given type is an 1-byte cLST, cMAP, kBOK, or kDIC. */
inline BOL TypeIsSupported(DTW type) { return true; }

/* Gets one f the STRTypes. */
inline const CHA* STRType(DTW index) {
  if (index < 0 || index >= cINV) index = 32;
  const CHA* Strings = STRTypes();
  return Strings + (index << 2);
}

/* Extracts the UTF type.
@return 0 if the type is not a stirng type or 1, 2, or 4 if it is. */
inline ISA TypeTextFormat(DTW type) {
  DTW core_type = type & cTypePODMask;
  if (core_type == 0) return -1;  //< then core_type < 32
  if (core_type <= cSTC) {
    if (core_type == cNIL) return -1;
    return ISA(type);
  }
  if (core_type == type) return -1;  //< then core_type < 32
  if (core_type == cCHA) return 1;
  if (core_type == cCHB) return 2;
  if (core_type <= cCHC) return 3;
  return -1;
}

/* Masks off the primary type. */
inline ISA PODType(DTW value) { return value & 0x1f; }

/* Returns true if the given type is an Array type. */
inline BOL TypeIsArray(DTW type) { return type >= cTypeCount; }

inline ISN TypeSizeWidthCode(ISN type) { return type >> 6; }

/* Extracts the Map Type. */
inline DTW TypeMap(DTW core_type, DTW map_type) {
  return core_type | (map_type << (cTypePODBitCount + 2));
}

inline DTW TypeMap(DTW core_type, DTW map_type, DTW size_width) {
  return TypeMap(core_type, map_type) | (size_width << cTypePODBitCount);
}

inline BOL TypeIsPOD(DT2 type) {
  return !((type >> 5) || ((type & cTypePODMask)));
}

}  // namespace _

#endif
#endif
