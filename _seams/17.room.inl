/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/17.room.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_ROOM
#include "../room.h"
using namespace _;
#if SEAM == SCRIPT2_ROOM
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
static const CHA* Room(const CHA* args) {
#if SEAM == SCRIPT2_ROOM
  A_TEST_BEGIN;
  Room room_a, room_b;
#endif
  return nullptr;
}
}  // namespace script2
