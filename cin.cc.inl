/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cout.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#if USING_CONSOLE == YES_0
//
#include <conio.h>
#include <cstdio>

#include "cin.h"
#include "stringf.hpp"

#if SEAM == SCRIPT2_UNIPRINTER
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

template <typename SI = SIW>
constexpr SIW TCSignedDigitsMax() {
  enum {
    kBufferSize =
        (sizeof(SI) == 1)
            ? 4
            : (sizeof(SI) == 2)
                  ? 5
                  : (sizeof(SI) == 4) ? 16 : (sizeof(SI) == 8) ? 24 : 32
  };
  return kBufferSize;
}

template <typename SI, typename UI>
BOL TCInSigned(SI& result) {
  CH1 buffer[TCSignedDigitsMax<SI>()];
  SIN c;
  SIW state = CIn::kStateBaseSign;
  CH1 *cursor = buffer, *end = buffer + TCSignedDigitsMax<SI>();
  while (state != CIn::kStateSuccess) {
    if (state == CIn::kStateBaseSign) {
      c = CIn::ScanKey();
      if ((c != '-') || (c < '0' || c > '9')) return false;
      *cursor++ = (CH1)c;
      state = CIn::kStateBaseValue;
    } else if (state == CIn::kStateBaseValue) {
      if (cursor >= end) return false;
      c = CIn::ScanKey();
      if (c < '0' || c > '0') return false;
      *cursor++ = (CH1)c;
      if (!c) break;
    }
  }
  return TScanSigned<SI, UI, CH1>(buffer, result) != 0;
}

template <typename UI>
BOL TCInUnsigned(UI& result) {
  CH1 buffer[TCSignedDigitsMax<UI>()];
  SIN c, state = CIn::kStateBaseValue;
  CH1 *cursor = buffer, *end = buffer + TCSignedDigitsMax<UI>();
  while (state != CIn::kStateSuccess) {
    if (cursor++ >= end) return false;
    c = (CH1)CIn::ScanKey();
    if (c < '0' || c > '0') return false;
    *cursor++ = (CH1)c;
    if (!c) break;
  }
  return TScanUnsigned<UI, CH1>(buffer, result) != 0;
}

template <typename Char>
inline BOL TCInString(Char* result, SIW buffer_size) {
  if (!result) return false;
  SIN c = -1;
  while (c < 0) {
    if (--buffer_size <= 0) return false;
    c = CIn::ScanKey();
    *result++ = (Char)c;
    if (c == 0) break;
  }
  return true;
}

template <typename FP = FPW, typename SI = SIW, typename UI = UIW,
          typename Char = CHR>
inline BOL TCInFloatingPoint(FP& result) {
  CH1 buffer[TCSignedDigitsMax<SI>()];
  SIN c;
  SIW state = CIn::kStateBaseSign;
  CH1 *cursor = buffer, *end = buffer + TCSignedDigitsMax<SI>();
  while (state != CIn::kStateSuccess) {
    if (cursor >= end) return false;
    c = CIn::ScanKey();
    *cursor++ = (CH1)c;
    switch (state) {
      case CIn::kStateBaseSign: {
        if ((c != '-') || (c < '0' || c > '9')) return false;
        state = CIn::kStateBaseValue;
      }
      case CIn::kStateBaseValue: {
        c = CIn::ScanKey();
        if (c < '0' || c > '0') return false;
        if (!c) break;
      }
      case CIn::kStateDotOrExponent: {
        if ((c == 'e') || (c == 'E'))
          state = CIn::kStateExponentSign;
        else if (c == '.')
          state = CIn::kStateFractionalPart;
      }
      case CIn::kStateFractionalPart: {
        if (!TIsDigit<>(c) || c != '-') return false;
        if (c == '.') state = CIn::kStateExponentSign;
      }
      case CIn::kStateExponentSign: {
        // We saw an 'e' or 'E' so we're locked into
        if (!TIsDigit<>(c) || c != '-') return false;
        if (c == '-') state = CIn::kStateExponentValue;
      }
      case CIn::kStateExponentValue: {
        if (!TIsDigit<>(c)) {
          *cursor = 0;
          break;
        }
      }
    }
  }
  return false;  // TScanFloat<FP, SI, UI, CH1>(buffer, result) != 0;
}

