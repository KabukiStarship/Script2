/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_map.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_LIST
#ifndef INCLUDED_CRAPS_TMAP
#define INCLUDED_CRAPS_TMAP

#include "c_avalue.h"
#include "c_socket.h"

#if SEAM == SCRIPT2_LIST
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
+---------------------------+ -----------
|_______ Buffer             |   ^     ^
|_______ Data object N      |  Data   |
|_______ Data object 0      |   v     |
+---------------------------+ -----   |
|_______ Buffer             |   ^     |
|_______ Sorted Mappings N  |   |     |
|        Sorted Mappings 1  |   |     |
+---------------------------+   |     |
|_______ Buffer             |   |    SIZ
|_______ Data Offset N      | Header  |
|        Data Offset 1      |  SIZ   |
+---------------------------+   |     |
|_______ Buffer             |   |     |
|_______ Type N             |   |     |
|        Type 1             |   |     |   ^ Up in addresses
+---------------------------+   |     |   |
|     TMapSparse Struct     |   v     v   ^
+---------------------------+ ----------- ^ 0xN base address
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
size = ; * (2*sizeof (UIY) + sizeof (SIZ)) + collissionSize +

# Cache Page Optimizations

In order to optimize the cache pages, we need to group hot data together.
ChineseRoom Objs work through calling by UIY, or by key by using the
function '\"' (i.e. "foo" is UIY 44).

# Use Case Scenario

We are creating a plug-in LIB_MEMBER. We need to create a map in the LIB_MEMBER
code, and pass it over to the program. The LIB_MEMBER manages the memory for the
map. This map might contain several million entries, and more than 4GB of data.

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
template <typename SIZ = SI4, typename SIY = SI2>
struct TMap {
  SIZ size;       //< ASCII AArray size.
  SIY table_size, /*< SIZ of the key strings in bytes.
                     Set to 0 for ASCII Map. */
      size_pile,  /*< SIZ of the collisions pile in bytes.
                      Set to 0 for ASCII Map and ASCII Multimap. */
      count,      //< Element count.
      count_max;  //< Max count of items that can fit in the socket.
};

template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
constexpr SI4 MapOverheadPerIndex() {
  return sizeof(2 * sizeof(UIY) + sizeof(SIZ) + sizeof(SIZ) + 3);
};

