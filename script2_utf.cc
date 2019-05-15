/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_strand.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if SEAM >= SCRIPT2_3
#if SEAM == SCRIPT2_3
#include "module_release.inl"
#else
#include "module_release.inl"
#endif

#include "t_strand.h"

#if USING_UTF8 == YES

namespace _ {

/*
SI4 COutHeap1(CObject& obj, SIW function, void* arg) {
  return TCOutHeap<CH1>(obj, function, arg);
}*/

const CH1* StringEmpty() { return TSTREmpty<CH1>(); }

const CH1* StringNL() { return TSTRNL<CH1>(); }

const CH1* StringError() { return TSTRError<CH1>(); }

BOL IsWhitespace(CH1 item) { return TIsWhitespace<CH1>(item); }

CH1 PrintableChar(CH1 item) { return TPrintableChar<CH1>(item); }

const CH1* STREnd(const CH1* start) { return TSTREnd<CH1>(start); }

SI4 StrandLength(const CH1* start) { return TSTRLength<CH1, SI4>(start); }

const CH1* StrandLineEnd(const CH1* start, SI4 count) {
  return TSTRLineEnd<CH1>(start, count);
}

const CH1* StrandLineEnd(const CH1* start, const CH1* stop, SI4 count) {
  return TSTRLineEnd<CH1>(start, stop, count);
}

const CH1* StrandDecimalStop(const CH1* start, const CH1* stop) {
  return TSTRDecimalEnd<CH1>(start);
}

const CH1* StrandDecimalStop(const CH1* start) {
  return TSTRDecimalEnd<CH1>(start);
}

const CH1* STRSkipChar(const CH1* start, CH1 skip_char) {
  return TSTRSkipChar<CH1>(start, skip_char);
}

const CH1* STRSkipSpaces(const CH1* start) {
  return TSTRSkipSpaces<CH1>(start);
}

const CH1* STRSkipSpaces(const CH1* start, const CH1* stop) {
  return TSTRSkipSpaces<CH1>(start, stop);
}

const CH1* STREquals(const CH1* text_a, const CH1* text_b) {
  return TSTREquals<CH1>(text_a, text_b);
}

const CH1* STREquals(const CH1* start, const CH1* stop, const CH1* query) {
  return TSTREquals<CH1>(start, stop, query);
}

SI4 STRCompare(const CH1* text_a, const CH1* text_b) {
  return TSTRCompare<CH1>(text_a, text_b);
}
/*
SI4 STRCompare(const CH1* text_a, const CH1* stop,
                  const CH1* text_b) {
  return TSTRCompare<CH1>(text_a, stop, text_b);
}*/

const CH1* STRFind(const CH1* start, const CH1* query) {
  return TSTRFind<CH1>(start, query);
}

CH1* Print(CH1* start, CH1* stop, const CH1* item) {
  return TPrint<CH1>(start, stop, item);
}

#if USING_UTF16 == YES
CH1* Print(CH1* start, CH1* stop, const CH2* item) {
  return TPrint<CH1>(start, stop, item);
}
#endif

#if USING_UTF32 == YES
CH1* Print(CH1* start, CH1* stop, const CH4* item) {
  return TPrint<CH1>(start, stop, item);
}
#endif

CH1* Print(CH1* start, CH1* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH1>(start, stop, item);
}

CH1* Print(CH1* start, CH1* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH1>(start, stop, item);
}

#if ALU_SIZE != 32
CH1* Print(CH1* start, CH1* stop, UI4 item) {
  return Print(start, stop, (UI8)item);
}

CH1* Print(CH1* start, CH1* stop, SI4 item) {
  return Print(start, stop, (SI8)item);
}
#else
CH1* Print(CH1* start, CH1* stop, UI4 item) {
  return TPrintUnsigned<UI8, CH1>(start, stop, (UI8)item);
}

CH1* Print(CH1* start, CH1* stop, SI4 item) {
  return TPrintSigned<SI8, UI8, CH1>(start, stop, (SI8)item);
}
#endif

#if USING_FP4 == YES
CH1* PrintCenter(CH1* start, CH1* stop, FP4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, FP4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}
#endif
#if USING_FP8 == YES
CH1* PrintCenter(CH1* start, CH1* stop, FP8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, FP8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

#endif

CH1* PrintCenter(CH1* start, CH1* stop, const CH1* begin, SI4 count) {
  return TPrintCenter<CH1>(start, stop, begin, count);
}

CH1* PrintCenter(CH1* start, CH1* stop, CH1 item, SI4 count) {
  return TPrintCenter<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, SI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, UI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, UI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, SI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintRight<CH1>(start, stop, item, count);
}

CH1* PrintRight(CH1* start, CH1* stop, CH1 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, UI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, SI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, UI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, SI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).Get(), count);
}

CH1* PrintHex(CH1* start, CH1* stop, const void* ptr) {
  return TPrintHex<CH1>(start, stop, ptr);
}

CH1* PrintHex(CH1* start, CH1* stop, UI1 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI1 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, UI2 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI2 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, UI4 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI4 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, UI8 item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, SI8 item) {
  return TPrintHex<CH1>(start, stop, item);
}

#if USING_FP4 == YES
CH1* PrintHex(CH1* start, CH1* stop, FP4 item) {
  return TPrintHex<CH1>(start, stop, item);
}
#endif
#if USING_FP8 == YES
CH1* PrintHex(CH1* start, CH1* stop, FP8 item) {
  return TPrintHex<CH1>(start, stop, item);
}
#endif

CH1* PrintBinary(CH1* start, CH1* stop, const void* ptr) {
  return TPrintBinary<CH1>(start, stop, ptr);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI1 item) {
  return TPrintBinary<CH1, UI1>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI1 item) {
  return TPrintBinary<CH1, UI1>(start, stop, (UI1)item);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI2 item) {
  return TPrintBinary<CH1, UI2>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI2 item) {
  return TPrintBinary<CH1, UI2>(start, stop, (UI2)item);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI4 item) {
  return TPrintBinary<CH1, UI4>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI4 item) {
  return TPrintBinary<CH1, UI4>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, UI8 item) {
  return TPrintBinary<CH1, UI8>(start, stop, item);
}

