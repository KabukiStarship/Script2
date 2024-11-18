// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_EXCEPTIONS_DECL
#define SCRIPT2_EXCEPTIONS_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#if USING_SCRIPT2_INTERRUPTS == YES_0
namespace _ {

#if USING_TEXT_SCRIPT == YES_0
/* Exception thrown to interrupt and crash the program. */
struct LIB_MEMBER RoomCrashException : public std::exception {
  RoomCrashException() {}
};
#endif  //< USING_SCRIPT2_INTERRUPTS == YES_0
}  //< namespace _
#endif
#endif
#endif
