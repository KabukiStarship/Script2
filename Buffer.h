/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Boofer.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_boofer
#define SCRIPT2_boofer
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
namespace _ {

/* Creates/Gets a static socket of the specified size. */
template<ISW cBooferSize = cBooferSizeDefault>
inline CHA* Boofer() {
  enum {
    cBooferSizeWords =
        (cBooferSize / sizeof(IUW)) + cBooferSize % sizeof(IUW) ? 1 : 0
  };
  static IUW socket[cBooferSizeWords];
  return TPtr<CHA>(socket);
}

}  //< namespace _
#endif
#endif
