// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BOOFER_DECL
#define CRABS_BOOFER_DECL 1
#include <_Config.h>
#if SEAM >= CRABS_ROOM
namespace _ {

/* Creates/Gets a static socket of the specified size. */
template<ISW BooferSize = BooferSizeDefault>
inline CHA* Boofer() {
  enum {
    BooferSizeWords =
        (BooferSize / sizeof(IUW)) + BooferSize % sizeof(IUW) ? 1 : 0
  };
  static IUW socket[BooferSizeWords];
  return TPtr<CHA>(socket);
}

}  //< namespace _
#endif
#endif
