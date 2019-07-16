/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_cin.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if USING_CONSOLE == YES

#ifndef SCRIPT2_C_CIN
#define SCRIPT2_C_CIN 1

#include "c_cout.h"

namespace _ {

/* Checks if the given string is yes or no.
@return -1 if no, 1 if yes, and 0 if neither. */
LIB_MEMBER SIN IsYesNo(const CH1* string);
LIB_MEMBER SIN IsYesNo(const CH2* string);
LIB_MEMBER SIN IsYesNo(const CH4* string);

/* Utility class for scanning types with operator overloads.
@code
SI4 a;
FL4 b;
CIn cin;
COut("\n\nEnter a value 0-1,000,000").Star() << cin.Scan(a)
@endcode
*/
class LIB_MEMBER CIn {
  char buffer_[24];  //< Buffer for scanning numbers and short strings.

 public:
  enum {
    kStateSuccess = 0,     //< State 0: Completed scanning.
    kStateBaseSign,        //< State 1: Scanning base sign.
    kStateBaseValue,       //< State 2: Scanning base value.
    kStateDotOrExponent,   //< State 3: Scanning '.', 'e', or 'E'.
    kStateFractionalPart,  //< State 4: Scanning the fraction part.
    kStateExponentSign,    //< State 4: Scanning exponent sign.
    kStateExponentValue,   //< State 5: Scanning exponent value.
  };

  enum {
    kBufferSizeMin = 2,  //< This min size of a string buffer.
  };

  /* Pauses until any key is pressed. */
  CIn();

#if USING_UTF8 == YES
  CIn(CH1& result);
  /* CIns a string with a larger buffer than the */
  CIn(CH1* result, SIW buffer_size);
#endif
#if USING_UTF16 == YES
  CIn(CH2& result);
  CIn(CH2* result, SIW buffer_size);
#endif
#if USING_UTF32 == YES
  CIn(CH4& result);
  CIn(CH4* result, SIW buffer_size);
#endif

  /* Scans the given item to the CIn stream. */
  CIn(SI1& result);
  CIn(UI1& result);
  CIn(SI2& result);
  CIn(UI2& result);
  CIn(SI4& result);
  CIn(UI4& result);
  CIn(SI8& result);
  CIn(UI8& result);
#if USING_FP4 == YES
  CIn(FP4& result);
#endif
#if USING_FP8 == YES
  CIn(FP8& result);
#endif

#if USING_UTF8 == YES
  /* Reads the character from the CIn stream. */
  static LIB_MEMBER BOL Scan(CH1& result);

  /* Reads the string with the given buffer_size from the CIn stream. */
  static LIB_MEMBER BOL Scan(CH1* result, SIW buffer_size);
#endif
#if USING_UTF16 == YES
  /* Reads the character from the CIn stream. */
  static LIB_MEMBER BOL Scan(CH2& result);

  /* Reads the string with the given buffer_size from the CIn stream. */
  static LIB_MEMBER BOL Scan(CH2* result, SIW buffer_size);
#endif
#if USING_UTF32 == YES
  /* Reads the character from the CIn stream. */
  static LIB_MEMBER BOL Scan(CH4& result);

  /* Reads the string with the given buffer_size from the CIn stream. */
  static LIB_MEMBER BOL Scan(CH4* result, SIW buffer_size);
#endif

  /* Reads the value from the CIn stream. */
  static LIB_MEMBER BOL Scan(SI1& result);
  static LIB_MEMBER BOL Scan(UI1& result);
  static LIB_MEMBER BOL Scan(SI2& result);
  static LIB_MEMBER BOL Scan(UI2& result);
  static LIB_MEMBER BOL Scan(SI4& result);
  static LIB_MEMBER BOL Scan(UI4& result);
  static LIB_MEMBER BOL Scan(SI8& result);
  static LIB_MEMBER BOL Scan(UI8& result);
#if USING_FP4 == YES
  static LIB_MEMBER BOL Scan(FP4& result);
#endif
#if USING_FP8 == YES
  static LIB_MEMBER BOL Scan(FP8& result);
#endif

  /* Reads the current key depressed on the keyboard.
  @return A negative number_ (typically 1) if no keys are pressed. */
  static LIB_MEMBER SIN GetKey();

  /* Spin waits for the user to press a keyboard key.
  @return The key the user pressed. */
  static LIB_MEMBER SIN ScanKey();

  /* Converts SI4 main(SI4,CH1**) arguments back into a string.
  @return nil if there are no arguments or the args string upon success.
  @param arg_count The number_ of arguments.
  @param args      The arguments. */
  static LIB_MEMBER const CH1* Args(SIN arg_count, CH1** args);
};

/* Prints a formatted string to the console and then pauses for the user to
press any key to continue. */
struct LIB_MEMBER Pausef {
  Pausef();
  Pausef(const CH1* format, ...);
};
}  // namespace _

::_::COut& operator<<(::_::COut& o, ::_::CIn& i);

::_::COut& operator<<(::_::COut& o, ::_::Pausef& i);

#endif
#endif
