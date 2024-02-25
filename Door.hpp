/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Door.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_DOOR
#define SCRIPT2_DOOR
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Crabs.h"
#include "Slot.h"
#include "Stack.hpp"
#include "String.hpp"
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
template<ISC cDoorCount_, ISC cSlotSizeDefault_>
class TDoor : public Operand {
 public:
  enum {
    cDoorCount = cDoorCount_,              //< Initial (or static) Door count.
    cSlotSizeDefault = cSlotSizeDefault_,  //< Default.
  };

  typedef enum Errors {
    cErrorInvalidOp = 0,   //< Error code for invalid operation.
    cErrorImplementation,  //< Error code for an unkown implementation error.
  } Error;

  enum {
    cMinDoorSize = 128,  //< The min and default size of the door socket.
  };

  /* A door in a Chinese room. */
  TDoor(const CHA* roomName = nullptr, IUW* socket = nullptr,
        IUW size_bytes = cMinDoorSize) {
    if (!socket) {
      if (size_bytes < cMinDoorSize) {
        size_bytes = cMinDoorSize;
      }
    } else {
      if (size_bytes < kMinDoorSize) {
        // @todo insert error code here
        D_COUT("\nError: Door size_bytes < kMinDoorSize!");
        return;
      }
    }
    // tx.SetBuffer (adjacentDoor->Rx ()->EndAddress () + 1), aSlotSize);
    // rx = new SerialSlot (tx.EndAddress (), aSlot, aSlotSize,
    //  aTalkbaccSize);
  }

  /* RAMFactory. */
  virtual ~TDoor() {
    if (origin) delete[] origin;
  }

  /* Gets the BOut at the given index. */
  BOut* GetSlot(ISC index) { return slots_->Element(index); }

  /* Address the given crabs to the Door. */
  ISC AddSlot(ISC slot) { return TStackInsert<ISC, ISC, ISC>(slots_, slot); }

  /* Attempts to find a Slot or Door with the given address. */
  BOL Contains(void* address) {
    return TStackContains<ISC, ISC, ISC>(slots_, address);
  }

  /* Gets the Slot that contains the given address.
  @return Returns the doors_ stack count if the Door does not contain the given
  address. */
  ISC FindSlot(void* address) {
    ISC count = slots_->count;
    for (ISC i = 0; i < count; ++i) {
      // Slot* slot = nullptr; //< @todo fix me!

      if (TStackContains<ISC, ISC, ISC>(slots_, address)) return i;
    }
    return count;
  }

  BIn* Slot(ISC index) {
    if (!slots_.InBounds(index)) return nullptr;
    return slots[i];
  }

  /* Executes all of the queued escape sequences.
  @return Nil upon success or an Error Op upon failure. */
  const Op* Exec(Crabs* crabs) {
    TMatrix<ISC, ISC, ISC>* slots = slots_;
    ISC scan_count_max = scan_count_max_;
    for (ISC i = 0; i < slots->Count(); ++i) {
      BIn* bin = Slot(i);
      for (ISC count = scan_count_max; count > 0; --count) {
        ISC value = BInNextByte(bin);
        if (value < 0) break;
        const Op* result = crabs->SScan(value);
      }
    }
    return nullptr;
  }

  /* Script2 operations. */
  virtual const Op* Star(CHC index, Crabs* crabs) {
    static const Op cThis = {
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
      nullptr
    };
    if (index == '?') {
      return CrabsQuery(crabs, cThis);
    }
    index -= ' ';
    if (((ISC)index) >= slots_->count) {
      return DoorResult(this, Door::c_ErrorInvalidOp);
    }
    return nullptr;
  }

 private:
  ISC size_bytes_,                 //< Door size in bytes.
      scan_count_max_;             //< Max bytes to pull throught the slot.
  IUW* begin_;                     //< Pointer to dynamic socket.
  TMatrix<ISC, ISC, ISC>* slots_;  //< Slots in the door.
  CBIn* OffsetToBIn(ISC offset) {
    return TPtr<CBIn>(IUW(this) + offset);
  }
};

/* Initializes a Door at the beginning of the given socket.
static Door* DoorInit (ISC* socket, ISC slot_size) {
  if (socket == nullptr) return nullptr;
  if (slot_size < kMinSlotSize) return nullptr;
  Wall* wall = TPtr<Door>(socket);
  w->is_dynamic = 0;
  w->num_doors = 0;
  w->max_num_doors;
  w->door_one = nullptr;
}*/

}  //< namespace _
#endif
#endif
