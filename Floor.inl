/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Floor.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Floor.h"
#include "Binary.hpp"
namespace _ {

CHA FloorInit(IUW* socket) { return 0; }

Floor* FloorInit(Floor* floor) {
  floor->epoch = cClockEpochInit;
  return floor;
}

inline Floor* Global() {
  static TBUF<cFloorSize, cCpuCacheLineSize> floor_socket;
  return floor_socket.Start<Floor>();
}

}  //< namespace _
#endif
