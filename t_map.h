/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_map.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the 
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with 
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>
#if SEAM >= SEAM_SCRIPT2_LIST
#ifndef INCLUDED_CRAPS_TMAP
#define INCLUDED_CRAPS_TMAP

#include "c_avalue.h"
#include "c_socket.h"

#if SEAM == SEAM_SCRIPT2_LIST
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* A one-to-one map that does not use hash table.

Maps share the same data structure as Multimaps, Dictionary(s) and Lists.
Maps like all Script Objects are required to are required to have a
stack_height, size_bytes, and header_size that is a multiple of 8 as well as
being .

It is easiest to explain this data structure in terms of the Socket. Sockets
use a TMap to map a Slot number_ to a slot.

# TMap Data Structure

@code
+===========================+ -----------
|_______ Buffer             |   ^     ^
|_______ ...                |   |     |
|_______ Data N             |  Data   |
|_______ ...                |   |     |
|_______ Data 0             |   v     |
|===========================| -----   |
|_______ count_max          |   ^     |
|_______ ...                |   |     |
|_______ Sorted Mappings N  |   |     |
|_______ ...                |   |     |
|        Sorted Mappings 1  |   |     |
|===========================|   |     |
|_______ count_max          |   |    Size
|_______ ...                |   |     |
|_______ Data Offset N      |   |     |
|_______ ...                | Header  |
|        Data Offset 1      |   |     |
|===========================|   |     |
|_______ count_max          |   |     |
|_______ ...                |   |     |
|_______ Type UI1 N         |   |     |
|_______ ...                |   |     |
|        Type UI1 1         |   |     |   ^ Up in addresses
|===========================|   |     |   |
|    TSparseArray Struct    |   v     v   ^
+===========================+ ----------- ^ 0xN
@endcode

| Map | Max Values | % Collisions (p) |           Overhead             |
|:---:|:----------:|:----------------:|:------------------------------:|
|  2  |     255    |    0.0001        | Ceiling (0.02*p*2^8)  = 2      |
|  4  |     2^13   |      0.1         | Ceiling (0.04*p*2^13) = 327.68 |
|  8  |     2^29   |    10^-16        | Ceiling (0.04*p*2^29) = 327.68 |

Memory Schema:
The memory schema is optimized for fast search and push back. When searching
for a key, there might or might not be a hash table.

How to calculate size:
The size of any size map can be calculated as follows:
size = ; * (2*sizeof (Index) + sizeof (Size)) + collissionSize +

# Cache Page Optimizations

In order to optimize the cache pages, we need to group hot data together.
ChineseRoom Objs work through calling by Index, or by key by using the
function '\"' (i.e. "foo" is Index 44).

# Use Case Scenario

We are creating a plug-in LIB_MEMBER. We need to create a map in the LIB_MEMBER code, and
pass it over to the program. The LIB_MEMBER manages the memory for the map. This
map might contain several million entries, and more than 4GB of data.

### Why So Many TMap Types?

We are running in RAM, and a map could contain millions of key-value pairs.
Adding extra bytes would added megabytes of data we don't need. Also, on
microcontrollers, especially 16-bit ones, will have very little RAM, so we
need an 16-bit object. It is easy to imagine a complex AI software using
more than 4GB RAM, or the need to attach a DVD ISO image as a key-value
pair, so we need a 64-bit map.

# Design Strengths

* Uses less memory.
* Fast push back when within socket size.
* Faster inserts on small collections when within socket size.
* 64-bit memory alignment ensures highest performance on Intel.
* Mandating zeros in buffered memory space can serve help sanitize input.

# Design Weaknesses

* Slow insert in large collections.
* Slow at growing large collections when socket runs out.
* Applications with billions of items may have too much memory overhead.
* More complicated.

@code
.
.
.
@endcode
*/
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
struct TMap {
  Size size;        //< ASCII AArray size.
  Index table_size, /*< Size of the key strings in bytes.
                     Set to 0 for ASCII Map. */
      size_pile;    /*< Size of the collisions pile in bytes.
                        Set to 0 for ASCII Map and ASCII Multimap. */
  I count,          //< Element count.
      count_max;    //< Max count of items that can fit in the socket.
};

