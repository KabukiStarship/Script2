/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /csocket.h
@author  Cale McCollough <https://calemccollough.github.io>
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

#if SEAM >= _0_0_0__02

#ifndef INCLUDED_SCRIPTKABUKI_SOCKET
#define INCLUDED_SCRIPTKABUKI_SOCKET

namespace _ {

enum {
  kCpuCacheLineSize = 64,
  kWordBitCount = sizeof(void*) == 8 ? 3 : sizeof(void*) == 4 ? 2 : 0
};

/* Aligns the given pointer down to the given mask. */
API CH1* AlignDown(CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
API const CH1* AlignDown(const CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
API UIW* AlignDown(UIW* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
API const UIW* AlignDown(const UIW* pointer, UIW mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
API inline SI1 AlignDown(SI1 value, SI1 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
API inline SI2 AlignDown(SI2 value, SI2 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
API inline SI4 AlignDown(SI4 value, SI4 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
API inline SI8 AlignDown(SI8 value, SI8 mask = kWordLSbMask);

/* Aligns the given pointer up to the given mask. */
API const CH1* AlignUp(const CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given socket pointer up to a cache line boundary (64 bytes). */
API inline UIW* AlignUp(UIW* socket, UIW mask = kWordLSbMask);

/* Aligns the given pointer up to the given mask. */
API CH1* AlignUp(CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given value up to an 8-UI1 boundary. */
API inline UI1 AlignUp(UI1 value, UI1 mask = kWordLSbMask);

/* Aligns the given value up to an 8-UI1 boundary. */
API inline SI1 AlignUp(SI1 value, SI1 mask = kWordLSbMask);

/* Aligns the given value up to an 16-UI1 boundary. */
API UI2 AlignUp(UI2 value, UI2 mask = kWordLSbMask);

/* Aligns the given value up to an 16-UI1 boundary. */
API SI2 AlignUp(SI2 value, SI2 mask = kWordLSbMask);

/* Aligns the given value up to an 32-UI1 boundary. */
API inline UI4 AlignUp(UI4 value, UI4 mask = kWordLSbMask);

/* Aligns the given value up to an 32-UI1 boundary. */
API inline SI4 AlignUp(SI4 value, SI4 mask = kWordLSbMask);

/* Aligns the given value up to an 64-UI1 boundary. */
API inline UI8 AlignUp(UI8 value, UI8 mask = kWordLSbMask);

/* Aligns the given value up to an 64-UI1 boundary. */
API inline SI8 AlignUp(SI8 value, SI8 mask = kWordLSbMask);

/* A managed general purpose (i.e. not just for networking) memory socket.
    A socket is just a hole in something for fitting something in, like a light
    or electric socket. A socket of memory is just a block of memory you fit
    something in. A network socket is a socket for interprocess communication,
    which is usually implemented with a ring socket
    (@see ~/kabuki-toolkit/slot.h).
*/
struct Socket {
  CH1 *begin,  //< Beginning of the socket.
      *stop;   //< End of the socket.

  /* Constructs an uninitialized socket. */
  Socket();

  /* Constructor. */
  Socket(void* begin, void* stop);

  /* Constructor. */
  Socket(void* begin, SIW size);

  /* Clones the other memory. */
  Socket(const Socket& other);

  /* C++ operator= overload. */
  Socket& operator=(const Socket& other);
};

/* Creates a block of dynamic memory. */
API inline UIW* New(SIW size);

/* AsciiFactory deletes the socket. */
API inline void Delete(UIW* socket);

/* Converts the pointer to a std::UIW. */
API inline UIW UIntPtr(const void* value);

/* Converts the std::UIW to a pointer. */
API inline void* VoidPtr(UIW value);

/* Converts the std::UIW to a pointer. */
API inline const void* ConstVoidPtr(UIW value);

/* Calculates the difference between the begin and stop address. */
API inline SIW SizeOf(const void* begin, const void* stop);

/* Overwrites the memory with fill_char; functionally identical to memset. */
API CH1* SocketFill(CH1* begin, CH1* stop, SIW size, CH1 fill_char = 0);

/* Overwrites the memory with fill_char; functionally identical to memset. */
API CH1* SocketFill(void* begin, SIW size, CH1 fill_char = 0);

/* Copies the source to the target functionally identical to memcpy.
@param  begin     The begin of the write socket.
@param  size      The stop of the write socket.
@param  begin     The begin of the read socket.
@param  read_size Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
API CH1* SocketCopy(void* begin, SIW size, const void* read, SIW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin The begin of the write socket.
@param  stop   The stop of the write socket.
@param  begin The begin of the read socket.
@param  size      Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
API inline CH1* SocketCopy(void* start, void* stop, const void* begin,
                           SIW read_size);

/* Copies the source to the target functionally identical to memcpy.
    @param  begin The begin of the write socket.
    @param  stop   The stop of the write socket.
    @param  begin The begin of the read socket.
    @param  stop  The stop of the read socket.
    @return Pointer to the last UI1 written or nil upon failure. */
API inline CH1* SocketCopy(void* start, void* stop, const void* begin,
                           const void* end);

/* Compares the two memory sockets.
    @param  begin_a The beginning of Socket A.
    @param  end_a   The stop of Socket A.
    @param  begin_b The begin of Socket B.
    @param  stop_b  The stop of Socket B.
    @return True if they are the same and false if they are not. */
API BOL SocketCompare(const void* start, const void* stop, const void* begin,
                      const void* end);

/* Compares the two memory sockets.
@param  begin_a The beginning of Socket A.
@param  end_a   The stop of Socket A.
@param  begin_a The begin of Socket B.
@param  size_b  The size of Socket B.
@return True if they are the same and false if they are not. */
API inline BOL SocketCompare(const void* begin_a, void* end_a,
                             const void* begin_b, SIW read_size);

/* Compares the two memory sockets.
@param  begin_a The beginning of socket a.
@param  size_a  The size of Socket A .
@param  begin_a The begin of socket b.
@param  size_b  The size of Socket B.
@return True if they are the same and false if they are not. */
API inline BOL SocketCompare(const void* begin_a, SIW size_a,
                             const void* begin_b, SIW size_b);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param  begin The begin UI1.
@param  stop   The stop UI1.
@param  count The UI1 count to shift up. */
SIW SocketShiftUp(void* begin, void* stop, SIW count);

}  // namespace _

#endif  //< INCLUDED_SCRIPTKABUKI_SOCKET
#endif  //< #if SEAM >= _0_0_0__02
