/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/06.stack.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_STACK
#include "../stack.hpp"
using namespace _;
#if SEAM == SCRIPT2_STACK
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

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

  enum { cTestCount = 32, cOffset = '0' };
  D_COUT("\n\nPushing " << cTestCount << " items on to the Stack...\n");
  for (T i = cOffset; i <= cTestCount + cOffset; ++i) {
    D_COUT("\n| Before calling push:"
           << Charsf(stack.AJT().Origin(), stack.AJT().SizeBytes())
           << Linef("\n\n+---\n| ") << i << ".) ");
    stack.Push(i);
    D_COUT("\n| Result:");
    D_COUT_OBJ(stack);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack...\n"));

  for (T test_count = cTestCount + cOffset; test_count >= cOffset;
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
    cTestCharsCount = 1024,
    cTestCharsOffsetCount = 16,
  };
  CH1 test_chars[cTestCharsCount];
  CH1 test_chars_result[cTestCharsCount + cTestCharsOffsetCount];

  D_COUT("\ntest_chars[0]:0x" << Hexf(test_chars) << " test_chars_result[n]:0x"
                              << Hexf(test_chars_result));

  for (SI4 i = 0; i < cTestCharsOffsetCount; ++i) {
    for (SI4 j = 0; j < cTestCharsCount; ++j) test_chars[j] = (CH1)(j % 256);
    CH1* result = ArrayCopy(test_chars_result + i, cTestCharsCount, test_chars,
                            cTestCharsCount);
    A_ASSERT(result);
    A_ASSERT(!ArrayCompare(test_chars + i, cTestCharsCount, test_chars_result,
                           cTestCharsCount));
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
