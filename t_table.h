/* Script^2 @version 0.x
@file    /script2/t_table.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#if SEAM >= SEAM_SCRIPT2_TABLE
#ifndef INCLUDED_SCRIPTT2_TTABLE
#define INCLUDED_SCRIPTT2_TTABLE

#include "c_socket.h"
#include "t_hash.h"
#include "t_utf.h"

#if SEAM == SEAM_SCRIPT2_TABLE
#include "module_debug.inl"
#define D_COUT_TABLE(item) \
  TTablePrint<::_::COut, Char, SIZ, HSH>(COut().Star(), item)
#else
#include "module_release.inl"
#define D_COUT_TABLE(item)
#endif

namespace _ {

/* A one-to-one key-index ASCII Table/map.

# Collision Table

Collision table works by using the maximum key value (i.e. 255 for a SIZ,
2^15-1 for a SI2, etc). The collisions list is a sequence of indexes
terminated by an invalid index that is greater than kMaxNumOps.
collissionsList[0] is an invalid index, so the collisions list is searched
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
    |      | Collision table 0                        |
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
    |      | Key Offset 1                             |
    |_________________________________________________|
    |_____                        Size Size = 2^(N+1) |
    |_____   Buffer Indexes                           |
    |_____                              Size          |
    |_____ ^ Sorted Hash N             Hashes         |
    |_____ | ...                                      |
    |      | Sorted Hash 1                            |
    |_________________________________________________|
  ^ |                                                 |
  | |                 Header (8 bytes)                |
0x0 |_________________________________________________|
@endcode
*/
template <typename SIZ>
struct LIB_MEMBER TTable {
  SIZ size,       //< Size of this object in bytes.
      size_pile,  //< Size of the collision table pile.
      top,        //< Offset to the string write cursor.
      count,      //< Number of keys.
      count_max;  //< Number of buffered indexes.
};

enum {
  kMinTableSize = 64,  //< Min size of a Table
};

template <typename SIZ = SIN, typename HSH = UIN>
constexpr SIZ TTableEntryOverhead() {
  return 2 * (sizeof(SIZ) + sizeof(HSH));
}

/* Creates a streamable hash table with enough socket space for the
count_max.
@param  socket
@param  count_max The max count.
@param  size      The size in bytes.
@post   Users might want to call the TableIsValid<SIZ,HSH>
(Table<SIZ,HSH>) function after construction to verify the integrity of the
object. */
template <typename Char = CHR, typename SIZ = SIN, typename HSH = UIN>
TTable<SIZ>* TTableInit(UIW* socket, HSH count_max, SIZ size) {
  A_ASSERT(socket);
  Table<SIZ, HSH>* table = reinterpret_cast<Table<SIZ, HSH>*>(socket);

  SIZ min_required_size =
      sizeof(TTable<SIZ>) + count_max * (kOverheadPerIndex + 2);
  if (set_size < min_required_size) return nullptr;

  table->count = 0;
  table->count_max = count_max;
  table->size_pile = 0;
  table->size = set_size;
  return table;
}

template <typename Char = CHR, typename SIZ = SIN, typename HSH = UIN>
Char* TTableEnd(TTable<SIZ>* table) {
  SIW address = reinterpret_cast<SIW>(table) + table->size;
  return reinterpret_cast<Char*>(address) - 1;
}

#if USING_STR
/* Prints this object out to the console. */
template <typename Printer, typename Char = CHR, typename SIZ = SIN,
          typename HSH = UIN>
