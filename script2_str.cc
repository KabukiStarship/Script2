/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \script2_str.cc
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
#if SEAM >= _0_0_0__03
#include <cstdio>

#include "tstr.h"

#include "cascii.h"
#include "csocket.h"
#include "tbinary.h"

#if SEAM == _0_0_0__03
#include "test_release.inl"
#else
#include "test_release.inl"
#endif

#if USING_UTF

namespace _ {

SI4 Console(CObject& obj, SIW function, void* arg) {
  return TCOut<CH1>(obj, function, arg);
}

SI4 COutHeap(CObject& obj, SIW function, void* arg) {
  return TCOutHeap<CH1>(obj, function, arg);
}

void UTFAlignCenterSTR1(SI4 column_count, void* item, void* destination) {
  ASSERT(item);
  ASSERT(destination);
  ASSERT(column_count >= 0);
}

}  // namespace _

#endif  // #if USING_UTF

#if USING_UTF8 == YES
#include "cstr1.h"
namespace _ {

const CH1* TStringEmpty() { return TStringEmpty<CH1>(); }

const CH1* StringNL() { return TStringNL<CH1>(); }

const CH1* StringError() { return TStringError<CH1>(); }

BOL IsWhitespace(CH1 character) { return TIsWhitespace<CH1>(character); }

CH1 PrintableChar(CH1 value) { return TPrintableChar<CH1>(value); }

const CH1* StringEnd(const CH1* cursor) { return TStringEnd<CH1>(cursor); }

SI4 StringLength(const CH1* cursor) { return TStringLength<CH1, SI4>(cursor); }

const CH1* StringLineEnd(const CH1* cursor, SI4 column_count) {
  return TStringLineEnd<CH1>(cursor, column_count);
}

const CH1* StringLineEnd(const CH1* cursor, const CH1* stop, SI4 column_count) {
  return TStringLineEnd<CH1>(cursor, stop, column_count);
}

const CH1* StringDecimalStop(const CH1* cursor, const CH1* stop) {
  return TStringDecimalEnd<CH1>(cursor);
}

const CH1* StringDecimalStop(const CH1* cursor) {
  return TStringDecimalEnd<CH1>(cursor);
}

const CH1* TStringSkipChar(const CH1* cursor, CH1 skip_char) {
  return TStringSkipChar<CH1>(cursor, skip_char);
}

const CH1* StringSkipSpaces(const CH1* cursor) {
  return TStringSkipSpaces<CH1>(cursor);
}

const CH1* StringSkipSpaces(const CH1* cursor, const CH1* stop) {
  return TStringSkipSpaces<CH1>(cursor, stop);
}

const CH1* StringEquals(const CH1* text_a, const CH1* text_b) {
  return TStringEquals<CH1>(text_a, text_b);
}

const CH1* StringEquals(const CH1* cursor, const CH1* stop, const CH1* query) {
  return TStringEquals<CH1>(cursor, stop, query);
}

SI4 StringCompare(const CH1* text_a, const CH1* text_b) {
  return TStringCompare<CH1>(text_a, text_b);
}
/*
SI4 TStringCompare(const CH1* text_a, const CH1* stop,
                  const CH1* text_b) {
  return TStringCompare<CH1>(text_a, stop, text_b);
}*/

const CH1* StringFind(const CH1* cursor, const CH1* query) {
  return TStringFind<CH1>(cursor, query);
}

CH1* Print(CH1* cursor, CH1* stop, const CH1* string) {
  return TPrint<CH1>(cursor, stop, string);
}

CH1* Print(CH1* cursor, CH1* stop, UI8 value) {
  return TPrintUnsigned<UI8, CH1>(cursor, stop, value);
}

CH1* Print(CH1* cursor, CH1* stop, SI8 value) {
  return TPrintSigned<SI8, UI8, CH1>(cursor, stop, value);
}

#if WORD_SIZE != 32
CH1* Print(CH1* cursor, CH1* stop, UI4 value) {
  return Print(cursor, stop, (UI8)value);
}

CH1* Print(CH1* cursor, CH1* stop, SI4 value) {
  return Print(cursor, stop, (SI8)value);
}
#else
CH1* Print(CH1* cursor, CH1* stop, UI4 value) {
  return TPrintUnsigned<UI8, CH1>(cursor, stop, (UI8)value);
}

CH1* Print(CH1* cursor, CH1* stop, SI4 value) {
  return TPrintSigned<SI8, UI8, CH1>(cursor, stop, (SI8)value);
}
#endif

#if SEAM >= _0_0_0__04

CH1* PrintCenter(CH1* cursor, CH1* stop, FLT value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* cursor, CH1* stop, DBL value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, FLT value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, DBL value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

#endif

CH1* PrintCenter(CH1* cursor, CH1* stop, const CH1* begin, SI4 column_count) {
  return TPrintCenter<CH1>(cursor, stop, begin, column_count);
}

CH1* PrintCenter(CH1* cursor, CH1* stop, CH1 character, SI4 column_count) {
  return TPrintCenter<CH1>(cursor, stop, Utf8Text(character).String(),
                           column_count);
}

CH1* PrintCenter(CH1* cursor, CH1* stop, SI4 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* cursor, CH1* stop, UI4 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* cursor, CH1* stop, UI8 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* cursor, CH1* stop, SI8 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, const CH1* string, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, string, column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, CH1 character, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(character).String(),
                          column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, UI4 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, SI4 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, UI8 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* cursor, CH1* stop, SI8 value, SI4 column_count) {
  return TPrintRight<CH1>(cursor, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintHex(CH1* cursor, CH1* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<CH1>(cursor, stop, ptr);
}

CH1* PrintHex(CH1* cursor, CH1* stop, UI1 value) {
  return TPrintHex<CH1, UI1>(cursor, stop, value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, SI1 value) {
  return TPrintHex<CH1, UI1>(cursor, stop, (UI1)value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, UI2 value) {
  return TPrintHex<CH1, UI2>(cursor, stop, value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, SI2 value) {
  return TPrintHex<CH1, UI2>(cursor, stop, (UI2)value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, UI4 value) {
  return TPrintHex<CH1, UI4>(cursor, stop, value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, SI4 value) {
  return TPrintHex<CH1, UI4>(cursor, stop, (UI4)value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, UI8 value) {
  return TPrintHex<CH1, UI8>(cursor, stop, value);
}

CH1* PrintHex(CH1* cursor, CH1* stop, SI8 value) {
  return TPrintHex<CH1, UI8>(cursor, stop, (UI8)value);
}

#if SEAM >= _0_0_0__04
CH1* PrintHex(CH1* cursor, CH1* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<CH1, UI4>(cursor, stop, ui);
}

CH1* PrintHex(CH1* cursor, CH1* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<CH1, UI8>(cursor, stop, ui);
}
#endif

CH1* PrintBinary(CH1* cursor, CH1* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<CH1>(cursor, stop, ptr);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, UI1 value) {
  return TPrintBinary<CH1, UI1>(cursor, stop, value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, SI1 value) {
  return TPrintBinary<CH1, UI1>(cursor, stop, (UI1)value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, UI2 value) {
  return TPrintBinary<CH1, UI2>(cursor, stop, value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, SI2 value) {
  return TPrintBinary<CH1, UI2>(cursor, stop, (UI2)value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, UI4 value) {
  return TPrintBinary<CH1, UI4>(cursor, stop, value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, SI4 value) {
  return TPrintBinary<CH1, UI4>(cursor, stop, value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, UI8 value) {
  return TPrintBinary<CH1, UI8>(cursor, stop, value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, SI8 value) {
  return TPrintBinary<CH1, UI8>(cursor, stop, value);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<CH1, UI4>(cursor, stop, ui);
}

CH1* PrintBinary(CH1* cursor, CH1* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<CH1, UI8>(cursor, stop, ui);
}

CH1* PrintSocket(CH1* cursor, CH1* stop, const void* begin, size_t size) {
  return TPrintSocket<CH1>(cursor, stop, begin,
                           reinterpret_cast<const CH1*>(begin) + size);
}

CH1* PrintSocket(CH1* cursor, CH1* stop, const void* begin, const void* end) {
  return TPrintSocket<CH1>(cursor, stop, begin, end);
}

CH1* PrintLine(CH1* cursor, CH1* stop, CH1 token, SI4 column_count) {
  return TPrintLine<CH1>(cursor, stop, token, column_count);
}

CH1* TPrintLineString(CH1* cursor, CH1* stop, const CH1* string,
                      SI4 column_count) {
  return TPrintLineString<CH1>(cursor, stop, string, column_count);
}

const CH1* Scan(const CH1* cursor, SI1& result) {
  return TScanSigned<SI1, UI1, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, UI1& result) {
  return TScanUnsigned<UI1, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, SI2& result) {
  return TScanSigned<SI2, UI2, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, UI2& result) {
  return TScanUnsigned<UI2, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, SI4& result) {
  return TScanSigned<SI4, UI4, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, UI4& result) {
  return TScanUnsigned<UI4, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, SI8& result) {
  return TScanSigned<SI8, UI8, CH1>(cursor, result);
}

const CH1* Scan(const CH1* cursor, UI8& result) {
  return TScanUnsigned<UI8, CH1>(cursor, result);
}

UTF1::UTF1(CH1* begin, size_t buffer_size)
    : begin(begin), stop(begin + buffer_size - 1) {
  ASSERT(begin);
  ASSERT(buffer_size);
}

UTF1::UTF1(CH1* begin, CH1* stop) : begin(begin), stop(stop) {
  ASSERT(begin);
  ASSERT(begin < stop);
}

UTF1::UTF1(const UTF1& other) : begin(other.begin), stop(other.stop) {
  ASSERT(begin);
  ASSERT(stop);
}

UTF1& UTF1::Set(CH1* new_cursor) {
  begin = new_cursor;
  return *this;
}

UTF1& UTF1::Hex(UI1 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(SI1 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(UI2 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(SI2 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(UI4 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(SI4 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(UI8 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

UTF1& UTF1::Hex(SI8 value) { return Set(TPrintHex<CH1>(begin, stop, value)); }

#if SEAM >= _0_0_0__04
UTF1& UTF1::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<CH1>(begin, stop, ui));
}

UTF1& UTF1::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<CH1>(begin, stop, ui));
}
#endif

UTF1& UTF1::Hex(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintHex<CH1>(begin, stop, ptr));
}

UTF1& UTF1::Binary(UI1 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(SI1 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(UI2 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(SI2 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(UI4 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(SI4 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(UI8 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

UTF1& UTF1::Binary(SI8 value) {
  return Set(TPrintBinary<CH1>(begin, stop, value));
}

#if SEAM >= _0_0_0__04
UTF1& UTF1::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH1>(begin, stop, ui));
}

UTF1& UTF1::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH1>(begin, stop, ui));
}
#endif

UTF1& UTF1::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH1>(begin, stop, ptr));
}

Utf8Text::Utf8Text() {}

Utf8Text::Utf8Text(CH1 character) {
  *string_ = character;
  *(string_ + 1) = 0;
}

Utf8Text::Utf8Text(SI4 value) {
  TPrintSigned<SI4, UI4, CH1>(string_, string_ + kSize - 1, value);
}

Utf8Text::Utf8Text(UI4 value) {
  TPrintUnsigned<UI4, CH1>(string_, string_ + kSize - 1, value);
}

Utf8Text::Utf8Text(SI8 value) {
  TPrintSigned<SI8, UI8, CH1>(string_, string_ + kSize - 1, value);
}

Utf8Text::Utf8Text(UI8 value) {
  TPrintUnsigned<UI8, CH1>(string_, string_ + kSize - 1, value);
}

#if SEAM >= _0_0_0__04
Utf8Text::Utf8Text(FLT value) { Print(cursor, cursor + kSize - 1, value); }

Utf8Text::Utf8Text(DBL value) { Print(cursor, cursor + kSize - 1, value); }

#endif  //< #if SEAM == _0_0_0__04

const CH1* Utf8Text::String() { return string_; }

Utf8Center::Utf8Center(const CH1* string, SI4 column_count)
    : string_(string), column_count(column_count) {}

Utf8Center::Utf8Center(SI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(UI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(SI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(UI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM == _0_0_0__04
Utf8Center::Utf8Center(FLT value, SI4 column_count)
    : cursor(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(DBL value, SI4 column_count)
    : cursor(nullptr), number_(value), column_count(column_count) {}
#endif

const CH1* Utf8Center::String() {
  return (!string_) ? number_.String() : string_;
}

SI4 Utf8Center::GetColumnCount() { return column_count; }

Utf8Right::Utf8Right(const CH1* string, SI4 column_count)
    : string_(string), column_count(column_count) {}

Utf8Right::Utf8Right(SI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(UI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(SI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(UI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM >= _0_0_0__04
Utf8Right::Utf8Right(FLT value, SI4 column_count)
    : cursor(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(DBL value, SI4 column_count)
    : cursor(nullptr), number_(value), column_count(column_count) {}
#endif

const CH1* Utf8Right::String() {
  const CH1* string = string_;
  return (!string) ? number_.String() : string;
}

SI4 Utf8Right::GetColumnCount() { return column_count; }

Utf8Line::Utf8Line(CH1 token, SI4 column_count)
    : token(token), column_count(column_count) {
  // Nothing to do here. (:-)-+=<
}

Utf8LineString::Utf8LineString(const CH1* string, SI4 column_count)
    : string_(string), column_count(column_count) {
  // Nothing to do here. (:-)-+=<
}

/* ???
UIW* COutUtf8(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1>(begin, function, arg);
}

UIW* COutAutoUtf8(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1, kHeap>(begin, function, arg);
}*/

}  // namespace _

_::UTF1& operator<<(::_::UTF1& utf, const CH1* cursor) {
  return utf.Set(::_::Print(utf.begin, utf.stop, cursor));
}

_::UTF1& operator<<(::_::UTF1& utf, CH1 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, UI1 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, SI2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, UI2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, SI4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, UI4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, SI8 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, UI8 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

#if SEAM == _0_0_0__04
_::UTF1& operator<<(::_::UTF1& utf, FLT value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(::_::UTF1& utf, DBL value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}
#endif

_::UTF1& operator<<(::_::UTF1& utf, ::_::Utf8Center item) {
  return utf.Set(::_::PrintCenter(utf.begin, utf.stop, item.String(),
                                  item.GetColumnCount()));
}

_::UTF1& operator<<(::_::UTF1& utf, ::_::Utf8Right item) {
  return utf.Set(::_::PrintRight(utf.begin, utf.stop, item.String(),
                                 item.GetColumnCount()));
}

_::UTF1& operator<<(::_::UTF1& utf, ::_::Utf8Line line) {
  return utf.Set(
      ::_::PrintLine(utf.begin, utf.stop, line.token, line.column_count));
}

_::UTF1& operator<<(::_::UTF1& utf, ::_::Utf8LineString line) {
  return utf.Set(::_::TPrintLineString(utf.begin, utf.stop, line.string_,
                                       line.column_count));
}

#endif  //< #if USING_UTF8

#if USING_UTF16 == YES
#include "cstr2.h"
namespace _ {

const CH2* Empty() { return TStringEmpty<CH2>(); }

const CH2* NewLine() { return TStringNL<CH2>(); }

const CH2* ErrorHeader() { return TStringError<CH2>(); }

BOL IsWhitespace(CH2 character) { return TIsWhitespace<CH2>(character); }

CH2 PrintableChar(CH2 value) { return TPrintableChar<CH2>(value); }

const CH2* TStringEnd(const CH2* cursor) { return TStringEnd<CH2>(cursor); }

SI4 TStringLength(const CH2* cursor) { return TStringLength<CH2, SI4>(cursor); }

const CH2* StringLineEnd(const CH2* cursor, SI4 column_count) {
  return TStringLineEnd<CH2>(cursor, column_count);
}

const CH2* StringLineEnd(const CH2* cursor, const CH2* stop, SI4 column_count) {
  return TStringLineEnd<CH2>(cursor, stop, column_count);
}

const CH2* TStringDecimalEnd(const CH2* cursor, const CH2* stop) {
  return TStringDecimalEnd<CH2>(cursor, stop);
}

const CH2* TStringDecimalEnd(const CH2* cursor) {
  return TStringDecimalEnd<CH2>(cursor);
}

const CH2* TStringSkipChar(const CH2* cursor, CH2 skip_char) {
  return TStringSkipChar<CH2>(cursor, skip_char);
}

const CH2* StringSkipSpaces(const CH2* cursor) {
  return TStringSkipSpaces<CH2>(cursor);
}

const CH2* StringSkipSpaces(const CH2* cursor, const CH2* stop) {
  return TStringSkipSpaces<CH2>(cursor, stop);
}

const CH2* StringEquals(const CH2* text_a, const CH2* text_b) {
  return TStringEquals<CH2>(text_a, text_b);
}

const CH2* StringEquals(const CH2* cursor, const CH2* stop, const CH2* query) {
  return TStringEquals<CH2>(cursor, stop, query);
}

SI4 TStringCompare(const CH2* text_a, const CH2* text_b) {
  return TStringCompare<CH2>(text_a, text_b);
}

const CH2* StringFind(const CH2* cursor, const CH2* query) {
  return TStringFind<CH2>(cursor, query);
}

CH2* Print(CH2* cursor, CH2* stop, const CH2* string) {
  return TPrint<CH2>(cursor, stop, string);
}

CH2* Print(CH2* cursor, CH2* stop, UI4 value) {
  return TPrintUnsigned<UI4, CH2>(cursor, stop, value);
}

CH2* Print(CH2* cursor, CH2* stop, SI4 value) {
  return TPrintSigned<SI4, UI4, CH2>(cursor, stop, value);
}

CH2* Print(CH2* cursor, CH2* stop, UI8 value) {
  return TPrintUnsigned<UI8, CH2>(cursor, stop, value);
}

CH2* Print(CH2* cursor, CH2* stop, SI8 value) {
  return TPrintSigned<SI8, UI8, CH2>(cursor, stop, value);
}

#if SEAM >= _0_0_0__04
CH2* Print(CH2* cursor, CH2* stop, FLT value) {
  return TPrint<CH2>(cursor, stop, value);
}

CH2* Print(CH2* cursor, CH2* stop, DBL value) {
  return TPrint<CH2>(cursor, stop, value);
}
#endif

CH2* PrintCenter(CH2* cursor, CH2* stop, const CH2* string, SI4 column_count) {
  return TPrintCenter<CH2>(cursor, stop, string, column_count);
}

CH2* PrintCenter(CH2* cursor, CH2* stop, CH2 character, SI4 column_count) {
  return TPrintCenter<CH2>(cursor, stop, Text2(character).GetString(),
                           column_count);
}

CH2* PrintCenter(CH2* cursor, CH2* stop, SI4 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintCenter(CH2* cursor, CH2* stop, UI4 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintCenter(CH2* cursor, CH2* stop, UI8 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintCenter(CH2* cursor, CH2* stop, SI8 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

#if SEAM >= _0_0_0__04
CH2* PrintCenter(CH2* cursor, CH2* stop, FLT value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintCenter(CH2* cursor, CH2* stop, DBL value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}
#endif

CH2* PrintRight(CH2* cursor, CH2* stop, const CH2* string, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, string, column_count);
}

CH2* PrintRight(CH2* cursor, CH2* stop, CH2 character, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(character).GetString(),
                          column_count);
}

CH2* PrintRight(CH2* cursor, CH2* stop, UI4 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintRight(CH2* cursor, CH2* stop, SI4 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintRight(CH2* cursor, CH2* stop, UI8 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintRight(CH2* cursor, CH2* stop, SI8 value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

#if SEAM >= _0_0_0__04
CH2* PrintRight(CH2* cursor, CH2* stop, FLT value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}

CH2* PrintRight(CH2* cursor, CH2* stop, DBL value, SI4 column_count) {
  return TPrintRight<CH2>(cursor, stop, Text2(value).GetString(), column_count);
}
#endif

CH2* PrintHex(CH2* cursor, CH2* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<CH2>(cursor, stop, ptr);
}

CH2* PrintHex(CH2* cursor, CH2* stop, UI1 value) {
  return TPrintHex<CH2, UI1>(cursor, stop, value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, SI1 value) {
  return TPrintHex<CH2, UI1>(cursor, stop, (UI1)value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, UI2 value) {
  return TPrintHex<CH2, UI2>(cursor, stop, value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, SI2 value) {
  return TPrintHex<CH2, UI2>(cursor, stop, (UI2)value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, UI4 value) {
  return TPrintHex<CH2, UI4>(cursor, stop, value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, SI4 value) {
  return TPrintHex<CH2, UI4>(cursor, stop, (UI4)value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, UI8 value) {
  return TPrintHex<CH2, UI8>(cursor, stop, value);
}

CH2* PrintHex(CH2* cursor, CH2* stop, SI8 value) {
  return TPrintHex<CH2, UI8>(cursor, stop, (UI8)value);
}

#if SEAM >= _0_0_0__04
CH2* PrintHex(CH2* cursor, CH2* stop, FLT value) {
  UI4 float_as_ui32 = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<CH2, UI4>(cursor, stop, float_as_ui32);
}

CH2* PrintHex(CH2* cursor, CH2* stop, DBL value) {
  UI8 double_as_ui64 = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<CH2, UI8>(cursor, stop, double_as_ui64);
}
#endif

CH2* TPrintBinary(CH2* cursor, CH2* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<CH2>(cursor, stop, ptr);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, UI1 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, SI1 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, UI2 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, SI2 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, UI4 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, SI4 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, UI8 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, SI8 value) {
  return TPrintBinary<CH2>(cursor, stop, value);
}

#if SEAM >= _0_0_0__04
CH2* TPrintBinary(CH2* cursor, CH2* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Print(cursor, stop, ui);
}

CH2* TPrintBinary(CH2* cursor, CH2* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Print(cursor, stop, ui);
}
#endif

CH2* PrintSocket(CH2* cursor, CH2* stop, const void* begin, size_t size) {
  return TPrintSocket<CH2>(cursor, stop, begin,
                           reinterpret_cast<const CH2*>(begin) + size);
}

CH2* PrintSocket(CH2* cursor, CH2* stop, const void* begin, const void* end) {
  return TPrintSocket<CH2>(cursor, stop, begin, end);
}

const CH2* Scan(const CH2* cursor, SI1& result) {
  return TScanSigned<SI1, UI1, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, UI1& result) {
  return TScanUnsigned<UI1, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, SI2& result) {
  return TScanSigned<SI2, UI2, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, UI2& result) {
  return TScanUnsigned<UI2, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, SI4& result) {
  return TScanSigned<SI4, UI4, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, UI4& result) {
  return TScanUnsigned<UI4, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, SI8& result) {
  return TScanSigned<SI8, UI8, CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, UI8& result) {
  return TScanUnsigned<UI8, CH2>(cursor, result);
}

#if SEAM >= _0_0_0__04
const CH2* Scan(const CH2* cursor, FLT& result) {
  return TScanFloat<CH2>(cursor, result);
}

const CH2* Scan(const CH2* cursor, DBL& result) {
  return TScanFloat<CH2>(cursor, result);
}
#endif

/* ???
void COutUtf16(UIW* begin) { return TCOut<CH2>(begin); }

void DCOutUtf16(UIW* begin) { return TCOut<CH2>(begin); }*/

UTF2::UTF2(CH2* begin, size_t buffer_size)
    : begin(begin), stop(begin + buffer_size - 1) {
  ASSERT(begin);
  ASSERT(buffer_size);
}

UTF2::UTF2(CH2* begin, CH2* stop) : begin(begin), stop(stop) {
  ASSERT(begin);
  ASSERT(begin < stop);
}

UTF2::UTF2(const UTF2& other) : begin(other.begin), stop(other.stop) {
  ASSERT(begin);
  ASSERT(stop);
}

UTF2& UTF2::Set(CH2* new_cursor) {
  begin = new_cursor;
  return *this;
}

UTF2& UTF2::Hex(UI1 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(SI1 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(UI2 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(SI2 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(UI4 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(SI4 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(UI8 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

UTF2& UTF2::Hex(SI8 value) { return Set(TPrintHex<CH2>(begin, stop, value)); }

#if SEAM >= _0_0_0__04
UTF2& UTF2::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<CH2>(begin, stop, ui));
}

UTF2& UTF2::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<CH2>(begin, stop, ui));
}
#endif

UTF2& UTF2::Hex(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintHex<CH2>(begin, stop, ptr));
}

UTF2& UTF2::Binary(UI1 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(SI1 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(UI2 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(SI2 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(UI4 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(SI4 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(UI8 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

UTF2& UTF2::Binary(SI8 value) {
  return Set(TPrintBinary<CH2>(begin, stop, value));
}

#if SEAM >= _0_0_0__04
UTF2& UTF2::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH2>(begin, stop, ui));
}

UTF2& UTF2::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH2>(begin, stop, ui));
}
#endif

UTF2& UTF2::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH2>(begin, stop, ptr));
}

Text2::Text2() {}

Text2::Text2(CH2 character) {
  *string_ = character;
  *(string_ + 1) = 0;
}

Text2::Text2(SI4 value) {
  TPrintSigned<SI4, UI4, CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(UI4 value) {
  TPrintUnsigned<UI4, CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(SI8 value) {
  TPrintSigned<SI8, UI8, CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(UI8 value) {
  TPrintUnsigned<UI8, CH2>(string_, string_ + kSize - 1, value);
}

#if SEAM >= _0_0_0__04
Text2::Text2(FLT value) {
  TPrintFloat<FLT, CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(DBL value) {
  TPrintFloat<DBL, CH2>(string_, string_ + kSize - 1, value);
}
#endif

const CH2* Text2::GetString() { return string_; }

Utf16Center::Utf16Center(const CH2* string, SI4 column_count)
    : string_(string), column_count(column_count) {}

Utf16Center::Utf16Center(SI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(UI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(SI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(UI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM >= _0_0_0__04
Utf16Center::Utf16Center(FLT value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(DBL value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}
#endif

const CH2* Utf16Center::GetString() {
  const CH2* string = string_;
  return (!string) ? number_.GetString() : string;
}

SI4 Utf16Center::GetColumnCount() { return column_count; }

Utf16Right::Utf16Right(const CH2* string, SI4 column_count)
    : string_(string), column_count(column_count) {}

Utf16Right::Utf16Right(SI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(UI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(SI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(UI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM >= _0_0_0__04
Utf16Right::Utf16Right(FLT value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(DBL value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}
#endif

const CH2* Utf16Right::GetString() {
  const CH2* string = string_;
  return (!string) ? number_.GetString() : string;
}

SI4 Utf16Right::GetColumnCount() { return column_count; }

}  // namespace _

_::UTF2& operator<<(::_::UTF2& utf, const CH2* cursor) {
  return utf.Set(::_::Print(utf.begin, utf.stop, cursor));
}

_::UTF2& operator<<(::_::UTF2& utf, CH2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, UI1 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, SI2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, UI2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, SI4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, UI4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, SI8 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, UI8 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

#if SEAM >= _0_0_0__04
_::UTF2& operator<<(::_::UTF2& utf, FLT value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(::_::UTF2& utf, DBL value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}
#endif

_::UTF2& operator<<(::_::UTF2& utf, ::_::Utf16Center item) {
  return utf.Set(::_::PrintCenter(utf.begin, utf.stop, item.GetString(),
                                  item.GetColumnCount()));
}

_::UTF2& operator<<(::_::UTF2& utf, ::_::Utf16Right item) {
  return utf.Set(::_::PrintRight(utf.begin, utf.stop, item.GetString(),
                                 item.GetColumnCount()));
}

#endif  //< #if USING_UTF16

#if USING_UTF32 == YES
#include "cstr4.h"
namespace _ {

const CH4* EmptyCH4() { return TStringEmpty<CH4>(); }

const CH4* NewLineCH4() { return TStringNL<CH4>(); }

const CH4* ErrorHeaderCH4() { return TStringError<CH4>(); }

BOL IsWhitespace(CH4 character) { return TIsWhitespace<CH4>(character); }

CH4 PrintableChar(CH4 value) { return TPrintableChar<CH4>(value); }

const CH4* TStringEnd(const CH4* cursor) { return TStringEnd<CH4>(cursor); }

SI4 TStringLength(const CH4* cursor) { return TStringLength<CH4, SI4>(cursor); }

const CH4* StringLineEnd(const CH4* cursor, SI4 column_count) {
  return TStringLineEnd<CH4>(cursor, column_count);
}

const CH4* StringLineEnd(const CH4* cursor, const CH4* stop, SI4 column_count) {
  return TStringLineEnd<CH4>(cursor, stop, column_count);
}

const CH4* TStringDecimalEnd(const CH4* cursor, const CH4* stop) {
  return TStringDecimalEnd<CH4>(cursor, stop);
}

const CH4* TStringDecimalEnd(const CH4* cursor) {
  return TStringDecimalEnd<CH4>(cursor);
}

const CH4* TStringSkipChar(const CH4* cursor, CH4 skip_char) {
  return TStringSkipChar<CH4>(cursor, skip_char);
}

const CH4* StringSkipSpaces(const CH4* cursor) {
  return TStringSkipSpaces<CH4>(cursor);
}

const CH4* StringSkipSpaces(const CH4* cursor, const CH4* stop) {
  return TStringSkipSpaces<CH4>(cursor, stop);
}

const CH4* StringEquals(const CH4* text_a, const CH4* text_b) {
  return TStringEquals<CH4>(text_a, text_b);
}

const CH4* StringEquals(const CH4* cursor, const CH4* stop, const CH4* text_b) {
  return TStringEquals<CH4>(cursor, stop, text_b);
}

/*
BOL TTextQualifies(const CH4* cursor) { return TTextQualifies<CH4>(cursor); }

BOL TTextQualifies(const CH4* cursor, const CH4* stop) {
  return TTextQualifies<CH4>(cursor, stop);
}*/

SI4 TStringCompare(const CH4* text_a, const CH4* text_b) {
  return TStringCompare<CH4>(text_a, text_b);
}

const CH4* StringFind(const CH4* cursor, const CH4* query) {
  return TStringFind<CH4>(cursor, query);
}

CH4* Print(CH4* cursor, CH4* stop, const CH4* string) {
  return TPrint<CH4>(cursor, stop, string);
}

CH4* Print(CH4* cursor, CH4* stop, UI4 value) {
  return TPrintUnsigned<UI4, CH4>(cursor, stop, value);
}

CH4* Print(CH4* cursor, CH4* stop, SI4 value) {
  return TPrintSigned<SI4, UI4, CH4>(cursor, stop, value);
}

CH4* Print(CH4* cursor, CH4* stop, UI8 value) {
  return TPrintUnsigned<UI8, CH4>(cursor, stop, value);
}

CH4* Print(CH4* cursor, CH4* stop, SI8 value) {
  return TPrintSigned<SI8, UI8, CH4>(cursor, stop, value);
}

#if SEAM >= _0_0_0__04
CH4* Print(CH4* cursor, CH4* stop, FLT value) {
  return TPrint<CH4>(cursor, stop, value);
}

CH4* Print(CH4* cursor, CH4* stop, DBL value) {
  return TPrint<CH4>(cursor, stop, value);
}
#endif

CH4* PrintCenter(CH4* cursor, CH4* stop, const CH4* begin, SI4 column_count) {
  return TPrintCenter<CH4>(cursor, stop, begin, column_count);
}

CH4* PrintCenter(CH4* cursor, CH4* stop, CH4 character, SI4 column_count) {
  return TPrintCenter<CH4>(cursor, stop, Text4(character).GetString(),
                           column_count);
}

CH4* PrintCenter(CH4* cursor, CH4* stop, SI4 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintCenter(CH4* cursor, CH4* stop, UI4 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintCenter(CH4* cursor, CH4* stop, UI8 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintCenter(CH4* cursor, CH4* stop, SI8 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

#if SEAM >= _0_0_0__04
CH4* PrintCenter(CH4* cursor, CH4* stop, FLT value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintCenter(CH4* cursor, CH4* stop, DBL value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}
#endif

CH4* PrintRight(CH4* cursor, CH4* stop, const CH4* begin, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, begin, column_count);
}

CH4* PrintRight(CH4* cursor, CH4* stop, CH4 character, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(character).GetString(),
                          column_count);
}

CH4* PrintRight(CH4* cursor, CH4* stop, UI4 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintRight(CH4* cursor, CH4* stop, SI4 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintRight(CH4* cursor, CH4* stop, UI8 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintRight(CH4* cursor, CH4* stop, SI8 value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

#if SEAM >= _0_0_0__04
CH4* PrintRight(CH4* cursor, CH4* stop, FLT value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}

CH4* PrintRight(CH4* cursor, CH4* stop, DBL value, SI4 column_count) {
  return TPrintRight<CH4>(cursor, stop, Text4(value).GetString(), column_count);
}
#endif

CH4* PrintHex(CH4* cursor, CH4* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<CH4, UIW>(cursor, stop, ptr);
}

CH4* PrintHex(CH4* cursor, CH4* stop, UI1 value) {
  return TPrintHex<CH4, UI1>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, SI1 value) {
  return TPrintHex<CH4, UI1>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, UI2 value) {
  return TPrintHex<CH4, UI2>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, SI2 value) {
  return TPrintHex<CH4, UI2>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, UI4 value) {
  return TPrintHex<CH4, UI4>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, SI4 value) {
  return TPrintHex<CH4, UI4>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, UI8 value) {
  return TPrintHex<CH4, UI8>(cursor, stop, value);
}

CH4* PrintHex(CH4* cursor, CH4* stop, SI8 value) {
  return TPrintHex<CH4, UI8>(cursor, stop, value);
}

#if SEAM >= _0_0_0__04
CH4* PrintHex(CH4* cursor, CH4* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<CH4, UI8>(cursor, stop, ui);
}

CH4* PrintHex(CH4* cursor, CH4* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<CH4, UI8>(cursor, stop, ui);
}
#endif

CH4* TPrintBinary(CH4* cursor, CH4* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<CH4>(cursor, stop, ptr);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, UI1 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, SI1 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, UI2 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, SI2 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, UI4 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, SI4 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, UI8 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, SI8 value) {
  return TPrintBinary<CH4>(cursor, stop, value);
}

#if SEAM >= _0_0_0__04
CH4* TPrintBinary(CH4* cursor, CH4* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<CH4, UI8>(cursor, stop, ui);
}

CH4* TPrintBinary(CH4* cursor, CH4* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<CH4, UI8>(cursor, stop, ui);
}
#endif

CH4* PrintSocket(CH4* cursor, CH4* stop, const void* begin, size_t size) {
  return TPrintSocket<CH4>(cursor, stop, begin,
                           reinterpret_cast<const CH4*>(begin) + size);
}

CH4* PrintSocket(CH4* cursor, CH4* stop, const void* begin, const void* end) {
  return TPrintSocket<CH4>(cursor, stop, begin, end);
}

const CH4* Scan(const CH4* cursor, SI1& result) {
  return TScanSigned<SI1, UI2, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, UI1& result) {
  return TScanUnsigned<UI1, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, SI2& result) {
  return TScanSigned<SI2, UI2, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, UI2& result) {
  return TScanUnsigned<UI2, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, SI4& result) {
  return TScanSigned<SI4, UI4, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, UI4& result) {
  return TScanUnsigned<UI4, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, SI8& result) {
  return TScanSigned<SI8, UI8, CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, UI8& result) {
  return TScanUnsigned<UI8, CH4>(cursor, result);
}

#if SEAM >= _0_0_0__04
const CH4* Scan(const CH4* cursor, FLT& result) {
  return TScanFloat<CH4>(cursor, result);
}

const CH4* Scan(const CH4* cursor, DBL& result) {
  return TScanFloat<CH4>(cursor, result);
}
#endif

/*
void COuUtf32(UIW* begin) { return TCOut<CH4>(begin); }

void COuUtf32(UIW* begin) { return TCOut<CH4>(begin); }*/

UTF4::UTF4(CH4* begin, size_t buffer_size)
    : begin(begin), stop(begin + buffer_size - 1) {
  ASSERT(begin);
  ASSERT(buffer_size);
}

UTF4::UTF4(CH4* begin, CH4* stop) : begin(begin), stop(stop) {
  ASSERT(begin);
  ASSERT(begin < stop);
}

UTF4::UTF4(const UTF4& other) : begin(other.begin), stop(other.stop) {
  ASSERT(begin);
  ASSERT(stop);
}

UTF4& UTF4::Set(CH4* new_cursor) {
  begin = new_cursor;
  return *this;
}

UTF4& UTF4::Hex(UI1 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(SI1 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(UI2 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(SI2 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(UI4 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(SI4 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(UI8 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

UTF4& UTF4::Hex(SI8 value) { return Set(TPrintHex<CH4>(begin, stop, value)); }

#if SEAM >= _0_0_0__04
UTF4& UTF4::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<CH4>(begin, stop, value));
}
#endif

UTF4& UTF4::Hex(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintHex<CH4>(begin, stop, ptr));
}

UTF4& UTF4::Binary(UI1 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(SI1 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(UI2 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(SI2 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(UI4 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(SI4 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(UI8 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

UTF4& UTF4::Binary(SI8 value) {
  return Set(TPrintBinary<CH4>(begin, stop, value));
}

#if SEAM >= _0_0_0__04
UTF4& UTF4::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH4>(begin, stop, ui));
}

UTF4& UTF4::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH4>(begin, stop, ui));
}
#endif

UTF4& UTF4::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<CH4>(begin, stop, ptr));
}

Text4::Text4() {}

Text4::Text4(CH4 character) {
  *string_ = character;
  *(string_ + 1) = 0;
}

Text4::Text4(SI4 value) {
  TPrintSigned<SI4, UI4, CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(UI4 value) {
  TPrintUnsigned<UI4, CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(SI8 value) {
  TPrintSigned<SI8, UI8, CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(UI8 value) {
  TPrintUnsigned<UI8, CH4>(string_, string_ + kSize - 1, value);
}

#if SEAM >= _0_0_0__04
Text4::Text4(FLT value) {
  TPrintFloat<CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(DBL value) {
  TPrintFloat<CH4>(string_, string_ + kSize - 1, value);
}
#endif

const CH4* Text4::GetString() { return string_; }

Utf32Center::Utf32Center(const CH4* string, SI4 column_count)
    : string_(string), column_count(column_count) {}

Utf32Center::Utf32Center(SI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(UI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(SI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(UI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM >= _0_0_0__04
Utf32Center::Utf32Center(FLT value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(DBL value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}
#endif

const CH4* Utf32Center::GetString() {
  const CH4* string = string_;
  return (!string) ? number_.GetString() : string;
}

SI4 Utf32Center::GetColumnCount() { return column_count; }

Utf32Right::Utf32Right(const CH4* string, SI4 column_count)
    : string_(string), column_count(column_count) {}

Utf32Right::Utf32Right(SI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(UI4 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(SI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(UI8 value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM >= _0_0_0__04
Utf32Right::Utf32Right(FLT value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(DBL value, SI4 column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}
#endif

const CH4* Utf32Right::GetString() {
  const CH4* string = string_;
  return (!string) ? number_.GetString() : string;
}

SI4 Utf32Right::GetColumnCount() { return column_count; }

}  // namespace _

_::UTF4& operator<<(::_::UTF4& utf, const CH4* cursor) {
  return utf.Set(::_::Print(utf.begin, utf.stop, cursor));
}

_::UTF4& operator<<(::_::UTF4& utf, CH4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, UI1 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, SI2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, UI2 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, SI4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, UI4 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, SI8 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, UI8 value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

#if SEAM >= _0_0_0__04
_::UTF4& operator<<(::_::UTF4& utf, FLT value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(::_::UTF4& utf, DBL value) {
  return utf.Set(::_::Print(utf.begin, utf.stop, value));
}
#endif

_::UTF4& operator<<(::_::UTF4& utf, ::_::Utf32Center item) {
  return utf.Set(::_::PrintCenter(utf.begin, utf.stop, item.GetString(),
                                  item.GetColumnCount()));
}

_::UTF4& operator<<(::_::UTF4& utf, ::_::Utf32Right item) {
  return utf.Set(::_::PrintRight(utf.begin, utf.stop, item.GetString(),
                                 item.GetColumnCount()));
}

#endif  //< #if USING_UTF32
#endif  //< #if SEAM >= _0_0_0__03
