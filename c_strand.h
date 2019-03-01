/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_strand.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_3
#ifndef INCLUDED_SCRIPTUTF
#define INCLUDED_SCRIPTUTF

#include "c_socket.h"

#if USING_UTF8 == YES
#include "c_utf1.h"
#endif
#if USING_UTF16 == YES
#include "c_utf2.h"
#endif
#if USING_UTF32 == YES
#include "c_utf4.h"
#endif


#endif  //< #if INCLUDED_SCRIPTUTF
#endif  //< #if SEAM >= SCRIPT2_3
