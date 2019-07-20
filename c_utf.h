/* SCRIPT Script @version 0.x
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

namespace _ {

/* Converts the given value to lowercase if it is uppercase. */
LIB_MEMBER CH1 ToLower(CH1 value);
LIB_MEMBER CH2 ToLower(CH2 value);
LIB_MEMBER CH4 ToLower(CH4 value);

/* Converts a UI1 a one-UI1 hex representation. */
LIB_MEMBER CH1 HexNibbleToUpperCase(UI1 b);

/* Gets the header to print for PrintChars(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintCharsHeader();

/* Gets the header to print for PrintChars(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintCharsBorder();

/* Gets the header to print for PrintHex(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintHexHeader();

/* Gets the header to print for PrintHex(const void*, const void*). */
LIB_MEMBER const CH1* STRPrintHexBorder();

/* Converts a UI1 a one-UI1 hex representation. */
LIB_MEMBER CH1 HexNibbleToLowerCase(UI1 b);

/* Converts a UI1 a two-UI1 hex representation. */
LIB_MEMBER UI2 HexByteToLowerCase(UI1 b);

/* Converts a UI1 a two-UI1 hex representation. */
LIB_MEMBER UI2 HexByteToUpperCase(UI1 b);

/* Converts a single hex UI1 a UI1.
@return Returns -1 if c is not a hex UI1. */
LIB_MEMBER SI4 HexToByte(CH1 hex_byte);

/* Converts a UI1 into a two-UI1 hex representation.
@return Returns -1 if c is not a hex UI1.
*/
LIB_MEMBER SI4 HexToByte(UI2 hex);

#if USING_UTF8 == YES_0

/* Converts a signed or unsigned CH1 to a (unsigned) cH4. */
LIB_INLINE CH4 ToCH4(CH1 c);

/* Prints a CH2 to the CH1* by converting it to a CH4.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
LIB_MEMBER CH1* Print(CH1* cursor, CH1* stop, CH1 c);
LIB_MEMBER CH1* Print(CH1* cursor, CH1* stop, CH2 c);
LIB_MEMBER CH1* Print(CH1* cursor, CH1* stop, CH4 c);
LIB_MEMBER CH1* Print(CH1* cursor, SIW size, CH4 c);

#endif

#if USING_UTF16 == YES_0

/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH12 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
LIB_MEMBER CH2* Print(CH2* cursor, CH2* stop, CH2 c);
LIB_MEMBER CH2* Print(CH2* cursor, CH2* stop, CH1 c);
LIB_MEMBER CH2* Print(CH2* cursor, CH2* stop, CH4 c);

LIB_MEMBER CH2* Print(CH2* cursor, SIW size, CH4 c);

/* Attempts to scan a UTF-32 CH1 from the given UTF-8 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
LIB_MEMBER const CH1* Scan(const CH1* string, CH4& result);

/* Attempts to scan a UTF-32 CH1 from the given UTF-16 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
LIB_MEMBER const CH2* Scan(const CH2* string, CH4& result);
#endif

#if USING_UTF32 == YES_0
/* Prints a Unicode Char to the given socket.
@return  Nil upon failure or a pointer to the nil-term Char upon success.
@param   cursor The beginning of the socket.
@param   stop   The last UI1 in the socket.
@param   c      The CH1 to utf.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
LIB_MEMBER CH4* Print(CH4* cursor, CH4* stop, CH1 c);
LIB_MEMBER CH4* Print(CH4* cursor, CH4* stop, CH2 c);
LIB_MEMBER CH4* Print(CH4* cursor, CH4* stop, CH4 c);

/* Attempts to scan a UTF-32 CH1 from the given UTF-32 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CH1 upon
success. */
LIB_MEMBER const CH4* Scan(const CH4* string, CH4& result);
#endif

#endif  //< #if SEAM >= SEAM_SCRIPT2_ITOS

}  // namespace _
