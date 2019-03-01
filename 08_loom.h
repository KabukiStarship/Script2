/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/07_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

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
