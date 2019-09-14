/* SCRIPT Script (Script^2) @version 0.x
@link    https://github.com/kabuki-starship/kabuki_toolkit.git
@file    /script2_event.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#include "c_event.h"

namespace _ {

Event::Event() : timestamp_(0, 0) {}

Event::~Event() {}

TSS Event::GetTimestamp() { return timestamp_; }

}  // namespace _
#endif  //< #if SEAM >= KABUKI_TOOLKIT_AV_1
