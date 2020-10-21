/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /TypeValue.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Config.h>

#include "TypeValue.hpp"

#if SEAM == SCRIPT2_CORE
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif

namespace _ {

const CHA* STRTypes() {
  static const CHA kStrings[64][4] = {
      {'N', 'I', 'L', NIL},  //< 00
      {'C', 'H', 'A', NIL},  //< 01
      {'I', 'S', 'A', NIL},  //< 02
      {'I', 'U', 'A', NIL},  //< 03
      {'C', 'H', 'B', NIL},  //< 04
      {'I', 'S', 'B', NIL},  //< 05
      {'I', 'U', 'B', NIL},  //< 06
      {'F', 'P', 'B', NIL},  //< 07
      {'B', 'O', 'L', NIL},  //< 08
      {'C', 'H', 'C', NIL},  //< 09
      {'I', 'S', 'C', NIL},  //< 10
      {'I', 'U', 'C', NIL},  //< 11
      {'F', 'P', 'C', NIL},  //< 12
      {'T', 'M', 'E', NIL},  //< 13
      {'I', 'S', 'D', NIL},  //< 14
      {'I', 'U', 'D', NIL},  //< 15
      {'F', 'P', 'D', NIL},  //< 16
      {'I', 'S', 'E', NIL},  //< 17
      {'I', 'U', 'E', NIL},  //< 18
      {'F', 'P', 'E', NIL},  //< 19
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
  };
  return &kStrings[0][0];
}

const CHA* STRTrue() { return "true"; }
const CHA* STRFalse() { return "false"; }

Typef TypefOf() {
  Typef typef;
  typef.type = 0;
  typef.string = nullptr;
  return typef;
}

TypeValue::TypeValue() : type_(cNIL), word_(0), word_2_(0) {}
TypeValue::TypeValue(void* item) : type_(cPTR), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const void* item)
    : type_(cCNS_PTR), word_(IUW(item)), word_2_(0) {}
#if USING_UTF8 == YES_0
TypeValue::TypeValue(CHA item) : type_(cCHA), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const CHA* item)
    : type_(cSTA), word_(IUW(item)), word_2_(0) {}
#endif
#if USING_UTF16 == YES_0
TypeValue::TypeValue(CHB item) : type_(cCHB), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const CHB* item)
    : type_(cSTB), word_(IUW(item)), word_2_(0) {}
#endif
#if USING_UTF32 == YES_0
TypeValue::TypeValue(CHC item) : type_(cCHC), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(const CHC* item)
    : type_(cSTC), word_(IUW(item)), word_2_(0) {}
#endif
TypeValue::TypeValue(ISA item) : type_(cISA), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(IUA item) : type_(cIUA), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(ISB item) : type_(cISB), word_(IUW(item)), word_2_(0) {}
TypeValue::TypeValue(IUB item) : type_(cIUB), word_(IUW(item)), word_2_(0) {}
#if ALU_SIZE == ALU_16_BIT
AValue::AValue(ISC item) : type_(cISC) {
  // @todo I don't know if this is going to be needed. In my mind the compiler
  // will push the word_ onto the program stack because of the *reintpret_cast.
  // This might however get optimized into just storing item. Dissassemble me!
  *reinterpret_cast<ISC*>(&word_) = item;
}
#else
TypeValue::TypeValue(ISC item) : type_(cISC), word_(IUW(item)), word_2_(0) {}
#endif

#if ALU_SIZE == ALU_16_BIT
AValue::AValue(IUC item) : type_(cIUC) {
  *reinterpret_cast<IUC*>(&word_) = item;
}
#else
TypeValue::TypeValue(IUC item) : type_(cIUC), word_(IUW(item)), word_2_(0) {}
#endif

#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(ISD item) : type_(cISD), word_(IUW(item)), word_2_(0) {}
#else
AValue::AValue(ISD item) : type_(cISD) {
  *reinterpret_cast<ISD*>(&word_) = item;
}
#endif

#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(IUD item) : type_(cIUD), word_(IUW(item)), word_2_(0) {}
#else
AValue::AValue(IUD item) : type_(cIUD) {
  *reinterpret_cast<IUD*>(&word_) = item;
}

#endif
#if USING_FPC == YES_0
#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(FPC item)
    : type_(cFPC), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FPC item) : type_(cFPC) {
  *reinterpret_cast<FPC*>(&word_) = item;
}
#endif
#endif

