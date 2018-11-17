/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_object.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>

#if SEAM >= _0_0_0__03

#include "cobject.h"
#include "csocket.h"
#include "tobject.h"

#if SEAM == _0_0_0__03
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

void Destroy(CObject stack) {
  if (stack.factory) stack.factory(stack.start, 0, nullptr);
}

BOL ObjSizeIsValid(SI2 size, SI2 size_min) {
  return TObjSizeIsValid<SI2>(size, size_min);
}

BOL ObjSizeIsValid(SI4 size, SI4 size_min) {
  return TObjSizeIsValid<SI4>(size, size_min);
}

BOL ObjSizeIsValid(SI8 size, SI8 size_min) {
  return TObjSizeIsValid<SI8>(size, size_min);
}

BOL ObjCountIsValid(SI1 index, SI1 count_min) {
  return TObjCountIsValid<SI1>(index, count_min);
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

UIW* ObjNew(SI2 size, size_t header_size) {
  ASSERT(size >= 8);

  if (ObjSizeIsValid(size)) return nullptr;
  size = AlignUp(size);
  UIW* socket = new UIW[size >> kWordBitCount];
  *reinterpret_cast<SI2*>(socket) = size;
  return socket;
}

}  // namespace _

#endif  //< #if SEAM >= _0_0_0__05
