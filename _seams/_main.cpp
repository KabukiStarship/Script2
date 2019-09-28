/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/main.cpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#include "../_impl.inl"

#include "00.uniprinter.h"
#include "01.rng.h"
#include "02.itos.h"
#include "03.ftos.h"
#include "04.sprinter.h"
#include "05.clock.h"
#include "06.stack.h"
#include "07.matrix.h"
#include "08.strand.h"
#include "09.loom.h"
#include "10.list.h"
/*
#include "11.book.h"
#include "12.map.h"
#include "13.table.h"
#include "14.dictionary.h"
#include "15.expr.h"
#include "16.door.h"
#include "17.room.h"
*/
#include "18.release.h"

using namespace _;
using namespace script2;

SIN main(SIN arg_count, CH1** args) {
#if SEAM == SEAM_N
  return SeamResult(Release(ArgsToString(arg_count, args)));
#else
  return TTestTree<Uniprinter, RNG, ItoS, FtoS, SPrinter, Clock, Stack, Matrix,
                   Strand, Loom, List /*, Book, Map, Table, Dictionary,
Expr, Door,Room*/>(arg_count, args);
#endif
}
