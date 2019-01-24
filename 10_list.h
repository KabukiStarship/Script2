/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/09_list.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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

#if SEAM == SCRIPT2_10
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _10_List(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_10
  TEST_BEGIN;

  List<> list(36, 960);
  Assert(list.This())

      PRINTF("\nPushing items on to the List stack...\n")

          const SI4 test_ints[] = {'1', '2', '3', '4'};

  const SI4 list_test_count = 12;
  for (SI4 i = 0; i < 4;) {
    PRINTF("\ni%i:", i);
    list.Push(kSI4, &test_ints[i++]);
    COUT << '\n'
         << list << '\n'
         << "\n\n"
         << Socket(list.This(), list.This()->size);
  }
  const FLT test_floats[] = {9.0, 10.0, 11.0, 12.0};
  for (SI4 i = 0; i < 4;) {
    PRINTF("\ni%i:", i);
    list.Push(kFLT, &test_floats[i++]);
    PRINT('\n');
    PRINT(list);
    PRINT ('\n'');
    PRINT ("\n\n"');
    PRINT (Socket (list.This (), list.This ()->size));
  }

  const CH1* test_strings[] = {"Test", " 1, ", " 2, ", " 3"};
  for (SI4 i = 0; i < 4;) {
    PRINTF("\ni%i:", i);
    list.Push(kSTR, test_strings[i++]);
    PRINT('\n');
    PRINT(list);
    PRINT('\n');
    PRINT("\n\n");
    PRINT(Socket(list.This(), list.This()->size));
  }

  for (SI4 i = list_test_count - 1; i > 0; --i) list.Pop();

#endif
  return nullptr;
}
} //< namespace script2
