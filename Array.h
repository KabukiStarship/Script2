// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_ARRAY_DECL
#define CRABS_ARRAY_DECL 1
#include <_Config.h>
namespace _ {

/* Copies the source to the target functionally identical to memcpy.
@param write     The start of the write socket.
@param size      The stop of the write socket.
@param origin    The origin of the read socket.
@param read_size Number of bytes to copy.
@return Pointer to the last IUA written or nil upon failure. */
LIB_MEMBER inline ISW ArrayCopy(void* write, ISW size, const void* read,
                                ISW read_size);
LIB_MEMBER inline ISW ArrayCopy(void* write, ISW r_size, const void* read, 
                                const void* r_end);
LIB_MEMBER inline ISW ArrayCopy(void* write, void* write_end, const void* read,
                                ISW r_size);
LIB_MEMBER inline ISW ArrayCopy(void* write, void* write_end, const void* read,
                                void* r_end);

/* Compares the two memory sockets.
@param a            The start of socket a.
@param a_bytes The size of socket a in bytes.
@param b            The start of socket b.
@param b_bytes The size of socket b in bytes.
@return a_bytes if a is identical to b, or if a and b are not identical 
the return will be -1 times the number of bytes that were identical in a and 
b. */
LIB_MEMBER ISW ArrayCompare(const void* a, ISW a_bytes,
                            const void* b, ISW b_bytes);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param origin      The origin byte address.
@param end         The end IUA.
@param count_bytes The IUA count to shift up. */
LIB_MEMBER ISW ArrayShiftUp(void* origin, void* end, ISW count_bytes);

/* Shifts the memory down by the given bytes_count.
@return 0 upon failure and count upon success.
@param origin       The start IUA.
@param end         The end IUA.
@param count_bytes The IUA count to shift up. */
LIB_MEMBER ISW ArrayShiftDown(void* origin, void* end, ISW bytes_count);

/* Fills the array elements with the given fill_char; identical to memset. */
LIB_MEMBER CHA* ArrayFill(void* origin, ISW bytes, CHA fill_char = 0);

}  //< namespace _
#endif  //< #ifndef CRABS_ARRAY_DECL
