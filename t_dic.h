/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_dic.h
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_13

#ifndef SCRIPT2_TDIC
#define SCRIPT2_TDIC 1

#include "c_asciidata.h"
#include "c_socket.h"

#if SEAM >= SCRIPT2_13
#include "global_debug.inl"
#else
#include "global_release.inl"
#endif

namespace _ {

/* A one-to-one map of Key-{Type-Value} tuples.
  In mathematics, a tuple is a finite ordered list (sequence) of elements. A
  Dictionary is a hash-table that uses contiguous memory. The memory layout is
  the same for all of the Dictionary types as depicted below:

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
  |^^^^^^^^^^^^^^^^^^^^^^^^^^|   |     |
  |_______ Collision N       |   |     |
  |_______ ...               |   |     |
  |        Collision 1       |   |     |
  |==========================|   |     |
  |_______ count_max         |   |     |
  |_______ ...               |   |     |
  |_______ Collision Index N |   |     |
  |_______ ...               |   |     |
  |        Collision Index 1 |   |     |
  |==========================|   |    Size
  |_______ count_max         |   |     |
  |_______ ...               |   |     |
  |_______ Collision Table N |   |     |
  |_______ ...               |   |     |
  |        Collision Table 1 |   |     |
  |==========================| Header  |
  |_______ count_max         |   |     |
  |_______ ...               |   |     |
  |_______ Key Offset N      |   |     |
  |_______ ...               |   |     |
  |        Key Offset 1      |   |     |
  |==========================|   |     |
  |_______ count_max         |   |     |
  |_______ ...               |   |     |
  |_______ Sorted Mappings N |   |     |
  |_______ ...               |   |     |
  |        Sorted Mappings 1 |   |     |
  |==========================|   |     |
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

  | Dictionary | Max Values | % Collisions (p) |           Overhead |
  |:----:|:----------:|:----------------:|:------------------------------:|
  |  2   |     255    |    0.0001        | Ceiling (0.02*p*2^8)  = 2      |
  |  4   |     2^13   |      0.1         | Ceiling (0.04*p*2^13) = 327.68 |
  |  8   |     2^29   |    10^-16        | Ceiling (0.04*p*2^29) = 327.68 |

  Memory Schema:
  The memory schema is optimized for fast search and push back. When searching
  for a key, there might or might not be a hash table.

  How to calculate size:
  The size of any size dictionary can be calculated as follows:
  size = ; * (2*sizeof (Index) + sizeof (Size)) + collissionSize +

  # Cache Page Optimizations
  In order to optimize the cache pages, we need to group hot data together.
  ChineseRoom Objects work through calling by Index, or by key by using the
  function '\"' (i.e. "foo" is Index 44).

  # Hash Table Collisions.
  Because there are no pointers in Script collections, the hash tables are
  done using a nil-terminated list in the Collision List. In the

  # Use Case Scenario
  We are creating a plug-in SDK. We need to create a dictionary in the SDK
  code, and pass it over to the program. The SDK manages the memory for the
  dictionary. This dictionary might contain several million entries, and more
  than 4GB of data.

  ### Why So Many Dictionary Types?
  We are running in RAM, and a dictionary could contain millions of key-value
  pairs. Adding extra bytes would added megabytes of data we don't need. Also,
  on microcontrollers, especially 16-bit ones, will have very little RAM, so we
  need an 16-bit object. It is easy to imagine a complex AI software using
  more than 4GB RAM, or the need to attach a DVD ISO image as a key-value
  pair, so we need a 64-bit dictionary.

  # Design Strengths
  * Uses less memory.
  * Fast push back when within socket size.
  * Faster inserts on small collections when within socket size.

  # Design Weaknesses
  * Slow insert in large collections.
  * Slow at growing large collections when socket runs out.
  * More complicated.

  @code
  ;
  @endcode
*/
template <typename Size, typename Offset, typename Index>
struct SDK Dictionary {
  Size size;          //< Total size of the set.
  Offset table_size,  //< Size of the (optional) key strings in bytes.
      size_pile;      //< Size of the (optional) collisions pile in bytes.
  Index item_count,   //< Number of items.
      count;          //< Max number_ of items that can fit in the header.
};

using Dic2 = Dictionary<SI1, UI2, UI2>;
using Dic4 = Dictionary<SI2, UI2, UI4>;
using Dic8 = Dictionary<SI4, UI4, UI8>;

template <typename Size, typename Offset, typename Index>
constexpr Size DicOverheadPerIndex() {
  return sizeof(2 * sizeof(Index) + sizeof(Offset) + sizeof(Size) + 3);
};

template <typename Size, typename Offset, typename Index>
constexpr Size MinSizeDic(Index item_count) {
  return item_count *
         sizeof(2 * sizeof(Index) + sizeof(Offset) + sizeof(Size) + 3);
};

enum {
  kMaxNumMappingsDic2 = 255,                //< The number_ of pages in a Dic2.
  kMaxNumMappingsDic4 = 8 * 1024,           //< The number_ of pages in a Dic4.
  kMaxNumMappingsDic8 = 256 * 1024 * 1024,  //< The number_ of pages in a Dic8.
  kOverheadPerDic2Index = DicOverheadPerIndex<UI1, UI2, UI2>(),
  kOverheadPerDic4Index = DicOverheadPerIndex<UI2, UI2, UI4>(),
  kOverheadPerDic8Index = DicOverheadPerIndex<UI4, UI4, UI8>(),
};

/* Initializes a Dictionary.
    @post    Users might want to call the IsValid () function after construction
             to verify the integrity of the object.
    @warning The reservedNumOperands must be aligned to a 32-bit value, and it
             will get rounded up to the next higher multiple of 4. */
template <typename Size, typename Offset, typename Index>
Dictionary<Size, Offset, Index>* DictionaryInit(UIW* socket, UI1 max_size,
                                                UI2 table_size, UI2 size) {
  ASSERT(socket);
  if (table_size >= (size - sizeof(Dictionary<Size, Offset, Index>)))
    return nullptr;
  if (table_size < sizeof(Dictionary<Size, Offset, Index>) +
                       max_size * (DicOverheadPerIndex<UI1, UI2, UI2>() + 2))
    return nullptr;

  Dictionary<Size, Offset, Index>* dictionary =
      reinterpret_cast<Dictionary<Size, Offset, Index>*>(socket);
  dictionary->size = table_size;
  dictionary->table_size = table_size;
  dictionary->item_count = 0;
  dictionary->count = max_size;
  dictionary->size_pile = 1;
  return dictionary;
}

Dictionary<UI2, UI2, SI1>* DictionaryInit(UIW* socket, UI1 max_size,
                                          UI2 table_size, UI2 size) {
  return DictionaryInit<UI2, UI2, SI1>(socket, max_size, table_size, size);
}

/* Insets the given key-value pair.
 */
template <typename Size, typename Offset, typename Index, typename T,
          AsciiType kType>
Index DictionaryInsert(Dictionary<Size, Offset, Index>* dictionary,
                       const CH1* key, T value, Index index) {
  if (dictionary == nullptr) return 0;
  return ~0;
}

template <typename Index>
Index DictionaryCountUpperBounds() {
  // return sizeof (Index) == 1 ? 255 : sizeof (Index) == 2 ? 8 * 1024 :
  //                                    sizeof (Index) == 4 ? 512 * 1024 * 1024
  //                            : 0;
  return ~(Index)0;
}

/* Adds a key-value pair to the stop of the dictionary. */
template <typename Size, typename Offset, typename Index, typename T,
          AsciiType type>
Index DictionaryAdd(Dictionary<Size, Offset, Index>* dictionary, const CH1* key,
                    T data) {
  if (dictionary == nullptr) return 0;
  if (key == nullptr) return 0;

  TPrintLinef(key);

  Index item_count = dictionary->item_count, count = dictionary->count, temp;

  Offset table_size = dictionary->table_size;

  if (item_count >= count) return ~0;
  //< We're out of buffered indexes.

  CH1* states = reinterpret_cast<CH1*>(dictionary) +
                sizeof(Dictionary<Size, Offset, Index>);
  Offset* key_offsets = reinterpret_cast<Offset*>(states + count);
  Size* data_offsets =
      reinterpret_cast<Size*>(states + count * (sizeof(Offset)));
  Size *hashes = reinterpret_cast<Size*>(
           states + count * (sizeof(Offset) + sizeof(Size))),
       *hash_ptr;
  Index *indexes = reinterpret_cast<Index*>(
            states + count * (sizeof(Offset) + sizeof(Size) + sizeof(Index))),
        *unsorted_indexes = indexes + count,
        *collission_list = unsorted_indexes + count;
  CH1 *keys = reinterpret_cast<CH1*>(dictionary) + table_size - 1, *destination;

  // Calculate space left.
  Offset value =
             table_size - count * DicOverheadPerIndex<Index, Offset, Size>(),
         key_length = static_cast<UI2>(SlotLength(key)), size_pile;

  TPrintLinef();
  PRINTF(
      "Adding Key %s\n%20s: 0x%p\n%20s: %p\n%20s: 0x%p\n"
      "%20s: %p\n%20s: %u\n",
      key, "hashes", hashes, "key_offsets", key_offsets, "keys", keys,
      "indexes", indexes, "value", value)

  Size hash = Hash16(key), current_hash;

  if (key_length > value) {
    PRINTF("Buffer overflow\n")
    return ~((Index)0);
  }

  // utf ();

  if (item_count == 0) {
    dictionary->item_count = 1;
    *hashes = hash;
    *key_offsets = static_cast<UI2>(key_length);
    *indexes = ~0;
    *unsorted_indexes = 0;
    destination = keys - key_length;

    SlotWrite(destination, key);
    PRINTF("\nInserted key %s at GetAddress 0x%p", key, destination)
    DicPrint(dictionary);
    return 0;
  }

  // Calculate left over socket size by looking up last CH1.

  if (key_length >= value) {
    PRINTF("\nNot enough room in buffer!")
    return 0;  //< There isn't enough room left in the socket.
  }

  PRINTF("\nFinding insert location...")

  SI4 low = 0, mid, high = item_count, index;

  Index* temp_ptr;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_hash = hashes[mid];
    PRINTF("high: %i mid: %i low %i hash: %x\n", high, mid, low, current_hash)

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {  // Duplicate hash detected.
      PRINTF("hash detected, ")

      // Check for other collisions.

      index = indexes[mid];  //< Index in the collision table.

      PRINTF("index:%u", index)

      if (index < ~0) {  //< There are other collisions.
        PRINTF("with collisions, ")
        // There was a collision so check the table.

        // The collisionsList is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisionsList is searched from
        // lower address up.
        temp = indexes[mid];
        temp_ptr = collission_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < MaxDicIndexes<Index>()) {
          PRINTF("comparing to \"%s\"", keys - key_offsets[index])
          if (strcmp(key, keys - key_offsets[index]) == 0) {
            PRINTF(" but table already contains key at offset: %u.\n", index)
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }

        // Its a new collision!
        PRINTF("and new collision detected.")

        // Copy the key
        value = key_offsets[item_count - 1] + key_length + 1;
        SlotWrite(keys - value, key);
        key_offsets[item_count] = value;

        // Update the collision table.
        size_pile = dictionary->size_pile;
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

        dictionary->size_pile = size_pile + 1;
        PRINTF("\ncollision index: %u", temp)
        // Store the collision index.
        indexes[item_count] = temp;  //< Store the collision index
        dictionary->item_count = item_count + 1;
        hashes[item_count] = ~0;  //< Dictionary the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        indexes += count;

        //< Add the newest CH1 to the stop.
        indexes[item_count] = item_count;

        DicPrint(dictionary);
        PRINTF("Done inserting.\n")
        return item_count;
      }

      // But we still don't know if the CH1 is a new collision.

      PRINTF("Checking if it's a collision... ")

      if (strcmp(key, keys - key_offsets[index]) != 0) {
        // It's a new collision!
        PRINTF("It's a new collision!\n")

        if (value < 3) {
          PRINTF("Buffer overflow!\n")
          return ~0;
        }

        // Get offset to write the key too.
        value = key_offsets[item_count - 1] + key_length + 1;

        UI1 collision_index = unsorted_indexes[mid];
        PRINTF("\n\ncollision_index: %u", collision_index)

        SlotWrite(keys - value, key);
        PRINTF(
            "\nInserting value: %u into index:%u item_count:%u with other "
            "collision_index: %u",
            value, index, item_count, collision_index)
        key_offsets[item_count] = value;

        size_pile = dictionary->size_pile;
        indexes[mid] = static_cast<UI1>(size_pile);
        indexes[item_count] = static_cast<UI1>(size_pile);

        // Insert the collision into the collision table.
        temp_ptr = &collission_list[size_pile];
        // Move collisions pointer to the unsorted_indexes.
        indexes += count;
        *temp_ptr = collision_index;
        ++temp_ptr;
        *temp_ptr = item_count;
        ++temp_ptr;
        *temp_ptr = ~0;
        dictionary->size_pile = size_pile + 3;
        //< Added one term-UI1 and two indexes.

        // Add the newest key at the stop.
        indexes[item_count] = item_count;

        // Dictionary the last hash to 0xFFFF
        hashes[item_count] = ~0;

        dictionary->item_count = item_count + 1;

        DicPrint(dictionary);

        DicPrint(dictionary);
        PRINTF("\nDone inserting.")
        // Then it was a collision so the table doesn't contain .
        return item_count;
      }
      PRINTF("\nTable already contains the key")
      return index;
    }
  }

