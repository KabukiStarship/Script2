/* Script
@version 0.x
@file    /script2/wall.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_14
#ifndef SCRIPT2_WALL
#define SCRIPT2_WALL
#include "door.h"
#include "c_op.h"

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

  Wall(TCArray<Door*>* doors);

  /* Constructs a wall from the given socket. */
  Wall(SIW size_bytes = kMinSizeBytes);

  /* Constructs a wall from the given socket. */
  Wall(UIW* socket, SIW size_bytes);

  /* Gets the size of the wall in bytes. */
  SIW GetSizeBytes();

  /* Gets a pointer to the array of pointers to Door(). */
  TCArray<Door*>* Doors();

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
  SIW size_bytes_;      //< Size of the Wall in bytes.
  UIW* begin;              //< The Wall's socket.
  TCArray<Door*>* doors_;  //< The doors in the room.
};

}  // namespace _
#endif  //< SCRIPT2_WALL
#endif  //< #if SEAM >= SCRIPT2_14
