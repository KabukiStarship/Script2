/* SCRIPT Script @version 0.x
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

#if SEAM == SEAM_SCRIPT2_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename SIZ>
void TestStack(const CH1* args) {
  D_COUT("\n\nTesting AStack<SI");
  D_COUT(sizeof(SIZ));
  D_COUT(">...\n\nPrinting empty stack...\n");

  AStack<SI8, SIZ, TSocket<8, SI8, TStack<SIZ>>> stack;
#if DEBUG_THIS
  stack.COut();
#endif

  D_COUT("\n\nPushing items on to the Stack...\n");

  SI8 test_count = 32, count_init = 0;
  for (SI8 i = count_init; i <= test_count; ++i) stack.Push(i);

  D_COUT("\nPopping items off the Stack...\n");

  for (SI8 i = test_count; i >= count_init; --i)
    A_AVOW_INDEX(i, stack.Pop(), i);
  A_ASSERT(stack.Count() == 0);
}

static const CH1* _07_Stack(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_STACK
  A_TEST_BEGIN;

  const CH1* result = 0;
  TestStack<SI2>(args);
  TestStack<SI4>(args);
  TestStack<SI8>(args);
#endif
  return nullptr;
}
}  // namespace script2
