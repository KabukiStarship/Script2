/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/test_tree.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#include "t_test.h"

#if SEAM >= SEAM_SCRIPT2_CORE
#include "00_core.h"
#endif
#if SEAM >= SEAM_SCRIPT2_ITOS
#include "01_itos.h"
#endif
#if SEAM >= SEAM_SCRIPT2_SOCKET
#include "02_socket.h"
#endif
#if SEAM >= SEAM_SCRIPT2_FTOS
#include "03_ftos.h"
#endif
#if SEAM >= SEAM_SCRIPT2_UTF
#include "04_utf.h"
#endif
#if SEAM >= SEAM_SCRIPT2_CLOCK
#include "05_clock.h"
#endif
#if SEAM >= SEAM_SCRIPT2_STACK
#include "06_stack.h"
#endif
#if SEAM >= SEAM_SCRIPT2_STRAND
#include "07_strand.h"
#endif
#if SEAM >= SEAM_SCRIPT2_LOOM
#include "09_loom.h"
#endif
#if SEAM >= SEAM_SCRIPT2_TABLE
#include "10_table.h"
#endif
#if SEAM >= SEAM_SCRIPT2_LIST
#include "11_list.h"
#endif
#if SEAM >= SEAM_SCRIPT2_MAP
#include "12_map.h"
#endif
#if SEAM >= SEAM_SCRIPT2_BOOK
#include "13_book.h"
#endif
#if SEAM >= SEAM_SCRIPT2_DIC
#include "14_dictionary.h"
#endif
#if SEAM >= SEAM_SCRIPT2_EXPR
#include "15_expr.h"
#endif
#if SEAM >= SEAM_SCRIPT2_DOOR
#include "16_door.h"
#endif
#if SEAM >= SEAM_SCRIPT2_ROOM
#include "17_room.h"
#endif

using namespace _;

namespace script2 {
static const CH1* TestNode(const CH1* args) {
  return TTestTree<_00_Core
#if SEAM >= SEAM_SCRIPT2_ITOS
                   ,
                   _01_ItoS_StoI
#endif
#if SEAM >= SEAM_SCRIPT2_SOCKET
                   ,
                   _02_Socket
#endif
#if SEAM >= SEAM_SCRIPT2_FTOS
                   ,
                   _04_FtoS
#endif
#if SEAM >= SEAM_SCRIPT2_UTF
                   ,
                   _04_UTF
#endif
#if SEAM >= SEAM_SCRIPT2_CLOCK
                   ,
                   _05_Clock
#endif
#if SEAM >= SEAM_SCRIPT2_STACK
                   ,
                   _07_Stack
#endif
#if SEAM >= SEAM_SCRIPT2_STRAND
                   ,
                   _06_Strand
#endif
#if SEAM >= SEAM_SCRIPT2_LOOM
                   ,
                   _09_Loom
#endif
#if SEAM >= SEAM_SCRIPT2_TABLE
                   ,
                   _10_Table
#endif
#if SEAM >= SEAM_SCRIPT2_LIST
                   ,
                   _11_List
#endif
#if SEAM >= SEAM_SCRIPT2_MAP
                   ,
                   _12_Map
#endif
#if SEAM >= SEAM_SCRIPT2_BOOK
                   ,
                   _13_Book
#endif
#if SEAM >= SEAM_SCRIPT2_DIC
                   ,
                   _14_Dictionary
#endif
#if SEAM >= SEAM_SCRIPT2_EXPR
                   ,
                   _15_Expr
#endif
#if SEAM >= SEAM_SCRIPT2_DOOR
                   ,
                   _16_Door
#endif
#if SEAM >= SEAM_SCRIPT2_ROOM
                   ,
                   _17_Room_Wall
#endif
                   >(args);
}
}  // namespace script2
