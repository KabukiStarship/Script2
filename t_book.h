/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_book.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SEAM_SCRIPT2_MAP
#ifndef INCLUDED_SCRIPTTBOOK
#define INCLUDED_SCRIPTTBOOK

#include "t_dic.h"

#if SEAM == SEAM_SCRIPT2_MAP
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* A multimap created from contiguous memory.
@ingroup Book
A multimap is like a Python dictionary or C++ map, the difference being a
TMultimap can contain nested TMultimap (). The key design difference
between both Python dictionaries and C++ maps are Sets do not contains
points, and instead works using offsets.

A multimap may or may not have a hash table. In order to turn on the hash
table, simply set the collissionsSize to non-zero in the TMultimap header.

The memory layout is the same for all of the TMultimap types as depicted
below:

@code
+==========================+ -----------
|_______ Buffer            |   ^     ^
|_______ ...               |   |     |
|_______ Data N            |  Data   |
|_______ ...               |   |     |
|_______ Data 0            |   v     |
|==========================| -----   |
|        Key 1             |   ^     |
|        ...               |   |     |
|        Key N             |   |     |
|vvvvvvvvvvvvvvvvvvvvvvvvvv|   |     |
|        socket            |   |     |
|==========================|   |     |
|_______ count_max         |   |     |
|_______ ...               |   |    Size
|_______ Key Offset N      |   |     |
|_______ ...               |   |     |
|        Key Offset 1      |   |     |
|==========================| Header  |
|_______ count_max         |   |     |
|_______ ...               |   |     |
|_______ Data Offset N     |   |     |
|_______ ...               |   |     |
|        Data Offset 1     |   |     |
|==========================|   |     |
|_______ count_max         |   |     |
|_______ ...               |   |     |
|_______ Type UI1 N        |   |     |
|_______ ...               |   |     |
|        Type UI1 1        |   |     |   ^ Up in addresses
|==========================|   |     |   |
|      TMapKey Header      |   v     v   ^
+==========================+ ----------- ^ 0xN
@endcode

# Memory Overhead

| #Bytes | I | Index | Size | Total | Overhead Per index |
|:------:|:-:|:-----:|:----:|:-----:|:-------------------|
|    2   | 1 |   2   |   2  |   8   |  8 + 3 per index + socket.|
|    4   | 2 |   4   |   4  |   16  | 16 + 5 per index + socket.|
|    8   | 4 |   8   |   8  |   32  | 24 + 9 per index + socket.|

* Sizes shown in bytes.
*/

using TMultimap2 = TMap<UI2, SI2, UI1>;
using TMultimap4 = TMap<UI4, SI4, SI2>;
using TMultimap8 = TMap<UI8, SI4, SI4>;

/* The overhead per index for a multimap. */
template <typename Size, typename Index, typename I>
constexpr SI4 MultimapOverheadPerIndex() {
  return sizeof(2 * sizeof(I) + sizeof(Index) + sizeof(Size) + 3);
};

/* The min size a Multimap with the given Size, Index, I sizes. */
template <typename Size, typename Index, typename I>
constexpr Size MultimapSizeMin(I item_count) {
  return item_count * sizeof(2 * sizeof(I) + sizeof(Index) + sizeof(Size) + 3);
};

enum {
  kMaxNumPagesSet2 = 120,                //< The number_ of pages in a Set2.
  kMaxNumPagesSet4 = 8 * 1024,           //< The number_ of pages in a Set4.
  kMaxNumPagesSet8 = 256 * 1024 * 1024,  //< The number_ of pages in a Set8.
  kOverheadPerSet2Index = MultimapOverheadPerIndex<UI1, UI2, UI2>(),
  kOverheadPerSet4Index = MultimapOverheadPerIndex<UI1, UI2, UI2>(),
  kOverheadPerSet8Index = MultimapOverheadPerIndex<UI1, UI2, UI2>(),
};

/* Initializes a Multimap with the given .
    @post    Users might want to call the IsValid () function after construction
             to verify the integrity of the object.
    @warning The reservedNumOperands must be aligned to a 32-bit value, and it
             will get rounded up to the next higher multiple of 4. */
