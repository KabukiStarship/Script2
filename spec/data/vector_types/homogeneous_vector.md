# [SCRIPT Specification](../../readme.md)

## [ASCII Data Specification](../readme.md)

### [Vector Types](./readme.md)

#### Homogenous Vector

A Homogenous Vector is a Vector of homogeneous types of length 2, 3, or 4. Homogeneous Vectors are created using one of the illegal 16-bit types.

***2-byte Bit Pattern***

2-byte types can be used created a Core Type or a map one Core Type to another such as a ST1_FP4 (UTF-8 string-to-float) map or a CH1_BOL (char-to-bool) map. To create a single core type set the Size Width (SW) bits of the ASCII Data Types word to 1:

| b15:b14 |  b13:b9  | b8:b7 | b6:b5  | b4:b0 |
|:-------:|:--------:|:-----:|:------:|:-----:|
|   RW    | Map type | SW=1  | Vector | Core  |

**<< [Previous Section](.md)** | **[Next Section](.md) >>**

## License

Copyright (C) 2014-9 Cale McCollough <http://calemccollough.github.io/>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
