/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/script2_socket.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <pch.h>
#if SEAM >= SCRIPT2_SEAM_SOCKET

#include "t_socket.h"

#if SEAM == SCRIPT2_SEAM_SOCKET
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

UI1 Negative(SI1 value) { return (UI1)(-value); }

UI1 Negative(UI1 value) { return (UI1)(-(SI1)value); }

UI2 Negative(SI2 value) { return (UI2)(-value); }

UI2 Negative(UI2 value) { return (UI2)(-(SI2)value); }

UI4 Negative(SI4 value) { return (UI4)(-value); }

UI4 Negative(UI4 value) { return (UI4)(-(SI4)value); }

UI8 Negative(SI8 value) { return (UI8)(-value); }

UI8 Negative(UI8 value) { return (UI8)(-(SI8)value); }

CH1* AlignDown(CH1* pointer, UIW mask) { return TAlignDown<CH1*>(pointer); }

const CH1* AlignDown(const CH1* pointer, UIW mask) {
  return TAlignDown<const CH1*>(pointer);
}

const UIW* AlignDown(const UIW* pointer, UIW mask) {
  return TAlignDown<const UIW*>(pointer);
}

UIW* AlignDown(UIW* pointer, UIW mask) { return TAlignDown<UIW*>(pointer); }

SI1 AlignDown(SI1 value, SI1 mask) { return TAlignDownI<SI1>(value, mask); }

SI2 AlignDown(SI2 value, SI2 mask) { return TAlignDownI<SI2>(value, mask); }

SI4 AlignDown(SI4 value, SI4 mask) { return TAlignDownI<SI4>(value, mask); }

SI8 AlignDown(SI8 value, SI8 mask) { return TAlignDownI<SI8>(value, mask); }

UIW* AlignUp(UIW* socket, UIW mask) { return TAlignUp<UIW>(socket, mask); }

CH1* AlignUp(CH1* pointer, UIW mask) { return TAlignUp<CH1>(pointer, mask); }

const CH1* AlignUp(const CH1* pointer, UIW mask) {
  return TAlignUp<const CH1>(pointer, mask);
}

UI1 AlignUp(UI1 value, UI1 mask) { return TAlignUpUnsigned<UI1>(value, mask); }

SI1 AlignUp(SI1 value, SI1 mask) { return TAlignUpSigned<SI1>(value, mask); }

UI2 AlignUp(UI2 value, UI2 mask) { return TAlignUpUnsigned<UI2>(value, mask); }

SI2 AlignUp(SI2 value, SI2 mask) { return TAlignUpSigned<SI2>(value, mask); }

UI4 AlignUp(UI4 value, UI4 mask) { return TAlignUpUnsigned<UI4>(value, mask); }

SI4 AlignUp(SI4 value, SI4 mask) { return TAlignUpSigned<SI4>(value, mask); }

UI8 AlignUp(UI8 value, UI8 mask) { return TAlignUpUnsigned<UI8>(value, mask); }

SI8 AlignUp(SI8 value, SI8 mask) { return TAlignUpSigned<SI8>(value, mask); }

UIW* New(SIW size) {
  // try {
  //  begin = new UIW[size >> TBitShiftCount<>()];
  //} catch (const std::bad_alloc& exception) {
  //  ObjException(exception.what());
  //  return nullptr;
  //}
  size = TAlignUpSigned<SIW>(size);
  DASSERT(!(size & (sizeof(SIW) - 1)));
  return new UIW[TWordCount<SIW>(size)];
}

void Delete(UIW* buffer, BOL using_heap) {
  if (using_heap) delete[] buffer;
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
         reinterpret_cast<const CH1*>(start);
}

inline UIW FillWord(CH1 fill_char) {
  UIW value = (UIW)(UI1)fill_char;
#if CPU_ENDIAN == LITTLE_ENDIAN
#if CPU_WORD_SIZE == 64
  return value | (value << 8) | (value << 16) | (value << 24) | (value << 32) |
         (value << 48) | (value << 56);
#elif CPU_WORD_SIZE == 32
  return value | (value << 8) | (value << 16) | (value << 24);
#else
  return value | (value << 8);
#endif
#else
#error You're CPU is in poopy mode. Change to Litle endian mode or fix me.
#endif
}

