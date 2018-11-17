/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_wall.cc
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
#if SEAM >= _0_0_0__13

#if SEAM == _0_0_0__13
#include "test_release.inl"
#else
#include "test_release.inl"
#endif

#include "wall.h"

#include "csocket.h"
#include "cstack.h"

#include "test_header.h"

namespace _ {

Wall::~Wall() {
  if (is_dynamic_) {
    char* socket = reinterpret_cast<char*>(doors_);
    delete[] socket;
  }
}

Wall::Wall(size_t size_bytes) : is_dynamic_(true) {
  size_bytes = size_bytes < kMinSizeBytes ? (UIT)kMinSizeBytes : size_bytes;
  size_bytes = TAlignUpUnsigned<SI8, size_t>(size_bytes);
  size_t size_words = (size_bytes >> sizeof(void*)) + 3;
  UIW *socket = new UIW[size_words],
      *aligned_buffer = AlignUpPointer8<UIW>(socket);
  //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
  //< on 16 and 32-bit systems.
  size_bytes -= sizeof(UIW) * (aligned_buffer - socket);
  start = socket;
  doors_ = reinterpret_cast<TCArray<Door*>*>(aligned_buffer);
  StackInit(socket, size_bytes >> sizeof(UIW));
}

Wall::Wall(UIW* socket, size_t size_bytes) {
  // char* ptr     = reinterpret_cast<char*> (socket);//,
  //    * new_ptr = ptr + AlignOffset<UI8> (ptr),
  //    * end_ptr = ptr + size_bytes;
  enum {
    kBitsShift = sizeof(UIW) == 2 ? 1 : sizeof(UIW) == 2 ? 2 : 3,
  };
  // UIT size_words = (size_bytes >> kBitsShift) + 3;
  //< Computer engineering voodoo for aligning to 64-bit boundary.

  UIW* aligned_buffer = AlignUpPointer8<UIW>(socket);
  //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
  //< on 16 and 32-bit systems.
  size_bytes -= sizeof(UIW) * (aligned_buffer - socket);
  start = socket;
  doors_ = reinterpret_cast<TCArray<Door*>*>(aligned_buffer);
  StackInit(socket, size_bytes >> sizeof(UIW));
}

Wall::Wall(TCArray<Door*>* doors) {}

UIW Wall::GetSizeBytes() { return size_bytes_; }

TCArray<Door*>* Wall::Doors() { return doors_; }

Door* Wall::GetDoor(int index) { return 0; }

int Wall::OpenDoor(Door* door) { return 0; }

BOL Wall::CloseDoor(int index) { return false; }

Slot& Wall::Print(Slot& slot) {
  // Printf ("\nDoor:\nis_dynamic %s\nnum_doors: %u\nmax_num_doors: %u\n",
  //        is_dynamic ? "true" : "false", num_doors, max_num_doors);
  return slot;
}

}  // namespace _
#include "test_footer.h"
#endif  //< #if SEAM >= _0_0_0__13
