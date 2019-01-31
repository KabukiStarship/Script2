/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \03_utf.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#include "t_socket.h"
#include "t_strand.h"
#include "t_test.h"

#include "c_cout.h"

#if SEAM == SCRIPT2_3
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

using namespace _;

#if SEAM >= SCRIPT2_3
namespace script2 {
template <typename Char, typename Size>
static const Char* _03_UTF () {
  PRINTF ("\n\nTesting UTF<CH%c,SI%c>", '0' + sizeof (Char), 
    '0' + sizeof (Size));

  enum {
    kCount = 512,
  };

  Char str_a[kCount],
    str_b[kCount];
  Char* check_char = str_a + kCount + 1;

  static const Char kTesting123[] = {
    'T', 'e', 's', 't', 'i', 'n', 'g', ' ', '1', ',', ' ', '2', ',', ' ', '3',
    NIL
  };

  SocketFill(str_a, kCount);
  TPrint<Char>(str_a, kCount, kTesting123);
  PRINT_CHARS(str_a, kCount);

  enum { kCheckChar = '!' };
  *check_char = kCheckChar;

  TUTF<Char> utf(str_a, kCount);

  enum {
    kTestStrandsCount = 4
  };

  const Char kTestStrands[5][2][7] = {
      {{'?', NIL, NIL, NIL, NIL, NIL, NIL}, {NIL, NIL, NIL, NIL, NIL, NIL, NIL}},
      {{'?', NIL, NIL, NIL, NIL, NIL, NIL}, {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
      {{'?', ' ', NIL, NIL, NIL, NIL, NIL}, {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
      {{'A', 'p', 'p', 'l', 'e', 's', NIL}, {'A', 'p', 'p', 'l', 'e', 's', NIL}},
      {{'A', 'p', 'p', 'l', 'e', 's', NIL}, {'A', 'p', 'p', 'l', 'e', 's', NIL}}};

  const Char* cursor;
  for (SI4 i = 0; i < kTestStrandsCount; ++i) {
    cursor = TPrint<Char>(str_a, str_a + kCount, kTestStrands[i][0]);
    PRINT_CHARS(str_a, kCount);
    Test(cursor);

    cursor = TStrandEquals<Char>(str_a, kTestStrands[i][0]);
    Test(cursor);
  }

  PRINT_HEADING("Testing Universal Text Formatter");
  PRINTF("\n\n    Expecting \"%s\"", kTesting123);

  const Char kTestingSpace[] = { 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL };
  const Char kCommaSpace[] = { ',', ' ', NIL };

  utf.Set(str_a) << kTestingSpace << 1 << kCommaSpace << 2 << ", " << 3;
  PRINT_CHARS(str_a, kCount);
  AVOW(kTesting123, str_a);

  const Char kCompareStrands[4][9] = {
    { 'T', 'e', 's', 't', 'i', 'n', 'g', NIL, NIL },
    { 'T', 'e', 'x', 't', 'i', 'n', 'g', NIL, NIL },
    { 'T', 'e', 's', 't', 'i', 'n', 'g', '@', NIL },
    { 'T', 'e', 'x', 't', 'i', 'n', 'g', '@', NIL },
  };

  ASSERT(!TStrandEquals<Char>(kCompareStrands[0], kCompareStrands[1]));
  ASSERT(!TStrandEquals<Char>(kCompareStrands[0], kCompareStrands[3]));
  ASSERT(TStrandEquals<Char>(kCompareStrands[0], kCompareStrands[0]));
  ASSERT(!TStrandEquals<Char>(kCompareStrands[2], kCompareStrands[3]));
  ASSERT(TStrandEquals<Char>(kCompareStrands[2], kCompareStrands[2]));

  const Char k1to9[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  AVOW(9, TStrandLength<Char>(k1to9));

  PRINTF("\n\nTesting StrandFind");

  const Char kOne[] = { 'o', 'n', 'e', NIL };
  const Char kThreePeriod[] = { 't','h','r','e','e','.', NIL};
  ASSERT(TStrandFind<Char>(kTesting123, kOne));
  ASSERT(TStrandFind<Char>(kTesting123, kThreePeriod));

  PRINTF("\n\nTesting PrintRight");

  const Char kRightAligned[6][13] = {
      { ' ', ' ',' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL},
      {'T', 'e', 's', 't', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL}};

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kCount, kTestingSpace, 12));
  PRINT_CHARS(str_a, kCount);
  PRINTF("\n    Wrote:\"%s\":%i", str_a, TStrandLength<Char>(str_a));
  AVOW(&kRightAligned[0][0], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kCount, kTestingSpace, 7));
  PRINT_CHARS(str_a, kCount);
  AVOW(&kRightAligned[1][0], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kCount, kTestingSpace, 1));
  PRINT_CHARS(str_a, kCount);
  AVOW(&kRightAligned[2][0], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kCount, kTestingSpace, 2));
  PRINT_CHARS(str_a, kCount);
  AVOW(&kRightAligned[3][0], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kCount, kTestingSpace, 3));
  PRINT_CHARS(str_a, kCount);
  AVOW(&kRightAligned[4][0], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kCount, kTestingSpace, 4));
  PRINT_CHARS(str_a, kCount);
  AVOW(&kRightAligned[5][0], str_a);

  PRINTF("\n\n    Testing PrintCentered");

