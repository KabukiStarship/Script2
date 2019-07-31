/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_array.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#if SEAM >= SCRIPT2_STACK

#include "c_array.h"
#include "t_binary.h"

#if SEAM == SCRIPT2_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

// enum {
//  kWordBitCount = (sizeof(void*) == 8) ? 3 : (sizeof(void*) == 4) ? 2 : 1
//};

template <DTW kDataType_>
UIW* TRamFactoryHeap(UIW* obj, SIW size) {
  if (obj) {
    delete[] obj;
  }
  if (size < 0) {
    if (size == 0) return (UIW*)RamFactoryHeap;
    return (UIW)kDataType_;
  }
  size += (-size) & (sizeof(UIW) - 1);
  return new UIW[size >> kWordBitCount];
}

template <DTW kDataType_>
UIW* TRamFactoryStack(UIW* obj, SIW size) {
  if (obj) {
    delete[] obj;
  }
  if (size < 0) {
    if (size == 0) return (UIW*)RamFactoryHeap;
    return (UIW)kDataType_;
  }
  size += (-size) & (sizeof(UIW) - 1);
  return new UIW[size >> kWordBitCount];
}

UIW* RamFactoryStack(UIW* obj, SIW size) {
  return TRamFactoryStack<kNIL>(obj, size);
}

UIW* RamFactoryHeap(UIW* obj, SIW size) {
  return TRamFactoryHeap<kNIL>(obj, size);
}

UIW* AutojectBeginSet(Autoject& obj, void* buffer) {
  UIW* ptr = reinterpret_cast<UIW*>(buffer);
  if (!ptr) return ptr;
  obj.begin = ptr;
  return ptr;
}

}  // namespace _
#endif
