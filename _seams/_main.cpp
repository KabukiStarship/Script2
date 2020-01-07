/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /_seams/main.cpp
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_config.h>

#include "../_impl.inl"

#include "00.uniprinter.inl"
#include "01.rng.inl"
#include "02.itos.inl"
#include "03.ftos.inl"
#include "04.sprinter.inl"
#include "05.clock.inl"
#include "06.stack.inl"
#include "07.matrix.inl"
#include "08.strand.inl"
#include "09.loom.inl"
#include "10.list.inl"
#include "11.book.inl"
#include "12.map.inl"
#include "13.table.inl"
#include "14.dic.inl"
#include "15.expr.inl"
#include "16.door.inl"
#include "17.room.inl"
#include "18.release.inl"

using namespace _;
using namespace script2;

ISN main(ISN arg_count, CHA** args) {
#if SEAM == SEAM_N
  return SeamResult(Release(ArgsToString(arg_count, args)));
#else
  return TTestTree<Uniprinter, RNG, ItoS, FtoS, SPrinter, Clock, Stack, Matrix,
                   Strand, Loom, List, Book, Map, Table, Dic, Expr, Door, Room>(
      arg_count, args);
#endif
}