Printer& TTablePrint(Printer& o, TTable<SIZ>* table) {
  A_ASSERT(table);
  SIZ count = table->count,          //
      count_max = table->count_max,  //
      collision_index, temp,         //
      size = table->size,            //
      size_pile = table->size_pile;  //

  o << Linef('_') << "\nTable:" << Hexf(table) << "\nnum_keys:" << count
    << " count_max:" << count_max << " size_pile:" << size_pile
    << " size:" << size << "\n|";
  for (SIZ i = 0; i < 79; ++i) o << '_';
  o << kLF;

  HSH* hashes = reinterpret_cast<HSH*>(reinterpret_cast<Char*>(table) +
                                       sizeof(TTable<SIZ>));
  HSH* key_offsets = reinterpret_cast<HSH*>(hashes + count_max);
  Char *indexes = reinterpret_cast<Char*>(key_offsets + count_max),
       *unsorted_indexes = indexes + count_max,
       *collission_list = unsorted_indexes + count_max,  //
      *begin;
  Char* keys = reinterpret_cast<Char*>(table) + size - 1;

  o << kLF << Rightf("i", 3) << Rightf("key", 10) << Rightf("offset", 8)
    << Rightf("hash_e", 10) << Rightf("hash_u", 10) << Rightf("index_u", 10)
    << Rightf("collisions", 11) << '|';

  for (SIZ i = 0; i < 79; ++i) o << '_';
  o << kLF;

  for (SIZ i = 0; i < count; ++i) {
    // Print each record as a row.
    // @todo Change count_max to count after done debugging.
    collision_index = indexes[i];

    o << Rightf(i, 3) << Rightf(keys - key_offsets[i], 10)
      << Rightf(key_offsets[i], 8)
      << Rightf(THashPrime<Char, HSH>(keys - key_offsets[i]), 10)
      << Rightf(hashes[unsorted_indexes[i]], 10) << Rightf(hashes[i], 10)
      << Rightf(unsorted_indexes[i], 10) << Rightf(collision_index, 11);

    if ((collision_index != -1) && (i < count)) {
      // Print collisions.
      begin = &collission_list[collision_index];
      temp = *begin;
      ++begin;
      o << temp;
      while (temp != -1) {
        temp = *begin;
        ++begin;
        if (temp != -1) o << ", " << temp;
      }
    }
    o << kLF;
  }
  o << '|';
  for (SIZ i = 0; i < 79; ++i) o << '_';
  return o << '\n' << Charsf(table, table->size) << kLF;
}
#endif

