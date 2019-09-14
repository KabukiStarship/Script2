/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /c_wall.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_WALL_HEADER
#define SCRIPT2_WALL_HEADER

#if SEAM == SCRIPT2_ROOM
#include "module_release.inl"
#else
#include "module_release.inl"
#endif

#include "c_door.h"
#include "c_op.h"

namespace _ {

/* A group of slots that all go to the same Room.
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
@endcode */
class Wall : public Operand {
 public:
  enum {
    kMinSizeBytes = 512,  //< Min functional Wall size.
  };

  virtual ~Wall() {
    if (is_dynamic_) {
      CH1* socket = reinterpret_cast<CH1*>(doors_);
      delete[] socket;
    }
  }

  Wall(TMap<Door*>* doors);

  /* Constructs a wall from the given socket. */
  Wall(SIW size_bytes = kMinSizeBytes) : is_dynamic_(true) {
    size_bytes = size_bytes < kMinSizeBytes ? (SI4)kMinSizeBytes : size_bytes;
    size_bytes = TAlignUpUnsigned<SI8, SIW>(size_bytes);
    SIW size_words = (size_bytes >> sizeof(void*)) + 3;
    UIW *socket = new UIW[size_words],
        *aligned_buffer = AlignUpPointer8<UIW>(socket);
    //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
    //< on 16 and 32-bit systems.
    size_bytes -= sizeof(UIW) * (aligned_buffer - socket);
    origin = socket;
    doors_ = reinterpret_cast<TMatrix<Door*>*>(aligned_buffer);
    TStackInit(socket, size_bytes >> sizeof(UIW));
  }

  /* Constructs a wall from the given socket. */
  Wall(UIW* socket, SIW size_bytes) {
    // CH1* ptr     = reinterpret_cast<CH1*> (socket);//,
    //    * new_ptr = ptr + AlignOffset<UI8> (ptr),
    //    * end_ptr = ptr + size_bytes;
    enum {
      kBitsShift = sizeof(UIW) == 2 ? 1 : sizeof(UIW) == 2 ? 2 : 3,
    };
    // SI4 size_words = (size_bytes >> kBitsShift) + 3;
    //< Computer engineering voodoo for aligning to 64-bit boundary.

    UIW* aligned_buffer = AlignUpPointer8<UIW>(socket);
    //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
    //< on 16 and 32-bit systems.
    size_bytes -= sizeof(UIW) * (aligned_buffer - socket);
    origin = socket;
    doors_ = reinterpret_cast<TMatrix<Door*>*>(aligned_buffer);
    TStackInit(socket, size_bytes >> sizeof(UIW));
  }

  /* Gets the size of the wall in bytes. */
  SIW GetSizeBytes() {
    return size_bytes_;

    /* Gets a pointer to the array of pointers to Door(). */
    TMatrix<Door*>* Doors();

    /* Gets the Door from the Door at the given index. */
    Door* GetDoor(SIN index) { return 0; }

    /* Adds a Door to the slot.
    @return Returns nil if the Door is full and a pointer to the Door in the
            socket upon success. */
    SI4 OpenDoor(Door * door) { return 0; }

    /* Deletes the Door from the Door at the given index. */
    BOL CloseDoor(SIN index) { return false; }

    /* Prints the given Door to the stream. */
    template <typename Printer>
    Printer& PrintTo(Printer & o) {
      return o;
    }

   private:
    BOL is_dynamic_;        //< Flag for if using dynamic memory.
    SIW size_bytes_;        //< Size of the Wall in bytes.
    UIW* origin;            //< The Wall's socket.
    TSTack<Door*>* doors_;  //< The doors in the room.
  };

}  // namespace _
#endif
#endif
