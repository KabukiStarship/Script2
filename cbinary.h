/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cbinary.h
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

#ifndef SCRIPT2_CBINARY
#define SCRIPT2_CBINARY 1

namespace _ {

/* Converts a UI1 a one-UI1 hex representation. */
API CH1 HexNibbleToUpperCase(UI1 b);

#if SEAM >= _0_0_0__01

/* Lookup table of ASCII Char pairs for 00, 01, ..., 99. */
API const UI2* BinaryLUTDecimals();

/* Lookup table of the IEEE754 integral portion of pre-computed powers of ten.
 */
API const SI2* BinaryLUTE();

/* Lookup table of the IEEE754 exponent of pre-computed powers of ten. */
API const UI8* BinaryLUTF();

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(SI1 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(UI1 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(SI2 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(UI2 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(SI4 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(UI4 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(SI8 value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(UI8 value);

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
API CH1 HexNibbleToLowerCase(UI1 b);

/* Converts a UI1 a two-UI1 hex representation. */
API UI2 HexByteToLowerCase(UI1 b);

/* Converts a UI1 a two-UI1 hex representation. */
API UI2 HexByteToUpperCase(UI1 b);

/* Converts a single hex UI1 a UI1.
@return Returns -1 if c is not a hex UI1. */
API int HexToByte(CH1 hex_byte);

/* Converts a UI1 into a two-UI1 hex representation.
@return Returns -1 if c is not a hex UI1.
*/
API int HexToByte(UI2 hex);

/* Prints the given SI4 to the socket. */
API CH1* Print(CH1* cursor, CH1* stop, SI4 value);

/* Prints the given UI4 to the socket. */
API CH1* Print(CH1* cursor, CH1* stop, UI4 value);

#endif  //< #if SEAM >= _0_0_0__01

#if SEAM >= _0_0_0__04
/* Gets the maximum number_ of digits required to represent a FLT as in
ASCII. */
API int FloatDigitsMax();

/* Gets the maximum number_ of digits required to represent a DBL as in
ASCII. */
API int DoubleDigitsMax();

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(FLT value);

/* Checks if the given value is Not-a-Number.
@param  value The value to check.
@return True if the value is NaN and false otherwise. */
API BOL IsNaN(DBL value);

/* Checks if the given value is not NaN or +/- Infinity. */
API BOL IsFinite(FLT value);

/* Checks if the given value is not NaN or +/- Infinity. */
API BOL IsFinite(DBL value);

/* Checks if the given value is not NaN or +/- Infinity. */
API BOL IsInfinite(FLT value);

/* Checks if the given value is not NaN or +/- Infinity. */
API BOL IsInfinite(DBL value);

/* Returns the ceiling of the given value to the next highest up integer. */
API FLT Ceiling(FLT value);

/* Returns the ceiling of the given value to the next highest up integer. */
API DBL Ceiling(DBL value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(UI1 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(SI1 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(UI2 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(SI2 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(UI4 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(SI4 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(UI8 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
API int MSbAsserted(SI8 value);

/* IEEE754 Powers of 10 exponents LUT. */
API const SI2* IEEE754Pow10E();

/* IEEE754 Powers of 10 integral portions LUT. */
API const UI8* IEEE754Pow10F();

/* Returns the last UI1 in the given CH1, which in this case is c. */
API CH1* LastByte(CH1* c);

/* Prints the given FLT to the socket. */
API CH1* Print(CH1* cursor, CH1* stop, FLT value);

/* Prints the given FLT to the socket. */
API CH1* Print(CH1* cursor, CH1* stop, DBL value);

/* Scans a FLT from the given string_.
@return Nil if the string_ doesn't begin with a FLT. */
const CH1* Scan(const CH1* cursor, FLT& value);

/* Scans a DBL from the given string_.
@return Nil if the string_ doesn't begin with a DBL. */
const CH1* Scan(const CH1* cursor, DBL& value);

#if USING_UTF16 == YES
/* Returns the last UI1 in the given CH1. */
API CH1* LastByte(CH2* c);

/* Prints the given FLT to the socket. */
API CH2* Print(CH2* cursor, CH2* stop, FLT value);

/* Prints the given FLT to the socket. */
API CH2* Print(CH2* cursor, CH2* stop, DBL value);
#endif

#if USING_UTF32 == YES
/* Returns the last UI1 in the given CH1. */
API CH1* LastByte(CH4* c);

/* Prints the given FLT to the socket. */
API CH4* Print(CH4* cursor, CH4* stop, FLT value);

/* Prints the given FLT to the socket. */
API CH4* Print(CH4* cursor, CH4* stop, DBL value);
#endif

#endif  //< #if SEAM >= _0_0_0__03
}  // namespace _
#endif  //< #ifndef SCRIPT2_CBINARY
