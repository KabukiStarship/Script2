/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Slot.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#ifndef SCRIPT2_SLOT
#define SCRIPT2_SLOT
#include "Slot.hpp"
#include "Binary.hpp"
namespace _ {

/* Calculates the used ring socket space.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
template<typename T>
inline T TSlotLength(CHA* origin, CHA* stop, IUW size) {
  return TPtr<T>(stop - origin);
}

/* Calculates the space left in the given ring socket.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
template<typename T>
inline T TSlotSpace(CHA* origin, CHA* stop, IUW size) {
  return TPtr<T>(size - (stop - origin));
}

}  //< namespace _

#endif
#endif
