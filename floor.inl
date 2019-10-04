/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /floor.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>
#if SEAM >= SCRIPT2_DIC
#include "floor.h"

#include "binary.hpp"
#include "lock.h"

namespace _ {

CH1 FloorInit(UIW* socket) { return 0; }

Floor* FloorInit(Floor* floor) {
  floor->epoch = cClockEpochInit;
  return floor;
}

inline Floor* Global() {
  static TUIB<cFloorSize, cCpuCacheLineSize> floor_socket;
  return floor_socket.Start<Floor>();
}

}  // namespace _
#endif
