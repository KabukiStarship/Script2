/* Script^2 @version 0.x
@file    /script2/t_able.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_SEAM_LIST
#ifndef INCLUDED_SCRIPTT2_TTABLE
#define INCLUDED_SCRIPTT2_TTABLE

#include "c_socket.h"

#if SEAM == SCRIPT2_SEAM_LIST
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* A one-to-one key-index ASCII Table/map.

# Collision Table

Collision table works by using the maximum key value (i.e. 255 for a UI1,
2^15-1 for a SI2, etc). The collisions list is a sequence of indexes
terminated by an invalid index that is greater than kMaxNumOps.
collissionsList[0] is an invalid index, so the collisionsList is searched
from lower address up.

# Memory Layout

@code
    ___________________________________________________
    |_____ | Key 1                                    |
    |_____ | ...                          Keys        |
    |_____ v Key N                                    |
    |_________________________________________________|
    |                                                 |
    |               Header Buffer Space               |
    |_________________________________________________|
    |_____                          Size Size = 2^N   |
    |_____                                            |
    |_____   Collision List N          Hash Table     |
    |_____ ^ ...                        Collision     |
    |_____ | Collision List 0              List       |
    |_________________________________________________|
    |_____                          Size Size = 2^N   |
    |_____   Buffer Indexes                           |
    |_____                             Hash Table     |
    |_____ ^ Collision Table N          Unsorted      |
    |_____ | ...                         Indexes      |
    |        | Collision table 0                      |
    |_________________________________________________|
    |_____                          Size Size = 2^N   |
    |_____   Buffer Indexes                           |
    |_____                             Hash Table     |
    |_____ ^ Collision Index N         Collision      |
    |_____ | ...                        Indexes       |
    |      | Collision Index 0                        |
    |_________________________________________________|
    |_____                        Size Size = 2^(N+1) |
    |_____   Buffer Indexes                           |
    |_____                                Size        |
    |_____ ^ Key Offset N                 key         |
    |_____ | ...                        Offsets       |
    |        | Key Offset 1                           |
    |_________________________________________________|
    |_____                        Size Size = 2^(N+1) |
    |_____   Buffer Indexes                           |
    |_____                              Size          |
    |_____ ^ Sorted Hash N             Hashes         |
    |_____ | ...                                      |
    |        | Sorted Hash 1                          |
    |_________________________________________________|
  ^ |                                                 |
  | |                 Header (8 bytes)                |
0x0 |_________________________________________________|
@endcode
*/
template <typename Size, typename Index>
struct SDK Table {
  Size size,         //< Size of this object in bytes.
      size_pile;     //< Size of the collision table pile.
  Index first_char,  //< The first CH1 of the Table.
      count,         //< Number of keys.
      count_max;     //< Number of buffered indexes.
};

enum {
  kMinTableSize = 64,  //< Min size of a Table
  kOverheadPerIndex = sizeof(UI2) + sizeof(UI2) + sizeof(UI1) + sizeof(UI1),
};

// void Print (Table* rt);

/* Creates a streamable hash table with enough socket space for the
count_max.
@param  socket
@param  count_max The max count.
@param  size      The size in bytes.
@post   Users might want to call the TableIsValid<Size,Index>
(Table<Size,Index>) function after construction to verify the integrity of the
object. */
template <typename Size, typename Index>
Table<Size, Index>* TableInit(UIW* socket, Index count_max, Size size) {
  ASSERT(socket)
  Table* table = reinterpret_cast<Table<Size, Index>*>(socket);

  SI4 min_required_size =
      sizeof(Table<Size, Index>) + count_max * (kOverheadPerIndex + 2);
  if (set_size < min_required_size) return nullptr;

  table->count = 0;
  table->count_max = count_max;
  table->size_pile = 0;
  table->size = set_size;
  return table;
}

/* Adds the given key and returns the index 64-255 of the index of the
    op.
    @return Returns an index 64-255 */
