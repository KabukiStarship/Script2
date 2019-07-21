/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/global.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SCRIPTGLOBAL
#define INCLUDED_SCRIPTGLOBAL 1

#if SEAM == SEAM_SCRIPT2_CORE
#include "c_cout.h"
#include "c_rng.h"
#endif
#if SEAM == SEAM_SCRIPT2_ITOS
#include "c_cout.h"
#include "c_rng.h"
#endif
#if SEAM == SEAM_SCRIPT2_SOCKET
#include "c_cout.h"
#include "c_rng.h"
#include "t_socket.h"
#include "t_utf.h"
#endif
#if SEAM == SEAM_SCRIPT2_UTF || SEAM == SEAM_SCRIPT2_FTOS
#include "c_cout.h"
#include "c_rng.h"
#include "t_utf.h"
#endif
#if SEAM == SEAM_SCRIPT2_CLOCK
#include "c_cout.h"
#include "c_rng.h"
#include "t_clock.h"
#endif
#if SEAM == SEAM_SCRIPT2_STRAND
#endif
#if SEAM == SEAM_SCRIPT2_STACK
#endif
#if SEAM == SEAM_SCRIPT2_MATRIX
#endif
#if SEAM == SEAM_SCRIPT2_LOOM
#endif
#if SEAM == SEAM_SCRIPT2_TABLE
#endif
#if SEAM == SEAM_SCRIPT2_LIST
#endif
#if SEAM == SEAM_SCRIPT2_MAP
#endif
#if SEAM == SEAM_SCRIPT2_BOOK
#endif
#if SEAM == SEAM_SCRIPT2_DICTIONARY
#endif
#if SEAM == SEAM_SCRIPT2_EXPR
#endif
#if SEAM == SEAM_SCRIPT2_DOOR
#endif
#if SEAM == SEAM_SCRIPT2_ROOM
#endif

#endif
