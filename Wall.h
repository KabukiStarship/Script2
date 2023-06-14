/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Wall.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_WALL_HEADER
#define SCRIPT2_WALL_HEADER
#undef  TARGS
#define TARGS
#undef  TPARAMS
#define TPARAMS

#if SEAM == SCRIPT2_CRABS
#include "_Release.inl"
#else
#include "_Release.inl"
#endif

#include "Door.hpp"
#include "Operand.h"

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
|  TStack of   |
|    Doors     |
|   Offsets    |
|--------------|
|    Header    |
+--------------+
@endcode */
class Wall : public Operand {
 public:
  enum {
    cMinSizeBytes = 512,  //< Min functional Wall size.
  };

  virtual ~Wall() {
    if (is_dynamic_) {
      CHA* socket = TPtr<CHA>(doors_);
      delete[] socket;
    }
  }

  Wall(TMap<Door*>* doors);

  /* Constructs a wall from the given socket. */
  Wall(ISW size_bytes = cMinSizeBytes) : is_dynamic_(true) {
    size_bytes = size_bytes < cMinSizeBytes ? (ISC)cMinSizeBytes : size_bytes;
    size_bytes = TAlignUpUnsigned<ISD, ISW>(size_bytes);
    ISW size_words = (size_bytes >> sizeof(void*)) + 3;
    IUW *socket = new IUW[size_words],
        *aligned_buffer = AlignUpPointer8<IUW>(socket);
    //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
    //< on 16 and 32-bit systems.
    size_bytes -= sizeof(IUW) * (aligned_buffer - socket);
    origin = socket;
    doors_ = TPtr<TMatrix<Door*>>(aligned_buffer);
    TStackInit(socket, size_bytes >> sizeof(IUW));
  }

  /* Constructs a wall from the given socket. */
  Wall(IUW* socket, ISW size_bytes) {
    // CHA* ptr     = TPtr<CHA> (socket);//,
    //    * new_ptr = ptr + AlignOffset<IUD> (ptr),
    //    * end_ptr = ptr + size_bytes;
    enum {
      cBitsShift = sizeof(IUW) == 2 ? 1 : sizeof(IUW) == 2 ? 2 : 3,
    };
    // ISC size_words = (size_bytes >> kBitsShift) + 3;
    //< Computer engineering voodoo for aligning to 64-bit boundary.

    IUW* aligned_buffer = AlignUpPointer8<IUW>(socket);
    //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
    //< on 16 and 32-bit systems.
    size_bytes -= sizeof(IUW) * (aligned_buffer - socket);
    origin = socket;
    doors_ = TPtr<TMatrix<Door*>>(aligned_buffer);
    TStackInit(socket, size_bytes >> sizeof(IUW));
  }

  /* Gets the size of the wall in bytes. */
  ISW GetSizeBytes() {
    return size_bytes_;

    /* Gets a pointer to the array of pointers to Door(). */
    TMatrix<Door*>* Doors();

    /* Gets the Door from the Door at the given index. */
    Door* GetDoor(ISN index) { return 0; }

    /* Adds a Door to the slot.
    @return Returns nil if the Door is full and a pointer to the Door in the
            socket upon success. */
    ISC OpenDoor(Door * door) { return 0; }

    /* Deletes the Door from the Door at the given index. */
    BOL CloseDoor(ISN index) { return false; }

    /* Prints the given Door to the stream. */
    template <typename Printer>
    Printer& PrintTo(Printer & o) {
      return o;
    }

   private:
    BOL is_dynamic_;        //< Flag for if using dynamic memory.
    ISW size_bytes_;        //< Size of the Wall in bytes.
    IUW* origin;            //< The Wall's socket.
    TStack<Door*>* doors_;  //< The doors in the room.
  };

}  //< namespace _
#endif
#endif
