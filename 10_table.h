/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/08_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_SEAM_TABLE
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _10_Table(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_SEAM_TABLE
  TEST_BEGIN;

  Printf("\n\nTesting ASCII OBJ Types");

  Print("\n  - Running TableTest...\n");

  CH4 index;
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

  PrintLineBreak("\n  + Running MultimapTests\n", 10);

  PrintLineBreak("\n  - Running MultimapInit...\n", 5, ' ');
  SI1 index;

  enum {
    kBufferSize = 256,
    kBufferSizeWords = kBufferSize / sizeof(UIW),
  };

  slot << 'a' << "b"
       << "cd" << (SI1)1 << (UI1)2 << (SI2)3 << (UI2)4 << (SI4)5 << (UI4)6
       << (SI8)7 << (UI8)8;

  Print(slot);

  UIW socket[kBufferSizeWords];

  Multimap2* multimap = Multimap2Init(socket, 8, kBufferSize, 128);

  Assert(multimap != nullptr);

  index = Multimap2Add<UI1, kUI1>(multimap, "D", (UI1)0xFF);

  Compare(0, index) Multimap2Print(multimap);
  Compare(0, index) index = Multimap2Find(multimap, "D");
  Compare(0, index) PAUSE("\n");
  index = Multimap2Add<UI1, kUI1>(multimap, "C", (UI1)0xFF);
  Compare(1, index) index = Multimap2Find(multimap, "D");
  Compare(0, index) index = Multimap2Find(multimap, "C");
  Compare(1, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "BIn", (UI1)0xFF);
  Compare(2, index) index = Multimap2Find(multimap, "D");
  Compare(0, index) index = Multimap2Find(multimap, "C");
  Compare(1, index) index = Multimap2Find(multimap, "BIn");
  Compare(2, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "A", (UI1)0xFF);
  Compare(3, index) index = Multimap2Find(multimap, "D");
  Compare(0, index) index = Multimap2Find(multimap, "C");
  Compare(1, index) index = Multimap2Find(multimap, "BIn");
  Compare(2, index) index = Multimap2Find(multimap, "A");
  Compare(3, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "abc", (UI1)0xFF);
  Compare(4, index) index = Multimap2Find(multimap, "abc");
  Compare(4, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "bac", (UI1)0xFF);
  Compare(5, index) index = Multimap2Find(multimap, "abc");
  Compare(4, index) index = Multimap2Find(multimap, "bac");
  Compare(5, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "cba", (UI1)0xFF);
  Compare(6, index) index = Multimap2Find(multimap, "abc");
  Compare(4, index) index = Multimap2Find(multimap, "bac");
  Compare(5, index) index = Multimap2Find(multimap, "cba");
  Compare(6, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "cab", (UI1)0xFF);
  Compare(7, index) index = Multimap2Find(multimap, "abc");
  Compare(4, index) index = Multimap2Find(multimap, "bac");
  Compare(5, index) index = Multimap2Find(multimap, "cba");
  Compare(6, index) index = Multimap2Find(multimap, "cab");
  Compare(7, index);

  index = Multimap2Add<UI1, kUI1>(multimap, "test", (UI1)0xFF);
  Compare(index, -1);
#endif
  return nullptr;
}
}  // namespace script2
