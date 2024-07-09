/* Script2™
@link    https://github.com/KabukiStarship/Script2.git
@file    /Autoject.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship™ <kabukistarship.com>; This Source Code 
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at 
<https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_AUTOJECT_HEADER
#define SCRIPT2_AUTOJECT_HEADER
#include <_Config.h>
#if SEAM >= SCRIPT2_STACK
namespace _ {

struct Autoject;
}

/* RAMFactory manages memory for ASCII Objects.
@return A word-aligned boofer, rounding up if unaligned.
@param obj  A block of word-aligned heap memory.
@param size The size of the boofer to create in bytes. */
typedef IUW* (*RAMFactory)(IUW* obj, ISW size);

namespace _ {

/* ASCII OBJ and RAMFactory. */
struct Autoject {
  RAMFactory ram_factory;  //< Autoject Factory function pointer.
  IUW* begin;              //< Pointer to the Autoject.
};

enum RAMFactoryFunction {
  RAMFactoryDelete = 0,  //< Factory function deletes an OBJ.
  RAMFactoryNew = 1,     //< Factory function checks if the size can double.
  RAMFactoryGrow = 2,    //< Factory function double OBJ size.
  RAMFactoryClone = 3,   //< Factory function clones the OBJ.
  RAMFactoryName = 4,    //< Factory function gets the info AString.
  RAMFactoryFunctionCount = 5,  //< Factory function count.
};

enum RAMFactoryError {
  RAMFactorySuccess = 0,      //< Factory operation completed successfully error.
  RAMFactoryNil = 1,          //< Factory missing error.
  RAMFactoryNilOBJ = 2,       //< Factory found nil obj.begin pointer error.
  RAMFactoryNilArg = 3,       //< Factory arg nil error.
  FactoryCantGrow = 4,     //< Factory can't grow.
  RAMFactorySizeInvalid = 5,  //< Factory size invalid.
  RAMFactoryErrorCount = 6,   //< Factory function count.
};

/* Creates or destroys a block of heap memory.
@pre size_bytes > 0 */
LIB_MEMBER IUW* RAMFactoryHeap(IUW* obj, ISW size_bytes);

/* Creates a block of heap memory. */
LIB_MEMBER IUW* RAMFactoryStack(IUW* ptr, ISW size_bytes);

LIB_INLINE IUW* AutojectBeginSet(Autoject& obj, void* boofer);

/* Deletes the given obj using the obj.factory. */
LIB_MEMBER void Delete(Autoject& obj);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CHA* RAMFill(void* begin, void* end, CHA fill_char = 0);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CHA* RAMFill(void* begin, ISW size, CHA fill_char = 0);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CHA* ArrayWipe(void* begin, void* end);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CHA* ArrayWipe(void* begin, ISW size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin     The start of the write socket.
@param  size      The stop of the write socket.
@param  begin     The begin of the read socket.
@param  read_size Number of bytes to copy.
@return Pointer to the last IUA written or nil upon failure. */
LIB_MEMBER CHA* RAMCopy(void* begin, ISW size, const void* read,
                          ISW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  size  Number of bytes to copy.
@return Pointer to the last IUA written or nil upon failure. */
LIB_MEMBER CHA* RAMCopy(void* start, void* stop, const void* begin,
                          ISW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  start The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  end   The end of the read socket.
@return Pointer to the last IUA written or nil upon failure. */
LIB_INLINE CHA* RAMCopy(void* start, void* stop, const void* begin,
                          const void* end);

/* Compares the two memory sockets.
@param  start  The start of Socket A.
@param  stop   The stop of Socket A.
@param  begin  The begin of Socket B.
@param  end    The end of Socket B.
@return True if they are the same and false if they are not. */
LIB_MEMBER const void* RAMCompare(const void* start, const void* stop,
                                    const void* begin, const void* end);

/* Compares the two memory sockets.
@param  start The start of Socket A.
@param  stop  The stop of Socket A.
@param  begin The begin of Socket B.
@param  size  The size of Socket B.
@return True if they are the same and false if they are not. */
LIB_MEMBER const void* RAMCompare(const void* start, void* stop, 
                                    const void* begin, ISW size);

/* Compares the two memory sockets.
@param  start The start of socket a.
@param  size_a The size of Socket A .
@param  start  The begin of socket b.
@param  size_b The size of Socket B.
@return True if they are the same and false if they are not. */
LIB_MEMBER const void* RAMCompare(const void* start, ISW size_a,
                                    const void* begin, ISW size_b);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param  begin       The begin IUA.
@param  end         The end IUA.
@param  count_bytes The IUA count to shift up. */
LIB_MEMBER ISW RAMShiftUp(void* begin, void* end, ISW count_bytes);

/* Shifts the memory down by the given bytes_count.
@return 0 upon failure and count upon success.
@param  begin       The start IUA.
@param  end         The end IUA.
@param  count_bytes The IUA count to shift up. */
LIB_MEMBER ISW RAMShiftDown(void* begin, void* end, ISW bytes_count);

}  //< namespace _
#endif
#endif
