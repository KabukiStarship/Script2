/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /Types.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef INCLUDED_TYPEVALUE_CODE
#define INCLUDED_TYPEVALUE_CODE
#include "Types.h"
namespace _ {

/* Stores an ASCII type and pointer to it's value. */
template<typename DT = DTW>
struct TTypeValue {
  DT type;      //< The ASCII data type word.
  void* value;  //< POint to the value of the type.
};

/* Stores an offset to the ASCII data type and it's value. */
template<typename IS = ISW, typename DT = DTW>
struct TTypeValueOffset {
  DT type;      //< The ASCII data type word.
  IS value;     //< Offset to the value of the type.
};

/* Gets the log_b. */
template<typename T>
constexpr Sizef TSizef () {
  Sizef result = {0};
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

/* Gets one of the STRTypes. */
inline const CHA* STRTypePOD(DTW index) {
  if (index < 0 || index >= Invalid) index = 32;
  return STRTypesPOD() + (index << 2); // << 2 to * 4
}

/* Gets one f the STRTypes. */
inline const CHA* STRTypeVector(DTW index) {
  if (index < 0 || index >= 4) index = 0;
  return STRTypesVector() + (index << 2); // << 2 to * 4
}

/* Gets one f the STRTypes. */
inline const CHA* STRTypeModifier(DTW index) {
  if (index < 0 || index >= 4) index = 0;
  return STRTypesModifier() + (index << 2); // << 2 to * 4
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
template<typename DT = DTB>
inline DT TTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}
template<typename DT = DTB>
constexpr DT CTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}

/* Extracts the Map type 0-3 of the type. */
template<typename DT = DTB>
inline DT TTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}
template<typename DT = DTB>
constexpr DT CTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}

/* Creates an ASCII Vector Data Type. */
template<typename DT = DTB>
inline DT TTypeVector(DTW pod_type, DTW vector_type, DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}
template<typename DT = DTB>
constexpr DT CTypeVector(DTW pod_type, DTW vector_type,
                         DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}

/* Creates an ASCII Map Type. */
template<typename DT = DTB>
constexpr DT CTypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}
template<typename DT = DTB>
inline DT TTypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template<typename IS = CHR, typename DT = DTB>
constexpr DT CTypeSize() {
  return (sizeof(IS) ==  1) ? _SWA 
       : (sizeof(IS) ==  2) ? _SWB
       : (sizeof(IS) ==  4) ? _SWC
       : (sizeof(IS) ==  8) ? _SWD 
       : (sizeof(IS) == 16) ? _SWE : 0;
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template<typename T, typename DT = DTB>
constexpr DT CTypeSize(DT pod_type) {
  return pod_type | (CTypeSize<T>() << 7);
}

template<typename T, typename DT = DTB>
inline DT TTypeSize(DT pod_type) {
  return pod_type | (CTypeSize<T>() << 7);
}

/* Returns the ASCII Type for the given floating-point type FP.
FPB:  4   0b00100   (0b001 << 2) | 0b00
FPC:  8   0b01000   (0b010 << 2) | 0b00
FPD: 12   0b01100   (0b011 << 2) | 0b00
FPE: 16   0b10000   (0b100 << 2) | 0b00
*/
template<typename FP, typename DT = DTB>
constexpr DT CTypeFP() {
  return (CTypeSize<FP, DT>() << 2);
}

/* Returns the ASCII Type for the given unsigned integer type IS.
IUA:  1   0b00001   (0b000 << 2) | 0b01
IUB:  5   0b00101   (0b001 << 2) | 0b01
IUC:  9   0b01001   (0b010 << 2) | 0b01
IUD: 13   0b01101   (0b011 << 2) | 0b01
IUE: 17   0b10001   (0b100 << 2) | 0b01
*/
template<typename IU, typename DT = DTB>
constexpr DT CTypeIU() {
  return (CTypeSize<IU, DT>() << 2) | 1;
}

/* Returns the ASCII Type for the given signed integer type IS.
ISA:  2   0b00010   (0b000 << 2) | 0b10
ISB:  6   0b00110   (0b001 << 2) | 0b10
ISC: 10   0b01010   (0b010 << 2) | 0b10
ISD: 14   0b01110   (0b011 << 2) | 0b10
ISE: 18   0b10010   (0b100 << 2) | 0b10
*/
template<typename IS, typename DT = DTB>
constexpr DT CTypeIS() {
  return (CTypeSize<IS, DT>() << 2) | 2;
}

/* Returns the ASCII Type for the given character type CH.
CHB:  3   0b0011   (0b00 << 2) | 0b11
CHC:  7   0b0111   (0b01 << 2) | 0b11
CHD: 11   0b1011   (0b10 << 2) | 0b11
CHE: 15   0b1111   (0b11 << 2) | 0b11
*/
template<typename CH, typename DT = DTB>
constexpr DT CTypeCH() {
  return (CTypeSize<CH, DT>() << 2) | 3;
}

}  //< namespace _

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
inline DTW AlignmentMask(void* item) { return WordLSbMask; }
inline DTW AlignmentMask(const void* item) { return WordLSbMask; }

