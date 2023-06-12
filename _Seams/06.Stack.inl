/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/06.Stack.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
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
  D_COUT("Testing AStack<IS" << CHA('@' + sizeof(T)) << ",IS" << CHA('@' + sizeof(ISZ)) << ">...\n");

  AStack<T, ISZ, 8> stack;

  D_COUT(Linef("\n+---\n| TBUF: size:")
         << stack.AJT().Buffer().Size() << " expected_size_bytes:"
         << stack.AJT().Buffer().Size() * sizeof(T) + sizeof(TStack<ISZ>)
         << " size_bytes:" << stack.AJT().Buffer().SizeBytes()
         << " size_words:" << stack.AJT().Buffer().SizeWords());
  D_COUT_OBJ(stack);

  enum { TestCount = 32 };
  D_COUT("\n\nPushing " << TestCount << " items on to the Stack...\n");
  T i;
  for (i = 0; i < TestCount; ++i) {
    D_COUT("\n| " << i << ".) count:" <<
           stack.Count());
    //D_COUT("\n| Before calling push:" << 
    //       Charsf(stack.AJT().Origin(), stack.AJT().SizeBytes()) << 
    //       Linef("\n\n+---\n| ") << i << ".) ");
    stack.Push('0' + i);
    //D_COUT("\n| Result:");
    //D_COUT_OBJ(stack);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack... ") << "i:" << i << 'n');
  for (i=i-1; i >= 0; --i) {
    //D_COUT_OBJ(stack);
    A_AVOW_INDEX(i, stack.Pop() - '0', i);
    D_COUT("\n| " << i << ".) Popping count:" << stack.Count());
  }
  D_COUT("\n\nEnding stack.Count(): " << stack.Count() << " i: " << 
         i << '\n');
  D_COUT_OBJ(stack);
  A_ASSERT(stack.Count() == 0);
}
#endif

