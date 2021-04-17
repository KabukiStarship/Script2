/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Buffer.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_BUFFER
#define SCRIPT2_BUFFER
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
namespace _ {

/* Creates/Gets a static socket of the specified size. */
template <ISW cBufferSize = cBufferSizeDefault>
inline CHA* Buffer() {
  enum {
    cBufferSizeWords =
        (cBufferSize / sizeof(IUW)) + cBufferSize % sizeof(IUW) ? 1 : 0
  };
  static IUW socket[cBufferSizeWords];
  return TPtr<CHA>(socket);
}

}  // namespace _
#endif
#endif
