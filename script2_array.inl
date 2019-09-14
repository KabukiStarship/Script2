/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_object.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>

#include "t_binary.h"
namespace _ {

/* Creastes a CPU word from the repeated fill_char. */
inline UIW FillWord(CH1 fill_char) {
  UIW value = (UIW)(UI1)fill_char;
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
#if ALU_SIZE == ALU_64_BIT
  return value | (value << 8) | (value << 16) | (value << 24) | (value << 32) |
         (value << 48) | (value << 56);
#elif ALU_SIZE == ALU_32_BIT
  return value | (value << 8) | (value << 16) | (value << 24);
#else
  return value | (value << 8);
#endif
#else
#error You're CPU is in poopy mode. Change to Litle endian mode.
#endif
}

CH1* ArrayFill(void* origin, SIW count, CH1 fill_char) {
  if (!origin) return nullptr;
  CH1* start = reinterpret_cast<CH1*>(origin);
  if (count < 3 * sizeof(SIW)) {
    while (--count > 0) *start++ = fill_char;
    return start;
  }

  CH1* stop = start + count;

  UIW fill_word = FillWord(fill_char);

  // 1.) Align start pointer up to a word boundry and fill the unaligned bytes.
  CH1 *success = stop, *aligned_pointer = TAlignUpPTR<>(start);
  while (start < aligned_pointer) *start++ = fill_char;
  // 2.) Align stop pointer down to a word boundry and copy the midde words.
  UIW *words = reinterpret_cast<UIW*>(start),
      *words_end = TAlignDownPTR<UIW*>(stop);
  while (words < words_end) *words++ = fill_word;
  // 3.) Copy remaining unaligned bytes.
  start = reinterpret_cast<CH1*>(words_end);
  while (start < stop) *start++ = fill_char;

  return success;
}
}  // namespace _

#if SEAM >= SCRIPT2_STACK
#include "t_array.h"

#if SEAM == SCRIPT2_STRAND
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

UIW* RamFactoryStack(UIW* buffer, SIW size_bytes, DTW data_type) {
  if (size_bytes < 0) return (UIW*)data_type;
  size_bytes += (-size_bytes) & kWordLSbMask;
  return new UIW[size_bytes >> kWordBitCount];
}

UIW* RamFactoryHeap(UIW* buffer, SIW size_bytes, DTW data_type) {
  if (buffer) {
    delete[] buffer;
    return nullptr;
  }
  return RamFactoryStack(buffer, size_bytes, data_type);
}

CH1* ArrayCopy(void* destination, SIW destination_size, const void* source,
               SIW source_size) {
  if (source_size <= 0 || destination_size <= 0) return nullptr;
  A_ASSERT(destination);
  A_ASSERT(source);
  // A_ASSERT(destination_size > 0);
  // A_ASSERT(source_size > 0);

  if (destination_size < source_size) return nullptr;
  CH1 *cursor = reinterpret_cast<CH1*>(destination),
      *end_ptr = cursor + destination_size;
  const CH1 *start_ptr = reinterpret_cast<const CH1*>(source),
            *stop_ptr = start_ptr + source_size;

  while (start_ptr < stop_ptr) *cursor++ = *start_ptr++;
  return cursor; /*
  if (source_size < (2 * sizeof(void*) + 1)) {
    // There is not enough bytes to copy in words.
    while (start_ptr < stop_ptr) *cursor++ = *start_ptr++;
    return cursor;
  }

  D_COUT("\nCopying " << stop_ptr - start_ptr << " bytes from " << Hexf(cursor)
                      << " and writing to " << Hexf (stop_ptr));

  // Algorithm:
  // 1.) Save return value.
  // 2.) Align write pointer up and copy the unaligned bytes in the lower
  //     memory region.
  // 3.) Align write_end pointer down and copy the unaligned bytes in the
  //     upper memory region.
  // 4.) Copy the word-aligned middle region.
  CH1 *success = end_ptr, *aligned_pointer = TAlignUp<>(cursor);
  D_COUT("\n  AlignUpPTR<> (origin):0x" << Hexf (aligned_pointer));
  while (cursor < aligned_pointer) *cursor++ = *start_ptr++;
  aligned_pointer = TAlignDown<CH1*>(end_ptr);
  D_COUT("\n  AlignDownPointer<> (origin):0x" << aligned_pointer;
  while (end_ptr > aligned_pointer) *end_ptr-- = *stop_ptr--;
  D_COUT("\n  Down-stage pointers are now origin:0x" << Hexf(cursor) << "
  end:0x"
  << Hexf(end_ptr));

  UIW *words = reinterpret_cast<UIW*>(cursor),
      *words_end = reinterpret_cast<UIW*>(end_ptr);
  const UIW* read_word = reinterpret_cast<const UIW*>(start_ptr);

  while (words < words_end) *words++ = *read_word++;

  return success;*/
}

BOL ArrayCompare(const void* begin_a, SIW size_a, const void* begin_b,
                 SIW size_b) {
  if (size_a != size_b) return false;
  const CH1 *cursor_a = reinterpret_cast<const CH1*>(begin_a),
            *end_a = cursor_a + size_a,
            *cursor_b = reinterpret_cast<const CH1*>(begin_b),
            *end_b = cursor_b + size_b;
  while (cursor_a < end_a) {
    CH1 a = *cursor_a++, b = *end_a++;
    if (a != b) return false;
  }
  return true;
}

Nil::Nil() {}
constexpr SIW Nil::Size() { return 0; }
constexpr SIW Nil::SizeBytes() { return 0; }
constexpr SIW Nil::SizeWords() { return 0; }
UIW* Nil::Words() { return nullptr; }

SIW ArrayShiftUp(void* origin, void* end, SIW count) {
  if (!origin || origin <= end || count <= 0) return 0;
  CH1 *start = reinterpret_cast<CH1*>(origin),
      *stop = reinterpret_cast<CH1*>(end);
  if (count < 3 * sizeof(void*)) {
    for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  UIW lsb_mask = sizeof(UIW) - 1;
  // Align the pointer down.
  UIW value = reinterpret_cast<UIW>(stop);
  CH1* pivot = reinterpret_cast<CH1*>(value - (value & lsb_mask));

  // Shift up the top portion.
  for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop--;
  UIW* stop_word = reinterpret_cast<UIW*>(stop);

  // Align the pointer up.
  value = AlignUp(value, lsb_mask);
  UIW* start_word = reinterpret_cast<UIW*>(value);

  // Shift up the moddle portion.
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;

  // Shift up the bottom portion.
  pivot = reinterpret_cast<CH1*>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

SIW ArrayShiftDown(void* origin, void* end, SIW count) {
  if (!origin || origin <= end || count <= 0) return 0;
  CH1 *start = reinterpret_cast<CH1*>(origin),
      *stop = reinterpret_cast<CH1*>(end);
  if (count < 3 * sizeof(void*)) {
    for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  UIW least_significant_bits_mask = sizeof(UIW) - 1;
  // Align the pointer down.
  UIW value = reinterpret_cast<UIW>(stop);
  CH1* pivot =
      reinterpret_cast<CH1*>(value - (value & least_significant_bits_mask));

  // Shift up the top portion.
  for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop--;
  UIW* stop_word = reinterpret_cast<UIW*>(stop);

  // Align the pointer up.
  value = reinterpret_cast<UIW>(start);
  UIW* start_word = reinterpret_cast<UIW*>(
      value + ((-(SIW)value) & least_significant_bits_mask));

  // Shift up the moddle portion.
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;

  // Shift up the bottom portion.
  pivot = reinterpret_cast<CH1*>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

}  // namespace _
#endif
