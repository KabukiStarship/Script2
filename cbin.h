/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_console.cc
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2018 Cale McCollough <calemccollough.github.io>;
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
#ifndef INCLUDED_CRABS_CBIN
#define INCLUDED_CRABS_CBIN 1
#include "cbout.h"
#include "cop.h"

namespace _ {

/* List of BIn States.
@see SCRIPT Specification RFC. */
typedef enum BInStates {
  kBInStateAddress = 0,    //< State  0: Scanning address.
  kBInStatePackedArgs,     //< State  1: Scanning arguments.
  kBInStatePackedUtf8,     //< State  2: Scanning UTF-8 string.
  kBInStatePackedUtf16,    //< State  3: Scanning UTF-16 string.
  kBInStatePackedUtf32,    //< State  4: Scanning UTF-32 string.
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
struct API BIn {
  UIT size,           //< The size of the socket.
      start;          //< The starting index of the ring socket data.
  volatile UIT stop;  //< The stopping index of the ring socket data.
  UIT read;           //< The read variable.
};

/* Get's the B-Input's socket. */
inline char* BInBegin(BIn* bin);

inline char* BInEnd(BIn* bin);

/* Calculates the used ring socket space.
@param  Start The start of the data.
@param  Stop  The stop of the data.
@param  Size  The size of the socket. */
inline SIW SlotLength(char* start, char* stop, UIW size);

/* Calculates the space left in the given ring socket.
@param  Start The start of the data.
@param  Stop  The stop of the data.
@param  Size  The size of the socket. */
inline SIW SlotSpace(char* start, char* stop, UIW size);

/* Gets the rx socket length. */
inline UIT BInSpace(BIn* bin);

inline UIT BinBufferLength(BIn* bin);

#if USING_CRABS_TEXT == YES
/* Gets a a char for printing out the bin_state. */
API const char** BInStateStrings();

/* Pulls the keyboard input into the ring socket. */
// API void BInKeyboard ()
#endif

/* Initializes the BIn struct API to an empty socket. */
API BIn* BInInit(UIW* socket, UIT size);

/* Gets the stop address of the rx socket. */
API char* BInEnd(BIn* bin);

/* Returns true if the BIn socket contains any data.
    @warning Function does not do any error checking for speed. */
API BOL BInIsReadable(BIn* bin);

/* Scans a message with the given params to the given BIn.
The data in the BIn is word-aligned, unlike the Slot. It also
doesn't have a hash with an escape sequence.

@param rx     The BIn socket.
@param params The parameters.
@param args   The arguments.
@return       Returns 0 upon success and an ErrorList ticket number upon
              failure. */
API const Op* BInRead(BIn* bin, const UIT* params, void** args);

inline const Op* BOutRead(BOut* bout, const UIT* params, void** args) {
  return BInRead(reinterpret_cast<BIn*>(bout), params, args);
}

#if USING_UTF8 == YES
/* Prints the BIn to the Text.
@param  bin The pin to utf.
@param  text The Text to utf the bin to.
@return The text. */
API UTF1& Print(UTF1& printer, BIn* bin);
#endif  //< #if USING_UTF8 == YES
#if USING_UTF16 == YES
/* Prints the BIn to the Text.
@param  bin The pin to utf.
@param  text The Text to utf the bin to.
@return The text. */
API UTF2& Print(UTF2& printer, BIn* bin);
#endif  //< #if USING_UTF16 == YES
#if USING_UTF32 == YES
/* Prints the BIn to the Text.
@param  bin The pin to utf.
@param  text The Text to utf the bin to.
@return The text. */
API UTF4& Print(UTF4& printer, BIn* bin);
#endif  //< #if USING_UTF32 == YES

}  // namespace _

#if USING_CRABS_TEXT == YES
/* Prints out the bin to the text. */
inline _::UTF1& operator<<(_::UTF1& utf, _::BIn* bin) {
  return Print(utf, bin);
}
#endif

#endif  //< INCLUDED_CRABS_CBIN
#endif  //> #if SEAM >= _0_0_0__13
