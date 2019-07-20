/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/09_loom.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "t_loom.h"

#if SEAM == SEAM_SCRIPT2_LOOM
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename Char, typename SIZ>
void TestLoom() {
  D_COUT_LINEF("\n\n---\n\n");

  enum {
    kSize = 256 * sizeof(Char),
    kCount = 32,
  };
  D_PRINTF("Testing ALoom<CH%c,SI%c> with kSize:%i and kCount:%i",
           '0' + sizeof(Char), '0' + sizeof(SIZ), kSize, kCount);

  ALoom<Char, SIZ, kSize, TSocket<kSize>> loom(kCount);
#if DEBUG_THIS
  CPrint() << "\nPrinting empty loom:\n";
  loom.COut();
#endif

  enum {
    kLengthMax = kSize << 2 - 1,
  };

  Char string[kLengthMax + 1];
  Char* string_end = &string[kLengthMax];

  for (SIN i = 0; i < 32; ++i) {
    TPrint<Char>(string, string_end, i);
    A_AVOW((SIZ)i, loom.Add(string));
  }

  D_COUT("\n\nTesting Factory.Grow...\n");

  TPrint<Char>(string, string_end, 32);
  A_AVOW((SIZ)32, loom.Add(string));

  for (SIN i = 33; i < 96; ++i) {
    TPrint<Char>(string, string_end, i);
    A_AVOW((SIZ)(i), loom.Add(string));
  }

  TPrint<Char>(string, string_end, 96);
  A_AVOW((SIZ)96, loom.Add(string));

  D_COUT("\n\nAttmpeting to add a very large string...\n");

  for (SIN i = 0; i < kLengthMax; ++i) string[i] = '*';

  string[kLengthMax] = 0;

  SIZ index = loom.Add(string);
#if DEBUG_THIS
  loom.COut();
#endif
  A_AVOW((SIZ)97, index);

#if DEBUG_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  D_COUT("\nTesting TLoomFind...\n");

  static const Char a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                    d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                    bac[] = {'b', 'a', 'c', '\0'},
                    cba[] = {'c', 'b', 'a', '\0'},
                    cab[] = {'c', 'a', 'b', '\0'},
                    test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW((SIZ)98, loom.Add(d));

  A_AVOW((SIZ)98, loom.Find(d));

  A_AVOW((SIZ)99, loom.Add(c));
  A_AVOW((SIZ)98, loom.Find(d));
  A_AVOW((SIZ)99, loom.Find(c));

  A_AVOW((SIZ)100, loom.Add(b));
  A_AVOW((SIZ)98, loom.Find(d));
  A_AVOW((SIZ)99, loom.Find(c));
  A_AVOW((SIZ)100, loom.Find(b));

  A_AVOW((SIZ)101, loom.Add(a));
  A_AVOW((SIZ)98, loom.Find(d));
  A_AVOW((SIZ)99, loom.Find(c));
  A_AVOW((SIZ)100, loom.Find(b));
  A_AVOW((SIZ)101, loom.Find(a));

  A_AVOW((SIZ)102, loom.Add(abc));
  A_AVOW((SIZ)102, loom.Find(abc));

  A_AVOW((SIZ)103, loom.Add(bac));
  A_AVOW((SIZ)102, loom.Find(abc));
  A_AVOW((SIZ)103, loom.Find(bac));

  A_AVOW((SIZ)104, loom.Add(cba));
  A_AVOW((SIZ)102, loom.Find(abc));
  A_AVOW((SIZ)103, loom.Find(bac));
  A_AVOW((SIZ)104, loom.Find(cba));

  A_AVOW((SIZ)105, loom.Add(cab));
  A_AVOW((SIZ)102, loom.Find(abc));
  A_AVOW((SIZ)103, loom.Find(bac));
  A_AVOW((SIZ)104, loom.Find(cba));
  A_AVOW((SIZ)105, loom.Find(cab));

#if DEBUG_THIS
  D_COUT('\n');
  loom.COut();
  D_COUT('\n');
#endif

  A_AVOW((SIZ)-1, loom.Find(test));
}

static const CH1* _09_Loom(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_LOOM
  A_TEST_BEGIN;
  TestLoom<CH1, SI2>();
  TestLoom<CH2, SI2>();
  TestLoom<CH1, SI4>();
  TestLoom<CH2, SI4>();
  // TestLoom<CH4, SI4>();
#endif
  return nullptr;
}
}  // namespace script2
