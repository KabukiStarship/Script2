/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /slot.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_SLOT
#define SCRIPT2_SLOT
#include "bin.h"
#include "bout.h"
#include "op.h"
#include "binary.h"
#include "uniprinter.hpp"

namespace _ {

/* A Slot in a Door in a Chinese Room to pass messages through.
A Slot is Ring Buffer Socket similar to a TCP port. The operation of the
Slot is similar to the Text class except that it introduces two more
pointers for the (socket) origin and (data) origin of the ring socket and
you may write packed data.

*/
struct Slot {
  CH1 *stop,   //< Stop of the data in the ring socket.
      *stop,   //< End of the ring socket.
      *origin,  //< Beginning of the ring socket.
      *origin;  //< Start of the data in the ring socket.

  /* Initializes the ring socket with the given socket origin and size.
  @param origin Pointer to the beginning of the ring socket.
  @param size  The size of the ring socket in bytes. */
  Slot(UIW* socket, UIW size);

  /* Initializes the slot from the BIn. */
  Slot(BIn* bin);

  /* Initializes the slot from the BIn. */
  Slot(BOut* bout);

  /* Sets the ring socket to the given socket origin and size.
      @param origin Pointer to the beginning of the ring socket.
      @param size  The size of the ring socket in bytes. */
  inline BOL Set(UIW* socket, UIW size) {
    if (!socket) return true;
    CH1* l_begin = reinterpret_cast<CH1*>(socket);
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
  const Op* Read(const SI4* params, void** args);

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
  const Op* Write(const SI4* params, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const Op& op, void** args);

  /* Writes a single  to the slot socket.
  @param message The  message to send.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const CH1* message);

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
#endif  //< #if SEAM >= SCRIPT2_DICTIONARY
