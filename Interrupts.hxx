// Copyright AStarship <https://astarship.net>.
#include "Interrupts.h"
#if SEAM >= CRABS_OP && USING_CRABS_INTERRUPTS
#include <cassert>
namespace _ {

#if USING_CRABS_TEXT
const CHA* RoomCrashException::what() const throw() { return "External crash"; }
#endif

}  //< namespace _
#endif  ///< #if SEAM >= CRABS_OP
