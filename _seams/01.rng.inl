/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/01.rng.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Cale McCollough
<<cale-mccollough.github.io>>; all right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_RNG
#include "../rng.h"
using namespace _;
#if SEAM == SCRIPT2_RNG
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
static const CHA* RNG(const CHA* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_RNG
  enum { cPrintCount = 256 };
#else
  enum { cPrintCount = 1 };
#endif

  for (ISN i = 0; i < cPrintCount; ++i)
    D_COUT('\n' << i << ".) " << Random(TSignedMin<ISN>(), TSignedMax<ISN>()));

#endif
  return nullptr;
}
}  // namespace script2
