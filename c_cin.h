/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_cin.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
