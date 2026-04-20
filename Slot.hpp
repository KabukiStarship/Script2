// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_SLOT_HPP
#define CRABS_SLOT_HPP
#include "Slot.h"
#if SEAM >= CRABS_OP
namespace _ {


/* @defgroup Slot
@brief Slot utilities for ring sockets.
*/

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
  T delta = T(stop - start);
  if (start < stop)
    return T(size - delta);
  return T(start + size - stop);
}
// @} Slot
}  //< namespace _

#endif
#endif
