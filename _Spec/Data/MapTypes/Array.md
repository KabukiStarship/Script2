# Array

ASCII Arrays are C-Style arrays where the number of elements is stored in the header of the array. The number of elements is referred to as the count.

The size of the Array is stored in the number of elements rather than the size in bytes to avoid repetitive calculations.

```C++
template <typename SIZ = ISC>
struct TArray {
  SIZ size;  //< Size of the Array in elements.
};
```

## Memory Layout

```AsciiArt
    +----------------+
    | C-Style Array  |
 ^  |----------------|
 |  |     Header     |
0xN +----------------+
```

**[<< Previous Section: Socket](./Socket) | [Vector Types](./) | [Next Section: Stack >>](./Stack)**

## Requirements

[1] ./

## License

Copyright [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
