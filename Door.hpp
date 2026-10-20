// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_DOOR_DECL
#define CRABS_DOOR_DECL
#include <_Config.h>
#if SEAM >= CRABS_ROOM
#include "Crabs.h"
#include "BIn.h"
#include "Slot.h"
#include "Stack.hpp"
#include "String.hpp"
#include "AType.hpp"
/* @defgroup Door
Chinese Room Door
A portal between two Chinese Rooms. Contains a stack of Slot
(TBIn/TBOut) pairs that exchange type-tagged messages over
lock-free SPSC rings. A Mirror is a Door variant that leads
back to the same system.
@{ */

namespace _ {

enum {
  DoorBytesMin = 128,  //< Min functional Door size.
};

/* A door in a Chinese room. */
template<DOR_P>
TDoor<DOR_A>* TDoorInit(TDoor<DOR_A>* door, const CHA* roomName = NILP, IUW* socket = NILP,
      IUW bytes = DoorBytesMin) {
  if (IsError(socket)) {
    if (bytes < DoorBytesMin) {
      bytes = DoorBytesMin;
    }
  } else {
    if (bytes < DoorBytesMin) {
      // @todo insert error code here
      D_COUT("\nError: Door bytes < DoorBytesMin!");
      return NILP;
    }
  }
  // tx.SetBoofer (adjacentDoor->Rx ()->EndAddress () + 1), aSlotSize);
  // rx = new SerialSlot (tx.EndAddress (), aSlot, aSlotSize,
  //  aTalkbackSize);
  return door;
}

/* Gets the TBOut at the given index. */
template<DOR_P>
TBOut<ISC>* TDoorGetSlot(TDoor<DOR_A>* door, ISZ index) { return door->slots_->Element(index); }

/* Address the given crabs to the Door. */
template<DOR_P>
ISZ TDoorAddSlot(TDoor<DOR_A>* door, ISZ slot) {
  return TStackInsert<ISZ, ISZ, ISZ>(door->slots_, slot);
}

/* Attempts to find a Slot or Door with the given address. */
template<DOR_P>
BOL TDoorContains(TDoor<DOR_A>* door, void* address) {
  return TStackContains<ISZ, ISZ, ISZ>(door->slots_, address);
}

/* Gets the Slot that contains the given address.
@return Returns the doors_ stack count if the Door does not contain the given
address. */
template<DOR_P>
ISZ TDoorFindSlot(TDoor<DOR_A>* door, void* address) {
  ISZ count = door->slots_->count;
  for (ISZ i = 0; i < count; ++i) {
    // Slot* slot = NILP; //< @todo fix me!

    if (TStackContains<ISZ, ISZ, ISZ>(door->slots_, address)) return i;
  }
  return count;
}

template<DOR_P>
TBIn<ISC>* TDoorSlotNumber(TDoor<DOR_A>* door, ISZ index) {
  if (!door->slots_->InBounds(index)) return NILP;
  return TPtr<TBIn<ISC>>(&door->slots_->Element(index));
}

/* Executes all of the queued escape sequences.
@return Nil upon success or an Error Op upon failure. */
template<DOR_P>
const Op* TDoorExec(TDoor<DOR_A>* door, Crabs* crabs) {
  TStack<Slot, ISZ, ISZ>* slots = door->slots_;
  ISZ scan_total = door->scan_total_;
  for (ISZ i = 0; i < slots->count; ++i) {
    Slot* slot = slots->Element(i);
    TBIn<ISC>* bin = TPtr<TBIn<ISC>>(slot);
    for (ISZ count = scan_total; count > 0; --count) {
      ISN value = BInStreamByte(bin);
      if (value < 0) break;
      //const Op* result = crabs->SScan(value);
    }
  }
  return NILP;
}

/* Crabs operations.
template<DOR_P>
const Op* TDoorStar(CHC index, Crabs* crabs) {
  static const Op This = {
    "Door",
    OpFirst('A'),
    OpFirst(ASizeCodef(door->slots_->count)),
    "A door in a Chinese room with a bunch of slots in it where "
    "messages are passed.",
    '}',
    ';',
    ' ',
    false,
    NILP,
    NILP
  };
  if (index == '?') {
    return CrabsQuery(crabs, This, 0);
  }
  index -= ' ';
  if (ISZ(index) >= slots_->count) {
    //return DoorResult(this, Door::ErrorInvalidOp);
    return NILP;
  }
  return NILP;
} */

template<DOR_P>
TBIn<ISC>* TDoorOffsetToBIn(TDoor<DOR_A>* door, ISZ offset) {
  return TPtr<TBIn<ISC>>(IUW(door) + offset);
}

}  //< namespace _

/* @} */  // End of Door group.
#endif
#endif
