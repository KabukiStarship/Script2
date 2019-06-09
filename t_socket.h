/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_socket.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_SOCKET
#ifndef SCRIPT2_KABUKI_TSOCKET
#define SCRIPT2_KABUKI_TSOCKET

#include "c_socket.h"

namespace _ {

/* @ingroup Socket */

enum {
  kStack = 0,  //< Flag for using stack memory.
  kHeap = 1,   //< Flag for using heap memory.
};

/* Returns the N in 2^N for the sizeof (I) to speed up dividing by powers of 2.
@code
SIN size_bytes = 32;
SIN size_words = size_bytes >> TBitShiftCount<SIN> ()
@endcode
*/
template <typename I = SIW>
inline SI4 TBitShiftCount() {
  return (sizeof(I) == 1)
             ? 0
             : (sizeof(I) == 2)
                   ? 1
                   : (sizeof(I) == 4)
                         ? 2
                         : (sizeof(I) == 8) ? 3 : (sizeof(I) == 16) ? 4 : 0;
}

template <typename SIZ, SIZ kSize_>
constexpr SIZ TSizeWords() {
  SIZ align_offset = (-kSize) & (sizeof(SIW) - 1);
  SIZ size_aligned = kSize_ + align_offset;
  return size_aligned >> TBitShiftCount<SIZ>();
}

template <typename SIZ>
inline SIZ TSizeWords(SIZ size) {
  SIZ align_offset = (-size) & (sizeof(SIW) - 1);
  SIZ size_aligned = size + align_offset;
  return size_aligned >> TBitShiftCount<SIZ>();
}

/* Converts the given size into CPU word count. */
template <typename SIZ, SIZ kHeaderSize = sizeof(SIW)>
inline SIZ TWordCount(SIZ size) {
  // SIZ align_offset = (-size) & (kHeaderSize - 1); // Why did I do this???
  // SIZ size_aligned = size + align_offset;
  return size >> TBitShiftCount<SIW>();
}

/* Aligns the given pointer up to a sizeof (T) boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask).
@desc Algorithm works by inverting the bits, mask of the LSbs and adding 1.
This allows the algorithm to word align without any if statements. The
algorithm works the same for all memory widths as proven by the truth
tables bellow.

@code
// The convention KT uses is that the unsigned size always comes first
// because it's the first UI1 of an ASCII AArray.
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
// 8-bit example:
// value + ((~value) + 1) & (sizeof (SI1) - 1) = value
@endcode */
template <typename I = UIW>
inline I TAlignUpOffset(I value, I mask = sizeof(I) * 8 - 1) {
  return Negative(value) & mask;
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename UI = CH1>
inline UI TAlignUpUnsigned(UI value, UI mask = kWordLSbMask) {
  return value + TAlignUpOffset<UI>(value, mask);
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename SI = CH1>
inline SI TAlignUpSigned(SI value, SI mask = kWordLSbMask) {
  return value + TAlignUpOffset<SI>(value, mask);
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CH1>
inline T* TAlignUp(void* pointer, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(value + TAlignUpOffset<>((UIW)pointer, mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CH1>
inline T* TAlignUp(const void* pointer, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(value + TAlignUpOffset<>((UIW)pointer, mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = UIW>
inline T TAlignDown(void* ptr, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<T>(value - (value & mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = UIW>
inline T TAlignDown(const void* ptr, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<const T>(value - (value & mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename I = UIW>
inline I TAlignDownI(I value, I mask = (I)kWordLSbMask) {
  return value & (~mask);
}

/* Calculates the offset to align the given pointer to a 16-bit word boundary.
@return The aligned value.
@param  pointer The value to align. */
template <typename T = CH1>
inline T* TAlignUp2(void* pointer) {
  // Mask off lower bit and add it to the ptr.
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(ptr + (ptr & 0x1));
}

/* Calculates the offset to align the given pointer to a 16-bit word boundary.
@return A TMatrix you add to a pointer to align it. */
template <typename T = CH1>
inline T* TAlignUp2(const void* pointer) {
  // Mask off lower bit and add it to the ptr.
  UIW ptr = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<T*>(ptr + (ptr & 0x1));
}

/* Aligns the given size to a word-sized boundary. */
template <typename SIZ>
constexpr SIZ SizeAlign(SIZ size) {
  SIZ lsb_mask = sizeof(UIW) - 1;
  if (size < sizeof(UIW)) return sizeof(UIW);
  SIZ size_max = ~lsb_mask;
  if (size > size_max) return size;
  return size + (-size) & lsb_mask;
}

/* A contiguous memory socket of kSize_ elements of T including a Header. */
template <SIW kSize_ = kCpuCacheLineSize, typename T = UI1,
          typename Class = Nil>
class TSocket {
 public:
  /* Default destructor does nothing. */
  TSocket() {}

  /* The size in elements. */
  static constexpr SIW Size() {
    if (kSize_ < sizeof(Class)) return sizeof(Class);
    return kSize_;
  }

  /* The size in bytes including the header. */
  static constexpr SIW SizeBytes() {
    SIW size = Size() * sizeof(T) + sizeof(Class),
        size_aligned = size + (-size & (sizeof(SIW) - 1));
    return size_aligned / (SIW)sizeof(SIW);
  }

  /* The size in words rounded down. */
  static constexpr SIW SizeWords() {
    SIW size = Size() * sizeof(T) + sizeof(Class),
        size_aligned = size + (-size & (sizeof(SIW) - 1));
    return size_aligned / (SIW)sizeof(SIW);
  }

  /* Returns the socket as a UIW*. */
  inline UIW* Buffer() { return socket_; }

  /* Gets the begin UI1 of the socket. */
  inline UIW* BufferEnd() { return &socket_[SizeWords()]; }

  /* Gets the begin element of the socket. */
  template <typename T = CH1>
  inline T* Begin() {
    return reinterpret_cast<T*>(socket_);
  }

  /* Gets the end element of the socket. */
  inline T* End() { return Begin() + kSize_; }

  /* Returns the first element of the ASCII Object data section. */
  template <typename T>
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(socket_);
    return reinterpret_cast<T*>(ptr + sizeof(Class));
  }

  /* Returns the last element of the ASCII Object data section. */
  template <typename T, UIW kHeaderSize_>
  inline T* Stop() {
    return Start<SIW, T>() + index - 1;
  }

  /* Gets the begin of the socket. */
  template <typename T = CH1, typename I = SIW>
  inline T* Element(I index) {
    if (!InRange(index)) return nullptr;
    return Start()[index];
  }

  /* Sets the size to the new value. */
  template <typename SIW>
  inline UIW* SetSize(SIW size) {
    ASSERT((size & kAlignMask) == 0)
    *reinterpret_cast<SIW*>(socket_) = size;
    return socket_;
  }

 private:
  UIW socket_[SizeWords()];  //< The word-aligned socket.
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
@param  base The base address.
@param  offset The offset. */
template <typename T>
inline T* TPtr(const void* begin, SIW offset) {
  return reinterpret_cast<T*>(reinterpret_cast<UIW>(begin) + offset);
}

}  // namespace _

#endif
#endif
