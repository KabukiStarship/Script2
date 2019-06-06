/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_object.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_STRAND

#include "c_autoject.h"

#if SEAM == SCRIPT2_SEAM_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

void* Error(SIW code) { return reinterpret_cast<void*>(code); }

SIW IsError(SIW factory_result) {
  BOL is_factory_error =
      (factory_result >= 0) && (factory_result <= kFactoryErrorCount);
  return (SIW)is_factory_error;
}

SIW IsError(void* factory_result) {
  return IsError(reinterpret_cast<SIW>(factory_result));
}

const CH1* AsciiFactoryFunction(SIW index) {
  static const CH1 kStrings[7][8] = {"CanGrow", "Destroy", "New",    "Clone",
                                     "Grow",    "Info",    "Invalid"};
  if (!IsError(index)) return &kStrings[kFactoryFunctionCount][0];
  return &kStrings[index][0];
}

const CH1* AsciiFactoryError(SIW index) {
  static const CH1 kStrings[7][21] = {
      "Factory Success", "Factory nil",        "Factory nil OBJ",
      "Factory nil arg", "Factory out of RAM", "Factory size invalid",
      "Invalid"};
  if (!IsError(index)) return &kStrings[kFactoryErrorCount][0];
  return &kStrings[index][0];
}

SIW Do(Autoject& obj, SIW function, SIW arg) {
  AsciiFactory factory = obj.factory;
  if (factory) return factory(obj, function, arg);
  PRINT("\nNil factory.");
  return 0;
}

UIW* AutojectBeginSet(Autoject& obj, void* buffer) {
  UIW* ptr = reinterpret_cast<UIW*>(buffer);
  if (!ptr) return ptr;
  obj.begin = ptr;
  return ptr;
}

void Delete(Autoject& obj) {
  AsciiFactory factory = obj.factory;
  if (factory) factory(obj, kFactoryDelete, 0);
}

void ObjException(const CH1* what) {
  // PRINTF("\nERROR:%s\n", exception.what());
}

}  // namespace _
#endif
