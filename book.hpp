/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /t_book.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_MAP
#ifndef INCLUDED_SCRIPTTBOOK
#define INCLUDED_SCRIPTTBOOK

#include "dictionary.hpp"

#if SEAM == SCRIPT2_MAP
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {
/* @ingroup Book
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/map_types/book.md
*/

/* A multimap created from contiguous memory.
@ingroup Book
@code
+--------------------------+
|_______ Buffer            |
|_______ Data N            |
|_______ Data 0            |
|--------------------------|
|        Key 1             |
|        ...               |
|        Key N             |
|vvvvvvvvvvvvvvvvvvvvvvvvvv|
|        socket            |
|--------------------------|
|_______ Buffer            |
|_______ Key Offset N      |
|        Key Offset 1      |
|--------------------------|
|_______ Buffer            |
|_______ Type N            |
|        Type 1            |
|--------------------------|
|_______ Buffer            |
|_______ Value Offset N    |
|        Value Offset 1    |
|--------------------------|  ^ Up in addresses
|       TBook Header       |  |
+--------------------------+ 0xN
@endcode

# Memory Overhead

| #Bytes | I | Index | Size | Total | Overhead Per index |
|:------:|:-:|:-----:|:----:|:-----:|:-------------------|
|    2   | 1 |   2   |   2  |   8   |  8 + 3 per index + socket.|
|    4   | 2 |   4   |   4  |   16  | 16 + 5 per index + socket.|
|    8   | 4 |   8   |   8  |   32  | 24 + 9 per index + socket.|

* Sizes shown in bytes.
*/
template <typename SIZ = SIN, typename HSH = UIN,
          typename SIY = SIG typename Char = CHR>
struct TBook {
  TLoom<SIZ>* keys;
};

}  // namespace _

#endif  //< INCLUDED_SCRIPTTBOOK
#endif  //< #if SEAM >= SCRIPT2_MAP
