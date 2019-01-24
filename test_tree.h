/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/test_tree.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_0
#include "00_rng.h"
#endif
#if SEAM >= SCRIPT2_1
#include "01_itos_and_stoi.h"
#endif
#if SEAM >= SCRIPT2_2
#include "02_socket.h"
#endif
#if SEAM >= SCRIPT2_3
#include "03_utf_and_strand.h"
#endif
#if SEAM >= SCRIPT2_4
#include "04_ftos_and_stof.h"
#endif
#if SEAM >= SCRIPT2_5
#include "05_clock.h"
#endif
#if SEAM >= SCRIPT2_6
#include "06_stack.h"
#endif
#if SEAM >= SCRIPT2_7
#include "07_array.h"
#endif
#if SEAM >= SCRIPT2_8
#include "08_loom.h"
#endif
#if SEAM >= SCRIPT2_9
#include "09_table.h"
#endif
#if SEAM >= SCRIPT2_10
#include "10_list.h"
#endif
#if SEAM >= SCRIPT2_11
#include "11_map.h"
#endif
#if SEAM >= SCRIPT2_12
#include "12_book.h"
#endif
#if SEAM >= SCRIPT2_13
#include "14_dictionary.h"
#endif
#if SEAM >= SCRIPT2_14
#include "14_expr.h"
#endif
#if SEAM >= SCRIPT2_15
#include "15_door.h"
#endif
#if SEAM >= SCRIPT2_16
#include "16_room_and_wall.h"
#endif

using namespace _;

namespace script2 {
static const CH1* TestNode(CH1* seam_log, CH1* seam_end, const CH1* args) {
  return TTestTree<_00_RNG

#if SEAM >= SCRIPT2_1
                   ,
                   _01_ItoS_and_StoI
#endif
#if SEAM >= SCRIPT2_2
                   ,
                   _02_Socket
#endif
#if SEAM >= SCRIPT2_3
                   ,
                   _03_UTF_and_Strand
#endif
#if SEAM >= SCRIPT2_4
                   ,
                   _04_FtoS_and_StoF
#endif
#if SEAM >= SCRIPT2_5
                   ,
                   _05_Clock
#endif
#if SEAM >= SCRIPT2_6
                   ,
                   _06_Stack
#endif
#if SEAM >= SCRIPT2_7
                   ,
                   _07_Array
#endif
#if SEAM >= SCRIPT2_8
                   ,
                   _08_Loom
#endif
#if SEAM >= SCRIPT2_9
                   ,
                   _09_Table
#endif
#if SEAM >= SCRIPT2_10
                   ,
                   _10_List
#endif
#if SEAM >= SCRIPT2_11
                   ,
                   _11_Map
#endif
#if SEAM >= SCRIPT2_12
                   ,
                   _12_Book
#endif
#if SEAM >= SCRIPT2_13
                   ,
                   _13_Dictionary
#endif
#if SEAM >= SCRIPT2_14
                   ,
                   _14_Expr
#endif
#if SEAM >= SCRIPT2_15
                   ,
                   _15_Door
#endif
#if SEAM >= SCRIPT2_16
                   ,
                   _16_Room
#endif
                   >(seam_log, seam_end, args);
}
} //< namespace script2
