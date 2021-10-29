# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Vector Types](./)

#### Array

ASCII Arrays are C-Style arrays where the number of elements is stored in the header of the array. The number of elements is referred to as the count. The size of the Array is stored in the number of elements rather to avoid use of division instructions to find the array count.

```C++
template <typename SIZ = ISC>
struct TArray {
  SIZ size;  //< Size of the Array in elements.
};
```

##### Memory Layout

```AsciiArt
    +----------------+
    | C-Style Array  |
 ^  |----------------|
 |  |     Header     |
0xN +----------------+
```

**[<< Previous Section: Socket](./Socket.md) | [Next Section: Stack >>](./Stack.md)**

## Requirements

[1] ./

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
