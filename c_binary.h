/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_binary.h
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

#ifndef SCRIPT2_CBINARY
#define SCRIPT2_CBINARY 1

namespace _ {

/* Converts a UI1 a one-UI1 hex representation. */
SDK CH1 HexNibbleToUpperCase(UI1 b);

/* Gets the header to print for PrintChars(const void*, const void*). */
SDK const CH1* StrandSocketHeader();

/* Gets the header to print for PrintChars(const void*, const void*). */
SDK const CH1* StrandSocketBorder();

/* Gets the header to print for PrintHex(const void*, const void*). */
SDK const CH1* STRSocketHexHeader();

/* Gets the header to print for PrintHex(const void*, const void*). */
SDK const CH1* STRSocketHexBorder();

#if SEAM >= SCRIPT2_1

/* Lookup table of ASCII Char pairs for 00, 01, ..., 99. */
SDK const UI2* BinaryLUTDecimals();

/* IEEE754 Powers of 10 integral portions LUT. */
SDK inline const void* Binary32Pow10IntegralPortions();

/* IEEE754 Powers of 10 integral portions LUT. */
SDK inline const void* Binary64Pow10IntegralPortions();

/* Lookup table of the IEEE754 integral portion of pre-computed powers of 10.
 */
SDK inline const void* BinaryPow10Exponents();

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(SI1 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(UI1 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(SI2 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(UI2 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(SI4 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(UI4 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(SI8 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(UI8 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI1 Unsigned(SI1 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI2 Unsigned(SI2 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI4 Unsigned(SI4 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI8 Unsigned(SI8 value);

/* Utility function multiplies the given value by -1. */
UI1 Negative(SI1 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI1 Negative(UI1 value);

/* Utility function multiplies the given value by -1. */
UI2 Negative(SI2 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI2 Negative(UI2 value);

/* Utility function multiplies the given value by -1. */
UI4 Negative(SI4 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI4 Negative(UI4 value);

/* Utility function multiplies the given value by -1. */
UI8 Negative(SI8 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI8 Negative(UI8 value);

/* Converts a UI1 a one-UI1 hex representation. */
SDK CH1 HexNibbleToLowerCase(UI1 b);

/* Converts a UI1 a two-UI1 hex representation. */
SDK UI2 HexByteToLowerCase(UI1 b);

/* Converts a UI1 a two-UI1 hex representation. */
SDK UI2 HexByteToUpperCase(UI1 b);

/* Converts a single hex UI1 a UI1.
@return Returns -1 if c is not a hex UI1. */
SDK SI4 HexToByte(CH1 hex_byte);

/* Converts a UI1 into a two-UI1 hex representation.
@return Returns -1 if c is not a hex UI1.
*/
SDK SI4 HexToByte(UI2 hex);

/* Prints the given SI4 to the socket. */
SDK CH1* Print(CH1* cursor, CH1* stop, SI4 value);

/* Prints the given UI4 to the socket. */
SDK CH1* Print(CH1* cursor, CH1* stop, UI4 value);

#if USING_UTF8 == YES
/* Prints a CH2 to the CH1* by converting it to a CH4.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH1* Print(CH1* cursor, CH1* stop, CH1 c);

/* Prints a CH2 to the CH1* by converting it to a CH4.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH1* Print(CH1* cursor, CH1* stop, CH2 c);

/* Converts a signed or unsigned CH1 to a (unsigned) cH4. */
inline SDK CH4 ToCH4(CH1 c);

/* Prints a CH2 to the CH1* by converting it to a CH4.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH1* Print(CH1* cursor, CH1* stop, CH4 c);
SDK CH1* Print(CH1* cursor, SIW size, CH4 c);

/* Attempts to scan a UTF-32 CH1 from the given UTF-8 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
SDK const CH1* Scan(const CH1* string, CH4& result);
#endif

#if USING_UTF16 == YES

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH2* Print(CH2* cursor, CH2* stop, CH2 c);

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH2* Print(CH2* cursor, CH2* stop, CH1 c);

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH2* Print(CH2* cursor, CH2* stop, CH4 c);

SDK CH2* Print(CH2* cursor, SIW size, CH4 c);

/* Attempts to scan a UTF-32 CH1 from the given UTF-16 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
SDK const CH2* Scan(const CH2* string, CH4& result);
#endif

#if USING_UTF32 == YES
/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH1 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
CH4* Print(CH4* cursor, CH4* stop, CH1 c);

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK inline CH4* Print(CH4* cursor, CH4* stop, CH2 c);

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH4 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
CH4* Print(CH4* cursor, CH4* stop, CH4 c);

#endif

#endif  //< #if SEAM >= SCRIPT2_1

#if SEAM >= SCRIPT2_4
/* Gets the maximum number_ of digits required to represent a FP4 as in
ASCII. */
SDK SI4 FloatDigitsMax();

/* Gets the maximum number_ of digits required to represent a FP8 as in
ASCII. */
SDK SI4 DoubleDigitsMax();

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(FP4 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
SDK BOL IsNaN(FP8 value);

/* Checks if the given value is not NaN or +/- Infinity. */
SDK BOL IsFinite(FP4 value);

/* Checks if the given value is not NaN or +/- Infinity. */
SDK BOL IsFinite(FP8 value);

/* Checks if the given value is not NaN or +/- Infinity. */
SDK BOL IsInfinite(FP4 value);

/* Checks if the given value is not NaN or +/- Infinity. */
SDK BOL IsInfinite(FP8 value);

/* Returns the ceiling of the given value to the next highest up integer. */
SDK FP4 Ceiling(FP4 value);

/* Returns the ceiling of the given value to the next highest up integer. */
SDK FP8 Ceiling(FP8 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(UI1 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(SI1 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(UI2 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(SI2 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(UI4 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(SI4 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(UI8 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(SI8 value);

/* Returns the last UI1 in the given CH1, which is c in this case. */
SDK CH1* LastByte(CH1* c);

/* Prints the given FP4 to the socket. */
SDK CH1* Print(CH1* cursor, CH1* stop, FP4 value);

/* Prints the given FP4 to the socket. */
SDK CH1* Print(CH1* cursor, CH1* stop, FP8 value);

/* Scans a FP4 from the given .
@return Nil if the  doesn't begin with a FP4. */
const CH1* Scan(const CH1* cursor, FP4& value);

/* Scans a FP8 from the given .
@return Nil if the  doesn't begin with a FP8. */
const CH1* Scan(const CH1* cursor, FP8& value);

#if USING_UTF16 == YES
/* Returns the last UI1 in the given CH2. */
SDK CH1* LastByte(CH2* c);

/* Prints the given FP4 to the socket. */
SDK CH2* Print(CH2* cursor, CH2* stop, FP4 value);

/* Prints the given FP4 to the socket. */
SDK CH2* Print(CH2* cursor, CH2* stop, FP8 value);
#endif

#if USING_UTF32 == YES
/* Returns the last UI1 in the given CH4. */
SDK CH1* LastByte(CH4* c);

/* Prints the given FP4 to the socket. */
SDK CH4* Print(CH4* cursor, CH4* stop, FP4 value);

/* Prints the given FP4 to the socket. */
SDK CH4* Print(CH4* cursor, CH4* stop, FP8 value);
#endif

/* Utility class for printing a POD type in hex. */
struct Hex {
  void* item;       //< Pointer to the POD instance.
  SI4 width_bytes;  //< Width of the item in bytes.

  Hex(SI1& item);
  Hex(UI1& item);
  Hex(SI2& item);
  Hex(UI2& item);
  Hex(SI4& item);
  Hex(UI4& item);
  Hex(SI8& item);
  Hex(UI8& item);

  Hex(const void* item);

#if USING_FP4 == YES
  Hex(FP4& item);
#endif
#if USING_FP8 == YES
  Hex(FP8& item);
#endif
};

#endif  //< #if SEAM >= SCRIPT2_3
}  // namespace _
#endif  //< #ifndef SCRIPT2_CBINARY
