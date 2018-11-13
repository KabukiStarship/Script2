/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /library/script/mirror.h
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
#ifndef INCLUDED_SCRIPT_MIRROR
#define INCLUDED_SCRIPT_MIRROR
#include "bin.h"
#include "bout.h"
#include "op.h"

namespace _ {

/* A Mirror in a Chinese Room.
A Mirror */
struct API Mirror {
  UIT size,  //< The size of the buffer.
      start,    //< The starting index of the ring buffer data.
      stop,     //< The stopping index of the ring buffer data.
      read;     //< The read variable.
};

const Op* MirrorResult(Mirror* mirror, Error error);
const Op* MirrorResult(Mirror* mirror, Error error);

enum {
  kMirrorHeaderSize = 4 * sizeof(UIT)  //< Size of a Mirror Header.
};

static const UIW kMaxMirrorSize = ~((UIW)0);

/* Calculates the used ring buffer space.
@param  Start The start of the data.
@param  Stop  The stop of the data.
@param  Size The size of the buffer. */
API UIT MirrorLength(char* start, char* stop, UIT size);

/* Calculates the space left in the given ring buffer.
@param  Start The start of the data.
@param  Stop  The stop of the data.
@param  Size  The size of the buffer. */
API UIT MirrorSpace(char* start, char* stop, UIT size);

/* Checks if the given slot contains the specified address. */
API void* MirrorContains(Mirror* mirror, void* address);

/* Clears the ring buffer by writing zeros to it. */
API void MirrorWipe(Mirror* mirror);

/* Copies a block from a ring-buffer to the given destination. */
// API char* MirrorWrite (Mirror* mirror, void* source, size_t size);

/* Copies a block from a ring-buffer to the given destination. */
// API char* MirrorRead (Mirror* mirror, void* source, size_t size);

/* Gets the args from the b-sequence. */
API const Op* MirrorRead(Mirror* mirror, const UIT* params, void** args);

/* Posts a evaluated result to the b-sequence. */
// API const Op* MirrorWrite (Mirror* mirror, const UIT* params,
//                                   void** args);

API BOL MirrorIsReadable(Mirror* mirror);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
API const Op* MirrorResult(Mirror* mirror, Error error, const UIT* header);
/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
API const Op* MirrorResult(Mirror* mirror, Error error, const UIT* header);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
API const Op* MirrorResult(Mirror* mirror, Error error, const UIT* header,
                           UI1 offset);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
// API const Op* MirrorResult (Mirror* mirror, Error error,
//                                   const UIT* header,
//                                   UIT offset);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
API const Op* MirrorResult(Mirror* mirror, Error error, const UIT* header,
                           UIT offset, char* address);

/* Used to return an erroneous result from a B-Input.
@param  bin     The source Mirror.
@param  error   The error type.
@param  header  The B-Sequence Header.
@param  offset  The offset to the type in error in the B-Sequence.
@param  address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
API const Op* MirrorResult(Mirror* mirror, Error error, const UIT* header,
                           UIT offset, char* address);

}  //< namespace _
#endif  //< INCLUDED_SCRIPT_MIRROR
#endif  //< #if SEAM >= _0_0_0__13
