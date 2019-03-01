/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/06_array.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "t_array.h"

#if SEAM == SCRIPT2_7
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _07_Array(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_7
  TEST_BEGIN;

  static const SI4 array_3d_exected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const SI4* test = Dimensions<2, 2, 2>();
  TArray<SI4> test_array(test);
  *test_array.Elements() = {{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}};
  i = 0;
  SI4* array_base = test_array.Elements();
  for (SI4 z = 0; z < 2; ++z)
    for (SI4 y = 0; y < 2; ++y)
      for (SI4 x = 0; x < 2; ++x) Compare(i++, array_3d_exected[x][y][z]);

#endif
  return nullptr;
}
} //< namespace script2
