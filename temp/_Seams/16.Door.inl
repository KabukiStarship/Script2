/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/16.Door.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_DOOR
#include "../Room.h"
using namespace _;
#if SEAM == SCRIPT2_DOOR
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
static const CHA* Door(const CHA* args) {
#if SEAM == SCRIPT2_DOOR
  A_TEST_BEGIN;
  ADoor door;
  Slot slot
#endif
      return nullptr;
}
}  // namespace Script2
