/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_ascii.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if SEAM >= SCRIPT2_3

#include "t_ascii.h"

#include "t_socket.h"

#if SEAM == SCRIPT2_3
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1* STRType() {
  static const CH1 kStrings[64][4] = {
      {'N', 'I', 'L', NIL},  //
      {'S', 'I', '1', NIL},  //
      {'U', 'I', '1', NIL},  //
      {'S', 'I', '2', NIL},  //
      {'U', 'I', '2', NIL},  //
      {'F', 'P', '2', NIL},  //
      {'B', 'O', 'L', NIL},  //
      {'S', 'I', '4', NIL},  //
      {'U', 'I', '4', NIL},  //
      {'F', 'P', '4', NIL},  //
      {'S', 'I', '8', NIL},  //
      {'U', 'I', '8', NIL},  //
      {'F', 'P', '8', NIL},  //
      {'F', 'P', 'H', NIL},  //
      {'S', 'I', '1', NIL},  //
      {'U', 'I', '1', NIL},  //
      {'S', 'I', '2', NIL},  //
      {'U', 'I', '2', NIL},  //
      {'F', 'P', '2', NIL},  //
      {'B', 'O', 'L', NIL},  //
      {'S', 'I', '4', NIL},  //
      {'U', 'I', '4', NIL},  //
      {'F', 'P', '4', NIL},  //
      {'S', 'I', '8', NIL},  //
      {'U', 'I', '8', NIL},  //
      {'F', 'P', '8', NIL},  //
      {'F', 'P', 'H', NIL},  //
      {'C', 'H', '1', NIL},  //
      {'C', 'H', '2', NIL},  //
      {'C', 'H', '4', NIL},  //
      {'T', 'M', '4', NIL},  //
      {'T', 'M', '8', NIL},  //
      {'T', 'M', '8', NIL},  //
      {'P', 'T', '2', NIL},  //
      {'P', 'C', '2', NIL},  //
      {'P', 'T', '4', NIL},  //
      {'P', 'C', '4', NIL},  //
      {'P', 'T', '8', NIL},  //
      {'P', 'C', '8', NIL},  //
      {'O', 'A', '4', NIL},  //
      {'O', 'A', '8', NIL},  //
      {'P', '1', '6', NIL},  //
      {'P', '3', '2', NIL},  //
      {'O', 'B', 'J', NIL},  //
      {'B', 'N', 'M', NIL},  //
      {'V', 'I', 'N', NIL},  //
      {'S', 'T', '1', NIL},  //
      {'S', 'T', '2', NIL},  //
      {'S', 'T', '4', NIL},  //
      {'T', 'K', 'N', NIL},  //
      {'A', 'D', 'R', NIL},  //
      {'R', 'E', 'C', NIL},  //
      {'L', 'O', 'M', NIL},  //
      {'O', 'B', '1', NIL},  //
      {'O', 'B', 'J', NIL},  //
      {'S', 'L', 'T', NIL},  //
      {'B', 'S', 'Q', NIL},  //
      {'E', 'X', 'P', NIL},  //
      {'W', 'L', 'D', NIL},  //
  };
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
  SIN invalid = kINV;
  if (index < 0 || index > invalid) return -1;
  return TypePODSizes()[index];
}

const CH1* STRType(SI4 index) {
  if (index < 0 || index >= kINV) index = 32;
  const CH1* strings = STRType();
  return strings + (index << 2);
}

template <typename T, SI1 kAlignment_>
int TAsciiType(void* begin, void* end, UI2 type, T item) {
  return 0;
}

BOL TypeIsValid(SI4 type) { return (type >> 7) == 0; }

/* This might be junk. I don't know how the bounds checking works yet.

struct SDK Wildcard {
  UI2 type;

  Wildcard (CH1* item);

#if USING_UTF16 == YES
  Wildcard (CH2* item);
#endif

#if USING_UTF32 == YES
  Wildcard (CH4* item);
#endif

  Wildcard (SI1* item);
  Wildcard (UI1* item);
  Wildcard (SI2* item);
  Wildcard (UI2* item);
  Wildcard (SI4* item);
  Wildcard (UI4* item);
  Wildcard (SI8* item);
  Wildcard (UI8* item);

#if USING_FP4 == YES
  Wildcard (FP4* item);
#endif
#if USING_FP8 == YES
  Wildcard (FP8* item);
#endif
};

Wildcard::Wildcard(CH1* item) : type(kCH1) {
}

#if USING_UTF16 == YES
Wildcard::Wildcard(CH2* item) : type(kCH2) {}
#endif

#if USING_UTF32 == YES
Wildcard::Wildcard(CH4* item) : type(kCH4) {}
#endif

Wildcard::Wildcard(SI1* item) : type(kSI1) {}

Wildcard::Wildcard(UI1* item) : type(kUI1) {}

Wildcard::Wildcard(SI2* item) : type(kSI2) {}

Wildcard::Wildcard(UI2* item) : type(kUI2) {}

Wildcard::Wildcard(SI4* item) : type(kSI4) {}

Wildcard::Wildcard(UI4* item) : type(kUI4) {}

Wildcard::Wildcard(SI8* item) : type(kSI8) {}

Wildcard::Wildcard(UI8* item) : type(type) {}

#if USING_FP4 == YES
Wildcard::Wildcard(FP4* item) : type(type) {}
#endif
#if USING_FP8 == YES
Wildcard::Wildcard(FP8* item) : type(type) {}
#endif*/

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
::_::UTF1& operator<<(::_::UTF1& utf, const ::_::TypeValue& item) {
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
::_::UTF2& operator<<(::_::UTF2& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item.type, item.value));
}
#endif
#if USING_UTF32
namespace _ {
CH4* Print(CH4* begin, CH4* stop, SI4 type, const void* value) {
  return TPrint<CH4>(begin, stop, type, value);
}
}  // namespace _
::_::UTF4& operator<<(::_::UTF4& utf, const ::_::TypeValue& item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item.type, item.value));
}
#endif

#endif  //< #if SEAM >= SCRIPT2_13
