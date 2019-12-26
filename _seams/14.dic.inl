/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/14.dic.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_DIC
#include "../dic.hpp"
using namespace _;
#if SEAM == SCRIPT2_DIC
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif

namespace script2 {
template <typename ISZ = ISN, typename IUZ = IUN, typename ISY = ISM,
          typename CHT = CHR>
static void TestDic() {
#if SEAM >= SCRIPT2_DIC
  A_TEST_BEGIN;

#endif
  return nullptr;
}
}  // namespace script2
#endif

namespace script2 {
const CHA* Dic(const CHA* args) {
#if SEAM >= SCRIPT2_DIC
  A_TEST_BEGIN;
  TestDic<ISB, IUB, ISA, CHA>();
  TestDic<ISB, IUB, ISA, CHB>();
  TestDic<ISB, IUB, ISA, CHC>();
#if USING_UTF16 == YES_0
  TestDic<ISC, IUC, ISB, CHA>();
  TestDic<ISC, IUC, ISB, CHB>();
  TestDic<ISC, IUC, ISB, CHC>();
#endif
#if USING_UTF32 == YES_0
  TestDic<ISD, IUD, ISB, CHA>();
  TestDic<ISD, IUD, ISB, CHB>();
  TestDic<ISD, IUD, ISB, CHC>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