static const CHA* Stack(const CHA* args) {
#if SEAM >= SCRIPT2_STACK
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing ArrayCompare with offset sequential arrays..."));

  enum {
    Offset = 2 * sizeof(IUW),
    TestByteCount = 256,
    BufferSizeBytes = TestByteCount + 2 * Offset,
    BufferSizeWords = BufferSizeBytes >> WordBitCount,
  };
  for (ISN a_offset = 0; a_offset < Offset; ++a_offset) {
    // Create an array of bytes valued sequentially 0 through 255.
    // i is the offset of the source array and b_offset is the offset of the 
    // desination array so we can check all memory alignment configurations.
    IUW source[BufferSizeWords];
    IUA* cursor = TPtr<IUA>(source), * end = cursor + BufferSizeBytes;
    // @todo We only need to zero out the i-b_offset bytes
    for (ISN b_offset = a_offset; b_offset > 0; --b_offset) *cursor++ = 0;
    for (ISN b_offset = 0; b_offset < TestByteCount; ++b_offset)
      *cursor++ = ISA(b_offset);
    while (cursor < end) *cursor++ = 0;
    //D_COUT(Charsf(source, cBufferSizeBytes));
    // Copy those bytes into a buffer with an offset to exaustly test each 
    // memory layout variation modulo the word size.
    IUW destination[BufferSizeWords];
    for (ISN b_offset = 0; b_offset < Offset; ++b_offset) {
      //D_COUT("\na_offset: " << a_offset << " b_offset: " << b_offset);
      ArrayFill(destination, BufferSizeBytes, 0);
      IUA* a_start = TPtr<IUA>(source) + a_offset, 
         * b_start = TPtr<IUA>(destination) + b_offset;
      auto result = ArrayCopy(b_start, BufferSizeBytes,
                              TPtr<IUA>(source) + a_offset, TestByteCount);
      if (result == 0) {
        D_COUT("\n\nArrayCopy failed!\nsource:\n" << 
               Charsf(source, TestByteCount));
        D_COUT("\ndestination:\n" << Charsf(destination, TestByteCount));
        D_ASSERT(result != 0);
      }
      result = ArrayCompareSlow(a_start, TestByteCount, b_start, TestByteCount);
      if (result <= 0) {
        result = result * -1 - 1;
        D_COUT("\n\nArrayCompareSlow failed at byte " << result << 
               " with i:" << a_offset << " b_offset:" << b_offset <<
               "\na_cursor[-1]: " << Hexf(*(a_start + result - 1)) <<
               "  b_cursor[-1]: " << Hexf(*(b_start + result - 1)) <<
               "\na_cursor[ 0]: " << Hexf(*(a_start + result    )) <<
               "  b_cursor[ 0]: " << Hexf(*(b_start + result    )) <<
               "\na_cursor[+1]: " << Hexf(*(a_start + result + 1)) <<
               "  b_cursor[+1]: " << Hexf(*(b_start + result + 1)) <<
               "\n\nsource:"      << Charsf(source, BufferSizeBytes) <<
               "\n\ndestination:" << Charsf(destination, BufferSizeBytes));
        A_ASSERT(result < 0);
      }
      for (ISN k = TestByteCount - 1; k > 0; --k) {
        result = ArrayCompareFast(a_start, TestByteCount - k, b_start,
                                  TestByteCount - k);
        if (result <= 0) {
          result = result * -1 - 1;
          D_COUT(
              "\n\nArrayCompareFast failed at byte " << result << 
              " with a_offset:" << a_offset << " b_offset:" << b_offset << 
              "\na_cursor[-1]: " << Hexf(*(a_start + result - 1)) << 
              "  b_cursor[-1]: " << Hexf(*(b_start + result - 1)) << 
              "\na_cursor[ 0]: " << Hexf(*(a_start + result    )) << 
              "  b_cursor[ 0]: " << Hexf(*(b_start + result    )) << 
              "\na_cursor[+1]: " << Hexf(*(a_start + result + 1)) << 
              "  b_cursor[+1]: " << Hexf(*(b_start + result + 1)) << 
              "\n\nsource:"      << Charsf(source, BufferSizeBytes) << 
              "\n\ndestination:" << Charsf(destination, BufferSizeBytes));
          A_ASSERT(result < 0);
        }
      }
    }
  }

  D_COUT(Headingf("Test ArrayCopy and MemoryCompare"));

  IUA source[TestByteCount + Offset],
      destination[TestByteCount + Offset];

  for (IUW s_offset = 0; s_offset < Offset; 
      ++s_offset) {
    for (IUW d_offset = 0; d_offset < Offset;
         ++d_offset) {
      IUA* a_cursor = source;
      for (IUW i = 0; i < s_offset; ++i) *a_cursor++ = 0;
      for (IUW i = 0; i < TestByteCount; ++i) *a_cursor++ = IUA(i);
      for (IUW i = 0; i < Offset - s_offset; ++i)
        *a_cursor++ = 0;

      IUA* s_start = source + s_offset, 
         * d_start = destination + d_offset;
      ISW result = ArrayCopySlow(s_start, d_start, TestByteCount);
      A_ASSERT(result == TestByteCount);
      result = ArrayCompareSlow(source + s_offset, TestByteCount,
                                destination, TestByteCount);
      if (result <= 0) {
        D_COUT("\n\nArrayCompareFast failed at byte: " << result << 
               "\n\nsource:" << Charsf(source, TestByteCount + Offset) << 
               "\n\ndestination:" << Charsf(destination, TestByteCount + Offset));
        A_ASSERT(result >= 0);
      }
    }
  }

  D_COUT(Headingf("TestStack"));

  // TestStack<ISC, ISD>(args); is illegal
  TestStack<ISC, ISC>(args);
  TestStack<ISD, ISD>(args);
  TestStack<ISD, ISC>(args);
#endif
  return nullptr;
}
}  //< namespace Script2
