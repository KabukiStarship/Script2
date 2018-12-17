/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    \0_0_0__02_ascii_strings_and_socket.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
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

#if SEAM == _0_0_0__02
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

template <typename Char, typename Size>
static const CH1* _0_0_0__02_Strand() {
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
    kSize = 511,
  };

  static const Char* test_strings[kCompareStringsCount][2] = {
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

  static const Char kTestingString[] = "Testing one, two, three.";

  static const Char* kStringsRightAligned[] = {
      "    Testing one, two, three.", "Test...", ".", "..", "...", "T...",
  };

  static const Char kStringNumbers[] = "1234567890\0";

  static const Char* kStringsCentered[] = {" 1234567890", " 1234567890 ",
                                           "  1234567890 ", "123..."};

  const Char* stop;
  CH1 socket[kSize + 1], buffer_b[kSize + 1];

  enum { kCheckChar = '!' };
  CH1* check_char = socket + kSize + 1;

  SocketFill(socket, kSize);
  TPrint<Char>(socket, kSize, "Testing 1, 2, 3");
  PRINT_SOCKET(socket, kSize);

  *check_char = kCheckChar;

  TUTF<Char> utf(socket, kSize);

  for (int i = 0; i < kCompareStringsCount; ++i) {
    stop = TPrint<Char>(socket, socket + kSize, test_strings[i][0]);
    PRINT_SOCKET(socket, kSize);
    Test(stop);

    stop = TStringEquals<Char>(socket, test_strings[i][0]);
    Test(stop);
  }

  static const Char kTesting123[] = "Testing 1, 2, 3\0";

  PRINT_HEADING("Testing Universal Text Formatter");
  PRINTF("\n\n    Expecting \"%s\"", kTesting123);

  utf.Set(socket) << "Testing " << 1 + (int)'0' << ", " << 2 + (int)'0' << ", "
                  << 3 + (int)'0';
  PRINT_SOCKET(socket, kSize);
  AVOW(kTesting123, socket);

  ASSERT(!TStringEquals<Char>(kCompareStrings[0], kCompareStrings[1]));
  ASSERT(!TStringEquals<Char>(kCompareStrings[0], kCompareStrings[3]));
  ASSERT(TStringEquals<Char>(kCompareStrings[0], kCompareStrings[0]));
  ASSERT(!TStringEquals<Char>(kCompareStrings[2], kCompareStrings[3]));
  ASSERT(TStringEquals<Char>(kCompareStrings[2], kCompareStrings[2]));

  AVOW(9, TStringLength<Char>("123456789"));

  PRINTF("\n\nTesting StringFind");

  ASSERT(TStringFind<Char>(kTestingString, "one"));
  ASSERT(TStringFind<Char>(kTestingString, "three."));

  PRINTF("\n\nTesting PrintRight");

  ASSERT(TPrintRight<Char>(socket, socket + kSize, kTestingString, 28));
  PRINT_SOCKET(socket, kSize);
  PRINTF("\n    Wrote:\"%s\":%i", socket, TStringLength<Char>(socket));
  AVOW(kStringsRightAligned[0], socket);

  ASSERT(TPrintRight<Char>(socket, socket + kSize, kTestingString, 7));
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsRightAligned[1], socket);

  ASSERT(TPrintRight<Char>(socket, socket + kSize, kTestingString, 1));
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsRightAligned[2], socket);

  ASSERT(TPrintRight<Char>(socket, socket + kSize, kTestingString, 2));
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsRightAligned[3], socket);

  ASSERT(TPrintRight<Char>(socket, socket + kSize, kTestingString, 3));
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsRightAligned[4], socket);

  ASSERT(TPrintRight<Char>(socket, socket + kSize, kTestingString, 4));
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsRightAligned[5], socket);

  PRINTF("\n\n    Testing PrintCentered");

  for (int i = 0; i < 4; ++i) {
    PRINTF("\n    %i.)\"%s\"", i, kStringsCentered[i]);
  }

  utf.Set(socket) << TCenter<Char>(kStringNumbers, 10);
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringNumbers, socket);

  utf.Set(socket) << TCenter<Char>(kStringNumbers, 11);
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsCentered[0], socket);

  utf.Set(socket) << TCenter<Char>(kStringNumbers, 12);
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsCentered[1], socket);

  utf.Set(socket) << TCenter<Char>(kStringNumbers, 13);
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsCentered[2], socket);

  utf.Set(socket) << TCenter<Char>(kStringNumbers, 6);
  PRINT_SOCKET(socket, kSize);
  AVOW(kStringsCentered[3], socket);
  int i = 0;  //< Shared looping variable.

  PRINT_HEADING("Testing Socket");
  PRINT_HEADING("Testing PrintSocket (void*, int size)");

  for (int i = 1; i <= kSize; ++i) buffer_b[i - 1] = '0' + i % 10;
  buffer_b[kSize] = 0;
  ASSERT(TPrintSocket<Char>(socket, socket + kSize, buffer_b, buffer_b + 160));
  PRINT_SOCKET(socket, kSize);
  PRINTF("\n    Printed:\n%s", socket);

  PRINT_HEADING("Testing TStrand...");

  enum {
    kStrandLoopCount = 100,
  };

  TStrand<Char> strand("Testing ");
  PrintSocket(strand.Obj().Begin(), strand.Obj().SizeBytes());
  for (SIN i = 0; i < kStrandLoopCount; ++i) {
    strand << i << ", ";
  }
  PRINTF("\nstrand.Obj().SizeBytes():%i", (int)strand.Obj().SizeBytes());
  PrintSocket(strand.Obj().Begin(), strand.Obj().SizeBytes());
  Char* cursor = strand.Find("Testing ");
  ASSERT(cursor);
  for (SIN i = 0; i < kStrandLoopCount; ++i) {
    strand << i << ", ";
    TToken<Char> i_string(i);
    cursor = TStringFind<Char>(cursor, i_string.String());
  }

  return nullptr;
}

