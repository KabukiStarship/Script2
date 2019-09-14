/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /array.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#ifndef SCRIPT2_ARRAY_CODLESS_HEADER
#define SCRIPT2_ARRAY_CODLESS_HEADER

namespace _ {
struct Autoject;
/* Fills the array with the given fill_char identical to memset. */
LIB_MEMBER CH1* ArrayFill(void* origin, SIW size_bytes, CH1 fill_char = 0);
}  // namespace _

#if SEAM >= SCRIPT2_STACK

/* SocketFactory manages memory for ASCII Objects.
@return A word-aligned buffer, rounding up if unaligned.
@param obj  A block of word-aligned heap memory.
@param size The size of the buffer to create in bytes. */
typedef UIW* (*SocketFactory)(UIW* obj, SIW size);

namespace _ {

/* ASCII OBJ and SocketFactory. */
struct Autoject {
  SocketFactory socket_factory;  //< Autoject Factory function pointer.
  UIW* origin;                   //< Pointer to the Autoject.
};

enum AsciiFactoryFunction {
  kFactoryDelete = 0,  //< Factory function deletes an OBJ.
  kFactoryNew = 1,     //< Factory function checks if the size can double.
  kFactoryGrow = 2,    //< Factory function double OBJ size.
  kFactoryClone = 3,   //< Factory function clones the OBJ.
  kFactoryName = 4,    //< Factory function gets the info string.
  kFactoryFunctionCount = 5,  //< Factory function count.
};

enum AsciiFactoryError {
  kFactorySuccess = 0,      //< Factory operation completed successfully error.
  kFactoryNil = 1,          //< Factory missing error.
  kFactoryNilOBJ = 2,       //< Factory found nil obj.origin pointer error.
  kFactoryNilArg = 3,       //< Factory arg nil error.
  kFactoryCantGrow = 4,     //< Factory can't grow.
  kFactorySizeInvalid = 5,  //< Factory size invalid.
  kFactoryErrorCount = 6,   //< Factory function count.
};

/* SocketFactory for Autojects on the heap that deletes a the buffer. */
LIB_MEMBER UIW* RamFactoryHeap(UIW* buffer, SIW size_bytes, DTW data_type);

/* SocketFactory for Autojects on the program stack that doesn't delete the
buffer. */
LIB_MEMBER UIW* RamFactoryStack(UIW* buffer, SIW size_bytes, DTW data_type);

class Nil {
 public:
  /* Constructures nothing. */
  Nil();

  /* Gets the size of the socket. */
  static constexpr SIW Size();

  /* Gets the size of the socket. */
  static constexpr SIW SizeBytes();

  /* Gets the size of the socket. */
  static constexpr SIW SizeWords();

  /* Gets the nil origin word address. */
  UIW* Words();
};

/* Copies the source to the target functionally identical to memcpy.
@param origin     The start of the write socket.
@param size      The stop of the write socket.
@param origin     The origin of the read socket.
@param read_size Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
LIB_MEMBER CH1* ArrayCopy(void* origin, SIW size, const void* read,
                          SIW read_size);

/* Compares the two memory sockets.
@param start The start of socket a.
@param size_a The size of Array A .
@param start  The origin of socket b.
@param size_b The size of Array B.
@return True if they are the same and false if they are not. */
LIB_MEMBER BOL ArrayCompare(const void* start, SIW size_a, const void* origin,
                            SIW size_b);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param origin       The origin UI1.
@param end         The end UI1.
@param count_bytes The UI1 count to shift up. */
LIB_MEMBER SIW ArrayShiftUp(void* origin, void* end, SIW count_bytes);

/* Shifts the memory down by the given bytes_count.
@return 0 upon failure and count upon success.
@param origin       The start UI1.
@param end         The end UI1.
@param count_bytes The UI1 count to shift up. */
LIB_MEMBER SIW ArrayShiftDown(void* origin, void* end, SIW bytes_count);

}  // namespace _
#endif
#endif
