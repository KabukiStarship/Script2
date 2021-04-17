/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Array.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_ARRAY_DECL
#define SCRIPT2_ARRAY_DECL
namespace _ {

struct Autoject;
/* Fills the array with the given fill_char identical to memset. */
LIB_MEMBER CHA* ArrayFill(void* origin, ISW size_bytes, CHA fill_char = 0);
}  // namespace _

#if SEAM >= SCRIPT2_STACK

/* SocketFactory manages memory for ASCII Objects.
@return A word-aligned buffer, rounding up if unaligned.
@param obj  A block of word-aligned heap memory.
@param size The size of the buffer to create in bytes. */
typedef IUW* (*SocketFactory)(IUW* obj, ISW size);

namespace _ {

/* ASCII OBJ and SocketFactory. */
struct Autoject {
  SocketFactory socket_factory;  //< Autoject Factory function pointer.
  IUW* origin;                   //< Pointer to the Autoject.
};

enum AsciiFactoryFunction {
  cFactoryDelete = 0,  //< Factory function deletes an OBJ.
  cFactoryNew = 1,     //< Factory function checks if the size can double.
  cFactoryGrow = 2,    //< Factory function double OBJ size.
  cFactoryClone = 3,   //< Factory function clones the OBJ.
  cFactoryName = 4,    //< Factory function gets the info string.
  cFactoryFunctionCount = 5,  //< Factory function count.
};

enum AsciiFactoryError {
  cFactorySuccess = 0,      //< Factory operation completed successfully error.
  cFactoryNil = 1,          //< Factory missing error.
  cFactoryNilOBJ = 2,       //< Factory found nil obj.origin pointer error.
  cFactoryNilArg = 3,       //< Factory arg nil error.
  cFactoryCantGrow = 4,     //< Factory can't grow.
  cFactorySizeInvalid = 5,  //< Factory size invalid.
  cFactoryErrorCount = 6,   //< Factory function count.
};

/* SocketFactory for Autojects on the heap that deletes a the buffer. */
LIB_MEMBER IUW* RamFactoryHeap(IUW* buffer, ISW size_bytes, DTW data_type);

/* SocketFactory for Autojects on the program stack that doesn't delete the
buffer. */
LIB_MEMBER IUW* RamFactoryStack(IUW* buffer, ISW size_bytes, DTW data_type);

class Nil {
 public:
  /* Constructures nothing. */
  Nil();

  /* Gets the size of the socket. */
  static constexpr ISW Size();

  /* Gets the size of the socket. */
  static constexpr ISW SizeBytes();

  /* Gets the size of the socket. */
  static constexpr ISW SizeWords();

  /* Gets the nil origin word address. */
  IUW* Words();
};

/* Copies the source to the target functionally identical to memcpy.
@param origin     The start of the write socket.
@param size      The stop of the write socket.
@param origin     The origin of the read socket.
@param read_size Number of bytes to copy.
@return Pointer to the last IUA written or nil upon failure. */
LIB_MEMBER CHA* ArrayCopy(void* origin, ISW size, const void* read,
                          ISW read_size);

/* Compares the two memory sockets.
@param start The start of socket a.
@param size_a The size of Array A .
@param start  The origin of socket b.
@param size_b The size of Array B.
@return True if they are the same and false if they are not. */
LIB_MEMBER BOL ArrayCompare(const void* start, ISW size_a, const void* origin,
                            ISW size_b);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param origin       The origin IUA.
@param end         The end IUA.
@param count_bytes The IUA count to shift up. */
LIB_MEMBER ISW ArrayShiftUp(void* origin, void* end, ISW count_bytes);

/* Shifts the memory down by the given bytes_count.
@return 0 upon failure and count upon success.
@param origin       The start IUA.
@param end         The end IUA.
@param count_bytes The IUA count to shift up. */
LIB_MEMBER ISW ArrayShiftDown(void* origin, void* end, ISW bytes_count);

}  // namespace _
#endif
#endif
