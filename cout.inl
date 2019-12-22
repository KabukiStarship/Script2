/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cout.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#if USING_CONSOLE == YES_0

#include "cout.h"
//
#include "puff.hpp"
#include "stringf.hpp"
#include "typevalue.h"
#include "uniprinter.hpp"

//#include <cstdio>
#include <iostream>

#if SEAM == SCRIPT2_UNIPRINTER
#include "_debug.inl"
#else
#include "_release.inl"
#endif

#define STD_COUT std::wcerr

namespace _ {

COut::COut() {}

COut::COut(CHA item) { Print(item); }
COut::COut(const CHA* item) { Print(item); }
#if USING_UTF16 == YES_0
COut::COut(CHB item) { Print(item); }
COut::COut(const CHB* item) { Print(item); }
#endif
#if USING_UTF32 == YES_0
COut::COut(CHC item) { Print(item); }
COut::COut(const CHC* item) { Print(item); }
#endif
COut::COut(ISA item) { Print(item); }
COut::COut(IUA item) { Print(item); }
COut::COut(ISB item) { Print(item); }
COut::COut(IUB item) { Print(item); }
COut::COut(ISC item) { Print(item); }
COut::COut(IUC item) { Print(item); }
COut::COut(ISD item) { Print(item); }
COut::COut(IUD item) { Print(item); }
#if USING_FPC == YES_0
COut::COut(FPC item) { Print(item); }
#endif
#if USING_FPD == YES_0
COut::COut(FPD item) { Print(item); }
#endif
COut::COut(Hexf item) { Print(item); }
COut::COut(Binaryf item) { Print(item); }
COut::COut(Centerf item) { Print(item); }
COut::COut(Rightf item) { Print(item); }
COut::COut(Linef item) { Print(item); }
COut::COut(Headingf item) { Print(item); }
COut::COut(Indentf item) { Print(item); }
COut::COut(Charsf item) { Print(item); }

COut::COut(const CHA* item, CHA second_item) {
  Print(item);
  Print(second_item);
}

COut::COut(const CHA* item, const CHA* second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CHA item, CHA second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CHA item, const CHA* second_item) {
  Print(item);
  Print(second_item);
}
COut::COut(CHA item, CHA second_item, CHA third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(CHA item, CHA second_item, const CHA* third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(const CHA* item, const CHA* second_item, CHA third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut::COut(const CHA* item, const CHA* second_item, const CHA* third_item) {
  Print(item);
  Print(second_item);
  Print(third_item);
}
COut& COut::Star() { return *this; }

COut& COut::Print(CHA item) {
  STD_COUT << item;
  return *this;
}

COut& COut::Print(const CHA* item) {
  return TSPrintString<COut, CHA>(*this, item);
}

#if USING_UTF16 == YES_0
COut& COut::Print(CHB item) {
  STD_COUT << (CHN)item;
  return *this;
}

COut& COut::Print(const CHB* item) {
  return TSPrintString<COut, CHB>(*this, item);
}

#endif
#if USING_UTF32 == YES_0
COut& COut::Print(CHC item) {
  if (item >= (CHC(1) << 9)) {
    STD_COUT << (CHN)(item & 0x3f) + 0xD800;
    STD_COUT << (CHN)((item >> 10) & 0x3f) + 0xDC00;
  } else {
    STD_COUT << (CHN)item;
  }
  return *this;
}
COut& COut::Print(const CHC* item) {
  return TSPrintString<COut, CHC>(*this, item);
}
#endif

COut& COut::Print(ISC item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
#if ALU_SIZE == ALU_64_BIT
  Print((ISD)item);
#else
  enum { cSize = 24 };
  CHA socket[cSize];
  TSPrintSigned<ISD, IUD, CHA>(socket, cSize - 1, (ISD)value);
  Print(socket);
#endif
#endif
  return *this;
}

COut& COut::Print(IUC item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
#if ALU_SIZE == ALU_64_BIT
  Print((IUD)item);
#else
  enum { cSize = 24 };
  CHA buffer[cSize];
  TSPrintUnsigned<IUC, CHA>(buffer, cSize - 1, item);
  Print(buffer);
#endif
#endif
  return *this;
}

COut& COut::Print(ISD item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
  enum { cSize = 24 };
  CHA buffer[cSize];
  TSPrintSigned<ISD, IUD, CHA>(buffer, cSize - 1, item);
  Print(buffer);
#endif
  return *this;
}

COut& COut::Print(IUD item) {
#if SEAM <= SCRIPT2_ITOS
  STD_COUT << item;
#else
  enum { cSize = 24 };
  CHA buffer[cSize];
  TSPrintUnsigned<IUD, CHA>(buffer, cSize - 1, item);
  Print(buffer);
#endif
  return *this;
}

#if USING_FPC == YES_0
COut& COut::Print(FPC item) {
#if SEAM <= SCRIPT2_BOOK
  STD_COUT << item;
#else
  enum { cSize = 16 };
  CHA buffer[cSize];
  TPrintFloat<FPC, IUC, CHA>(buffer, cSize, value);
  Print(buffer);
#endif
  return *this;
}
#endif
#if USING_FPD == YES_0
COut& COut::Print(FPD item) {
#if SEAM <= SCRIPT2_BOOK
  STD_COUT << item;
#else
  enum { cSize = 24 };
  CHA buffer[cSize];
  TPrintFloat<FPD, IUD, CHA>(buffer, cSize - 1, item);
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
COut& COut::NL(CHA item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CHA* item) {
  NL();
  return Print(item);
}
#if USING_UTF16 == YES_0
COut& COut::NL(CHB item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CHB* item) {
  NL();
  return Print(item);
}
#endif
#if USING_UTF32 == YES_0
COut& COut::NL(CHC item) {
  NL();
  return Print(item);
}
COut& COut::NL(const CHC* item) {
  NL();
  return Print(item);
}
#endif
COut& COut::NL(ISC item) {
  NL();
  return Print(item);
}
COut& COut::NL(IUC item) {
  NL();
  return Print(item);
}
COut& COut::NL(ISD item) {
  NL();
  return Print(item);
}
COut& COut::NL(IUD item) {
  NL();
  return Print(item);
}
#if USING_FPC == YES_0
COut& COut::NL(FPC item) {
  NL();
  return Print(item);
}
#endif
#if USING_FPD == YES_0
COut& COut::NL(FPD item) {
  NL();
  return Print(item);
}
#endif

COut& COut::Hex(const void* item) { return TPrintHex<COut>(*this, item); }
COut& COut::Hex(const void* item, ISW size) {
  return TPrintHex<COut>(*this, item, size);
}
COut& COut::Hex(const void* item, const void* item_stop) {
  return TPrintHex<COut>(*this, item, item_stop);
}
COut& COut::Hex(ISA item) { return TPrintHex<COut, ISA, IUA>(*this, item); }
COut& COut::Hex(IUA item) { return TPrintHex<COut, IUA>(*this, item); }
COut& COut::Hex(ISB item) { return TPrintHex<COut, ISB, IUB>(*this, item); }
COut& COut::Hex(IUB item) { return TPrintHex<COut, IUB>(*this, item); }
COut& COut::Hex(ISC item) { return TPrintHex<COut, ISC, IUC>(*this, item); }
COut& COut::Hex(IUC item) { return TPrintHex<COut, IUC>(*this, item); }
COut& COut::Hex(ISD item) { return TPrintHex<COut, ISD, IUD>(*this, item); }
COut& COut::Hex(IUD item) { return TPrintHex<COut, IUD>(*this, item); }
#if USING_FPC == YES_0
COut& COut::Hex(FPC item) { return TPrintHex<COut>(*this, item); }
#endif
#if USING_FPD == YES_0
COut& COut::Hex(FPD item) { return TPrintHex<COut>(*this, item); }
#endif

/* Stores the given item to the buffer and store the size. */
COut& COut::Binary(const void* item) { return TPrintBinary<COut>(*this, item); }
COut& COut::Binary(const void* item, ISW size) {
  return TPrintBinary<COut>(*this, item, size);
}
COut& COut::Binary(const void* start, const void* stop) {
  return TPrintBinary<COut>(
      *this, start,
      reinterpret_cast<const CHA*>(stop) - reinterpret_cast<const CHA*>(start));
}
COut& COut::Binary(ISA item) {
  return TPrintBinary<COut, ISA, IUA>(*this, item);
}
COut& COut::Binary(IUA item) { return TPrintBinary<COut, IUA>(*this, item); }
COut& COut::Binary(ISB item) {
  return TPrintBinary<COut, ISB, IUB>(*this, item);
}
COut& COut::Binary(IUB item) { return TPrintBinary<COut, IUB>(*this, item); }
COut& COut::Binary(ISC item) {
  return TPrintBinary<COut, ISC, IUC>(*this, item);
}
COut& COut::Binary(IUC item) { return TPrintBinary<COut, IUC>(*this, item); }
COut& COut::Binary(ISD item) {
  return TPrintBinary<COut, ISD, IUD>(*this, item);
}
COut& COut::Binary(IUD item) { return TPrintBinary<COut, IUD>(*this, item); }
#if USING_FPC == YES_0
COut& COut::Binary(FPC item) { return TPrintBinary<COut>(*this, item); }
#endif
#if USING_FPD == YES_0
COut& COut::Binary(FPD item) { return TPrintBinary<COut>(*this, item); }
#endif
ISN COut::PrintAndCount(const CHA* string) {
  return TPrintAndCount<COut, CHA>(*this, string);
}
#if USING_UTF16 == YES_0
ISN COut::PrintAndCount(const CHB* string) {
  return TPrintAndCount<COut, CHB>(*this, string);
}
#endif
#if USING_UTF32 == YES_0
ISN COut::PrintAndCount(const CHC* string) {
  return TPrintAndCount<COut, CHC>(*this, string);
}
#endif

COut CPrint(CHA item) { return COut(item); }
COut CPrint(const CHA* item) { return COut(item); }
#if USING_UTF16 == YES_0
COut CPrint(CHB item) { return COut(item); }
COut CPrint(const CHB* item) { return COut(item); }
#endif
#if USING_UTF32 == YES_0
COut CPrint(CHC item) { return COut(item); }
COut CPrint(const CHC* item) { return COut(item); }
#endif

COut CPrint(ISC item) { return COut(item); }
COut CPrint(IUC item) { return COut(item); }
COut CPrint(ISD item) { return COut(item); }
COut CPrint(IUD item) { return COut(item); }
#if USING_FPC == YES_0
COut CPrint(FPC item) { return COut(item); }
#endif
#if USING_FPD == YES_0
COut CPrint(FPD item) { return COut(item); }
#endif
COut CPrint(Hexf& item) { return COut(item); }
COut CPrint(Binaryf& item) { return COut(item); }
COut CPrint(Centerf& item) { return COut(item); }
COut CPrint(Rightf& item) { return COut(item); }
COut CPrint(Linef& item) { return COut(item); }
COut CPrint(Headingf& item) { return COut(item); }
COut CPrint(Indentf& item) { return COut(item); }

}  // namespace _

_::COut& operator<<(_::COut& o, CHA item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, const CHA* item) { return o.Print(item); }
#if USING_UTF16 == YES_0
_::COut& operator<<(_::COut& o, CHB item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, const CHB* item) { return o.Print(item); }
#endif
#if USING_UTF32 == YES_0
_::COut& operator<<(_::COut& o, CHC item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, const CHC* item) { return o.Print(item); }
#endif
_::COut& operator<<(_::COut& o, ISC item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, IUC item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, ISD item) { return o.Print(item); }
_::COut& operator<<(_::COut& o, IUD item) { return o.Print(item); }
#if USING_FPC == YES_0
_::COut& operator<<(_::COut& o, FPC item) { return o.Print(item); }
#endif
#if USING_FPD == YES_0
_::COut& operator<<(_::COut& o, FPD item) { return o.Print(item); }
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
