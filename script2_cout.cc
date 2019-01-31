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

#include "c_ascii.h"
#include "t_binary.h"
#include "t_test.h"

#include <conio.h>
#include <cstdio>
#include <iostream>

#if SEAM == SCRIPT2_0
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

const CH1* ArgsToStrand(SI4 arg_count, CH1** args) {
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

inline void Print(CH1 c) {
  putchar(c);
}

inline void PrintChar (CH1 c) {
  return Print (c);
}

inline void Print (CH4 c) {
  wprintf_s (L"%c", c);
  //std::wcout << c;
}

inline void PrintChar (CH4 c) {
  wprintf_s (L"%c", c);
  //std::wcout << c;
}

inline void Print (CH2 c) {
  wprintf_s (L"%c", c);
  //std::wcout << c;
}

inline void PrintChar (CH2 c) {
  wprintf_s (L"%c", c);
  //std::wcout << c;
}

inline void Print(CH1 first, CH1 second) {
  Print(first);
  Print(second);
}

inline void Print(CH1 first, CH1 second, CH1 third) {
  Print(first);
  Print(second);
  Print(third);
}

void PrintLn(CH1 c) { Print('\n', c); }

void PrintLn(CH1 first, CH1 second) { return Print('\n', first, second); }

void Printf(const CH1* format, ...) {
  if (!format) return;
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
}

void PrintfLn(const CH1* format, ...) {
  if (!format) return;
  PrintLn();
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);
}

void Print(const CH1* item) { std::cout << item; }

void Print(const CH2* item) { TPrintStrand<CH2>(item); }

void Print(const CH4* item) { TPrintStrand<CH4>(item); }