template <typename Size, typename Index>
UI1 TableAdd(Table<Size, Index>* table, const CH1* key) {
  ASSERT(table)
  ASSERT(keys)

  // TPrintLinef(key);

  UI1 count = table->count, count_max = table->count_max, temp;

  UI2 size = table->size;

  if (count >= count_max) return kInvalidIndex;
  //< We're out of buffered indexes.

  UI2* hashes = reinterpret_cast<UI2*>(reinterpret_cast<CH1*>(table) +
                                       sizeof(Table<Size, Index>));
  UI2* key_offsets = reinterpret_cast<UI2*>(hashes + count_max);
  CH1 *indexes = reinterpret_cast<CH1*>(key_offsets + count_max),
      *unsorted_indexes = indexes + count_max,
      *collission_list = unsorted_indexes + count_max;
  CH1 *keys = reinterpret_cast<CH1*>(table) + size - 1, *destination;

  // Calculate space left.
  UI2 value = size - count_max * kOverheadPerIndex, size_pile,
      key_length = static_cast<UI2>(SlotLength(key));

  PRINTF(
      "\nAdding key \"%s\":%u\n%20s:%x\n%20s:%x\n%20s:%x\n%20s:%x"
      "\n%20s:%x\n%20s:%x\n%20s:%x\n%20s:%x\n%20s:%x",
      key, (UIN)key_length, "hashes", hashes, "key_offsets", key_offsets,
      "keys", keys, "indexes", indexes, "value", value, "hashes", hashes,
      "key_offsets", key_offsets, "keys", keys, "indexes", indexes, "value",
      value);

  UI2 hash = Hash16(key), current_hash;

  if (key_length > value) {
    PRINTF("\nBuffer overflow!");
    return ~(UI1)0;
  }

  PRINT_TABLE;

  if (count == 0) {
    table->count = 1;
    *hashes = hash;
    *key_offsets = static_cast<UI2>(key_length);
    *indexes = kInvalidIndex;
    *unsorted_indexes = 0;
    destination = keys - key_length;

    SlotWrite(destination, key);
    PRINTF("\nInserted key \"%s\" at GetAddress 0x%p", key, destination);
    PRINT_TABLE;
    return 0;
  }

  // Calculate left over socket size by looking up last CH1.

  if (key_length >= value) {
    PRINTF("\nNot enough room in buffer!\n");
    return 0;  //< There isn't enough room left in the socket.
  }

  PRINTF("\nFinding insert location...");

  Index low = 0, mid, high = count, index;

  CH1* temp_ptr;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_hash = hashes[mid];
    PRINTF("high:%i mid:%i low:%i hash:0x%x", high, mid, low, current_hash);

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else  // Duplicate hash detected.
    {
      PRINTF("hash detected, ");

      // Check for other collisions.

      index = indexes[mid];  //< Index in the collision table.

      PRINTF("index:%i", (SI4)index);

      if (index != kInvalidIndex) {  //< There are other collisions.
        PRINTF("with collisions, ");
        // There was a collision so check the table.

        // The collisionsList is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisionsList is searched from
        // lower address up.
        temp = indexes[mid];
        temp_ptr = collission_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < kInvalidIndex) {
          PRINTF("comparing to \"%s\" ", keys - key_offsets[index]);
          if (SlotEquals(key, keys - key_offsets[index])) {
            PRINTF(
                "but table already contains key at "
                "offset:%i",
                (SI4)index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }

        PRINTF("\nNew collision detected.\n");

        // Copy the key
        value = key_offsets[count - 1] + key_length + 1;
        SlotWrite(keys - value, key);
        key_offsets[count] = value;

        // Update the collision table.
        size_pile = table->size_pile;
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
        PRINTF("\ncollision index:%i", (SI4)temp);
        // Store the collision index.
        indexes[count] = temp;  //< Store the collision index
        table->count = count + 1;
        hashes[count] = ~0;  //< Set the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        indexes += count_max;

        //< Add the newest CH1 to the stop.
        indexes[count] = count;

        PRINT_TABLE;
        PRINTF("Done inserting.\n");
        return count;
      }

      // But we still don't know if the CH1 is a new collision.

      index = unsorted_indexes[mid];

      PRINTF("\nChecking if %i is a collision...", (SI4)index);
      if (!SlotEquals(key, keys - key_offsets[index])) {
        // It's a new collision!
        PRINTF("\nIt's a new collision!");

        if (value < 3) {
          PRINTF("\nBuffer overflow!");
          return kInvalidIndex;
        }

        // Get offset to write the key too.
        value = key_offsets[count - 1] + key_length + 1;

        UI1 collision_index = unsorted_indexes[mid];
        SlotWrite(keys - value, key);
        PRINTF(
            "Inserting value: into index:%i count:%u with "
            "other collision_index:%i",
            value, index, count, collision_index);
        key_offsets[count] = value;

        size_pile = table->size_pile;
        indexes[mid] = static_cast<UI1>(size_pile);
        indexes[count] = static_cast<UI1>(size_pile);

        // Insert the collision into the collision table.
        temp_ptr = &collission_list[size_pile];
        // Move collisions pointer to the unsorted_indexes.
        indexes += count_max;
        *temp_ptr = collision_index;
        ++temp_ptr;
        *temp_ptr = count;
        ++temp_ptr;
        *temp_ptr = ~0;
        table->size_pile = size_pile + 3;
        //< Added one term-UI1 and two indexes.

        // Add the newest key at the stop.
        indexes[count] = count;

        // Set the last hash to 0xFFFF
        hashes[count] = ~0;

        table->count = count + 1;

        PRINT_TABLE;
        PRINTF("\nDone inserting.");
        // Then it was a collision so the table doesn't contain .
        return count;
      }
      PRINTF("\nTable already contains the key");
      return index;
    }
  }

  // The hash was not in the table.

  value = key_offsets[count - 1] + key_length + 1;
  destination = keys - value;

  PRINTF(
      "\nThe hash 0x%x was not in the table so inserting \"%s\""
      "into mid:%i at index 0x%p before hash 0x%x",
      hash, key, (SI4)mid, destination - reinterpret_cast<CH1*>(table),
      hashes[mid]);

  // First copy the CH1 and set the key offset.
  SlotWrite(destination, key);
  key_offsets[count] = value;

  // Second move up the hashes and insert at the insertion point.
  UI2* hash_ptr = hashes + count;
  //*test = hashes;
  PRINTF("l_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u\n", count,
         hashes - reinterpret_cast<UI2*>(table),
         hash_ptr - reinterpret_cast<UI2*>(table),
         hashes + mid - reinterpret_cast<UI2*>(table));
  hashes += mid;
  PRINT_TABLE;
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = hash;

  // Mark as not having any collisions.
  indexes[count] = kInvalidIndex;

  // Move up the sorted indexes and insert the unsorted index (which is
  // the current count).
  indexes += count_max + mid;
  temp_ptr = indexes + count;

  while (temp_ptr > indexes) {
    *temp_ptr = *(temp_ptr - 1);
    --temp_ptr;
  }
  *temp_ptr = count;  // unsorted_indexes[mid] = count;

  table->count = count + 1;

  PRINT_TABLE;
  PRINTF("Done inserting.\n");
  PRINT_LINEF('-');

  return count;
}

