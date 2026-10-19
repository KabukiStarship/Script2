// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BUFFER_DECL
#define CRABS_BUFFER_DECL
#include "_Config.h"
#if SEAM >= CRABS_ROOM
namespace _ {

/* Creates/Gets a static socket of the specified size. */
template<ISW BufferSize = BufferSizeDefault>
inline CHA* Buffer() {
  enum {
    BufferSizeWords =
        (BufferSize / sizeof(IUW)) + BufferSize % sizeof(IUW) ? 1 : 0
  };
  static IUW socket[BufferSizeWords];
  return TPtr<CHA>(socket);
}

}  //< namespace _
#endif
#endif
