/* Script^2 @version 0.x
@file    /0_0_0__04_clock.h
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

#include <cclock.h>

#if SEAM == _0_0_0__05
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

using namespace _;

static const CH1* _0_0_0__05_Clock(CH1* seam_log, CH1* seam_end,
                                   const CH1* args) {
#if SEAM >= _0_0_0__05
  TEST_BEGIN;

  PRINT_HEADING("\n\nTesting TStringScanTime...");

  TMS t, t_found;
  const CH1* result;

  // @note The following dates must be the current day to work right in order
  //       to auto-detect the year.
  const CH1* strings[] = {
      "8/9",
      "08/09",
      "8/9/18",
      "8/09/18",
      "8/9/2018",
      "8/09/2018",
      "8/09/2018",
      "08/9/2018",
      "8/09/2018@00",
      "8.09.2018@00AM",
      "8/09/2018@00:00",
      "8/09/18@00:0AM",
      "8/09/2018@00:00:00",
      "8/09/2018@00:00:00AM",
      "2018-08-09@00:00:00AM",
      "2018-08-09@00:00:00am",
      "2018-08-09@00:00:00A",
      "2018-08-09@00:00:00a ",
  };

  for (int i = 0; i < 18; ++i) {
    PRINT_LINE('-');
    PRINTF("\n    %i", i);
    TMS t = 0;
    result = TStringScanTime(strings[i], t);
    // Assert (!ClockCompare (t, 2018, 8, 9, 0, 0, 0))
  }

  PRINTF("\n\nTesting more valid input...\n");

  enum { kSize = 128 };
  CH1 socket[kSize];

  t = ClockTimeTMS(8, 9, 17, 4, 20);
  Print(socket, socket + kSize, t);
  result = TStringScanTime(socket, t_found);
  ASSERT(ClockCompare(t_found, t));

  t = ClockTimeTMS(2020, 4, 20, 4, 20);
  Print(socket, socket + kSize, t);
  result = TStringScanTime(socket, t_found);
  ASSERT(ClockCompare(t, t_found));

  t = ClockTimeTMS(1947, 12, 7, 23, 5, 7);
  Print(socket, socket + kSize, t);
  result = TStringScanTime(socket, t_found);
  ASSERT(ClockCompare(t, t_found));

  PRINT_HEADING("\nTesting invalid input...\n");
  TStringScanTime("cat", t);

  TStringScanTime("2017-30-40", t);

  PRINTF("\nDone testing date parsing utils! :-)\n");
#endif
  return nullptr;
}
