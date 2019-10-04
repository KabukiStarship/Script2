/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/01.itos.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_ITOS
#include <cString>
#include <cstdio>
//
#include "../puff.hpp"
#include "../rng.h"
#include "../stringf.hpp"
using namespace _;
#if SEAM == SCRIPT2_ITOS
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {

inline const CH1* ItoS(const CH1* args) {
#if SEAM >= SCRIPT2_ITOS
  A_TEST_BEGIN;
  D_COUT(
      "\n\nDirections: To use this tester, you'll want to run the script on "
      "random numbers until you find one that fails the test. After the test "
      "has failed you add that number to the problem_child array so it will "
      "get tested first and you'll get some extra debug information.");

  D_COUT("\n\nTesting Pow10_UI2...");
  UI2 pow10_ui2 = 1;
  for (UI2 i = 0; i < cUI2DigitCountMax; ++i) {
    A_AVOW_INDEX(pow10_ui2, Pow10(i), i);
    pow10_ui2 *= 10;
  }

  D_COUT("\n\nTesting Pow10_UI4...");
  UI4 pow10_ui4 = 1;
  for (UI4 i = 0; i < cUI4DigitCountMax; ++i) {
    A_AVOW_INDEX(pow10_ui4, Pow10(i), i);
    pow10_ui4 *= 10;
  }

  D_COUT("\n\nTesting Pow10_UI8...");
  UI8 pow10_ui8 = 1;
  for (UI8 i = 0; i < cUI8DigitCountMax; ++i) {
    A_AVOW_INDEX(pow10_ui8, Pow10(i), i);
    pow10_ui8 *= 10;
  }

  static const UI8 edge_condition[] = {1,
                                       12,
                                       123,
                                       1234,
                                       12345,
                                       123456,
                                       1234567,
                                       12345678,
                                       123456789,
                                       Pow10_UI8()[1] - 1,
                                       Pow10_UI8()[1],
                                       Pow10_UI8()[1] + 1,
                                       Pow10_UI8()[1] + Pow10_UI8()[1] / 2,
                                       Pow10_UI8()[2] - 1,
                                       Pow10_UI8()[2],
                                       Pow10_UI8()[2] + 1,
                                       Pow10_UI8()[2] + Pow10_UI8()[2] / 2,
                                       Pow10_UI8()[3] - 1,
                                       Pow10_UI8()[3],
                                       Pow10_UI8()[3] + 1,
                                       Pow10_UI8()[3] + Pow10_UI8()[3] / 2,
                                       Pow10_UI8()[4] - 1,
                                       Pow10_UI8()[4],
                                       Pow10_UI8()[4] + 1,
                                       Pow10_UI8()[4] + Pow10_UI8()[4] / 2,
                                       Pow10_UI8()[5] - 1,
                                       Pow10_UI8()[5],
                                       Pow10_UI8()[5] + 1,
                                       Pow10_UI8()[5] + Pow10_UI8()[5] / 2,
                                       Pow10_UI8()[6] - 1,
                                       Pow10_UI8()[6],
                                       Pow10_UI8()[6] + 1,
                                       Pow10_UI8()[6] + Pow10_UI8()[6] / 2,
                                       Pow10_UI8()[7] - 1,
                                       Pow10_UI8()[7],
                                       Pow10_UI8()[7] + 1,
                                       Pow10_UI8()[7] + Pow10_UI8()[7] / 2,
                                       Pow10_UI8()[8] - 1,
                                       Pow10_UI8()[8],
                                       Pow10_UI8()[8] + 1,
                                       Pow10_UI8()[8] + Pow10_UI8()[8] / 2,
                                       Pow10_UI8()[9] - 1,
                                       Pow10_UI8()[9],
                                       Pow10_UI8()[9] + 1,
                                       Pow10_UI8()[9] + Pow10_UI8()[9] / 2,
                                       0};

  static const UI8 problem_child[] = {9173263544803952, 827672716845, 0};

  enum { cProblemChildCount = 2, cSize = 23 };

  CH1 text[cSize + 1], expecting[cSize + 1];
  CH1 socket[cSize];
  CH1* result;
  UI8 result_ui8, expected_ui8;

  D_COUT("\nTesting ScanUnsigned<UI, CHT> (const CHT*, const CH1*, I);");

  for (SIN i = 0; i < 1 << 6; ++i) {
    expected_ui8 = RandomUI8();
    sprintf_s(socket, cSize, "%llu", expected_ui8);
    const CH1* test = TScanUnsigned<UI8, CH1>(socket, result_ui8);
    A_ASSERT(test);
    A_AVOW(expected_ui8, result_ui8);
  }

  D_COUT("\n\nTesting Puff ItoS Algorithm...\n\n");

  SIN count = TSTRLength<UI8>(problem_child);
  D_COUT("\n\nTesting %i problem children...\n\n" << count);

  for (SIN i = 0; i < count; ++i) {
    expected_ui8 = problem_child[i];
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    static const CH1 kPuffDebugHeader[] =
        "\n\n    "
        "|6666555555555544444444443333333333222222222211111111110000000000|\n"
        "    "
        "|3210987654321098765432109876543210987654321098765432109876543210|\n"
        "    "
        "|*   *  *  *   *  *  *   *  *  *   *  *  *   *  *  *   *  *  *   |\n"
        "    |\0";
    D_COUT(kPuffDebugHeader << Binaryf(expected_ui8) << '|' << '\n'
                            << i << ".) ");
    SIN expected_length = TSTRLength<CH1>(expecting);
    result = TSPrintUnsigned<UI8, CH1>(text, text + cSize - 1, expected_ui8);
    if (!result) {
      D_PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    D_AVOW(expecting, text);
  }

  count = TSTRLength<UI8>(edge_condition);
  D_COUT("\n\nTesting " << count << " edge conditions...\n\n");
  for (SIW i = 0; i < count; ++i) {
    D_COUT(Linef('-'));
    expected_ui8 = edge_condition[i];
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    D_COUT("\n\n" << i + 1 << ".) ");
    result = TSPrintUnsigned<UI8, CH1>(text, text + cSize - 1, expected_ui8);
    if (!result) {
      D_PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    D_AVOW(expecting, text);
  }
#if D_THIS
  count = 200;
#else
  count = 1000;
#endif
  /* The RNG some broke. I don't know what's wrong.
  D_COUT("\n\nTesting " << count << " random numbers of each length...\n\n");
  SIN count_digits = STRLength(count);
  D_COUT("\n\ncount_digits:" << count_digits);

  // We don't want to do 1000 tests of length 1, so we're going to

  for (SIN i = 0; i < 20; ++i) {
    for (SIN j = 0; j < count; ++j) {
      if (j >= Pow10_UI8()[i + i] - 1 - Pow10_UI8()[i]) break;
      UI8 lower_bounds = Pow10_UI8()[i], upper_bounds = Pow10_UI8()[i + 1] - 1;
      expected_ui8 = Random(lower_bounds, upper_bounds);
      sprintf_s(expecting, 24, "%llu", expected_ui8);
      D_COUT("\n\n" << i + 1);
      result = TSPrintUnsigned<UI8, CH1>(text, text + cSize - 1, expected_ui8);
      if (!result) {
        D_PAUSE("An error occurred :-(");
        break;
      }
      *result = 0;
      D_AVOW(expecting, text);
    }
  }*/

#endif
  return 0;
}
}  // namespace script2
