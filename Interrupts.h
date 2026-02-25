// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_EXCEPTIONS_DECL
#define CRABS_EXCEPTIONS_DECL 1
#include <_Config.h>
#if SEAM >= CRABS_OPERATION
#if USING_CRABS_INTERRUPTS == YES_0
namespace _ {

#if USING_TEXT_SCRIPT == YES_0
/* Exception thrown to interrupt and crash the program. */
struct LIB_MEMBER RoomCrashException : public std::exception {
  RoomCrashException() {}
};
#endif  //< USING_CRABS_INTERRUPTS == YES_0
}  //< namespace _
#endif
#endif
#endif