  // The hash was not in the table.

  value = key_offsets[item_count - 1] + key_length + 1;
  destination = keys - value;

  PRINTF(
      "The hash 0x%x was not in the table so inserting %s into mid: %i at "
      "index %u before hash 0x%x \n",
      hash, key, mid, Diff(dictionary, destination), hashes[mid]);

  // First copy the CH1 and set the key offset.
  SlotWrite(destination, key);
  key_offsets[item_count] = value;

  // Second move up the hashes and insert at the insertion point.
  hash_ptr = hashes;
  hash_ptr += item_count;
  //*test = hashes;
  PRINTF("l_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u\n", item_count,
         Diff(dictionary, hashes), Diff(dictionary, hash_ptr),
         Diff(dictionary, hashes + mid))
  hashes += mid;
  DicPrint(dictionary);
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = hash;

  // Mark as not having any collisions.
  indexes[item_count] = ~0;

  // Move up the sorted indexes and insert the unsorted index (which is
  // the current ;).
  indexes += count + mid;
  temp_ptr = indexes + item_count;

  while (temp_ptr > indexes) {
    *temp_ptr = *(temp_ptr - 1);
    --temp_ptr;
  }
  *temp_ptr = item_count;

  dictionary->item_count = item_count + 1;

  DicPrint(dictionary);
  PRINTF("Done inserting.\n")
  TPrintLinef();

