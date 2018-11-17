/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2_socket.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#include <pch.h>
#if SEAM >= _0_0_0__02

#include "tbinary.h"
#include "tsocket.h"

#if SEAM == _0_0_0__02
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

namespace _ {

char* AlignDown(char* pointer, UIW mask) { return TAlignDown<char*>(pointer); }

const char* AlignDown(const char* pointer, UIW mask) {
  return TAlignDown<const char*>(pointer);
}

const UIW* AlignDown(const UIW* pointer, UIW mask) {
  return TAlignDown<const UIW*>(pointer);
}

UIW* AlignDown(UIW* pointer, UIW mask) { return TAlignDown<UIW*>(pointer); }

UIW* AlignUp(UIW* socket, UIW mask) { return TAlignUp<UIW>(socket, mask); }

char* AlignUp(char* pointer, UIW mask) { return TAlignUp<char>(pointer, mask); }

const char* AlignUp(const char* pointer, UIW mask) {
  return TAlignUp<const char>(pointer, mask);
}

UI1 AlignUp(UI1 value, UI1 mask) { return TAlignUpUnsigned<UI1>(value, mask); }

SI1 AlignUp(SI1 value, SI1 mask) { return TAlignUpSigned<SI1>(value, mask); }

UI2 AlignUp(UI2 value, UI2 mask) { return TAlignUpUnsigned<UI2>(value, mask); }

SI2 AlignUp(SI2 value, SI2 mask) { return TAlignUpSigned<SI2>(value, mask); }

UI4 AlignUp(UI4 value, UI4 mask) { return TAlignUpUnsigned<UI4>(value, mask); }

SI4 AlignUp(SI4 value, SI4 mask) { return TAlignUpSigned<SI4>(value, mask); }

UI8 AlignUp(UI8 value, UI8 mask) { return TAlignUpUnsigned<UI8>(value, mask); }

SI8 AlignUp(SI8 value, SI8 mask) { return TAlignUpSigned<SI8>(value, mask); }

UIW* TNew(SIW size) { return new UIW[size]; }

void Destroy(UIW* socket) {
  ASSERT(socket);
  delete[] socket;
}

UIW UIntPtr(const void* value) { return reinterpret_cast<UIW>(value); }

void* VoidPtr(UIW value) { return reinterpret_cast<void*>(value); }

const void* ConstVoidPtr(UIW value) {
  return reinterpret_cast<const void*>(value);
}

SIW SizeOf(void* start, void* stop) {
  return reinterpret_cast<char*>(stop) - reinterpret_cast<char*>(start);
}

SIW SizeOf(const void* start, const void* stop) {
  return reinterpret_cast<const char*>(stop) -
         reinterpret_cast<const char*>(start);
}

inline UIW FillWord(char fill_char) {
  UIW value = fill_char;
#if CPU_WORD_SIze == 32
  return value | (value << 8) | (value << 16) | (value << 24);
#else
  return value | (value << 8) | (value << 16) | (value << 24) | (value << 32) |
         (value << 48) | (value << 56);
#endif
}

char* SocketFill(char* cursor, char* stop, SIW byte_count, char fill_char) {
  ASSERT(cursor);
  PRINTF("\ncursor:%p\nbyte_count:%d", cursor, (int)byte_count);
  ASSERT(byte_count >= 0);

  if ((stop - cursor) < byte_count) {
    PRINT("\nBuffer overflow!");
    return nullptr;
  }
  stop = cursor + byte_count;

  PRINTF("\nFilling %i bytes from %p", (int)byte_count, cursor);

  if (byte_count < (2 * sizeof(void*) + 1)) {
    while (cursor < stop) *cursor++ = fill_char;
    return cursor;
  }

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
  char *success = stop, *aligned_pointer = TAlignUp<>(cursor);
  while (cursor < aligned_pointer) *cursor++ = fill_char;
  aligned_pointer = TAlignDown<char*>(stop);
  while (stop > aligned_pointer) *stop-- = fill_char;

  UIW *words = reinterpret_cast<UIW*>(cursor),
      *words_end = reinterpret_cast<UIW*>(stop);

  while (words < words_end) *words++ = fill_word;

  return success;
}

char* SocketFill(void* cursor, SIW count, char fill_char) {
  return SocketFill(reinterpret_cast<char*>(cursor),
                    reinterpret_cast<char*>(cursor) + count, count, fill_char);
}

BOL SocketWipe(void* cursor, void* stop, SIW count) {
  return SocketFill(reinterpret_cast<char*>(cursor),
                    reinterpret_cast<char*>(stop), count) != nullptr;
}

char* SocketCopy(void* start, SIW size, const void* read, SIW read_size) {
  ASSERT(start);
  ASSERT(read);
  ASSERT(size > 0);
  ASSERT(read_size > 0);

  if (size < read_size) return nullptr;
  char *cursor = reinterpret_cast<char*>(start), *end_ptr = cursor + size;
  const char *start_ptr = reinterpret_cast<const char*>(read),
             *stop_ptr = start_ptr + read_size;

  if (read_size < (2 * sizeof(void*) + 1)) {
    // There is not enough bytes to copy in words.
    while (start_ptr < stop_ptr) *cursor++ = *start_ptr++;
    return cursor;
  }

  PRINTF("\nCopying %i bytes from %p and writing to %p",
         (int)(stop_ptr - start_ptr), cursor, stop_ptr);

  // Debug stuff.
  char *begin_debug = cursor, *end_debug = end_ptr;

  // Algorithm:
  // 1.) Save return value.
  // 2.) Align write pointer up and copy the unaligned bytes in the lower
  //     memory region.
  // 3.) Align write_end pointer down and copy the unaligned bytes in the
  //     upper memory region.
  // 4.) Copy the word-aligned middle region.
  char *success = end_ptr, *aligned_pointer = TAlignUp<>(cursor);
  PRINTF("\n  AlignUpPointer<> (begin):0x%p", aligned_pointer);
  while (cursor < aligned_pointer) *cursor++ = *start_ptr++;
  aligned_pointer = TAlignDown<char*>(end_ptr);
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

char* SocketCopy(void* start, void* stop, const void* begin_read,
                 SIW read_size) {
  return SocketCopy(start, SizeOf(start, stop), begin_read, read_size);
}

char* SocketCopy(void* start, void* stop, const void* begin_read,
                 const void* read_end) {
  return SocketCopy(start, SizeOf(start, stop), begin_read,
                    SizeOf(begin_read, read_end));
}

BOL SocketCompare(const void* begin_a, SIW size_a, const void* begin_b,
                  SIW size_b) {
  if (size_a != size_b) return false;
  const char *cursor_a = reinterpret_cast<const char*>(begin_a),
             *end_a = cursor_a + size_a,
             *cursor_b = reinterpret_cast<const char*>(begin_b),
             *end_b = cursor_b + size_b;
  while (cursor_a < end_a) {
    char a = *cursor_a++, b = *end_a++;
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
                       reinterpret_cast<const char*>(begin_b) + size_b);
}

Socket::Socket() {
  // Nothing to do here! (:-)-+=<
}

Socket::Socket(void* start, void* stop)
    : start(reinterpret_cast<char*>(start)),
      stop(reinterpret_cast<char*>(stop)) {
  if (!start || !stop || start > stop) {
    start = stop = 0;
    return;
  }
}

Socket::Socket(void* start, SIW size)
    : start(reinterpret_cast<char*>(start)),
      stop(reinterpret_cast<char*>(start) + size) {
  if (!start || size < 0) {
    stop = reinterpret_cast<char*>(start);
    return;
  }
}

Socket::Socket(const Socket& other) : start(other.start), stop(other.stop) {
  // Nothing to do here! (:-)-+=<
}

Socket& Socket::operator=(const Socket& other) {
  start = other.start;
  stop = other.stop;
  return *this;
}

void DestructorNoOp(UIW* socket) {
  // Nothing to do here! (:-)+==<
}

void DestructorDeleteBuffer(UIW* socket) {
  ASSERT(socket);
  delete socket;
}

SIW SocketShiftUp(void* begin, void* end, SIW count) {
  if (!begin || begin <= end || count <= 0) return 0;
  char *start = reinterpret_cast<char*>(begin),
       *stop = reinterpret_cast<char*>(end);
  if (count < 3 * sizeof(void*)) {
    for (int i = 0; i < count; ++i) *(stop + count) = *stop;
    return 0;
  }
  char* pivot = TAlignDown<char*>(stop);
  for (int i = 0; i < count; ++i) *(stop + count) = *stop--;
  UIW *stop_word = reinterpret_cast<UIW*>(stop),
      *start_word = reinterpret_cast<UIW*>(TAlignUp<UIW*>(start));
  while (stop_word >= start_word) *(stop_word + count) = *stop_word--;
  pivot = reinterpret_cast<char*>(stop_word + 1);
  while (pivot >= start) *(pivot + count) = *pivot--;
  return count;
}

}  // namespace _

#endif  //<  #if SEAM >= _0_0_0__02
