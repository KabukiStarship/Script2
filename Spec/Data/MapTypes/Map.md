# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types]./()

#### Map

A Map is a sparse array map of Sorted Domain Values to Codomain Mappings. Codomain mappings always unsigned integers starting where the highest value integer, 0xF...F or -1 in 2's complement, is always an illegal mapping index. Domain types shall be integer or floating-point types.

##### Set C++ Data Structure

The TMap data structure is identical to the TStack but the two classes are not interoperable due to Memory Layout Requirement.

```C++
template <typename SIZ = ISC>
struct TMap {
  SIZ size,   //< Number of elements in the map.
      count;  //< Number of mappings.
};
```

##### Memory Layout

The Memory Layout Requirement is we are required to first search the sorted domain values before looking up it's Codomain mapping.

```AsciiArt
+-------------------------------+
|_____   Buffer                 |
|_____ ^ Y_n        Codomain    |
|      | Y_0        Mappings    |
+-------------------------------+
|_____   Buffer                 |
|_____ ^ X_n     Sorted Domain  |
|      | X_0         Values     |
+-------------------------------+  ^ Up in addresses.
|          TMap Header          |  |
+-------------------------------+ 0x0
```

**[<< Previous Section:Book](Book.md) | [Next Section: Dictionary >>](Dictionaries.md)**

## Requirements

[1] ./

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
