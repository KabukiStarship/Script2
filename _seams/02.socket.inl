/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/02.Socket.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_RNG
#include "../Binary.hpp"
using namespace _;
#if SEAM == SCRIPT2_RNG
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
static const CHA* _02_Socket(const CHA* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing Rangom Number Generator (RNG)"));

  for (ISC i = 0; i < 100; ++i) {
    RandomizeSeed();
    auto value = RandomUI4();
    D_COUT("\n, " << value);
  }

  D_COUT(Headingf("Testing Hex functions"));
  for (ISC i = 0; i < 16; ++i) {
    ISC value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    // D_COUT("\n    " << i << ".) " >> value);
    value = HexToByte(HexNibbleToUpperCase(i));
    // D_COUT(" Result:" << value);
    Test(i, value);
  }

  for (ISC i = 0; i < 256; ++i) {
    IUB c = HexByteToLowerCase(i);
    // D_COUT('\n' << i << ".) Expecting:" << Hexf(i)
    //             << "        HexByteToLowerCase:" << CHA(c) << CHA(c >> 8));
    ISC value = HexToByte(c);
    // D_COUT("        HexToByte:" << value);
    A_AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    // D_COUT(" Result:" << value);
    Test(i, value);
  }

#endif
  return nullptr;
}
}  // namespace Script2
