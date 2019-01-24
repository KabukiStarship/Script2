/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \03_socket.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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

#include "tsocket.h"
#include "tstrand.h"
#include "ttest.h"

#include "cconsole.h"

#if SEAM == SCRIPT2_3
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

using namespace _;

#if SEAM >= SCRIPT2_3
namespace script2 {
template <typename Char, typename Size>
static const CH1* _03_UTF_and_Strand() {
  const CH1* char_type_string =
      (sizeof(Char) == 1)
          ? "CH1"
          : (sizeof(Char) == 2) ? "CH2"
                                : (sizeof(Char) == 4) ? "CH4" : "Invalid Char";
  const CH1* size_type_string =
      (sizeof(Size) == 1)
          ? "int8_t"
          : (sizeof(Size) == 2)
                ? "int16_t"
                : (sizeof(Size) == 4)
                      ? "int32_t"
                      : (sizeof(Size) == 8) ? "int64_t" : "Invalid Size";
  PRINTF("\nTesting TStrand<%s,%s>", char_type_string, size_type_string);
  enum {
    kCompareStringsCount = 5,
    kSize = 127,
  };

  static const Char* kTestStrings[kCompareStringsCount][2] = {
      {"?", ""},
      {"?", "?"},
      {"? ", "?"},
      {"Apples", "Apples"},
      {"Apples", "Apples"},
  };

  static const Char* kCompareStrings[] = {
      "Testing",
      "Texting",
      "Testing@",
      "Texting@",
  };

  static const Char kStringTesting123[] = "Testing 1, 2, 3\0";

  static const Char kStringTestingOneTwoThree[] =
      "Testing one, two, three.";  //< @todo Replace with kStringTesting123.

  static const Char* kStringsRightAligned[] = {
      "    Testing one, two, three.", "Test...", ".", "..", "...", "T...",
  };

  static const Char kStringNumbers[] = "1234567890\0";

  static const Char* kStringsCentered[] = {" 1234567890", " 1234567890 ",
                                           "  1234567890 ", "123..."};

  const Char* stop;
  Char str_a[kSize + 1],  //< String A.
    str_b[kSize + 1];     //< String B.

  enum { kCheckChar = '!' };
  Char* check_char = str_a + kSize + 1;

  SocketFill(str_a, kSize);
  TPrint<Char>(str_a, kSize, kStringTesting123);
  PRINT_BYTES(str_a, kSize);

  *check_char = kCheckChar;

  TUTF<Char> utf(str_a, kSize);

  for (SI4 i = 0; i < kCompareStringsCount; ++i) {
    stop = TPrint<Char>(str_a, str_a + kSize, kTestStrings[i][0]);
    PRINT_BYTES(str_a, kSize);
    Test(stop);

    stop = TStringEquals<Char>(str_a, kTestStrings[i][0]);
    Test(stop);
  }

  PRINT_HEADING("Testing Universal Text Formatter");
  PRINTF("\n\n    Expecting \"%s\"", kStringTesting123);

  utf.Set(str_a) << "Testing " << 1 << ", " << 2 << ", " << 3;
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringTesting123, str_a);

  ASSERT(!TStringEquals<Char>(kCompareStrings[0], kCompareStrings[1]));
  ASSERT(!TStringEquals<Char>(kCompareStrings[0], kCompareStrings[3]));
  ASSERT(TStringEquals<Char>(kCompareStrings[0], kCompareStrings[0]));
  ASSERT(!TStringEquals<Char>(kCompareStrings[2], kCompareStrings[3]));
  ASSERT(TStringEquals<Char>(kCompareStrings[2], kCompareStrings[2]));

  AVOW(9, TStringLength<Char>("123456789"));

  PRINTF("\n\nTesting StringFind");

  ASSERT(TStringFind<Char>(kStringTestingOneTwoThree, "one"));
  ASSERT(TStringFind<Char>(kStringTestingOneTwoThree, "three."));

