/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/13.Table.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_TABLE
#include "../Table.hpp"
using namespace _;
#if SEAM == SCRIPT2_TABLE
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
namespace Script2 {

template<TBL_A>
void TestTable() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting ATable<IS")
         << CSizef<ISZ>() << ",IU" << CSizef<HSH>() << ",CH"
         << CSizef<CHT>() << ">\n"
         << Linef("+---\n\n"));

  ATable<TBL_P> table;
  const TBL* This = table.This();

  static const CHT a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                   d[] = {'D', '\0'}, e[] = { 'E', '\0' },
                   abc[] = {'a', 'b', 'c', '\0'},
                   bac[] = {'b', 'a', 'c', '\0'}, cba[] = {'c', 'b', 'a', '\0'},
                   cab[] = {'c', 'a', 'b', '\0'},
                   test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW(ISY(0), table.Add(a));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));

  A_AVOW(ISY(1), table.Add(b));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));
  A_AVOW(ISY(1), table.Find(b));

  A_AVOW(ISY(2), table.Add(c));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));
  A_AVOW(ISY(1), table.Find(b));
  A_AVOW(ISY(2), table.Find(c));

  A_AVOW(ISY(3), table.Add(d));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));
  A_AVOW(ISY(1), table.Find(b));
  A_AVOW(ISY(2), table.Find(c));
  A_AVOW(ISY(3), table.Find(d));

  A_AVOW(ISY(0), table.Add(a));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(1), table.Add(b));
  A_AVOW(ISY(2), table.Add(c));
  A_AVOW(ISY(3), table.Add(d));

  A_AVOW(ISY(4), table.Add(abc));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));

  A_AVOW(ISY(5), table.Add(bac));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));

  A_AVOW(ISY(6), table.Add(cba));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));
  A_AVOW(ISY(6), table.Find(cba));

  A_AVOW(ISY(7), table.Add(e));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));
  A_AVOW(ISY(6), table.Find(cba));
  A_AVOW(ISY(7), table.Find(e));

  A_AVOW(ISY(8), table.Add(cab));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));
  A_AVOW(ISY(6), table.Find(cba));
  A_AVOW(ISY(7), table.Find(e));
  A_AVOW(ISY(8), table.Find(cab));

  D_COUT_OBJ(table);
  A_AVOW(CAInvalidIndex<ISY>(), table.Find(test));

  // D_PAUSE("");
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* Table(const CHA* args) {
#if SEAM >= SCRIPT2_TABLE
  A_TEST_BEGIN;

  TestTable<CHA, ISC, ISB, IUC>();
  TestTable<CHA, ISD, ISC, IUD>();
#if USING_UTF16 == YES_0
  TestTable<CHB, ISC, ISB, IUC>();
  TestTable<CHB, ISD, ISC, IUD>();
#endif
#if USING_UTF32 == YES_0
  TestTable<CHC, ISC, ISB, IUC>();
  TestTable<CHC, ISD, ISC, IUD>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
#undef TBL_A
#undef TBL_P
