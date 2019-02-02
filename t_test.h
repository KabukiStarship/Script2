/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \ttest.h
@author  Cale McCollough <cale@astartup.net>
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

#ifndef SCRIPT2_TTEST
#define SCRIPT2_TTEST 1

#include "c_test.h"

#include "c_cin.h"
#include "c_cout.h"
#include "t_binary.h"

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

#endif  //< SCRIPT2_TTEST
