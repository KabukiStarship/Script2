/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /t_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough
<<calemccollough.github.io>>; All right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_TABLE

#ifndef SCRIPTT2_TABLE_T
#define SCRIPTT2_TABLE_T

#include "t_array.h"
#include "t_binary.h"
#include "t_uniprinter.h"

#if SEAM == SCRIPT2_TABLE
#include "module_debug.inl"
#else
#include "module_release.inl"
#define D_COUT_TABLE(item)
#endif

namespace _ {

/* A dense key-index map.
@see ASCII Data Type Specification.
@link ./spec/data/map_types/table.md

# Collision Table

Collision table works by using the maximum key value (i.e. 255 for a SIZ,
2^15TTableInvalidIndex<SIZ>() for a SI2, etc). The collisions list is a sequence
of indexes terminated by an invalid index that is greater than kMaxNumOps.
collissionsList[0] is an invalid index, so the collisions list is searched
from lower address up.
@code
         Table Memory Layout
+--------------------------------------+
|_____ | Key 1                         |
|_____ v Key N                Keys     |
+--------------------------------------+
|        Buffer                        |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision N        Collision  |
|_____ | Collision 0          Pile     |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision Index N   Unsorted  |
|      | Collision Index 0   Indexes   |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision Index N  Collision  |
|      | Collision Index 0   Indexes   |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Key Offset N          Key     |
|      | Key Offset 1        Offsets   |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Sorted Hash N        Hashes   |
|      | Sorted Hash 1                 |
+--------------------------------------+  ^ Up in addresses.
|            TTable Header             |  |
+-------------------------------------+ 0x0
@endcode
*/
template <typename SIZ>
struct TTable {
  SIZ size_bytes,  //< Size of this object in bytes.
      size_pile,   //< Size of the collision table pile.
      count,       //< Number of keys.
      count_max;   //< Number of buffered indexes.
};

enum {
  kMinTableSize = 64,  //< Min size of a Table
};

/* Returns the highest signed prime that can fit in type SI.
@return 0 if the sizeof (SI) is not 1, 2, 4, or 8.  */
template <typename SI>
inline SI PrimeMaxSigned() {
  SI prime = (sizeof(SI) == 1)
                 ? 127
                 : (sizeof(SI) == 2)
                       ? 32767
                       : (sizeof(SI) == 4)
                             ? 2147483647
                             : (sizeof(SI) == 8) ? 9223372036854775783 : 0;
  return prime;
}

/* Returns the highest signed prime that can fit in type UI.
@return 0 if the sizeof (UI) is not 1, 2, 4, or 8. */
template <typename HSH>
inline HSH TPrimeMaxUnigned() {
  HSH prime = sizeof(HSH) == 1
                  ? 251
                  : sizeof(HSH) == 2
                        ? 65535
                        : sizeof(HSH) == 4
                              ? 4294967291
                              : sizeof(HSH) == 8 ? 18446744073709551557 : 0;
  return prime;
}

template <typename HSH, typename Char = CHR>
inline HSH THashPrime(Char value, HSH hash) {
  return hash + hash * (HSH)value;
}

template <typename HSH = UIN, typename Char = CHR>
inline HSH THashPrime(const Char* str) {
  Char c = (Char)*str++;
  HSH hash = TPrimeMaxUnigned<HSH>();
  while (c) {
    hash = THashPrime<HSH, Char>(c, hash);
    c = *str++;
  }
  return hash;
}

inline UI2 Hash16UI2(UI2 value, UI2 hash) {
  UI2 prime = TPrimeMaxUnigned<UI2>();
  hash = ((value & 0xff) * prime) + hash;
  hash = ((value >> 8) * prime) + hash;
  return hash;
}

inline UI2 Hash16UI4(UI4 value, UI2 hash) {
  UI2 prime = TPrimeMaxUnigned<UI2>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  return hash;
}

inline UI2 Hash16UI8(UI8 value, UI2 hash) {
  UI2 prime = TPrimeMaxUnigned<UI2>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  hash = (((value >> 32) & 0xff) * prime) + hash;
  hash = (((value >> 40) & 0xff) * prime) + hash;
  hash = (((value >> 48) & 0xff) * prime) + hash;
  hash = (((value >> 56) & 0xff) * prime) + hash;
  return hash;
}

/* Checks of the given index is valid. */
template <typename SIZ>
inline BOL TIndexIsValid(SIZ index) {
  return index >= 0;
}

template <typename SIZ = SIN>
inline SIZ TTableEntryOverhead() {
  return 4 * sizeof(SIZ);
}

template <typename SIZ = SIN, typename Char = CHR, SIZ kCountMax = 32,
          SIZ kAverageStringLength = 16>
constexpr SIZ TTableSize() {
  return sizeof(TTable<SIZ>) + 4 * kCountMax * sizeof(SIZ) +
         kCountMax * (kAverageStringLength + 1);
}

template <typename SIZ = SIN, typename Char = CHR>
constexpr SIZ TTableSize(SIZ count_max, SIZ average_String_length = 24) {
  return sizeof(TTable<SIZ>) + 4 * count_max * sizeof(SIZ) +
         count_max * (average_String_length + 1);
}

template <typename SIZ = SIN, typename Char = CHR>
inline Char* TTableKeysStop(TTable<SIZ>* table, SIZ size_bytes) {
  return TPtr<Char>(table, size_bytes) - 1;
}

#if USING_STR
/* Prints this object out to the console. */
template <typename Printer, typename SIZ = SIN, typename HSH = UIN,
          typename Char = CHR>
Printer& TTablePrint(Printer& o, TTable<SIZ>* table) {
  D_ASSERT(table);
  enum {
    kHashWidth = (sizeof(HSH) * 2) < 10 ? 10 : (sizeof(HSH) * 2),
  };
  SIZ count = table->count,            //
      count_max = table->count_max,    //
      collision_pile_index,            //
      size_bytes = table->size_bytes,  //
      size_pile = table->size_pile;    //

  SIN count_length_max = STRLength(count_max);
  count_length_max = (count_length_max < 2 ? 2 : count_length_max);
  o << Linef("\n+---\n| Table<SI") << CH1('0' + sizeof(SIZ)) << ",UI"
    << CH1('0' + sizeof(HSH)) << ",CH" << CH1('0' + sizeof(Char)) << ">:0x"
    << Hexf(table) << " size_bytes:" << size_bytes << " key_count:" << count
    << " count_max:" << count_max << " size_pile:" << size_pile
    << Linef("\n+---\n| ") << Rightf("i", count_length_max)  //
    << Centerf("hash_e", kHashWidth - 2) << Centerf("hash_u", kHashWidth - 2)
    << Centerf("hash_s", kHashWidth - 2) << Centerf("index_u", kHashWidth)
    << Centerf("offset", 8) << Linef(" \"Key\":{Collissions}\n+---");

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes) - 1;

