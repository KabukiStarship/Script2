/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /slot.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= _0_0_0__13
#ifndef SCRIPT2_SLOT
#define SCRIPT2_SLOT
#include "csocket.h"

#include "bin.h"
#include "bout.h"
#include "op.h"
#include "str1.h"

namespace _ {

/* A Slot in a Door in a Chinese Room to pass messages through.
A Slot is Ring Buffer Socket similar to a TCP port. The operation of the
Slot is similar to the Text class except that it introduces two more
pointers for the (socket) begin and (data) begin of the ring socket and
you may write packed data.

*/
struct Slot {
  char *stop,  //< Stop of the data in the ring socket.
      *stop,   //< End of the ring socket.
      *begin,  //< Beginning of the ring socket.
      *begin;  //< Start of the data in the ring socket.

  /* Initializes the ring socket with the given socket begin and size.
  @param begin Pointer to the beginning of the ring socket.
  @param size  The size of the ring socket in bytes. */
  Slot(UIW* socket, UIW size);

  /* Initializes the slot from the BIn. */
  Slot(BIn* bin);

  /* Initializes the slot from the BIn. */
  Slot(BOut* bout);

  /* Sets the ring socket to the given socket begin and size.
      @param begin Pointer to the beginning of the ring socket.
      @param size  The size of the ring socket in bytes. */
  inline BOL Set(UIW* socket, UIW size) {
    if (!socket) return true;
    char* l_begin = reinterpret_cast<char*>(socket);
    begin = begin = stop = l_begin;
    stop = l_begin + size;
    return false;
  }

  /* Checks if this slot contains the given address.
  @return Returns inputed address if this Slot contains the given address
          and nil else wise. */
  void* Contains(void* address);

  /* Clears the socket without zeroing it out. */
  inline void Clear() { begin = stop = begin; }

  /* Zeros out the Slot. */
  void Wipe();

  /* Checks if there is space in the socket.
  @return True if the socket has space. */
  BOL IsWritable();

  /* Checks if there is data in the socket.
      @return True if the socket has data. */
  BOL IsReadable();

  /* Reads the given Operation input parameters from the slot to the args.
  @param  slot The slot to read from.
  @param  op   The Operation to get the in from.
  @param  args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Read(const UIT* params, void** args);

  /* Reads the given Operation input parameters from the slot to the args.
  @param  slot The slot to read from.
  @param  op   The Operation to get the in from.
  @param  args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Read(const Op& op, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param  slot The slot to read from.
  @param  op   The Operation to get the in from.
  @param  args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const UIT* params, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param  slot The slot to read from.
  @param  op   The Operation to get the in from.
  @param  args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const Op& op, void** args);

  /* Writes a single string_ to the slot socket.
  @param message The string_ message to send.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const char* message);

  /* Copies the contents of the other slot into the slot. */
  const Op* Write(Slot& other);

#if USING_CRABS_TEXT
  /* Prints a string_ rep of this object to the printer. */
  UTF1& Print(UTF1& printer);
#endif
};

}  // namespace _

#if USING_CRABS_TEXT
/* Prints out the bin to the text. */
inline _::UTF1& operator<<(_::UTF1& printer, _::Slot& slot) {
  return slot.Print(printer);
}
#endif

#endif  //< SCRIPT2_SLOT
#endif  //< #if SEAM >= _0_0_0__13
