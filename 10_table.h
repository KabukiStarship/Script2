/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/10_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "t_table.h"

#if SEAM == SCRIPT2_TABLE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename SIZ, typename HSH, typename Char>
void TestTable() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting ATable<SI")
         << Char('0' + sizeof(SIZ)) << ",UI" << Char('0' + sizeof(HSH)) << ",CH"
         << Char('0' + sizeof(Char)) << ">\n"
         << Linef("+---\n"));

  ATable<SIZ, HSH, Char> table;

  static const Char a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                    d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                    bac[] = {'b', 'a', 'c', '\0'},
                    cba[] = {'c', 'b', 'a', '\0'},
                    cab[] = {'c', 'a', 'b', '\0'},
                    test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW((SIZ)0, table.Add(a));

  A_AVOW((SIZ)0, table.Find(a));

  A_AVOW((SIZ)1, table.Add(b));
  A_AVOW((SIZ)0, table.Find(a));
  A_AVOW((SIZ)1, table.Find(b));

  A_AVOW((SIZ)2, table.Add(c));
  A_AVOW((SIZ)0, table.Find(a));
  A_AVOW((SIZ)1, table.Find(b));
  A_AVOW((SIZ)2, table.Find(c));

  A_AVOW((SIZ)3, table.Add(d));
  A_AVOW((SIZ)0, table.Find(a));
  A_AVOW((SIZ)1, table.Find(b));
  A_AVOW((SIZ)2, table.Find(c));
  A_AVOW((SIZ)3, table.Find(d));

  A_AVOW((SIZ)-1, table.Add(a));
  A_AVOW((SIZ)-1, table.Add(b));
  A_AVOW((SIZ)-1, table.Add(c));
  A_AVOW((SIZ)-1, table.Add(d));

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

  D_COUT_OBJ(table);
  A_AVOW((SIZ)-1, table.Find(test));

  // D_PAUSE("");
}

static const CH1* _10_Table(const CH1* args) {
#if SEAM >= SCRIPT2_TABLE
  A_TEST_BEGIN;

  TestTable<SI2, UI2, CH1>();
  TestTable<SI4, UI4, CH1>();
#if USING_UTF16 == YES_0
  TestTable<SI2, UI2, CH2>();
  TestTable<SI4, UI4, CH2>();
#endif
#if USING_UTF32 == YES_0
  TestTable<SI2, UI2, CH4>();
  TestTable<SI4, UI4, CH4>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
