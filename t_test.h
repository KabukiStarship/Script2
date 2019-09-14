/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \t_test.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_TTEST
#define SCRIPT2_TTEST 1

#include "c_test.h"
//
#include "c_cin.h"

namespace _ {

template <TestCase... N>
const CH1* TTestTree(const CH1* args) {
  static TestCase nodes[sizeof...(N)] = {N...};
  return TestTree(args, nodes, sizeof...(N));
}

template <TestCase... N>
SI4 TTestTree(SI4 arg_count, CH1** args) {
  static TestCase tests[sizeof...(N)] = {N...};
  return SeamTreeTest(arg_count, args, tests, sizeof...(N));
}

}  // namespace _

#endif
