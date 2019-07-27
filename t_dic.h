/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_dic.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#if SEAM >= SCRIPT2_BOOK

#ifndef SCRIPT2_TDIC
#define SCRIPT2_TDIC 1

#include "c_avalue.h"
#include "c_socket.h"

#if SEAM >= SCRIPT2_BOOK
#include "module_debug.inl"
#else
#include "module_release.inl"
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
  We are creating a plug-in LIB_MEMBER. We need to create a dictionary in the
  LIB_MEMBER code, and pass it over to the program. The LIB_MEMBER manages the
  memory for the dictionary. This dictionary might contain several million
  entries, and more than 4GB of data.

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
struct LIB_MEMBER Dictionary {
  Size size;          //< Total size of the set.
  Offset table_size,  //< Size of the (optional) key strings in bytes.
      size_pile;      //< Size of the (optional) collisions pile in bytes.
  Index item_count,   //< Number of items.
      count;          //< Max number_ of items that can fit in the header.
};

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
  kOverheadPerDic2Index = TDicOverheadPerIndex<UI1, UI2, UI2>(),
  kOverheadPerDic4Index = TDicOverheadPerIndex<UI2, UI2, UI4>(),
  kOverheadPerDic8Index = TDicOverheadPerIndex<UI4, UI4, UI8>(),
};

}  // namespace _

#endif  //< SCRIPT2_TDIC
#endif  //< #if SEAM >= SCRIPT2_BOOK