  return item_count;
}

/* Adds a key-value pair to the stop of the dictionary. */
// UI1 Add2 (Dic2* dictionary, const CH1* key, UI1 data) {
//    return DicAdd<UI1, UI2, UI2, UI2> (dictionary, key, kUI1,
//    &data);
//}

/* Returns  the given query CH1 in the hash table. */
template <typename Size, typename Offset, typename Index>
Index DictionaryFind(Dictionary<Size, Offset, Index>* dictionary,
                     const CH1* key) {
  if (dictionary == nullptr) return 0;
  PRINT_HEADING("Finding record...")
  Index index, item_count = dictionary->item_count, count = dictionary->count,
               temp;

  if (key == nullptr || item_count == 0) return ~((Index)0);

  Offset table_size = dictionary->table_size;

  const Size* hashes =
      reinterpret_cast<const Size*>(reinterpret_cast<const CH1*>(dictionary) +
                                    sizeof(Dictionary<Size, Offset, Index>));
  const Offset* key_offsets = reinterpret_cast<const UI2*>(hashes + count);
  const Index *indexes = reinterpret_cast<const Index*>(key_offsets + count),
              *unsorted_indexes = indexes + count,
              *collission_list = unsorted_indexes + count;
  const CH1* keys = reinterpret_cast<const CH1*>(dictionary) + table_size - 1;
  const Index *collisions, *temp_ptr;

  Size hash = Hash16(key);

  PRINTF("\nSearching for key \"%s\" with hash 0x%x", key, hash)

  if (item_count == 1) {
    if (!SlotEquals(key, keys - key_offsets[0])) {
      PRINTF("\nDid not find key %s", key)
      return ~((Index)0);
    }
    PRINTF("\nFound key \"%s\"", key)
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
    PRINTF("\nlow: %i mid: %i high %i hashes[mid]:%x", low, mid, high,
           hashes[mid])

    if (current_hash > hash) {
      high = mid - 1;
    } else if (current_hash < hash) {
      low = mid + 1;
    } else {
      // Duplicate hash found.
      PRINTF(
          "\nFound same hash at mid:%i hash:%x offset for key: "
          "%s",
          mid, hashes[mid], key)

      // Check for collisions
      collisions =
          reinterpret_cast<const Index*>(key_offsets) + count * sizeof(Offset);

      index = collisions[mid];

      if (index < ~0) {
        // There was a collision so check the table.
        PRINTF("\nThere was a collision so check the table")

        // The collisionsList is a sequence of indexes terminated by
        // an invalid index > kMaxNumOperands. collissionsList[0] is an
        // invalid index, so the collisionsList is searched from
        // lower address up.

        temp = indexes[mid];

        temp_ptr = collission_list + temp;
        index = *temp_ptr;
        while (index < MaxDicIndexes<Index>()) {
          PRINTF("\nComparing to \"%s\"", keys - key_offsets[index]);
          if (!SlotEquals(key, keys - key_offsets[index])) {
            PRINTF("but table already contains key at offset:%u.", index)
            return index;
          }
          ++temp_ptr;
          index = *temp_ptr;
        }
        PRINTF("Did not find \"" << key << "\"\n")
        return ~((Index)0);
      }

      // There were no collisions.

      // But we still don't know if the CH1 is new or a collision.

      // Move collisions pointer to the unsorted indexes.
      indexes += count;
      index = unsorted_indexes[mid];

      PRINTF("\n!!!mid: %i-%x unsorted_indexes: %u key: %s\n hash: %x\n", mid,
             hashes[mid], index, keys - key_offsets[index],
             Hash16(keys - key_offsets[index]));

      if (!SlotEquals(key, keys - key_offsets[index]) != 0) {
        //< It was a collision so the table doesn't contain .
        PRINTF(" but it was a collision and did not find key.\n");
        return ~((Index)0);
      }

      PRINTF("and found key at mid: %i", (SI4)mid);
      return index;
    }
  }
  PRINTF("\nDid not find a hash for key \"%s\"", key);
  TPrintLinef();

  return ~((Index)0);
}

