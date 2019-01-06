/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tsocket.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
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
#ifndef SCRIPT2_KABUKI_TSOCKET
#define SCRIPT2_KABUKI_TSOCKET

#include "csocket.h"

#include "cbinary.h"

namespace _ {

/* @ingroup Socket */

enum {
  kStack = 0,  //< Flag for using stack memory.
  kHeap = 1,   //< Flag for using heap memory.
};

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
// because it's the first UI1 of an ASCII CObject.
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
template <typename I = UIW>
inline I TAlignDownOffset(I value, I mask = kWordLSbMask) {
  return value & mask;
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = UIW>
inline T TAlignDown(void* ptr, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<T>(value - TAlignDownOffset<>(value, mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = UIW>
inline T TAlignDown(const void* ptr, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<const T>(value - TAlignDownOffset<>(value, mask));
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
@return A vector you add to a pointer to align it. */
template <typename T = CH1>
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

/* Aligns the given size to a word-sized boundary. */
template <typename Size>
constexpr Size SizeAlign(Size size) {
  Size lsb_mask = sizeof(UIW) - 1;
  if (size < sizeof(UIW)) return sizeof(UIW);
  Size size_max = ~lsb_mask;
  if (size > size_max) return size;
  return size + (-size) & lsb_mask;
}

/* A contiguous memory socket. */
template <typename Size, Size kSize_>
class TSocket {
 public:
  /* Default destructor does nothing. */
  TSocket() {}

  /* The size of the Size type. */
  static constexpr Size SizeSize() { return (Size)sizeof(Size); }

  /* The min size in bytes. */
  static constexpr Size SizeMin() { return SizeSize(); }

  /* The size in bytes. */
  static constexpr Size SizeBytes() {
    // static_assert(kSize_ >= SizeMin(), "kSize_ < SizeMin ()");
    if (kSize_ < SizeMin()) return SizeMin();
    return kSize_;
  }

  /* The size in words rounded down. */
  static constexpr UIW SizeWords() {
    UIW size_words = (UIW)(SizeBytes() / (Size)sizeof(UIW));
    return (size_words <= 0) ? 1 : size_words;
  }

  /* Returns the socket as a UIW*. */
  inline UIW* Words() { return socket_; }

  /* Gets the begin UI1 of the socket. */
  template <typename T = UIW>
  inline T* Begin() {
    return reinterpret_cast<T*>(socket_);
  }

  /* Gets the begin UI1 of the socket. */
  inline CH1* End() { return reinterpret_cast<CH1*>(socket_) + kSize_; }

  /* Returns the first byte of the ASCII Object. */
  template <typename Size, typename T>
  inline T* Start() {
    UIW ptr = reinterpret_cast<UIW>(socket_);
    return reinterpret_cast<T*>(ptr + sizeof(Size));
  }

  /* Gets the begin of the socket. */
  template <typename T = CH1, typename I = Size>
  inline T* Element(I index) {
    if (!InRange(index)) return nullptr;
    return Start()[index];
  }

  /* Sets the size to the new value. */
  template <typename Size>
  inline UIW* SetSize(Size size) {
    ASSERT((size & kAlignMask) == 0)
    *reinterpret_cast<Size*>(socket_) = size;
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
@param base The base address.
@param offset The offset. */
template <typename T>
inline T* TPtr(const void* begin, SIW offset) {
  return reinterpret_cast<T*>(reinterpret_cast<UIW>(begin) + offset);
}

/* Creates a new socket of the given size or deletes it. */
template <typename Size = SI4>
UIW* TNew(SIW size) {
  size = AlignUp(size);
  return new UIW[size >> kWordBitCount];
}

}  // namespace _

#endif  //< SCRIPT2_KABUKI_TSOCKET
#endif  //< #if SEAM >= _0_0_0__02
