// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BIN_DECL
#define CRABS_BIN_DECL
#include <_Config.h>
#if SEAM >= CRABS_OPERATION
namespace _ {

struct BIn;
struct BOut;
struct Op;

/* List of BIn States.
@see SCRIPT Specification RFC. */
typedef enum BInStates {
  BInStateAddress = 0,    //< State  0: Scanning address.
  BInStatePackedArgs,     //< State  1: Scanning arguments.
  BInStatePackedUTF8,     //< State  2: Scanning UTF-8.
  BInStatePackedUTF16,    //< State  3: Scanning UTF-16.
  BInStatePackedUTF32,    //< State  4: Scanning UTF-32.
  BInStatePackedVarint,   //< State  5: Scanning varint.
  BInStatePackedObj,      //< State  6: 8-bit OB1 state.
  BInStateVerifyingHash,  //< State  7: Verifying the 32-bit hash.
  BInStateHandlingError,  //< State  8: Handling an error state.
  BInStateDisconnected,   //< State  9: Disconnected state.
  BInStateAck,            //< State 10: Awaiting connection ACK.
  BInStateLocked,         //< State 11: Locked state.
  BInStatePackedPOD,      //< State 12: Scanning plain-old-data.
  BInStateInvalid         //< Number of BIn States.
} BInState;

/* B-Input ring boofer Slot.
A B-Input Slot is functionally identical to a input port in TCP. */
struct LIB_MEMBER BIn {
  ISN bytes,          //< The size of the socket in bytes.
      origin;         //< The starting index of the ring socket data.
  volatile ISN stop;  //< The stopping index of the ring socket data.
  ISN read;           //< The read variable to memory align the socket.
};

/* Get's the B-Input's socket. */
LIB_MEMBER inline const IUA* BInOrigin(const BIn* bin);
LIB_MEMBER inline IUA* BInOrigin(BIn* bin);

LIB_MEMBER inline IUA* BInEnd(BIn* bin);

/* Calculates the used ring socket space.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
LIB_MEMBER inline ISW SlotLength(IUA* origin, IUA* stop, IUW size);

/* Calculates the space left in the given ring socket.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
LIB_MEMBER inline ISW SlotSpace(IUA* origin, IUA* stop, IUW size);

/* Gets the rx socket length. */
LIB_MEMBER inline ISN BInSpace(BIn* bin);

LIB_MEMBER inline ISN BinBooferLength(BIn* bin);

#if USING_CRABS_TEXT == YES_0

/* Pulls the keyboard input into the ring socket. */
// LIB_MEMBER void BInKeyboard()
#endif

/* Initializes the BIn struct LIB_MEMBER to an empty socket. */
LIB_MEMBER BIn* BInInit(BIn* socket, ISN size);

/* Gets the stop address of the rx socket. */
LIB_MEMBER IUA* BInEnd(BIn* bin);

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
LIB_MEMBER const Op* BInRead(BIn* bin, const DTB* params, void** args, IUD 
                             pc_ctx);

}  //< namespace _

#endif
#endif
