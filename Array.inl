/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Array.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#include "Array.hpp"
#include "Binary.hpp"
#include <typeinfo>
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

/* Compares the two blocks of memory byte by byte to check if they're identical.
@return a_size_bytes if the two blocks of memory are idential, 0 if either the
pointers are null or the size in bytes are not the same, and any negative result
is the index + 1 of the first byte that was not the same. */
ISW ArrayCompareSlow(const void* a, ISW a_size_bytes, const void* b,
                     ISW b_size_bytes) {
  if (a_size_bytes != b_size_bytes || a_size_bytes <= 0) return 0;
  const CHA* a_cursor = TPtr<CHA>(a),
    * a_stop = a_cursor + a_size_bytes,
    * b_cursor = TPtr<CHA>(b);
  while (a_cursor < a_stop) {
    if (*a_cursor++ != *b_cursor++)
      return -TDelta<>(a, a_cursor);
  }
  return a_size_bytes;
}

/* Compares the two blocks of memory in words see if they're identical
@return a_size_bytes if the two blocks of memory are idential, 0 if either the 
pointers are null or the size in bytes are not the same, and any negative result
is the index + 1 of the first byte that was not the same. */
ISW ArrayCompareFast(const void* a, ISW a_size_bytes, const void* b,
                 ISW b_size_bytes) {
  if (a_size_bytes != b_size_bytes || a_size_bytes <= 0) return 0;
  const CHA *a_cursor = TPtr<const CHA>(a),
            *a_end = a_cursor + a_size_bytes,
            *b_cursor = TPtr<const CHA>(b),
            *b_end = b_cursor + b_size_bytes;
  // 16-byte Example:
  // v-- 0x0
  // xABCDEFG_HIJKLMN_P                  <- a_offset = 1
  // xxxxABCD_EFGHIJK_LMNP               <- b_offset = 4
  // 26-byte Example:              v------- a_end
  // xABCDEFG_HIJKLMNP_OQRSTUVW_XYZ   v---- b_end
  // xxxxABCD_EFGHIJKL_MNPOQRST_UVWXYZ
  if(a_size_bytes < 2 * WordByteCount) {
    while (a_cursor < a_end) {
      if (*a_cursor++ != *b_cursor++)
        return -TDelta<>(a, a_cursor);
    }
    return a_size_bytes;  
  }
  D_COUT("\n\nStep 1: Compare the words... ");
  const IUW* a_begin_word = TAlignDownPTR<IUW>(a_cursor),
           * b_begin_word = TAlignDownPTR<IUW>(b_cursor);
  const ISW a_offset = TDelta(a_begin_word, a_cursor),
            b_offset = TDelta(b_begin_word, b_cursor),
            a_offset_msb = WordByteCount - a_offset,
            b_offset_msb = WordByteCount - b_offset;
  IUW a_lsb = *a_begin_word,
      b_lsb = *b_begin_word;
  a_cursor = (CHA*)a_begin_word;
  b_cursor = (CHA*)b_begin_word;
  D_COUT("\na_offset: " << a_offset << " b_offset: " << b_offset);
  while (a_cursor < a_end - a_offset) {
    D_COUT("!");
    a_cursor += WordByteCount;
    b_cursor += WordByteCount;
    const IUW a_msb  = *(IUW*)a_cursor,
              b_msb  = *(IUW*)b_cursor,
              a_lsb_shifted = a_lsb >> a_offset,
              b_lsb_shifted = b_lsb >> b_offset,
              a_msb_shifted = a_msb << a_offset_msb,
              b_msb_shifted = b_msb << b_offset_msb,
              a_word = (a_lsb >> a_offset) | (a_msb << a_offset_msb),
              b_word = (b_lsb >> b_offset) | (b_msb << b_offset_msb);
    //0x00ff00
    // >>
    //0x0000ff
    // <<
    //0xff0000
    if (a_word != b_word) {
      D_COUT("\nFound naughty word!" <<
             "\n0x" << Hexf(a_word) << "\n0x" << Hexf(b_word) <<
             "\na_lsb: " << Hexf(a_lsb) << "\nb_lsb: " << Hexf(b_lsb) << 
             "\na_lsb_shifted: " << Hexf(a_lsb_shifted) <<
             "\nb_lsb_shifted: " << Hexf(b_lsb_shifted) <<
             "\ntypeid_a: " << typeid(a_lsb_shifted).name() <<
             "\na_msb: " << Hexf(a_msb) << "\nb_msb: " << Hexf(b_msb) <<
             "\na_msb_shifted: " << Hexf(a_msb_shifted) <<
             "\nb_msb_shifted: " << Hexf(b_msb_shifted) <<
             "\nTDelta(a, a_curosor): " << TDelta(a, a_cursor) <<
            " \nTDelta(b, b_curosor): " << TDelta(b, b_cursor));
      IUW index = 0;
      while (((a_word << index) & 0xff) == ((b_word << index) & 0xff)) ++index;
      return -TDelta<>(a, a_cursor - WordByteCount + index);
    }
    a_lsb = a_msb;
    b_lsb = b_msb;
  }
  D_COUT("\n\nStep 2: Compare the MSB.");
  a_cursor -= a_offset;
  b_cursor -= b_offset;
  while (a_cursor < a_end) {
    if(*a_cursor++ != *b_cursor)
      return -TDelta<>(a, a_begin_word - 1);
  }
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
