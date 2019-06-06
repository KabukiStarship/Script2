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

#include "c_cout.h"
#include "t_utf.h"

#if SEAM == SCRIPT2_SEAM_RNG
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

void Print(CH1 c) { std::wcout << c; }

void Print(const CH1* item) { std::wcout << item; }

void Print(CH2 c) { std::wcout << (CHN)c; }

void Print(const CH2* item) { TPrintString<COut, CH2>(COut().Star(), item); }

void Print(CH4 c) { std::wcout << (CHN)c; }

void Print(const CH4* item) { TPrintString<COut, CH4>(COut().Star(), item); }

/*inline*/ void Print(CH1 first, CH1 second) {
  Print(first);
  Print(second);
}

inline void Print(CH1 first, CH1 second, CH1 third) {
  Print(first);
  Print(second);
  Print(third);
}

void PrintNL() { Print('\n'); }

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
#if SEAM <= SCRIPT2_SEAM_ITOS
  return Printf(FORMAT_UI8, value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintUnsigned<UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void Print(UI4 value) {
#if SEAM <= SCRIPT2_SEAM_ITOS
  return Printf("%u", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintUnsigned<UI4, CH1>(socket, kSize - 1, value);
#endif
}

void Print(SI8 value) {
#if SEAM <= SCRIPT2_SEAM_ITOS
  return Printf(FORMAT_SI8, value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8, UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void Print(SI4 value) {
#if SEAM <= SCRIPT2_SEAM_ITOS
  return Printf("%i", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8, UI8, CH1>(socket, kSize - 1, (SI8)value);
#endif
}

void Print(FP4 value) {
#if SEAM <= SCRIPT2_SEAM_BOOK
  return Printf("%f", value);
#else
  enum { kSize = 16 };
  CH1 socket[kSize];
  TPrintFloat<FP4, UI4, CH1>(socket, kSize, value);
  Print(socket);
#endif
}

void Print(FP8 value) {
#if SEAM <= SCRIPT2_SEAM_BOOK
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
  return TPrintLinef<COut, CH1>(COut().Star(), style, column_count);
}

void PrintLinef(CH1 token, SI4 column_count) {
  TPrintLinef<COut, CH1>(COut().Star(), token, column_count);
}

void PrintHeadingf(const CH1* caption, const CH1* style, SI4 column_count,
                   const CH1* caption2, const CH1* caption3) {
  TPrintHeadingf<COut, CH1>(COut().Star(), caption, style, column_count,
                            caption2, caption3);
}

void PrintBinary(UI1 value) { TPrintBinary<COut, UI1>(COut().Star(), value); }

void PrintBinary(SI1 value) {
  TPrintBinary<COut, UI1>(COut().Star(), (UI1)value);
}

void PrintBinary(UI2 value) { TPrintBinary<COut, UI2>(COut().Star(), value); }

void PrintBinary(SI2 value) {
  TPrintBinary<COut, UI2>(COut().Star(), (UI2)value);
}

void PrintBinary(UI4 value) { TPrintBinary<COut, UI4>(COut().Star(), value); }

void PrintBinary(SI4 value) { TPrintBinary<COut, UI4>(COut().Star(), value); }

void PrintBinary(UI8 value) { TPrintBinary<COut, UI8>(COut().Star(), value); }

void PrintBinary(SI8 value) { TPrintBinary<COut, UI8>(COut().Star(), value); }

void PrintBinary(FP4 value) {
  TPrintBinary<COut, UI4>(COut().Star(), *reinterpret_cast<UI4*>(&value));
}

void PrintBinary(FP8 value) {
  TPrintBinary<COut, UI8>(COut().Star(), *reinterpret_cast<UI8*>(&value));
}

void PrintBinary(const void* ptr) {
  TPrintBinary<COut, UIW>(COut().Star(), *reinterpret_cast<UIW*>(&ptr));
}

void PrintHex(CH1 value) { TPrintHex<COut, UI1>(COut().Star(), value); }

void PrintHex(CH2 value) { TPrintHex<COut, UI2>(COut().Star(), value); }

void PrintHex(CH4 value) { TPrintHex<COut, UI4>(COut().Star(), value); }

void PrintHex(UI1 value) { TPrintHex<COut, UI1>(COut().Star(), value); }

void PrintHex(SI1 value) { TPrintHex<COut, UI1>(COut().Star(), (UI1)value); }

void PrintHex(UI2 value) { TPrintHex<COut, UI2>(COut().Star(), value); }

void PrintHex(SI2 value) { TPrintHex<COut, UI2>(COut().Star(), (UI2)value); }

void PrintHex(UI4 value) { TPrintHex<COut, UI4>(COut().Star(), value); }

void PrintHex(SI4 value) { TPrintHex<COut, UI4>(COut().Star(), (UI4)value); }

void PrintHex(UI8 value) { TPrintHex<COut, UI8>(COut().Star(), value); }

void PrintHex(SI8 value) { TPrintHex<COut, UI8>(COut().Star(), (UI8)value); }

void PrintHex(FP4 value) {
  UI4 f = *reinterpret_cast<UI4*>(&value);
  TPrintHex<COut, UI4>(COut().Star(), f);
}

void PrintHex(FP8 value) {
  UI8 f = *reinterpret_cast<UI8*>(&value);
  TPrintHex<COut, UI8>(COut().Star(), f);
}

void PrintHex(const void* ptr) {
  UIW value = reinterpret_cast<UIW>(ptr);
  TPrintHex<COut, UIW>(COut().Star(), value);
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
  TPrintHex<COut>(COut().Star(), begin, size_bytes);
}

void PrintChars(const void* begin, const void* end) {
  TPrintChars<COut, CH1>(COut().Star(), reinterpret_cast<const CH1*>(begin),
                         reinterpret_cast<const CH1*>(end));
}

void PrintChars(const void* start, SIW count) {
  const CH1* ptr = reinterpret_cast<const CH1*>(start);
  PrintChars(ptr, ptr + count);
}

#if USING_UTF16 == YES

void PrintChars(const CH2* start, const CH2* stop) {
  TPrintChars<COut, CH2>(COut().Star(), start, stop);
}

void PrintChars(const CH2* start, SI4 count) {
  TPrintChars<COut, CH2>(COut().Star(), start, count);
}

void PrintRight(const CH2* start, SI4 count) {
  TPrintRight<COut, CH2>(COut().Star(), start, count);
}

void PrintCenter(const CH2* item, SI4 count) {
  TPrintCenter<COut, CH2>(COut().Star(), item, count);
}

const CH2* PrintLinefCH2() { return TSTRLinef<CH2>(); }

const CH2* PrintLinef(const CH2* style, SI4 count) {
  return TPrintLinef<COut, CH2>(COut().Star(), style, count);
}

void PrintLinef(CH2 token, SI4 count) {
  TPrintLinef<COut, CH2>(COut().Star(), token, count);
}

void PrintHeadingf(const CH2* caption, const CH2* style, SI4 column_count,
                   const CH2* caption2, const CH2* caption3) {
  TPrintHeadingf<COut, CH2>(COut().Star(), caption, style, column_count,
                            caption2, caption3);
}

#endif

#if USING_UTF32 == YES
void PrintChars(const CH4* start, SIW count) {
  TPrintChars<COut, CH4>(COut().Star(), start, start + count);
}

void PrintChars(const CH4* start, const CH4* stop) {
  TPrintChars<COut, CH4>(COut().Star(), start, stop);
}

void PrintChars(const CH4* start, SI4 count) {
  TPrintChars<COut, CH4>(COut().Star(), start, count);
}

void PrintRight(const CH4* start, SI4 count) {
  TPrintRight<COut, CH4>(COut().Star(), start, count);
}

void PrintCenter(const CH4* item, SI4 count) {
  TPrintCenter<COut, CH4>(COut().Star(), item, count);
}

const CH4* PrintLinefCH4() { return TSTRLinef<CH4>(); }

const CH4* PrintLinef(const CH4* style, SI4 count) {
  return TPrintLinef<COut, CH4>(COut().Star(), style, count);
}

void PrintLinef(CH4 token, SI4 count) {
  TPrintLinef<COut, CH4>(COut().Star(), token, count);
}

void PrintHeadingf(const CH4* caption, const CH4* style, SI4 column_count,
                   const CH4* caption2, const CH4* caption3) {
  TPrintHeadingf<COut, CH4>(COut().Star(), caption, style, column_count,
                            caption2, caption3);
}

void PrintRight(const CH1* item, SI4 count) {
  ::_::TPrintRight<COut, CH1>(COut().Star(), item, count);
}

void PrintCenter(const CH1* item, SI4 count) {
  ::_::TPrintCenter<COut, CH1>(COut().Star(), item, count);
}
#endif

COut::COut() {}

COut::COut(CH1 item) { ::_::Print(item); }
COut::COut(const CH1* item) { ::_::Print(item); }

COut::COut(const CH2* item) { ::_::Print(item); }

COut::COut(CH4 item) { ::_::Print(item); }
COut::COut(const CH4* item) { ::_::Print(item); }

COut::COut(SI1 item) { ::_::Print(item); }

COut::COut(UI1 item) { ::_::Print(item); }

COut::COut(SI2 item) { ::_::Print(item); }

COut::COut(UI2 item) { ::_::Print(item); }

COut::COut(SI4 item) { ::_::Print(item); }

COut::COut(UI4 item) { ::_::Print(item); }

COut::COut(SI8 item) { ::_::Print(item); }

COut::COut(UI8 item) { ::_::Print(item); }

#if SEAM >= SCRIPT2_SEAM_FTOS

COut::COut(FP4 item) { ::_::Print(item); }

COut::COut(FP8 item) { ::_::Print(item); }
#endif

COut& COut::Star() { return *this; }

COut& COut::Print(CH1 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(const CH1* item) {
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

#if USING_FP4 == YES
COut& COut::Print(FP4 item) {
  ::_::Print(item);
  return *this;
}
#endif
#if USING_FP8 == YES
COut& COut::Print(FP8 item) {
  ::_::Print(item);
  return *this;
}
#endif

COut& COut::PrintHex(const void* begin, SIW size_bytes) {
  TPrintHex<COut>(COut().Star(), begin, size_bytes);
  return *this;
}

COut& COut::Print(Hex item) { return PrintHex(item.Begin(), item.Size()); }

COut& COut::PrintBinary(const void* begin, SIW size_bytes) {
  TPrintBinary<COut>(COut().Star(), begin, size_bytes);
  return *this;
}

COut& COut::Print(Binary item) {
  return PrintBinary(item.Begin(), item.Size());
}

#if SEAM >= SCRIPT2_SEAM_UTF
COut& COut::Print(Right1 item) {
  ::_::PrintRight(item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Center1 item) {
  ::_::PrintCenter(item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Linef1 item) {
  TPrintLinef<COut, CH1>(*this, item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Headingf1 item) {
  PrintHeadingf(item.caption.String(), item.style, item.caption.Count(),
                item.caption2, item.caption3);
  return *this;
}

COut& COut::Print(Chars1 item) {
  return TPrintChars<COut, CH1>(*this, item.start, item.stop);
}

#endif

#if USING_UTF16 == YES
COut& COut::Print(CH2 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(const CH2* item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(Right2 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Center2 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Linef2 item) {
  TPrintLinef<COut, CH2>(*this, item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Headingf2 item) {
  return TPrintHeadingf<COut, CH2>(*this, item.caption.String(), item.style,
                                   item.caption.Count(), item.caption2,
                                   item.caption3);
}

COut& COut::Print(Chars2 item) {
  return TPrintChars<COut, CH2>(*this, item.start, item.stop);
}
#endif
#if USING_UTF32 == YES

COut& COut::Print(CH4 item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(const CH4* item) {
  ::_::Print(item);
  return *this;
}

COut& COut::Print(Right4 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Center4 item) {
  Print(item.token.String());
  return *this;
}

COut& COut::Print(Linef4 item) {
  TPrintLinef<COut, CH4>(*this, item.token.String(), item.token.Count());
  return *this;
}

COut& COut::Print(Headingf4 item) {
  return TPrintHeadingf<COut, CH4>(*this, item.caption.String(), item.style,
                                   item.caption.Count(), item.caption2,
                                   item.caption3);
}

COut& COut::Print(Chars4 item) {
  return TPrintChars<COut, CH4>(*this, item.start, item.stop);
}

#endif

}  // namespace _

::_::COut& operator<<(::_::COut& o, ::_::COut& p) { return o; }

::_::COut& operator<<(::_::COut& o, CH1 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, const CH1* item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, SI4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, UI4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, SI8 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, UI8 item) { return o.Print(item); }

#if USING_FP4 == YES
::_::COut& operator<<(::_::COut& o, FP4 item) { return o.Print(item); }
#endif

#if USING_FP8 == YES
::_::COut& operator<<(::_::COut& o, FP8 item) { return o.Print(item); }
#endif

::_::COut& operator<<(::_::COut& o, ::_::Hex item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Binary item) { return o.Print(item); }

#if SEAM >= SCRIPT2_SEAM_UTF
::_::COut& operator<<(::_::COut& o, ::_::Center1 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Right1 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Linef1 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Headingf1 item) {
  return o.Print(item);
}

::_::COut& operator<<(::_::COut& o, ::_::Chars1 item) { return o.Print(item); }
#endif

#if USING_UTF16 == YES
::_::COut& operator<<(::_::COut& o, CH2 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, const CH2* item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Center2 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Right2 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Linef2 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Headingf2 item) {
  return o.Print(item);
}

::_::COut& operator<<(::_::COut& o, ::_::Chars2 item) { return o.Print(item); }
#endif

#if USING_UTF32 == YES
::_::COut& operator<<(::_::COut& o, CH4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, const CH4* item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Center4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Right4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Linef4 item) { return o.Print(item); }

::_::COut& operator<<(::_::COut& o, ::_::Headingf4 item) {
  return o.Print(item);
}

::_::COut& operator<<(::_::COut& o, ::_::Chars4 item) { return o.Print(item); }
#endif
