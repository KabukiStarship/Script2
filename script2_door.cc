/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_door.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__13
#include "tdoor.h"

#if SEAM == _0_0_0__13
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

const Op* DoorResult(Door* door, Door::Error error) { return 0; }

const char* DoorErrorText(Door::Error error) {
  static const char* strings[] = {"Invalid op", "Room error"};

  // if (error < 0)
  //    return strings[Door::kErrorImplementation];
  return strings[error];
}

Door::Door(const char* room_name, UIW* socket, UIW size_bytes) {
  if (!socket) {
    if (size_bytes < kMinDoorSize) {
      size_bytes = kMinDoorSize;
    }
  } else {
    if (size_bytes < kMinDoorSize) {
      // @todo insert error code here
      PRINTF("\nError: Door size_bytes < kMinDoorSize!")
      return;
    }
  }
  // tx.SetBuffer (adjacentDoor->Rx ()->EndAddress () + 1), aSlotSize);
  // rx = new SerialSlot (tx.EndAddress (), aSlot, aSlotSize,
  //  aTalkbackSize);
}

Door::~Door() {
  if (start) delete[] start;
}

slot_t Door::GetSlot(slot_t index) {
  return TStackGet<slot_t, UIT, int_t>(slots_, index);
}

slot_t Door::AddSlot(slot_t slot) {
  return TStackPush<slot_t, UIT, int_t>(slots_, slot);
}

BOL Door::Contains(void* address) {
  return TStackContains<slot_t, UIT, int_t>(slots_, address);
}

slot_t Door::FindSlot(void* address) {
  slot_t count = slots_->count;
  for (slot_t i = 0; i < count; ++i) {
    // Slot* slot = nullptr; //< @todo fix me!

    if (TStackContains<slot_t, UIT, int_t>(slots_, address)) return i;
  }
  return count;
}

const Op* Door::ExecAll() { return 0; }

const Op* Door::Star(CHW index, CCrabs* crabs) {
  static const Op kThis = {
      "Door",
      OpFirst('A'),
      OpFirst('A' + slots_->count),
      "A door in a Chinese room with a bunch of slots in it where "
      "messages are passed.",
      '}',
      ';',
      ' ',
      false,
      nullptr,
      nullptr};
  if (index == '?') {
    return ExprQuery(crabs, kThis);
  }
  index -= ' ';
  if (((slot_t)index) >= slots_->count) {
    return DoorResult(this, Door::kErrorInvalidOp);
  }
  return nullptr;
}

/*
API Door& Doors () {
  static Door front_door;
  return front_door;
}*/

/* Initializes a Door at the beginning of the given socket.
static Door* DoorInit (UIW* socket, slot_t slot_size) {
  if (socket == nullptr) return nullptr;
  if (slot_size < kMinSlotSize) return nullptr;
  Wall* wall = reinterpret_cast<Door*>(socket);
  w->is_dynamic = 0;
  w->num_doors = 0;
  w->max_num_doors;
  w->door_one = nullptr;
}*/

}  // namespace _

#endif  //> #if SEAM >= _0_0_0__13
