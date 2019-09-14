/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /06_array.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "stack.hpp"

#if SEAM == SCRIPT2_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {

#if SEAM >= SCRIPT2_STACK
template <typename T, typename SIZ>
void TestStack(const CH1* args) {
  D_COUT("Testing AStack<SI" << sizeof(T) << ",SI" << sizeof(SIZ) << ">...\n");

  AStack<T, SIZ, 8> stack;

  D_COUT(Linef("\n+---\n| TUIB: size:")
         << stack.AJT().Buffer().Size() << " expected_size_bytes:"
         << stack.AJT().Buffer().Size() * sizeof(T) + sizeof(TStack<SIZ>)
         << " size_bytes:" << stack.AJT().Buffer().SizeBytes()
         << " size_words:" << stack.AJT().Buffer().SizeWords());
  D_COUT_OBJ(stack);

  enum { kTestCount = 32, kOffset = '0' };
  D_COUT("\n\nPushing " << kTestCount << " items on to the Stack...\n");
  for (T i = kOffset; i <= kTestCount + kOffset; ++i) {
    D_COUT("\n| Before calling push:"
           << Charsf(stack.AJT().Begin(), stack.AJT().SizeBytes())
           << Linef("\n\n+---\n| ") << i << ".) ");
    stack.Push(i);
    D_COUT("\n| Result:");
    D_COUT_OBJ(stack);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack...\n"));

  for (T test_count = kTestCount + kOffset; test_count >= kOffset;
       --test_count) {
    D_COUT_OBJ(stack);
    A_AVOW_INDEX(test_count, stack.Pop(), test_count);
  }
  D_COUT_OBJ(stack);
  A_ASSERT(stack.Count() == 0);
}
#endif

static const CH1* Stack(const CH1* args) {
#if SEAM >= SCRIPT2_STACK

  D_COUT(Headingf("Test ArrayCopy and MemoryCompare"));

  enum {
    kTestCharsCount = 1024,
    kTestCharsOffsetCount = 16,
  };
  CH1 test_chars[kTestCharsCount];
  CH1 test_chars_result[kTestCharsCount + kTestCharsOffsetCount];

  D_COUT("\ntest_chars[0]:0x" << Hexf(test_chars) << " test_chars_result[n]:0x"
                              << Hexf(test_chars_result));

  for (SI4 i = 0; i < kTestCharsOffsetCount; ++i) {
    for (SI4 j = 0; j < kTestCharsCount; ++j) test_chars[j] = (CH1)(j % 256);
    CH1* result = ArrayCopy(test_chars_result + i, kTestCharsCount, test_chars,
                            kTestCharsCount);
    A_ASSERT(result);
    A_ASSERT(!ArrayCompare(test_chars + i, kTestCharsCount, test_chars_result,
                           kTestCharsCount));
  }

  A_TEST_BEGIN;

  // TestStack<SI4, SI8>(args); is illegal
  TestStack<SI4, SI4>(args);
  TestStack<SI8, SI8>(args);
  TestStack<SI8, SI4>(args);
#endif
  return nullptr;
}
}  // namespace script2
