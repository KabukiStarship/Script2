// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_CRABS_DECL
#define CRABS_CRABS_DECL
#include "Op.h"
#include "Operand.h"
#if SEAM >= CRABS_OPERATION
namespace _ {

/* A full-duplex Crabs EXP (Expression) interpreter.
Crabs' (crabs(s)) must be word-aligned in order to run correctly
so it's best to scan and word align the data types in the same sweep.

Crabs' are composed of one B-Input (BIn) and one B-Output (BOut) socket. The
App/Driver/User writes to the stop of the Tx socket and the driver reads from
the beginning. The user writes are synchronous and the driver reads are
asynchronous.

# Ring Boofer Streaming Diagram

@code
      |>---------------------- Ring Boofer ------------------------->|
      ________________________________________________________________
BOut  |>-Boofer->|>-Sync User SScan->|>-Async Portal Rx-->|>-Boofer->|
      |__________|___________________|____________________|__________|
      ________________________________________________________________
BIn   |>-Boofer->|>-Async Portal Tx->|>-Sync User Writes->|>-Boofer->|
      |__________|___________________|____________________|__________|
@endcode

Almost all block of memory in Script has something that grows up and another
that grows down.

## Stack Memory Layout

@code
0x0 +-------------------------+
 |  |      Crabs struct       |
 V  |-------------------------|
(+) |   Stack of Operand**    |
    |-------------------------|
    |          Slot           |
    |-------------------------|
    |         Boofer          |
    |-------------------------|
    |     Evaluated Result    |
0xN +-------------------------+
@endcode
*/
struct Crabs {

  enum {
    StackTotalMin  = 8, //< Size of the crabs stack.
    BooferTotalMin = 2, //< Min socket size.
  };

  ISC socket_bytes,     //< Offset to the BOut slot.
      header_bytes,     //< The total size of the header in bytes.
      stack_count,      //< Stack Operand count.
      stack_total,      //< Max stack count.
      type,             //< Current type being scanned.
      num_states,       //< Number of states on the state stack.
      bytes_left,       //< Countdown counter for parsing POD types.
      params_left;      //< Height of header and cursors stacks.
  IUA bout_state,       //< BOut streaming state.
      bin_state,        //< Slot streaming state.
      last_bin_state,   //< Last BIn state.
      last_byte;        //< Last byte read.
  CHC current_char;     //< Current Unicode CHA being scanned.
  IUB hash;             //< Packed BSQ hash.
  IUC timeout_us;       //< Timeout time in microseconds.
  ISD last_time;        //< Last time the Stack was scanned.
  IUD ctxt;             //< Current Plain Context Types map word.
  const Op* result;     //< Result of the EXR.
  const DTB* header,    //< Pointer to the header being verified.
      * header_start;   //< Start of the header being verified.
  Operand* operand,     //< Current Script Operand.
      * root;           //< Root-level scope Operand.
  Slot* args;           //< Arguments slot for running.
  Slot slot;            //< Slot for unpacking B-Sequences to.
};

/*  */
inline ISC CrabsHeaderBytes(ISC stack_total);

/* Gets the crabs's socket. */
LIB_MEMBER IUA* CrabsBoofer(Crabs* crabs);

/* Gets a pointer to the BIn slot. */
LIB_MEMBER BIn* CrabsBIn(Crabs* crabs);

/* Gets a pointer to the BOut slot. */
LIB_MEMBER BOut* CrabsBOut(Crabs* crabs);

/* Creates a Stack with equal sized rx and tx slots.
@param root The root-scope device.
@param unpacked_boofer The word-aligned expression socket.
@param unpacked_size   Size of the unpacked socket. */
LIB_MEMBER Crabs* CrabsInit(IUW* socket, ISC boofer_size, ISC stack_count,
                            Operand* root, IUW* unpacked_boofer,
                            IUW unpacked_size, IUD ctxt);

/* Gets the base address of the device stack. */
inline Operand** CrabsStack(Crabs* crabs) {
  return TPtr<Operand*>(&crabs->root);
}

/* Returns true if the Stack uses dynamic memory. */
// LIB_MEMBER BOL CrabsIsDynamic (Crabs* crabs);

LIB_MEMBER IUA* CrabsEndAddress(Crabs* crabs);

/* Resets this Stack to the new state. */
LIB_MEMBER const Op* CrabsReset(Crabs* crabs);

/* Pushes the operand at the given index of the current device control onto the stack.
@return Returns nil upon success and a pointer to a CHA
upon failure. */
LIB_MEMBER const Op* Push(Crabs* crabs, Operand* operand);

/* Attempts to pop an Star off the stack and returns a pointer to a CHA upon failure. */
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
LIB_MEMBER const Op* CrabsScanHeader(Crabs* crabs, const DTB* header);

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
LIB_MEMBER const Op* CrabsForceDisconnect(Crabs* crabs, ERC error);

/* Pops the args off the Crabs Args Stack. */
inline const Op* CrabsArgs(Crabs* crabs, const DTB* params, void** args);

/* Writes the result to the Crabs.
@param crabs The resulting expression.
@param op   The Operation with result B-Sequence header.
@param args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(Crabs* crabs, const Op& op, void** args);

/* Writes the result to the Crabs.
@return NIL upon  @todo something or other, I don't know. WTF is this?
@param crabs The resulting expression.
@param op   The Operation with result B-Sequence header.
@param args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(Crabs* crabs, const Op* op, void** args);

/* Writes the result to the Crabs.
@param crabs The resulting expression.
@param op   The Operation with result B-Sequence header.
@param args Pointers to the B-Sequence args. */
inline const Op* CrabsResult(Crabs* crabs, const ISC* params, void** args);

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
