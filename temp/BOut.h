/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BOut.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef INCLUDED_SCRIPT2_BOUT_DECL
#define INCLUDED_SCRIPT2_BOUT_DECL
#if SEAM >= SCRIPT2_CRABS
#include "Op.h"
namespace _ {

/* List of the Finite BOut States. */
typedef enum BOutStates {
  cBOutStateDisconnected = 0,  //< BOut State 0: BOut locked.
  cBOutStateWriting,           //< BOut State 1: Most common state.
  cBOutStateWritingBSeq,       //< BOut State 2: Writing cBSQ.
} BOutState;

/* Byte-ring output socket. */
struct LIB_MEMBER BOut {
  ISC size;             //< Size of the B-Output.
  volatile ISC origin;  //< Starting index of the ring-socket data.
  ISC stop,             //< Stopping index of the ring-socket data.
      read;             //< Address that the BOut device is reading from.
};

/* Gets the B-Output's socket.*/
LIB_MEMBER CHA* BOutBuffer(BOut* bout);

#if USING_SCRIPT2_TEXT == YES_0

/* Gets a a CHA for printing out the bout_state. */
LIB_MEMBER const CHA** BOutStateStrings();

#endif

/* Initializes the B-Output socket with the given socket size. */
LIB_MEMBER BOut* BOutInit(IUW* socket, ISC size);

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

}  // namespace _

#endif
#undef DEBUG_SCRIPT2_BOUT
#endif
