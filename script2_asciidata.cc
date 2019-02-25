/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_asciidata.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= SCRIPT2_3

#include "t_asciidata.h"

#include "t_socket.h"

#if SEAM == SCRIPT2_3
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1* STRType() {
  static const CH1 kStrings[33][4] = {{'N', 'I', 'L', NIL},   //< 0.
                                      {'S', 'I', '1', NIL},   //< 1.
                                      {'U', 'I', '1', NIL},   //< 2.
                                      {'C', 'H', '1', NIL},   //< 3.
                                      {'S', 'I', '2', NIL},   //< 4.
                                      {'U', 'I', '2', NIL},   //< 5.
                                      {'F', 'P', '2', NIL},   //< 6.
                                      {'C', 'H', '2', NIL},   //< 7.
                                      {'B', 'O', 'L', NIL},   //< 8.
                                      {'S', 'I', '4', NIL},   //< 9.
                                      {'U', 'I', '4', NIL},   //< 10.
                                      {'F', 'L', 'T', NIL},   //< 11.
                                      {'T', 'M', '4', NIL},   //< 12.
                                      {'T', 'M', '8', NIL},   //< 13.
                                      {'S', 'I', '8', NIL},   //< 14.
                                      {'U', 'I', '8', NIL},   //< 15.
                                      {'F', 'P', '8', NIL},   //< 16.
                                      {'S', 'V', '8', NIL},   //< 17.
                                      {'F', 'P', 'H', NIL},   //< 19.
                                      {'U', 'I', 'X', NIL},   //< 20.
                                      {'O', 'B', 'J', NIL},   //< 21.
                                      {'L', 'O', 'M', NIL},   //< 25.
                                      {'B', 'S', 'Q', NIL},   //< 26.
                                      {'E', 'S', 'C', NIL},   //< 27.
                                      {'L', 'S', 'T', NIL},   //< 28.
                                      {'B', 'O', 'K', NIL},   //< 29.
                                      {'D', 'I', 'C', NIL},   //< 30.
                                      {'M', 'A', 'P', NIL},   //< 31.
                                      {NIL, NIL, NIL, NIL},   //< 31.
                                      {'A', 'D', 'R', NIL},   //< 25.
                                      {'S', 'T', 'R', NIL},   //< 24.
                                      {'T', 'K', 'N', NIL}};  //< 25.
  return &kStrings[0][0];
}

const SI1* TypePODSizes() {
  static const SI1 kSizes[] = {
      0,   //< 0.
      1,   //< 1.
      1,   //< 2.
      2,   //< 3.
      2,   //< 4.
      2,   //< 5.
      4,   //< 6.
      4,   //< 7.
      4,   //< 8.
      4,   //< 9.
      8,   //< 10.
      8,   //< 11.
      8,   //< 12.
      16,  //< 13.
      16,  //< 14.
      16,  //< 15.
      16,  //< 16.
      2,   //< 17.
      2,   //< 18.
      4,   //< 19.
      4,   //< 20.
      4,   //< 21.
      8,   //< 22.
      8,   //< 23.
      8,   //< 24.
      8,   //< 25.
      16,  //< 26.
      16,  //< 27.
      16,  //< 28.
      32,  //< 29.
      32,  //< 30.
      32,  //< 31.
      1,   //< 32. CH1
      2,   //< 33.
      4,   //< 34.
      4,   //< 35.
      8,   //< 36.
      8,   //< 37.
      2,   //< 38.
      2,   //< 39.
      4,   //< 40.
      4,   //< 41.
      8,   //< 42.
      8,   //< 43.
      8,   //< 44.
      16,  //< 45.
      32,  //< 46.
      -1,  //< 47. INV
  };
  return kSizes;
}

SI1 TypePODSize(SIN index) {
  if (index < 0 || index >= kINV) return -1;
  return TypePODSizes()[index];
}
const CH1* STRType(SI4 index) {
  if (index < 0 || index >= 31) index = 32;
  const CH1* strings = STRType();
  return strings + (index << 2);
}

BOL TypeIsValid(SI4 type) { return (type >> 7) == 0; }

AsciiValue::AsciiValue(CH1* item) : type(kCH1), value(item) {}

#if USING_UTF16 == YES
AsciiValue::AsciiValue(CH2* item) : type(type), value(item) {}
#endif

#if USING_UTF32 == YES
AsciiValue::AsciiValue(CH4* item) : type(type), value(item) {}
#endif

AsciiValue::AsciiValue(SI1* item) : type(type), value(item) {}

AsciiValue::AsciiValue(UI1* item) : type(type), value(item) {}

AsciiValue::AsciiValue(SI2* item) : type(type), value(item) {}

AsciiValue::AsciiValue(UI2* item) : type(type), value(item) {}

AsciiValue::AsciiValue(SI4* item) : type(type), value(item) {}

AsciiValue::AsciiValue(UI4* item) : type(type), value(item) {}

AsciiValue::AsciiValue(SI8* item) : type(type), value(item) {}

AsciiValue::AsciiValue(UI8* item) : type(type), value(item) {}

