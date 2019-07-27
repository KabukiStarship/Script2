/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/05_stack.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "t_strand.h"

#if SEAM == SCRIPT2_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
#if SEAM >= SCRIPT2_STRAND
template <typename Char, typename SIZ>
void _06_StrandN() {
  static const Char kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    kStrandLoopCount = 3,
    kCharSizeChar = '0' + sizeof(Char),
  };

  AStrand<Char, SIZ, 8> strand;
  D_COUT_OBJ(strand);
  D_COUT("\nbuffer_size:" << strand.Array().Size() << " buffer_size_bytes:"
                          << strand.Array().SizeBytes() << " buffer_size_words:"
                          << strand.Array().SizeWords());
  D_COUT("\n\nExpecting \""
         << kTesting123 << "\"\n\nThe first print function should fail...\n");

  strand << "Testing " << 1 << ", " << 2 << ", " << 3 << '.';
  D_COUT("\n\nResult:\"" << strand.Start() << "\"\n");
  A_ASSERT(strand.Find(kTesting123));
}
#endif

static const CH1* _06_Strand(const CH1* args) {
#if SEAM >= SCRIPT2_STRAND
  A_TEST_BEGIN;

  _06_StrandN<CH1, SI4>();
#if USING_UTF16 == YES_0
  _06_StrandN<CH2, SI4>();
#endif
#if USING_UTF32 == YES_0
  _06_StrandN<CH4, SI4>();
#endif

#endif
  return nullptr;
}
}  // namespace script2
