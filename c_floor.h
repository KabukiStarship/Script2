/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /floor.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_FLOOR
#define SCRIPT2_FLOOR

namespace _ {

/* Cache-aligned group of global system variables.
The Floor is the Floor in the Chinese Room. In Kabuki Crabs, the floor is
designed to store variables without having to include the classes the variable
controls. For this reason only Strings and POD types are in the Floor.
*/
struct LIB_MEMBER Floor {
  SI2 epoch;
};

/* Returns the the global Floor. */
LIB_MEMBER inline Floor* Global();

}  // namespace _

#endif  // #if SCRIPT2_FLOOR
#endif  // #if SEAM >= SCRIPT2_DICTIONARY
