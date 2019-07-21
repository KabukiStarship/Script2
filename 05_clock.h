/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/05_uts_and_clock.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "t_clock.h"
#include "t_utf.h"

#if SEAM == SEAM_SCRIPT2_CLOCK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _05_Clock(const CH1* args) {
#if SEAM >= SEAM_SCRIPT2_CLOCK
  A_TEST_BEGIN;

  D_COUT_HEADING("\n\nTesting TScanTime...");

  TM4 t, t_found;
  const CH1* result;

  // @note The following dates must be the current day to work right in order
  //       to auto-detect the year.
  const CH1* strings[] = {
      "1/19",
      "01/19",
      "1/9/19",
      "1/19/19",
      "1/9/2019",
      "1/19/2019",
      "1/19/2019",
      "01/19/2019",
      "1/19/2019@00",
      "1.19.2019@00AM",
      "1/19/2019@00:00",
      "1/19/19@00:0AM",
      "1/19/2019@00:00:00",
      "1/19/2019@00:00:00AM",
      "2019-01-19@00:00:00AM",
      "2019-01-19@00:00:00am",
      "2019-01-19@00:00:00A",
      "2019-01-19@00:00:00a ",
  };

  for (SI4 i = 0; i < 18; ++i) {
    D_COUT_LINEF('-');
    D_PRINTF("\n    %i", i);
    TM4 t = 0;
    result = ScanTime(strings[i], t);
    // Assert (!ClockCompare (t, 2018, 8, 9, 0, 0, 0))
  }

  D_PRINTF("\n\nTesting more valid input...\n");

  enum { kSize = 128 };
  CH1 socket[kSize];

  t = ClockTimeTMS(8, 9, 17, 4, 20);
  ClockPrint(socket, socket + kSize, t);
  result = ScanTime(socket, t_found);
  A_ASSERT(ClockCompare(t_found, t));

  t = ClockTimeTMS(2020, 4, 20, 4, 20);
  ClockPrint(socket, socket + kSize, t);
  result = ScanTime(socket, t_found);
  A_ASSERT(ClockCompare(t, t_found));

  t = ClockTimeTMS(1947, 12, 7, 23, 5, 7);
  ClockPrint(socket, socket + kSize, t);
  D_COUT("\n  Before:\"");
  D_COUT(socket);
  D_COUT('\"');
  result = TScan<CH1>(socket, t_found);
  D_COUT("\n\n\nresult:\"");
  D_COUT(TClock<SI4>(t_found));
  D_COUT("\"\"");
  A_ASSERT(ClockCompare(t, t_found));

  D_COUT_HEADING("Testing invalid input");
  TScan<CH1>("cat", t);

  TScan<CH1>("2017-30-40", t);

  D_PRINTF("\nDone testing date parsing utils! :-)\n");
#endif
  return nullptr;
}
}  // namespace script2
