/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_cout.cc
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

#include "t_cout.h"

#include "t_strand.h"
#include "t_test.h"

#include <cstdio>
#include <iostream>

#if SEAM == SCRIPT2_0
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1* ArgsToSring(SI4 arg_count, CH1** args) {
  if (!args || arg_count <= 1) {
    PRINT("\n!args || arg_count <= 1");
    return "";
  }
  if (arg_count == 2) {
    PRINT("\narg_count == 2");
    return args[1];
  }
  PRINT_ARGS;
  CH1 *begin = args[1], *stop = args[arg_count - 1] - 1;
  while (stop != begin) {
    CH1 c = *stop;
    if (!c) c = ' ';
    --stop;
  }
  return begin;
}
#undef PRINT_ARGS

void PrintChar(CH1 c) {
  putchar(c);
  /// std::cout << c;
}

void Print(CH1 c) { PrintChar(c); }

void Print(const CH1* item) { std::cout << item; }

void PrintChar(CH4 c) {
  wprintf_s(L"%c", (int)c);
  // std::wcout << (CHN)c; //< @todo This isn't working
}

void Print(const CH4* item) { TPrintString<CH4>(item); }

void Print(CH4 c) { PrintChar(c); }

void Print(const CH2* item) { TPrintString<CH2>(item); }

void PrintChar(CH2 c) {
#if USING_UTF32 == YES
  Print((CH4)c);
#else
  wprintf_s(L"%c", (int)c);
  // std::wcout << (CHN)c; //< @todo This isn't working
#endif
}

void Print(CH2 c) { PrintChar(c); }

inline void Print(CH1 first, CH1 second) {
  Print(first);
  Print(second);
}

inline void Print(CH1 first, CH1 second, CH1 third) {
  Print(first);
  Print(second);
  Print(third);
}

void PrintNL() { PrintChar('\n'); }

void PrintNL(CH1 c) { Print(kLF, c); }

void PrintNL(CH1 first, CH1 second) { return Print(kLF, first, second); }

void Printf(const CH1* format, ...) {
  if (!format) return;
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
}

void PrintfLn(const CH1* format, ...) {
  if (!format) return;
  PrintNL();
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
}

void Print(const CH1* item, CH1 c) {
  Print(item);
  Print(c);
}

void Print(const CH1* a, const CH1* b) {
  if (!a || !b) return;
  Print(a);
  Print(b);
}

void Print(const CH1* a, const CH1* b, const CH1* c) {
  if (!a || !b || !c) return;
  Print(a);
  Print(b);
  Print(c);
}

