/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_ascii_data.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__13

#include "tasciidata.h"

#include "tsocket.h"

#if SEAM == _0_0_0__13
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

BOL TypeIsValid(SIN type) {
  if (type >= kLST && type <= kDIC ||
      (type >= (kADR + 32) && type <= (kTKN + 32)))
    return false;
  return true;
}

TypeValue::TypeValue(SIN type, const void* value) : type(type), value(value) {
  // Nothing to do here! (:-)-+=<
}

SI4 TypeFixedSize(SI4 type) {
  static const SI1 kWidths[] = {
      0,   //< kNIL: 0
      1,   //< kSI1: 1
      1,   //< kUI1: 2
      2,   //< kSI2: 3
      2,   //< kUI2: 4
      2,   //< kHLF: 5
      4,   //< kBOL: 6
      4,   //< kSI4: 7
      4,   //< kUI4: 8
      4,   //< kFLT: 9
      4,   //< kTMS: 10
      8,   //< kTME: 11
      8,   //< kSI8: 12
      8,   //< kUI8: 13
      8,   //< kDBL: 14
      16,  //< kSIH: 15
      16,  //< kUIH: 16
      16,  //< kDEC: 17
  };
  SIN type_upper_bits = type >> 3;
  type &= 0x1f;
  if (type == kUIX) return ((SI4)2) << type_upper_bits;
  if (type > kOBJ) return -1;
  return kWidths[type];
}

const CH1** TypeStrings() { return TTypeStrings<CH1>(); }

const CH1* TypeString(SIN type) { return TypeStrings()[type & 0x1f]; }

const CH1* TypeString(SI4 type) { return TypeString((UI1)type); }

UI1 TypeMask(UI1 value) { return value & 0x1f; }

BOL TypeIsArray(SI4 type) { return type >= kTypeCount; }

BOL TypeIsSet(SI4 type) { return type >= kTypeCount; }

void* TypeAlign(SIN type, void* value) {
  ASSERT(value);
  if (type == 0) return nullptr;
  if (!TypeIsValid(type)) return nullptr;

  SI4 size = TypeFixedSize(type);
  if (type <= kUI1) return value;
  SIN* value_ptr = reinterpret_cast<SIN*>(value);
#if WORD_SIZE == 2
  if (type <= kHLF) return AlignUpPointer2<>(value);
#else
  if (type <= kBOL) return TAlignUp2<>(value);
#endif
  if (type <= kTMS) return AlignUp<>(value, 3);
  if (type <= kDEC) return AlignUp<>(value, 7);

  switch (type >> 6) {
    case 0:
      return value;
    case 1:
      return TAlignUp2<>(value);
    case 2:
      return AlignUp<>(value, 3);
    case 3:
      return AlignUp<>(value, 7);
  }
  return 0;
}
/*
template <typename Char, typename UI>
inline CH1* WriteString(CH1* begin, CH1* stop, const void* value) {
  begin = AlignUpPointer<CH1>(begin);
  if (stop - begin < 2 * sizeof(UI)) return nullptr;
  const Char* source = reinterpret_cast<const Char*>(value);
  UI length = TStringLength<UI, Char>(source);
  UI* target = reinterpret_cast<UI*>(begin);
  *target++ = length;
  return SocketCopy(target, stop, value, length + sizeof(Char));
}*/

template <typename UI>
inline CH1* WriteObj(CH1* begin, CH1* stop, const void* value) {
  UI* target = AlignUpPointer<UI>(begin);
  const UI* source = reinterpret_cast<const UI*>(value);
  UI size = *source++;
  if (size < sizeof(UI) || size >=) return nullptr;
  *target++ = size;
  return SocketCopy(target, stop, value, size - sizeof(UI));
}

CH1* Write(CH1* begin, CH1* stop, SIN type, const void* value) {
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
  if (type <= kTMS) {
    CH4* target_4 = AlignUp<CH4>(begin, 3);
    *target_4++ = *reinterpret_cast<const CH4*>(value);
    return reinterpret_cast<CH1*>(target_4);
  }
  if (type <= kDEC) {
    UI8* target_8 = AlignUp<UI8>(begin, 7);
    const UI8* source_8 = reinterpret_cast<const UI8*>(value);
    *target_8++ = *source_8++;
    if (type == kDEC) {
      *target_8++ = *source_8;
      return reinterpret_cast<CH1*>(target_8);
    }
    return reinterpret_cast<CH1*>(target_8);
  }
  if (TypeIsString(type)) {
    switch (type >> 6) {
      case 0:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 1:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 2:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 3:
        return reinterpret_cast<CH1*>(TPrint<CH2>(
            reinterpret_cast<UI2*>(begin), reinterpret_cast<UI2*>(stop),
            reinterpret_cast<const UI2*>(value)));
      case 4:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 5:
        return reinterpret_cast<CH1*>(TPrint<CH2>(
            reinterpret_cast<UI2*>(begin), reinterpret_cast<UI2*>(stop),
            reinterpret_cast<const UI2*>(value)));
      case 6:
        return TPrint<CH1>(begin, stop, reinterpret_cast<const CH1*>(value));
      case 7:
        return reinterpret_cast<CH1*>(TPrint<CH2>(
            reinterpret_cast<UI2*>(begin), reinterpret_cast<UI2*>(stop),
            reinterpret_cast<const UI2*>(value)));
    }
  }
  CH1 array_type = type >> 6;
  switch (array_type) {
    case 0:
      return WriteObj<UI1>(begin, stop, value);
    case 1:
      return WriteObj<UI2>(begin, stop, value);
    case 2:
      return WriteObj<UI4>(begin, stop, value);
    case 3:
      return WriteObj<UI8>(begin, stop, value);
  }
  return nullptr;
}

BOL TypeIsObj(SIN type) {
  if (type < kOBJ) return false;
  return true;
}

BOL TypeIsString(SIN type) {
  type &= 0x1f;
  if (type >= kADR && type <= kTKN) return true;
  return false;
}

BOL TypeIsUtf16(SIN type) { return (BOL)(type & 0x20); }

inline int TypeSizeWidthCode(SIN type) { return type >> 6; }

}  // namespace _

#if USING_UTF8
namespace _ {
CH1* Print(CH1* begin, CH1* stop, SIN type, const void* value) {
  return TPrint<CH1>(begin, stop, type, value);
}
_::UTF1& operator<<(::_::UTF1& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.begin, utf.stop, item.type, item.value));
}
}  // namespace _
#endif
#if USING_UTF16
namespace _ {
CH2* Print(CH2* begin, CH2* stop, SIN type, const void* value) {
  return TPrint<CH2>(begin, stop, type, value);
}
}  // namespace _
_::UTF2& operator<<(::_::UTF2& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.begin, utf.stop, item.type, item.value));
}
#endif
#if USING_UTF32
namespace _ {
CH4* Print(CH4* begin, CH4* stop, SIN type, const void* value) {
  return TPrint<CH4>(begin, stop, type, value);
}
}  // namespace _
_::UTF4& operator<<(::_::UTF4& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.begin, utf.stop, item.type, item.value));
}
#endif

#endif  //< #if SEAM >= _0_0_0__13