/* Gets the type of the given item. */
inline DTW TypeOf(CHA item) { return _CHA; }
inline DTW TypeOf(ISA item) { return _ISA; }
inline DTW TypeOf(IUA item) { return _IUA; }
inline DTW TypeOf(CHB item) { return _CHB; }
inline DTW TypeOf(ISB item) { return _ISB; }
inline DTW TypeOf(IUB item) { return _IUB; }
inline DTW TypeOf(CHC item) { return _CHB; }
inline DTW TypeOf(ISC item) { return _ISC; }
inline DTW TypeOf(IUC item) { return _IUC; }
inline DTW TypeOf(FPC item) { return _FPC; }
inline DTW TypeOf(ISD item) { return _ISD; }
inline DTW TypeOf(IUD item) { return _IUD; }
inline DTW TypeOf(FPD item) { return _FPD; }
inline DTW TypeOf(CHA* item) { return _STA; }
inline DTW TypeOf(const CHA* item) { return _CNS_STA; }
inline DTW TypeOf(void* item) { return _PTR; }
inline DTW TypeOf(const void* item) { return _CNS_PTR; }

template<typename IS>
inline BOL TSizeIsValid(IS size) {
  return (size & (sizeof(IS) - 1)) == 0;
}

/* An ROM  for one of the 32 types.
C++11 variadic templates ensure there is only one copy in of the given in ROM.
*/
template<CHA CharA, CHA CharB, CHA CharC>
inline IUC T() {
  return ((IUC)CharA) & (((IUC)CharB) << 8) & (((IUC)CharC) << 16);
}

/* Gets the alignment mask for the given POD data type. */
inline ISW TypeAlignmentMask(DTW type) {
  if (type == 0) return WordLSbMask;
  if (type <= _IUA) return 0;
  if (type <= _FPB) return 1;
  if (type <= _TME) sizeof(ISN) - 1;
  return sizeof(ISW) - 1;
}

/* Aligns the pointer up to the word boundry required by the type. */
template<typename T = CHA>
T* TTypeAlignUp(void* pointer, ISW type) {
  ISW align_mask = TypeAlignmentMask(type & PODTypeMask);
  return TPtr<T>(AlignUpPTR(pointer, align_mask));
}

/* Gets the size of the type in bytes.
@return A postivie size_bytes if the type is a POD type; 0 if the type is an
Object type; or -1 if the value is a STR. */
inline ISW TypeSizeOf(DTW type) {
  if (type == 0) return WordLSbMask;
  if (type <= _IUA) return 0;
  if (type <= _FPB) return 1;
  if (type <= _TME) sizeof(ISN) - 1;
  return sizeof(ISW) - 1;
}

/* Checks if the given type is valid.
@return False if the given type is an 1-byte cLST, cMAP, kBOK, or kDIC. */
inline BOL TypeIsSupported(DTW type) { return true; }

/* Extracts the UTF type.
@return 0 if the type is not a stirng type or 1, 2, or 4 if it is. */
inline ISA TypeTextFormat(DTW type) {
  DTW core_type = type & PODTypeMask;
  if (core_type == 0) return -1;  //< then core_type < 32
  if (core_type <= _STC) {
    if (core_type == _NIL) return -1;
    return ISA(type);
  }
  if (core_type == type) return -1;  //< then core_type < 32
  if (core_type == _CHA) return 1;
  if (core_type == _CHB) return 2;
  if (core_type <= _CHC) return 3;
  return -1;
}

/* Masks off the primary type. */
inline ISA TypePODMask(DTW value) { return value & 0x1f; }

/* Returns true if the given type is an Array type. */
inline BOL TypeIsArray(DTW type) { return type >= PODTypeCount; }

inline ISN TypeSizeWidthCode(ISN type) { return type >> 6; }

/* Extracts the Map Type. */
inline DTW TypeMap(DTW core_type, DTW map_type) {
  return core_type | (map_type << (TypePODBitCount + 2));
}

inline DTW TypeMap(DTW core_type, DTW map_type, DTW size_width) {
  return TypeMap(core_type, map_type) | (size_width << TypePODBitCount);
}

inline BOL TypeIsPOD(DTB type) {
  return !((type >> 5) || ((type & PODTypeMask)));
}

}  //< namespace _

#endif
#endif
