// Copyright Kabuki Starship� <kabukistarship.com>.
#include "Floor.h"
#if SEAM >= SCRIPT2_ROOM
#include "Binary.hpp"
namespace _ {

CHA FloorInit(IUW* socket) { return 0; }

Floor* FloorInit(Floor* floor) {
  floor->epoch = AClockEpochInit;
  return floor;
}

inline Floor* Global() {
  static TBUF<AFloorSize, IUA, ISA> floor_socket;
  return floor_socket.Start<Floor>();
}

}  //< namespace _
#endif
