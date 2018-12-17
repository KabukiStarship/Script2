/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \script2_str.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__02
#include <cstdio>

#include "tstr.h"

#include "cascii.h"
#include "csocket.h"
#include "tbinary.h"

#if SEAM == _0_0_0__02
#include "test_release.inl"
#else
#include "test_release.inl"
#endif

#if USING_UTF

namespace _ {

int Console(CObject& obj, SIW function, void* arg) {
  return TCOut<CH1>(obj, function, arg);
}

int COutHeap(CObject& obj, SIW function, void* arg) {
  return TCOutHeap<CH1>(obj, function, arg);
}

void UTFAlignCenterSTR1(int column_count, void* item, void* destination) {
  ASSERT(item);
  ASSERT(destination);
  ASSERT(column_count >= 0);
}

}  // namespace _

#endif  // #if USING_UTF

#if USING_UTF8
#include "cstr1.h"
namespace _ {

const CH1* TStringEmpty() { return TStringEmpty<CH1>(); }

const CH1* StringNL() { return TStringNL<CH1>(); }

const CH1* StringError() { return TStringError<CH1>(); }

BOL IsWhitespace(CH1 character) { return TIsWhitespace<CH1>(character); }

CH1 PrintableChar(CH1 value) { return TPrintableChar<CH1>(value); }

const CH1* StringEnd(const CH1* text) { return TStringEnd<CH1>(text); }

int StringLength(const CH1* text) { return TStringLength<CH1, int>(text); }

const CH1* StringLineEnd(const CH1* text, int column_count) {
  return TStringLineEnd<CH1>(text, column_count);
}

const CH1* StringLineEnd(const CH1* text, const CH1* text_end,
                          int column_count) {
  return TStringLineEnd<CH1>(text, text_end, column_count);
}

const CH1* StringDecimalStop(const CH1* text, const CH1* text_end) {
  return TStringDecimalEnd<CH1>(text);
}

const CH1* StringDecimalStop(const CH1* text) {
  return TStringDecimalEnd<CH1>(text);
}

const CH1* TStringSkipChar(const CH1* text, CH1 skip_char) {
  return TStringSkipChar<CH1>(text, skip_char);
}

const CH1* StringSkipSpaces(const CH1* text) {
  return TStringSkipSpaces<CH1>(text);
}

const CH1* StringSkipSpaces(const CH1* text, const CH1* text_end) {
  return TStringSkipSpaces<CH1>(text, text_end);
}

const CH1* StringEquals(const CH1* text_a, const CH1* text_b) {
  return TStringEquals<CH1>(text_a, text_b);
}

const CH1* StringEquals(const CH1* text, const CH1* text_end,
                         const CH1* query) {
  return TStringEquals<CH1>(text, text_end, query);
}

BOL TextQualifies(const CH1* text) { return TStringIsntEmpty<CH1>(text); }

BOL TextQualifies(const CH1* text, const CH1* text_end) {
  return TStringIsntEmpty<CH1>(text, text_end);
}

int StringCompare(const CH1* text_a, const CH1* text_b) {
  return TStringCompare<CH1>(text_a, text_b);
}
/*
int TStringCompare(const CH1* text_a, const CH1* text_end,
                  const CH1* text_b) {
  return TStringCompare<CH1>(text_a, text_end, text_b);
}*/

const CH1* StringFind(const CH1* text, const CH1* query) {
  return TStringFind<CH1>(text, query);
}

CH1* Print(CH1* begin, CH1* stop, const CH1* string_) {
  return TPrint<CH1>(begin, stop, string_);
}

CH1* Print(CH1* begin, CH1* stop, CH1 character) {
  return TPrintChar<CH1>(begin, stop, character);
}

CH1* Print(CH1* begin, CH1* stop, UI8 value) {
  return TPrintUnsigned<UI8, CH1>(begin, stop, value);
}

CH1* Print(CH1* begin, CH1* stop, SI8 value) {
  return TPrintSigned<SI8, UI8, CH1>(begin, stop, value);
}

#if ALU_WORD_SIZE != 32
CH1* Print(CH1* begin, CH1* stop, UI4 value) {
  return Print(begin, stop, (UI8)value);
}

CH1* Print(CH1* begin, CH1* stop, SI4 value) {
  return Print(begin, stop, (SI8)value);
}
#else
CH1* Print(CH1* begin, CH1* stop, UI4 value) {
  return TPrintUnsigned<UI8, CH1>(begin, stop, (UI8)value);
}

CH1* Print(CH1* begin, CH1* stop, SI4 value) {
  return TPrintSigned<SI8, UI8, CH1>(begin, stop, (SI8)value);
}
#endif

#if SEAM >= _0_0_0__03

CH1* PrintCenter(CH1* begin, CH1* stop, FLT value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* begin, CH1* stop, DBL value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, FLT value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, DBL value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

#endif  //< #if SEAM >= _0_0_0__03

CH1* PrintCenter(CH1* begin, CH1* stop, const CH1* string_,
                  int column_count) {
  return TPrintCenter<CH1>(begin, stop, string_, column_count);
}

CH1* PrintCenter(CH1* begin, CH1* stop, CH1 character, int column_count) {
  return TPrintCenter<CH1>(begin, stop, Utf8Text(character).String(),
                            column_count);
}

CH1* PrintCenter(CH1* begin, CH1* stop, SI4 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* begin, CH1* stop, UI4 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* begin, CH1* stop, UI8 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintCenter(CH1* begin, CH1* stop, SI8 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, const CH1* string_,
                 int column_count) {
  return TPrintRight<CH1>(begin, stop, string_, column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, CH1 character, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(character).String(),
                           column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, UI4 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, SI4 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, UI8 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintRight(CH1* begin, CH1* stop, SI8 value, int column_count) {
  return TPrintRight<CH1>(begin, stop, Utf8Text(value).String(), column_count);
}

CH1* PrintHex(CH1* begin, CH1* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<CH1>(begin, stop, ptr);
}

CH1* PrintHex(CH1* begin, CH1* stop, UI1 value) {
  return TPrintHex<CH1, UI1>(begin, stop, value);
}

CH1* PrintHex(CH1* begin, CH1* stop, SI1 value) {
  return TPrintHex<CH1, UI1>(begin, stop, (UI1)value);
}

CH1* PrintHex(CH1* begin, CH1* stop, UI2 value) {
  return TPrintHex<CH1, UI2>(begin, stop, value);
}

CH1* PrintHex(CH1* begin, CH1* stop, SI2 value) {
  return TPrintHex<CH1, UI2>(begin, stop, (UI2)value);
}

CH1* PrintHex(CH1* begin, CH1* stop, UI4 value) {
  return TPrintHex<CH1, UI4>(begin, stop, value);
}

CH1* PrintHex(CH1* begin, CH1* stop, SI4 value) {
  return TPrintHex<CH1, UI4>(begin, stop, (UI4)value);
}

CH1* PrintHex(CH1* begin, CH1* stop, UI8 value) {
  return TPrintHex<CH1, UI8>(begin, stop, value);
}

CH1* PrintHex(CH1* begin, CH1* stop, SI8 value) {
  return TPrintHex<CH1, UI8>(begin, stop, (UI8)value);
}

CH1* PrintHex(CH1* begin, CH1* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<CH1, UI4>(begin, stop, ui);
}

CH1* PrintHex(CH1* begin, CH1* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<CH1, UI8>(begin, stop, ui);
}

CH1* PrintBinary(CH1* begin, CH1* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<CH1>(begin, stop, ptr);
}

CH1* PrintBinary(CH1* begin, CH1* stop, UI1 value) {
  return TPrintBinary<CH1, UI1>(begin, stop, value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, SI1 value) {
  return TPrintBinary<CH1, UI1>(begin, stop, (UI1)value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, UI2 value) {
  return TPrintBinary<CH1, UI2>(begin, stop, value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, SI2 value) {
  return TPrintBinary<CH1, UI2>(begin, stop, (UI2)value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, UI4 value) {
  return TPrintBinary<CH1, UI4>(begin, stop, value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, SI4 value) {
  return TPrintBinary<CH1, UI4>(begin, stop, value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, UI8 value) {
  return TPrintBinary<CH1, UI8>(begin, stop, value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, SI8 value) {
  return TPrintBinary<CH1, UI8>(begin, stop, value);
}

CH1* PrintBinary(CH1* begin, CH1* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<CH1, UI4>(begin, stop, ui);
}

CH1* PrintBinary(CH1* begin, CH1* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<CH1, UI8>(begin, stop, ui);
}

CH1* PrintSocket(CH1* start, CH1* stop, const void* begin, size_t size) {
  return TPrintSocket<CH1>(start, stop, begin,
                            reinterpret_cast<const CH1*>(begin) + size);
}

CH1* PrintSocket(CH1* start, CH1* stop, const void* begin, const void* end) {
  return TPrintSocket<CH1>(start, stop, begin, end);
}

CH1* PrintLine(CH1* cursor, CH1* stop, CH1 token, int column_count) {
  return TPrintLine<CH1>(cursor, stop, token, column_count);
}

CH1* TPrintLineString(CH1* cursor, CH1* stop, const CH1* string_,
                       int column_count) {
  return TPrintLineString<CH1>(cursor, stop, string_, column_count);
}

const CH1* Scan(const CH1* string_, SI1& result) {
  return TScanSigned<SI1, UI1, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, UI1& result) {
  return TScanUnsigned<UI1, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, SI2& result) {
  return TScanSigned<SI2, UI2, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, UI2& result) {
  return TScanUnsigned<UI2, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, SI4& result) {
  return TScanSigned<SI4, UI4, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, UI4& result) {
  return TScanUnsigned<UI4, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, SI8& result) {
  return TScanSigned<SI8, UI8, CH1>(string_, result);
}

const CH1* Scan(const CH1* string_, UI8& result) {
  return TScanUnsigned<UI8, CH1>(string_, result);
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

UTF1& UTF1::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<CH1>(begin, stop, ui));
}

UTF1& UTF1::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<CH1>(begin, stop, ui));
}

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

UTF1& UTF1::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH1>(begin, stop, ui));
}

UTF1& UTF1::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH1>(begin, stop, ui));
}

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

#if SEAM >= _0_0_0__03
Utf8Text::Utf8Text(FLT value) { Print(string_, string_ + kSize - 1, value); }

Utf8Text::Utf8Text(DBL value) { Print(string_, string_ + kSize - 1, value); }

#endif  //< #if SEAM == _0_0_0__03

const CH1* Utf8Text::String() { return string_; }

Utf8Center::Utf8Center(const CH1* string_, int column_count)
    : string_(string_), column_count(column_count) {}

Utf8Center::Utf8Center(SI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(UI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(SI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(UI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM == _0_0_0__03
Utf8Center::Utf8Center(FLT value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Center::Utf8Center(DBL value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}
#endif

const CH1* Utf8Center::String() {
  return (string_ == nullptr) ? number_.String() : string_;
}

int Utf8Center::GetColumnCount() { return column_count; }

Utf8Right::Utf8Right(const CH1* string_, int column_count)
    : string_(string_), column_count(column_count) {}

Utf8Right::Utf8Right(SI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(UI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(SI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(UI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

#if SEAM >= _0_0_0__03
Utf8Right::Utf8Right(FLT value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf8Right::Utf8Right(DBL value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}
#endif

const CH1* Utf8Right::String() {
  return (string_ == nullptr) ? number_.String() : string_;
}

int Utf8Right::GetColumnCount() { return column_count; }

Utf8Line::Utf8Line(CH1 token, int column_count)
    : token(token), column_count(column_count) {
  // Nothing to do here. (:-)-+=<
}

Utf8LineString::Utf8LineString(const CH1* string_, int column_count)
    : string_(string_), column_count(column_count) {
  // Nothing to do here. (:-)-+=<
}

UIW* COutUtf8(UIW* begin, SIW function, void* arg) {
  return TCOut<CH1>(begin, function, arg);
}

UIW* COutAutoUtf8(UIW* begin, SIW function, void* arg) {
  return TCOutHeap<CH1>(begin, function, arg);
}

}  // namespace _

_::UTF1& operator<<(_::UTF1& utf, const CH1* string_) {
  return utf.Set(_::Print(utf.begin, utf.stop, string_));
}

_::UTF1& operator<<(_::UTF1& utf, CH1 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI1 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI4 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI4 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI8 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI8 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

#if SEAM == _0_0_0__03
_::UTF1& operator<<(_::UTF1& utf, FLT value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, DBL value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}
#endif

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Center item) {
  return utf.Set(_::PrintCenter(utf.begin, utf.stop, item.String(),
                                item.GetColumnCount()));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Right item) {
  return utf.Set(
      _::PrintRight(utf.begin, utf.stop, item.String(), item.GetColumnCount()));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Line line) {
  return utf.Set(
      _::PrintLine(utf.begin, utf.stop, line.token, line.column_count));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8LineString line) {
  return utf.Set(_::TPrintLineString(utf.begin, utf.stop, line.string_,
                                     line.column_count));
}

#endif  //< #if USING_UTF8

#if USING_UTF16
#include "str2.h"
namespace _ {

const CH2* Empty() { return Empty<CH2>(); }

const CH2* NewLine() { return NewLine<CH2>(); }

const CH2* ErrorHeader() { return ErrorHeader<CH2>(); }

BOL IsWhitespace(CH2 character) {
  return TIsWhitespace<CH2>(character);
}

CH2 PrintableChar(CH2 value) {
  return PrintableChar<CH2>(value);
}

const CH2* TStringEnd(const CH2* text) {
  return TStringEnd<CH2>(text);
}

int TStringLength(const CH2* text) {
  return TStringLength<CH2, int>(text);
}

CH2* StringClone(const CH2* text) {
  return StringClone<CH2>(text);
}

const CH2* StringLineEnd(const CH2* text, int column_count) {
  return StringLineEnd<CH2>(text, column_count);
}

const CH2* StringLineEnd(const CH2* text, const CH2* text_end,
                              int column_count) {
  return StringLineEnd<CH2>(text, text_end, column_count);
}

const CH2* TStringDecimalEnd(const CH2* text,
                                  const CH2* text_end) {
  return TStringDecimalEnd<const CH2>(text, text_end);
}

const CH2* TStringDecimalEnd(const CH2* text) {
  return TStringDecimalEnd<const CH2>(text);
}

const CH2* TStringSkipChar(const CH2* text, CH2 skip_char) {
  return TStringSkipChar<CH2>(text, skip_char);
}

const CH2* StringSkipSpaces(const CH2* text) {
  return StringSkipSpaces<CH2>(text);
}

const CH2* StringSkipSpaces(const CH2* text,
                                 const CH2* text_end) {
  return StringSkipSpaces<CH2>(text, text_end);
}

const CH2* StringEquals(const CH2* text_a, const CH2* text_b) {
  return StringEquals<CH2>(text_a, text_b);
}

const CH2* StringEquals(const CH2* text, const CH2* text_end,
                             const CH2* query) {
  return StringEquals<CH2>(text, text_end, query);
}

BOL TextQualifies(const CH2* text) {
  return TextQualifies<CH2>(text);
}

BOL TextQualifies(const CH2* text, const CH2* text_end) {
  return TextQualifies<CH2>(text, text_end);
}

int TStringCompare(const CH2* text_a, const CH2* text_b) {
  return TStringCompare<CH2>(text_a, text_b);
}

int TStringCompare(const CH2* text_a, const CH2* text_end,
                   const CH2* text_b) {
  return TStringCompare<CH2>(text_a, text_end, text_b);
}

const CH2* StringFind(const CH2* text, const CH2* query) {
  return StringFind<CH2>(text, query);
}

CH2* Print(CH2* begin, CH2* stop, const CH2* string_) {
  return TPrint<CH2>(begin, stop, string_);
}

CH2* Print(CH2* begin, CH2* stop, CH2 character) {
  return TPrintChar<CH2>(begin, stop, character);
}

CH2* Print(CH2* begin, CH2* stop, UI4 value) {
  return TPrint<CH2>(begin, stop, value);
}

CH2* Print(CH2* begin, CH2* stop, SI4 value) {
  return TPrint<CH2>(begin, stop, value);
}

CH2* Print(CH2* begin, CH2* stop, UI8 value) {
  return TPrint<CH2>(begin, stop, value);
}

CH2* Print(CH2* begin, CH2* stop, SI8 value) {
  return TPrint<CH2>(begin, stop, value);
}

CH2* Print(CH2* begin, CH2* stop, FLT value) {
  return TPrint<CH2>(begin, stop, value);
}

CH2* Print(CH2* begin, CH2* stop, DBL value) {
  return TPrint<CH2>(begin, stop, value);
}

CH2* PrintCenter(CH2* begin, CH2* stop, const CH2* string_,
                      int column_count) {
  return PrintCenter<CH2>(begin, stop, string_, column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, CH2 character,
                      int column_count) {
  return PrintCenter<CH2>(begin, stop, Text2(character).GetString(),
                               column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, SI4 value,
                      int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, UI4 value,
                      int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, UI8 value,
                      int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, SI8 value,
                      int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, FLT value,
                      int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintCenter(CH2* begin, CH2* stop, DBL value,
                      int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, const CH2* string_,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, string_, column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, CH2 character,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(character).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, UI4 value,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, SI4 value,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, UI8 value,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, SI8 value,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, FLT value,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintRight(CH2* begin, CH2* stop, DBL value,
                     int column_count) {
  return TPrintRight<CH2>(begin, stop, Text2(value).GetString(),
                               column_count);
}

CH2* PrintHex(CH2* begin, CH2* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<CH2>(begin, stop, ptr);
}

CH2* PrintHex(CH2* begin, CH2* stop, UI1 value) {
  return TPrintHex<CH2, UI1>(begin, stop, value);
}

CH2* PrintHex(CH2* begin, CH2* stop, SI1 value) {
  return TPrintHex<CH2, UI1>(begin, stop, (UI1)value);
}

CH2* PrintHex(CH2* begin, CH2* stop, UI2 value) {
  return TPrintHex<CH2, UI2>(begin, stop, value);
}

CH2* PrintHex(CH2* begin, CH2* stop, SI2 value) {
  return TPrintHex<CH2, UI2>(begin, stop, (UI2)value);
}

CH2* PrintHex(CH2* begin, CH2* stop, UI4 value) {
  return TPrintHex<CH2, UI4>(begin, stop, value);
}

CH2* PrintHex(CH2* begin, CH2* stop, SI4 value) {
  return TPrintHex<CH2, UI4>(begin, stop, (UI4)value);
}

CH2* PrintHex(CH2* begin, CH2* stop, UI8 value) {
  return TPrintHex<CH2, UI8>(begin, stop, value);
}

CH2* PrintHex(CH2* begin, CH2* stop, SI8 value) {
  return TPrintHex<CH2, UI8>(begin, stop, (UI8)value);
}

CH2* PrintHex(CH2* begin, CH2* stop, FLT value) {
  UI4 float_as_ui32 = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<CH2, UI4>(begin, stop, float_as_ui32);
}

CH2* PrintHex(CH2* begin, CH2* stop, DBL value) {
  UI8 double_as_ui64 = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<CH2, UI8>(begin, stop, double_as_ui64);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<CH2>(begin, stop, ptr);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, UI1 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, SI1 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, UI2 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, SI2 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, UI4 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, SI4 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, UI8 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, SI8 value) {
  return TPrintBinary<CH2>(begin, stop, value);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Print(begin, stop, ui);
}

CH2* TPrintBinary(CH2* begin, CH2* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Print(begin, stop, ui);
}

CH2* PrintSocket(CH2* begin, CH2* stop, const void* begin,
                      size_t size) {
  return PrintSocket<CH2>(begin, stop, begin,
                               reinterpret_cast<const CH2*>(begin) + size);
}

CH2* PrintSocket(CH2* begin, CH2* stop, const void* begin,
                      const void* stop) {
  return PrintSocket<CH2>(begin, stop, begin, stop);
}
}  // namespace _
}  //< namespace _

const CH2* Scan(const CH2* string_, SI1& result) {
  return TScanSigned<CH2, SI1>(string_, result);
}

const CH2* Scan(const CH2* string_, UI1& result) {
  return ScanUnsigned<CH2, UI1>(string_, result);
}

const CH2* Scan(const CH2* string_, SI2& result) {
  return TScanSigned<CH2, SI2>(string_, result);
}

const CH2* Scan(const CH2* string_, UI2& result) {
  return ScanUnsigned<CH2, UI2>(string_, result);
}

const CH2* Scan(const CH2* string_, SI4& result) {
  return TScanSigned<CH2, SI4>(string_, result);
}

const CH2* Scan(const CH2* string_, UI4& result) {
  return ScanUnsigned<CH2, UI4>(string_, result);
}

const CH2* Scan(const CH2* string_, SI8& result) {
  return TScanSigned<CH2, SI8>(string_, result);
}

const CH2* Scan(const CH2* string_, UI8& result) {
  return ScanUnsigned<CH2, UI8>(string_, result);
}

const CH2* Scan(const CH2* string_, FLT& result) {
  return TScan<CH2>(string_, result);
}

const CH2* Scan(const CH2* string_, DBL& result) {
  return TScan<CH2>(string_, result);
}

void COutUtf16(UIW* begin) { return Console<CH2>(begin); }

void DCOutUtf16(UIW* begin) { return DCOut<CH2>(begin); }

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

UTF2& UTF2::Hex(UI1 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(SI1 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(UI2 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(SI2 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(UI4 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(SI4 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(UI8 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(SI8 value) {
  return Set(TPrintHex<CH2>(begin, stop, value));
}

UTF2& UTF2::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<CH2>(begin, stop, ui));
}

UTF2& UTF2::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<CH2>(begin, stop, ui));
}

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

UTF2& UTF2::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH2>(begin, stop, ui));
}

UTF2& UTF2::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH2>(begin, stop, ui));
}

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
  TPrint<CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(UI4 value) {
  TPrint<CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(SI8 value) {
  TPrint<CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(UI8 value) {
  TPrint<CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(FLT value) {
  TPrint<CH2>(string_, string_ + kSize - 1, value);
}

Text2::Text2(DBL value) {
  TPrint<CH2>(string_, string_ + kSize - 1, value);
}

const CH2* Text2::GetString() { return string_; }

Utf16Center::Utf16Center(const CH2* string_, int column_count)
    : string_(string_), column_count(column_count) {}

Utf16Center::Utf16Center(SI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(UI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(SI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(UI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(FLT value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Center::Utf16Center(DBL value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

const CH2* Utf16Center::GetString() {
  return (string_ == nullptr) ? number_.GetString() : string_;
}

int Utf16Center::GetColumnCount() { return column_count; }

Utf16Right::Utf16Right(const CH2* string_, int column_count)
    : string_(string_), column_count(column_count) {}

Utf16Right::Utf16Right(SI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(UI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(SI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(UI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(FLT value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf16Right::Utf16Right(DBL value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

const CH2* Utf16Right::GetString() {
  return (string_ == nullptr) ? number_.GetString() : string_;
}

int Utf16Right::GetColumnCount() { return column_count; }

}  //< namespace _

_::UTF2& operator<<(_::UTF2& utf, const CH2* string_) {
  return utf.Set(_::Print(utf.begin, utf.stop, string_));
}

_::UTF2& operator<<(_::UTF2& utf, CH2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI1 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI4 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI4 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI8 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI8 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, FLT value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, DBL value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, _::Utf16Center item) {
  utf.Set(_::PrintCenter(utf.begin, utf.stop, item.GetString(),
                         item.GetColumnCount()));
}

_::UTF2& operator<<(_::UTF2& utf, _::Utf16Right item) {
  utf.Set(_::PrintRight(utf.begin, utf.stop, item.GetString(),
                        item.GetColumnCount()));
}

#endif  //< #if USING_UTF16

#if USING_UTF32
#include "str4.h"
namespace _ {

const CH4* Empty() { return Empty<CH4>(); }

const CH4* NewLine() { return NewLine<CH4>(); }

const CH4* ErrorHeader() { return ErrorHeader<CH4>(); }

BOL IsWhitespace(CH4 character) {
  return TIsWhitespace<CH4>(character);
}

CH4 PrintableChar(CH4 value) {
  return PrintableChar<CH4>(value);
}

const CH4* TStringEnd(const CH4* text) {
  return TStringEnd<CH4>(text);
}

int TStringLength(const CH4* text) {
  return TStringLength<CH4, int>(text);
}

CH4* StringClone(const CH4* text) {
  return StringClone<CH4>(text);
}

const CH4* StringLineEnd(const CH4* text, int column_count) {
  return StringLineEnd<CH4>(text, column_count);
}

const CH4* StringLineEnd(const CH4* text, const CH4* text_end,
                              int column_count) {
  return StringLineEnd<CH4>(text, text_end, column_count);
}

const CH4* TStringDecimalEnd(const CH4* text,
                                  const CH4* text_end) {
  return TStringDecimalEnd<const CH4>(text, text_end);
}

const CH4* TStringDecimalEnd(const CH4* text) {
  return TStringDecimalEnd<const CH4>(text);
}

const CH4* TStringSkipChar(const CH4* text, CH4 skip_char) {
  return TStringSkipChar<CH4>(text, skip_char);
}

const CH4* StringSkipSpaces(const CH4* text) {
  return StringSkipSpaces<CH4>(text);
}

const CH4* StringSkipSpaces(const CH4* text,
                                 const CH4* text_end) {
  return StringSkipSpaces<CH4>(text, text_end);
}

const CH4* StringEquals(const CH4* text_a, const CH4* text_b) {
  return StringEquals<CH4>(text_a, text_b);
}

const CH4* StringEquals(const CH4* cursor, const CH4* stop,
                             const CH4* text_b) {
  return StringEquals<CH4>(cursor, stop, text_b);
}

BOL TextQualifies(const CH4* text) {
  return TextQualifies<CH4>(text);
}

BOL TextQualifies(const CH4* text, const CH4* text_end) {
  return TextQualifies<CH4>(text, text_end);
}

int TStringCompare(const CH4* text_a, const CH4* text_b) {
  return TStringCompare<CH4>(text_a, text_b);
}

int TStringCompare(const CH4* text_a, const CH4* text_end,
                   const CH4* text_b) {
  return TStringCompare<CH4>(text_a, text_end, text_b);
}

const CH4* StringFind(const CH4* text, const CH4* query) {
  return StringFind<CH4>(text, query);
}

CH4* Print(CH4* begin, CH4* stop, const CH4* string_) {
  return TPrint<CH4>(begin, stop, string_);
}

CH4* Print(CH4* begin, CH4* stop, CH4 character) {
  return TPrintChar<CH4>(begin, stop, character);
}

CH4* Print(CH4* begin, CH4* stop, UI4 value) {
  return TPrint<CH4>(begin, stop, value);
}

CH4* Print(CH4* begin, CH4* stop, SI4 value) {
  return TPrint<CH4>(begin, stop, value);
}

CH4* Print(CH4* begin, CH4* stop, UI8 value) {
  return TPrint<CH4>(begin, stop, value);
}

CH4* Print(CH4* begin, CH4* stop, SI8 value) {
  return TPrint<CH4>(begin, stop, value);
}

CH4* Print(CH4* begin, CH4* stop, FLT value) {
  return TPrint<CH4>(begin, stop, value);
}

CH4* Print(CH4* begin, CH4* stop, DBL value) {
  return TPrint<CH4>(begin, stop, value);
}

CH4* PrintCenter(CH4* begin, CH4* stop, const CH4* string_,
                      int column_count) {
  return PrintCenter<CH4>(begin, stop, string_, column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, CH4 character,
                      int column_count) {
  return PrintCenter<CH4>(begin, stop, Text4(character).GetString(),
                               column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, SI4 value,
                      int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, UI4 value,
                      int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, UI8 value,
                      int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, SI8 value,
                      int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, FLT value,
                      int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintCenter(CH4* begin, CH4* stop, DBL value,
                      int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, const CH4* string_,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, string_, column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, CH4 character,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(character).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, UI4 value,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, SI4 value,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, UI8 value,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, SI8 value,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, FLT value,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintRight(CH4* begin, CH4* stop, DBL value,
                     int column_count) {
  return TPrintRight<CH4>(begin, stop, Text4(value).GetString(),
                               column_count);
}

CH4* PrintHex(CH4* begin, CH4* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<CH4, UIW>(begin, stop, ptr);
}

CH4* PrintHex(CH4* begin, CH4* stop, UI1 value) {
  return TPrintHex<CH4, UI1>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, SI1 value) {
  return TPrintHex<CH4, UI1>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, UI2 value) {
  return TPrintHex<CH4, UI2>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, SI2 value) {
  return TPrintHex<CH4, UI2>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, UI4 value) {
  return TPrintHex<CH4, UI4>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, SI4 value) {
  return TPrintHex<CH4, UI4>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, UI8 value) {
  return TPrintHex<CH4, UI8>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, SI8 value) {
  return TPrintHex<CH4, UI8>(begin, stop, value);
}

CH4* PrintHex(CH4* begin, CH4* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<CH4, UI8>(begin, stop, ui);
}

CH4* PrintHex(CH4* begin, CH4* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<CH4, UI8>(begin, stop, ui);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<CH4>(begin, stop, ptr);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, UI1 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, SI1 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, UI2 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, SI2 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, UI4 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, SI4 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, UI8 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, SI8 value) {
  return TPrintBinary<CH4>(begin, stop, value);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<CH4, UI8>(begin, stop, ui);
}

CH4* TPrintBinary(CH4* begin, CH4* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<CH4, UI8>(begin, stop, ui);
}

CH4* PrintSocket(CH4* begin, CH4* stop, const void* begin,
                      size_t size) {
  return PrintSocket<CH4>(begin, stop, begin,
                               reinterpret_cast<const CH4*>(begin) + size);
}

CH4* PrintSocket(CH4* begin, CH4* stop, const void* begin,
                      const void* stop) {
  return PrintSocket<CH4>(begin, stop, begin, stop);
}

const CH4* Scan(const CH4* string_, SI1& result) {
  return TScanSigned<CH4, SI1>(string_, result);
}

const CH4* Scan(const CH4* string_, UI1& result) {
  return ScanUnsigned<CH4, UI1>(string_, result);
}

const CH4* Scan(const CH4* string_, SI2& result) {
  return TScanSigned<CH4, SI2>(string_, result);
}

const CH4* Scan(const CH4* string_, UI2& result) {
  return ScanUnsigned<CH4, UI2>(string_, result);
}

const CH4* Scan(const CH4* string_, SI4& result) {
  return TScanSigned<CH4, SI4>(string_, result);
}

const CH4* Scan(const CH4* string_, UI4& result) {
  return ScanUnsigned<CH4, UI4>(string_, result);
}

const CH4* Scan(const CH4* string_, SI8& result) {
  return TScanSigned<CH4, SI8>(string_, result);
}

const CH4* Scan(const CH4* string_, UI8& result) {
  return ScanUnsigned<CH4, UI8>(string_, result);
}

const CH4* Scan(const CH4* string_, FLT& result) {
  return TScan<CH4>(string_, result);
}

const CH4* Scan(const CH4* string_, DBL& result) {
  return TScan<CH4>(string_, result);
}

void COuUtf32(UIW* begin) { return Console<CH4>(begin); }

void COuUtf32(UIW* begin) { return DCOut<CH4>(begin); }

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

UTF4& UTF4::Hex(UI1 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(SI1 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(UI2 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(SI2 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(UI4 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(SI4 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(UI8 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(SI8 value) {
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<CH4>(begin, stop, value));
}

UTF4& UTF4::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<CH4>(begin, stop, value));
}

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

UTF4& UTF4::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH4>(begin, stop, ui));
}

UTF4& UTF4::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<CH4>(begin, stop, ui));
}

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
  TPrint<CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(UI4 value) {
  TPrint<CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(SI8 value) {
  TPrint<CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(UI8 value) {
  TPrint<CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(FLT value) {
  TPrint<CH4>(string_, string_ + kSize - 1, value);
}

Text4::Text4(DBL value) {
  TPrint<CH4>(string_, string_ + kSize - 1, value);
}

const CH4* Text4::GetString() { return string_; }

Utf32Center::Utf32Center(const CH4* string_, int column_count)
    : string_(string_), column_count(column_count) {}

Utf32Center::Utf32Center(SI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(UI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(SI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(UI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(FLT value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Center::Utf32Center(DBL value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

const CH4* Utf32Center::GetString() {
  return (string_ == nullptr) ? number_.GetString() : string_;
}

int Utf32Center::GetColumnCount() { return column_count; }

Utf32Right::Utf32Right(const CH4* string_, int column_count)
    : string_(string_), column_count(column_count) {}

Utf32Right::Utf32Right(SI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(UI4 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(SI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(UI8 value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(FLT value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

Utf32Right::Utf32Right(DBL value, int column_count)
    : string_(nullptr), number_(value), column_count(column_count) {}

const CH4* Utf32Right::GetString() {
  return (string_ == nullptr) ? number_.GetString() : string_;
}

int Utf32Right::GetColumnCount() { return column_count; }

}  // namespace _

_::UTF4& operator<<(_::UTF4& utf, const CH4* string_) {
  return utf.Set(_::Print(utf.begin, utf.stop, string_));
}

_::UTF4& operator<<(_::UTF4& utf, CH4 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI1 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI2 value) {
  return utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI4 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI4 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI8 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI8 value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, FLT value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, DBL value) {
  utf.Set(_::Print(utf.begin, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, _::Utf32Center item) {
  utf.Set(_::PrintCenter(utf.begin, utf.stop, item.GetString(),
                         item.GetColumnCount()));
}

_::UTF4& operator<<(_::UTF4& utf, _::Utf32Right item) {
  utf.Set(_::PrintRight(utf.begin, utf.stop, item.GetString(),
                        item.GetColumnCount()));
}

#endif  //< #if USING_UTF32

#endif  //< #if SEAM >= _0_0_0__02