  const Char kCentered[4][14] = {
    {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', NIL, NIL, NIL},
    {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', NIL, NIL},
    {' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', NIL},
    {'1', '2', '3', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL}};

  for (SI4 i = 0; i < 4; ++i) {
    PRINTF("\n    %i.)\"%s\"", i, kCentered[i]);
  }

  static const Char kNumbers[] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', NIL
  };

  utf.Set(str_a) << TCenter<Char>(kNumbers, 10);
  PRINT_CHARS(str_a, kCount);
  AVOW(kNumbers, str_a);

  utf.Set(str_a) << TCenter<Char>(kNumbers, 11);
  PRINT_CHARS(str_a, kCount);
  AVOW(&kCentered[0][0], str_a);

  utf.Set(str_a) << TCenter<Char>(kNumbers, 12);
  PRINT_CHARS(str_a, kCount);
  AVOW(&kCentered[1][0], str_a);

  utf.Set(str_a) << TCenter<Char>(kNumbers, 13);
  PRINT_CHARS(str_a, kCount);
  AVOW(&kCentered[2][0], str_a);

  utf.Set(str_a) << TCenter<Char>(kNumbers, 6);
  PRINT_CHARS(str_a, kCount);
  AVOW(&kCentered[3][0], str_a);
  SI4 i = 0;  //< Shared looping variable.

  PRINT_HEADING("Testing TPrintSocket<Char>");

  for (SI4 i = 0; i < kCount; ++i) str_b[i] = '0' + i % 10;
  str_b[kCount - 1] = 0;
  ASSERT(TPrintSocket<Char>(str_a, str_a + kCount, str_b, str_b + 160));
  PRINT_CHARS(str_b, kCount);
  PRINTF("\n    Printed:\n");
  PRINT (str_a);
  return nullptr;
}
#endif  //< #if SEAM >= SCRIPT2_3

static const CH1* _03_UTF(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_3
  TEST_BEGIN;

  PRINT("\n\nTesting PrintHex");
  for (SI4 i = 0; i < 16; ++i) {
    SI4 value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    //PRINTF("\n    %i.) %i", i, value);
    value = HexToByte(HexNibbleToUpperCase(i));
    //PRINTF(" Result:%i", value);
    Test(i, value);
  }

  for (SI4 i = 0; i < 256; ++i) {
    UI2 c = HexByteToLowerCase(i);
    //PRINTF("\n%i.) Expecting:%x        HexByteToLowerCase:%c%c", i, i, (CH1)c,
    //       (CH1)(c >> 8));
    SI4 value = HexToByte(c);
    //PRINTF("        HexToByte:%i", value);
    AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    //PRINTF(" Result:%i", value);
    Test(i, value);
  }

  PRINT ("\n\nTesting Unicode character functions.");

  PRINT ("\nTesting CH1* Print (CH1*,CH1*,CH4);\n");
  enum { kSTR1Count = 8 };
  CH1 str1[kSTR1Count];
  CH4 ch4_found;
  CH1* str1_cursor = Print (str1, kSTR1Count, (CH4)0);
  SocketFill (str1, kSTR1Count);
  ASSERT (str1_cursor);
  const CH1* str1_result = Scan (str1, ch4_found);
  ASSERT_INDEX (str1_result, (SI4)0);
  if (ch4_found != 0) PrintHex (str1, kSTR1Count);
  AVOW_INDEX ((CH4)0, ch4_found, 0);

  for (CH4 ch4_expected = 1; ch4_expected < (1 << 21); ++ch4_expected) {
    SocketFill (str1, kSTR1Count);
    str1_cursor = Print (str1, kSTR1Count, ch4_expected);
    ASSERT_INDEX (str1_cursor, (UI4)ch4_expected);
    const CH1* str1_result = Scan (str1, ch4_found);
    ASSERT_INDEX (str1_result, (UI4)ch4_expected);
    if (ch4_found != ch4_expected) PrintHex (str1, kSTR1Count);
    AVOW_INDEX (ch4_expected, ch4_found, (SI4)ch4_expected);
  }

  PRINT ("\n\nTesting CH2* Print (CH2*,CH2*,CH4);\n");
  enum { kSTR2Count = 4, };
  CH2 str2[kSTR2Count];
  SocketFill (str2, kSTR2Count * 2);
  CH2* str2_cursor = str2;
  str2_cursor = Print (str2, str2 + kSTR2Count - 1, (CH4)0);
  PRINT_HEXS (str2, reinterpret_cast<CH1*> (str2 + 3) - 1);
  ASSERT (str2_cursor);
  const CH2* str2_result = Scan (str2, ch4_found);
  ASSERT_INDEX (str2_result, (SI4)0);
  AVOW_INDEX ((CH4)0, ch4_found, 0);

  for (CH4 ch4_expected = 1; ch4_expected < (1 << 10); ++ch4_expected) {
    SocketFill (str1, kSTR1Count);
    str2_cursor = Print (str2, str2 + 3, ch4_expected);
    ASSERT_INDEX (str2_cursor, (UI4)ch4_expected);
    const CH2* str2_result = Scan (str2, ch4_found);
    ASSERT_INDEX (str2_result, (UI4)ch4_expected);
    AVOW_INDEX (ch4_expected, ch4_found , (SI4)ch4_expected);
    if (ch4_found != ch4_expected) PrintHex (str2, kSTR1Count * 2);
  }

  if (_03_UTF<CH1, SI4> ()) return "Error testing UTF-8.";
  if (_03_UTF<CH2, SI4> ()) return "Error testing UTF-16.";
  if (_03_UTF<CH4, SI4> ()) return "Error testing UTF-32.";

#endif
  return nullptr;
}
} //< namespace script2
