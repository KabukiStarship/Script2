/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Slot.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#ifndef SCRIPT2_SLOT
#define SCRIPT2_SLOT
#include "bin.hpp"
#include "Binary.hpp"
#include "BOut.h"
#include "Op.h"
#include "Uniprinter.hpp"

namespace _ {

/* A Slot in a Door in a Chinese Room to pass messages through.
A Slot is Ring Buffer Socket similar to a TCP port. The operation of the
Slot is similar to the Text class except that it introduces two more
pointers for the (socket) origin and (data) origin of the ring socket and
you may write packed data.

*/
struct Slot {
  CHA *stop,    //< Stop of the data in the ring socket.
      *stop,    //< End of the ring socket.
      *origin,  //< Beginning of the ring socket.
      *origin;  //< Start of the data in the ring socket.

  /* Initializes the ring socket with the given socket origin and size.
  @param origin Pointer to the beginning of the ring socket.
  @param size  The size of the ring socket in bytes. */
  Slot(IUW* socket, IUW size);

  /* Initializes the slot from the BIn. */
  Slot(BIn* bin);

  /* Initializes the slot from the BIn. */
  Slot(BOut* bout);

  /* Sets the ring socket to the given socket origin and size.
      @param origin Pointer to the beginning of the ring socket.
      @param size  The size of the ring socket in bytes. */
  inline BOL Set(IUW* socket, IUW size) {
    if (!socket) return true;
    CHA* l_begin = reinterpret_cast<CHA*>(socket);
    origin = origin = stop = l_begin;
    stop = l_begin + size;
    return false;
  }

  /* Checks if this slot contains the given address.
  @return Returns inputed address if this Slot contains the given address
          and nil else wise. */
  void* Contains(void* address);

  /* Clears the socket without zeroing it out. */
  inline void Clear() { origin = stop = origin; }

  /* Zeros out the Slot. */
  void Wipe();

  /* Checks if there is space in the socket.
  @return True if the socket has space. */
  BOL IsWritable();

  /* Checks if there is data in the socket.
      @return True if the socket has data. */
  BOL IsReadable();

  /* Reads the given Operation input parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Read(const ISC* params, void** args);

  /* Reads the given Operation input parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Read(const Op& op, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const ISC* params, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const Op& op, void** args);

  /* Writes a single  to the slot socket.
  @param message The  message to send.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const CHA* message);

  /* Copies the contents of the other slot into the slot. */
  const Op* Write(Slot& other);

#if USING_SCRIPT2_TEXT
  /* Prints a  rep of this object to the printer. */
  UTF1& Print(UTF1& printer);
#endif
};

}  // namespace _

#if USING_SCRIPT2_TEXT
/* Prints out the bin to the text. */
inline _::UTF1& operator<<(_::UTF1& printer, _::Slot& slot) {
  return slot.Print(printer);
}
#endif

#endif  //< SCRIPT2_SLOT
#endif  //< #if SEAM >= SCRIPT2_DIC
