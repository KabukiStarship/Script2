/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/18.Release.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once

#if SEAM >= SCRIPT2_RELEASE
#if SEAM == SCRIPT2_RELEASE
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
inline const CHA* Release(const CHA* args) {
#if SEAM == SCRIPT2_RELEASE
#endif
  return nullptr;
}
}  // namespace Script2