template <typename Size = UI4, typename Index = SI4, typename I = SI2>
constexpr SI4 MapOverheadPerIndex() {
  return sizeof(2 * sizeof(Index) + sizeof(Size) + sizeof(Size) + 3);
};

template <typename Size = UI4, typename Index = SI4, typename I = SI2>
constexpr Size MapSizeRequired(Index count) {
  return count * sizeof(2(sizeof(Index) + sizeof(Size)) + 3);
};

enum {
  kMaxNumPagesMap2 = 255,                //< The number_ of pages in a Map2.
  kMaxNumPagesMap4 = 8 * 1024,           //< The number_ of pages in a Map4.
  kMaxNumPagesMap8 = 256 * 1024 * 1024,  //< The number_ of pages in a Map8.
  kOverheadPerMap2Index = MapOverheadPerIndex<UI2, SI2, SI1>(),
  kOverheadPerMap4Index = MapOverheadPerIndex<UI4, SI4, SI2>(),
  kOverheadPerMap8Index = MapOverheadPerIndex<UI8, SI8, SI4>(),
};

/* Initializes a TMap from a word-aligned socket.
    @post    Users might want to call the IsValid () function after construction
             to verify the integrity of the object.
    @warning The reservedNumOperands must be aligned to a 32-bit value, and it
             will get rounded up to the next higher multiple of 4.
*/
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
TMap<Size, Index, I>* MapInit(UIW* socket, Size size, I count_max) {
  A_ASSERT(socket);

  if (table_size >= size) return nullptr;
  Size kSizeMin = sizeof(TMap<Size, Index, I>) +
                  count_max * (MapOverheadPerIndex<Size, Index, I>() + 2);
  if (table_size < kSizeMin) return nullptr;

  Map<Size, Index, I>* map = reinterpret_cast<TMap*>(socket);
  map->size = table_size;
  map->table_size = table_size;
  map->size_pile = 1;
  map->count_max = count_max;
  map->count = 0;
  return map;
}
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
inline Size MapSizeBoundsLower() {
  return 64;
}
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
inline Size MapSizeBoundsUpper() {
  Size bounds_upper = 0;
  bounds_upper = ~bounds_upper;
  return bounds_upper - 7;
}

template <typename Size = UI4, typename Index = SI4, typename I = SI2>
inline Index MapCountBoundsLower() {
  return 8 / sizeof(Size);
}

/* Creates a map from dynamic memory. */
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
UIW* MapNew(Size size = 0, I count_max = 0) {
  size = AlignDown<SI8, Size>(size);
  count_max = AlignDown<SI8, Index>(count_max);
  Size size_min = MapSizeBoundsLower<Size, Index, I>();
  Index count_min = MapCountBoundsLower<Size, Index, I>();
  if (size < size_min || count_max < count_min) {
    size = size_min;
    count_max = size_min;
  }

  UIW* socket = new UIW[size >> kWordBitCount];
  TMap<Size, Index, I>* map = reinterpret_cast<TMap<Size, Index, I>*>(socket);
  map->size = size;
  map->table_size = 0;
  map->size_pile = 0;
  map->count = 0;
  map->count_max = count_max;
  return socket;
}

template <typename Index>
Index MapCountUpperBounds() {
  enum {
    kCountUpperBounds = sizeof(Index) == 1
                            ? 120
                            : sizeof(Index) == 2
                                  ? 8 * 1024
                                  : sizeof(Index) == 4 ? 512 * 1024 * 1024 : 0
  };
  return CountUpperBounds;
}

