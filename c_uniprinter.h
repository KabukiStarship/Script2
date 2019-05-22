/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_uniprinter.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_CBINARY
#define SCRIPT2_CBINARY 1

namespace _ {

/* Converts a UI1 a one-UI1 hex representation. */
SDK CH1 HexNibbleToUpperCase(UI1 b);

/* Gets the header to print for PrintChars(const void*, const void*). */
SDK const CH1* STRSocketHeader();

/* Gets the header to print for PrintChars(const void*, const void*). */
SDK const CH1* STRSocketBorder();

/* Gets the header to print for PrintHex(const void*, const void*). */
SDK const CH1* STRSocketHexHeader();

/* Gets the header to print for PrintHex(const void*, const void*). */
SDK const CH1* STRSocketHexBorder();

#if SEAM >= SCRIPT2_1

/* Lookup table of ASCII Char pairs for 00, 01, ..., 99. */
SDK const UI2* BinaryLUTDecimals();

/* IEEE754 Powers of 10 integral portions LUT. */
SDK /*inline*/ const void* Binary32Pow10IntegralPortions();

/* IEEE754 Powers of 10 integral portions LUT. */
SDK /*inline*/ const void* Binary64Pow10IntegralPortions();

/* Lookup table of the IEEE754 integral portion of pre-computed powers of 10.
 */
SDK /*inline*/ const void* BinaryPow10Exponents();

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

/* Converts a signed or unsigned CH1 to a (unsigned) cH4. */
/*inline*/ SDK CH4 ToCH4(CH1 c);

/* Prints a CH2 to the CH1* by converting it to a CH4.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
SDK CH1* Print(CH1* cursor, CH1* stop, CH1 c);
SDK CH1* Print(CH1* cursor, CH1* stop, CH2 c);
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
SDK CH2* Print(CH2* cursor, CH2* stop, CH1 c);
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
SDK /*inline*/ CH4* Print(CH4* cursor, CH4* stop, CH2 c);
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

/* Checks if the given value is Not-a-Number. */
SDK BOL IsNaN(FP4 value);
SDK BOL IsNaN(FP8 value);

/* Checks if the given value is not NaN or +/- Infinity. */
SDK BOL IsFinite(FP4 value);
SDK BOL IsFinite(FP8 value);

/* Checks if the given value is not NaN or +/- Infinity. */
SDK BOL IsInfinite(FP4 value);
SDK BOL IsInfinite(FP8 value);

/* Returns the ceiling of the given value to the next highest up integer. */
SDK FP4 Ceiling(FP4 value);
SDK FP8 Ceiling(FP8 value);

/* Gets the Most Significant Asserted Bit (MSbAsserted).
@return A negative number_ if value is zero and the highest bit. */
SDK SI4 MSbAsserted(UI1 value);
SDK SI4 MSbAsserted(SI1 value);
SDK SI4 MSbAsserted(UI2 value);
SDK SI4 MSbAsserted(SI2 value);
SDK SI4 MSbAsserted(UI4 value);
SDK SI4 MSbAsserted(SI4 value);
SDK SI4 MSbAsserted(UI8 value);
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

/* Prints the given item to the socket. */
SDK CH2* Print(CH2* cursor, CH2* stop, FP4 item);
SDK CH2* Print(CH2* cursor, CH2* stop, FP8 item);
#endif

#if USING_UTF32 == YES
/* Returns the last UI1 in the given CH4. */
SDK CH1* LastByte(CH4* c);

/* Prints the given item to the socket. */
SDK CH4* Print(CH4* cursor, CH4* stop, FP4 value);
SDK CH4* Print(CH4* cursor, CH4* stop, FP8 value);
#endif

#endif

/* Utility function for use in templates to convert the given value to it's
unsigned equivalent. */
/*inline*/ UI1 ToUnsigned(CH1 value);
/*inline*/ UI2 ToUnsigned(CH2 value);
/*inline*/ UI4 ToUnsigned(CH4 value);
/*inline*/ UIN ToUnsigned(CHN value);
/*inline*/ UI1 ToUnsigned(SI1 value);
/*inline*/ UI2 ToUnsigned(SI2 value);
/*inline*/ UI4 ToUnsigned(SI4 value);
/*inline*/ UI8 ToUnsigned(SI8 value);
/*inline*/ UI1 ToUnsigned(UI1 value);
/*inline*/ UI2 ToUnsigned(UI2 value);
/*inline*/ UI4 ToUnsigned(UI4 value);
/*inline*/ UI8 ToUnsigned(UI8 value);
/*inline*/ UIW ToUnsigned(const void* value);
#if USING_FP4 == YES
/*inline*/ UI4 ToUnsigned(FP4 value);
#endif
#if USING_FP8 == YES
/*inline*/ UI8 ToUnsigned(FP8 value);
#endif

/* Utility function for use in templates to convert the given value to it's
signed equivalent. */
/*inline*/ SI1 ToSigned(CH1 value);
/*inline*/ SI2 ToSigned(CH2 value);
/*inline*/ SI4 ToSigned(CH4 value);
/*inline*/ SIN ToSigned(CHN value);
/*inline*/ SI1 ToSigned(UI1 value);
/*inline*/ SI2 ToSigned(UI2 value);
/*inline*/ SI4 ToSigned(UI4 value);
/*inline*/ SI8 ToSigned(UI8 value);
/*inline*/ SI1 ToSigned(SI1 value);
/*inline*/ SI2 ToSigned(SI2 value);
/*inline*/ SI4 ToSigned(SI4 value);
/*inline*/ SI8 ToSigned(SI8 value);
/*inline*/ SIW ToSigned(const void* value);
#if USING_FP4 == YES
/*inline*/ SI4 ToSigned(FP4 value);
#endif
#if USING_FP8 == YES
/*inline*/ SI8 ToSigned(FP8 value);
#endif

/* Utility class for printing a POD type in hex. */
class Hex {
 public:
  enum { kBufferSizeWords = 2 };

  /* Stores the given item to the buffer and store the size. */
  Hex(const void* item);
  Hex(const void* item, SIW size);
  Hex(SI1 item);
  Hex(UI1 item);
  Hex(SI2 item);
  Hex(UI2 item);
  Hex(SI4 item);
  Hex(UI4 item);
  Hex(SI8 item);
  Hex(UI8 item);
#if USING_FP4 == YES
  Hex(FP4 item);
#endif
#if USING_FP8 == YES
  Hex(FP8 item);
#endif

  /* Gets the begin of the socket. */
  const CH1* Begin();

  /* Gets the size of the socket. */
  SIW Size();

 private:
  UIW buffer_[kBufferSizeWords];  // The buffer with kSizeWords elements.
  SIW size_;                      //< Width of the item in bytes.
};

/* Utility class for printing a POD type in binary. */
class Binary {
 public:
  enum { kBufferSizeWords = 2 };

  /* Pushes the item out to RAM and stores the byte_count. */
  Binary(const void* item);
  Binary(const void* item, SIW size);
  Binary(SI1 item);
  Binary(UI1 item);
  Binary(SI2 item);
  Binary(UI2 item);
  Binary(SI4 item);
  Binary(UI4 item);
  Binary(SI8 item);
  Binary(UI8 item);
#if USING_FP4 == YES
  Binary(FP4 item);
#endif
#if USING_FP8 == YES
  Binary(FP8 item);
#endif

  /* Gets the begin of the socket. */
  const CH1* Begin();

  /* Gets the size of the socket. */
  SIW Size();

 private:
  UIW buffer_[kBufferSizeWords];
  SIW size_;  //< Width of the item in bytes.
};

}  // namespace _
#endif
