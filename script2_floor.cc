/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_floor.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SEAM_SCRIPT2_DICTIONARY
#include "c_floor.h"

#include "c_lock.h"
#include "t_socket.h"

namespace _ {

CH1 FloorInit(UIW* socket) { return 0; }

Floor* FloorInit(Floor* floor) {
  floor->epoch = kClockEpochInit;
  return floor;
}

inline Floor* Global() {
  static TSocket<kFloorSize, kCpuCacheLineSize> floor_socket;
  return floor_socket.Start<Floor>();
}

}  // namespace _
#endif  // #if SEAM >= SEAM_SCRIPT2_DICTIONARY
