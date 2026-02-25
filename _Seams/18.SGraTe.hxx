// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_SGRATE
#include "../Room.hpp"
#if SEAM == CRABS_SGRATE
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Crabs {

/* Seam contains test functions for the rest of the Autojects. */
static const CHA* SGraTe(const CHA* args) {
#if SEAM == CRABS_STACK
  A_TEST_BEGIN;
#endif
  return NILP;
}

}  //< namespace Crabs
