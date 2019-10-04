/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/18.release.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once

#if SEAM >= SCRIPT2_RELEASE
#if SEAM == SCRIPT2_RELEASE
#include "../_debug.inl"
#else
#include "../_release.inl"
#endif
#endif

namespace script2 {
inline const CH1* Release(const CH1* args) {
#if SEAM == SCRIPT2_RELEASE
#endif
  return nullptr;
}
}  // namespace script2