/* Adds the given key and returns the index 64-255 of the index of the
op.
@return Returns an index 64-255 */
template <typename Char = CHR, typename SIZ = SIN, typename HSH = UIN>
SIZ TTableAdd(TTable<SIZ>* table, const Char* key) {
  A_ASSERT(table);
  A_ASSERT(key);

  // TPrintLinef(key);

  SIZ count = table->count, count_max = table->count_max, temp,
      size = table->size;

  if (count >= count_max) return -1;
  //< We're out of buffered indexes.

  HSH* hashes = reinterpret_cast<HSH*>(reinterpret_cast<Char*>(table) +
                                       sizeof(TTable<SIZ>));
  HSH* key_offsets = reinterpret_cast<HSH*>(hashes + count_max);
  Char *indexes = reinterpret_cast<Char*>(key_offsets + count_max),
       *unsorted_indexes = indexes + count_max,
       *collission_list = unsorted_indexes + count_max;
  Char *keys = reinterpret_cast<Char*>(table) + size - 1, *destination;

  // Calculate space left.
  HSH value = size - count_max * TTableEntryOverhead<SIZ, HSH>(),  //
      size_pile,                                                   //
      key_length = static_cast<HSH>(TSTRLength<Char>(key));

  D_PRINTF(
      "\nAdding key \"%s\":%u\n%20s:%x\n%20s:%x\n%20s:%x\n%20s:%x"
      "\n%20s:%x\n%20s:%x\n%20s:%x\n%20s:%x\n%20s:%x",
      key, (UIN)key_length, "hashes", hashes, "key_offsets", key_offsets,
      "keys", keys, "indexes", indexes, "value", value, "hashes", hashes,
      "key_offsets", key_offsets, "keys", keys, "indexes", indexes, "value",
      value);

  HSH hash = THashPrime<Char, HSH>(key), current_hash;

  if (key_length > value) {
    D_PRINTF("\nBuffer overflow!");
    return ~(SIZ)0;
  }

  D_COUT_TABLE(table);

  if (count == 0) {
    table->count = 1;
    *hashes = hash;
    *key_offsets = static_cast<HSH>(key_length);
    *indexes = -1;
    *unsorted_indexes = 0;
    destination = keys - key_length;

    TPrint<Char>(destination, TTableEnd<Char, SIZ>(table), key);
    D_PRINTF("\nInserted key \"%s\" at GetAddress 0x%p", key, destination);
    D_COUT_TABLE(table);
    return 0;
  }

  // Calculate left over socket size by looking up last Char.

  if (key_length >= value) {
    D_PRINTF("\nNot enough room in buffer!\n");
    return 0;  //< There isn't enough room left in the socket.
  }

  D_PRINTF("\nFinding insert location... ");

  HSH low = 0, mid, high = count, index;

  Char* temp_ptr;

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

      index = indexes[mid];  //< HSH in the collision table.

      D_PRINTF("index:%i", (SIZ)index);

      if (index != -1) {  //< There are other collisions.
        D_PRINTF("with collisions, ");
        // There was a collision so check the table.

        // The collisions_list is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisions_list is searched from
        // lower address up.
        temp = indexes[mid];
        temp_ptr = collission_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < -1) {
          D_PRINTF("comparing to \"%s\" ", keys - key_offsets[index]);
          if (TSTREquals<Char>(key, keys - key_offsets[index])) {
            D_PRINTF(
                "but table already contains key at "
                "offset:%i",
                (SIZ)index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }

        D_PRINTF("\nNew collision detected.\n");

        // Copy the key
        value = key_offsets[count - 1] + key_length + 1;
        TPrint<Char>(keys - value, TTableEnd<Char, SIZ>(table), key);
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
        D_PRINTF("\ncollision index:%i", (SIZ)temp);
        // Store the collision index.
        indexes[count] = temp;  //< Store the collision index
        table->count = count + 1;
        hashes[count] = ~0;  //< Set the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        indexes += count_max;

        //< Add the newest Char to the stop.
        indexes[count] = count;

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

        if (value < 3) {
          D_PRINTF("\nBuffer overflow!");
          return -1;
        }

        // Get offset to write the key too.
        value = key_offsets[count - 1] + key_length + 1;

        SIZ collision_index = unsorted_indexes[mid];
        TPrint<Char>(keys - value, TTableEnd<Char, SIZ>(table), key);
        D_PRINTF(
            "Inserting value: into index:%i count:%u with "
            "other collision_index:%i",
            value, index, count, collision_index);
        key_offsets[count] = value;

        size_pile = table->size_pile;
        indexes[mid] = static_cast<SIZ>(size_pile);
        indexes[count] = static_cast<SIZ>(size_pile);

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
        //< Added one term-SIZ and two indexes.

        // Add the newest key at the stop.
        indexes[count] = count;

        // Set the last hash to 0xFFFF
        hashes[count] = ~0;

        table->count = count + 1;

        D_COUT_TABLE(table);
        D_PRINTF("\nDone inserting.");
        // Then it was a collision so the table doesn't contain .
        return count;
      }
      D_PRINTF("\nTable already contains the key");
      return index;
    }
  }

  // The hash was not in the table.

  value = key_offsets[count - 1] + key_length + 1;
  destination = keys - value;

  D_PRINTF(
      "\nThe hash 0x%x was not in the table so inserting \"%s\""
      "into mid:%i at index 0x%p before hash 0x%x",
      hash, key, (SIZ)mid, destination - reinterpret_cast<Char*>(table),
      hashes[mid]);

  // First copy the Char and set the key offset.
  TPrint<Char>(destination, TTableEnd<Char, SIZ>(table), key);
  key_offsets[count] = value;

  // Second move up the hashes and insert at the insertion point.
  HSH* hash_ptr = hashes + count;
  //*test = hashes;
  D_PRINTF("l_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u\n", count,
          hashes - reinterpret_cast<HSH*>(table),
          hash_ptr - reinterpret_cast<HSH*>(table),
          hashes + mid - reinterpret_cast<HSH*>(table));
  hashes += mid;
  D_COUT_TABLE(table);
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = hash;

  // Mark as not having any collisions.
  indexes[count] = -1;

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

  D_COUT_TABLE(table);
  D_PRINTF("Done inserting.\n");
  D_COUT_LINEF('-');

  return count;
}

