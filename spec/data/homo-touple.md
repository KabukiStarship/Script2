# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### Homo-vector

A Homo-vector (Homogenous Vector) is a Vector of homogeneous types of length 1, 2, 3, or 4. Homogeneous Vectors are created when the Vector bits are set to zero where the number of homogenous types in the set are determined by the SW (Size Width) one is added to the SW value to store the number of vector elements.

***Bit Pattern***

2-byte types can be used created a Core Type or a map one Core Type to another such as a ST1_FP4 (UTF-8 string-to-float) map or a CH1_BOL (char-to-bool) map. To create a single core type set the Size Width (SW) bits of the ASCII Data Types word to 1:

| b8:b7 | b6:b5  | b4:b0 |
|:-----:|:------:|:-----:|
|  SW   |  VHT   |  0-31 |

**[<< Previous Section: B-Sequences](./b-sequences) | [Next Section: Map Types >>](./map_types)**

## Requirements

[1] http://google.com

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
