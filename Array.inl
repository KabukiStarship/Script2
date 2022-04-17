/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Array.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-22 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Array.hpp"
#include "Binary.hpp"
namespace _ {

/* Creates a CPU word from the repeated fill_char. */
inline IUW FillWord(CHA fill_char) {
  IUW value = (IUW)(IUA)fill_char;
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

CHA* ArrayFill(void* origin, ISW count, CHA fill_char) {
  if (!origin) return nullptr;
  CHA* start = TPtr<CHA>(origin);
  if (count < 3 * sizeof(ISW)) {
    while (--count > 0) *start++ = fill_char;
    return start;
  }

  CHA* stop = start + count;

  IUW fill_word = FillWord(fill_char);

  // 1.) Align start pointer up to a word boundry and fill the unaligned bytes.
  CHA *success = stop, *aligned_pointer = TAlignUpPTR<>(start);
  while (start < aligned_pointer) *start++ = fill_char;
  // 2.) Align stop pointer down to a word boundry and copy the midde words.
  IUW *words = reinterpret_cast<IUW*>(start),
      *words_end = TAlignDownPTR<IUW*>(stop);
  while (words < words_end) *words++ = fill_word;
  // 3.) Copy remaining unaligned bytes.
  start = TPtr<CHA>(words_end);
  while (start < stop) *start++ = fill_char;

  return success;
}
}  //< namespace _

#if SEAM >= SCRIPT2_STACK
#include "Array.hpp"

#if SEAM == SCRIPT2_STRING
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif

namespace _ {

IUW* RamFactoryStack(IUW* buffer, ISW size_bytes, DTW data_type) {
  if (size_bytes < 0) return (IUW*)data_type;
  size_bytes += (-size_bytes) & cWordLSbMask;
  ISW size_words = size_bytes >> cWordBitCount;
  IUW* socket = new IUW[size_words];
  return socket;
}

IUW* RamFactoryHeap(IUW* buffer, ISW size_bytes, DTW data_type) {
  if (buffer) {
    delete[] buffer;
    return nullptr;
  }
  return RamFactoryStack(buffer, size_bytes, data_type);
}

CHA* ArrayCopy(void* destination, ISW destination_size, const void* source,
               ISW source_size) {
  if (source_size <= 0 || destination_size <= 0) return nullptr;
  A_ASSERT(destination);
  A_ASSERT(source);
  // A_ASSERT(destination_size > 0);
  // A_ASSERT(source_size > 0);

  if (destination_size < source_size) return nullptr;
  CHA *cursor = TPtr<CHA>(destination),
      *end_ptr = cursor + destination_size;
  const CHA *start_ptr = reinterpret_cast<const CHA*>(source),
            *stop_ptr = start_ptr + source_size;

  while (start_ptr < stop_ptr) *cursor++ = *start_ptr++;
  return cursor;
  /* There was a bug in this code bug.
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
  CHA *success = end_ptr, *aligned_pointer = TAlignUp<>(cursor);
  D_COUT("\n  AlignUpPTR<> (origin):0x" << Hexf (aligned_pointer));
  while (cursor < aligned_pointer) *cursor++ = *start_ptr++;
  aligned_pointer = TAlignDown<CHA*>(end_ptr);
  D_COUT("\n  AlignDownPointer<> (origin):0x" << aligned_pointer;
  while (end_ptr > aligned_pointer) *end_ptr-- = *stop_ptr--;
  D_COUT("\n  Down-stage pointers are now origin:0x" << Hexf(cursor) << "
  end:0x"
  << Hexf(end_ptr));

  IUW *words = reinterpret_cast<IUW*>(cursor),
      *words_end = reinterpret_cast<IUW*>(end_ptr);
  const IUW* read_word = reinterpret_cast<const IUW*>(start_ptr);

  while (words < words_end) *words++ = *read_word++;

  return success;*/
}

BOL ArrayCompare(const void* begin_a, ISW size_a, const void* begin_b,
                 ISW size_b) {
  if (size_a != size_b) return false;
  const CHA *cursor_a = reinterpret_cast<const CHA*>(begin_a),
            *end_a = cursor_a + size_a,
            *cursor_b = reinterpret_cast<const CHA*>(begin_b),
            *end_b = cursor_b + size_b;
  while (cursor_a < end_a) {
    CHA a = *cursor_a++, b = *end_a++;
    if (a != b) return false;
  }
  return true;
}

Nil::Nil() {}
constexpr ISW Nil::Size() { return 0; }
constexpr ISW Nil::SizeBytes() { return 0; }
constexpr ISW Nil::SizeWords() { return 0; }
IUW* Nil::Words() { return nullptr; }

ISW ArrayShiftUp(void* origin, void* end, ISW count) {
  if (!origin || origin <= end || count <= 0) return 0;
  CHA *start = TPtr<CHA>(origin),
      *stop = TPtr<CHA>(end);
  if (count < 3 * sizeof(void*)) {
    for (ISC i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  IUW lsb_mask = sizeof(IUW) - 1;
  // Align the pointer down.
  IUW value = reinterpret_cast<IUW>(stop);
  CHA* pivot = reinterpret_cast<CHA*>(value - (value & lsb_mask));

  // Shift up the top portion.
  for (ISC i = 0; i < count; ++i) *(stop + count) = *stop--;
  IUW* stop_word = reinterpret_cast<IUW*>(stop);

  // Align the pointer up.
  value = CAlignUp(value, lsb_mask);
  IUW* start_word = reinterpret_cast<IUW*>(value);

  // Shift up the moddle portion.
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;

  // Shift up the bottom portion.
  pivot = TPtr<CHA>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

ISW ArrayShiftDown(void* origin, void* end, ISW count) {
  if (!origin || origin <= end || count <= 0) return 0;
  CHA *start = TPtr<CHA>(origin),
      *stop = TPtr<CHA>(end);
  if (count < 3 * sizeof(void*)) {
    for (ISC i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  IUW least_significant_bits_mask = sizeof(IUW) - 1;
  // Align the pointer down.
  IUW value = reinterpret_cast<IUW>(stop);
  CHA* pivot =
      reinterpret_cast<CHA*>(value - (value & least_significant_bits_mask));

  // Shift up the top portion.
  for (ISC i = 0; i < count; ++i) *(stop + count) = *stop--;
  IUW* stop_word = reinterpret_cast<IUW*>(stop);

  // Align the pointer up.
  value = reinterpret_cast<IUW>(start);
  IUW* start_word = reinterpret_cast<IUW*>(
      value + ((-(ISW)value) & least_significant_bits_mask));

  // Shift up the moddle portion.
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;

  // Shift up the bottom portion.
  pivot = TPtr<CHA>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

}  //< namespace _
#endif
