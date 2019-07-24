/* SCRIPT Script @version 0.x
@file    /script2/t_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_TABLE

#ifndef SCRIPTT2_TABLE_T
#define SCRIPTT2_TABLE_T

#include "c_socket.h"
#include "t_array.h"
#include "t_hash.h"
#include "t_socket.h"
#include "t_utf.h"

#if SEAM == SEAM_SCRIPT2_TABLE
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
2^15-1 for a SI2, etc). The collisions list is a sequence of indexes
terminated by an invalid index that is greater than kMaxNumOps.
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
      top,         //< Offset to the string write cursor.
      count,       //< Number of keys.
      count_max;   //< Number of buffered indexes.
};

enum {
  kMinTableSize = 64,  //< Min size of a Table
};

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

/* The last Char in the Table keys.
The keys get printed down from the end so this is the first nil-term Char of the
first string, which is very convenient. */
template <typename SIZ = SIN, typename Char = CHR>
inline Char* TTableKeysTop(TTable<SIZ>* table, SIZ* offsets, SIZ count) {
  return TPtr<Char>(table, offsets[count - 1]) - 1;
}

/* Creates a streamable hash table with enough socket space for the
count_max.
@param  socket
@param  count_max  The max count.
@param  size_bytes The size in bytes.
@post   Users might want to call the TableIsValid<SIZ,HSH>
(Table<SIZ,HSH>) function after construction to verify the integrity of the
object. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
TTable<SIZ>* TTableInit(TTable<SIZ>* table, SIZ count_max, SIZ size_bytes) {
  D_ASSERT(table);

  SIZ array_sizes =
          count_max * TTableEntryOverhead<SIZ>() + sizeof(TTable<SIZ>),
      min_required_size = 2 * count_max;
  min_required_size += array_sizes;
  D_PRINTF(
      "\nAttempting to create aTTable<> with size_bytes:%i count:%i"
      " min_required_size:%i",
      SIN(size_bytes), SIN(count_max), SIN(min_required_size));

  if (size_bytes < min_required_size) {
    D_PRINTF("\nTable init failed because size_bytes < min_required_size");
    return nullptr;
  }

  D_SOCKET_WIPE(table, size_bytes);

  table->count = 0;
  table->count_max = count_max;
  table->top = size_bytes - sizeof(Char);
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
    kHashWidth = (sizeof(HSH) * 2) < 8 ? 8 : (sizeof(HSH) * 2),
  };
  SIZ count = table->count,            //
      count_max = table->count_max,    //
      collision_index, temp,           //
      size_bytes = table->size_bytes,  //
      size_pile = table->size_pile;    //

  SIN count_length_max = STRLength(count_max);
  o << Linef("\n+---") << "\nTable<SI" << CH1('0' + sizeof(SIZ)) << ",UI"
    << CH1('0' + sizeof(HSH)) << ",CH" << CH1('0' + sizeof(Char)) << ">:0x"
    << Hexf(table) << " size_bytes:" << size_bytes << " key_count:" << count
    << " count_max:" << count_max << " size_pile:" << size_pile
    << Linef("\n+---") << '\n'
    << Rightf("i", count_length_max) << Centerf("offset", 8)
    << Centerf("hash_e", kHashWidth) << Centerf("hash_u", kHashWidth)
    << Centerf("hash_s", kHashWidth) << Centerf("index_u", kHashWidth)
    << Linef(" \"Key\":{Collissions}\n+---");

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = reinterpret_cast<SIZ*>(key_offsets + count_max),
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes - sizeof(Char));

  for (SIZ i = 0; i < count; ++i) {
    o << '\n'
      << Rightf(i, count_length_max)  //
      << Centerf(key_offsets[i], 8)
      << Centerf().Hex(THashPrime<HSH, Char>(keys - key_offsets[i]), kHashWidth)
      << Centerf().Hex(hashes[i], kHashWidth)
      << Centerf().Hex(hashes[unsorted_indexes[i]], kHashWidth)
      << Centerf(unsorted_indexes[i], kHashWidth) << " \""
      << (keys - key_offsets[i]) << "\":{";

    collision_index = collision_indexes[i];
    if ((collision_index >= 0) && (i < count)) {
      // Print collisions.
      SIZ *collission_list = unsorted_indexes + count_max,
          *begin = &collission_list[collision_index];

      temp = *begin;
      ++begin;
      o << temp;
      while (temp >= 0) {
        temp = *begin;
        ++begin;
        if (temp != -1) o << ", " << temp;
      }
    }
    o << '}';
  }
#if DEBUG_THIS
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
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  SIZ count = table->count, count_max = table->count_max,
      size_bytes = table->size_bytes, temp;

  if (count >= count_max) return -1;  //< We're out of buffered indexes.

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes - sizeof(Char));

  // Calculate space left.
  SIZ* collission_list = unsorted_indexes + count_max;
  Char *top = TPtr<Char>(table, keys[count - 1]),
       *bottom = reinterpret_cast<Char*>(collission_list + table->size_pile);
  SIZ key_length = TSTRLength<Char, SIZ>(key);
  SIZ sapce_left = SIZ(top - bottom);  //

  D_PRINTF(
      "\nAdding key \"%s\":%u"
      "\n           hashes:%i"
      "\n      key_offsets:%i"
      "\ncollision_indexes:%i"
      "\n             keys:%i"
      "\n       size_bytes:%i"
      "\n       sapce_left:%i",
      key, (UIN)key_length, TDelta<SIN>(table, hashes),
      TDelta<SIN>(table, key_offsets), TDelta<SIN>(table, collision_indexes),
      TDelta<SIN>(table, keys), SIN(size_bytes), SIN(sapce_left));

  if (key_length > sapce_left) {
    D_PRINTF("\nBuffer overflow!");
    return ~(SIZ)0;
  }

  HSH hash = THashPrime<HSH, Char>(key), current_hash;
  D_PRINTF("\n             hash:0x%x\n", hash);
  Char* destination;
  if (count == 0) {
    table->count = 1;
    *hashes = hash;
    *key_offsets = key_length;
    *collision_indexes = -1;
    *unsorted_indexes = 0;
    destination = keys - key_length;
    TPrintString<Char>(destination, keys, key);
    D_PRINTF("\nInserted key \"%s\" at element:%i with result:\"%s\"", key,
             TDelta<SIN>(table, destination), destination);
    D_COUT_TABLE(table);
    return 0;
  }

  // Calculate left over socket size by looking up last Char.

  if (key_length >= sapce_left) {
    D_PRINTF("\nNot enough room in buffer!\n");
    return 0;  //< There isn't enough room left in the socket.
  }

  D_PRINTF("\nFinding insert location... ");

  SIZ low = 0, mid, high = count, index;

  SIZ* temp_ptr;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_hash = hashes[mid];
    D_PRINTF("high:%i mid:%i low:%i hash:0x%x ", high, mid, low, current_hash);

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {  // Duplicate hash detected.
      D_PRINTF("hash detected, ");

      // Check for other collisions.

      index = collision_indexes[mid];  //< HSH in the collision table.

      D_PRINTF("index:%i", (SIZ)index);

      if (index != -1) {  //< There are other collisions.
        D_PRINTF("with collisions, ");
        // There was a collision so check the table.

        // The collisions_list is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisions_list is searched from
        // lower address up.
        temp = collision_indexes[mid];
        temp_ptr = collission_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < -1) {
          D_PRINTF("comparing to \"%s\" ", keys - key_offsets[index]);
          if (TSTREquals<Char>(key, keys - key_offsets[index])) {
            D_PRINTF("but table already contains key at offset:%i", (SIZ)index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }

        D_PRINTF("\nNew collision detected.\n");

        // Copy the key
        sapce_left = key_offsets[count - 1] + key_length + 1;
        TPrintString<Char>(keys - sapce_left, keys, key);
        key_offsets[count] = sapce_left;

        // Update the collision table.
        SIZ size_pile = table->size_pile;
        // Shift the collisions table up one element and insert
        // the unsorted collision index.
        // Then move to the top of the collisions list.
        collission_list += size_pile;
        // and iterate down to the insert spot
        while (collission_list > temp_ptr) {
          *collission_list = *(collission_list - 1);
          --collission_list;
        }
        *temp_ptr = count;

        table->size_pile = size_pile + 1;
        D_PRINTF("\ncollision index:%i", (SIZ)temp);
        // Store the collision index.
        collision_indexes[count] = temp;  //< Store the collision index
        table->count = count + 1;
        hashes[count] = ~0;  //< Set the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        collision_indexes += count_max;

        //< Add the newest Char to the stop.
        collision_indexes[count] = count;

        D_COUT_TABLE(table);
        D_PRINTF("Done inserting.\n");
        return count;
      }

      // But we still don't know if the Char is a new collision.

      index = unsorted_indexes[mid];

      D_PRINTF("\nChecking if %i is a collision...", (SIZ)index);
      if (!TSTREquals<Char>(key, keys - key_offsets[index])) {
        // It's a new collision!
        D_PRINTF("\nIt's a new collision!");

        if (sapce_left < 3) {
          D_PRINTF("\nBuffer overflow!");
          return -1;
        }

        // Get offset to write the key too.
        sapce_left = key_offsets[count - 1] + key_length + 1;

        SIZ collision_index = unsorted_indexes[mid];
        TPrintString<Char>(keys - sapce_left, keys, key);
        D_PRINTF(
            "Inserting value: into index:%i count:%u with "
            "other collision_index:%i",
            sapce_left, index, count, collision_index);
        key_offsets[count] = sapce_left;

        SIZ size_pile = table->size_pile;
        collision_indexes[mid] = static_cast<SIZ>(size_pile);
        collision_indexes[count] = static_cast<SIZ>(size_pile);

        // Insert the collision into the collision table.
        temp_ptr = &collission_list[size_pile];
        // Move collisions pointer to the unsorted_indexes.
        collision_indexes += count_max;
        *temp_ptr = collision_index;
        ++temp_ptr;
        *temp_ptr = count;
        ++temp_ptr;
        *temp_ptr = ~0;
        table->size_pile = size_pile + 3;
        //< Added one term-SIZ and two indexes.

        // Add the newest key at the stop.
        collision_indexes[count] = count;

        // Set the last hash to 0xFFFF
        hashes[count] = ~0;

        table->count = count + 1;

        D_COUT_TABLE(table);
        D_PRINTF("\nDone inserting.");
        // Then it was a collision so the table doesn't contain .
        return count;
      }
      D_PRINTF("\nTable already contains the key");
      return -1;
    }
  }

  // The hash was not in the table.

  sapce_left = key_offsets[count - 1] + key_length + 1;
  destination = keys - sapce_left;

  D_PRINTF(
      "\nThe hash 0x%x was not in the table so inserting \"%s\""
      "into mid:%i at index 0x%p before hash 0x%x",
      hash, key, (SIZ)mid, destination - reinterpret_cast<Char*>(table),
      hashes[mid]);

  // First copy the Char and set the key offset.
  TPrintString<Char>(destination, keys, key);
  key_offsets[count] = sapce_left;

  // Second move up the hashes and insert at the insertion point.
  HSH* hash_ptr = hashes + count;
  //*test = hashes;
  D_PRINTF("l_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u\n", count,
           UIN(hashes - reinterpret_cast<HSH*>(table)),
           UIN(hash_ptr - reinterpret_cast<HSH*>(table)),
           UIN(hashes + mid - reinterpret_cast<HSH*>(table)));
  hashes += mid;
  D_COUT_TABLE(table);
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = hash;

  // Mark as not having any collisions.
  collision_indexes[count] = -1;

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

  table->count = count + 1;

  D_COUT_TABLE(table);
  D_COUT_LINEF("Done inserting.\n---");

  return count;
}

/* Attempts to find the given key.
@return Returns -1 upon failure, and valid index upon success. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
LIB_MEMBER SIZ TTableFind(const TTable<SIZ>* table, const Char* key) {
  D_ASSERT(table);
  SIZ index, count = table->count, count_max = table->count_max, temp;

  if (!key || count == 0) return -1;

  SIZ size_bytes = table->size_bytes;

  HSH* hashes = reinterpret_cast<HSH*>(TPtr<CH1>(table, sizeof(TTable<SIZ>)));
  SIZ *key_offsets = reinterpret_cast<SIZ*>(hashes + count_max),
      *collision_indexes = key_offsets + count_max,
      *unsorted_indexes = collision_indexes + count_max;
  Char* keys = TPtr<Char>(table, size_bytes - sizeof(Char));

  HSH hash = THashPrime<HSH, Char>(key);

  D_PRINTF("\nSearching for key \"%s\" with hash 0x%x\n", key, hash);

  if (count == 1) {
    D_PRINTF("Comparing keys - key_offsets[0] - this %u\n%s\n",
             (keys - key_offsets[0]) - reinterpret_cast<const Char*>(table),
             keys - key_offsets[0]);
    if (!TSTREquals<Char>(key, keys - key_offsets[0])) {
      D_PRINTF("Did not find key %s\n", key);
      return -1;
    }
    D_PRINTF("Found key %s\n", key);
    D_COUT(Linef('-'));
    return 0;
  }

  // Perform a binary search to find the first instance of the hash the
  // binary search yields. If the mid is odd, we need to subtract the
  // sizeof (HSH*) in order to get the right pointer address.
  SIZ low = 0, mid, high = count - 1;

  while (low <= high) {
    mid = (low + high) >> 1;  //< >> 1 to /2

    HSH current_hash = hashes[mid];
    D_PRINTF("low:%i mid:%i high:%i hashes[mid]:%x\n", low, mid, high,
             hashes[mid]);
    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {
      // Duplicate hash found.
      D_PRINTF(
          "\nFound same hash at mid:%i hash:%x offset for key: "
          "%s\n",
          mid, hashes[mid], key);

      // Check for collisions

      SIZ* collisions = unsorted_indexes + count_max;
      index = collisions[mid];

      if (index != -1) {
        // There was a collision so check the table.
        // D_PRINTF ("There was a collision so check the table\n");

        // The collisions_list is a sequence of indexes terminated by
        // an invalid index > kMaxNumOps. collissionsList[0] is an
        // invalid index, so the collisions_list is searched from
        // lower address up.

        temp = collision_indexes[mid];
        SIZ *collission_list = unsorted_indexes + count_max,
            *temp_ptr = collission_list + temp;
        index = *temp_ptr;
        while (index != -1) {
          D_PRINTF("comparing to \"%s\"", keys - key_offsets[index]);
          if (TSTREquals<Char>(key, keys - key_offsets[index])) {
            D_PRINTF(
                "Table already contains key at offset:"
                "%u.\n",
                index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }
        D_PRINTF("\nDid not find \"%s\"", key);
        return -1;
      }

      // There were no collisions.

      // But we still don't know if the Char is new or a collision.

      // Move collisions pointer to the unsorted indexes.
      collision_indexes += count_max;
      index = unsorted_indexes[mid];

      D_PRINTF("\nmid:%i hashes[mid]:%x index:%i table_key:\"%s\" hash:0x%x",
               (SIZ)mid, (UIN)hashes[mid], index, keys - key_offsets[index],
               THashPrime<HSH, Char>(keys - key_offsets[index]));

      if (!TSTREquals<Char>(key, keys - key_offsets[index])) {
        //< It was a collision so the table doesn't contain .
        D_PRINTF(" but it was a collision and did not find key.");
        return -1;
      }

      D_PRINTF("\nFound key at mid:%i", mid);
      return index;
    }
  }
  D_PRINTF("\nDidn't find a hash for key \"%s\"", key);
  D_COUT_LINEF('-');

  return -1;
}

/* Gets the given key.
@return Returns the index it go inserted into. */
template <typename SIZ = SIN, typename HSH = UIN, typename Char = CHR>
SIZ TTableGet(TTable<SIZ>* table, SIZ index) {
  D_ASSERT(table);
  D_COUT("\nBefore:");
  D_COUT_TABLE(table);

  SIZ count = table->count;
  if (index < 0 || index >= count) return -1;

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
  if (index < 0 || index >= count) return -1;

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
          typename BUF = TSocket<TTableSize<SIZ, Char, kCountMax_>(), SI1, SIZ,
                                 TTable<SIZ>>>
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
    return TTableAdd<SIZ, HSH, Char>(OBJ(), string);
  }

  /* Removes the string at the given index from the Table. */
  inline SIZ Remove(SIZ index) {
    return TTableRemove<SIZ, HSH, Char>(OBJ(), index);
  }

  /* Removes the string at the given index from the Table. */
  inline SIZ Remove(const Char* key) {
    return TTableRemove<SIZ, HSH, Char>(OBJ(), key);
  }

  /* Gets the string at the given index. */
  inline Char* Get(SIZ index) {
    return TTableGet<SIZ, HSH, Char>(OBJ(), index);
  }

  inline SIZ Find(const Char* string) {
    return TTableFind<SIZ, HSH, Char>(OBJ(), string);
  }

  /* Gets the ASCII Object. */
  inline TTable<SIZ>* OBJ() { return obj_.BeginAs<TTable<SIZ>>(); }

  /* Gets the Auto-Array. */
  inline AArray<Char, SIZ, BUF>& Auto() { return obj_; }

#if USING_STR
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TTablePrint<Printer, SIZ, HSH, Char>(o, OBJ());
  }

  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }
#endif
};

}  // namespace _
#undef D_COUT_TABLE
#endif
#endif
