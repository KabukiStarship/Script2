// Copyright Kabuki Starship <kabukistarship.com>.
#include "Types.hpp"
#if SEAM == SCRIPT2_COUT
#include "_Debug.hxx"
#else
#include "_Release.hxx"
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
  //return (type & 3) && (type != 15);
  return type == _CHA || type == _CHB || type == _CHC;
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

// Retrusn the size of an ASCII POD Type 0-31 in bytes.
ISA ATypeSizeOfPOD(DTB type) {
  if (type <= 0) return 0;
  if (type <= _CHA) return 1;
  if (type <= _CHB) return 2;
  if (type <= _CHC) return 4;
  if (type <= _TMD) return 8;
  if (type <= _TME) return 16;
#if USING_CT5
  if (type <= _CT5) return 16;
#endif
#if USING_CT4
  if (type <= _CT4) return 8;
#endif
#if USING_CT3
  if (type <= _CT3) return 4;
#endif
#if USING_CT2
  if (type <= _CT2) return 2;
#endif
  if (type <= 31) return 1;
  return 0;
}

ISW ATypeBytes(const void* value, DTB type) {
  return TATypeSizeOf<ISW>(value, type);
}

ISW ATypeBytes(const void* value_base, ISA bytes, DTB type) {
  return ATypeBytes(TPtr<>(value_base, bytes), type);
}

void* ATypeValueEnd(void* value, DTB type) {
  return TPtr<void>(value, ATypeBytes(value, type));
}

// Returns an array of the customizable POD type sizes.
//const ISA* ATypeCustomSize() {
//  return nullptr;
//}

// Returns an array of the user-defined type alignment masks.
//const ISA* ATypeCustomAlignMask() {
//  return nullptr;
//}

// Returns the custom time alignment mask for the given type.
//ISA ATypeCustomAlignMask(DTA type) {
//  return 0;
//}

/* Converts an ASCII Data Type to Extended Type.
@return If the type isn't an extended type, (type & 0x7fff) * -1. */
DTB ATypeEXT(DTB type) {
  const DTB MOD = type >> ATypeMODBit0;
  type ^= MOD << ATypeMODBit0;
  if (type < _INV || type > ATypeCTXMax) return 0;
  const DTB SW_VT = type >> ATypeVTBit0;
  const DTB POD = type ^ SW_VT << ATypeVTBit0;
  if (SW_VT && !POD) return SW_VT; //< A
  if ((SW_VT & ATypePODMask) == 0) return 0;
  if (POD < _FPC) return 0;
  if (SW_VT < 4) {
    if (POD >= _FPC) return type; //< B
    if (POD < _FPB || SW_VT > 2) return 0;
  }
  if (POD >= _CTE) 
    return ATypeEXTTotal + (((SW_VT - 4) << ATypeVTBit0) | (POD - 16)); //< C
  if (POD >= _CTA) {
    if (SW_VT < 8)
      return ATypeEXTTotal + (((SW_VT - 4) << ATypeVTBit0) | (POD - 12)); //< D
    return ATypeEXTTotal + (((SW_VT - 8) << ATypeVTBit0) | (POD - 12));  //< E
  }
  if (SW_VT < 8) {
    if (POD < _FPD) 
      return ATypeEXTTotal + (((SW_VT - 5) << 8) | (POD - 12)); //< F
    if (POD < _FPC || SW_VT > 5) return 0;
  }
  if (SW_VT < 12) return 16 + (((SW_VT - 5) << 4) | (POD - 12)); //< G
  return POD + 12;  //< H
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
AValue::AValue(ISC item) : type_(_ISC) {
  // @todo I don't know if this is going to be needed. In my mind the compiler
  // will push the word_ onto the program stack because of the *reintpret_cast.
  // This might however get optimized into just storing item. Dissassemble me!
  *TPtr<ISC>(&word_) = item;
}
#else
TypeValue::TypeValue(ISC item) : type_(_ISC), word_(IUW(item)), word_2_(0) {}
#endif

#if CPU_SIZE == CPU_2_BYTE
AValue::AValue(IUC item) : type_(_IUC) {
  *TPtr<IUC>(&word_) = item;
}
#else
TypeValue::TypeValue(IUC item) : type_(_IUC), word_(IUW(item)), word_2_(0) {}
#endif

#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(ISD item) : type_(_ISD), word_(IUW(item)), word_2_(0) {}
#else
AValue::AValue(ISD item) : type_(_ISD) { *TPtr<ISD>(&word_) = item; }
#endif

#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(IUD item) : type_(_IUD), word_(IUW(item)), word_2_(0) {}
#else
AValue::AValue(IUD item) : type_(_IUD) {
  *TPtr<IUD>(&word_) = item;
}

#endif
#if USING_FPC == YES_0
#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(FPC item)
    : type_(_FPC), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FPC item) : type_(_FPC) { *TPtr<FPC>(&word_) = item; }
#endif
#endif

#if USING_FPD == YES_0
#if CPU_SIZE == CPU_8_BYTE
TypeValue::TypeValue(FPD item)
    : type_(_FPD), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FPD item) : type_(_FPD) { *TPtr<FPD>(&word_) = item; }
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

DTW TypeValue::UnicodeFormat() { return ATypeTextFormat(type_); }

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
  type_ = CATypeMap(_STA, _CNS_PTR);
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
