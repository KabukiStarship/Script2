/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_cout.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_COUT_C
#define SCRIPT2_COUT_C 1

#if SCRIPT2_CHAR_SIZE == UTF8
#include "c_utf1.h"
#elif SCRIPT2_CHAR_SIZE == UTF16
#include "c_utf2.h"
#elif SCRIPT2_CHAR_SIZE == UTF32
#include "c_utf4.h"
#endif

namespace _ {

/* Converts SI4 main(SI4,CH1**) arguments back into a string.
@return nil if there are no arguments or the args string upon success.
@param arg_count The number_ of arguments.
@param args      The arguments. */
SDK const CH1* ArgsToStrand(SI4 arg_count, CH1** args);

/* Prints a single CH1 to the console. */
SDK inline void Print(CH1 c);

/* Prints a single CH1 to the console. */
SDK inline void Print (CH4 c);

/* Prints a single CH1 to the console. */
SDK inline void Print (CH2 c);

/* Prints a single CH1 to the console. */
SDK void Print(CH1 first, CH1 second);

/* Prints a single CH1 to the console. */
SDK void Print(CH1 first, CH1 second, CH1 third);

/* Prints a single string to the console. */
SDK void Print(const CH1* string);

/* Prints a single string to the console. */
SDK void Print(const CH2* string);

/* Prints a single string to the console. */
SDK void Print(const CH4* string);

/* Prints a single string to the console followed by the given delimiter. */
SDK void Print(const CH1* string, CH1 delimiter);

/* Prints two strings. */
SDK void Print(const CH1* a, const CH1* b);

/* Writes the give CH1 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH1
upon success.
@param value The value to utf. */
SDK void Print(SI8 value);

/* Writes the give CH1 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH1
upon success.
@param value The value to utf. */
SDK void Print(UI8 value);

/* Writes the give CH1 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH1
upon success.
@param value The value to utf. */
SDK void Print(SI4 value);

/* Writes the give CH1 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH1
upon success.
@param value The value to utf. */
SDK void Print(UI4 value);

/* Writes the give CH1 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH1
upon success.
@param value The value to utf. */
SDK void Print(FLT value);

/* Writes the give CH1 to the given socket.
@return Returns nil upon socket overflow and a pointer to the nil-term CH1
upon success.
@param value The value to utf. */
SDK void Print(DBL value);

/* Prints a new line followed by a single CH1 to the console. */
SDK inline void PrintLn(CH1 c = '\n');

/* Prints a new line followed by a single CH1 to the console. */
SDK inline void PrintLn(CH1 first, CH1 second);

/* Prints a new line followed by a single string to the console. */
SDK inline void PrintLn(const CH1* string);

/* Prints a formatted string to the console. */
SDK void Printf(const CH1* format, ...);

/* Prints a new line followed by a formatted string to the console. */
SDK void PrintfLn(const CH1* format, ...);

/* Prints a new line followed by the given number_ of spaces.
@param The number_ of spaces to indent. */
SDK void PrintIndent(SI4 count = 1);

/* Prints the given token a specified count. */
SDK void PrintLine(CH1 token = '-', SI4 count = 80, CH1 first_token = '-');

/* Prints the given string a specified count of characters. */
SDK void PrintLine (const CH1* string, SI4 count = 80, CH1 first_token = '-');

/* Prints the given item a specified count of characters. */
SDK void PrintRepeat (CH1 item = '\n', SI4 count = 80);

/* Prints the given item a specified count of characters. */
SDK void PrintRepeat (const CH1* item, SI4 count = 80, CH1 delimiter = '\n');

/* Prints a the given line_count of new lines followed by a PrintLine, the
heading, followed by another PrintLine.
@param heading The heading to utf.
@param line_count The number_ of new lines before the heading to utf.
@param width The width of the line to utf.
@param first_token The first token to utf. */
SDK void PrintHeading(const CH1* heading = nullptr, SI4 line_count = 5,
                      SI4 width = 80, CH1 token = '-', CH1 first_token = '+');

/* Prints a the given line_count of new lines followed by a PrintLine, the
heading, followed by another PrintLine.
@param heading The heading to utf.
@param line_count The number_ of new lines before the heading to utf.
@param width The width of the line to utf.
@param first_token The first token to utf. */
SDK void PrintHeading(const CH1* heading_a, const CH1* heading_b,
                      SI4 line_count = 5, SI4 width = 80, CH1 token = '-',
                      CH1 first_token = '+');

/* Prints a 8-bit binary item to the console. */
SDK void PrintBinary(UI1 item);

/* Prints a 8-bit binary item to the console. */
SDK void PrintBinary(SI1 item);

/* Prints a 16-bit binary item to the console. */
SDK void PrintBinary(UI2 item);

/* Prints a 16-bit binary item to the console. */
SDK void PrintBinary(SI2 item);

/* Prints a 32-bit binary item to the console. */
SDK void PrintBinary(UI4 item);

/* Prints a 32-bit binary item to the console. */
SDK void PrintBinary(SI4 item);

/* Prints a 64-bit binary item to the console. */
SDK void PrintBinary(UI8 item);

/* Prints a 64-bit binary item to the console. */
SDK void PrintBinary(SI8 item);

/* Prints a 32-bit floating-point number_ to the console in binary. */
SDK void PrintBinary(FLT item);

/* Prints a 64-bit floating-point number_ to the console in binary. */
SDK void PrintBinary(DBL item);

/* Prints a pointer to the console in binary. */
SDK void PrintBinary(const void* item);

/* Prints a item to the console to hex. */
SDK void PrintHex (CH1 item);

/* Prints a item to the console to hex. */
SDK void PrintHex (CH2 item);

/* Prints a item to the console to hex. */
SDK void PrintHex (CH4 item);

/* Prints a 8-bit binary item to the console to hex. */
SDK void PrintHex(UI1 item);

/* Prints a 8-bit binary item to the console to hex. */
SDK void PrintHex(SI1 item);

/* Prints a 16-bit binary item to the console to hex. */
SDK void PrintHex(UI2 item);

/* Prints a 16-bit binary item to the console to hex. */
SDK void PrintHex(SI2 item);

/* Prints a 32-bit binary item to the console to hex. */
SDK void PrintHex(UI4 item);

/* Prints a 32-bit binary item to the console to hex. */
SDK void PrintHex(SI4 item);

/* Prints a 64-bit binary item to the console to hex. */
SDK void PrintHex(UI8 item);

/* Prints a 64-bit binary item to the console to hex. */
SDK void PrintHex(SI8 item);

/* Prints a 32-bit floating-point number_ to the console in hex. */
SDK void PrintHex(FLT item);

/* Prints a 64-bit floating-point number_ to the console in hex. */
SDK void PrintHex(DBL item);

/* Prints the given socket to the stdout in hex format. */
SDK void PrintHex (const void* begin, const void* end);

/* Prints the given socket to the stdout in hex format. */
SDK void PrintHex (const void* begin, SIW size);

/* Prints a pointer to the console in hex. */
SDK void PrintHex(const void* value);

/* Prints the given socket to the stdout. */
SDK void PrintChars(const void* begin, const void* end);

/* Prints the given socket to the stdout. */
SDK void PrintChars(const void* begin, SIW size);

#if USING_UTF16 == YES
/* Prints the given CH2 buffer including nil-term chars. */
void PrintChars (const CH2* start, SIW count);
#endif
#if USING_UTF32 == YES
/* Prints the given CH4 buffer including nil-term chars. */
void PrintChars (const CH4* start, SIW count);
#endif

/* Prints the given item right aligned the given count to the stdout. */
SDK inline void PrintRight (const CH1* item, SI4 count = 80);

/* Prints the given item center aligned the given count to the stdout. */
SDK inline void PrintCenter (const CH1* item, SI4 count = 80);

/* Wrapper class for the stdout. */
class COut {
 public:
    
