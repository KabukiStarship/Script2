/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_avalue.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#include "t_avalue.h"

#if SEAM == SEAM_SCRIPT2_CORE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1* STRTypes() {
  static const CH1 kStrings[64][4] = {
      {'N', 'I', 'L', NIL},  //< 00
      {'A', 'D', 'R', NIL},  //< 01
      {'S', 'T', 'R', NIL},  //< 02
      {'T', 'K', 'N', NIL},  //< 03
      {'C', 'H', '1', NIL},  //< 04
      {'B', 'N', '1', NIL},  //< 05
      {'S', 'I', '1', NIL},  //< 06
      {'U', 'I', '1', NIL},  //< 07
      {'C', 'H', '2', NIL},  //< 08
      {'B', 'N', '2', NIL},  //< 09
      {'S', 'I', '2', NIL},  //< 10
      {'U', 'I', '2', NIL},  //< 11
      {'F', 'P', '2', NIL},  //< 12
      {'C', 'H', '4', NIL},  //< 13
      {'B', 'N', '4', NIL},  //< 14
      {'S', 'I', '4', NIL},  //< 15
      {'S', 'I', '4', NIL},  //< 16
      {'U', 'I', '4', NIL},  //< 17
      {'F', 'P', '4', NIL},  //< 17
      {'T', 'M', '4', NIL},  //< 18
      {'T', 'M', 'E', NIL},  //< 19
      {'T', 'M', '8', NIL},  //< 20
      {'S', 'I', '8', NIL},  //< 21
      {'U', 'I', '8', NIL},  //< 22
      {'F', 'P', '8', NIL},  //< 23
      {'S', 'I', 'H', NIL},  //< 24
      {'U', 'I', 'H', NIL},  //< 25
      {'F', 'P', 'H', NIL},  //< 26
      {'P', 'T', 'R', NIL},  //< 27
      {'P', 'T', 'C', NIL},  //< 28
      {'O', 'P', 'D', NIL},  //< 29
      {'A', 'J', 'T', NIL},  //< 30
      {'V', 'A', 'L', NIL},  //< 31
  };
  return &kStrings[0][0];
}

const SI1* TypeBasicSizes() {
  static const SI1 kSizes[] = {
      -1,               //< 00. NIL
      -1,               //< 01. ADR
      -1,               //< 02. STR
      -1,               //< 03. TKN
      1,                //< 04. CH1
      1,                //< 05. SI1
      1,                //< 06. UI1
      2,                //< 08. CH2
      2,                //< 09. SI2
      2,                //< 10. UI2
      2,                //< 12. FP2
      2,                //< 11. BOL
      4,                //< 13. CH4
      4,                //< 15. SI4
      4,                //< 16. UI4
      4,                //< 17. FP4
      4,                //< 18. TM4
      8,                //< 19. TME
      8,                //< 20. TM8
      8,                //< 21. SI8
      8,                //< 22. UI8
      8,                //< 23. FP8
      16,               //< 24. SIH
      16,               //< 25. UIH
      16,               //< 26. FPH
      sizeof(UIW),      //< 27. SIV
      sizeof(UIW),      //< 27. UIV
      sizeof(UIW),      //< 27. PTC
      sizeof(UIW),      //< 28. PTR
      sizeof(UIW),      //< 29. OPD
      2 * sizeof(UIW),  //< 30. AJT
      3 * sizeof(UIW),  //< 31. VAL
  };
  return kSizes;
}

DTW TypeSizeOf(DTW type) {
  type &= kTypeCountMask;
  if (type >= kVAL) return -1;
  return (DTW)TypeBasicSizes()[type];
}