static const CH1* _0_0_0__02_ASCII_Strand_and_Socket(CH1* seam_log,
                                                     CH1* seam_end,
                                                     const CH1* args) {
#if SEAM >= _0_0_0__02
  TEST_BEGIN;

  PRINT("\nRunning HexTest");
  for (int i = 0; i < 16; ++i) {
    int value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    PRINTF("\n    %i.) %i", i, value);
    value = HexToByte(HexNibbleToUpperCase(i));
    PRINTF(" value is now:%i", value);
    Test(i, value);
  }

  for (int i = 0; i < 256; ++i) {
    UI2 c = HexByteToLowerCase(i);
    PRINTF("\n%i.) expecting: %x        HexByteToLowerCase:%c%c", i, i, (CH1)c,
           (CH1)(c >> 8));
    int value = HexToByte(c);
    PRINTF("        HexToByte:%i", value);
    AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    PRINTF("     value is now:%i", value);
    Test(i, value);
  }

  PRINT_HEADING("Test SocketCopy and MemoryCompare");

  enum {
    kTestCharsCount = 1024,
    kTestCharsOffsetCount = 16,
  };
  CH1 test_chars[kTestCharsCount];
  CH1 test_chars_result[kTestCharsCount + kTestCharsOffsetCount];

  PRINTF("\ntest_chars[0]:0x%p test_chars_result[n]:0x%p ", test_chars,
         test_chars_result);

  for (int i = 0; i < kTestCharsOffsetCount; ++i) {
    for (int j = 0; j < kTestCharsCount; ++j) test_chars[j] = (CH1)(j % 256);
    CH1* result = SocketCopy(test_chars_result + i, kTestCharsCount, test_chars,
                             kTestCharsCount);
    ASSERT(result);
    ASSERT(!SocketCompare(test_chars + i, kTestCharsCount, test_chars_result,
                          kTestCharsCount));
  }

  const CH1* result = _0_0_0__02_Strand<CH1, SI4>();
  if (result) return result;

#endif
  return nullptr;
}

}  // namespace _
