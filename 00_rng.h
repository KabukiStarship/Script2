/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/00_rng.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "c_cout.h"
#include "c_rng.h"

#if SEAM == SCRIPT2_0
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
inline const CH1* _00_RNG(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_0
  TEST_BEGIN;

  PRINT_HEADING("Testing ArgsToSring");

  CH1 arg_string[] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  CH1* test_args[] = {arg_string, arg_string + 11, arg_string + 16,
                      arg_string + 26};
  const SI4 kArgCount = 4;

  PRINT("\nArguments:\n");
  for (SI4 i = 0; i < kArgCount; ++i) {
    CH1* arg = test_args[i];
    if (arg) {
      PRINTF("\ni:%i\"%s\" 0x%p", i, arg, arg);
    } else {
      PRINT("\nNil arg.");
    }
  }
  PRINT("\n\nRunning ArgsToSring...\n");
  ASSERT(ArgsToSring(kArgCount, test_args));

  PRINT("\n\nPrinting argument string...\n");
  PRINT(test_args[1]);

  PRINT("\n\nDone testing const CH1* ArgsToSring(SI4, CH1**);");

  PRINT_HEADING("Testing RNG");

  for (SI4 i = 0; i < 10000; ++i) {
    RandomizeSeed();
    auto value = RandomUI2();
    // PRINTNL;
    // PRINTF("%u", (UIN)value);
  }

#endif
  return 0;
}
}  // namespace script2
