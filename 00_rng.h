/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/00_rng.h
@author  Cale McCollough <calemccollough.github.io>
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

#include "cconsole.h"
#include "crng.h"

#if SEAM == SCRIPT2_0
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

using namespace _;

namespace script2 {
inline const CH1* _00_RNG (CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_0
  TEST_BEGIN;

  PRINT_HEADING ("Testing ArgsToString");

  CH1 arg_string[] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  CH1* test_args[] = { arg_string, arg_string + 11, arg_string + 16,
                      arg_string + 26 };
  const SI4 kArgCount = 4;

  PRINT ("\nArguments:\n");
  for (SI4 i = 0; i < kArgCount; ++i) {
    CH1* arg = test_args[i];
    if (arg) {
      PRINTF ("\ni:%i\"%s\" 0x%p", i, arg, arg);
    }
    else {
      PRINT ("\nNil arg.");
    }
  }
  PRINT ("\n\nRunning ArgsToString...\n");
  ASSERT (ArgsToString (kArgCount, test_args));

  PRINT ("\n\nPrinting argument string...\n");
  PRINT (test_args[1]);

  PRINT ("\n\nDone testing const CH1* ArgsToString(SI4, CH1**);");

  PRINT_HEADING ("Testing RNG");

  for (SI4 i = 0; i < 10000; ++i) {
    RandomizeSeed ();
    auto value = RandomUI2 ();
    PRINT ('\n');
    PRINT (value);
  }

#endif
  return 0;
}
} //< namespace script2
