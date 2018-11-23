/* Script^2 @version 0.x
@file    /0_0_0__07_ascii_table.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM == _0_0_0__07
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

static const char* _0_0_0__07_ASCII_Loom(char* seam_log, char* seam_end,
                                         const char* args) {
#if SEAM >= _0_0_0__07
  TEST_BEGIN;

  Printf("\n\nTesting ASCII OBJ Types");

  Print("\n  - Running TableTest...\n");

  CHW index;
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
}  // namespace _
