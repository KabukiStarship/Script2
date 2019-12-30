# [SCRIPT Specification](../)

## ASCII Data Specification

Automaton Standard Code for Information Interchange (ASCII) Data Types are mimicked after the the American Standard Code for Information Interchange C0 Control Codes using 3 all capitol letters. There are 32 POD Data Types, mimicking the number of ASCII C0 Control Codes. Arrays, Stacks, multi-dimensional matrices, and 2, 3, and 4-homogenous-tuple (homo-tuple) types can be created using the Vector types bit. All data types are word-aligned leaving some illegal Vector types such as an 1-byte Array of 2-byte types. These illegal types are used in order to create 2, 3, and 4-tuple homogeneous Vectors of a type, such as a 4-tuple of 1-byte unsigned integers (IUA).

The Automaton Standard Code for Information Interchange (ASCII) Data Specification provides:

* All of the C++ POD types and year 2038-safe sub-second timestamps.
* Convenient and easy-to-read-and-type 3-letter all-caps abbreviations that POP out around lower_snake_case.
* Types can be represented as 8-bits/256-types for microcontrollers that are forward compatible with 16-bit/64K-types for more powerful processors.
* UTF-8, UTF-16, and UTF-32 Strings.
* B-Sequence - Describes the order and maximum sizes of a Byte-Sequence of ASCII Data.
* Map types:
  * Vector types:
    * Homo-tuples - Create tuples of 2, 3, or 4 of the same POD types.
    * Array - An array with the first word being the element count.
    * Stack - A stack of POD types stored as an array where the second word is the stack count.
    * Matrix - A homogeneous multi-dimensional array with a Stack of dimensions.
  * Loom - A homogeneous array of UTF-8, UTF-16, or UTF-32 strings using a Stack of offsets.
  * Map - A sparse array of one 1, 2, 4, or 8-byte data type to another data type.
  * Table - A Prime Multiple Hash (PMH) associative array that maps unique strings to contiguous integers.
  * Dictionary - A dictionary of heterogeneous types with a Table.
  * Book - A key-value dictionary of heterogeneous types with a Loom rather than a Table for fastest push-back performance and later conversion to a Table.

**[<< Previous Section: SCRIPT Specification](../)  |  [Next Section:Data Types >>](data_types)**

## Requirements

[1] http://google.com

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