void Print(const CH1* item, CH1 delimiter) {
  Print(item);
  Print(delimiter);
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

void Print(FLT value) {
#if SEAM <= SCRIPT2_13
  return Printf("%f", value);
#else
  enum { kSize = 16 };
  CH1 socket[kSize];
  TPrintFloat<FLT, UI4, CH1>(socket, kSize, value);
  Print(socket);
#endif
}

void Print(DBL value) {
#if SEAM <= SCRIPT2_13
  return Printf("%f", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintFloat<DBL, UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void PrintLn(const CH1* item) {
  Print('\n');
  Print(item);
}

void PrintIndent(SI4 count) {
  Print('\n');
  while (--count > 0) Print(' ');
}

void PrintRepeat (CH1 item, SI4 count) {
  TPrintRepeat<CH1> (item, count);
}

void PrintRepeat (const CH1* item, SI4 count, CH1 delimiter) {
  TPrintRepeat<CH1> (item, count, delimiter);
}

void PrintLine(CH1 item, SI4 count, CH1 first_token) {
  TPrintLine<CH1> (item, count, first_token);
}

SDK void PrintLine (const CH1* item, SI4 count, CH1 first_token) {
  TPrintLine<CH1> (item, count, first_token);
}

void PrintHeading(const CH1* heading_a, const CH1* heading_b, SI4 row_count,
                  SI4 column_count, CH1 token, CH1 first_token) {
  TPrintHeading<CH1> (heading_a, heading_b, row_count, column_count, token, 
                      first_token);
}

void PrintHeading(const CH1* heading, SI4 row_count, SI4 column_count, CH1 token,
                  CH1 first_token) {
  if (row_count < 1 || column_count < 1) return;
  while (row_count-- > 0) Print('\n');
  PrintLine(token, column_count, '+');
  Print("\n| ");
  Print(heading);
  PrintLine(token, column_count, '+');
  Print('\n');
}

void PrintBinary(UI1 value) { return TPrintBinary<UI1>(value); }

void PrintBinary(SI1 value) { return TPrintBinary<UI1> ((UI1)value); }

void PrintBinary(UI2 value) { return TPrintBinary<UI2>(value); }

void PrintBinary(SI2 value) { return TPrintBinary<UI2> ((UI2)value); }

void PrintBinary(UI4 value) { return TPrintBinary<UI4>(value); }

void PrintBinary(SI4 value) { return TPrintBinary<UI4> (value); }

void PrintBinary(UI8 value) { return TPrintBinary<UI8>(value); }

void PrintBinary(SI8 value) { return TPrintBinary<UI8> (value); }

void PrintBinary(FLT value) {
  return TPrintBinary<UI4>(*reinterpret_cast<UI4*>(&value));
}

void PrintBinary(DBL value) {
  return TPrintBinary<UI8>(*reinterpret_cast<UI8*>(&value));
}

void PrintBinary(const void* ptr) {
  return TPrintBinary<UIW>(*reinterpret_cast<UIW*>(&ptr));
}

void PrintHex (CH1 value) { TPrintHexConsole<UI1> (value); }

void PrintHex (CH2 value) { TPrintHexConsole<UI2> (value); }

void PrintHex (CH4 value) { TPrintHexConsole<UI4> (value); }

void PrintHex(UI1 value) { TPrintHexConsole<UI1>(value); }

void PrintHex(SI1 value) { TPrintHexConsole<UI1>((UI1)value); }

void PrintHex(UI2 value) { TPrintHexConsole<UI2>(value); }

void PrintHex(SI2 value) { TPrintHexConsole<UI2>((UI2)value); }

void PrintHex(UI4 value) { TPrintHexConsole<UI4>(value); }

void PrintHex(SI4 value) { TPrintHexConsole<UI4>((UI4)value); }

void PrintHex(UI8 value) { TPrintHexConsole<UI8>(value); }

void PrintHex(SI8 value) { TPrintHexConsole<UI8>((UI8)value); }

void PrintHex(FLT value) {
  UI4 f = *reinterpret_cast<UI4*>(&value);
  TPrintHexConsole<UI4>(f);
}

void PrintHex(DBL value) {
  UI8 f = *reinterpret_cast<UI8*>(&value);
  TPrintHexConsole<UI8>(f);
}

void PrintHex(const void* ptr) {
  UIW value = reinterpret_cast<UIW>(ptr);
  TPrintHexConsole<UIW>(value);
}

void PrintHex (const void* begin, const void* end) {
  if (!begin || begin >= end) return;

  const CH1 *address_ptr = reinterpret_cast<const CH1*>(begin),
    *address_end_ptr = reinterpret_cast<const CH1*>(end);
  size_t size = address_end_ptr - address_ptr,
    num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  size += num_bytes;
  Print (StrandSocketHexHeader ());
  Print (StrandSocketHexBorder ());
  PrintHex (address_ptr);

  CH1 c;
  while (address_ptr < address_end_ptr) {
    Print ('\n', '|');
    for (SI4 i = 0; i < 32; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (c < ' ')
        c += kPrintC0Offset;
      PrintHex (c);
    }
    Print ('|', ' ');
    PrintHex (address_ptr);
  }
  Print (StrandSocketHexBorder ());
  PrintHex (address_ptr + size);
}

void PrintHex (const void* begin, SIW size) {
  const CH1* begin_char = reinterpret_cast<const CH1*>(begin);
  return PrintHex (begin_char, begin_char + size);
}

SI4 CInKey() { return _getch(); }

BOL CInState(SI4 vk_code) {
#if COMPILER == VISUAL_CPP

#elif COMPILER == GCC

#elif COMPILER == CLANG

#endif
  return false;
}

void Pause(const CH1* message) {
  if (!message) message = "";
  Printf("\n\n%s\nPress any key to continue...", message);
  while (CInKey() < 0)
    ;
}

void Pausef(const CH1* format, ...) {
  if (!format) return;
  PrintLn();
  va_list arg;
  va_start(arg, format);
  vfprintf(stdout, format, arg);
  va_end(arg);

  Pause("\nPress any key to continue...");
  while (CInKey() < 0)
    ;
}

}  // namespace _

namespace _ {

void PrintChars (const void* begin, const void* end) {
  TPrintChars<CH1> (reinterpret_cast<const CH1*> (begin),
                    reinterpret_cast<const CH1*> (end));
}

void PrintChars (const void* start, SIW count) {
  const CH1* ptr = reinterpret_cast<const CH1*> (start);
  return PrintChars (ptr, ptr + count - 1);
}

#if USING_UTF16 == YES
void PrintChars (const CH2* start, SIW count) {
  TPrintChars<CH2> (start, start + count - 1);
}
#endif
#if USING_UTF32 == YES
void PrintChars (const CH4* start, SIW count) {
  TPrintChars<CH4> (start, start + count - 1);
}
#endif

void PrintRight (const CH1* item, SI4 count) {
  ::_::TPrintRight<CH1> (item, count);
}

void PrintCenter (const CH1* item, SI4 count) {
  ::_::TPrintCenter<CH1> (item, count);
}

COut::COut (const CH1* item) {
  ::_::Print (item);
}

COut::COut (const CH2* item) {
  ::_::Print (item);
}

COut::COut (const CH4* item) {
  ::_::Print (item);
}

COut::COut (SI1 item) {
  ::_::Print (item);
}

COut::COut (UI1 item) {
  ::_::Print (item);
}

COut::COut (SI2 item) {
  ::_::Print (item);
}

COut::COut (UI2 item) {
  ::_::Print (item);
}

COut::COut (SI4 item) {
  ::_::Print (item);
}

COut::COut (UI4 item) {
  ::_::Print (item);
}

COut::COut (SI8 item) {
  ::_::Print (item);
}

COut::COut (UI8 item) {
  ::_::Print (item);
}

#if SEAM >= SCRIPT2_4

COut::COut (FLT item) {
  ::_::Print (item);
}

COut::COut (DBL item) {
  ::_::Print (item);
}
#endif

COut& COut::Star () { return *this; }

COut& COut::Print (CH1 item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (CH2 item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (CH4 item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (const CH1* item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (const CH2* item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (const CH4* item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (SI4 item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (UI4 item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (SI8 item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (UI8 item) {
  ::_::Print (item);
  return *this;
}

#if SEAM >= SCRIPT2_4

COut& COut::Print (FLT item) {
  ::_::Print (item);
  return *this;
}

COut& COut::Print (DBL item) {
  ::_::Print (item);
  return *this;
}
#endif

#if SCRIPT2_CHAR_SIZE == UTF8

COut& COut::Print (Right1 item) {
  ::_::PrintRight (item.token.String (), item.token.Count ());
  return *this;
}

COut& COut::Print (Center1 item) {
  ::_::PrintCenter (item.token.String (), item.token.Count ());
  return *this;
}

COut& COut::Print (Line1 item) {
  PrintLine (item.token.String (), item.token.Count ());
  return *this;
}

COut& COut::Print (Repeat1 item) {
  PrintRepeat (item.token.String (), item.token.Count ());
  return *this;
}

#elif SCRIPT2_CHAR_SIZE == UTF16

COut& COut::Print (Right2 item) {
  Print (item.token.String ());
  return *this;
}

COut& COut::Print (Center2 item) {
  Print (item.token.String ());
  return *this;
}

COut& COut::Print (Line2 item) {
  auto string = item.token.String ();
  if (string) PrintLine (string, item.token. Count ());
  else        PrintLine (item.token, item.token. Count ());
  return *this;
}

COut& COut::Print (Repeat2 item) {
  auto string = item.token.String ();
  if (string) PrintRepeat (string);
  else        PrintRepeat (item.token);
  return *this;
}

#lif SCRIPT2_CHAR_SIZE == UTF32

COut& COut::Print (Right4 item) {
  Print (item.token.String ());
  return *this;
}

COut& COut::Print (Center4 item) {
  Print (item.token.String ());
  return *this;
}

COut& COut::Print (Line4 item) {
  auto string = item.token.String ();
  if (string) PrintLine (string);
  else        PrintLine (item.token);
  return *this;
}

COut& COut::Print (Repeat4 item) {
  const CH4* string = item.token.String ();
  if (string) PrintRepeat (string);
  else        PrintRepeat (item.token);
  return *this;
}

#endif

}  // namespace _

::_::COut& operator<<(::_::COut& cout, const CH1* string) {
  return cout.Print (string);
}

::_::COut& operator<<(::_::COut& cout, const CH2* string) {
  return cout.Print (string);
}

::_::COut& operator<<(::_::COut& cout, const CH4* string) {
  return cout.Print (string);
}

::_::COut& operator<<(::_::COut& cout, CH1 c) {
  return cout.Print (c);
}

::_::COut& operator<<(::_::COut& cout, CH2 c) {
  return cout.Print (c);
}

::_::COut& operator<<(::_::COut& cout, CH4 c) {
  return cout.Print (c);
}

::_::COut& operator<<(::_::COut& cout, UI1 value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, SI2 value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, UI2 value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, SI4 value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, UI4 value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, SI8 value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, UI8 value) {
  return cout.Print (value);
}

#if SEAM >= SCRIPT2_4

::_::COut& operator<<(::_::COut& cout, FLT value) {
  return cout.Print (value);
}

::_::COut& operator<<(::_::COut& cout, DBL value) {
  return cout.Print (value);
}
#endif

#if SCRIPT2_CHAR_SIZE == UTF8

::_::COut& operator<<(::_::COut& cout, ::_::Center1 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Right1 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Line1 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Repeat1 item) {
  return cout.Print (item);
}

#elif SCRIPT2_CHAR_SIZE == UTF16

::_::COut& operator<<(::_::COut& cout, ::_::Center2 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Right2 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Line2 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Repeat2 item) {
  return cout.Print (item);
}

#lif SCRIPT2_CHAR_SIZE == UTF32


::_::COut& operator<<(::_::COut& cout, ::_::Center4 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Right4 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Line4 item) {
  return cout.Print (item);
}

::_::COut& operator<<(::_::COut& cout, ::_::Repeat4 item) {
  return cout.Print (item);
}

#endif

#undef PRINT_ARGS
