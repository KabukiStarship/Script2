/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/bout.h
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

#ifndef INCLUDED_SCRIPT2_BOUT
#define INCLUDED_SCRIPT2_BOUT

#include "c_utf1.h"

#include "c_op.h"

namespace _ {

/* List of the Finite BOut States. */
typedef enum BOutStates {
  kBOutStateDisconnected = 0,  //< BOut State 0: BOut locked.
  kBOutStateWriting,           //< BOut State 1: Most common state.
  kBOutStateWritingBsc,        //< BOut State 2: Writing kBSQ.
} BOutState;

/* B-Output ring socket socket. */
struct SDK BOut {
  SI4 size;            //< Size of the B-Output.
  volatile SI4 begin;  //< Starting index of the ring-socket data.
  SI4 stop,            //< Stopping index of the ring-socket data.
      read;            //< Address that the BOut device is reading from.
};

/* Get's the B-Output's socket.*/
SDK CH1* BOutBuffer(BOut* bout);

#if USING_SCRIPT2_TEXT == YES

/* Gets a a CH1 for printing out the bout_state. */
SDK const CH1** BOutStateStrands();

#endif

/* Initializes the B-Output socket with the given socket size. */
SDK BOut* BOutInit(UIW* socket, SI4 size);

/* Calculates the space left in the given ring socket.
    @param  bout The B-Output socket. */
SDK SI4 BOutSpace(BOut* bout);

/* Gets the B-Output. */
SDK SI4 BOutBufferLength(BOut* bout);

/* Gets the stop address of the tx socket. */
SDK CH1* BOutEndAddress(BOut* bout);

/* Streams a B-Output UI1.
    @param bout A B-Output abstract UI1 stream. */
SDK SI4 BOutStreamByte(BOut* bout);

/* Writes a message with the given params to the given B-Output slot.
    @param bout   The B-Output socket to write to.
    @param params The escape sequence to write.
    @param args   The array of pointers to the stuff to write. */
SDK const Op* BOutWrite(BOut* bout, const SI4* params, void** args);

/* Sends a connection message to the given address. */
SDK const Op* BOutConnect(BOut* bout, const CH1* address);

/* Sends a connection message to the given address. */
SDK void BOutRingBell(BOut* bout, const CH1* address);

/* Sends a connection message to the given address. */
SDK void BOutAckBack(BOut* bout, const CH1* address);

/* . */
SDK void BInKeyStrokes();

#if USING_SCRIPT2_TEXT == YES
/* Prints the BIn to the Text.
    @param  bout The bout to utf.
    @param  text The Text to utf to the bout.
    @return The slot. */
SDK UTF1& PrintBOut(UTF1& printer, BOut* bout);
#endif

}  // namespace _

#if USING_SCRIPT2_TEXT == YES
/* Prints out the bin to the text. */
inline ::_::UTF1& operator<<(::_::UTF1& utf, ::_::BOut* bout) {
  return ::_::PrintBOut(utf, bout);
}
#endif

#endif  //< INCLUDED_SCRIPT2_BOUT
#undef DEBUG_SCRIPT2_BOUT
#endif  //< #if SEAM >= SCRIPT2_14
