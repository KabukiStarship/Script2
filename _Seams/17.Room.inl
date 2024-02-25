/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/17.Room.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_CRABS
#include "../Room.h"
#if SEAM == SCRIPT2_CRABS
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif
using namespace _;
namespace Script2 {

static const CHA* Room(const CHA* args) {
#if SEAM == SCRIPT2_CRABS
  A_TEST_BEGIN;
  Room room_a, room_b;
#endif
  return nullptr;
}

}  //< namespace Script2
