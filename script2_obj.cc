/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script.git
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

void Delete(CObject obj) {
  if (!obj.manager) return;
  obj.manager(obj.begin);
}

BOL ObjSizeIsValid(SI2 size, SI2 size_min) {
  return ObjSizeIsValid<SI2>(size, size_min);
}

BOL ObjSizeIsValid(SI4 size, SI4 size_min) {
  return ObjSizeIsValid<SI4>(size, size_min);
}

BOL ObjSizeIsValid(SI8 size, SI8 size_min) {
  return ObjSizeIsValid<SI8>(size, size_min);
}

BOL ObjCountIsValid(SI1 index, SI1 count_min) {
  return ObjCountIsValid<SI1>(index, count_min);
}

BOL ObjCountIsValid(SI2 index, SI2 count_min) {
  return ObjCountIsValid<SI2>(index, count_min);
}

BOL ObjCountIsValid(SI4 index, SI4 count_min) {
  return ObjCountIsValid<SI4>(index, count_min);
}

BOL ObjCountIsValid(SI8 index, SI8 count_min) {
  return ObjCountIsValid<SI8>(index, count_min);
}

uintptr_t* ObjClone(uintptr_t* ascii_object, SI1 size) {
  return ObjClone<SI1>(ascii_object, size);
}

uintptr_t* ObjClone(uintptr_t* ascii_object, SI2 size) {
  return ObjClone<SI2>(ascii_object, size);
}

uintptr_t* ObjClone(uintptr_t* ascii_object, SI4 size) {
  return ObjClone<SI4>(ascii_object, size);
}

uintptr_t* ObjClone(uintptr_t* ascii_object, SI8 size) {
  return ObjClone<SI8>(ascii_object, size);
}

uintptr_t* ObjNew(SI2 size, size_t header_size) {
  ASSERT(size >= 8);

  if (ObjSizeIsValid(size)) return nullptr;
  size = AlignUp(size);
  uintptr_t* buffer = new uintptr_t[size >> kWordBitCount];
  *reinterpret_cast<SI2*>(buffer) = size;
  return buffer;
}

}  // namespace _
#include "test_footer.inl"
#endif  //< #if SEAM >= _0_0_0__05