  for (SIZ i = 0; i < count; ++i) {
    o << "\n| " << Rightf(i, count_length_max)  //
      << Centerf().Hex(THashPrime<HSH, Char>(keys - key_offsets[i]), kHashWidth)
      << Centerf().Hex(hashes[unsorted_indexes[i]], kHashWidth)
      << Centerf().Hex(hashes[i], kHashWidth)
      << Centerf(unsorted_indexes[i], kHashWidth) << Centerf(key_offsets[i], 8)
      << " \"" << (keys - key_offsets[i]) << "\":{";

    collision_pile_index = collision_indexes[i];
    if (TIndexIsValid<SIZ>(collision_pile_index) && (i < count)) {
      SIZ *collision_pile = unsorted_indexes + count_max,
          *collision_begin = collision_pile + collision_pile_index;
      SIZ collision = *collision_begin++;
      o << collision;
      while (TIndexIsValid<SIZ>(collision)) {
        collision = *collision_begin++;
        if (TIndexIsValid<SIZ>(collision)) o << ", " << collision;
      }
    }
    o << '}';
  }
#if D_THIS
  return o << Linef("\n+---") << Charsf(table, table->size_bytes) << '\n';
#endif
  return o << Linef("\n+---\n");
#endif
}  // namespace _

/* Creates a streamable hash table with enough socket space for the
count_max. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
TTable<SIZ>* TTableInit(TTable<SIZ>* table, SIZ height, SIZ size_bytes) {
  D_ASSERT(table);

  SIZ array_sizes = height * TTableEntryOverhead<SIZ>() + sizeof(TTable<SIZ>),
      min_required_size = 2 * height;
  min_required_size += array_sizes;
  D_COUT("\nCreating a TTable<> with size_bytes:"
         << size_bytes << " size:" << height
         << " min_required_size:" << min_required_size);

  if (size_bytes < min_required_size) {
    D_COUT("\nTable init failed because size_bytes < min_required_size");
    return nullptr;
  }

  D_ARRAY_WIPE(table, size_bytes);

  table->count = 0;
  table->count_max = height;
  table->size_pile = 0;
  table->size_bytes = size_bytes;
  D_COUT_TABLE(table);
  return table;
}

template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
inline TTable<SIZ>* TTableInit(UIW* socket, HSH count_max, SIZ size) {
  auto table = reinterpret_cast<TTable<SIZ>*>(socket);
  return TTableInit<SIZ, HSH, Char>(table, count_max, size);
}

/* Adds the key to the table.
@return An invalid index upon failure or valid index upon success. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableAdd(TTable<SIZ>* table, const Char* key) {
  D_ASSERT(table);
  D_ASSERT(key);

  SIZ count = table->count, count_max = table->count_max,
      size_bytes = table->size_bytes;

  if (count >= count_max)
    return CInvalidIndex<SIZ>();  //< We're out of buffered indexes.

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max,
      *collision_pile = unsorted_indexes + count_max;
  Char *keys = TPtr<Char>(table, size_bytes) - 1, *destination;
  HSH hash = THashPrime<HSH, Char>(key), current_hash;
  SIZ key_length = TSTRLength<Char, SIZ>(key);
  Char* bottom = reinterpret_cast<Char*>(collision_pile + table->size_pile) + 1;

  D_COUT("\n\nAdding        key:\"" << key <<                             //
         "\"\n             hash:0x" << Hexf(hash) <<                      //
         "\n           length:" << key_length <<                          //
         "\n           hashes:" << TDelta<>(table, hashes) <<             //
         "\n      key_offsets:" << TDelta<>(table, key_offsets) <<        //
         "\ncollision_indexes:" << TDelta<>(table, collision_indexes) <<  //
         "\n           bottom:" << TDelta<>(table, bottom) <<             //
         "\n             keys:" << TDelta<>(table, keys) <<               //
         "\n       space_left:" << keys - bottom <<                       //
         "\n       size_bytes:" << size_bytes);

  if (count == 0) {
    *hashes = hash;
    *collision_indexes = CInvalidIndex<SIZ>();
    *unsorted_indexes = 0;
    destination = keys - key_length;
    D_COUT("\n      destination:" << TDelta<>(table, destination) <<  //
           "\n       key_offset:" << TDelta<>(destination, keys));

    if (!TSPrintString<Char>(destination, keys, key)) {
      D_COUT("\nKey buffer overflow printing string when count:0");
      return CInvalidIndex<SIZ>();
    }
    SIZ key_offset = SIZ(keys - destination);
    key_offsets[count] = key_offset;
    D_COUT("\n\nAdded the first key_offset:" << key_offset);
    table->count = 1;
    D_COUT_TABLE(table);
    return count;
  };

  Char* top = keys - key_offsets[count - 1] - 1;
  destination = top - key_length;
  D_COUT("\n           bottom:" << TDelta<>(table, bottom) <<       //
         "\n      destination:" << TDelta<>(table, destination) <<  //
         "\n       key_offset:" << TDelta<>(destination, keys) <<   //
         "\n              top:" << TDelta<>(table, top));

  SIZ key_offset = SIZ(keys - destination);
  if (!TSPrintString<Char>(destination, keys, key)) {
    D_COUT("\nKey buffer overflow printing key.");
    return CInvalidIndex<SIZ>();
  }
  key_offsets[count] = key_offset;
  D_COUT("\n       key_offset:" << key_offset <<  //
         "\n\nFinding insert location... ");

  SIZ low = 0, mid = 0, high = count;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_hash = hashes[mid];
    D_COUT("\n   low:" << low << " mid:" << mid << " high:" << high
                       << " hash:0x" << Hexf(current_hash));

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {
      SIZ unsorted_index = unsorted_indexes[mid],
          collision_index = collision_indexes[unsorted_index];
      D_COUT(" Found hash at unsorted_index:"
             << unsorted_index << " collision_index:" << collision_index);
      if (TIndexIsValid<SIZ>(collision_index)) {
        D_COUT("\n       Found collision. Checking the collision_pile...");

        SIZ* collision_pile = unsorted_indexes + count_max;
        SIZ* collision_cursor = collision_pile + collision_index;
        SIZ collision = *collision_cursor++;
        while (collision < 0) {
          SIZ offset = key_offsets[collision];
          D_COUT("comparing to \"" << keys - offset << "\". ");
          if (TSTREquals<Char>(key, keys - offset)) {
            D_COUT(" Found key at offset:" << collision);
            return collision_index;
          }
          collision_index = *collision_cursor++;
        }
        D_COUT("\n    New collision detected. Updating the collision_pile...");
        SIZ size_pile = table->size_pile;
        TStackInsert<SIZ>(collision_pile, count, collision_index, size_pile);
        table->size_pile = size_pile + 1;
        collision_indexes[count] = collision_index;
        unsorted_indexes[count] = count;

        D_COUT("\n\n    Inserted at collision_index:" << collision_index);
        table->count = count + 1;
        D_COUT_TABLE(table);
        return count;
      }
      key_offset = key_offsets[unsorted_index];
      Char* other_key = keys - key_offset;
      D_COUT("\n     No collisions exist.\n     Comparing to "
             << unsorted_index << ":\"" << other_key
             << "\" at key_offset:" << key_offset);
      if (!TSTREquals<Char>(key, other_key)) {
        SIZ size_pile = table->size_pile;
        D_COUT("\n       New collision with unsorted_index:"
               << unsorted_index << " size_pile:" << size_pile
               << " count:" << count);
        collision_indexes[unsorted_index] = size_pile;
        collision_indexes[count] = size_pile;
        SIZ* collision_pile_top = collision_pile + size_pile;

        *collision_pile_top++ = unsorted_index;
        *collision_pile_top++ = count;
        *collision_pile_top = CInvalidIndex<SIZ>();

        table->size_pile = size_pile + 3;
        table->count = count + 1;
        D_COUT_TABLE(table);
        return count;
      }
      D_COUT("\nTable already contains the key.");
      return CInvalidIndex<SIZ>();
    }
  }
  D_COUT("\n\nHash not found. Inserting into mid:" << mid << " before hash:0x"
                                                   << Hexf(hashes[mid]));

  TStackInsert<HSH>(hashes, count, mid, hash);
  collision_indexes[count] = CInvalidIndex<SIZ>();
  TStackInsert<SIZ>(unsorted_indexes, count, mid, count);
  table->count = count + 1;
  D_COUT_TABLE(table);
  return count;
}

/* Attempts to find the given key.
@return Returns TTableInvalidIndex<SIZ>() upon failure, and valid index upon
success. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableFind(const TTable<SIZ>* table, const Char* key) {
  D_ASSERT(table);
  SIZ count = table->count, count_max = table->count_max;

  if (!key || count == 0) return CInvalidIndex<SIZ>();

  SIZ size_bytes = table->size_bytes;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes) - 1;

  HSH hash = THashPrime<HSH, Char>(key);

  D_COUT("\n\nSearching for key:\"" << key << "\"\n             hash:0x"
                                    << Hexf(hash) << "...");

  if (count == 1) {
    SIZ offset = key_offsets[0];
    D_COUT("\nComparing to only key \"" << keys - offset << "\"...");
    if (TSTREquals<Char>(key, keys - offset)) {
      D_COUT("hit at offset:" << offset);
      return 0;
    }
    if (!TSTREquals<Char>(key, keys - offset)) {
      D_COUT("key not found.");
      return CInvalidIndex<SIZ>();
    }
    D_COUT("Found key:\"" << key << '\"' << Linef('-'));
    return 0;
  }

  // Perform a binary search to find the hash. If the mid is odd, we need to
  // subtract the sizeof (HSH*) in order to get the right pointer address.
  SIZ low = 0, mid, high = count - 1;

  while (low <= high) {
    mid = (low + high) >> 1;  //< >> 1 to /2

    HSH current_hash = hashes[mid];
    D_COUT("\n  low:" << low << " mid:" << mid << " high:" << high
                      << " hashes[mid]:" << Hexf(hashes[mid]));
    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {
      SIZ unsorted_index = unsorted_indexes[mid],
          collision_index = collision_indexes[unsorted_index];
      D_COUT("\n    Found hash[" << mid << "]:0x" << Hexf(hashes[mid])
                                 << " unsorted_index:" << unsorted_index
                                 << " collision_index:" << collision_index);

      if (TIndexIsValid<SIZ>(collision_index)) {
        D_COUT("\n    Collision detected at collision_index:"
               << collision_index << ". Checking the collision_pile...");

        // The collision_pile is a sequence of indexes terminated by
        // an invalid index > kMaxNumOps. collissionsList[0] is an
        // invalid index, so the collision_pile is searched from
        // lower address up.

        SIZ *collision_pile = unsorted_indexes + count_max,
            *collision_cursor =
                collision_pile + collision_indexes[unsorted_index];
        collision_index = *collision_cursor++;

        while (TIndexIsValid<SIZ>(collision_index)) {
          SIZ key_offset = key_offsets[collision_index];
          D_COUT("\n      Comparing to:\"" << keys - key_offset
                                           << "\" at offset:" << key_offset);
          if (TSTREquals<Char>(key, keys - key_offset)) {
            D_COUT(". Hit at index:" << collision_index
                                     << " offset:" << key_offset);
            return collision_index;
          }
          collision_index = *collision_cursor++;
        }
        D_COUT(Linef("\n      collision_pile does not contain the key.\n---"));
        return CInvalidIndex<SIZ>();
      }

      SIZ key_offset = key_offsets[unsorted_index];
      Char* other_key = keys - key_offsets[unsorted_index];
      D_COUT("\n    Comparing to key:\"" << other_key << '"');

      if (!TSTREquals<Char>(key, other_key)) {
        D_COUT("\n    Table does not contain key.");
        return CInvalidIndex<SIZ>();
      }

      D_COUT("\n    Found key at unsorted_index:" << unsorted_index);
      return unsorted_index;
    }
  }
  D_COUT(Linef("\nTable does not contain the hash.\n---"));

  return CInvalidIndex<SIZ>();
}

/* Gets the given key.
@return Returns the index it go inserted into. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableGet(TTable<SIZ>* table, SIZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  SIZ count = table->count;
  if (index < 0 || index >= count) return CInvalidIndex<SIZ>();

  SIZ size_bytes = table->size_bytes, count_max = table->count_max, temp;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes) - 1;
}

/* Removes the string at the given index. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableRemove(TTable<SIZ>* table, SIZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  SIZ count = table->count;
  if (index < 0 || index >= count) return CInvalidIndex<SIZ>();

  SIZ size_bytes = table->size_bytes, count_max = table->count_max, temp;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes) - 1;

  // Algorithm:
  // 1. Remove the hashes.
  // 2. Remove the key offsets.
  // 3. Remove from collision indexes.
  // 4. Remove from unsorted indexes.
  // 5. Remove from collisions list.
  return count;
}

/* Removes the given key from the table. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableRemove(TTable<SIZ>* table, const Char* key) {
  SIZ index = TTableFind<SIZ, HSH, Char>(table, key);
  return TTableRemove<SIZ, HSH, Char>(table, index);
}

/* An ASCII Table Autoject. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR,
          SIZ kCountMax_ = 32,
          typename BUF =
              TUIB<TTableSize<SIZ, Char, kCountMax_>(), SI1, SIZ, TTable<SIZ>>>
class ATable {
  AArray<Char, SIZ, BUF> obj_;  //< Auto-Array of Char(s).
 public:
  /* Constructs a Table.
  @param factory SocketFactory to call when the Strand overflows. */
  ATable() {
    SIZ size_bytes = TTableSize<SIZ, Char, kCountMax_>();
    D_ARRAY_WIPE(obj_.Begin(), size_bytes);
    TTableInit<SIZ, HSH, Char>(obj_.Begin(), kCountMax_, size_bytes);
  }

  /* Constructs a Table.
  @param factory SocketFactory to call when the Strand overflows. */
  ATable(SIZ count_max) {
    SIZ size_bytes = TTableSize<SIZ, Char, count_max>();
    D_ARRAY_WIPE(obj_.Begin(), size_bytes);
    TTableInit<SIZ, HSH, Char>(obj_.Begin(), count_max, size_bytes);
  }

  /* Deep copies the given string into the Table.
  @return The index of the string in the Table. */
  inline SIZ Add(const Char* string) {
    return TTableAdd<SIZ, HSH, Char>(This(), string);
  }

  /* Removes the string at the given index from the Table. */
  inline SIZ Remove(SIZ index) {
    return TTableRemove<SIZ, HSH, Char>(This(), index);
  }

  /* Removes the string at the given index from the Table. */
  inline SIZ Remove(const Char* key) {
    return TTableRemove<SIZ, HSH, Char>(This(), key);
  }

  /* Gets the string at the given index. */
  inline Char* Get(SIZ index) {
    return TTableGet<SIZ, HSH, Char>(This(), index);
  }

  inline SIZ Find(const Char* string) {
    return TTableFind<SIZ, HSH, Char>(This(), string);
  }

  /* Gets the ASCII Object. */
  inline TTable<SIZ>* This() { return obj_.BeginAs<TTable<SIZ>>(); }

  /* Gets the Auto-Array. */
  inline AArray<Char, SIZ, BUF>& Array() { return obj_; }

#if USING_STR
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TTablePrint<Printer, SIZ, HSH, Char>(o, This());
  }

  inline void CPrint() { PrintTo<_::COut>(_::COut().Star()); }
#endif
};

}  // namespace _
#undef D_COUT_TABLE
#endif
#endif
