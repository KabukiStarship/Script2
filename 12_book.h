/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/12_book.h
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

#if SEAM == SCRIPT2_12
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _12_Book(CH1* seam_log, CH1* seam_end,
                                        const CH1* args) {
#if SEAM >= SCRIPT2_12
  TEST_BEGIN;

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
#endif
  return nullptr;
}
} //< namespace script2
