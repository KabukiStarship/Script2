// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_boofer
#define SCRIPT2_boofer
#include <_Config.h>
#if SEAM >= SCRIPT2_ROOM
namespace _ {

/* Creates/Gets a static socket of the specified size. */
template<ISW cBooferSize = cBooferSizeDefault>
inline CHA* Boofer() {
  enum {
    cBooferSizeWords =
        (cBooferSize / sizeof(IUW)) + cBooferSize % sizeof(IUW) ? 1 : 0
  };
  static IUW socket[cBooferSizeWords];
  return TPtr<CHA>(socket);
}

}  //< namespace _
#endif
#endif
