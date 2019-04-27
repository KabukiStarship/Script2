/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_cout.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#include <cstdio>
#include <iostream>

#include "c_sout.h"
#include "t_uniprinter.h"

#if SEAM == SCRIPT2_6
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
  // putchar(c); This wasn't working for some reason???
  std::wcout << c;
}

void Print(CH1 c) { PrintChar(c); }

void Print(const CH1* item) { std::cout << item; }

void PrintChar(CH4 c) {
  // wprintf_s(L"%c", (int)c);
  std::wcout << c;  //< @todo This isn't working???
}

void Print(const CH4* item) {
  TPrintString<std::wostream, CH4>(std::wcout, item);
}

void Print(CH4 c) { PrintChar(c); }

void Print(const CH2* item) {
  TPrintString<std::wostream, CH2>(std::wcout, item);
}

void PrintChar(CH2 c) {
#if USING_UTF32 == YES
  Print((CH4)c);
#else
  wprintf_s(L"%c", (int)c);
  // std::wcout << (CHN)c; //< @todo This isn't working
#endif
}

void Print(CH2 c) { PrintChar(c); }

/*inline*/ void Print(CH1 first, CH1 second) {
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
  return TPrintLinef<std::wostream, CH1>(std::wcout, style, column_count);
}

void PrintLinef(CH1 token, SI4 column_count) {
  TPrintLinef<std::wostream, CH1>(std::wcout, token, column_count);
}

void PrintHeadingf(const CH1* caption, const CH1* style, SI4 column_count,
                   const CH1* caption2, const CH1* caption3) {
  TPrintHeadingf<std::wostream, CH1>(std::wcout, caption, style, column_count,
                                     caption2, caption3);
}

void PrintBinary(UI1 value) {
  TPrintBinary<std::wostream, UI1>(std::wcout, value);
}

void PrintBinary(SI1 value) {
  TPrintBinary<std::wostream, UI1>(std::wcout, (UI1)value);
}

void PrintBinary(UI2 value) {
  TPrintBinary<std::wostream, UI2>(std::wcout, value);
}

void PrintBinary(SI2 value) {
  TPrintBinary<std::wostream, UI2>(std::wcout, (UI2)value);
}

void PrintBinary(UI4 value) {
  TPrintBinary<std::wostream, UI4>(std::wcout, value);
}

void PrintBinary(SI4 value) {
  TPrintBinary<std::wostream, UI4>(std::wcout, value);
}

void PrintBinary(UI8 value) {
  TPrintBinary<std::wostream, UI8>(std::wcout, value);
}

void PrintBinary(SI8 value) {
  TPrintBinary<std::wostream, UI8>(std::wcout, value);
}

void PrintBinary(FP4 value) {
  TPrintBinary<std::wostream, UI4>(std::wcout, *reinterpret_cast<UI4*>(&value));
}

void PrintBinary(FP8 value) {
  TPrintBinary<std::wostream, UI8>(std::wcout, *reinterpret_cast<UI8*>(&value));
}

void PrintBinary(const void* ptr) {
  TPrintBinary<std::wostream, UIW>(std::wcout, *reinterpret_cast<UIW*>(&ptr));
}

void PrintHex(CH1 value) { TPrintHex<std::wostream, UI1>(std::wcout, value); }

void PrintHex(CH2 value) { TPrintHex<std::wostream, UI2>(std::wcout, value); }

void PrintHex(CH4 value) { TPrintHex<std::wostream, UI4>(std::wcout, value); }

void PrintHex(UI1 value) { TPrintHex<std::wostream, UI1>(std::wcout, value); }

void PrintHex(SI1 value) {
  TPrintHex<std::wostream, UI1>(std::wcout, (UI1)value);
}

void PrintHex(UI2 value) { TPrintHex<std::wostream, UI2>(std::wcout, value); }

void PrintHex(SI2 value) {
  TPrintHex<std::wostream, UI2>(std::wcout, (UI2)value);
}

void PrintHex(UI4 value) { TPrintHex<std::wostream, UI4>(std::wcout, value); }

void PrintHex(SI4 value) {
  TPrintHex<std::wostream, UI4>(std::wcout, (UI4)value);
}

void PrintHex(UI8 value) { TPrintHex<std::wostream, UI8>(std::wcout, value); }

void PrintHex(SI8 value) {
  TPrintHex<std::wostream, UI8>(std::wcout, (UI8)value);
}

void PrintHex(FP4 value) {
  UI4 f = *reinterpret_cast<UI4*>(&value);
  TPrintHex<std::wostream, UI4>(std::wcout, f);
}

void PrintHex(FP8 value) {
  UI8 f = *reinterpret_cast<UI8*>(&value);
  TPrintHex<std::wostream, UI8>(std::wcout, f);
}

void PrintHex(const void* ptr) {
  UIW value = reinterpret_cast<UIW>(ptr);
  TPrintHex<std::wostream, UIW>(std::wcout, value);
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

void PrintHex(const void* begin, SIW size_bytes) {
  TPrintHex<std::wostream>(std::wcout, begin, size_bytes);
}

}  // namespace _

