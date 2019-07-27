/* SCRIPT Script @version 0.x
@file    /script2/t_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_TABLE

#ifndef SCRIPTT2_TABLE_T
#define SCRIPTT2_TABLE_T

#include "c_socket.h"
#include "t_array.h"
#include "t_hash.h"
#include "t_socket.h"
#include "t_uniprinter.h"

#if SEAM == SCRIPT2_TABLE
#include "module_debug.inl"
#define D_COUT_TABLE(item) \
  TTablePrint<_::COut, SIZ, HSH, Char>(COut().Star(), item)
#else
#include "module_release.inl"
#define D_COUT_TABLE(item)
#endif

namespace _ {

/* A dense key-index map.
@see ASCII Data Type Specification for DRY documentation.
@link ./spec/data/map_types/table.md

# Collision Table

Collision table works by using the maximum key value (i.e. 255 for a SIZ,
2^15TTableInvalidIndex<SIZ>() for a SI2, etc). The collisions list is a sequence
of indexes terminated by an invalid index that is greater than kMaxNumOps.
collissionsList[0] is an invalid index, so the collisions list is searched
from lower address up.

## Memory Layout

@code
+--------------------------------------+
|_____ | Key 1                         |
|_____ v Key N                Keys     |
|+-------------------------------------+
|        Buffer                        |
|+-------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision List N   Collision  |
|_____ | Collision List 0     List     |
+--------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision Index N   Unsorted  |
|      | Collision Index 0   Indexes   |
|+-------------------------------------+
|_____   Buffer                        |
|_____ ^ Collision Index N  Collision  |
|      | Collision Index 0   Indexes   |
|+-------------------------------------+
|_____   Buffer Indexes                |
|_____ ^ Key Offset N          key     |
|      | Key Offset 1        Offsets   |
|+-------------------------------------+
|_____   Buffer Indexes                |
|_____ ^ Sorted hash N        Hashes   |
|      | Sorted Hash 1                 |
|+-------------------------------------+  ^ Up in addresses.
|            TTable Header             |  |
|+-------------------------------------+ 0x0
@endcode
*/
template <typename SIZ>
struct LIB_MEMBER TTable {
  SIZ size_bytes,  //< Size of this object in bytes.
      size_pile,   //< Size of the collision table pile.
      count,       //< Number of keys.
      count_max;   //< Number of buffered indexes.
};

enum {
  kMinTableSize = 64,  //< Min size of a Table
};

