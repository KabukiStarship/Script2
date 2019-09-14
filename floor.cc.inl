/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /floor.inl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#include "floor.h"

#include "binary.hpp"
#include "lock.h"

namespace _ {

CH1 FloorInit(UIW* socket) { return 0; }

Floor* FloorInit(Floor* floor) {
  floor->epoch = kClockEpochInit;
  return floor;
}

inline Floor* Global() {
  static TUIB<kFloorSize, kCpuCacheLineSize> floor_socket;
  return floor_socket.Start<Floor>();
}

}  // namespace _
#endif
