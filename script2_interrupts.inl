/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_exceptions.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
// Dependencies:
#include "c_interrupts.h"
// End dependencies.
#if USING_SCRIPT2_INTERRUPTS
#include <cassert>

namespace _ {

#if USING_SCRIPT2_TEXT
const CH1* RoomCrashException::what() const throw() {
  return "External crash";
}
#endif

}  //< namespace _
#endif  //< USING_SCRIPT2_INTERRUPTS
#endif  ///< #if SEAM >= SCRIPT2_DICTIONARY
