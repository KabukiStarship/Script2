/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_socket.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#include <pch.h>
#if SEAM >= SCRIPT2_SOCKET

#include "t_socket.h"

#if SEAM == SCRIPT2_RNG
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

CH1* AlignDown(CH1* pointer, UIW mask) { return TAlignDown<CH1*>(pointer); }

const CH1* AlignDown(const CH1* pointer, UIW mask) {
  return TAlignDown<const CH1*>(pointer);
}

const UIW* AlignDown(const UIW* pointer, UIW mask) {
  return TAlignDown<const UIW*>(pointer);
}

const CH1* AlignUp(const CH1* pointer, UIW mask) {
  return TAlignUp<const CH1>(pointer, mask);
}

const void* TypeAlignUp(SIW type, const void* value) {
  A_ASSERT(value);
  if (type == 0) return nullptr;
  SIW align_mask = TypeAlignmentMask(type & kTypeBitCount);
  if (align_mask < 0) return value;
  return AlignUp(value, align_mask);
}

void* TypeAlignUp(SIW type, void* value) {
  return const_cast<void*>(TypeAlignUp(type, (const void*)value));
}

UIW UIntPtr(const void* value) { return reinterpret_cast<UIW>(value); }

void* VoidPtr(UIW value) { return reinterpret_cast<void*>(value); }

const void* ConstVoidPtr(UIW value) {
  return reinterpret_cast<const void*>(value);
}

SIW SizeOf(void* begin, void* stop) {
  return reinterpret_cast<CH1*>(stop) - reinterpret_cast<CH1*>(begin);
}

SIW SizeOf(const void* start, const void* stop) {
  return reinterpret_cast<const CH1*>(stop) -
         reinterpret_cast<const CH1*>(start) + 1;
}

inline UIW FillWord(CH1 fill_char) {
  UIW value = (UIW)(UI1)fill_char;
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
#if CPU_WORD_SIZE == CPU_64_BIT
  return value | (value << 8) | (value << 16) | (value << 24) | (value << 32) |
         (value << 48) | (value << 56);
#elif CPU_WORD_SIZE == CPU_32_BIT
  return value | (value << 8) | (value << 16) | (value << 24);
#else
  return value | (value << 8);
#endif
#else
#error You're CPU is in poopy mode. Change to Litle endian mode.
#endif
}

CH1* SocketFill(void* begin, SIW count, CH1 fill_char) {
  D_ASSERT(begin);
  CH1* start = reinterpret_cast<CH1*>(begin);
  if (count < 3 * sizeof(SIW)) {
    while (--count > 0) *start++ = fill_char;
    return start;
  }

  D_COUT("\ncursor:" << Hexf(start) << "\ncount:" << count);

  CH1* stop = start + count;

  UIW fill_word = FillWord(fill_char);

  // 1.) Align start pointer up to a word boundry and fill the unaligned bytes.
  CH1 *success = stop, *aligned_pointer = TAlignUp<>(start);
  while (start < aligned_pointer) *start++ = fill_char;
  // 2.) Align stop pointer down to a word boundry and copy the midde words.
  UIW *words = reinterpret_cast<UIW*>(start),
      *words_end = reinterpret_cast<UIW*>(TAlignDown<CH1*>(stop));
  while (words < words_end) *words++ = fill_word;
  // 3.) Copy remaining unaligned bytes.
  start = reinterpret_cast<CH1*>(words_end);
  while (start < stop) *start++ = fill_char;

  return success;
}

CH1* SocketFill(void* begin, void* end, CH1 fill_char) {
  return SocketFill(reinterpret_cast<CH1*>(begin), TDelta<SIW>(begin, end) + 1,
                    fill_char);
}

CH1* SocketWipe(void* begin, void* end) { return SocketFill(begin, end, 0); }

CH2* SocketWipe(CH2* start, CH2* stop) {
  CH1* result = SocketFill(start, TDelta<SIW>(start, stop + 1));
  return reinterpret_cast<CH2*>(result);
}

CH4* SocketWipe(CH4* start, CH4* stop) {
  CH1* result = SocketFill(start, TDelta<SIW>(start, stop + 1));
  return reinterpret_cast<CH4*>(result);
}

CH1* SocketWipe(void* begin, SIW count) { return SocketFill(begin, count, 0); }