template <typename Size, typename Index, typename I>
UIW* MultimapInit(UIW* socket, UI1 count_max, UI2 size) {
  A_ASSERT(socket);
  if (table_size <
      sizeof(TMap) +
          count_max * (MultimapOverheadPerIndex<UI1, UI2, UI2, UI2>() + 2))
    return nullptr;

  Multimap<>* multimap = reinterpret_cast<TMap*>(socket);
  multimap->size = table_size;
  multimap->table_size = table_size;
  multimap->item_count;
  = 0;
  multimap->count_max = count_max;
  multimap->size_pile = 1;
  return socket;
}

/* Insets the given key-value pair.
 */
template <typename Size, typename Index, typename I>
I MultimapInsert(TMap<Index, I>* multimap, UI1 type, const CH1* key,
                 void* data, I index) {
  if (multimap == nullptr) return 0;
  return ~0;
}

template <typename I>
I MultimapIndexMax() {
  enum {
    kMaxIndexes =
        sizeof(I) == 1
            ? 255
            : sizeof(I) == 2 ? 8 * 1024 : sizeof(I) == 4 ? 512 * 1024 * 1024 : 0
  };
  return kMaxIndexes;
}

/* Adds a key-value pair to the stop of the multimap. */
template <typename Size, typename Index, typename I>
I MultimapAdd(TMap<Index, I>* multimap, const CH1* key, AsciiType type,
              void* data) {
  if (multimap == nullptr) return 0;
  if (key == nullptr) return 0;

  TPrintLinef(key);

  I item_count = multimap->item_count, count_max = multimap->count_max, temp;

  Index table_size = multimap->table_size;

  if (item_count >= count_max) return ~0;
  //< We're out of buffered indexes.

  CH1* states = reinterpret_cast<CH1*>(multimap) + sizeof(TMap<Index, I>);
  Index* key_offsets = reinterpret_cast<Index*>(states + count_max);
  Size* data_offsets =
      reinterpret_cast<Size*>(states + count_max * (sizeof(Index)));
  Size *hashes = reinterpret_cast<Size*>(
           states + count_max * (sizeof(Index) + sizeof(Size))),
       *hash_ptr;
  I *indexes = reinterpret_cast<I*>(
        states + count_max * (sizeof(Index) + sizeof(Size) + sizeof(I))),
    *unsorted_indexes = indexes + count_max,
    *collission_list = unsorted_indexes + count_max;
  CH1 *keys = reinterpret_cast<CH1*>(multimap) + table_size - 1, *destination;

  // Calculate space left.
  Index value = table_size - count_max * MultimapOverheadPerIndex<Index, I>(),
        key_length = static_cast<UI2>(strlen(key)), size_pile;

  TPrintLinef();
  D_PRINTF(
      "Adding Key %s\n%20s: 0x%p\n%20s: %p\n%20s: 0x%p\n"
      "%20s: %p\n%20s: %u\n",
      key, "hashes", hashes, "key_offsets", key_offsets, "keys", keys,
      "indexes", indexes, "value", value);

  Size hash = HashPrime16(key), current_hash;

  if (key_length > value) {
    D_PRINTF("Buffer overflow\n");
    return ~((I)0);
  }

  // utf ();

  if (item_count == 0) {
    multimap->item_count = 1;
    *hashes = hash;
    *key_offsets = static_cast<UI2>(key_length);
    *indexes = ~0;
    *unsorted_indexes = 0;
    destination = keys - key_length;

    SlotWrite(destination, key);
    D_PRINTF("Inserted key %s at GetAddress 0x%p\n", key, destination);
    SetPrint(multimap);
    return 0;
  }

  // Calculate left over socket size by looking up last CH1.

  if (key_length >= value) {
    D_PRINTF("Not enough room in buffer!\n");
    return 0;  //< There isn't enough room left in the socket.
  }

  D_PRINTF("Finding insert location... \n");

  SI4 low = 0, mid, high = item_count, index;

  I* temp_ptr;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_hash = hashes[mid];
    D_PRINTF("high: %i mid: %i low %i hash: %x\n", high, mid, low, current_hash);

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else  // Duplicate hash detected.
    {
      D_PRINTF("hash detected, ");

      // Check for other collisions.

      index = indexes[mid];  //< Index in the collision table.

      D_PRINTF("index:%u\n", index);

      if (index < ~0)  //< There are other collisions.
      {
        D_PRINTF("with collisions, ");
        // There was a collision so check the table.

        // The collisionsList is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisionsList is searched from
        // lower address up.
        temp = indexes[mid];
        temp_ptr = collission_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < MaxSetIndexes<I>()) {
          D_PRINTF("comparing to \"%s\"\n", keys - key_offsets[index]);
          if (strcmp(key, keys - key_offsets[index]) == 0) {
            D_PRINTF(
                "but table already contains key at "
                "offset: %u.\n",
                index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }

        // Its a new collision!
        D_PRINTF("and new collision detected.\n");

        // Copy the key
        value = key_offsets[item_count - 1] + key_length + 1;
        SlotWrite(keys - value, key);
        key_offsets[item_count] = value;

        // Update the collision table.
        size_pile = multimap->size_pile;
        // Shift the collisions table up one element and insert
        // the unsorted collision index.
        // Then move to the top of the collisions list.
        collission_list += size_pile;
        // and iterate down to the insert spot
        while (collission_list > temp_ptr) {
          *collission_list = *(collission_list - 1);
          --collission_list;
        }
        *temp_ptr = item_count;

        multimap->size_pile = size_pile + 1;
        D_PRINTF("\n\ncollision index: %u\n", temp);
        // Store the collision index.
        indexes[item_count] = temp;  //< Store the collision index
        multimap->item_count = item_count + 1;
        hashes[item_count] = ~0;  //< TMultimap the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        indexes += count_max;

        //< Add the newest CH1 to the stop.
        indexes[item_count] = item_count;

        SetPrint(multimap);
        D_PRINTF("Done inserting.\n");
        return item_count;
      }

      // But we still don't know if the CH1 is a new collision.

      D_PRINTF("Checking if it's a collision... ");

      if (strcmp(key, keys - key_offsets[index]) != 0) {
        // It's a new collision!
        D_PRINTF("It's a new collision!\n");

        if (value < 3) {
          D_PRINTF("Buffer overflow!\n");
          return ~0;
        }

        // Get offset to write the key too.
        value = key_offsets[item_count - 1] + key_length + 1;

        UI1 collision_index = unsorted_indexes[mid];
        D_PRINTF("\n\ncollision_index: %u", collision_index);

        SlotWrite(keys - value, key);
        D_PRINTF(
            "Inserting value: %u into index:%u "
            ";:%u with other collision_index: %u\n",
            value, index, item_count, collision_index);
        key_offsets[item_count] = value;

        size_pile = multimap->size_pile;
        indexes[mid] = static_cast<UI1>(size_pile);
        indexes[item_count] = static_cast<UI1>(size_pile);

        // Insert the collision into the collision table.
        temp_ptr = &collission_list[size_pile];
        // Move collisions pointer to the unsorted_indexes.
        indexes += count_max;
        *temp_ptr = collision_index;
        ++temp_ptr;
        *temp_ptr = item_count;
        ++temp_ptr;
        *temp_ptr = ~0;
        multimap->size_pile = size_pile + 3;
        //< Added one term-UI1 and two indexes.

        // Add the newest key at the stop.
        indexes[item_count] = item_count;

        // TMultimap the last hash to 0xFFFF
        hashes[item_count] = ~0;

        multimap->item_count = item_count + 1;

        SetPrint(multimap);

        SetPrint(multimap);
        D_PRINTF("Done inserting.\n");
        // Then it was a collision so the table doesn't contain .
        return item_count;
      }
      D_PRINTF("table already contains the key\n");
      return index;
    }
  }

  // The hash was not in the table.

  value = key_offsets[item_count - 1] + key_length + 1;
  destination = keys - value;

  D_PRINTF(
      "The hash 0x%x was not in the table so inserting %s into mid:"
      " %i at index %u before hash 0x%x \n",
      hash, key, mid, Diff(multimap, destination), hashes[mid]);

  // First copy the CH1 and set the key offset.
  SlotWrite(destination, key);
  key_offsets[item_count] = value;

  // Second move up the hashes and insert at the insertion point.
  hash_ptr = hashes;
  hash_ptr += item_count;
  //*test = hashes;
  D_PRINTF("l_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u\n", item_count,
         Diff(multimap, hashes), Diff(multimap, hash_ptr),
         Diff(multimap, hashes + mid));
  hashes += mid;
  SetPrint(multimap);
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = hash;

  // Mark as not having any collisions.
  indexes[item_count] = ~0;

  // Move up the sorted indexes and insert the unsorted index (which is
  // the current ;).
  indexes += count_max + mid;
  temp_ptr = indexes + item_count;

  while (temp_ptr > indexes) {
    *temp_ptr = *(temp_ptr - 1);
    --temp_ptr;
  }
  *temp_ptr = item_count;

  multimap->item_count = item_count + 1;

  SetPrint(multimap);
  D_PRINTF("Done inserting.\n");
  TPrintLinef();

  return item_count;
}

