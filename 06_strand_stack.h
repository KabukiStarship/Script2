/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/05_stack.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#include "t_stack.h"

#if SEAM == SCRIPT2_6
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

#if SEAM >= SCRIPT2_6
namespace script2 {
template <typename Char>
void _06_Strand() {
  PRINTF("\n\nTesting UTF<CH%c>", '0' + sizeof(Char));

  static const Char kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};

  enum {
    kStrandLoopCount = 3,
    kCharSizeChar = '0' + sizeof(Char),
  };

  TStrand<Char> strand("Testing ");
  strand.Print();

  PRINTF("\n\nExpecting \"%s\"\n", kTesting123);
  strand << 1 << ", " << 2 << ", " << 3;
  PRINT_CHARS(strand.CObj().Start<>(), strand.CObj().SizeBytes());
  const Char* cursor = strand.Find(kTesting123);
  ASSERT(cursor);
}
#endif  //< #if SEAM >= SCRIPT2_6

static const CH1* _06_Strand_Stack(CH1* seam_log, CH1* seam_end,
                                   const CH1* args) {
#if SEAM >= SCRIPT2_6
  TEST_BEGIN;

  PRINT("\n\nTesting TStrand...\n");

  _06_Strand<CH1>();
  _06_Strand<CH2>();
  _06_Strand<CH4>();

  PRINT("\n\nPushing items on to the Stack...\n");

  TStack<SI4> stack(8);
  stack.Print();
  stack.Push(0);
  PRINT_SOCKET_TOBJ(stack.TObj());

  for (SI4 i = 1; i <= 10; ++i)
    ;

  PRINT_TOBJ(stack);

  PRINT("\nPopping items off the Stack...\n");

  for (SI4 i = 10; i > 0; --i) AVOW(i, stack.Pop());

  PRINT_TOBJ(stack);

#endif
  return nullptr;
}
}  //< namespace script2
