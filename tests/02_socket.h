/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \02_rng.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "t_binary.h"

#if SEAM == SCRIPT2_RNG
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _02_Socket(const CH1* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing Rangom Number Generator (RNG)"));

  for (SI4 i = 0; i < 100; ++i) {
    RandomizeSeed();
    auto value = RandomUI4();
    D_COUT("\n, " << value);
  }

  D_COUT(Headingf("Testing Hex functions"));
  for (SI4 i = 0; i < 16; ++i) {
    SI4 value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    // D_COUT("\n    " << i << ".) " >> value);
    value = HexToByte(HexNibbleToUpperCase(i));
    // D_COUT(" Result:" << value);
    Test(i, value);
  }

  for (SI4 i = 0; i < 256; ++i) {
    UI2 c = HexByteToLowerCase(i);
    // D_COUT('\n' << i << ".) Expecting:" << Hexf(i)
    //             << "        HexByteToLowerCase:" << CH1(c) << CH1(c >> 8));
    SI4 value = HexToByte(c);
    // D_COUT("        HexToByte:" << value);
    A_AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    // D_COUT(" Result:" << value);
    Test(i, value);
  }

#endif
  return nullptr;
}
}  // namespace script2
