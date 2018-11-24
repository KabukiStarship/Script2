/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tsocket.h
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
#ifndef INCLUDED_SCRIPT_KABUKI_TSOCKET
#define INCLUDED_SCRIPT_KABUKI_TSOCKET

#include "csocket.h"

#include "cbinary.h"

namespace _ {

/* @group Socket */

/* Aligns the given pointer up to a sizeof (T) boundary.
@return The aligned value.
@param  ptr The address to align.
@desc Algorithm works by inverting the bits, mask of the LSbs and adding 1.
This allows the algorithm to word align without any if statements. The
algorithm works the same for all memory widths as proven by the truth
tables bellow.

@code
// The convention KT uses is that the unsigned size always comes first
// because it's the first UI1 of an ASCII Obj.
SI4 signed_example = 7;
signed_example = AlignUp<SI8, UI4, SI4> (signed_example);

UI2 unsigned_example = 3;
unsgiend_example = AlignUp<SI4, UI2, UI2> (unsigned_example);

// 64-bit alignment example:
// ~000 = 111 => 000 + 111 + 1 = 0x1000
// ~001 = 110 => 001 + 110 + 1 = 0x1000
// ~010 = 101 => 010 + 101 + 1 = 0x1000
// ~011 = 100 => 011 + 100 + 1 = 0x1000
// ~100 = 011 => 100 + 011 + 1 = 0x1000
// ~101 = 010 => 101 + 010 + 1 = 0x1000
// ~110 = 001 => 110 + 001 + 1 = 0x1000
// ~111 = 000 => 111 + 000 + 1 = 0x1000
// 32-bit alignment example:
// ~00 = 11 => 00 + 11 + 1 = 0x100
// ~01 = 10 => 01 + 10 + 1 = 0x100
// ~10 = 01 => 10 + 01 + 1 = 0x100
// ~11 = 00 => 11 + 00 + 1 = 0x100
// 16-bit alignment example:
// ~0 = 1 => 0 + 1 = 1
// ~1 = 0 => 1 + 0 = 0
// //
// 8-bit example:
// value + ((~value) + 1) & (sizeof (SI1) - 1) = value
@endcode */
template <typename I = UIW>
inline I TAlignUpOffset(I value, I mask = sizeof(I) * 8 - 1) {
  return 0;  // Negative (value) & mask;
}

/* Aligns the given pointer to a power of two boundary.
@warning Function does not check if the boundary is a power of 2! */
template <typename UI = char>
inline UI TAlignUpUnsigned(UI value, UI mask = kWordBitsMask) {
  return value + TAlignUpOffset<UI>(value, mask);
}

/* Aligns the given pointer to a power of two boundary.
@warning Function does not check if the boundary is a power of 2! */
template <typename SI = char>
inline SI TAlignUpSigned(SI value, SI mask = kWordBitsMask) {
  return value + TAlignUpOffset<SI>(value, mask);
}

/* Aligns the given pointer to a power of two boundary.
@warning Function does not check if the boundary is a power of 2! */
template <typename T = char>
inline T* TAlignUp(void* pointer, UIW mask = kWordBitsMask) {
  UIW value = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(value + TAlignUpOffset<>((UIW)pointer, mask));
}

/* Aligns the given pointer to a power of two boundary.
@warning Function does not check if the boundary is a power of 2! */
template <typename T = char>
inline T* TAlignUp(const void* pointer, UIW mask = kWordBitsMask) {
  UIW value = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(value + TAlignUpOffset<>((UIW)pointer, mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@param  value The value to align.
@return The aligned value. */
template <typename I = UIW>
inline I TAlignDownOffset(I value, I mask = kWordBitsMask) {
  return value & mask;
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@param  value The value to align.
@return The aligned value. */
template <typename T = UIW>
inline T TAlignDown(void* ptr, UIW mask = kWordBitsMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<T>(value - TAlignDownOffset<>(value, mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@param  value The value to align.
@return The aligned value. */
template <typename T = UIW>
inline T TAlignDown(const void* ptr, UIW mask = kWordBitsMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<const T>(value - TAlignDownOffset<>(value, mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@param  value The value to align.
@return The aligned value. */
template <typename I = UIW>
inline I TAlignDownI(I value, I mask = kWordBitsMask) {
  return value - (value & mask);
}

/* Calculates the offset to align the given pointer to a 16-bit word boundary.
@return A vector you add to a pointer to align it. */
template <typename T = char>
inline T* TAlignUp2(void* pointer) {
  // Mask off lower bit and add it to the ptr.
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(ptr + (ptr & 0x1));
}

/* Calculates the offset to align the given pointer to a 16-bit word boundary.
@return A vector you add to a pointer to align it. */
template <typename T = char>
inline T* TAlignUp2(const void* pointer) {
  // Mask off lower bit and add it to the ptr.
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(ptr + (ptr & 0x1));
}

/* Returns the N in 2^N for the sizeof (I). */
template <typename I>
inline int TBitShiftCount() {
  return (sizeof(I) == 1)
             ? 0
             : (sizeof(I) == 2)
                   ? 1
                   : (sizeof(I) == 4)
                         ? 2
                         : (sizeof(I) == 8) ? 3 : (sizeof(I) == 16) ? 4 : 0;
}

template <typename Size>
constexpr Size SizeAlign(Size size) {
  Size lsb_mask = sizeof(UIW) - 1;
  if (size < sizeof(UIW)) return sizeof(UIW);
  Size size_max = ~lsb_mask;
  if (size > size_max) return size;
  return size + (-size) & lsb_mask;
}

/* A memory socket. */
template <typename Size, Size kSize_>
class TSocket {
 public:
  /* Default destructor does nothing. */
  TSocket() {}

  /* The size in bytes. */
  static constexpr Size SizeBytes() {
    Size lsb_mask = sizeof(UIW) - 1;
    if (kSize_ < sizeof(UIW)) return sizeof(UIW);
    Size size_max = ~lsb_mask;
    if (kSize_ > size_max) return size_max;
    return kSize_ + (-kSize_) & lsb_mask;
  }

  /* Returns the socket as a UIW*. */
  inline UIW* Words() { return socket; }

  /* Gets the start UI1 of the socket. */
  inline char* Begin() { return reinterpret_cast<char*>(socket); }

  /* Gets the start begin of the socket. */
  template <typename T = char, typename I = size_t>
  inline char* Begin(I offset) {
    UIW address = reinterpret_cast<UIW>(socket) + offset;
    return reinterpret_cast<T>(address);
  }

  /* Gets the start UI1 of the socket. */
  inline char* End() { return reinterpret_cast<char*>(socket) + kSize_; }

  /* Returns the first byte of the ASCII Object data. */
  template <typename T>
  inline T* Start() {
    return reinterpret_cast<T*>(socket);
  }

  /* Sets the size to the new value. */
  template <typename Size>
  inline UIW* SetSize(Size size) {
    ASSERT((size & kAlignMask) == 0)
    *reinterpret_cast<Size*>(socket) = size;
    return socket;
  }

 private:
  UIW socket[SizeBytes()];  //< The word-aligned socket.
};

/* Syntactical sugar for reinterpret_cast using templates. */
template <typename T>
inline T* TPtr(void* ptr) {
  return reinterpret_cast<T*>(ptr);
}

/* Syntactical sugar for reinterpret_cast using templates. */
template <typename T>
inline T* TPtr(const void* ptr) {
  return reinterpret_cast<T*>(ptr);
}

/* Utility function for syntactical sugar creating a pointer from a base plus
offset.
@return Pointer of the type specified by template parameter T.
@param base The base address.
@param offset The offset. */
template <typename T>
inline T* TPtr(const void* start, SIW offset) {
  return reinterpret_cast<T*>(reinterpret_cast<UIW>(start) + offset);
}

/* Creates a new socket of the given size or deletes it. */
template <typename Size = SI4>
UIW* TNew(UIW* socket, SIW size) {
  size = AlignUp(size);
  return new UIW[size >> kWordBitCount];
}

}  // namespace _

#endif  //< INCLUDED_SCRIPT_KABUKI_TSOCKET
#endif  //< #if SEAM >= _0_0_0__02
