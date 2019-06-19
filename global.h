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

#if SEAM == SCRIPT2_SEAM_RNG
#include "c_cout.h"
#include "c_rng.h"
#endif
#if SEAM == SCRIPT2_SEAM_ITOS
#include "c_cout.h"
#include "c_rng.h"
#endif
#if SEAM == SCRIPT2_SEAM_SOCKET
#include "c_cout.h"
#include "c_rng.h"
#include "t_socket.h"
#include "t_utf.h"
#endif
#if SEAM == SCRIPT2_SEAM_UTF || SEAM == SCRIPT2_SEAM_FTOS
#include "c_cout.h"
#include "c_rng.h"
#include "t_utf.h"
#endif
#if SEAM == SCRIPT2_SEAM_CLOCK
#include "c_cout.h"
#include "c_rng.h"
#include "t_clock.h"
#endif
#if SEAM == SCRIPT2_SEAM_STRAND
#endif
#if SEAM == SCRIPT2_SEAM_STACK
#endif
#if SEAM == SCRIPT2_SEAM_MATRIX
#endif
#if SEAM == SCRIPT2_SEAM_LOOM
#endif
#if SEAM == SCRIPT2_SEAM_TABLE
#endif
#if SEAM == SCRIPT2_SEAM_LIST
#endif
#if SEAM == SCRIPT2_SEAM_MAP
#endif
#if SEAM == SCRIPT2_SEAM_BOOK
#endif
#if SEAM == SCRIPT2_SEAM_DIC
#endif
#if SEAM == SCRIPT2_SEAM_EXPR
#endif
#if SEAM == SCRIPT2_SEAM_DOOR
#endif
#if SEAM == SCRIPT2_SEAM_ROOM
#endif

#endif  //< #ifndef INCLUDED_SCRIPTGLOBAL
