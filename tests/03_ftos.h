/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2\03_ftos_and_stof.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

//#include "c_rng.h"
//#include "c_utf.h"

#include <cmath>
#include <cstdio>

using namespace std;

#if SEAM == SCRIPT2_FTOS
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
const CH1* FtoS(const CH1* args) {
#if SEAM >= SCRIPT2_FTOS
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_FTOS
  enum { kTestCount = 1 << 20 };
#else
  enum { kTestCount = 1 << 15 };
#endif
  /*
  enum { kSize = 31 };
  CH1 socket[kSize + 1];

  UI8 value;
  FP8 dbl_expected, dbl_found;

  D_COUT("\n\nTesting Float Ceiling<Float, UI> (Float)...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FP8>(value);
    } while (!IsFinite(dbl_expected));
    dbl_found = ceil(dbl_expected);
    dbl_expected = Ceiling(dbl_expected);
    Test(dbl_expected, dbl_found);
  }

  D_COUT(
      "\n\nTesting const Char* TSScan<Char> (const Char*, const Char*, FP4&) "
      "functions...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FP8>(value);
    } while (!IsFinite(dbl_expected));
    sprintf_s(socket, kSize, "%lf", dbl_expected);
    A_ASSERT(SScan(socket, dbl_found));
    A_AVOW(dbl_expected, dbl_found);
  }

  D_COUT("\n\nTesting Char* TSPrint<Char> (Char*, Char*, Float)...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FP8>(value);
    } while (!IsFinite(dbl_expected));
    Print(socket, socket + kSize, dbl_expected);
    SI4 r = sscanf_s(socket, "%lf", &dbl_found);
    A_ASSERT(r);
    A_AVOW(dbl_expected, dbl_found);
  }
  TBinary<>::PrintDebugInfo();
  */
#endif
  return nullptr;
}
}  // namespace script2
