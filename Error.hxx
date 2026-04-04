// Copyright AStarship <https://astarship.net>.
#include "Error.hpp"
#if SEAM >= CRABS_STACK
namespace _ {
const CHA* ASCIIErrorSTA() {
  return TAErrors<CHA>();
}

const CHA* ASCIIErrorSTA(ISW error) {
  error = error < 0 ? -error : error;
  if (error > AErrorTotal) error = AErrorTotal;
  return &TAErrors<CHA>()[error * 32];
}

BOL AIsError(const void* result) {
  return TDelta<IUW>(result) < AErrorTotal;
}

}  //< namespace _
#endif
