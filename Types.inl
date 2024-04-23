/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Types.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Types.hpp"
#if SEAM == SCRIPT2_COUT
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif
namespace _ {

DTB ATypePack(DTB pod, DTB vt) {
  return pod | vt << ATypeVTBit0;
}

DTB ATypePack(DTB pod, DTB vt, DTB sw) {
  return pod | vt << ATypeVTBit0 | sw << ATypeSWBit0;
}

DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt) {
  return pod | vt << ATypeVTBit0 | sw << ATypeSWBit0 | mt << ATypeMTBit0;
}

DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt, DTB mod) {
  return pod | vt << ATypeVTBit0 | sw << ATypeSWBit0 | mt << ATypeMTBit0 |
         mod << ATypeMODBit0;
}

BOL ATypeIsCH(DTB type) {
  // CHA: 3   0b0011
  // CHB: 7   0b0111
  // CHC: 11  0b1011
  return ((type & 3) != 3) && ((type >> 2) <= 2);
}

BOL ATypeVTBits(DTB type) {
  //| b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
  //|:-------:|:------:|:-----:|:-----:|:-----:|
  //|   MOD   |   MT   |  SW   |  VT   |  POD  |
  const DTB mask = 3,
        VT = (type >> ATypeVTBit0) & mask,
        MT = (type >> ATypeMTBit0) & mask;
  return (VT != _ARY || MT != 0) ? -1 : VT;
}

const ISA* ATypeCustomSize() {
  static const ISA custom_sizes[13] = {
    BOLSizeBits,
    DTASize,
    DTBSize,
    DTCSize,
    DTDSize,
    DTESize,
    DTFSize,
    DTGSize,
    DTHSize,
    DTISize,
    DTJSize,
    DTKSize,
    DTLSize
  };
  return custom_sizes;
}

const ISA* ATypeCustomAlignMask() {
  static const ISA align_masks[] = {
    BOLSizeBits,
    DTAAlignMask,
    DTBAlignMask,
    DTCAlignMask,
    DTDAlignMask,
    DTEAlignMask,
    DTFAlignMask,
    DTGAlignMask,
    DTHAlignMask,
    DTIAlignMask,
    DTJAlignMask,
    DTKAlignMask,
    DTLAlignMask
  };
  return align_masks;
}

ISA ATypeCustomAlignMask(DTA type) {
  if (type < _BOL || type >= ATypePODCount) return sizeof(ISW) - 1;
  return ATypeCustomAlignMask()[type - _BOL];
}

ISA ATypeSizeOfPOD(DTB type) {
  if (type == 0 || type >= ATypePODCount) return 0;
  if (type < _FPB) return 1;
  if (type < _FPC) return 2;
  if (type < _FPD) return 4;
  if (type < _FPE) return 8;
  if (type < _BOL) return 16;
  return ATypeCustomSize()[type - _BOL];
}

ISW ATypeSizeBytes(void* value, DTB type) {
  return TATypeSizeOf<ISW>(value, type);
}

ISW ATypeSizeBytes(void* value_base, ISA size_bytes, DTB type) {
  return ATypeSizeBytes(TPtr<>(value_base, size_bytes), type);
}

void* ATypeValueEnd(void* value, DTB type) {
  return TPtr<void>(value, ATypeSizeBytes(value, type));
}

TypeValue::TypeValue() : type_(_NIL), word_(0), word_2_(0) {}
TypeValue::TypeValue(void* item) : type_(_PTR), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const void* item)
    : type_(_CNS_PTR), word_(IUW(item)), word_2_(0) {}
#if USING_UTF8 == YES_0
TypeValue::TypeValue(CHA item) : type_(_CHA), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const CHA* item)
    : type_(_STA), word_(IUW(item)), word_2_(0) {}
#endif
#if USING_UTF16 == YES_0
TypeValue::TypeValue(CHB item) : type_(_CHB), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const CHB* item)
    : type_(_STB), word_(IUW(item)), word_2_(0) {}
#endif
#if USING_UTF32 == YES_0
TypeValue::TypeValue(CHC item) : type_(_CHC), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const CHC* item)
    : type_(_STC), word_(IUW(item)), word_2_(0) {}
#endif
TypeValue::TypeValue(ISA item) : type_(_ISA), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(IUA item) : type_(_IUA), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(ISB item) : type_(_ISB), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(IUB item) : type_(_IUB), word_(IUW(item)), word_2_(0) {}
#if CPU_SIZE == CPU_2_BYTE
AValue::AValue(ISC item) : type_(cISC) {
  // @todo I don't know if this is going to be needed. In my mind the compiler
  // will push the word_ onto the program stack because of the *reintpret_cast.
  // This might however get optimized into just storing item. Dissassemble me!
  *TPtr<ISC>(&word_) = item;
}
#else
TypeValue::TypeValue(ISC item) : type_(_ISC), word_(IUW(item)), word_2_(0) {}
#endif

#if CPU_SIZE == CPU_2_BYTE
AValue::AValue(IUC item) : type_(cIUC) {
  *TPtr<IUC>(&word_) = item;
}
#else
TypeValue::TypeValue(IUC item) : type_(_IUC), word_(IUW(item)), word_2_(0) {}
#endif

