// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef INCLUDED_TYPES_CODE
#define INCLUDED_TYPES_CODE
#include "Types.h"
namespace _ {

/* Stores an ASCII type and pointer to it's value. */
template<typename DT = DTW>
struct TATypeValuePtr {
  DT    type;   //< The ASCII data type word.
  void* value;  //< POint to the value of the type.
};

/* Stores an ASCII data type and offset to value.
This class is preferred over TATypeValuePtr for x86_64 because two 32-bit or 
smaller values may be returned from functions without using the stack. */
template<typename IS = ISW, typename DT = DTW>
struct TATypeValue {
  DT type;      //< The ASCII data type word.
  IS value;     //< Offset to the value of the type.
};

/* Stores a pointer to the ASCII data type and it's value. */
template<typename IS = ISW, typename DT = DTW, typename CH = CHR>
struct TATypeKV {
  const CH* key;          //< Pointer to the key.
  TATypeValue<IS, DT> tv; //< AType value offset pair.
};

/* Stores a pointer to the ASCII data type and it's value. */
template<typename IS = ISW, typename DT = DTW, typename CH = CHR>
struct TATypeKeyValueIndex {
  IS index;                        //< Index of the key-value pair.
  TATypeKV<IS, DT, CH> type_value; //< Pointer to the value of the type.
};

/* An 8-bit, 16-bit, or 32-bit ASCII Data Type. */
template<typename DT>
class TType {
 public:

  DT type;  //< The ASCII Data Type.