/* Prints this object out to the console. */
template <typename Size, typename Offset, typename Index, typename Char = CH1>
TUTF<Char> DicPrint(TUTF<Char>& utf,
                    const Dictionary<Size, Offset, Index>* dictionary) {
  ASSERT(dictionary)

  Index item_count = dictionary->item_count, count = dictionary->count,
        collision_index, temp;
  Offset table_size = dictionary->table_size, size_pile = dictionary->size_pile;

  PRINT_LINEF('_', 80);

  PRINTF((sizeof(Size) == 2)
             ? "\nDic2:\n"
             : (sizeof(Size) == 4)
                   ? "\nDic4:0x%p\n"
                   : (sizeof(Size) == 8) ? "\nDic8:0x%p\n" : "\nError:");
  PRINTF("\n0x%p %u stack_height: %u size_pile: %u  size: %u\n|", dictionary,
         item_count, stack_height, size_pile, table_size);
  PRINT_LINEF('_', 80);
  PRINTF('\n');

  const CH1* states = reinterpret_cast<const CH1*>(dictionary) +
                      sizeof(Dictionary<Size, Offset, Index>);
  const Offset* key_offsets = reinterpret_cast<const Offset*>(states + count);
  // const Size* data_offsets = reinterpret_cast<const Size*>
  //                            (states + stack_height *(sizeof (Offset)));
  const Size* hashes = reinterpret_cast<const Size*>(
      states + count * (sizeof(Offset) + sizeof(Size)));
  const Index *indexes = reinterpret_cast<const Index*>(
                  states +
                  count * (sizeof(Offset) + sizeof(Size) + sizeof(Index))),
              *unsorted_indexes = indexes + count,
              *collission_list = unsorted_indexes + count, *begin;
  const CH1* keys = reinterpret_cast<const CH1*>(dictionary) + table_size - 1;

  PRINTF("\n%3s%10s%8s%10s%10s%10s%10s%11s\n", "i", "key", "offset", "hash_e",
         "hash_u", "hash_s", "index_u", "collisions");
  PRINT('|');
  for (SI4 i = 0; i < 79; ++i) PRINT('_');
  PRINT('\n');

  for (Index i = 0; i < count; ++i) {
    // Print each record as a row.
    // @todo Change stack_height to ; after done debugging.
    collision_index = indexes[i];
    PRINTF("\n%3i %9s %7u %9x %9x %9x %9u %10u: ", i, keys - key_offsets[i],
           key_offsets[i], Hash16(keys - key_offsets[i]),
           hashes[unsorted_indexes[i]], hashes[i], unsorted_indexes[i],
           collision_index);

    if (collision_index != ~0 && i < item_count) {
      // Print collisions.
      begin = &collission_list[collision_index];
      temp = *begin;
      ++begin;
      PRINTF("%u@", temp);
      while (temp != ~0) {
        temp = *begin;
        ++begin;
        if (temp == ~0) break;
        PRINTF(", %u$", temp);
      }
    }

    PRINT('\n');
  }
  TPrintLinef('_');

  PrintChars(reinterpret_cast<const CH1*>(dictionary) +
                 sizeof(Dictionary<Size, Offset, Index>),
             dictionary->size);
  PRINT('\n');
}