  PRINTF("\n\nTesting PrintRight");

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kSize, kStringTestingOneTwoThree, 28));
  PRINT_BYTES(str_a, kSize);
  PRINTF("\n    Wrote:\"%s\":%i", str_a, TStringLength<Char>(str_a));
  AVOW(kStringsRightAligned[0], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kSize, kStringTestingOneTwoThree, 7));
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsRightAligned[1], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kSize, kStringTestingOneTwoThree, 1));
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsRightAligned[2], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kSize, kStringTestingOneTwoThree, 2));
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsRightAligned[3], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kSize, kStringTestingOneTwoThree, 3));
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsRightAligned[4], str_a);

  ASSERT(
      TPrintRight<Char>(str_a, str_a + kSize, kStringTestingOneTwoThree, 4));
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsRightAligned[5], str_a);

  PRINTF("\n\n    Testing PrintCentered");

  for (SI4 i = 0; i < 4; ++i) {
    PRINTF("\n    %i.)\"%s\"", i, kStringsCentered[i]);
  }

  utf.Set(str_a) << TCenter<Char>(kStringNumbers, 10);
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringNumbers, str_a);

  utf.Set(str_a) << TCenter<Char>(kStringNumbers, 11);
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsCentered[0], str_a);

  utf.Set(str_a) << TCenter<Char>(kStringNumbers, 12);
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsCentered[1], str_a);

  utf.Set(str_a) << TCenter<Char>(kStringNumbers, 13);
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsCentered[2], str_a);

  utf.Set(str_a) << TCenter<Char>(kStringNumbers, 6);
  PRINT_BYTES(str_a, kSize);
  AVOW(kStringsCentered[3], str_a);
  SI4 i = 0;  //< Shared looping variable.

  PRINT_HEADING("Testing Socket");
  PRINT_HEADING("Testing PrintSocket (void*, SI4 size)");

  for (SI4 i = 1; i <= kSize; ++i) str_b[i - 1] = '0' + i % 10;
  str_b[kSize] = 0;
  ASSERT(TPrintSocket<Char>(str_a, str_a + kSize, str_b, str_b + 160));
  PRINT_BYTES(str_a, kSize);
  PRINTF("\n    Printed:\n%s", str_a);

  PRINT_HEADING("Testing TStrand");

  enum {
    kStrandLoopCount = 3,
    kCharSizeChar = '0' + sizeof (Char),
  };

  TStrand<Char> strand("Testing ");
  strand.Print ();

  PRINTF("\n\nExpecting \"%s\"\n", kStringTesting123);
  strand << 1  //<
    << ", "    //<
    << 2       //<
    << ", "    //<
    << 3;
  PRINT_BYTES(strand.CObj().Start<>(), strand.CObj().SizeBytes());
  const Char* cursor = strand.Find(kStringTesting123);
  ASSERT(cursor);

  return nullptr;
}
#endif  //< #if SEAM >= SCRIPT2_3

static const CH1* _03_UTF_and_Strand(CH1* seam_log, CH1* seam_end,
                                            const CH1* args) {
#if SEAM >= SCRIPT2_3
  TEST_BEGIN;

  PRINT("\nRunning HexTest");
  for (SI4 i = 0; i < 16; ++i) {
    SI4 value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    //PRINTF("\n    %i.) %i", i, value);
    value = HexToByte(HexNibbleToUpperCase(i));
    //PRINTF(" value is now:%i", value);
    Test(i, value);
  }

  for (SI4 i = 0; i < 256; ++i) {
    UI2 c = HexByteToLowerCase(i);
    PRINTF("\n%i.) expecting: %x        HexByteToLowerCase:%c%c", i, i, (CH1)c,
           (CH1)(c >> 8));
    SI4 value = HexToByte(c);
    PRINTF("        HexToByte:%i", value);
    AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    PRINTF("     value is now:%i", value);
    Test(i, value);
  }

  PRINT_HEADING("Test SocketCopy and MemoryCompare");

  enum {
    kSTR1Count = 128,
    kSTR1LengthMax = kSTR1Count - 1,
    kTestCharsOffsetCount = 16,
  };
  CH1 str1[kSTR1Count];
  CH1 str1_found[kSTR1Count + kTestCharsOffsetCount];
  CH1* str1_cursor;
  SocketFill (str1, kSTR1Count);
  PRINTF("\ntest_chars[0]:0x%p test_chars_result[n]:0x%p ", str1,
         str1_found);

  for (SI4 i = 0; i < kTestCharsOffsetCount; ++i) {
    for (SI4 j = 0; j < kSTR1Count; ++j) str1[j] = (CH1)(j % 256);
    str1_cursor = SocketCopy(str1_found + i, kSTR1Count, str1,
                             kSTR1Count);
    ASSERT(str1_cursor);
    ASSERT(!SocketCompare(str1 + i, kSTR1Count, str1_found,
                          kSTR1Count));
  }

  PRINT_HEADING ("Testing Unicode character functions.");

  PRINT ("\nTesting CH1* Print (CH1*,CH1*,CH4);\n");
  SocketFill (str1, kSTR1Count);
  CH4 ch4_found;
  str1_cursor = Print (str1, kSTR1Count, (CH4)0);
  ASSERT (str1_cursor);
  const CH1* str1_result = Scan (str1, ch4_found);
  ASSERT_INDEX (str1_result, (SI4)0);
  if (ch4_found != 0) PRINT_BYTES (str1, kSTR1Count);
  AVOW_INDEX ((CH4)0, ch4_found, 0);

  for (CH4 ch4_expected = 1; ch4_expected < (1 << 21); ++ch4_expected) {
    SocketFill (str1, kSTR1Count);
    str1_cursor = Print (str1, kSTR1Count, ch4_expected);
    ASSERT_INDEX (str1_cursor, (UI4)ch4_expected);
    const CH1* str1_result = Scan (str1, ch4_found);
    ASSERT_INDEX (str1_result, (UI4)ch4_expected);
    if (ch4_found != ch4_expected) PRINT_HEXS (str1, kSTR1Count);
    AVOW_INDEX (ch4_expected, ch4_found, (SI4)ch4_expected);
  }

  PRINT ("\nTesting CH2* Print (CH2*,CH2*,CH4);\n");
  SocketFill (str1, kSTR1Count);
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
    if (ch4_found != ch4_expected) PRINT_HEXS (str2, kSTR1Count * 2);
  }

  const CH1* result = _03_UTF_and_Strand<CH1, SI4>();
  if (result) return result;

#endif
  return nullptr;
}
} //< namespace script2
