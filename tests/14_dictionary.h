/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /14_dictionary.h
@author  Cale McCollough <<https://calemccollough.github.io>>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM == SCRIPT2_DICTIONARY
#include "../dictionary.hpp"
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace script2 {
static const CH1* Dictionary(CH1* seam_log, CH1* seam_end, const CH1* args) {
#if SEAM >= SCRIPT2_DICTIONARY
  A_TEST_BEGIN;

  UIW socket[kBufferSizeWords];

  Multimap2* multimap = Multimap2Init(socket, 8, kBufferSize, 128);

  Assert(multimap != nullptr);

  index = Multimap2Add<UI1, kUI1>(multimap, "D", (UI1)0xFF);

  Compare(0, index) Multimap2Print(multimap);
  Compare(0, index) index = Multimap2Find(multimap, "D");
  Compare(0, index) D_PAUSE("\n");
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
