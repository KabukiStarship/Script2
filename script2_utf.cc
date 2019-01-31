/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_strand.cc
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
#include <cstdio>

#include "t_strand.h"

#if SEAM == SCRIPT2_3
#include "global_release.inl"
#else
#include "global_release.inl"
#endif

#if USING_UTF8 == YES
#include "c_utf1.h"

namespace _ {

SI4 COutHeap1 (CObject& obj, SIW function, void* arg) {
  return TCOutHeap<CH1> (obj, function, arg);
}

const CH1* StringEmpty() { return TSTREmpty<CH1>(); }

const CH1* StringNL() { return TSTRNL<CH1>(); }

const CH1* StringError() { return TSTRError<CH1>(); }

BOL IsWhitespace(CH1 item) { return TIsWhitespace<CH1>(item); }

CH1 PrintableChar(CH1 item) { return TPrintableChar<CH1>(item); }

const CH1* StrandEnd(const CH1* start) { return TStrandEnd<CH1>(start); }

SI4 StrandLength(const CH1* start) { return TStrandLength<CH1, SI4>(start); }

const CH1* StrandLineEnd(const CH1* start, SI4 count) {
  return TStrandLineEnd<CH1>(start, count);
}

const CH1* StrandLineEnd(const CH1* start, const CH1* stop, SI4 count) {
  return TStrandLineEnd<CH1>(start, stop, count);
}

const CH1* StrandDecimalStop(const CH1* start, const CH1* stop) {
  return TStrandDecimalEnd<CH1>(start);
}

const CH1* StrandDecimalStop(const CH1* start) {
  return TStrandDecimalEnd<CH1>(start);
}

const CH1* StrandSkipChar(const CH1* start, CH1 skip_char) {
  return TStrandSkipChar<CH1>(start, skip_char);
}

const CH1* StrandSkipSpaces(const CH1* start) {
  return TStrandSkipSpaces<CH1>(start);
}

const CH1* StrandSkipSpaces(const CH1* start, const CH1* stop) {
  return TStrandSkipSpaces<CH1>(start, stop);
}

const CH1* StrandEquals(const CH1* text_a, const CH1* text_b) {
  return TStrandEquals<CH1>(text_a, text_b);
}

const CH1* StrandEquals(const CH1* start, const CH1* stop, const CH1* query) {
  return TStrandEquals<CH1>(start, stop, query);
}

SI4 StrandCompare(const CH1* text_a, const CH1* text_b) {
  return TStrandCompare<CH1>(text_a, text_b);
}
/*
SI4 StrandCompare(const CH1* text_a, const CH1* stop,
                  const CH1* text_b) {
  return TStrandCompare<CH1>(text_a, stop, text_b);
}*/

const CH1* StrandFind(const CH1* start, const CH1* query) {
  return TStrandFind<CH1>(start, query);
}

CH1* Print(CH1* start, CH1* stop, const CH1* item) {
  return TPrint<CH1>(start, stop, item);
}

#if USING_UTF16 == YES
CH1* Print (CH1* start, CH1* stop, const CH2* item) {
  return TPrint<CH1> (start, stop, item);
}
#endif

#if USING_UTF32 == YES
CH1* Print (CH1* start, CH1* stop, const CH4* item) {
  return TPrint<CH1> (start, stop, item);
}
#endif

CH1* Print(CH1* start, CH1* stop, UI8 item) {
  return TPrintUnsigned<UI8, CH1>(start, stop, item);
}

CH1* Print(CH1* start, CH1* stop, SI8 item) {
  return TPrintSigned<SI8, UI8, CH1>(start, stop, item);
}

#if WORD_SIZE != 32
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

#if SEAM >= SCRIPT2_4

CH1* PrintCenter(CH1* start, CH1* stop, FLT item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, DBL item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, FLT item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, DBL item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

#endif

CH1* PrintCenter(CH1* start, CH1* stop, const CH1* begin, SI4 count) {
  return TPrintCenter<CH1>(start, stop, begin, count);
}

CH1* PrintCenter(CH1* start, CH1* stop, CH1 item, SI4 count) {
  return TPrintCenter<CH1>(start, stop, Token1(item).String(),
                           count);
}

CH1* PrintCenter(CH1* start, CH1* stop, SI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, UI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, UI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintCenter(CH1* start, CH1* stop, SI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, const CH1* item, SI4 count) {
  return TPrintRight<CH1>(start, stop, item, count);
}

CH1* PrintRight(CH1* start, CH1* stop, CH1 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(),
                          count);
}

CH1* PrintRight(CH1* start, CH1* stop, UI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, SI4 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, UI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
}

CH1* PrintRight(CH1* start, CH1* stop, SI8 item, SI4 count) {
  return TPrintRight<CH1>(start, stop, Token1(item).String(), count);
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

#if SEAM >= SCRIPT2_4
CH1* PrintHex(CH1* start, CH1* stop, FLT item) {
  return TPrintHex<CH1>(start, stop, item);
}

CH1* PrintHex(CH1* start, CH1* stop, DBL item) {
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

CH1* PrintBinary(CH1* start, CH1* stop, FLT item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<CH1, UI4>(start, stop, ui);
}

CH1* PrintBinary(CH1* start, CH1* stop, DBL item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<CH1, UI8>(start, stop, ui);
}

CH1* PrintChars(CH1* start, CH1* stop, const void* begin, const void* end) {
  return TPrintSocket<CH1>(start, stop, begin, end);
}

CH1* PrintChars (CH1* start, CH1* stop, const void* begin, SIW size) {
  const CH1* ptr = reinterpret_cast<const CH1*>(begin);
  return PrintChars (start, stop, begin, ptr + size - 1);
}

CH1* PrintLine(CH1* start, CH1* stop, CH1 token, SI4 count) {
  return TPrintLine<CH1>(start, stop, token, count);
}

CH1* PrintLine(CH1* start, CH1* stop, const CH1* item,
                      SI4 count) {
  return TPrintLine<CH1>(start, stop, item, count);
}

CH1* PrintRepeat (CH1* start, CH1* stop, CH1 token, SI4 count) {
  return TPrintRepeat<CH1> (start, stop, token, count);
}

CH1* PrintRepeat (CH1* start, CH1* stop, const CH1* item,
  SI4 count) {
  return TPrintRepeat<CH1> (start, stop, item, count);
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

UTF1::UTF1(CH1* start, size_t buffer_size)
    : start (start), stop(start + buffer_size - 1) {
  DASSERT(start);
  DASSERT(buffer_size);
}

UTF1::UTF1(CH1* begin, CH1* stop) : start (start), stop(stop) {
  DASSERT(begin);
  DASSERT(begin < stop);
}

UTF1::UTF1(const UTF1& other) : start (other.start), stop(other.stop) {
  DASSERT(start);
  DASSERT(stop);
}

UTF1& UTF1::Set(CH1* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF1& UTF1::Print (CH1 item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (CH2 item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (CH4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (const CH1* item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (const CH2* item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (const CH4* item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (SI4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (UI4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (SI8 item) {
  return Set (::_::Print (start, stop, item));
}

UTF1& UTF1::Print (UI8 item) {
  return Set (::_::Print (start, stop, item));
}

#if SEAM >= SCRIPT2_4
@return A UTF. */
UTF1& UTF1::Print (FLT item) {
  return Set (::_::Print (start, stop, item));
}

@return A UTF. */
UTF1& UTF1::Print (DBL item) {
  return Set (::_::Print (start, stop, item));
}
#endif

UTF1& UTF1::Print (Right1 item) {
  return Set (::_::PrintRight (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF1& UTF1::Print (Center1 item) {
  return Set (::_::PrintCenter (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF1& UTF1::Print (Line1 item) {
  return Set (::_::PrintLine (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF1& UTF1::Print (Repeat1 item) {
  return Set (::_::PrintLine (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF1& UTF1::Hex(UI1 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI1 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI2 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI2 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI4 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(UI8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(SI8 item) { return Set(TPrintHex<CH1>(start, stop, item)); }

#if SEAM >= SCRIPT2_4
UTF1& UTF1::Hex(FLT item) { return Set(TPrintHex<CH1>(start, stop, item)); }

UTF1& UTF1::Hex(DBL item) { return Set(TPrintHex<CH1>(start, stop, item)); }
#endif

UTF1& UTF1::Hex(const void* ptr) {
  return Set(TPrintHex<CH1>(start, stop, ptr));
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

#if SEAM >= SCRIPT2_4
UTF1& UTF1::Binary(FLT item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH1>(start, stop, ui));
}

UTF1& UTF1::Binary(DBL item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH1>(start, stop, ui));
}
#endif

UTF1& UTF1::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH1>(start, stop, ptr));
}

Token1::Token1(CH1 item, SI4 count)
  : string_ (strand_), count_ (count) {
  CH1* start = strand_;
  *start++ = item;
  *start = 0;
}

Token1::Token1 (const CH1* item, SI4 count)
  : string_ (item), count_ (count) {
  if (!item) {
    *strand_ = 0;
    string_ = strand_;
  }
}

Token1::Token1(SI4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
}

Token1::Token1(UI4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
}

Token1::Token1(SI8 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
}

Token1::Token1(UI8 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
}

#if SEAM >= SCRIPT2_4
Token1::Token1(FLT item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
 }
Token1::Token1(DBL item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
}
#endif

SI4 Token1::Count () { return count_; }

const CH1* Token1::String () { return string_; }

Center1::Center1(const CH1* item, SI4 count)
  : token (item, count) {}

Center1::Center1(SI4 item, SI4 count)
  : token (item, count) {}

Center1::Center1(UI4 item, SI4 count)
  : token (item, count) {}

Center1::Center1(SI8 item, SI4 count)
  : token (item, count) {}

Center1::Center1(UI8 item, SI4 count)
  : token (item, count) {}

#if SEAM == SCRIPT2_4
Center1::Center1(FLT item, SI4 count)
  : token (item, count) {}

Center1::Center1(DBL item, SI4 count)
  : token (item, count) {}
#endif

Right1::Right1 (CH1 item, SI4 count)
  : token (item, count) {}

Right1::Right1(const CH1* item, SI4 count)
  : token (item, count) {}

Right1::Right1(SI4 item, SI4 count)
  : token (item, count) {}

Right1::Right1(UI4 item, SI4 count)
  : token (item, count) {}

Right1::Right1(SI8 item, SI4 count)
  : token (item, count) {}

Right1::Right1(UI8 item, SI4 count)
  : token (item, count) {}

#if SEAM >= SCRIPT2_4
Right1::Right1(FLT item, SI4 count)
  : token (item, count) {}

Right1::Right1(DBL item, SI4 count)
  : token (item, count) {}
#endif

Line1::Line1(CH1 item, SI4 count)
  : token (item, count) {}

Line1::Line1(const CH1* item, SI4 count)
  : token (item, count) {}

Repeat1::Repeat1 (CH1 item, SI4 count)
  : token (item, count) {}

Repeat1::Repeat1 (const CH1* item, SI4 count)
  : token (item, count) {}

/*
UIW* COut1(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1>(begin, function, arg);
}

UIW* COut1Auto(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1, kHeap>(begin, function, arg);
}*/

}  // namespace _

_::UTF1& operator<<(::_::UTF1& utf, const CH1* start) {
  return utf.Set(::_::Print(utf.start, utf.stop, start));
}

_::UTF1& operator<<(::_::UTF1& utf, CH1 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, UI1 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, SI2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, UI2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, SI4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, UI4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, SI8 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, UI8 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

#if SEAM == SCRIPT2_4
_::UTF1& operator<<(::_::UTF1& utf, FLT item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF1& operator<<(::_::UTF1& utf, DBL item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}
#endif

_::UTF1& operator<<(::_::UTF1& utf, ::_::Center1 item) {
  return utf.Set(::_::PrintCenter(utf.start, utf.stop, item.token.String (),
                                  item.token.Count()));
}

_::UTF1& operator<<(::_::UTF1& utf, ::_::Right1 item) {
  return utf.Set(::_::PrintRight(utf.start, utf.stop, item.token.String (),
                                 item.token.Count()));
}

_::UTF1& operator<<(::_::UTF1& utf, ::_::Line1 item) {
  return utf.Set(
      ::_::PrintLine(utf.start, utf.stop, item.token.String (), item.token.Count ()));
}

_::UTF1& operator<<(::_::UTF1& utf, ::_::Repeat1 item) {
  return utf.Set(
    ::_::PrintRepeat (utf.start, utf.stop, item.token.String (), item.token.Count ()));
}

#endif  //< #if USING_UTF8

#if USING_UTF16 == YES
#include "c_utf2.h"
namespace _ {

  SI4 COutHeap2 (CObject& obj, SIW function, void* arg) {
    return TCOutHeap<CH2> (obj, function, arg);
  }

const CH2* Empty() { return TSTREmpty<CH2>(); }

const CH2* NewLine() { return TSTRNL<CH2>(); }

const CH2* ErrorHeader() { return TSTRError<CH2>(); }

BOL IsWhitespace(CH2 item) { return TIsWhitespace<CH2>(item); }

CH2 PrintableChar(CH2 item) { return TPrintableChar<CH2>(item); }

const CH2* StrandEnd(const CH2* start) { return TStrandEnd<CH2>(start); }

SI4 StrandLength(const CH2* start) { return TStrandLength<CH2, SI4>(start); }

const CH2* StrandLineEnd(const CH2* start, SI4 count) {
  return TStrandLineEnd<CH2>(start, count);
}

const CH2* StrandLineEnd(const CH2* start, const CH2* stop, SI4 count) {
  return TStrandLineEnd<CH2>(start, stop, count);
}

const CH2* StrandDecimalEnd(const CH2* start, const CH2* stop) {
  return TStrandDecimalEnd<CH2>(start, stop);
}

const CH2* StrandDecimalEnd(const CH2* start) {
  return TStrandDecimalEnd<CH2>(start);
}

const CH2* StrandSkipChar(const CH2* start, CH2 skip_char) {
  return TStrandSkipChar<CH2>(start, skip_char);
}

const CH2* StrandSkipSpaces(const CH2* start) {
  return TStrandSkipSpaces<CH2>(start);
}

const CH2* StrandSkipSpaces(const CH2* start, const CH2* stop) {
  return TStrandSkipSpaces<CH2>(start, stop);
}

const CH2* StrandEquals(const CH2* text_a, const CH2* text_b) {
  return TStrandEquals<CH2>(text_a, text_b);
}

const CH2* StrandEquals(const CH2* start, const CH2* stop, const CH2* query) {
  return TStrandEquals<CH2>(start, stop, query);
}

SI4 StrandCompare(const CH2* text_a, const CH2* text_b) {
  return TStrandCompare<CH2>(text_a, text_b);
}

const CH2* StrandFind(const CH2* start, const CH2* query) {
  return TStrandFind<CH2>(start, query);
}

#if USING_UTF8 == YES
CH2* Print (CH2* start, CH2* stop, const CH1* item) {
  return TPrint<CH2> (start, stop, item);
}
#endif

CH2* Print(CH2* start, CH2* stop, const CH2* item) {
  return TPrint<CH2>(start, stop, item);
}

#if USING_UTF32 == YES
CH2* Print (CH2* start, CH2* stop, const CH4* item) {
  return TPrint<CH2> (start, stop, item);
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
  return TPrintCenter<CH2>(start, stop, Token2(item).String(),
                           count);
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

#if SEAM >= SCRIPT2_4
CH2* PrintCenter(CH2* start, CH2* stop, FLT item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintCenter(CH2* start, CH2* stop, DBL item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
#endif

CH2* PrintRight(CH2* start, CH2* stop, const CH2* item, SI4 count) {
  return TPrintRight<CH2>(start, stop, item, count);
}

CH2* PrintRight(CH2* start, CH2* stop, CH2 item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(),
                          count);
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

#if SEAM >= SCRIPT2_4
CH2* PrintRight(CH2* start, CH2* stop, FLT item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}

CH2* PrintRight(CH2* start, CH2* stop, DBL item, SI4 count) {
  return TPrintRight<CH2>(start, stop, Token2(item).String(), count);
}
#endif

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

#if SEAM >= SCRIPT2_4
CH2* PrintHex(CH2* start, CH2* stop, FLT item) {
  return TPrintHex<CH2>(start, stop, item);
}

CH2* PrintHex(CH2* start, CH2* stop, DBL item) {
  return TPrintHex<CH2>(start, stop, item);
}
#endif

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

#if SEAM >= SCRIPT2_4
CH2* PrintBinary(CH2* start, CH2* stop, FLT item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Print(start, stop, ui);
}

CH2* PrintBinary(CH2* start, CH2* stop, DBL item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return Print(start, stop, ui);
}
#endif

CH2* PrintChars(CH2* start, CH2* stop, const void* begin, const void* end) {
  return TPrintSocket<CH2>(start, stop, begin, end);
}

CH2* PrintChars (CH2* start, CH2* stop, const void* begin, SIW size) {
  const CH1* end = reinterpret_cast<const CH1*> (begin) + size - 1;
  return PrintChars (start, stop, begin, end);
}

CH2* PrintLine (CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintLine<CH2> (start, stop, token, count);
}

CH2* PrintLine (CH2* start, CH2* stop, const CH2* token, SI4 count) {
  return TPrintLine<CH2> (start, stop, token, count);
}

CH2* PrintRepeat (CH2* start, CH2* stop, CH2 token, SI4 count) {
  return TPrintRepeat<CH2> (start, stop, token, count);
}

CH2* PrintRepeat (CH2* start, CH2* stop, const CH2* token, SI4 count) {
  return TPrintRepeat<CH2> (start, stop, token, count);
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

#if SEAM >= SCRIPT2_4
const CH2* Scan(const CH2* start, FLT& result) {
  return TScanFloat<FLT, UI4, CH2>(start, result);
}

const CH2* Scan(const CH2* start, DBL& result) {
  return TScanFloat<DBL, UI8 CH2>(start, result);
}
#endif

/*
void COut2(UIW* begin) { return TCOut<CH2>(begin); }

void COut2Auto(UIW* begin) { return TCOutAuto<CH2>(begin); }*/

UTF2::UTF2(CH2* start, size_t buffer_size)
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

UTF2& UTF2::Print (CH1 item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (CH2 item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (CH4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (const CH1* item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (const CH2* item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (const CH4* item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (SI4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (UI4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (SI8 item) {
  return Set (::_::Print (start, stop, item));
}

UTF2& UTF2::Print (UI8 item) {
  return Set (::_::Print (start, stop, item));
}

#if SEAM >= SCRIPT2_4
@return A UTF. * /
UTF2 & UTF2::Print (FLT item) {
  return Set (::_::Print (start, stop, item));
}

@return A UTF. * /
UTF2 & UTF2::Print (DBL item) {
  return Set (::_::Print (start, stop, item));
}
#endif

UTF2& UTF2::Print (Right2 item) {
  return Set (::_::PrintRight (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF2& UTF2::Print (Center2 item) {
  return Set (::_::PrintCenter (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF2& UTF2::Print (Line2 item) {
  return Set (::_::PrintLine (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF2& UTF2::Print (Repeat2 item) {
  return Set (::_::PrintLine (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF2& UTF2::Hex(UI1 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI1 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI2 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI2 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI4 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(UI8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(SI8 item) { return Set(TPrintHex<CH2>(start, stop, item)); }

#if SEAM >= SCRIPT2_4
UTF2& UTF2::Hex(FLT item) { return Set(TPrintHex<CH2>(start, stop, item)); }

UTF2& UTF2::Hex(DBL item) { return Set(TPrintHex<CH2>(start, stop, item)); }
#endif

UTF2& UTF2::Hex(const void* ptr) {
  return Set(TPrintHex<CH2>(start, stop, ptr));
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

#if SEAM >= SCRIPT2_4
UTF2& UTF2::Binary(FLT item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH2>(start, stop, ui));
}

UTF2& UTF2::Binary(DBL item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH2>(start, stop, ui));
}
#endif

UTF2& UTF2::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH2>(start, stop, ptr));
}

Token2::Token2 (CH2 item, SI4 count)
  : string_ (strand_), count_ (count) {
  CH2* start = strand_;
  *start++ = item;
  *start = 0;
}

Token2::Token2 (const CH2* item, SI4 count)
  : string_ (item), count_ (count) {
  if (!item) *strand_ = 0;
}

Token2::Token2(SI4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  Print(strand_, strand_ + kTokenCount - 1, item);
}

Token2::Token2(UI4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  Print (strand_, strand_ + kTokenCount - 1, item);
}

Token2::Token2(SI8 item, SI4 count)
  : string_ (strand_), count_ (count) {
  Print (strand_, strand_ + kTokenCount - 1, item);
}

Token2::Token2(UI8 item, SI4 count)
  : string_ (strand_), count_ (count) {
  Print (strand_, strand_ + kTokenCount - 1, item);
}

#if SEAM >= SCRIPT2_4
Token2::Token2(FLT item, SI4 count)
  : string_ (strand_), count_ (count) {
  Print (strand_, strand_ + kTokenCount - 1, item);
}

Token2::Token2(DBL item, SI4 count)
  : string_ (strand_), count_ (count) {
  Print (strand_, strand_ + kTokenCount - 1, item);
}
#endif

const CH2* Token2::String() { 
  const CH2* ptr = string_;
  return ptr ? ptr : strand_;
}

SI4 Token2::Count () { return count_; }

Center2::Center2(const CH2* item, SI4 count)
    : token_(item, count) {}

Center2::Center2(SI4 item, SI4 count)
  : token_ (item, count) {}

Center2::Center2(UI4 item, SI4 count)
  : token_ (item, count) {}

Center2::Center2(SI8 item, SI4 count)
  : token_ (item, count) {}

Center2::Center2(UI8 item, SI4 count)
  : token_ (item, count) {}

#if SEAM >= SCRIPT2_4
Center2::Center2(FLT item, SI4 count)
  : token_ (item, count) {}

Center2::Center2(DBL item, SI4 count)
  : token_ (item, count) {}
#endif

Right2::Right2(const CH2* item, SI4 count)
    : token (item, count) {}

Right2::Right2(SI4 item, SI4 count)
  : token (item, count) {}

Right2::Right2(UI4 item, SI4 count)
  : token (item, count) {}

Right2::Right2(SI8 item, SI4 count)
  : token (item, count) {}

Right2::Right2(UI8 item, SI4 count)
  : token (item, count) {}

#if SEAM >= SCRIPT2_4
Right2::Right2(FLT item, SI4 count)
  : token (item, count) {}

Right2::Right2(DBL item, SI4 count)
  : token (item, count) {}
#endif

Line2::Line2 (CH2 item, SI4 count)
  : token (item, count) {}

Line2::Line2 (const CH2* item, SI4 count)
  : token (item, count) {}

Repeat2::Repeat2 (CH2 item, SI4 count)
  : token (item, count) {}

Repeat2::Repeat2 (const CH2* item, SI4 count)
  : token (item, count) {}

}  // namespace _

_::UTF2& operator<<(::_::UTF2& utf, const CH2* start) {
  return utf.Set(::_::Print(utf.start, utf.stop, start));
}

_::UTF2& operator<<(::_::UTF2& utf, CH2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, UI1 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, SI2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, UI2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, SI4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, UI4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, SI8 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, UI8 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

#if SEAM >= SCRIPT2_4
_::UTF2& operator<<(::_::UTF2& utf, FLT item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF2& operator<<(::_::UTF2& utf, DBL item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}
#endif

_::UTF2& operator<<(::_::UTF2& utf, ::_::Center2 item) {
  return utf.Set(::_::PrintCenter(utf.start, utf.stop, item.token.String (),
                                  item.token.Count()));
}

_::UTF2& operator<<(::_::UTF2& utf, ::_::Right2 item) {
  return utf.Set(::_::PrintRight(utf.start, utf.stop, item.token.String (),
                                 item.token.Count()));
}

_::UTF2& operator<<(::_::UTF2& utf, ::_::Line2 item) {
  return utf.Set (
    ::_::PrintLine(utf.start, utf.stop, item.token.String (), item.token.Count ()));
}

_::UTF2& operator<<(::_::UTF2& utf, ::_::Repeat2 item) {
  return utf.Set (
    ::_::PrintRepeat (utf.start, utf.stop, item.token.String (), item.token.Count ()));
}
#endif  //< #if USING_UTF16

#if USING_UTF32 == YES
#include "c_utf4.h"
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

const CH4* StrandEnd(const CH4* start) { return TStrandEnd<CH4>(start); }

SI4 StrandLength(const CH4* start) { return TStrandLength<CH4, SI4>(start); }

const CH4* StrandLineEnd(const CH4* start, SI4 count) {
  return TStrandLineEnd<CH4>(start, count);
}

const CH4* StrandLineEnd(const CH4* start, const CH4* stop, SI4 count) {
  return TStrandLineEnd<CH4>(start, stop, count);
}

const CH4* StrandDecimalEnd(const CH4* start, const CH4* stop) {
  return TStrandDecimalEnd<CH4>(start, stop);
}

const CH4* StrandDecimalEnd(const CH4* start) {
  return TStrandDecimalEnd<CH4>(start);
}

const CH4* StrandSkipChar(const CH4* start, CH4 skip_char) {
  return TStrandSkipChar<CH4>(start, skip_char);
}

const CH4* StrandSkipSpaces(const CH4* start) {
  return TStrandSkipSpaces<CH4>(start);
}

const CH4* StrandSkipSpaces(const CH4* start, const CH4* stop) {
  return TStrandSkipSpaces<CH4>(start, stop);
}

const CH4* StrandEquals(const CH4* text_a, const CH4* text_b) {
  return TStrandEquals<CH4>(text_a, text_b);
}

const CH4* StrandEquals(const CH4* start, const CH4* stop, const CH4* text_b) {
  return TStrandEquals<CH4>(start, stop, text_b);
}

/*
BOL TTextQualifies(const CH4* start) { return TTextQualifies<CH4>(start); }

BOL TTextQualifies(const CH4* start, const CH4* stop) {
  return TTextQualifies<CH4>(start, stop);
}*/

SI4 StrandCompare(const CH4* text_a, const CH4* text_b) {
  return TStrandCompare<CH4>(text_a, text_b);
}

const CH4* StrandFind(const CH4* start, const CH4* item) {
  return TStrandFind<CH4>(start, item);
}

#if USING_UTF8 == YES
CH4* Print (CH4* start, CH4* stop, const CH1* item) {
  return TPrint<CH4> (start, stop, item);
}
#endif

#if USING_UTF16 == YES
CH4* Print (CH4* start, CH4* stop, const CH2* item) {
  return TPrint<CH4> (start, stop, item);
}
#endif

CH4* Print(CH4* start, CH4* stop, const CH4* item) {
  return TPrint<CH4>(start, stop, item);
}

CH4* Print (CH4* start, SIW count, const CH4* item) {
  return TPrint<CH4> (start, count, item);
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
  return TPrintCenter<CH4>(start, stop, Token4(item).String(),
                           count);
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

#if SEAM >= SCRIPT2_4
CH4* PrintCenter(CH4* start, CH4* stop, FLT item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintCenter(CH4* start, CH4* stop, DBL item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
#endif

CH4* PrintRight(CH4* start, CH4* stop, const CH4* begin, SI4 count) {
  return TPrintRight<CH4>(start, stop, begin, count);
}

CH4* PrintRight(CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(),
                          count);
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

#if SEAM >= SCRIPT2_4
CH4* PrintRight(CH4* start, CH4* stop, FLT item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}

CH4* PrintRight(CH4* start, CH4* stop, DBL item, SI4 count) {
  return TPrintRight<CH4>(start, stop, Token4(item).String(), count);
}
#endif

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

#if SEAM >= SCRIPT2_4
CH4* PrintHex(CH4* start, CH4* stop, FLT item) {
  return TPrintHex<CH4>(start, stop, item);
}

CH4* PrintHex(CH4* start, CH4* stop, DBL item) {
  return TPrintHex<CH4>(start, stop, item);
}
#endif

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

#if SEAM >= SCRIPT2_4
CH4* PrintBinary(CH4* start, CH4* stop, FLT item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return TPrintBinary<CH4, UI8>(start, stop, ui);
}

CH4* PrintBinary(CH4* start, CH4* stop, DBL item) {
  UI8 ui = *reinterpret_cast<UI8*>(&item);
  return TPrintBinary<CH4, UI8>(start, stop, ui);
}
#endif

CH4* PrintChars(CH4* start, CH4* stop, const void* begin, const void* end) {
  return TPrintSocket<CH4>(start, stop, begin, end);
}

CH4* PrintChars (CH4* start, CH4* stop, const void* begin, SIW size) {
  const CH4* ptr = reinterpret_cast<const CH4*>(begin);
  return PrintChars (start, stop, begin, ptr + size - 1);
}

CH4* PrintLine (CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintLine<CH4> (start, stop, item, count);
}

CH4* PrintLine (CH4* start, CH4* stop, const CH4* item, SI4 count) {
  return TPrintLine<CH4> (start, stop, item, count);
}

CH4* PrintRepeat (CH4* start, CH4* stop, CH4 item, SI4 count) {
  return TPrintRepeat<CH4> (start, stop, item, count);
}

CH4* PrintRepeat (CH4* start, CH4* stop, const CH4* item, SI4 count) {
  return TPrintRepeat<CH4> (start, stop, item, count);
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

#if SEAM >= SCRIPT2_4
const CH4* Scan(const CH4* start, FLT& result) {
  return TScanFloat<CH4>(start, result);
}

const CH4* Scan(const CH4* start, DBL& result) {
  return TScanFloat<CH4>(start, result);
}
#endif

/*
void COut4(UIW* begin) { return TCOut<CH4>(begin); }

void COutAuto4(UIW* begin) { return TCOutAuto<CH4>(begin); }*/

UTF4::UTF4(CH4* start, size_t buffer_size)
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

UTF4& UTF4::Print (CH1 item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (CH2 item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (CH4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (const CH1* item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (const CH2* item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (const CH4* item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (SI4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (UI4 item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (SI8 item) {
  return Set (::_::Print (start, stop, item));
}

UTF4& UTF4::Print (UI8 item) {
  return Set (::_::Print (start, stop, item));
}

#if SEAM >= SCRIPT2_4
@return A UTF. * /
UTF4 & UTF4::Print (FLT item) {
  return Set (::_::Print (start, stop, item));
}

@return A UTF. * /
UTF4 & UTF4::Print (DBL item) {
  return Set (::_::Print (start, stop, item));
}
#endif

UTF4& UTF4::Print (Right4 item) {
  return Set (::_::PrintRight (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF4& UTF4::Print (Center4 item) {
  return Set (::_::PrintCenter (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF4& UTF4::Print (Line4 item) {
  return Set (::_::PrintLine (start, stop, item.token.String (),
    item.token.Count ()));
}

UTF4& UTF4::Print (Repeat4 item) {
  return Set (::_::PrintLine (start, stop, item.token.String (),
    item.token.Count ()));
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

#if SEAM >= SCRIPT2_4
UTF4& UTF4::Hex(FLT item) { return Set(TPrintHex<CH4>(start, stop, item)); }

UTF4& UTF4::Hex(DBL item) { return Set(TPrintHex<CH4>(start, stop, item)); }
#endif

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

#if SEAM >= SCRIPT2_4
UTF4& UTF4::Binary(FLT item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH4>(start, stop, ui));
}

UTF4& UTF4::Binary(DBL item) {
  UI4 ui = *reinterpret_cast<UI4*>(&item);
  return Set(TPrintBinary<CH4>(start, stop, ui));
}
#endif

UTF4& UTF4::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH4>(start, stop, ptr));
}

Token4::Token4 (CH4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  CH4* start = strand_;
  *start++ = item;
  *start = 0;
}

Token4::Token4 (const CH4* item, SI4 count)
  : string_ (item), count_ (count) {
  if (!item) *strand_ = 0;
}

Token4::Token4(SI4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print(strand_, strand_ + kTokenCount - 1, item);
}

Token4::Token4(UI4 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print (strand_, strand_ + kTokenCount - 1, item);
}

Token4::Token4(SI8 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print (strand_, strand_ + kTokenCount - 1, item);
}

Token4::Token4(UI8 item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print (strand_, strand_ + kTokenCount - 1, item);
}

#if SEAM >= SCRIPT2_4
Token4::Token4(FLT item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print (strand_, strand_ + kTokenCount - 1, item);
}

Token4::Token4(DBL item, SI4 count)
  : string_ (strand_), count_ (count) {
  ::_::Print (strand_, strand_ + kTokenCount - 1, item);
 }
#endif

 const CH4* Token4::String () { return string_; }

SI4 Token4::Count () { return count_; }

Center4::Center4(const CH4* item, SI4 count)
    : token (item, count) {}

Center4::Center4(SI4 item, SI4 count)
  : token (item, count) {}

Center4::Center4(UI4 item, SI4 count)
  : token (item, count) {}

Center4::Center4(SI8 item, SI4 count)
  : token (item, count) {}

Center4::Center4(UI8 item, SI4 count)
  : token (item, count) {}

#if SEAM >= SCRIPT2_4
Center4::Center4(FLT item, SI4 count)
  : token (item, count) {}

Center4::Center4(DBL item, SI4 count)
  : token (item, count) {}
#endif

Right4::Right4(const CH4* item, SI4 count)
  : token (item, count) {}

Right4::Right4(SI4 item, SI4 count)
  : token (item, count) {}

Right4::Right4(UI4 item, SI4 count)
  : token (item, count) {}

Right4::Right4(SI8 item, SI4 count)
  : token (item, count) {}

Right4::Right4(UI8 item, SI4 count)
  : token (item, count) {}

#if SEAM >= SCRIPT2_4
Right4::Right4(FLT item, SI4 count)
  : token (item, count) {}

Right4::Right4(DBL item, SI4 count)
  : token (item, count) {}
#endif

Line4::Line4 (CH4 item, SI4 count)
  : token (item, count) {}

Line4::Line4 (const CH4* item, SI4 count)
  : token (item, count) {}

Repeat4::Repeat4 (CH4 item, SI4 count)
  : token (item, count) {}

Repeat4::Repeat4 (const CH4* item, SI4 count)
  : token (item, count) {}

}  // namespace _

_::UTF4& operator<<(::_::UTF4& utf, const CH4* item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, CH4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, UI1 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, SI2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, UI2 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, SI4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, UI4 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, SI8 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, UI8 item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

#if SEAM >= SCRIPT2_4
_::UTF4& operator<<(::_::UTF4& utf, FLT item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}

_::UTF4& operator<<(::_::UTF4& utf, DBL item) {
  return utf.Set(::_::Print(utf.start, utf.stop, item));
}
#endif

_::UTF4& operator<<(::_::UTF4& utf, ::_::Center4 item) {
  return utf.Set(::_::PrintCenter(utf.start, utf.stop, item.token.String (),
                                  item.token.Count()));
}

_::UTF4& operator<<(::_::UTF4& utf, ::_::Right4 item) {
  return utf.Set(::_::PrintRight(utf.start, utf.stop, item.token.String (),
                                 item.token.Count()));
}

_::UTF4& operator<<(::_::UTF4& utf, ::_::Line4 item) {
  return utf.Set (
    ::_::PrintLine(utf.start, utf.stop, item.token.String (), item.token.Count ()));
}

_::UTF4& operator<<(::_::UTF4& utf, ::_::Repeat4 item) {
  return utf.Set (::_::PrintRepeat (utf.start, utf.stop, item.token.String (),
                                    item.token.Count ()));
}

#endif  //< #if USING_UTF32
#endif  //< #if SEAM >= SCRIPT2_3
