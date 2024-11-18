// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_SLOT_INLINE_CODE
#define SCRIPT2_SLOT_INLINE_CODE
#include "Slot.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

enum {
  SlotBytesMin = 32  //< Minimum size of a slot in bytes.
};

/* Calculates the used ring socket space.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
template<typename T>
inline T TSlotLength(IUA* origin, IUA* stop, ISW size) {
  return T(stop - origin);
}

/* Calculates the space left in the given ring socket.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
template<typename T>
inline T TSlotSpace(IUA* start, IUA* stop, ISW size) {
  return T(size - (stop - start));
}

}  //< namespace _

#endif
#endif
