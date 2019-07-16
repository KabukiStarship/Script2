/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/00_core.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "c_rng.h"
#include "t_stringcore.h"

#if SEAM == SEAM_SCRIPT2_CORE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
inline const CH1* _00_RNG(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_CORE
  A_TEST_BEGIN;

  D_COUT_HEADING("Testing CIn::Args");

  CH1 arg_string[48] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  D_COUT("\n\narg_string:\"");
  D_COUT_2(arg_string, '\"');
  CH1* test_args[] = {arg_string, arg_string + 11, arg_string + 16,
                      arg_string + 26};
  const SI4 kArgCount = 4;

  D_COUT("\nArguments:\n");
  for (SI4 i = 0; i < kArgCount; ++i) {
    CH1* arg = test_args[i];
    if (arg) {
      D_PRINTF("\n%i.)\"%s\" delta:%i", i, arg, (SIN)(arg - arg_string));
    } else {
      D_COUT("\nNil arg.");
    }
  }
  D_COUT("\n\nRunning CIn::Args... ");
  D_ASSERT(CIn::Args(kArgCount, test_args));

  D_COUT("Result:\"");
  D_COUT(test_argsg[1]);
  D_COUT('\"');
  D_COUT_HEADING("Testing Rangom Number Generator (RNG)");

  for (SI4 i = 0; i < 10000; ++i) {
    RandomizeSeed();
    auto value = RandomUI2();
    // D_COUT_NL;
    // D_PRINTF("%u", (UIN)value);
  }

#endif
  return 0;
}
}  // namespace script2
