// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_FLOOR_DECL
#define SCRIPT2_FLOOR_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_ROOM
namespace _ {

/* Cache-aligned group of global system variables.
The Floor is the Floor in the Chinese Room. In Kabuki Crabs, the floor is
designed to store variables without having to include the classes the variable
controls. For this reason only Strings and POD types are in the Floor. */
struct LIB_MEMBER Floor {
  ISB epoch;
};

/* Returns the the global Floor. */
LIB_MEMBER inline Floor* Global();

}  //< namespace _

#endif
#endif
