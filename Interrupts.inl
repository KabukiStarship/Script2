// Copyright Kabuki Starship� <kabukistarship.com>.
#include "Interrupts.h"
#if SEAM >= SCRIPT2_CRABS && USING_SCRIPT2_INTERRUPTS
#include <cassert>
namespace _ {

#if USING_SCRIPT2_TEXT
const CHA* RoomCrashException::what() const throw() { return "External crash"; }
#endif

}  //< namespace _
#endif  ///< #if SEAM >= SCRIPT2_CRABS
