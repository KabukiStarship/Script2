/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_object.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if SEAM >= SCRIPT2_3

#include "c_object.h"
#include "c_socket.h"
#include "t_object.h"

#if SEAM == SCRIPT2_3
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

const CH1* STRAsciiFactoryFunction(SIN index) {
  static const CH1 kStrings[7][8] = {"CanGrow", "Destroy", "New",    "Clone",
                                     "Grow",    "Info",    "Invalid"};
  if (index < 0 || index >= kFactoryFunctionCount)
    return &kStrings[kFactoryFunctionCount][0];
  return &kStrings[index][0];
}

const CH1* STRAsciiFactoryError(SIN index) {
  static const CH1 kStrings[7][21] = {
      "Factory Success", "Factory nil",        "Factory nil OBJ",
      "Factory nil arg", "Factory out of RAM", "Factory size invalid",
      "Invalid"};
  if (index < 0 || index >= kFactoryErrorCount)
    return &kStrings[kFactoryErrorCount][0];
  return &kStrings[index][0];
}

SI4 ObjDo(CObject& obj, SIW function, void* arg) {
  AsciiFactory factory = obj.factory;
  if (factory) return factory(obj, function, arg);
  PRINTF("\nNil factory.", result);
  return kFactoryNil;
}

BOL ObjCountIsValid(SI1 index, SI1 count_min) {
  return TObjCountIsValid<SI1>(index, count_min);
}

void Delete(CObject& obj) {
  AsciiFactory factory = obj.factory;
  if (factory) factory(obj, kFactoryDestroy, nullptr);
}

BOL IsOBJFactoryFunction(SIW function) { return function <= kFactoryInfo; }

BOL ObjSizeIsValid(SI2 size, SI2 size_min) {
  return TObjCanGrow<SI2>(size, size_min);
}

BOL ObjSizeIsValid(SI4 size, SI4 size_min) {
  return TObjCanGrow<SI4>(size, size_min);
}

BOL ObjSizeIsValid(SI8 size, SI8 size_min) {
  return TObjCanGrow<SI8>(size, size_min);
}

BOL ObjCountIsValid(SI2 index, SI2 count_min) {
  return TObjCountIsValid<SI2>(index, count_min);
}

BOL ObjCountIsValid(SI4 index, SI4 count_min) {
  return TObjCountIsValid<SI4>(index, count_min);
}

BOL ObjCountIsValid(SI8 index, SI8 count_min) {
  return TObjCountIsValid<SI8>(index, count_min);
}

UIW* ObjNew(SI2 size, SIW header_size) {
  ASSERT(size >= 8);

  if (ObjSizeIsValid(size)) return nullptr;
  size = AlignUp(size);
  UIW* socket = new UIW[size >> kWordBitCount];
  *reinterpret_cast<SI2*>(socket) = size;
  return socket;
}

void SocketHeap(UIW* socket) {
  if (socket) delete[] socket;
}

void SocketStack(UIW* socket) {}

void ObjException(const CH1* what) {
  // PRINTF("\nERROR:%s\n", exception.what());
}

}  // namespace _
#endif
