/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/11_list.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_SEAM_LIST
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _11_List(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_SEAM_LIST
  TEST_BEGIN;

  List<> list(36, 960);

  PRINTF("\nPushing items on to the List stack...\n");

  const SI4 test_ints[] = {'1', '2', '3', '4'};

  const SI4 list_test_count = 12;
  for (SI4 i = 0; i < 4;) {
    PRINTF("\ni%i:", i);
    list.Push(kSI4, &test_ints[i++]);
    COUT << kLF << list << kLF << "\n\n"
         << Socket(list.This(), list.This()->size);
  }
  const FP4 test_floats[] = {9.0, 10.0, 11.0, 12.0};
  for (SI4 i = 0; i < 4;) {
    PRINTF("\ni%i:", i);
    list.Push(kFP4, &test_floats[i++]);
    PRINT(kLF);
    PRINT(list);
    PRINT(kLF);
    PRINT("\n\n");
    PRINT(Socket(list.This(), list.This()->size));
  }

  const CH1* test_strings[] = {"Test", " 1, ", " 2, ", " 3"};
  for (SI4 i = 0; i < 4;) {
    PRINTF("\ni%i:", i);
    list.Push(kSTR, test_strings[i++]);
    PRINT(kLF);
    PRINT(list);
    PRINT(kLF);
    PRINT("\n\n");
    PRINT(Socket(list.This(), list.This()->size));
  }

  for (SI4 i = list_test_count - 1; i > 0; --i) list.Pop();

#endif
  return nullptr;
}
}  // namespace script2
