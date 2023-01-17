/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /BIn.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_BIN_DECL
#define SCRIPT2_BIN_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
#include "Op.h"
namespace _ {

/* List of BIn States.
@see SCRIPT Specification RFC. */
typedef enum BInStates {
  cBInStateAddress = 0,    //< State  0: Scanning address.
  cBInStatePackedArgs,     //< State  1: Scanning arguments.
  cBInStatePackedUTF8,     //< State  2: Scanning UTF-8.
  cBInStatePackedUTF16,    //< State  3: Scanning UTF-16.
  cBInStatePackedUTF32,    //< State  4: Scanning UTF-32.
  cBInStatePackedVarint,   //< State  5: Scanning varint.
  cBInStatePackedObj,      //< State  6: 8-bit OB1 state.
  cBInStateVerifyingHash,  //< State  7: Verifying the 32-bit hash.
  cBInStateHandlingError,  //< State  8: Handling an error state.
  cBInStateDisconnected,   //< State  9: Disconnected state.
  cBInStateAck,            //< State 10: Awaiting connection ACK.
  cBInStateLocked,         //< State 11: Locked state.
  cBInStatePackedPod,      //< State 12: Scanning plain-old-data.
} BInState;

/* B-Input ring buffer Slot.
A B-Input Slot is functionally identical to a input port in TCP. */
struct LIB_MEMBER BIn {
  ISC size,           //< The size of the socket.
      origin;         //< The starting index of the ring socket data.
  volatile ISC stop;  //< The stopping index of the ring socket data.
  ISC read;           //< The read variable to memory align the socket.
};

/* Get's the B-Input's socket. */
LIB_MEMBER inline CHA* BInBegin(BIn* bin);

LIB_MEMBER inline CHA* BInEnd(BIn* bin);

/* Calculates the used ring socket space.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
LIB_MEMBER inline ISW SlotLength(CHA* origin, CHA* stop, IUW size);

/* Calculates the space left in the given ring socket.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
LIB_MEMBER inline ISW SlotSpace(CHA* origin, CHA* stop, IUW size);

/* Gets the rx socket length. */
LIB_MEMBER inline ISC BInSpace(BIn* bin);

LIB_MEMBER inline ISC BinBufferLength(BIn* bin);

#if USING_SCRIPT2_TEXT == YES_0
/* Gets a a CHA for printing out the bin_state. */
LIB_MEMBER const CHA** STRBInStates();

/* Pulls the keyboard input into the ring socket. */
// LIB_MEMBER void BInKeyboard ()
#endif

/* Initializes the BIn struct LIB_MEMBER to an empty socket. */
LIB_MEMBER BIn* BInInit(IUW* socket, ISC size);

/* Gets the stop address of the rx socket. */
LIB_MEMBER CHA* BInEnd(BIn* bin);

/* Returns true if the BIn socket contains any data.
    @warning Function does not do any error checking for speed. */
LIB_MEMBER BOL BInIsReadable(BIn* bin);

/* Scans a message with the given params to the given BIn.
The data in the BIn is word-aligned, unlike the Slot. It also
doesn't have a hash with an escape sequence.

@param rx     The BIn socket.
@param params The parameters.
@param args   The arguments.
@return       Returns 0 upon success and an ErrorList ticket number upon
              failure. */
LIB_MEMBER const Op* BInRead(BIn* bin, const ISC* params, void** args);

}  //< namespace _

#endif
#endif
