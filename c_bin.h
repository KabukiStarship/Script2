/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_console.cc
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_14
#ifndef INCLUDED_CRABS_CBIN
#define INCLUDED_CRABS_CBIN 1
#include "c_bout.h"
#include "c_op.h"

namespace _ {

/* List of BIn States.
@see SCRIPT Specification RFC. */
typedef enum BInStates {
  kBInStateAddress = 0,    //< State  0: Scanning address.
  kBInStatePackedArgs,     //< State  1: Scanning arguments.
  kBInStatePackedUTF8,     //< State  2: Scanning UTF-8 .
  kBInStatePackedUTF16,    //< State  3: Scanning UTF-16 .
  kBInStatePackedUTF32,    //< State  4: Scanning UTF-32 .
  kBInStatePackedVarint,   //< State  5: Scanning varint.
  kBInStatePackedObj,      //< State  6: 8-bit OB1 state.
  kBInStateVerifyingHash,  //< State  7: Verifying the 32-bit hash.
  kBInStateHandlingError,  //< State  8: Handling an error state.
  kBInStateDisconnected,   //< State  9: Disconnected state.
  kBInStateAck,            //< State 10: Awaiting connection ACK.
  kBInStateLocked,         //< State 11: Locked state.
  kBInStatePackedPod,      //< State 12: Scanning plain-old-data.
} BInState;

/* A*B B-Input Slot.
A B-Input Slot is functionally identical to a input port in TCP. */
struct SDK BIn {
  SI4 size,           //< The size of the socket.
      begin;          //< The starting index of the ring socket data.
  volatile SI4 stop;  //< The stopping index of the ring socket data.
  SI4 read;           //< The read variable.
};

/* Get's the B-Input's socket. */
inline CH1* BInBegin(BIn* bin);

inline CH1* BInEnd(BIn* bin);

/* Calculates the used ring socket space.
@param  Start The begin of the data.
@param  Stop  The stop of the data.
@param  Size  The size of the socket. */
inline SIW SlotLength(CH1* begin, CH1* stop, UIW size);

/* Calculates the space left in the given ring socket.
@param  Start The begin of the data.
@param  Stop  The stop of the data.
@param  Size  The size of the socket. */
inline SIW SlotSpace(CH1* begin, CH1* stop, UIW size);

/* Gets the rx socket length. */
inline SI4 BInSpace(BIn* bin);

inline SI4 BinBufferLength(BIn* bin);

#if USING_CRABS_TEXT == YES
/* Gets a a CH1 for printing out the bin_state. */
SDK const CH1** BInStateStrands();

/* Pulls the keyboard input into the ring socket. */
// SDK void BInKeyboard ()
#endif

/* Initializes the BIn struct SDK to an empty socket. */
SDK BIn* BInInit(UIW* socket, SI4 size);

/* Gets the stop address of the rx socket. */
SDK CH1* BInEnd(BIn* bin);

/* Returns true if the BIn socket contains any data.
    @warning Function does not do any error checking for speed. */
SDK BOL BInIsReadable(BIn* bin);

/* Scans a message with the given params to the given BIn.
The data in the BIn is word-aligned, unlike the Slot. It also
doesn't have a hash with an escape sequence.

@param rx     The BIn socket.
@param params The parameters.
@param args   The arguments.
@return       Returns 0 upon success and an ErrorList ticket number_ upon
              failure. */
SDK const Op* BInRead(BIn* bin, const SI4* params, void** args);

inline const Op* BOutRead(BOut* bout, const SI4* params, void** args) {
  return BInRead(reinterpret_cast<BIn*>(bout), params, args);
}

#if USING_UTF8 == YES
/* Prints the BIn to the Text.
@param  bin The pin to utf.
@param  text The Text to utf the bin to.
@return The text. */
SDK UTF1& Print(UTF1& printer, BIn* bin);
#endif  //< #if USING_UTF8 == YES
#if USING_UTF16 == YES
/* Prints the BIn to the Text.
@param  bin The pin to utf.
@param  text The Text to utf the bin to.
@return The text. */
SDK UTF2& Print(UTF2& printer, BIn* bin);
#endif  //< #if USING_UTF16 == YES
#if USING_UTF32 == YES
/* Prints the BIn to the Text.
@param  bin The pin to utf.
@param  text The Text to utf the bin to.
@return The text. */
SDK UTF4& Print(UTF4& printer, BIn* bin);
#endif  //< #if USING_UTF32 == YES

}  // namespace _

#if USING_CRABS_TEXT == YES
/* Prints out the bin to the text. */
inline ::_::UTF1& operator<<(::_::UTF1& utf, ::_::BIn* bin) {
  return Print(utf, bin);
}
#endif

#endif  //< INCLUDED_CRABS_CBIN
#endif  //> #if SEAM >= SCRIPT2_14