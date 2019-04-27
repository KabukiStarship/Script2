/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_sout.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_COUT_C
#define SCRIPT2_COUT_C 1

#if USING_STR == UTF8
#include "c_uniprinter1.h"
#endif

#if USING_STR == UTF16
#include "c_uniprinter2.h"
#endif

#if USING_STR == UTF32
#include "c_uniprinter4.h"
#endif

namespace _ {

/* Converts SI4 main(SI4,CH1**) arguments back into a string.
@return nil if there are no arguments or the args string upon success.
@param arg_count The number_ of arguments.
@param args      The arguments. */
SDK const CH1* ArgsToSring(SI4 arg_count, CH1** args);

/* Force-prints a single CH1 to the console. */
SDK /*inline*/ void PrintChar(CH1 c);
SDK /*inline*/ void PrintChar(CH2 c);
SDK /*inline*/ void PrintChar(CH4 c);

/* Prints a single CH1 to the console. */
SDK void Print(CH1 first, CH1 second);

/* Prints a single CH1 to the console. */
SDK void Print(CH1 first, CH1 second, CH1 third);

/* Prints a single string to the console followed by the given delimiter. */
SDK void Print(const CH1* string, CH1 delimiter);

/* Prints two strings to the SOut. */
SDK void Print(const CH1* a, const CH1* b);

/* Prints the give item to the SOut. */
SDK /*inline*/ void Print(CH1 c);
SDK /*inline*/ void Print(CH2 c);
SDK /*inline*/ void Print(CH4 c);
SDK void Print(const CH1* string);
SDK void Print(const CH2* string);
SDK void Print(const CH4* string);
SDK void Print(SI8 item);
SDK void Print(UI8 item);
SDK void Print(SI4 item);
SDK void Print(UI4 item);
SDK void Print(FP4 item);
SDK void Print(FP8 item);

/* Prints a new line followed by a single CH1 to the console. */
SDK /*inline*/ void PrintNL();

/* Prints a new line followed by a single CH1 to the console. */
SDK /*inline*/ void PrintNL(CH1 c);

/* Prints a new line followed by a single CH1 to the console. */
SDK /*inline*/ void PrintNL(CH1 first, CH1 second);

/* Prints a new line followed by a single string to the console. */
SDK /*inline*/ void PrintNL(const CH1* string);

/* Prints a formatted string to the console. */
SDK void Printf(const CH1* format, ...);

/* Prints a new line followed by a formatted string to the console. */
SDK void PrintfLn(const CH1* format, ...);

/* Prints a new line followed by the given number_ of spaces.
@param The number_ of spaces to indent. */
SDK void PrintIndent(SI4 count = 1);

/* Prints a item to the SOut. */
SDK void PrintBinary(UI1 item);
SDK void PrintBinary(SI1 item);
SDK void PrintBinary(UI2 item);
SDK void PrintBinary(SI2 item);
SDK void PrintBinary(UI4 item);
SDK void PrintBinary(SI4 item);
SDK void PrintBinary(UI8 item);
SDK void PrintBinary(SI8 item);
SDK void PrintBinary(FP4 item);
SDK void PrintBinary(FP8 item);
SDK void PrintBinary(const void* item);

/* Prints a item to the console to hex. */
SDK void PrintHex(CH1 item);
SDK void PrintHex(CH2 item);
SDK void PrintHex(CH4 item);
SDK void PrintHex(UI1 item);
SDK void PrintHex(SI1 item);
SDK void PrintHex(UI2 item);
SDK void PrintHex(SI2 item);
SDK void PrintHex(UI4 item);
SDK void PrintHex(SI4 item);
SDK void PrintHex(UI8 item);
SDK void PrintHex(SI8 item);
SDK void PrintHex(FP4 item);
SDK void PrintHex(FP8 item);

/* Prints the given socket to the stdout in hex format. */
SDK void PrintHex(const void* begin, const void* end);

/* Prints the given socket to the stdout in hex format. */
SDK void PrintHex(const void* begin, SIW size);

/* Prints a pointer to the console in hex. */
SDK void PrintHex(const void* value);

/* Prints the given socket to the stdout. */
SDK void PrintChars(const void* begin, const void* end);

/* Prints the given socket to the stdout. */
SDK void PrintChars(const void* begin, SIW size);

/* Prints the given item right aligned the given count to the stdout. */
SDK /*inline*/ void PrintRight(const CH1* item, SI4 count = 80);

/* Prints the given item center aligned the given count to the stdout. */
SDK /*inline*/ void PrintCenter(const CH1* item, SI4 count = 80);

SDK const CH1* PrintLinefCH1();

/* Prints the given token a specified count. */
SDK const CH1* PrintLinef(const CH1* style, SI4 column_count = 80);

/* Prints a the given line_count of new lines followed by a PrintLinef, the
heading, followed by another PrintLinef.
@return Nil upon success or a pointer to the
@param style       The line format string.
@param column_count The width of the line to utf. */
SDK void PrintHeadingf(const CH1* caption, const CH1* style = nullptr,
                       SI4 column_count = 80, const CH1* caption2 = nullptr,
                       const CH1* caption3 = nullptr);

#if USING_UTF16 == YES

/* Prints the given UTF-16 characters to the stdout. */
SDK void PrintChars(const CH2* start, const CH2* stop);

/* Prints the given UTF-16 characters to the stdout. */
SDK void PrintChars(const CH2* start, SI4 count);

/* Prints the given item right aligned the given count to the stdout. */
SDK /*inline*/ void PrintRight(const CH2* item, SI4 count = 80);

/* Prints the given item center aligned the given count to the stdout. */
SDK /*inline*/ void PrintCenter(const CH2* item, SI4 count = 80);

SDK const CH2* PrintLinefCH2();

/* Prints the given token a specified count. */
SDK const CH2* PrintLinef(const CH2* style = PrintLinefCH2(),
                          SI4 column_count = 80);

/* Prints a the given line_count of new lines followed by a PrintLinef, the
heading, followed by another PrintLinef.
@param style       The line format string.
@param column_count The width of the line to utf. */
SDK void PrintHeadingf(const CH2* caption, const CH2* style = nullptr,
                       SI4 column_count = 80, const CH2* caption2 = nullptr,
                       const CH2* caption3 = nullptr);
#endif
#if USING_UTF32 == YES

/* Prints the given UTF-16 characters to the stdout. */
SDK void PrintChars(const CH4* start, const CH4* stop);

/* Prints the given UTF-16 characters to the stdout. */
SDK void PrintChars(const CH4* start, SI4 size);

/* Prints the given item right aligned the given count to the stdout. */
SDK /*inline*/ void PrintRight(const CH4* item, SI4 count = 80);

/* Prints the given item center aligned the given count to the stdout. */
SDK /*inline*/ void PrintCenter(const CH4* item, SI4 count = 80);

SDK const CH4* PrintLinefCH4();

/* Prints the given style a specified count. */
SDK const CH4* PrintLinef(const CH4* style, SI4 column_count = 80);

/* Prints the given token a specified count. */
SDK void PrintLinef(CH4 token, SI4 column_count = 80);

/* Prints a the given line_count of new lines followed by a PrintLinef, the
heading, followed by another PrintLinef.
@param style       The line format string.
@param column_count The width of the line to utf. */
SDK void PrintHeadingf(const CH4* caption, const CH4* style = nullptr,
                       SI4 column_count = 80, const CH4* caption2 = nullptr,
                       const CH4* caption3 = nullptr);
#endif

/* Utility class for printing to the stdout. */
class SOut {
 public:
  /* Does nothing. */
  SOut();

