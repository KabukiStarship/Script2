/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /event.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_EVENT_C
#define SCRIPT2_EVENT_C

#include "op.h"

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