/* Deletes the dictionary contents without wiping the contents. */
template <typename Size, typename Offset, typename Index>
void DicClear(Dictionary<Size, Offset, Index>* dictionary) {
  ASSERT(dictionary);

  dictionary->item_count = 0;
  dictionary->size_pile = 0;
}

/* Deletes the dictionary contents by overwriting it with zeros. */
template <typename Size, typename Offset, typename Index>
void DictionaryWipe(Dictionary<Size, Offset, Index>* dictionary) {
  ASSERT(dictionary);

  Size size = dictionary->size;
  memset(dictionary, 0, size);
}

/* Returns true if this crabs contains only the given address. */
template <typename Size, typename Offset, typename Index>
void* DicContains(Dictionary<Size, Offset, Index>* dictionary, void* data) {
  ASSERT(dictionary);

  if (data < dictionary) return false;
  CH1* base = reinterpret_cast<CH1*>(dictionary);
  if (data < base) return nullptr;
  if (data > base + dictionary->size_bytes) return nullptr;
  return data;
}

/* Removes that object from the dictionary and copies it to the destination. */
template <typename Size, typename Offset, typename Index>
BOL DicRemoveCopy(Dictionary<Size, Offset, Index>* dictionary,
                  void* destination, SIW buffer_size, void* data) {
  ASSERT(dictionary);

  return false;
}

/* Removes the item at the given address from the dictionary. */
template <typename Size, typename Offset, typename Index>
BOL DicRemove(Dictionary<Size, Offset, Index>* dictionary, void* adress) {
  ASSERT(dictionary);

  return false;
}

/* Prints the given Dictionary to the console. */
template <typename Size, typename Offset, typename Index>
UTF1& DicPrint(UTF1& utf, Dictionary<Size, Offset, Index>* dictionary) {
  ASSERT(dictionary);
  return utf;
}

}  // namespace _

#endif  //< SCRIPT2_TDIC
#endif  //< #if SEAM >= SCRIPT2_13
