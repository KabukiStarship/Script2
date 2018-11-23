/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \script2_utf.cc
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

#include "tutf.h"

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

UIW* Console(UIW* socket, SIW function, void* arg) {
  return TCOut<char>(socket, function, arg);
}

UIW* COutAuto(UIW* socket, SIW function, void* arg) {
  return TCOutAuto<char>(socket, function, arg);
}

void UTFAlignCenterSTR1(int column_count, void* item, void* destination) {
  ASSERT(item);
  ASSERT(destination);
  ASSERT(column_count >= 0);
}

}  // namespace _

#endif  // #if USING_UTF

#if USING_UTF8
#include "cutf1.h"
namespace _ {

const char* TStringEmpty() { return TStringEmpty<char>(); }

const char* StringNL() { return TStringNL<char>(); }

const char* StringError() { return TStringError<char>(); }

BOL IsWhitespace(char character) { return TIsWhitespace<char>(character); }

char PrintableChar(char value) { return TPrintableChar<char>(value); }

const char* StringEnd(const char* text) { return TStringEnd<char>(text); }

int StringLength(const char* text) { return TStringLength<char, int>(text); }

const char* StringLineEnd(const char* text, int column_count) {
  return TStringLineEnd<char>(text, column_count);
}

const char* StringLineEnd(const char* text, const char* text_end,
                          int column_count) {
  return TStringLineEnd<char>(text, text_end, column_count);
}

const char* StringDecimalStop(const char* text, const char* text_end) {
  return TStringDecimalEnd<char>(text);
}

const char* StringDecimalStop(const char* text) {
  return TStringDecimalEnd<char>(text);
}

const char* TStringSkipChar(const char* text, char skip_char) {
  return TStringSkipChar<char>(text, skip_char);
}

const char* StringSkipSpaces(const char* text) {
  return TStringSkipSpaces<char>(text);
}

const char* StringSkipSpaces(const char* text, const char* text_end) {
  return TStringSkipSpaces<char>(text, text_end);
}

const char* StringEquals(const char* text_a, const char* text_b) {
  return TStringEquals<char>(text_a, text_b);
}

const char* StringEquals(const char* text, const char* text_end,
                         const char* query) {
  return TStringEquals<char>(text, text_end, query);
}

BOL TextQualifies(const char* text) { return TStringIsntEmpty<char>(text); }

BOL TextQualifies(const char* text, const char* text_end) {
  return TStringIsntEmpty<char>(text, text_end);
}

int StringCompare(const char* text_a, const char* text_b) {
  return TStringCompare<char>(text_a, text_b);
}
/*
int TStringCompare(const char* text_a, const char* text_end,
                  const char* text_b) {
  return TStringCompare<char>(text_a, text_end, text_b);
}*/

const char* StringFind(const char* text, const char* query) {
  return TStringFind<char>(text, query);
}

char* Print(char* start, char* stop, const char* string) {
  return TPrint<char>(start, stop, string);
}

char* Print(char* start, char* stop, char character) {
  return TPrintChar<char>(start, stop, character);
}

char* Print(char* start, char* stop, UI8 value) {
  return TPrintUnsigned<UI8, char>(start, stop, value);
}

char* Print(char* start, char* stop, SI8 value) {
  return TPrintSigned<SI8, UI8, char>(start, stop, value);
}

#if ALU_WORD_SIZE != 32
char* Print(char* start, char* stop, UI4 value) {
  return Print(start, stop, (UI8)value);
}

char* Print(char* start, char* stop, SI4 value) {
  return Print(start, stop, (SI8)value);
}
#else
char* Print(char* start, char* stop, UI4 value) {
  return TPrintUnsigned<UI8, char>(start, stop, (UI8)value);
}

char* Print(char* start, char* stop, SI4 value) {
  return TPrintSigned<SI8, UI8, char>(start, stop, (SI8)value);
}
#endif

#if SEAM >= _0_0_0__03

char* PrintCenter(char* start, char* stop, FLT value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* start, char* stop, DBL value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* start, char* stop, FLT value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* start, char* stop, DBL value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

#endif  //< #if SEAM >= _0_0_0__03

char* PrintCenter(char* start, char* stop, const char* string,
                  int column_count) {
  return TPrintCenter<char>(start, stop, string, column_count);
}

char* PrintCenter(char* start, char* stop, char character, int column_count) {
  return TPrintCenter<char>(start, stop, Utf8Text(character).String(),
                            column_count);
}

char* PrintCenter(char* start, char* stop, SI4 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* start, char* stop, UI4 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* start, char* stop, UI8 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* start, char* stop, SI8 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* start, char* stop, const char* string,
                 int column_count) {
  return TPrintRight<char>(start, stop, string, column_count);
}

char* PrintRight(char* start, char* stop, char character, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(character).String(),
                           column_count);
}

char* PrintRight(char* start, char* stop, UI4 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* start, char* stop, SI4 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* start, char* stop, UI8 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* start, char* stop, SI8 value, int column_count) {
  return TPrintRight<char>(start, stop, Utf8Text(value).String(), column_count);
}

char* PrintHex(char* start, char* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<char>(start, stop, ptr);
}

char* PrintHex(char* start, char* stop, UI1 value) {
  return TPrintHex<char, UI1>(start, stop, value);
}

char* PrintHex(char* start, char* stop, SI1 value) {
  return TPrintHex<char, UI1>(start, stop, (UI1)value);
}

char* PrintHex(char* start, char* stop, UI2 value) {
  return TPrintHex<char, UI2>(start, stop, value);
}

char* PrintHex(char* start, char* stop, SI2 value) {
  return TPrintHex<char, UI2>(start, stop, (UI2)value);
}

char* PrintHex(char* start, char* stop, UI4 value) {
  return TPrintHex<char, UI4>(start, stop, value);
}

char* PrintHex(char* start, char* stop, SI4 value) {
  return TPrintHex<char, UI4>(start, stop, (UI4)value);
}

char* PrintHex(char* start, char* stop, UI8 value) {
  return TPrintHex<char, UI8>(start, stop, value);
}

char* PrintHex(char* start, char* stop, SI8 value) {
  return TPrintHex<char, UI8>(start, stop, (UI8)value);
}

char* PrintHex(char* start, char* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<char, UI4>(start, stop, ui);
}

char* PrintHex(char* start, char* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<char, UI8>(start, stop, ui);
}

char* PrintBinary(char* start, char* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<char>(start, stop, ptr);
}

char* PrintBinary(char* start, char* stop, UI1 value) {
  return TPrintBinary<char, UI1>(start, stop, value);
}

char* PrintBinary(char* start, char* stop, SI1 value) {
  return TPrintBinary<char, UI1>(start, stop, (UI1)value);
}

char* PrintBinary(char* start, char* stop, UI2 value) {
  return TPrintBinary<char, UI2>(start, stop, value);
}

char* PrintBinary(char* start, char* stop, SI2 value) {
  return TPrintBinary<char, UI2>(start, stop, (UI2)value);
}

char* PrintBinary(char* start, char* stop, UI4 value) {
  return TPrintBinary<char, UI4>(start, stop, value);
}

char* PrintBinary(char* start, char* stop, SI4 value) {
  return TPrintBinary<char, UI4>(start, stop, value);
}

char* PrintBinary(char* start, char* stop, UI8 value) {
  return TPrintBinary<char, UI8>(start, stop, value);
}

char* PrintBinary(char* start, char* stop, SI8 value) {
  return TPrintBinary<char, UI8>(start, stop, value);
}

char* PrintBinary(char* start, char* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<char, UI4>(start, stop, ui);
}

char* PrintBinary(char* start, char* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<char, UI8>(start, stop, ui);
}

char* PrintSocket(char* start, char* stop, const void* begin, size_t size) {
  return TPrintSocket<char>(start, stop, begin,
                            reinterpret_cast<const char*>(begin) + size);
}

char* PrintSocket(char* start, char* stop, const void* begin, const void* end) {
  return TPrintSocket<char>(start, stop, begin, end);
}

char* PrintLine(char* cursor, char* stop, char token, int column_count) {
  return TPrintLine<char>(cursor, stop, token, column_count);
}

char* TPrintLineString(char* cursor, char* stop, const char* string,
                       int column_count) {
  return TPrintLineString<char>(cursor, stop, string, column_count);
}

const char* Scan(const char* string, SI1& result) {
  return TScanSigned<SI1, UI1, char>(string, result);
}

const char* Scan(const char* string, UI1& result) {
  return TScanUnsigned<UI1, char>(string, result);
}

const char* Scan(const char* string, SI2& result) {
  return TScanSigned<SI2, UI2, char>(string, result);
}

const char* Scan(const char* string, UI2& result) {
  return TScanUnsigned<UI2, char>(string, result);
}

const char* Scan(const char* string, SI4& result) {
  return TScanSigned<SI4, UI4, char>(string, result);
}

const char* Scan(const char* string, UI4& result) {
  return TScanUnsigned<UI4, char>(string, result);
}

const char* Scan(const char* string, SI8& result) {
  return TScanSigned<SI8, UI8, char>(string, result);
}

const char* Scan(const char* string, UI8& result) {
  return TScanUnsigned<UI8, char>(string, result);
}

UTF1::UTF1(char* start, size_t buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF1::UTF1(char* start, char* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF1::UTF1(const UTF1& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF1& UTF1::Set(char* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF1& UTF1::Hex(UI1 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(SI1 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(UI2 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(SI2 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(UI4 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(SI4 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(UI8 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(SI8 value) { return Set(TPrintHex<char>(start, stop, value)); }

UTF1& UTF1::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<char>(start, stop, ui));
}

UTF1& UTF1::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<char>(start, stop, ui));
}

UTF1& UTF1::Hex(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintHex<char>(start, stop, ptr));
}

UTF1& UTF1::Binary(UI1 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(SI1 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(UI2 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(SI2 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(UI4 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(SI4 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(UI8 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(SI8 value) {
  return Set(TPrintBinary<char>(start, stop, value));
}

UTF1& UTF1::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<char>(start, stop, ui));
}

UTF1& UTF1::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<char>(start, stop, ui));
}

UTF1& UTF1::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<char>(start, stop, ptr));
}

Utf8Text::Utf8Text() {}

Utf8Text::Utf8Text(char character) {
  *string = character;
  *(string + 1) = 0;
}

Utf8Text::Utf8Text(SI4 value) {
  TPrintSigned<SI4, UI4, char>(string, string + kSize - 1, value);
}

Utf8Text::Utf8Text(UI4 value) {
  TPrintUnsigned<UI4, char>(string, string + kSize - 1, value);
}

Utf8Text::Utf8Text(SI8 value) {
  TPrintSigned<SI8, UI8, char>(string, string + kSize - 1, value);
}

Utf8Text::Utf8Text(UI8 value) {
  TPrintUnsigned<UI8, char>(string, string + kSize - 1, value);
}

#if SEAM >= _0_0_0__03
Utf8Text::Utf8Text(FLT value) { Print(string, string + kSize - 1, value); }

Utf8Text::Utf8Text(DBL value) { Print(string, string + kSize - 1, value); }

#endif  //< #if SEAM == _0_0_0__03

const char* Utf8Text::String() { return string; }

Utf8Center::Utf8Center(const char* string, int column_count)
    : string(string), column_count(column_count) {}

Utf8Center::Utf8Center(SI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Center::Utf8Center(UI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Center::Utf8Center(SI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Center::Utf8Center(UI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

#if SEAM == _0_0_0__03
Utf8Center::Utf8Center(FLT value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Center::Utf8Center(DBL value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}
#endif

const char* Utf8Center::String() {
  return (string == nullptr) ? number.String() : string;
}

int Utf8Center::GetColumnCount() { return column_count; }

Utf8Right::Utf8Right(const char* string, int column_count)
    : string(string), column_count(column_count) {}

Utf8Right::Utf8Right(SI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Right::Utf8Right(UI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Right::Utf8Right(SI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Right::Utf8Right(UI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

#if SEAM >= _0_0_0__03
Utf8Right::Utf8Right(FLT value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf8Right::Utf8Right(DBL value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}
#endif

const char* Utf8Right::String() {
  return (string == nullptr) ? number.String() : string;
}

int Utf8Right::GetColumnCount() { return column_count; }

Utf8Line::Utf8Line(char token, int column_count)
    : token(token), column_count(column_count) {
  // Nothing to do here. (:-)-+=<
}

Utf8LineString::Utf8LineString(const char* string, int column_count)
    : string(string), column_count(column_count) {
  // Nothing to do here. (:-)-+=<
}

UIW* COutUtf8(UIW* start, SIW function, void* arg) {
  return TCOut<char>(start, function, arg);
}

UIW* COutAutoUtf8(UIW* start, SIW function, void* arg) {
  return TCOutAuto<char>(start, function, arg);
}

}  // namespace _

_::UTF1& operator<<(_::UTF1& utf, const char* string) {
  return utf.Set(_::Print(utf.start, utf.stop, string));
}

_::UTF1& operator<<(_::UTF1& utf, char value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI1 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI2 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI2 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI4 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI4 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI8 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI8 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

#if SEAM == _0_0_0__03
_::UTF1& operator<<(_::UTF1& utf, FLT value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF1& operator<<(_::UTF1& utf, DBL value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}
#endif

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Center item) {
  return utf.Set(_::PrintCenter(utf.start, utf.stop, item.String(),
                                item.GetColumnCount()));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Right item) {
  return utf.Set(
      _::PrintRight(utf.start, utf.stop, item.String(), item.GetColumnCount()));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Line line) {
  return utf.Set(
      _::PrintLine(utf.start, utf.stop, line.token, line.column_count));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8LineString line) {
  return utf.Set(
      _::TPrintLineString(utf.start, utf.stop, line.string, line.column_count));
}

#endif  //< #if USING_UTF8

#if USING_UTF16
#include "str2.h"
namespace _ {

const char16_t* Empty() { return Empty<char16_t>(); }

const char16_t* NewLine() { return NewLine<char16_t>(); }

const char16_t* ErrorHeader() { return ErrorHeader<char16_t>(); }

BOL IsWhitespace(char16_t character) {
  return TIsWhitespace<char16_t>(character);
}

char16_t PrintableChar(char16_t value) {
  return PrintableChar<char16_t>(value);
}

const char16_t* TStringEnd(const char16_t* text) {
  return TStringEnd<char16_t>(text);
}

int TStringLength(const char16_t* text) {
  return TStringLength<char16_t, int>(text);
}

char16_t* StringClone(const char16_t* text) {
  return StringClone<char16_t>(text);
}

const char16_t* StringLineEnd(const char16_t* text, int column_count) {
  return StringLineEnd<char16_t>(text, column_count);
}

const char16_t* StringLineEnd(const char16_t* text, const char16_t* text_end,
                              int column_count) {
  return StringLineEnd<char16_t>(text, text_end, column_count);
}

const char16_t* TStringDecimalEnd(const char16_t* text,
                                  const char16_t* text_end) {
  return TStringDecimalEnd<const char16_t>(text, text_end);
}

const char16_t* TStringDecimalEnd(const char16_t* text) {
  return TStringDecimalEnd<const char16_t>(text);
}

const char16_t* TStringSkipChar(const char16_t* text, char16_t skip_char) {
  return TStringSkipChar<char16_t>(text, skip_char);
}

const char16_t* StringSkipSpaces(const char16_t* text) {
  return StringSkipSpaces<char16_t>(text);
}

const char16_t* StringSkipSpaces(const char16_t* text,
                                 const char16_t* text_end) {
  return StringSkipSpaces<char16_t>(text, text_end);
}

const char16_t* StringEquals(const char16_t* text_a, const char16_t* text_b) {
  return StringEquals<char16_t>(text_a, text_b);
}

const char16_t* StringEquals(const char16_t* text, const char16_t* text_end,
                             const char16_t* query) {
  return StringEquals<char16_t>(text, text_end, query);
}

BOL TextQualifies(const char16_t* text) {
  return TextQualifies<char16_t>(text);
}

BOL TextQualifies(const char16_t* text, const char16_t* text_end) {
  return TextQualifies<char16_t>(text, text_end);
}

int TStringCompare(const char16_t* text_a, const char16_t* text_b) {
  return TStringCompare<char16_t>(text_a, text_b);
}

int TStringCompare(const char16_t* text_a, const char16_t* text_end,
                   const char16_t* text_b) {
  return TStringCompare<char16_t>(text_a, text_end, text_b);
}

const char16_t* StringFind(const char16_t* text, const char16_t* query) {
  return StringFind<char16_t>(text, query);
}

char16_t* Print(char16_t* start, char16_t* stop, const char16_t* string) {
  return TPrint<char16_t>(start, stop, string);
}

char16_t* Print(char16_t* start, char16_t* stop, char16_t character) {
  return TPrintChar<char16_t>(start, stop, character);
}

char16_t* Print(char16_t* start, char16_t* stop, UI4 value) {
  return TPrint<char16_t>(start, stop, value);
}

char16_t* Print(char16_t* start, char16_t* stop, SI4 value) {
  return TPrint<char16_t>(start, stop, value);
}

char16_t* Print(char16_t* start, char16_t* stop, UI8 value) {
  return TPrint<char16_t>(start, stop, value);
}

char16_t* Print(char16_t* start, char16_t* stop, SI8 value) {
  return TPrint<char16_t>(start, stop, value);
}

char16_t* Print(char16_t* start, char16_t* stop, FLT value) {
  return TPrint<char16_t>(start, stop, value);
}

char16_t* Print(char16_t* start, char16_t* stop, DBL value) {
  return TPrint<char16_t>(start, stop, value);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, const char16_t* string,
                      int column_count) {
  return PrintCenter<char16_t>(start, stop, string, column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, char16_t character,
                      int column_count) {
  return PrintCenter<char16_t>(start, stop, Text2(character).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, SI4 value,
                      int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, UI4 value,
                      int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, UI8 value,
                      int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, SI8 value,
                      int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, FLT value,
                      int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* start, char16_t* stop, DBL value,
                      int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, const char16_t* string,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, string, column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, char16_t character,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(character).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, UI4 value,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, SI4 value,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, UI8 value,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, SI8 value,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, FLT value,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintRight(char16_t* start, char16_t* stop, DBL value,
                     int column_count) {
  return TPrintRight<char16_t>(start, stop, Text2(value).GetString(),
                               column_count);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<char16_t>(start, stop, ptr);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, UI1 value) {
  return TPrintHex<char16_t, UI1>(start, stop, value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, SI1 value) {
  return TPrintHex<char16_t, UI1>(start, stop, (UI1)value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, UI2 value) {
  return TPrintHex<char16_t, UI2>(start, stop, value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, SI2 value) {
  return TPrintHex<char16_t, UI2>(start, stop, (UI2)value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, UI4 value) {
  return TPrintHex<char16_t, UI4>(start, stop, value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, SI4 value) {
  return TPrintHex<char16_t, UI4>(start, stop, (UI4)value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, UI8 value) {
  return TPrintHex<char16_t, UI8>(start, stop, value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, SI8 value) {
  return TPrintHex<char16_t, UI8>(start, stop, (UI8)value);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, FLT value) {
  UI4 float_as_ui32 = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<char16_t, UI4>(start, stop, float_as_ui32);
}

char16_t* PrintHex(char16_t* start, char16_t* stop, DBL value) {
  UI8 double_as_ui64 = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<char16_t, UI8>(start, stop, double_as_ui64);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<char16_t>(start, stop, ptr);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI1 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI1 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI2 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI2 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI4 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI4 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, UI8 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, SI8 value) {
  return TPrintBinary<char16_t>(start, stop, value);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Print(start, stop, ui);
}

char16_t* TPrintBinary(char16_t* start, char16_t* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Print(start, stop, ui);
}

char16_t* PrintSocket(char16_t* start, char16_t* stop, const void* start,
                      size_t size) {
  return PrintSocket<char16_t>(start, stop, start,
                               reinterpret_cast<const char16_t*>(start) + size);
}

char16_t* PrintSocket(char16_t* start, char16_t* stop, const void* start,
                      const void* stop) {
  return PrintSocket<char16_t>(start, stop, start, stop);
}
}  // namespace _
}  //< namespace _

const char16_t* Scan(const char16_t* string, SI1& result) {
  return TScanSigned<char16_t, SI1>(string, result);
}

const char16_t* Scan(const char16_t* string, UI1& result) {
  return ScanUnsigned<char16_t, UI1>(string, result);
}

const char16_t* Scan(const char16_t* string, SI2& result) {
  return TScanSigned<char16_t, SI2>(string, result);
}

const char16_t* Scan(const char16_t* string, UI2& result) {
  return ScanUnsigned<char16_t, UI2>(string, result);
}

const char16_t* Scan(const char16_t* string, SI4& result) {
  return TScanSigned<char16_t, SI4>(string, result);
}

const char16_t* Scan(const char16_t* string, UI4& result) {
  return ScanUnsigned<char16_t, UI4>(string, result);
}

const char16_t* Scan(const char16_t* string, SI8& result) {
  return TScanSigned<char16_t, SI8>(string, result);
}

const char16_t* Scan(const char16_t* string, UI8& result) {
  return ScanUnsigned<char16_t, UI8>(string, result);
}

const char16_t* Scan(const char16_t* string, FLT& result) {
  return TScan<char16_t>(string, result);
}

const char16_t* Scan(const char16_t* string, DBL& result) {
  return TScan<char16_t>(string, result);
}

void COutUtf16(UIW* start) { return Console<char16_t>(start); }

void DCOutUtf16(UIW* start) { return DCOut<char16_t>(start); }

UTF2::UTF2(char16_t* start, size_t buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF2::UTF2(char16_t* start, char16_t* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF2::UTF2(const UTF2& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF2& UTF2::Set(char16_t* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF2& UTF2::Hex(UI1 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(SI1 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(UI2 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(SI2 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(UI4 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(SI4 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(UI8 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(SI8 value) {
  return Set(TPrintHex<char16_t>(start, stop, value));
}

UTF2& UTF2::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<char16_t>(start, stop, ui));
}

UTF2& UTF2::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<char16_t>(start, stop, ui));
}

UTF2& UTF2::Hex(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintHex<char16_t>(start, stop, ptr));
}

UTF2& UTF2::Binary(UI1 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(SI1 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(UI2 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(SI2 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(UI4 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(SI4 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(UI8 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(SI8 value) {
  return Set(TPrintBinary<char16_t>(start, stop, value));
}

UTF2& UTF2::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<char16_t>(start, stop, ui));
}

UTF2& UTF2::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<char16_t>(start, stop, ui));
}

UTF2& UTF2::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<char16_t>(start, stop, ptr));
}

Text2::Text2() {}

Text2::Text2(char16_t character) {
  *string = character;
  *(string + 1) = 0;
}

Text2::Text2(SI4 value) { TPrint<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(UI4 value) { TPrint<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(SI8 value) { TPrint<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(UI8 value) { TPrint<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(FLT value) { TPrint<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(DBL value) { TPrint<char16_t>(string, string + kSize - 1, value); }

const char16_t* Text2::GetString() { return string; }

Utf16Center::Utf16Center(const char16_t* string, int column_count)
    : string(string), column_count(column_count) {}

Utf16Center::Utf16Center(SI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Center::Utf16Center(UI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Center::Utf16Center(SI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Center::Utf16Center(UI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Center::Utf16Center(FLT value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Center::Utf16Center(DBL value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

const char16_t* Utf16Center::GetString() {
  return (string == nullptr) ? number.GetString() : string;
}

int Utf16Center::GetColumnCount() { return column_count; }

Utf16Right::Utf16Right(const char16_t* string, int column_count)
    : string(string), column_count(column_count) {}

Utf16Right::Utf16Right(SI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Right::Utf16Right(UI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Right::Utf16Right(SI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Right::Utf16Right(UI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Right::Utf16Right(FLT value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf16Right::Utf16Right(DBL value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

const char16_t* Utf16Right::GetString() {
  return (string == nullptr) ? number.GetString() : string;
}

int Utf16Right::GetColumnCount() { return column_count; }

}  //< namespace _

_::UTF2& operator<<(_::UTF2& utf, const char16_t* string) {
  return utf.Set(_::Print(utf.start, utf.stop, string));
}

_::UTF2& operator<<(_::UTF2& utf, char16_t value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI1 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI2 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI2 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI4 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI4 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI8 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI8 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, FLT value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, DBL value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF2& operator<<(_::UTF2& utf, _::Utf16Center item) {
  utf.Set(_::PrintCenter(utf.start, utf.stop, item.GetString(),
                         item.GetColumnCount()));
}

_::UTF2& operator<<(_::UTF2& utf, _::Utf16Right item) {
  utf.Set(_::PrintRight(utf.start, utf.stop, item.GetString(),
                        item.GetColumnCount()));
}

#endif  //< #if USING_UTF16

#if USING_UTF32
#include "str4.h"
namespace _ {

const char32_t* Empty() { return Empty<char32_t>(); }

const char32_t* NewLine() { return NewLine<char32_t>(); }

const char32_t* ErrorHeader() { return ErrorHeader<char32_t>(); }

BOL IsWhitespace(char32_t character) {
  return TIsWhitespace<char32_t>(character);
}

char32_t PrintableChar(char32_t value) {
  return PrintableChar<char32_t>(value);
}

const char32_t* TStringEnd(const char32_t* text) {
  return TStringEnd<char32_t>(text);
}

int TStringLength(const char32_t* text) {
  return TStringLength<char32_t, int>(text);
}

char32_t* StringClone(const char32_t* text) {
  return StringClone<char32_t>(text);
}

const char32_t* StringLineEnd(const char32_t* text, int column_count) {
  return StringLineEnd<char32_t>(text, column_count);
}

const char32_t* StringLineEnd(const char32_t* text, const char32_t* text_end,
                              int column_count) {
  return StringLineEnd<char32_t>(text, text_end, column_count);
}

const char32_t* TStringDecimalEnd(const char32_t* text,
                                  const char32_t* text_end) {
  return TStringDecimalEnd<const char32_t>(text, text_end);
}

const char32_t* TStringDecimalEnd(const char32_t* text) {
  return TStringDecimalEnd<const char32_t>(text);
}

const char32_t* TStringSkipChar(const char32_t* text, char32_t skip_char) {
  return TStringSkipChar<char32_t>(text, skip_char);
}

const char32_t* StringSkipSpaces(const char32_t* text) {
  return StringSkipSpaces<char32_t>(text);
}

const char32_t* StringSkipSpaces(const char32_t* text,
                                 const char32_t* text_end) {
  return StringSkipSpaces<char32_t>(text, text_end);
}

const char32_t* StringEquals(const char32_t* text_a, const char32_t* text_b) {
  return StringEquals<char32_t>(text_a, text_b);
}

const char32_t* StringEquals(const char32_t* cursor, const char32_t* stop,
                             const char32_t* text_b) {
  return StringEquals<char32_t>(cursor, stop, text_b);
}

BOL TextQualifies(const char32_t* text) {
  return TextQualifies<char32_t>(text);
}

BOL TextQualifies(const char32_t* text, const char32_t* text_end) {
  return TextQualifies<char32_t>(text, text_end);
}

int TStringCompare(const char32_t* text_a, const char32_t* text_b) {
  return TStringCompare<char32_t>(text_a, text_b);
}

int TStringCompare(const char32_t* text_a, const char32_t* text_end,
                   const char32_t* text_b) {
  return TStringCompare<char32_t>(text_a, text_end, text_b);
}

const char32_t* StringFind(const char32_t* text, const char32_t* query) {
  return StringFind<char32_t>(text, query);
}

char32_t* Print(char32_t* start, char32_t* stop, const char32_t* string) {
  return TPrint<char32_t>(start, stop, string);
}

char32_t* Print(char32_t* start, char32_t* stop, char32_t character) {
  return TPrintChar<char32_t>(start, stop, character);
}

char32_t* Print(char32_t* start, char32_t* stop, UI4 value) {
  return TPrint<char32_t>(start, stop, value);
}

char32_t* Print(char32_t* start, char32_t* stop, SI4 value) {
  return TPrint<char32_t>(start, stop, value);
}

char32_t* Print(char32_t* start, char32_t* stop, UI8 value) {
  return TPrint<char32_t>(start, stop, value);
}

char32_t* Print(char32_t* start, char32_t* stop, SI8 value) {
  return TPrint<char32_t>(start, stop, value);
}

char32_t* Print(char32_t* start, char32_t* stop, FLT value) {
  return TPrint<char32_t>(start, stop, value);
}

char32_t* Print(char32_t* start, char32_t* stop, DBL value) {
  return TPrint<char32_t>(start, stop, value);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, const char32_t* string,
                      int column_count) {
  return PrintCenter<char32_t>(start, stop, string, column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, char32_t character,
                      int column_count) {
  return PrintCenter<char32_t>(start, stop, Text4(character).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, SI4 value,
                      int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, UI4 value,
                      int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, UI8 value,
                      int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, SI8 value,
                      int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, FLT value,
                      int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* start, char32_t* stop, DBL value,
                      int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, const char32_t* string,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, string, column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, char32_t character,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(character).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, UI4 value,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, SI4 value,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, UI8 value,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, SI8 value,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, FLT value,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintRight(char32_t* start, char32_t* stop, DBL value,
                     int column_count) {
  return TPrintRight<char32_t>(start, stop, Text4(value).GetString(),
                               column_count);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintHex<char32_t, UIW>(start, stop, ptr);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, UI1 value) {
  return TPrintHex<char32_t, UI1>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, SI1 value) {
  return TPrintHex<char32_t, UI1>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, UI2 value) {
  return TPrintHex<char32_t, UI2>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, SI2 value) {
  return TPrintHex<char32_t, UI2>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, UI4 value) {
  return TPrintHex<char32_t, UI4>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, SI4 value) {
  return TPrintHex<char32_t, UI4>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, UI8 value) {
  return TPrintHex<char32_t, UI8>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, SI8 value) {
  return TPrintHex<char32_t, UI8>(start, stop, value);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintHex<char32_t, UI8>(start, stop, ui);
}

char32_t* PrintHex(char32_t* start, char32_t* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintHex<char32_t, UI8>(start, stop, ui);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return TPrintBinary<char32_t>(start, stop, ptr);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, UI1 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, SI1 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, UI2 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, SI2 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, UI4 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, SI4 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, UI8 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, SI8 value) {
  return TPrintBinary<char32_t>(start, stop, value);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return TPrintBinary<char32_t, UI8>(start, stop, ui);
}

char32_t* TPrintBinary(char32_t* start, char32_t* stop, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return TPrintBinary<char32_t, UI8>(start, stop, ui);
}

char32_t* PrintSocket(char32_t* start, char32_t* stop, const void* start,
                      size_t size) {
  return PrintSocket<char32_t>(start, stop, start,
                               reinterpret_cast<const char32_t*>(start) + size);
}

char32_t* PrintSocket(char32_t* start, char32_t* stop, const void* start,
                      const void* stop) {
  return PrintSocket<char32_t>(start, stop, start, stop);
}

const char32_t* Scan(const char32_t* string, SI1& result) {
  return TScanSigned<char32_t, SI1>(string, result);
}

const char32_t* Scan(const char32_t* string, UI1& result) {
  return ScanUnsigned<char32_t, UI1>(string, result);
}

const char32_t* Scan(const char32_t* string, SI2& result) {
  return TScanSigned<char32_t, SI2>(string, result);
}

const char32_t* Scan(const char32_t* string, UI2& result) {
  return ScanUnsigned<char32_t, UI2>(string, result);
}

const char32_t* Scan(const char32_t* string, SI4& result) {
  return TScanSigned<char32_t, SI4>(string, result);
}

const char32_t* Scan(const char32_t* string, UI4& result) {
  return ScanUnsigned<char32_t, UI4>(string, result);
}

const char32_t* Scan(const char32_t* string, SI8& result) {
  return TScanSigned<char32_t, SI8>(string, result);
}

const char32_t* Scan(const char32_t* string, UI8& result) {
  return ScanUnsigned<char32_t, UI8>(string, result);
}

const char32_t* Scan(const char32_t* string, FLT& result) {
  return TScan<char32_t>(string, result);
}

const char32_t* Scan(const char32_t* string, DBL& result) {
  return TScan<char32_t>(string, result);
}

void COuUtf32(UIW* start) { return Console<char32_t>(start); }

void COuUtf32(UIW* start) { return DCOut<char32_t>(start); }

UTF4::UTF4(char32_t* start, size_t buffer_size)
    : start(start), stop(start + buffer_size - 1) {
  ASSERT(start);
  ASSERT(buffer_size);
}

UTF4::UTF4(char32_t* start, char32_t* stop) : start(start), stop(stop) {
  ASSERT(start);
  ASSERT(start < stop);
}

UTF4::UTF4(const UTF4& other) : start(other.start), stop(other.stop) {
  ASSERT(start);
  ASSERT(stop);
}

UTF4& UTF4::Set(char32_t* new_cursor) {
  start = new_cursor;
  return *this;
}

UTF4& UTF4::Hex(UI1 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(SI1 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(UI2 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(SI2 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(UI4 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(SI4 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(UI8 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(SI8 value) {
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(TPrintHex<char32_t>(start, stop, value));
}

UTF4& UTF4::Hex(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintHex<char32_t>(start, stop, ptr));
}

UTF4& UTF4::Binary(UI1 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(SI1 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(UI2 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(SI2 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(UI4 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(SI4 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(UI8 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(SI8 value) {
  return Set(TPrintBinary<char32_t>(start, stop, value));
}

UTF4& UTF4::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<char32_t>(start, stop, ui));
}

UTF4& UTF4::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(TPrintBinary<char32_t>(start, stop, ui));
}

UTF4& UTF4::Binary(const void* pointer) {
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return Set(TPrintBinary<char32_t>(start, stop, ptr));
}

Text4::Text4() {}

Text4::Text4(char32_t character) {
  *string = character;
  *(string + 1) = 0;
}

Text4::Text4(SI4 value) { TPrint<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(UI4 value) { TPrint<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(SI8 value) { TPrint<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(UI8 value) { TPrint<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(FLT value) { TPrint<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(DBL value) { TPrint<char32_t>(string, string + kSize - 1, value); }

const char32_t* Text4::GetString() { return string; }

Utf32Center::Utf32Center(const char32_t* string, int column_count)
    : string(string), column_count(column_count) {}

Utf32Center::Utf32Center(SI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Center::Utf32Center(UI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Center::Utf32Center(SI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Center::Utf32Center(UI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Center::Utf32Center(FLT value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Center::Utf32Center(DBL value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

const char32_t* Utf32Center::GetString() {
  return (string == nullptr) ? number.GetString() : string;
}

int Utf32Center::GetColumnCount() { return column_count; }

Utf32Right::Utf32Right(const char32_t* string, int column_count)
    : string(string), column_count(column_count) {}

Utf32Right::Utf32Right(SI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Right::Utf32Right(UI4 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Right::Utf32Right(SI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Right::Utf32Right(UI8 value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Right::Utf32Right(FLT value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

Utf32Right::Utf32Right(DBL value, int column_count)
    : string(nullptr), number(value), column_count(column_count) {}

const char32_t* Utf32Right::GetString() {
  return (string == nullptr) ? number.GetString() : string;
}

int Utf32Right::GetColumnCount() { return column_count; }

}  // namespace _

_::UTF4& operator<<(_::UTF4& utf, const char32_t* string) {
  return utf.Set(_::Print(utf.start, utf.stop, string));
}

_::UTF4& operator<<(_::UTF4& utf, char32_t value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI1 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI2 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI2 value) {
  return utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI4 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI4 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI8 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI8 value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, FLT value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, DBL value) {
  utf.Set(_::Print(utf.start, utf.stop, value));
}

_::UTF4& operator<<(_::UTF4& utf, _::Utf32Center item) {
  utf.Set(_::PrintCenter(utf.start, utf.stop, item.GetString(),
                         item.GetColumnCount()));
}

_::UTF4& operator<<(_::UTF4& utf, _::Utf32Right item) {
  utf.Set(_::PrintRight(utf.start, utf.stop, item.GetString(),
                        item.GetColumnCount()));
}

#endif  //< #if USING_UTF32

#endif  //< #if SEAM >= _0_0_0__02
