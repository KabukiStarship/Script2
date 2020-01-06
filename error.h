/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /error.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-9 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_LIST
#ifndef SCRIPT2_ERROR
#define SCRIPT2_ERROR

namespace _ {

// @see conifg_header.inl for enum of error codes.

/* Returns an array or  pointers for the KabukiError(s). */
LIB_MEMBER const CHA** STRErrors();

/* Returns one of the Errors () Strings. */
LIB_MEMBER const CHA* STRError(ISN error);

}  // namespace _
#endif
#endif
