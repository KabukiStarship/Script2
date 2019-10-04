/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/14.dic.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_DIC
#include "../dic.hpp"
using namespace _;
#if SEAM == SCRIPT2_DIC
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif

namespace script2 {
template <typename SIZ = SIN, typename UIZ = UIN, typename SIY = SIG,
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
const CH1* Dic(const CH1* args) {
#if SEAM >= SCRIPT2_DIC
  A_TEST_BEGIN;
  TestDic<SI2, UI2, SI1, CH1>();
  TestDic<SI2, UI2, SI1, CH2>();
  TestDic<SI2, UI2, SI1, CH4>();
#if USING_UTF16 == YES_0
  TestDic<SI4, UI4, SI2, CH1>();
  TestDic<SI4, UI4, SI2, CH2>();
  TestDic<SI4, UI4, SI2, CH4>();
#endif
#if USING_UTF32 == YES_0
  TestDic<SI8, UI8, SI2, CH1>();
  TestDic<SI8, UI8, SI2, CH2>();
  TestDic<SI8, UI8, SI2, CH4>();
#endif
#endif
  return nullptr;
}
}  // namespace script2