const SI1* TypeAlignmentMasks() {
  static const SI1 kSizes[] = {
      0,                //< 00. NIL
      0,                //< 01. ADR
      0,                //< 02. STR
      0,                //< 03. TKN
      0,                //< 04. CH1
      0,                //< 05. SI1
      0,                //< 06. UI1
      1,                //< 07. CH2
      1,                //< 08. SI2
      1,                //< 09. UI2
      1,                //< 10. FP2
      sizeof(SIN) - 1,  //< 11. BOL
      sizeof(SIN) - 1,  //< 12. CH4
      sizeof(SIN) - 1,  //< 13. SI4
      sizeof(SIN) - 1,  //< 14. UI4
      sizeof(SIN) - 1,  //< 15. FP4
      sizeof(SIN) - 1,  //< 16. TM4
      sizeof(SIN) - 1,  //< 17. TME
      kWordLSbMask,     //< 18. TM8
      kWordLSbMask,     //< 19. SI8
      kWordLSbMask,     //< 20. UI8
      kWordLSbMask,     //< 21. FP8
      kWordLSbMask,     //< 22. SIH
      kWordLSbMask,     //< 23. UIH
      kWordLSbMask,     //< 24. FPH
      kWordLSbMask,     //< 25. SIV
      kWordLSbMask,     //< 26. UIV
      kWordLSbMask,     //< 27. PTC
      kWordLSbMask,     //< 28. PTR
      kWordLSbMask,     //< 29. OPD
      kWordLSbMask,     //< 30. AJT
      kWordLSbMask,     //< 31. VAL
  };
  return kSizes;
}

SI1 TypePODSize(DTW index) {
  SIN invalid = kINV;
  if (index < 0 || index > invalid) return -1;
  return TypeBasicSizes()[index];
}

BOL TypeIsSupported(DTW type) { return true; }

const CH1* STRType(DTW index) {
  if (index < 0 || index >= kINV) index = 32;
  const CH1* strings = STRTypes();
  return strings + (index << 2);
}

DT2 TypeWidthBits(DTW value) { return value >> 12; }

SI1 TypeTextFormat(DTW type) {
  DTW core_type = type & kTypeCountMask;
  if (core_type == 0) return -1;  //< then core_type < 32
  if (core_type <= kST3) {
    if (core_type == kNIL) return -1;
    return type;
  }
  if (core_type == type) return -1;  //< then core_type < 32
  if (core_type == kCH1) return 1;
  if (core_type == kCH2) return 2;
  if (core_type <= kCH4) return 3;
  return -1;
}

SI1 TypeBase(DTW value) { return value & 0x1f; }

BOL TypeIsArray(DTW type) { return type >= kTypeCount; }

inline SIN TypeSizeWidthCode(SIN type) { return type >> 6; }

DTW TypeMap(DTW core_type, DTW map_type) {
  return core_type | (map_type << (kTypeBitCount + 2));
}

DTW TypeMap(DTW core_type, DTW map_type, DTW size_width) {
  return TypeMap(core_type, map_type) | (size_width << kTypeBitCount);
}

AValue::AValue() : type_(kNIL) { value_[0] = 0; }

AValue::AValue(UIW item, DTW type) : type_(type) {
  *reinterpret_cast<DTW*>(value_) = item;
}

AValue::AValue(void* item) : type_(kPTR) {
  *reinterpret_cast<void**>(value_) = item;
}

AValue::AValue(const void* item) : type_(kPTC) {
  *reinterpret_cast<const void**>(value_) = item;
}

#if USING_UTF8 == YES_0
AValue::AValue(CH1 item) : type_(kCH1) {
  *reinterpret_cast<CH1*>(value_) = item;
}

AValue::AValue(const CH1* item) : type_(kST1) {
  *reinterpret_cast<const CH1**>(value_) = item;
}
#endif

#if USING_UTF16 == YES_0
AValue::AValue(CH2 item) : type_(kCH2) {
  *reinterpret_cast<CH2*>(value_) = item;
}

AValue::AValue(const CH2* item) : type_(kST2) {
  *reinterpret_cast<const CH2**>(value_) = item;
}
#endif

#if USING_UTF32 == YES_0
AValue::AValue(CH4 item) : type_(kCH4) {
  *reinterpret_cast<CH4*>(value_) = item;
}

AValue::AValue(const CH4* item) : type_(kST3) {
  *reinterpret_cast<const CH4**>(value_) = item;
}
#endif

