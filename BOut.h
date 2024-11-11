// Copyright Kabuki Starship� <kabukistarship.com>.
#pragma once
#ifndef INCLUDED_SCRIPT2_BOUT_DECL
#define INCLUDED_SCRIPT2_BOUT_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
namespace _ {

struct BIn;
struct BOut;
struct Op;

/* List of the Finite BOut States. */
typedef enum BOutStates {
  BOutStateDisconnected = 0,  //< BOut State 0: BOut locked.
  BOutStateWriting,           //< BOut State 1: Most common state.
  BOutStateWritingBSeq,       //< BOut State 2: Writing _BSQ.
} BOutState;

/* Byte-ring output socket. */
struct LIB_MEMBER BOut {
  ISN size;             //< Size of the B-Output.
  volatile ISN origin;  //< Starting index of the ring-socket data.
  ISN stop,             //< Stopping index of the ring-socket data.
      read;             //< Address that the BOut device is reading from.
};

/* The first byte in the B-Output's socket.*/
LIB_MEMBER IUA* BOutBoofer(BOut* bout);

/* Used to return an erroneous result from a B-Output.
@param bout       The source BOut.
@param error      The error type.
@param header     The B-Sequence Header.
@param bsq_error  The offset to the type in error in the B-Sequence.
@param error_byte The address of the IUA in error.
@return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error, const ISN* header,
  ISN bsq_error, IUA* error_byte);

#if USING_SCRIPT2_TEXT == YES_0

/* Gets a a CHA for printing out the bout_state. */
LIB_MEMBER const CHA** BOutStateStrings();

#endif

/* Initializes the B-Output socket with the given socket size. */
LIB_MEMBER BOut* BOutInit(IUW* socket, ISN size);

/* Calculates the space left in the given ring socket.
    @param bout The B-Output socket. */
LIB_MEMBER ISN BOutSpace(BOut* bout);

/* Gets the B-Output. */
LIB_MEMBER ISN BOutBooferLength(BOut* bout);

/* Gets the stop address of the tx socket. */
LIB_MEMBER IUA* BOutEndAddress(BOut* bout);

/* Streams a B-Output IUA.
    @param bout A B-Output abstract IUA stream. */
LIB_MEMBER ISN BOutStreamByte(BOut* bout);

/* Writes a message with the given params to the given B-Output slot.
@param bout   The B-Output socket to write to.
@param params The escape sequence to write.
@param args   The array of pointers to the stuff to write. */
LIB_MEMBER const Op* BOutWrite(BOut* bout, const ISN* params, void** args);

/* Sends a connection message to the given address. */
LIB_MEMBER const Op* BOutConnect(BOut* bout, const CHA* address);

/* Sends a connection message to the given address. */
LIB_MEMBER void BOutRingBell(BOut* bout, const CHA* address);

/* Sends a connection message to the given address. */
LIB_MEMBER void BOutAckBack(BOut* bout, const CHA* address);

}  //< namespace _

#endif
#undef DEBUG_SCRIPT2_BOUT
#endif
