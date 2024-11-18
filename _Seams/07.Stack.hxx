// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_STACK
#include "../Stack.hpp"
using namespace ::_;
#if SEAM == SCRIPT2_STACK
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif
namespace Script2 {

#if SEAM >= SCRIPT2_STACK
template<typename T, typename IS>
void TestStack(const CHA* args) {
  D_COUT("Testing AStack<IS" << CHA('@' + sizeof(T)) << ",IS" << 
         CHA('@' + sizeof(IS)) << ">...\n");

  AStack<T, IS, 8> stack;

  D_COUT(Linef("\n+---\n| TBUF: size:")
         << stack.AJT().Boofer().Size() << " expected_bytes:"
         << stack.AJT().Boofer().Size() * sizeof(T) + sizeof(TStack<IS>)
         << " bytes:" << stack.AJT().Boofer().SizeBytes()
         << " size_words:" << stack.AJT().Boofer().SizeWords());
  D_COUT_OBJ(stack);

  enum { TestCount = 32 };
  D_COUT("\n\nPushing " << TestCount << " items on to the Stack...\n");
  T i;
  auto count_start = stack.Count();
  for (i = 0; i < TestCount; ++i) {
    D_COUT("\n| " << i << ".) count:" << stack.Count());
    D_COUT("\n| Before calling push:" << 
           Charsf(stack.AJT().Origin(), stack.AJT().SizeBytes()) << 
           Linef("\n\n+---\n| ") << i << ".) ");
    auto result = stack.Push('0' + i);
    D_COUT("\n| Result:" << result);
    D_COUT_OBJ(stack);
    D_AVOW(IS(count_start + i), result);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack... ") << "i:" << i << 'n');
  #if SEAM == SCRIPT2_STACK
  TStackPrint<_::COut, T, IS>(StdOut(), stack.This());
  #endif
  for (i=i-1; i >= 0; --i) {
    //D_COUT_OBJ(stack);
    auto value = stack.Pop();
    A_AVOW_INDEX(i, value - '0', i);
    D_COUT("\n| " << i << ".) Popping " << value << " count:" << stack.Count());
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

  D_COUT(Headingf("Testing RAMCompare with offset sequential arrays..."));

  enum {
    OffsetMax = 2 * ALUSize,
    TestByteCount = 256,
    BooferSizeBytes = TestByteCount + 2 * OffsetMax,
    BooferSizeWords = BooferSizeBytes >> WordSizeLog2,
  };
  IUW source[BooferSizeWords],
      destination[BooferSizeWords + OffsetMax];
  for (ISN s_offset = 0; s_offset < OffsetMax; ++s_offset) {
    // Create an array of bytes valued sequentially 0 through 255.
    // i is the offset of the source array and d_offset is the offset of the 
    // desination array so we can check all memory alignment configurations.
    IUA* cursor  = TPtr<IUA>(source),
       * s_end   = cursor + BooferSizeBytes,
       * s_start = TPtr<IUA>(source) + s_offset;
    // @todo We only need to zero out the i-d_offset bytes
    while (cursor < s_start) *cursor++ = 0;
    for (ISN i = 0; i < TestByteCount; ++i) *cursor++ = ISA(i);
    while (cursor < s_end) *cursor++ = 0;
    //D_COUT(Charsf(source, cBooferSizeBytes));
    // Copy those bytes into a boofer with an offset to exaustly test each 
    // memory layout variation modulo the word size.
    for (ISN d_offset = 0; d_offset < OffsetMax; ++d_offset) {
      cursor = TPtr<IUA>(destination);
      IUA * d_start = cursor + d_offset,
          * d_end = d_start + BooferSizeBytes;
      while (cursor < d_start) *cursor++ = 0;
      for (ISN i = 0; i < TestByteCount; ++i)
        *cursor++ = ISA(i);
      while (cursor < d_end) *cursor++ = 0;

      ISW result = ArrayCompareSlow(s_start, TestByteCount, d_start, 
                                    TestByteCount);
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
               "\n\nsource:"      << Charsf(source, BooferSizeBytes) <<
               "\n\ndestination:" << Charsf(destination, BooferSizeBytes));
        A_ASSERT(result < 0);
      }
      for (ISN k = TestByteCount - 1; k > 0; --k) {
        result = ArrayCompareFast(s_start, ISW(TestByteCount) - k, d_start,
                                  ISW(TestByteCount) - k);
        if (result <= 0) {
          result = result * -1 - 1;
          D_COUT("\n\nArrayCompareFast failed at byte " << result << 
                 " with s_offset:" << s_offset << " d_offset:" << d_offset << 
                 "\na_cursor[-1]: " << Hexf(*(s_start + result - 1)) << 
                 "  b_cursor[-1]: " << Hexf(*(d_start + result - 1)) << 
                 "\na_cursor[ 0]: " << Hexf(*(s_start + result    )) << 
                 "  b_cursor[ 0]: " << Hexf(*(d_start + result    )) << 
                 "\na_cursor[+1]: " << Hexf(*(s_start + result + 1)) << 
                 "  b_cursor[+1]: " << Hexf(*(d_start + result + 1)) << 
                 "\n\nsource:"      << Charsf(source, BooferSizeBytes) << 
                 "\n\ndestination:" << Charsf(destination, BooferSizeBytes));
          A_ASSERT(result < 0);
        }
      }
    }
  }

  D_COUT(Headingf("Test RAMCopy"));

  for (IUW s_offset = 0; s_offset < OffsetMax; ++s_offset) {
    for (IUW d_offset = 0; d_offset < OffsetMax; ++d_offset) {
      //D_COUT("\n\ns_offset: " << s_offset << "  d_offset: " << d_offset);
      RAMFill(destination, BooferSizeBytes, 0);
      IUA* cursor = TPtr<IUA>(source);

      for (IUW i = 0; i < s_offset; ++i) *cursor++ = 0;
      for (IUW i = 0; i < TestByteCount; ++i) *cursor++ = IUA(i);
      for (IUW i = 0; i < OffsetMax - s_offset; ++i) *cursor++ = 0;
      IUA *s_start = TPtr<IUA>(source) + s_offset,
          *d_start = TPtr<IUA>(destination) + d_offset;
      
      ISW result = ArrayCopyFast(d_start, TestByteCount, s_start, 
                                 TestByteCount);
      A_ASSERT(result == TestByteCount);
      //D_COUT("\n\nsource:" << Charsf(source, BooferSizeBytes) << 
      //       "\n\ndestination:" << Charsf(destination, BooferSizeBytes));
      result = ArrayCompareSlow(s_start, TestByteCount, d_start, TestByteCount);
      if (result <= 0) {
        D_COUT("\n\nArrayCompareFast failed at byte: " << result << 
               "\n\nsource:" << Charsf(source, BooferSizeBytes) << 
               "\n\ndestination:" << Charsf(destination, BooferSizeBytes));
        A_ASSERT(result >= 0);
      }
      d_start = TPtr<IUA>(destination);
      for (IUW i = 0; i < d_offset; ++i) {
        IUA current = *d_start++;
        if (current != 0) {
          D_COUT("\n\nArrayCompareFast printed bad data at byte: " << i <<
                 "\nd_offset: " << d_offset <<
                 "\n\nsource:" << Charsf(source, BooferSizeBytes) << 
                 "\n\ndestination:" << Charsf(destination, BooferSizeBytes));
          A_ASSERT(current == 0);
        }
      }
      d_start = TPtr<IUA>(destination) + d_offset + TestByteCount;
      IUA* d_end = TPtr<IUA>(destination) + BooferSizeBytes;
      for (IUW i = 0; i < (OffsetMax - d_offset); ++i) {
        IUA current = *d_start++;
        if (current != 0) {
          D_COUT("\n\nArrayCompareFast printed bad data at byte: "
                 << TDelta(destination, d_start)
                 << "\n\nsource:" << Charsf(source, BooferSizeBytes)
                 << "\n\ndestination:" << Charsf(destination, BooferSizeBytes));
          A_ASSERT(current == 0);
        }
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
