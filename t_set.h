/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_set.h
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
#if SEAM >= SCRIPT2_5
#ifndef INCLUDED_F2_SET
#define INCLUDED_F2_SET 1

#include "c_asciidata.h"
#include "c_binary.h"

namespace _ {
/*
    @code
    ;
    @endcode
*/
template <typename Index, typename TKey, typename Size, typename THash>
struct SDK TSet {
  Size size;         //< Total size of the set.
  TKey table_size,   //< Size of the (optional) key strings in bytes.
      size_pile;     //< Size of the (optional) collisions pile in bytes.
  Index item_count,  //< Number of items.
      count_max;     //< Max number_ of items that can fit in the header.
};

/* A Type-Value Tuple. */
struct Tuple2 {
  AsciiType type;  //< The tuple type.
  void* value;     //< The tuple value.
};

/* A Type-Value Tuple. */
struct Tuple3 {
  AsciiType type;   //< The tuple type.
  void* value;      //< The tuple value.
  const CH1* key;  //< The Tuple key.
};

/* Interface for a Script Set.
    Set Types:

    | Name       | Code | Description                                 |
    |-----------:|:----:|:--------------------------------------------|
    |      Array | ARY  | A packed c-style array of POD number_ types. |
    |      Stack | STK  | A stack of POD number_ types.                |
    |       List | kLST  | A stack of Type-Value tuples.               |
    |        Map | kMAP  | A one-to-one map of Id-Value tuples.        |
    |   Multimap | kDIC  | A multimap of Key-Value tuples.             |
    | Dictionary | kDIC  | A one-to-one map of Key-Value tuples.       |
    |   Observer | STC  | A Observer with Subscriber List.            |
*/
struct Collection {
  /* Clears the Set without wiping the memory. */
  virtual void Clear() = 0;

  /* Clears the Set and wipes the memory. */
  virtual void Wipe() = 0;

  /* Adds the given Tuple2 to this Set. */
  virtual BOL Push(AsciiType type, void* value) = 0;

  /* Adds the given Tuple3 to this Set. */
  virtual BOL Push(AsciiType type, void* value, const CH1* key) = 0;

  /* Merges the given Set into this one. */
  virtual BOL Merge(Collection* collection) = 0;

  /* Removes the given object from this collection. */
  virtual BOL Remove(Tuple2* tuple) = 0;

  /* Removes the given index from this collection. */
  virtual BOL Remove(UIW) = 0;

  /* Removes the given key from this collection (if applicable.). */
  virtual BOL Remove(const CH1* key) = 0;

  /* Gets the element at the given index. */
  virtual void* Get(UIW index) = 0;

  /* Searches for the data of the given type and returns a pointer to it.
      @return Returns nil if the Set does not contain the given data. */
  virtual void* Get(const CH1* key) = 0;

  /* Returns true if this Set contains this given key. */
  virtual UIW FindIndex(const CH1* key) = 0;

  /* Returns true if this Set contains this given Type-Value. */
  virtual UIW FindIndex(AsciiType type, void* value) = 0;

  /* Gets the size_t of the object being stored. */
  virtual UIW Size() = 0;

  /* Gets the size_t of the object being stored. */
  virtual UIW GetSizeWidth() = 0;

  /*  */
  virtual UTF1& Print(UTF1& out_) = 0;
};
}  // namespace _
#endif  //< #if SEAM >= SCRIPT2_5
#endif  //< INCLUDED_F2_SET
