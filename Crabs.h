/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Crabs.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_CRABS_DECL
#define SCRIPT2_CRABS_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#include "Args.h"
#include "BIn.hpp"
#include "BOut.h"
#include "BSeq.h"
#include "Error.h"
#include "Operand.h"
#include "Slot.h"
namespace _ {

/* A full-duplex Crabs EXP (Expression) interpreter.
Crabs' (crabs(s)) must be word-aligned in order to run correctly
so it's best to scan and word align the data types in the same sweep.

Crabs' are composed of one B-Input (BIn) and one B-Output (BOut) socket. The
App/Driver/User writes to the stop of the Tx socket and the driver reads from
the beginning. The user writes are synchronous and the driver reads are
asynchronous.

# Ring Buffer Streaming Diagram

@code
      |>---------------------- Ring Buffer ------------------------->|
      ________________________________________________________________
BOut  |>-Buffer->|>-Sync User SScan-->|>-Async Portal Rx-->|>-Buffer->|
      |__________|___________________|____________________|__________|
      ________________________________________________________________
BIn   |>-Buffer->|>-Async Portal Tx->|>-Sync User Writes->|>-Buffer->|
      |__________|___________________|____________________|__________|
@endcode

Almost all block of memory in Script has something that grows up and another
that grows down.

# Stack Memory Layout

@code
    |=========================|
    |     Evaluated Result    |
    |            |            |
    |            v            |
    |=========================|
    |          Buffer         |
    |=========================|
    |          Slot           |
    |=========================|
    |   Stack of Operand**    |
 +  |=========================|
 |  |      Crabs struct      |
0xN |=========================|
@endcode
*/
struct Crabs {
  /* List of Crabs Error Ops. */
  typedef enum Errors {
    cErrorBufferOverflow = 0,
    cErrorBufferUnderflow,
    cErrorInvalidOperand,
    cErrorStackOverflow,
    cErrorLockedState,
    cErrorTextOverflow,
    cErrorVarintOverflow,
    cErrorReadInvalidType,
    cErrorImplementation
  } Error;

  enum {
    cMinStaccSize = 16,  //< Size of the crabs stack.
    cMinBufferSize = 2,  //< Min socket size.
  };