CH1* PrintBinary(CH1* start, CH1* stop, SI8 item) {
  return TPrintBinary<CH1, UI8>(start, stop, item);
}

#if USING_FP4 == YES
CH1* PrintBinary(CH1* start, CH1* stop, FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<CH1, UI4>(start, stop, ui);
}
#endif
#if USING_FP8 == YES
CH1* PrintBinary(CH1* start, CH1* stop, FP8 item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<CH1, UI8>(start, stop, ui);
}
#endif
CH1* PrintChars(CH1* start, CH1* stop, const void* begin, const void* end) {
  return TPrintSocket<CH1>(start, stop, begin, end);
}

CH1* PrintChars(CH1* start, CH1* stop, const void* begin, SIW size) {
  const CH1* ptr = reinterpret_cast<const CH1*>(begin);
  return PrintChars(start, stop, begin, ptr + size - 1);
}

CH1* PrintLinef(CH1* start, CH1* stop, CH1 token, SI4 count) {
  return TPrintLinef<CH1>(start, stop, token, count);
}

CH1* PrintLinef(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintLinef<CH1>(start, stop, item, count);
}

CH1* PrintRepeat(CH1* start, CH1* stop, CH1 token, SI4 count) {
  return TPrintHeadingf<CH1>(start, stop, token, count);
}

CH1* PrintRepeat(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintHeadingf<CH1>(start, stop, item, count);
}

const CH1* Scan(const CH1* start, SI1& result) {
  return TScanSigned<SI1, UI1, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI1& result) {
  return TScanUnsigned<UI1, CH1>(start, result);
}

const CH1* Scan(const CH1* start, SI2& result) {
  return TScanSigned<SI2, UI2, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI2& result) {
  return TScanUnsigned<UI2, CH1>(start, result);
}

const CH1* Scan(const CH1* start, SI4& result) {
  return TScanSigned<SI4, UI4, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI4& result) {
  return TScanUnsigned<UI4, CH1>(start, result);
}

const CH1* Scan(const CH1* start, SI8& result) {
  return TScanSigned<SI8, UI8, CH1>(start, result);
}

const CH1* Scan(const CH1* start, UI8& result) {
  return TScanUnsigned<UI8, CH1>(start, result);
}

Token1::Token1(const CH1* item, SI4 count) : string_(item), count_(count) {
  Print(item);
}

#if USING_UTF16 == YES
Token1::Token1(CH2 item, SI4 count) : string_(strand_), count_(count) {
  Print(item);
}

Token1::Token1(const CH2* item, SI4 count) : string_(strand_), count_(count) {}
#endif

#if USING_UTF32 == YES
Token1::Token1(CH4 item, SI4 count) : string_(strand_), count_(count) {
  Print(item);
}

Token1::Token1(const CH4* item, SI4 count) : count_(count) { Print(item); }
#endif

