/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/05_stack.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
  PRINTF("\n\nTesting TStrand<CH%c>\n\n", '0' + sizeof(Char));

  static const Char kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};
  enum {
    kStrandLoopCount = 3,
    kCharSizeChar = '0' + sizeof(Char),
  };

  PRINTF("\n\nExpecting \"%s\"\n", kTesting123);
  TStrand<Char, 8> strand;
  strand.Wipe();
  strand.PrintConstants();
  strand << "Testing ";
  strand << 1;
  strand << ", ";
  strand << 2;
  strand << ", ";
  strand << 3;
  PRINT("\nResult:");
  PRINT_CHARS(strand.CObj().Start<>(), strand.CObj().SizeBytes());

  const Char* cursor = strand.Find(kTesting123);
  ASSERT(cursor);
}
#endif  //< #if SEAM >= SCRIPT2_6

static const CH1* _06_Strand_Stack(CH1* seam_log, CH1* seam_end,
                                   const CH1* args) {
#if SEAM >= SCRIPT2_6
  TEST_BEGIN;

  PRINT("\n\nTesting TStrand<>...\n");

  _06_Strand<CH1>();
  _06_Strand<CH2>();
  _06_Strand<CH4>();

  PRINT("\n\nTesting TStack<SI4>...\n\nPrinting empty stack...\n");

  TStack<SI4> stack(8);
  stack.Print();

  PRINT("\n\nPushing items on to the Stack...\n");
  stack.Push(0);
  PRINT_SOCKET_TOBJ(stack.TObj());

  for (SI4 i = 1; i <= 10; ++i) stack.Push(i);

  PRINT_TOBJ(stack);

  PRINT("\nPopping items off the Stack...\n");

  for (SI4 i = 10; i > 0; --i) AVOW(i, stack.Pop());

  PRINT_TOBJ(stack);

#endif
  return nullptr;
}
}  //< namespace script2
