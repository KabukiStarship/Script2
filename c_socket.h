/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/c_socket.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_SOCKET

#ifndef INCLUDED_SCRIPTKABUKI_SOCKET
#define INCLUDED_SCRIPTKABUKI_SOCKET

namespace _ {

/* Aligns the given pointer down to the given mask. */
LIB_MEMBER CH1* AlignDown(CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
LIB_MEMBER const CH1* AlignDown(const CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
LIB_MEMBER UIW* AlignDown(UIW* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
LIB_MEMBER const UIW* AlignDown(const UIW* pointer, UIW mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
LIB_MEMBER LIB_INLINE SI1 AlignDown(SI1 value, SI1 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
LIB_MEMBER LIB_INLINE SI2 AlignDown(SI2 value, SI2 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
LIB_MEMBER LIB_INLINE SI4 AlignDown(SI4 value, SI4 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
LIB_MEMBER LIB_INLINE SI8 AlignDown(SI8 value, SI8 mask = kWordLSbMask);

/* Aligns the given pointer up to the given mask. */
LIB_MEMBER const CH1* AlignUp(const CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given socket pointer up to a cache line boundary (64 bytes). */
LIB_MEMBER LIB_INLINE UIW* AlignUp(UIW* socket, UIW mask = kWordLSbMask);

/* Aligns the given pointer up to the given mask. */
LIB_MEMBER CH1* AlignUp(CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given value up to an 8-UI1 boundary. */
LIB_MEMBER LIB_INLINE UI1 AlignUp(UI1 value, UI1 mask = kWordLSbMask);

/* Aligns the given value up to an 8-UI1 boundary. */
LIB_MEMBER LIB_INLINE SI1 AlignUp(SI1 value, SI1 mask = kWordLSbMask);

/* Aligns the given value up to an 16-UI1 boundary. */
LIB_MEMBER UI2 AlignUp(UI2 value, UI2 mask = kWordLSbMask);

/* Aligns the given value up to an 16-UI1 boundary. */
LIB_MEMBER SI2 AlignUp(SI2 value, SI2 mask = kWordLSbMask);

/* Aligns the given value up to an 32-UI1 boundary. */
LIB_MEMBER LIB_INLINE UI4 AlignUp(UI4 value, UI4 mask = kWordLSbMask);

/* Aligns the given value up to an 32-UI1 boundary. */
LIB_MEMBER LIB_INLINE SI4 AlignUp(SI4 value, SI4 mask = kWordLSbMask);

/* Aligns the given value up to an 64-UI1 boundary. */
LIB_MEMBER LIB_INLINE UI8 AlignUp(UI8 value, UI8 mask = kWordLSbMask);

/* Aligns the given value up to an 64-UI1 boundary. */
LIB_MEMBER LIB_INLINE SI8 AlignUp(SI8 value, SI8 mask = kWordLSbMask);

/* Gets the next address that a data type may be stored at. */
LIB_MEMBER const void* TypeAlign(SIW type, const void* value);

/* Gets the next address that a data type may be stored at. */
LIB_MEMBER void* TypeAlign(SIW type, void* value);

/* A managed general purpose (i.e. not just for networking) memory socket.
A socket is just a hole in something for fitting something in, like a light
or electric socket. A socket of memory is just a block of memory you fit
something in. A network socket is a socket for interprocess communication,
which is usually implemented with a ring socket
(@see ~/kabuki-toolkit/slot.h).
*/
class Socket {
 public:
  CH1 *begin,  //< Beginning of the socket.
      *end;    //< End of the socket.

  /* Constructs an uninitialized socket. */
  Socket();

  /* Constructor. */
  Socket(void* begin, void* stop);

  /* Constructor. */
  Socket(void* begin, SIW size);

  /* Clones the other memory. */
  Socket(const Socket& other);

  /* Gets the size of the socket. */
  SIW Size();

  /* C++ operator= overload. */
  Socket& operator=(const Socket& other);
};

class Nil {
 public:
  /* Constructures nothing. */
  Nil();

  /* Gets the size of the socket. */
  static constexpr SIW Size();

  /* Gets the nil begin word address. */
  UIW* Buffer();
};

/* Converts the pointer to a std::UIW. */
LIB_MEMBER LIB_INLINE UIW UIntPtr(const void* value);

/* Converts the std::UIW to a pointer. */
LIB_MEMBER LIB_INLINE void* VoidPtr(UIW value);

/* Converts the std::UIW to a pointer. */
LIB_MEMBER LIB_INLINE const void* ConstVoidPtr(UIW value);

/* Calculates the difference between the begin and stop address. */
LIB_MEMBER LIB_INLINE SIW SizeOf(const void* begin, const void* stop);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CH1* SocketFill(void* begin, void* end, CH1 fill_char);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CH1* SocketFill(void* begin, SIW size, CH1 fill_char);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CH1* SocketWipe(void* begin, void* end);

/* Overwrites the memory with fill_char; functionally identical to memset. */
LIB_MEMBER CH1* SocketWipe(void* begin, SIW size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin     The start of the write socket.
@param  size      The stop of the write socket.
@param  begin     The begin of the read socket.
@param  read_size Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
LIB_MEMBER CH1* SocketCopy(void* begin, SIW size, const void* read,
                           SIW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  size  Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
LIB_MEMBER CH1* SocketCopy(void* start, void* stop, const void* begin,
                           SIW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  start The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  end   The end of the read socket.
@return Pointer to the last UI1 written or nil upon failure. */
LIB_MEMBER LIB_INLINE CH1* SocketCopy(void* start, void* stop,
                                      const void* begin, const void* end);

/* Compares the two memory sockets.
@param  start  The start of Socket A.
@param  stop   The stop of Socket A.
@param  begin  The begin of Socket B.
@param  end    The end of Socket B.
@return True if they are the same and false if they are not. */
LIB_MEMBER BOL SocketCompare(const void* start, const void* stop,
                             const void* begin, const void* end);

/* Compares the two memory sockets.
@param  start The start of Socket A.
@param  stop  The stop of Socket A.
@param  begin The begin of Socket B.
@param  size  The size of Socket B.
@return True if they are the same and false if they are not. */
LIB_MEMBER LIB_INLINE BOL SocketCompare(const void* start, void* stop,
                                        const void* begin, SIW size);

/* Compares the two memory sockets.
@param  start The start of socket a.
@param  size_a The size of Socket A .
@param  start  The begin of socket b.
@param  size_b The size of Socket B.
@return True if they are the same and false if they are not. */
LIB_MEMBER LIB_INLINE BOL SocketCompare(const void* start, SIW size_a,
                                        const void* begin, SIW size_b);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param  begin       The begin UI1.
@param  end         The end UI1.
@param  count_bytes The UI1 count to shift up. */
SIW SocketShiftUp(void* begin, void* end, SIW count_bytes);

/* Shifts the memory down by the given bytes_count.
@return 0 upon failure and count upon success.
@param  begin       The start UI1.
@param  end         The end UI1.
@param  count_bytes The UI1 count to shift up. */
SIW SocketShiftDown(void* begin, void* end, SIW bytes_count);

}  // namespace _

#endif
#endif
