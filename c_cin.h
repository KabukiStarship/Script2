/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_cout.h
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

#ifndef SCRIPT2_CIN_C
#define SCRIPT2_CIN_C 1

namespace _ {

/* Prints a message then pauses the application until a key is pressed. */
SDK void Pause(const CH1* message = "");

/* Prints a message then pauses the application until a key is pressed. */
SDK void Pausef(const CH1* message, ...);

/* Reads the current key depressed on the keyboard.
@return A negative number_ (typically 1) if no keys are pressed. */
SDK SI4 CInKey();

}  // namespace _

#endif
