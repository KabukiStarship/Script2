/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /Error.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_ERROR_DECL
#define SCRIPT2_ERROR_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_LIST
namespace _ {

// @see _ConfigHeader.inl for enum of error codes.

/* Returns an array or  pointers for the KabukiError(s). */
LIB_MEMBER const CHA** STRErrors();

/* Returns one of the Errors () Strings. */
LIB_MEMBER const CHA* STRError(ISN error);

}  //< namespace _
#endif
#endif
