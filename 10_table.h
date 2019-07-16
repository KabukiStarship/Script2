/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/08_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "t_table.h"

#if SEAM == SEAM_SCRIPT2_TABLE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename Char, typename SIZ>
void TestTable() {
  D_PRINTF("Testing ATable<CH%c,SI%c>\n\n", '0' + sizeof(Char),
           '0' + sizeof(SIZ));

  ATable<Char, SIZ> table;

#if DEBUG_THIS
  table.COut();
#endif

  static const Char a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                    d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                    bac[] = {'b', 'a', 'c', '\0'},
                    cba[] = {'c', 'b', 'a', '\0'},
                    cab[] = {'c', 'a', 'b', '\0'},
                    test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW((SIZ)0, table.Add(d));

  D_COUT_OBJ(table);

  A_AVOW((SIZ)0, table.Find(d));

  A_AVOW((SIZ)1, table.Add(c));
  A_AVOW((SIZ)0, table.Find(d));
  A_AVOW((SIZ)1, table.Find(c));

  A_AVOW((SIZ)2, table.Add(b));
  A_AVOW((SIZ)0, table.Find(d));
  A_AVOW((SIZ)1, table.Find(c));
  A_AVOW((SIZ)2, table.Find(b));

  A_AVOW((SIZ)3, table.Add(a));
  A_AVOW((SIZ)0, table.Find(d));
  A_AVOW((SIZ)1, table.Find(c));
  A_AVOW((SIZ)2, table.Find(b));
  A_AVOW((SIZ)3, table.Find(a));

  A_AVOW((SIZ)4, table.Add(abc));
  A_AVOW((SIZ)4, table.Find(abc));

  A_AVOW((SIZ)5, table.Add(bac));
  A_AVOW((SIZ)4, table.Find(abc));
  A_AVOW((SIZ)5, table.Find(bac));

  A_AVOW((SIZ)6, table.Add(cba));
  A_AVOW((SIZ)4, table.Find(abc));
  A_AVOW((SIZ)5, table.Find(bac));
  A_AVOW((SIZ)6, table.Find(cba));

  A_AVOW((SIZ)7, table.Add(cab));
  A_AVOW((SIZ)4, table.Find(abc));
  A_AVOW((SIZ)5, table.Find(bac));
  A_AVOW((SIZ)6, table.Find(cba));
  A_AVOW((SIZ)7, table.Find(cab));

  A_AVOW((SIZ)1, table.Add(a));
  A_AVOW((SIZ)1, table.Add(b));
  A_AVOW((SIZ)1, table.Add(c));
  A_AVOW((SIZ)1, table.Add(d));

  D_COUT_OBJ(table);
  A_AVOW((SIZ)-1, table.Find(test));
  D_PAUSE("");
}

static const CH1* _10_Table(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_TABLE
  A_TEST_BEGIN;

  TestTable<CH1, SI2>();
  TestTable<CH2, SI2>();
  TestTable<CH4, SI2>();
  TestTable<CH1, SI4>();
  TestTable<CH2, SI4>();
  TestTable<CH4, SI4>();
#endif
  return nullptr;
}
}  // namespace script2
