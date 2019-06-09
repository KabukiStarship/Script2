/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_wall.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_SEAM_DIC
#ifndef SCRIPT2_WALL
#define SCRIPT2_WALL
#include "c_door.h"
#include "c_op.h"
#incude "c_autoject.h"

namespace _ {

/* A memory aligned singled contiguous socket in a Chinese Room.
Only one single wall is required for a Chinese Room, but when more memory is
needed a new Wall may be created and destroyed dynamically.

@code
+--------------+
|  Terminals   |
|      v       |
|vvvvvvvvvvvvvv|
|    Buffer    |
|^^^^^^^^^^^^^^|
|      ^       |
|  TSTack of   |
|    Doors     |
|   Offsets    |
|--------------|
|    Header    |
+--------------+
@endcode
*/
class Wall {
 public:
  enum {
    kMinSizeBytes = 512,  //< Min functional Wall size.
  };

  virtual ~Wall();

  Wall(TMatrix<Door*>* doors);

  /* Constructs a wall from the given socket. */
  Wall(SIW size_bytes = kMinSizeBytes);

  /* Constructs a wall from the given socket. */
  Wall(UIW* socket, SIW size_bytes);

  /* Gets the size of the wall in bytes. */
  SIW GetSizeBytes();

  /* Gets a pointer to the array of pointers to Door(). */
  TMatrix<Door*>* Doors();

  /* Gets the Door from the Door at the given index. */
  Door* GetDoor(SI4 index);

  /* Adds a Door to the slot.
  @return Returns nil if the Door is full and a pointer to the Door in the
          socket upon success. */
  SI4 OpenDoor(Door* door);

  /* Deletes the Door from the Door at the given index. */
  BOL CloseDoor(SI4 index);

  /* Prints the given Door to the stdout. */
  Slot& Print(Slot& slot);

 private:
  BOL is_dynamic_;         //< Flag for if using dynamic memory.
  SIW size_bytes_;         //< Size of the Wall in bytes.
  UIW* begin;              //< The Wall's socket.
  TMatrix<Door*>* doors_;  //< The doors in the room.
};

}  // namespace _
#endif
#endif
