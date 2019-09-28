/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /typevalue.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#include "avalue.hpp"

#if SEAM == SCRIPT2_UNIPRINTER
#include "_debug.inl"
#else
#include "_release.inl"
#endif

namespace _ {

const CH1* STRTypes() {
  static const CH1 kStrings[64][4] = {
      {'N', 'I', 'L', NIL},  //< 00
      {'S', 'T', '1', NIL},  //< 01
      {'S', 'T', '2', NIL},  //< 02
      {'S', 'T', '3', NIL},  //< 03
      {'C', 'H', '1', NIL},  //< 04
      {'S', 'I', '1', NIL},  //< 05
      {'U', 'I', '1', NIL},  //< 06
      {'C', 'H', '2', NIL},  //< 07
      {'S', 'I', '2', NIL},  //< 08
      {'U', 'I', '2', NIL},  //< 09
      {'F', 'P', '2', NIL},  //< 10
      {'B', 'O', '2', NIL},  //< 11
      {'C', 'H', '4', NIL},  //< 12
      {'S', 'I', '4', NIL},  //< 13
      {'U', 'I', '4', NIL},  //< 14
      {'F', 'P', '4', NIL},  //< 15
      {'B', 'O', '4', NIL},  //< 16
      {'T', 'M', '4', NIL},  //< 17
      {'T', 'M', 'E', NIL},  //< 18
      {'T', 'M', '8', NIL},  //< 19
      {'S', 'I', '8', NIL},  //< 20
      {'U', 'I', '8', NIL},  //< 21
      {'F', 'P', '8', NIL},  //< 22
      {'S', 'I', 'H', NIL},  //< 23
      {'U', 'I', 'H', NIL},  //< 24
      {'F', 'P', 'H', NIL},  //< 25
      {'P', 'D', 'A', NIL},  //< 26
      {'P', 'D', 'B', NIL},  //< 27
      {'P', 'D', 'C', NIL},  //< 28
      {'P', 'D', 'D', NIL},  //< 29
      {'P', 'D', 'E', NIL},  //< 30
      {'P', 'D', 'F', NIL},  //< 31
  };
  return &kStrings[0][0];
}

const CH1* STRTrue() { return "true"; }
const CH1* STRFalse() { return "false"; }

TypeValue::TypeValue() : type_(kNIL), word_(0), word_2_(0) {}
TypeValue::TypeValue(void* item) : type_(kPTR), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(const void* item)
    : type_(kCNS_PTR), word_(UIW(item)), word_2_(0) {}
#if USING_UTF8 == YES_0
TypeValue::TypeValue(CH1 item) : type_(kCH1), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(const CH1* item)
    : type_(kST1), word_(UIW(item)), word_2_(0) {}
#endif
#if USING_UTF16 == YES_0
TypeValue::TypeValue(CH2 item) : type_(kCH2), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(const CH2* item)
    : type_(kST2), word_(UIW(item)), word_2_(0) {}
#endif
#if USING_UTF32 == YES_0
TypeValue::TypeValue(CH4 item) : type_(kCH4), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(const CH4* item)
    : type_(kST3), word_(UIW(item)), word_2_(0) {}
#endif
TypeValue::TypeValue(SI1 item) : type_(kSI1), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(UI1 item) : type_(kUI1), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(SI2 item) : type_(kSI2), word_(UIW(item)), word_2_(0) {}
TypeValue::TypeValue(UI2 item) : type_(kUI2), word_(UIW(item)), word_2_(0) {}
#if ALU_SIZE == ALU_16_BIT
AValue::AValue(SI4 item) : type_(kSI4) {
  // @todo I don't know if this is going to be needed. In my mind the compiler
  // will push the word_ onto the program stack because of the *reintpret_cast.
  // This might however get optimized into just storing item. Dissassemble me!
  *reinterpret_cast<SI4*>(&word_) = item;
}
#else
TypeValue::TypeValue(SI4 item) : type_(kSI4), word_(UIW(item)), word_2_(0) {}
#endif

#if ALU_SIZE == ALU_16_BIT
AValue::AValue(UI4 item) : type_(kUI4) {
  *reinterpret_cast<UI4*>(&word_) = item;
}
#else
TypeValue::TypeValue(UI4 item) : type_(kUI4), word_(UIW(item)), word_2_(0) {}
#endif

#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(SI8 item) : type_(kSI8), word_(UIW(item)), word_2_(0) {}
#else
AValue::AValue(SI8 item) : type_(kSI8) {
  *reinterpret_cast<SI8*>(&word_) = item;
}
#endif

#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(UI8 item) : type_(kUI8), word_(UIW(item)), word_2_(0) {}
#else
AValue::AValue(UI8 item) : type_(kUI8) {
  *reinterpret_cast<UI8*>(&word_) = item;
}

#endif
#if USING_FP4 == YES_0
#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(FP4 item)
    : type_(kFP4), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FP4 item) : type_(kFP4) {
  *reinterpret_cast<FP4*>(&word_) = item;
}
#endif
#endif

