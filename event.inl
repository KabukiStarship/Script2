/* Script2 (TM) (Script^2) @version 0.x
@link    https://github.com/KabukiStarship/kabuki.toolkit.git
@file    /Event.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#include "Event.h"

namespace _ {

Event::Event() : timestamp_(0, 0) {}

Event::~Event() {}

TSS Event::GetTimestamp() { return timestamp_; }

}  // namespace _
#endif
