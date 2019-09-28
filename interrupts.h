/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /interrupts.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef INCLUDED_SCRIPT2_EXCEPTIONS
#define INCLUDED_SCRIPT2_EXCEPTIONS YES_0
#if USING_SCRIPT2_INTERRUPTS == YES_0

namespace _ {

#if USING_TEXT_SCRIPT == YES_0
/* Exception thrown to interrupt and crash the program. */
struct LIB_MEMBER RoomCrashException : public std::exception {
  const CH1* what() const throw();
};
#endif
}  // namespace _
#endif
#endif
#endif
