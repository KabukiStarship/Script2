/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Table.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_Config.h>

#if SEAM >= SCRIPT2_TABLE

#ifndef SCRIPTT2_TABLE_T
#define SCRIPTT2_TABLE_T

#include "Array.hpp"
#include "Binary.hpp"
#include "Uniprinter.hpp"

#if SEAM == SCRIPT2_TABLE
#include "_Debug.inl"
#else
#include "_Release.inl"
#define D_COUT_TABLE(item)
#endif

namespace _ {

/* A dense key-index map.
@see ASCII Data Type Specification.
@link ./spec/data/map_types/table.md

# Collision Table

Collision table works by using the maximum key value (i.e. 255 for a ISZ,
2^15TTableInvalidIndex<ISZ>() for a ISB, etc). The collisions list is a sequence
of indexes terminated by an invalid index that is greater than cMaxNumOps.
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
template <typename ISZ>
struct TTable {
  ISZ size_bytes,  //< Size of this object in bytes.
      size_pile,   //< Size of the collision table pile.
      count,       //< Number of keys.
      count_max;   //< Number of buffered indexes.
};

enum {
  cMinTableSize = 64,  //< Min size of a Table
};

/* Returns the highest signed prime that can fit in type IS.
@return 0 if the sizeof (IS) is not 1, 2, 4, or 8.  */
template <typename IS>
inline IS PrimeMaxSigned() {
  IS prime = (sizeof(IS) == 1)
                 ? 127
                 : (sizeof(IS) == 2)
                       ? 32767
                       : (sizeof(IS) == 4)
                             ? 2147483647
                             : (sizeof(IS) == 8) ? 9223372036854775783 : 0;
  return prime;
}

/* Returns the highest signed prime that can fit in type IU.
@return 0 if the sizeof (IU) is not 1, 2, 4, or 8. */
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

template <typename HSH, typename CHT = CHR>
inline HSH THashPrime(CHT value, HSH hash) {
  return hash + hash * (HSH)value;
}

template <typename HSH = IUN, typename CHT = CHR>
inline HSH THashPrime(const CHT* str) {
  CHT c = (CHT)*str++;
  HSH hash = TPrimeMaxUnigned<HSH>();
  while (c) {
    hash = THashPrime<HSH, CHT>(c, hash);
    c = *str++;
  }
  return hash;
}

inline IUB HashIUB(IUB value, IUB hash) {
  IUB prime = TPrimeMaxUnigned<IUB>();
  hash = ((value & 0xff) * prime) + hash;
  hash = ((value >> 8) * prime) + hash;
  return hash;
}

inline IUB HashIUB(IUC value, IUB hash) {
  IUB prime = TPrimeMaxUnigned<IUB>();
  hash = ((value & 0xff) * prime) + hash;
  hash = (((value >> 8) & 0xff) * prime) + hash;
  hash = (((value >> 16) & 0xff) * prime) + hash;
  hash = (((value >> 24) & 0xff) * prime) + hash;
  return hash;
}

inline IUB HashIUB(IUD value, IUB hash) {
  IUB prime = TPrimeMaxUnigned<IUB>();
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
template <typename ISZ>
inline BOL TIndexIsValid(ISZ index) {
  return index >= 0;
}

template <typename ISZ = ISN>
inline ISZ TTableEntryOverhead() {
  return 4 * sizeof(ISZ);
}

template <typename ISZ = ISN, typename CHT = CHR, ISZ cCountMax = 32,
          ISZ cAverageStringLength = 16>
constexpr ISZ CTableSize() {
  return sizeof(TTable<ISZ>) + 4 * cCountMax * sizeof(ISZ) +
         cCountMax * (cAverageStringLength + 1);
}

template <typename ISZ = ISN, typename CHT = CHR>
constexpr ISZ CTableSize(ISZ count_max, ISZ average_string_length = 24) {
  return sizeof(TTable<ISZ>) + 4 * count_max * sizeof(ISZ) +
         count_max * (average_string_length + 1);
}

template <typename ISZ = ISN, typename CHT = CHR>
inline CHT* TTableKeysStop(TTable<ISZ>* table, ISZ size_bytes) {
  return TPtr<CHT>(table, size_bytes) - 1;
}

#if USING_STR
/* Prints this object out to the console. */
template <typename Printer, typename ISZ = ISN, typename HSH = IUN,
          typename CHT = CHR>
Printer& TTablePrint(Printer& o, TTable<ISZ>* table) {
  D_ASSERT(table);
  enum {
    cHashWidth = (sizeof(HSH) * 2) < 10 ? 10 : (sizeof(HSH) * 2),
  };
  ISZ count = table->count,            //
      count_max = table->count_max,    //
      collision_pile_index,            //
      size_bytes = table->size_bytes,  //
      size_pile = table->size_pile;    //

  ISN count_length_max = STRLength(count_max);
  count_length_max = (count_length_max < 2 ? 2 : count_length_max);
  o << Linef("\n+---\n| Table<IS") << CHA('0' + sizeof(ISZ)) << ",IU"
    << CHA('0' + sizeof(HSH)) << ",CH" << CHA('0' + sizeof(CHT)) << ">:0x"
    << Hexf(table) << " size_bytes:" << size_bytes << " key_count:" << count
    << " count_max:" << count_max << " size_pile:" << size_pile
    << Linef("\n+---\n| ") << Rightf("i", count_length_max)  //
    << Centerf("hash_e", cHashWidth - 2) << Centerf("hash_u", cHashWidth - 2)
    << Centerf("hash_s", cHashWidth - 2) << Centerf("index_u", cHashWidth)
    << Centerf("offset", 8) << Linef(" \"Key\":{Collissions}\n+---");

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CHA>(table, sizeof(TTable<ISZ>)));
  ISZ *key_offsets = reinterpret_cast<ISZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  CHT* keys = TPtr<CHT>(table, size_bytes) - 1;

  for (ISZ i = 0; i < count; ++i) {
    o << "\n| " << Rightf(i, count_length_max)  //
      << Centerf().Hex(THashPrime<HSH, CHT>(keys - key_offsets[i]), cHashWidth)
      << Centerf().Hex(hashes[unsorted_indexes[i]], cHashWidth)
      << Centerf().Hex(hashes[i], cHashWidth)
      << Centerf(unsorted_indexes[i], cHashWidth) << Centerf(key_offsets[i], 8)
      << " \"" << (keys - key_offsets[i]) << "\":{";

    collision_pile_index = collision_indexes[i];
    if (TIndexIsValid<ISZ>(collision_pile_index) && (i < count)) {
      ISZ *collision_pile = unsorted_indexes + count_max,
          *collision_begin = collision_pile + collision_pile_index;
      ISZ collision = *collision_begin++;
      o << collision;
      while (TIndexIsValid<ISZ>(collision)) {
        collision = *collision_begin++;
        if (TIndexIsValid<ISZ>(collision)) o << ", " << collision;
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
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
TTable<ISZ>* TTableInit(TTable<ISZ>* table, ISZ height, ISZ size_bytes) {
  D_ASSERT(table);

  ISZ array_sizes = height * TTableEntryOverhead<ISZ>() + sizeof(TTable<ISZ>),
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

template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
inline TTable<ISZ>* TTableInit(IUW* socket, HSH count_max, ISZ size) {
  auto table = reinterpret_cast<TTable<ISZ>*>(socket);
  return TTableInit<ISZ, HSH, CHT>(table, count_max, size);
}

/* Adds the key to the table.
@return An invalid index upon failure or valid index upon success. */
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
ISZ TTableAdd(TTable<ISZ>* table, const CHT* key) {
  D_ASSERT(table);
  D_ASSERT(key);

  ISZ count = table->count, count_max = table->count_max,
      size_bytes = table->size_bytes;

  if (count >= count_max)
    return CInvalidIndex<ISZ>();  //< We're out of buffered indexes.

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CHA>(table, sizeof(TTable<ISZ>)));
  ISZ* key_offsets = reinterpret_cast<ISZ*>(hashes + count_max),
     * collision_indexes = key_offsets + count_max,
     * unsorted_indexes = collision_indexes + count_max,
     * collision_pile = unsorted_indexes + count_max;
  CHT *keys = TPtr<CHT>(table, size_bytes) - 1, *destination;
  HSH hash = THashPrime<HSH, CHT>(key), current_hash;
  ISZ key_length = TSTRLength<CHT, ISZ>(key);
  CHT* bottom = reinterpret_cast<CHT*>(collision_pile + table->size_pile) + 1;

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
    *collision_indexes = CInvalidIndex<ISZ>();
    *unsorted_indexes = 0;
    destination = keys - key_length;
    D_COUT("\n      destination:" << TDelta<>(table, destination) <<  //
           "\n       key_offset:" << TDelta<>(destination, keys));

    if (!TSPrintString<CHT>(destination, keys, key)) {
      D_COUT("\nKey buffer overflow printing string when count:0");
      return CInvalidIndex<ISZ>();
    }
    ISZ key_offset = ISZ(keys - destination);
    key_offsets[count] = key_offset;
    D_COUT("\n\nAdded the first key_offset:" << key_offset);
    table->count = 1;
    D_COUT_TABLE(table);
    return count;
  };

  CHT* top = keys - key_offsets[count - 1] - 1;
  destination = top - key_length;
  D_COUT("\n           bottom:" << TDelta<>(table, bottom) <<       //
         "\n      destination:" << TDelta<>(table, destination) <<  //
         "\n       key_offset:" << TDelta<>(destination, keys) <<   //
         "\n              top:" << TDelta<>(table, top));

  ISZ key_offset = ISZ(keys - destination);
  if (!TSPrintString<CHT>(destination, keys, key)) {
    D_COUT("\nKey buffer overflow printing key.");
    return CInvalidIndex<ISZ>();
  }
  key_offsets[count] = key_offset;
  D_COUT("\n       key_offset:" << key_offset <<  //
         "\n\nFinding insert location... ");

  ISZ low = 0, mid = 0, high = count;

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
      ISZ unsorted_index = unsorted_indexes[mid],
          collision_index = collision_indexes[unsorted_index];
      D_COUT(" Found hash at unsorted_index:"
             << unsorted_index << " collision_index:" << collision_index);
      if (TIndexIsValid<ISZ>(collision_index)) {
        D_COUT("\n       Found collision. Checking the collision_pile...");

        ISZ* collision_pile = unsorted_indexes + count_max;
        ISZ* collision_cursor = collision_pile + collision_index;
        ISZ collision = *collision_cursor++;
        while (collision < 0) {
          ISZ offset = key_offsets[collision];
          D_COUT("comparing to \"" << keys - offset << "\". ");
          if (TSTREquals<CHT>(key, keys - offset)) {
            D_COUT(" Found key at offset:" << collision);
            return collision_index;
          }
          collision_index = *collision_cursor++;
        }
        D_COUT("\n    New collision detected. Updating the collision_pile...");
        ISZ size_pile = table->size_pile;
        TStackInsert<ISZ>(collision_pile, count, collision_index, size_pile);
        table->size_pile = size_pile + 1;
        collision_indexes[count] = collision_index;
        unsorted_indexes[count] = count;

        D_COUT("\n\n    Inserted at collision_index:" << collision_index);
        table->count = count + 1;
        D_COUT_TABLE(table);
        return count;
      }
      key_offset = key_offsets[unsorted_index];
      CHT* other_key = keys - key_offset;
      D_COUT("\n     No collisions exist.\n     Comparing to "
             << unsorted_index << ":\"" << other_key
             << "\" at key_offset:" << key_offset);
      if (!TSTREquals<CHT>(key, other_key)) {
        ISZ size_pile = table->size_pile;
        D_COUT("\n       New collision with unsorted_index:"
               << unsorted_index << " size_pile:" << size_pile
               << " count:" << count);
        collision_indexes[unsorted_index] = size_pile;
        collision_indexes[count] = size_pile;
        ISZ* collision_pile_top = collision_pile + size_pile;

        *collision_pile_top++ = unsorted_index;
        *collision_pile_top++ = count;
        *collision_pile_top = CInvalidIndex<ISZ>();

        table->size_pile = size_pile + 3;
        table->count = count + 1;
        D_COUT_TABLE(table);
        return count;
      }
      D_COUT("\nTable already contains the key.");
      return CInvalidIndex<ISZ>();
    }
  }
  D_COUT("\n\nHash not found. Inserting into mid:" << mid << " before hash:0x"
                                                   << Hexf(hashes[mid]));

  TStackInsert<HSH>(hashes, count, mid, hash);
  collision_indexes[count] = CInvalidIndex<ISZ>();
  TStackInsert<ISZ>(unsorted_indexes, count, mid, count);
  table->count = count + 1;
  D_COUT_TABLE(table);
  return count;
}

/* Attempts to find the given key.
@return Returns TTableInvalidIndex<ISZ>() upon failure, and valid index upon
success. */
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
ISZ TTableFind(const TTable<ISZ>* table, const CHT* key) {
  D_ASSERT(table);
  ISZ count = table->count, count_max = table->count_max;

  if (!key || count == 0) return CInvalidIndex<ISZ>();

  ISZ size_bytes = table->size_bytes;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CHA>(table, sizeof(TTable<ISZ>)));
  ISZ *key_offsets = reinterpret_cast<ISZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  CHT* keys = TPtr<CHT>(table, size_bytes) - 1;

  HSH hash = THashPrime<HSH, CHT>(key);

  D_COUT("\n\nSearching for key:\"" << key << "\"\n             hash:0x"
                                    << Hexf(hash) << "...");

  if (count == 1) {
    ISZ offset = key_offsets[0];
    D_COUT("\nComparing to only key \"" << keys - offset << "\"...");
    if (TSTREquals<CHT>(key, keys - offset)) {
      D_COUT("hit at offset:" << offset);
      return 0;
    }
    if (!TSTREquals<CHT>(key, keys - offset)) {
      D_COUT("key not found.");
      return CInvalidIndex<ISZ>();
    }
    D_COUT("Found key:\"" << key << '\"' << Linef('-'));
    return 0;
  }

  // Perform a binary search to find the hash. If the mid is odd, we need to
  // subtract the sizeof (HSH*) in order to get the right pointer address.
  ISZ low = 0, mid, high = count - 1;

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
      ISZ unsorted_index = unsorted_indexes[mid],
          collision_index = collision_indexes[unsorted_index];
      D_COUT("\n    Found hash[" << mid << "]:0x" << Hexf(hashes[mid])
                                 << " unsorted_index:" << unsorted_index
                                 << " collision_index:" << collision_index);

      if (TIndexIsValid<ISZ>(collision_index)) {
        D_COUT("\n    Collision detected at collision_index:"
               << collision_index << ". Checking the collision_pile...");

        // The collision_pile is a sequence of indexes terminated by
        // an invalid index > cMaxNumOps. collissionsList[0] is an
        // invalid index, so the collision_pile is searched from
        // lower address up.

        ISZ *collision_pile = unsorted_indexes + count_max,
            *collision_cursor =
                collision_pile + collision_indexes[unsorted_index];
        collision_index = *collision_cursor++;

        while (TIndexIsValid<ISZ>(collision_index)) {
          ISZ key_offset = key_offsets[collision_index];
          D_COUT("\n      Comparing to:\"" << keys - key_offset
                                           << "\" at offset:" << key_offset);
          if (TSTREquals<CHT>(key, keys - key_offset)) {
            D_COUT(". Hit at index:" << collision_index
                                     << " offset:" << key_offset);
            return collision_index;
          }
          collision_index = *collision_cursor++;
        }
        D_COUT(Linef("\n      collision_pile does not contain the key.\n---"));
        return CInvalidIndex<ISZ>();
      }

      ISZ key_offset = key_offsets[unsorted_index];
      CHT* other_key = keys - key_offsets[unsorted_index];
      D_COUT("\n    Comparing to key:\"" << other_key << '"');

      if (!TSTREquals<CHT>(key, other_key)) {
        D_COUT("\n    Table does not contain key.");
        return CInvalidIndex<ISZ>();
      }

      D_COUT("\n    Found key at unsorted_index:" << unsorted_index);
      return unsorted_index;
    }
  }
  D_COUT(Linef("\nTable does not contain the hash.\n---"));

  return CInvalidIndex<ISZ>();
}

