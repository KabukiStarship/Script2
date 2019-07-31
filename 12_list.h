/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/11_list.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_LIST
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _12_List(const CH1* args) {
#if SEAM >= SCRIPT2_LIST
  A_TEST_BEGIN;

  AList<> list(36, 960);

  D_COUT("\nPushing items on to the List stack...\n");

  const SI4 test_ints[] = {'1', '2', '3', '4'};

  const SI4 list_test_count = 12;
  for (SI4 i = 0; i < 4;) {
    D_COUT("\ni" << i << ':');
    list.Push(kSI4, &test_ints[i++]);
    COUT << '\n' << list << '\n' << "\n\n"
         << Socket(list.This(), list.This()->size);
  }
  const FP4 test_floats[] = {9.0, 10.0, 11.0, 12.0};
  for (SI4 i = 0; i < 4;) {
    D_COUT("\ni" << i << ':');
    list.Push(kFP4, &test_floats[i++]);
    D_COUT('\n');
    D_COUT(list);
    D_COUT('\n');
    D_COUT("\n\n");
    D_COUT(Socket(list.This(), list.This()->size));
  }

  const CH1* test_strings[] = {"Test", " 1, ", " 2, ", " 3"};
  for (SI4 i = 0; i < 4;) {
    D_COUT("\ni" << i << ':');
    list.Push(kSTR, test_strings[i++]);
    D_COUT('\n');
    D_COUT(list);
    D_COUT('\n');
    D_COUT("\n\n");
    D_COUT(Socket(list.This(), list.This()->size));
  }

  for (SI4 i = list_test_count - 1; i > 0; --i) list.Pop();

#endif
  return nullptr;
}
}  // namespace script2
