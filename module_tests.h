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

#if SEAM >= SCRIPT2_0
#include "00_rng.h"
#endif
#if SEAM >= SCRIPT2_1
#include "01_itos_stoi.h"
#endif
#if SEAM >= SCRIPT2_2
#include "02_socket.h"
#endif
#if SEAM >= SCRIPT2_3
#include "03_utf.h"
#endif
#if SEAM >= SCRIPT2_4
#include "04_ftos_stof.h"
#endif
#if SEAM >= SCRIPT2_5
#include "05_clock.h"
#endif
#if SEAM >= SCRIPT2_6
#include "06_strand.h"
#endif
#if SEAM >= SCRIPT2_7
#include "07_stack.h"
#endif
#if SEAM >= SCRIPT2_8
#include "08_stack.h"
#endif
#if SEAM >= SCRIPT2_9
#include "09_loom.h"
#endif
#if SEAM >= SCRIPT2_10
#include "10_table.h"
#endif
#if SEAM >= SCRIPT2_11
#include "11_list.h"
#endif
#if SEAM >= SCRIPT2_12
#include "12_map.h"
#endif
#if SEAM >= SCRIPT2_13
#include "13_book.h"
#endif
#if SEAM >= SCRIPT2_14
#include "14_dictionary.h"
#endif
#if SEAM >= SCRIPT2_15
#include "15_expr.h"
#endif
#if SEAM >= SCRIPT2_16
#include "16_door.h"
#endif
#if SEAM >= SCRIPT2_17
#include "17_room_wall.h"
#endif

using namespace _;

namespace script2 {
static const CH1* TestNode(CH1* seam_log, CH1* seam_end, const CH1* args) {
  return TTestTree<_00_RNG
#if SEAM >= SCRIPT2_1
                   ,
                   _01_ItoS_StoI
#endif
#if SEAM >= SCRIPT2_2
                   ,
                   _02_Socket
#endif
#if SEAM >= SCRIPT2_3
                   ,
                   _03_UTF
#endif
#if SEAM >= SCRIPT2_4
                   ,
                   _04_FtoS_StoF
#endif
#if SEAM >= SCRIPT2_5
                   ,
                   _05_Clock
#endif
#if SEAM >= SCRIPT2_6
                   ,
                   _06_Strand
#endif
#if SEAM >= SCRIPT2_7
                   ,
                   _07_Stack
#endif
#if SEAM >= SCRIPT2_8
                   ,
                   _08_Array
#endif
#if SEAM >= SCRIPT2_9
                   ,
                   _09_Loom
#endif
#if SEAM >= SCRIPT2_10
                   ,
                   _10_Table
#endif
#if SEAM >= SCRIPT2_11
                   ,
                   _11_List
#endif
#if SEAM >= SCRIPT2_12
                   ,
                   _12_Map
#endif
#if SEAM >= SCRIPT2_13
                   ,
                   _13_Book
#endif
#if SEAM >= SCRIPT2_14
                   ,
                   _14_Dictionary
#endif
#if SEAM >= SCRIPT2_15
                   ,
                   _15_Expr
#endif
#if SEAM >= SCRIPT2_16
                   ,
                   _16_Door
#endif
#if SEAM >= SCRIPT2_17
                   ,
                   _17_Room_Wall
#endif
                   >(seam_log, seam_end, args);
}
}  // namespace script2
