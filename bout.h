/* Script2 (TM) @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /bout.h
@author  Cale McCollough <https://cale-mccollough.github.io>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM >= SCRIPT2_DIC

#ifndef INCLUDED_SCRIPT2_BOUT
#define INCLUDED_SCRIPT2_BOUT

#include "op.h"

namespace _ {

/* List of the Finite BOut States. */
typedef enum BOutStates {
  cBOutStateDisconnected = 0,  //< BOut State 0: BOut locked.
  cBOutStateWriting,           //< BOut State 1: Most common state.
  cBOutStateWritingBsc,        //< BOut State 2: Writing kBSQ.
} BOutState;

/* B-Output ring socket socket. */
struct LIB_MEMBER BOut {
  ISC size;             //< Size of the B-Output.
  volatile ISC origin;  //< Starting index of the ring-socket data.
  ISC stop,             //< Stopping index of the ring-socket data.
      read;             //< Address that the BOut device is reading from.
};

/* Get's the B-Output's socket.*/
LIB_MEMBER CHA* BOutBuffer(BOut* bout);

#if USING_SCRIPT2_TEXT == YES_0

/* Gets a a CHA for printing out the bout_state. */
LIB_MEMBER const CHA** BOutStateStrands();

#endif

/* Initializes the B-Output socket with the given socket size. */
LIB_MEMBER BOut* BOutInit(UIW* socket, ISC size);

/* Calculates the space left in the given ring socket.
    @param bout The B-Output socket. */
LIB_MEMBER ISC BOutSpace(BOut* bout);

/* Gets the B-Output. */
LIB_MEMBER ISC BOutBufferLength(BOut* bout);

/* Gets the stop address of the tx socket. */
LIB_MEMBER CHA* BOutEndAddress(BOut* bout);

/* Streams a B-Output IUA.
    @param bout A B-Output abstract IUA stream. */
LIB_MEMBER ISC BOutStreamByte(BOut* bout);

/* Writes a message with the given params to the given B-Output slot.
    @param bout   The B-Output socket to write to.
    @param params The escape sequence to write.
    @param args   The array of pointers to the stuff to write. */
LIB_MEMBER const Op* BOutWrite(BOut* bout, const ISC* params, void** args);

/* Sends a connection message to the given address. */
LIB_MEMBER const Op* BOutConnect(BOut* bout, const CHA* address);

/* Sends a connection message to the given address. */
LIB_MEMBER void BOutRingBell(BOut* bout, const CHA* address);

/* Sends a connection message to the given address. */
LIB_MEMBER void BOutAckBack(BOut* bout, const CHA* address);

/* . */
LIB_MEMBER void BInKeyStrokes();

#if USING_SCRIPT2_TEXT == YES_0
/* Prints the BIn to the Text.
    @param bout The bout to utf.
    @param text The Text to utf to the bout.
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
#endif  //< #if SEAM >= SCRIPT2_DIC
