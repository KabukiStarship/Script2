/* Script^2 @version 0.x
@file    /0_0_0__05_ascii_stack.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#include "tstack.h"

#if SEAM == _0_0_0__06
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

static const CH1* _0_0_0__06_ASCII_Stack(CH1* seam_log, CH1* seam_end,
                                          const CH1* args) {
#if SEAM >= _0_0_0__06
  TEST_BEGIN;

  PRINT("\n\nPushing items on to the Stack...\n");

  TStack<int> stack(8);

  for (int i = 0; i <= 10; ++i) stack.Push(i);

  PRINT_TOBJ(stack);

  PRINT("\nPopping items off the Stack...\n");

  for (int i = 10; i > 0; --i) AVOW(i, stack.Pop());

  PRINT_TOBJ(stack);

#endif
  return nullptr;
}
}  // namespace _
