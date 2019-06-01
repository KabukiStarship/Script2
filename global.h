/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/global.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SCRIPTGLOBAL
#define INCLUDED_SCRIPTGLOBAL 1

#if SEAM == SCRIPT2_0
#include "c_cout.h"
#include "c_rng.h"
#endif
#if SEAM == SCRIPT2_1
#include "c_cout.h"
#include "c_rng.h"
#endif
#if SEAM == SCRIPT2_2
#include "c_cout.h"
#include "c_rng.h"
#include "t_socket.h"
#include "t_uniprinter.h"
#endif
#if SEAM == SCRIPT2_3 || SEAM == SCRIPT2_4
#include "c_cout.h"
#include "c_rng.h"
#include "t_uniprinter.h"
#endif
#if SEAM == SCRIPT2_5
#include "c_cout.h"
#include "c_rng.h"
#include "t_clock.h"
#endif
#if SEAM == SCRIPT2_6
#endif
#if SEAM == SCRIPT2_7
#endif
#if SEAM == SCRIPT2_8
#endif
#if SEAM == SCRIPT2_9
#endif
#if SEAM == SCRIPT2_10
#endif
#if SEAM == SCRIPT2_11
#endif
#if SEAM == SCRIPT2_12
#endif
#if SEAM == SCRIPT2_13
#endif
#if SEAM == SCRIPT2_14
#endif
#if SEAM == SCRIPT2_15
#endif
#if SEAM == SCRIPT2_16
#endif
#if SEAM == SCRIPT2_17
#endif

#endif  //< #ifndef INCLUDED_SCRIPTGLOBAL
