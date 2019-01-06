/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tdoor.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= _0_0_0__15
#ifndef SCRIPT2_DOOR
#define SCRIPT2_DOOR
#include "ccrabs.h"
#include "cslot.h"
#include "tstack.h"
#include "tstr.h"

namespace _ {

/* A door that connects two Chinese rooms.
A door can lead to one or more Rooms. A Door that can
be locked, in which case all of the Rooms behind this door are locked
out. When a door is locked, no messages are processed or sent to or
from the door and its subsidiary agents.

Rooms can be connected by one or more Portal. An example of a
system with one Door and multiple Portals is a WiFi plus USB/Serial
connection. This is a commonly used configuration for debugging the system.

Multiple doors also might share the same Portal. An example of this is a
connection to multiple systems over a WiFi connection.

@code

+=============+
|    slots    |
|=============|
| Door struct |
+=============+

@endcode
*/
template <SI4 kDoorCount_, SI4 kSlotSizeDefault_>
class TDoor : public Operand {
 public:
  enum {
    kDoorCount = kDoorCount_,              //< Initial (or static) Door count.
    kSlotSizeDefault = kSlotSizeDefault_,  //< Default.
  };

  typedef enum Errors {
    kErrorInvalidOp = 0,   //< Error code for invalid operation.
    kErrorImplementation,  //< Error code for an unkown implementation error.
  } Error;

  enum {
    kMinDoorSize = 128,  //< The min and default size of the door socket.
  };

  /* A door in a Chinese room. */
  TDoor(const CH1* roomName = nullptr, UIW* socket = nullptr,
        UIW size_bytes = kMinDoorSize) {
    if (!socket) {
      if (size_bytes < kMinDoorSize) {
        size_bytes = kMinDoorSize;
      }
    } else {
      if (size_bytes < kMinDoorSize) {
        // @todo insert error code here
        PRINTF("\nError: Door size_bytes < kMinDoorSize!");
        return;
      }
    }
    // tx.SetBuffer (adjacentDoor->Rx ()->EndAddress () + 1), aSlotSize);
    // rx = new SerialSlot (tx.EndAddress (), aSlot, aSlotSize,
    //  aTalkbackSize);
  }

  /* AsciiFactory. */
  virtual ~TDoor() {
    if (begin) delete[] begin;
  }

  /* Gets the BOut at the given index. */
  BOut* GetSlot(SIN index) { return slots_->Element(index); }

  /* Address the given crabs to the Door. */
  SIN AddSlot(SIN slot) { return TStackPush<SIN, SIN, SIN>(slots_, slot); }

  /* Attempts to find a Slot or Door with the given address. */
  BOL Contains(void* address) {
    return TStackContains<SIN, SIN, SIN>(slots_, address);
  }

  /* Gets the Slot that contains the given address.
  @return Returns the doors_ stack count if the Door does not contain the given
  address. */
  SIN FindSlot(void* address) {
    SIN count = slots_->count;
    for (SIN i = 0; i < count; ++i) {
      // Slot* slot = nullptr; //< @todo fix me!

      if (TStackContains<SIN, SIN, SIN>(slots_, address)) return i;
    }
    return count;
  }

  BIn* Slot(SI4 index) {
    if (!slots_.InBounds(index)) return nullptr;
    return slots[i];
  }

  /* Executes all of the queued escape sequences.
  @return Nil upon success or an Error Op upon failure. */
  const Op* Exec(CCrabs* crabs) {
    TArray<SI4, SI4, SI4>* slots = slots_;
    SI4 scan_count_max = scan_count_max_;
    for (SI4 i = 0; i < slots->Count(); ++i) {
      BIn* bin = Slot(i);
      for (SI4 count = scan_count_max; count > 0; --count) {
        SI4 value = BInNextByte(bin);
        if (value < 0) break;
        const Op* result = crabs->Scan(value);
      }
    }
    return nullptr;
  }

  /* Script2 operations. */
  virtual const Op* Star(CHW index, CCrabs* crabs) {
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
      return CrabsQuery(crabs, kThis);
    }
    index -= ' ';
    if (((SIN)index) >= slots_->count) {
      return DoorResult(this, Door::kErrorInvalidOp);
    }
    return nullptr;
  }

 private:
  SI4 size_bytes_,                //< Door size in bytes.
      scan_count_max_;            //< Max bytes to pull throught the slot.
  UIW* begin_;                    //< Pointer to dynamic socket.
  TArray<SI4, SI4, SI4>* slots_;  //< Slots in the door.
  CBIn* OffsetToBIn(SI4 offset) {
    return reinterpret_cast<CBIn*>(reinterpret_cast<UIW>(this) + offset);
  }
};

/* Initializes a Door at the beginning of the given socket.
static Door* DoorInit (int* socket, SI4 slot_size) {
  if (socket == nullptr) return nullptr;
  if (slot_size < kMinSlotSize) return nullptr;
  Wall* wall = reinterpret_cast<Door*>(socket);
  w->is_dynamic = 0;
  w->num_doors = 0;
  w->max_num_doors;
  w->door_one = nullptr;
}*/

}  // namespace _
#endif  //< #if SEAM >= _0_0_0__15
#endif  //< SCRIPT2_DOOR
