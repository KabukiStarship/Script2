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
static const CH1* _07_Stack_Array(CH1* seam_log, CH1* seam_end,
                                  const CH1* args) {
#if SEAM >= SCRIPT2_7
  TEST_BEGIN;

  PRINT("\n\nTesting TStack<SI4>...\n\nPrinting empty stack...\n");

  TStack<SI4> stack(8);
  stack.COut();

  PRINT("\n\nPushing items on to the Stack...\n");
  stack.Push(0);
  PRINT_SOCKET_TOBJ(stack.TObj());

  for (SI4 i = 1; i <= 10; ++i) stack.Push(i);

  PRINT_OBJ(stack);

  PRINT("\nPopping items off the Stack...\n");

  for (SI4 i = 10; i > 0; --i) AVOW_INDEX(i, stack.Pop(), i);

  PRINT_OBJ(stack);

  static const SI4 array_3d_exected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const SI4* test = Dimensions<2, 2, 2>();
  TArray<SI4> test_array(test);
  *test_array.Elements() = {{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}};

  SI4 w = 0;
  SI4* array_base = test_array.Elements();
  for (SI4 z = 0; z < 2; ++z)
    for (SI4 y = 0; y < 2; ++y)
      for (SI4 x = 0; x < 2; ++x) AVOW(w++, array_3d_exected[x][y][z]);

#endif
  return nullptr;
}
}  // namespace script2
