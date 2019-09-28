/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cout.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if USING_CONSOLE == YES_0

#ifndef SCRIPT2_COUT_H
#define SCRIPT2_COUT_H 1

#include "stringf.h"

namespace _ {

/* Utility class for printing to the stdout. */
class LIB_MEMBER COut {
 public:
  /* Prints nothing. */
  COut();

  /* Prints the given item to the COut stream. */
  COut(CH1 item);
  COut(const CH1* item);

#if USING_UTF16 == YES_0
  COut(CH2 item);
  COut(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  COut(CH4 item);
  COut(const CH4* item);
#endif
  COut(SI1 item);
  COut(UI1 item);
  COut(SI2 item);
  COut(UI2 item);
  COut(SI4 item);
  COut(UI4 item);
  COut(SI8 item);
  COut(UI8 item);
#if USING_FP4 == YES_0
  COut(FP4 item);
#endif
#if USING_FP8 == YES_0
  COut(FP8 item);
#endif
  COut(Hexf item);
  COut(Binaryf item);
  COut(Centerf item);
  COut(Rightf item);
  COut(Linef item);
  COut(Headingf item);
  COut(Indentf item);
  COut(Charsf item);

  /* Prints the given items to the COut stream. */
  COut(CH1 item, CH1 second_item);
  COut(CH1 item, const CH1* second_item);
  COut(const CH1* item, CH1 second_item);
  COut(const CH1* item, const CH1* second_item);
  COut(CH1 item, CH1 second_item, CH1 third_item);
  COut(CH1 item, CH1 second_item, const CH1* third_item);
  COut(const CH1* item, const CH1* second_item, CH1 third_item);
  COut(const CH1* item, const CH1* second_item, const CH1* third_item);

  /* Returns reference to this. */
  COut& Star();

  /* Prints the given item to the stdout. */
  COut& Print(CH1 item);
  COut& Print(const CH1* item);
#if USING_UTF16 == YES_0
  COut& Print(CH2 item);
  COut& Print(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  COut& Print(CH4 item);
  COut& Print(const CH4* item);
#endif
  COut& Print(SI4 item);
  COut& Print(UI4 item);
  COut& Print(SI8 item);
  COut& Print(UI8 item);
#if USING_FP4 == YES_0
  COut& Print(FP4 item);
#endif
#if USING_FP8 == YES_0
  COut& Print(FP8 item);
#endif
  COut& Print(Hexf& item);
  COut& Print(Binaryf& item);
  COut& Print(Centerf& item);
  COut& Print(Rightf& item);
  COut& Print(Linef& item);
  COut& Print(Headingf& item);
  COut& Print(Indentf& item);
  COut& Print(Charsf& item);

  /* Prints a new line followed by the given item to the stdout. */
  COut& NL();

  /* Prints a new line followed by the given item to the stdout. */
  COut& NL(CH1 item);
  COut& NL(const CH1* item);
#if USING_UTF16 == YES_0
  COut& NL(CH2 item);
  COut& NL(const CH2* item);
#endif
#if USING_UTF32 == YES_0
  COut& NL(CH4 item);
  COut& NL(const CH4* item);
#endif
  COut& NL(SI4 item);
  COut& NL(UI4 item);
  COut& NL(SI8 item);
  COut& NL(UI8 item);
#if USING_FP4 == YES_0
  COut& NL(FP4 item);
#endif
#if USING_FP8 == YES_0
  COut& NL(FP8 item);
#endif

  /* Stores the given item to the buffer and store the size. */
  COut& Hex(const void* item);
  COut& Hex(const void* item, SIW size);
  COut& Hex(const void* item, const void* item_stop);
  COut& Hex(SI1 item);
  COut& Hex(UI1 item);
  COut& Hex(SI2 item);
  COut& Hex(UI2 item);
  COut& Hex(SI4 item);
  COut& Hex(UI4 item);
  COut& Hex(SI8 item);
  COut& Hex(UI8 item);
#if USING_FP4 == YES_0
  COut& Hex(FP4 item);
#endif
#if USING_FP8 == YES_0
  COut& Hex(FP8 item);
#endif

  /* Stores the given item to the buffer and store the size. */
  COut& Binary(const void* item);
  COut& Binary(const void* item, SIW size);
  COut& Binary(const void* item, const void* item_stop);
  COut& Binary(SI1 item);
  COut& Binary(UI1 item);
  COut& Binary(SI2 item);
  COut& Binary(UI2 item);
  COut& Binary(SI4 item);
  COut& Binary(UI4 item);
  COut& Binary(SI8 item);
  COut& Binary(UI8 item);
#if USING_FP4 == YES_0
  COut& Binary(FP4 item);
#endif
#if USING_FP8 == YES_0
  COut& Binary(FP8 item);
#endif

  SIN PrintAndCount(const CH1* string);
#if USING_UTF16 == YES_0
  SIN PrintAndCount(const CH2* string);
#endif
#if USING_UTF32 == YES_0
  SIN PrintAndCount(const CH4* string);
#endif
};

/* Wrapper function for COut so you can use it more than once in a lexical
scope without delcaring COut cout. */
inline COut CPrint() { return COut(); }

/* Prints the given item to the COut. */
COut CPrint(CH1 item);
COut CPrint(const CH1* item);
#if USING_UTF16 == YES_0
COut CPrint(CH2 item);
COut CPrint(const CH2* item);
#endif
#if USING_UTF32 == YES_0
COut CPrint(CH4 item);
COut CPrint(const CH4* item);
#endif

COut CPrint(SI4 item);
COut CPrint(UI4 item);
COut CPrint(SI8 item);
COut CPrint(UI8 item);
#if USING_FP4 == YES_0
COut CPrint(FP4 item);
#endif
#if USING_FP8 == YES_0
COut CPrint(FP8 item);
#endif
COut CPrint(Hexf& item);
COut CPrint(Binaryf& item);
COut CPrint(Centerf& item);
COut CPrint(Rightf& item);
COut CPrint(Linef& item);
COut CPrint(Headingf& item);
COut CPrint(Indentf& item);

}  // namespace _

/* Prints the given item to the COut. */
_::COut& operator<<(_::COut& o, CH1 item);
_::COut& operator<<(_::COut& o, const CH1* item);

#if USING_UTF16 == YES_0
_::COut& operator<<(_::COut& o, CH2 item);
_::COut& operator<<(_::COut& o, const CH2* item);
#endif
#if USING_UTF32 == YES_0
_::COut& operator<<(_::COut& o, CH4 item);
_::COut& operator<<(_::COut& o, const CH4* item);
#endif
_::COut& operator<<(_::COut& o, SI4 item);
_::COut& operator<<(_::COut& o, UI4 item);
_::COut& operator<<(_::COut& o, SI8 item);
_::COut& operator<<(_::COut& o, UI8 item);
#if USING_FP4 == YES_0
_::COut& operator<<(_::COut& o, FP4 item);
#endif
#if USING_FP8 == YES_0
_::COut& operator<<(_::COut& o, FP8 item);
#endif
_::COut& operator<<(_::COut& o, _::Hexf item);
_::COut& operator<<(_::COut& o, _::Binaryf item);
_::COut& operator<<(_::COut& o, _::Centerf item);
_::COut& operator<<(_::COut& o, _::Rightf item);
_::COut& operator<<(_::COut& o, _::Linef item);
_::COut& operator<<(_::COut& o, _::Headingf item);
_::COut& operator<<(_::COut& o, _::Indentf item);
_::COut& operator<<(_::COut& o, _::Charsf item);
_::COut& operator<<(_::COut& o, _::COut item);
#endif
#endif