  TType(DT type) : type(type) {} //< Stores the type.
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

// Returns the memory alignment mask for this type.
ISA ATypeAlignMask(DTB type) {
  DezNutz:
  if (type <= _CHA) return 0;
  if (type <= _CHB) return 1;
  if (type <= _CHC) return ALUAlignC;
  if (type <= _TME) return ALUAlignD;
  if (type < _CTD) return ALUAlignD;
  if (type < _CTC) return ALUAlignC;
  if (type < _CTB) return 1;
  if (type < _CTA) return 0;
  DTB mod = type >> ATypeMODBit0;
  type ^= mod << ATypeMODBit0;
  DTB mt = type >> ATypeMTBit0;
  type ^= mt << ATypeMTBit0;
  DTB sw = type >> ATypeSWBit0;
  type ^= sw << ATypeSWBit0;
  DTB vt = type >> ATypeVTBit0;
  type ^= vt << ATypeVTBit0;
  if (vt == 0) { // Vetor of 2 to 4 Homo-tuples
    type &= (ATypePODTotal - 1);
    goto DezNutz;
  }
  switch (sw) {
  case 0: return 0;
  case 1: return 1;
  case 2: return ALUAlignC;
  case 3: return ALUAlignD;
  }
  return ALUWordMask;
}
ISA ATypeAlignMask(DTC type) {  return ATypeAlignMask(DTB(type)); }
ISA ATypeAlignMask(DTD type) {  return ATypeAlignMask(DTB(type)); }

/* Aligns the pointer up to the word boundry required by the type. */
template<typename T = void>
T* TATypePtrUp(void* pointer, DTB type) {
  ISW align_mask = ATypeAlignMask(type);
  return reinterpret_cast<T*>(ISW(pointer) + (-ISW(pointer) & align_mask));
}
template<typename T = void>
inline const T* TATypePtrUp(const void* pointer, DTB type) {
  return const_cast<const T*>(TATypePtrUp<T>(const_cast<T*>(pointer), type));
}
template<typename T = void>
T* TATypePtrUp(void* pointer, DTC type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrUp(const void* pointer, DTC type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}
template<typename T = void>
T* TATypePtrUp(void* pointer, DTD type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrUp(const void* pointer, DTD type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}

/* Aligns the pointer down to the word boundry required by the type. */
template<typename T = void>
T* TATypePtrDown(void* pointer, DTB type) {
  ISW align_mask = ATypeAlignMask(type);
  return reinterpret_cast<T*>(ISW(pointer) - (ISW(pointer) & align_mask));
}
template<typename T = void>
inline const T* TATypePtrDown(const void* pointer, DTB type) {
  return const_cast<const T*>(TATypePtrDown<T>(const_cast<T*>(pointer), type));
}
template<typename T = void>
T* TATypePtrDown(void* pointer, DTC type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrDown(const void* pointer, DTC type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}
template<typename T = void>
T* TATypePtrDown(void* pointer, DTD type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrDown(const void* pointer, DTD type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}

/* Copies the source to the destination.
This function is different in that it 
@return nullptr if the destination does not have enough space. */
template<typename IS = ISR>
void* TATypeClone(void* destination, const void* source) {
  auto dst = static_cast<IS*>(destination);
  auto src = static_cast<const IS*>(source);
  auto dst_count = *dst;
  auto src_count = *src;
  if (dst_count < src_count) return nullptr;
  auto result = RAMCopy(dst, dst_count, src, src_count);
  if (result <= 0) return nullptr;
  return static_cast<void*>(dst);
}
/* Writes the given value to the socket. */
template<typename IS = ISR>
void* TATypeWriteCustom(void* begin, void* end, DTB type) {
  return begin;
}

/* Writes the given value to the socket between begin and end without any 
checks.
@warning You must memory align and verify the boofer fits before calling. */
template<typename IS = ISR>
void* TATypeWrite_NC(void* begin, void* end, DTB type, const void* value) {
  // | b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
  // |:-------:|:------:|:-----:|:-----:|:-----:|
  // |   MOD   |   MT   |  SW   |  VT   |  POD  |
  DTB mod = type >> ATypeMODBit0;
  type ^= mod << ATypeMODBit0;
  if (mod && 1) type = _IUW;

  ISW align_mask = ATypeAlignMask(type);
  void* value_aligned_ptr = TPtrUp<>(value, align_mask);
  auto value_align_delta = ISW(value_aligned_ptr) - ISW(value);
  void* base_ptr = TPtrUp<>(begin, align_mask);
  ISW freespace = ISW(end) - ISW(base_ptr);
  if (type <= _CHA) {
    Write1Byte:
    if (freespace < 1) return nullptr;
    auto ptr = reinterpret_cast<IUA*>(base_ptr);
    *ptr++ = *reinterpret_cast<const IUA*>(value_aligned_ptr);
    return ptr;
  }
  if (type <= _CHB) {
    Write2Bytes:
    if (freespace < 2) return nullptr;
    auto ptr = reinterpret_cast<IUB*>(base_ptr);
    *ptr++ = *reinterpret_cast<const IUB*>(value_aligned_ptr);
    return ptr;
  }
  if (type <= _CHC) {
    Write4Bytes:
    if (freespace < 4) return nullptr;
    auto ptr = reinterpret_cast<IUC*>(base_ptr);
    *ptr++ = *reinterpret_cast<const IUC*>(value_aligned_ptr);
    return ptr;
  }
  if (type <= _TMD) {
    Write8Bytes:
    if (freespace < 8) return nullptr;
    auto ptr = reinterpret_cast<IUD*>(base_ptr);
    *ptr++ = *reinterpret_cast<const IUD*>(value_aligned_ptr);
    return ptr;
  }
  if (type <= _TME) {
    Write16Bytes:
    if (freespace < 16) return nullptr;
    auto ptr = reinterpret_cast<IUD*>(base_ptr);
    auto value_ptr = reinterpret_cast<const IUD*>(value_aligned_ptr);
    *ptr++ = *value_ptr++;
    *ptr++ = *value_ptr;
    return ptr;
  }
  if (type <= _CTE) goto Write16Bytes;
  if (type <= _CTD) goto Write8Bytes;
  if (type <= _CTC) goto Write4Bytes;
  if (type <= _CTB) goto Write2Bytes;
  if (type <= _CTA) goto Write1Byte;

  DTB mt = type >> ATypeMTBit0;
  type ^= mt << ATypeMTBit0;
  DTB sw = type >> ATypeSWBit0;
  type ^= sw << ATypeSWBit0;
  DTB vt = type >> ATypeVTBit0;
  type ^= vt << ATypeVTBit0;
  //@todo Fix me!
  if (vt == 0) { // Vector of Homotuples.
    auto bytes = (1 << vt) * ATypeSizeOfPOD(type);
    return reinterpret_cast<ISA*>(base_ptr) + bytes;
  } else {
    switch (vt) {
      case 0: {
        auto bytes = *reinterpret_cast<const ISA*>(value_aligned_ptr);
        if (freespace <= bytes) return nullptr;
        *reinterpret_cast<ISA*>(base_ptr) = bytes;
        return reinterpret_cast<ISA*>(base_ptr) + bytes;
      }
      case 1: {
        auto bytes = *reinterpret_cast<const ISB*>(value_aligned_ptr);
        if (freespace <= bytes) return nullptr;
        *reinterpret_cast<ISB*>(base_ptr) = bytes;
        return reinterpret_cast<ISA*>(base_ptr) + bytes;
      }
      case 2: {
        auto bytes = *reinterpret_cast<const ISC*>(value_aligned_ptr);
        if (freespace <= bytes) return nullptr;
        *reinterpret_cast<ISC*>(base_ptr) = bytes;
        return reinterpret_cast<ISA*>(base_ptr) + bytes;
      }
      case 3: {
        auto bytes = *reinterpret_cast<const ISD*>(value_aligned_ptr);
        if (freespace <= bytes) return nullptr;
        *reinterpret_cast<ISD*>(base_ptr) = bytes;
        return reinterpret_cast<ISA*>(base_ptr) + bytes;
      }
    }
  }
  return nullptr;
}

template<typename IS = ISR>
void* TATypeWrite_NC(void* begin, void* end, DTC type, const void* value) {
  auto result = TATypeWrite_NC<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  return TATypeWrite_NC<IS>(result, end, DTB(type >> 16), value);
}

template<typename IS = ISR>
void* TATypeWrite_NC(void* begin, void* end, DTD type, const void* value) {
  auto result = TATypeWrite_NC<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  result = TATypeWrite_NC<IS>(result, end, DTB(type >> 16), value);
  if (!result) return result;
  return TATypeWrite_NC<IS>(result, end, DTB(type >> 24), value);
}

template<typename IS = ISR>
void* TATypeWrite(void* begin, void* end, DTB type, const void* value) {
  return TATypeWrite<IS>(begin, end, type, value);
}

template<typename IS = ISR>
void* TATypeWrite(void* begin, void* end, DTC type, const void* value) {
  auto result = TATypeWrite<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  return TATypeWrite<IS>(result, end, DTB(type >> 16), value);
}

template<typename IS = ISR>
void* TATypeWrite(void* begin, void* end, DTD type, const void* value) {
  auto result = TATypeWrite<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  result = TATypeWrite<IS>(result, end, DTB(type >> 16), value);
  if (!result) return result;
  return TATypeWrite<IS>(result, end, DTB(type >> 24), value);
}

/* Creates an ASCII Vector Data Type. */
template<typename DT = DTB>
inline DT TATypeVector(DTW pod_type, DTW vector_type, DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}
template<typename DT = DTB>
constexpr DT CATypeVector(DTW pod_type, DTW vector_type,
                         DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}

/* Creates an ASCII Map Type. */
template<typename DT = DTB>
constexpr DT CATypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}
template<typename DT = DTB>
inline DT TATypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}

// Strings for the POD types 0-31.
template<typename CHT = CHR>
const CHT* TATypePODs() {
  static const CHT Strings[64][4] = {
      {'N', 'I', 'L', NIL},  //< 00
      {'I', 'U', 'A', NIL},  //< 01
      {'I', 'S', 'A', NIL},  //< 02
      {'C', 'H', 'A', NIL},  //< 03
      {'F', 'P', 'B', NIL},  //< 04
      {'I', 'U', 'B', NIL},  //< 05
      {'I', 'S', 'B', NIL},  //< 06
      {'C', 'H', 'B', NIL},  //< 07
      {'F', 'P', 'C', NIL},  //< 08
      {'I', 'U', 'C', NIL},  //< 09
      {'I', 'S', 'C', NIL},  //< 10
      {'C', 'H', 'C', NIL},  //< 11
      {'F', 'P', 'D', NIL},  //< 12
      {'I', 'U', 'D', NIL},  //< 13
      {'I', 'S', 'D', NIL},  //< 14
      {'T', 'M', 'D', NIL},  //< 15
      {'F', 'P', 'E', NIL},  //< 16
      {'I', 'U', 'E', NIL},  //< 17
      {'I', 'S', 'E', NIL},  //< 18
      {'T', 'M', 'E', NIL},  //< 19
      {'D', 'T', 'A', NIL},  //< 20
      {'D', 'T', 'B', NIL},  //< 21
      {'D', 'T', 'C', NIL},  //< 22
      {'D', 'T', 'D', NIL},  //< 23
      {'D', 'T', 'E', NIL},  //< 24
      {'D', 'T', 'F', NIL},  //< 25
      {'D', 'T', 'G', NIL},  //< 26
      {'D', 'T', 'H', NIL},  //< 27
      {'D', 'T', 'I', NIL},  //< 28
      {'D', 'T', 'J', NIL},  //< 29
      {'D', 'T', 'K', NIL},  //< 30
      {'D', 'T', 'L', NIL},  //< 31
      {'I', 'N', 'V', NIL},  //< 32
  };
  return &Strings[0][0];
}

template<typename CHT = CHR, typename IS = ISW>
const CHT* TATypePODs(IS type) {
  type = (type < 0 || type > ATypePODTotal) ? ATypePODTotal : type;
  return &TATypePODs<CHT>()[type << 2];
}

template<typename CHT = CHR>
const CHT* TATypeVectors() {
  static const CHT Strings[17][4] = {
      {'V', 'H', 'A', NIL},  //< 00
      {'A', 'R', 'A', NIL},  //< 01
      {'S', 'C', 'A', NIL},  //< 02
      {'M', 'A', 'A', NIL},  //< 03
      {'V', 'H', 'B', NIL},  //< 04
      {'A', 'R', 'B', NIL},  //< 05
      {'S', 'C', 'B', NIL},  //< 06
      {'M', 'A', 'B', NIL},  //< 07
      {'V', 'H', 'C', NIL},  //< 08
      {'A', 'R', 'C', NIL},  //< 09
      {'S', 'C', 'C', NIL},  //< 10
      {'M', 'A', 'C', NIL},  //< 11
      {'V', 'H', 'D', NIL},  //< 12
      {'A', 'R', 'D', NIL},  //< 13
      {'S', 'C', 'D', NIL},  //< 14
      {'M', 'A', 'D', NIL},  //< 15
      {'I', 'N', 'V', NIL},  //< 16
  };
  return &Strings[0][0];
}

template<typename CHT = CHR, typename IS = ISW>
const CHT* TATypeVectors(IS value) {
  value = (value < 0 || value > 16) ? 16 : value;
  return &TATypeVectors<CHT>()[value << 2];
}

template<typename CHT = CHR, typename IS = ISW>
const CHT* TATypeVectors(IS size_width_bits, IS vector_type_bits) {
  IS value = (size_width_bits << 2) | vector_type_bits;
  value = (value < 0 || value > 16) ? 16 : value;
  return &TATypeVectors<CHT>()[value << 2];
}

template<typename CHT = CHR>
const CHT* TATypeVectorClasses() {
  static const CHT Strings[5][4] = {
      {'V', 'H', 'T', NIL},  //< 00
      {'A', 'R', 'Y', NIL},  //< 01
      {'S', 'C', 'K', NIL},  //< 02
      {'M', 'T', 'X', NIL},  //< 03
      {'I', 'N', 'V', NIL},  //< 04
  };
  return &Strings[0][0];
}

template<typename CHT = CHR, typename IS = ISW>
const CHT* TATypeVectorClasses(IS value) {
  value = (value < 0 || value > 16) ? 16 : value;
  return &TATypeVectorClasses<CHT>()[value << 2];
}

template<typename CHT = CHR>
const CHT* TATypeModifiers() {
  static const CHT Strings[5][4] = {
      {'P', 'O', 'D', NIL},  //< 00
      {'P', 'T', 'R', NIL},  //< 01
      {'C', 'N', 'S', NIL},  //< 02
      {'P', 'T', 'C', NIL},  //< 03
      {'I', 'N', 'V', NIL},  //< 04
  };
  return &Strings[0][0];
}

template<typename CHT = CHR, typename IS = ISW>
const CHT* TATypeModifiers(IS value) {
  value = (value < 0 || value > 4) ? 4 : value;
  return &TATypeModifiers<CHT>()[value << 2];
}

template<typename CHT = CHR>
const CHT* TATypeMaps() {
  static const CHT Strings[5][4] = {
      {'M', 'A', 'C', NIL},  //< 00
      {'M', 'A', 'D', NIL},  //< 01
      {'I', 'N', 'V', NIL},  //< 04
  };
  return &Strings[0][0];
}

template<typename CHT = CHR, typename IS = ISW>
const CHT* TATypeMaps(IS value) {
  value = (value < 0 || value > 2) ? 2 : value;
  return &TATypeMaps<CHT>()[value << 2];
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template<typename IS = CHR, typename DT = DTB>
constexpr DT CATypeSize() {
  return (sizeof(IS) ==  1) ? _SWA 
       : (sizeof(IS) ==  2) ? _SWB
       : (sizeof(IS) ==  4) ? _SWC
       : (sizeof(IS) ==  8) ? _SWD 
       : (sizeof(IS) == 16) ? _SWE : 0;
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template<typename T, typename DT = DTB>
constexpr DT CATypeSize(DT pod_type) {
  return pod_type | (CATypeSize<T>() << 7);
}

template<typename T, typename DT = DTB>
inline DT TATypeSize(DT pod_type) {
  return pod_type | (CATypeSize<T>() << 7);
}

template<typename IS = ISW>
IS TATypeSizeOf(const void* value, DTB type) {
  if (type < ATypePODTotal)
    return ATypeSizeOfPOD(type);
  // | b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
  // |:-------:|:------:|:-----:|:-----:|:-----:|
  // |   MOD   |   MT   |  SW   |  VT   |  POD  |
  DTB mod = type >> ATypeMODBit0;
  if (mod && 1) return sizeof(void*);
  type ^= mod << ATypeMODBit0;
  DTB mt = type >> ATypeMTBit0;
  type ^= mt << ATypeMTBit0;
  DTB sw = type >> ATypeSWBit0;
  type ^= sw << ATypeSWBit0;
  DTB vt = type >> ATypeVTBit0;
  type ^= vt << ATypeVTBit0;
  if (vt == DTB(0)) {
    IS dez  = IS(sw);
    IS nutz = IS(ATypeSizeOfPOD(type));
    return dez * nutz;
  }
  IS size = 1;
  switch (sw) {
    case 0: return IS(*static_cast<const ISA*>(value));
    case 1: return IS(*static_cast<const ISB*>(value));
    case 2: return IS(*static_cast<const ISC*>(value));
  }
  return IS(*static_cast<const ISD*>(value));
}

template<typename IS = ISW>
IS TATypeSizeOf(void* value, DTB type) {
  return TATypeSizeOf<IS>((const void*)value, type);
}
template<typename IS = ISW>
IS TATypeSizeOf(const void* value_base, IS bytes, DTB type) {
  const IUA* vbase = (const IUA*)value_base;
  return TATypeSizeOf<IS>(vbase + bytes, type);
}
template<typename IS = ISW>
IS TATypeSizeOf(void* value_base, IS bytes, DTB type) {
  const void* vbase = (const void*)value_base;
  return TATypeSizeOf<IS>(vbase, bytes, type);
}

/* Returns the ASCII Type for the given floating-point type FP.
FPB:  4   0b00100   (0b001 << 2) | 0b00
FPC:  8   0b01000   (0b010 << 2) | 0b00
FPD: 12   0b01100   (0b011 << 2) | 0b00
FPE: 16   0b10000   (0b100 << 2) | 0b00
*/
template<typename FP, typename DT = DTB>
constexpr DT CATypeFP() {
  return (CATypeSize<FP, DT>() << 2);
}

/* Returns the ASCII Type for the given unsigned integer type IS.
IUA:  1   0b00001   (0b000 << 2) | 0b01
IUB:  5   0b00101   (0b001 << 2) | 0b01
IUC:  9   0b01001   (0b010 << 2) | 0b01
IUD: 13   0b01101   (0b011 << 2) | 0b01
IUE: 17   0b10001   (0b100 << 2) | 0b01
*/
template<typename IU, typename DT = DTB>
constexpr DT CATypeIU() {
  return (CATypeSize<IU, DT>() << 2) | 1;
}

/* Returns the ASCII Type for the given signed integer type IS.
ISA:  2   0b00010   (0b000 << 2) | 0b10
ISB:  6   0b00110   (0b001 << 2) | 0b10
ISC: 10   0b01010   (0b010 << 2) | 0b10
ISD: 14   0b01110   (0b011 << 2) | 0b10
ISE: 18   0b10010   (0b100 << 2) | 0b10
*/
template<typename IS, typename DT = DTB>
constexpr DT CATypeIS() {
  return (CATypeSize<IS, DT>() << 2) | 2;
}

/* Returns the ASCII Type for the given character type CH.
CHB:  3   0b0011   (0b00 << 2) | 0b11
CHC:  7   0b0111   (0b01 << 2) | 0b11
CHD: 11   0b1011   (0b10 << 2) | 0b11
CHE: 15   0b1111   (0b11 << 2) | 0b11

template<typename CH, typename DT = DTB>
constexpr DT CATypeCH() {
  return (CATypeSize<CH, DT>() << 2) | 3;
} */

/* Extracts the UTF type.
@return 0 if the type is not a stirng type or 1, 2, or 4 if it is. */
inline ISA ATypeTextFormat(DTW type) {
  DTW core_type = type & ATypePODMask;
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

}  //< namespace _

#if SEAM >= SCRIPT2_COUT
#include "Uniprinter.hpp"

#if SEAM == SCRIPT2_COUT
#include "_Debug.hxx"
#else
#include "_Release.hxx"
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
inline DTW AlignmentMask(void* item) { return ALUWordMask; }
inline DTW AlignmentMask(const void* item) { return ALUWordMask; }

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

/* A ROM  for one of the 32 types.
C++11 variadic templates ensure there is only one copy in of the given in ROM.

template<CHA CharA, CHA CharB, CHA CharC>
inline IUC T() {
  return ((IUC)CharA) & (((IUC)CharB) << 8) & (((IUC)CharC) << 16);
}*/

/* Masks off the primary type. */
inline ISA ATypeMaskPOD(DTW value) { return value & 0x1f; }

/* Returns true if the given type is an Array type. */
inline BOL ATypeIsArray(DTW type) { return type >= ATypePODTotal; }

inline ISN ATypeSizeWidthCode(ISN type) { return type >> 6; }

/* Extracts the Map Type. */
inline DTW ATypeMap(DTW core_type, DTW map_type) {
  return core_type | (map_type << (ATypePODBits + 2));
}

inline DTW ATypeMap(DTW core_type, DTW map_type, DTW size_width) {
  return ATypeMap(core_type, map_type) | (size_width << ATypePODBits);
}

inline BOL ATypeIsPOD(DTB type) {
  return !((type >> 5) || ((type & ATypePODMask)));
}

}  //< namespace _

#endif
#endif