#if USING_FP4 == YES
AsciiValue::AsciiValue(FP4* item) : type(type), value(item) {}
#endif
#if USING_FP8 == YES
AsciiValue::AsciiValue(FP8* item) : type(type), value(item) {}
#endif

SI4 TypeFixedSize(SI4 type) {
  static const SI1 kWidths[] = {
      0,   //< kNIL: 0
      1,   //< kSI1: 1
      1,   //< kUI1: 2
      2,   //< kSI2: 3
      2,   //< kUI2: 4
      2,   //< kFP2: 5
      4,   //< kBOL: 6
      4,   //< kSI4: 7
      4,   //< kUI4: 8
      4,   //< kFP4: 9
      4,   //< kTM4: 10
      8,   //< kTM8: 11
      8,   //< kSI8: 12
      8,   //< kUI8: 13
      8,   //< kFP8: 14
      16,  //< kSIH: 15
      16,  //< kUIH: 16
      16,  //< kFPH: 17
  };
  SI4 type_upper_bits = type >> 3;
  type &= 0x1f;
  if (type == kBNM) return ((SI4)2) << type_upper_bits;
  if (type > kOBJ) return -1;
  return kWidths[type];
}

UI1 TypeMask(UI1 value) { return value & 0x1f; }

BOL TypeIsArray(SI4 type) { return type >= kTypeCount; }

BOL TypeIsSet(SI4 type) { return type >= kTypeCount; }

void* TypeAlign(SI4 type, void* value) {
  ASSERT(value);
  if (type == 0) return nullptr;
  if (!TypeIsValid(type)) return nullptr;

  SI4 size = TypeFixedSize(type);
  if (type <= kUI1) return value;
  SI4* value_ptr = reinterpret_cast<SI4*>(value);
#if ALU_SIZE == 2
  if (type <= kFP2) return AlignUpPointer2<>(value);
#else
  if (type <= kBOL) return TAlignUp2<>(value);
#endif
  if (type <= kTM4) return TAlignUp<>(value, 3);
  if (type <= kFPH) return TAlignUp<>(value, 7);

  switch (type >> 6) {
    case 0:
      return value;
    case 1:
      return TAlignUp2<>(value);
    case 2:
      return TAlignUp<>(value, 3);
    case 3:
      return TAlignUp<>(value, 7);
  }
  return 0;
}
/*
template <typename Char, typename UI>
inline CH1* WriteStrand(CH1* begin, CH1* stop, const void* value) {
  begin = AlignUpPointer<CH1>(begin);
  if (stop - begin < 2 * sizeof(UI)) return nullptr;
  const Char* source = reinterpret_cast<const Char*>(value);
  UI length = TStrandLength<UI, Char>(source);
  UI* target = reinterpret_cast<UI*>(begin);
  *target++ = length;
  return SocketCopy(target, stop, value, length + sizeof(Char));
}*/

template <typename SI>
inline CH1* TWriteObj(CH1* begin, CH1* stop, const void* value) {
  SI* target = TAlignUp<SI>(begin);
  const SI* source = reinterpret_cast<const SI*>(value);
  SI size = *source++;
  if (!TSizeIsValid<SI>(size)) return nullptr;
  *target++ = size;
  return SocketCopy(target, stop, value, size - sizeof(SI));
}

CH1* Write(CH1* begin, CH1* stop, SI4 type, const void* value) {
  // Algorithm:
  // 1.) Determine type.
  // 2.) Align begin pointer to type width.
  // 3.) Check for enough room in begin-stop socket.
  // 4.) Use SocketCopy to copy the data into the given begin-stop socket.

  if (!begin || begin >= stop || !value || !TypeIsValid(type)) return nullptr;

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
}

BOL TypeIsObj(SI4 type) {
  if (type < kOBJ) return false;
  return true;
}

BOL TypeIsStrand(SI4 type) {
  type &= 0x1f;
  if (type >= kADR && type <= kTKN) return true;
  return false;
}

BOL TypeIsUTF16(SI4 type) { return (BOL)(type & 0x20); }

inline SI4 TypeSizeWidthCode(SI4 type) { return type >> 6; }

}  // namespace _

#if USING_UTF8
namespace _ {
CH1* Print(CH1* begin, CH1* stop, SI4 type, const void* value) {
  return TPrint<CH1>(begin, stop, type, value);
}
_::UTF1& operator<<(::_::UTF1& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item.type, item.value));
}
}  // namespace _
#endif
#if USING_UTF16
namespace _ {
CH2* Print(CH2* begin, CH2* stop, SI4 type, const void* value) {
  return TPrint<CH2>(begin, stop, type, value);
}
}  // namespace _
_::UTF2& operator<<(::_::UTF2& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item.type, item.value));
}
#endif
#if USING_UTF32
namespace _ {
CH4* Print(CH4* begin, CH4* stop, SI4 type, const void* value) {
  return TPrint<CH4>(begin, stop, type, value);
}
}  // namespace _
_::UTF4& operator<<(::_::UTF4& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item.type, item.value));
}
#endif

#endif  //< #if SEAM >= SCRIPT2_13
