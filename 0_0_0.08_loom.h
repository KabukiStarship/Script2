/* Script^2 @version 0.x
@file    /0_0_0__07_ascii_table.h
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

#if SEAM == _0_0_0__08
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

static const CH1* _0_0_0__08_ASCII_Loom(CH1* seam_log, CH1* seam_end,
                                         const CH1* args) {
#if SEAM >= _0_0_0__08
  TEST_BEGIN;

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
