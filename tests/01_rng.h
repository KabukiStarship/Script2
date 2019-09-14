/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \02_socket.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "rng.h"

#if SEAM == SCRIPT2_RNG
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* RNG(const CH1* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_RNG
  enum { kPrintCount = 256 };
#else
  enum { kPrintCount = 1 };
#endif
  D_COUT(
      Headingf("Printing ", TStringf<>(kPrintCount).string(), " numbers..."));

  for (SIN i = 0; i < kPrintCount; ++i)
    D_COUT('\n' << i << ".) " << Random(TSignedMin<SIN>(), TSignedMax<SIN>()));

#endif
  return nullptr;
}
}  // namespace script2
