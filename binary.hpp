/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /binary.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SOCKET
#ifndef SCRIPT2_KABUKI_BINARY_WITH_TEMPLATES
#define SCRIPT2_KABUKI_BINARY_WITH_TEMPLATES

namespace _ {

/* @ingroup Binary
@brief Misc binary and pointer function. */

/* Converts the given value to a signed value of the same width. */
inline SI1 ToSigned(CH1 value) { return (SI1)value; }
inline SI2 ToSigned(CH2 value) { return (SI2)value; }
inline SI4 ToSigned(CH4 value) { return (SI4)value; }
inline SIN ToSigned(CHN value) { return (SIN)value; }
inline SI1 ToSigned(UI1 value) { return (SI1)value; }
inline SI2 ToSigned(UI2 value) { return (SI2)value; }
inline SI4 ToSigned(UI4 value) { return (SI4)value; }
inline SI8 ToSigned(UI8 value) { return (SI8)value; }
inline SI1 ToSigned(SI1 value) { return (SI1)value; }
inline SI2 ToSigned(SI2 value) { return (SI2)value; }
inline SI4 ToSigned(SI4 value) { return (SI4)value; }
inline SI8 ToSigned(SI8 value) { return (SI8)value; }
inline SIW ToSigned(const void* value) { return reinterpret_cast<SIW>(value); }
#if USING_FP4 == YES_0
inline SI4 ToSigned(FP4 value) { return *reinterpret_cast<SI4*>(&value); }
#endif
#if USING_FP8 == YES_0
inline SI8 ToSigned(FP8 value) { return *reinterpret_cast<SI8*>(&value); }
#endif

/* Converts the given value to a unsigned value of the same width. */
inline UI1 ToUnsigned(CH1 value) { return (UI1)value; }
inline UI2 ToUnsigned(CH2 value) { return (UI2)value; }
inline UI4 ToUnsigned(CH4 value) { return (UI4)value; }
inline UIN ToUnsigned(CHN value) { return (UIN)value; }
inline UI1 ToUnsigned(SI1 value) { return (UI1)value; }
inline UI2 ToUnsigned(SI2 value) { return (UI2)value; }
inline UI4 ToUnsigned(SI4 value) { return (UI4)value; }
inline UIN ToUnsigned(BOL value) { return (UIN)value; }
inline UI8 ToUnsigned(SI8 value) { return (UI8)value; }
inline UI1 ToUnsigned(UI1 value) { return (UI1)value; }
inline UI2 ToUnsigned(UI2 value) { return (UI2)value; }
inline UI4 ToUnsigned(UI4 value) { return (UI4)value; }
inline UI8 ToUnsigned(UI8 value) { return (UI8)value; }
inline UIW ToUnsigned(const void* value) {
  return reinterpret_cast<UIW>(value);
}
#if USING_FP4 == YES_0
inline UI4 ToUnsigned(FP4 value) { return *reinterpret_cast<UI4*>(&value); }
#endif
#if USING_FP8 == YES_0
inline UI8 ToUnsigned(FP8 value) { return *reinterpret_cast<UI8*>(&value); }
#endif

/* Converts the value to a floating-point number. */
inline FP4 ToFloat(UI4 value) { return *reinterpret_cast<FP4*>(&value); }
inline FP8 ToFloat(UI8 value) { return *reinterpret_cast<FP8*>(&value); }

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
inline SI TDelta(const void* start, const void* stop) {
  SIW delta = reinterpret_cast<SIW>(stop) - reinterpret_cast<SIW>(start);
  return (SI)delta;
}

enum {
  kStack = 0,  //< Flag for using stack memory.
  kHeap = 1,   //< Flag for using heap memory.
};

/* Returns the N in 2^N for the sizeof (I) to speed up dividing by powers of 2.
@code
SIN size_bytes = 32;
SIN size_words = size_bytes >> CBitCount<SIN> ()
@endcode
*/
template <typename SIZ = SIW>
constexpr SI4 CBitCount() {
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

inline SI1 AlignUp(SI1 value, SI1 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline UI1 AlignUp(UI1 value, UI1 align_lsb_mask = kWordLSbMask) {
  return UI1(AlignUp(SI1(value), SI1(align_lsb_mask)));
}
inline SI2 AlignUp(SI2 value, SI2 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline UI2 AlignUp(UI2 value, UI2 align_lsb_mask = kWordLSbMask) {
  return value + (UI2(-SI2(value)) & align_lsb_mask);
}
inline SI4 AlignUp(SI4 value, SI4 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline UI4 AlignUp(UI4 value, UI4 align_lsb_mask = kWordLSbMask) {
  return value + (UI4(-SI4(value)) & align_lsb_mask);
}
constexpr SI8 AlignUp(SI8 value, SI8 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr UI8 AlignUp(UI8 value, UI8 align_lsb_mask = kWordLSbMask) {
  return value + (UI8(-SI8(value)) & align_lsb_mask);
}
constexpr SI1 CAlignUp(SI1 value, SI1 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr UI1 CAlignUp(UI1 value, UI1 align_lsb_mask = kWordLSbMask) {
  return UI1(CAlignUp(SI1(value), SI1(align_lsb_mask)));
}
constexpr SI2 CAlignUp(SI2 value, SI2 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr UI2 CAlignUp(UI2 value, UI2 align_lsb_mask = kWordLSbMask) {
  return value + (UI2(-SI2(value)) & align_lsb_mask);
}
constexpr SI4 CAlignUp(SI4 value, SI4 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr UI4 CAlignUp(UI4 value, UI4 align_lsb_mask = kWordLSbMask) {
  return value + (UI4(-SI4(value)) & align_lsb_mask);
}
constexpr SI8 CAlignUp(SI8 value, SI8 align_lsb_mask = kWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr UI8 CAlignUp(UI8 value, UI8 align_lsb_mask = kWordLSbMask) {
  return value + (UI8(-SI8(value)) & align_lsb_mask);
}

inline void* AlignUpPTR(void* pointer, SIW mask = kWordLSbMask) {
  SIW address = reinterpret_cast<SIW>(pointer);
  return reinterpret_cast<void*>(AlignUp(address, mask));
}
inline const void* AlignUpPTR(const void* pointer, SIW mask = kWordLSbMask) {
  SIW value = reinterpret_cast<UIW>(pointer);
  return reinterpret_cast<void*>(AlignUp(value, mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CH1>
inline T* TAlignUpPTR(void* pointer, SIW mask = kWordLSbMask) {
  SIW value = reinterpret_cast<SIW>(pointer);
  return reinterpret_cast<T*>(value + ((-value) & mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CH1>
inline T* TAlignUpPTR(const void* pointer, SIW mask = kWordLSbMask) {
  SIW value = reinterpret_cast<SIW>(pointer);
  return reinterpret_cast<T*>(value + ((-value) & mask));
}

/* Aligns th given value down to the given word goundary. */
inline SI1 AlignDown(SI1 value, SI1 align_lsb_mask) {
  return value + (value & align_lsb_mask);
}
inline UI1 AlignDown(UI1 value, UI1 align_lsb_mask) {
  return UI1(AlignDown(SI1(value), SI1(align_lsb_mask)));
}
inline SI2 AlignDown(SI2 value, SI2 align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline UI2 AlignDown(UI2 value, UI2 align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline SI4 AlignDown(SI4 value, SI4 align_lsb_mask) {
  return value + (value & align_lsb_mask);
}
inline UI4 AlignDown(UI4 value, UI4 align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline SI8 AlignDown(SI8 value, SI8 align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline UI8 AlignDown(UI8 value, UI8 align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
constexpr SI1 CAlignDown(SI1 value, SI1 align_lsb_mask = kWordLSbMask) {
  return value - (value & align_lsb_mask);
}
constexpr UI1 CAlignDown(UI1 value, UI1 align_lsb_mask = kWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr SI2 CAlignDown(SI2 value, SI2 align_lsb_mask = kWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr UI2 CAlignDown(UI2 value, UI2 align_lsb_mask = kWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr SI4 CAlignDown(SI4 value, SI4 align_lsb_mask = kWordLSbMask) {
  return value - (value & align_lsb_mask);
}
constexpr UI4 CAlignDown(UI4 value, UI4 align_lsb_mask = kWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr SI8 CAlignDown(SI8 value, SI8 align_lsb_mask = kWordLSbMask) {
  return value - (value & align_lsb_mask);
}
constexpr UI8 CAlignDown(UI8 value, UI8 align_lsb_mask = kWordLSbMask) {
  return value + (value & align_lsb_mask);
}

/* Calculates the size_bytes in size_words. */
template <typename SIZ>
inline SIZ TSizeWords(SIZ size) {
  return AlignUp(size) >> kWordBitCount;
}

template <typename SIZ>
constexpr SIZ CSizeWords(SIZ size) {
  SIZ size_aligned = size + ((-size) & kWordLSbMask);
  size_aligned = size_aligned >> kWordBitCount;
  return (size_aligned < 1) ? 1 : size_aligned;
}

/* Converts the given size into CPU word count. */
template <typename SIZ = SIW>
inline SIZ TWordCount(SIZ size) {
  SIZ align_offset = (-size) & (sizeof(SIW) - 1);
  size += align_offset;
  return size >> CBitCount<SIW>();
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
inline T TAlignDownPTR(void* ptr, SIW mask = kWordLSbMask) {
  UIW value = reinterpret_cast<UIW>(ptr);
  return reinterpret_cast<T>(value - (value & mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = UIW>
inline T TAlignDownPTR(const void* ptr, SIW mask = kWordLSbMask) {
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
  SIZ align_lsb_mask = sizeof(UIW) - 1;
  if (size < sizeof(UIW)) return sizeof(UIW);
  SIZ size_max = ~align_lsb_mask;
  if (size > size_max) return size;
  return size + (-size) & align_lsb_mask;
}

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
@param base The base address.
@param offset The offset in bytes. */
template <typename T = void>
inline T* TPtr(const void* origin, SIW offset) {
  return reinterpret_cast<T*>(reinterpret_cast<SIW>(origin) + offset);
}

/* Gets a value of type T. */
template <typename T>
inline T TGet(const void* ptr) {
  return *reinterpret_cast<const T*>(ptr);
}

/* Writes the value to the address.
@pre User must ensure start is never nil. */
template <typename T = CH1>
inline T* TSet(void* address, T value) {
  T* cursor = reinterpret_cast<T*>(address);
  *cursor = value;
  return cursor;
}

/* Masks off the lower bits. */
template <typename UI>
inline UI TMaskLSb(UI value, UI msb_zero_count) {
  UI mask = (~UI(0)) >> msb_zero_count;
  return value & mask;
}

/* Unsigned Not-a-number_ is any number_ that can't be aligned up properly. */
template <typename UI>
inline UI TUnsignedNaN() {
  return (~UI(0));
}
template <typename UI>
inline UI CUnsignedNaN() {
  return (~UI(0));
}

/* Returns the minimum signed value.
@param one Parameter allows the compiler to detect which SignedMin function to
call, else we would need to use a UI template parameter for TSignedMin<SI,UI>().
***Example***
@code
SI1 signed_min_si1 = SignedMin(SI1(1));
SI8 signed_min_si8 = CSignedMin(SI8(1));
@endcode
*/
inline SI1 SignedMin(SI1 one) { return SI1(UI1(one) << (sizeof(SI1) * 8 - 1)); }
inline SI2 SignedMin(SI2 one) { return SI2(UI2(one) << (sizeof(SI2) * 8 - 1)); }
inline SI4 SignedMin(SI4 one) { return SI4(UI4(one) << (sizeof(SI4) * 8 - 1)); }
inline SI8 SignedMin(SI8 one) { return SI8(UI8(one) << (sizeof(SI8) * 8 - 1)); }
constexpr SI1 CSignedMin(SI1 one) {
  return SI1(UI1(one) << (sizeof(SI1) * 8 - 1));
}
constexpr SI2 CSignedMin(SI2 one) {
  return SI2(UI2(one) << (sizeof(SI2) * 8 - 1));
}
constexpr SI4 CSignedMin(SI4 one) {
  return SI4(UI4(one) << (sizeof(SI4) * 8 - 1));
}
constexpr SI8 CSignedMin(SI8 one) {
  return SI8(UI8(one) << (sizeof(SI8) * 8 - 1));
}
template <typename SI>
inline SI TSignedMin() {
  return SignedMin(SI(1));
}
template <typename SI>
constexpr SI CSignedMin() {
  return CSignedMin(SI(1));
}

/* ASCII Signed Not-a-Number is the lowest possible signed integer value. */
template <typename SI>
inline SI TSignedNaN() {
  return TSignedMin<SI>() - 1;
}
template <typename SI>
constexpr SI CSignedNaN() {
  return TSignedNaN<SI>();
}

/* Returns the maximum unsigned value.
@param zero Parameter used for the SignedMax, TSignedMax, and CSignedMax
functions to avoid TSignedMax<SI,UI> syntax.
***Example***
@code
UI1 max_ui1 = UnsignedMax(IU1(0));
UI4 max_ui4 = CUnignedMax(UI4(0));
UI8 max_ui8 = TUnsignedMax<UI8>();
@endcode */
inline UI1 UnsignedMax(SI1 zero) { return ~UI1(zero); }
inline UI2 UnsignedMax(SI2 zero) { return ~UI2(zero); }
inline UI4 UnsignedMax(SI4 zero) { return ~UI4(zero); }
inline UI8 UnsignedMax(SI8 zero) { return ~UI8(zero); }
template <typename UI>
inline UI TUnsignedMax() {
  return UnsignedMax(UI(0));
}
constexpr UI1 CUnsignedMax(SI1 zero) { return ~UI1(zero); }
constexpr UI2 CUnsignedMax(SI2 zero) { return ~UI2(zero); }
constexpr UI4 CUnsignedMax(SI4 zero) { return ~UI4(zero); }
constexpr UI8 CUnsignedMax(SI8 zero) { return ~UI8(zero); }
template <typename SI>
constexpr SI CUnsignedMax() {
  return CUnsignedMax(SI(0));
}

/* Returns the minimum signed value.
@param zero Parameter allows the compiler to detect which SignedMax function to
call, else we would need to use a UI template parameter for TSignedMax<SI,UI>().
***Example***
@code
SI1 signed_max_si1 = SignedMax(SI1(0));
SI8 signed_max_si8 = CSignedMax(SI8(0));
@endcode
*/
inline SI1 SignedMax(SI1 zero) { return SI1(UnsignedMax(zero) >> 1); }
inline SI2 SignedMax(SI2 zero) { return SI2(UnsignedMax(zero) >> 1); }
inline SI4 SignedMax(SI4 zero) { return SI4(UnsignedMax(zero) >> 1); }
inline SI8 SignedMax(SI8 zero) { return SI8(UnsignedMax(zero) >> 1); }
template <typename SI>
inline SI TSignedMax() {
  return SignedMax(SI(0));
}
constexpr SI1 CSignedMax(SI1 zero) { return SI1(CUnsignedMax(zero) >> 1); }
constexpr SI2 CSignedMax(SI2 zero) { return SI2(CUnsignedMax(zero) >> 1); }
constexpr SI4 CSignedMax(SI4 zero) { return SI4(CUnsignedMax(zero) >> 1); }
constexpr SI8 CSignedMax(SI8 zero) { return SI8(CUnsignedMax(zero) >> 1); }

template <typename SI>
constexpr SI CSignedMax() {
  return CSignedMax(SI(0));
}

/* Checsk if the value is Not-a-Number. */
inline BOL IsNaN(SI1 value) { return value == TSignedNaN<SI1>(); }
inline BOL IsNaN(UI1 value) { return value == TUnsignedNaN<UI1>(); }
inline BOL IsNaN(SI2 value) { return value == TSignedNaN<SI2>(); }
inline BOL IsNaN(UI2 value) { return value == TUnsignedNaN<UI2>(); }
inline BOL IsNaN(SI4 value) { return value == TSignedNaN<SI4>(); }
inline BOL IsNaN(UI4 value) { return value == TUnsignedNaN<UI4>(); }
inline BOL IsNaN(SI8 value) { return value == TSignedNaN<SI8>(); }
inline BOL IsNaN(UI8 value) { return value == TUnsignedNaN<UI8>(); }

/* Gets the number of bits in the exponent of a floating-point number. */
template <typename UI>
inline UI TFloatExponentBitCount() {
  return (sizeof(UI) == 2)
             ? 5
             : (sizeof(UI) == 4)
                   ? 4
                   : (sizeof(UI) == 8) ? 11 : (sizeof(UI) == 10) ? 15 : 0;
}

/* Creates a floatingpoint NaN from CPu instructions.

***32-bit Floating-point Example***

FP4   NaN: 0 11111111111 1000000000000000000000000000000000000000000000000001
          +/- Exponent                        Mantissa
x=0     1: 0 00000000000 0000000000000000000000000000000000000000000000000000
~x      2: 1 11111111111 1111111111111111111111111111111111111111111111111111
x >> y  3: 0 00000000000 0011111111111111111111111111111111111111111111111111
x << 2  4: 0 00000000000 1111111111111111111111111111111111111111111111111100
~x      5: 1 11111111111 0000000000000000000000000000000000000000000000000011
x >> 1  6: 0 11111111111 1000000000000000000000000000000000000000000000000001
*/
template <typename UI>
inline UI TNaNFloatMask() {
  UI y = sizeof(UI) * 8 - TFloatExponentBitCount<UI>() + 2;
  return (~(((~UI(0)) >> y) << 2)) << 1;
}

/* Checks if the value is Not-a-Number (NaN). */
#if USING_FP4 == YES_0
inline BOL IsNaN(FP4 value) {
  return TNaNFloatMask<UI4>() != ToUnsigned(value);
}
#endif
#if USING_FP8 == YES_0
inline BOL IsNaN(FP8 value) {
  return TNaNFloatMask<UI8>() != ToUnsigned(value);
}
#endif

#if USING_FP4 == YES_0
/* The longest string that a floating-point number can produce. */
inline SIN FP4DigitsMax() { return 15; }
#endif
#if USING_FP8 == YES_0
inline SIN FP8DigitsMax() { return 31; }
#endif

/* Masks the lower bits using faster bit shifting.
@brief The algorithm has you enter the highest bit rather than bit count
because it would introduce an extra instruction and you should do that
manually if you wish to do so.
@param value The value to mask.
@param left_bits Number of bits to shift left.
@param right_bits Number of bits to shift right. */
template <typename UI>
inline UI TShiftLeftRight(UI value, SI4 left_bits, SI4 right_bits) {
  value = value << left_bits;
  return value >> right_bits;
}

/* Aligns the given pointer down to the given least_significant_bits_max. */
inline CH1* AlignDown(CH1* pointer, UIW least_significant_bits_max) {
  return TAlignDownPTR<CH1*>(pointer);
}
inline const CH1* AlignDown(const CH1* pointer,
                            UIW least_significant_bits_max) {
  return TAlignDownPTR<const CH1*>(pointer);
}
inline const UIW* AlignDown(const UIW* pointer,
                            UIW least_significant_bits_max) {
  return TAlignDownPTR<const UIW*>(pointer);
}
inline UIW* AlignDown(UIW* pointer, UIW least_significant_bits_max) {
  return const_cast<UIW*>(
      AlignDown(const_cast<const UIW*>(pointer), least_significant_bits_max));
}

/* Aligns the given pointer up to the given least_significant_bits_max. */
inline const CH1* AlignUp(const CH1* pointer, UIW least_significant_bits_max) {
  return TAlignUpPTR<const CH1>(pointer, least_significant_bits_max);
}

/* Aligns up a number to the given kPowerOf2_.
This funciton is for those not familiar with how Script2 does pointer alignment.
It's faster to align the pointer using the max for the power of 2 rather than
power of 2. The only difference is the mask is one less than the power of 2. */
template <typename I = SIW, I kPowerOf2_ = CBitCount<I>()>
I TAlignUp(I value) {
  return ALignUp(value, kPowerOf2_ - 1);
}

/* Aligns up a number to the given kPowerOf2_.
This funciton is for those not familiar with how Script2 does pointer alignment.
It's faster to align the pointer using the max for the power of 2 rather than
power of 2. The only difference is the mask is one less than the power of 2. */
template <typename T = void*, SIW kPowerOf2_>
const T* TAlignUpPointer(const void* value) {
  return AlignUpPTR(value, kPowerOf2_ - 1);
}

/* Aligns up a number to the given kPowerOf2_.
This funciton is for those not familiar with how Script2 does pointer alignment.
It's faster to align the pointer using the max for the power of 2 rather than
power of 2. The only difference is the mask is one less than the power of 2. */
template <typename T = void*, SIW kPowerOf2_>
T* TAlignUpPointer(void* value) {
  return AlignUpPTR(value, kPowerOf2_ - 1);
}

inline void* ToPTR(UIW value) { return reinterpret_cast<void*>(value); }

inline const void* ToPTC(UIW value) {
  return reinterpret_cast<const void*>(value);
}

inline SIW Delta(void* start, void* stop) {
  return reinterpret_cast<CH1*>(stop) - reinterpret_cast<CH1*>(start);
}

inline SIW SizeOf(const void* start, const void* stop) {
  return TDelta<SIW>(start, stop) + 1;
}

}  // namespace _

#endif
#endif
