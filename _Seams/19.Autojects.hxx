// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_AUTOJECTS
#include "../Room.hpp"
#if SEAM == SCRIPT2_AUTOJECTS
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif
using namespace _;
namespace Script2 {

static const CHA* Autojects(const CHA* args) {
#if SEAM == SCRIPT2_AUTOJECTS
  A_TEST_BEGIN;
#endif
  return nullptr;
}

}  //< namespace Script2
