/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/interrupts.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_SEAM_DIC
#ifndef INCLUDED_SCRIPT2_EXCEPTIONS
#define INCLUDED_SCRIPT2_EXCEPTIONS YES
#if USING_SCRIPT2_INTERRUPTS == YES

namespace _ {

#if USING_TEXT_SCRIPT == YES
/* Exception thrown to interrupt and crash the program. */
struct SDK RoomCrashException : public std::exception {
  const CH1* what() const throw();
};
#endif
}  // namespace _
#endif  //< #if USING_SCRIPT2_INTERRUPTS == YES
#endif  //< #if INCLUDED_SCRIPT2_EXCEPTIONS == YES
#endif  //< #if SEAM >= SCRIPT2_SEAM_DIC
