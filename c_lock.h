/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_lock.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */
#pragma once
#include <pch.h>
#ifndef INCLUDED_SCRIPTLOCK
#define INCLUDED_SCRIPTLOCK
namespace _ {
/* Locks the processor. */
SDK inline void RoomLock();

/* Unlocks the processor. */
SDK inline void RoomUnlock();
}  //< namespace _
#endif  //< #if INCLUDED_SCRIPTLOCK
