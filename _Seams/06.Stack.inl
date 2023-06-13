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
    OffsetMax = 2 * WordByteCount,
    TestByteCount = 256,
    BufferSizeBytes = TestByteCount + 2 * OffsetMax,
    BufferSizeWords = BufferSizeBytes >> WordBitCount,
  };
  for (ISN s_offset = 0; s_offset < OffsetMax; ++s_offset) {
    // Create an array of bytes valued sequentially 0 through 255.
    // i is the offset of the source array and d_offset is the offset of the 
    // desination array so we can check all memory alignment configurations.
    IUW source[BufferSizeWords];
    IUA* cursor = TPtr<IUA>(source),
       * s_end   = cursor + BufferSizeBytes,
       * s_start = TPtr<IUA>(source) + s_offset;
    // @todo We only need to zero out the i-d_offset bytes
    while (cursor < s_start) *cursor++ = 0;
    for (ISN i = 0; i < TestByteCount; ++i) *cursor++ = ISA(i);
    while (cursor < s_end) *cursor++ = 0;
    //D_COUT(Charsf(source, cBufferSizeBytes));
    // Copy those bytes into a buffer with an offset to exaustly test each 
    // memory layout variation modulo the word size.
    IUW destination[BufferSizeWords];
    for (ISN d_offset = 0; d_offset < OffsetMax; ++d_offset) {
      cursor = TPtr<IUA>(destination);
      IUA *d_start = cursor + d_offset,
         * d_end = d_start + BufferSizeBytes;
      while (cursor < d_start) *cursor++ = 0;
      for (ISN i = 0; i < TestByteCount; ++i)
        *cursor++ = ISA(i);
      while (cursor < d_end) *cursor++ = 0;

      ISW result = ArrayCompareSlow(s_start, TestByteCount, d_start, TestByteCount);
      if (result <= 0) {
        result = result * -1 - 1;
        D_COUT("\n\nArrayCompareSlow failed at byte " << result << 
               " with s_offset:" << s_offset << " d_offset:" << d_offset <<
               "\na_cursor[-1]: " << Hexf(*(s_start + result - 1)) <<
               "  b_cursor[-1]: " << Hexf(*(d_start + result - 1)) <<
               "\na_cursor[ 0]: " << Hexf(*(s_start + result    )) <<
               "  b_cursor[ 0]: " << Hexf(*(d_start + result    )) <<
               "\na_cursor[+1]: " << Hexf(*(s_start + result + 1)) <<
               "  b_cursor[+1]: " << Hexf(*(d_start + result + 1)) <<
               "\n\nsource:"      << Charsf(source, BufferSizeBytes) <<
               "\n\ndestination:" << Charsf(destination, BufferSizeBytes));
        A_ASSERT(result < 0);
      }
      for (ISN k = TestByteCount - 1; k > 0; --k) {
        result = ArrayCompareFast(s_start, TestByteCount - k, d_start,
                                  TestByteCount - k);
        if (result <= 0) {
          result = result * -1 - 1;
          D_COUT(
              "\n\nArrayCompareFast failed at byte " << result << 
              " with s_offset:" << s_offset << " d_offset:" << d_offset << 
              "\na_cursor[-1]: " << Hexf(*(s_start + result - 1)) << 
              "  b_cursor[-1]: " << Hexf(*(d_start + result - 1)) << 
              "\na_cursor[ 0]: " << Hexf(*(s_start + result    )) << 
              "  b_cursor[ 0]: " << Hexf(*(d_start + result    )) << 
              "\na_cursor[+1]: " << Hexf(*(s_start + result + 1)) << 
              "  b_cursor[+1]: " << Hexf(*(d_start + result + 1)) << 
              "\n\nsource:"      << Charsf(source, BufferSizeBytes) << 
              "\n\ndestination:" << Charsf(destination, BufferSizeBytes));
          A_ASSERT(result < 0);
        }
      }
    }
  }

  D_COUT(Headingf("Test ArrayCopy"));

  IUA source[TestByteCount + OffsetMax],
      destination[TestByteCount + OffsetMax];
  for (IUW s_offset = 0; s_offset < OffsetMax; ++s_offset) {
    for (IUW d_offset = 0; d_offset < OffsetMax; ++d_offset) {
      //D_COUT("\n\ns_offset1: " << s_offset << "  d_offset1: " << d_offset);
      IUA* cursor = source;

      for (IUW i = 0; i < s_offset; ++i) *cursor++ = 0;
      for (IUW i = 0; i < TestByteCount; ++i) *cursor++ = IUA(i);
      for (IUW i = 0; i < OffsetMax - s_offset; ++i) *cursor++ = 0;
      cursor = destination;
      while (cursor < destination + TestByteCount + OffsetMax) *cursor++ = 0;
      IUA* s_start = source + s_offset,
         * d_start = destination + d_offset;
      
      ISW result = ArrayCopyFast(d_start, TestByteCount, s_start, TestByteCount);
      A_ASSERT(result == TestByteCount);
      //D_COUT("\n\nsource:" << Charsf(source, TestByteCount + OffsetMax) << 
      //       "\n\ndestination:" << Charsf(destination, TestByteCount + OffsetMax));
      result = ArrayCompareSlow(s_start, TestByteCount, d_start, TestByteCount);
      if (result <= 0) {
        D_COUT("\n\nArrayCompareFast failed at byte: " << result << 
               "\n\nsource:" << Charsf(source, TestByteCount + OffsetMax) << 
               "\n\ndestination:" << Charsf(destination, TestByteCount + OffsetMax));
        A_ASSERT(result >= 0);
      }
    }
  }
  D_COUT(Headingf("TestStack"));
  D_ASSERT(false);

  // TestStack<ISC, ISD>(args); is illegal
  TestStack<ISC, ISC>(args);
  TestStack<ISD, ISD>(args);
  TestStack<ISD, ISC>(args);
#endif
  return nullptr;
}
}  //< namespace Script2
