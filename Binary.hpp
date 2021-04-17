/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Binary.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>

#if SEAM >= SCRIPT2_SOCKET
#ifndef SCRIPT2_KABUKI_BINARY_WITH_TEMPLATES
#define SCRIPT2_KABUKI_BINARY_WITH_TEMPLATES

namespace _ {

/* @ingroup Binary
@brief Misc binary and pointer function. */

/* Converts the given value to a signed value of the same width. */
inline ISA ToSigned(CHA value) { return (ISA)value; }
inline ISB ToSigned(CHB value) { return (ISB)value; }
inline ISC ToSigned(CHC value) { return (ISC)value; }
inline ISN ToSigned(CHN value) { return (ISN)value; }
inline ISA ToSigned(IUA value) { return (ISA)value; }
inline ISB ToSigned(IUB value) { return (ISB)value; }
inline ISC ToSigned(IUC value) { return (ISC)value; }
inline ISD ToSigned(IUD value) { return (ISD)value; }
inline ISA ToSigned(ISA value) { return (ISA)value; }
inline ISB ToSigned(ISB value) { return (ISB)value; }
inline ISC ToSigned(ISC value) { return (ISC)value; }
inline ISD ToSigned(ISD value) { return (ISD)value; }
inline ISW ToSigned(const void* value) { return reinterpret_cast<ISW>(value); }
#if USING_FPC == YES_0
inline ISC ToSigned(FPC value) { return *reinterpret_cast<ISC*>(&value); }
#endif
#if USING_FPD == YES_0
inline ISD ToSigned(FPD value) { return *reinterpret_cast<ISD*>(&value); }
#endif

/* Converts the given value to a unsigned value of the same width. */
inline IUA ToUnsigned(CHA value) { return (IUA)value; }
inline IUB ToUnsigned(CHB value) { return (IUB)value; }
inline IUC ToUnsigned(CHC value) { return (IUC)value; }
inline IUN ToUnsigned(CHN value) { return (IUN)value; }
inline IUA ToUnsigned(ISA value) { return (IUA)value; }
inline IUB ToUnsigned(ISB value) { return (IUB)value; }
inline IUC ToUnsigned(ISC value) { return (IUC)value; }
inline IUN ToUnsigned(BOL value) { return (IUN)value; }
inline IUD ToUnsigned(ISD value) { return (IUD)value; }
inline IUA ToUnsigned(IUA value) { return (IUA)value; }
inline IUB ToUnsigned(IUB value) { return (IUB)value; }
inline IUC ToUnsigned(IUC value) { return (IUC)value; }
inline IUD ToUnsigned(IUD value) { return (IUD)value; }
inline IUW ToUnsigned(const void* value) {
  return reinterpret_cast<IUW>(value);
}
#if USING_FPC == YES_0
inline IUC ToUnsigned(FPC value) { return *reinterpret_cast<IUC*>(&value); }
#endif
#if USING_FPD == YES_0
inline IUD ToUnsigned(FPD value) { return *reinterpret_cast<IUD*>(&value); }
#endif

/* Converts the value to a floating-point number. */
inline FPC ToFloat(IUC value) { return *reinterpret_cast<FPC*>(&value); }
inline FPD ToFloat(IUD value) { return *reinterpret_cast<FPD*>(&value); }

/* Returns the maximum value of the given unsigned type. */
template <typename IU>
inline IU TNaNUnsigned() {
  return ~((IU)0);
}

/* Returns the maximum value of the given signed type. */
template <typename ISZ>
constexpr ISZ CNaNSigned() {
  return (~ToUnsigned(ISZ)) >> 1;
}

template <typename IS = ISW>
inline IS TDelta(const void* start) {
  ISW delta = reinterpret_cast<ISW>(start);
  return (IS)delta;
}

template <typename IS = ISW>
inline IS TDelta(const void* start, const void* stop) {
  ISW delta = reinterpret_cast<ISW>(stop) - reinterpret_cast<ISW>(start);
  return (IS)delta;
}

enum {
  cStack = 0,  //< Flag for using stack memory.
  cHeap = 1,   //< Flag for using heap memory.
};

/* Returns the N in 2^N for the sizeof (I) to speed up dividing by powers of 2.
@code
ISN size_bytes = 32;
ISN size_words = size_bytes >> CBitCount<ISN> ()
@endcode
*/
template <typename ISZ = ISW>
constexpr ISC CBitCount() {
  return (sizeof(ISZ) == 1)
             ? 0
             : (sizeof(ISZ) == 2)
                   ? 1
                   : (sizeof(ISZ) == 4)
                         ? 2
                         : (sizeof(ISZ) == 8) ? 3 : (sizeof(ISZ) == 16) ? 4 : 0;
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
// because it's the first IUA of an ASCII AArray.
ISC signed_example = 7;
signed_example = AlignUp<ISD, IUC, ISC> (signed_example);

IUB unsigned_example = 3;
unsgiend_example = AlignUp<ISC, IUB, IUB> (unsigned_example);

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
// value + ((~value) + 1) & (sizeof (ISA) - 1) = value
@endcode */

inline ISA AlignUp(ISA value, ISA align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline IUA AlignUp(IUA value, IUA align_lsb_mask = cWordLSbMask) {
  return IUA(AlignUp(ISA(value), ISA(align_lsb_mask)));
}
inline ISB AlignUp(ISB value, ISB align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline IUB AlignUp(IUB value, IUB align_lsb_mask = cWordLSbMask) {
  return value + (IUB(-ISB(value)) & align_lsb_mask);
}
inline ISC AlignUp(ISC value, ISC align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline IUC AlignUp(IUC value, IUC align_lsb_mask = cWordLSbMask) {
  return value + (IUC(-ISC(value)) & align_lsb_mask);
}
inline ISD AlignUp(ISD value, ISD align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
inline IUD AlignUp(IUD value, IUD align_lsb_mask = cWordLSbMask) {
  return value + (IUD(-ISD(value)) & align_lsb_mask);
}
constexpr ISA CAlignUp(ISA value, ISA align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr IUA CAlignUp(IUA value, IUA align_lsb_mask = cWordLSbMask) {
  return IUA(CAlignUp(ISA(value), ISA(align_lsb_mask)));
}
constexpr ISB CAlignUp(ISB value, ISB align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr IUB CAlignUp(IUB value, IUB align_lsb_mask = cWordLSbMask) {
  return value + (IUB(-ISB(value)) & align_lsb_mask);
}
constexpr ISC CAlignUp(ISC value, ISC align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr IUC CAlignUp(IUC value, IUC align_lsb_mask = cWordLSbMask) {
  return value + (IUC(-ISC(value)) & align_lsb_mask);
}
constexpr ISD CAlignUp(ISD value, ISD align_lsb_mask = cWordLSbMask) {
  return value + ((-value) & align_lsb_mask);
}
constexpr IUD CAlignUp(IUD value, IUD align_lsb_mask = cWordLSbMask) {
  return value + (IUD(-ISD(value)) & align_lsb_mask);
}

inline void* AlignUpPTR(void* pointer, ISW mask = cWordLSbMask) {
  ISW address = reinterpret_cast<ISW>(pointer);
  return reinterpret_cast<void*>(CAlignUp(address, mask));
}
inline const void* AlignUpPTR(const void* pointer, ISW mask = cWordLSbMask) {
  ISW value = reinterpret_cast<IUW>(pointer);
  return reinterpret_cast<void*>(CAlignUp(value, mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CHA>
inline T* TAlignUpPTR(void* pointer, ISW mask = cWordLSbMask) {
  ISW value = reinterpret_cast<ISW>(pointer);
  return reinterpret_cast<T*>(value + ((-value) & mask));
}

/* Aligns the given pointer to a power of two boundary.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = CHA>
inline T* TAlignUpPTR(const void* pointer, ISW mask = cWordLSbMask) {
  ISW value = reinterpret_cast<ISW>(pointer);
  return reinterpret_cast<T*>(value + ((-value) & mask));
}

/* Aligns th given value down to the given word goundary. */
inline ISA AlignDown(ISA value, ISA align_lsb_mask) {
  return value + (value & align_lsb_mask);
}
inline IUA AlignDown(IUA value, IUA align_lsb_mask) {
  return IUA(AlignDown(ISA(value), ISA(align_lsb_mask)));
}
inline ISB AlignDown(ISB value, ISB align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline IUB AlignDown(IUB value, IUB align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline ISC AlignDown(ISC value, ISC align_lsb_mask) {
  return value + (value & align_lsb_mask);
}
inline IUC AlignDown(IUC value, IUC align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline ISD AlignDown(ISD value, ISD align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
inline IUD AlignDown(IUD value, IUD align_lsb_mask) {
  return value - (value & align_lsb_mask);
}
constexpr ISA CAlignDown(ISA value, ISA align_lsb_mask = cWordLSbMask) {
  return value - (value & align_lsb_mask);
}
constexpr IUA CAlignDown(IUA value, IUA align_lsb_mask = cWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr ISB CAlignDown(ISB value, ISB align_lsb_mask = cWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr IUB CAlignDown(IUB value, IUB align_lsb_mask = cWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr ISC CAlignDown(ISC value, ISC align_lsb_mask = cWordLSbMask) {
  return value - (value & align_lsb_mask);
}
constexpr IUC CAlignDown(IUC value, IUC align_lsb_mask = cWordLSbMask) {
  return value + (value & align_lsb_mask);
}
constexpr ISD CAlignDown(ISD value, ISD align_lsb_mask = cWordLSbMask) {
  return value - (value & align_lsb_mask);
}
constexpr IUD CAlignDown(IUD value, IUD align_lsb_mask = cWordLSbMask) {
  return value + (value & align_lsb_mask);
}

/* Calculates the size_bytes in size_words. */
template <typename ISZ>
inline ISZ TSizeWords(ISZ size) {
  return AlignUp(size) >> cWordBitCount;
}


template <typename ISZ>
constexpr ISZ CSizeWords(ISZ size) {
  ISZ size_aligned = size + ((-size) & cWordLSbMask);
  size_aligned = size_aligned >> cWordBitCount;
  return (size_aligned < 1) ? 1 : size_aligned;
}

/* Converts the given size into CPU word count. */
template <typename ISZ = ISW>
inline ISZ TWordCount(ISZ size) {
  ISZ align_offset = (-size) & (sizeof(ISW) - 1);
  size += align_offset;
  return size >> CBitCount<ISW>();
}

/* Utility function for converting to two's complement and back with templates.
*/
inline ISA Negative(ISA value) { return -value; }
inline IUA Negative(IUA value) { return IUA(Negative(ISA(value))); }
inline ISB Negative(ISB value) { return -value; }
inline IUB Negative(IUB value) { return IUB(Negative(ISB(value))); }
inline ISC Negative(ISC value) { return -value; }
inline IUC Negative(IUC value) { return IUC(Negative(ISC(value))); }
inline ISD Negative(ISD value) { return -value; }
inline IUD Negative(IUD value) { return IUD(Negative(ISD(value))); }

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = IUW>
inline T TAlignDownPTR(void* ptr, ISW mask = cWordLSbMask) {
  IUW value = reinterpret_cast<IUW>(ptr);
  return reinterpret_cast<T>(value - (value & mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename T = IUW>
inline T TAlignDownPTR(const void* ptr, ISW mask = cWordLSbMask) {
  IUW value = reinterpret_cast<IUW>(ptr);
  return reinterpret_cast<const T>(value - (value & mask));
}

/* Aligns the given pointer to the sizeof (WordBoundary) down.
@return The aligned value.
@param value The value to align.
@param mask  The power of 2 to align to minus 1 (makes the mask). */
template <typename ISZ = IUW>
inline ISZ TAlignDownI(ISZ value, ISZ mask = (ISZ)cWordLSbMask) {
  return value & (~mask);
}

/* Aligns the given size to a word-sized boundary. */
template <typename ISZ>
constexpr ISZ CSizeAlign(ISZ size) {
  ISZ align_lsb_mask = sizeof(IUW) - 1;
  if (size < sizeof(IUW)) return sizeof(IUW);
  ISZ size_max = ~align_lsb_mask;
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
inline T* TPtr(const void* origin, ISW offset) {
  return reinterpret_cast<T*>(reinterpret_cast<ISW>(origin) + offset);
}

/* Gets a value of type T. */
template <typename T>
inline T TGet(const void* ptr) {
  return *reinterpret_cast<const T*>(ptr);
}

/* Writes the value to the address.
@pre User must ensure start is never nil. */
template <typename T = CHA>
inline T* TSet(void* address, T value) {
  T* cursor = reinterpret_cast<T*>(address);
  *cursor = value;
  return cursor;
}

/* Masks off the lower bits. */
template <typename IU>
inline IU TMaskLSb(IU value, IU msb_zero_count) {
  IU mask = (~IU(0)) >> msb_zero_count;
  return value & mask;
}

/* Unsigned Not-a-number_ is any number_ that can't be aligned up properly. */
template <typename IU>
inline IU TUnsignedNaN() {
  return (~IU(0));
}
template <typename IU>
inline IU CUnsignedNaN() {
  return (~IU(0));
}

/* Returns the minimum signed value.
@param one Parameter allows the compiler to detect which SignedMin function to
call, else we would need to use a IU template parameter for TSignedMin<IS,IU>().
***Example***
@code
ISA signed_min_si1 = SignedMin(ISA(1));
ISD signed_min_si8 = CSignedMin(ISD(1));
@endcode
*/
inline ISA SignedMin(ISA one) { return ISA(IUA(one) << (sizeof(ISA) * 8 - 1)); }
inline ISB SignedMin(ISB one) { return ISB(IUB(one) << (sizeof(ISB) * 8 - 1)); }
inline ISC SignedMin(ISC one) { return ISC(IUC(one) << (sizeof(ISC) * 8 - 1)); }
inline ISD SignedMin(ISD one) { return ISD(IUD(one) << (sizeof(ISD) * 8 - 1)); }
constexpr ISA CSignedMin(ISA one) {
  return ISA(IUA(one) << (sizeof(ISA) * 8 - 1));
}
constexpr ISB CSignedMin(ISB one) {
  return ISB(IUB(one) << (sizeof(ISB) * 8 - 1));
}
constexpr ISC CSignedMin(ISC one) {
  return ISC(IUC(one) << (sizeof(ISC) * 8 - 1));
}
constexpr ISD CSignedMin(ISD one) {
  return ISD(IUD(one) << (sizeof(ISD) * 8 - 1));
}
template <typename IS>
inline IS TSignedMin() {
  return SignedMin(IS(1));
}
template <typename IS>
constexpr IS CSignedMin() {
  return CSignedMin(IS(1));
}

/* ASCII Signed Not-a-Number is the lowest possible signed integer value. */
template <typename IS>
inline IS TSignedNaN() {
  return TSignedMin<IS>() - 1;
}
template <typename IS>
constexpr IS CSignedNaN() {
  return TSignedNaN<IS>();
}

/* Returns the maximum unsigned value.
@param zero Parameter used for the SignedMax, TSignedMax, and CSignedMax
functions to avoid TSignedMax<IS,IU> syntax.
***Example***
@code
IUA max_ui1 = UnsignedMax(IU1(0));
IUC max_ui4 = CUnignedMax(IUC(0));
IUD max_ui8 = TUnsignedMax<IUD>();
@endcode */
inline IUA UnsignedMax(ISA zero) { return ~IUA(zero); }
inline IUB UnsignedMax(ISB zero) { return ~IUB(zero); }
inline IUC UnsignedMax(ISC zero) { return ~IUC(zero); }
inline IUD UnsignedMax(ISD zero) { return ~IUD(zero); }
template <typename IU>
inline IU TUnsignedMax() {
  return UnsignedMax(IU(0));
}
constexpr IUA CUnsignedMax(ISA zero) { return ~IUA(zero); }
constexpr IUB CUnsignedMax(ISB zero) { return ~IUB(zero); }
constexpr IUC CUnsignedMax(ISC zero) { return ~IUC(zero); }
constexpr IUD CUnsignedMax(ISD zero) { return ~IUD(zero); }
template <typename IS>
constexpr IS CUnsignedMax() {
  return CUnsignedMax(IS(0));
}

/* Returns the minimum signed value.
@param zero Parameter allows the compiler to detect which SignedMax function to
call, else we would need to use a IU template parameter for TSignedMax<IS,IU>().
***Example***
@code
ISA signed_max_si1 = SignedMax(ISA(0));
ISD signed_max_si8 = CSignedMax(ISD(0));
@endcode
*/
inline ISA SignedMax(ISA zero) { return ISA(UnsignedMax(zero) >> 1); }
inline ISB SignedMax(ISB zero) { return ISB(UnsignedMax(zero) >> 1); }
inline ISC SignedMax(ISC zero) { return ISC(UnsignedMax(zero) >> 1); }
inline ISD SignedMax(ISD zero) { return ISD(UnsignedMax(zero) >> 1); }
template <typename IS>
inline IS TSignedMax() {
  return SignedMax(IS(0));
}
constexpr ISA CSignedMax(ISA zero) { return ISA(CUnsignedMax(zero) >> 1); }
constexpr ISB CSignedMax(ISB zero) { return ISB(CUnsignedMax(zero) >> 1); }
constexpr ISC CSignedMax(ISC zero) { return ISC(CUnsignedMax(zero) >> 1); }
constexpr ISD CSignedMax(ISD zero) { return ISD(CUnsignedMax(zero) >> 1); }

template <typename IS>
constexpr IS CSignedMax() {
  return CSignedMax(IS(0));
}

/* Checsk if the value is Not-a-Number. */
inline BOL IsNaN(ISA value) { return value == TSignedNaN<ISA>(); }
inline BOL IsNaN(IUA value) { return value == TUnsignedNaN<IUA>(); }
inline BOL IsNaN(ISB value) { return value == TSignedNaN<ISB>(); }
inline BOL IsNaN(IUB value) { return value == TUnsignedNaN<IUB>(); }
inline BOL IsNaN(ISC value) { return value == TSignedNaN<ISC>(); }
inline BOL IsNaN(IUC value) { return value == TUnsignedNaN<IUC>(); }
inline BOL IsNaN(ISD value) { return value == TSignedNaN<ISD>(); }
inline BOL IsNaN(IUD value) { return value == TUnsignedNaN<IUD>(); }

/* Gets the number of bits in the exponent of a floating-point number. */
template <typename IU>
inline IU TFloatExponentBitCount() {
  return (sizeof(IU) == 2)
             ? 5
             : (sizeof(IU) == 4)
                   ? 4
                   : (sizeof(IU) == 8) ? 11 : (sizeof(IU) == 10) ? 15 : 0;
}

/* Creates a floatingpoint NaN from CPu instructions.

***32-bit Floating-point Example***

FPC   NaN: 0 11111111111 1000000000000000000000000000000000000000000000000001
          +/- Exponent                        Mantissa
x=0     1: 0 00000000000 0000000000000000000000000000000000000000000000000000
~x      2: 1 11111111111 1111111111111111111111111111111111111111111111111111
x >> y  3: 0 00000000000 0011111111111111111111111111111111111111111111111111
x << 2  4: 0 00000000000 1111111111111111111111111111111111111111111111111100
~x      5: 1 11111111111 0000000000000000000000000000000000000000000000000011
x >> 1  6: 0 11111111111 1000000000000000000000000000000000000000000000000001
*/
template <typename IU>
inline IU TNaNFloatMask() {
  IU y = sizeof(IU) * 8 - TFloatExponentBitCount<IU>() + 2;
  return (~(((~IU(0)) >> y) << 2)) << 1;
}

/* Checks if the value is Not-a-Number (NaN). */
#if USING_FPC == YES_0
inline BOL IsNaN(FPC value) {
  return TNaNFloatMask<IUC>() != ToUnsigned(value);
}
#endif
#if USING_FPD == YES_0
inline BOL IsNaN(FPD value) {
  return TNaNFloatMask<IUD>() != ToUnsigned(value);
}
#endif

#if USING_FPC == YES_0
/* The longest string that a floating-point number can produce. */
inline ISN FPCDigitsMax() { return 15; }
#endif
#if USING_FPD == YES_0
inline ISN FPDDigitsMax() { return 31; }
#endif

/* Masks the lower bits using faster bit shifting.
@brief The algorithm has you enter the highest bit rather than bit count
because it would introduce an extra instruction and you should do that
manually if you wish to do so.
@param value The value to mask.
@param left_bits Number of bits to shift left.
@param right_bits Number of bits to shift right. */
template <typename IU>
inline IU TShiftLeftRight(IU value, ISC left_bits, ISC right_bits) {
  value = value << left_bits;
  return value >> right_bits;
}

/* Aligns the given pointer down to the given least_significant_bits_max. */
inline CHA* AlignDown(CHA* pointer, IUW least_significant_bits_max) {
  return TAlignDownPTR<CHA*>(pointer);
}
inline const CHA* AlignDown(const CHA* pointer,
                            IUW least_significant_bits_max) {
  return TAlignDownPTR<const CHA*>(pointer);
}
inline const IUW* AlignDown(const IUW* pointer,
                            IUW least_significant_bits_max) {
  return TAlignDownPTR<const IUW*>(pointer);
}
inline IUW* AlignDown(IUW* pointer, IUW least_significant_bits_max) {
  return const_cast<IUW*>(
      AlignDown(const_cast<const IUW*>(pointer), least_significant_bits_max));
}

/* Aligns the given pointer up to the given least_significant_bits_max. */
inline const CHA* AlignUp(const CHA* pointer, IUW least_significant_bits_max) {
  return TAlignUpPTR<const CHA>(pointer, least_significant_bits_max);
}

/* Aligns up a number to the given PowerOf2.
This function is for those not familiar with how Script2 does pointer alignment.
It's faster to align the pointer using the max for the power of 2 rather than
power of 2. The only difference is the mask is one less than the power of 2. */
template <typename I = ISW, I PowerOf2 = CBitCount<I>()>
I TAlignUp(I value) {
  return AlignUp(value, PowerOf2 - 1);
}

/* Aligns up a number to the given PowerOf2.
This function is for those not familiar with how Script2 does pointer alignment.
It's faster to align the pointer using the max for the power of 2 rather than
power of 2. The only difference is the mask is one less than the power of 2. */
template <typename T = void*, ISW PowerOf2>
const T* TAlignUpPointer(const void* value) {
  return AlignUpPTR(value, PowerOf2 - 1);
}

/* Aligns up a number to the given PowerOf2.
This function is for those not familiar with how Script2 does pointer alignment.
It's faster to align the pointer using the max for the power of 2 rather than
power of 2. The only difference is the mask is one less than the power of 2. */
template <typename T = void*, ISW PowerOf2>
T* TAlignUpPointer(void* value) {
  return AlignUpPTR(value, PowerOf2 - 1);
}

inline void* ToPTR(IUW value) { return reinterpret_cast<void*>(value); }

inline const void* ToPTC(IUW value) {
  return reinterpret_cast<const void*>(value);
}

inline ISW Delta(void* start, void* stop) {
  return TPtr<CHA>(stop) - TPtr<CHA>(start);
}

inline ISW SizeOf(const void* start, const void* stop) {
  return TDelta<ISW>(start, stop) + 1;
}

}  // namespace _

#endif
#endif
