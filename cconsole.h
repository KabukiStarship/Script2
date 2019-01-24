/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/cconsole.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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

#ifndef SCRIPT2_CCONSOLE
#define SCRIPT2_CCONSOLE 1

namespace _ {

/* Converts SI4 main(SI4,CH1**) arguments back into a string.
@return nil if there are no arguments or the args string upon success.
@param arg_count The number_ of arguments.
@param args      The arguments. */
SDK const CH1* ArgsToString(SI4 arg_count, CH1** args);

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

/* Prints the given token CH1 a specified number_ of times. */
SDK void PrintLine(SI4 width = 80, CH1 token = '-', CH1 first_token = '-');

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

/* Prints a message then pauses the application until a key is pressed. */
SDK void Pause(const CH1* message = "");

/* Prints a message then pauses the application until a key is pressed. */
SDK void Pausef(const CH1* message, ...);

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

/* Reads the current key depressed on the keyboard.
@return A negative number_ (typically 1) if no keys are pressed. */
SDK SI4 CInKey();

/* Prints the given socket to the stdout. */
SDK void PrintSocket(const void* begin, const void* end);

/* Prints the given socket to the stdout. */
SDK void PrintSocket(const void* begin, SIW size);

}  // namespace _

#endif  //< #ifndef SCRIPT2_CCONSOLE