#if USING_FP8 == YES_0
#if ALU_SIZE == ALU_64_BIT
TypeValue::TypeValue(FP8 item)
    : type_(kFP8), word_(ToUnsigned(item)), word_2_(0) {}
#else
AValue::AValue(FP8 item) : type_(kFP8) {
  *reinterpret_cast<FP8*>(&word_) = item;
}
#endif
#endif

TypeValue::TypeValue(const void* item, DTW type) : type_(type), word_2_(0) {
  DTW pod_type = type & kTypePODMask;
  if (type != pod_type) {
    word_ = reinterpret_cast<UIW>(item);
  } else if (pod_type <= 7) {
    word_ = TGet<UI1>(item);
  } else if (pod_type <= 15) {
    word_ = TGet<UI2>(item);
  } else if (pod_type <= 15) {
    word_ = TGet<UI4>(item);
  } else {
#if ALU_SIZE != ALU_16_BIT
    UI8* destination = reinterpret_cast<UI8*>(WordPTR());
    const UI8* source = reinterpret_cast<const UI8*>(item);
    *destination = *source;
    if (pod_type >= kSIH) {
      ++destination;
      ++source;
      *destination = *source;
    }
#else
    word_ = UIW(item);
#endif
  }
}

DTW TypeValue::Type() { return type_; }

DTW TypeValue::UnicodeFormat() { return TypeTextFormat(type_); }

void* TypeValue::WordPTR() { return &word_; }

void* TypeValue::ToPTR() { return reinterpret_cast<void*>(word_); }
CH1* TypeValue::ToST1() { return reinterpret_cast<CH1*>(word_); }
CH2* TypeValue::ToST2() { return reinterpret_cast<CH2*>(word_); }
CH4* TypeValue::ToST3() { return reinterpret_cast<CH4*>(word_); }
UI1 TypeValue::ToUI1() { return UI1(word_); }
UI2 TypeValue::ToUI2() { return UI2(word_); }
UIN TypeValue::ToUIN() { return UIN(word_); }
UI4 TypeValue::ToUI4() {
#if ALU_SIZE == ALU_16_BIT
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *reinterpret_cast<UI4*>(&word_);
#else
  return UI4(word_);
#endif
}
UI8 TypeValue::ToUI8() {
#if ALU_SIZE == ALU_64_BIT
  return word_;
#else
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *reinterpret_cast<UI8*>(&word_);
#endif
}

UIW TypeValue::Word() { return word_; }
UIW TypeValue::Word2() { return word_2_; }

void TypeValue::SetWord(UIW value) { word_ = value; }
void TypeValue::SetWord2(UIW value) { word_2_ = value; }
void TypeValue::SetNIL() { type_ = word_ = kNIL; }
void TypeValue::SetNIL(UIW value) {
  type_ = kNIL;
  word_ = value;
}
#if USING_UTF8 == YES_0
void TypeValue::Set(CH1 item) {
  type_ = kCH1;
  word_ = UIW(item);
}
void TypeValue::Set(const CH1* item) {
  type_ = CTypeMap(kST1, kCNS_PTR);
  word_ = reinterpret_cast<UIW>(item);
}
#endif
#if USING_UTF16 == YES_0
void TypeValue::Set(CH2 item) {
  type_ = kCH2;
  word_ = UIW(item);
}
void TypeValue::Set(const CH2* item) {
  type_ = kST2;
  word_ = reinterpret_cast<UIW>(item);
}
#endif
#if USING_UTF32 == YES_0
void TypeValue::Set(CH4 item) {
  type_ = kCH4;
  word_ = UIW(item);
}
void TypeValue::Set(const CH4* item) {
  type_ = kST3;
  word_ = reinterpret_cast<UIW>(item);
}
#endif
void TypeValue::Set(SI1 item) {
  type_ = kSI1;
  word_ = UIW(item);
}
void TypeValue::Set(UI1 item) {
  type_ = kUI1;
  word_ = UIW(item);
}
void TypeValue::Set(SI2 item) {
  type_ = kSI2;
  word_ = UIW(item);
}
void TypeValue::Set(UI2 item) {
  type_ = kUI2;
  word_ = UIW(item);
}
void TypeValue::Set(BOL item) {
  type_ = kBOL;
  word_ = UIW(item);
}
void TypeValue::Set(SI4 item) {
  type_ = kSI4;
  word_ = UIW(item);
}
void TypeValue::Set(UI4 item) {
  type_ = kUI4;
  word_ = UIW(item);
}
void TypeValue::Set(SI8 item) {
  type_ = kSI8;
  word_ = UIW(item);
}
void TypeValue::Set(UI8 item) {
  type_ = kUI8;
  word_ = UIW(item);
}
#if USING_FP4 == YES_0
void TypeValue::Set(FP4 item) {
  type_ = kFP4;
  word_ = UIW(item);
}
#endif
#if USING_FP8 == YES_0
void TypeValue::Set(FP8 item) {
  type_ = kFP8;
  word_ = UIW(item);
}
#endif

AType::AType(DTW type) : type(type) {}

}  // namespace _
