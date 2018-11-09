/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
@file    /script2_ascii_data.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__12
#if SEAM == _0_0_0__12
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

#include "casciidata.h"

#include "tsocket.h"
#include "ttest.h"

namespace _ {

BOL TypeIsValid(type_t type) {
  if (type >= kLST && type <= kDIC || (type >= (kADR + 32) && type <= (kTKN + 32)))
    return false;
  return true;
}

TypeValue::TypeValue(type_t type, const void* value)
    : type(type), value(value) {
  // Nothing to do here! (:-)-+=<
}

uint_t TypeFixedSize(uint_t type) {
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
  type_t type_upper_bits = type >> 3;
  type &= 0x1f;
  if (type == kUIX) return ((uint_t)2) << type_upper_bits;
  if (type > kOBJ) return -1;
  return kWidths[type];
}

const char** TypeStrings() { return TypeStrings<char>(); }

const char* TypeString(type_t type) { return TypeStrings()[type & 0x1f]; }

const char* TypeString(uint_t type) { return TypeString((UI1)type); }

UI1 TypeMask(UI1 value) { return value & 0x1f; }

BOL TypeIsArray(uint_t type) { return type >= kTypeCount; }

BOL TypeIsSet(uint_t type) { return type >= kTypeCount; }

void* TypeAlign(type_t type, void* value) {
  ASSERT(value);
  if (type == 0) return nullptr;
  if (!TypeIsValid(type)) return nullptr;

  uint_t size = TypeFixedSize(type);
  if (type <= kUI1) return value;
  type_t* value_ptr = reinterpret_cast<type_t*>(value);
#if WORD_SIZE == 2
  if (type <= kHLF) return AlignUpPointer2<>(value);
#else
  if (type <= kBOL) return AlignUp2<>(value);
#endif
  if (type <= kTMS) return AlignUp<>(value, 3);
  if (type <= kDEC) return AlignUp<>(value, 7);

  switch (type >> 6) {
    case 0:
      return value;
    case 1:
      return AlignUp2<>(value);
    case 2:
      return AlignUp<>(value, 3);
    case 3:
      return AlignUp<>(value, 7);
  }
  return 0;
}
/*
template <typename Char, typename UI>
inline char* WriteString(char* begin, char* end, const void* value) {
  begin = AlignUpPointer<char>(begin);
  if (end - begin < 2 * sizeof(UI)) return nullptr;
  const Char* source = reinterpret_cast<const Char*>(value);
  UI length = StringLength<UI, Char>(source);
  UI* target = reinterpret_cast<UI*>(begin);
  *target++ = length;
  return SocketCopy(target, end, value, length + sizeof(Char));
}*/

template <typename UI>
inline char* WriteObj(char* begin, char* end, const void* value) {
  UI* target = AlignUpPointer<UI>(begin);
  const UI* source = reinterpret_cast<const UI*>(value);
  UI size = *source++;
  if (size < sizeof(UI) || size >=) return nullptr;
  *target++ = size;
  return SocketCopy(target, end, value, size - sizeof(UI));
}

char* Write(char* begin, char* end, type_t type, const void* value) {
  // Algorithm:
  // 1.) Determine type.
  // 2.) Align begin pointer to type width.
  // 3.) Check for enough room in begin-end socket.
  // 4.) Use SocketCopy to copy the data into the given begin-end socket.

  if (!begin || begin >= end || !value || !TypeIsValid(type)) return nullptr;

  if (type <= kUI1) {
    char* target_1 = reinterpret_cast<char*>(begin);
    *target_1++ = *reinterpret_cast<const char*>(value);
    return target_1;
  }
  if (type <= kBOL) {
    char16_t* target_2 = AlignUp2<char16_t>(begin);
    *target_2++ = *reinterpret_cast<const char16_t*>(value);
    return reinterpret_cast<char*>(target_2);
  }
  if (type <= kTMS) {
    char32_t* target_4 = AlignUp<char32_t>(begin, 3);
    *target_4++ = *reinterpret_cast<const char32_t*>(value);
    return reinterpret_cast<char*>(target_4);
  }
  if (type <= kDEC) {
    UI8* target_8 = AlignUp<UI8>(begin, 7);
    const UI8* source_8 = reinterpret_cast<const UI8*>(value);
    *target_8++ = *source_8++;
    if (type == kDEC) {
      *target_8++ = *source_8;
      return reinterpret_cast<char*>(target_8);
    }
    return reinterpret_cast<char*>(target_8);
  }
  if (TypeIsString(type)) {
    switch (type >> 6) {
      case 0:
        return Print<char>(begin, end, reinterpret_cast<const char*>(value));
      case 1:
        return Print<char>(begin, end, reinterpret_cast<const char*>(value));
      case 2:
        return Print<char>(begin, end, reinterpret_cast<const char*>(value));
      case 3:
        return reinterpret_cast<char*>(
            Print<char16_t>(reinterpret_cast<UI2*>(begin),
                            reinterpret_cast<UI2*>(end),
                            reinterpret_cast<const UI2*>(value)));
      case 4:
        return Print<char>(begin, end, reinterpret_cast<const char*>(value));
      case 5:
        return reinterpret_cast<char*>(
            Print<char16_t>(reinterpret_cast<UI2*>(begin),
                            reinterpret_cast<UI2*>(end),
                            reinterpret_cast<const UI2*>(value)));
      case 6:
        return Print<char>(begin, end, reinterpret_cast<const char*>(value));
      case 7:
        return reinterpret_cast<char*>(
            Print<char16_t>(reinterpret_cast<UI2*>(begin),
                            reinterpret_cast<UI2*>(end),
                            reinterpret_cast<const UI2*>(value)));
    }
  }
  char array_type = type >> 6;
  switch (array_type) {
    case 0:
      return WriteObj<UI1>(begin, end, value);
    case 1:
      return WriteObj<UI2>(begin, end, value);
    case 2:
      return WriteObj<UI4>(begin, end, value);
    case 3:
      return WriteObj<UI8>(begin, end, value);
  }
  return nullptr;
}

BOL TypeIsObj(type_t type) {
  if (type < kOBJ) return false;
  return true;
}

BOL TypeIsString(type_t type) {
  type &= 0x1f;
  if (type >= kADR && type <= kTKN) return true;
  return false;
}

BOL TypeIsUtf16(type_t type) { return (BOL)(type & 0x20); }

inline int TypeSizeWidthCode(type_t type) { return type >> 6; }

}  // namespace _

#if USING_UTF8
namespace _ {
char* Print(char* begin, char* end, type_t type, const void* value) {
  return Print<char>(begin, end, type, value);
}  //< namespace _
_::UTF8& operator<<(_::UTF8& utf, const _::TypeValue& item) {
  return utf.Set(_::Print(utf.begin, utf.end, item.type, item.value));
}
#endif
#if USING_UTF16
namespace _ {
char16_t* Print(char16_t* begin, char16_t* end, type_t type,
                const void* value) {
  return Print<char16_t>(begin, end, type, value);
}
}  // namespace _
_::UTF2& operator<<(_::UTF2& utf, const _::TypeValue& item) {
  return utf.Set(_::Print(utf.begin, utf.end, item.type, item.value));
}
#endif
#if USING_UTF32
namespace _ {
char32_t* Print(char32_t* begin, char32_t* end, type_t type,
                const void* value) {
  return Print<char32_t>(begin, end, type, value);
}
}  // namespace _
_::UTF4& operator<<(_::UTF4& utf, const _::TypeValue& item) {
  return utf.Set(_::Print(utf.begin, utf.end, item.type, item.value));
}
#endif
#include "test_footer.inl"
#endif  //< #if SEAM >= _0_0_0__12
