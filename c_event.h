/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c__event.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_14
#ifndef SCRIPT2_EVENT_C
#define SCRIPT2_EVENT_C

#include "c_op.h"

namespace _ {

/* Interface for an abstract event.
 */
struct CEvent {
  /* Virtual destructor. */
  virtual ~CEvent() = 0;

  /* Triggers the event. */
  virtual void Trigger() = 0;
};

}  // namespace _
#endif
#endif