template <typename I>
inline I TInvalidIndex() {
  return -1;
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
constexpr SIZ TTableSize(SIZ count_max, SIZ average_string_length = 24) {
  return sizeof(TTable<SIZ>) + 4 * count_max * sizeof(SIZ) +
         count_max * (average_string_length + 1);
}

template <typename SIZ = SIN, typename Char = CHR>
inline Char* TTableKeysStop(TTable<SIZ>* table, SIZ size_bytes) {
  return TPtr<Char>(table, size_bytes) - 1;
}

/* Creates a streamable hash table with enough socket space for the
count_max. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
TTable<SIZ>* TTableInit(TTable<SIZ>* table, SIZ height, SIZ size_bytes) {
  D_ASSERT(table);

  SIZ array_sizes = height * TTableEntryOverhead<SIZ>() + sizeof(TTable<SIZ>),
      min_required_size = 2 * height;
  min_required_size += array_sizes;
  D_COUT("\nAttempting to create a TTable<> with size_bytes:"
         << size_bytes << " size:" << height
         << " min_required_size:" << min_required_size);

  if (size_bytes < min_required_size) {
    D_COUT("\nTable init failed because size_bytes < min_required_size");
    return nullptr;
  }

  D_SOCKET_WIPE(table, size_bytes);

  table->count = 0;
  table->count_max = height;
  table->size_pile = 0;
  table->size_bytes = size_bytes;
  return table;
}

template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
inline TTable<SIZ>* TTableInit(UIW* socket, HSH count_max, SIZ size) {
  auto table = reinterpret_cast<TTable<SIZ>*>(socket);
  return TTableInit<SIZ, HSH, Char>(table, count_max, size);
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
      collision_index, temp,           //
      size_bytes = table->size_bytes,  //
      size_pile = table->size_pile;    //

  SIN count_length_max = STRLength(count_max);
  count_length_max = (count_length_max < 2 ? 2 : count_length_max);
  o << Linef("\n+---") << "\n| Table<SI" << CH1('0' + sizeof(SIZ)) << ",UI"
    << CH1('0' + sizeof(HSH)) << ",CH" << CH1('0' + sizeof(Char)) << ">:0x"
    << Hexf(table) << " size_bytes:" << size_bytes << " key_count:" << count
    << " count_max:" << count_max << " size_pile:" << size_pile
    << Linef("\n+---\n| ") << Rightf("i", count_length_max)  //
    << Centerf("offset", 8) << Centerf("hash_e", kHashWidth)
    << Centerf("hash_u", kHashWidth) << Centerf("hash_s", kHashWidth)
    << Centerf("index_u", kHashWidth) << Linef(" \"Key\":{Collissions}\n+---");

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = reinterpret_cast<SIZ*>(key_offsets + count_max),
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes - sizeof(Char));

  for (SIZ i = 0; i < count; ++i) {
    o << "\n| " << Rightf(i, count_length_max)  //
      << Centerf(key_offsets[i], 8)
      << Centerf().Hex(THashPrime<HSH, Char>(keys - key_offsets[i]), kHashWidth)
      << Centerf().Hex(hashes[i], kHashWidth)
      << Centerf().Hex(hashes[unsorted_indexes[i]], kHashWidth)
      << Centerf(unsorted_indexes[i], kHashWidth) << " \""
      << (keys - key_offsets[i]) << "\":{";

    collision_index = collision_indexes[i];
    if ((collision_index >= 0) && (i < count)) {
      // Print collisions.
      SIZ *collision_list = unsorted_indexes + count_max,
          *begin = &collision_list[collision_index];

      temp = *begin;
      ++begin;
      o << temp;
      while (temp >= 0) {
        temp = *begin;
        ++begin;
        if (temp != TInvalidIndex<SIZ>()) o << ", " << temp;
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

/* Adds the given key.
@return Returns the index it go inserted into. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableAdd(TTable<SIZ>* table, const Char* key) {
  D_ASSERT(table);
  D_ASSERT(key);

  SIZ count = table->count, count_max = table->count_max,
      size_bytes = table->size_bytes, temp;

  if (count >= count_max)
    return TInvalidIndex<SIZ>();  //< We're out of buffered indexes.

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char *keys = TPtr<Char>(table, size_bytes) - 1, *destination;

  // Calculate space_left.
  SIZ key_length = TSTRLength<Char, SIZ>(key);

  HSH hash = THashPrime<HSH, Char>(key), current_hash;

  D_COUT("\nAdding key \"" << key << "\":" <<                             //
         "\n             hash:0x" << Hexf(hash) <<                        //
         "\n           hashes:" << TDelta<>(table, hashes) <<             //
         "\n      key_offsets:" << TDelta<>(table, key_offsets) <<        //
         "\ncollision_indexes:" << TDelta<>(table, collision_indexes) <<  //
         "\n             keys:" << TDelta<>(table, keys) <<               //
         "\n       size_bytes:" << size_bytes);

  if (count == 0) {
    *hashes = hash;
    *collision_indexes = TInvalidIndex<SIZ>();
    *unsorted_indexes = 0;
    // Check if there is enough room to print the string
    SIZ* collision_list = unsorted_indexes + count_max;
    Char* bottom =
        reinterpret_cast<Char*>(collision_list + table->size_pile) + 1;
    destination = keys - key_length;
    D_COUT("\n       space_left:" << keys - bottom <<            //
           "\n           bottom:" << TDelta<>(table, bottom) <<  //
           "\n      destination:" << TDelta<>(table, destination));

    if (!TSPrintString<Char>(destination, keys, key)) {
      D_COUT("\nKey buffer overflow printing string when count is 0.");
      return TInvalidIndex<SIZ>();
    }
    SIZ offset = SIZ(keys - destination);
    key_offsets[count] = offset;
    D_COUT("\nAdded key \"" << destination << "\" at offset:" << offset);
    table->count = 1;
    D_COUT_TABLE(table);
    return count;
  };

  SIZ* collision_list = unsorted_indexes + count_max;
  SIZ top_offset = key_offsets[count - 1];
  Char *bottom = reinterpret_cast<Char*>(collision_list + table->size_pile) + 1,
       *top = keys - top_offset - 1;
  destination = top - key_length;
  SIZ space_left = SIZ(top - bottom);
  D_COUT("\n       top_offset:" << top_offset <<                    //
         "\n           bottom:" << TDelta<>(table, bottom) <<       //
         "\n      destination:" << TDelta<>(table, destination) <<  //
         "\n              top:" << TDelta<>(table, top) <<          //
         "\n       space_left:" << top - bottom);

  SIZ offset = SIZ(keys - destination);
  if (!TSPrintString<Char>(destination, keys, key)) {
    D_COUT("\nKey buffer overflow printing string.");
    return TInvalidIndex<SIZ>();
  }
  D_COUT("\nPrinted key \"" << destination << "\" at offset:" << offset
                            << "\nFinding insert location... ");

  SIZ low = 0, mid = 0, high = count;

  SIZ* temp_ptr;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_hash = hashes[mid];
    D_COUT("high:" << high << " mid:" << mid << " low:" << low << " hash:0x"
                   << Hexf(current_hash));

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {  // Duplicate hash detected.
      D_COUT("hash detected, ");

      // Check for other collisions.

      SIZ index = collision_indexes[mid];  //< HSH in the collision table.

      D_COUT("index:" << index);

      if (index != TInvalidIndex<SIZ>()) {  //< There are other collisions.
        D_COUT("with collisions, ");
        // There was a collision so check the table.

        // The collisions_list is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisions_list is searched from
        // lower address up.
        temp = collision_indexes[mid];
        temp_ptr = collision_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < 0) {
          SIZ offset = key_offsets[index];
          D_COUT("comparing to \"" << keys - offset << "\"... ");
          if (TSTREquals<Char>(key, keys - offset)) {
            D_COUT("but table already contains key at offset:" << index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }

        D_COUT("\nNew collision detected.");

        // Copy the key
        space_left = key_offsets[count - 1] + key_length + 1;

        // Update the collision table.
        SIZ size_pile = table->size_pile;
        // Shift the collisions table up one element and insert
        // the unsorted collision index.
        // Then move to the top of the collisions list.
        collision_list += size_pile;
        // and iterate down to the insert spot
        while (collision_list > temp_ptr) {
          *collision_list = *(collision_list - 1);
          --collision_list;
        }
        *temp_ptr = count;

        table->size_pile = size_pile + 1;
        D_COUT("\ncollision index:" << temp);
        // Store the collision index.
        collision_indexes[count] = temp;       //< Store the collision index
        hashes[count] = TInvalidIndex<SIZ>();  //< Set the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        collision_indexes += count_max;

        //< Add the newest Char to the stop.
        collision_indexes[count] = count;

        index = SIZ(keys - destination);
        key_offsets[count] = index;
        D_COUT("\n\n| Inserted at index:" << index << " in path 1");
        table->count = count + 1;
        D_COUT_TABLE(table);
        return count;
      }

      // But we still don't know if the Char is a new collision.

      index = unsorted_indexes[mid];

      D_COUT("\nChecking if " << index << " is a collision... ");
      if (!TSTREquals<Char>(key, keys - key_offsets[index])) {
        D_COUT("new collision detected.");

        if (space_left < 3) {
          D_COUT("buffer overflow!");
          return TInvalidIndex<SIZ>();
        }

        // Get offset to write the key too.
        space_left = key_offsets[count - 1] + key_length + 1;

        key_offsets[count] = space_left;

        SIZ size_pile = table->size_pile;
        collision_indexes[mid] = static_cast<SIZ>(size_pile);
        collision_indexes[count] = static_cast<SIZ>(size_pile);

        // Insert the collision into the collision table.
        temp_ptr = &collision_list[size_pile];
        // Move collisions pointer to the unsorted_indexes.
        collision_indexes += count_max;
        SIZ collision_index = unsorted_indexes[mid];
        *temp_ptr = collision_index;
        ++temp_ptr;
        *temp_ptr = count;
        ++temp_ptr;
        *temp_ptr = TInvalidIndex<SIZ>();
        table->size_pile = size_pile + 3;

        // Add the newest key at the stop.
        collision_indexes[count] = count;

        // Set the last hash to 0xFFFF
        hashes[count] = TInvalidIndex<SIZ>();

        D_COUT("Inserting value: into index:" << index << " count:" << count
                                              << " with other collision_index:"
                                              << collision_index);

        SIZ index = SIZ(keys - destination);
        key_offsets[count] = index;
        D_COUT("\nInserted at key_offsets[count]:" << index << " in path 2");
        table->count = count + 1;
        D_COUT_TABLE(table);
        return count;
      }
      D_COUT("\nTable already contains the key");
      return TInvalidIndex<SIZ>();
    }
  }

  D_COUT("\nThe hash 0x" << Hexf(hash)
                         << " was not in the table so inserting \"" << key
                         << "\" into mid:" << mid << " at index "
                         << TDelta<>(table, destination) << " before hash 0x"
                         << Hexf(hashes[mid]));

  // Move up the hashes and insert at the insertion point.
  HSH* hash_ptr = hashes + count;
  //*test = hashes;
  D_COUT("\ncount: " << count << " hashes:" << TDelta<>(table, hashes)
                     << " hash_ptr:" << TDelta<>(table, hash_ptr)
                     << " insert_ptr:" << TDelta<>(table, hashes + mid));
  hashes += mid;
  D_COUT_TABLE(table);
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = hash;

  // Mark as not having any collisions.
  collision_indexes[count] = TInvalidIndex<SIZ>();

  // Move up the sorted indexes and insert the unsorted index (which is
  // the current count).
  collision_indexes += count_max;
  collision_indexes += mid;
  temp_ptr = collision_indexes + count;

  while (temp_ptr > collision_indexes) {
    *temp_ptr = *(temp_ptr - 1);
    --temp_ptr;
  }
  *temp_ptr = count;  // unsorted_indexes[mid] = count;

  key_offsets[count] = offset;
  table->count = count + 1;
  D_COUT_TABLE(table);
  return count;
}

/* Attempts to find the given key.
@return Returns TTableInvalidIndex<SIZ>() upon failure, and valid index upon
success. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
LIB_MEMBER SIZ TTableFind(const TTable<SIZ>* table, const Char* key) {
  D_ASSERT(table);
  SIZ count = table->count, count_max = table->count_max, temp;

  if (!key || count == 0) return TInvalidIndex<SIZ>();

  SIZ size_bytes = table->size_bytes;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes) - 1;

  HSH hash = THashPrime<HSH, Char>(key);

  D_COUT("\nSearching for key \"" << key << "\" with hash:0x" << Hexf(hash)
                                  << "...");

  if (count == 1) {
    SIZ offset = key_offsets[0];
    D_COUT("\nComparing to only key \"" << keys - offset << "\"...");
    if (TSTREquals<Char>(key, keys - offset)) {
      D_COUT("hit at offset:" << offset);
      return 0;
    }
    if (!TSTREquals<Char>(key, keys - offset)) {
      D_COUT("key not found.");
      return TInvalidIndex<SIZ>();
    }
    D_COUT("Found key:\"" << key << '\"' << Linef('-'));
    return 0;
  }

  // Perform a binary search to find the first instance of the hash the
  // binary search yields. If the mid is odd, we need to subtract the
  // sizeof (HSH*) in order to get the right pointer address.
  SIZ low = 0, mid, high = count - 1;

  while (low <= high) {
    mid = (low + high) >> 1;  //< >> 1 to /2

    HSH current_hash = hashes[mid];
    D_COUT("\nlow:" << low << " mid:" << mid << " high:" << high
                    << " hashes[mid]:" << Hexf(hashes[mid]));
    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {
      D_COUT("\n\nFound duplicate hash:"
             << Hexf(hashes[mid]) << " found at mid:" << mid
             << " for key:" << key << ". Checking for collisions:");

      SIZ* collisions = unsorted_indexes + count_max;
      SIZ index = collisions[mid];

      if (index != TInvalidIndex<SIZ>()) {
        D_COUT("\nThere was a collision. Checking the table...");

        // The collisions_list is a sequence of indexes terminated by
        // an invalid index > kMaxNumOps. collissionsList[0] is an
        // invalid index, so the collisions_list is searched from
        // lower address up.

        temp = collision_indexes[mid];
        SIZ *collision_list = unsorted_indexes + count_max,
            *temp_ptr = collision_list + temp;
        index = *temp_ptr;
        while (index >= 0) {
          SIZ offset = key_offsets[index];
          D_COUT("\nComparing to:\"" << keys - offset
                                     << " at offset:" << offset);
          if (TSTREquals<Char>(key, keys - offset)) {
            D_COUT("hit at index:" << index << " offset:" << offset);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }
        D_COUT("\nDid not find \"" << key << '"');
        return TInvalidIndex<SIZ>();
      }

      D_COUT(
          "\nThere were no collisions. But we still don't know if the Char is "
          "new or a collision.");

      // Move collisions pointer to the unsorted indexes.
      collision_indexes += count_max;
      index = unsorted_indexes[mid];

      SIZ offset = key_offsets[index];
      D_COUT("\nmid:" << mid << " hashes[mid]:" << Hexf(hashes[mid])
                      << " index:" << index << " table_key:\"" << keys - offset
                      << "\" hash_expected:0x"
                      << Hexf(THashPrime<HSH, Char>(keys - offset)));

      if (!TSTREquals<Char>(key, keys - offset)) {
        D_COUT(" but it was a collision and did not find key.");
        return TInvalidIndex<SIZ>();
      }

      D_COUT("\nFound key at mid:" << mid);
      return index;
    }
  }
  D_COUT("\nDidn't find a hash for key \"" << key << Linef("\"\n---"));

  return TInvalidIndex<SIZ>();
}

/* Gets the given key.
@return Returns the index it go inserted into. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableGet(TTable<SIZ>* table, SIZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  SIZ count = table->count;
  if (index < 0 || index >= count) return TInvalidIndex<SIZ>();

  SIZ size_bytes = table->size_bytes, count_max = table->count_max, temp;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes - sizeof(Char));
}

/* Removes the string at the given index. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableRemove(TTable<SIZ>* table, SIZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  SIZ count = table->count;
  if (index < 0 || index >= count) return TInvalidIndex<SIZ>();

  SIZ size_bytes = table->size_bytes, count_max = table->count_max, temp;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = reinterpret_cast<Char*>(key_offsets + count_max),
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes - sizeof(Char));

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
              TBuf<TTableSize<SIZ, Char, kCountMax_>(), SI1, SIZ, TTable<SIZ>>>
class ATable {
  AArray<Char, SIZ, BUF> obj_;  //< Auto-Array of Char(s).
 public:
  /* Constructs a Table.
  @param factory ASCII Factory to call when the Strand overflows. */
  ATable() {
    SIZ size_bytes = TTableSize<SIZ, Char, kCountMax_>();
    D_SOCKET_WIPE(obj_.Begin(), size_bytes);
    TTableInit<SIZ, HSH, Char>(obj_.Begin(), kCountMax_, size_bytes);
  }

  /* Constructs a Table.
  @param factory ASCII Factory to call when the Strand overflows. */
  ATable(SIZ count_max) {
    SIZ size_bytes = TTableSize<SIZ, Char, count_max>();
    D_SOCKET_WIPE(obj_.Begin(), size_bytes);
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