#if USING_FPD == YES_0
#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(FPD item)
    : type_(cFPD), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FPD item) : type_(cFPD) {
  *reinterpret_cast<FPD*>(&word_) = item;
}
#endif
#endif

TypeValue::TypeValue(const void* item, DTW type) : type_(type), word_2_(0) {
  DTW pod_type = type & cTypePODMask;
  if (type != pod_type) {
    word_ = reinterpret_cast<IUW>(item);
  } else if (pod_type <= 7) {
    word_ = TGet<IUA>(item);
  } else if (pod_type <= 15) {
    word_ = TGet<IUB>(item);
  } else if (pod_type <= 15) {
    word_ = TGet<IUC>(item);
  } else {
#if ALU_SIZE != ALU_16_BIT
    IUD* destination = reinterpret_cast<IUD*>(WordPTR());
    const IUD* source = reinterpret_cast<const IUD*>(item);
    *destination = *source;
    if (pod_type >= cISE) {
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

void* TypeValue::ToPTR() { return reinterpret_cast<void*>(word_); }
CHA* TypeValue::ToSTA() { return reinterpret_cast<CHA*>(word_); }
CHB* TypeValue::ToSTB() { return reinterpret_cast<CHB*>(word_); }
CHC* TypeValue::ToSTC() { return reinterpret_cast<CHC*>(word_); }
IUA TypeValue::ToUIA() { return IUA(word_); }
IUB TypeValue::ToUI2() { return IUB(word_); }
IUN TypeValue::ToUIN() { return IUN(word_); }
IUC TypeValue::ToUI4() {
#if ALU_SIZE == ALU_16_BIT
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *reinterpret_cast<IUC*>(&word_);
#else
  return IUC(word_);
#endif
}
IUD TypeValue::ToUI8() {
#if ALU_SIZE == ALU_64_BIT
  return word_;
#else
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *reinterpret_cast<IUD*>(&word_);
#endif
}

IUW TypeValue::Word() { return word_; }
IUW TypeValue::Word2() { return word_2_; }

void TypeValue::SetWord(IUW value) { word_ = value; }
void TypeValue::SetWord2(IUW value) { word_2_ = value; }
void TypeValue::SetNIL() { type_ = word_ = cNIL; }
void TypeValue::SetNIL(IUW value) {
  type_ = cNIL;
  word_ = value;
}
#if USING_UTF8 == YES_0
void TypeValue::Set(CHA item) {
  type_ = cCHA;
  word_ = IUW(item);
}
void TypeValue::Set(const CHA* item) {
  type_ = CTypeMap(cSTA, cCNS_PTR);
  word_ = reinterpret_cast<IUW>(item);
}
#endif
#if USING_UTF16 == YES_0
void TypeValue::Set(CHB item) {
  type_ = cCHB;
  word_ = IUW(item);
}
void TypeValue::Set(const CHB* item) {
  type_ = cSTB;
  word_ = reinterpret_cast<IUW>(item);
}
#endif
#if USING_UTF32 == YES_0
void TypeValue::Set(CHC item) {
  type_ = cCHC;
  word_ = IUW(item);
}
void TypeValue::Set(const CHC* item) {
  type_ = cSTC;
  word_ = reinterpret_cast<IUW>(item);
}
#endif
void TypeValue::Set(ISA item) {
  type_ = cISA;
  word_ = IUW(item);
}
void TypeValue::Set(IUA item) {
  type_ = cIUA;
  word_ = IUW(item);
}
void TypeValue::Set(ISB item) {
  type_ = cISB;
  word_ = IUW(item);
}
void TypeValue::Set(IUB item) {
  type_ = cIUB;
  word_ = IUW(item);
}
void TypeValue::Set(BOL item) {
  type_ = cBOL;
  word_ = IUW(item);
}
void TypeValue::Set(ISC item) {
  type_ = cISC;
  word_ = IUW(item);
}
void TypeValue::Set(IUC item) {
  type_ = cIUC;
  word_ = IUW(item);
}
void TypeValue::Set(ISD item) {
  type_ = cISD;
  word_ = IUW(item);
}
void TypeValue::Set(IUD item) {
  type_ = cIUD;
  word_ = IUW(item);
}
#if USING_FPC == YES_0
void TypeValue::Set(FPC item) {
  type_ = cFPC;
  word_ = IUW(item);
}
#endif
#if USING_FPD == YES_0
void TypeValue::Set(FPD item) {
  type_ = cFPD;
  word_ = IUW(item);
}
#endif

}  // namespace _
