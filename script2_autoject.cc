/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_object.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#if SEAM >= SCRIPT2_STACK

#include "c_autoject.h"
#include "t_socket.h"

#if SEAM == SCRIPT2_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

UIW* RamFactoryHeap(UIW* obj, SIW size) {
  if (size > 0) {
    size = AlignUp(size);
    D_ASSERT(!(size & (sizeof(SIW) - 1)));
    return new UIW[TWordCount<SIW>(size)];
  }
  if (obj) delete[] obj;
  return nullptr;
}

UIW* RamFactoryStack(UIW* ptr, SIW size) {
  return RamFactoryHeap(nullptr, size);
}

UIW* AutojectBeginSet(Autoject& obj, void* buffer) {
  UIW* ptr = reinterpret_cast<UIW*>(buffer);
  if (!ptr) return ptr;
  obj.begin = ptr;
  return ptr;
}

void Delete(Autoject& obj) {
  RamFactory ram_factory = obj.ram_factory;
  if (ram_factory) ram_factory(obj.begin, 0);
}

}  // namespace _
#endif
