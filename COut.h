/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /COut.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_COUT_DECL
#define SCRIPT2_COUT_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0
#include "Stringf.h"
namespace _ {

/* Returns true if the item is printable*/
BOL CIsPrintable(CHA item);
BOL CIsPrintable(CHB item);
BOL CIsPrintable(CHC item);

/* Utility class for printing to the stdout. */
class LIB_MEMBER COut {
 public:
  /* Prints nothing. */
  COut();

  /* Prints the given item to the COut stream. */
  COut(CHA item);
  COut(const CHA* item);

#if USING_UTF16 == YES_0
  COut(CHB item);
  COut(const CHB* item);
#endif
#if USING_UTF32 == YES_0
  COut(CHC item);
  COut(const CHC* item);
#endif
  COut(ISA item);
  COut(IUA item);
  COut(ISB item);
  COut(IUB item);
  COut(ISC item);
  COut(IUC item);
  COut(ISD item);
  COut(IUD item);
#if USING_FPC == YES_0
  COut(FPC item);
#endif
#if USING_FPD == YES_0
  COut(FPD item);
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
  COut(CHA item, CHA second_item);
  COut(CHA item, const CHA* second_item);
  COut(const CHA* item, CHA second_item);
  COut(const CHA* item, const CHA* second_item);
  COut(CHA item, CHA second_item, CHA third_item);
  COut(CHA item, CHA second_item, const CHA* third_item);
  COut(const CHA* item, const CHA* second_item, CHA third_item);
  COut(const CHA* item, const CHA* second_item, const CHA* third_item);

  /* Returns reference to this. */
  COut& Star();

  /* Prints the given item to the stdout. */
  COut& Print(CHA item);
  COut& Print(const CHA* item);
#if USING_UTF16 == YES_0
  COut& Print(CHB item);
  COut& Print(const CHB* item);
#endif
#if USING_UTF32 == YES_0
  COut& Print(CHC item);
  COut& Print(const CHC* item);
#endif
  COut& Print(ISC item);
  COut& Print(IUC item);
  COut& Print(ISD item);
  COut& Print(IUD item);
#if USING_FPC == YES_0
  COut& Print(FPC item);
#endif
#if USING_FPD == YES_0
  COut& Print(FPD item);
#endif
  COut& Print(Hexf& item);
  COut& Print(Binaryf& item);
  COut& Print(Centerf& item);
  COut& Print(Rightf& item);
  COut& Print(Linef& item);
  COut& Print(Headingf& item);
  COut& Print(Indentf& item);
  COut& Print(Charsf& item);
  //COut& Print(TypeWordValue item);

  /* Prints a new line followed by the given item to the stdout. */
  COut& NL();

  /* Prints a new line followed by the given item to the stdout. */
  COut& NL(CHA item);
  COut& NL(const CHA* item);
#if USING_UTF16 == YES_0
  COut& NL(CHB item);
  COut& NL(const CHB* item);
#endif
#if USING_UTF32 == YES_0
  COut& NL(CHC item);
  COut& NL(const CHC* item);
#endif
  COut& NL(ISC item);
  COut& NL(IUC item);
  COut& NL(ISD item);
  COut& NL(IUD item);
#if USING_FPC == YES_0
  COut& NL(FPC item);
#endif
#if USING_FPD == YES_0
  COut& NL(FPD item);
#endif

  /* Stores the given item to the boofer and store the size. */
  COut& Hex(const void* item);
  COut& Hex(const void* item, ISW size);
  COut& Hex(const void* item, const void* item_stop);
  COut& Hex(ISA item);
  COut& Hex(IUA item);
  COut& Hex(ISB item);
  COut& Hex(IUB item);
  COut& Hex(ISC item);
  COut& Hex(IUC item);
  COut& Hex(ISD item);
  COut& Hex(IUD item);
#if USING_FPC == YES_0
  COut& Hex(FPC item);
#endif
#if USING_FPD == YES_0
  COut& Hex(FPD item);
#endif

