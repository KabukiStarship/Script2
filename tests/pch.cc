/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /pch.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
//
#include "../module_assembly.inl"

#if SCRIPT2_RUN_TESTS == YES_0

#include "../test.hpp"

#if SEAM >= SCRIPT2_UNIPRINTER
#include "00_uniprinter.h"
#endif
#if SEAM >= SCRIPT2_RNG
#include "01_rng.h"
#endif
#if SEAM >= SCRIPT2_ITOS
#include "02_itos.h"
#endif
#if SEAM >= SCRIPT2_FTOS
#include "03_ftos.h"
#endif
#if SEAM >= SCRIPT2_SPRINTER
#include "04_sprinter.h"
#endif
#if SEAM >= SCRIPT2_CLOCK
#include "05_clock.h"
#endif
#if SEAM >= SCRIPT2_STACK
#include "06_stack.h"
#endif
#if SEAM >= SCRIPT2_MATRIX
#include "07_matrix.h"
#endif
#if SEAM >= SCRIPT2_STRAND
#include "08_strand.h"
#endif
#if SEAM >= SCRIPT2_LOOM
#include "09_loom.h"
#endif
#if SEAM >= SCRIPT2_LIST
#include "10_list.h"
#endif
#if SEAM >= SCRIPT2_BOOK
#include "11_book.h"
#endif
#if SEAM >= SCRIPT2_MAP
#include "12_map.h"
#endif
#if SEAM >= SCRIPT2_TABLE
#include "13_table.h"
#endif
#if SEAM >= SCRIPT2_DICTIONARY
#include "14_dictionary.h"
#endif
#if SEAM >= SCRIPT2_EXPR
#include "15_expr.h"
#endif
#if SEAM >= SCRIPT2_DOOR
#include "16_door.h"
#endif
#if SEAM >= SCRIPT2_ROOM
#include "17_room.h"
#endif

using namespace _;

namespace script2 {
static const CH1* TestNode(const CH1* args) {
  return TTestTree<Uniprinter
#if SEAM >= SCRIPT2_RNG
                   ,
                   RNG
#endif
#if SEAM >= SCRIPT2_ITOS
                   ,
                   ItoS
#endif
#if SEAM >= SCRIPT2_FTOS
                   ,
                   FtoS
#endif
#if SEAM >= SCRIPT2_SPRINTER
                   ,
                   SPrinter
#endif
#if SEAM >= SCRIPT2_CLOCK
                   ,
                   Clock
#endif
#if SEAM >= SCRIPT2_STACK
                   ,
                   Stack
#endif
#if SEAM >= SCRIPT2_MATRIX
                   ,
                   Matrix
#endif
#if SEAM >= SCRIPT2_STRAND
                   ,
                   Strand
#endif
#if SEAM >= SCRIPT2_LOOM
                   ,
                   Loom
#endif
#if SEAM >= SCRIPT2_LIST
                   ,
                   List
#endif
#if SEAM >= SCRIPT2_BOOK
                   ,
                   Book
#endif
#if SEAM >= SCRIPT2_MAP
                   ,
                   Map
#endif
#if SEAM >= SCRIPT2_TABLE
                   ,
                   Table
#endif
#if SEAM >= SCRIPT2_DICTIONARY
                   ,
                   Dictionary
#endif
#if SEAM >= SCRIPT2_EXPR
                   ,
                   Expr
#endif
#if SEAM >= SCRIPT2_DOOR
                   ,
                   Door
#endif
#if SEAM >= SCRIPT2_ROOM
                   ,
                   Room
#endif
                   >(args);
}
}  // namespace script2

SIN main(SIN arg_count, CH1** args) {
  return _::TTestTree<script2::TestNode>(arg_count, args);
}
#endif
