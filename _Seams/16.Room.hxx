// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_ROOM
#include "../Room.hpp"
#if SEAM == CRABS_ROOM
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace CRTest {

static const CHA* Room(const CHA* args) {
#if SEAM == CRABS_ROOM
  A_TEST_BEGIN;
  //TRoom<> room_a, //
  //        room_b;
#endif
  return NILP;
}

}  //< namespace CRTest
