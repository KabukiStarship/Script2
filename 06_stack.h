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

#include "t_stack.h"

#if SEAM == SEAM_SCRIPT2_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

template <typename T, typename SIZ>
void TestStack(const CH1* args) {
  D_PRINTF("Testing AStack<SI%i, SI%i>...\n", sizeof(T), sizeof(SIZ));

  AStack<T, SIZ, 8> stack;

  D_COUT(Linef("\n+---\n| TSocket: size:")
         << stack.Auto().Buffer().Size() << " expected_size_bytes:"
         << stack.Auto().Buffer().Size() * sizeof(T) + sizeof(TStack<SIZ>)
         << " size_bytes:" << stack.Auto().Buffer().SizeBytes()
         << " size_words:" << stack.Auto().Buffer().SizeWords());
  D_COUT_OBJ(stack);

  enum { kTestCount = 32, kOffset = '0' };
  D_PRINTF("\n\nPushing %i items on to the Stack...\n", kTestCount);
  for (T i = kOffset; i <= kTestCount + kOffset; ++i) {
    D_COUT("\n| Before calling push:" << Charsf(stack.Auto().Begin(),
                                                stack.Auto().SizeBytes()));
    D_COUT(Linef("\n\n+---\n| ") << i << ".) ");
    stack.Push(i);
    D_COUT("\n| Result:");
    D_COUT_OBJ(stack);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack...\n"));

  for (T test_count = kTestCount + kOffset; test_count >= kOffset;
       --test_count) {
    D_COUT_OBJ(stack);
    A_AVOW_INDEX(test_count, stack.Pop(), test_count);
  }
  D_COUT_OBJ(stack);
  A_ASSERT(stack.Count() == 0);
}

static const CH1* _07_Stack(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_STACK
  A_TEST_BEGIN;

  // TestStack<SI4, SI8>(args); is illegal
  TestStack<SI4, SI4>(args);
  TestStack<SI8, SI8>(args);
  TestStack<SI8, SI4>(args);
#endif
  return nullptr;
}
}  // namespace script2
