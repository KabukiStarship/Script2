/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/bout.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_DICTIONARY

#ifndef INCLUDED_SCRIPT2_BOUT
#define INCLUDED_SCRIPT2_BOUT

#include "c_op.h"

namespace _ {

/* List of the Finite BOut States. */
typedef enum BOutStates {
  kBOutStateDisconnected = 0,  //< BOut State 0: BOut locked.
  kBOutStateWriting,           //< BOut State 1: Most common state.
  kBOutStateWritingBsc,        //< BOut State 2: Writing kBSQ.
} BOutState;

/* B-Output ring socket socket. */
struct LIB_MEMBER BOut {
  SI4 size;            //< Size of the B-Output.
  volatile SI4 begin;  //< Starting index of the ring-socket data.
  SI4 stop,            //< Stopping index of the ring-socket data.
      read;            //< Address that the BOut device is reading from.
};

/* Get's the B-Output's socket.*/
LIB_MEMBER CH1* BOutBuffer(BOut* bout);

#if USING_SCRIPT2_TEXT == YES_0

/* Gets a a CH1 for printing out the bout_state. */
LIB_MEMBER const CH1** BOutStateStrands();

#endif

/* Initializes the B-Output socket with the given socket size. */
LIB_MEMBER BOut* BOutInit(UIW* socket, SI4 size);

/* Calculates the space left in the given ring socket.
    @param  bout The B-Output socket. */
LIB_MEMBER SI4 BOutSpace(BOut* bout);

/* Gets the B-Output. */
LIB_MEMBER SI4 BOutBufferLength(BOut* bout);

/* Gets the stop address of the tx socket. */
LIB_MEMBER CH1* BOutEndAddress(BOut* bout);

/* Streams a B-Output UI1.
    @param bout A B-Output abstract UI1 stream. */
LIB_MEMBER SI4 BOutStreamByte(BOut* bout);

/* Writes a message with the given params to the given B-Output slot.
    @param bout   The B-Output socket to write to.
    @param params The escape sequence to write.
    @param args   The array of pointers to the stuff to write. */
LIB_MEMBER const Op* BOutWrite(BOut* bout, const SI4* params, void** args);

/* Sends a connection message to the given address. */
LIB_MEMBER const Op* BOutConnect(BOut* bout, const CH1* address);

/* Sends a connection message to the given address. */
LIB_MEMBER void BOutRingBell(BOut* bout, const CH1* address);

/* Sends a connection message to the given address. */
LIB_MEMBER void BOutAckBack(BOut* bout, const CH1* address);

/* . */
LIB_MEMBER void BInKeyStrokes();

#if USING_SCRIPT2_TEXT == YES_0
/* Prints the BIn to the Text.
    @param  bout The bout to utf.
    @param  text The Text to utf to the bout.
    @return The slot. */
LIB_MEMBER UTF1& PrintBOut(UTF1& printer, BOut* bout);
#endif

}  // namespace _

#if USING_SCRIPT2_TEXT == YES_0
/* Prints out the bin to the text. */
inline _::UTF1& operator<<(_::UTF1& utf, _::BOut* bout) {
  return _::PrintBOut(utf, bout);
}
#endif

#endif  //< INCLUDED_SCRIPT2_BOUT
#undef DEBUG_SCRIPT2_BOUT
#endif  //< #if SEAM >= SEAM_SCRIPT2_DICTIONARY
