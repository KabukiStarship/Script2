/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/05.stack.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_STRAND
#include "../strand.hpp"
using namespace _;
#if SEAM == SCRIPT2_STRAND
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
#if SEAM >= SCRIPT2_STRAND
template <typename CHT = CHR, typename ISZ = ISN>
void TestStrandN() {
  static const CHT kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    cStrandLoopCount = 3,
    cCharSizeChar = '0' + sizeof(CHT),
  };

  AStrand<CHT, ISZ, 8> strand;
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

static const CHA* Strand(const CHA* args) {
#if SEAM >= SCRIPT2_STRAND
  A_TEST_BEGIN;

  TestStrandN<CHA, ISC>();
#if USING_UTF16 == YES_0
  TestStrandN<CHB, ISC>();
#endif
#if USING_UTF32 == YES_0
  TestStrandN<CHC, ISC>();
#endif

#endif
  return nullptr;
}
}  // namespace script2
