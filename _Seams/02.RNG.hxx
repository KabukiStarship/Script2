// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_RNG
#include "../RNG.h"
#if SEAM == SCRIPT2_RNG
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif
using namespace _;
namespace Script2 {

static const CHA* RNG(const CHA* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_RNG
  enum { cPrintCount = 256 };
#else
  enum { cPrintCount = 1 };
#endif

  for (ISN i = 0; i < cPrintCount; ++i)
    D_COUT('\n' << i << ".) " << Random(TSignedMin<ISN>(), TSignedMax<ISN>()));

#endif
  return nullptr;
}
}  //< namespace Script2
