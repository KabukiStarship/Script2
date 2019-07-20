/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/05_stack.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "t_strand.h"

#if SEAM == SEAM_SCRIPT2_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
#if SEAM >= SEAM_SCRIPT2_STRAND
template <typename Char>
void _06_StrandN() {
  D_COUT_LINEF('-');
  D_PRINTF("Testing TStrand<CH%c>\n\n", '0' + sizeof(Char));

  static const Char kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    kStrandLoopCount = 3,
    kCharSizeChar = '0' + sizeof(Char),
  };

  D_COUT("\n\nExpecting \"");
  D_COUT(kTesting123);
  D_COUT("\"\n");
  AStrand<Char, 8> strand;
  D_COUT("\nPrinting newly constructed strand:\n");
#if DEBUG_THIS
  strand.PrintTo<COut>(COut().Star());
#endif
  D_COUT("\n\nPrinting:\"Testing \"");
  strand << "Testing ";
  D_COUT("\n\nPrinting:\"1\"");
  strand << 1;
  D_COUT("\n\nPrinting:\", \"");
  strand << ", ";
  D_COUT("\n\nPrinting:\"2\"");
  strand << 2;
  D_COUT("\n\nPrinting:\", \"");
  strand << ", ";
  D_COUT("\n\nPrinting:\"3\"");
  strand << 3;
  D_COUT("\n\nPrinting:\".\"");
  strand << '.';
  D_PRINTF("\n\nResult:\"");
  D_COUT(strand.Start());
  D_COUT("\"\n");
  // D_COUT_CHARS(strand.ARY().Begin(), strand.ARY().Size());

  const Char* cursor = strand.Find(kTesting123);
  A_ASSERT(cursor);
  D_PRINTF("\nDone testing TStrand<CH%c>\n\n", '0' + sizeof(Char));
}
#endif  //< #if SEAM >= SEAM_SCRIPT2_STRAND

static const CH1* _06_Strand(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_STRAND
  A_TEST_BEGIN;

  _06_StrandN<CH1>();
  //_06_StrandN<CH2>();
  //_06_StrandN<CH4>();

#endif
  return nullptr;
}
}  // namespace script2
