/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_wall.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#if SEAM >= SCRIPT2_14

#if SEAM == SCRIPT2_14
#include "module_release.inl"
#else
#include "module_release.inl"
#endif

#include "c_wall.h"

#include "c_socket.h"
#include "c_stack.h"

namespace _ {

Wall::~Wall() {
  if (is_dynamic_) {
    CH1* socket = reinterpret_cast<CH1*>(doors_);
    delete[] socket;
  }
}

Wall::Wall(SIW size_bytes) : is_dynamic_(true) {
  size_bytes = size_bytes < kMinSizeBytes ? (SI4)kMinSizeBytes : size_bytes;
  size_bytes = TAlignUpUnsigned<SI8, SIW>(size_bytes);
  SIW size_words = (size_bytes >> sizeof(void*)) + 3;
  UIW *socket = new UIW[size_words],
      *aligned_buffer = AlignUpPointer8<UIW>(socket);
  //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
  //< on 16 and 32-bit systems.
  size_bytes -= sizeof(UIW) * (aligned_buffer - socket);
  begin = socket;
  doors_ = reinterpret_cast<TArray<Door*>*>(aligned_buffer);
  TStackInit(socket, size_bytes >> sizeof(UIW));
}

Wall::Wall(UIW* socket, SIW size_bytes) {
  // CH1* ptr     = reinterpret_cast<CH1*> (socket);//,
  //    * new_ptr = ptr + AlignOffset<UI8> (ptr),
  //    * end_ptr = ptr + size_bytes;
  enum {
    kBitsShift = sizeof(UIW) == 2 ? 1 : sizeof(UIW) == 2 ? 2 : 3,
  };
  // SI4 size_words = (size_bytes >> kBitsShift) + 3;
  //< Computer engineering voodoo for aligning to 64-bit boundary.

  UIW* aligned_buffer = AlignUpPointer8<UIW>(socket);
  //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
  //< on 16 and 32-bit systems.
  size_bytes -= sizeof(UIW) * (aligned_buffer - socket);
  begin = socket;
  doors_ = reinterpret_cast<TArray<Door*>*>(aligned_buffer);
  TStackInit(socket, size_bytes >> sizeof(UIW));
}

Wall::Wall(TArray<Door*>* doors) {}

UIW Wall::GetSizeBytes() { return size_bytes_; }

TArray<Door*>* Wall::Doors() { return doors_; }

Door* Wall::GetDoor(SI4 index) { return 0; }

SI4 Wall::OpenDoor(Door* door) { return 0; }

BOL Wall::CloseDoor(SI4 index) { return false; }

Slot& Wall::Print(Slot& slot) {
  // Printf ("\nDoor:\nis_dynamic %s\nnum_doors: %u\nmax_num_doors: %u\n",
  //        is_dynamic ? "true" : "false", num_doors, max_num_doors);
  return slot;
}

}  // namespace _
#include "global_footer.inl"
#endif  //< #if SEAM >= SCRIPT2_14
