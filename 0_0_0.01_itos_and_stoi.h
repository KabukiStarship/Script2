/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /0_0_0__01_itos_and_stoi.h
@author  Cale McCollough <calemccollough.github.io>
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

#include <cstdio>
#include <cstring>

#include "tbinary.h"

#if SEAM == _0_0_0__01
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {
inline const CH1* _0_0_0__01_ItoS_and_StoI(CH1* seam_log, CH1* seam_end,
                                            const CH1* args) {
#if SEAM >= _0_0_0__01
  TEST_BEGIN;

  static const UI8 k10ToThe[20] = {
      1,           //< 10^0
      10,          //< 10^1
      100,         //< 10^2
      1000,        //< 10^3
      10000,       //< 10^4
      100000,      //< 10^5
      1000000,     //< 10^6
      10000000,    //< 10^7
      100000000,   //< 10^8
      1000000000,  //< 10^9
  };

  static const UI8 test_value[] = {
      1,
      12,
      123,
      1234,
      12345,
      123456,
      1234567,
      12345678,
      123456789,
      k10ToThe[0] - 1,
      k10ToThe[0],
      k10ToThe[0] + 1,
      k10ToThe[1] - 1,
      k10ToThe[1],
      k10ToThe[1] + 1,
      k10ToThe[1] + k10ToThe[1] / 2,
      k10ToThe[2] - 1,
      k10ToThe[2],
      k10ToThe[2] + 1,
      k10ToThe[2] + k10ToThe[2] / 2,
      k10ToThe[3] - 1,
      k10ToThe[3],
      k10ToThe[3] + 1,
      k10ToThe[3] + k10ToThe[3] / 2,
      k10ToThe[4] - 1,
      k10ToThe[4],
      k10ToThe[4] + 1,
      k10ToThe[4] + k10ToThe[4] / 2,
      k10ToThe[5] - 1,
      k10ToThe[5],
      k10ToThe[5] + 1,
      k10ToThe[5] + k10ToThe[5] / 2,
      k10ToThe[6] - 1,
      k10ToThe[6],
      k10ToThe[6] + 1,
      k10ToThe[6] + k10ToThe[6] / 2,
      k10ToThe[7] - 1,
      k10ToThe[7],
      k10ToThe[7] + 1,
      k10ToThe[7] + k10ToThe[7] / 2,
      k10ToThe[8] - 1,
      k10ToThe[8],
      k10ToThe[8] + 1,
      k10ToThe[8] + k10ToThe[8] / 2,
      k10ToThe[9] - 1,
      k10ToThe[9],
      k10ToThe[9] + 1,
      k10ToThe[9] + k10ToThe[9] / 2,
  };

  /*
  PRINTF ("\nTesting quick MSD lookup...\n    Length 1:");
  static const UI8 delta_one_bits[] = { 4, 7, 10, 14, 17, 20, 24, 27, 30 };
  UI8 max,
           num_bits,
           msd_bit_range;
  PRINTF ("\n| Length | MSD Offset | Min Value  |"
          "\n|:------:|:----------:|:----------:|");
  for (int length = 3; length < 10; ++length) {
      num_bits = delta_one_bits[length - 2];
      msd_bit_range = (length == 10 || length == 20) ? 16: 8;
      for (UI8 i = 1;  i <= 8; ++i) {
          PRINTF ("\n|   %llu    |     %llu      | %10u |", length, i, i <<
  num_bits);
      }
  }
  PRINT ('\n');
  system ("PAUSE");*/

  static const UI8 problem_children[] = {
      9173263544803952,
  };
  enum { kNumProblemChildren = 0, kSize = 23 };

  CH1 text[kSize + 1], expecting[kSize + 1];
  CH1 socket[kSize];
  CH1* result;
  UI8 result_ui8, expected_ui8;

  PRINT("\nTesting ScanUnsigned<UI, Char> (const Char*, const CH1*, I);");

  for (int i = 0; i < 1 << 6; ++i) {
    expected_ui8 = RandomUI8();
    sprintf_s(socket, kSize, FORMAT_UI8, expected_ui8);
    const CH1* test = TScanUnsigned<UI8, CH1>(socket, result_ui8);
    ASSERT(test);
    AVOW(expected_ui8, result_ui8);
  }

  PRINT("\n\nTesting Puff ItoS Algorithm...\n\n");

  // PrintDigits99To99Lut ();

  PRINT("\n\nTesting problem children...\n\n");

  for (int i = 0; i < kNumProblemChildren; ++i) {
    PRINT_LINE('-');
    PRINT('\n');
    expected_ui8 = problem_children[i];
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    PRINTF("\n%i.) Expecting \"%s\":%llu", i + 1, expecting,
           TStringLength<>(expecting));
    result = TPrintUnsigned<UI8, CH1>(text, text + kSize - 1, expected_ui8);
    if (!result) {
      PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    if (TStringCompare<>(expecting, text)) {
      PAUSEF("\n\nERROR: Expecting \"%s\":%llu and found \"%s\":%llu",
             expecting, TStringLength<>(expecting), text,
             TStringLength<>(text));
    }
  }

  PRINT("\n\nTesting edge conditions...\n\n");
  for (int i = 0; i < 28; ++i) {
    PRINT_LINE('-');
    PRINT('\n');
    expected_ui8 = test_value[i];
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    PRINTF("\n%i.) ", i + 1);
    result = TPrintUnsigned<UI8, CH1>(text, text + kSize - 1, expected_ui8);
    if (!result) {
      PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    if (strcmp(expecting, text)) {
      PAUSEF("\n\nERROR: Expecting \"%s\":%llu and found \"%s\":%llu",
             expecting, TStringLength<>(expecting), text,
             TStringLength<>(text));
    }
  }

  PRINTF("\n\nTesting random numbers...\n\n");

  for (int i = 0; i < 0x0000ffff; ++i) {
    PRINT_LINE('-');
    PRINT('\n');
    expected_ui8 = RandomUI8();
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    result = TPrintUnsigned<UI8, CH1>(text, text + kSize - 1, expected_ui8);
    if (!result) {
      PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    if (TStringCompare<>(expecting, text)) {
      PAUSEF("\n\nERROR: Expecting \"%s\":%llu and found \"%s\":%llu",
             expecting, TStringLength<>(expecting), text,
             TStringLength<>(text));
    }
  }

#endif
  return 0;
}
}  // namespace _
