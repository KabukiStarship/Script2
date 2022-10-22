/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /TypeValue.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef INCLUDED_TYPEVALUE_CODE
#define INCLUDED_TYPEVALUE_CODE
#include "TypeValue.h"
namespace _ {

/* Gets the log_b. */
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
Printer& TSizefPrint(Printer& printer, Sizef item) {
  auto value = item.size;
  if (value < 0) return printer << CHA('@' + (-value));
  return printer << value;
}

/* Gets one of the STRTypes. */
inline const CHA* STRTypePOD(DTW index) {
  if (index < 0 || index >= cINV) index = 32;
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

/* Prints a string represntation of an ASCII Data Type. */
template<typename Printer>
Printer& TTypePrint(Printer& printer, DTW item) {
  if (item < 32) return printer << STRTypePOD(item); // POD Type
  DTW type_pod = item & 0x1f,
      type_vector = (item & cDTVHT) >> 5;
  if (item >> 8 == 0) { // 8-bit data type.
    // | b7 |    b6:b5    | b4:b0 |
    // |:--:|:-----------:|:-----:|
    // | SW | Vector Type |  POD  |
    if (item >> 7) { // SW bit asserted, there is a 16-bit size_width
      return printer << STRTypeVector(type_vector) << 'B' << '_' 
                     << STRTypePOD(type_pod);
    }

    return printer << STRTypeVector(type_vector) << 'A' << '_'
      << STRTypePOD(type_pod);
  }
  DTW size_width = (item & cDTBSW) >> 7;
  if (item >> 16 == 0) { // 16-bit data type.
    // | b15:b14 |  b13:b9  | b8:b7 | b6:b5 | b4:b0 |
    // |:-------:|:--------:|:-----:|:-----:|:-----:|
    // |   MB    | Map type |  SW   |  VHT  |  POD  |
    if (type_pod == 0) {
      printer << "NIL" << CHA('A' + ((item >> 5) & 0xf)) << " or ";
    }
    DTW modifiers = item >> 14;
    if (modifiers) printer << STRTypeModifier(modifiers) << '_';

    DTW size_width = (item & 0x180) >> 7;
    if (size_width) { // SW bits b8:b7 asserted
      return printer << STRTypeVector(type_vector) 
                     << CHA('@' + size_width) << '_'
                     << STRTypePOD(type_pod);
    }

    DTW type_map = (item & 0x3E00) >> 9;
    if (type_map) 
      return printer << "MAP_" << STRTypePOD(type_map) << '_' << STRTypePOD(type_pod);

    return printer << "ERROR: You done messed up A-A-ron.";
  }
#if ALU_SIZE >= ALU_32_BIT // CPU is 32-bit or 64-bit
#endif
#if ALU_SIZE == ALU_64_BIT
  if (item & ~IUW(0xffffffff)) { // 64-bit data type.
    return printer << "Error dfjaisdfas89fasd0af9sd0";
  }
#endif

  return printer << "Error 4u910j414lj4l24";
}

/* Prints a summary of the type-value tuple with word-sized Data Type. */
template<typename Printer>
Printer& TTypePrint(Printer& printer, TypeWordValue item) {
  return TTypePrint<Printer>(printer, item.type);
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
template <typename DT = DTB>
inline DT TTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}
template <typename DT = DTB>
constexpr DT CTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}

/* Extracts the Map type 0-3 of the type. */
template <typename DT = DTB>
inline DT TTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}
template <typename DT = DTB>
constexpr DT CTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}

/* Creates an ASCII Vector Data Type. */
template <typename DT = DTB>
inline DT TTypeVector(DTW pod_type, DTW vector_type, DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}
template <typename DT = DTB>
constexpr DT CTypeVector(DTW pod_type, DTW vector_type,
                         DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}

/* Creates an ASCII Map Type. */
template <typename DT = DTB>
constexpr DT CTypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}
template <typename DT = DTB>
inline DT TTypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}

/* The ASCII Data Type for the given CHT, cCHA, cCHB, or cCHC. */
template <typename CHT = CHR, typename DT = DTB>
constexpr DT CTypeChar() {
  return DT((sizeof(CHT) == 1)
                ? cCHA
                : (sizeof(CHT) == 2) ? cCHB : (sizeof(CHT) == 4) ? cCHC : 0);
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template <typename ISZ = CHR, typename DT = DTB>
constexpr DT CTypeSize() {
  return (sizeof(ISZ) == 1)
             ? cSW1 
             : (sizeof(ISZ) == 2)
                   ? cSW2
                   : (sizeof(ISZ) == 4) ? cSW4 : (sizeof(ISZ) == 8) ? cSW8 : 0;
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template <typename T, typename DT = DTB>
constexpr DT CTypeSize(DT pod_type) {
  return pod_type | (CTypeSize<T>() << 7);
}

template <typename T, typename DT = DTB>
inline DT TTypeSize(DT pod_type) {
  return pod_type | (CTypeSize<T>() << 7);
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
inline ISA PODTypeMask(DTW value) { return value & 0x1f; }

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

inline BOL TypeIsPOD(DTB type) {
  return !((type >> 5) || ((type & cTypePODMask)));
}

}  //< namespace _

#endif
#endif
