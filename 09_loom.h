/* Script^2 @version 0.x
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

#if SEAM == SCRIPT2_SEAM_LOOM
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename Char, typename SIZ>
void TestLoom() {
  PRINT_LINEF("\n\n---\n\n");

  enum {
    kSize = 256 * sizeof(Char),
    kCount = 32,
  };
  PRINTF("Testing ALoom<CH%c,SI%c> with kSize:%i and kCount:%i",
         '0' + sizeof(Char), '0' + sizeof(SIZ), kSize, kCount);

  ALoom<Char, SIZ, kSize, TSocket<kSize>> loom(kCount);
#if DEBUG_SEAM
  Print("\nPrinting empty loom:\n");
  loom.COut();
#endif

  enum {
    kLengthMax = kSize << 2 - 1,
  };

  Char string[kLengthMax + 1];
  Char* string_end = &string[kLengthMax];

  for (SIN i = 0; i < 32; ++i) {
    Print(string, string_end, i);
    AVOW((SIZ)i, loom.Add(string));
  }

  PRINT("\n\nTesting Factory.Grow...\n");

  Print(string, string_end, 32);
  AVOW((SIZ)32, loom.Add(string));

  for (SIN i = 33; i < 96; ++i) {
    Print(string, string_end, i);
    AVOW((SIZ)(i), loom.Add(string));
  }

  Print(string, string_end, 96);
  AVOW((SIZ)96, loom.Add(string));

  PRINT("\n\nAttmpeting to add a very large string...\n");

  for (SIN i = 0; i < kLengthMax; ++i) string[i] = '*';

  string[kLengthMax] = 0;

  SIZ index = loom.Add(string);
#if DEBUG_SEAM
  loom.COut();
#endif
  AVOW((SIZ)97, index);

#if DEBUG_SEAM
  PRINT('\n');
  loom.COut();
  PRINT('\n');
#endif

  PRINT("\nTesting TLoomFind...\n");

  static const Char a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                    d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                    bac[] = {'b', 'a', 'c', '\0'},
                    cba[] = {'c', 'b', 'a', '\0'},
                    cab[] = {'c', 'a', 'b', '\0'},
                    test[] = {'t', 'e', 's', 't', '\0'};

  AVOW((SIZ)98, loom.Add(d));

  AVOW((SIZ)98, loom.Find(d));

  AVOW((SIZ)99, loom.Add(c));
  AVOW((SIZ)98, loom.Find(d));
  AVOW((SIZ)99, loom.Find(c));

  AVOW((SIZ)100, loom.Add(b));
  AVOW((SIZ)98, loom.Find(d));
  AVOW((SIZ)99, loom.Find(c));
  AVOW((SIZ)100, loom.Find(b));

  AVOW((SIZ)101, loom.Add(a));
  AVOW((SIZ)98, loom.Find(d));
  AVOW((SIZ)99, loom.Find(c));
  AVOW((SIZ)100, loom.Find(b));
  AVOW((SIZ)101, loom.Find(a));

  AVOW((SIZ)102, loom.Add(abc));
  AVOW((SIZ)102, loom.Find(abc));

  AVOW((SIZ)103, loom.Add(bac));
  AVOW((SIZ)102, loom.Find(abc));
  AVOW((SIZ)103, loom.Find(bac));

  AVOW((SIZ)104, loom.Add(cba));
  AVOW((SIZ)102, loom.Find(abc));
  AVOW((SIZ)103, loom.Find(bac));
  AVOW((SIZ)104, loom.Find(cba));

  AVOW((SIZ)105, loom.Add(cab));
  AVOW((SIZ)102, loom.Find(abc));
  AVOW((SIZ)103, loom.Find(bac));
  AVOW((SIZ)104, loom.Find(cba));
  AVOW((SIZ)105, loom.Find(cab));

#if DEBUG_SEAM
  PRINT('\n');
  loom.COut();
  PRINT('\n');
#endif

  AVOW((SIZ)-1, loom.Find(test));
}

static const CH1* _09_Loom(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_SEAM_LOOM
  TEST_BEGIN;
  TestLoom<CH1, SI2>();
  TestLoom<CH2, SI2>();
  TestLoom<CH1, SI4>();
  TestLoom<CH2, SI4>();
  TestLoom<CH4, SI4>();
#endif
  return nullptr;
}
}  // namespace script2
