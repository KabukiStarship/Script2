/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/00_core.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "c_rng.h"

#if SEAM == SEAM_SCRIPT2_CORE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
inline const CH1* _00_Core(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_CORE
  A_TEST_BEGIN;

  D_COUT("\n\nTesting ArgsToString\n\n");

  CH1 arg_string[48] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  D_COUT("arg_string:\"");
  CH1* cursor = arg_string;
  for (SIN i = 0; i < 35; ++i) D_COUT(*cursor++);
  D_COUT('\"');

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
  D_COUT("\n\nRunning ArgsToString... ");

  D_ASSERT(ArgsToString(kArgCount, test_args));

  D_COUT("Result:\"");
  D_COUT(test_args[1]);
  D_COUT("\"\n\nTesting Rangom Number Generator (RNG)");

  for (SI4 i = 0; i < 100; ++i) {
    RandomizeSeed();
    auto value = RandomUI4();
    D_COUT_NL;
    D_PRINTF("%u, ", value);
  }

#endif
  return 0;
}
}  // namespace script2
