// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_FILE
#include "../File.h"
#if SEAM == SCRIPT2_FILE
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif
using namespace _;
namespace Script2 {

static const CHA* File(const CHA* args) {
#if SEAM == SCRIPT2_FILE
  A_TEST_BEGIN;
#endif
  return nullptr;
}

}  //< namespace Script2