/* Attempts to find the given key.
@return Returns -1 upon failure, and valid index upon success. */
template <typename Char = CHR, typename SIZ = SIN, typename HSH = UIN>
LIB_MEMBER SIZ TTableFind(const TTable<SIZ>* table, const Char* key) {
  A_ASSERT(table);
  HSH index, count = table->count, count_max = table->count_max, temp;

  D_COUT_HEADING("Finding record...");

  if (key == nullptr || count == 0) return -1;

  HSH size = table->size;

  const HSH* hashes = reinterpret_cast<const HSH*>(
      reinterpret_cast<const Char*>(table) + sizeof(TTable<SIZ>));
  const HSH* key_offsets = reinterpret_cast<const HSH*>(hashes + count_max);
  const Char *indexes = reinterpret_cast<const Char*>(key_offsets + count_max),
             *unsorted_indexes = indexes + count_max,
             *collission_list = unsorted_indexes + count_max;
  const Char* keys = reinterpret_cast<const Char*>(table) + size - 1;
  const Char *collisions, *temp_ptr;

  HSH hash = THashPrime<Char, HSH>(key);

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
    D_COUT_LINEF('-');
    return 0;
  }

  // Perform a binary search to find the first instance of the hash the
  // binary search yields. If the mid is odd, we need to subtract the
  // sizeof (HSH*) in order to get the right pointer address.
  SIZ low = 0, mid, high = count - 1;

  while (low <= high) {
    mid = (low + high) >> 1;  //< >> 1 to /2

    HSH current_hash = hashes[mid];
    D_PRINTF("low: %i mid: %i high %i hashes[mid]:%x\n", low, mid, high,
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

      collisions =
          reinterpret_cast<const Char*>(key_offsets) + count_max * sizeof(HSH);
      index = collisions[mid];

      if (index != -1) {
        // There was a collision so check the table.
        // D_PRINTF ("There was a collision so check the table\n");

        // The collisions_list is a sequence of indexes terminated by
        // an invalid index > kMaxNumOps. collissionsList[0] is an
        // invalid index, so the collisions_list is searched from
        // lower address up.

        temp = indexes[mid];

        temp_ptr = collission_list + temp;
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
      indexes += count_max;
      index = unsorted_indexes[mid];

      D_PRINTF("\nmid:%i-%u unsorted_indexes:%HSH key:\"%s\" hash:0x%x",
              (SIZ)mid, (UIN)hashes[mid], index, keys - key_offsets[index],
              THashPrime<Char, HSH>(keys - key_offsets[index]));

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

/* An ASCII Table Autoject. */
template <typename Char = CHR, typename SIZ = SIN, typename HSH = UIN,
          SIZ kCount_ = 512,
          typename BUF = TSocket<kCount_, Char, TStrand<SIZ>>>
class ATable {
 public:
  /* Constructs a Table.
  @param factory ASCII Factory to call when the Strand overflows. */
  ATable() {}

  /* Deep copies the given string into the Table.
  @return The index of the string in the Table. */
  inline SIZ Add(const Char* string) {
    return TTableAdd<Char, SIZ, HSH>(OBJ(), string);
  }

  /* Removes the string at the given index from the Table. */
  inline SIZ Remove(SIZ index) {
    return TTableRemove<Char, SIZ, HSH>(OBJ(), index);
  }

  /* Gets the string at the given index. */
  inline Char* Get(SIZ index) {
    return TTableGet<Char, SIZ, HSH>(OBJ(), index);
  }

  inline SIZ Find(const Char* string) {
    return TTableFind<Char, SIZ, HSH>(OBJ(), string);
  }

  /* Gets the ASCII Object. */
  inline TTable<SIZ>* OBJ() { return obj_.BeginAs<TTable<SIZ>>(); }

  /* Gets the Auto-Array. */
  inline AArray<Char, SIZ, BUF>& Auto() { return obj_; }

  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TTablePrint<Printer, Char, SIZ, HSH>(o, OBJ());
  }

  inline void COut() { PrintTo<::_::COut>(::_::COut().Star()); }

 private:
  AArray<Char, SIZ, BUF> obj_;  //< Auto-Array of Char(s).
};                              // namespace _

}  // namespace _

#endif
#endif