std::wostream& operator<<(std::wostream& o, ::_::Char c) { return o << c.ch; }

std::wostream& operator<<(std::wostream& o, ::_::Hex hex) {
  return ::_::TPrintHex<std::wostream>(o, hex.begin, hex.size_bytes);
}

namespace _ {

void PrintChars(const void* begin, const void* end) {
  TPrintChars<std::wostream, CH1>(std::wcout,
                                  reinterpret_cast<const CH1*>(begin),
                                  reinterpret_cast<const CH1*>(end));
}

void PrintChars(const void* start, SIW count) {
  const CH1* ptr = reinterpret_cast<const CH1*>(start);
  PrintChars(ptr, ptr + count);
}

#if USING_UTF16 == YES

void PrintChars(const CH2* start, const CH2* stop) {
  TPrintChars<std::wostream, CH2>(std::wcout, start, stop);
}

void PrintChars(const CH2* start, SI4 count) {
  TPrintChars<std::wostream, CH2>(std::wcout, start, count);
}

void PrintRight(const CH2* start, SI4 count) {
  TPrintRight<std::wostream, CH2>(std::wcout, start, count);
}

void PrintCenter(const CH2* item, SI4 count) {
  TPrintCenter<std::wostream, CH2>(std::wcout, item, count);
}

const CH2* PrintLinefCH2() { return TSTRLinef<CH2>(); }

const CH2* PrintLinef(const CH2* style, SI4 count) {
  return TPrintLinef<std::wostream, CH2>(std::wcout, style, count);
}

void PrintLinef(CH2 token, SI4 count) {
  TPrintLinef<std::wostream, CH2>(std::wcout, token, count);
}

void PrintHeadingf(const CH2* caption, const CH2* style, SI4 column_count,
                   const CH2* caption2, const CH2* caption3) {
  TPrintHeadingf<std::wostream, CH2>(std::wcout, caption, style, column_count,
                                     caption2, caption3);
}

#endif

#if USING_UTF32 == YES
void PrintChars(const CH4* start, SIW count) {
  TPrintChars<std::wostream, CH4>(std::wcout, start, start + count);
}

void PrintChars(const CH4* start, const CH4* stop) {
  TPrintChars<std::wostream, CH4>(std::wcout, start, stop);
}

void PrintChars(const CH4* start, SI4 count) {
  TPrintChars<std::wostream, CH4>(std::wcout, start, count);
}

void PrintRight(const CH4* start, SI4 count) {
  TPrintRight<std::wostream, CH4>(std::wcout, start, count);
}

void PrintCenter(const CH4* item, SI4 count) {
  TPrintCenter<std::wostream, CH4>(std::wcout, item, count);
}

const CH4* PrintLinefCH4() { return TSTRLinef<CH4>(); }

const CH4* PrintLinef(const CH4* style, SI4 count) {
  return TPrintLinef<std::wostream, CH4>(std::wcout, style, count);
}

void PrintLinef(CH4 token, SI4 count) {
  TPrintLinef<std::wostream, CH4>(std::wcout, token, count);
}

void PrintHeadingf(const CH4* caption, const CH4* style, SI4 column_count,
                   const CH4* caption2, const CH4* caption3) {
  TPrintHeadingf<std::wostream, CH4>(std::wcout, caption, style, column_count,
                                     caption2, caption3);
}
#endif

void PrintRight(const CH1* item, SI4 count) {
  ::_::TPrintRight<std::wostream, CH1>(std::wcout, item, count);
}

void PrintCenter(const CH1* item, SI4 count) {
  ::_::TPrintCenter<std::wostream, CH1>(std::wcout, item, count);
}

SOut::SOut() {}

SOut::SOut(const CH1* item) { ::_::Print(item); }

SOut::SOut(const CH2* item) { ::_::Print(item); }

SOut::SOut(const CH4* item) { ::_::Print(item); }

SOut::SOut(SI1 item) { ::_::Print(item); }

SOut::SOut(UI1 item) { ::_::Print(item); }

SOut::SOut(SI2 item) { ::_::Print(item); }

SOut::SOut(UI2 item) { ::_::Print(item); }

SOut::SOut(SI4 item) { ::_::Print(item); }

SOut::SOut(UI4 item) { ::_::Print(item); }

SOut::SOut(SI8 item) { ::_::Print(item); }

SOut::SOut(UI8 item) { ::_::Print(item); }

#if SEAM >= SCRIPT2_4

SOut::SOut(FP4 item) { ::_::Print(item); }

SOut::SOut(FP8 item) { ::_::Print(item); }
#endif

SOut& SOut::Star() { return *this; }

SOut& SOut::Print(CH1 item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(CH2 item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(CH4 item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(const CH1* item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(const CH2* item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(const CH4* item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(SI4 item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(UI4 item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(SI8 item) {
  ::_::Print(item);
  return *this;
}

SOut& SOut::Print(UI8 item) {
  ::_::Print(item);
  return *this;
}

#if USING_FP4 == YES
SOut& SOut::Print(FP4 item) {
  ::_::Print(item);
  return *this;
}
#endif
#if USING_FP8 == YES
SOut& SOut::Print(FP8 item) {
  ::_::Print(item);
  return *this;
}
#endif

SOut& SOut::Print(const void* begin, SIW size_bytes) {
  TPrintHex<std::wostream>(std::wcout, begin, size_bytes);
  return *this;
}

SOut& SOut::Print(Hex item) {
  TPrintHex<std::wostream>(std::wcout, item.begin, item.size_bytes);
  return *this;
}

#if SEAM >= SCRIPT2_3
#if USING_STR == UTF8
SOut& SOut::Print(Right1 item) {
  ::_::PrintRight(item.token.String(), item.token.Count());
  return *this;
}

SOut& SOut::Print(Center1 item) {
  ::_::PrintCenter(item.token.String(), item.token.Count());
  return *this;
}

SOut& SOut::Print(Linef1 item) {
  PrintLinef(item.token.String(), item.token.Count());
  return *this;
}

SOut& SOut::Print(Headingf1 item) {
  TPrintHeadingf<std::wostream, CH1>(std::wcout, item.caption.String(),
                                     item.style, item.caption.Count(),
                                     item.caption2, item.caption3);
  return *this;
}

SOut& SOut::Print(Chars1 item) { return *this; }

}  // namespace _
std::wostream& operator<<(std::wostream& o, ::_::Chars1 chars) {
  return ::_::TPrintChars<std::wostream>(o, chars.start, chars.stop);
}

namespace _ {

SOut& SOut::Print(Hexs1 item) { return *this; }
#endif

#elif USING_STR == UTF16

SOut& SOut::Print(Right2 item) {
  Print(item.token.String());
  return *this;
}

SOut& SOut::Print(Center2 item) {
  Print(item.token.String());
  return *this;
}

SOut& SOut::Print(Linef2 item) {
  auto string = item.token.String();
  if (string)
    PrintLinef(string, item.token.Count());
  else
    PrintLinef(item.token, item.token.Count());
  return *this;
}

SOut& SOut::Print(Headingf2 item) {
  auto string = item.token.String();
  if (string)
    PrintRepeat(string);
  else
    PrintRepeat(item.token);
  return *this;
}

#lif USING_STR == UTF32

SOut& SOut::Print(Right4 item) {
  Print(item.token.String());
  return *this;
}

SOut& SOut::Print(Center4 item) {
  Print(item.token.String());
  return *this;
}

SOut& SOut::Print(Linef4 item) {
  auto string = item.token.String();
  if (string)
    PrintLinef(string);
  else
    PrintLinef(item.token);
  return *this;
}

SOut& SOut::Print(Headingf4 item) {
  const CH4* string = item.token.String();
  if (string)
    PrintRepeat(string);
  else
    PrintRepeat(item.token);
  return *this;
}

#endif

}  // namespace _

::_::SOut& operator<<(::_::SOut& o, ::_::SOut& p) { return o; }

::_::SOut& operator<<(::_::SOut& o, const CH1* item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, const CH2* item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, const CH4* item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, CH1 c) { return o.Print(c); }

::_::SOut& operator<<(::_::SOut& o, CH2 c) { return o.Print(c); }

::_::SOut& operator<<(::_::SOut& o, CH4 c) { return o.Print(c); }

::_::SOut& operator<<(::_::SOut& o, UI1 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, SI2 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, UI2 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, SI4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, UI4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, SI8 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, UI8 item) { return o.Print(item); }

#if SEAM >= SCRIPT2_4

::_::SOut& operator<<(::_::SOut& o, FP4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, FP8 item) { return o.Print(item); }
#endif

::_::SOut& operator<<(::_::SOut& o, ::_::Hex item) { return o.Print(item); }

#if SEAM >= SCRIPT2_3

#if USING_STR == UTF8

::_::SOut& operator<<(::_::SOut& o, ::_::Center1 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Right1 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Linef1 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Headingf1 item) {
  return o.Print(item);
}

::_::SOut& operator<<(::_::SOut& o, ::_::Chars1 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Hexs1 item) { return o.Print(item); }
#endif

#elif USING_STR == UTF16

::_::SOut& operator<<(::_::SOut& o, ::_::Center2 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Right2 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Linef2 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Headingf2 item) {
  return o.Print(item);
}

::_::SOut& operator<<(::_::SOut& o, ::_::Chars2 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Hexs2 item) { return o.Print(item); }

#lif USING_STR == UTF32

::_::SOut& operator<<(::_::SOut& o, ::_::Center4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Right4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Linef4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Headingf4 item) {
  return o.Print(item);
}

::_::SOut& operator<<(::_::SOut& o, ::_::Chars4 item) { return o.Print(item); }

::_::SOut& operator<<(::_::SOut& o, ::_::Hexs4 item) { return o.Print(item); }

#endif
