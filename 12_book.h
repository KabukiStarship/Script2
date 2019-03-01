/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/12_book.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_12
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _12_Book(CH1* seam_log, CH1* seam_end,
                                        const CH1* args) {
#if SEAM >= SCRIPT2_12
  TEST_BEGIN;

  CHN index;
  UIW socket[128];
  Printf("\n &buffer[0]:%p &buffer[127]:%p\n", &socket[0], &socket[127]);

  Table* table = TableInit(socket, 8, 128);

  Assert(table != nullptr);

  index = TableAdd(table, "D");
  Compare(0, index) index = TableFind(table, "D");
  Compare(0, index);

  index = TableAdd(table, "C");
  Compare(1, index) index = TableFind(table, "D");
  Compare(0, index) index = TableFind(table, "C");
  Compare(1, index);

  index = TableAdd(table, "B");
  Compare(2, index) index = TableFind(table, "D");
  Compare(0, index) index = TableFind(table, "C");
  Compare(1, index) index = TableFind(table, "B");
  Compare(2, index);

  index = TableAdd(table, "A");
  Compare(3, index) index = TableFind(table, "D");
  Compare(0, index) index = TableFind(table, "C");
  Compare(1, index) index = TableFind(table, "B");
  Compare(2, index) index = TableFind(table, "A");
  Compare(3, index);

  index = TableAdd(table, "abc");
  Compare(4, index) index = TableFind(table, "abc");
  Compare(4, index);

  index = TableAdd(table, "bac");
  Compare(5, index) index = TableFind(table, "abc");
  Compare(4, index) index = TableFind(table, "bac");
  Compare(5, index);

  index = TableAdd(table, "cba");
  Compare(6, index) index = TableFind(table, "abc");
  Compare(4, index) index = TableFind(table, "bac");
  Compare(5, index) index = TableFind(table, "cba");
  Compare(6, index);

  index = TableAdd(table, "cab");
  Compare(7, index) index = TableFind(table, "abc");
  Compare(4, index) index = TableFind(table, "bac");
  Compare(5, index) index = TableFind(table, "cba");
  Compare(6, index) index = TableFind(table, "cab");
  Compare(7, index);

  index = TableAdd(table, "test");
  Compare(kInvalidIndex, index);

  TablePrint(table);
#endif
  return nullptr;
}
} //< namespace script2
