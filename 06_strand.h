/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/05_stack.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "t_stack.h"

#if SEAM == SCRIPT2_6
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

#if SEAM >= SCRIPT2_6
namespace script2 {
template <typename Char>
void _06_StrandN() {
  PRINTF("\n\nTesting TStrand<CH%c>\n\n", '0' + sizeof(Char));

  static const Char kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    kStrandLoopCount = 3,
    kCharSizeChar = '0' + sizeof(Char),
  };

  PRINT("\n\nExpecting \"");
  PRINT(kTesting123);
  PRINT("\"\n");
  TStrand<Char, 8> strand;
  strand.PrintConstants();
  strand.Wipe();
  PRINT("\n\nPrinting:\"Testing \"");
  strand << "Testing ";
  PRINT("\n\nPrinting:\"1\"");
  strand << 1;
  PRINT("\n\nPrinting:\", \"");
  strand << ", ";
  PRINT("\n\nPrinting:\"2\"");
  strand << 2;
  PRINT("\n\nPrinting:\", \"");
  strand << ", ";
  PRINT("\n\nPrinting:\"3\"");
  strand << 3;
  PRINT("\n\nPrinting:\".\"");
  strand << '.';
  PRINTF("\n\nResult:\"");
  PRINT(strand.Start());
  PRINT("\"\n");
  PRINT_CHARS(strand.AObj().Begin(), strand.AObj().Size());

  const Char* cursor = strand.Find(kTesting123);
  ASSERT(cursor);
}
#endif  //< #if SEAM >= SCRIPT2_6

static const CH1* _06_Strand(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_6
  TEST_BEGIN;

  PRINT("\n\nTesting TStrand<>...\n");

  _06_StrandN<CH1>();
  _06_StrandN<CH2>();
  _06_StrandN<CH4>();

#endif
  return nullptr;
}
}  //< namespace script2