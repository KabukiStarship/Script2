/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /mirror.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <calemccollough.github.io>;
all right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#if SEAM >= SCRIPT2_DICTIONARY
#ifndef SCRIPT2_MIRROR
#define SCRIPT2_MIRROR
#include "bin.h"
#include "bout.h"
#include "op.h"

namespace _ {

/* A Mirror in a Chinese Room.
A Mirror */
struct LIB_MEMBER Mirror {
  SI4 size,    //< The size of the socket.
      origin,  //< The starting index of the ring socket data.
      stop,    //< The stopping index of the ring socket data.
      read;    //< The read variable.
};

const Op* MirrorResult(Mirror* mirror, Error error);
const Op* MirrorResult(Mirror* mirror, Error error);

enum {
  kMirrorHeaderSize = 4 * sizeof(SI4)  //< Size of a Mirror Header.
};

static const UIW kMaxMirrorSize = ~((UIW)0);

/* Calculates the used ring socket space.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size The size of the socket. */
LIB_MEMBER SI4 MirrorLength(CH1* origin, CH1* stop, SI4 size);

/* Calculates the space left in the given ring socket.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
LIB_MEMBER SI4 MirrorSpace(CH1* origin, CH1* stop, SI4 size);

/* Checks if the given slot contains the specified address. */
LIB_MEMBER void* MirrorContains(Mirror* mirror, void* address);

/* Clears the ring socket by writing zeros to it. */
LIB_MEMBER void MirrorWipe(Mirror* mirror);

/* Copies a block from a ring-socket to the given destination. */
// LIB_MEMBER CH1* MirrorWrite (Mirror* mirror, void* source, SIW size);

/* Copies a block from a ring-socket to the given destination. */
// LIB_MEMBER CH1* MirrorRead (Mirror* mirror, void* source, SIW size);

/* Gets the args from the b-sequence. */
LIB_MEMBER const Op* MirrorRead(Mirror* mirror, const SI4* params, void** args);

/* Posts a evaluated result to the b-sequence. */
// LIB_MEMBER const Op* MirrorWrite (Mirror* mirror, const SI4* params,
//                                   void** args);

LIB_MEMBER BOL MirrorIsReadable(Mirror* mirror);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const SI4* header);
/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const SI4* header);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const SI4* header, UI1 offset);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
// LIB_MEMBER const Op* MirrorResult (Mirror* mirror, Error error,
//                                   const SI4* header,
//                                   SI4 offset);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const SI4* header, SI4 offset, CH1* address);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the UI1 in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const SI4* header, SI4 offset, CH1* address);

}  // namespace _
#endif  //< SCRIPT2_MIRROR
#endif  //< #if SEAM >= SCRIPT2_DICTIONARY