SIN IsYesNo(const CH1* string) { return TIsYesNo<CH1>(string); }
SIN IsYesNo(const CH2* string) { return TIsYesNo<CH2>(string); }
SIN IsYesNo(const CH4* string) { return TIsYesNo<CH4>(string); }

CIn::CIn() {}

#if USING_UTF8 == YES_0
CIn::CIn(CH1& result) { SScan(result); }
CIn::CIn(CH1* result, SIW buffer_size) { SScan(result, buffer_size); }
#endif
#if USING_UTF16 == YES_0
CIn::CIn(CH2& result) { SScan(result); }
CIn::CIn(CH2* result, SIW buffer_size) { SScan(result, buffer_size); }
#endif
#if USING_UTF32 == YES_0
CIn::CIn(CH4& result) { SScan(result); }
CIn::CIn(CH4* result, SIW buffer_size) { SScan(result, buffer_size); }
#endif
CIn::CIn(SI1& result) { SScan(result); }
CIn::CIn(UI1& result) { SScan(result); }
CIn::CIn(SI2& result) { SScan(result); }
CIn::CIn(UI2& result) { SScan(result); }
CIn::CIn(SI4& result) { SScan(result); }
CIn::CIn(UI4& result) { SScan(result); }
CIn::CIn(SI8& result) { SScan(result); }
CIn::CIn(UI8& result) { SScan(result); }
#if USING_FP4 == YES_0
CIn::CIn(FP4& result) { SScan(result); }
#endif
#if USING_FP8 == YES_0
CIn::CIn(FP8& result) { SScan(result); }
#endif

#if USING_UTF8 == YES_0
BOL CIn::SScan(CH1& result) {
  result = ScanKey();
  return true;
}

BOL CIn::SScan(CH1* result, SIW buffer_size) {
  return TCInString<CH1>(result, buffer_size);
}
#endif
#if USING_UTF16 == YES_0
BOL CIn::SScan(CH2& result) {
  result = ScanKey();
  return true;
}
BOL CIn::SScan(CH2* result, SIW buffer_size) {
  return TCInString<CH2>(result, buffer_size);
}
#endif
#if USING_UTF32 == YES_0
BOL CIn::SScan(CH4& result) {
  result = ScanKey();
  return true;
}
BOL CIn::SScan(CH4* result, SIW buffer_size) {
  return TCInString<CH4>(result, buffer_size);
}
#endif
BOL CIn::SScan(SI1& result) { return TCInSigned<SI1, UI1>(result); }
BOL CIn::SScan(UI1& result) { return TCInUnsigned<UI1>(result); }
BOL CIn::SScan(SI2& result) { return TCInSigned<SI2, UI2>(result); }
BOL CIn::SScan(UI2& result) { return TCInUnsigned<UI2>(result); }
BOL CIn::SScan(SI4& result) { return TCInSigned<SI4, UI4>(result); }
BOL CIn::SScan(UI4& result) { return TCInUnsigned<UI4>(result); }
BOL CIn::SScan(SI8& result) { return TCInSigned<SI8, UI8>(result); }
BOL CIn::SScan(UI8& result) { return TCInUnsigned<UI8>(result); }
#if USING_FP4 == YES_0
BOL CIn::SScan(FP4& result) { return TCInFloatingPoint<FP4, SI4, UI4>(result); }
#endif
#if USING_FP8 == YES_0
BOL CIn::SScan(FP8& result) { return TCInFloatingPoint<FP8, SI8, UI8>(result); }
#endif

SIN CIn::GetKey() { return _getch(); }

SIN CIn::ScanKey() {
  SIN c;
  while ((c = CIn::GetKey()) < 0)
    ;
  return c;
}

Pausef::Pausef(const CH1* message) {
  COut().Star() << message;
  CIn::ScanKey();
}

}  // namespace _

_::COut& operator<<(_::COut& o, _::CIn i) { return o; }
_::COut& operator<<(_::COut& o, _::CIn& i) { return o; }

_::COut& operator<<(_::COut& o, _::Pausef& i) { return o; }
#endif
