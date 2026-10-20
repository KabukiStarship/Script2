// Copyright AStarship <https://astarship.net>.
#if SEAM >= CRABS_RANDOM
#include "../Random.h"
#if SEAM == CRABS_RANDOM
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace CRTest {

static const CHA* RNG(const CHA* args) {
#if SEAM >= CRABS_RANDOM
  A_TEST_BEGIN;

#if SEAM == CRABS_RANDOM
  enum { PrintCount = 256 };
#else
  enum { PrintCount = 1 };
#endif

  for (ISN i = 0; i < PrintCount; ++i)
    D_COUT('\n' << i << ".) " << Random(TISMin<ISN>(), TISMax<ISN>()));

#endif
  return NILP;
}
}  //< namespace CRTest