/* Insets the given key-type-value tuple.
 */
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
Index MapInsert(TMap<Size, Index, I>* map, void* value, SI4 type, Index index) {
  A_ASSERT(map);
  A_ASSERT(value);

  D_COUT_LINEF(id, 80);

  Index count = map->count, count = map->stack->count, temp;

  Size table_size = map->table_size;

  if (count >= count) return ~0;
  //< We're out of buffered indexes.

  CH1* types = reinterpret_cast<CH1*>(map) + sizeof(TMap<Size, Index, I>);
  Size* data_offsets = reinterpret_cast<Size*>(types + count * (sizeof(Size)));
  Size *hashes = reinterpret_cast<Size*>(types +
                                         count * (sizeof(Size) + sizeof(Size))),
       *hash_ptr;
  Index *indexes = reinterpret_cast<Index*>(
            types + count * (sizeof(Size) + 2 * sizeof(Index))),
        *unsorted_indexes = indexes + count,
        *collission_list = unsorted_indexes + count;
  CH1 *keys = reinterpret_cast<CH1*>(map) + table_size - 1, *destination;

  // Calculate space left.
  Size value = table_size - count * MapOverheadPerIndex<Size, Index, I>(),
       key_length = static_cast<UI2>(strlen(id)), size_pile;

  D_COUT_LINEF('-');
  D_PRINTF(
      "\nAdding Key %s\n%20s: 0x%p\n%20s: %p\n%20s: 0x%p"
      "%20s: %p\n%20s: %u\n",
      id, "hashes", hashes, "key_offsets", key_offsets, "keys", keys, "indexes",
      indexes, "value", value);

  Size temp_id = HashPrime16(id), current_mapping;

  if (key_length > value) {
    D_PRINTF("\nBuffer overflow!");
    return ~((Index)0);
  }

  if (count == 0) {
    map->count = 1;
    *hashes = temp_id;
    *key_offsets = static_cast<UI2>(key_length);
    *indexes = ~0;
    *unsorted_indexes = 0;
    destination = keys - key_length;

    SlotWrite(destination, id);
    D_PRINTF("\nInserted key %s at GetAddress 0x%p", id, destination);
    MapPrint(map);
    return 0;
  }

  // Calculate left over socket size by looking up last CH1.

  if (key_length >= value) {
    D_PRINTF("\nNot enough room in buffer!");
    return 0;  //< There isn't enough room left in the socket.
  }

  D_PRINTF("\nFinding insert location...");

  Index low = 0, mid, high = count, index;

  Index* temp_ptr;

  while (low <= high) {
    mid = (low + high) >> 1;  //< Shift >> 1 to / 2

    current_mapping = hashes[mid];
    D_PRINTF("\nhigh: %i mid: %i low %i hash: %x", high, mid, low,
           current_mapping);

    if (current_mapping > temp_id) {
      high = mid - 1;
    } else if (current_mapping < temp_id) {
      low = mid + 1;
    } else {
      D_PRINTF(" duplicate hash detected, ");

      // Check for other collisions.

      index = indexes[mid];  //< Index in the collision table.

      D_PRINTF("index:%i", (SI4)index);

      if (index < ~0) {  //< There are other collisions.
        D_PRINTF("with collisions, ");
        // There was a collision so check the table.

        // The collisionsList is a sequence of indexes terminated
        // by an invalid index. collissionsList[0] is
        // an invalid index, so the collisionsList is searched from
        // lower address up.
        temp = indexes[mid];
        temp_ptr = collission_list + temp;
        index = *temp_ptr;  //< Load the index in the collision table.
        while (index < MapCountUpperBounds<Index>()) {
          D_PRINTF("\ncomparing to \"%s\"", keys - key_offsets[index]);
          if (strcmp(id, keys - key_offsets[index]) == 0) {
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
        D_PRINTF(" new collision detected.");

        // Copy the key
        value = key_offsets[count - 1] + key_length + 1;
        SlotWrite(keys - value, id);
        key_offsets[count] = value;

        // Update the collision table.
        size_pile = map->size_pile;
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

        map->size_pile = size_pile + 1;
        D_PRINTF("\ncollision index: %u", temp);
        // Store the collision index.
        indexes[count] = temp;  //< Store the collision index
        map->count = count + 1;
        hashes[count] = ~0;  //< TMap the last hash to 0xFFFF

        // Move collisions pointer to the unsorted_indexes.
        indexes += count;

        //< Add the newest CH1 to the stop.
        indexes[count] = count;

        MapPrint(map);
        D_COUT("\nDone inserting.");
        return count;
      }

      // But we still don't know if the CH1 is a new collision.

      D_COUT("\nChecking if it's a collision... ");

      if (strcmp(id, keys - key_offsets[index]) != 0) {
        // It's a new collision!
        D_COUT("It's a new collision!");

        if (value < 3) {
          D_COUT("Buffer overflow!");
          return ~0;
        }

        // Get offset to write the key too.
        value = key_offsets[count - 1] + key_length + 1;

        SI4 collision_index = unsorted_indexes[mid];
        D_PRINTF("\n\ncollision_index: %u", collision_index);

        SlotWrite(keys - value, id);
        D_PRINTF(
            "\nInserting value: %u into index:%u "
            "count:%u with other collision_index: %u",
            value, index, count, collision_index);
        key_offsets[count] = value;

        size_pile = map->size_pile;
        indexes[mid] = static_cast<SI4>(size_pile);
        indexes[count] = static_cast<SI4>(size_pile);

        // Insert the collision into the collision table.
        temp_ptr = &collission_list[size_pile];
        // Move collisions pointer to the unsorted_indexes.
        indexes += count;
        *temp_ptr = collision_index;
        ++temp_ptr;
        *temp_ptr = count;
        ++temp_ptr;
        *temp_ptr = ~0;
        map->size_pile = size_pile + 3;
        //< Added one term-SI4 and two indexes.

        // Add the newest key at the stop.
        indexes[count] = count;

        // TMap the last hash to 0xFFFF
        hashes[count] = ~0;

        map->count = count + 1;

        MapPrint(map);

        MapPrint(map);
        D_COUT("\nDone inserting.");
        // Then it was a collision so the table doesn't contain .
        return count;
      }
      D_COUT("\nTable already contains the key");
      return index;
    }
  }

  // The id was not in the table.

  value = key_offsets[count - 1] + key_length + 1;
  destination = keys - value;

  D_PRINTF(
      "\nThe id 0x%x was not in the table so inserting %s into mid:"
      " %i at index %u before hash 0x%x",
      temp_id, id, mid, Diff(map, destination), hashes[mid]);

  // First copy the CH1 and set the key offset.
  SlotWrite(destination, id);
  key_offsets[count] = value;

  // Second move up the hashes and insert at the insertion point.
  hash_ptr = hashes;
  hash_ptr += count;
  //*test = hashes;
  D_PRINTF("\nl_numkeys: %u, hashes: %u hash_ptr: %u insert_ptr: %u", count,
         Diff(map, hashes), Diff(map, hash_ptr), Diff(map, hashes + mid));
  hashes += mid;
  MapPrint(map);
  while (hash_ptr > hashes) {
    *hash_ptr = *(hash_ptr - 1);
    --hash_ptr;
  }
  *hashes = temp_id;

  // Mark as not having any collisions.
  indexes[count] = ~0;

  // Move up the sorted indexes and insert the unsorted index (which is
  // the current count).
  indexes += count + mid;
  temp_ptr = indexes + count;

  while (temp_ptr > indexes) {
    *temp_ptr = *(temp_ptr - 1);
    --temp_ptr;
  }
  *temp_ptr = count;

  map->count = count + 1;

  MapPrint(map);
  D_COUT("\nDone inserting.");
  D_COUT_LINEF('-');

  return count;
}

/* Deletes the map contents without wiping the contents. */
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
void MapClear(TMap<Size, Index, I>* map) {
  A_ASSERT(map);

  map->count = 0;
  map->size_pile = 0;
}

/* Deletes the map contents by overwriting it with zeros. */
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
void MapWipe(TMap<Size, Index, I>* map) {
  A_ASSERT(map);

  Size size = map->size;
  MemoryWipe(reinterpret_cast<CH1*>(map) + sizeof(TMap<Size, Index, I>), size);
}

/* Returns true if this crabs contains only the given address. */
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
BOL MapContains(TMap<Size, Index, I>* map, void* value) {
  A_ASSERT(map);

  if (value < map) return false;
  if (value > GetEndAddress()) return false;
  return true;
}

/* Removes the item at the given address from the map. */
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
BOL MapRemove(TMap<Size, Index, I>* map, void* adress) {
  A_ASSERT(map);

  return false;
}

/* Prints this object out to the console. */
template <typename Size = UI4, typename Index = SI4, typename I = SI2,
          typename Char = CHR>
TUTF<Char>& MapPrint(TUTF<Char>& utf, const TMap<Size, Index, I>* map) {
  A_ASSERT(map)
  l

      Index count = map->count,
            collision_index, temp;
  Size table_size = map->table_size, size_pile = map->size_pile;

  utf << '_';

  utf << "\nMap" << sizeof(Size) << ": " << Hex<>(map) << " count:" << count
      << "size_pile:" << size_pile << " size:" << map->size;
  utf << "\n|";
  for (SI4 i = 0; i < 79; ++i) utf << '_';
  utf << kLF;

  const CH1* states =
      reinterpret_cast<const CH1*>(map) + sizeof(TMap<Size, Index, I>);
  const Size* key_offsets = reinterpret_cast<const Size*>(states + count);
  const Size* data_offsets =
      reinterpret_cast<const Size*>(states + count * sizeof(Size));
  const Size* hashes = reinterpret_cast<const Size*>(
      states + count * (sizeof(Size) + sizeof(Size)));
  const Index *indexes = reinterpret_cast<const Index*>(
                  states +
                  count * (sizeof(Size) + sizeof(Size) + sizeof(Index))),
              *unsorted_indexes = indexes + count,
              *collission_list = unsorted_indexes + count, *begin;
  const CH1* keys = reinterpret_cast<const CH1*>(map) + table_size - 1;
  utf << "\n " << Right<>("i", 3) << Right<>("key", 10) << Right<>("offset", 8)
      << Right<>("hash_e", 10) << Right<>("hash_s", 10)
      << Right<>("index_u", 10) << Right<>("collisions", 11);
  utf << '|';
  for (SI4 i = 0; i < 79; ++i) utf << '_';
  utf << kLF;

  for (Index i = 0; i < count; ++i) {
    // Print each record as a row.
    // @todo Change stack_height to ; after done debugging.
    collision_index = indexes[i];
    utf << Right<Index>(i, 3) << Right<Index>(keys - key_offsets[i], 10)
        << Right<Index>(key_offsets[i], 8)
        << Right<Hex<Size>>(HashPrime16(keys - key_offsets[i]), 10)
        << Right<Hex<Size>>(hashes[unsorted_indexes[i]], 10)
        << Right<Hex<Size>>(hashes[i], 10)
        << Right<Size>(unsorted_indexes[i], 10)
        << Right<Size>(collision_index, 11);

    if (collision_index != ~0 && i < item_count) {
      // Print collisions.
      begin = &collission_list[collision_index];
      temp = *begin;
      ++begin;
      utf << temp;
      while (temp != ~0) {
        temp = *begin;
        ++begin;
        if (temp == ~0) break;
        utf << ", " << temp;
      }
    }

    utf << '_';
  }

  return utf << '_' << Socket(reinterpret_cast<const CH1*>(map), map->size)
             << kLF;
}

/* C++ Wrapper for the AsciiMap that uses dynamic memory and auto-grows.

    @code
    .
    .
    .
    @endcode
*/
template <typename Size = UI4, typename Index = SI4, typename I = SI2>
class Map {
 public:
  /* Constructs a Map with the given count_max.
      If count_max is less than 0 it will be set to the default value. IF the
      */
  Map(Size size = 0, I count_max = 0)
      : socket(MapNew<Size, Index, I>(size, count_max)) {
    // Nothing to do here! (:-)-+=<
  }

  /* Destructs the dynamically allocated socket. */
  ~Map() { delete socket; }

  inline BOL Remove(void* adress) {
    return MapRemove<Size, Index, I>(AArray(), adress);
  }

  /* Checks if the map contains the given pointer.
      @return True if the pointer lies in this socket. */
  inline BOL Contains(void* value) {
    return MapContains<Size, Index, I>(AArray(), value);
  }

  /* Wipes the map by overwriting it with zeros. */
  inline void Wipe() { MapWipe<Size, Index, I>(AArray()); }

  static inline Index CountUpperBounds() {
    return MapCountUpperBounds<Size, Index, I>();
  }

  inline Index Insert(void* value, Index index, SI4 type) {
    return MapInsert<Size, Index, I>(AArray(), value, type, index);
  }

  /* Clears the list. */
  inline void Clear() { MapClear<Size, Index, I>(AArray()); }

  /* Prints this object to a printer. */
  inline UTF1& Print(UTF1& printer) {
    return MapPrint<Size, Index, I>(utf, AArray());
  }

 private:
  UIW* socket;

  /* Returns the socket casted as a TMap<Size, Index, I>*. */
  inline TMap<Size, Index, I>* AArray() {
    return reinterpret_cast<TMap<Size, Index, I>*>(socket);
  }
};  //< class Map
}  // namespace _

#endif  //< INCLUDED_CRAPS_TMAP
#endif  //< #if SEAM >= SEAM_SCRIPT2_LIST
