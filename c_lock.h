/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_lock.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */
#pragma once
#include <pch.h>
#ifndef INCLUDED_SCRIPTLOCK
#define INCLUDED_SCRIPTLOCK
namespace _ {
/* Locks the processor. */
LIB_MEMBER inline void RoomLock();

/* Unlocks the processor. */
LIB_MEMBER inline void RoomUnlock();
}  //< namespace _
#endif  //< #if INCLUDED_SCRIPTLOCK