#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(ISD item) : type_(_ISD), word_(IUW(item)), word_2_(0) {}
#else
AValue::AValue(ISD item) : type_(cISD) { *TPtr<ISD>(&word_) = item; }
#endif

#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(IUD item) : type_(_IUD), word_(IUW(item)), word_2_(0) {}
#else
AValue::AValue(IUD item) : type_(cIUD) {
  *TPtr<IUD>(&word_) = item;
}

#endif
#if USING_FPC == YES_0
#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(FPC item)
    : type_(_FPC), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FPC item) : type_(cFPC) { *TPtr<FPC>(&word_) = item; }
#endif
#endif

#if USING_FPD == YES_0
#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(FPD item)
    : type_(_FPD), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FPD item) : type_(cFPD) { *TPtr<FPD>(&word_) = item; }
#endif
#endif

TypeValue::TypeValue(const void* item, DTW type) : type_(type), word_2_(0) {
  DTW pod_type = type & ATypePODMask;
  if (type != pod_type) {
    word_ = IUW(item);
  } else if (pod_type <= 7) {
    word_ = TGet<IUA>(item);
  } else if (pod_type <= 15) {
    word_ = TGet<IUB>(item);
  } else if (pod_type <= 15) {
    word_ = TGet<IUC>(item);
  } else {
#if CPU_SIZE != CPU_2_BYTE
    IUD* destination = TPtr<IUD>(WordPTR());
    const IUD* source = TPtr<const IUD>(item);
    *destination = *source;
    if (pod_type >= _ISE) {
      ++destination;
      ++source;
      *destination = *source;
    }
#else
    word_ = IUW(item);
#endif
  }
}

DTW TypeValue::Type() { return type_; }

DTW TypeValue::UnicodeFormat() { return TypeTextFormat(type_); }

void* TypeValue::WordPTR() { return &word_; }

void* TypeValue::ToPTR() { return TPtr<void>(word_); }
CHA* TypeValue::ToSTA() { return TPtr<CHA>(word_); }
CHB* TypeValue::ToSTB() { return TPtr<CHB>(word_); }
CHC* TypeValue::ToSTC() { return TPtr<CHC>(word_); }
IUA TypeValue::ToIUA() { return IUA(word_); }
IUB TypeValue::ToIUB() { return IUB(word_); }
IUN TypeValue::ToIUN() { return IUN(word_); }
IUC TypeValue::ToIUC() {
#if CPU_SIZE == CPU_2_BYTE
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *TPtr<IUC>(&word_);
#else
  return IUC(word_);
#endif
}
IUD TypeValue::ToUID() {
#if CPU_SIZE == CPU_8_BYTE
  return word_;
#else
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *TPtr<IUD>(&word_);
#endif
}

IUW TypeValue::Word() { return word_; }
IUW TypeValue::Word2() { return word_2_; }

void TypeValue::SetWord(IUW value) { word_ = value; }
void TypeValue::SetWord2(IUW value) { word_2_ = value; }
void TypeValue::SetNIL() { type_ = word_ = _NIL; }
void TypeValue::SetNIL(IUW value) {
  type_ = _NIL;
  word_ = value;
}
#if USING_UTF8 == YES_0
void TypeValue::Set(CHA item) {
  type_ = _CHA;
  word_ = IUW(item);
}
void TypeValue::Set(const CHA* item) {
  type_ = CTypeMap(_STA, _CNS_PTR);
  word_ = IUW(item);
}
#endif
#if USING_UTF16 == YES_0
void TypeValue::Set(CHB item) {
  type_ = _CHB;
  word_ = IUW(item);
}
void TypeValue::Set(const CHB* item) {
  type_ = _STB;
  word_ = IUW(item);
}
#endif
#if USING_UTF32 == YES_0
void TypeValue::Set(CHC item) {
  type_ = _CHC;
  word_ = IUW(item);
}
void TypeValue::Set(const CHC* item) {
  type_ = _STC;
  word_ = IUW(item);
}
#endif
void TypeValue::Set(ISA item) {
  type_ = _ISA;
  word_ = IUW(item);
}
void TypeValue::Set(IUA item) {
  type_ = _IUA;
  word_ = IUW(item);
}
void TypeValue::Set(ISB item) {
  type_ = _ISB;
  word_ = IUW(item);
}
void TypeValue::Set(IUB item) {
  type_ = _IUB;
  word_ = IUW(item);
}
void TypeValue::Set(BOL item) {
  type_ = _BOL;
  word_ = IUW(item);
}
void TypeValue::Set(ISC item) {
  type_ = _ISC;
  word_ = IUW(item);
}
void TypeValue::Set(IUC item) {
  type_ = _IUC;
  word_ = IUW(item);
}
void TypeValue::Set(ISD item) {
  type_ = _ISD;
  word_ = IUW(item);
}
void TypeValue::Set(IUD item) {
  type_ = _IUD;
  word_ = IUW(item);
}
#if USING_FPC == YES_0
void TypeValue::Set(FPC item) {
  type_ = _FPC;
  word_ = IUW(item);
}
#endif
#if USING_FPD == YES_0
void TypeValue::Set(FPD item) {
  type_ = _FPD;
  word_ = IUW(item);
}
#endif

}  //< namespace _