  /* Stores the given item to the boofer and store the size. */
  COut& Binary(const void* item);
  COut& Binary(const void* item, ISW size);
  COut& Binary(const void* item, const void* item_stop);
  COut& Binary(ISA item);
  COut& Binary(IUA item);
  COut& Binary(ISB item);
  COut& Binary(IUB item);
  COut& Binary(ISC item);
  COut& Binary(IUC item);
  COut& Binary(ISD item);
  COut& Binary(IUD item);
#if USING_FPC == YES_0
  COut& Binary(FPC item);
#endif
#if USING_FPD == YES_0
  COut& Binary(FPD item);
#endif

  ISN PrintAndCount(const CHA* string);
#if USING_UTF16 == YES_0
  ISN PrintAndCount(const CHB* string);
#endif
#if USING_UTF32 == YES_0
  ISN PrintAndCount(const CHC* string);
#endif
};

// Returns the standard conole out.
inline COut& StdOut();

/* Wrapper function for COut so you can use it more than once in a lexical
scope without delcaring COut cout.
inline COut CPrint() { return COut(); } */

/* Prints the given item to the COut. */
COut CPrint(CHA item);
COut CPrint(const CHA* item);
#if USING_UTF16 == YES_0
COut CPrint(CHB item);
COut CPrint(const CHB* item);
#endif
#if USING_UTF32 == YES_0
COut CPrint(CHC item);
COut CPrint(const CHC* item);
#endif

COut CPrint(ISC item);
COut CPrint(IUC item);
COut CPrint(ISD item);
COut CPrint(IUD item);
#if USING_FPC == YES_0
COut CPrint(FPC item);
#endif
#if USING_FPD == YES_0
COut CPrint(FPD item);
#endif
COut CPrint(Hexf& item);
COut CPrint(Binaryf& item);
COut CPrint(Centerf& item);
COut CPrint(Rightf& item);
COut CPrint(Linef& item);
COut CPrint(Headingf& item);
COut CPrint(Indentf& item);

}  //< namespace _

/* Prints the given item to the COut. */
inline _::COut& operator<<(_::COut& o, CHA item);
inline _::COut& operator<<(_::COut& o, const CHA* item);

#if USING_UTF16 == YES_0
inline _::COut& operator<<(_::COut& o, CHB item);
inline _::COut& operator<<(_::COut& o, const CHB* item);
#endif
#if USING_UTF32 == YES_0
inline _::COut& operator<<(_::COut& o, CHC item);
inline _::COut& operator<<(_::COut& o, const CHC* item);
#endif
inline _::COut& operator<<(_::COut& o, ISC item);
inline _::COut& operator<<(_::COut& o, IUC item);
inline _::COut& operator<<(_::COut& o, ISD item);
inline _::COut& operator<<(_::COut& o, IUD item);
#if USING_FPC == YES_0
inline _::COut& operator<<(_::COut& o, FPC item);
#endif
#if USING_FPD == YES_0
inline _::COut& operator<<(_::COut& o, FPD item);
#endif
inline _::COut& operator<<(_::COut& o, _::Hexf item);
inline _::COut& operator<<(_::COut& o, _::Binaryf item);

inline _::COut& operator<<(_::COut& o, _::Headingf item);
#if SEAM >= SCRIPT2_UNIPRINTER
inline _::COut& operator<<(_::COut& o, _::Centerf item);
inline _::COut& operator<<(_::COut& o, _::Rightf item);
inline _::COut& operator<<(_::COut& o, _::Linef item);
inline _::COut& operator<<(_::COut& o, _::Indentf item);
inline _::COut& operator<<(_::COut& o, _::Charsf item);
inline _::COut& operator<<(_::COut& o, _::Sizef item);
inline _::COut& operator<<(_::COut& o, _::ATypef item);
//inline _::COut& operator<<(_::COut& o, _::TypeWordValue item);
inline _::COut& operator<<(_::COut& o, _::COut& item);
#endif
#endif
#endif
