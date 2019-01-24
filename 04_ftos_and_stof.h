/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2\03_ftos_and_stof.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#include <cmath>
#include <cstdio>

#include "cbinary.h"
#include "crng.h"

using namespace std;

#if SEAM == SCRIPT2_4
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

using namespace _;

namespace script2 {
const CH1* _04_FtoS_and_StoF(CH1* seam_log, CH1* seam_end, const CH1* args) {
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
  DBL dbl_expected, dbl_found;

  PRINTF("\n\nTesting Float Ceiling<Float, UI> (Float)...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<DBL>(value);
    } while (!IsFinite(dbl_expected));
    dbl_found = ceil(dbl_expected);
    dbl_expected = Ceiling(dbl_expected);
    Test(dbl_expected, dbl_found);
  }

  PRINT(
      "\n\nTesting const Char* TScan<Char> (const Char*, const Char*, FLT&) "
      "functions...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<DBL>(value);
    } while (!IsFinite(dbl_expected));
    sprintf_s(socket, kSize, "%lf", dbl_expected);
    ASSERT(Scan(socket, dbl_found));
    AVOW(dbl_expected, dbl_found);
  }

  PRINTF("\n\nTesting Char* TPrint<Char> (Char*, Char*, Float)...\n");

  for (SI4 i = 0; i < kTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<DBL>(value);
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
