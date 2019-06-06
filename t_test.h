/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \t_test.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_TTEST
#define SCRIPT2_TTEST 1

#include "c_cin.h"
#include "c_cout.h"
#include "c_test.h"
#include "t_utf.h"

namespace _ {

template <TestCase... N>
const CH1* TTestTree(CH1* seam_log, CH1* seam_end, const CH1* args) {
  static TestCase nodes[sizeof...(N)] = {N...};
  return TestTree(seam_log, seam_end, args, nodes, sizeof...(N));
}

template <TestCase... N>
SI4 TTestTree(SI4 arg_count, CH1** args, CH1* seam_log, SI4 seam_log_size) {
  static TestCase tests[sizeof...(N)] = {N...};
  return SeamTreeTest(arg_count, args, seam_log, seam_log_size, tests,
                      sizeof...(N));
}

}  // namespace _

#endif
