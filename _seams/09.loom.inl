/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/09.loom.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<cale-mccollough.github.io>>; all right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_LOOM
#include "../loom.hpp"
using namespace _;
#if SEAM == SCRIPT2_LOOM
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif

namespace script2 {
template <typename CHT = CHR, typename SIZ = SIN>
void TestLoom() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSize = 192 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ALoom<CH"
         << CHT('0' + sizeof(CHT)) << ",SI" << CHT('0' + sizeof(SIZ))
         << "> with cSize:" << cSize << " and cCount:cCount");

  ALoom<CHT, SIZ, cSize, TUIB<cSize>> loom(cCount);
#if D_THIS
  D_COUT("\nPrinting empty loom:\n");
  loom.COut();
#endif

  enum {
    cLengthMax = (cSize << 2) - 1,
  };

  CHT string[cLengthMax + 1];
  CHT* String_end = &string[cLengthMax];

  for (SIN i = 0; i < 32; ++i) {
    TSPrint<CHT>(string, String_end, i);
    A_AVOW((SIZ)i, loom.Insert(string));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  TSPrint<CHT>(string, String_end, 32);
  A_AVOW((SIZ)32, loom.Insert(string));

  for (SIN i = 33; i < 96; ++i) {
    TSPrint<CHT>(string, String_end, i);
    A_AVOW((SIZ)(i), loom.Insert(string));
  }

  TSPrint<CHT>(string, String_end, 96);
  A_AVOW((SIZ)96, loom.Insert(string));

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  for (SIN i = 0; i < cLengthMax; ++i) string[i] = '*';

  string[cLengthMax] = 0;

  SIZ index = loom.Insert(string);
#if D_THIS
  loom.COut();
#endif
  A_AVOW((SIZ)97, index);

#if D_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  D_COUT("\nTesting TLoomFind...\n");

  static const CHT a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                   d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                   bac[] = {'b', 'a', 'c', '\0'}, cba[] = {'c', 'b', 'a', '\0'},
                   cab[] = {'c', 'a', 'b', '\0'},
                   test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW((SIZ)98, loom.Insert(d));

  A_AVOW((SIZ)98, loom.Find(d));

  A_AVOW((SIZ)99, loom.Insert(c));
  A_AVOW((SIZ)98, loom.Find(d));
  A_AVOW((SIZ)99, loom.Find(c));

  A_AVOW((SIZ)100, loom.Insert(b));
  A_AVOW((SIZ)98, loom.Find(d));
  A_AVOW((SIZ)99, loom.Find(c));
  A_AVOW((SIZ)100, loom.Find(b));

  A_AVOW((SIZ)101, loom.Insert(a));
  A_AVOW((SIZ)98, loom.Find(d));
  A_AVOW((SIZ)99, loom.Find(c));
  A_AVOW((SIZ)100, loom.Find(b));
  A_AVOW((SIZ)101, loom.Find(a));

  A_AVOW((SIZ)102, loom.Insert(abc));
  A_AVOW((SIZ)102, loom.Find(abc));

  A_AVOW((SIZ)103, loom.Insert(bac));
  A_AVOW((SIZ)102, loom.Find(abc));
  A_AVOW((SIZ)103, loom.Find(bac));

  A_AVOW((SIZ)104, loom.Insert(cba));
  A_AVOW((SIZ)102, loom.Find(abc));
  A_AVOW((SIZ)103, loom.Find(bac));
  A_AVOW((SIZ)104, loom.Find(cba));

  A_AVOW((SIZ)105, loom.Insert(cab));
  A_AVOW((SIZ)102, loom.Find(abc));
  A_AVOW((SIZ)103, loom.Find(bac));
  A_AVOW((SIZ)104, loom.Find(cba));
  A_AVOW((SIZ)105, loom.Find(cab));

#if D_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  A_AVOW((SIZ)-1, loom.Find(test));
}
}  // namespace script2
#endif

namespace script2 {
static const CH1* Loom(const CH1* args) {
#if SEAM >= SCRIPT2_LOOM
  A_TEST_BEGIN;
  TestLoom<CH1, SI2>();
  TestLoom<CH1, SI4>();
#if USING_UTF16 == YES_0
  TestLoom<CH2, SI2>();
  TestLoom<CH2, SI4>();
#endif
#if USING_UTF32 == YES_0
  TestLoom<CH4, SI4>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
