/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/test_tree.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_RNG
#include "00_rng.h"
#endif
#if SEAM >= SCRIPT2_SEAM_ITOS
#include "01_itos.h"
#endif
#if SEAM >= SCRIPT2_SEAM_SOCKET
#include "02_socket.h"
#endif
#if SEAM >= SCRIPT2_SEAM_FTOS
#include "03_ftos.h"
#endif
#if SEAM >= SCRIPT2_SEAM_UTF
#include "04_utf.h"
#endif
#if SEAM >= SCRIPT2_SEAM_CLOCK
#include "05_clock.h"
#endif
#if SEAM >= SCRIPT2_SEAM_STRAND
#include "06_strand.h"
#endif
#if SEAM >= SCRIPT2_SEAM_STACK
#include "07_stack.h"
#endif
#if SEAM >= SCRIPT2_SEAM_ARRAY
#include "08_stack.h"
#endif
#if SEAM >= SCRIPT2_SEAM_LOOM
#include "09_loom.h"
#endif
#if SEAM >= SCRIPT2_SEAM_TABLE
#include "10_table.h"
#endif
#if SEAM >= SCRIPT2_SEAM_LIST
#include "11_list.h"
#endif
#if SEAM >= SCRIPT2_SEAM_MAP
#include "12_map.h"
#endif
#if SEAM >= SCRIPT2_SEAM_BOOK
#include "13_book.h"
#endif
#if SEAM >= SCRIPT2_SEAM_DIC
#include "14_dictionary.h"
#endif
#if SEAM >= SCRIPT2_SEAM_EXPR
#include "15_expr.h"
#endif
#if SEAM >= SCRIPT2_SEAM_DOOR
#include "16_door.h"
#endif
#if SEAM >= SCRIPT2_SEAM_ROOM
#include "17_room.h"
#endif

using namespace _;

namespace script2 {
static const CH1* TestNode(CH1* seam_log, CH1* seam_end, const CH1* args) {
  return TTestTree<_00_RNG
#if SEAM >= SCRIPT2_SEAM_ITOS
                   ,
                   _01_ItoS_StoI
#endif
#if SEAM >= SCRIPT2_SEAM_SOCKET
                   ,
                   _02_Socket
#endif
#if SEAM >= SCRIPT2_SEAM_FTOS
                   ,
                   _04_FtoS
#endif
#if SEAM >= SCRIPT2_SEAM_UTF
                   ,
                   _04_UTF
#endif
#if SEAM >= SCRIPT2_SEAM_CLOCK
                   ,
                   _05_Clock
#endif
#if SEAM >= SCRIPT2_SEAM_STRAND
                   ,
                   _06_Strand
#endif
#if SEAM >= SCRIPT2_SEAM_STACK
                   ,
                   _07_Stack
#endif
#if SEAM >= SCRIPT2_SEAM_ARRAY
                   ,
                   _08_Array
#endif
#if SEAM >= SCRIPT2_SEAM_LOOM
                   ,
                   _09_Loom
#endif
#if SEAM >= SCRIPT2_SEAM_TABLE
                   ,
                   _10_Table
#endif
#if SEAM >= SCRIPT2_SEAM_LIST
                   ,
                   _11_List
#endif
#if SEAM >= SCRIPT2_SEAM_MAP
                   ,
                   _12_Map
#endif
#if SEAM >= SCRIPT2_SEAM_BOOK
                   ,
                   _13_Book
#endif
#if SEAM >= SCRIPT2_SEAM_DIC
                   ,
                   _14_Dictionary
#endif
#if SEAM >= SCRIPT2_SEAM_EXPR
                   ,
                   _15_Expr
#endif
#if SEAM >= SCRIPT2_SEAM_DOOR
                   ,
                   _16_Door
#endif
#if SEAM >= SCRIPT2_SEAM_ROOM
                   ,
                   _17_Room_Wall
#endif
                   >(seam_log, seam_end, args);
}
}  // namespace script2
