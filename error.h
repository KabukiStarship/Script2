/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /error.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2014-9 Kabuki Starship <kabukistarship.com>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_ERROR
#define SCRIPT2_ERROR

namespace _ {

/* Returns an array or  pointers for the KabukiError(s). */
LIB_MEMBER const CH1** ErrorStrands();

/* Returns one of the Errors () Strings. */
LIB_MEMBER const CH1* ErrorStrand(Error error);

}  // namespace _
#endif
#endif
