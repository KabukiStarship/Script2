/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_socket.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SOCKET
#ifndef SCRIPT2_KABUKI_TSOCKET
#define SCRIPT2_KABUKI_TSOCKET

#include "c_cout.h"
#include "c_socket.h"

namespace _ {

/* @ingroup Socket */

/* Returns the maximum value of the given unsigned type. */
template <typename UI>
inline UI TNaNUnsigned() {
  return ~((UI)0);
}

/* Returns the maximum value of the given signed type. */
template <typename SIZ>
constexpr SIZ TNaNSigned() {
  return (~ToUnsigned(SIZ)) >> 1;
}

template <typename SI = SIW>
inline SI TDelta(const void* begin, const void* end) {
  SIW delta = reinterpret_cast<SIW>(end) - reinterpret_cast<SIW>(begin);
  return (SI)delta;
}

enum {
  kStack = 0,  //< Flag for using stack memory.
  kHeap = 1,   //< Flag for using heap memory.
};

/* Returns the N in 2^N for the sizeof (I) to speed up dividing by powers of 2.
@code
SIN size_bytes = 32;
SIN size_words = size_bytes >> TBitCount<SIN> ()
@endcode
*/
template <typename SIZ = SIW>
inline SI4 TBitCount() {
  return (sizeof(SIZ) == 1)
             ? 0
             : (sizeof(SIZ) == 2)
                   ? 1
                   : (sizeof(SIZ) == 4)
                         ? 2
                         : (sizeof(SIZ) == 8) ? 3 : (sizeof(SIZ) == 16) ? 4 : 0;
}

/* Aligns the given value up to a sizeof (T) boundary.
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

inline SI1 AlignUp(SI1 value, SI1 align_mask) {
  return value + ((-value) & align_mask);
}
inline UI1 AlignUp(UI1 value, UI1 align_mask) {
  return UI1(AlignUp(SI1(value), SI1(align_mask)));
}

inline SI2 AlignUp(SI2 value, SI2 align_mask) {
  return value + ((-value) & align_mask);
}
inline UI2 AlignUp(UI2 value, UI2 align_mask) {
  return value + (UI2(-SI2(value)) & align_mask);
}

inline SI4 AlignUp(SI4 value, SI4 align_mask) {
  return value + ((-value) & align_mask);
}
inline UI4 AlignUp(UI4 value, UI4 align_mask) {
  return value + (UI4(-SI4(value)) & align_mask);
}

inline SI8 AlignUp(SI8 value, SI8 align_mask) {
  return value + ((-value) & align_mask);
}
inline UI8 AlignUp(UI8 value, UI8 align_mask) {
  return value + (UI8(-SI8(value)) & align_mask);
}

inline void* AlignUp(void* pointer, UIW mask = kWordLSbMask) {
  UIW address = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<void*>(AlignUp(address, mask));
}
inline const void* AlignUp(const void* pointer, UIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<void*>(AlignUp(value, mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CH1>
inline T* TAlignUp(void* pointer, SIW mask = kWordLSbMask) {
  SIW value = reinterpret_cast<SIW>(pointer);
  return reinterpret_cast<T*>(value + ((-value) & mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CH1>
inline T* TAlignUp(const void* pointer, SIW mask = kWordLSbMask) {
  SIW value = reinterpret_cast<SIW>(pointer);
  return reinterpret_cast<T*>(value + ((-value) & mask));
}

/* Aligns th given value down to the given word goundary. */
template <SI1 kValue_, SI1 kAlignMask_ = kWordLSbMask>
constexpr SI1 TAlignDown() {
  return kValue_ - (kValue_ & kAlignMask_);
}
template <UI1 kValue_, UI1 kAlignMask_ = kWordLSbMask>
constexpr UI1 TAlignDown() {
  return kValue_ + (kValue_ & kAlignMask_);
}
inline SI1 AlignDown(SI1 value, SI1 align_mask) {
  return value + (value & align_mask);
}
inline UI1 AlignDown(UI1 value, UI1 align_mask) {
  return UI1(AlignDown(SI1(value), SI1(align_mask)));
}

template <SI2 kValue_, SI2 kAlignMask_ = kWordLSbMask>
constexpr SI2 TAlignDown() {
  return kValue_ + (kValue_ & kAlignMask_);
}
template <UI2 kValue_, UI2 kAlignMask_ = kWordLSbMask>
constexpr UI2 TAlignDown() {
  return kValue_ + (kValue_ & kAlignMask_);
}
inline SI2 AlignDown(SI2 value, SI2 align_mask) {
  return value - (value & align_mask);
}
inline UI2 AlignDown(UI2 value, UI2 align_mask) {
  return value - (value & align_mask);
}

template <SI4 kValue_, SI4 kAlignMask_ = kWordLSbMask>
constexpr SI4 TAlignDown() {
  return kValue_ - (kValue_ & kAlignMask_);
}
template <UI4 kValue_, UI4 kAlignMask_ = kWordLSbMask>
constexpr UI4 TAlignDown() {
  return kValue_ + (kValue_ & kAlignMask_);
}
inline SI4 AlignDown(SI4 value, SI4 align_mask) {
  return value + (value & align_mask);
}
inline UI4 AlignDown(UI4 value, UI4 align_mask) {
  return value - (value & align_mask);
}

template <SI8 kValue_, SI8 kAlignMask_ = kWordLSbMask>
constexpr SI8 TAlignDown() {
  return kValue_ - (kValue_ & kAlignMask_);
}
template <UI8 kValue_, UI8 kAlignMask_ = kWordLSbMask>
constexpr UI8 TAlignDown() {
  return kValue_ + (kValue_ & kAlignMask_);
}
inline SI8 AlignDown(SI8 value, SI8 align_mask) {
  return value - (value & align_mask);
}
inline UI8 AlignDown(UI8 value, UI8 align_mask) {
  return value - (value & align_mask);
}

template <typename SIZ, SIZ kSize_>
constexpr SIZ TSizeWords() {
  SIZ size_aligned = kSize_ + ((-kSize_) & (sizeof(SIW) - 1));
  size_aligned = size_aligned >> kWordBitCount;
  return (size_aligned < 1) ? 1 : size_aligned;
}

template <typename SIZ, typename SIY>
inline SIZ TSizeWords(SIZ size, SIY align_mask) {
  SIZ size_aligned = size + ((-size) & SIZ(align_mask));
  size_aligned = size_aligned >> kWordBitCount;
  return (size_aligned < 1) ? 1 : size_aligned;
}

template <typename SIZ>
constexpr SIZ CSizeWords(SIZ size) {
  SIZ size_aligned = size + ((-size) & (sizeof(SIW) - 1));
  size_aligned = size_aligned >> kWordBitCount;
  return (size_aligned < 1) ? 1 : size_aligned;
}

/* Converts the given size into CPU word count.
template <typename SIZ = SIW, SIZ kSize_ = 0>
inline SIZ TWordCount() {
  SIZ align_offset = (-kSize_) & (kHeaderSize - 1);  // Why did I do this???
  SIZ size_aligned = kSize_ + align_offset;
  return size_aligned >> TBitCount<SIW>();
} */

/* Converts the given size into CPU word count. */
template <typename SIZ = SIW>
inline SIZ TWordCount(SIZ size) {
  SIZ align_offset = (-size) & (sizeof(SIW) - 1);
  size += align_offset;
  return size >> TBitCount<SIW>();
}

/* Utility function for converting to two's complement and back with templates.
 */
inline SI1 Negative(SI1 value) { return -value; }
inline UI1 Negative(UI1 value) { return UI1(Negative(SI1(value))); }
inline SI2 Negative(SI2 value) { return -value; }
inline UI2 Negative(UI2 value) { return UI2(Negative(SI2(value))); }
inline SI4 Negative(SI4 value) { return -value; }
inline UI4 Negative(UI4 value) { return UI4(Negative(SI4(value))); }
inline SI8 Negative(SI8 value) { return -value; }
inline UI8 Negative(UI8 value) { return UI8(Negative(SI8(value))); }

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
template <typename SIZ = UIW>
inline SIZ TAlignDownI(SIZ value, SIZ mask = (SIZ)kWordLSbMask) {
  return value & (~mask);
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

/* A word-aligned array of kSize_ elements of T on the progam stack. */
template <SIW kSize_ = kCpuCacheLineSize, typename T = UI1, typename SIZ = SIN,
          typename Class = Nil>
class TBuf {
 public:
  /* Default destructor does nothing. */
  TBuf() {}

  /* Returns the socket as a UIW*. */
  inline UIW* Words() { return words_; }

  /* Gets the end word of the socket. */
  inline UIW* WordsEnd() { return &words_[SizeWords()]; }

  /* Gets the stop word of the socket. */
  inline UIW* WordsStop() { return WordsEnd() - 1; }

  /* Gets the begin element of the socket. */
  template <typename T = CH1>
  inline T* Begin() {
    return reinterpret_cast<T*>(words_);
  }

  /* Returns the first element of the ASCII Object data section. */
  template <typename RT = T>
  inline RT* Start() {
    SIW address = reinterpret_cast<UIW>(words_);
    return reinterpret_cast<RT*>(address + sizeof(Class));
  }

  /* Gets the end element of the socket. */
  inline T* End() { return &words_[SizeWords()]; }

  /* Returns the last element of the ASCII Object data section. */
  inline T* Stop() { return Start<>() + Size() - 1; }

  /* Gets the begin of the socket. */
  template <typename T = CH1, typename SIZ = SIW>
  inline T& Element(SIZ index) {
    if (index < 0 || index >= Size()) return nullptr;
    return Start()[index];
  }

  /* Sets the size to the new value. */
  template <typename SIW>
  inline UIW* SetSize(SIW size) {
    A_ASSERT((size & kWordLSbMask) == 0)
    *reinterpret_cast<SIW*>(words_) = size;
    return words_;
  }

  /* The size in elements. */
  static constexpr SIZ Size() { return (SIZ(kSize_) < 0) ? 0 : SIZ(kSize_); }

  /* The size in bytes including the header. */
  static constexpr SIZ SizeBytes() {
    return Size() * sizeof(T) + sizeof(Class);
  }

  /* The size in words rounded down. */
  static constexpr SIZ SizeWords() { return CSizeWords<SIZ>(SizeBytes()); }

 private:
  UIW words_[SizeWords()];  //< The word-aligned socket.
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

/* Creates a T pointer from a base pointer plus the offset.
@param  base The base address.
@param  offset The offset in bytes. */
template <typename T = void>
inline T* TPtr(const void* begin, SIW offset) {
  return reinterpret_cast<T*>(reinterpret_cast<SIW>(begin) + offset);
}

/* Masks off the lower bits. */
template <typename UI>
inline UI TMaskLSb(UI value, UI msb_zero_count) {
  UI mask = (~UI(0)) >> msb_zero_count;
  return value & mask;
}

}  // namespace _

#endif
#endif