CH1* SocketCopy(void* destination, SIW destination_size, const void* source,
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
  D_COUT("\n  AlignUpPointer<> (begin):0x" << Hexf (aligned_pointer));
  while (cursor < aligned_pointer) *cursor++ = *start_ptr++;
  aligned_pointer = TAlignDown<CH1*>(end_ptr);
  D_COUT("\n  AlignDownPointer<> (begin):0x" << aligned_pointer;
  while (end_ptr > aligned_pointer) *end_ptr-- = *stop_ptr--;
  D_COUT("\n  Down-stage pointers are now begin:0x" << Hexf(cursor) << " end:0x"
  << Hexf(end_ptr));

  UIW *words = reinterpret_cast<UIW*>(cursor),
      *words_end = reinterpret_cast<UIW*>(end_ptr);
  const UIW* read_word = reinterpret_cast<const UIW*>(start_ptr);

  while (words < words_end) *words++ = *read_word++;

  return success;*/
}

CH1* SocketCopy(void* begin, void* stop, const void* read_begin,
                SIW read_size) {
  return SocketCopy(begin, SizeOf(begin, stop), read_begin, read_size);
}

CH1* SocketCopy(void* begin, void* stop, const void* read_begin,
                const void* read_end) {
  return SocketCopy(begin, SizeOf(begin, stop), read_begin,
                    SizeOf(read_begin, read_end));
}

BOL SocketCompare(const void* begin_a, SIW size_a, const void* begin_b,
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

BOL SocketCompare(const void* begin_a, const void* end_a, const void* begin_b,
                  const void* end_b) {
  return SocketCompare(begin_a, SizeOf(begin_a, end_a), begin_b,
                       SizeOf(begin_b, end_b));
}

BOL SocketCompare(const void* begin_a, void* end_a, const void* begin_b,
                  SIW size_b) {
  return SocketCompare(begin_a, end_a, begin_a,
                       reinterpret_cast<const CH1*>(begin_b) + size_b);
}

BufPtrs::BufPtrs() : begin(nullptr), end(nullptr) {}

BufPtrs::BufPtrs(void* begin, void* end)
    : begin(reinterpret_cast<CH1*>(begin)), end(reinterpret_cast<CH1*>(end)) {
  if (!begin || !end || begin > end) {
    begin = end = 0;
    return;
  }
}

BufPtrs::BufPtrs(void* begin, SIW size)
    : begin(reinterpret_cast<CH1*>(begin)),
      end(reinterpret_cast<CH1*>(begin) + size) {
  if (!begin || size < 0) {
    end = reinterpret_cast<CH1*>(begin);
    return;
  }
}

BufPtrs::BufPtrs(const BufPtrs& other) : begin(other.begin), end(other.end) {
  // Nothing to do here! (:-)-+=<
}

SIW BufPtrs::Size() { return end - begin; }

BufPtrs& BufPtrs::operator=(const BufPtrs& other) {
  begin = other.begin;
  end = other.end;
  return *this;
}

Nil::Nil() {}

constexpr SIW Nil::Size() { return 0; }
constexpr SIW Nil::SizeBytes() { return 0; }
constexpr SIW Nil::SizeWords() { return 0; }

UIW* Nil::Buffer() { return nullptr; }

void DestructorNoOp(UIW* socket) {
  // Nothing to do here! (:-)+==<
}

void DestructorDeleteBuffer(UIW* socket) {
  A_ASSERT(socket);
  delete socket;
}

SIW SocketShiftUp(void* begin, void* end, SIW count) {
  if (!begin || begin <= end || count <= 0) return 0;
  CH1 *start = reinterpret_cast<CH1*>(begin),
      *stop = reinterpret_cast<CH1*>(end);
  if (count < 3 * sizeof(void*)) {
    for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  UIW mask = sizeof(UIW) - 1;
  // Align the pointer down.
  UIW value = reinterpret_cast<UIW>(stop);
  CH1* pivot = reinterpret_cast<CH1*>(value - (value & mask));

  // Shift up the top portion.
  for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop--;
  UIW* stop_word = reinterpret_cast<UIW*>(stop);

  // Align the pointer up.
  value = reinterpret_cast<UIW>(start);
  UIW* start_word = reinterpret_cast<UIW*>(value + ((-(SIW)value) & mask));

  // Shift up the moddle portion.
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;

  // Shift up the bottom portion.
  pivot = reinterpret_cast<CH1*>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

SIW SocketShiftDown(void* begin, void* end, SIW count) {
  if (!begin || begin <= end || count <= 0) return 0;
  CH1 *start = reinterpret_cast<CH1*>(begin),
      *stop = reinterpret_cast<CH1*>(end);
  if (count < 3 * sizeof(void*)) {
    for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  UIW mask = sizeof(UIW) - 1;
  // Align the pointer down.
  UIW value = reinterpret_cast<UIW>(stop);
  CH1* pivot = reinterpret_cast<CH1*>(value - (value & mask));

  // Shift up the top portion.
  for (SI4 i = 0; i < count; ++i) *(stop + count) = *stop--;
  UIW* stop_word = reinterpret_cast<UIW*>(stop);

  // Align the pointer up.
  value = reinterpret_cast<UIW>(start);
  UIW* start_word = reinterpret_cast<UIW*>(value + ((-(SIW)value) & mask));

  // Shift up the moddle portion.
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;

  // Shift up the bottom portion.
  pivot = reinterpret_cast<CH1*>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

}  // namespace _

#endif
