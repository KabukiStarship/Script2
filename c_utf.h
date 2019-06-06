/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_utf.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_CBINARY
#define SCRIPT2_CBINARY 1

#include "c_puff.h"

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

#if SEAM >= SCRIPT2_SEAM_ITOS

/* Utility function for casting a sign to an unsigned in templates. */
UI1 Unsigned(SI1 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI2 Unsigned(SI2 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI4 Unsigned(SI4 value);

/* Utility function for casting a sign to an unsigned in templates. */
UI8 Unsigned(SI8 value);

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

#if USING_FP4
/* Scans a FP4 from the given .
@return Nil if the  doesn't begin with a FP4. */
const CH1* Scan(const CH1* cursor, FP4& value);
#endif
#if USING_FP8
/* Scans a FP8 from the given .
@return Nil if the  doesn't begin with a FP8. */
const CH1* Scan(const CH1* cursor, FP8& value);
#endif
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

#endif  //< #if SEAM >= SCRIPT2_SEAM_ITOS

/* Utility function for use in templates to convert the given value to it's
unsigned equivalent. */
/*inline*/ UI1 ToUnsigned(CH1 value);
/*inline*/ UI2 ToUnsigned(CH2 value);
/*inline*/ UI4 ToUnsigned(CH4 value);
/*inline*/ UIN ToUnsigned(CH4 value);
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
/*inline*/ SIN ToSigned(CH4 value);
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
