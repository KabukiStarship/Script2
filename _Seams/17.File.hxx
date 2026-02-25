// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_FILE
#include "../File.h"
#if SEAM == CRABS_FILE
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Crabs {

static const CHA* File(const CHA* args) {
#if SEAM == CRABS_FILE
  A_TEST_BEGIN;
#endif
  return NILP;
}

}  //< namespace Crabs