/* Attempts to find the given key.
@return Returns 0 upon failure, and valid index upon success. */
template <typename Size, typename Index>
SDK UI1 TableFind(const Table<Size, Index>* table, const CH1* key) {
  ASSERT(table)
  Index index, count = table->count, count_max = table->count_max, temp;

  PRINT_HEADING("Finding record...");

  if (key == nullptr || count == 0) return kInvalidIndex;

  UI2 size = table->size;

  const UI2* hashes = reinterpret_cast<const UI2*>(
      reinterpret_cast<const CH1*>(table) + sizeof(Table<Size, Index>));
  const UI2* key_offsets = reinterpret_cast<const UI2*>(hashes + count_max);
  const CH1 *indexes = reinterpret_cast<const CH1*>(key_offsets + count_max),
            *unsorted_indexes = indexes + count_max,
            *collission_list = unsorted_indexes + count_max;
  const CH1* keys = reinterpret_cast<const CH1*>(table) + size - 1;
  const CH1 *collisions, *temp_ptr;

  UI2 hash = Hash16(key);

  PRINTF("\nSearching for key \"%s\" with hash 0x%x\n", key, hash);

  if (count == 1) {
    PRINTF("Comparing keys - key_offsets[0] - this %u\n%s\n",
           (keys - key_offsets[0]) - reinterpret_cast<const CH1*>(table),
           keys - key_offsets[0]);
    if (!SlotEquals(key, keys - key_offsets[0])) {
      PRINTF("Did not find key %s\n", key)
      return kInvalidIndex;
    }
    PRINTF("Found key %s\n", key);
    PRINT_LINEF('-');
    return 0;
  }

  // Perform a binary search to find the first instance of the hash the
  // binary search yields. If the mid is odd, we need to subtract the
  // sizeof (UI2*) in order to get the right pointer address.
  SI4 low = 0, mid, high = count - 1;

  while (low <= high) {
    mid = (low + high) >> 1;  //< >> 1 to /2

    UI2 current_hash = hashes[mid];
    PRINTF("low: %i mid: %i high %i hashes[mid]:%x\n", low, mid, high,
           hashes[mid]);

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {
      // Duplicate hash found.
      PRINTF(
          "\nFound same hash at mid:%i hash:%x offset for key: "
          "%s\n",
          mid, hashes[mid], key);

      // Check for collisions

      collisions =
          reinterpret_cast<const CH1*>(key_offsets) + count_max * sizeof(UI2);
      index = collisions[mid];

      if (index != kInvalidIndex) {
        // There was a collision so check the table.
        // PRINTF ("There was a collision so check the table\n");

        // The collisionsList is a sequence of indexes terminated by
        // an invalid index > kMaxNumOps. collissionsList[0] is an
        // invalid index, so the collisionsList is searched from
        // lower address up.

        temp = indexes[mid];

        temp_ptr = collission_list + temp;
        index = *temp_ptr;
        while (index != kInvalidIndex) {
          PRINTF("comparing to \"%s\"", keys - key_offsets[index]);
          if (SlotEquals(key, keys - key_offsets[index])) {
            PRINTF(
                "Table already contains key at offset:"
                "%u.\n",
                index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }
        PRINTF("\nDid not find \"%s\"", key);
        return kInvalidIndex;
      }

      // There were no collisions.

      // But we still don't know if the CH1 is new or a collision.

      // Move collisions pointer to the unsorted indexes.
      indexes += count_max;
      index = unsorted_indexes[mid];

      PRINTF("\nmid:%i-%u unsorted_indexes:%Index key:\"%s\" hash:0x%x",
             (SI4)mid, (UIN)hashes[mid], index, keys - key_offsets[index],
             Hash16(keys - key_offsets[index]));

      if (!SlotEquals(key, keys - key_offsets[index])) {
        //< It was a collision so the table doesn't contain .
        PRINTF(" but it was a collision and did not find key.");
        return kInvalidIndex;
      }

      PRINTF("\nFound key at mid:%i", mid);
      return index;
    }
  }
  PRINTF("\nDidn't find a hash for key \"%s\"", key);
  PRINT_LINEF('-');

  return kInvalidIndex;
}

#if USING_STR
/* Prints this object out to the console. */
template <typename Size, typename Index>
UTF1& TablePrint(UTF1& utf, Table<Size, Index>* table) {
  ASSERT(table)
  Index count = table->count, count_max = table->count_max, collision_index,
        temp;
  Size size = table->size, size_pile = table->size_pile;

  utf << Line('_') << "\nTable:" << Hex<>(table) << "\nnum_keys:" << count
      << " count_max:" << count_max << " size_pile:" << size_pile
      << " size:" << size << "\n|";
  for (SI4 i = 0; i < 79; ++i) utf << '_';
  utf << kLF;

  UI2* hashes = reinterpret_cast<UI2*>(reinterpret_cast<CH1*>(table) +
                                       sizeof(Table<Size, Index>));
  UI2* key_offsets = reinterpret_cast<UI2*>(hashes + count_max);
  CH1 *indexes = reinterpret_cast<CH1*>(key_offsets + count_max),
      *unsorted_indexes = indexes + count_max,
      *collission_list = unsorted_indexes + count_max, *begin;
  CH1* keys = reinterpret_cast<CH1*>(table) + size - 1;

  utf << kLF << Right<Index>("i", 3) << Right<>("key", 10)
      << Right<>("offset", 8) << Right<>("hash_e", 10) << Right<>("hash_u", 10)
      << Right<>("index_u", 10) << Right<>("collisions", 11) << '|';
  for (SI4 i = 0; i < 79; ++i) utf << '_';
  utf << kLF;

  for (SI4 i = 0; i < count; ++i) {
    // Print each record as a row.
    // @todo Change count_max to count after done debugging.
    collision_index = indexes[i];
    utf << Right<SI4>(i, 3) << Right<>(keys - key_offsets[i], 10)
        << Right<Size>(key_offsets[i], 8)
        << Right<Hex<Size>>(Hash16(keys - key_offsets[i]), 10)
        << Right<Hex<Size>>(hashes[unsorted_indexes[i]], 10)
        << Right<Hex<Size>>(hashes[i], 10)
        << Right<Size>(unsorted_indexes[i], 10)
        << Right<Size>(collision_index, 11);

    if ((collision_index != kInvalidIndex) && (i < count)) {
      // Print collisions.
      begin = &collission_list[collision_index];
      temp = *begin;
      ++begin;
      utf << temp;
      while (temp != kInvalidIndex) {
        temp = *begin;
        ++begin;
        if (temp != kInvalidIndex) utf << ", " << temp;
      }
    }

    utf << kLF;
  }
  utf << '|';
  for (SI4 i = 0; i < 79; ++i) utf << '_';
  utf << kLF << Memory(table, table->size) << kLF;
}
#endif

/* An ASCII Table Autoject. */
template <typename Char = CH1, typename SIZ = SIN, SIZ kCount_ = 512,
          typename BUF = TSocket<kCount_, Char, TStrand<SIN>>>
class ATable {
 public:
  /* Constructs a Table.
  @param factory ASCII Factory to call when the Strand overflows. */
  ATable() : obj_(RamFactoryInit()) {}

  /* Deep copies the given string into the Table.
  @return The index of the string in the Table. */
  inline SIZ Add(const Char* string) {
    return TTableAdd<SIZ, Char>(ARY(), string);
  }

  /* Removes the string at the given index from the Table. */
  inline SIZ Remove(SIZ index) { return TTableRemove<SIZ, Char>(OBJ(), index); }

  /* Gets the string at the given index. */
  inline Char* Get(SIZ index) { return TTableGet<Char, SIZ>(OBJ(), index); }

  inline SIZ Find(const Char* string) { return TTableFind<Char, SIZ>(OBJ()); }

  /* Gets the ASCII Object. */
  inline TTable<SIZ>* OBJ() { return obj_.BeginAs<TTable<SIZ>>() }

  /* Gets the Auto-Array. */
  inline AArray<Char, SIZ, BUF>& ARY() { return obj_; }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    TTablePrint<SIZ, Char, Printer>(o, OBJ());
  }

  inline void COut() { PrintTo<COut>(COut().Star()); }

 private:
  AArray<Char, SIN, BUF> obj_;  //< Auto-Array of Char(s).

  /* Gets the RamFactory based on if the BUF is Nil or a TSocket. */
  constexpr RamFactory RamFactoryInit() {
    return obj_.UsesStack() ? TStrandFactoryStack<Char>
                            : TStrandFactoryHeap<Char>;
  }
};  // namespace _

}  // namespace _

#endif
#endif