CH1* SocketFill(void* begin, void* end, CH1 fill_char) {
  CH1 *start = reinterpret_cast<CH1*>(begin),
      *stop = reinterpret_cast<CH1*>(end);
  ASSERT(start);
  SIW count = stop - start;
  PRINTF("\ncursor:%p\nbyte_count:%d", start, (SI4)count);

  PRINTF("\nFilling %i bytes from %p", (SI4)count, start);

  UIW fill_word = FillWord(fill_char);

  // Algorithm:
  // 1.) Save return value.
  // 2.) Align write pointer up and copy the unaligned bytes in
  // the lower
  //     memory region.
  // 3.) Align write_end pointer down and copy the unaligned
  // bytes in the
  //     upper memory region.
  // 4.) Copy the word-aligned middle region.
  CH1 *success = stop, *aligned_pointer = TAlignUp<>(start);
  while (start < aligned_pointer) *start++ = fill_char;
  aligned_pointer = TAlignDown<CH1*>(stop);
  while (stop > aligned_pointer) *stop-- = fill_char;

  UIW *words = reinterpret_cast<UIW*>(start),
      *words_end = reinterpret_cast<UIW*>(stop);

  while (words < words_end) *words++ = fill_word;

  return success;
}

CH1* SocketFill(void* begin, SIW count, CH1 fill_char) {
  return SocketFill(reinterpret_cast<CH1*>(begin),
                    reinterpret_cast<CH1*>(begin) + count - 1, fill_char);
}

CH1* SocketWipe(void* begin, void* end) { return SocketFill(begin, end, 0); }

CH1* SocketWipe(CH2* begin, CH2* end) {
  return SocketFill(begin, reinterpret_cast<CH1*>(end) + 1, 0);
}

CH1* SocketWipe(CH2* begin, CH4* end) {
  return SocketFill(begin, reinterpret_cast<CH1*>(end) + 3, 0);
}

CH1* SocketWipe(void* begin, SIW count) { return SocketFill(begin, count, 0); }

CH1* SocketCopy(void* begin, SIW size, const void* read, SIW read_size) {
  ASSERT(begin);
  ASSERT(read);
  ASSERT(size > 0);
  ASSERT(read_size > 0);

  if (size < read_size) return nullptr;
  CH1 *cursor = reinterpret_cast<CH1*>(begin), *end_ptr = cursor + size;
  const CH1 *start_ptr = reinterpret_cast<const CH1*>(read),
            *stop_ptr = start_ptr + read_size;

  if (read_size < (2 * sizeof(void*) + 1)) {
    // There is not enough bytes to copy in words.
    while (start_ptr < stop_ptr) *cursor++ = *start_ptr++;
    return cursor;
  }

  PRINTF("\nCopying %i bytes from %p and writing to %p",
         (SI4)(stop_ptr - start_ptr), cursor, stop_ptr);

  // Debug stuff.
  CH1 *begin_debug = cursor, *end_debug = end_ptr;

  // Algorithm:
  // 1.) Save return value.
  // 2.) Align write pointer up and copy the unaligned bytes in the lower
  //     memory region.
  // 3.) Align write_end pointer down and copy the unaligned bytes in the
  //     upper memory region.
  // 4.) Copy the word-aligned middle region.
  CH1 *success = end_ptr, *aligned_pointer = TAlignUp<>(cursor);
  PRINTF("\n  AlignUpPointer<> (begin):0x%p", aligned_pointer);
  while (cursor < aligned_pointer) *cursor++ = *start_ptr++;
  aligned_pointer = TAlignDown<CH1*>(end_ptr);
  PRINTF("\n  AlignDownPointer<> (begin):0x%p", aligned_pointer);
  while (end_ptr > aligned_pointer) *end_ptr-- = *stop_ptr--;
  PRINTF("\n  Down-stage pointers are now begin:0x%p end:0x%p", cursor,
         end_ptr);

  UIW *words = reinterpret_cast<UIW*>(cursor),
      *words_end = reinterpret_cast<UIW*>(end_ptr);
  const UIW* read_word = reinterpret_cast<const UIW*>(start_ptr);

  while (words < words_end) *words++ = *read_word++;

  return success;
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

Socket::Socket() {
  // Nothing to do here! (:-)-+=<
}

Socket::Socket(void* begin, void* end)
    : begin(reinterpret_cast<CH1*>(begin)), end(reinterpret_cast<CH1*>(end)) {
  if (!begin || !end || begin > end) {
    begin = end = 0;
    return;
  }
}

Socket::Socket(void* begin, SIW size)
    : begin(reinterpret_cast<CH1*>(begin)),
      end(reinterpret_cast<CH1*>(begin) + size) {
  if (!begin || size < 0) {
    end = reinterpret_cast<CH1*>(begin);
    return;
  }
}

Socket::Socket(const Socket& other) : begin(other.begin), end(other.end) {
  // Nothing to do here! (:-)-+=<
}

SIW Socket::Size() { return end - begin; }

Socket& Socket::operator=(const Socket& other) {
  begin = other.begin;
  end = other.end;
  return *this;
}

Nil::Nil() {}

constexpr SIW Nil::Size() { return 0; }

UIW* Nil::Buffer() { return nullptr; }

void DestructorNoOp(UIW* socket) {
  // Nothing to do here! (:-)+==<
}

void DestructorDeleteBuffer(UIW* socket) {
  ASSERT(socket);
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

}  // namespace _

#endif
