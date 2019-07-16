/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_cout.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if USING_CONSOLE == YES
//
#include <conio.h>

#include <cstdio>

#include "c_cin.h"
#include "t_stringcore.h"

#if SEAM == SEAM_SCRIPT2_CORE
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
        if (c != 'e' || c != 'E') return false;
        if (c == '.') state = CIn::kStateExponentSign;
      }
      case CIn::kStateFractionalPart: {
        if (c != 'e' || c != 'E') return false;
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

#if USING_UTF8 == YES
CIn::CIn(CH1& result) { Scan(result); }
CIn::CIn(CH1* result, SIW buffer_size) { Scan(result, buffer_size); }
#endif
#if USING_UTF16 == YES
CIn::CIn(CH2& result) { Scan(result); }
CIn::CIn(CH2* result, SIW buffer_size) { Scan(result, buffer_size); }
#endif
#if USING_UTF32 == YES
CIn::CIn(CH4& result) { Scan(result); }
CIn::CIn(CH4* result, SIW buffer_size) { Scan(result, buffer_size); }
#endif
CIn::CIn(SI1& result) { Scan(result); }
CIn::CIn(UI1& result) { Scan(result); }
CIn::CIn(SI2& result) { Scan(result); }
CIn::CIn(UI2& result) { Scan(result); }
CIn::CIn(SI4& result) { Scan(result); }
CIn::CIn(UI4& result) { Scan(result); }
CIn::CIn(SI8& result) { Scan(result); }
CIn::CIn(UI8& result) { Scan(result); }
#if USING_FP4 == YES
CIn::CIn(FP4& result) { Scan(result); }
#endif
#if USING_FP8 == YES
CIn::CIn(FP8& result) { Scan(result); }
#endif

#if USING_UTF8 == YES
BOL CIn::Scan(CH1& result) {
  result = ScanKey();
  return true;
}

BOL CIn::Scan(CH1* result, SIW buffer_size) {
  return TCInString<CH1>(result, buffer_size);
}
#endif
#if USING_UTF16 == YES
BOL CIn::Scan(CH2& result) {
  result = ScanKey();
  return true;
}
BOL CIn::Scan(CH2* result, SIW buffer_size) {
  return TCInString<CH2>(result, buffer_size);
}
#endif
#if USING_UTF32 == YES
BOL CIn::Scan(CH4& result) {
  result = ScanKey();
  return true;
}
BOL CIn::Scan(CH4* result, SIW buffer_size) {
  return TCInString<CH4>(result, buffer_size);
}
#endif
BOL CIn::Scan(SI1& result) { return TCInSigned<SI1, UI1>(result); }
BOL CIn::Scan(UI1& result) { return TCInUnsigned<UI1>(result); }
BOL CIn::Scan(SI2& result) { return TCInSigned<SI2, UI2>(result); }
BOL CIn::Scan(UI2& result) { return TCInUnsigned<UI2>(result); }
BOL CIn::Scan(SI4& result) { return TCInSigned<SI4, UI4>(result); }
BOL CIn::Scan(UI4& result) { return TCInUnsigned<UI4>(result); }
BOL CIn::Scan(SI8& result) { return TCInSigned<SI8, UI8>(result); }
BOL CIn::Scan(UI8& result) { return TCInUnsigned<UI8>(result); }
#if USING_FP4 == YES
BOL CIn::Scan(FP4& result) { return TCInFloatingPoint<FP4, SI4, UI4>(result); }
#endif
#if USING_FP8 == YES
BOL CIn::Scan(FP8& result) { return TCInFloatingPoint<FP8, SI8, UI8>(result); }
#endif

SIN CIn::GetKey() { return _getch(); }

SIN CIn::ScanKey() {
  SIN c;
  while ((c = CIn::GetKey()) < 0)
    ;
  return c;
}

const CH1* CIn::Args(SIN arg_count, CH1** args) {
  if (!args || arg_count <= 1) return "";
  if (arg_count == 2) return args[1];
  CH1 *begin = args[1], *stop = args[arg_count - 1] - 1;
  while (stop > begin) {
    CH1 c = *stop;
    if (!c) *stop = ' ';
    --stop;
  }
  return begin;
}

Pausef::Pausef() {
  COut("\nPress any key to continue...");
  CIn::ScanKey();
}

Pausef::Pausef(const CH1* format, ...) {
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
  Pausef();
}

}  // namespace _

::_::COut& operator<<(::_::COut& o, ::_::CIn& i) { return o; }

::_::COut& operator<<(::_::COut& o, ::_::Pausef& i) { return o; }
#endif