  /* Prints the given item to the SOut stream. */
  SOut(const CH1* item);
  SOut(const CH2* item);
  SOut(const CH4* item);
  SOut(SI1 item);
  SOut(UI1 item);
  SOut(SI2 item);
  SOut(UI2 item);
  SOut(SI4 item);
  SOut(UI4 item);
  SOut(SI8 item);
  SOut(UI8 item);
#if SEAM >= SCRIPT2_4
  SOut(FP4 item);
  SOut(FP8 item);
#endif

  /* Returns reference to this. */
  SOut& Star();

  /* Prints the given item to the stdout. */
  SOut& Print(CH1 item);
  SOut& Print(CH2 item);
  SOut& Print(CH4 item);
  SOut& Print(const CH1* item);
  SOut& Print(const CH2* item);
  SOut& Print(const CH4* item);
  SOut& Print(SI4 item);
  SOut& Print(UI4 item);
  SOut& Print(SI8 item);
  SOut& Print(UI8 item);
#if USING_FP4 == YES
  SOut& Print(FP4 item);
#endif
#if USING_FP8 == YES
  SOut& Print(FP8 item);
#endif
  SOut& Print(const void* begin, SIW size_bytes);
  SOut& Print(Hex item);
#if SEAM >= SCRIPT2_3
#if USING_STR == UTF8
  SOut& Print(Right1 item);
  SOut& Print(Center1 item);
  SOut& Print(Linef1 item);
  SOut& Print(Headingf1 item);
  SOut& Print(Chars1 item);
  SOut& Print(Hexs1 item);
#elif USING_STR == UTF16
  SOut& Print(Right2 item);
  SOut& Print(Center2 item);
  SOut& Print(Linef2 item);
  SOut& Print(Headingf2 item);
  // SOut& Print(Chars2 item);
  // SOut& Print(Hexs2 item);
#lif USING_STR == UTF32
  SOut& Print(Right4 item);
  SOut& Print(Center4 item);
  SOut& Print(Linef4 item);
  SOut& Print(Headingf4 item);
  // SOut& Print(Chars4 item);
  // SOut& Print(Hexs4 item);
#endif
#endif
};

}  // namespace _

/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::SOut& o);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, const CH1* string);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, const CH2* string);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, const CH4* string);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, CH1 c);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, CH2 c);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, CH4 c);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, UI1 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, SI2 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, UI2 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, SI4 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, UI4 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, SI8 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, UI8 value);
#if SEAM >= SCRIPT2_4
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, FP4 value);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, FP8 value);
#endif
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Hex item);
#if SEAM >= SCRIPT2_3
#if USING_STR == UTF8
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Center1 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Right1 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Linef1 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Headingf1 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Chars1 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Hexs1 item);
#elif USING_STR == UTF16
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Center2 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Right2 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Linef2 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Headingf2 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Chars2 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Hexs2 item);
#elif USING_STR == UTF32
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Center4 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Right4 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Linef4 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Headingf4 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Chars4 item);
/*inline*/ ::_::SOut& operator<<(::_::SOut& cout, ::_::Hexs4 item);
#endif

#endif
#endif