Token1::Token1(SI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token1::Token1(UI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token1::Token1(SI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token1::Token1(UI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

#if USING_FP4 == YES
Token1::Token1(FP4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif
#if USING_FP8 == YES
Token1::Token1(FP8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif

const CH1* Token1::String() { return string_; }

CH1* Token1::Strand() { return strand_; }

const CH1* Token1::Set(const CH1* string) {
  if (!string) return string;
  string_ = string;
  return string;
}

const CH1* Token1::Get() {
  const CH1* string = string_;
  return string ? string : strand_;
}

SI4 Token1::Count() { return count_; }

CH1* Token1::Print(CH1 item) {
  return ::_::Print(strand_, strand_ + kTokenLongest, item);
}

CH1* Token1::Print(const CH1* item) {
  CH1* cursor = ::_::TPrint<CH1>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#if USING_UTF16 == YES
CH1* Token1::Print(CH2 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(const CH2* item) {
  CH1* cursor = ::_::TPrint<CH1>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_UTF32 == YES
CH1* Token1::Print(CH4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(const CH4* item) {
  CH1* cursor = ::_::TPrint<CH1>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

CH1* Token1::Print(SI4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(UI4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(SI8 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH1* Token1::Print(UI8 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#if USING_FP4 == YES
CH1* Token1::Print(FP4 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_FP8 == YES
CH1* Token1::Print(FP8 item) {
  CH1* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

Center1::Center1(CH1 item, SI4 count) : token(item, count) {}

Center1::Center1(const CH1* item, SI4 count) : token(item, count) {}

#if USING_UTF16 == YES
Center1::Center1(CH2 item, SI4 count) : token(item, count) {}

Center1::Center1(const CH2* item, SI4 count) : token(item, count) {}
#endif

#if USING_UTF32 == YES
Center1::Center1(CH4 item, SI4 count) : token(item, count) {}

Center1::Center1(const CH4* item, SI4 count) : token(item, count) {}
#endif

Center1::Center1(SI4 item, SI4 count) : token(item, count) {}

Center1::Center1(UI4 item, SI4 count) : token(item, count) {}

Center1::Center1(SI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Center1::Center1(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Center1::Center1(FP8 item, SI4 count) : token(item, count) {}
#endif

Center1::Center1(UI8 item, SI4 count) : token(item, count) {}

Right1::Right1(CH1 item, SI4 count) : token(item, count) {}

Right1::Right1(const CH1* item, SI4 count) : token(item, count) {}

#if USING_UTF16 == YES
Right1::Right1(CH2 item, SI4 count) : token(item, count) {}

Right1::Right1(const CH2* item, SI4 count) : token(item, count) {}
#endif
#if USING_UTF32 == YES
Right1::Right1(CH4 item, SI4 count) : token(item, count) {}

Right1::Right1(const CH4* item, SI4 count) : token(item, count) {}
#endif

Right1::Right1(SI4 item, SI4 count) : token(item, count) {}

Right1::Right1(UI4 item, SI4 count) : token(item, count) {}

Right1::Right1(SI8 item, SI4 count) : token(item, count) {}

Right1::Right1(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Right1::Right1(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Right1::Right1(FP8 item, SI4 count) : token(item, count) {}
#endif

Linef1::Linef1(CH1 item, SI4 count) : token(token.Strand(), count) {
  CH1* strand = token.Strand();
  TPrint<CH1>(strand, strand + kTokenLongest, item);
}

Linef1::Linef1(const CH1* item, SI4 count) : token(token.Strand(), count) {
  CH1* strand = token.Strand();
  TPrint<CH1>(strand, strand + kTokenLongest, item);
}

Headingf1::Headingf1(const CH1* caption1, const CH1* style, SI4 count,
                     const CH1* caption2, const CH1* caption3)
    : caption(caption1, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Chars1::Chars1(const CH1* start, const CH1* stop) : start(start), stop(stop) {}

UTF1::UTF1(CH1* start, SIW buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  DASSERT(start);
  DASSERT(buffer_size);
}

UTF1::UTF1(CH1* begin, CH1* stop) : start(start), stop(stop) {
  DASSERT(begin);
  DASSERT(begin < stop);
}

UTF1::UTF1(const UTF1& other) : start(other.start), stop(other.stop) {
  DASSERT(start);
  DASSERT(stop);
}

UTF1& UTF1::Set(CH1* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF1& UTF1::PrintChar(CH1 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(CH1 item) { return PrintChar(item); }

UTF1& UTF1::PrintChar(CH2 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(CH2 item) { return PrintChar(item); }

UTF1& UTF1::PrintChar(CH4 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(CH4 item) { return PrintChar(item); }

UTF1& UTF1::Print(const CH1* item) {
  return Set(::_::Print(start, stop, item));
}

UTF1& UTF1::Print(const CH2* item) {
  return Set(::_::Print(start, stop, item));
}

UTF1& UTF1::Print(const CH4* item) {
  return Set(::_::Print(start, stop, item));
}

UTF1& UTF1::Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

UTF1& UTF1::Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
UTF1& UTF1::Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
#endif
#if USING_FP8 == YES
UTF1& UTF1::Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
#endif

UTF1& UTF1::Print(Right1 item) {
  return Set(
      ::_::PrintRight(start, stop, item.token.Get(), item.token.Count()));
}

UTF1& UTF1::Print(Center1 item) {
  return Set(
      ::_::PrintCenter(start, stop, item.token.Get(), item.token.Count()));
}

UTF1& UTF1::Print(Linef1 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.token.Get(), item.token.Count()));
}

UTF1& UTF1::Print(Headingf1 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.caption.Get(), item.caption.Count()));
}

UTF1& UTF1::Hex(UI1 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI1 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI2 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI2 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

#if USING_FP4 == YES
UTF1& UTF1::Hex(FP4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }
#endif
#if USING_FP8 == YES
UTF1& UTF1::Hex(FP8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }
#endif

template <typename T, typename Char = CH1>
Char* TPrintHex(Char* start, Char* stop, const void* begin, SIW size_bytes) {
  Char* end = start + (size_bytes * 2);
  if (!start || size_bytes <= 0 || LoopAround(end, start)) return nullptr;
  const UI1* cursor = reinterpret_cast<const UI1*>(begin);
  while (size_bytes-- > 0) {
    UI1 byte = *cursor++;
    *start++ = HexNibbleToUpperCase(byte >> 4);
    *start++ = HexNibbleToUpperCase(byte & 0xf);
  }
  *start = 0;
  return start;
}

UTF1& UTF1::Hex(const void* ptr) {
  return Set(TPrintHex<CH1>(start, stop, ptr));
}

UTF1& UTF1::Print(::_::Hex item) {
  return Set(TPrintHex<CH1>(start, stop, item.buffer, item.byte_count));
}

UTF1& UTF1::Binary(UI1 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI1 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(UI2 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI2 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(UI4 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI4 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(UI8 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

UTF1& UTF1::Binary(SI8 item) {
  return Set(TPrintBinary<CH1>(start, stop, item));
}

#if USING_FP4 == YES
UTF1& UTF1::Binary(FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH1>(start, stop, ui));
}
#endif
#if USING_FP8 == YES
UTF1& UTF1::Binary(FP8 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH1>(start, stop, ui));
}
#endif

UTF1& UTF1::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH1>(start, stop, ptr));
}

UTF1& UTF1::Print(Chars1 chars) {
  return Set(TPrintChars<CH1>(start, stop, chars.start, chars.stop));
}

Token1::Token1(CH1 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH1>(strand_, item);
}

/*
UIW* COut1(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1>(begin, function, arg);
}

UIW* COut1Auto(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1, kHeap>(begin, function, arg);
}*/

}  // namespace _

::_::UTF1& operator<<(::_::UTF1& o, CH1 item) { return o.PrintChar(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::UTF1& p) { return o; }

::_::UTF1& operator<<(::_::UTF1& o, const CH1* item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, SI2 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI2 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, SI4 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI4 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, SI8 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::UTF1& operator<<(::_::UTF1& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES
::_::UTF1& operator<<(::_::UTF1& o, FP8 item) { return o.Print(item); }
#endif

::_::UTF1& operator<<(::_::UTF1& o, ::_::Hex item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Center1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Right1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Linef1 item) { return o.Print(item); }

::_::UTF1& operator<<(::_::UTF1& o, ::_::Headingf1 item) {
  return o.Print(item);
}

::_::UTF1& operator<<(::_::UTF1& o, ::_::Chars1 item) { return o.Print(item); }

#if USING_UTF16 == YES
::_::UTF1& operator*(::_::UTF1& o, CH2 item) { return o.Print(item); }
::_::UTF1& operator*=(::_::UTF1& o, CH2 item) { return o.Print(item); }
::_::UTF1& operator*(::_::UTF1& o, const CH2* item) { return o.Print(item); }
#endif
#if USING_UTF32 == YES
::_::UTF1& operator<<(::_::UTF1& o, CH4 item) { return o.PrintChar(item); }

::_::UTF1& operator*(::_::UTF1& o, const CH4* item) { return o.Print(item); }
#endif

#endif  //< #if USING_UTF8

#if USING_UTF16 == YES
namespace _ {

SI4 COutHeap2(CObject& obj, SIW function, void* arg) {
  return TCOutHeap<CH2>(obj, function, arg);
}

const CH2* Empty() { return TSTREmpty<CH2>(); }

const CH2* NewLine() { return TSTRNL<CH2>(); }

const CH2* ErrorHeader() { return TSTRError<CH2>(); }

BOL IsWhitespace(CH2 item) { return TIsWhitespace<CH2>(item); }

CH2 PrintableChar(CH2 item) { return TPrintableChar<CH2>(item); }

const CH2* STREnd(const CH2* start) { return TSTREnd<CH2>(start); }

SI4 StrandLength(const CH2* start) { return TSTRLength<CH2, SI4>(start); }

const CH2* StrandLineEnd(const CH2* start, SI4 count) {
  return TSTRLineEnd<CH2>(start, count);
}

const CH2* StrandLineEnd(const CH2* start, const CH2* stop, SI4 count) {
  return TSTRLineEnd<CH2>(start, stop, count);
}

const CH2* StrandDecimalEnd(const CH2* start, const CH2* stop) {
  return TSTRDecimalEnd<CH2>(start, stop);
}

const CH2* StrandDecimalEnd(const CH2* start) {
  return TSTRDecimalEnd<CH2>(start);
}

const CH2* STRSkipChar(const CH2* start, CH2 skip_char) {
  return TSTRSkipChar<CH2>(start, skip_char);
}

const CH2* STRSkipSpaces(const CH2* start) {
  return TSTRSkipSpaces<CH2>(start);
}

const CH2* STRSkipSpaces(const CH2* start, const CH2* stop) {
  return TSTRSkipSpaces<CH2>(start, stop);
}

const CH2* STREquals(const CH2* text_a, const CH2* text_b) {
  return TSTREquals<CH2>(text_a, text_b);
}

const CH2* STREquals(const CH2* start, const CH2* stop, const CH2* query) {
  return TSTREquals<CH2>(start, stop, query);
}

SI4 STRCompare(const CH2* text_a, const CH2* text_b) {
  return TSTRCompare<CH2>(text_a, text_b);
}

const CH2* STRFind(const CH2* start, const CH2* query) {
  return TSTRFind<CH2>(start, query);
}

#if USING_UTF8 == YES
CH2* Print(CH2* start, CH2* stop, const CH1* item) {
  return TPrint<CH2>(start, stop, item);
}
#endif

CH2* Print(CH2* start, CH2* stop, const CH2* item) {
  return TPrint<CH2>(start, stop, item);
}

#if USING_UTF32 == YES
CH2* Print(CH2* start, CH2* stop, const CH4* item) {
  return TPrint<CH2>(start, stop, item);
}
#endif

CH2* Print(CH2* start, CH2* stop, UI4 item) {
  return TPrintUnsigned<UI4, CH2>(start, stop, item);
}

CH2* Print(CH2* start, CH2* stop, SI4 item) {
  return TPrintSigned<SI4, UI4, CH2>(start, stop, item);
}

CH2* Print(CH2* start, CH2* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH2>(start, stop, item);
}

CH2* Print(CH2* start, CH2* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH2>(start, stop, item);
}

CH2* PrintCenter(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintCenter<CH2>(start, stop, item, count);
}

CH2* PrintCenter(CH2* start, CH2* stop, CH2 item, SI4 count) {
  return TPrintCenter<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, SI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, UI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, UI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, SI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

#if USING_FP4 == YES
CH2* PrintCenter(CH2* start, CH2* stop, FP4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintRight(CH2* start, CH2* stop, FP4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintHex(CH2* start, CH2* stop, FP4 item) {
  return TPrintHex<CH2>(start, stop, item);
}
CH2* PrintBinary(CH2* start, CH2* stop, FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Print(start, stop, ui);
}
const CH2* Scan(const CH2* start, FP4& result) {
  return TScan<CH2>(start, result);
}
#endif
#if USING_FP8 == YES
CH2* PrintCenter(CH2* start, CH2* stop, FP8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintRight(CH2* start, CH2* stop, FP8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
CH2* PrintHex(CH2* start, CH2* stop, FP8 item) {
  return TPrintHex<CH2>(start, stop, item);
}
CH2* PrintBinary(CH2* start, CH2* stop, FP8 item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return Print(start, stop, ui);
}
const CH2* Scan(const CH2* start, FP8& result) {
  return TScan<CH2>(start, result);
}
#endif

CH2* PrintRight(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintRight<CH2>(start, stop, item, count);
}

CH2* PrintRight(CH2* start, CH2* stop, CH2 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, UI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, SI4 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, UI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, SI8 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintHex(CH2* start, CH2* stop, const void* ptr) {
  return TPrintHex<CH2>(start, stop, ptr);
}

CH2* PrintHex(CH2* start, CH2* stop, UI1 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI1 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, UI2 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI2 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, UI4 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI4 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, UI8 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, SI8 item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, const void* ptr) {
  return TPrintBinary<CH2>(start, stop, ptr);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI1 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI1 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI2 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI2 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI4 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI4 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, UI8 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintBinary(CH2* start, CH2* stop, SI8 item) {
  return TPrintBinary<CH2>(start, stop, item);
}

CH2* PrintChars(CH2* start, CH2* stop, const void* begin, const void* end) {
  return TPrintSocket<CH2>(start, stop, begin, end);
}

CH2* PrintChars(CH2* start, CH2* stop, const void* begin, SIW size) {
  const CH1* end = reinterpret_cast<const CH1*>(begin) + size - 1;
  return PrintChars(start, stop, begin, end);
}

CH2* PrintLinef(CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintLinef<CH2>(start, stop, token, count);
}

CH2* PrintLinef(CH2* start, CH2* stop, const CH2* token, SI4 count) {
  return TPrintLinef<CH2>(start, stop, token, count);
}

CH2* PrintRepeat(CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, token, count);
}

CH2* PrintRepeat(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, item, count);
}

CH2* PrintHeadingf(CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, token, count);
}

CH2* PrintHeadingf(CH2* start, CH2* stop, const CH2* token, SI4 count) {
  return TPrintHeadingf<CH2>(start, stop, token, count);
}

const CH2* Scan(const CH2* start, SI1& result) {
  return TScanSigned<SI1, UI1, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI1& result) {
  return TScanUnsigned<UI1, CH2>(start, result);
}

const CH2* Scan(const CH2* start, SI2& result) {
  return TScanSigned<SI2, UI2, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI2& result) {
  return TScanUnsigned<UI2, CH2>(start, result);
}

const CH2* Scan(const CH2* start, SI4& result) {
  return TScanSigned<SI4, UI4, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI4& result) {
  return TScanUnsigned<UI4, CH2>(start, result);
}

const CH2* Scan(const CH2* start, SI8& result) {
  return TScanSigned<SI8, UI8, CH2>(start, result);
}

const CH2* Scan(const CH2* start, UI8& result) {
  return TScanUnsigned<UI8, CH2>(start, result);
}

/*
void COut2(UIW* begin) { return TCOut<CH2>(begin); }

void COut2Auto(UIW* begin) { return TCOutAuto<CH2>(begin); }*/

UTF2::UTF2(CH2* start, SIW buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF2::UTF2(CH2* start, CH2* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF2::UTF2(const UTF2& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF2& UTF2::Set(CH2* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF2& UTF2::PrintChar(CH1 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(CH1 item) { return PrintChar(item); }

UTF2& UTF2::PrintChar(CH2 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(CH2 item) { return PrintChar(item); }

UTF2& UTF2::PrintChar(CH4 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(CH4 item) { return PrintChar(item); }

UTF2& UTF2::Print(const CH1* item) {
  return Set(::_::Print(start, stop, item));
}

UTF2& UTF2::Print(const CH2* item) {
  return Set(::_::Print(start, stop, item));
}

UTF2& UTF2::Print(const CH4* item) {
  return Set(::_::Print(start, stop, item));
}

UTF2& UTF2::Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

UTF2& UTF2::Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
UTF2& UTF2::Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
UTF2& UTF2::Hex(FP4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }
UTF2& UTF2::Binary(FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH2>(start, stop, ui));
}
#endif
#if USING_FP8 == YES
UTF2& UTF2::Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
UTF2& UTF2::Hex(FP8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }
UTF2& UTF2::Binary(FP8 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH2>(start, stop, ui));
}
#endif

UTF2& UTF2::Print(Right2 item) {
  return Set(
      ::_::PrintRight(start, stop, item.token.Get(), item.token.Count()));
}

UTF2& UTF2::Print(Center2 item) {
  return Set(
      ::_::PrintCenter(start, stop, item.token.Get(), item.token.Count()));
}

UTF2& UTF2::Print(Linef2 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.token.Get(), item.token.Count()));
}

UTF2& UTF2::Print(Headingf2 item) {
  return Set(::_::PrintLinef(start, stop, item.caption.String(),
                             item.caption.Count()));
}

UTF2& UTF2::Print(Chars2 item) {
  return Set(::_::PrintChars(start, stop, item.start, item.stop));
}

UTF2& UTF2::Print(::_::Hex item) {
  return Set(::_::TPrintHex<CH2>(start, stop, item.buffer, item.byte_count));
}

UTF2& UTF2::Hex(UI1 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI1 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI2 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI2 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(const void* item) {
  return Set(TPrintHex<CH2>(start, stop, item));
}

UTF2& UTF2::Hex(const void* item, SIW size_bytes) {
  return Set(TPrintHex<CH2>(start, stop, item, size_bytes));
}

UTF2& UTF2::Binary(UI1 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI1 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(UI2 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI2 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(UI4 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI4 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(UI8 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(SI8 item) {
  return Set(TPrintBinary<CH2>(start, stop, item));
}

UTF2& UTF2::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH2>(start, stop, ptr));
}

Token2::Token2(CH1 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH2>(strand_, item);
}

Token2::Token2(const CH1* item, SI4 count) : string_(strand_), count_(count) {
  if (!Print(item)) *strand_ = 0;
}

Token2::Token2(CH2 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH2>(strand_, item);
}

Token2::Token2(const CH2* item, SI4 count) : string_(item), count_(count) {
  if (!item) *strand_ = 0;
}

#if USING_UTF32
Token2::Token2(CH4 item, SI4 count) : string_(strand_), count_(count) {
  Print(item);
}

Token2::Token2(const CH4* item, SI4 count) : string_(item), count_(count) {
  if (!Print(item)) *strand_ = 0;
}
#endif

Token2::Token2(SI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token2::Token2(UI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token2::Token2(SI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token2::Token2(UI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

#if USING_FP4 == YES
Token2::Token2(FP4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif
#if USING_FP8 == YES
Token2::Token2(FP8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif

const CH2* Token2::String() { return string_; }

CH2* Token2::Strand() { return strand_; }

const CH2* Token2::Get() {
  const CH2* ptr = string_;
  return ptr ? ptr : strand_;
}

const CH2* Token2::Set(const CH2* string) {
  if (!string) return string;
  string_ = string;
  return string;
}

SI4 Token2::Count() { return count_; }

CH2* Token2::Print(CH1 item) {
  return ::_::Print(strand_, strand_ + kTokenLongest, item);
}

CH2* Token2::Print(const CH1* item) {
  CH2* cursor = ::_::TPrint<CH2>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#if USING_UTF16 == YES
CH2* Token2::Print(CH2 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(const CH2* item) {
  CH2* cursor = ::_::TPrint<CH2>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_UTF32 == YES
CH2* Token2::Print(CH4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(const CH4* item) {
  CH2* cursor = ::_::TPrint<CH2>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

CH2* Token2::Print(SI4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(UI4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(SI8 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH2* Token2::Print(UI8 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#if USING_FP4 == YES
CH2* Token2::Print(FP4 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_FP8 == YES
CH2* Token2::Print(FP8 item) {
  CH2* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

Center2::Center2(const CH1* item, SI4 count) : token(item, count) {}

Center2::Center2(CH1 item, SI4 count) : token(item, count) {}

Center2::Center2(const CH2* item, SI4 count) : token(item, count) {}

#if USING_UTF32
Center2::Center2(CH4 item, SI4 count) : token(item, count) {}
Center2::Center2(const CH4* item, SI4 count) : token(item, count) {}
#endif

Center2::Center2(CH2 item, SI4 count) : token(item, count) {}

Center2::Center2(SI4 item, SI4 count) : token(item, count) {}

Center2::Center2(UI4 item, SI4 count) : token(item, count) {}

Center2::Center2(SI8 item, SI4 count) : token(item, count) {}

Center2::Center2(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Center2::Center2(FP4 item, SI4 count) : token_(item, count) {}
#endif
#if USING_FP8 == YES
Center2::Center2(FP8 item, SI4 count) : token_(item, count) {}
#endif

Right2::Right2(CH1 item, SI4 count) : token(item, count) {}

Right2::Right2(const CH1* item, SI4 count) : token(item, count) {}

Right2::Right2(CH2 item, SI4 count) : token(item, count) {}

Right2::Right2(const CH2* item, SI4 count) : token(item, count) {}

#if USING_UTF32
Right2::Right2(CH4 item, SI4 count) : token(item, count) {}

Right2::Right2(const CH4* item, SI4 count) : token(item, count) {}
#endif

Right2::Right2(SI4 item, SI4 count) : token(item, count) {}

Right2::Right2(UI4 item, SI4 count) : token(item, count) {}

Right2::Right2(SI8 item, SI4 count) : token(item, count) {}

Right2::Right2(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Right2::Right2(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Right2::Right2(FP8 item, SI4 count) : token(item, count) {}
#endif

Linef2::Linef2(const CH1* item, SI4 count) : token(token.Strand(), count) {
  CH2* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef2::Linef2(CH1 item, SI4 count) : token(token.Strand(), count) {
  CH2* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef2::Linef2(CH2 item, SI4 count) : token(token.Strand(), count) {
  CH2* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef2::Linef2(const CH2* item, SI4 count) : token(item, count) {}

Headingf2::Headingf2(const CH2* caption, const CH2* style, SI4 count,
                     const CH2* caption2, const CH2* caption3)
    : caption(caption, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

}  // namespace _

::_::UTF2& operator<<(::_::UTF2& o, CH4 item) { return o.PrintChar(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::UTF2& p) { return o; }

::_::UTF2& operator<<(::_::UTF2& o, const CH1* item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, const CH2* item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, const CH4* item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI1 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, SI2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, SI4 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI4 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, SI8 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::UTF2& operator<<(::_::UTF2& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES
::_::UTF2& operator<<(::_::UTF2& o, FP8 item) { return o.Print(item); }
#endif

::_::UTF2& operator<<(::_::UTF2& o, ::_::Hex item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Center2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Right2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Linef2 item) { return o.Print(item); }

::_::UTF2& operator<<(::_::UTF2& o, ::_::Headingf2 item) {
  return o.Print(item);
}

::_::UTF2& operator<<(::_::UTF2& o, ::_::Chars2 item) { return o.Print(item); }
#endif  //< #if USING_UTF16

#if USING_UTF32 == YES
namespace _ {
/*
SI4 COutHeap4 (CObject& obj, SIW function, void* arg) {
  return TCOutHeap<CH4> (obj, function, arg);
}*/

const CH4* EmptyCH4() { return TSTREmpty<CH4>(); }

const CH4* NewLineCH4() { return TSTRNL<CH4>(); }

const CH4* ErrorHeaderCH4() { return TSTRError<CH4>(); }

BOL IsWhitespace(CH4 item) { return TIsWhitespace<CH4>(item); }

CH4 PrintableChar(CH4 item) { return TPrintableChar<CH4>(item); }

const CH4* STREnd(const CH4* start) { return TSTREnd<CH4>(start); }

SI4 StrandLength(const CH4* start) { return TSTRLength<CH4, SI4>(start); }

const CH4* StrandLineEnd(const CH4* start, SI4 count) {
  return TSTRLineEnd<CH4>(start, count);
}

const CH4* StrandLineEnd(const CH4* start, const CH4* stop, SI4 count) {
  return TSTRLineEnd<CH4>(start, stop, count);
}

const CH4* StrandDecimalEnd(const CH4* start, const CH4* stop) {
  return TSTRDecimalEnd<CH4>(start, stop);
}

const CH4* StrandDecimalEnd(const CH4* start) {
  return TSTRDecimalEnd<CH4>(start);
}

const CH4* STRSkipChar(const CH4* start, CH4 skip_char) {
  return TSTRSkipChar<CH4>(start, skip_char);
}

const CH4* STRSkipSpaces(const CH4* start) {
  return TSTRSkipSpaces<CH4>(start);
}

const CH4* STRSkipSpaces(const CH4* start, const CH4* stop) {
  return TSTRSkipSpaces<CH4>(start, stop);
}

const CH4* STREquals(const CH4* text_a, const CH4* text_b) {
  return TSTREquals<CH4>(text_a, text_b);
}

const CH4* STREquals(const CH4* start, const CH4* stop, const CH4* text_b) {
  return TSTREquals<CH4>(start, stop, text_b);
}

/*
BOL TTextQualifies(const CH4* start) { return TTextQualifies<CH4>(start); }

BOL TTextQualifies(const CH4* start, const CH4* stop) {
  return TTextQualifies<CH4>(start, stop);
}*/

SI4 STRCompare(const CH4* text_a, const CH4* text_b) {
  return TSTRCompare<CH4>(text_a, text_b);
}

const CH4* STRFind(const CH4* start, const CH4* item) {
  return TSTRFind<CH4>(start, item);
}

#if USING_UTF8 == YES
CH4* Print(CH4* start, CH4* stop, const CH1* item) {
  return TPrint<CH4>(start, stop, item);
}
#endif

#if USING_UTF16 == YES
CH4* Print(CH4* start, CH4* stop, const CH2* item) {
  return TPrint<CH4>(start, stop, item);
}
#endif

CH4* Print(CH4* start, CH4* stop, const CH4* item) {
  return TPrint<CH4>(start, stop, item);
}

CH4* Print(CH4* start, SIW count, const CH4* item) {
  return TPrint<CH4>(start, count, item);
}

CH4* Print(CH4* start, CH4* stop, UI4 item) {
  return TPrintUnsigned<UI4, CH4>(start, stop, item);
}

CH4* Print(CH4* start, CH4* stop, SI4 item) {
  return TPrintSigned<SI4, UI4, CH4>(start, stop, item);
}

CH4* Print(CH4* start, CH4* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH4>(start, stop, item);
}

CH4* Print(CH4* start, CH4* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH4>(start, stop, item);
}

CH4* PrintCenter(CH4* start, CH4* stop, const CH4* begin, SI4 count) {
  return TPrintCenter<CH4>(start, stop, begin, count);
}

CH4* PrintCenter(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintCenter<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, SI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, UI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, UI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, SI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

#if USING_FP4 == YES
CH4* PrintCenter(CH4* start, CH4* stop, FP4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintRight(CH4* start, CH4* stop, FP4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintHex(CH4* start, CH4* stop, FP4 item) {
  return TPrintHex<CH4>(start, stop, item);
}
CH4* PrintBinary(CH4* start, CH4* stop, FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<CH4, UI8>(start, stop, ui);
}
const CH4* Scan(const CH4* start, FP4& result) {
  return TScan<CH4>(start, result);
}
#endif
#if USING_FP8 == YES
CH4* PrintCenter(CH4* start, CH4* stop, FP8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintRight(CH4* start, CH4* stop, FP8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
CH4* PrintHex(CH4* start, CH4* stop, FP8 item) {
  return TPrintHex<CH4>(start, stop, item);
}
CH4* PrintBinary(CH4* start, CH4* stop, FP8 item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<CH4, UI8>(start, stop, ui);
}
const CH4* Scan(const CH4* start, FP8& result) {
  return TScan<CH4>(start, result);
}
#endif

CH4* PrintRight(CH4* start, CH4* stop, const CH4* begin, SI4 count) {
  return TPrintRight<CH4>(start, stop, begin, count);
}

CH4* PrintRight(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, UI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, SI4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, UI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, SI8 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintHex(CH4* start, CH4* stop, const void* ptr) {
  return TPrintHex<CH4>(start, stop, ptr);
}

CH4* PrintHex(CH4* start, CH4* stop, UI1 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI1 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, UI2 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI2 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, UI4 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI4 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, UI8 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, SI8 item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, const void* ptr) {
  return TPrintBinary<CH4>(start, stop, ptr);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI1 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI1 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI2 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI2 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI4 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI4 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, UI8 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintBinary(CH4* start, CH4* stop, SI8 item) {
  return TPrintBinary<CH4>(start, stop, item);
}

CH4* PrintChars(CH4* start, CH4* stop, const void* begin, const void* end) {
  return TPrintSocket<CH4>(start, stop, begin, end);
}

CH4* PrintChars(CH4* start, CH4* stop, const void* begin, SIW size) {
  const CH4* ptr = reinterpret_cast<const CH4*>(begin);
  return PrintChars(start, stop, begin, ptr + size - 1);
}

CH4* PrintLinef(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintLinef<CH4>(start, stop, item, count);
}

CH4* PrintLinef(CH4* start, CH4* stop, const CH4* item, SI4 count) {
  return TPrintLinef<CH4>(start, stop, item, count);
}

CH4* PrintRepeat(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintHeadingf<CH4>(start, stop, item, count);
}

CH4* PrintRepeat(CH4* start, CH4* stop, const CH4* item, SI4 count) {
  return TPrintHeadingf<CH4>(start, stop, item, count);
}

const CH4* Scan(const CH4* start, SI1& result) {
  return TScanSigned<SI1, UI2, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI1& result) {
  return TScanUnsigned<UI1, CH4>(start, result);
}

const CH4* Scan(const CH4* start, SI2& result) {
  return TScanSigned<SI2, UI2, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI2& result) {
  return TScanUnsigned<UI2, CH4>(start, result);
}

const CH4* Scan(const CH4* start, SI4& result) {
  return TScanSigned<SI4, UI4, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI4& result) {
  return TScanUnsigned<UI4, CH4>(start, result);
}

const CH4* Scan(const CH4* start, SI8& result) {
  return TScanSigned<SI8, UI8, CH4>(start, result);
}

const CH4* Scan(const CH4* start, UI8& result) {
  return TScanUnsigned<UI8, CH4>(start, result);
}

/*
void COut4(UIW* begin) { return TCOut<CH4>(begin); }

void COutAuto4(UIW* begin) { return TCOutAuto<CH4>(begin); }*/

UTF4::UTF4(CH4* start, SIW buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF4::UTF4(CH4* start, CH4* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF4::UTF4(const UTF4& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF4& UTF4::Set(CH4* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF4& UTF4::PrintChar(CH1 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(CH1 item) { return PrintChar(item); }

UTF4& UTF4::PrintChar(CH2 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(CH2 item) { return PrintChar(item); }

UTF4& UTF4::PrintChar(CH4 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(CH4 item) { return PrintChar(item); }

UTF4& UTF4::Print(const CH1* item) {
  return Set(::_::Print(start, stop, item));
}

UTF4& UTF4::Print(const CH2* item) {
  return Set(::_::Print(start, stop, item));
}

UTF4& UTF4::Print(const CH4* item) {
  return Set(::_::Print(start, stop, item));
}

UTF4& UTF4::Print(SI4 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(UI4 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(SI8 item) { return Set(::_::Print(start, stop, item)); }

UTF4& UTF4::Print(UI8 item) { return Set(::_::Print(start, stop, item)); }

#if USING_FP4 == YES
UTF4& UTF4::Print(FP4 item) { return Set(::_::Print(start, stop, item)); }
UTF4& UTF4::Hex(FP4 item) { return Set(TPrintHex<CH4>(start, stop, item)); }
UTF4& UTF4::Binary(FP4 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH4>(start, stop, ui));
}
#endif
#if USING_FP4 == YES
UTF4& UTF4::Print(FP8 item) { return Set(::_::Print(start, stop, item)); }
UTF4& UTF4::Hex(FP8 item) { return Set(TPrintHex<CH4>(start, stop, item)); }
UTF4& UTF4::Binary(FP8 item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH4>(start, stop, ui));
}
#endif

UTF4& UTF4::Print(Right4 item) {
  return Set(
      ::_::PrintRight(start, stop, item.token.Get(), item.token.Count()));
}

UTF4& UTF4::Print(Center4 item) {
  return Set(
      ::_::PrintCenter(start, stop, item.token.Get(), item.token.Count()));
}

UTF4& UTF4::Print(Linef4 item) {
  return Set(
      ::_::PrintLinef(start, stop, item.token.Get(), item.token.Count()));
}

UTF4& UTF4::Print(Headingf4 item) {
  return Set(::_::PrintLinef(start, stop, item.caption.String(),
                             item.caption.Count()));
}

UTF4& UTF4::Print(::_::Hex item) {
  return Set(::_::TPrintHex<CH4>(start, stop, item.buffer, item.byte_count));
}

UTF4& UTF4::Hex(UI1 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI1 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(UI2 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI2 item) {
  return Set(TPrintHex<CH4>(start, stop, (UI2)item));
}

UTF4& UTF4::Hex(UI4 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI4 item) {
  return Set(TPrintHex<CH4>(start, stop, (UI4)item));
}

UTF4& UTF4::Hex(UI8 item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(SI8 item) {
  return Set(TPrintHex<CH4>(start, stop, (UI8)item));
}

UTF4& UTF4::Hex(const void* ptr) {
  return Set(TPrintHex<CH4>(start, stop, ptr));
}

UTF4& UTF4::Binary(UI1 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI1 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(UI2 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI2 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(UI4 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI4 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(UI8 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(SI8 item) {
  return Set(TPrintBinary<CH4>(start, stop, item));
}

UTF4& UTF4::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH4>(start, stop, ptr));
}

Token4::Token4(CH4 item, SI4 count) : string_(strand_), count_(count) {
  TPrint1<CH4>(strand_, item);
}

Token4::Token4(const CH4* item, SI4 count) : string_(item), count_(count) {
  if (!item) *strand_ = 0;
}

Token4::Token4(SI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token4::Token4(UI4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token4::Token4(SI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

Token4::Token4(UI8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}

#if USING_FP4 == YES
Token4::Token4(FP4 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif
#if USING_FP8 == YES
Token4::Token4(FP8 item, SI4 count) : string_(strand_), count_(count) {
  ::_::Print(strand_, strand_ + kTokenLongest, item);
}
#endif

const CH4* Token4::String() { return string_; }

CH4* Token4::Strand() { return strand_; }

const CH4* Token4::SetString(const CH4* ptr) {
  string_ = ptr;
  return ptr;
}

const CH4* Token4::Get() {
  const CH4* ptr = string_;
  return ptr ? ptr : strand_;
}

SI4 Token4::Count() { return count_; }

CH4* Token4::Print(CH1 item) {
  return ::_::TPrint<CH4>(strand_, strand_ + kTokenLongest, item);
}

CH4* Token4::Print(const CH1* item) {
  CH4* cursor = ::_::TPrint<CH4>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#if USING_UTF16 == YES
CH4* Token4::Print(CH2 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(const CH2* item) {
  CH4* cursor = ::_::TPrint<CH4>(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_UTF32 == YES
CH4* Token4::Print(CH4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(const CH4* item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

CH4* Token4::Print(SI4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(UI4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(SI8 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

CH4* Token4::Print(UI8 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#if USING_FP4 == YES
CH4* Token4::Print(FP4 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}

#endif
#if USING_FP8 == YES
CH4* Token4::Print(FP8 item) {
  CH4* cursor = ::_::Print(strand_, strand_ + kTokenLongest, item);
  if (!cursor) return cursor;
  string_ = nullptr;
  return cursor;
}
#endif

Center4::Center4(const CH4* item, SI4 count) : token(item, count) {}

Center4::Center4(SI4 item, SI4 count) : token(item, count) {}

Center4::Center4(UI4 item, SI4 count) : token(item, count) {}

Center4::Center4(SI8 item, SI4 count) : token(item, count) {}

Center4::Center4(UI8 item, SI4 count) : token(item, count) {}

#if USING_FP4 == YES
Center4::Center4(FP4 item, SI4 count) : token(item, count) {}
#endif
#if USING_FP8 == YES
Center4::Center4(FP8 item, SI4 count) : token(item, count) {}
#endif

Right4::Right4(const CH4* item, SI4 count) : token(item, count) {}

Right4::Right4(SI4 item, SI4 count) : token(item, count) {}

Right4::Right4(UI4 item, SI4 count) : token(item, count) {}

Right4::Right4(SI8 item, SI4 count) : token(item, count) {}

Right4::Right4(UI8 item, SI4 count) : token(item, count) {}

#if SEAM >= SCRIPT2_4
Right4::Right4(FP4 item, SI4 count) : token(item, count) {}

Right4::Right4(FP8 item, SI4 count) : token(item, count) {}
#endif

Linef4::Linef4(CH4 item, SI4 count) : token(token.Strand(), count) {
  CH4* strand = token.Strand();
  ::_::Print(strand, strand + kTokenLongest, item);
}

Linef4::Linef4(const CH4* item, SI4 count) : token(item, count) {}

Headingf4::Headingf4(const CH4* caption, const CH4* style, SI4 count,
                     const CH4* caption2, const CH4* caption3)
    : caption(caption, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Chars4::Chars4(const CH4* start, const CH4* stop) : start(start), stop(stop) {}

}  // namespace _

::_::UTF4& operator<<(::_::UTF4& o, CH4 item) { return o.PrintChar(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::UTF4& p) { return o; }

::_::UTF4& operator<<(::_::UTF4& o, const CH1* item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, const CH2* item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, const CH4* item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI1 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, SI2 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI2 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, SI4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, SI8 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::UTF4& operator<<(::_::UTF4& o, FP4 item) { return o.Print(item); }
#endif
#if USING_FP8 == YES
::_::UTF4& operator<<(::_::UTF4& o, FP8 item) { return o.Print(item); }
#endif

::_::UTF4& operator<<(::_::UTF4& o, ::_::Hex item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Center4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Right4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Linef4 item) { return o.Print(item); }

::_::UTF4& operator<<(::_::UTF4& o, ::_::Headingf4 item) {
  return o.Print(item);
}

::_::UTF4& operator<<(::_::UTF4& o, ::_::Chars4 item) {
  return ::_::TPrintChars<::_::UTF4>(o, item.start, item.stop);
}

#endif
#endif
