// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_RELEASE
#if SEAM == SCRIPT2_RELEASE
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
#endif
namespace Script2 {

inline const CHA* Release(const CHA* args) {
#if SEAM == SCRIPT2_RELEASE
#endif
  return nullptr;
}

}  //< namespace Script2