AValue::AValue(SI1 item) : type_(kSI1) {
  *reinterpret_cast<SI1*>(value_) = item;
}

AValue::AValue(UI1 item) : type_(kUI1) {
  *reinterpret_cast<UI1*>(value_) = item;
}

AValue::AValue(SI2 item) : type_(kSI2) {
  *reinterpret_cast<SI2*>(value_) = item;
}

AValue::AValue(UI2 item) : type_(kUI2) {
  *reinterpret_cast<UI2*>(value_) = item;
}

AValue::AValue(SI4 item) : type_(kSI4) {
  *reinterpret_cast<SI4*>(value_) = item;
}

AValue::AValue(UI4 item) : type_(kUI4) {
  *reinterpret_cast<UI4*>(value_) = item;
}

AValue::AValue(SI8 item) : type_(kSI8) {
  *reinterpret_cast<SI8*>(value_) = item;
}

AValue::AValue(UI8 item) : type_(kUI8) {
  *reinterpret_cast<UI8*>(value_) = item;
}

#if USING_FP4 == YES_0
AValue::AValue(FP4 item) : type_(kFP4) {
  *reinterpret_cast<FP4*>(value_) = item;
}
#endif

#if USING_FP8 == YES_0
AValue::AValue(FP8 item) : type_(kFP8) {
  *reinterpret_cast<FP8*>(value_) = item;
}
#endif

DTW AValue::Type() { return type_; }

DTW AValue::UnicodeFormat() { return TypeTextFormat(type_); }

void* AValue::Value() { return value_; }

void* AValue::Ptr() { return reinterpret_cast<void*>(value_[0]); }

const CH1* AValue::ST1() { return reinterpret_cast<const CH1*>(value_[0]); }

const CH2* AValue::ST2() { return reinterpret_cast<const CH2*>(value_[0]); }

const CH4* AValue::ST3() { return reinterpret_cast<const CH4*>(value_[0]); }

UIW AValue::Word() { return value_[0]; }

void AValue::SetNIL() { type_ = kNIL; }

void AValue::SetNIL(UIW value) {
  type_ = kNIL;
  value_[0] = value;
}

#if USING_UTF8 == YES_0
void AValue::Set(CH1 item) {
  type_ = kCH1;
  value_[0] = (UIW)item;
}

void AValue::Set(const CH1* item) {
  type_ = TTypeMap<kST1, kPTC>();
  value_[0] = reinterpret_cast<UIW>(item);
}
#endif
#if USING_UTF16 == YES_0
void AValue::Set(CH2 item) {
  type_ = kCH2;
  value_[0] = (UIW)item;
}

void AValue::Set(const CH2* item) {
  type_ = kST2;
  value_[0] = reinterpret_cast<UIW>(item);
}

#endif
#if USING_UTF32 == YES_0
void AValue::Set(CH4 item) {
  type_ = kCH4;
  value_[0] = (UIW)item;
}

void AValue::Set(const CH4* item) {
  type_ = kST3;
  value_[0] = reinterpret_cast<UIW>(item);
}
#endif

void AValue::Set(SI1 item) {
  type_ = kSI1;
  value_[0] = (UIW)item;
}

void AValue::Set(UI1 item) {
  type_ = kUI1;
  value_[0] = (UIW)item;
}

void AValue::Set(SI2 item) {
  type_ = kSI2;
  value_[0] = (UIW)item;
}

void AValue::Set(UI2 item) {
  type_ = kUI2;
  value_[0] = (UIW)item;
}

void AValue::Set(BOL item) {
  type_ = kBOL;
  value_[0] = (UIW)item;
}

void AValue::Set(SI4 item) {
  type_ = kSI4;
  value_[0] = (UIW)item;
}

void AValue::Set(UI4 item) {
  type_ = kUI4;
  value_[0] = (UIW)item;
}

void AValue::Set(SI8 item) {
  type_ = kSI8;
  value_[0] = (UIW)item;
}

void AValue::Set(UI8 item) {
  type_ = kUI8;
  value_[0] = (UIW)item;
}