/* Gets the given key.
@return Returns the index it go inserted into. */
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
ISZ TTableGet(TTable<ISZ>* table, ISZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  ISZ count = table->count;
  if (index < 0 || index >= count) return CInvalidIndex<ISZ>();

  ISZ size_bytes = table->size_bytes, count_max = table->count_max, temp;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CHA>(table, sizeof(TTable<ISZ>)));
  ISZ *key_offsets = reinterpret_cast<ISZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  CHT* keys = TPtr<CHT>(table, size_bytes) - 1;
}

/* Removes the string at the given index. */
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
ISZ TTableRemove(TTable<ISZ>* table, ISZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  ISZ count = table->count;
  if (index < 0 || index >= count) return CInvalidIndex<ISZ>();

  ISZ size_bytes = table->size_bytes, count_max = table->count_max, temp;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CHA>(table, sizeof(TTable<ISZ>)));
  ISZ *key_offsets = reinterpret_cast<ISZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  CHT* keys = TPtr<CHT>(table, size_bytes) - 1;

  // Algorithm:
  // 1. Remove the hashes.
  // 2. Remove the key offsets.
  // 3. Remove from collision indexes.
  // 4. Remove from unsorted indexes.
  // 5. Remove from collisions list.
  return count;
}

/* Removes the given key from the table. */
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR>
ISZ TTableRemove(TTable<ISZ>* table, const CHT* key) {
  ISZ index = TTableFind<ISZ, HSH, CHT>(table, key);
  return TTableRemove<ISZ, HSH, CHT>(table, index);
}

