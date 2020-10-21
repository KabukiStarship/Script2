/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/06.Stack.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_STACK
#include "../Stack.hpp"
using namespace _;
#if SEAM == SCRIPT2_STACK
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {

#if SEAM >= SCRIPT2_STACK
template <typename T, typename ISZ>
void TestStack(const CHA* args) {
  D_COUT("Testing AStack<IS" << sizeof(T) << ",IS" << sizeof(ISZ) << ">...\n");

  AStack<T, ISZ, 8> stack;

  D_COUT(Linef("\n+---\n| TBUF: size:")
         << stack.AJT().Buffer().Size() << " expected_size_bytes:"
         << stack.AJT().Buffer().Size() * sizeof(T) + sizeof(TStack<ISZ>)
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

static const CHA* Stack(const CHA* args) {
#if SEAM >= SCRIPT2_STACK

  D_COUT(Headingf("Test ArrayCopy and MemoryCompare"));

  enum {
    cTestCharsCount = 1024,
    cTestCharsOffsetCount = 16,
  };
  CHA test_chars[cTestCharsCount];
  CHA test_chars_result[cTestCharsCount + cTestCharsOffsetCount];

  D_COUT("\ntest_chars[0]:0x" << Hexf(test_chars) << " test_chars_result[n]:0x"
                              << Hexf(test_chars_result));

  for (ISC i = 0; i < cTestCharsOffsetCount; ++i) {
    for (ISC j = 0; j < cTestCharsCount; ++j) test_chars[j] = (CHA)(j % 256);
    CHA* result = ArrayCopy(test_chars_result + i, cTestCharsCount, test_chars,
                            cTestCharsCount);
    A_ASSERT(result);
    A_ASSERT(!ArrayCompare(test_chars + i, cTestCharsCount, test_chars_result,
                           cTestCharsCount));
  }

  A_TEST_BEGIN;

  // TestStack<ISC, ISD>(args); is illegal
  TestStack<ISC, ISC>(args);
  TestStack<ISD, ISD>(args);
  TestStack<ISD, ISC>(args);
#endif
  return nullptr;
}
}  // namespace Script2
