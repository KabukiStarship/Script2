/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/16.door.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_DOOR
#include "../room.h"
using namespace _;
#if SEAM == SCRIPT2_DOOR
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
static const CHA* Door(const CHA* args) {
#if SEAM == SCRIPT2_DOOR
  A_TEST_BEGIN;
  ADoor door;
  Slot slot
#endif
      return nullptr;
}
}  // namespace script2