/* An ASCII Table Autoject. */
template <typename ISZ = ISN, typename HSH = IUN, typename CHT = CHR,
          ISZ cCountMax = 32,
          typename BUF =
              TBUF<CTableSize<ISZ, CHT, cCountMax>(), ISA, ISZ, TTable<ISZ>>>
class ATable {
  AArray<CHT, ISZ, BUF> obj_;  //< Auto-Array of CHT(s).
 public:
  /* Constructs a Table.
  @param factory SocketFactory to call when the String overflows. */
  ATable() {
    ISZ size_bytes = CTableSize<ISZ, CHT, cCountMax>();
    D_ARRAY_WIPE(obj_.Origin(), size_bytes);
    TTableInit<ISZ, HSH, CHT>(obj_.Origin(), cCountMax, size_bytes);
  }

  /* Constructs a Table.
  @param factory SocketFactory to call when the String overflows. */
  ATable(ISZ count_max) {
    ISZ size_bytes = CTableSize<ISZ, CHT, count_max>();
    D_ARRAY_WIPE(obj_.Origin(), size_bytes);
    TTableInit<ISZ, HSH, CHT>(obj_.Origin(), count_max, size_bytes);
  }

  /* Deep copies the given string into the Table.
  @return The index of the string in the Table. */
  inline ISZ Add(const CHT* string) {
    return TTableAdd<ISZ, HSH, CHT>(This(), string);
  }

  /* Removes the string at the given index from the Table. */
  inline ISZ Remove(ISZ index) {
    return TTableRemove<ISZ, HSH, CHT>(This(), index);
  }

  /* Removes the string at the given index from the Table. */
  inline ISZ Remove(const CHT* key) {
    return TTableRemove<ISZ, HSH, CHT>(This(), key);
  }

  /* Gets the string at the given index. */
  inline CHT* Get(ISZ index) {
    return TTableGet<ISZ, HSH, CHT>(This(), index);
  }

  inline ISZ Find(const CHT* string) {
    return TTableFind<ISZ, HSH, CHT>(This(), string);
  }

  /* Gets the ASCII Object. */
  inline TTable<ISZ>* This() { return obj_.OriginAs<TTable<ISZ>*>(); }

  /* Gets the Auto-Array. */
  inline AArray<CHT, ISZ, BUF>& Array() { return obj_; }

#if USING_STR
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TTablePrint<Printer, ISZ, HSH, CHT>(o, This());
  }

  inline void CPrint() { PrintTo<_::COut>(_::COut().Star()); }
#endif
};

}  // namespace _
#undef D_COUT_TABLE
#endif
#endif
