/* Script2 (TM) (Script^2) @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.git
@file    /event.inl
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>
#if SEAM >= SCRIPT2_DIC
#include "event.h"

namespace _ {

Event::Event() : timestamp_(0, 0) {}

Event::~Event() {}

TSS Event::GetTimestamp() { return timestamp_; }

}  // namespace _
#endif