/* Adds a key-value pair to the stop of the multimap. */
// UI1 Add2 (Set2* multimap, const CH1* key, UI1 data) {
//    return SetAdd<UI1, UI2, UI2, UI2> (multimap, key, kUI1,
//    &data);
//}

/* Returns  the given query CH1 in the hash table. */
template <typename Size, typename Index, typename I>
I MultimapFind(TMap<Index, I>* multimap, const CH1* key) {
  if (multimap == nullptr) return 0;
  PrintLineBreak("Finding record...", 5);
  I index, item_count = multimap->item_count, count_max = multimap->count_max,
           temp;

  if (key == nullptr || item_count == 0) return ~((I)0);

  Index table_size = multimap->table_size;

  const Size* hashes = reinterpret_cast<const Size*>(
      reinterpret_cast<const CH1*>(multimap) + sizeof(TMap<Index, I>));
  const Index* key_offsets = reinterpret_cast<const UI2*>(hashes + count_max);
  const CH1 *indexes = reinterpret_cast<const CH1*>(key_offsets + count_max),
             *unsorted_indexes = indexes + count_max,
             *collission_list = unsorted_indexes + count_max;
  const CH1* keys = reinterpret_cast<const CH1*>(multimap) + table_size - 1;
  const I *collisions, *temp_ptr;

  Size hash = HashPrime16(key);

  D_PRINTF("\nSearching for key \"%s\" with hash 0x%x\n", key, hash);

  if (item_count == 1) {
    if (strcmp(key, keys - key_offsets[0]) != 0) {
      D_PRINTF("Did not find key %s\n", key);
      return ~((I)0);
    }
    D_PRINTF("Found key %s\n", key);
    TPrintLinef();
    return 0;
  }

  // Perform a binary search to find the first instance of the hash the
  // binary search yields. If the mid is odd, we need to subtract the
  // sizeof (Size*) in order to get the right pointer address.
  SI4 low = 0, mid, high = item_count - 1;

  while (low <= high) {
    mid = (low + high) >> 1;  //< >> 1 to /2

    Size current_hash = hashes[mid];
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
          reinterpret_cast<const CH1*>(key_offsets) + count_max * sizeof(UI2);
      index = collisions[mid];

      if (index < ~0) {
        // There was a collision so check the table.
        D_PRINTF("There was a collision so check the table\n");

        // The collisionsList is a sequence of indexes terminated by
        // an invalid index > kMaxNumOperands. collissionsList[0] is an
        // invalid index, so the collisionsList is searched from
        // lower address up.

        temp = indexes[mid];

        temp_ptr = collission_list + temp;
        index = *temp_ptr;
        while (index < MaxSetIndexes<I>()) {
          D_PRINTF("comparing to \"%s\"\n", keys - key_offsets[index]);
          if (strcmp(key, keys - key_offsets[index]) == 0) {
            D_PRINTF(
                "but table already contains key at offset:"
                "%u.\n",
                index);
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }
        D_PRINTF("Did not find \"%s\"\n", key);
        return ~((I)0);
      }

      // There were no collisions.

      // But we still don't know if the CH1 is new or a collision.

      // Move collisions pointer to the unsorted indexes.
      indexes += count_max;
      index = unsorted_indexes[mid];

      D_PRINTF(
          "\n!!!mid: %i-%x unsorted_indexes: %u key: %s\n"
          "hash: %x\n",
          mid, hashes[mid], index, keys - key_offsets[index],
          HashPrime16(keys - key_offsets[index]));

      if (strcmp(key, keys - key_offsets[index]) != 0) {
        //< It was a collision so the table doesn't contain .
        D_PRINTF(" but it was a collision and did not find key.\n");
        return ~((I)0);
      }

      D_PRINTF("and found key at mid: %i\n", (SI4)mid);
      return index;
    }
  }
  D_PRINTF("Did not find a hash for key \"%s\"\n", key);
  TPrintLinef();

  return ~((I)0);
}

