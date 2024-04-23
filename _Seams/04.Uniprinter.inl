/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/04.Uniprinter.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_UNIPRINTER
#include "../Uniprinter.hpp"
using namespace _;
#if SEAM == SCRIPT2_UNIPRINTER
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
#if SEAM >= SCRIPT2_UNIPRINTER
template<typename CHT = CHR, typename IS = ISN>
static const CHA* TestSPrinter() {
  D_COUT(Linef('-') << "\n\n\nTesting UTF<CH" << sizeof(CHT) << ",IS"
                    << sizeof(IS) << ">\n\n"
                    << Linef('-'));
  enum {
    Count = 512,
  };
  CHT str_a[Count];
  static const CHT Testing123[] = { 'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL };

  D_ARRAY_WIPE(str_a, Count * sizeof(CHT));
  TSPrint<CHT>(str_a, Count, Testing123);
  D_COUT(Charsf(str_a, 64));

  TSPrinter<CHT> utf(str_a, Count);

  enum { TestStringsCount = 4 };

  const CHT TestStrings[5][2][7] = {{{'?', NIL, NIL, NIL, NIL, NIL, NIL},
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
  for (ISC i = 0; i < TestStringsCount; ++i) {
    D_ARRAY_WIPE(str_a, Count * sizeof(CHT));
    cursor = TSPrintString<CHT>(str_a, str_a + Count, TestStrings[i][0]);
    D_COUT(Charsf(str_a, 64));
    Test(cursor);
    cursor = TSTREquals<CHT>(str_a, TestStrings[i][0]);
    Test(cursor);
  }

  D_COUT(Headingf("Testing TSPrinter<CHT>")
         << "\n\nExpecting \"" << Testing123 << '\"');
  static const CHT CommaSpace[] = {',', ' ', NIL};

  const CHT kTestingSpace[] = {'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL};

  D_ARRAY_WIPE(str_a, Count * sizeof(CHT));

  utf.Set(str_a).Print(kTestingSpace);
  utf.Print(1);
  utf.Print(CommaSpace);
  utf.Print(2);
  utf.Print(", ");
  utf.Print(3);
  utf.Print('.');

  utf.Set(str_a) << kTestingSpace << 1 << CommaSpace << 2 << ", " << 3 << '.';
  D_COUT(Charsf(str_a, 64));
  A_AVOW(Testing123, str_a);

  D_COUT("\n\nTesting TSTREquals<CHT>");

  const CHT CompareStrings[4][9] = {
      {'T', 'e', 's', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 's', 't', 'i', 'n', 'g', '@', NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', '@', NIL},
  };

  A_ASSERT(!TSTREquals<CHT>(CompareStrings[0], CompareStrings[1]));
  A_ASSERT(!TSTREquals<CHT>(CompareStrings[0], CompareStrings[3]));
  A_ASSERT(TSTREquals<CHT>(CompareStrings[0], CompareStrings[0]));
  A_ASSERT(!TSTREquals<CHT>(CompareStrings[2], CompareStrings[3]));
  A_ASSERT(TSTREquals<CHT>(CompareStrings[2], CompareStrings[2]));

  const CHT Chars1to9[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', NIL};
  A_AVOW(9, TSTRLength<CHT>(Chars1to9));

  D_COUT("\n\nTesting TSTRFind<CHT>");

  const CHT One[] = {'1', ',', NIL};
  const CHT ThreePeriod[] = {'3', '.', NIL};
  A_ASSERT(TSTRFind<CHT>(Testing123, One));
  A_ASSERT(TSTRFind<CHT>(Testing123, ThreePeriod));

  D_COUT(Headingf("Testing TPrintRight<CHT>"));

  const CHT RightAligned[12][13] = {
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

  ISC shift_right = 6;
  for (ISC i = 0; i < 12; ++i) {
    D_ARRAY_WIPE(str_a, (ISW)(Count * sizeof(CHT)));
    cursor = TPrintRight<CHT>(str_a, str_a + Count - 1, kTestingSpace, i + 1);
    D_ASSERT_INDEX(cursor, i);
    D_COUT(Charsf(str_a, 64)
           << "\n    Wrote:\"" << str_a << "\":" << TSTRLength<CHT>(str_a));
    A_AVOW_INDEX(&RightAligned[i][0], str_a, i);
  }
  D_COUT(Headingf("Testing TPrintCenter<CHT>"));

  const CHT CenterAligned[13][14] = {
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

  static const CHT Numbers1To9[] = {'1', '2', '3', '4', '5',
                                    '6', '7', '8', '9', NIL};

  for (ISC i = 12; i >= 0; --i) {
    D_ARRAY_WIPE(str_a, Count * sizeof(CHT));
    cursor = TPrintCenter<CHT>(str_a, str_a + Count - 1, Numbers1To9, i + 1);
    D_ASSERT_INDEX(cursor, i);
    D_COUT(Charsf(str_a, 64)
           << "\n    Wrote:\"" << str_a << "\":" << TSTRLength<CHT>(str_a));
    A_AVOW_INDEX(&CenterAligned[i][0], str_a, i);
  }

  return nullptr;
}

static const CHA* TestSPrinter() {
  A_TEST_BEGIN;
  if (TestSPrinter<CHA, ISC>()) return "Error testing SPrinter UTF-8.";
#if USING_UTF16 == YES_0
  if (TestSPrinter<CHB, ISC>()) return "Error testing SPrinter UTF-16.";
#endif
#if USING_UTF32 == YES_0
  if (TestSPrinter<CHC, ISC>()) return "Error testing SPrinter UTF-32.";
#endif
  return nullptr;
}

static const CHR* TestATypef() {
  D_COUT("Testing ATypef...");
  // ATypef was the first class that implemented the new Center and Right 
  // functions that return Centerf and Right respectivly. I'm not very conserned
  // about the types being printed right so much as I am in testing said
  // funcationality.
  auto o = ::_::StdOut();
  CHA buffer[256];
  buffer[255] = 0;
  TSPrinter<CHA, ISW> p(buffer, 1024);
  TPrintAType<TSPrinter<CHA, ISW>>(p, ATypePack(_ISA, _STK));

  o << "\n\nResult:\n\"" <<  buffer << '\"';
  return nullptr;
}

#endif  //< #if SEAM >= SCRIPT2_UNIPRINTER

static const CHA* Uniprinter(const CHA* args) {
#if SEAM >= SCRIPT2_UNIPRINTER
  D_RUN(TestSPrinter);
  D_RUN(TestATypef);
#endif
  return nullptr;
}
}  //< namespace Script2
