/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/09.Loom.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_LOOM
#include "../Loom.hpp"
//
#include "TestWords.h"
using namespace _;
#if SEAM == SCRIPT2_LOOM
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif

namespace Script2 {
template<typename CHT = CHR, typename ISZ = ISN, typename ISY = ISN>
void TestLoom() {
  D_COUT(Linef("\n\n---\n\n"));

  enum {
    cSize = 192 * sizeof(CHT),
    cCount = 32,
  };
  D_COUT("Testing ALoom<CH" << TSizef<CHT>() << ",IS" << TSizef<ISZ>()
         << "> with cSize:" << cSize << " and cCount:" << cCount);

  ALoom<CHT, ISZ, ISY, cSize, TBUF<cSize>> loom(cCount);
#if D_THIS
  D_COUT("\nPrinting empty loom:\n");
  loom.COut();
#endif

  enum {
    cLengthMax = (cSize << 2) - 1,
  };

  CHT string[cLengthMax + 1];
  CHT* string_end = &string[cLengthMax];

  for (ISN i = 0; i < 32; ++i) {
    TSPrint<CHT>(string, string_end, i);
    A_AVOW(ISY(i), loom.Insert(string));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  TSPrint<CHT>(string, string_end, 32);
  A_AVOW(ISY(32), loom.Insert(string));

  for (ISN i = 33; i < 96; ++i) {
    TSPrint<CHT>(string, string_end, i);
    A_AVOW(ISY(i), loom.Insert(string));
  }

  TSPrint<CHT>(string, string_end, 96);
  A_AVOW(ISY(96), loom.Insert(string));

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  for (ISN i = 0; i < cLengthMax; ++i) string[i] = '*';

  string[cLengthMax] = 0;

  ISY index = loom.Insert(string);
#if D_THIS
  loom.COut();
#endif
  A_AVOW(ISY(97), index);

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

  A_AVOW(ISY(98), loom.Insert(d));

  A_AVOW(ISY(98), loom.Find(d));

  A_AVOW(ISY(99), loom.Insert(c));
  A_AVOW(ISY(98), loom.Find(d));
  A_AVOW(ISY(99), loom.Find(c));

  A_AVOW(ISY(100), loom.Insert(b));
  A_AVOW(ISY(98), loom.Find(d));
  A_AVOW(ISY(99), loom.Find(c));
  A_AVOW(ISY(100), loom.Find(b));

  A_AVOW(ISY(101), loom.Insert(a));
  A_AVOW(ISY(98), loom.Find(d));
  A_AVOW(ISY(99), loom.Find(c));
  A_AVOW(ISY(100), loom.Find(b));
  A_AVOW(ISY(101), loom.Find(a));

  A_AVOW(ISY(102), loom.Insert(abc));
  A_AVOW(ISY(102), loom.Find(abc));

  A_AVOW(ISY(103), loom.Insert(bac));
  A_AVOW(ISY(102), loom.Find(abc));
  A_AVOW(ISY(103), loom.Find(bac));

  A_AVOW(ISY(104), loom.Insert(cba));
  A_AVOW(ISY(102), loom.Find(abc));
  A_AVOW(ISY(103), loom.Find(bac));
  A_AVOW(ISY(104), loom.Find(cba));

  A_AVOW(ISY(105), loom.Insert(cab));
  A_AVOW(ISY(102), loom.Find(abc));
  A_AVOW(ISY(103), loom.Find(bac));
  A_AVOW(ISY(104), loom.Find(cba));
  A_AVOW(ISY(105), loom.Find(cab));

#if D_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  A_AVOW(ISY(-1), loom.Find(test));
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* Loom(const CHA* args) {
#if SEAM >= SCRIPT2_LOOM
  A_TEST_BEGIN;
  TestLoom<CHA, ISB, ISB>();
  TestLoom<CHA, ISC, ISC>();
#if USING_UTF16 == YES_0
  TestLoom<CHB, ISB, ISB>();
  TestLoom<CHB, ISC, ISC>();
#endif
#if USING_UTF32 == YES_0
  TestLoom<CHC, ISC, ISC>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
