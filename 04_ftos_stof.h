/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2\03_ftos_and_stof.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include <cmath>
#include <cstdio>

#include "c_binary.h"
#include "c_rng.h"

using namespace std;

#if SEAM == SCRIPT2_4
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
const CH1* _04_FtoS_StoF(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_4
  TEST_BEGIN;

#if SEAM == SCRIPT2_4
  enum { kTestCount = 1 << 20 };
#else
  enum { kTestCount = 1 << 15 };
#endif
  /*
  enum { kSize = 31 };
  CH1 socket[kSize + 1];

  UI8 value;
  FP8 dbl_expected, dbl_found;

  PRINTF("\n\nTesting Float Ceiling<Float, UI> (Float)...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FP8>(value);
    } while (!IsFinite(dbl_expected));
    dbl_found = ceil(dbl_expected);
    dbl_expected = Ceiling(dbl_expected);
    Test(dbl_expected, dbl_found);
  }

  PRINT(
      "\n\nTesting const Char* TScan<Char> (const Char*, const Char*, FP4&) "
      "functions...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FP8>(value);
    } while (!IsFinite(dbl_expected));
    sprintf_s(socket, kSize, "%lf", dbl_expected);
    ASSERT(Scan(socket, dbl_found));
    AVOW(dbl_expected, dbl_found);
  }

  PRINTF("\n\nTesting Char* TPrint<Char> (Char*, Char*, Float)...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FP8>(value);
    } while (!IsFinite(dbl_expected));
    Print(socket, socket + kSize, dbl_expected);
    SI4 r = sscanf_s(socket, "%lf", &dbl_found);
    ASSERT(r);
    AVOW(dbl_expected, dbl_found);
  }
  */
  TBinary<>::PrintDebugInfo();
#endif
  return nullptr;
}
} //< namespace script2
