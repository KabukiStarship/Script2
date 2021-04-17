/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /Set.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-21 Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#include <_Config.h>
#if SEAM >= SCRIPT2_BOOK
#ifndef SCRIPT2_BOOK_DECIMPL
#define SCRIPT2_BOOK_DECIMPL 1
#include "TypeValue.h"
namespace _ {
/*
  @code
  ;
  @endcode
*/
template <typename Index, typename TKey, typename ISZ, typename THash>
struct LIB_MEMBER TCollection {
  ISZ size;          //< Total size of the set.
  TKey table_size,   //< Size of the (optional) key Strings in bytes.
      size_pile;     //< Size of the (optional) collisions pile in bytes.
  Index item_count,  //< Number of items.
      count_max;     //< Max number_ of items that can fit in the header.
};

/* A Type-Value Tuple. */
struct Tuple2 {
  PODType type;  //< The tuple type.
  void* value;   //< The tuple value.
};

/* A Type-Value Tuple. */
struct Tuple3 {
  PODType type;    //< The tuple type.
  void* value;     //< The tuple value.
  const CHA* key;  //< The Tuple key.
};

/* Interface for a Script Set.
Set Types:
| Name       | Code | Description                                 |
|-----------:|:----:|:--------------------------------------------|
|      Array | ARY  | A packed c-style array of POD number_ types. |
|      Stack | STK  | A stack of POD number_ types.                |
|       List | cLST  | A stack of Type-Value tuples.               |
|        Map | cMAP  | A one-to-one map of Id-Value tuples.        |
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
  virtual BOL Push(PODType type, void* value) = 0;

  /* Adds the given Tuple3 to this Set. */
  virtual BOL Push(PODType type, void* value, const CHA* key) = 0;

  /* Merges the given Set into this one. */
  virtual BOL Merge(Collection* collection) = 0;

  /* Removes the given object from this collection. */
  virtual BOL Remove(Tuple2* tuple) = 0;

  /* Removes the given index from this collection. */
  virtual BOL Remove(IUW) = 0;

  /* Removes the given key from this collection (if applicable.). */
  virtual BOL Remove(const CHA* key) = 0;

  /* Gets the element at the given index. */
  virtual void* Get(IUW index) = 0;

  /* Searches for the data of the given type and returns a pointer to it.
      @return Returns nil if the Set does not contain the given data. */
  virtual void* Get(const CHA* key) = 0;

  /* Returns true if this Set contains this given key. */
  virtual IUW FindIndex(const CHA* key) = 0;

  /* Returns true if this Set contains this given Type-Value. */
  virtual IUW FindIndex(PODType type, void* value) = 0;

  /* Gets the ISW of the object being stored. */
  virtual IUW Size() = 0;

  /* Gets the ISW of the object being stored. */
  virtual IUW GetSizeWidth() = 0;
};
}  // namespace _
#endif
#endif
