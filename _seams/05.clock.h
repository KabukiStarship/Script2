/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/05.clock.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_CLOCK
#include "../clock.hpp"
#include "../stringf.hpp"
using namespace _;
#if SEAM == SCRIPT2_CLOCK
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
static const CH1* Clock(const CH1* args) {
#if SEAM >= SCRIPT2_CLOCK
  A_TEST_BEGIN;

  D_COUT(Headingf("\n\nTesting TScanTime..."));

  TM4 t, t_found;
  const CH1* result;

  // @note The following dates must be the current day to work right in order
  //       to auto-detect the year.
  const CH1* Strings[] = {
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
    D_COUT(Linef('-') << "\n    " << i);
    TM4 t = 0;
    result = ScanTime(Strings[i], t);
    // Assert (!ClockCompare (t, 2018, 8, 9, 0, 0, 0))
  }

  D_COUT("\n\nTesting more valid input...\n");

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
  D_COUT("\n  Before:\"" << socket << '\"');
  result = TSScan<CH1>(socket, t_found);
  D_COUT("\n\n\nresult:\"" << TClock<SI4>(t_found) << "\"\"");
  A_ASSERT(ClockCompare(t, t_found));

  D_COUT(Headingf("Testing invalid input"));
  TSScan<CH1>("cat", t);

  TSScan<CH1>("2017-30-40", t);

  D_COUT("\nDone testing date parsing utils! :-)\n");
#endif
  return nullptr;
}
}  // namespace script2
