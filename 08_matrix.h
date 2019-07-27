/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/06_array.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "t_matrix.h"

#if SEAM == SCRIPT2_MATRIX
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _08_Matrix(const CH1* args) {
#if SEAM >= SCRIPT2_MATRIX
  A_TEST_BEGIN;

  D_COUT("\n\nTesting AStack<SI4>...\n\nPrinting empty stack...\n");

  static const SI4 array_3d_exected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const SI4* dimensions = TStack4<2, 2, 2>();
  AMatrix<SI4> test_matrix(2, 2, 2, &array_3d_exected[0][0][0]);

  SI4 w = 0;
  SI4* array_base = test_matrix.Elements();
  for (SI4 x = 0; x < 2; ++x)
    for (SI4 y = 0; y < 2; ++y)
      for (SI4 z = 0; z < 2; ++z) A_AVOW(w++, array_3d_exected[x][y][z]);
#endif
  return nullptr;
}
}  // namespace script2
