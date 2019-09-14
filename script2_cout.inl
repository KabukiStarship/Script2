/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_cout.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#if USING_CONSOLE == YES_0

#include "c_cout.h"
//
#include "c_typevalue.h"
#include "t_puff.h"
#include "t_string.h"
#include "t_uniprinter.h"

//#include <cstdio>
#include <iostream>

#if SEAM == SCRIPT2_UNIPRINTER
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#define STD_COUT std::wcerr

namespace _ {

COut::COut() {}

COut::COut(CH1 item) { Print(item); }
COut::COut(const CH1* item) { Print(item); }
#if USING_UTF16 == YES_0
COut::COut(CH2 item) { Print(item); }
COut::COut(const CH2* item) { Print(item); }
#endif
#if USING_UTF32 == YES_0
COut::COut(CH4 item) { Print(item); }
COut::COut(const CH4* item) { Print(item); }
#endif
COut::COut(SI1 item) { Print(item); }
COut::COut(UI1 item) { Print(item); }
COut::COut(SI2 item) { Print(item); }
COut::COut(UI2 item) { Print(item); }
COut::COut(SI4 item) { Print(item); }
COut::COut(UI4 item) { Print(item); }
COut::COut(SI8 item) { Print(item); }
COut::COut(UI8 item) { Print(item); }
#if USING_FP4 == YES_0
COut::COut(FP4 item) { Print(item); }
#endif
#if USING_FP8 == YES_0
COut::COut(FP8 item) { Print(item); }
#endif
COut::COut(Hexf item) { Print(item); }
COut::COut(Binaryf item) { Print(item); }
COut::COut(Centerf item) { Print(item); }
COut::COut(Rightf item) { Print(item); }
COut::COut(Linef item) { Print(item); }
COut::COut(Headingf item) { Print(item); }
COut::COut(Indentf item) { Print(item); }
COut::COut(Charsf item) { Print(item); }

COut::COut(const CH1* item, CH1 second_item) {
  Print(item);
  Print(second_item);
}

COut::COut(const CH1* item, const CH1* second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CH1 item, CH1 second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CH1 item, const CH1* second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CH1 item, CH1 second_item, CH1 third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(CH1 item, CH1 second_item, const CH1* third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(const CH1* item, const CH1* second_item, CH1 third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(const CH1* item, const CH1* second_item, const CH1* third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut& COut::Star() { return *this; }

COut& COut::Print(CH1 item) {
  STD_COUT << item;
  return *this;
}

COut& COut::Print(const CH1* item) {
  return TSPrintString<COut, CH1>(*this, item);
}

#if USING_UTF16 == YES_0
COut& COut::Print(CH2 item) {
  STD_COUT << (CHN)item;
  return *this;
}

COut& COut::Print(const CH2* item) {
  return TSPrintString<COut, CH2>(*this, item);
}

#endif
#if USING_UTF32 == YES_0
COut& COut::Print(CH4 item) {
  if (item >= (CH4(1) << 9)) {
    STD_COUT << (CHN)(item & 0x3f) + 0xD800;
    STD_COUT << (CHN)((item >> 10) & 0x3f) + 0xDC00;
  } else {
    STD_COUT << (CHN)item;
  }
  return *this;
}
COut& COut::Print(const CH4* item) {
  return TSPrintString<COut, CH4>(*this, item);
}
#endif

COut& COut::Print(SI4 item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
#if ALU_SIZE == ALU_64_BIT
  Print((SI8)item);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TSPrintSigned<SI8, UI8, CH1>(socket, kSize - 1, (SI8)value);
  Print(socket);
#endif
#endif
  return *this;
}

COut& COut::Print(UI4 item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
#if ALU_SIZE == ALU_64_BIT
  Print((UI8)item);
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TSPrintUnsigned<UI4, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
#endif
  return *this;
}

COut& COut::Print(SI8 item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TSPrintSigned<SI8, UI8, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
  return *this;
}

COut& COut::Print(UI8 item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TSPrintUnsigned<UI8, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
  return *this;
}

#if USING_FP4 == YES_0
COut& COut::Print(FP4 item) {
#if SEAM <= SCRIPT2_BOOK
  STD_COUT << item;
#else
  enum { kSize = 16 };
  CH1 buffer[kSize];
  TPrintFloat<FP4, UI4, CH1>(buffer, kSize, value);
  Print(buffer);
#endif
  return *this;
}
#endif
#if USING_FP8 == YES_0
COut& COut::Print(FP8 item) {
#if SEAM <= SCRIPT2_BOOK
  STD_COUT << item;
#else
  enum { kSize = 24 };
  CH1 buffer[kSize];
  TPrintFloat<FP8, UI8, CH1>(buffer, kSize - 1, item);
  Print(buffer);
#endif
  return *this;
}
#endif

COut& COut::Print(Hexf& item) {
  return TPrintHex<COut>(*this, item.element.Value(), item.element.count);
}

COut& COut::Print(Binaryf& item) {
  return TPrintBinary<COut>(*this, item.element.Value(), item.element.count);
}

COut& COut::Print(Centerf& item) {
  return TPrintCenter<COut>(*this, item.element);
}

COut& COut::Print(Rightf& item) {
  return TPrintRight<COut>(*this, item.element);
}

COut& COut::Print(Linef& item) { return TPrintLinef<COut>(*this, item); }

COut& COut::Print(Headingf& item) { return TPrintHeadingf<COut>(*this, item); }

COut& COut::Print(Indentf& item) {
  return _::TPrintIndent<_::COut>(*this, item.indent_count);
}

COut& COut::Print(Charsf& item) {
  return _::TPrintChars<COut>(*this, item);
}  // namespace _

COut& COut::NL() { return Print('\n'); }
COut& COut::NL(CH1 item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CH1* item) {
  NL();
  return Print(item);
}
#if USING_UTF16 == YES_0
COut& COut::NL(CH2 item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CH2* item) {
  NL();
  return Print(item);
}
#endif
#if USING_UTF32 == YES_0
COut& COut::NL(CH4 item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CH4* item) {
  NL();
  return Print(item);
}
#endif
COut& COut::NL(SI4 item) {
  NL();
  return Print(item);
}
COut& COut::NL(UI4 item) {
  NL();
  return Print(item);
}
COut& COut::NL(SI8 item) {
  NL();
  return Print(item);
}
COut& COut::NL(UI8 item) {
  NL();
  return Print(item);
}
#if USING_FP4 == YES_0
COut& COut::NL(FP4 item) {
  NL();
  return Print(item);
}
#endif
#if USING_FP8 == YES_0
COut& COut::NL(FP8 item) {
  NL();
  return Print(item);
}
#endif

COut& COut::Hex(const void* item) { return TPrintHex<COut>(*this, item); }
COut& COut::Hex(const void* item, SIW size) {
  return TPrintHex<COut>(*this, item, size);
}
COut& COut::Hex(const void* item, const void* item_stop) {
  return TPrintHex<COut>(*this, item, item_stop);
}
COut& COut::Hex(SI1 item) { return TPrintHex<COut, SI1, UI1>(*this, item); }
COut& COut::Hex(UI1 item) { return TPrintHex<COut, UI1>(*this, item); }
COut& COut::Hex(SI2 item) { return TPrintHex<COut, SI2, UI2>(*this, item); }
COut& COut::Hex(UI2 item) { return TPrintHex<COut, UI2>(*this, item); }
COut& COut::Hex(SI4 item) { return TPrintHex<COut, SI4, UI4>(*this, item); }
COut& COut::Hex(UI4 item) { return TPrintHex<COut, UI4>(*this, item); }
COut& COut::Hex(SI8 item) { return TPrintHex<COut, SI8, UI8>(*this, item); }
COut& COut::Hex(UI8 item) { return TPrintHex<COut, UI8>(*this, item); }
#if USING_FP4 == YES_0
COut& COut::Hex(FP4 item) { return TPrintHex<COut>(*this, item); }
#endif
#if USING_FP8 == YES_0
COut& COut::Hex(FP8 item) { return TPrintHex<COut>(*this, item); }
#endif

/* Stores the given item to the buffer and store the size. */
COut& COut::Binary(const void* item) { return TPrintBinary<COut>(*this, item); }
COut& COut::Binary(const void* item, SIW size) {
  return TPrintBinary<COut>(*this, item, size);
}
COut& COut::Binary(const void* start, const void* stop) {
  return TPrintBinary<COut>(
      *this, start,
      reinterpret_cast<const CH1*>(stop) - reinterpret_cast<const CH1*>(start));
}
COut& COut::Binary(SI1 item) {
  return TPrintBinary<COut, SI1, UI1>(*this, item);
}
COut& COut::Binary(UI1 item) { return TPrintBinary<COut, UI1>(*this, item); }
COut& COut::Binary(SI2 item) {
  return TPrintBinary<COut, SI2, UI2>(*this, item);
}
COut& COut::Binary(UI2 item) { return TPrintBinary<COut, UI2>(*this, item); }
COut& COut::Binary(SI4 item) {
  return TPrintBinary<COut, SI4, UI4>(*this, item);
}
COut& COut::Binary(UI4 item) { return TPrintBinary<COut, UI4>(*this, item); }
COut& COut::Binary(SI8 item) {
  return TPrintBinary<COut, SI8, UI8>(*this, item);
}
COut& COut::Binary(UI8 item) { return TPrintBinary<COut, UI8>(*this, item); }
#if USING_FP4 == YES_0
COut& COut::Binary(FP4 item) { return TPrintBinary<COut>(*this, item); }
#endif
#if USING_FP8 == YES_0
COut& COut::Binary(FP8 item) { return TPrintBinary<COut>(*this, item); }
#endif
SIN COut::PrintAndCount(const CH1* string) {
  return TPrintAndCount<COut, CH1>(*this, string);
}
#if USING_UTF16 == YES_0
SIN COut::PrintAndCount(const CH2* string) {
  return TPrintAndCount<COut, CH2>(*this, string);
}
#endif
#if USING_UTF32 == YES_0
SIN COut::PrintAndCount(const CH4* string) {
  return TPrintAndCount<COut, CH4>(*this, string);
}
#endif

COut CPrint(CH1 item) { return COut(item); }
COut CPrint(const CH1* item) { return COut(item); }
#if USING_UTF16 == YES_0
COut CPrint(CH2 item) { return COut(item); }
COut CPrint(const CH2* item) { return COut(item); }
#endif
#if USING_UTF32 == YES_0
COut CPrint(CH4 item) { return COut(item); }
COut CPrint(const CH4* item) { return COut(item); }
#endif

COut CPrint(SI4 item) { return COut(item); }
COut CPrint(UI4 item) { return COut(item); }
COut CPrint(SI8 item) { return COut(item); }
COut CPrint(UI8 item) { return COut(item); }
#if USING_FP4 == YES_0
COut CPrint(FP4 item) { return COut(item); }
#endif
#if USING_FP8 == YES_0
COut CPrint(FP8 item) { return COut(item); }
#endif
COut CPrint(Hexf& item) { return COut(item); }
COut CPrint(Binaryf& item) { return COut(item); }
COut CPrint(Centerf& item) { return COut(item); }
COut CPrint(Rightf& item) { return COut(item); }
COut CPrint(Linef& item) { return COut(item); }
COut CPrint(Headingf& item) { return COut(item); }
COut CPrint(Indentf& item) { return COut(item); }

}  // namespace _

_::COut& operator<<(_::COut& o, CH1 item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, const CH1* item) { return o.Print(item); }
#if USING_UTF16 == YES_0
_::COut& operator<<(_::COut& o, CH2 item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, const CH2* item) { return o.Print(item); }
#endif
#if USING_UTF32 == YES_0
_::COut& operator<<(_::COut& o, CH4 item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, const CH4* item) { return o.Print(item); }
#endif
_::COut& operator<<(_::COut& o, SI4 item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, UI4 item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, SI8 item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, UI8 item) { return o.Print(item); }
#if USING_FP4 == YES_0
_::COut& operator<<(_::COut& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES_0
_::COut& operator<<(_::COut& o, FP8 item) { return o.Print(item); }
#endif
_::COut& operator<<(_::COut& o, _::Hexf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Binaryf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Centerf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Rightf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Linef item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Headingf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Indentf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::Charsf item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, _::COut item) { return o; }

#endif
