/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /socket.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_BUFFER
#define SCRIPT2_BUFFER
// Dependencies:
#include "c_onfig.h"
// End dependencies.

namespace _ {

/* Creates/Gets a static socket of the specified size. */
template <SIW kBufferSize = kBufferSizeDefault>
inline CH1* Buffer() {
  enum {
    kBufferSizeWords =
        (kBufferSize / sizeof(UIW)) + kBufferSize % sizeof(UIW) ? 1 : 0
  };
  static UIW socket[kBufferSizeWords];
  return reinterpret_cast<CH1*>(socket);
}

}  // namespace _
#endif  //< SCRIPT2_BUFFER
#endif  //< #if SEAM >= SCRIPT2_DICTIONARY
