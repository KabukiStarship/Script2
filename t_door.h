/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_door.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SEAM_SCRIPT2_EXPR
#ifndef SCRIPT2_DOOR
#define SCRIPT2_DOOR
#include "c_crabs.h"
#include "c_slot.h"
#include "t_stack.h"
#include "t_strand.h"

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
        D_PRINTF("\nError: Door size_bytes < kMinDoorSize!");
        return;
      }
    }
    // tx.SetBuffer (adjacentDoor->Rx ()->EndAddress () + 1), aSlotSize);
    // rx = new SerialSlot (tx.EndAddress (), aSlot, aSlotSize,
    //  aTalkbackSize);
  }

  /* RamFactory. */
  virtual ~TDoor() {
    if (begin) delete[] begin;
  }

  /* Gets the BOut at the given index. */
  BOut* GetSlot(SI4 index) { return slots_->Element(index); }

  /* Address the given crabs to the Door. */
  SI4 AddSlot(SI4 slot) { return TStackPush<SI4, SI4, SI4>(slots_, slot); }

  /* Attempts to find a Slot or Door with the given address. */
  BOL Contains(void* address) {
    return TStackContains<SI4, SI4, SI4>(slots_, address);
  }

  /* Gets the Slot that contains the given address.
  @return Returns the doors_ stack count if the Door does not contain the given
  address. */
  SI4 FindSlot(void* address) {
    SI4 count = slots_->count;
    for (SI4 i = 0; i < count; ++i) {
      // Slot* slot = nullptr; //< @todo fix me!

      if (TStackContains<SI4, SI4, SI4>(slots_, address)) return i;
    }
    return count;
  }

  BIn* Slot(SI4 index) {
    if (!slots_.InBounds(index)) return nullptr;
    return slots[i];
  }

  /* Executes all of the queued escape sequences.
  @return Nil upon success or an Error Op upon failure. */
  const Op* Exec(Crabs* crabs) {
    TMatrix<SI4, SI4, SI4>* slots = slots_;
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
  virtual const Op* Star(CH4 index, Crabs* crabs) {
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
    if (((SI4)index) >= slots_->count) {
      return DoorResult(this, Door::kErrorInvalidOp);
    }
    return nullptr;
  }

 private:
  SI4 size_bytes_,                //< Door size in bytes.
      scan_count_max_;            //< Max bytes to pull throught the slot.
  UIW* begin_;                    //< Pointer to dynamic socket.
  TMatrix<SI4, SI4, SI4>* slots_;  //< Slots in the door.
  CBIn* OffsetToBIn(SI4 offset) {
    return reinterpret_cast<CBIn*>(reinterpret_cast<UIW>(this) + offset);
  }
};

/* Initializes a Door at the beginning of the given socket.
static Door* DoorInit (SI4* socket, SI4 slot_size) {
  if (socket == nullptr) return nullptr;
  if (slot_size < kMinSlotSize) return nullptr;
  Wall* wall = reinterpret_cast<Door*>(socket);
  w->is_dynamic = 0;
  w->num_doors = 0;
  w->max_num_doors;
  w->door_one = nullptr;
}*/

}  // namespace _
#endif  //< #if SEAM >= SEAM_SCRIPT2_EXPR
#endif  //< SCRIPT2_DOOR
