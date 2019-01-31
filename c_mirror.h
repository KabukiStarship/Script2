/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/library/script/mirror.h
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
#ifndef SCRIPT2_MIRROR
#define SCRIPT2_MIRROR
#include "bin.h"
#include "bout.h"
#include "c_op.h"

namespace _ {

/* A Mirror in a Chinese Room.
A Mirror */
struct SDK Mirror {
  SI4 size,   //< The size of the socket.
      begin,  //< The starting index of the ring socket data.
      stop,   //< The stopping index of the ring socket data.
      read;   //< The read variable.
};

const Op* MirrorResult(Mirror* mirror, Error error);
const Op* MirrorResult(Mirror* mirror, Error error);

enum {
  kMirrorHeaderSize = 4 * sizeof(SI4)  //< Size of a Mirror Header.
};

static const UIW kMaxMirrorSize = ~((UIW)0);

/* Calculates the used ring socket space.
@param  Start The begin of the data.
@param  Stop  The stop of the data.
@param  Size The size of the socket. */
SDK SI4 MirrorLength(CH1* begin, CH1* stop, SI4 size);

/* Calculates the space left in the given ring socket.
@param  Start The begin of the data.
@param  Stop  The stop of the data.
@param  Size  The size of the socket. */
SDK SI4 MirrorSpace(CH1* begin, CH1* stop, SI4 size);

/* Checks if the given slot contains the specified address. */
SDK void* MirrorContains(Mirror* mirror, void* address);

/* Clears the ring socket by writing zeros to it. */
SDK void MirrorWipe(Mirror* mirror);

/* Copies a block from a ring-socket to the given destination. */
// SDK CH1* MirrorWrite (Mirror* mirror, void* source, size_t size);

/* Copies a block from a ring-socket to the given destination. */
// SDK CH1* MirrorRead (Mirror* mirror, void* source, size_t size);

/* Gets the args from the b-sequence. */
SDK const Op* MirrorRead(Mirror* mirror, const SI4* params, void** args);

/* Posts a evaluated result to the b-sequence. */
// SDK const Op* MirrorWrite (Mirror* mirror, const SI4* params,
//                                   void** args);

SDK BOL MirrorIsReadable(Mirror* mirror);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
SDK const Op* MirrorResult(Mirror* mirror, Error error, const SI4* header);
/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
SDK const Op* MirrorResult(Mirror* mirror, Error error, const SI4* header);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
SDK const Op* MirrorResult(Mirror* mirror, Error error, const SI4* header,
                           UI1 offset);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
// SDK const Op* MirrorResult (Mirror* mirror, Error error,
//                                   const SI4* header,
//                                   SI4 offset);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
SDK const Op* MirrorResult(Mirror* mirror, Error error, const SI4* header,
                           SI4 offset, CH1* address);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
SDK const Op* MirrorResult(Mirror* mirror, Error error, const SI4* header,
                           SI4 offset, CH1* address);

}  // namespace _
#endif  //< SCRIPT2_MIRROR
#endif  //< #if SEAM >= SCRIPT2_14
