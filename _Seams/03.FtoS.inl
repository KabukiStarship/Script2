/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/03.FtoS.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_FTOS
//#include "../RNG.h"
using namespace std;
using namespace _;
#if SEAM == SCRIPT2_FTOS
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
const CHA* FtoS(const CHA* args) {
#if SEAM >= SCRIPT2_FTOS
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_FTOS
  enum { cTestCount = 1 << 20 };
#else
  enum { cTestCount = 1 << 15 };
#endif
  /*
  enum { cSize = 31 };
  CHA socket[cSize + 1];

  IUD value;
  FPD dbl_expected, dbl_found;

  D_COUT("\n\nTesting Float Ceiling<Float, IU> (Float)...\n");

  for (ISC i = 0; i < cTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FPD>(value);
    } while (!IsFinite(dbl_expected));
    dbl_found = ceil(dbl_expected);
    dbl_expected = Ceiling(dbl_expected);
    Test(dbl_expected, dbl_found);
  }

  D_COUT(
      "\n\nTesting const CHT* TSScan<CHT> (const CHT*, const CHT*, FPC&) "
      "functions...\n");

  for (ISC i = 0; i < cTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FPD>(value);
    } while (!IsFinite(dbl_expected));
    sprintf_s(socket, cSize, "%lf", dbl_expected);
    A_ASSERT(SScan(socket, dbl_found));
    A_AVOW(dbl_expected, dbl_found);
  }

  D_COUT("\n\nTesting CHT* TSPrint<CHT> (CHT*, CHT*, Float)...\n");

  for (ISC i = 0; i < cTestCount; ++i) {
    do {
      value = RandomUI8();
      dbl_expected = static_cast<FPD>(value);
    } while (!IsFinite(dbl_expected));
    Print(socket, socket + cSize, dbl_expected);
    ISC r = sscanf_s(socket, "%lf", &dbl_found);
    A_ASSERT(r);
    A_AVOW(dbl_expected, dbl_found);
  }
  TBinary<>::PrintDebugInfo();
  */
#endif
  return nullptr;
}
}  //< namespace Script2
