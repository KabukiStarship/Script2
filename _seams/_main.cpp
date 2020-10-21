/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/_Main.cpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#include <_Config.h>

#include "../_Package.inl"

#include "00.Core.inl"
#include "01.RNG.inl"
#include "02.ItoS.inl"
#include "03.FtoS.inl"
#include "04.SPrinter.inl"
#include "05.Clock.inl"
#include "06.Stack.inl"
#include "07.Matrix.inl"
#include "08.String.inl"
#include "09.Loom.inl"
#include "10.List.inl"
#include "11.Book.inl"
#include "12.Map.inl"
#include "13.Table.inl"
#include "14.Dic.inl"
#include "15.Crabs.inl"
#include "16.Door.inl"
#include "17.Room.inl"
#include "18.Release.inl"

using namespace _;
using namespace Script2;

ISN main(ISN arg_count, CHA** args) {
#if SEAM == SEAM_N
  return SeamResult(Release(ArgsToString(arg_count, args)));
#else
  return TTestTree<Core, RNG, ItoS, FtoS, SPrinter, Clock, Stack, Matrix,
                   String, Loom, List, Book, Map, Table, Dic, Crabs, Door, Room>(
      arg_count, args);
#endif
}
