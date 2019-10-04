/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/04.sprinter.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_SPRINTER
#include "../array.hpp"
#include "../stringf.hpp"
using namespace _;
#if SEAM == SCRIPT2_SPRINTER
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
#if SEAM >= SCRIPT2_SPRINTER
template <typename CHT = CHR, typename SIZ = SIN>
static const CHT* TestSPrinter() {
  D_COUT(Linef('-') << "\n\n\nTesting UTF<CH" << sizeof(CHT) << ",SI"
                    << sizeof(SIZ) << ">\n\n"
                    << Linef('-'));

  enum {
    cCount = 512,
  };

  CHT str_a[cCount];

  static const CHT kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};

  D_ARRAY_WIPE(str_a, cCount * sizeof(CHT));
  TSPrint<CHT>(str_a, cCount, kTesting123);
  D_COUT(Charsf(str_a, 64));

  TSPrinter<CHT> utf(str_a, cCount);

  enum { cTestStrandsCount = 4 };

  const CHT kTestStrands[5][2][7] = {{{'?', NIL, NIL, NIL, NIL, NIL, NIL},
                                       {NIL, NIL, NIL, NIL, NIL, NIL, NIL}},
                                      {{'?', NIL, NIL, NIL, NIL, NIL, NIL},
                                       {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
                                      {{'?', ' ', NIL, NIL, NIL, NIL, NIL},
                                       {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
                                      {{'A', 'p', 'p', 'l', 'e', 's', NIL},
                                       {'A', 'p', 'p', 'l', 'e', 's', NIL}},
                                      {{'A', 'p', 'p', 'l', 'e', 's', NIL},
                                       {'A', 'p', 'p', 'l', 'e', 's', NIL}}};
  const CHT* cursor;
  for (SI4 i = 0; i < cTestStrandsCount; ++i) {
    D_ARRAY_WIPE(str_a, cCount * sizeof(CHT));
    cursor = TSPrintString<CHT>(str_a, str_a + cCount, kTestStrands[i][0]);
    D_COUT(Charsf(str_a, 64));
    Test(cursor);
    cursor = TSTREquals<CHT>(str_a, kTestStrands[i][0]);
    Test(cursor);
  }

  D_COUT(Headingf("Testing TSPrinter<CHT>")
         << "\n\nExpecting \"" << kTesting123 << '\"');
  static const CHT kCommaSpace[] = {',', ' ', NIL};

  const CHT kTestingSpace[] = {'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL};

  D_ARRAY_WIPE(str_a, cCount * sizeof(CHT));

  utf.Set(str_a).Print(kTestingSpace);
  utf.Print(1);
  utf.Print(kCommaSpace);
  utf.Print(2);
  utf.Print(", ");
  utf.Print(3);
  utf.Print('.');

  utf.Set(str_a) << kTestingSpace << 1 << kCommaSpace << 2 << ", " << 3 << '.';
  D_COUT(Charsf(str_a, 64));
  A_AVOW(kTesting123, str_a);

  D_COUT("\n\nTesting TSTREquals<CHT>");

  const CHT kCompareStrands[4][9] = {
      {'T', 'e', 's', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 's', 't', 'i', 'n', 'g', '@', NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', '@', NIL},
  };

  A_ASSERT(!TSTREquals<CHT>(kCompareStrands[0], kCompareStrands[1]));
  A_ASSERT(!TSTREquals<CHT>(kCompareStrands[0], kCompareStrands[3]));
  A_ASSERT(TSTREquals<CHT>(kCompareStrands[0], kCompareStrands[0]));
  A_ASSERT(!TSTREquals<CHT>(kCompareStrands[2], kCompareStrands[3]));
  A_ASSERT(TSTREquals<CHT>(kCompareStrands[2], kCompareStrands[2]));

  const CHT k1to9[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', NIL};
  A_AVOW(9, TSTRLength<CHT>(k1to9));

  D_COUT("\n\nTesting TSTRFind<CHT>");

  const CHT kOne[] = {'1', ',', NIL};
  const CHT kThreePeriod[] = {'3', '.', NIL};
  A_ASSERT(TSTRFind<CHT>(kTesting123, kOne));
  A_ASSERT(TSTRFind<CHT>(kTesting123, kThreePeriod));

  D_COUT(Headingf("Testing TPrintRight<CHT>"));

  const CHT kRightAligned[12][13] = {
      {'.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', 's', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', 's', 't', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL, NIL, NIL, NIL},
      {' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL, NIL, NIL},
      {' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL, NIL},
      {' ', ' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL},
      {' ', ' ', ' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL}};

  SI4 shift_right = 6;
  for (SI4 i = 0; i < 12; ++i) {
    D_ARRAY_WIPE(str_a, (SIW)(cCount * sizeof(CHT)));
    cursor = TPrintRight<CHT>(str_a, str_a + cCount - 1, kTestingSpace, i + 1);
    D_ASSERT_INDEX(cursor, i);
    D_COUT(Charsf(str_a, 64)
           << "\n    Wrote:\"" << str_a << "\":" << TSTRLength<CHT>(str_a));
    A_AVOW_INDEX(&kRightAligned[i][0], str_a, i);
  }
  D_COUT(Headingf("Testing TPrintCenter<CHT>"));

  const CHT kCentered[13][14] = {
      {'.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '5', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '5', '6', '7', '8', '9', NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', NIL, NIL, NIL, NIL},
      {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', NIL, NIL, NIL},
      {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', ' ', NIL, NIL},
      {' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', ' ', NIL}};

  static const CHT kNumbers[] = {'1', '2', '3', '4', '5',
                                  '6', '7', '8', '9', NIL};

  for (SI4 i = 12; i >= 0; --i) {
    D_ARRAY_WIPE(str_a, cCount * sizeof(CHT));
    cursor = TPrintCenter<CHT>(str_a, str_a + cCount - 1, kNumbers, i + 1);
    D_ASSERT_INDEX(cursor, i);
    D_COUT(Charsf(str_a, 64)
           << "\n    Wrote:\"" << str_a << "\":" << TSTRLength<CHT>(str_a));
    A_AVOW_INDEX(&kCentered[i][0], str_a, i);
  }

  return nullptr;
}
#endif  //< #if SEAM >= SCRIPT2_SPRINTER

static const CH1* SPrinter(const CH1* args) {
#if SEAM >= SCRIPT2_SPRINTER
  A_TEST_BEGIN;

  if (TestSPrinter<CH1, SI4>()) return "Error testing UTF-8.";

#if USING_UTF16 == YES_0
  if (TestSPrinter<CH2, SI4>()) return "Error testing UTF-16.";
#endif
#if USING_UTF32 == YES_0
  if (TestSPrinter<CH4, SI4>()) return "Error testing UTF-32.";
#endif
#endif
  return nullptr;
}
}  // namespace script2
