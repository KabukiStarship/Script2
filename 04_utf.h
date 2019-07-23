/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \04_utf.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "t_utf.h"

#if SEAM == SEAM_SCRIPT2_UTF
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

#if SEAM >= SEAM_SCRIPT2_UTF
namespace script2 {

template <typename Char, typename SIZ>
static const Char* _04_UTF() {
  D_COUT_LINEF('-');
  D_COUT_LINEF('-');
  D_PRINTF("\n\n\nTesting UTF<CH%c,SI%c>\n\n", '0' + sizeof(Char),
           '0' + sizeof(SIZ));
  D_COUT_LINEF('-');
  D_COUT_LINEF('-');

  enum {
    kCount = 512,
  };

  Char str_a[kCount], str_b[kCount];

  static const Char kTesting123[] = {'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL};

  D_SOCKET_WIPE(str_a, kCount * sizeof(Char));
  TPrint<Char>(str_a, kCount, kTesting123);
  D_COUT_CHARS(str_a, 64);

  TUTF<Char> utf(str_a, kCount);

  enum { kTestStrandsCount = 4 };

  const Char kTestStrands[5][2][7] = {{{'?', NIL, NIL, NIL, NIL, NIL, NIL},
                                       {NIL, NIL, NIL, NIL, NIL, NIL, NIL}},
                                      {{'?', NIL, NIL, NIL, NIL, NIL, NIL},
                                       {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
                                      {{'?', ' ', NIL, NIL, NIL, NIL, NIL},
                                       {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
                                      {{'A', 'p', 'p', 'l', 'e', 's', NIL},
                                       {'A', 'p', 'p', 'l', 'e', 's', NIL}},
                                      {{'A', 'p', 'p', 'l', 'e', 's', NIL},
                                       {'A', 'p', 'p', 'l', 'e', 's', NIL}}};
  const Char* cursor;
  for (SI4 i = 0; i < kTestStrandsCount; ++i) {
    D_SOCKET_WIPE(str_a, kCount * sizeof(Char));
    cursor = TPrintString<Char>(str_a, str_a + kCount, kTestStrands[i][0]);
    D_COUT_CHARS(str_a, 64);
    Test(cursor);
    cursor = TSTREquals<Char>(str_a, kTestStrands[i][0]);
    Test(cursor);
  }

  D_COUT(Headingf("Testing TUTF<Char>"));

  D_PRINTF("\n\nExpecting \"%s\"", kTesting123);
  static const Char kCommaSpace[] = {',', ' ', NIL};

  const Char kTestingSpace[] = {'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL};

  D_SOCKET_WIPE(str_a, kCount * sizeof(Char));

  utf.Set(str_a).Print(kTestingSpace);
  utf.Print(1);
  utf.Print(kCommaSpace);
  utf.Print(2);
  utf.Print(", ");
  utf.Print(3);
  utf.Print('.');

  utf.Set(str_a) << kTestingSpace << 1 << kCommaSpace << 2 << ", " << 3 << '.';
  D_COUT_CHARS(str_a, 64);
  A_AVOW(kTesting123, str_a);

  D_PRINTF("\n\nTesting TSTREquals<Char>");

  const Char kCompareStrands[4][9] = {
      {'T', 'e', 's', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 's', 't', 'i', 'n', 'g', '@', NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', '@', NIL},
  };

  A_ASSERT(!TSTREquals<Char>(kCompareStrands[0], kCompareStrands[1]));
  A_ASSERT(!TSTREquals<Char>(kCompareStrands[0], kCompareStrands[3]));
  A_ASSERT(TSTREquals<Char>(kCompareStrands[0], kCompareStrands[0]));
  A_ASSERT(!TSTREquals<Char>(kCompareStrands[2], kCompareStrands[3]));
  A_ASSERT(TSTREquals<Char>(kCompareStrands[2], kCompareStrands[2]));

  const Char k1to9[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', NIL};
  A_AVOW(9, TSTRLength<Char>(k1to9));

  D_PRINTF("\n\nTesting TSTRFind<Char>");

  const Char kOne[] = {'1', ',', NIL};
  const Char kThreePeriod[] = {'3', '.', NIL};
  A_ASSERT(TSTRFind<Char>(kTesting123, kOne));
  A_ASSERT(TSTRFind<Char>(kTesting123, kThreePeriod));

  D_COUT(Headingf("Testing TPrintRight<Char>"));

  const Char kRightAligned[12][13] = {
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
    D_SOCKET_WIPE(str_a, (SIW)(kCount * sizeof(Char)));
    cursor = TPrintRight<Char>(str_a, str_a + kCount - 1, kTestingSpace, i + 1);
    D_COUT_CHARS(str_a, 64);
    D_ASSERT_INDEX(cursor, i);
    D_PRINTF("\n    Wrote:\"%s\":%i", str_a, TSTRLength<Char>(str_a));
    A_AVOW_INDEX(&kRightAligned[i][0], str_a, i);
  }
  D_COUT(Headingf("Testing TPrintCenter<Char>"));

  const Char kCentered[13][14] = {
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

  static const Char kNumbers[] = {'1', '2', '3', '4', '5',
                                  '6', '7', '8', '9', NIL};

  for (SI4 i = 12; i >= 0; --i) {
    D_SOCKET_WIPE(str_a, kCount * sizeof(Char));
    cursor = TPrintCenter<Char>(str_a, str_a + kCount - 1, kNumbers, i + 1);
    D_COUT_CHARS(str_a, 64);
    D_ASSERT_INDEX(cursor, i);
    D_PRINTF("\n    Wrote:\"%s\":%i", str_a, TSTRLength<Char>(str_a));
    A_AVOW_INDEX(&kCentered[i][0], str_a, i);
  }

  D_COUT(Headingf("Testing TPrintSocket<Char>"));

  for (SI4 i = 0; i < kCount / 4; ++i) str_b[i] = '0' + i % 10;

  D_SOCKET_WIPE(str_a, (kCount * sizeof(Char)) / 4);

  str_b[kCount - 1] = 0;
  A_ASSERT(
      TPrintSocket<Char>(str_a, str_a + kCount, str_b, str_b + kCount / 4));
  D_COUT_CHARS(str_b, kCount / 2);

  return nullptr;
}
#endif  //< #if SEAM >= SEAM_SCRIPT2_UTF

static const CH1* _04_UTF(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_UTF
  A_TEST_BEGIN;

  D_COUT("\n\nTesting COut().Hex");
  for (SI4 i = 0; i < 16; ++i) {
    SI4 value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    // D_PRINTF("\n    %i.) %i", i, value);
    value = HexToByte(HexNibbleToUpperCase(i));
    // D_PRINTF(" Result:%i", value);
    Test(i, value);
  }

  for (SI4 i = 0; i < 256; ++i) {
    UI2 c = HexByteToLowerCase(i);
    // D_PRINTF("\n%i.) Expecting:%x        HexByteToLowerCase:%c%c", i, i,
    // (CH1)c,
    //       (CH1)(c >> 8));
    SI4 value = HexToByte(c);
    // D_PRINTF("        HexToByte:%i", value);
    A_AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    // D_PRINTF(" Result:%i", value);
    Test(i, value);
  }

  D_COUT("\n\nTesting Unicode character functions.");

  D_COUT("\n\nTesting CH1* Print (CH1*,CH1*,CH4);\n");
  enum { kSTR1Count = 8 };
  CH1 str1[kSTR1Count];
  CH4 ch4_found;
  CH1* str1_cursor = Print(str1, kSTR1Count, (CH4)0);
  D_SOCKET_WIPE(str1, kSTR1Count);
  A_ASSERT(str1_cursor);
  const CH1* str1_result = Scan(str1, ch4_found);
  D_ASSERT_INDEX(str1_result, (SI4)0);
  if (ch4_found != 0) COut().Hex(str1, kSTR1Count);
  A_AVOW_INDEX((CH4)0, ch4_found, 0);

  for (CH4 ch4_expected = 1; ch4_expected < (1 << 21); ++ch4_expected) {
    D_SOCKET_WIPE(str1, kSTR1Count);
    str1_cursor = Print(str1, kSTR1Count, ch4_expected);
    D_ASSERT_INDEX(str1_cursor, (UI4)ch4_expected);
    const CH1* str1_result = Scan(str1, ch4_found);
    D_ASSERT_INDEX(str1_result, (UI4)ch4_expected);
    if (ch4_found != ch4_expected) COut().Hex(str1, kSTR1Count);
    A_AVOW_INDEX(ch4_expected, ch4_found, (SI4)ch4_expected);
  }

  D_COUT("\n\nTesting CH2* Print (CH2*,CH2*,CH4);\n");
  enum {
    kSTR2Count = 4,
  };
  CH2 str2[kSTR2Count];
  D_SOCKET_WIPE(str2, kSTR2Count * 2);
  CH2* str2_cursor = str2;
  str2_cursor = Print(str2, str2 + kSTR2Count - 1, (CH4)0);
  D_COUT_HEXF(str2, reinterpret_cast<CH1*>(str2 + 3) - 1);
  A_ASSERT(str2_cursor);
  const CH2* str2_result = Scan(str2, ch4_found);
  D_ASSERT_INDEX(str2_result, (SI4)0);
  A_AVOW_INDEX((CH4)0, ch4_found, 0);

  for (CH4 ch4_expected = 1; ch4_expected < (1 << 10); ++ch4_expected) {
    D_SOCKET_WIPE(str1, kSTR1Count);
    str2_cursor = Print(str2, str2 + 3, ch4_expected);
    D_ASSERT_INDEX(str2_cursor, (UI4)ch4_expected);
    const CH2* str2_result = Scan(str2, ch4_found);
    D_ASSERT_INDEX(str2_result, (UI4)ch4_expected);
    A_AVOW_INDEX(ch4_expected, ch4_found, (SI4)ch4_expected);
    if (ch4_found != ch4_expected) COut().Hex(str2, kSTR1Count * 2);
  }

  if (_04_UTF<CH1, SI4>()) return "Error testing UTF-8.";
  if (_04_UTF<CH2, SI4>()) return "Error testing UTF-16.";
  if (_04_UTF<CH4, SI4>()) return "Error testing UTF-32.";

#endif
  return nullptr;
}
}  //< namespace script2
