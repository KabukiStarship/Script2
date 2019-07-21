/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_benchmark.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_BOOK
#ifndef INCLUDED_SCRIPTTBENCHMARK
#define INCLUDED_SCRIPTTBENCHMARK

#include "benchmark.h"

namespace _ {

template <typename UI>
const CH1* BenchmarkCaseLoop(CH1* cursor, CH1* stop, const CH1* args) {
  PrintHeading((sizeof(UI) == 8) ? "Testing 64-bit use case"
                                 : "Testing 32-bit use case");
}

}  // namespace _

#endif
#endif