void Print(UI8 value) {
#if SEAM <= SCRIPT2_1
  return Printf(FORMAT_UI8, value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintUnsigned<UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void Print(UI4 value) {
#if SEAM <= SCRIPT2_1
  return Printf("%u", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintUnsigned<UI4, CH1>(socket, kSize - 1, value);
#endif
}

void Print(SI8 value) {
#if SEAM <= SCRIPT2_1
  return Printf(FORMAT_SI8, value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8, UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void Print(SI4 value) {
#if SEAM <= SCRIPT2_1
  return Printf("%i", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8, UI8, CH1>(socket, kSize - 1, (SI8)value);
#endif
}

void Print(FP4 value) {
#if SEAM <= SCRIPT2_13
  return Printf("%f", value);
#else
  enum { kSize = 16 };
  CH1 socket[kSize];
  TPrintFloat<FP4, UI4, CH1>(socket, kSize, value);
  Print(socket);
#endif
}

void Print(FP8 value) {
#if SEAM <= SCRIPT2_13
  return Printf("%f", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintFloat<FP8, UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void PrintNL(const CH1* item) {
  PrintNL();
  Print(item);
}

void PrintIndent(SI4 count) {
  PrintNL();
  while (--count > 0) Print(' ');
}

const CH1* PrintLinefCH1() { return TSTRLinef<CH1>(); }

const CH1* PrintLinef(const CH1* style, SI4 column_count) {
  return TPrintLinef<CH1>(style, column_count);
}

void PrintLinef(CH1 token, SI4 column_count) {
  TPrintLinef<CH1>(token, column_count);
}

void PrintHeadingf(const CH1* caption, const CH1* style, SI4 column_count,
                   const CH1* caption2, const CH1* caption3) {
  TPrintHeadingf<CH1>(caption, style, column_count, caption2, caption3);
}

void PrintBinary(UI1 value) { return TPrintBinary<UI1>(value); }

void PrintBinary(SI1 value) { return TPrintBinary<UI1>((UI1)value); }

void PrintBinary(UI2 value) { return TPrintBinary<UI2>(value); }

void PrintBinary(SI2 value) { return TPrintBinary<UI2>((UI2)value); }

void PrintBinary(UI4 value) { return TPrintBinary<UI4>(value); }

void PrintBinary(SI4 value) { return TPrintBinary<UI4>(value); }

void PrintBinary(UI8 value) { return TPrintBinary<UI8>(value); }

void PrintBinary(SI8 value) { return TPrintBinary<UI8>(value); }

void PrintBinary(FP4 value) {
  return TPrintBinary<UI4>(*reinterpret_cast<UI4*>(&value));
}

void PrintBinary(FP8 value) {
  return TPrintBinary<UI8>(*reinterpret_cast<UI8*>(&value));
}

void PrintBinary(const void* ptr) {
  return TPrintBinary<UIW>(*reinterpret_cast<UIW*>(&ptr));
}

void PrintHex(CH1 value) { TPrintHexConsole<UI1>(value); }

void PrintHex(CH2 value) { TPrintHexConsole<UI2>(value); }

void PrintHex(CH4 value) { TPrintHexConsole<UI4>(value); }

void PrintHex(UI1 value) { TPrintHexConsole<UI1>(value); }

void PrintHex(SI1 value) { TPrintHexConsole<UI1>((UI1)value); }

void PrintHex(UI2 value) { TPrintHexConsole<UI2>(value); }

void PrintHex(SI2 value) { TPrintHexConsole<UI2>((UI2)value); }

void PrintHex(UI4 value) { TPrintHexConsole<UI4>(value); }

void PrintHex(SI4 value) { TPrintHexConsole<UI4>((UI4)value); }

void PrintHex(UI8 value) { TPrintHexConsole<UI8>(value); }

void PrintHex(SI8 value) { TPrintHexConsole<UI8>((UI8)value); }

void PrintHex(FP4 value) {
  UI4 f = *reinterpret_cast<UI4*>(&value);
  TPrintHexConsole<UI4>(f);
}

void PrintHex(FP8 value) {
  UI8 f = *reinterpret_cast<UI8*>(&value);
  TPrintHexConsole<UI8>(f);
}

void PrintHex(const void* ptr) {
  UIW value = reinterpret_cast<UIW>(ptr);
  TPrintHexConsole<UIW>(value);
}

void PrintHex(const void* begin, const void* end) {
  if (!begin || begin >= end) return;

  const CH1 *address_ptr = reinterpret_cast<const CH1*>(begin),
            *address_end_ptr = reinterpret_cast<const CH1*>(end);
  SIW size = address_end_ptr - address_ptr,
      num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  size += num_bytes;
  Print(STRSocketHexHeader());
  Print(STRSocketHexBorder());
  PrintHex(address_ptr);

  CH1 c;
  while (address_ptr < address_end_ptr) {
    Print(kLF, '|');
    for (SI4 i = 0; i < 32; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (c < ' ')
        c += kPrintC0Offset;
      PrintHex(c);
    }
    Print('|', ' ');
    PrintHex(address_ptr);
  }
  Print(STRSocketHexBorder());
  PrintHex(address_ptr + size);
}

void PrintHex(const void* begin, SIW size) {
  const CH1* begin_char = reinterpret_cast<const CH1*>(begin);
  return PrintHex(begin_char, begin_char + size);
}

}  // namespace _

namespace _ {

void PrintChars(const void* begin, const void* end) {
  TPrintChars<CH1>(reinterpret_cast<const CH1*>(begin),
                   reinterpret_cast<const CH1*>(end));
}

void PrintChars(const void* start, SIW count) {
  const CH1* ptr = reinterpret_cast<const CH1*>(start);
  return PrintChars(ptr, ptr + count);
}

#if USING_UTF16 == YES

void PrintChars(const CH2* start, const CH2* stop) {
  TPrintChars<CH2>(start, stop);
}

void PrintChars(const CH2* start, SI4 count) { TPrintChars<CH2>(start, count); }

void PrintRight(const CH2* start, SI4 count) { TPrintRight<CH2>(start, count); }

void PrintCenter(const CH2* item, SI4 count) { TPrintCenter<CH2>(item, count); }

const CH2* PrintLinefCH2() { return TSTRLinef<CH2>(); }

const CH2* PrintLinef(const CH2* style, SI4 count) {
  return TPrintLinef<CH2>(style, count);
}

void PrintLinef(CH2 token, SI4 count) { TPrintLinef<CH2>(token, count); }

void PrintHeadingf(const CH2* caption, const CH2* style, SI4 column_count,
                   const CH2* caption2, const CH2* caption3) {
  TPrintHeadingf<CH2>(caption, style, column_count, caption2, caption3);
}

#endif

#if USING_UTF32 == YES
void PrintChars(const CH4* start, SIW count) {
  TPrintChars<CH4>(start, start + count);
}

void PrintChars(const CH4* start, const CH4* stop) {
  TPrintChars<CH4>(start, stop);
}

void PrintChars(const CH4* start, SI4 count) { TPrintChars<CH4>(start, count); }

void PrintRight(const CH4* start, SI4 count) { TPrintRight<CH4>(start, count); }

void PrintCenter(const CH4* item, SI4 count) { TPrintCenter<CH4>(item, count); }

const CH4* PrintLinefCH4() { return TSTRLinef<CH4>(); }

const CH4* PrintLinef(const CH4* style, SI4 count) {
  return TPrintLinef<CH4>(style, count);
}

void PrintLinef(CH4 token, SI4 count) { TPrintLinef<CH4>(token, count); }

void PrintHeadingf(const CH4* caption, const CH4* style, SI4 column_count,
                   const CH4* caption2, const CH4* caption3) {
  TPrintHeadingf<CH4>(caption, style, column_count, caption2, caption3);
}
#endif

void PrintRight(const CH1* item, SI4 count) {
  ::_::TPrintRight<CH1>(item, count);
}

void PrintCenter(const CH1* item, SI4 count) {
  ::_::TPrintCenter<CH1>(item, count);
}

COut::COut() {}

COut::COut(const CH1* item) { ::_::Print(item); }

COut::COut(const CH2* item) { ::_::Print(item); }

COut::COut(const CH4* item) { ::_::Print(item); }

COut::COut(SI1 item) { ::_::Print(item); }

COut::COut(UI1 item) { ::_::Print(item); }

COut::COut(SI2 item) { ::_::Print(item); }

COut::COut(UI2 item) { ::_::Print(item); }

COut::COut(SI4 item) { ::_::Print(item); }

COut::COut(UI4 item) { ::_::Print(item); }

COut::COut(SI8 item) { ::_::Print(item); }

COut::COut(UI8 item) { ::_::Print(item); }

#if SEAM >= SCRIPT2_4

COut::COut(FP4 item) { ::_::Print(item); }

COut::COut(FP8 item) { ::_::Print(item); }
#endif

COut& COut::Star() { return *this; }

COut& COut::Print(CH1 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(CH2 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(CH4 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(const CH1* item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(const CH2* item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(const CH4* item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(SI4 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(UI4 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(SI8 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(UI8 item) {
  ::_::Print(item);
  return *this;
}

#if SEAM >= SCRIPT2_4

COut& COut::Print(FP4 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(FP8 item) {
  ::_::Print(item);
  return *this;
}
#endif

#if SEAM >= SCRIPT2_3
#if USING_STR == UTF8

COut& COut::Print(Right1 item) {
  ::_::PrintRight(item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Center1 item) {
  ::_::PrintCenter(item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Linef1 item) {
  PrintLinef(item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Headingf1 item) {
  TPrintHeadingf<CH1>(item.caption.String(), item.style, item.caption.Count(),
                      item.caption2, item.caption3);
  return *this;
}
#endif

#elif USING_STR == UTF16

COut& COut::Print(Right2 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Center2 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Linef2 item) {
  auto string = item.token.String();
  if (string)
    PrintLinef(string, item.token.Count());
  else
    PrintLinef(item.token, item.token.Count());
  return *this;
}

COut& COut::Print(Headingf2 item) {
  auto string = item.token.String();
  if (string)
    PrintRepeat(string);
  else
    PrintRepeat(item.token);
  return *this;
}

#lif USING_STR == UTF32

COut& COut::Print(Right4 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Center4 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Linef4 item) {
  auto string = item.token.String();
  if (string)
    PrintLinef(string);
  else
    PrintLinef(item.token);
  return *this;
}

COut& COut::Print(Headingf4 item) {
  const CH4* string = item.token.String();
  if (string)
    PrintRepeat(string);
  else
    PrintRepeat(item.token);
  return *this;
}

#endif

}  // namespace _

::_::COut& operator<<(::_::COut& cout, const CH1* string) {
  return cout.Print(string);
}

::_::COut& operator<<(::_::COut& cout, const CH2* string) {
  return cout.Print(string);
}

::_::COut& operator<<(::_::COut& cout, const CH4* string) {
  return cout.Print(string);
}

::_::COut& operator<<(::_::COut& cout, CH1 c) { return cout.Print(c); }

::_::COut& operator<<(::_::COut& cout, CH2 c) { return cout.Print(c); }

::_::COut& operator<<(::_::COut& cout, CH4 c) { return cout.Print(c); }

::_::COut& operator<<(::_::COut& cout, UI1 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, SI2 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, UI2 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, SI4 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, UI4 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, SI8 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, UI8 value) { return cout.Print(value); }

#if SEAM >= SCRIPT2_4

::_::COut& operator<<(::_::COut& cout, FP4 value) { return cout.Print(value); }

::_::COut& operator<<(::_::COut& cout, FP8 value) { return cout.Print(value); }
#endif

#if SEAM >= SCRIPT2_3
#if USING_STR == UTF8

::_::COut& operator<<(::_::COut& cout, ::_::Center1 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Right1 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Linef1 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Headingf1 item) {
  return cout.Print(item);
}
#endif

#elif USING_STR == UTF16

::_::COut& operator<<(::_::COut& cout, ::_::Center2 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Right2 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Linef2 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Headingf2 item) {
  return cout.Print(item);
}

#lif USING_STR == UTF32

::_::COut& operator<<(::_::COut& cout, ::_::Center4 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Right4 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Linef4 item) {
  return cout.Print(item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Headingf4 item) {
  return cout.Print(item);
}

#endif

#undef PRINT_ARGS
