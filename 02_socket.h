/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \02_socket.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