// static UI1 Find2 (Set2* multimap, const CH1* key) {
//    return SetFind<UI1, UI2, UI2, UI2> (multimap, key);
//}

/* Prints this object out to the console. */
template <typename Size, typename Index, typename I>
void MultimapPrint(const TMap<Index, I>* multimap) {
  if (multimap == nullptr) return;
  I item_count = multimap->item_count, count_max = multimap->count_max,
    collision_index, temp;
  Index table_size = multimap->table_size, size_pile = multimap->size_pile;
  TPrintLinef('_');

  if (sizeof(Size) == 2)
    D_PRINTF("\nSet2: %p\n", multimap);
  else if (sizeof(Size) == 4)
    D_PRINTF("\nSet4: %p\n", multimap);
  else if (sizeof(Size) == 8)
    D_PRINTF("\nSet8: %p\n", multimap);
  else
    D_PRINTF("\nInvalid TMultimap type: %p\n", multimap);
  D_PRINTF(
      "\n;: %u count_max: %u  "
      "size_pile: %u  size: %u",
      item_count, count_max, size_pile, table_size);
  D_COUT(kLF);
  D_COUT('|');
  for (SI4 i = 0; i < 79; ++i) D_COUT('_');
  D_COUT(kLF);

  const CH1* states =
      reinterpret_cast<const CH1*>(multimap) + sizeof(TMap<Index, I>);
  const Index* key_offsets = reinterpret_cast<const Index*>(states + count_max);
  const Size* data_offsets =
      reinterpret_cast<const Size*>(states + count_max * (sizeof(Index)));
  const Size* hashes = reinterpret_cast<const Size*>(
      states + count_max * (sizeof(Index) + sizeof(Size)));
  const I *indexes = reinterpret_cast<const I*>(
              states + count_max * (sizeof(Index) + sizeof(Size) + sizeof(I))),
          *unsorted_indexes = indexes + count_max,
          *collission_list = unsorted_indexes + count_max, *begin;
  const CH1* keys = reinterpret_cast<const CH1*>(multimap) + table_size - 1;

  D_PRINTF("\n%3s%10s%8s%10s%10s%10s%10s%11s\n", "i", "key", "offset", "hash_e",
         "hash_u", "hash_s", "index_u", "collisions");
  D_COUT('|');
  for (SI4 i = 0; i < 79; ++i) Print('_');
  D_COUT(kLF);

  for (I i = 0; i < count_max; ++i) {
    // Print each record as a row.
    // @todo Change count_max to ; after done debugging.
    collision_index = indexes[i];
    D_PRINTF("\n%3i %9s %7u %9x %9x %9x %9u %10u: ", i, keys - key_offsets[i],
           key_offsets[i], HashPrime16(keys - key_offsets[i]),
           hashes[unsorted_indexes[i]], hashes[i], unsorted_indexes[i],
           collision_index);

    if (collision_index != ~0 && i < item_count) {
      // Print collisions.
      begin = &collission_list[collision_index];
      temp = *begin;
      ++begin;
      D_PRINTF("%u", temp);
      while (temp != ~0) {
        temp = *begin;
        ++begin;
        if (temp == ~0) break;
        D_PRINTF(", %u", temp);
      }
    }

    D_COUT(kLF);
  }
  TPrintLinef('_');

  PrintChars(reinterpret_cast<const CH1*>(multimap) + sizeof(TMap<Index, I>),
              multimap->size);
  D_COUT(kLF);
}

