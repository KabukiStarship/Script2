/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \02_ascii_strings_and_socket.h
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

#include "t_socket.h"
#include "t_strand.h"
#include "t_test.h"

#include "c_cout.h"

#if SEAM == SCRIPT2_2
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _02_Socket(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_2
  TEST_BEGIN;

  PRINT_HEADING("Test SocketCopy and MemoryCompare");

  enum {
    kTestCharsCount = 1024,
    kTestCharsOffsetCount = 16,
  };
  CH1 test_chars[kTestCharsCount];
  CH1 test_chars_result[kTestCharsCount + kTestCharsOffsetCount];

  PRINTF("\ntest_chars[0]:0x%p test_chars_result[n]:0x%p ", test_chars,
         test_chars_result);

  for (SI4 i = 0; i < kTestCharsOffsetCount; ++i) {
    for (SI4 j = 0; j < kTestCharsCount; ++j) test_chars[j] = (CH1)(j % 256);
    CH1* result = SocketCopy(test_chars_result + i, kTestCharsCount, test_chars,
                             kTestCharsCount);
    ASSERT(result);
    ASSERT(!SocketCompare(test_chars + i, kTestCharsCount, test_chars_result,
                          kTestCharsCount));
  }
#endif
  return nullptr;
}
} //< namespace script2
