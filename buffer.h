/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /socket.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_BUFFER
#define SCRIPT2_BUFFER
// Dependencies:

// End dependencies.

namespace _ {

/* Creates/Gets a static socket of the specified size. */
template <ISW cBufferSize = cBufferSizeDefault>
inline CHA* Buffer() {
  enum {
    cBufferSizeWords =
        (cBufferSize / sizeof(UIW)) + cBufferSize % sizeof(UIW) ? 1 : 0
  };
  static UIW socket[cBufferSizeWords];
  return reinterpret_cast<CHA*>(socket);
}

}  // namespace _
#endif  //< SCRIPT2_BUFFER
#endif  //< #if SEAM >= SCRIPT2_DIC
