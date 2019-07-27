/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_book.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SCRIPT2_MAP
#ifndef INCLUDED_SCRIPTTBOOK
#define INCLUDED_SCRIPTTBOOK

#include "t_dic.h"

#if SEAM == SCRIPT2_MAP
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

}  // namespace _

#endif  //< INCLUDED_SCRIPTTBOOK
#endif  //< #if SEAM >= SCRIPT2_MAP
