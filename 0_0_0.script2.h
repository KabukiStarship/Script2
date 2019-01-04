/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /0_0_0.script.h
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
#if SEAM >= _0_0_0__00
#include "0_0_0.00_rng.h"
#endif
#if SEAM >= _0_0_0__01
#include "0_0_0.01_itos_and_stoi.h"
#endif
#if SEAM >= _0_0_0__02
#include "0_0_0.02_socket.h"
#endif
#if SEAM >= _0_0_0__03
#include "0_0_0.03_utf_and_strand.h"
#endif
#if SEAM >= _0_0_0__04
#include "0_0_0.04_ftos_and_stof.h"
#endif
#if SEAM >= _0_0_0__05
#include "0_0_0.05_clock.h"
#endif
#if SEAM >= _0_0_0__06
#include "0_0_0.06_stack.h"
#endif
#if SEAM >= _0_0_0__07
#include "0_0_0.07_array.h"
#endif
#if SEAM >= _0_0_0__08
#include "0_0_0.08_loom.h"
#endif
#if SEAM >= _0_0_0__09
#include "0_0_0.09_table.h"
#endif
#if SEAM >= _0_0_0__10
#include "0_0_0.10_list.h"
#endif
#if SEAM >= _0_0_0__11
#include "0_0_0.11_map.h"
#endif
#if SEAM >= _0_0_0__12
#include "0_0_0.12_book.h"
#endif
#if SEAM >= _0_0_0__13
#include "0_0_0.14_dictionary.h"
#endif
#if SEAM >= _0_0_0__14
#include "0_0_0.14_expr.h"
#endif
#if SEAM >= _0_0_0__15
#include "0_0_0.15_door.h"
#endif
#if SEAM >= _0_0_0__16
#include "0_0_0.16_room_and_wall.h"
#endif

namespace _ {
static const CH1* _0_0_0_Script2(CH1* seam_log, CH1* seam_end, const CH1* args) {
  return TTestTree<_0_0_0__00_RNG

#if SEAM >= _0_0_0__01
                   ,
                   _0_0_0__01_ItoS_and_StoI
#endif
#if SEAM >= _0_0_0__02
                   ,
                   _0_0_0__02_Socket
#endif
#if SEAM >= _0_0_0__03
                   ,
                   _0_0_0__03_UTF_and_Strand
#endif
#if SEAM >= _0_0_0__04
                   ,
                   _0_0_0__04_FtoS_and_StoF
#endif
#if SEAM >= _0_0_0__05
                   ,
                   _0_0_0__05_Clock
#endif
#if SEAM >= _0_0_0__06
                   ,
                   _0_0_0__06_Stack
#endif
#if SEAM >= _0_0_0__07
                   ,
                   _0_0_0__07_Array
#endif
#if SEAM >= _0_0_0__08
                   ,
                   _0_0_0__08_Loom
#endif
#if SEAM >= _0_0_0__09
                   ,
                   _0_0_0__09_Table
#endif
#if SEAM >= _0_0_0__10
                   ,
                   _0_0_0__10_List
#endif
#if SEAM >= _0_0_0__11
                   ,
                   _0_0_0__11_Map
#endif
#if SEAM >= _0_0_0__12
                   ,
                   _0_0_0__12_Book
#endif
#if SEAM >= _0_0_0__13
                   ,
                   _0_0_0__13_Dictionary
#endif
#if SEAM >= _0_0_0__14
                   ,
                   _0_0_0__14_Expr
#endif
#if SEAM >= _0_0_0__15
    ,
    _0_0_0__15_Door
#endif
#if SEAM >= _0_0_0__16
    ,
    _0_0_0__16_Room
#endif
                   >(seam_log, seam_end, args);
}
}  // namespace _
