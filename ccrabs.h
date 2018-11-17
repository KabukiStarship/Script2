/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /ccrabs.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
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
#ifndef INCLUDED_CRABS_EXPR
#define INCLUDED_CRABS_EXPR
#include "args.h"
#include "bin.h"
#include "bout.h"
#include "cbsq.h"
#include "error.h"
#include "operand.h"

namespace _ {

/* A full-duplex CCrabs EXP (Expression) interpreter.
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
BOut  |>-Buffer->|>-Sync User Scan-->|>-Async Portal Rx-->|>-Buffer->|
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
 |  |      CCrabs struct      |
0xN |=========================|
@endcode
*/
struct CCrabs {
  /* List of CCrabs Error Ops. */
  typedef enum Errors {
    kErrorBufferOverflow = 0,
    kErrorBufferUnderflow,
    kErrorInvalidOperand,
    kErrorStackOverflow,
    kErrorLockedState,
    kErrorTextOverflow,
    kErrorVarintOverflow,
    kErrorReadInvalidType,
    kErrorImplementation
  } Error;

  enum {
    kMinStackSize = 16,  //< Size of the crabs stack.
    kMinBufferSize = 2,  //< Min socket size.
  };

  UIT size,            //< Offset to the BOut slot.
      header_size,     //< The total size of the header.
      stack_count,     //< Stack Operand count.
      stack_size,      //< Stack Operand socket size.
      type,            //< Current type being scanned.
      num_states,      //< Number of states on the state stack.
      bytes_left,      //< Countdown counter for parsing POD types.
      params_left;     //< Height of header and cursors stacks.
  UI1 bout_state,      //< BOut streaming state.
      bin_state,       //< Slot streaming state.
      last_bin_state,  //< Last BIn state.
      last_byte;       //< Last UI1 read.
  CHW current_char;    //< Current Unicode char being scanned.
  hash16_t hash;       //< Packed BSQ hash.
  UI4 timeout_us;      //< Timeout time in microseconds.
  TME last_time;       //< Last time the Stack was scanned.
  const Op* result;    //< Result of the EXR.
  const UIT *header,   //< Pointer to the header being verified.
      *header_start;   //< Start of the header being verified.
  Operand *operand,    //< Current Script Operand.
      *root;           //< Root-level scope Operand.
  Slot& args;          //< Arguments slot for running.
  Slot slot;           //< Slot for unpacking B-Sequences to.
};

/* Gets a pointer to the BIn slot. */
API UIW* CrabsBinAddress(CCrabs* crabs);

/* Gets the crabs's socket. */
API char* CrabsBuffer(CCrabs* crabs);

/* Gets a pointer to the BIn slot. */
API BIn* CrabsBIn(CCrabs* crabs);

/* Gets a pointer to the BOut slot. */
API UIW* CrabsBOutAddress(CCrabs* crabs);

/* Gets a pointer to the BOut slot. */
API BOut* CrabsBOut(CCrabs* crabs);

/* Creates a Stack with equal sized rx and tx slots.
@param root The root-scope device.
@param unpacked_buffer The word-aligned expression socket.
@param unpacked_size   Size of the unpacked socket. */
API CCrabs* CrabsInit(UIW* socket, UIT buffer_size, UIT stack_count,
                      Operand* root, UIW* unpacked_buffer, UIW unpacked_size);

/* Gets the base address of the device stack. */
inline Operand** CrabsStack(CCrabs* crabs) {
  return reinterpret_cast<Operand**>(&crabs->root);
}

/* Returns true if the Stack uses dynamic memory. */
// API BOL CrabsIsDynamic (CCrabs* crabs);

API char* CrabsEndAddress(CCrabs* crabs);

/* Resets this Stack to the new state. */
API const Op* CrabsReset(CCrabs* crabs);

/* Pushes the operand at the given index of the current
device control onto the stack.
@return Returns nil upon success and a pointer to a char
upon failure. */
API const Op* Push(CCrabs* crabs, Operand* operand);

/* Attempts to pop an Star off the stack and returns a pointer to a
    char upon failure. */
API const Op* Pop(CCrabs* crabs);

/* Exits the current state. */
API UI1 CrabsExitState(CCrabs* crabs);

/* Sets the new state onto the expression stack.
API const Op* CrabsSetState (CCrabs* crabs, BInState state); */

/* Saves the current bin_state and sets the bin_state to the new state. */
API const Op* CrabsEnterState(CCrabs* crabs, BInState state);

/* Streams a B-Output UI1. */
API UI1 CrabsStreamBOut(CCrabs* crabs);

/* Scans the BOut socket and marks the data as being ready to execute.
@param a The Stack to scan. */
API const Op* CrabsUnpack(CCrabs* crabs);  // , Portal* io);

/* Returns true if the given Stack contains the given address. */
API BOL CrabsContains(CCrabs* crabs, void* address);

/* Pushes a header onto the scan stack.*/
API const Op* CrabsScanHeader(CCrabs* crabs, const UIT* header);

/* Gets the base address of the header stack. */
API const UIT* CrabsHeaderStack(CCrabs* crabs);

/* Closes the current crabs and cues it for execution. */
API void CrabsClose(CCrabs* crabs);

/* Cancels the current crabs. */
API void CrabsCancel(CCrabs* crabs);

/* Cancels the current crabs and writes zeros to the socket. */
API void CrabsClear(CCrabs* crabs);

/* Script Bell Op rings the bell of the given address. */
API void CrabsRingBell(CCrabs* crabs, const char* address = "");

/* Script Ack-back Op replies an ACK to a Bell Op. */
API void CrabsAckBack(CCrabs* crabs, const char* address = "");

/* Disconnects the expression. */
API const Op* CrabsForceDisconnect(CCrabs* crabs, Error error);

/* Reads the CCrabs args from the crabs->slot.
inline const Op* CrabsArgs (CCrabs* crabs, const UIT* params, void** args) {
   const char* cursor = ArgsParse (crabs->args_cursor, crabs->args_end,
                                   params, args);
   if (!cursor) {
   }
}*/

/* Pops the args off the CCrabs Args Stack. */
inline const Op* CrabsArgs(CCrabs* crabs, const UIT* params, void** args) {
  ASSERT(params);
  ASSERT(args);
  Slot slot(CrabsBIn(crabs));
  return slot.Read(params, args);
}

/* Pops the args off the CCrabs Args Stack. */
inline const Op* CrabsArgs(CCrabs* crabs, const Op& op, void** args) {
  ASSERT(crabs);
  ASSERT(args);
  Slot slot(CrabsBIn(crabs));
  return slot.Read(op.in, args);
}

/* Writes the result to the CCrabs.
@param  crabs The resulting expression.
@param  op   The Operation with result B-Sequence header.
@param  args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(CCrabs* crabs, const Op& op, void** args) {
  return BOutWrite(CrabsBOut(crabs), op.out, args);
}

/* Writes the result to the CCrabs.
@param  crabs The resulting expression.
@param  op   The Operation with result B-Sequence header.
@param  args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(CCrabs* crabs, const UIT* params, void** args) {
  if (!params) {
    return nullptr;
  }
  return BOutWrite(CrabsBOut(crabs), params, args);
}

/* Writes the result to the CCrabs.
@return NIL upon ?
@param  crabs The resulting expression.
@param  op   The Operation with result B-Sequence header.
@param  args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(CCrabs* crabs, const Op* op, void** args) {
  if (!op) {
    return nullptr;
  }
  return BOutWrite(CrabsBOut(crabs), op->out, args);
}

/* Returns the Operand header or writes it to the CCrabs.
@param crabs  The expression to write the Op header to.
@param header The Op header.
@return Returns the header if crabs is nil. */
API const Op* CrabsQuery(CCrabs* crabs, const Op& header);

/* Returns the Op header or writes it to the CCrabs.
@param crabs The expression to write the Op header to.
@param op    The Op header.
@return Returns the header if crabs is nil. */
API const Op* CrabsQuery(CCrabs* crabs, const Op* op);

#if CRABS_TEXT

/* Prints the CCrabs stack to the Text socket */
API UTF1& PrintCrabs(UTF1& printer, CCrabs* crabs);

/* Prints the CCrabs stack to the Text socket */
API UTF1& PrintCrabsStack(UTF1& printer, CCrabs* crabs);
#endif

}  // namespace _

#if CRABS_TEXT

/* Prints the given CCrabs to the Text socket. */
inline _::UTF1& operator<<(_::UTF1& printer, _::CCrabs* crabs) {
  return _::PrintCrabs(printer, crabs);
}
#endif

#endif  //< INCLUDED_CRABS_EXPR
#endif  //< #if SEAM >= _0_0_0__13
