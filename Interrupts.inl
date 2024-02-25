/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Interrupts.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
// Dependencies:
#include "Interrupts.h"
// End dependencies.
#if USING_SCRIPT2_INTERRUPTS
#include <cassert>
namespace _ {

#if USING_SCRIPT2_TEXT
const CHA* RoomCrashException::what() const throw() { return "External crash"; }
#endif

}  //< namespace _
#endif  //< USING_SCRIPT2_INTERRUPTS
#endif  ///< #if SEAM >= SCRIPT2_DIC
