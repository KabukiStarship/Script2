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

#if SEAM >= SCRIPT2_SEAM_SOCKET

#ifndef INCLUDED_SCRIPTKABUKI_SOCKET
#define INCLUDED_SCRIPTKABUKI_SOCKET

namespace _ {

/* Utility function multiplies the given value by -1. */
UI1 Negative(SI1 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI1 Negative(UI1 value);

/* Utility function multiplies the given value by -1. */
UI2 Negative(SI2 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI2 Negative(UI2 value);

/* Utility function multiplies the given value by -1. */
UI4 Negative(SI4 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI4 Negative(UI4 value);

/* Utility function multiplies the given value by -1. */
UI8 Negative(SI8 value);

/* Utility function inverts the bits and adds one (i.e. multiplies by -1). */
UI8 Negative(UI8 value);

/* Aligns the given pointer down to the given mask. */
SDK CH1* AlignDown(CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
SDK const CH1* AlignDown(const CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
SDK UIW* AlignDown(UIW* pointer, UIW mask = kWordLSbMask);

/* Aligns the given pointer down to the given mask. */
SDK const UIW* AlignDown(const UIW* pointer, UIW mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
SDK /*inline*/ SI1 AlignDown(SI1 value, SI1 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
SDK /*inline*/ SI2 AlignDown(SI2 value, SI2 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
SDK /*inline*/ SI4 AlignDown(SI4 value, SI4 mask = kWordLSbMask);

/* Aligns the given value down to the given mask. */
SDK /*inline*/ SI8 AlignDown(SI8 value, SI8 mask = kWordLSbMask);

/* Aligns the given pointer up to the given mask. */
SDK const CH1* AlignUp(const CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given socket pointer up to a cache line boundary (64 bytes). */
SDK /*inline*/ UIW* AlignUp(UIW* socket, UIW mask = kWordLSbMask);

/* Aligns the given pointer up to the given mask. */
SDK CH1* AlignUp(CH1* pointer, UIW mask = kWordLSbMask);

/* Aligns the given value up to an 8-UI1 boundary. */
SDK /*inline*/ UI1 AlignUp(UI1 value, UI1 mask = kWordLSbMask);

/* Aligns the given value up to an 8-UI1 boundary. */
SDK /*inline*/ SI1 AlignUp(SI1 value, SI1 mask = kWordLSbMask);

/* Aligns the given value up to an 16-UI1 boundary. */
SDK UI2 AlignUp(UI2 value, UI2 mask = kWordLSbMask);

/* Aligns the given value up to an 16-UI1 boundary. */
SDK SI2 AlignUp(SI2 value, SI2 mask = kWordLSbMask);

/* Aligns the given value up to an 32-UI1 boundary. */
SDK /*inline*/ UI4 AlignUp(UI4 value, UI4 mask = kWordLSbMask);

/* Aligns the given value up to an 32-UI1 boundary. */
SDK /*inline*/ SI4 AlignUp(SI4 value, SI4 mask = kWordLSbMask);

/* Aligns the given value up to an 64-UI1 boundary. */
SDK /*inline*/ UI8 AlignUp(UI8 value, UI8 mask = kWordLSbMask);

/* Aligns the given value up to an 64-UI1 boundary. */
SDK /*inline*/ SI8 AlignUp(SI8 value, SI8 mask = kWordLSbMask);

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

/* Creates a block of dynamic memory. */
SDK /*inline*/ UIW* New(SIW size, SIW size_header = 0);

/* AsciiFactory deletes the socket. */
SDK /*inline*/ void Delete(UIW* socket, BOL using_heap = true);

/* Converts the pointer to a std::UIW. */
SDK /*inline*/ UIW UIntPtr(const void* value);

/* Converts the std::UIW to a pointer. */
SDK /*inline*/ void* VoidPtr(UIW value);

/* Converts the std::UIW to a pointer. */
SDK /*inline*/ const void* ConstVoidPtr(UIW value);

/* Calculates the difference between the begin and stop address. */
SDK /*inline*/ SIW SizeOf(const void* begin, const void* stop);

/* Overwrites the memory with fill_char; functionally identical to memset. */
SDK CH1* SocketFill(void* begin, void* end, CH1 fill_char);

/* Overwrites the memory with fill_char; functionally identical to memset. */
SDK CH1* SocketFill(void* begin, SIW size, CH1 fill_char);

/* Overwrites the memory with fill_char; functionally identical to memset. */
SDK CH1* SocketWipe(void* begin, void* end);

/* Overwrites the memory with fill_char; functionally identical to memset. */
SDK CH1* SocketWipe(void* begin, SIW size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin     The start of the write socket.
@param  size      The stop of the write socket.
@param  begin     The begin of the read socket.
@param  read_size Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
SDK CH1* SocketCopy(void* begin, SIW size, const void* read, SIW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  begin The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  size  Number of bytes to copy.
@return Pointer to the last UI1 written or nil upon failure. */
SDK CH1* SocketCopy(void* start, void* stop, const void* begin, SIW read_size);

/* Copies the source to the target functionally identical to memcpy.
@param  start The start of the write socket.
@param  stop  The stop of the write socket.
@param  begin The begin of the read socket.
@param  end   The end of the read socket.
@return Pointer to the last UI1 written or nil upon failure. */
SDK /*inline*/ CH1* SocketCopy(void* start, void* stop, const void* begin,
                               const void* end);

/* Compares the two memory sockets.
@param  start  The start of Socket A.
@param  stop   The stop of Socket A.
@param  begin  The begin of Socket B.
@param  end    The end of Socket B.
@return True if they are the same and false if they are not. */
SDK BOL SocketCompare(const void* start, const void* stop, const void* begin,
                      const void* end);

/* Compares the two memory sockets.
@param  start The start of Socket A.
@param  stop  The stop of Socket A.
@param  begin The begin of Socket B.
@param  size  The size of Socket B.
@return True if they are the same and false if they are not. */
SDK /*inline*/ BOL SocketCompare(const void* start, void* stop,
                                 const void* begin, SIW size);

/* Compares the two memory sockets.
@param  start The start of socket a.
@param  size_a The size of Socket A .
@param  start  The begin of socket b.
@param  size_b The size of Socket B.
@return True if they are the same and false if they are not. */
SDK /*inline*/ BOL SocketCompare(const void* start, SIW size_a,
                                 const void* begin, SIW size_b);

/* Shifts the memory up by the given count in bytes.
@return 0 upon failure and count upon success.
@param  start The start UI1.
@param  stop   The stop UI1.
@param  count The UI1 count to shift up. */
SIW SocketShiftUp(void* start, void* stop, SIW count);

}  // namespace _

#endif
#endif
