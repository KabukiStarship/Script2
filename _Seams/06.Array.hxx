// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_ARRAY
#include "../Array.hpp"
using namespace ::_;
#if SEAM == CRABS_ARRAY
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
namespace Crabs {

#if SEAM >= CRABS_ARRAY
template<typename T, typename ISZ>
void TestArray(const CHA* args) {
  D_COUT("Testing AArray<ISZ" << CHA('@' + sizeof(T)) << ",ISZ" << 
         CHA('@' + sizeof(ISZ)) << ">...\n");

  AArray<T, ISZ, 8> array;

  D_COUT(Linef("\n+---\n| AArray: total:") << array.Total() << 
         " bytes:" << array.Bytes() << " size_words:" << array.SizeWords());
  D_COUT_OBJ(array);
}
#endif

static const CHA* Array(const CHA* args) {
#if SEAM >= CRABS_ARRAY
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing RAMCompare with offset sequential arrays..."));

  enum {
    OffsetMax = 2 * ACPUBytes,
    TestByteCount = 256,
    BooferSizeBytes = TestByteCount + 2 * OffsetMax,
    BooferSizeWords = BooferSizeBytes >> ACPUBytesLog2,
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

  D_COUT(Headingf("Test ArrayCopy"));

  for (IUW s_offset = 0; s_offset < OffsetMax; ++s_offset) {
    for (IUW d_offset = 0; d_offset < OffsetMax; ++d_offset) {
      //D_COUT("\n\ns_offset: " << s_offset << "  d_offset: " << d_offset);
      ArrayFill(destination, BooferSizeBytes, 0);
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
  D_COUT(Headingf("TestArray"));

  // TestArray<ISC, ISD>(args); is illegal
  TestArray<ISC, ISC>(args);
  TestArray<ISD, ISD>(args);
  TestArray<ISD, ISC>(args);
#endif
  return NILP;
}
}  //< namespace Crabs
