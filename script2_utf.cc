/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
@file    \kabuki\f2\f2_str.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
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
#include "cascii.h"
#include "csocket.h"
#include "tbinary.h"
#include "tutf.h"
#if SEAM == _0_0_0__02
#include "test_release.inl"
#else
#include "test_release.inl"
#endif
#if USING_UTF

namespace _ {

void Console(uintptr_t* buffer) { Console<char>(buffer); }

void COutAuto(uintptr_t* buffer) { COutAuto<char>(buffer); }

}  // namespace _

#endif  // #if USING_UTF

#if USING_UTF8
#include "cutf1.h"
namespace _ {

const char* StringEmpty() { return StringEmpty<char>(); }

const char* StringNL() { return StringNL<char>(); }

const char* StringError() { return StringError<char>(); }

BOL IsWhitespace(char character) { return IsWhitespace<char>(character); }

char PrintableChar(char value) { return PrintableChar<char>(value); }

const char* StringEnd(const char* text) { return StringEnd<char>(text); }

int StringLength(const char* text) { return StringLength<char, int>(text); }

const char* TextLineEnd(const char* text, int column_count) {
  return TextLineEnd<char>(text, column_count);
}

const char* TextLineEnd(const char* text, const char* text_end,
                        int column_count) {
  return TextLineEnd<char>(text, text_end, column_count);
}

const char* StringDecimalStop(const char* text, const char* text_end) {
  return StringDecimalStop<char>(text);
}

const char* StringDecimalStop(const char* text) {
  return StringDecimalStop<char>(text);
}

const char* TextSkipChar(const char* text, char skip_char) {
  return TextSkipChar<char>(text, skip_char);
}

const char* StringSkipSpaces(const char* text) {
  return StringSkipSpaces<char>(text);
}

const char* StringSkipSpaces(const char* text, const char* text_end) {
  return StringSkipSpaces<char>(text, text_end);
}

const char* StringEquals(const char* text_a, const char* text_b) {
  return StringEquals<char>(text_a, text_b);
}

const char* StringEquals(const char* text, const char* text_end,
                         const char* query) {
  return StringEquals<char>(text, text_end, query);
}

BOL TextQualifies(const char* text) { return TextQualifies<char>(text); }

BOL TextQualifies(const char* text, const char* text_end) {
  return TextQualifies<char>(text, text_end);
}

int StringCompare(const char* text_a, const char* text_b) {
  return StringCompare<char>(text_a, text_b);
}
/*
int StringCompare(const char* text_a, const char* text_end,
                  const char* text_b) {
  return StringCompare<char>(text_a, text_end, text_b);
}*/

const char* StringFind(const char* text, const char* query) {
  return StringFind<char>(text, query);
}

char* Print(char* begin, char* end, const char* string) {
  return Print<char>(begin, end, string);
}

char* Print(char* begin, char* end, char character) {
  return PrintChar<char>(begin, end, character);
}

char* Print(char* begin, char* end, UI8 value) {
  return PrintUnsigned<UI8, char>(begin, end, value);
}

char* Print(char* begin, char* end, SI8 value) {
  return PrintSigned<SI8, UI8, char>(begin, end, value);
}

#if ALU_WORD_SIZE != 32
char* Print(char* begin, char* end, UI4 value) {
  return Print(begin, end, (UI8)value);
}

char* Print(char* begin, char* end, SI4 value) {
  return Print(begin, end, (SI8)value);
}
#else
char* Print(char* begin, char* end, UI4 value) {
  return PrintUnsigned<UI8, char>(begin, end, (UI8)value);
}

char* Print(char* begin, char* end, SI4 value) {
  return PrintSigned<SI8, UI8, char>(begin, end, (SI8)value);
}
#endif

#if SEAM >= _0_0_0__03

char* PrintCenter(char* begin, char* end, FLT value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* begin, char* end, DBL value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* begin, char* end, FLT value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* begin, char* end, DBL value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

#endif  //< #if SEAM >= _0_0_0__03

char* PrintCenter(char* begin, char* end, const char* string,
                  int column_count) {
  return PrintCenter<char>(begin, end, string, column_count);
}

char* PrintCenter(char* begin, char* end, char character, int column_count) {
  return PrintCenter<char>(begin, end, Utf8Text(character).String(),
                           column_count);
}

char* PrintCenter(char* begin, char* end, SI4 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* begin, char* end, UI4 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* begin, char* end, UI8 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintCenter(char* begin, char* end, SI8 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* begin, char* end, const char* string, int column_count) {
  return PrintRight<char>(begin, end, string, column_count);
}

char* PrintRight(char* begin, char* end, char character, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(character).String(),
                          column_count);
}

char* PrintRight(char* begin, char* end, UI4 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* begin, char* end, SI4 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* begin, char* end, UI8 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintRight(char* begin, char* end, SI8 value, int column_count) {
  return PrintRight<char>(begin, end, Utf8Text(value).String(), column_count);
}

char* PrintHex(char* begin, char* end, const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return PrintHex<char>(begin, end, ptr);
}

char* PrintHex(char* begin, char* end, UI1 value) {
  return PrintHex<char, UI1>(begin, end, value);
}

char* PrintHex(char* begin, char* end, SI1 value) {
  return PrintHex<char, UI1>(begin, end, (UI1)value);
}

char* PrintHex(char* begin, char* end, UI2 value) {
  return PrintHex<char, UI2>(begin, end, value);
}

char* PrintHex(char* begin, char* end, SI2 value) {
  return PrintHex<char, UI2>(begin, end, (UI2)value);
}

char* PrintHex(char* begin, char* end, UI4 value) {
  return PrintHex<char, UI4>(begin, end, value);
}

char* PrintHex(char* begin, char* end, SI4 value) {
  return PrintHex<char, UI4>(begin, end, (UI4)value);
}

char* PrintHex(char* begin, char* end, UI8 value) {
  return PrintHex<char, UI8>(begin, end, value);
}

char* PrintHex(char* begin, char* end, SI8 value) {
  return PrintHex<char, UI8>(begin, end, (UI8)value);
}

char* PrintHex(char* begin, char* end, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return PrintHex<char, UI4>(begin, end, ui);
}

char* PrintHex(char* begin, char* end, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return PrintHex<char, UI8>(begin, end, ui);
}

char* PrintBinary(char* begin, char* end, const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return PrintBinary<char>(begin, end, ptr);
}

char* PrintBinary(char* begin, char* end, UI1 value) {
  return PrintBinary<char, UI1>(begin, end, value);
}

char* PrintBinary(char* begin, char* end, SI1 value) {
  return PrintBinary<char, UI1>(begin, end, (UI1)value);
}

char* PrintBinary(char* begin, char* end, UI2 value) {
  return PrintBinary<char, UI2>(begin, end, value);
}

char* PrintBinary(char* begin, char* end, SI2 value) {
  return PrintBinary<char, UI2>(begin, end, (UI2)value);
}

char* PrintBinary(char* begin, char* end, UI4 value) {
  return PrintBinary<char, UI4>(begin, end, value);
}

char* PrintBinary(char* begin, char* end, SI4 value) {
  return PrintBinary<char, UI4>(begin, end, value);
}

char* PrintBinary(char* begin, char* end, UI8 value) {
  return PrintBinary<char, UI8>(begin, end, value);
}

char* PrintBinary(char* begin, char* end, SI8 value) {
  return PrintBinary<char, UI8>(begin, end, value);
}

char* PrintBinary(char* begin, char* end, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return PrintBinary<char, UI4>(begin, end, ui);
}

char* PrintBinary(char* begin, char* end, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return PrintBinary<char, UI8>(begin, end, ui);
}

char* PrintSocket(char* begin, char* end, const void* start, size_t size) {
  return TPrintSocket<char>(begin, end, start,
                            reinterpret_cast<const char*>(start) + size);
}

char* PrintSocket(char* begin, char* end, const void* start, const void* stop) {
  return TPrintSocket<char>(begin, end, start, stop);
}

char* PrintLine(char* cursor, char* end, char token, int column_count) {
  return PrintLine<char>(cursor, end, token, column_count);
}

char* PrintLineString(char* cursor, char* end, const char* string,
                      int column_count) {
  return PrintLineString<char>(cursor, end, string, column_count);
}

const char* Scan(const char* string, SI1& result) {
  return ScanSigned<SI1, UI1, char>(string, result);
}

const char* Scan(const char* string, UI1& result) {
  return ScanUnsigned<UI1, char>(string, result);
}

const char* Scan(const char* string, SI2& result) {
  return ScanSigned<SI2, UI2, char>(string, result);
}

const char* Scan(const char* string, UI2& result) {
  return ScanUnsigned<UI2, char>(string, result);
}

const char* Scan(const char* string, SI4& result) {
  return ScanSigned<SI4, UI4, char>(string, result);
}

const char* Scan(const char* string, UI4& result) {
  return ScanUnsigned<UI4, char>(string, result);
}

const char* Scan(const char* string, SI8& result) {
  return ScanSigned<SI8, UI8, char>(string, result);
}

const char* Scan(const char* string, UI8& result) {
  return ScanUnsigned<UI8, char>(string, result);
}

UTF1::UTF1(char* begin, size_t buffer_size)
    : begin(begin), end(begin + buffer_size - 1) {
  ASSERT(begin);
  ASSERT(buffer_size);
}

UTF1::UTF1(char* begin, char* end) : begin(begin), end(end) {
  ASSERT(begin);
  ASSERT(begin < end);
}

UTF1::UTF1(const UTF1& other) : begin(other.begin), end(other.end) {
  ASSERT(begin);
  ASSERT(end);
}

UTF1& UTF1::Set(char* new_cursor) {
  begin = new_cursor;
  return *this;
}

UTF1& UTF1::Hex(UI1 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(SI1 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(UI2 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(SI2 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(UI4 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(SI4 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(UI8 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(SI8 value) { return Set(PrintHex<char>(begin, end, value)); }

UTF1& UTF1::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintHex<char>(begin, end, ui));
}

UTF1& UTF1::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(PrintHex<char>(begin, end, ui));
}

UTF1& UTF1::Hex(const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return Set(PrintHex<char>(begin, end, ptr));
}

UTF1& UTF1::Binary(UI1 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(SI1 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(UI2 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(SI2 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(UI4 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(SI4 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(UI8 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(SI8 value) {
  return Set(PrintBinary<char>(begin, end, value));
}

UTF1& UTF1::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintBinary<char>(begin, end, ui));
}

UTF1& UTF1::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintBinary<char>(begin, end, ui));
}

UTF1& UTF1::Binary(const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return Set(PrintBinary<char>(begin, end, ptr));
}

Utf8Text::Utf8Text() {}

Utf8Text::Utf8Text(char character) {
  *string = character;
  *(string + 1) = 0;
}

Utf8Text::Utf8Text(SI4 value) {
  PrintSigned<SI4, UI4, char>(string, string + kSize - 1, value);
}

Utf8Text::Utf8Text(UI4 value) {
  PrintUnsigned<UI4, char>(string, string + kSize - 1, value);
}

Utf8Text::Utf8Text(SI8 value) {
  PrintSigned<SI8, UI8, char>(string, string + kSize - 1, value);
}

Utf8Text::Utf8Text(UI8 value) {
  PrintUnsigned<UI8, char>(string, string + kSize - 1, value);
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

void COutUtf8(uintptr_t* buffer) { return Console<char>(buffer); }

void COutAutoUtf8(uintptr_t* buffer) { return COutAuto<char>(buffer); }

}  // namespace _

_::UTF1& operator<<(_::UTF1& utf, const char* string) {
  return utf.Set(_::Print(utf.begin, utf.end, string));
}

_::UTF1& operator<<(_::UTF1& utf, char value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI1 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI2 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI2 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI4 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI4 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, SI8 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, UI8 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

#if SEAM == _0_0_0__03
_::UTF1& operator<<(_::UTF1& utf, FLT value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF1& operator<<(_::UTF1& utf, DBL value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}
#endif

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Center item) {
  return utf.Set(
      _::PrintCenter(utf.begin, utf.end, item.String(), item.GetColumnCount()));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Right item) {
  return utf.Set(
      _::PrintRight(utf.begin, utf.end, item.String(), item.GetColumnCount()));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8Line line) {
  return utf.Set(
      _::PrintLine(utf.begin, utf.end, line.token, line.column_count));
}

_::UTF1& operator<<(_::UTF1& utf, _::Utf8LineString line) {
  return utf.Set(
      _::PrintLineString(utf.begin, utf.end, line.string, line.column_count));
}

#endif  //< #if USING_UTF8

#if USING_UTF16
#include "str2.h"
namespace _ {

const char16_t* Empty() { return Empty<char16_t>(); }

const char16_t* NewLine() { return NewLine<char16_t>(); }

const char16_t* ErrorHeader() { return ErrorHeader<char16_t>(); }

BOL IsWhitespace(char16_t character) {
  return IsWhitespace<char16_t>(character);
}

char16_t PrintableChar(char16_t value) {
  return PrintableChar<char16_t>(value);
}

const char16_t* StringEnd(const char16_t* text) {
  return StringEnd<char16_t>(text);
}

int StringLength(const char16_t* text) {
  return StringLength<char16_t, int>(text);
}

char16_t* StringClone(const char16_t* text) {
  return StringClone<char16_t>(text);
}

const char16_t* TextLineEnd(const char16_t* text, int column_count) {
  return TextLineEnd<char16_t>(text, column_count);
}

const char16_t* TextLineEnd(const char16_t* text, const char16_t* text_end,
                            int column_count) {
  return TextLineEnd<char16_t>(text, text_end, column_count);
}

const char16_t* StringDecimalStop(const char16_t* text,
                                  const char16_t* text_end) {
  return StringDecimalStop<const char16_t>(text, text_end);
}

const char16_t* StringDecimalStop(const char16_t* text) {
  return StringDecimalStop<const char16_t>(text);
}

const char16_t* TextSkipChar(const char16_t* text, char16_t skip_char) {
  return TextSkipChar<char16_t>(text, skip_char);
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

int StringCompare(const char16_t* text_a, const char16_t* text_b) {
  return StringCompare<char16_t>(text_a, text_b);
}

int StringCompare(const char16_t* text_a, const char16_t* text_end,
                  const char16_t* text_b) {
  return StringCompare<char16_t>(text_a, text_end, text_b);
}

const char16_t* StringFind(const char16_t* text, const char16_t* query) {
  return StringFind<char16_t>(text, query);
}

char16_t* Print(char16_t* begin, char16_t* end, const char16_t* string) {
  return Print<char16_t>(begin, end, string);
}

char16_t* Print(char16_t* begin, char16_t* end, char16_t character) {
  return PrintChar<char16_t>(begin, end, character);
}

char16_t* Print(char16_t* begin, char16_t* end, UI4 value) {
  return Print<char16_t>(begin, end, value);
}

char16_t* Print(char16_t* begin, char16_t* end, SI4 value) {
  return Print<char16_t>(begin, end, value);
}

char16_t* Print(char16_t* begin, char16_t* end, UI8 value) {
  return Print<char16_t>(begin, end, value);
}

char16_t* Print(char16_t* begin, char16_t* end, SI8 value) {
  return Print<char16_t>(begin, end, value);
}

char16_t* Print(char16_t* begin, char16_t* end, FLT value) {
  return Print<char16_t>(begin, end, value);
}

char16_t* Print(char16_t* begin, char16_t* end, DBL value) {
  return Print<char16_t>(begin, end, value);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, const char16_t* string,
                      int column_count) {
  return PrintCenter<char16_t>(begin, end, string, column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, char16_t character,
                      int column_count) {
  return PrintCenter<char16_t>(begin, end, Text2(character).GetString(),
                               column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, SI4 value,
                      int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, UI4 value,
                      int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, UI8 value,
                      int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, SI8 value,
                      int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, FLT value,
                      int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintCenter(char16_t* begin, char16_t* end, DBL value,
                      int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, const char16_t* string,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, string, column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, char16_t character,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(character).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, UI4 value,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, SI4 value,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, UI8 value,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, SI8 value,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, FLT value,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintRight(char16_t* begin, char16_t* end, DBL value,
                     int column_count) {
  return PrintRight<char16_t>(begin, end, Text2(value).GetString(),
                              column_count);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return PrintHex<char16_t>(begin, end, ptr);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, UI1 value) {
  return PrintHex<char16_t, UI1>(begin, end, value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, SI1 value) {
  return PrintHex<char16_t, UI1>(begin, end, (UI1)value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, UI2 value) {
  return PrintHex<char16_t, UI2>(begin, end, value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, SI2 value) {
  return PrintHex<char16_t, UI2>(begin, end, (UI2)value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, UI4 value) {
  return PrintHex<char16_t, UI4>(begin, end, value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, SI4 value) {
  return PrintHex<char16_t, UI4>(begin, end, (UI4)value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, UI8 value) {
  return PrintHex<char16_t, UI8>(begin, end, value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, SI8 value) {
  return PrintHex<char16_t, UI8>(begin, end, (UI8)value);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, FLT value) {
  UI4 float_as_ui32 = *reinterpret_cast<UI4*>(&value);
  return PrintHex<char16_t, UI4>(begin, end, float_as_ui32);
}

char16_t* PrintHex(char16_t* begin, char16_t* end, DBL value) {
  UI8 double_as_ui64 = *reinterpret_cast<UI8*>(&value);
  return PrintHex<char16_t, UI8>(begin, end, double_as_ui64);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return PrintBinary<char16_t>(begin, end, ptr);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, UI1 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, SI1 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, UI2 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, SI2 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, UI4 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, SI4 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, UI8 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, SI8 value) {
  return PrintBinary<char16_t>(begin, end, value);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Print(begin, end, ui);
}

char16_t* PrintBinary(char16_t* begin, char16_t* end, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Print(begin, end, ui);
}

char16_t* PrintSocket(char16_t* begin, char16_t* end, const void* start,
                      size_t size) {
  return PrintSocket<char16_t>(begin, end, start,
                               reinterpret_cast<const char16_t*>(start) + size);
}

char16_t* PrintSocket(char16_t* begin, char16_t* end, const void* start,
                      const void* stop) {
  return PrintSocket<char16_t>(begin, end, start, stop);
}
}  // namespace _
}  //< namespace _

const char16_t* Scan(const char16_t* string, SI1& result) {
  return ScanSigned<char16_t, SI1>(string, result);
}

const char16_t* Scan(const char16_t* string, UI1& result) {
  return ScanUnsigned<char16_t, UI1>(string, result);
}

const char16_t* Scan(const char16_t* string, SI2& result) {
  return ScanSigned<char16_t, SI2>(string, result);
}

const char16_t* Scan(const char16_t* string, UI2& result) {
  return ScanUnsigned<char16_t, UI2>(string, result);
}

const char16_t* Scan(const char16_t* string, SI4& result) {
  return ScanSigned<char16_t, SI4>(string, result);
}

const char16_t* Scan(const char16_t* string, UI4& result) {
  return ScanUnsigned<char16_t, UI4>(string, result);
}

const char16_t* Scan(const char16_t* string, SI8& result) {
  return ScanSigned<char16_t, SI8>(string, result);
}

const char16_t* Scan(const char16_t* string, UI8& result) {
  return ScanUnsigned<char16_t, UI8>(string, result);
}

const char16_t* Scan(const char16_t* string, FLT& result) {
  return Scan<char16_t>(string, result);
}

const char16_t* Scan(const char16_t* string, DBL& result) {
  return Scan<char16_t>(string, result);
}

void COutUtf16(uintptr_t* buffer) { return Console<char16_t>(buffer); }

void DCOutUtf16(uintptr_t* buffer) { return DCOut<char16_t>(buffer); }

UTF2::UTF2(char16_t* begin, size_t buffer_size)
    : begin(begin), end(begin + buffer_size - 1) {
  ASSERT(begin);
  ASSERT(buffer_size);
}

UTF2::UTF2(char16_t* begin, char16_t* end) : begin(begin), end(end) {
  ASSERT(begin);
  ASSERT(begin < end);
}

UTF2::UTF2(const UTF2& other) : begin(other.begin), end(other.end) {
  ASSERT(begin);
  ASSERT(end);
}

UTF2& UTF2::Set(char16_t* new_cursor) {
  begin = new_cursor;
  return *this;
}

UTF2& UTF2::Hex(UI1 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(SI1 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(UI2 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(SI2 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(UI4 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(SI4 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(UI8 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(SI8 value) {
  return Set(PrintHex<char16_t>(begin, end, value));
}

UTF2& UTF2::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintHex<char16_t>(begin, end, ui));
}

UTF2& UTF2::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(PrintHex<char16_t>(begin, end, ui));
}

UTF2& UTF2::Hex(const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return Set(PrintHex<char16_t>(begin, end, ptr));
}

UTF2& UTF2::Binary(UI1 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(SI1 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(UI2 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(SI2 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(UI4 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(SI4 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(UI8 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(SI8 value) {
  return Set(PrintBinary<char16_t>(begin, end, value));
}

UTF2& UTF2::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintBinary<char16_t>(begin, end, ui));
}

UTF2& UTF2::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintBinary<char16_t>(begin, end, ui));
}

UTF2& UTF2::Binary(const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return Set(PrintBinary<char16_t>(begin, end, ptr));
}

Text2::Text2() {}

Text2::Text2(char16_t character) {
  *string = character;
  *(string + 1) = 0;
}

Text2::Text2(SI4 value) { Print<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(UI4 value) { Print<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(SI8 value) { Print<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(UI8 value) { Print<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(FLT value) { Print<char16_t>(string, string + kSize - 1, value); }

Text2::Text2(DBL value) { Print<char16_t>(string, string + kSize - 1, value); }

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
  return utf.Set(_::Print(utf.begin, utf.end, string));
}

_::UTF2& operator<<(_::UTF2& utf, char16_t value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI1 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI2 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI2 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI4 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI4 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, SI8 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, UI8 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, FLT value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, DBL value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF2& operator<<(_::UTF2& utf, _::Utf16Center item) {
  utf.Set(_::PrintCenter(utf.begin, utf.end, item.GetString(),
                         item.GetColumnCount()));
}

_::UTF2& operator<<(_::UTF2& utf, _::Utf16Right item) {
  utf.Set(_::PrintRight(utf.begin, utf.end, item.GetString(),
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
  return IsWhitespace<char32_t>(character);
}

char32_t PrintableChar(char32_t value) {
  return PrintableChar<char32_t>(value);
}

const char32_t* StringEnd(const char32_t* text) {
  return StringEnd<char32_t>(text);
}

int StringLength(const char32_t* text) {
  return StringLength<char32_t, int>(text);
}

char32_t* StringClone(const char32_t* text) {
  return StringClone<char32_t>(text);
}

const char32_t* TextLineEnd(const char32_t* text, int column_count) {
  return TextLineEnd<char32_t>(text, column_count);
}

const char32_t* TextLineEnd(const char32_t* text, const char32_t* text_end,
                            int column_count) {
  return TextLineEnd<char32_t>(text, text_end, column_count);
}

const char32_t* StringDecimalStop(const char32_t* text,
                                  const char32_t* text_end) {
  return StringDecimalStop<const char32_t>(text, text_end);
}

const char32_t* StringDecimalStop(const char32_t* text) {
  return StringDecimalStop<const char32_t>(text);
}

const char32_t* TextSkipChar(const char32_t* text, char32_t skip_char) {
  return TextSkipChar<char32_t>(text, skip_char);
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

const char32_t* StringEquals(const char32_t* cursor, const char32_t* end,
                             const char32_t* text_b) {
  return StringEquals<char32_t>(cursor, end, text_b);
}

BOL TextQualifies(const char32_t* text) {
  return TextQualifies<char32_t>(text);
}

BOL TextQualifies(const char32_t* text, const char32_t* text_end) {
  return TextQualifies<char32_t>(text, text_end);
}

int StringCompare(const char32_t* text_a, const char32_t* text_b) {
  return StringCompare<char32_t>(text_a, text_b);
}

int StringCompare(const char32_t* text_a, const char32_t* text_end,
                  const char32_t* text_b) {
  return StringCompare<char32_t>(text_a, text_end, text_b);
}

const char32_t* StringFind(const char32_t* text, const char32_t* query) {
  return StringFind<char32_t>(text, query);
}

char32_t* Print(char32_t* begin, char32_t* end, const char32_t* string) {
  return Print<char32_t>(begin, end, string);
}

char32_t* Print(char32_t* begin, char32_t* end, char32_t character) {
  return PrintChar<char32_t>(begin, end, character);
}

char32_t* Print(char32_t* begin, char32_t* end, UI4 value) {
  return Print<char32_t>(begin, end, value);
}

char32_t* Print(char32_t* begin, char32_t* end, SI4 value) {
  return Print<char32_t>(begin, end, value);
}

char32_t* Print(char32_t* begin, char32_t* end, UI8 value) {
  return Print<char32_t>(begin, end, value);
}

char32_t* Print(char32_t* begin, char32_t* end, SI8 value) {
  return Print<char32_t>(begin, end, value);
}

char32_t* Print(char32_t* begin, char32_t* end, FLT value) {
  return Print<char32_t>(begin, end, value);
}

char32_t* Print(char32_t* begin, char32_t* end, DBL value) {
  return Print<char32_t>(begin, end, value);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, const char32_t* string,
                      int column_count) {
  return PrintCenter<char32_t>(begin, end, string, column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, char32_t character,
                      int column_count) {
  return PrintCenter<char32_t>(begin, end, Text4(character).GetString(),
                               column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, SI4 value,
                      int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, UI4 value,
                      int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, UI8 value,
                      int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, SI8 value,
                      int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, FLT value,
                      int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintCenter(char32_t* begin, char32_t* end, DBL value,
                      int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, const char32_t* string,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, string, column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, char32_t character,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(character).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, UI4 value,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, SI4 value,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, UI8 value,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, SI8 value,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, FLT value,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintRight(char32_t* begin, char32_t* end, DBL value,
                     int column_count) {
  return PrintRight<char32_t>(begin, end, Text4(value).GetString(),
                              column_count);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return PrintHex<char32_t, uintptr_t>(begin, end, ptr);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, UI1 value) {
  return PrintHex<char32_t, UI1>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, SI1 value) {
  return PrintHex<char32_t, UI1>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, UI2 value) {
  return PrintHex<char32_t, UI2>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, SI2 value) {
  return PrintHex<char32_t, UI2>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, UI4 value) {
  return PrintHex<char32_t, UI4>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, SI4 value) {
  return PrintHex<char32_t, UI4>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, UI8 value) {
  return PrintHex<char32_t, UI8>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, SI8 value) {
  return PrintHex<char32_t, UI8>(begin, end, value);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return PrintHex<char32_t, UI8>(begin, end, ui);
}

char32_t* PrintHex(char32_t* begin, char32_t* end, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return PrintHex<char32_t, UI8>(begin, end, ui);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return PrintBinary<char32_t>(begin, end, ptr);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, UI1 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, SI1 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, UI2 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, SI2 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, UI4 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, SI4 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, UI8 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, SI8 value) {
  return PrintBinary<char32_t>(begin, end, value);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return PrintBinary<char32_t, UI8>(begin, end, ui);
}

char32_t* PrintBinary(char32_t* begin, char32_t* end, DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return PrintBinary<char32_t, UI8>(begin, end, ui);
}

char32_t* PrintSocket(char32_t* begin, char32_t* end, const void* start,
                      size_t size) {
  return PrintSocket<char32_t>(begin, end, start,
                               reinterpret_cast<const char32_t*>(start) + size);
}

char32_t* PrintSocket(char32_t* begin, char32_t* end, const void* start,
                      const void* stop) {
  return PrintSocket<char32_t>(begin, end, start, stop);
}

const char32_t* Scan(const char32_t* string, SI1& result) {
  return ScanSigned<char32_t, SI1>(string, result);
}

const char32_t* Scan(const char32_t* string, UI1& result) {
  return ScanUnsigned<char32_t, UI1>(string, result);
}

const char32_t* Scan(const char32_t* string, SI2& result) {
  return ScanSigned<char32_t, SI2>(string, result);
}

const char32_t* Scan(const char32_t* string, UI2& result) {
  return ScanUnsigned<char32_t, UI2>(string, result);
}

const char32_t* Scan(const char32_t* string, SI4& result) {
  return ScanSigned<char32_t, SI4>(string, result);
}

const char32_t* Scan(const char32_t* string, UI4& result) {
  return ScanUnsigned<char32_t, UI4>(string, result);
}

const char32_t* Scan(const char32_t* string, SI8& result) {
  return ScanSigned<char32_t, SI8>(string, result);
}

const char32_t* Scan(const char32_t* string, UI8& result) {
  return ScanUnsigned<char32_t, UI8>(string, result);
}

const char32_t* Scan(const char32_t* string, FLT& result) {
  return Scan<char32_t>(string, result);
}

const char32_t* Scan(const char32_t* string, DBL& result) {
  return Scan<char32_t>(string, result);
}

void COuUtf32(uintptr_t* buffer) { return Console<char32_t>(buffer); }

void COuUtf32(uintptr_t* buffer) { return DCOut<char32_t>(buffer); }

UTF4::UTF4(char32_t* begin, size_t buffer_size)
    : begin(begin), end(begin + buffer_size - 1) {
  ASSERT(begin);
  ASSERT(buffer_size);
}

UTF4::UTF4(char32_t* begin, char32_t* end) : begin(begin), end(end) {
  ASSERT(begin);
  ASSERT(begin < end);
}

UTF4::UTF4(const UTF4& other) : begin(other.begin), end(other.end) {
  ASSERT(begin);
  ASSERT(end);
}

UTF4& UTF4::Set(char32_t* new_cursor) {
  begin = new_cursor;
  return *this;
}

UTF4& UTF4::Hex(UI1 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(SI1 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(UI2 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(SI2 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(UI4 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(SI4 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(UI8 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(SI8 value) {
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(DBL value) {
  UI8 ui = *reinterpret_cast<UI8*>(&value);
  return Set(PrintHex<char32_t>(begin, end, value));
}

UTF4& UTF4::Hex(const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return Set(PrintHex<char32_t>(begin, end, ptr));
}

UTF4& UTF4::Binary(UI1 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(SI1 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(UI2 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(SI2 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(UI4 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(SI4 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(UI8 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(SI8 value) {
  return Set(PrintBinary<char32_t>(begin, end, value));
}

UTF4& UTF4::Binary(FLT value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintBinary<char32_t>(begin, end, ui));
}

UTF4& UTF4::Binary(DBL value) {
  UI4 ui = *reinterpret_cast<UI4*>(&value);
  return Set(PrintBinary<char32_t>(begin, end, ui));
}

UTF4& UTF4::Binary(const void* pointer) {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(pointer);
  return Set(PrintBinary<char32_t>(begin, end, ptr));
}

Text4::Text4() {}

Text4::Text4(char32_t character) {
  *string = character;
  *(string + 1) = 0;
}

Text4::Text4(SI4 value) { Print<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(UI4 value) { Print<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(SI8 value) { Print<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(UI8 value) { Print<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(FLT value) { Print<char32_t>(string, string + kSize - 1, value); }

Text4::Text4(DBL value) { Print<char32_t>(string, string + kSize - 1, value); }

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
  return utf.Set(_::Print(utf.begin, utf.end, string));
}

_::UTF4& operator<<(_::UTF4& utf, char32_t value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI1 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI2 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI2 value) {
  return utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI4 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI4 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, SI8 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, UI8 value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, FLT value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, DBL value) {
  utf.Set(_::Print(utf.begin, utf.end, value));
}

_::UTF4& operator<<(_::UTF4& utf, _::Utf32Center item) {
  utf.Set(_::PrintCenter(utf.begin, utf.end, item.GetString(),
                         item.GetColumnCount()));
}

_::UTF4& operator<<(_::UTF4& utf, _::Utf32Right item) {
  utf.Set(_::PrintRight(utf.begin, utf.end, item.GetString(),
                        item.GetColumnCount()));
}

#endif  //< #if USING_UTF32

#include "test_footer.inl"
#endif  //< #if SEAM >= _0_0_0__02