/* Deletes the multimap contents without wiping the contents. */
template <typename Size, typename Index, typename I>
void MultimapClear(TMap<Index, I>* multimap) {
  if (multimap == nullptr) return;
  multimap->item_count = 0;
  multimap->size_pile = 0;
}

/* Deletes the multimap contents by overwriting it with zeros. */
template <typename Size, typename Index, typename I>
void MultimapWipe(TMap<Index, I>* multimap) {
  if (multimap == nullptr) return;
  Size size = multimap->size;
  memset(multimap, 0, size);
}

/* Returns true if this crabs contains only the given address. */
template <typename Size, typename Index, typename I>
BOL MultimapContains(TMap<Index, I>* multimap, void* data) {
  if (multimap == nullptr) return false;
  if (data < multimap) return false;
  if (data > GetEndAddress()) return false;
  return true;
}

/* Removes that object from the multimap and copies it to the destination. */
template <typename Size, typename Index, typename I>
BOL MultimapRemoveCopy(TMap<Index, I>* multimap, void* destination,
                       SIW buffer_size, void* data) {
  if (multimap == nullptr) return false;

  return false;
}

/* Removes the item at the given address from the multimap. */
template <typename Size, typename Index, typename I>
BOL MultimapRemove(TMap<Index, I>* multimap, void* adress) {
  if (multimap == nullptr) return false;

  return false;
}

