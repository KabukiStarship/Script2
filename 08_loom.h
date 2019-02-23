/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/07_table.h
@author  Cale McCollough <cale@astartup.net>
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

#if SEAM == SCRIPT2_8
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* _08_Loom(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_8
  TEST_BEGIN;

  UIW socket[kBufferSizeWords];

  Loom2* loom = Loom2Init(socket, 8, kBufferSize, 128);

  Assert(loom != nullptr);

  index = Loom2Add<UI1, kUI1>(loom, "D", (UI1)0xFF);

  Compare(0, index) Loom2Print(loom);
  Compare(0, index) index = Loom2Find(loom, "D");
  Compare(0, index) PAUSE("\n");
  index = Loom2Add<UI1, kUI1>(loom, "C", (UI1)0xFF);
  Compare(1, index) index = Loom2Find(loom, "D");
  Compare(0, index) index = Loom2Find(loom, "C");
  Compare(1, index);

  index = Loom2Add<UI1, kUI1>(loom, "BIn", (UI1)0xFF);
  Compare(2, index) index = Loom2Find(loom, "D");
  Compare(0, index) index = Loom2Find(loom, "C");
  Compare(1, index) index = Loom2Find(loom, "BIn");
  Compare(2, index);

  index = Loom2Add<UI1, kUI1>(loom, "A", (UI1)0xFF);
  Compare(3, index) index = Loom2Find(loom, "D");
  Compare(0, index) index = Loom2Find(loom, "C");
  Compare(1, index) index = Loom2Find(loom, "BIn");
  Compare(2, index) index = Loom2Find(loom, "A");
  Compare(3, index);

  index = Loom2Add<UI1, kUI1>(loom, "abc", (UI1)0xFF);
  Compare(4, index) index = Loom2Find(loom, "abc");
  Compare(4, index);

  index = Loom2Add<UI1, kUI1>(loom, "bac", (UI1)0xFF);
  Compare(5, index) index = Loom2Find(loom, "abc");
  Compare(4, index) index = Loom2Find(loom, "bac");
  Compare(5, index);

  index = Loom2Add<UI1, kUI1>(loom, "cba", (UI1)0xFF);
  Compare(6, index) index = Loom2Find(loom, "abc");
  Compare(4, index) index = Loom2Find(loom, "bac");
  Compare(5, index) index = Loom2Find(loom, "cba");
  Compare(6, index);

  index = Loom2Add<UI1, kUI1>(loom, "cab", (UI1)0xFF);
  Compare(7, index) index = Loom2Find(loom, "abc");
  Compare(4, index) index = Loom2Find(loom, "bac");
  Compare(5, index) index = Loom2Find(loom, "cba");
  Compare(6, index) index = Loom2Find(loom, "cab");
  Compare(7, index);

  index = Loom2Add<UI1, kUI1>(loom, "test", (UI1)0xFF);
  Compare(index, -1);
#endif
  return nullptr;
}
}  // namespace script2
