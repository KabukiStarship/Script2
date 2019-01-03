/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_console.cc
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

#include <conio.h>
#include <cstdio>
#include <iostream>

#include "cconsole.h"

#include "cascii.h"
#include "tbinary.h"
#include "ttest.h"

#if SEAM == _0_0_0__00
#include "test_debug.inl"
#define PRINT_ARGS                                    \
  Printf("\nargs_count:%i args:%p", arg_count, args); \
  for (int i = 0; i < arg_count; ++i) Printf("\n%i:\"%s", i, args[i])
#else
#include "test_release.inl"
#define PRINT_ARGS
#endif

namespace _ {

const CH1* ArgsToString(int arg_count, CH1** args) {
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

inline void Print(CH1 c) { putchar(c); }

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

void Print(const CH1* string_) { Printf(string_); }

void Print(const CH2* string_) { TPrintString<CH2>(string_); }

void Print(const CH4* string_) { TPrintString<CH4>(string_); }

void Print(const CH1* string_, CH1 delimiter) {
  Printf(string_);
  return Print(delimiter);
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
#if SEAM <= _0_0_0__01
  return Printf(FORMAT_UI8, value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintUnsigned<>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void Print(UI4 value) {
#if SEAM <= _0_0_0__01
  return Printf("%u", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintUnsigned<UI4, CH1>(socket, kSize - 1, value);
#endif
}

void Print(SI8 value) {
#if SEAM <= _0_0_0__01
  return Printf(FORMAT_SI8, value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void Print(SI4 value) {
#if SEAM <= _0_0_0__01
  return Printf("%i", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintSigned<SI8>(socket, kSize - 1, (SI8)value);
#endif
}

void Print(FLT value) {
#if SEAM <= _0_0_0__13
  return Printf("%f", value);
#else
  enum { kSize = 16 };
  CH1 socket[kSize];
  TPrintFloat<FLT, UI4, CH1>(socket, kSize, value);
  Print(socket);
#endif
}

void Print(DBL value) {
#if SEAM <= _0_0_0__13
  return Printf("%f", value);
#else
  enum { kSize = 24 };
  CH1 socket[kSize];
  TPrintFloat<DBL, UI8, CH1>(socket, kSize - 1, value);
  Print(socket);
#endif
}

void PrintLn(const CH1* string_) {
  Print('\n');
  Print(string_);
}

void PrintIndent(int count) {
  Print('\n');
  while (--count > 0) Print(' ');
}

void PrintLine(int width, CH1 token, CH1 first_token) {
  Print('\n');
  if (width > 1) Print(first_token);
  while (width-- > 0) Print(token);
}

void PrintHeading(const CH1* heading_a, const CH1* heading_b, int line_count,
                  int width, CH1 token, CH1 first_token) {
  if (line_count < 1 || width < 1)
    while (line_count-- > 0) Print('\n');
  PrintLine(width, token, '+');
  Print("\n| ");
  Print(heading_a);
  Print(heading_b);
  PrintLine(width, token, '+');
  Print('\n');
}

void PrintHeading(const CH1* heading, int line_count, int width, CH1 token,
                  CH1 first_token) {
  if (line_count < 1 || width < 1) return;
  while (line_count-- > 0) Print('\n');
  PrintLine(width, token, '+');
  Print("\n| ");
  Print(heading);
  PrintLine(width, token, '+');
  Print('\n');
}

template <typename UI>
void TPrintBinaryUnsigned(UI value) {
  enum { kSize = sizeof(UI) * 8 };

  for (int i = kSize; i > 0; --i) {
    CH1 c = (CH1)('0' + (value >> (kSize - 1)));
    Print(c);
    value = value << 1;
  }
}

template <typename SI, typename UI>
void PrintBinarySigned(SI value) {
  return TPrintBinaryUnsigned<UI>((UI)value);
}

void PrintBinary(UI1 value) { return TPrintBinaryUnsigned<UI1>(value); }

void PrintBinary(SI1 value) { return PrintBinarySigned<SI1, UI1>(value); }

void PrintBinary(UI2 value) { return TPrintBinaryUnsigned<UI2>(value); }

void PrintBinary(SI2 value) { return PrintBinarySigned<SI2, UI2>(value); }

void PrintBinary(UI4 value) { return TPrintBinaryUnsigned<UI4>(value); }

void PrintBinary(SI4 value) { return PrintBinarySigned<SI4, UI4>(value); }

void PrintBinary(UI8 value) { return TPrintBinaryUnsigned<UI8>(value); }

void PrintBinary(SI8 value) { return PrintBinarySigned<SI8, UI8>(value); }

void PrintBinary(FLT value) {
  return TPrintBinaryUnsigned<UI4>(*reinterpret_cast<UI4*>(&value));
}

void PrintBinary(DBL value) {
  return TPrintBinaryUnsigned<UI8>(*reinterpret_cast<UI8*>(&value));
}

void PrintBinary(const void* ptr) {
  return TPrintBinaryUnsigned<UIW>(*reinterpret_cast<UIW*>(&ptr));
}

/* Prints the following value to the console in Hex. */
template <typename UI>
void TPrintHexConsole(UI value) {
  enum { kHexStringLengthSizeMax = sizeof(UI) * 2 + 3 };
  Print('0', 'x');
  for (int num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4)
    Print(HexNibbleToUpperCase((UI1)(value >> num_bits_shift)));
}

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

int CInKey() { return _getch(); }

BOL CInState(int vk_code) {
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

#if SEAM >= _0_0_0__02
namespace _ {

void PrintSocket(const CH1* begin, const CH1* end) {
  // @todo This function needs to write the memory to a Socket which then
  // gets printed to the TCOut ().

  if (!begin || begin >= end) return;

  const CH1 *address_ptr = reinterpret_cast<const CH1*>(begin),
             *address_end_ptr = reinterpret_cast<const CH1*>(end);
  size_t size = address_end_ptr - address_ptr,
         num_rows = size / 64 + (size % 64 != 0) ? 1 : 0;

  SIW num_bytes = 81 * (num_rows + 2);
  size += num_bytes;
  Print('\n', '|');

  //  Columns
  Printf("0%8i ", 8);
  for (int i = 16; i <= 56; i += 8) Printf("%8i", i);
  for (int j = 6; j > 0; --j) Print(' ');
  Print('|', '\n', '|');
  for (int j = 8; j > 0; --j) {
    Print('+');
    for (int k = 7; k > 0; --k) Print('-');
  }
  Print('|', ' ');

  PrintHex(address_ptr);

  CH1 c;
  while (address_ptr < address_end_ptr) {
    Print('\n');
    Print('|');
    for (int i = 0; i < 64; ++i) {
      c = *address_ptr++;
      if (address_ptr > address_end_ptr)
        c = 'x';
      else if (!c || c == TAB)
        c = ' ';
      else if (c < ' ')
        c = DEL;
      Print(c);
    }
    Print('|', ' ');
    PrintHex(address_ptr);
  }
  Print('\n', '|');
  for (int j = 8; j > 0; --j) {
    Print('+');
    for (int k = 7; k > 0; --k) {
      Print('-');
    }
  }
  Print('|', ' ');
  PrintHex(address_ptr + size);
}

void PrintSocket(const void* begin, SIW size) {
  const CH1* begin_char = reinterpret_cast<const CH1*>(begin);
  return PrintSocket(begin_char, begin_char + size);
}

}  // namespace _
#endif  //< #if SEAM >= _0_0_0__02
#undef PRINT_ARGS