template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
constexpr SIZ MapSizeRequired(UIY count) {
  return count * sizeof(2(sizeof(UIY) + sizeof(SIZ)) + 3);
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
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
TMap<SIZ, UIY, I>* MapInit(UIW* socket, SIZ size, I count_max) {
  A_ASSERT(socket);

  if (table_size >= size) return nullptr;
  SIZ kSizeMin = sizeof(TMap<SIZ, UIY, I>) +
                 count_max * (MapOverheadPerIndex<SIZ, UIY, I>() + 2);
  if (table_size < kSizeMin) return nullptr;

  Map<SIZ, UIY, I>* map = reinterpret_cast<TMap*>(socket);
  map->size = table_size;
  map->table_size = table_size;
  map->size_pile = 1;
  map->count_max = count_max;
  map->count = 0;
  return map;
}
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
inline SIZ MapSizeBoundsLower() {
  return 64;
}
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
inline SIZ MapSizeBoundsUpper() {
  SIZ bounds_upper = 0;
  bounds_upper = ~bounds_upper;
  return bounds_upper - 7;
}

template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
inline UIY MapCountBoundsLower() {
  return 8 / sizeof(SIZ);
}

/* Creates a map from dynamic memory. */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
UIW* MapNew(SIZ size = 0, I count_max = 0) {
  size = AlignDown<SI8, SIZ>(size);
  count_max = AlignDown<SI8, UIY>(count_max);
  SIZ size_min = MapSizeBoundsLower<SIZ, UIY, I>();
  UIY count_min = MapCountBoundsLower<SIZ, UIY, I>();
  if (size < size_min || count_max < count_min) {
    size = size_min;
    count_max = size_min;
  }

  UIW* socket = new UIW[size >> kWordBitCount];
  TMap<SIZ, UIY, I>* map = reinterpret_cast<TMap<SIZ, UIY, I>*>(socket);
  map->size = size;
  map->table_size = 0;
  map->size_pile = 0;
  map->count = 0;
  map->count_max = count_max;
  return socket;
}

template <typename UIY>
UIY MapCountUpperBounds() {
  enum {
    kCountUpperBounds = sizeof(UIY) == 1
                            ? 120
                            : sizeof(UIY) == 2
                                  ? 8 * 1024
                                  : sizeof(UIY) == 4 ? 512 * 1024 * 1024 : 0
  };
  return CountUpperBounds;
}

/* Insets the given key-type-value tuple.
 */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
UIY MapInsert(TMap<SIZ, UIY, I>* map, void* value, SI4 type, UIY index) {
  A_ASSERT(map);
  A_ASSERT(value);

  return count;
}

/* Deletes the map contents without wiping the contents. */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
void MapClear(TMap<SIZ, UIY, I>* map) {
  A_ASSERT(map);

  map->count = 0;
  map->size_pile = 0;
}

/* Deletes the map contents by overwriting it with zeros. */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
void MapWipe(TMap<SIZ, UIY, I>* map) {
  A_ASSERT(map);

  SIZ size = map->size;
  MemoryWipe(reinterpret_cast<CH1*>(map) + sizeof(TMap<SIZ, UIY, I>), size);
}

/* Returns true if this crabs contains only the given address. */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
BOL MapContains(TMap<SIZ, UIY, I>* map, void* value) {
  A_ASSERT(map);

  if (value < map) return false;
  if (value > GetEndAddress()) return false;
  return true;
}

/* Removes the item at the given address from the map. */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
BOL MapRemove(TMap<SIZ, UIY, I>* map, void* adress) {
  A_ASSERT(map);

  return false;
}

/* Prints this object out to the console. */
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2,
          typename Char = CHR>
TSPrinter<Char>& MapPrint(TSPrinter<Char>& o, const TMap<SIZ, UIY, I>* map) {
  A_ASSERT(map)
  l

      UIY count = map->count,
          collision_index, temp;
  SIZ table_size = map->table_size, size_pile = map->size_pile;

  o << Linef("\n+---") << "\nMap" << sizeof(SIZ) << ": " << Hex<>(map)
    << " count:" << count << "size_pile:" << size_pile << " size:" << map->size;
  o << "\n|";

  return o << '_' << Socket(reinterpret_cast<const CH1*>(map), map->size)
           << kLF;
}

/* C++ Wrapper for the AsciiMap that uses dynamic memory and auto-grows.

    @code
    .
    .
    .
    @endcode
*/
template <typename SIZ = UI4, typename UIY = SI4, typename I = SI2>
class AMap {
 public:
  /* Constructs a Map with the given count_max.
  If count_max is less than 0 it will be set to the default value. If the
  */
  AMap(SIZ size = 0, I count_max = 0)
      : socket(MapNew<SIZ, UIY, I>(size, count_max)) {
    // Nothing to do here! (:-)-+=<
  }

  /* Destructs the dynamically allocated socket. */
  ~AMap() { delete socket; }

  inline BOL Remove(void* adress) {
    return MapRemove<SIZ, UIY, I>(AArray(), adress);
  }

  /* Checks if the map contains the given pointer.
      @return True if the pointer lies in this socket. */
  inline BOL Contains(void* value) {
    return MapContains<SIZ, UIY, I>(AArray(), value);
  }

  /* Wipes the map by overwriting it with zeros. */
  inline void Wipe() { MapWipe<SIZ, UIY, I>(AArray()); }

  static inline UIY CountUpperBounds() {
    return MapCountUpperBounds<SIZ, UIY, I>();
  }

  inline UIY Insert(void* value, UIY index, SI4 type) {
    return MapInsert<SIZ, UIY, I>(AArray(), value, type, index);
  }

  /* Clears the list. */
  inline void Clear() { MapClear<SIZ, UIY, I>(AArray()); }

  /* Prints this object to a printer. */
  template <typename Printer>
  inline Printer& Print(Printer& o) {
    return TMapPrint<SIZ, UIY, I>(o, This());
  }

 private:
  UIW* socket;

  /* Returns the socket casted as a TMap<SIZ, UIY, I>*. */
  inline TMap<SIZ, UIY, I>* AArray() {
    return reinterpret_cast<TMap<SIZ, UIY>*>(socket);
  }
};  //< class Map
}  // namespace _

#endif  //< INCLUDED_CRAPS_TMAP
#endif  //< #if SEAM >= SCRIPT2_LIST
