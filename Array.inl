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
      *words_end = TAlignDownPTR<IUW>(stop);
  while (words < words_end) *words++ = fill_word;
  // 3.) Copy remaining unaligned bytes.
  start = TPtr<CHA>(words_end);
  while (start < stop) *start++ = fill_char;

  return success;
}
}  //< namespace _

#if SEAM >= SCRIPT2_STACK
#include "Array.hpp"

#if SEAM == SCRIPT2_STACK
#include "_Debug.inl"
#else
#include "_Release.inl"
#endif

namespace _ {

IUW* RamFactoryStack(IUW* buffer, ISW size_bytes) {
  size_bytes += (-size_bytes) & cWordLSbMask; //< Word align up.
  ISW size_words = size_bytes >> cWordBitCount;
  IUW* socket = new IUW[size_words];
  // @todo Check if the memory was created successfully.
  return socket;
}

IUW* RamFactoryHeap(IUW* buffer, ISW size_bytes) {
  if (buffer) {
    delete[] buffer;
    return nullptr;
  }
  return RamFactoryStack(buffer, size_bytes);
}

ISW ArrayCopySlow(void* write, const void* read, ISW size_bytes) {
  CHA* cursor = TPtr<CHA>(write);
  const CHA* start = TPtr<CHA>(read),
    * stop = start + size_bytes;
  while (start < stop) *cursor++ = *start++;
  return size_bytes;
}

ISW ArrayCopyFast(void* write, const void* read, ISW size_bytes) {
  // Algorithm:
  // 64-bit Memory Layout that grows 3 bytes: 
  // b=byte bbbbbbbb_=64-bit word x=illegal memory address ?=legal memory byte
  //       0xN   v---cursor
  // Write: xxxxxbbb_bbbbbbbb_bbbbbbbb_bbbbbbbb_bbb?????
  //       0xN+M     begin_word        end_word
  //  Read: xxxxxxxb_bbbbbbbb_bbbbbbbb_bbbbbbbb_bb??????
  //               ^--start                stop--^
  // 
  // Step 1: Copy to the unaligned lower write bytes.
  // We start out with a socket full of memory taht we're not allowed to access
  // any of the x memory bytes else the compiler will yell at us.
  CHA* cursor = TPtr<CHA>(write);
  const CHA* start = TPtr<CHA>(read),
    * stop = start + size_bytes;
  IUW* write_begin_word = TAlignUpPTR<IUW>(cursor),
     * write_end_word = TAlignDownPTR<IUW>(cursor + size_bytes);
  const IUW* read_begin_word  = TAlignUpPTR<IUW>(start),
           * read_end_word = TAlignDownPTR<IUW>(stop);
  ISW  offset_read      = TDelta<ISW>(cursor, write_begin_word),
       offset_lower     = TDelta<ISW>(read_begin_word, start + offset_read),
       offset_upper     = sizeof(IUW) - offset_lower;
  while (cursor < TPtr<CHA>(write_begin_word)) *cursor++ = *start++;

  // Step 2: Copy the Word aligned data.
  // Write: bbbbbbbb_bbbbbbbb_bbbbbbbb_bbb?????
  //     -->  <-- offset_lower=2
  //  Read: ??bbbbbb_bbbbbbbb_bbbbbbbb_bb??????
  //       -->      <-- offset_upper=6
  IUW word_upper, word_lower;
  word_upper = *read_begin_word++;
  while(write_begin_word < write_end_word) {
    word_lower = word_upper >> offset_lower;
    word_upper  = *read_begin_word++;
    word_lower |= word_upper << offset_upper;
    *write_begin_word++ = word_lower;
    word_upper = word_lower;
  }

  // Stop 3: Copy the unaligned upper bytes.
  //  Write: bbbbbbbb_bbbbbbbb_bbbbbbbb
  start = TPtr<CHA>(read_end_word);
  while (start < stop) *cursor++ = *start++;
  return size_bytes;
}

ISW ArrayCopy(void* destination, ISW destination_size, const void* source,
               ISW source_size) {
  if (source_size <= 0 || destination_size < source_size) return 0;
  return ArrayCopySlow(destination, source, source_size);
}

ISW ArrayCompareSlow(const void* a, ISW a_size_bytes, const void* b,
                     ISW b_size_bytes) {
                                                                                                                            
  return a_size_bytes;
}

ISW ArrayCompareFast(const void* a, ISW a_size_bytes, const void* b,
                 ISW b_size_bytes) {
  if (a_size_bytes != b_size_bytes || a_size_bytes == 0) return 0;
  const CHA *a_cursor = TPtr<const CHA>(a),
            *a_end = a_cursor + a_size_bytes,
            *b_cursor = TPtr<const CHA>(b),
            *b_end = b_cursor + b_size_bytes;
  // Algoirhm: (@see ArrayCopy)  @todo Test me!
  // Step 1: Compare the unaligned lower write bytes.
  const CHA* cursor = TPtr<CHA>(a),
           * start  = TPtr<CHA>(b),
           * stop   = start + a_size_bytes;
  const IUW* a_begin_word = TAlignUpPTR<IUW>(cursor),
           * b_begin_word = TAlignUpPTR<IUW>(start);
  D_COUT("\na:0x" << Hexf(a) <<
         "\n :0x" << Hexf(a_begin_word) << 
         "\nb:0x" << Hexf(b) <<
         "\n :0x" << Hexf(b_begin_word));
  ISW offset_read  = TDelta<ISW>(cursor, a_begin_word),
      offset_lower = TDelta<ISW>(b_begin_word, start + offset_read),
      offset_upper = sizeof(IUW) - offset_lower;
  while (cursor < TPtr<CHA>(a_begin_word))
    if(*cursor++ != *start++)
      return -TDelta<>(a, cursor);
  // Step 2: Compare the Word aligned data.
  const IUW* a_end_word = TAlignDownPTR<IUW>(cursor + a_size_bytes),
           * b_end_word = TAlignDownPTR<IUW>(stop);
  IUW b_word, b_word_upper = *b_begin_word++;
  while (a_begin_word < a_end_word) {
    b_word = b_word_upper >> offset_lower;
    b_word_upper = *b_begin_word++;
    b_word |= b_word_upper << offset_upper;
    IUW a_word = *a_begin_word++;
    D_COUT("\na_word:0x" << Hexf(a_word) << 
           "\nb_word:0x" << Hexf(b_word));
    if (a_word != b_word) {
      //       word:0xff00ff00
      // word_lower:0xffff0000
      // word ^ word_lower: 00ffff00
      a_word ^= b_word;
      D_COUT("\n  ^   :0x" << Hexf(a_word));
      IUA word_byte = a_word & 0xff;
      IUA r = 0;
      while (!word_byte) {
        a_word >>= 8;
        word_byte = a_word & 0xff;
        ++r;
      }
      D_COUT(" r:" << r);
      return -(TDelta<>(a, a_begin_word - 1)) + r;
;   }
    b_word_upper = *b_begin_word++;
  }
  D_COUT("\n\nYour mom\n\n");
  // Stop 3: Compare the unaligned upper bytes.
  start = TPtr<CHA>(b_end_word);
  while (start < stop) if (*cursor++ != *start++) return -TDelta<>(a, cursor);
  return a_size_bytes;
}

ISW ArrayCompare(const void* a, ISW a_size_bytes, const void* b,
  ISW b_size_bytes) {
  return ArrayCompareFast(a, a_size_bytes, b, b_size_bytes);
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