#if USING_FP4 == YES_0
void AValue::Set(FP4 item) {
  type_ = kFP4;
  value_[0] = (UIW)item;
}

#endif
#if USING_FP8 == YES_0
void AValue::Set(FP8 item) {
  type_ = kFP8;
  value_[0] = (UIW)item;
}
#endif

/*
template <typename Char, typename UI>
inline CH1* WriteStrand(CH1* begin, CH1* stop, const void* value) {
  begin = AlignUpPointer<CH1>(begin);
  if (stop - begin < 2 * sizeof(UI)) return nullptr;
  const Char* source = reinterpret_cast<const Char*>(value);
  UI length = TSTRLength<UI, Char>(source);
  UI* target = reinterpret_cast<UI*>(begin);
  *target++ = length;
  return SocketCopy(target, stop, value, length + sizeof(Char));
}*/

/*
template <typename SI>
inline CH1* TWriteObj(CH1* begin, CH1* stop, const void* value) {
  SI* target = TAlignUp<SI>(begin);
  const SI* source = reinterpret_cast<const SI*>(value);
  SI size = *source++;
  if (!TSizeIsValid<SI>(size)) return nullptr;
  *target++ = size;
  return SocketCopy(target, stop, value, size - sizeof(SI));
}

CH1* Write(CH1* begin, CH1* stop, SIN type, const void* value) {
  // Algorithm:
  // 1.) Determine type.
  // 2.) Align begin pointer to type width.
  // 3.) Check for enough room in begin-stop socket.
  // 4.) Use SocketCopy to copy the data into the given begin-stop socket.

  if (!begin || begin >= stop || !value || !TypeIsSupported(type)) return
nullptr;

  if (type <= kUI1) {
    CH1* target_1 = reinterpret_cast<CH1*>(begin);
    *target_1++ = *reinterpret_cast<const CH1*>(value);
    return target_1;
  }
  if (type <= kBOL) {
    CH2* target_2 = TAlignUp2<CH2>(begin);
    *target_2++ = *reinterpret_cast<const CH2*>(value);
    return reinterpret_cast<CH1*>(target_2);
  }
  if (type <= kTM4) {
    CH4* target_4 = TAlignUp<CH4>(begin, 3);
    *target_4++ = *reinterpret_cast<const CH4*>(value);
    return reinterpret_cast<CH1*>(target_4);
  }
  if (type <= kFPH) {
    UI8* target_8 = TAlignUp<UI8>(begin, 7);
    const UI8* source_8 = reinterpret_cast<const UI8*>(value);
    *target_8++ = *source_8++;
    if (type == kFPH) {
      *target_8++ = *source_8;
      return reinterpret_cast<CH1*>(target_8);
    }
    return reinterpret_cast<CH1*>(target_8);
  }
  if (TypeIsStrand(type)) {
    switch (type >> 6) {
      case 0:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 1:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 2:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 3:
        return reinterpret_cast<CH1*>(TPrint<CH2>(
            reinterpret_cast<CH2*>(begin), reinterpret_cast<CH2*>(stop),
            reinterpret_cast<const CH2*>(value)));
      case 4:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 5:
        return reinterpret_cast<CH1*>(TPrint<CH2>(
            reinterpret_cast<CH2*>(begin), reinterpret_cast<CH2*>(stop),
            reinterpret_cast<const CH2*>(value)));
      case 6:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 7:
        return reinterpret_cast<CH1*>(TPrint<CH2>(
            reinterpret_cast<CH2*>(begin), reinterpret_cast<CH2*>(stop),
            reinterpret_cast<const CH2*>(value)));
    }
  }
  CH1 array_type = type >> 6;
  switch (array_type) {
    case 0:
      return TWriteObj<UI1>(begin, stop, value);
    case 1:
      return TWriteObj<UI2>(begin, stop, value);
    case 2:
      return TWriteObj<UI4>(begin, stop, value);
    case 3:
      return TWriteObj<UI8>(begin, stop, value);
  }
  return nullptr;
}*/

}  // namespace _
