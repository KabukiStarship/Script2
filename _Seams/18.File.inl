/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/18.File.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_FILE
#include "../Room.h"
#if SEAM == SCRIPT2_FILE
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif
using namespace _;
namespace Script2 {

static const CHA* File(const CHA* args) {
#if SEAM == SCRIPT2_CRABS
  A_TEST_BEGIN;
  Room room_a, room_b;
#endif
  return nullptr;
}

}  //< namespace Script2