  COut (const CH1* item);

  COut (const CH2* item);

  COut (const CH4* item);

  COut (SI1 item);

  COut (UI1 item);

  COut (SI2 item);

  COut (UI2 item);

  COut (SI4 item);

  COut (UI4 item);

  COut (SI8 item);

  COut (UI8 item);

#if SEAM >= SCRIPT2_4
  COut (FLT item);

  COut (DBL item);

#endif

  COut& Star ();

  COut& Print (CH1 item);

  COut& Print (CH2 item);

  COut& Print (CH4 item);

  COut& Print (const CH1* item);

  COut& Print (const CH2* item);

  COut& Print (const CH4* item);

  COut& Print (SI4 item);

  COut& Print (UI4 item);

  COut& Print (SI8 item);

  COut& Print (UI8 item);

#if SEAM >= SCRIPT2_4

  COut& Print (FLT item);

  COut& Print (DBL item);

#endif

#if SCRIPT2_CHAR_SIZE == UTF8

  COut& Print (Right1 item);
      
  COut& Print (Center1 item);

  COut& Print (Line1 item);

  COut& Print (Repeat1 item);

#elif SCRIPT2_CHAR_SIZE == UTF16

  COut& Print (Right2 item);

  COut& Print (Center2 item);

  COut& Print (Line2 item);

  COut& Print (Repeat2 item);

#lif SCRIPT2_CHAR_SIZE == UTF32

  COut& Print (Right4 item);

  COut& Print (Center4 item);

  COut& Print (Line4 item);

  COut& Print (Repeat4 item);

#endif

};

} //< namespace _

inline ::_::COut& operator<<(::_::COut& cout, const CH1* string);
inline ::_::COut& operator<<(::_::COut& cout, const CH2* string);
inline ::_::COut& operator<<(::_::COut& cout, const CH4* string);
inline ::_::COut& operator<<(::_::COut& cout, CH1 c);
inline ::_::COut& operator<<(::_::COut& cout, CH2 c);
inline ::_::COut& operator<<(::_::COut& cout, CH4 c);
inline ::_::COut& operator<<(::_::COut& cout, UI1 value);
inline ::_::COut& operator<<(::_::COut& cout, SI2 value);
inline ::_::COut& operator<<(::_::COut& cout, UI2 value);
inline ::_::COut& operator<<(::_::COut& cout, SI4 value);
inline ::_::COut& operator<<(::_::COut& cout, UI4 value);
inline ::_::COut& operator<<(::_::COut& cout, SI8 value);
inline ::_::COut& operator<<(::_::COut& cout, UI8 value);

#if SEAM >= SCRIPT2_4

inline ::_::COut& operator<<(::_::COut& cout, FLT value);
inline ::_::COut& operator<<(::_::COut& cout, DBL value);

#endif

#if SEAM >= SCRIPT2_3

#if SCRIPT2_CHAR_SIZE == UTF8

inline ::_::COut& operator<<(::_::COut& cout, ::_::Center1 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Right1 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Line1 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Repeat1 item);

#elif SCRIPT2_CHAR_SIZE == UTF16

inline ::_::COut& operator<<(::_::COut& cout, ::_::Center2 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Right2 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Line2 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Repeat2 item);

#elif SCRIPT2_CHAR_SIZE == UTF32

inline ::_::COut& operator<<(::_::COut& cout, ::_::Center4 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Right4 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Line4 item);
inline ::_::COut& operator<<(::_::COut& cout, ::_::Repeat4 item);

#endif
#endif
#endif
