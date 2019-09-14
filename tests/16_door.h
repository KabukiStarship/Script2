/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /16_door.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_DOOR
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

#include "c_room.h"

using namespace _;

namespace script2 {
static const CH1* Door(const CH1* args) {
#if SEAM == SCRIPT2_DOOR
  A_TEST_BEGIN;
  ADoor door;
  Slot slot
#endif
      return nullptr;
}
}  // namespace script2