/* Removes all but the given multimap from the multimap. */
template <typename Size, typename Index, typename I>
BOL MultimapRetain(TMap<Index, I>* multimap) {
  if (multimap == nullptr) return false;

  return false;
}

/* Creates a multimap from dynamic memory. */
template <typename Size, typename Index, typename I>
TMap<Index, I>* MultimapCreate(I buffered_indexes, Size table_size, Size size) {
  TMap<Index, I>* multimap = TNew<TMap, SI4>();
  return multimap;
}

/* Prints the given TMultimap to the console. */
template <typename Size, typename Index, typename I>
UTF1& MultimapPrint(UTF1& utf, TMap<Index, I>* multimap) {}

/* C++ Wrapper class for an ASCII Multimap that uses dynamic memory and can
    auto-grow. */
template <typename Size, typename Index, typename I>
class Multimap {
 public:
  Multimap(Size size) { MultimapInit<Size, Index, I> }

  /* Deletes the multimap and it's dynamic memory. */
  ~Multimap() { delete begin; }

  constexpr SI4 MultimapOverheadPerIndex() {
    return MultimapOverheadPerIndex<Index, I>();
  };

  constexpr I SizeMin(I item_count) {
    return MultimapSizeMin<Index, I>(item_count);
  };

  /* Insets the given key-value pair.
   */
  inline I Insert(UI1 type, const CH1* key, void* data, I index) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapInsert<Index, I>(multimap, type, key, data, index);
  }

  inline I IndexMax() { return MultimapIndexMax<Index, I>(); }

  inline I Add(const CH1* key, AsciiType type, void* data) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapAdd<Index, I>(multimap, key, type, data);
  }

  /* Returns  the given query CH1 in the hash table. */
  inline I Find(const CH1* key) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapFind(multimap, key);
  }

  /* Deletes the multimap contents without wiping the contents. */
  inline void Clear() {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapClear<Index, I>(multimap);
  }

  /* Deletes the multimap contents by overwriting it with zeros. */
  inline void Wipe() {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return Wipe<Index, I>(multimap);
  }

  /* Returns true if this crabs contains only the given address. */
  inline BOL Contains(void* data) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapContains<Index, I>(multimap, void* data);
  }

  /* Removes that object from the multimap and copies it to the destination. */
  inline BOL MultimapRemoveCopy(void* destination, SIW buffer_size,
                                void* data) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return;
  }

  /* Removes the item at the given address from the multimap. */
  inline BOL MultimapRemove(void* adress) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapRemove<Index, I>(multimap);
  }

  /* Removes all but the given multimap from the multimap. */
  inline BOL Retain() {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapRetain<Index, I>(multimap);
  }

  /* Prints the given TMultimap to the console. */
  inline UTF1& Print(UTF1& printer) {
    auto multimap = reinterpret_cast<Multimap<Index, I>>(begin);
    return MultimapPrint<Index, I>(multimap);
  }

 private:
  UIW* begin;  //< Dynamic memory socket.

  TMap
};

using Multimap2 = TMap<UI1, UI2, UI2>;
using Multimap4 = TMap<UI2, UI2, UI4>;
using Multimap8 = TMap<UI4, UI4, UI8>;

}  // namespace _

#endif  //< INCLUDED_SCRIPTTBOOK
#endif  //< #if SEAM >= SEAM_SCRIPT2_MAP
