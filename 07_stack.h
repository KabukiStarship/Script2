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

#include "t_stack.h"

#if SEAM == SCRIPT2_SEAM_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename SIZ>
void TestTStack(CH1* seam_log, CH1* seam_end, const CH1* args) {
  PRINT("\n\nTesting AStack<SI");
  PRINT(sizeof(SIZ));
  PRINT(">...\n\nPrinting empty stack...\n");

  AStack<SI4, SIZ, TSocket<64>> stack(8);
  stack.COut();

  PRINT("\n\nPushing items on to the Stack...\n");
  stack.Push(0);
  PRINT_SOCKET_OBJ(stack.OBJ());

  for (SI4 i = 1; i <= 10; ++i) stack.Push(i);

  PRINT_OBJ(stack);

  PRINT("\nPopping items off the Stack...\n");

  for (SI4 i = 10; i > 0; --i) AVOW_INDEX(i, stack.Pop(), i);

  PRINT_OBJ(stack);
}

static const CH1* _07_Stack(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_SEAM_STACK
  TEST_BEGIN;

  const CH1* result = 0;
  TestTStack<SI2>(seam_log, seam_end, args);
  TestTStack<SI4>(seam_log, seam_end, args);
  TestTStack<SI8>(seam_log, seam_end, args);
#endif
  return nullptr;
}
}  // namespace script2
