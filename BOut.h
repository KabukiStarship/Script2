// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BOUT_DECL
#define CRABS_BOUT_DECL
#include "_Config.h"
#if SEAM >= CRABS_OP
namespace _ {

struct BIn;
struct Op;

/* List of the Finite BOut States. */
typedef enum BOutStates {
  BOutStateDisconnected = 0,  //< BOut State 0: BOut locked.
  BOutStateWriting,           //< BOut State 1: Most common state.
  BOutStateWritingBSeq,       //< BOut State 2: Writing _BSQ.
} BOutState;

/* Byte-ring output socket. */
struct BOut {
  ISN bytes;            //< Size of the B-Output in bytes.
  volatile ISN origin;  //< Starting index of the ring-socket data.
  ISN stop,             //< Stopping index of the ring-socket data.
      read;             //< Address that the BOut device is reading from.
};

/* Used to return an erroneous result from a B-Output.
@param bout       The source BOut.
@param error      The error type.
@param header     The B-Sequence Header.
@param bsq_error  The offset to the type in error in the B-Sequence.
@param error_byte The address of the IUA in error.
@return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error, const DTB* header,
  ISN bsq_error, IUA* error_byte);

#if USING_CRABS_TEXT == YES_0

/* Gets a a CHA for printing out the bout_state. */
const CHA** BOutStateStrings();

#endif

/* Initializes the B-Output socket with the given socket size. */
BOut* BOutInit(BOut* socket, ISN size);

/* Calculates the space left in the given ring socket.
    @param bout The B-Output socket. */
ISN BOutSpace(BOut* bout);

/* Gets the B-Output. */
ISN BOutBufferLength(BOut* bout);

/* Gets the stop address of the tx socket. */
IUA* BOutEndAddress(BOut* bout);

/* Streams a B-Output IUA.
    @param bout A B-Output abstract IUA stream. */
ISN BOutStreamByte(BOut* bout);

/* The first byte in the B-Output's socket.*/
IUA* BOutBuffer(BOut* bout);

/* Gets the begin of the socket. */
inline const CHA* BOutBegin(const BOut* bout);
inline CHA* BOutBegin(BOut* bout);

/* Used to return an erroneous result from a B-Output.
@param error The error type.
@return Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error);

/* Used to return an erroneous result from a B-Output.
@param bout    The source BOut.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error, const DTB* header);

/* Used to return an erroneous result from a B-Output.
@param bout    The source BOut.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Op Result. */
inline const Op* BOutError(BOut* bout, ERC error, const DTB* header,
  ISN offset);

/* Writes a message with the given params to the given B-Output slot.
@param bout   The B-Output socket to write to.
@param params The escape sequence to write.
@param args   The array of pointers to the stuff to write.
@param pc_ctx The context mapping for the write operation. */
const Op* BOutWrite(BOut* bout, const DTB* params, void** args, 
  IUD pc_ctx);

/* Sends a connection message to the given address. */
const Op* BOutConnect(BOut* bout, const CHA* address, IUD pc_ctx);

/* Sends a connection message to the given address. */
void BOutRingBell(BOut* bout, const CHA* address);

/* Sends a connection acknowledgment to the given address. */
void BOutAckBack(BOut* bout, const CHA* address);

/* Sends a connection termination message to the given address. */
void BOutTerminate(BOut* bout, const CHA* address);

/* Sends a connection reset message to the given address. */
void BOutReset(BOut* bout, const CHA* address);

/* Links a BOut (producer) and a BIn (consumer) so they share one ring.
This is the single-producer/single-consumer lock-free pipe: the BOut's
write-head (bout->stop) and the BIn's read-head (bin->origin) become the two
independent volatile counters over one shared byte region. The BIn's
write-head mirror (bin->stop) and the BOut's read-head mirror (bout->origin)
alias the producer/consumer heads respectively so each side sees the other's
progress. After calling this, BOutWrite(bout, ...) into the producer and
BInRead(bin, ...) from the consumer exchange messages through the shared ring.
@param bin   The consumer BIn (Room B's input).
@param bout  The producer BOut (Room A's output).
@param buffer The shared byte region both structs will use (must be at least
              SlotBytesMin bytes). This is the memory that, in a real
              interprocess pipe, would live in shared memory.
@return Returns the consumer BIn upon success.
@see BIn.h, BOut.h, Slot.h (the Chinese Room Slot/Door/pipe). */
BIn* BInAttach(BIn* bin, BOut* bout, IUA* buffer, ISN buffer_bytes);

}  //< namespace _

#endif
#endif
