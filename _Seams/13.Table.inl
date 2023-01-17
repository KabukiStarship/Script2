/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/13.Table.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_TABLE
#include "../Table.hpp"
using namespace _;
#if SEAM == SCRIPT2_TABLE
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#define TPARAMS CHT, ISZ, ISY, HSH
#define TARGS \
  typename CHT = CHR, typename ISZ = ISN, typename ISY = ISM, typename HSH = IUN

namespace Script2 {

template <TARGS>
void TestTable() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting ATable<IS")
         << CHT('@' + sizeof(ISZ)) << ",IU" << CHT('0' + sizeof(HSH)) << ",CH"
         << CHT('@' + sizeof(CHT)) << ">\n"
         << Linef("+---\n\n"));

  ATable<TPARAMS> table;

  static const CHT a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                   d[] = {'D', '\0'}, abc[] = {'a', 'b', 'c', '\0'},
                   bac[] = {'b', 'a', 'c', '\0'}, cba[] = {'c', 'b', 'a', '\0'},
                   cab[] = {'c', 'a', 'b', '\0'},
                   test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW((ISY)0, table.Add(a));

  A_AVOW((ISY)0, table.Find(a));

  A_AVOW((ISY)1, table.Add(b));
  A_AVOW((ISY)0, table.Find(a));
  A_AVOW((ISY)1, table.Find(b));

  A_AVOW((ISY)2, table.Add(c));
  A_AVOW((ISY)0, table.Find(a));
  A_AVOW((ISY)1, table.Find(b));
  A_AVOW((ISY)2, table.Find(c));

  A_AVOW((ISY)3, table.Add(d));
  A_AVOW((ISY)0, table.Find(a));
  A_AVOW((ISY)1, table.Find(b));
  A_AVOW((ISY)2, table.Find(c));
  A_AVOW((ISY)3, table.Find(d));

  A_AVOW(CInvalidIndex<ISY>(), table.Add(a));
  A_AVOW(CInvalidIndex<ISY>(), table.Add(b));
  A_AVOW(CInvalidIndex<ISY>(), table.Add(c));
  A_AVOW(CInvalidIndex<ISY>(), table.Add(d));

  A_AVOW((ISY)4, table.Add(abc));
  A_AVOW((ISY)4, table.Find(abc));

  A_AVOW((ISY)5, table.Add(bac));
  A_AVOW((ISY)4, table.Find(abc));
  A_AVOW((ISY)5, table.Find(bac));

  A_AVOW((ISY)6, table.Add(cba));
  A_AVOW((ISY)4, table.Find(abc));
  A_AVOW((ISY)5, table.Find(bac));
  A_AVOW((ISY)6, table.Find(cba));

  A_AVOW((ISY)7, table.Add(cab));
  A_AVOW((ISY)4, table.Find(abc));
  A_AVOW((ISY)5, table.Find(bac));
  A_AVOW((ISY)6, table.Find(cba));
  A_AVOW((ISY)7, table.Find(cab));

  D_COUT_OBJ(table);
  A_AVOW(CInvalidIndex<ISY>(), table.Find(test));

  // D_PAUSE("");
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* Table(const CHA* args) {
#if SEAM >= SCRIPT2_TABLE
  A_TEST_BEGIN;

  TestTable<CHA, ISB, IUB>();
  TestTable<CHA, ISC, IUC>();
#if USING_UTF16 == YES_0
  TestTable<CHB, ISB, IUB>();
  TestTable<CHB, ISC, IUC>();
#endif
#if USING_UTF32 == YES_0
  TestTable<CHC, ISB, IUB>();
  TestTable<CHC, ISC, IUC>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
#undef TARGS
#undef TPARAMS