  ISC size,            //< Offset to the BOut slot.
      header_size,     //< The total size of the header.
      stack_count,     //< Stack Operand count.
      stack_size,      //< Stack Operand socket size.
      type,            //< Current type being scanned.
      num_states,      //< Number of states on the state stack.
      bytes_left,      //< Countdown counter for parsing POD types.
      params_left;     //< Height of header and cursors stacks.
  IUA bout_state,      //< BOut streaming state.
      bin_state,       //< Slot streaming state.
      last_bin_state,  //< Last BIn state.
      last_byte;       //< Last IUA read.
  CHC current_char;    //< Current Unicode CHA being scanned.
  IUB hash;            //< Packed BSQ hash.
  IUC timeout_us;      //< Timeout time in microseconds.
  TMD last_time;       //< Last time the Stack was scanned.
  const Op* result;    //< Result of the EXR.
  const ISC* header,   //< Pointer to the header being verified.
      * header_start;  //< Start of the header being verified.
  Operand* operand,    //< Current Script Operand.
      * root;          //< Root-level scope Operand.
  Slot& args;          //< Arguments slot for running.
  Slot slot;           //< Slot for unpacking B-Sequences to.
};

/* Gets a pointer to the BIn slot. */
LIB_MEMBER IUW* CrabsBinAddress(Crabs* crabs);

/* Gets the crabs's socket. */
LIB_MEMBER CHA* CrabsBuffer(Crabs* crabs);

/* Gets a pointer to the BIn slot. */
LIB_MEMBER BIn* CrabsBIn(Crabs* crabs);

/* Gets a pointer to the BOut slot. */
LIB_MEMBER IUW* CrabsBOutAddress(Crabs* crabs);

/* Gets a pointer to the BOut slot. */
LIB_MEMBER BOut* CrabsBOut(Crabs* crabs);

/* Creates a Stack with equal sized rx and tx slots.
@param root The root-scope device.
@param unpacked_buffer The word-aligned expression socket.
@param unpacked_size   Size of the unpacked socket. */
LIB_MEMBER Crabs* CrabsInit(IUW* socket, ISC buffer_size, ISC stack_count,
                            Operand* root, IUW* unpacked_buffer,
                            IUW unpacked_size);

/* Gets the base address of the device stack. */
inline Operand** CrabsStack(Crabs* crabs) {
  return TPtr<Operand*>(&crabs->root);
}

/* Returns true if the Stack uses dynamic memory. */
// LIB_MEMBER BOL CrabsIsDynamic (Crabs* crabs);

LIB_MEMBER CHA* CrabsEndAddress(Crabs* crabs);

/* Resets this Stack to the new state. */
LIB_MEMBER const Op* CrabsReset(Crabs* crabs);

/* Pushes the operand at the given index of the current
device control onto the stack.
@return Returns nil upon success and a pointer to a CHA
upon failure. */
LIB_MEMBER const Op* Push(Crabs* crabs, Operand* operand);

/* Attempts to pop an Star off the stack and returns a pointer to a
    CHA upon failure. */
LIB_MEMBER const Op* Pop(Crabs* crabs);

/* Exits the current state. */
LIB_MEMBER IUA CrabsExitState(Crabs* crabs);

/* Sets the new state onto the expression stack.
LIB_MEMBER const Op* CrabsSetState (Crabs* crabs, BInState state); */

/* Saves the current bin_state and sets the bin_state to the new state. */
LIB_MEMBER const Op* CrabsEnterState(Crabs* crabs, BInState state);

/* Streams a B-Output IUA. */
LIB_MEMBER IUA CrabsStreamBOut(Crabs* crabs);

/* Scans the BIn socket and marks the data as being ready to execute.
@param a The Stack to scan. */
LIB_MEMBER const Op* CrabsScanBIn(Crabs* crabs);  // , Portal* io);

/* Returns true if the given Stack contains the given address. */
LIB_MEMBER BOL CrabsContains(Crabs* crabs, void* address);

/* Pushes a header onto the scan stack.*/
LIB_MEMBER const Op* CrabsScanHeader(Crabs* crabs, const ISC* header);

/* Gets the base address of the header stack. */
LIB_MEMBER const ISC* CrabsHeaderStack(Crabs* crabs);

/* Closes the current crabs and cues it for execution. */
LIB_MEMBER void CrabsClose(Crabs* crabs);

/* Cancels the current crabs. */
LIB_MEMBER void CrabsCancel(Crabs* crabs);

/* Cancels the current crabs and writes zeros to the socket. */
LIB_MEMBER void CrabsClear(Crabs* crabs);

/* Script Bell Op rings the bell of the given address. */
LIB_MEMBER void CrabsRingBell(Crabs* crabs, const CHA* address = "");

/* Script Ack-back Op replies an ACK to a Bell Op. */
LIB_MEMBER void CrabsAckBack(Crabs* crabs, const CHA* address = "");

/* Disconnects the expression. */
LIB_MEMBER const Op* CrabsForceDisconnect(Crabs* crabs, Error error);

/* Reads the Crabs args from the crabs->slot.
inline const Op* CrabsArgs (Crabs* crabs, const ISC* params, void** args) {
   const CHA* cursor = ArgsParse (crabs->args_cursor, crabs->args_end,
                                   params, args);
   if (!cursor) {
   }
}*/

/* Pops the args off the Crabs Args Stack. */
inline const Op* CrabsArgs(Crabs* crabs, const ISC* params, void** args) {
  A_ASSERT(params);
  A_ASSERT(args);
  Slot slot(CrabsBIn(crabs));
  return slot.Read(params, args);
}

/* Pops the args off the Crabs Args Stack. */
inline const Op* CrabsArgs(Crabs* crabs, const Op& op, void** args) {
  A_ASSERT(crabs);
  A_ASSERT(args);
  Slot slot(CrabsBIn(crabs));
  return slot.Read(op.in, args);
}

/* Writes the result to the Crabs.
@param crabs The resulting expression.
@param op   The Operation with result B-Sequence header.
@param args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(Crabs* crabs, const Op& op, void** args) {
  return BOutWrite(CrabsBOut(crabs), op.out, args);
}

/* Writes the result to the Crabs.
@param crabs The resulting expression.
@param op   The Operation with result B-Sequence header.
@param args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(Crabs* crabs, const ISC* params, void** args) {
  if (!params) {
    return nullptr;
  }
  return BOutWrite(CrabsBOut(crabs), params, args);
}

/* Writes the result to the Crabs.
@return NIL upon ?
@param crabs The resulting expression.
@param op   The Operation with result B-Sequence header.
@param args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(Crabs* crabs, const Op* op, void** args) {
  if (!op) {
    return nullptr;
  }
  return BOutWrite(CrabsBOut(crabs), op->out, args);
}

/* Returns the Operand header or writes it to the Crabs.
@param crabs  The expression to write the Op header to.
@param header The Op header.
@return Returns the header if crabs is nil. */
LIB_MEMBER const Op* CrabsQuery(Crabs* crabs, const Op& header);

/* Returns the Op header or writes it to the Crabs.
@param crabs The expression to write the Op header to.
@param op    The Op header.
@return Returns the header if crabs is nil. */
LIB_MEMBER const Op* CrabsQuery(Crabs* crabs, const Op* op);

}  //< namespace _

#endif
#endif
